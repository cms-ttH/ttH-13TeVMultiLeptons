#include <iostream>
#include <fstream>
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
#include "TH3D.h"

void plotVarsFromTree(void)
{
  TString signal_file = "/hadoop/store/user/mbeydler/bdtreco_v21/tth_nonbb/*.root";
  //TString background_file = "/hadoop/store/user/mbeydler/bdtreco_v7/ttjets_semilep/*.root";

  //  TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/lxbatch_output/ttbar_semiLep_powheg.root";
  
  TChain *chain1 = new TChain("OSTwoLepAna/summaryTree");
  chain1->Add(signal_file);
 // TChain *chain2 = new TChain("OSTwoLepAna/summaryTree");
 // chain2->Add(background_file);  

  // Writing to a file
  
  ofstream myfile;
  //myfile.open ("~/www/GT6PSUJetsInfo.txt");
  //myfile.open ("~/www/LT6PSUJetsInfo.txt");
  //myfile.open ("~/www/EQ6PSUJetsInfo.txt");

  TH1D* mr0_h = new TH1D("mr0_h", "mr0_h", 5, 0.5, 5.5);  
  TH1D* mr1_h = new TH1D("mr1_h", "mr1_h", 5, 0.5, 5.5);
  TH1D* mr2_h = new TH1D("mr2_h", "mr2_h", 5, 0.5, 5.5);
  TH1D* mr3_h = new TH1D("mr3_h", "mr3_h", 5, 0.5, 5.5);
  TH1D* mr4_h = new TH1D("mr4_h", "mr4_h", 5, 0.5, 5.5);
  TH1D* mr5_h = new TH1D("mr5_h", "mr5_h", 5, 0.5, 5.5);
  TH1D* mr6_h = new TH1D("mr6_h", "mr6_h", 5, 0.5, 5.5);

  TH1D* mr00_h = new TH1D("mr00_h", "mr00_h", 5, 0.5, 5.5);
  TH1D* mr11_h = new TH1D("mr11_h", "mr11_h", 5, 0.5, 5.5);
  TH1D* mr22_h = new TH1D("mr22_h", "mr22_h", 5, 0.5, 5.5);
  TH1D* mr33_h = new TH1D("mr33_h", "mr33_h", 5, 0.5, 5.5);
  TH1D* mr44_h = new TH1D("mr44_h", "mr44_h", 5, 0.5, 5.5);
  TH1D* mr55_h = new TH1D("mr55_h", "mr55_h", 5, 0.5, 5.5);
  TH1D* mr66_h = new TH1D("mr66_h", "mr66_h", 5, 0.5, 5.5);

  TH1D* mr000_h = new TH1D("mr000_h", "mr000_h", 5, 0.5, 5.5);
  TH1D* mr111_h = new TH1D("mr111_h", "mr111_h", 5, 0.5, 5.5);
  TH1D* mr222_h = new TH1D("mr222_h", "mr222_h", 5, 0.5, 5.5);
  TH1D* mr333_h = new TH1D("mr333_h", "mr333_h", 5, 0.5, 5.5);
  TH1D* mr444_h = new TH1D("mr444_h", "mr444_h", 5, 0.5, 5.5);
  TH1D* mr555_h = new TH1D("mr555_h", "mr555_h", 5, 0.5, 5.5);
  TH1D* mr666_h = new TH1D("mr666_h", "mr666_h", 5, 0.5, 5.5);
  //  TCut cut = "csv_sorted_jets[1].csv < .423 && matched_jets.obj.pt() < 300";
  //  TCut cut = "matched_jets.obj.pt() < 300";
  //TCut cut = "@preselected_jets_uncor.size() >= 4";
  //TCut cut = "reco_score > -999.";

  //TCut cut1 = "num_jet_matches_truth == 6 && num_real_jets_bdt == 6"; 
  TCut cut1 = "@preselected_jets_uncor.size() > 6";
  TCut cut3 = "@preselected_jets_uncor.size() < 6";
  TCut cut2 = "@preselected_jets_uncor.size() == 6";

  chain1->Draw("matching_results[0] >> mr0_h", cut1 ,"goffnorm");
  chain1->Draw("matching_results[1] >> mr1_h", cut1, "goffnorm");
  chain1->Draw("matching_results[2] >> mr2_h", cut1, "goffnorm");
  chain1->Draw("matching_results[3] >> mr3_h", cut1, "");
  chain1->Draw("matching_results[4] >> mr4_h", cut1, "");
  chain1->Draw("matching_results[5] >> mr5_h", cut1, "");
  chain1->Draw("matching_results[6] >> mr6_h", cut1, "");

  chain1->Draw("matching_results[0] >> mr00_h", cut2,"goffnorm");
  chain1->Draw("matching_results[1] >> mr11_h", cut2, "goffnorm");
  chain1->Draw("matching_results[2] >> mr22_h", cut2, "goffnorm");
  chain1->Draw("matching_results[3] >> mr33_h", cut2, "");
  chain1->Draw("matching_results[4] >> mr44_h", cut2, "");
  chain1->Draw("matching_results[5] >> mr55_h", cut2, "");
  chain1->Draw("matching_results[6] >> mr66_h", cut2, "");

  chain1->Draw("matching_results[0] >> mr000_h", cut3,"goffnorm");
  chain1->Draw("matching_results[1] >> mr111_h", cut3, "goffnorm");
  chain1->Draw("matching_results[2] >> mr222_h", cut3, "goffnorm");
  chain1->Draw("matching_results[3] >> mr333_h", cut3, "");
  chain1->Draw("matching_results[4] >> mr444_h", cut3, "");
  chain1->Draw("matching_results[5] >> mr555_h", cut3, "");
  chain1->Draw("matching_results[6] >> mr666_h", cut3, ""); 
  
  /* 
  double bin1 = mr1_h->GetBinContent(1);
  double bin2 = mr1_h->GetBinContent(2);
  double bin3 = mr1_h->GetBinContent(3);
  double bin4 = mr1_h->GetBinContent(4);
  double bin5 = mr1_h->GetBinContent(5);

  myfile << "\n             BJET FROM HADTOP";
  myfile << "\n       null BDT        real BDT\n";
  myfile << "-----------------------------------\n";
  myfile << "null:   " << (bin4*100) << "         " << (bin2*100);   
  myfile << "\n";
  myfile << "real:   " << (bin1*100) << "         "  << ((bin5+bin3)*100);
  myfile << "\n";

  double abin1 = mr2_h->GetBinContent(1);
  double abin2 = mr2_h->GetBinContent(2);
  double abin3 = mr2_h->GetBinContent(3);
  double abin4 = mr2_h->GetBinContent(4);
  double abin5 = mr2_h->GetBinContent(5);
  myfile << "\n             BJET FROM LEPTOP";
  myfile << "\n       null BDT        real BDT\n";
  myfile << "-----------------------------------\n";
  myfile << "null:   " << (abin4*100) << "         " << (abin2*100);
  myfile << "\n";
  myfile << "real:   " << (abin1*100) << "         "  << ((abin5+abin3)*100);
  myfile << "\n";  

  double bbin1 = mr3_h->GetBinContent(1);
  double bbin2 = mr3_h->GetBinContent(2);
  double bbin3 = mr3_h->GetBinContent(3);
  double bbin4 = mr3_h->GetBinContent(4);
  double bbin5 = mr3_h->GetBinContent(5);
  myfile << "\n             Q1JET FROM HADTOP";
  myfile << "\n       null BDT        real BDT\n";
  myfile << "-----------------------------------\n";
  myfile << "null:   " << (bbin4*100) << "         " << (bbin2*100);
  myfile << "\n";
  myfile << "real:   " << (bbin1*100) << "         "  << ((bbin5+bbin3)*100);
  myfile << "\n";

  double cbin1 = mr4_h->GetBinContent(1);
  double cbin2 = mr4_h->GetBinContent(2);
  double cbin3 = mr4_h->GetBinContent(3);
  double cbin4 = mr4_h->GetBinContent(4);
  double cbin5 = mr4_h->GetBinContent(5);
  myfile << "\n             Q2JET FROM HADTOP";
  myfile << "\n       null BDT        real BDT\n";
  myfile << "-----------------------------------\n";
  myfile << "null:   " << (cbin4*100) << "         " << (cbin2*100);
  myfile << "\n";
  myfile << "real:   " << (cbin1*100) << "         "  << ((cbin5+cbin3)*100);
  myfile << "\n";

  double dbin1 = mr5_h->GetBinContent(1);
  double dbin2 = mr5_h->GetBinContent(2);
  double dbin3 = mr5_h->GetBinContent(3);
  double dbin4 = mr5_h->GetBinContent(4);
  double dbin5 = mr5_h->GetBinContent(5);
  myfile << "\n             Q1JET FROM WHIGGS";
  myfile << "\n       null BDT        real BDT\n";
  myfile << "-----------------------------------\n";
  myfile << "null:   " << (dbin4*100) << "         " << (dbin2*100);
  myfile << "\n";
  myfile << "real:   " << (dbin1*100) << "         "  << ((dbin5+dbin3)*100);
  myfile << "\n";

  double ebin1 = mr6_h->GetBinContent(1);
  double ebin2 = mr6_h->GetBinContent(2);
  double ebin3 = mr6_h->GetBinContent(3);
  double ebin4 = mr6_h->GetBinContent(4);
  double ebin5 = mr6_h->GetBinContent(5);
  myfile << "\n             Q2JET FROM WHIGGS";
  myfile << "\n       null BDT        real BDT\n";
  myfile << "-----------------------------------\n";
  myfile << "null:   " << (ebin4*100) << "         " << (ebin2*100);
  myfile << "\n";
  myfile << "real:   " << (ebin1*100) << "         "  << ((ebin5+ebin3)*100);
  myfile << "\n";
 
  //myfile.close();
*/

// MATCHED RESULTS PLOTTING
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);

  TCanvas* can = new TCanvas("can", "can", 1300, 800);
  can->Divide(3,4);
