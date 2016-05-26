// usage: root -l makesimpleplot.C+
#include "variables.h"
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include "TString.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include <cmath>
#include <array>
#include <unordered_map>
//#include "/afs/cern.ch/user/g/gesmith/nicepalette.h"
//#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/objectClasses.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "DataFormats/Math/interface/deltaR.h"

ttH::Lepton findRecoMatch(ttH::GenParticle gen_lep, vector<ttH::Electron> reco_eles, vector<ttH::Muon> reco_mus)
{
  double dR;
  double min_dR = 1000.;
  ttH::Lepton matched_reco_lep;
  
  if (abs(gen_lep.pdgID) == 13)
    {
      for (const auto & mu : reco_mus)
	{
	  dR = reco::deltaR(gen_lep.obj.eta(),gen_lep.obj.phi(),mu.obj.eta(),mu.obj.phi());
	  if (dR < min_dR )
	    {
	      min_dR = dR;
	      matched_reco_lep = mu;
	    }
	}
    }
  else if (abs(gen_lep.pdgID) == 11)
    {
      for (const auto & ele : reco_eles)
	{
	  dR = reco::deltaR(gen_lep.obj.eta(),gen_lep.obj.phi(),ele.obj.eta(),ele.obj.phi());
	  if (dR < min_dR )
	    {
	      min_dR = dR;
	      matched_reco_lep = ele;
	    }
	}
    }
  return matched_reco_lep;
}

std::tuple < vector<ttH::Electron>,vector<ttH::Electron>,vector<ttH::Muon>,vector<ttH::Muon> >
findMatchedCollections(vector<ttH::Lepton> rawPatMatches, vector<ttH::Electron> inputRawEles,vector<ttH::Electron> inputPSEles,vector<ttH::Muon> inputRawMus,vector<ttH::Muon> inputPSMus)
{
  
  vector<ttH::Electron> raw_ele_matches;
  vector<ttH::Muon> raw_mu_matches;
  vector<ttH::Electron> ps_ele_matches;
  vector<ttH::Muon> ps_mu_matches;
  
  for (const auto &rawPatMatch: rawPatMatches)
    {
      if (abs(rawPatMatch.pdgID) == 11)
	{
	  for (const auto & ele : inputRawEles)
	    {
	      if (rawPatMatch.obj.pt() == ele.obj.pt())
		{
		  raw_ele_matches.push_back(ele);
		  break;
		}
	    }
	  for (const auto & ele : inputPSEles)
	    {
	      if (rawPatMatch.obj.pt() == ele.obj.pt())
		{
		  ps_ele_matches.push_back(ele);
		  break;
		}
	    } 
	}
      else if (abs(rawPatMatch.pdgID) == 13)
	{
	  for (const auto & mu : inputRawMus)
	    {
	      if (rawPatMatch.obj.pt() == mu.obj.pt())
		{
		  raw_mu_matches.push_back(mu);
		  break;
		}
	    }
	  for (const auto & mu : inputPSMus)
	    {
	      if (rawPatMatch.obj.pt() == mu.obj.pt())
		{
		  ps_mu_matches.push_back(mu);
		  break;
		}
	    } 
	}
    }  
  return std::make_tuple(raw_ele_matches,ps_ele_matches,raw_mu_matches,ps_mu_matches);
}

void lepMultiplicity(TH1D* hist, string title)
{
  std::cout << title << " multiplicity:" << std::endl;
  for (int i = 1; i <= hist->GetNbinsX(); i++)
    {
      std::cout << i-1 << " leps: " << hist->GetBinContent(i) << " %" <<std::endl;
    }
}

vector<ttH::Lepton> GetCollection (vector<ttH::Muon> muObjs, vector<ttH::Electron>eleObjs)
{
  vector<ttH::Lepton> lepCollection(muObjs.begin(),muObjs.end());
  lepCollection.insert(lepCollection.end(),eleObjs.begin(),eleObjs.end());
  std::sort(lepCollection.begin(), lepCollection.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.obj.Pt() > b.obj.Pt();});
  return lepCollection;
}

