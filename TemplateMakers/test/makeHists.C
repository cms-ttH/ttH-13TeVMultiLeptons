//Charlie Mueller 4/7/2016
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include <algorithm>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLine.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TPad.h"
#include <cmath>
#include "TLorentzVector.h"
#include "TLegend.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "selection.h"
#include "loadSamples.h"
//#include "plot_formatting/tdrstyle.C"
//#include "plot_formatting/CMS_lumi.C"

/////////////////////////////////////////
///
/// usage: root -l makeHists.C+
///
/////////////////////////////////////////

namespace eventType{ enum eventType{ss2l_ee, ss2l_mumu, ss2l_emu, l3}; }

class PlotObject
{
 private:
  TH1D *hist_eff_ee;
  TH1D *hist_trg_ee;
  TH1D *hist_eff_mm;
  TH1D *hist_trg_mm;
  TH1D *hist_eff_em;
  TH1D *hist_trg_em;
  TH1D *hist_eff_3l;
  TH1D *hist_trg_3l;
  TString axis_title_;
  TString variable_name_;

  void drawCanvas(TH1D *hist_trigger, TH1D *hist_map, eventType::eventType event_type)
  {
    TString can_name = variable_name_ + "_can";
    TString saveName = variable_name_ + "_";
    const char *category;

    if (event_type == eventType::ss2l_ee)
      {
	can_name += "_ee";
	category = "2lss ee";
	saveName += "2lss_ee_trg_closure.png";
      }
    else if (event_type == eventType::ss2l_mumu)
      {
	can_name += "_mm";
	category = "2lss #mu#mu";
	saveName += "2lss_mm_trg_closure.png";
      }
    else if (event_type == eventType::ss2l_emu)
      {
	can_name += "_em";
	category = "2lss e#mu";
	saveName += "2lss_em_trg_closure.png";
      }
    else if (event_type == eventType::l3)
      {
	can_name += "_3l";
	category = "#geq 3l";
	saveName += "3l_trg_closure.png";
      }
    else category = "";

    double x_min = hist_trigger->GetXaxis()->GetXmin();
    double x_max = hist_trigger->GetXaxis()->GetXmax();
    
    hist_trigger->SetTitle("");
    //    TCanvas* can = new TCanvas(can_name, can_name);
    TCanvas* can = new TCanvas(can_name, can_name,10,32,650,530);
    TPad* pad1 = new TPad("pad1","pad1",0,0.35,1,1);
    TLegend *leg = new TLegend(0.6192529,0.7196871,0.8649425,0.8598435);
    //    TLegend *leg = new TLegend(0.4971264,0.7189542,0.7428161,0.8594771);
    TLatex * tex = new TLatex(0.6882184,0.625163, category);
    //TLatex * tex = new TLatex(0.6063218,0.627451, category);
    tex->SetNDC(kTRUE); 
    tex->SetTextFont(42);
    tex->SetTextSize(0.08);
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    pad1->SetBottomMargin(0);
    pad1->Draw();
    pad1->cd();
    hist_trigger->SetStats(0);
    hist_map->SetStats(0);
    hist_trigger->SetLineWidth(2);
    hist_trigger->SetLineColor(kMagenta-3);
    hist_trigger->SetMarkerColor(kMagenta-3);
    hist_map->SetLineWidth(2);
    hist_map->SetLineColor(kGreen+2);
    hist_map->SetMarkerColor(kGreen+2);
    leg->AddEntry(hist_trigger,"trigger selection");
    leg->AddEntry(hist_map,"trigger effiency");
    leg->SetTextFont(62);
    hist_trigger->GetYaxis()->SetTitle("Events");
    hist_trigger->DrawCopy();
    hist_map->DrawCopy("same");
    leg->Draw("same");
    tex->Draw("same");
    can->cd();
    
    TPad* pad2 = new TPad("pad2","pad2",0,0,1,0.35);
    TLine *line = new TLine(x_min, 1., x_max, 1.);
    auto hist_ratio =  *hist_trigger;
    hist_ratio.SetLineWidth(1);
    hist_ratio.Divide(hist_map);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.4);
    pad2->SetGridy();
    pad2->Draw();
    pad2->cd();
    