/*
  can->cd(1);
  mr0_h->SetMaximum(1.0);
  mr0_h->SetMinimum(0.0);
  mr0_h->SetTitle("matching_results[0] - lepton matching");
  mr0_h->GetXaxis()->SetLabelOffset(99);
  mr0_h->GetYaxis()->SetLabelOffset(99);
  mr0_h->SetTitleOffset(1.2);
  mr0_h->GetXaxis()->SetTitle("match number");
  mr0_h->GetYaxis()->SetTitle("normalized units");
  mr0_h->Draw("hist");

  can->cd(2);
  mr00_h->SetMaximum(1.0);
  mr00_h->SetMinimum(0.0);
  mr00_h->SetTitle("matching_results[0] - lepton matching");
  mr00_h->GetXaxis()->SetTitle("match number");
  mr00_h->GetYaxis()->SetTitle("normalized units");
  mr00_h->Draw("hist");

  can->cd(3);
  mr000_h->SetMaximum(1.0);
  mr000_h->SetMinimum(0.0);
  mr000_h->SetTitle("matching_results[0] - lepton matching");
  mr000_h->GetXaxis()->SetTitle("match number");
  mr000_h->GetYaxis()->SetTitle("normalized units");
  mr000_h->Draw("hist");

  can->cd(4);
  mr1_h->SetMaximum(1.0);
  mr1_h->SetMinimum(0.0);
  mr1_h->SetTitle("matching_results[1] - bJet hadTop Jets>6");
  mr1_h->GetXaxis()->SetTitle("match number");
  mr1_h->GetYaxis()->SetTitle("normalized units");
  mr1_h->Draw("hist");

  can->cd(5);
  mr11_h->SetMaximum(1.0);
  mr11_h->SetMinimum(0.0);
  mr11_h->SetTitle("matching_results[1] - bJet hadTop Jets=6");
  mr11_h->GetXaxis()->SetTitle("match number");
  mr11_h->GetYaxis()->SetTitle("normalized units");
  mr11_h->Draw("hist");

  can->cd(6);
  mr111_h->SetMaximum(1.0);
  mr111_h->SetMinimum(0.0);
  mr111_h->SetTitle("matching_results[1] - bJet hadTop Jets<6");
  mr111_h->GetXaxis()->SetTitle("match number");
  mr111_h->GetYaxis()->SetTitle("normalized units");
  mr111_h->Draw("hist");

  can->cd(7);
  mr2_h->SetMaximum(1.0);
  mr2_h->SetMinimum(0.0);
  mr2_h->SetTitle("matching_results[2] - bJet lepTop Jets>6");
  mr2_h->GetXaxis()->SetTitle("match number");
  mr2_h->GetYaxis()->SetTitle("normalized units");
  mr2_h->Draw("hist");

  can->cd(8);
  mr22_h->SetMaximum(1.0);
  mr22_h->SetMinimum(0.0);
  mr22_h->SetTitle("matching_results[2] - bJet lepTop Jets=6");
  mr22_h->GetXaxis()->SetTitle("match number");
  mr22_h->GetYaxis()->SetTitle("normalized units");
  mr22_h->Draw("hist");

  can->cd(9);
  mr222_h->SetMaximum(1.0);
  mr222_h->SetMinimum(0.0);
  mr222_h->SetTitle("matching_results[2] - bJet lepTop Jets<6");
  mr222_h->GetXaxis()->SetTitle("match number");
  mr222_h->GetYaxis()->SetTitle("normalized units");
  mr222_h->Draw("hist");
*/

  can->cd(1);
  mr3_h->Add(mr4_h);
  mr3_h->SetMaximum(1.0);
  mr3_h->SetMinimum(0.0);
  mr3_h->Scale(1./(mr3_h->Integral()));
  mr3_h->SetTitle("matching_results[3] - q1Jet hadTop Jets>6");
  mr3_h->GetXaxis()->SetTitle("match number");
  mr3_h->GetYaxis()->SetTitle("normalized units");
  mr3_h->Draw("histtext0");

  can->cd(2);
  mr33_h->Add(mr44_h);
  mr33_h->SetMaximum(1.0);
  mr33_h->SetMinimum(0.0);
  mr33_h->Scale(1./(mr33_h->Integral()));
  mr33_h->SetTitle("matching_results[3] - q1Jet hadTop Jets=6");
  mr33_h->GetXaxis()->SetTitle("match number");
  mr33_h->GetYaxis()->SetTitle("normalized units");
  mr33_h->Draw("histtext0");

  can->cd(3);
  mr333_h->Add(mr444_h);
  mr333_h->SetMaximum(1.0);
  mr333_h->SetMinimum(0.0);
  mr333_h->Scale(1./(mr333_h->Integral()));
  mr333_h->SetTitle("matching_results[3] - q1Jet hadTop Jets<6");
  mr333_h->GetXaxis()->SetTitle("match number");
  mr333_h->GetYaxis()->SetTitle("normalized units");
  mr333_h->Draw("histtext0");