void preselectionEff(vector<ttH::Muon> muObjs, vector<int>* cut_vec_mu_int, int* raw_mu_size, vector<ttH::Electron> eleObjs, vector<int>* cut_vec_ele_int, int* raw_ele_size)
{
  vector<bool> cut_vec_ele_bool (7,false);
  vector<bool> cut_vec_mu_bool (7,false);
  for (const auto & ele : eleObjs)
    {
      //	  if (abs(ele.genMotherPdgID) == 15 || abs(ele.genMotherPdgID) == 23 || abs(ele.genMotherPdgID) == 24)
      //{
      cut_vec_ele_bool[0] = (ele.obj.pt() > 7);
      cut_vec_ele_bool[1] = (abs(ele.obj.eta()) < 2.5);
      cut_vec_ele_bool[2] = (ele.numMissingInnerHits <= 1);
      cut_vec_ele_bool[3] = (ele.dxy < 0.05);
      cut_vec_ele_bool[4] = (ele.dz < 0.1);
      cut_vec_ele_bool[5] = (ele.miniIso < 0.4);
      
      if (ele.obj.pt() > 10)
	{
	  if (ele.SCeta < 0.8) cut_vec_ele_bool[6] = (ele.mvaID > 0.35);
	  else if (ele.SCeta < 1.479) cut_vec_ele_bool[6] = (ele.mvaID > 0.2);
	  else cut_vec_ele_bool[6] = (ele.mvaID > -0.52);
	}
      else 
	{
	  cut_vec_ele_bool[6] = (false);
	}

      //START count unique cuts only
      // int ele_idx0 =0;
      // int ele_idx1 =0;
      // int index = -1;
      // for (bool cut: cut_vec_ele_bool)
      // 	{
      // 	  if (!cut)
      // 	    {
      // 	      index = ele_idx0;
      // 	      ele_idx1 +=1;
      // 	    }
      // 	  ele_idx0 += 1;
      // 	}
      // if (ele_idx1 == 1) (*cut_vec_ele_int)[index] += 1;

      int ele_idx = 0;
      for (const auto & passCut : cut_vec_ele_bool)
      	{
      	  if (passCut) (*cut_vec_ele_int)[ele_idx] += 1;
      	  ele_idx += 1;
      	}
      *raw_ele_size +=1;
      //}
    }
  for (const auto & mu : muObjs)
    {
      //	  if (abs(mu.genMotherPdgID) == 15 || abs(mu.genMotherPdgID) == 23 || abs(mu.genMotherPdgID) == 24)
      //{
      cut_vec_mu_bool[0] = (mu.obj.pt() > 5);
      cut_vec_mu_bool[1] = (mu.isPFMuon);
      cut_vec_mu_bool[2] = (abs(mu.obj.eta()) < 2.4);
      cut_vec_mu_bool[3] = (mu.isGlobalMuon || mu.isTrackerMuon);
      cut_vec_mu_bool[4] = (mu.dxy < 0.05);
      cut_vec_mu_bool[5] = (mu.dz < 0.1);
      cut_vec_mu_bool[6] = (mu.miniIso < 0.4);
      

      //START count unique cuts only
      // int mu_idx0 =0;
      // int mu_idx1 =0;
      // int index = -1;
      // for (bool cut: cut_vec_mu_bool)
      // 	{
      // 	  if (!cut)
      // 	    {
      // 	      index = mu_idx0;
      // 	      mu_idx1 +=1;
      // 	    }
      // 	  mu_idx0 += 1;
      // 	}
      // if (mu_idx1 == 1) (*cut_vec_mu_int)[index] += 1;
      //END count unique cuts only
      int mu_idx = 0;
      for (const auto & passCut : cut_vec_mu_bool)
      	{
      	  if (passCut) (*cut_vec_mu_int)[mu_idx] += 1;
      	  mu_idx += 1;
      	}
      *raw_mu_size +=1;
	  //}
    }  
}

void pureCuts(vector<bool> cut_vec, vector<int> pure_cut_counts)
{
  bool other_cuts_pass;
  vector<bool> temp_vec = cut_vec;
  for (unsigned int i=0; i <= cut_vec.size(); i++)
    {
      if (!cut_vec[i])
	{
	  pure_cut_counts[i] += 1;
	  // temp_vec = cut_vec;
	  // temp_vec[i] = true;
	  // other_cuts_pass = true;
	  // for (int j=0; j <= temp_vec.size(); j++)
	  //   {
	  //     if (!temp_vec[j])
	  // 	{
	  // 	  other_cuts_pass = false;
	  // 	  break;
	  // 	}
	  //   }
	  // if (other_cuts_pass)
	  //   {
	  //     (*pure_cut_counts)[i] += 1;
	  //     break;
	  //   }
	}
    }
}

void fill_2D(TH2D *hist, double maxPt, double minPt, int wgt, double xBinSz, double yBinSz)
{
  for (double x=maxPt; x >= 0.; x-= xBinSz)
    {
      for (double y=minPt; y >= 0.; y-= yBinSz)
	{
	  hist->Fill(x,y,wgt);
	}
    }
}

