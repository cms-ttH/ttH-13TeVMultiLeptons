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
/// usage: root -l makeStackPlotsFinalShape.C+
///
/////////////////////////////////////////

//namespace eventType{ enum eventType{ss2l_ee, ss2l_mumu, ss2l_emu, l3}; }

class Sample
{
private:
public:
  Sample(TString leg_name_="sample", int fill_color_=1, int fill_style_=1, double xsec_=1., TString file_name_="file_name.root")
  {
    legend_name = leg_name_;
    fill_color = fill_color_;
    fill_style = fill_style_;
    file_name = file_name_;
    xsec = xsec_;
  } //default constructor
  TString legend_name;
  int fill_color;
  int fill_style;
  TString file_name;
  double xsec; //13 TeV xsec in pb
  virtual ~Sample(){}
};

class PlotObject
{
private:
  Sample sample;
  TFile* fout;
  TH1D* template_hist;

  void SetTitleAndName(TH1D* input_hist_, TString name_postfix_, TString title_postfix_ )
  {
    
    
    TString hist_name = input_hist_->GetName(); hist_name += "_"+sample.legend_name+"_"+name_postfix_;
    TString hist_title = input_hist_->GetTitle(); hist_title += " "+sample.legend_name+" "+title_postfix_;
    input_hist_->SetTitle(hist_title);
    input_hist_->SetName(hist_name);
    input_hist_->SetDirectory(fout);
  }

  void FillCategories(int bin_num_, double weight_, TString flav_, bool isPlus_, bool bTight_, bool isTau_)
  {
    inclusive_hist->Fill( bin_num_, weight_ );

    if ( isTau_ ) tau_hist->Fill( bin_num_, weight_ );
    else if (flav_.CompareTo("ee")==0)
      {
	if ( isPlus_ ) ee_plus_hist->Fill( bin_num_, weight_ );
	else ee_minus_hist->Fill( bin_num_, weight_ );
      }
    else if (flav_.CompareTo("em")==0)
      {
	if ( isPlus_ ) 
	  {
	    if ( bTight_ ) em_bTight_plus_hist->Fill( bin_num_, weight_ );
	    else em_bLoose_plus_hist->Fill( bin_num_, weight_ );
	  }
	else 
	  {
	    if ( bTight_ ) em_bTight_minus_hist->Fill( bin_num_, weight_ );
	    else em_bLoose_minus_hist->Fill( bin_num_, weight_ );
	  }
      }
    else if (flav_.CompareTo("mm")==0)
      {
	if ( isPlus_ ) 
	  {
	    if ( bTight_ ) mm_bTight_plus_hist->Fill( bin_num_, weight_ );
	    else mm_bLoose_plus_hist->Fill( bin_num_, weight_ );
	  }
	else 
	  {
	    if ( bTight_ ) mm_bTight_minus_hist->Fill( bin_num_, weight_ );
	    else mm_bLoose_minus_hist->Fill( bin_num_, weight_ );
	  }
      }
  }
public:
  PlotObject(TH1D* template_hist_, Sample sample_, TFile* fout_)
  {
    sample = sample_;
    fout = fout_;
    template_hist = template_hist_;


    //set up individual histogram names
    inclusive_hist = template_hist;
    ee_plus_hist = template_hist;
    ee_minus_hist = template_hist;
    em_bTight_plus_hist = template_hist;
    em_bTight_minus_hist = template_hist;
    em_bLoose_plus_hist = template_hist;
    em_bLoose_minus_hist = template_hist;
    mm_bTight_plus_hist = template_hist;
    mm_bTight_minus_hist = template_hist;
    mm_bLoose_plus_hist = template_hist;
    mm_bLoose_minus_hist = template_hist;
    tau_hist = template_hist;
    cout << "here" << endl;

    SetTitleAndName(inclusive_hist,"","");
    SetTitleAndName(ee_plus_hist,"ee_p","ee +");
    SetTitleAndName(ee_minus_hist,"ee_m","ee -");
    SetTitleAndName(em_bTight_plus_hist,"em_bt_p","em btight +");
    SetTitleAndName(em_bTight_minus_hist,"em_bt_m","em btight -");
    SetTitleAndName(em_bLoose_plus_hist,"em_bl_p","em bloose +");
    SetTitleAndName(em_bLoose_minus_hist,"em_bl_m","em bloose -");
    SetTitleAndName(mm_bTight_plus_hist,"mm_bt_p","mm btight +");
    SetTitleAndName(mm_bTight_minus_hist,"mm_bt_m","mm btight -");
    SetTitleAndName(mm_bLoose_plus_hist,"mm_bl_p","mm bloose +");
    SetTitleAndName(mm_bLoose_minus_hist,"mm_bl_m","mm bloose -");
    SetTitleAndName(tau_hist,"tau","tau");
    cout << "here" << endl;


  }//default constructor

  TH1D* inclusive_hist;
  TH1D* ee_plus_hist;
  TH1D* ee_minus_hist;
  TH1D* em_bTight_plus_hist;
  TH1D* em_bTight_minus_hist;
  TH1D* em_bLoose_plus_hist;
  TH1D* em_bLoose_minus_hist;
  TH1D* mm_bTight_plus_hist;
  TH1D* mm_bTight_minus_hist;
  TH1D* mm_bLoose_plus_hist;
  TH1D* mm_bLoose_minus_hist;
  TH1D* tau_hist;

