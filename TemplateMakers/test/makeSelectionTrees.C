//Charlie Mueller 2/24/2016
#include "variables.h"
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include <cmath>
#include "TLorentzVector.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/LinkDef.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTrees.C+
///
/////////////////////////////////////////


vector<ttH::Lepton> get_collection(vector<ttH::Muon> muObjs, vector<ttH::Electron>eleObjs)
{
  vector<ttH::Lepton> lepCollection(muObjs.begin(),muObjs.end());
  lepCollection.insert(lepCollection.end(),eleObjs.begin(),eleObjs.end());
  std::sort(lepCollection.begin(), lepCollection.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.obj.Pt() > b.obj.Pt();});
  return lepCollection;
}

bool passCommon(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets)
{
  auto taggedjetstight = keepTagged(psJets,"M");
  auto taggedjetsloose = keepUnTagged(psJets,"L");
  
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);

  if (!( psLeps.size() >3 || tightLeps.size()>1)) return false;
  double mindilepmass = getTwoObjKineExtreme(psLeps,"min","mass");   
  if (!(mindilepmass>12)) return false;
  if (!(psLeps[0].obj.Pt()>20 && psLeps[1].obj.Pt()>10)) return false;        
  if (!((psJets).size()>1)) return false;
  if (!( (taggedjetsloose.size()>1) || (taggedjetstight.size()>0) )) return false;

  return true;
}

bool pass2lss(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
  
  if ( !( (psLeps.size() ==2 && tightLeps.size() == 2) || (psLeps.size() == 3 && tightLeps.size() == 2 && psLeps[2].obj.Pt() < tightLeps[1].obj.Pt() ) ) ) return false;

  if (tightLeps[0].charge != tightLeps[1].charge) return false;
  for (auto &ele: tightEles) if (!(ele.isGsfCtfScPixChargeConsistent)) return false;
  for (auto &mu: tightMus) if (!(mu.chargeFlip < 0.2)) return false;
  if ( !( psJets.size()>3 ) ) return false;

  auto objs_for_mht = getsumTLV(psLeps,psJets);
  double MHT_handle = objs_for_mht.Pt();
  double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
  if ( !(metLD_handle> 0.2) ) return false;
  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[1].obj.Pt()>10) ) return false;
  if ( !((tightLeps[0].obj.Pt() + tightLeps[1].obj.Pt() + met[0].obj.Pt())>100.) ) return false; 
  if (tightEles.size() ==2 )
    {
      double vetoZmass = pickFromSortedTwoObjKine(psEles,"mass",1,91.2);
      if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     
    }
  return true;
}

bool pass3l(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
  
  if ( !(tightLeps.size() >= 3) ) return false;

  auto objs_for_mht = getsumTLV(psLeps,psJets);
  double MHT_handle = objs_for_mht.Pt();
  double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
  if ( !(metLD_handle> 0.2 || psJets.size()>3)  ) return false;

  if (psJets.size() < 4)
    {
      if (tightMus.size() == 2)
	{
	  if (tightMus[0].charge != tightMus[1].charge)
	    {
	      if (!(metLD_handle > 0.3)) return false;
	    }
	}
      else if (tightEles.size() == 2)
	{
	  if (tightEles[0].charge != tightEles[1].charge)
	    {
	      if (!(metLD_handle > 0.3)) return false;
	    }
	}
    }

  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[2].obj.Pt()>10) ) return false;
  double vetoZmass = pickFromSortedTwoObjKine(tightLeps,"massSFOS",1,91.2);
  if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     
  
  return true;
}