/*
  can->cd(4);
  mr4_h->SetMaximum(1.0);
  mr4_h->SetMinimum(0.0);
  mr4_h->SetTitle("matching_results[4] - q2Jet hadTop Jets>6");
  mr4_h->GetXaxis()->SetTitle("match number");
  mr4_h->GetYaxis()->SetTitle("normalized units");
  mr4_h->Draw("histtext0");

  can->cd(5);
  mr44_h->SetMaximum(1.0);
  mr44_h->SetMinimum(0.0);
  mr44_h->SetTitle("matching_results[4] - q2Jet hadTop Jets=6");
  mr44_h->GetXaxis()->SetTitle("match number");
  mr44_h->GetYaxis()->SetTitle("normalized units");
  mr44_h->Draw("histtext0");

  can->cd(6);
  mr444_h->SetMaximum(1.0);
  mr444_h->SetMinimum(0.0);
  mr444_h->SetTitle("matching_results[4] - q2Jet hadTop Jets<6");
  mr444_h->GetXaxis()->SetTitle("match number");
  mr444_h->GetYaxis()->SetTitle("normalized units");
  mr444_h->Draw("histtext0");
*/
  can->cd(4);
  mr5_h->Add(mr6_h);
  mr5_h->SetMaximum(1.0);
  mr5_h->SetMinimum(0.0);
  mr5_h->Scale(1./(mr5_h->Integral()));
  mr5_h->SetTitle("matching_results[5] - q1Jet WHiggs Jets>6");
  mr5_h->GetXaxis()->SetTitle("match number");
  mr5_h->GetYaxis()->SetTitle("normalized units");
  mr5_h->Draw("histtext0");

  can->cd(5);
  mr55_h->Add(mr66_h);
  mr55_h->SetMaximum(1.0);
  mr55_h->SetMinimum(0.0);
  mr55_h->Scale(1./(mr55_h->Integral()));
  mr55_h->SetTitle("matching_results[5] - q1Jet WHiggs Jets=6");
  mr55_h->GetXaxis()->SetTitle("match number");
  mr55_h->GetYaxis()->SetTitle("normalized units");
  mr55_h->Draw("histtext0");

  can->cd(6);
  mr555_h->Add(mr666_h);
  mr555_h->SetMaximum(1.0);
  mr555_h->SetMinimum(0.0);
  mr555_h->Scale(1./(mr555_h->Integral()));
  mr555_h->SetTitle("matching_results[5] - q1Jet WHiggs Jets<6");
  mr555_h->GetXaxis()->SetTitle("match number");
  mr555_h->GetYaxis()->SetTitle("normalized units");
  mr555_h->Draw("histtext0");
