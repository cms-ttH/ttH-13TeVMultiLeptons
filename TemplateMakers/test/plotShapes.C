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
#include "TH2D.h"
#include "TFile.h"
#include "TLine.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <cmath>
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "selection.h"
#include "loadSamples.h"
#include "treeTools.h"

/////////////////////////////////////////
///
/// usage: root -l plotShapes.C+
///
/////////////////////////////////////////

void run_it(vector<TString> file_vec, TString sample)
{

  //  TChain *chain = new TChain("extraction_tree_standard");
  TChain *chain = new TChain("extraction_tree_recobdt_v1");
  for (const auto & file : file_vec) chain->Add(file);

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
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
  vector<ttH::Jet> *preselected_jets_genMatch_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  ttH::Jet *b_from_leptop_intree=0;

  double vs_ttbar_score_branch=-999.;
  double vs_ttbar_bdtReco_score_branch=-999.;
  double vs_ttv_score_branch=-999.;

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("vs_ttbar_bdt_score",1);
  chain->SetBranchStatus("vs_ttbar_bdtReco_bdt_score",1);
  chain->SetBranchStatus("vs_ttv_bdt_score",1);
  
  chain->SetBranchAddress("mcwgt", &wgt_intree);
  chain->SetBranchAddress("vs_ttbar_bdt_score", &vs_ttbar_score_branch);  
  chain->SetBranchAddress("vs_ttbar_bdtReco_bdt_score", &vs_ttbar_bdtReco_score_branch);  
  chain->SetBranchAddress("vs_ttv_bdt_score", &vs_ttv_score_branch);  


  TH2D *output_2d = new TH2D("bdt_output", "bdt output w/ reco bdt",30,-1,1,30,-1,1);

  TH1D *output_1d = new TH1D("bdt_output", sample ,30,-1,1);
  TH1D *output_1d_shifted = new TH1D("bdt_output_shifted", sample,30,-1,1);

  vector<TLine*> bin_lines_2d;

  //original
  double bin1_y = -0.2;
  double bin2_y = 0.1;
  double bin3_x = 0.3;
  double bin3_y = 0.4;
  double bin5_x = 0.1;
  double bin6_x = 0.4;

  //rebin
  // double bin1_y = -0.1;
  // double bin2_y = 0.3;
  // double bin3_x = 0.3;
  // double bin3_y = 0.6;
  // double bin5_x = 0.1;
  // double bin6_x = 0.4;


  TLine *line_1 = new TLine(-1, bin1_y, 1, bin1_y);
  bin_lines_2d.push_back(line_1);
  TLine *line_2 = new TLine(-1, bin2_y, 1, bin2_y);
  bin_lines_2d.push_back(line_2);
  TLine *line_3 = new TLine(bin3_x, bin2_y, bin3_x, bin3_y);
  bin_lines_2d.push_back(line_3);
  TLine *line_4 = new TLine(-1, bin3_y, 1, bin3_y);
  bin_lines_2d.push_back(line_4);
  TLine *line_5 = new TLine(bin5_x, bin3_y, bin5_x, 1);
  bin_lines_2d.push_back(line_5);
  TLine *line_6 = new TLine(bin6_x, bin3_y, bin6_x, 1);
  bin_lines_2d.push_back(line_6);

  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 

  double shift = 0.3;
  double starttime = get_wall_time();
  //  chainentries = 10000;
  for (int i=0; i<chainentries; i++)
    {
      
      printProgress(i,chainentries);
      chain->GetEntry(i);
      
      //////////////////////////
      ////
      //// calculate new vars
      ////
      //////////////////////////

      output_1d->Fill(vs_ttbar_score_branch, wgt_intree);
      output_1d_shifted->Fill(vs_ttbar_bdtReco_score_branch, wgt_intree);

      //      double y_value = vs_ttbar_score_branch;
      double y_value = vs_ttbar_bdtReco_score_branch;
      double x_value = vs_ttv_score_branch;
      output_2d->Fill( x_value, y_value, wgt_intree);
      
    }

  
  output_1d->Scale( 1.0 / output_1d->Integral() );
  output_1d_shifted->Scale( 1.0 / output_1d_shifted->Integral() );
  output_2d->Scale( 1.0 / output_2d->Integral() );

  TCanvas* can1 = new TCanvas("can", "can");
  output_2d->Draw("colz");
  output_2d->SetStats(0);

  output_2d->GetYaxis()->SetTitle("ttbar BDT score");
  output_2d->GetXaxis()->SetTitle("ttV BDT score");

  can1->Update();

  for (const auto & line : bin_lines_2d)
    {
      line->SetLineColor(2);
      line->SetLineWidth(2);
      line->Draw();
    }
  
  TString d2_prefix = "2d_bdtOutput_";
  d2_prefix += sample;
  TString d2_root_save = d2_prefix+".root";
  TString d2_pdf_save = d2_prefix+".pdf";
  can1->SaveAs(d2_root_save);
  can1->SaveAs(d2_pdf_save);


  TCanvas* can2 = new TCanvas("can2", "can2");
  output_1d->SetLineColor(1);
  output_1d_shifted->SetLineColor(2);
  output_1d->SetStats(0);
  output_1d_shifted->SetStats(0);

  TString x_title = "BDT(ttH,tt)";
  TString y_title = "normalized units";
  output_1d->GetXaxis()->SetTitle(x_title);
  output_1d_shifted->GetXaxis()->SetTitle(x_title);
  output_1d->GetYaxis()->SetTitle(y_title);
  output_1d_shifted->GetYaxis()->SetTitle(y_title);

  TLegend *leg = new TLegend(0.5830946,0.7109705,0.7994269,0.850211,NULL,"brNDC");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->AddEntry(output_1d, "ichep bdt","l");
  leg->AddEntry(output_1d_shifted, "ichep bdt + reco bdt","l");

  if (output_1d_shifted->GetMaximum() > output_1d->GetMaximum()) 
    {
      output_1d_shifted->Draw("hist");
      output_1d->Draw("histsame");
      output_1d_shifted->GetYaxis()->SetRangeUser(0., 1.7*output_1d_shifted->GetMaximum());
    }
  else 
    {
      output_1d->Draw("hist");
      output_1d_shifted->Draw("histsame");
      output_1d->GetYaxis()->SetRangeUser(0., 1.7*output_1d->GetMaximum());
    }

  leg->Draw("same");

  TString d1_prefix = "1d_bdtOutput_";
  d1_prefix += sample;
  TString d1_root_save = d1_prefix+".root";
  TString d1_pdf_save = d1_prefix+".pdf";
  can2->SaveAs(d1_root_save);
  can2->SaveAs(d1_pdf_save);

  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
}

void plotShapes(void)
{

  vector<TString> files;

  //ttW+ttZ
  files.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttW_aMCatNLO_2lss.root");
  files.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttZ_aMCatNLO_2lss.root");
  run_it(files,"ttV");
  files.clear();
  //ttbar
  files.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_semiLep_powheg_2lss.root");
  run_it(files,"ttbarFake");
  files.clear();
  // ttH
  files.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tth_aMC_old_2lss.root");
  run_it(files,"ttH");
  files.clear();
  //flips
  files.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_diLep_madgraph_2lss.root");
  run_it(files,"chargeFlip");

}