    hist_ratio.GetYaxis()->SetTitle("sel / eff");
    double offset_fraction = 1.6;//1.6;
    double hist_max = hist_ratio.GetMaximum();
    double hist_min = hist_ratio.GetMinimum();
    double y_max = 1 + offset_fraction*max(abs(hist_max - 1), abs(hist_min - 1 ));
    double y_min = 1 - offset_fraction*max(abs(hist_max - 1), abs(hist_min - 1 )); 
    hist_ratio.GetYaxis()->SetRangeUser( y_min, y_max );
    //    hist_ratio.GetYaxis()->SetRangeUser(0,2);
    hist_ratio.SetLineColor(1);
    hist_ratio.SetMarkerColor(1);
    hist_ratio.GetYaxis()->SetLabelSize(.08);
    hist_ratio.GetXaxis()->SetLabelSize(.12);
    hist_ratio.GetXaxis()->SetTitle(axis_title_);
    hist_ratio.GetXaxis()->SetTitleSize(0.17);
    hist_ratio.GetXaxis()->SetTitleFont(42);
    hist_ratio.GetYaxis()->SetTitleOffset(.4);
    hist_ratio.GetYaxis()->SetTitleSize(.10);
    hist_ratio.GetYaxis()->CenterTitle();
    hist_ratio.DrawCopy("ep");
    line->Draw("same");
    
    can->SaveAs(saveName);
  }
  
  
public:
  PlotObject(){
    
  }//default constructor

  void bookHists(TString hist_title, TString hist_name, TString axis_title, int n_bins, double x_min, double x_max)
  {
    axis_title_ = axis_title;
    variable_name_ = hist_name;
    hist_eff_ee = new TH1D(hist_title,hist_name,n_bins,x_min,x_max);
    hist_trg_ee = new TH1D(hist_title,hist_name,n_bins,x_min,x_max);
    hist_eff_mm = new TH1D(hist_title,hist_name,n_bins,x_min,x_max);
    hist_trg_mm = new TH1D(hist_title,hist_name,n_bins,x_min,x_max);
    hist_eff_em = new TH1D(hist_title,hist_name,n_bins,x_min,x_max);
    hist_trg_em = new TH1D(hist_title,hist_name,n_bins,x_min,x_max);
    hist_eff_3l = new TH1D(hist_title,hist_name,n_bins,x_min,x_max);
    hist_trg_3l = new TH1D(hist_title,hist_name,n_bins,x_min,x_max);    
  }

  void fillHists( eventType::eventType event_type, double fill_value, double eff_wgt, double trg_wgt )
  {
    if (event_type == eventType::ss2l_ee)
      {
	hist_eff_ee->Fill( fill_value, eff_wgt );
	hist_trg_ee->Fill( fill_value, trg_wgt );
      }
    else if (event_type == eventType::ss2l_mumu)
      {
	hist_eff_mm->Fill( fill_value, eff_wgt );
	hist_trg_mm->Fill( fill_value, trg_wgt );
      }
    else if (event_type == eventType::ss2l_emu)
      {
	hist_eff_em->Fill( fill_value, eff_wgt );
	hist_trg_em->Fill( fill_value, trg_wgt );
      }
    else if (event_type == eventType::l3)
      {
	hist_eff_3l->Fill( fill_value, eff_wgt );
	hist_trg_3l->Fill( fill_value, trg_wgt );
      }
  }

  void drawHists(void)
  {
    drawCanvas(hist_trg_ee, hist_eff_ee, eventType::ss2l_ee);
    drawCanvas(hist_trg_em, hist_eff_em, eventType::ss2l_emu);
    drawCanvas(hist_trg_mm, hist_eff_mm, eventType::ss2l_mumu);
    drawCanvas(hist_trg_3l, hist_eff_3l, eventType::l3);
  }
  //public vars go here
  virtual ~PlotObject(){};
};