/*
  can->cd(10);
  mr6_h->SetMaximum(1.0);
  mr6_h->SetMinimum(0.0);
  mr6_h->SetTitle("matching_results[6] - q2Jet WHiggs Jets>6");
  mr6_h->GetXaxis()->SetTitle("match number");
  mr6_h->GetYaxis()->SetTitle("normalized units");
  mr6_h->Draw("histtext0");

  can->cd(11);
  mr66_h->SetMaximum(1.0);
  mr66_h->SetMinimum(0.0);
  mr66_h->SetTitle("matching_results[6] - q2Jet WHiggs Jets=6");
  mr66_h->GetXaxis()->SetTitle("match number");
  mr66_h->GetYaxis()->SetTitle("normalized units");
  mr66_h->Draw("histtext0");

  can->cd(12);
  mr666_h->SetMaximum(1.0);
  mr666_h->SetMinimum(0.0);
  mr666_h->SetTitle("matching_results[6] - q2Jet WHiggs Jets<6");
  mr666_h->GetXaxis()->SetTitle("match number");
  mr666_h->GetYaxis()->SetTitle("normalized units");
  mr666_h->Draw("histtext0");
*/
  can->SaveAs("~/www/MRstudies_plots/finalMRJetCutsQTQHOnly.pdf");

