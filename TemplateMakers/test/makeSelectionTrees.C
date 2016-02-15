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
  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[1].obj.Pt()>20) ) return false;
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
  
  if ( !(psLeps.size() ==3 && tightLeps.size() == 3) ) return false;

  auto objs_for_mht = getsumTLV(psLeps,psJets);
  double MHT_handle = objs_for_mht.Pt();
  double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
  if ( !(metLD_handle> 0.2 ||psJets.size()>3)  ) return false;

  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[1].obj.Pt()>20) ) return false;
  if ( !((tightLeps[0].obj.Pt() + tightLeps[1].obj.Pt() + met[0].obj.Pt())>100.) ) return false; 
  double vetoZmass = pickFromSortedTwoObjKine(tightLeps,"massSFOS",1,91.2);
  if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     
  
  return true;
}

void run_it(TChain* chain, TString output_file)
{

  TMVA::Reader* TMVAReader_;
  Float_t bJet_csv_var;
  Float_t wJet1_csv_var;
  Float_t wJet2_csv_var;
  Float_t wJet1_qgid_var;
  Float_t wJet2_qgid_var;
  Float_t wMass_var;
  Float_t topMass_var;
  Float_t dR_bJet_W_var;
  Float_t dR_j_j_var;
  Float_t top_ratio_var;

  TMVAReader_ = new TMVA::Reader( "!Color:!Silent" );
  // TMVAReader_->AddVariable( "bJet.csv", &bJet_csv_var );
  // TMVAReader_->AddVariable( "wJet1_csv", &wJet1_csv_var );
  // TMVAReader_->AddVariable( "wJet2_csv", &wJet2_csv_var );
  // TMVAReader_->AddVariable( "w_Mass", &wMass_var );
  // TMVAReader_->AddVariable( "top_Mass", &topMass_var );
  // TMVAReader_->AddVariable( "bJet_W_dR", &dR_bJet_W_var );
  // TMVAReader_->AddVariable( "j_j_dR", &dR_j_j_var );
  TMVAReader_->AddVariable( "bJet.csv", &bJet_csv_var );
  TMVAReader_->AddVariable( "wJet1.csv", &wJet1_csv_var );
  TMVAReader_->AddVariable( "wJet2.csv", &wJet2_csv_var );
  TMVAReader_->AddVariable( "w_boson.M()", &wMass_var );
  TMVAReader_->AddVariable( "top_quark.M()", &topMass_var );
  TMVAReader_->AddVariable( "bJet_W_dR", &dR_bJet_W_var );
  TMVAReader_->AddVariable( "jj_dR", &dR_j_j_var );
  TMVAReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG2_ge4j.weights.xml");
  //  TMVAReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG2_notOverTrained_bkgReweight.weights.xml");
  //  TMVAReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG2_no9999pdgids.weights.xml");
  //  TMVAReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG2_attempt.weights.xml");
  
  
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
  vector<ttH::Lepton> *tightMvaBased_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Electron> *tightMvaBased_electrons_intree=0;
  vector<ttH::Muon> *raw_muons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Muon> *tightMvaBased_muons_intree=0;            
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  
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

  vector<ttH::Jet> *top_jets_intree=0;
  vector<ttH::Jet> *other_jets_intree=0;
  double bdt_score_intree = -99.;
  int had_top_present_intree = 0;
  TLorentzVector top_quark_intree;
  TLorentzVector w_boson_intree;
  w_boson_intree.SetPxPyPzE(0,0,0,0);
  top_quark_intree.SetPxPyPzE(0,0,0,0);
  three_lep_tree->Branch("top_jets", &top_jets_intree);
  three_lep_tree->Branch("other_jets", &other_jets_intree);
  three_lep_tree->Branch("top_quark", &top_quark_intree);
  three_lep_tree->Branch("w_boson", &w_boson_intree);
  three_lep_tree->Branch("bdt_score", &bdt_score_intree);
  three_lep_tree->Branch("had_top_present", &had_top_present_intree);
  
  TTree *two_lep_tree = (TTree*)chain->CloneTree(0);
  two_lep_tree->SetName("ss2l_tree");
  two_lep_tree->Branch("top_jets", &top_jets_intree);
  two_lep_tree->Branch("other_jets", &other_jets_intree);
  two_lep_tree->Branch("top_quark", &top_quark_intree);
  two_lep_tree->Branch("w_boson", &w_boson_intree);
  two_lep_tree->Branch("bdt_score", &bdt_score_intree);
  two_lep_tree->Branch("had_top_present", &had_top_present_intree);

  
  Int_t cachesize = 250000000;   //100 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  chainentries = 100000;
  for (int i=0; i<chainentries; i++)
    {
      
      if (i%4000 == 0)
	{
	  float fraction = 100.*i/chainentries;
	  cout << fraction << " % complete" << endl;
	  cout << i << endl;
	}

      chain->GetEntry(i);

      //      if ( (*preselected_jets_intree).size() < 3) continue; 
      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;
      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      bool passes3l = pass3l(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( !(passes2lss || passes3l) || (*preselected_jets_intree).size() < 3 ) continue;
      
      //figure out if a hadronic top is present
      bool isHadronicTopEvent = false;
      had_top_present_intree = 0;
      bdt_score_intree = -99.;
      w_boson_intree.SetPxPyPzE(0,0,0,0);
      top_quark_intree.SetPxPyPzE(0,0,0,0);
      other_jets_intree->clear();
      top_jets_intree->clear();

      vector<ttH::Jet> jetsFromTop;
      vector<ttH::Jet> jetsFromAntiTop;
      vector<ttH::Jet> jetsFromElsewhere;
      ttH::Jet bJet;
      ttH::Jet wJet1;
      ttH::Jet wJet2;
      vector<ttH::Jet> wJetVec;
      
      for (const auto & jet : *preselected_jets_intree)
	{
	  if (jet.genPdgID == 5 && jet.genMotherPdgID == 6) jetsFromTop.push_back(jet);
	  else if (jet.genPdgID == -5 && jet.genMotherPdgID == -6) jetsFromAntiTop.push_back(jet);
	  else if (jet.genMotherPdgID == 24 && jet.genGrandMotherPdgID == 6) jetsFromTop.push_back(jet);
	  else if (jet.genMotherPdgID == -24 && jet.genGrandMotherPdgID == -6) jetsFromAntiTop.push_back(jet);
	  else jetsFromElsewhere.push_back(jet);
	}

      if (jetsFromTop.size() < jetsFromAntiTop.size()) jetsFromTop = jetsFromAntiTop;
      jetsFromAntiTop.clear();
      
      if ( jetsFromTop.size() == 3 )
	{
	  for (const auto & jet: jetsFromTop)
	    {
	      if (abs(jet.genPdgID) == 5) bJet = jet;
	      else wJetVec.push_back(jet);
	    }
	  if (wJetVec[0].obj.pt() > wJetVec[1].obj.pt())
	    {
	      wJet1 = wJetVec[0];
	      wJet2 = wJetVec[1];
	    }
	  else
	    {
	      wJet1 = wJetVec[1];
	      wJet2 = wJetVec[0];
	    }

	  isHadronicTopEvent = true;
	  had_top_present_intree = 1;
	}

      TLorentzVector bjet_vect;
      TLorentzVector wjet1_vect;
      TLorentzVector wjet2_vect;
      TLorentzVector w_candidate_vect;
      TLorentzVector top_candidate_vect;
      int bjet_counter =0;
      for (const auto & bjet: *preselected_jets_intree)
	{
	  bjet_counter +=1;
	  bjet_vect.SetPtEtaPhiE(bjet.obj.pt(), bjet.obj.eta(), bjet.obj.phi(), bjet.obj.E());
	  int wjet1_counter =0;
	  for (const auto & wjet1: *preselected_jets_intree)
	    {
	      wjet1_counter +=1;
	      if (bjet_counter == wjet1_counter) continue;
	      wjet1_vect.SetPtEtaPhiE(wjet1.obj.pt(), wjet1.obj.eta(), wjet1.obj.phi(), wjet1.obj.E());
	      int wjet2_counter =0;
      	      for (const auto & wjet2: *preselected_jets_intree)
		{
		  wjet2_counter +=1;
		  if ( bjet_counter == wjet2_counter || wjet1_counter == wjet2_counter ) continue;
		  wjet2_vect.SetPtEtaPhiE(wjet2.obj.pt(), wjet2.obj.eta(), wjet2.obj.phi(), wjet2.obj.E());
		  w_candidate_vect = wjet1_vect + wjet2_vect;
		  top_candidate_vect = bjet_vect + w_candidate_vect;

		  top_ratio_var = top_candidate_vect.Pt()/(*preselected_jets_intree)[0].obj.pt();

		  double dR = w_candidate_vect.DeltaR( bjet_vect );
		  double dR_jj = wjet1_vect.DeltaR( wjet2_vect );
		  bJet_csv_var = bjet.csv;
		  topMass_var = top_candidate_vect.M();
		  wMass_var = w_candidate_vect.M();
		  dR_bJet_W_var = dR;
		  dR_j_j_var = dR_jj;
		  wJet1_csv_var = wjet1.csv;
		  wJet2_csv_var = wjet2.csv;
		  
		  double mva_value = TMVAReader_->EvaluateMVA( "BDTG method" );
		  if (mva_value > bdt_score_intree)
		    {
		      top_jets_intree->clear();
		      top_jets_intree->push_back(bjet);
		      top_jets_intree->push_back(wjet1);
		      top_jets_intree->push_back(wjet2);
		      top_quark_intree = top_candidate_vect;
		      w_boson_intree = w_candidate_vect;
		      bdt_score_intree = mva_value;
		    }
		}
	    }
	}
      
      for (const auto & jet: *preselected_jets_intree)
	{
	  bool isTopJet = false;
	  for (const auto & topjet: *top_jets_intree)
	    {
	      if (jet.obj.pt() == topjet.obj.pt())
		{
		  isTopJet = true;
		  break;
		}
	    }
	  if (!isTopJet) other_jets_intree->push_back(jet);
	}

      if ( passes2lss ) two_lep_tree->Fill();
      if ( passes3l ) three_lep_tree->Fill();
    }
  
  
  double endtime = get_wall_time();
  
  cout << "took " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  three_lep_tree->Write();
  two_lep_tree->Write();
  copiedfile->Close();

}


void makeSelectionTrees(void)
{
  //TChain *ttw_chain = new TChain("OSTwoLepAna/summaryTree");
  //TChain *tth_chain = new TChain("OSTwoLepAna/summaryTree");
  TChain *tt_chain = new TChain("OSTwoLepAna/summaryTree");
  
  //  TString ttw_file = "ttw_trees_test.root";
  //  TString tth_file = "tth_trees_test.root";
  TString tt_file = "tt_trees_ttbar_76X.root";

  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_1.root");
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_2.root");    
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_3.root");    
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_4.root");    
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_5.root");    
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_6.root");    

  // for (int i=1; i < 165; i++)
  //   {
  //     char filePath[512];
  //     sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125_aMC/160128_161341/0000/tree_BDT_%d.root",i);
  //     tth_chain->Add(filePath);
  //   }
  
  // for (int i=1; i < 203; i++)
  //   {
  //     char filePath[512];
  //     sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125_aMC_extn/160128_161921/0000/tree_BDT_%d.root",i);
  //     tth_chain->Add(filePath);
  //   }
  
  // for (int i=1; i < 81; i++)
  //   {
  //     char filePath[512];
  //     sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/ttHToNonbb_M125_13TeV_powheg_pythia8/crab_ttH125_powheg/160128_160938/0000/tree_BDT_%d.root",i);
  //     tth_chain->Add(filePath);
  //   }
    
  for (int i=1; i < 103; i++)
    {
      char filePath[512];
      sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/ttbar/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_ttbar_run0/160211_125629/0000/tree_BDT2_orig_%d.root",i);
      tt_chain->Add(filePath);
    }

  for (int i=1; i < 25; i++)
    {
      char filePath[512];
      sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/ttbar/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_ttbar_run1/160211_125713/0000/tree_BDT2_orig_%d.root",i);
      tt_chain->Add(filePath);
    }
  
  for (int i=1; i < 120; i++)
    {
      char filePath[512];
      sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/ttbar/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_ttbar_run2/160211_125746/0000/tree_BDT2_orig_%d.root",i);
      tt_chain->Add(filePath);
    }

  for (int i=1; i < 26; i++)
    {
      char filePath[512];
      sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/ttbar/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_ttbar_run3/160211_125815/0000/tree_BDT2_orig_%d.root",i);
      tt_chain->Add(filePath);
    }



  //  run_it(ttw_chain,ttw_file);
  //  run_it(tth_chain,tth_file);
  run_it(tt_chain,tt_file);
}