class TriggerHelper
  {
  private:
    bool pass_trigger_ee;
    bool pass_trigger_emu;
    bool pass_trigger_mumu;
    bool pass_trigger_3l;
    std::vector<string> pass_trigger_vec_ee;
    std::vector<string> pass_trigger_vec_emu;
    std::vector<string> pass_trigger_vec_mumu;
    std::vector<string> pass_trigger_vec_3l;
    vector<ttH::Lepton> tight_leptons;
    bool event_type_set;
    
  public:
    TriggerHelper(){

      event_type_set = false;
      //mumu
      pass_trigger_vec_mumu.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      pass_trigger_vec_mumu.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"); 	
      pass_trigger_vec_mumu.push_back("HLT_IsoMu22_v"); 					
      pass_trigger_vec_mumu.push_back("HLT_IsoTkMu22_v"); 				
      //ee
      pass_trigger_vec_ee.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); 
      pass_trigger_vec_ee.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v"); 
      //emu
      pass_trigger_vec_emu.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"); 
      pass_trigger_vec_emu.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"); 
      pass_trigger_vec_emu.push_back("HLT_IsoMu22_v"); 
      pass_trigger_vec_emu.push_back("HLT_IsoTkMu22_v"); 
      pass_trigger_vec_emu.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v"); 
      //ge3l
      pass_trigger_vec_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v"); 
      pass_trigger_vec_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"); 
      pass_trigger_vec_3l.push_back("HLT_TripleMu_12_10_5_v"); 
      pass_trigger_vec_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v"); 
      pass_trigger_vec_3l.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"); 
      pass_trigger_vec_3l.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"); 
      pass_trigger_vec_3l.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); 
      pass_trigger_vec_3l.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"); 
      pass_trigger_vec_3l.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"); 
      pass_trigger_vec_3l.push_back("HLT_IsoMu22_v"); 
      pass_trigger_vec_3l.push_back("HLT_IsoTkMu22_v"); 
      pass_trigger_vec_3l.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v"); 

    } // default constructor
    
    
    eventType::eventType event_type;


    void setEventType(vector<ttH::Lepton> tight_leptons_)
    {
      tight_leptons = tight_leptons_;
      int ele_count = 0;
      int mu_count = 0;
      for (const auto & lep : tight_leptons_)
	{
	  if ( abs(lep.pdgID) == 11 ) ele_count +=1;
	  else if ( abs(lep.pdgID) == 13 ) mu_count +=1;
	}
      
      if (mu_count == 2 && ele_count == 0) event_type = eventType::ss2l_mumu;
      else if (mu_count == 0 && ele_count == 2) event_type = eventType::ss2l_ee;
      else if (mu_count == 1 && ele_count == 1) event_type = eventType::ss2l_emu;
      else if (mu_count + ele_count >= 3) event_type = eventType::l3;
      event_type_set = true;

    }
    
    bool passesTrigger(std::vector<std::string> trg_vector)
    {
      if ( !event_type_set ) 
	{
	  cout << "Event Type is not set!!!!" << endl;
	  return false;
	}

      pass_trigger_ee = false;
      pass_trigger_emu = false;
      pass_trigger_mumu = false;
      pass_trigger_3l = false;
      
      for (const auto & trigger : trg_vector)
	{

	  for (const auto & trigger_ee : pass_trigger_vec_ee) if ( trigger.find(trigger_ee) != std::string::npos) pass_trigger_ee = true;
	  for (const auto & trigger_mumu : pass_trigger_vec_mumu) if ( trigger.find(trigger_mumu) != std::string::npos) pass_trigger_mumu = true;
      	  for (const auto & trigger_emu : pass_trigger_vec_emu) if ( trigger.find(trigger_emu) != std::string::npos) pass_trigger_emu = true;
      	  for (const auto & trigger_3l : pass_trigger_vec_3l) if ( trigger.find(trigger_3l) != std::string::npos) pass_trigger_3l = true;

	}

      switch(event_type)
	{
	case eventType::ss2l_ee:
	  return pass_trigger_ee;
	  break;
	case eventType::ss2l_mumu:
	  return pass_trigger_mumu;
	  break;
	case eventType::ss2l_emu:
	  return pass_trigger_emu;
	  break;
	case eventType::l3:
	  return pass_trigger_3l;
	  break;
	default:
	  break;
	}      
    }

    double getEfficiency(void)
    {
      if ( !event_type_set ) 
	{
	  cout << "Event Type is not set!!!!" << endl;
	  return -9999.;
	}      

      double l1_pt = tight_leptons[0].obj.pt();
      double l2_pt = tight_leptons[1].obj.pt();
      
      switch(event_type)
	{
	case eventType::ss2l_ee:
	  if (l1_pt < 30 && l2_pt < 25) return 0.78;
	  else if (l1_pt > 30 && l1_pt < 40 && l2_pt < 25) return 0.89;
	  else if (l1_pt > 40 && l2_pt < 25) return 0.92;
	  else if (l1_pt < 40 && l2_pt > 25) return 0.93;
	  else if (l1_pt > 40 && l2_pt > 25) return 0.96;
	  else return 0.;
	  //old maps
	  // if (l1_pt < 30 && l2_pt < 25) return 0.78;
	  // else if (l1_pt > 30 && l1_pt < 40 && l2_pt < 25) return 0.89;
	  // else if (l1_pt > 40 && l2_pt < 25) return 0.92;
	  // else if (l1_pt < 30 && l2_pt > 25) return 0.90;
	  // else if (l1_pt > 30 && l1_pt < 40 && l2_pt > 25) return 0.93;
	  // else if (l1_pt > 40 && l2_pt > 25) return 0.96;
	  break;
	case eventType::ss2l_mumu:
	  if (l2_pt < 20) return 0.92;
	  else return 0.98;
	  // if (l1_pt < 30 && l2_pt < 20) return 0.92;
	  // else if (l1_pt < 30 && l2_pt > 20 ) return 0.98;
	  // else if (l1_pt > 30 && l2_pt < 20 ) return 0.93;
	  // else if (l1_pt > 30 && l2_pt > 20 ) return 0.98;
	  break;
	case eventType::ss2l_emu:
	  if ( l2_pt > 25 ) return 0.96;
	  else if ( l1_pt < 30 && l2_pt < 20 ) return 0.86;
	  else if ( l1_pt > 30 && l2_pt < 20 ) return 0.92;
	  else if ( l1_pt < 30 && l2_pt > 20 && l2_pt < 25 ) return 0.91;
	  else if ( l1_pt > 30 && l2_pt > 20 && l2_pt < 25 ) return 0.93;
	  else return 0.;
	  // if ( l1_pt < 30 && l2_pt < 25 ) return 0.78;
	  // else if ( l1_pt > 30 && l1_pt < 40 && l2_pt < 25 ) return 0.89;
	  // else if ( l1_pt > 30 && l1_pt < 40 && l2_pt > 25 ) return 0.93;
	  // else if ( l1_pt > 40 && l2_pt < 25 ) return 0.92;
	  // else if ( l1_pt < 30 && l2_pt > 25 ) return 0.90;
	  // else if ( l1_pt > 40 && l2_pt > 25 ) return 0.96;
	  break;
	case eventType::l3:
	  if (l1_pt > 25) return 0.99;
	  else return 0.88;
	  // if (l1_pt < 30 && l2_pt < 20) return 0.92;
	  // else if (l1_pt > 30 && l2_pt < 20) return 0.96;
	  // else if (l1_pt < 30 && l2_pt > 20) return 0.98;
	  // else if (l1_pt > 30 && l2_pt > 20) return 0.99;
	  break;
	default:
	  return 0.;
	  break;
	}
    }
    
    virtual ~TriggerHelper(){};
};