void draw_2D(TH2D *hist, int counts)
{
  hist->Scale(100./counts);
  hist->SetStats(0);
  hist->GetXaxis()->SetTitle("leading lepton pT");
  hist->GetYaxis()->SetTitle("trailing lepton pT");  
  TCanvas *canvas = new TCanvas(hist->GetTitle(),"gen lepton pTs",150,10,990,660);
  hist->Draw("COLZ,TEXT");
  //hist->Draw("COLZ");
  //std::string canvasTitle = hist->GetTitle().c_str() + ".png";
  //canvas->SaveAs(canvasTitle.c_str());
}

void makesimpleplot(void)
{
  //  set_plot_style();
  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_1.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_10.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_11.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_12.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_13.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_14.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_15.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_16.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_17.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_18.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_19.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_2.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_20.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_3.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_4.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_5.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_6.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_7.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_8.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_9.root");

  int chainentries = chain->GetEntries();   
  cout << "tree entries: " << chainentries << endl;  
  
  Int_t cachesize = 100000000;   //100 MBytes
  chain->SetCacheSize(cachesize);   //<<<
  chain->SetCacheLearnEntries(20); 
  
  double mcwgt_intree = -999.;
  double wgt_intree = -999.;
  int hDecay_intree = -999;
  int eventNum_intree = -999;

  vector<ttH::GenParticle> *pruned_genParticles_intree = 0; 
  vector<ttH::Electron> *raw_electrons_intree = 0; 
  vector<ttH::Electron> *preselected_electrons_intree = 0; 
  vector<ttH::Electron> *tight_electrons_intree = 0; 
  vector<ttH::Muon> *raw_muons_intree = 0; 
  vector<ttH::Muon> *preselected_muons_intree = 0; 
  vector<ttH::Muon> *tight_muons_intree = 0; 
  vector<ttH::Lepton> *tight_leptons_intree = 0; 
  vector<ttH::Lepton> *preselected_leptons_intree = 0; 
  vector<ttH::Lepton> raw_leptons;
  
  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("wgt", &wgt_intree);
  chain->SetBranchAddress("eventnum", &eventNum_intree);
  chain->SetBranchAddress("higgs_decay", &hDecay_intree);
  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);
  chain->SetBranchAddress("raw_electrons", &raw_electrons_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("raw_muons", &raw_muons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);

  int positiveCharge;
  int negativeCharge;
  double leadPt;
  double trailPt;

  int duplicate = 0;
  int total_count = 0;
  int ss2l_reco_count =0;
  int ss2l_reco_agree_count =0;
  int ss2l_gen_count =0;
  int ss2l_ee_gen_count =0;
  int ss2l_mm_gen_count =0;
  int ss2l_em_gen_count =0;
  int ss2l_me_gen_count =0;
  int l3_reco_count =0;
  int l3_reco_agree_count =0;
  int l3_gen_count =0;
  int l4_reco_count =0;
  int l4_reco_agree_count =0;
  int l4_gen_count =0;

  int ss2l_PS_count = 0;
  int ss2l_raw_count = 0;
  int l3_PS_count = 0;
  int l3_raw_count = 0;
  int l4_PS_count = 0;
  int l4_raw_count = 0;
  
  int wgt;

  //pure rate study
  vector<int> cut_vec_ele_int (7,0);
  vector<int> cut_vec_mu_int (7,0);
  int raw_ele_size = 0;
  int raw_mu_size = 0;
    
  //2D plot vars
  vector<ttH::GenParticle> genMuons;
  vector<ttH::GenParticle> genElectrons;   
  vector<ttH::GenParticle> genLeptonsMatched;   
  vector<ttH::GenParticle> genLeptonsUnmatched;   

  int xRange = 40;
  int yRange = 40;
  int xBins = 20;
  int yBins = 20;
  int xBinSize = xRange/xBins; 
  int yBinSize = yRange/yBins; 

  TH2D *pT_hist_2lss = new TH2D("leading and trailing lepton pT 2lss","2lss",xBins,0,xRange,yBins,0,yRange); 
  TH2D *pT_hist_2lss_ee = new TH2D("leading and trailing lepton pT 2lss","2lss ee",xBins,0,xRange,yBins,0,yRange); 
  TH2D *pT_hist_2lss_mm = new TH2D("leading and trailing lepton pT 2lss","2lss mumu",xBins,0,xRange,yBins,0,yRange); 
  TH2D *pT_hist_2lss_em = new TH2D("leading and trailing lepton pT 2lss","2lss e mu",xBins,0,xRange,yBins,0,yRange); 
  TH2D *pT_hist_2lss_me = new TH2D("leading and trailing lepton pT 2lss","2lss mu e",xBins,0,xRange,yBins,0,yRange); 

  TH2D *pT_hist_3l = new TH2D("leading and trailing lepton pT 3l","3l",xBins,0,xRange,yBins,0,yRange); 
  TH2D *pT_hist_4l = new TH2D("leading and trailing lepton pT 4l","4l",xBins,0,xRange,yBins,0,yRange); 

  TH1D *pT_hist_matched = new TH1D("pT","pT matched",100,0,200);
  TH1D *pT_hist_unmatched = new TH1D("pT","pT unmatched",100,0,200);
  TH1D *eta_hist_matched = new TH1D("delta R","dR between matched gen-reco",50,0,0.075);

  TH1D *id_hist_matched = new TH1D("pdgID","pdgID of un matched PS lep",20,0,20);
  TH1D *id_hist_matched_parent = new TH1D("pdgID","pdgID of un matched PS lep grandparent",600,0,600);

  TH1D *charge_hist_2lss = new TH1D("charge","extra lep charge symmetry between 2lss",5,-2,3);
  TH1D *pt_hist_2lss = new TH1D("pt","extra lep pt ordering between 2lss",7,-2,5);

  TH1D *hist_numPsLeps_2lss = new TH1D("PS lepton multiplicity","PS lepton multiplicity 2lss",8,0,8);
  TH1D *hist_numPsLeps_3l = new TH1D("PS lepton multiplicity","PS lepton multiplicity 3l",8,0,8);
  TH1D *hist_numPsLeps_4l = new TH1D("PS lepton multiplicity","PS lepton multiplicity 4l",8,0,8);

  for (int i=0; i<chainentries; i++)
    {
      //report every 40k events
      //if (i == 1000) break; //testing feature
      if (i % 10000 == 0) std::cout << int(100.*i/chainentries) << "% of events processed" << std::endl; 

      chain->GetEntry(i);

      if (mcwgt_intree > 0) wgt =1;
      else wgt =-1;
      total_count +=wgt;

      positiveCharge = 0;
      negativeCharge = 0;
      vector<ttH::GenParticle> signalLeps;   
      
      for (const auto & genParticle : *pruned_genParticles_intree)
      	{
	  if ((abs(genParticle.pdgID) == 11 && genParticle.obj.pt() > 0) || (abs(genParticle.pdgID) == 13 && genParticle.obj.pt() > 0) )
      	    {
	      if (genParticle.isPromptFinalState || genParticle.isDirectPromptTauDecayProductFinalState)
      		{
      		  if  (genParticle.pdgID > 0) positiveCharge +=1;
      		  if  (genParticle.pdgID < 0) negativeCharge +=1;
		  if (abs(genParticle.pdgID) == 11) genElectrons.push_back(genParticle);
		  if (abs(genParticle.pdgID) == 13) genMuons.push_back(genParticle);
		  signalLeps.push_back(genParticle);
      		}
      	    }
      	}

      bool found_duplicate = false;
      vector<ttH::Lepton> raw_matches;      
      for (auto &promptGenLep: signalLeps)
	{
	  ttH::Lepton match = findRecoMatch(promptGenLep, *raw_electrons_intree, *raw_muons_intree);
	  for (auto & raw_match: raw_matches)
	    {
	      if (match.obj.pt() == raw_match.obj.pt())
		{
		  duplicate+=wgt;
		  found_duplicate = true;
		  break;
		}
	    }
	  if (found_duplicate) break;
	  else raw_matches.push_back(match);
	}
      if (found_duplicate) continue;      
      raw_leptons = GetCollection(*raw_muons_intree,*raw_electrons_intree);

      auto matchedLepTuple = findMatchedCollections(raw_matches,*raw_electrons_intree,*preselected_electrons_intree,*raw_muons_intree,*preselected_muons_intree);
      vector<ttH::Electron> matched_raw_electrons = std::get<0>(matchedLepTuple); 
      vector<ttH::Electron> matched_ps_electrons = std::get<1>(matchedLepTuple); 
      vector<ttH::Muon> matched_raw_muons = std::get<2>(matchedLepTuple); 
      vector<ttH::Muon> matched_ps_muons = std::get<3>(matchedLepTuple); 
      vector<ttH::Lepton> ps_matches = GetCollection(matched_ps_muons,matched_ps_electrons);
      

      
      //2lss
      if ((positiveCharge == 2 && negativeCharge == 0) || (negativeCharge ==2 && positiveCharge == 0)) //2lss
	{
	  
	  ttH::Lepton leadMatch = findRecoMatch(signalLeps[0], *raw_electrons_intree, *raw_muons_intree);
	  ttH::Lepton trailMatch = findRecoMatch(signalLeps[1], *raw_electrons_intree, *raw_muons_intree);
	  leadPt = leadMatch.obj.pt();
	  trailPt = trailMatch.obj.pt();

	  vector<ttH::Lepton> raw_matches;	  
	  raw_matches.push_back(leadMatch);
	  raw_matches.push_back(trailMatch);
	  
	  if (leadPt == trailPt)
	    { 
	      duplicate += wgt;
	      continue;
	    }
	  
	  hist_numPsLeps_2lss->Fill(preselected_leptons_intree->size()*wgt);

	  auto matchedLepTuple = findMatchedCollections(raw_matches,*raw_electrons_intree,*preselected_electrons_intree,*raw_muons_intree,*preselected_muons_intree);
	  vector<ttH::Electron> matched_raw_electrons = std::get<0>(matchedLepTuple); 
	  vector<ttH::Electron> matched_ps_electrons = std::get<1>(matchedLepTuple); 
	  vector<ttH::Muon> matched_raw_muons = std::get<2>(matchedLepTuple); 
	  vector<ttH::Muon> matched_ps_muons = std::get<3>(matchedLepTuple); 
	  vector<ttH::Lepton> ps_matches = GetCollection(matched_ps_muons,matched_ps_electrons);
	  
	  ss2l_PS_count += ps_matches.size()*wgt;
	  ss2l_raw_count += raw_matches.size()*wgt;
	  
	  vector<bool> promptVector;
	  vector<bool> promptTauVector;
	  
	  vector<ttH::Lepton> unmatchedPSLeptons;

	  vector<int> motherIdVector;
	  vector<int> grandMotherIdVector;
	  vector<int> unMatchedGrandMotherIdVector;
	  bool lead_ps_raw_match = false;
	  bool trail_ps_raw_match = false;
	  for (const auto & lep : *preselected_leptons_intree)
	    {
	      if (leadMatch.obj.pt() == lep.obj.pt())
		{
		  lead_ps_raw_match = true;
		  motherIdVector.push_back(abs(lep.genMotherPdgID));
		  grandMotherIdVector.push_back(abs(lep.genGrandMotherPdgID));
		  pT_hist_matched->Fill(lep.obj.pt());
		}
	      else if (trailMatch.obj.pt() == lep.obj.pt())
		{
		  trail_ps_raw_match = true;
		  motherIdVector.push_back(abs(lep.genMotherPdgID));
		  grandMotherIdVector.push_back(abs(lep.genGrandMotherPdgID));
		  pT_hist_matched->Fill(lep.obj.pt());
		}
	      else
		{
		  if (preselected_leptons_intree->size() == 3 )
		    {
		      
		      if (lep.charge == leadMatch.charge) charge_hist_2lss->Fill(1);
		      else charge_hist_2lss->Fill(-1);

		      if (lep.obj.pt() < trailMatch.obj.pt() && lep.obj.pt() < leadMatch.obj.pt()) pt_hist_2lss->Fill(-1);
		      else if (lep.obj.pt() > trailMatch.obj.pt() && lep.obj.pt() < leadMatch.obj.pt()) pt_hist_2lss->Fill(1);
		      else if (lep.obj.pt() > leadMatch.obj.pt()) pt_hist_2lss->Fill(3);
		      
		      id_hist_matched->Fill(abs(lep.pdgID));
		    }
		  unmatchedPSLeptons.push_back(lep);
		}
	    }


	  //START For finding the missing PS lepton
	  vector<ttH::Electron> ps_unmatched_raw_electrons; 
	  vector<ttH::Muon> ps_unmatched_raw_muons; 
	  if (!lead_ps_raw_match)
	    {
	      if (abs(leadMatch.pdgID) == 13)
		{
		  for (auto &mu: matched_raw_muons) if (leadMatch.obj.pt() == mu.obj.pt()) ps_unmatched_raw_muons.push_back(mu);
		}
	      else 
		{
		  for (auto &ele: matched_raw_electrons) if (leadMatch.obj.pt() == ele.obj.pt()) ps_unmatched_raw_electrons.push_back(ele);
		}
	    }
	  if (!trail_ps_raw_match)
	    {
	      if (abs(trailMatch.pdgID) == 13)
		{
		  for (auto &mu: matched_raw_muons) if (trailMatch.obj.pt() == mu.obj.pt()) ps_unmatched_raw_muons.push_back(mu);
		}
	      else 
		{
		  for (auto &ele: matched_raw_electrons) if (trailMatch.obj.pt() == ele.obj.pt()) ps_unmatched_raw_electrons.push_back(ele);
		}
	    }
	  
	  preselectionEff(ps_unmatched_raw_muons, &cut_vec_mu_int, &raw_mu_size, ps_unmatched_raw_electrons, &cut_vec_ele_int, &raw_ele_size);
	  //END For finding the missing PS lepton		      

	  motherIdVector.clear();
	  grandMotherIdVector.clear();
	  
	  eta_hist_matched->Fill(reco::deltaR(signalLeps[0].obj.eta(),signalLeps[0].obj.phi(),leadMatch.obj.eta(),leadMatch.obj.phi()));
	  eta_hist_matched->Fill(reco::deltaR(signalLeps[1].obj.eta(),signalLeps[1].obj.phi(),trailMatch.obj.eta(),trailMatch.obj.phi()));
	  
	  fill_2D(pT_hist_2lss,leadPt,trailPt,wgt, xBinSize, yBinSize);
	  ss2l_gen_count += wgt;
	  if (abs(leadMatch.pdgID) == 11)
	    {
	      if (abs(trailMatch.pdgID) == 11)
		{
		  fill_2D(pT_hist_2lss_ee,leadPt,trailPt,wgt, xBinSize, yBinSize);
		  ss2l_ee_gen_count += wgt;
		}
	      else if (abs(trailMatch.pdgID) == 13)
		{
		  fill_2D(pT_hist_2lss_em,leadPt,trailPt,wgt, xBinSize, yBinSize);
		  ss2l_em_gen_count += wgt;
		}
	    }
	  else if (abs(leadMatch.pdgID) == 13)
	    {
	      if (abs(trailMatch.pdgID) == 11)
		{
		  fill_2D(pT_hist_2lss_me,leadPt,trailPt,wgt, xBinSize, yBinSize);
		  ss2l_me_gen_count += wgt;
		}
	      else if (abs(trailMatch.pdgID) == 13)
		{
		  fill_2D(pT_hist_2lss_mm,leadPt,trailPt,wgt, xBinSize, yBinSize);
		  ss2l_mm_gen_count += wgt;
		}
	    }
	  
	  if (tight_leptons_intree->size() == 2 && abs((*tight_leptons_intree)[0].charge+(*tight_leptons_intree)[1].charge) == 2)
	    {
	      // leadPt = (*tight_leptons_intree)[0].obj.pt();
	      // trailPt = (*tight_leptons_intree)[1].obj.pt();
	      // fill_2D(pT_hist_2lss,leadPt,trailPt,wgt, xBinSize, yBinSize);
	      ss2l_reco_agree_count +=wgt;
	    }
	}
      
      else if (positiveCharge+negativeCharge == 3) //3l
      	{
	  l3_PS_count += preselected_leptons_intree->size()*wgt;
	  l3_raw_count += raw_leptons.size()*wgt;

	  hist_numPsLeps_3l->Fill(preselected_leptons_intree->size()*wgt);
      	  ttH::Lepton leadMatch = findRecoMatch(signalLeps[0], *raw_electrons_intree, *raw_muons_intree);
	  ttH::Lepton subLeadMatch = findRecoMatch(signalLeps[1], *raw_electrons_intree, *raw_muons_intree);
      	  ttH::Lepton trailMatch = findRecoMatch(signalLeps[2], *raw_electrons_intree, *raw_muons_intree);

	  vector<ttH::Lepton> raw_matches;	  
	  raw_matches.push_back(leadMatch);
	  raw_matches.push_back(subLeadMatch);
	  raw_matches.push_back(trailMatch);
	  
	  if (leadMatch.obj.pt() == subLeadMatch.obj.pt() ||
	      subLeadMatch.obj.pt() == trailMatch.obj.pt() || 
	      leadMatch.obj.pt() == trailMatch.obj.pt())
	    {
	      duplicate += wgt;
	      continue;	      
	    }


      	  // leadPt = leadMatch.obj.pt();
      	  // trailPt = trailMatch.obj.pt();
      	  // leadPt = signalLeps[0].obj.pt();
      	  // trailPt = signalLeps[2].obj.pt();	  
      	  // fill_2D(pT_hist_3l,leadPt,trailPt,wgt, xBinSize, yBinSize);
      	  // pT_hist_matched->Fill(abs(signalLeps[0].obj.pt()-leadPt));
      	  // pT_hist_matched->Fill(abs(signalLeps[2].obj.pt()-trailPt));
      	  // eta_hist_matched->Fill(deltaR(signalLeps[0],leadMatch));
      	  // eta_hist_matched->Fill(deltaR(signalLeps[2],trailMatch));

      	  l3_gen_count += wgt;
      	  if (tight_leptons_intree->size() == 3)
      	    {
      	      // leadPt = (*tight_leptons_intree)[0].obj.pt();
      	      // trailPt = (*tight_leptons_intree)[2].obj.pt();
      	      // fill_2D(pT_hist_3l,leadPt,trailPt,wgt, xBinSize, yBinSize);
      	      l3_reco_agree_count +=wgt;	      
      	    }
      	}
      else if (positiveCharge+negativeCharge >= 4) //4l
      	{
	  l4_PS_count += preselected_leptons_intree->size()*wgt;
	  l4_raw_count += raw_leptons.size()*wgt;

	  hist_numPsLeps_4l->Fill(preselected_leptons_intree->size()*wgt);
      	  // ttH::Lepton leadMatch = findRecoMatch(signalLeps[0], *raw_electrons_intree, *raw_muons_intree);
      	  // ttH::Lepton trailMatch = findRecoMatch(signalLeps[3], *raw_electrons_intree, *raw_muons_intree);
      	  // leadPt = leadMatch.obj.pt();
      	  // trailPt = trailMatch.obj.pt();
	  //      	  leadPt = signalLeps[0].obj.pt();
	  //      	  trailPt = signalLeps[3].obj.pt();	  
	  //      	  fill_2D(pT_hist_4l,leadPt,trailPt,wgt, xBinSize, yBinSize);
      	  // pT_hist_matched->Fill(abs(signalLeps[0].obj.pt()-leadPt));
      	  // pT_hist_matched->Fill(abs(signalLeps[3].obj.pt()-trailPt));
      	  // eta_hist_matched->Fill(deltaR(signalLeps[0],leadMatch));
      	  // eta_hist_matched->Fill(deltaR(signalLeps[3],trailMatch));

      	  l4_gen_count += wgt;
      	  if (preselected_leptons_intree->size() >= 4)
      	    {
      	      // leadPt = (*preselected_leptons_intree)[0].obj.pt();
      	      // trailPt = (*preselected_leptons_intree)[preselected_leptons_intree->size()-1].obj.pt();	  
      	      // fill_2D(pT_hist_4l,leadPt,trailPt,wgt, xBinSize, yBinSize);
      	      l4_reco_agree_count +=wgt;
      	    }
      	}
    }
  std::cout << "event loop complete. drawing hists." << std::endl;

  gStyle->SetOptStat(0);
  //  TCanvas* pT_can = new TCanvas("pt can", "pt can");  
  //  TLegend *pT_leg = new TLegend(0.83,0.66,0.99,0.77,NULL,"brNDC"); 
  //  TLegend *pT_leg = new TLegend(0.83,0.66,0.99,0.77); 
  //  pT_hist_matched->SetLineColor(1);
  //  pT_hist_unmatched->SetLineColor(2);
  //  pT_hist_matched->Scale(1/pT_hist_matched->Integral());
  //  pT_hist_unmatched->Scale(1/pT_hist_unmatched->Integral());
  //  pT_hist_matched->Draw();  
  //  pT_hist_matched->Draw("same");  
  //  pT_leg->AddEntry(pT_hist_matched,"gen-matched","l");
  //  pT_leg->AddEntry(pT_hist_unmatched,"not gen-matched","l");
  //  pT_leg->Draw("same");

  TCanvas* id_can = new TCanvas("id can", "id can");  
  id_hist_matched->Scale(1./id_hist_matched->Integral());
  id_hist_matched->Draw();  
  // TLegend *id_leg = new TLegend(0.83,0.66,0.99,0.77,NULL,"brNDC"); 
  // id_hist_unnmatched->SetLineColor(1);
  // id_hist_unmatched->SetLineColor(2);
  // id_hist_matched->SetLineColor(kBlue);

  //  id_hist_unmatched->Draw("same");  
  //  id_hist_matched->Draw("same");  
  //  id_leg->AddEntry(id_hist_matched,"matched W grandmothers","l");
  //  id_leg->AddEntry(id_hist_unmatched,"un matched W grandmother","l");
  //  id_leg->AddEntry(id_hist_unnmatched,"both matched","l");
  //  id_leg->Draw("same");

  TCanvas* charge_can1 = new TCanvas("charge can1", "charge can1");  
  charge_hist_2lss->Scale(1./charge_hist_2lss->Integral());
  charge_hist_2lss->Draw();

  TCanvas* pt_can1 = new TCanvas("pt can1", "pt can1");  
  pt_hist_2lss->Scale(1./pt_hist_2lss->Integral());
  pt_hist_2lss->Draw();

  TCanvas* id_can1 = new TCanvas("id can1", "id can1");  
  id_hist_matched_parent->Scale(1./id_hist_matched_parent->Integral());
  id_hist_matched_parent->Draw();  

  TCanvas* pT_can = new TCanvas("pt can", "pt can");  
  TLegend *pT_leg = new TLegend(0.83,0.66,0.99,0.77,NULL,"brNDC"); 
  pT_hist_matched->SetLineColor(1);
  pT_hist_unmatched->SetLineColor(2);
  //pT_hist_matched->Scale(1/pT_hist_matched->Integral());
  //  pT_hist_unmatched->Scale(1/pT_hist_unmatched->Integral());
  pT_hist_matched->Draw();  
  pT_hist_unmatched->Draw("same");  
  pT_leg->AddEntry(pT_hist_matched,"matched","l");
  pT_leg->AddEntry(pT_hist_unmatched,"not matched","l");
  pT_leg->Draw("same");

  TCanvas* can_numPS2 = new TCanvas("num can2", "num can2");  
  hist_numPsLeps_2lss->Scale(1./hist_numPsLeps_2lss->Integral());
  lepMultiplicity(hist_numPsLeps_2lss, "2lss");
  hist_numPsLeps_2lss->Draw();

  TCanvas* can_numPS3 = new TCanvas("num can3", "num can3");  
  hist_numPsLeps_3l->Scale(1./hist_numPsLeps_3l->Integral());
  lepMultiplicity(hist_numPsLeps_3l, "3l");
  hist_numPsLeps_3l->Draw();

  TCanvas* can_numPS4 = new TCanvas("num can4", "num can4");  
  hist_numPsLeps_4l->Scale(1./hist_numPsLeps_4l->Integral());
  lepMultiplicity(hist_numPsLeps_4l, "4l");
  hist_numPsLeps_4l->Draw();
  

  std::cout << "double matches " << duplicate << std::endl;  

  std::cout << "total_count = " << total_count << std::endl;
  std::cout << "ss2l_reco_count = " << ss2l_reco_count << std::endl;
  std::cout << "ss2l_reco_agree_count = " << ss2l_reco_agree_count << std::endl;
  std::cout << "ss2l_gen_count = " << ss2l_gen_count << std::endl;
  std::cout << "l3_reco_count = " << l3_reco_count << std::endl;
  std::cout << "l3_reco_agree_count = " << l3_reco_agree_count << std::endl;
  std::cout << "l3_gen_count = " << l3_gen_count << std::endl;
  std::cout << " > l4_reco_count = " << l4_reco_count << std::endl;
  std::cout << " > l4_reco_agree_count = " << l4_reco_agree_count << std::endl;
  std::cout << "> l4_gen_count = " << l4_gen_count << std::endl;


  std::cout << "> ss2l_PS_count = " << ss2l_PS_count << std::endl;
  std::cout << "> ss2l_raw_count = " << ss2l_raw_count << std::endl;
  std::cout << "> ss2l_eff = " << ss2l_PS_count/ss2l_raw_count << std::endl;
  std::cout << "> l3_PS_count = " << l3_PS_count << std::endl;
  std::cout << "> l3_raw_count = " << l3_raw_count << std::endl;
  std::cout << "> l3_eff = " << l3_PS_count/l3_raw_count << std::endl;
  std::cout << "> l4_PS_count = " << l4_PS_count << std::endl;
  std::cout << "> l4_raw_count = " << l4_raw_count << std::endl;
  std::cout << "> l4_eff = " << l4_PS_count/l4_raw_count << std::endl;

 

  int i = 0;
  for (int & frac : cut_vec_mu_int)
    {
      std::cout << frac << " " << raw_mu_size << std::endl;
      std::cout << "mu cut # " << i << " is removing: " << 100. - 100.*double(frac)/double(raw_mu_size) << "%" << std::endl;
      //std::cout << "mu cut # " << i << " failed uniquely: " << double(frac)/double(raw_mu_size) << "%" << std::endl;
      i +=1;
    }
  
  int j = 0;
  for (int & frac : cut_vec_ele_int)
    {
      std::cout << frac << " " << raw_mu_size << std::endl;
      std::cout << "ele cut # " << j << " is removing: " << 100. - 100.*double(frac)/double(raw_ele_size) << "%" << std::endl;
      //      std::cout << "ele cut # " << j << " failed uniquely: " << double(frac)/double(raw_ele_size) << "%" << std::endl;
      j +=1;
    }
  
}
