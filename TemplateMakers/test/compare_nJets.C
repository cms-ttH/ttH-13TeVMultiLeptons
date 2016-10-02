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

    chainentries = 10000; //trash this

    //    chain->Draw("@raw_jets.size() >> my_hist","mcwgt*(1.0)","goff");

    for (int i=0; i<chainentries; i++)
      {
    	chain->GetEntry(i);
    	printProgress(i,chainentries);
	//    	int nJets = preselected_jets_intree->size();
	int nJets = raw_jets_intree->size();
    	my_hist->Fill(nJets, mcwgt_intree);
      }
    
    //normalize
    my_hist->Scale( 1.0 / my_hist->Integral());
    my_hist->SetStats(0);
  }
public:
  PlotObject(TString sample_name_="sample_name", int line_color_=1, TString leg_name_="legend_name")
  { 
    my_hist = new TH1D(leg_name_,"",35,0,35);
    my_hist->SetLineColor(line_color_);
    my_hist->SetMarkerColor(line_color_);
    my_hist->GetXaxis()->SetTitle("N jets (no selection)");
    my_hist->GetYaxis()->SetTitle("normalized units");
    my_hist->GetYaxis()->SetTitleOffset(1.37);
    my_hist->GetYaxis()->SetLabelSize(0.025);
    FillHist(sample_name_);

  }//default constructor

  TH1D *my_hist;
  virtual ~PlotObject(){};
};


void drawPlots(vector<PlotObject> samples_)
{
  

  TCanvas* can = new TCanvas("can", "can",10,32,530,580);
  can->SetTopMargin(0.06);
  TLegend *leg = new TLegend(0.4753788,0.7815884,0.8882576,0.9205776,NULL,"brNDC"); 
  leg->SetBorderSize(0);
  double hist_max_val = 0.;
  for (const auto & sample : samples_)
    {
      //use max val to keep track of first iteration
      if ( hist_max_val == 0. ) sample.my_hist->Draw("hist");
      else  sample.my_hist->Draw("histsame");
      if ( sample.my_hist->GetMaximum() > hist_max_val)	hist_max_val = sample.my_hist->GetMaximum();
      leg->AddEntry(sample.my_hist, sample.my_hist->GetName(), "l");
    }  
  samples_[0].my_hist->GetYaxis()->SetRangeUser(0, 1.3*hist_max_val);
  leg->Draw("same");
  can->SaveAs("nJets_raw.pdf");

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