template <typename inObj> TLorentzVector setTlv(const inObj inputObj )
{
  TLorentzVector tlv; 
  tlv.SetPxPyPzE( inputObj.obj.px(), inputObj.obj.py(), inputObj.obj.pz(), inputObj.obj.E() );
  return tlv;
}

void run_it(TChain* chain)
{

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double wgt_intree = -999.;
  double wallTimePerEvent_intree = -99.;  
  int eventnum_intree = -999;
  int higgs_decay_intree = -9999;
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;
  std::vector<std::string> *passTrigger_intree=0;

  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *raw_muons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Jet> *preselected_jets_genMatch_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::Lepton> *tight_leptons_sortedByMiniIso_intree=0;  

  //only turn on branches we need -- makes reading tree much faster
  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("mcwgt", wgt_intree);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("preselected_jets.*",1);
  chain->SetBranchStatus("preselected_leptons.*",1);
  chain->SetBranchStatus("tightMvaBased_leptons.*",1);
  chain->SetBranchStatus("met.*",1);
  chain->SetBranchStatus("passTrigger",1);

  chain->SetBranchAddress("mcwgt", &wgt_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);  
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("passTrigger", &passTrigger_intree);

  //init hists
  PlotObject met_plots; met_plots.bookHists("met","MET","E_{T}^{miss} [GeV]",10,0,400);
  PlotObject nJet_plots; nJet_plots.bookHists("nJets","nJets","N(jet, p_{T} > 25 GeV)",10,2,12);
  PlotObject nJet_csvl_plots; nJet_csvl_plots.bookHists("nJets_CSVL","nJets_CSVL","N(jet, p_{T} > 25 GeV, CSVL)",10,2,12);
  PlotObject nJet_csvm_plots; nJet_csvm_plots.bookHists("nJets_CSVM","nJets_CSVM","N(jet, p_{T} > 25 GeV, CSVM)",10,2,12);
  PlotObject dilepPt_plots; dilepPt_plots.bookHists("dilep_pt","dilep_pt","p_{T} (ll) [GeV]",10,0,400);
  PlotObject ht_plots; ht_plots.bookHists("HT","HT","MHT [GeV]",10,0,400);

  //increase memory, faster
  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  TriggerHelper triggerHelper;

  double starttime = get_wall_time();
  //  chainentries = 10000;
  for (int i=0; i<chainentries; i++)
    {
      
      if (i%10000 == 0)
	{
	  float fraction = 100.*i/chainentries;
	  cout << fraction << " % complete" << endl;
	  cout << i << endl;
	}
      chain->GetEntry(i);
      
      //////////////////////////
      ////
      //// calculate new vars
      ////
      //////////////////////////

      triggerHelper.setEventType(*tight_leptons_intree);
      double eff_weight = triggerHelper.getEfficiency() * wgt_intree;
      bool passed_trigger = triggerHelper.passesTrigger(*passTrigger_intree);
      double trg_weight = passed_trigger ? 1.*wgt_intree : 0.; 

      double met_value = (*met_intree)[0].obj.E();
      met_plots.fillHists( triggerHelper.event_type, met_value, eff_weight, trg_weight );
      
      int nJet_value = (*preselected_jets_intree).size();
      nJet_plots.fillHists( triggerHelper.event_type, nJet_value, eff_weight, trg_weight );
      
      TLorentzVector lep1_tlv = setTlv((*tight_leptons_intree)[0]);
      TLorentzVector lep2_tlv = setTlv((*tight_leptons_intree)[1]);
      TLorentzVector dilep_sys = lep1_tlv + lep2_tlv;
      double dilepPt_value = dilep_sys.Pt();
      dilepPt_plots.fillHists( triggerHelper.event_type, dilepPt_value, eff_weight, trg_weight );

      auto mht_tlv = getsumTLV(*preselected_leptons_intree, *preselected_jets_intree);
      double ht_value = mht_tlv.Pt();
      ht_plots.fillHists( triggerHelper.event_type, ht_value, eff_weight, trg_weight );

      auto csvm_preselected_jets = keepTagged(*preselected_jets_intree,"M");
      int nJet_csvm_value = csvm_preselected_jets.size();
      nJet_csvm_plots.fillHists( triggerHelper.event_type, nJet_csvm_value, eff_weight, trg_weight );

      auto csvl_preselected_jets = keepTagged(*preselected_jets_intree,"L");
      int nJet_csvl_value = csvl_preselected_jets.size();
      nJet_csvl_plots.fillHists( triggerHelper.event_type, nJet_csvl_value, eff_weight, trg_weight );
      
    }
  
  met_plots.drawHists();
  nJet_plots.drawHists();
  dilepPt_plots.drawHists();
  ht_plots.drawHists();
  nJet_csvm_plots.drawHists();
  nJet_csvl_plots.drawHists();

  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
}

void makeHists(void)
{

  //  TString input_file_name = "ttH_tree_event_selection_triggerStudies_July20.root";
  TString input_file_name = "ttH_tree_event_selection_triggerStudies_July21_25_15_eeCuts.root";
  TString l3_tree_name = input_file_name+"/l3_tree";

  TChain *chain = new TChain("ss2l_tree");
  chain->Add(input_file_name);
  chain->Add(l3_tree_name);
  run_it(chain);
}

