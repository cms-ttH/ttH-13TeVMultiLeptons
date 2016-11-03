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
#include "loadSamples_notreDame.h"
#include "treeTools.h"

/////////////////////////////////////////
///
/// usage: root -l compareSamples.C+
///
/////////////////////////////////////////

class PlotObject
{
private:
  TH1D *nJets_selected_;
  TH1D *jetPt_selected_;
  TH1D *jetEta_selected_;
  TH1D *jetCsv_selected_;
  TH1D *nJets_raw_;
  TH1D *nJets_gen_;
  TH1D *lep1_pt_;
  TH1D *lep2_pt_;
  TH1D *lep1_iso_;
  TH1D *lep2_iso_;
  TH1D *lep1_MVA_;
  TH1D *lep2_MVA_;

  TH1D *lep1_csv_;
  TH1D *lep2_csv_;
  TH1D *lep1_ptRatio_;
  TH1D *lep2_ptRatio_;
  TH1D *lep1_ptRel_;
  TH1D *lep2_ptRel_;
  int hist_color_;

  void FillHist(TString sample_name_input_)
  {
    TChain *chain = new TChain("ss2l_tree");
    
    TString file_ = getSelectionFile(sample_name_input_);
    chain->Add(file_);
    int chainentries = chain->GetEntries();
    
    double mcwgt_intree = -999.;
    vector<ttH::Jet> *preselected_jets_intree=0;
    vector<ttH::Jet> *raw_jets_intree=0;
    vector<ttH::GenParticle> *gen_jets_intree=0;
    vector<ttH::Lepton> *loose_leptons_intree=0;
    vector<ttH::Lepton> *tight_leptons_intree=0;
    
    chain->SetBranchStatus("*",0);
    chain->SetBranchStatus("mcwgt",1);
    chain->SetBranchStatus("preselected_jets.*",1);
    chain->SetBranchStatus("raw_jets.*",1);
    chain->SetBranchStatus("genJets.*",1);
    chain->SetBranchStatus("looseMvaBased_leptons.*",1);
    chain->SetBranchStatus("tightMvaBased_leptons.*",1);

    chain->SetBranchAddress("mcwgt", &mcwgt_intree);
    chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
    chain->SetBranchAddress("raw_jets", &raw_jets_intree);
    chain->SetBranchAddress("genJets", &gen_jets_intree);
    chain->SetBranchAddress("tightMvaBased_leptons",&tight_leptons_intree);


    Int_t cachesize = 250000000;   //250 MBytes
    chain->SetCacheSize(cachesize);

    //    chainentries = 1000; //trash this

    for (int i=0; i<chainentries; i++)
      {
    	chain->GetEntry(i);
    	printProgress(i,chainentries);
	nJets_raw_->Fill(raw_jets_intree->size(), mcwgt_intree);
	nJets_gen_->Fill(gen_jets_intree->size(), mcwgt_intree);
    	nJets_selected_->Fill(preselected_jets_intree->size(), mcwgt_intree);

	//	auto lep_collection = *loose_leptons_intree;
	auto lep_collection = *tight_leptons_intree;

	lep1_pt_->Fill(lep_collection[0].obj.pt(),mcwgt_intree);
	lep2_pt_->Fill(lep_collection[1].obj.pt(),mcwgt_intree);
	lep1_iso_->Fill(lep_collection[0].miniIso,mcwgt_intree);
	lep2_iso_->Fill(lep_collection[1].miniIso,mcwgt_intree);
	lep1_MVA_->Fill(lep_collection[0].lepMVA,mcwgt_intree);
	lep2_MVA_->Fill(lep_collection[1].lepMVA,mcwgt_intree);

	lep1_csv_->Fill(lep_collection[0].csv,mcwgt_intree);
	lep2_csv_->Fill(lep_collection[1].csv,mcwgt_intree);
	lep1_ptRatio_->Fill(lep_collection[0].jetPtRatio,mcwgt_intree);
	lep2_ptRatio_->Fill(lep_collection[1].jetPtRatio,mcwgt_intree);
	lep1_ptRel_->Fill(lep_collection[0].jetPtRel,mcwgt_intree);
	lep2_ptRel_->Fill(lep_collection[1].jetPtRel,mcwgt_intree);
	

	for (const auto & jet : *preselected_jets_intree)
	  {
	    jetPt_selected_->Fill(jet.obj.pt(), mcwgt_intree);
	    jetEta_selected_->Fill(jet.obj.eta(), mcwgt_intree);
	    jetCsv_selected_->Fill(jet.csv, mcwgt_intree);
	  }
	
      }
    
    hist_vector.push_back(nJets_selected_);
    hist_vector.push_back(jetPt_selected_);
    hist_vector.push_back(jetEta_selected_);
    hist_vector.push_back(jetCsv_selected_);
    hist_vector.push_back(nJets_raw_);
    hist_vector.push_back(nJets_gen_);
    hist_vector.push_back(lep1_pt_);
    hist_vector.push_back(lep2_pt_);
    hist_vector.push_back(lep1_iso_);
    hist_vector.push_back(lep2_iso_);
    hist_vector.push_back(lep1_MVA_);
    hist_vector.push_back(lep2_MVA_);

    hist_vector.push_back(lep1_csv_);
    hist_vector.push_back(lep2_csv_);
    hist_vector.push_back(lep1_ptRatio_);
    hist_vector.push_back(lep2_ptRatio_);
    hist_vector.push_back(lep1_ptRel_);
    hist_vector.push_back(lep2_ptRel_);

    for (const auto & my_hist : hist_vector)
      {
	my_hist->Sumw2();
	my_hist->Scale( 1.0 / my_hist->Integral());
	
	my_hist->SetStats(0);
	my_hist->SetLineColor(hist_color_);
	my_hist->SetMarkerColor(hist_color_);
	my_hist->GetYaxis()->SetTitle("normalized units");
	my_hist->GetYaxis()->SetTitleOffset(1.37);
	my_hist->GetYaxis()->SetLabelSize(0.025);
      }
  }
public:
  PlotObject(TString sample_name_="sample_name", int line_color_=1, TString leg_name_="legend_name")
  { 
    hist_color_ = line_color_;

    nJets_raw_ = new TH1D(leg_name_,"nJets_raw",32,0,32);
    nJets_raw_->GetXaxis()->SetTitle("N jets (no selection)");

    nJets_selected_ = new TH1D(leg_name_,"nJets_selected",45,0,15);
    nJets_selected_->GetXaxis()->SetTitle("N jets");

    jetPt_selected_ = new TH1D(leg_name_,"jetPt_selected",25,0,300);
    jetPt_selected_->GetXaxis()->SetTitle("jet pT [GeV]");

    jetEta_selected_ = new TH1D(leg_name_,"jetEta_selected",25,-2.6,2.6);
    jetEta_selected_->GetXaxis()->SetTitle("jet eta");

    jetCsv_selected_ = new TH1D(leg_name_,"jetCsv_selected",25,-.1,1.1);
    jetCsv_selected_->GetXaxis()->SetTitle("jet CSV");

    nJets_gen_ = new TH1D(leg_name_,"nJets_gen",16,0,32);
    nJets_gen_->GetXaxis()->SetTitle("N gen jets (no selection) ");

    lep1_pt_ = new TH1D(leg_name_,"lep1_pt",25,0,250);
    lep1_pt_->GetXaxis()->SetTitle("lep1 pt");

    lep2_pt_ = new TH1D(leg_name_,"lep2_pt",25,0,250);
    lep2_pt_->GetXaxis()->SetTitle("lep2 pt");

    lep1_iso_ = new TH1D(leg_name_,"lep1_iso",25,0,0.4);
    lep1_iso_->GetXaxis()->SetTitle("lep1 miniIso");

    lep2_iso_ = new TH1D(leg_name_,"lep2_iso",25,0,0.4);
    lep2_iso_->GetXaxis()->SetTitle("lep2 miniIso");

    lep1_MVA_ = new TH1D(leg_name_,"lep1_MVA",25,0.,1);
    lep1_MVA_->GetXaxis()->SetTitle("lep1 lepMVA");

    lep2_MVA_ = new TH1D(leg_name_,"lep2_MVA",25,0.,1);
    lep2_MVA_->GetXaxis()->SetTitle("lep2 lepMVA");

    lep1_csv_ = new TH1D(leg_name_,"lep1_csv",25,-1,1);
    lep1_csv_->GetXaxis()->SetTitle("lep1 csv");

    lep2_csv_ = new TH1D(leg_name_,"lep2_csv",25,-1,1);
    lep2_csv_->GetXaxis()->SetTitle("lep2 csv");

    lep1_ptRatio_ = new TH1D(leg_name_,"lep1_ptRatio",25,0,1.6);
    lep1_ptRatio_->GetXaxis()->SetTitle("lep1 ptRatio");

    lep2_ptRatio_ = new TH1D(leg_name_,"lep2_ptRatio",25,0,1.6);
    lep2_ptRatio_->GetXaxis()->SetTitle("lep2 ptRatio");

    lep1_ptRel_ = new TH1D(leg_name_,"lep1_ptRel",25,0,160);
    lep1_ptRel_->GetXaxis()->SetTitle("lep1 ptRel");

    lep2_ptRel_ = new TH1D(leg_name_,"lep2_ptRel",25,0,160);
    lep2_ptRel_->GetXaxis()->SetTitle("lep2 ptRel");


    FillHist(sample_name_);

  }//default constructor