/*
  TCanvas* can2 = new TCanvas("can2", "can2");
  can2->SetGrid();

  mr0_h->SetTitle("matching_results[0] - lepton matching");
  mr0_h->GetXaxis()->SetTitle("match number");
  mr0_h->GetYaxis()->SetTitle("normalized units");
  mr0_h->Draw("hist");
  //can2->SaveAs("~/www/v6plots/matching_results0.png");

  TCanvas* can3 = new TCanvas("can3", "can3");
  can3->SetGrid();

  mr1_h->SetTitle("matching_results[1] - bJet hadTop");
  mr1_h->GetXaxis()->SetTitle("match number");
  mr1_h->GetYaxis()->SetTitle("normalized units");
  mr1_h->Draw("hist");
  //can3->SaveAs("~/www/v6plots/matching_results1.png");

  TCanvas* can4 = new TCanvas("can4", "can4");
  can4->SetGrid();

  mr2_h->SetTitle("matching_results[2] - bJet lepTop");
  mr2_h->GetXaxis()->SetTitle("match number");
  mr2_h->GetYaxis()->SetTitle("normalized units");
  mr2_h->Draw("hist");
  //can4->SaveAs("~/www/v6plots/matching_results2.png");  

  TCanvas* can5 = new TCanvas("can5", "can5");
  can5->SetGrid();

  mr3_h->SetTitle("matching_results[3] - q1Jet hadTop");
  mr3_h->GetXaxis()->SetTitle("match number");
  mr3_h->GetYaxis()->SetTitle("normalized units");
  mr3_h->Draw("hist");
  //can5->SaveAs("~/www/v6plots/matching_results3.png");

  TCanvas* can6 = new TCanvas("can6", "can6");
  can6->SetGrid();

  mr4_h->SetTitle("matching_results[4] - q2Jet hadTop");
  mr4_h->GetXaxis()->SetTitle("match number");
  mr4_h->GetYaxis()->SetTitle("normalized units");
  mr4_h->Draw("hist");
  //can6->SaveAs("~/www/v6plots/matching_results4.png");

  TCanvas* can7 = new TCanvas("can7", "can7");
  can7->SetGrid();

  mr5_h->SetTitle("matching_results[5] - q1Jet WHiggs");
  mr5_h->GetXaxis()->SetTitle("match number");
  mr5_h->GetYaxis()->SetTitle("normalized units");
  mr5_h->Draw("hist");
  //can7->SaveAs("~/www/v6plots/matching_results5.png");

  TCanvas* can8 = new TCanvas("can8", "can8");
  can8->SetGrid();

  mr6_h->SetTitle("matching_results[6] - q2Jet WHiggs");
  mr6_h->GetXaxis()->SetTitle("match number");
  mr6_h->GetYaxis()->SetTitle("normalized units");
  mr6_h->Draw("hist");
  //can8->SaveAs("~/www/v6plots/matching_results6.png");

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
  //can1->SaveAs("~/www/v6plots/reco_score.png");  

  //TCanvas* can2 = new TCanvas("can2", "can2");
  //can2->SetGrid();
  
  //mr0_h->SetTitle("matching_results[0] - lepton matching");
  //mr0_h->Draw("histsame");
  //can2->SaveAs("matching_results0.png");
*/

