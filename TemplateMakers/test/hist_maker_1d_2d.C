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
/// usage: root -l studyTemplate.C+
///
/////////////////////////////////////////



void run_it(TChain* chain, TString output_file)
{

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
  double vs_ttv_score_branch=-999.;

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("vs_ttbar_bdt_score",1);
  chain->SetBranchStatus("vs_ttv_bdt_score",1);
  
  chain->SetBranchAddress("mcwgt", &wgt_intree);
  chain->SetBranchAddress("vs_ttbar_bdt_score", &vs_ttbar_score_branch);  
  chain->SetBranchAddress("vs_ttv_bdt_score", &vs_ttv_score_branch);  


  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TH2D *output_2d = new TH2D("bdt_output", "bdt output ttV",30,-1,1,30,-1,1);

  TH1D *output_1d = new TH1D("bdt_output", "bdt output ttH",30,-1,1);
  TH1D *output_1d_shifted = new TH1D("bdt_output_shifted", "bdt output ttbar",30,-1,1);

  vector<TLine*> bin_lines_2d;
  TLine *line_1 = new TLine(-1, -0.2, 1, -0.2);
  bin_lines_2d.push_back(line_1);
  TLine *line_2 = new TLine(-1, 0.1, 1, 0.1);
  bin_lines_2d.push_back(line_2);
  TLine *line_3 = new TLine(0.3, 0.1, 0.3, 0.4);
  bin_lines_2d.push_back(line_3);
  TLine *line_4 = new TLine(-1, 0.4, 1, 0.4);
  bin_lines_2d.push_back(line_4);
  TLine *line_5 = new TLine(0.1, 0.4, 0.1, 1);
  bin_lines_2d.push_back(line_5);
  TLine *line_6 = new TLine(0.4, 0.4, 0.4, 1);
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
      //output_1d->Fill(vs_ttv_score_branch, wgt_intree);

      //      if (i%3 != 0 && (vs_ttv_score_branch < 0.4 || vs_ttbar_score_branch < 0.4)) vs_ttbar_score_branch = (vs_ttbar_score_branch+1)*( 1-shift ) -1;
      //      if (i%3 != 0 && (vs_ttv_score_branch < 0.4 || vs_ttbar_score_branch < 0.4)) vs_ttv_score_branch = (vs_ttv_score_branch+1)*( 1-shift ) -1;


      output_1d_shifted->Fill(vs_ttbar_score_branch, wgt_intree);
      //output_1d_shifted->Fill(vs_ttv_score_branch, wgt_intree);

      double y_value = vs_ttbar_score_branch;
      double x_value = vs_ttv_score_branch;
      
      output_2d->Fill( x_value, y_value, wgt_intree);
      
    }

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
  
  can1->Write();
  can1->SaveAs("2d_bdtOutput.root");
  can1->SaveAs("2d_bdtOutput.pdf");


  TCanvas* can2 = new TCanvas("can2", "can2");
  output_1d->SetLineColor(1);
  output_1d_shifted->SetLineColor(2);
  output_1d->SetStats(0);
  output_1d_shifted->SetStats(0);

  TLegend *leg = new TLegend(0.6790831,0.7046414,0.8954155,0.8438819,NULL,"brNDC");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->AddEntry(output_1d, "no shift","l");
  leg->AddEntry(output_1d_shifted, "shifted","l");

  output_1d_shifted->Draw("hist");
  output_1d->Draw("histsame");

  leg->Draw("same");
  can2->Write();
  can2->SaveAs("1d_bdtOutput.root");
  can2->SaveAs("1d_bdtOutput.pdf");

  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  copiedfile->Close();  
}

void hist_maker_1d_2d(void)
{
  TString output_file = "my_study.root";
  TChain *chain = new TChain("extraction_tree_standard");
  //  TChain *chain = new TChain("extraction_tree_csv2");

  //ttW+ttZ
  chain->Add("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttW-aMCatNLO_selection_tree_2lss.root");
  chain->Add("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttZ-aMCatNLO_selection_tree_2lss.root");
  //ttbar
  //chain->Add("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttbar-semiLep-powheg_selection_tree_2lss.root");
  // ttH
  //chain->Add("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/tth_aMC_old_selection_tree_2lss.root");
  run_it(chain,output_file);
}