void run_it(TChain* chain, TString output_file)
{

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  double wgt_intree = -999.;
  double wallTimePerEvent_intree = -99.;  
  int eventnum_intree = -999;
  int higgs_decay_intree = -9999;
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;
  
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *raw_muons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::Lepton> *tight_leptons_sortedByMiniIso_intree=0;  

  
  double max_lep_eta_intree = 0.;
  double min_dr_lep1_jet_intree = 0.;
  double min_dr_lep2_jet_intree = 0.;
  double min_dr_lepIso_jet_intree = 0.;
  double avg_dr_jet_intree = 0.;
  //  double mht_jet25_intree = 0.;

  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("wgt", &wgt_intree);
  chain->SetBranchAddress("wallTimePerEvent", &wallTimePerEvent_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("lumiBlock", &lumiBlock_intree);
  chain->SetBranchAddress("runNumber", &runNumber_intree);
  chain->SetBranchAddress("higgs_decay", &higgs_decay_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);    
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);   
  
  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");
  TTree *three_lep_tree = (TTree*)chain->CloneTree(0);
  three_lep_tree->SetName("threelep_tree");
  three_lep_tree->Branch("max_lep_eta", &max_lep_eta_intree);
  three_lep_tree->Branch("min_dr_lep1_jet", &min_dr_lep1_jet_intree);
  three_lep_tree->Branch("min_dr_lep2_jet", &min_dr_lep2_jet_intree);
  three_lep_tree->Branch("min_dr_lepIso_jet", &min_dr_lepIso_jet_intree);
  three_lep_tree->Branch("avg_dr_jet", &avg_dr_jet_intree);
  three_lep_tree->Branch("tightMvaBased_leptons_sortedMiniIso", &tight_leptons_sortedByMiniIso_intree);
  //  three_lep_top_absent_tree->Branch("mht_jet25", &mht_jet25_intree);

  TTree *two_lep_tree = (TTree*)chain->CloneTree(0);
  two_lep_tree->SetName("ss2l_tree");
  two_lep_tree->Branch("max_lep_eta", &max_lep_eta_intree);
  two_lep_tree->Branch("min_dr_lep1_jet", &min_dr_lep1_jet_intree);
  two_lep_tree->Branch("min_dr_lep2_jet", &min_dr_lep2_jet_intree);
  two_lep_tree->Branch("min_dr_lepIso_jet", &min_dr_lepIso_jet_intree);
  two_lep_tree->Branch("avg_dr_jet", &avg_dr_jet_intree);
  two_lep_tree->Branch("tightMvaBased_leptons_sortedMiniIso", &tight_leptons_sortedByMiniIso_intree);
  //  two_lep_top_absent_tree->Branch("mht_jet25", &mht_jet25_intree);
  
  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  chainentries = 100000;
  for (int i=0; i<chainentries; i++)
    {
      
      max_lep_eta_intree = -99.;
      min_dr_lep1_jet_intree = -99.;
      min_dr_lep2_jet_intree = -99.;
      avg_dr_jet_intree = -99.;

      if (i%10000 == 0)
	{
	  float fraction = 100.*i/chainentries;
	  cout << fraction << " % complete" << endl;
	  cout << i << endl;
	}
      chain->GetEntry(i);

      //////////////////////////
      ////
      //// selection, vetos etc
      ////
      //////////////////////////

      //      if ( (*preselected_jets_intree).size() < 3) continue; 
      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;
      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      bool passes3l = pass3l(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( !(passes2lss || passes3l) ) continue;

      //////////////////////////
      ////
      //// calculation of new vars etc
      ////
      //////////////////////////
      
      tight_leptons_sortedByMiniIso_intree = tight_leptons_intree;
      std::sort(tight_leptons_sortedByMiniIso_intree->begin(), tight_leptons_sortedByMiniIso_intree->end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.miniIso > b.miniIso;}); 
      
      double max_eta = 0.;
      for (const auto lep: *tight_leptons_intree) if (abs(lep.obj.eta()) > max_eta) max_eta = abs(lep.obj.eta());
      max_lep_eta_intree = max_eta;

      double min_dr_lep1 = 99.;
      double min_dr_lep2 = 99.;
      double min_dr_lepIso = 99.;
      TLorentzVector lepIso;
      TLorentzVector lep1;
      TLorentzVector lep2;
      lep1.SetPtEtaPhiE((*tight_leptons_intree)[0].obj.pt(), (*tight_leptons_intree)[0].obj.eta(), (*tight_leptons_intree)[0].obj.phi(), (*tight_leptons_intree)[0].obj.E());
      lepIso.SetPtEtaPhiE((*tight_leptons_sortedByMiniIso_intree)[0].obj.pt(), (*tight_leptons_sortedByMiniIso_intree)[0].obj.eta(), (*tight_leptons_sortedByMiniIso_intree)[0].obj.phi(), (*tight_leptons_sortedByMiniIso_intree)[0].obj.E());

      if ((*tight_leptons_intree).size() ==2) lep2.SetPtEtaPhiE((*tight_leptons_intree)[1].obj.pt(), (*tight_leptons_intree)[1].obj.eta(), (*tight_leptons_intree)[1].obj.phi(), (*tight_leptons_intree)[1].obj.E());
      else if ((*tight_leptons_intree).size() ==3) lep2.SetPtEtaPhiE((*tight_leptons_intree)[2].obj.pt(), (*tight_leptons_intree)[2].obj.eta(), (*tight_leptons_intree)[2].obj.phi(), (*tight_leptons_intree)[2].obj.E());
      int j1 =0;
      double avg_dr = 0;
      int dr_count =0;
      for (const auto & jet: *preselected_jets_intree)
	{
	  TLorentzVector jetv;
	  jetv.SetPtEtaPhiE(jet.obj.pt(), jet.obj.eta(), jet.obj.phi(), jet.obj.E());
	  if ( lep1.DeltaR( jetv ) < min_dr_lep1) min_dr_lep1 = lep1.DeltaR( jetv ); 
	  if ( lep2.DeltaR( jetv ) < min_dr_lep2) min_dr_lep2 = lep2.DeltaR( jetv ); 
	  if ( lepIso.DeltaR( jetv ) < min_dr_lepIso) min_dr_lepIso = lepIso.DeltaR( jetv );


	  int j2 =0;
	  for (const auto & jett: *preselected_jets_intree)
	    {
	  
	      if (j1 <= j2)
		{ 
		  j2+=1;
		  continue;
		}
	      else
		{
		  TLorentzVector jettv;
		  jettv.SetPtEtaPhiE(jett.obj.pt(), jett.obj.eta(), jett.obj.phi(), jett.obj.E());
		  avg_dr += jettv.DeltaR( jetv );
		  dr_count +=1;
		  j2+=1;
		}
	    }
	  j1+=1;
	}
      min_dr_lep1_jet_intree = min_dr_lep1;
      min_dr_lep2_jet_intree = min_dr_lep2;
      min_dr_lepIso_jet_intree = min_dr_lepIso;
      avg_dr_jet_intree = avg_dr/dr_count;
      
      if ( passes2lss ) two_lep_tree->Fill();
      else if ( passes3l ) three_lep_tree->Fill();
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  three_lep_tree->Write();
  two_lep_tree->Write();
  copiedfile->Close();

}

void loadFilesAndRun(TString sample)
{
  
  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  TString file;
  char filePath[512];
  TString file_path;

  if (sample == "ttH")
    {
      file = "ttH_tree.root";

      for (int i=1; i < 170; i++)
      	{
	  char filePath[512];
      	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125_aMC/160219_093049/0000/tree_BDT2_orig_%d.root",i);
      	  chain->Add(filePath);
      	}
      for (int i=1; i < 200; i++)
      	{
	  char filePath[512];
      	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125_aMC_extn/160219_093101/0000/tree_BDT2_orig_%d.root",i);
      	  chain->Add(filePath);
      	}
      for (int i=1; i < 83; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/ttHToNonbb_M125_13TeV_powheg_pythia8/crab_ttH125_powheg/160219_093036/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
    }
  else if (sample == "ttbar")
    {
      file = "ttbar_tree.root";

      for (int i=1; i < 714; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTToSemiLeptonic_13TeV-powheg/crab_TTJets_powheg/160219_093217/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}

      for (int i=1; i < 104; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM3/160219_093153/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
      
      for (int i=1; i < 30; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM4/160219_093206/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
      
      for (int i=1; i < 106; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM1/160219_093129/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
      
      for (int i=1; i < 30; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM2/160219_093141/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
      
      for (int i=1; i < 80; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_ttbar_aMC/160219_093117/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
    }

  else if (sample == "ttW")
    {
      file = "ttW_tree.root";
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_1.root");
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_2.root");    
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_3.root");    
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_4.root");    
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_5.root");    
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_6.root");
    }
  else
    {
      cout << "please specify valid sample name" << endl;
      return;
    }
  
  run_it(chain,file);  
}

void makeSelectionTrees(void)
{

  loadFilesAndRun("ttH");
  // loadFilesAndRun("ttbar");
  // loadFilesAndRun("ttW");

}
