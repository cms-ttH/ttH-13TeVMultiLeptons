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
/// usage: root -l compare_nJets.C+
///
/////////////////////////////////////////

class PlotObject
{
private:
  TH1D *nJets_selected_;
  TH1D *nJets_raw_;
  TH1D *nJets_gen_;
  int hist_color_;

  void FillHist(TString sample_name_input_)
  {
    TChain *chain = loadFiles(sample_name_input_);
    int chainentries = chain->GetEntries();
    
    double mcwgt_intree = -999.;
    vector<ttH::Jet> *preselected_jets_intree=0;
    vector<ttH::Jet> *raw_jets_intree=0;
    
    chain->SetBranchStatus("*",0);
    chain->SetBranchStatus("mcwgt",1);
    chain->SetBranchStatus("preselected_jets.*",1);
    chain->SetBranchStatus("raw_jets.*",1);
    //chain->SetBranchStatus("",1);

    chain->SetBranchAddress("mcwgt", &mcwgt_intree);
    chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
    chain->SetBranchAddress("raw_jets", &raw_jets_intree);

    Int_t cachesize = 250000000;   //250 MBytes
    chain->SetCacheSize(cachesize);

    chainentries = 4000; //trash this
    //    chain->Draw("@raw_jets.size() >> my_hist","mcwgt*(1.0)","goff");

    for (int i=0; i<chainentries; i++)
      {
    	chain->GetEntry(i);
    	printProgress(i,chainentries);
	//    	int nJets = preselected_jets_intree->size();
    	nJets_raw_->Fill(raw_jets_intree->size(), mcwgt_intree);
    	nJets_selected_->Fill(preselected_jets_intree->size(), mcwgt_intree);
      }
    
    hist_vector.push_back(nJets_selected_);
    hist_vector.push_back(nJets_raw_);
    //    hist_vector.push_back(nJets_gen_);

    for (const auto & my_hist : hist_vector)
      {
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

    nJets_selected_ = new TH1D(leg_name_,"nJets_selected",15,0,15);
    nJets_selected_->GetXaxis()->SetTitle("N jets (selected) ");

    nJets_gen_ = new TH1D(leg_name_,"nJets_gen",32,0,32);
    nJets_gen_->GetXaxis()->SetTitle("N gen jets (no selection) ");

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
      can->SetTopMargin(0.06);
      TLegend *leg = new TLegend(0.4753788,0.7815884,0.8882576,0.9205776,NULL,"brNDC"); 
      leg->SetBorderSize(0);
      double hist_max_val = 0.;
      TString can_save_name = title + ".pdf";
      for (const auto & sample : samples_)
	{
	  sample.hist_vector[i]->SetTitle("");
	  //use max val to keep track of first iteration
	  if ( hist_max_val == 0. ) sample.hist_vector[i]->Draw("hist");
	  else  sample.hist_vector[i]->Draw("histsame");
	  if ( sample.hist_vector[i]->GetMaximum() > hist_max_val)  hist_max_val = sample.hist_vector[i]->GetMaximum();
	  leg->AddEntry(sample.hist_vector[i], sample.hist_vector[i]->GetName(), "l");
	}  
      samples_[0].hist_vector[i]->GetYaxis()->SetRangeUser(0, 1.3*hist_max_val);
      leg->Draw("same");
      can->SaveAs(can_save_name);
    }
}

void compare_nJets(void)
{
  PlotObject tth_powheg_new = PlotObject("tth_powheg_new",1,"ttH powheg tranche3");
  PlotObject tth_powheg_old = PlotObject("tth_powheg_old",2,"ttH powheg reHLT");
  PlotObject tth_aMC_old = PlotObject("tth_aMC_old",4,"ttH aMC@NLO reHLT");
  
  vector<PlotObject> plot_vector;
  plot_vector.push_back(tth_powheg_new);
  plot_vector.push_back(tth_powheg_old);
  plot_vector.push_back(tth_aMC_old);  
  
  drawPlots(plot_vector);
}