  void Fill(double ttbar_score, double ttv_score, TString flavor, bool isPlus, bool bTight, bool isTau, double weight)
  {
    //this is where the 2D binning is defined!!!!
    if ( ttbar_score <= -0.2) FillCategories(1, weight, flavor, isPlus, bTight, isTau);
    else if ( ttbar_score <= 0.1) FillCategories(2, weight, flavor, isPlus, bTight, isTau);
    else if ( ttbar_score <= 0.4 )
      {
    	if ( ttv_score <= 0.3 ) FillCategories(3, weight, flavor, isPlus, bTight, isTau);
    	else  FillCategories(4, weight, flavor, isPlus, bTight, isTau);
      }
    else if ( ttv_score <= 0.1 ) FillCategories(5, weight, flavor, isPlus, bTight, isTau);
    else if ( ttv_score <= 0.4 ) FillCategories(6, weight, flavor, isPlus, bTight, isTau);
    else FillCategories(7, weight, flavor, isPlus, bTight, isTau);
  }
  
  void Write(void)
  {
    double norm_factor = sample.xsec / inclusive_hist->Integral();

    inclusive_hist->Scale( norm_factor );
    ee_plus_hist->Scale( norm_factor );
    ee_minus_hist->Scale( norm_factor );
    em_bTight_plus_hist->Scale( norm_factor );
    em_bTight_minus_hist->Scale( norm_factor );
    em_bLoose_plus_hist->Scale( norm_factor );
    em_bLoose_minus_hist->Scale( norm_factor );
    mm_bTight_plus_hist->Scale( norm_factor );
    mm_bTight_minus_hist->Scale( norm_factor );
    mm_bLoose_plus_hist->Scale( norm_factor );
    mm_bLoose_minus_hist->Scale( norm_factor );
    tau_hist->Scale( norm_factor );

    ee_plus_hist->Write();
    ee_minus_hist->Write();
    em_bTight_plus_hist->Write();
    em_bTight_minus_hist->Write();
    em_bLoose_plus_hist->Write();
    em_bLoose_minus_hist->Write();
    mm_bTight_plus_hist->Write();
    mm_bTight_minus_hist->Write();
    mm_bLoose_plus_hist->Write();
    mm_bLoose_minus_hist->Write();
    tau_hist->Write();
    inclusive_hist->Write();
  }

  virtual ~PlotObject(){}
};


void stackPlots(TH1D* input_hist, std::vector<Sample> sample_vector_, TFile* output_file_)
{
  //  StackObject myStackObject;
  for(const auto & sample : sample_vector_)
    {
      PlotObject myPlotObj(input_hist, sample, output_file_);

      TFile* input_file = new TFile(sample.file_name,"READONLY");
      TTree* input_tree = (TTree*)input_file->Get("extraction_tree");
      //loop over trees
      int chainentries = input_tree->GetEntries();

      double mcwgt_branch=-999.;
      double vs_ttbar_score_branch=-999.;
      double vs_ttbar_bdtReco_score_branch=-999.;
      double vs_ttv_score_branch=-999.;
      bool isBtight_branch=false;
      bool isPositive_branch=false;
      bool isTau_branch=false;
      TString flavor_branch = "null";

      //      input_tree->SetBranchStatus("*",0);
      //      input_tree->SetBranchStatus("mcwgt",1);
      
      input_tree->SetBranchAddress("mcwgt", &mcwgt_branch);
      input_tree->SetBranchAddress("vs_ttbar_bdt_score", &vs_ttbar_score_branch);
      input_tree->SetBranchAddress("vs_ttbar_bdtReco_bdt_score", &vs_ttbar_bdtReco_score_branch);
      input_tree->SetBranchAddress("vs_ttv_bdt_score", &vs_ttv_score_branch);
      input_tree->Branch("bTight_category", &isBtight_branch);
      input_tree->Branch("posCharge_category", &isPositive_branch);
      input_tree->Branch("tau_category", &isTau_branch);
      input_tree->Branch("flavor_category", &flavor_branch);

      Int_t cachesize = 250000000;   //250 MBytes
      input_tree->SetCacheSize(cachesize);
      input_tree->SetCacheLearnEntries(20); 
      for(int i=0; i<chainentries; i++)
	{
	  printProgress(i,chainentries);
	  input_tree->GetEntry(i);
	  myPlotObj.Fill(vs_ttbar_score_branch, vs_ttv_score_branch, flavor_branch, isPositive_branch, isBtight_branch, isTau_branch, mcwgt_branch);
	  //	  myPlotObj.Fill(vs_ttbar_bdtReco_score_branch, vs_ttv_score_branch, flavor_branch, isPositive_branch, isBtight_branch, isTau_branch, mcwgt_branch);
	}
      input_file->Close();
      myPlotObj.Write();
      //etc
      //      myStackPlotObj.Add( myPlotObj, sample );
      // stack1->Add(hist1_);
      // stack1_legend->Add( hist1_, sample.legend_name );
      // stack2->Add(hist2_);
      // stack2_legend->Add( hist2_, sample.legend_name );
      //etc
    }

  //  myStackPlotObj.Draw();
  // TCanvas can1;
  // stack1->Draw();
  // TCanvas can2;
  // stack2->Draw();
  //etc 
  output_file_->Close();
}

void makeStackPlotsFinalShape(void)
{
  Sample tth("ttH", 2, 1, 0.2586, "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttH_aMCatNLO_bdtEval.root");
  Sample ttbar_fakes("fakes", 1, 4096, 189., "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttbar_powheg_bdtEval.root");
  
  std::vector<Sample> sample_vector; //push back in order you want stacked
  sample_vector.push_back(tth);
  sample_vector.push_back(ttbar_fakes);

  TFile *output_file = new TFile("fatStackPlots.root", "RECREATE"); //"UPDATE");
  TH1D* input_hist = new TH1D("bdt_output_","BDT output 2lss",7,0,7);
  stackPlots(input_hist, sample_vector, output_file);
}