/*
// MATCHING RESULTS AGAINST EACH OTHER PLOTS
   TCanvas* can9 = new TCanvas("can9", "can9");
   can9->SetGrid();
   
   mr0_h->SetTitle("Leptons[0] vs. bJet hadTop"); 
   mr0_h->SetFillColor(2);
   mr1_h->SetFillColor(4);
   mr1_h->SetFillStyle(3001);
   mr0_h->Draw("hist");
   mr1_h->Draw("histsame");

   can9->SaveAs("mr0VSmr1.png");

   TCanvas* can10 = new TCanvas("can10", "can10");
   can10->SetGrid();

   mr0_h->SetTitle("leptons[0] vs. bJet lepTop");
   mr0_h->SetFillColor(2);
   mr2_h->SetFillColor(4);
   mr2_h->SetFillStyle(3001);
   mr0_h->Draw("hist");
   mr2_h->Draw("histsame");

   can10->SaveAs("mr0VSmr2.png");
   
   TCanvas* can11 = new TCanvas("can11", "can11");
   can11->SetGrid();

   mr0_h->SetTitle("leptons[0] vs. q1Jet hadTop");
   mr0_h->SetFillColor(2);
   mr3_h->SetFillColor(4);
   mr3_h->SetFillStyle(3001);
   mr0_h->Draw("hist");
   mr3_h->Draw("histsame");

   can11->SaveAs("mr0VSmr3.png");
  
   TCanvas* can12 = new TCanvas("can12", "can12");
   can12->SetGrid();

   mr0_h->SetTitle("leptons[0] vs. q2Jet hadTop");
   mr0_h->SetFillColor(2);
   mr4_h->SetFillColor(4);
   mr4_h->SetFillStyle(3001);
   mr0_h->Draw("hist");
   mr4_h->Draw("histsame");

   can12->SaveAs("mr0VSmr4.png");
   
   TCanvas* can13 = new TCanvas("can13", "can13");
   can13->SetGrid();

   mr0_h->SetTitle("leptons[0] vs. q1Jet WHiggs");
   mr0_h->SetFillColor(2);
   mr5_h->SetFillColor(4);
   mr5_h->SetFillStyle(3001);
   mr0_h->Draw("hist");
   mr5_h->Draw("histsame");

   can13->SaveAs("MRstudies_plots/mr0VSmr5.png");

   TCanvas* can14 = new TCanvas("can14", "can14");
   can14->SetGrid();

   mr0_h->SetTitle("leptons[0] vs. q2Jet WHiggs");
   mr0_h->SetFillColor(2);
   mr6_h->SetFillColor(4);
   mr6_h->SetFillStyle(3001);
   mr0_h->Draw("hist");
   mr6_h->Draw("histsame");

   can14->SaveAs("MRstudies_plots/mr0VSmr6.png");  
*/

}