  vector<TH1D*> hist_vector;
  virtual ~PlotObject(){};
};


void drawPlots(vector<PlotObject> samples_)
{
  
  for (unsigned int i=0; i < samples_[0].hist_vector.size(); i++)
    {
      TString title = samples_[0].hist_vector[i]->GetTitle();
      TCanvas* can = new TCanvas(title,title,10,32,530,580);
      TPad* pad1 = new TPad("pad1","pad1",0,0.2,1,1);
      TLegend *leg = new TLegend(0.5454545,0.8240072,0.8787879,0.9187726,NULL,"brNDC");
      leg->SetBorderSize(0);
      double hist_max_val = 0.;
      TString can_save_name = title + ".pdf";

      pad1->SetTopMargin(0.03);
      pad1->SetBottomMargin(0);
      pad1->Draw();
      pad1->cd();
    
      for (const auto & sample : samples_)
	{
	  if ( sample.hist_vector[i]->GetMaximum() > hist_max_val) hist_max_val = sample.hist_vector[i]->GetMaximum();	  
	}
      samples_[0].hist_vector[i]->GetYaxis()->SetRangeUser(0, 1.2*hist_max_val);

      int j = 0;
      for (const auto & sample : samples_)
	{
	  sample.hist_vector[i]->SetTitle("");
	  //use max val to keep track of first iteration
	  if ( j == 0 ) sample.hist_vector[i]->DrawCopy("hist");
	  else  sample.hist_vector[i]->DrawCopy("histsame");
	
	  leg->AddEntry(sample.hist_vector[i], sample.hist_vector[i]->GetName(), "l");
	  j++;
	}  

      double x_min = samples_[0].hist_vector[i]->GetXaxis()->GetXmin();
      double x_max = samples_[0].hist_vector[i]->GetXaxis()->GetXmax();

      leg->Draw("same");
      can->cd();

      TPad* pad2 = new TPad("pad2","pad2",0,0,1,0.2);
      TLine *line = new TLine(x_min, 1., x_max, 1.);
      auto hist_ratio =  *(samples_[0].hist_vector[i]);
      hist_ratio.SetLineWidth(1);
      //      hist_ratio.Sumw2();
      hist_ratio.Divide( samples_[1].hist_vector[i] );
      pad2->SetTopMargin(0);
      pad2->SetBottomMargin(0.35);
      //      pad2->SetGridy();
      pad2->Draw();
      pad2->cd();
      
      hist_ratio.GetYaxis()->SetTitle("filter / no filter");
      double offset_fraction = 1.6;//1.6;
      double hist_max = hist_ratio.GetMaximum();
      double hist_min = hist_ratio.GetMinimum();
      double y_max = 1 + offset_fraction*max(abs(hist_max - 1), abs(hist_min - 1 ));
      double y_min = 1 - offset_fraction*max(abs(hist_max - 1), abs(hist_min - 1 )); 
      //    hist_ratio.GetYaxis()->SetRangeUser( y_min, y_max );
      //      hist_ratio.GetYaxis()->SetRangeUser(-.5,2.5);
      hist_ratio.GetYaxis()->SetRangeUser(.25,1.75);
      hist_ratio.SetLineColor(1);
      hist_ratio.SetMarkerColor(1);
      hist_ratio.SetMarkerStyle(20);
      hist_ratio.SetMarkerSize(0.6);
      hist_ratio.GetYaxis()->SetLabelSize(.1);
      hist_ratio.GetXaxis()->SetLabelSize(.16);
      hist_ratio.GetXaxis()->SetTitle( samples_[0].hist_vector[i]->GetXaxis()->GetTitle() );
      hist_ratio.GetXaxis()->SetTitleSize(0.16);
      hist_ratio.GetXaxis()->SetTitleFont(42);
      hist_ratio.GetYaxis()->SetTitleOffset(.45);
      hist_ratio.GetYaxis()->SetTitleSize(.12);
      hist_ratio.GetYaxis()->CenterTitle();
      hist_ratio.DrawCopy("ep");
      line->Draw("same");
      
      can->SaveAs(can_save_name);
    }
}

void compareSamples(void)
{
  PlotObject sample1 = PlotObject("ttbar_genFilter",1,"filtered");
  PlotObject sample2 = PlotObject("ttbar_semiLep_powheg",2,"no filter");

  
  vector<PlotObject> plot_vector;
  plot_vector.push_back(sample1);
  plot_vector.push_back(sample2);

  
  drawPlots(plot_vector);
}

