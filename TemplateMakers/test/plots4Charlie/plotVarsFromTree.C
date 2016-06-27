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
#include "TH1I.h"
#include "TCut.h"

void plotVarsFromTree(void)
{

  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/lxbatch_output/ttH_powheg.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/lxbatch_output/ttW.root";


  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_weightedBkgSq/ttH_sum_v2.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_weightedBkgSq/ttbar_sum_v2.root";
  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baselineBdt_v1/ttH_tree.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baselineBdt_v1/ttbar_tree.root";
  
  //TString signal_file = "/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/plots4Charlie/bdtreco_v2/tth_nonbb/charlie_tree_11771.root";
  //TString background_file = "/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/plots4Charlie/bdtreco_v2/ttjets_semilep/charlie_tree_11142.root";

  TString signal_file = "/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/plots4Charlie/bdtreco_v2/tth_nonbb/*.root";
  TString background_file = "/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/plots4Charlie/bdtreco_v2/ttjets_semilep/*.root";

  //  TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/lxbatch_output/ttbar_semiLep_powheg.root";
  
  TChain *chain1 = new TChain("OSTwoLepAna/summaryTree");
  chain1->Add(signal_file);
  TChain *chain2 = new TChain("OSTwoLepAna/summaryTree");
  chain2->Add(background_file);  

/*
  TChain *chain1 = new TChain("OSTwoLepAna/summaryTree");
  chain1->Add(signal_file);
  TChain *chain2 = new TChain("OSTwoLepAna/summaryTree");
  chain2->Add(background_file);
  //  chain2->Add(background_file1);
  //  chain2->Add(background_file2);*/
  TH1D* sig_h = new TH1D("sig_h","sig_h",100,-1.3,1);
  TH1D* bkg_h = new TH1D("bkg_h","bkg_h",100,-1.3,1);
  
  TH1D* mr0_h = new TH1D("mr0_h", "mr0_h", 100, 0, 6);  
  TH1D* mr1_h = new TH1D("mr1_h", "mr1_h", 100, 0, 6);
  TH1D* mr2_h = new TH1D("mr2_h", "mr2_h", 100, 0, 6);
  TH1D* mr3_h = new TH1D("mr3_h", "mr3_h", 100, 0, 6);
  TH1D* mr4_h = new TH1D("mr4_h", "mr4_h", 100, 0, 6);
  TH1D* mr5_h = new TH1D("mr5_h", "mr5_h", 100, 0, 6);
  TH1D* mr6_h = new TH1D("mr6_h", "mr6_h", 100, 0, 6);

  //  TCut cut = "csv_sorted_jets[1].csv < .423 && matched_jets.obj.pt() < 300";
  //  TCut cut = "matched_jets.obj.pt() < 300";
  //TCut cut = "@preselected_jets_uncor.size() >= 4";
  TCut cut = "reco_score > -999.";

  chain1->Draw("reco_score >> sig_h",cut,"goffnorm");
  chain2->Draw("reco_score >> bkg_h",cut,"goffnorm");


  chain1->Draw("matching_results[0] >> mr0_h","","goffnorm");
  chain1->Draw("matching_results[1] >> mr1_h", "", "goffnorm");
  chain1->Draw("matching_results[2] >> mr2_h", "", "goffnorm");
  chain1->Draw("matching_results[3] >> mr3_h", "", "goffnorm");
  chain1->Draw("matching_results[4] >> mr4_h", "", "goffnorm");
  chain1->Draw("matching_results[5] >> mr5_h", "", "goffnorm");
  chain1->Draw("matching_results[6] >> mr6_h", "", "goffnorm");

  // chain1->Draw("higgs.M() >> sig_h","mcwgt*(tightMvaBased_leptons[0].lepMVA > 0.75 && tightMvaBased_leptons[1].lepMVA > 0.75 && higgs.M() > 1)","goffnorm");
  // chain2->Draw("higgs.M() >> bkg_h","mcwgt*(tightMvaBased_leptons[0].lepMVA > 0.75 && tightMvaBased_leptons[1].lepMVA > 0.75 && higgs.M() > 1)","goffnorm");
  // chain1->Draw("higgs.M() >> sig_h","mcwgt*(tightMvaBased_leptons[0].lepMVA > 0.75 && tightMvaBased_leptons[1].lepMVA > 0.75)","goffnorm");
  // chain2->Draw("higgs.M() >> bkg_h","mcwgt*(tightMvaBased_leptons[0].lepMVA > 0.75 && tightMvaBased_leptons[1].lepMVA > 0.75)","goffnorm");

  // chain2->Draw("higgs.Pt() >> bkg_h","mcwgt*(1)","goffnorm");
  // chain1->Draw("higgs.Pt() >> sig_h","mcwgt*(1)","goffnorm");

//   chain1->Draw("(tightMvaBased_leptons[0].miniIso*tightMvaBased_leptons[0].sip3D/tightMvaBased_leptons[0].jetPtRel)
// +(tightMvaBased_leptons[1].miniIso*tightMvaBased_leptons[1].sip3D/tightMvaBased_leptons[1].jetPtRel)
// +(tightMvaBased_leptons[2].miniIso*tightMvaBased_leptons[2].sip3D/tightMvaBased_leptons[2].jetPtRel)
//  >> sig_h","mcwgt*(1)","goffnorm");
  
//   chain2->Draw("(tightMvaBased_leptons[0].miniIso*tightMvaBased_leptons[0].sip3D/tightMvaBased_leptons[0].jetPtRel)
// +(tightMvaBased_leptons[1].miniIso*tightMvaBased_leptons[1].sip3D/tightMvaBased_leptons[1].jetPtRel)
// +(tightMvaBased_leptons[2].miniIso*tightMvaBased_leptons[2].sip3D/tightMvaBased_leptons[2].jetPtRel)
//  >> bkg_h","mcwgt*(1)","goffnorm");

  // chain1->Draw("(tightMvaBased_leptons[0].miniIso*tightMvaBased_leptons[0].sip3D/tightMvaBased_leptons[0].jetPtRel)+(tightMvaBased_leptons[1].miniIso*tightMvaBased_leptons[1].sip3D/tightMvaBased_leptons[1].jetPtRel)>> sig_h","mcwgt*(1)","goffnorm");
  // chain2->Draw("(tightMvaBased_leptons[0].miniIso*tightMvaBased_leptons[0].sip3D/tightMvaBased_leptons[0].jetPtRel)+(tightMvaBased_leptons[1].miniIso*tightMvaBased_leptons[1].sip3D/tightMvaBased_leptons[1].jetPtRel)>> bkg_h","mcwgt*(1)","goffnorm");
  
// MATCHED RESULTS PLOTTING
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  TCanvas* can2 = new TCanvas("can2", "can2");
  can2->SetGrid();

  mr0_h->SetTitle("matching_results[0] - lepton matching");
  mr0_h->GetXaxis()->SetTitle("match number");
  mr0_h->GetYaxis()->SetTitle("normalized units");
  mr0_h->Draw("hist");
  can2->SaveAs("matching_results0.png");

  TCanvas* can3 = new TCanvas("can3", "can3");
  can3->SetGrid();

  mr1_h->SetTitle("matching_results[1] - bJet hadTop");
  mr1_h->GetXaxis()->SetTitle("match number");
  mr1_h->GetYaxis()->SetTitle("normalized units");
  mr1_h->Draw("hist");
  can3->SaveAs("matching_results1.png");

  TCanvas* can4 = new TCanvas("can4", "can4");
  can4->SetGrid();

  mr2_h->SetTitle("matching_results[2] - bJet lepTop");
  mr2_h->GetXaxis()->SetTitle("match number");
  mr2_h->GetYaxis()->SetTitle("normalized units");
  mr2_h->Draw("hist");
  can4->SaveAs("matching_results2.png");  

  TCanvas* can5 = new TCanvas("can5", "can5");
  can5->SetGrid();

  mr3_h->SetTitle("matching_results[3] - q1Jet hadTop");
  mr3_h->GetXaxis()->SetTitle("match number");
  mr3_h->GetYaxis()->SetTitle("normalized units");
  mr3_h->Draw("hist");
  can5->SaveAs("matching_results3.png");

  TCanvas* can6 = new TCanvas("can6", "can6");
  can6->SetGrid();

  mr4_h->SetTitle("matching_results[4] - q2Jet hadTop");
  mr4_h->GetXaxis()->SetTitle("match number");
  mr4_h->GetYaxis()->SetTitle("normalized units");
  mr4_h->Draw("hist");
  can6->SaveAs("matching_results4.png");

  TCanvas* can7 = new TCanvas("can7", "can7");
  can7->SetGrid();

  mr5_h->SetTitle("matching_results[5] - q1Jet WHiggs");
  mr5_h->GetXaxis()->SetTitle("match number");
  mr5_h->GetYaxis()->SetTitle("normalized units");
  mr5_h->Draw("hist");
  can7->SaveAs("matching_results5.png");

  TCanvas* can8 = new TCanvas("can8", "can8");
  can8->SetGrid();

  mr6_h->SetTitle("matching_results[6] - q2Jet WHiggs");
  mr6_h->GetXaxis()->SetTitle("match number");
  mr6_h->GetYaxis()->SetTitle("normalized units");
  mr6_h->Draw("hist");
  can8->SaveAs("matching_results6.png");

// RECO SCORE PLOTTING
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  //  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("can", "can");
  can1->SetGrid();

  sig_h->SetTitle("reco score - 2lss selection");
  //sig_h->SetTitle("Higgs pt - 2lss selection");
  // sig_h->GetXaxis()->SetRangeUser(0.,1.4);
  sig_h->GetXaxis()->SetTitle("bdt score");
  //  sig_h->GetXaxis()->SetTitle("mass [GeV]");
  sig_h->GetYaxis()->SetTitle("normalized units");

  sig_h->SetFillColor(2);  
  bkg_h->SetFillColor(4);
  bkg_h->SetFillStyle(3001);
  sig_h->Draw("hist");
  bkg_h->Draw("histsame");
  
  if (sig_h->GetMaximum() < bkg_h->GetMaximum())
    {
      sig_h->SetMaximum(bkg_h->GetMaximum()*1.1);
    }
  
  TLegend *leg = new TLegend(0.6135057,0.7097458,0.8563218,0.8283898,NULL,"brNDC");
  leg->AddEntry(sig_h,"ttH","F");
  leg->AddEntry(bkg_h,"ttbar","F");
  leg->SetFillColor(0);
  leg->Draw("same");
  can1->SaveAs("reco_score.png");  

  //TCanvas* can2 = new TCanvas("can2", "can2");
  //can2->SetGrid();
  
  //mr0_h->SetTitle("matching_results[0] - lepton matching");
  //mr0_h->Draw("histsame");
  //can2->SaveAs("matching_results0.png");

}


