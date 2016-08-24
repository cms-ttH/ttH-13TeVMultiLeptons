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
#include "THStack.h"
#include "TCanvas.h"
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
  TFile* fout;
  TH1D* template_hist;

  TH1D* SetTitleAndName(TString name_postfix_, TString title_postfix_ )
  {    
    TString hist_name = template_hist->GetName(); hist_name += "_"+sample.legend_name+"_"+name_postfix_;
    TString hist_title = template_hist->GetTitle(); hist_title += " "+sample.legend_name+" "+title_postfix_;
    auto return_hist_ = new TH1D(hist_name, hist_title, template_hist->GetNbinsX(),1,8);
    return_hist_->SetFillColor(sample.fill_color);
    return_hist_->SetMarkerColor(sample.fill_color);
    return return_hist_;
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
  PlotObject(TH1D* template_hist_=0, Sample sample_=Sample(), TFile* fout_=0):
    sample(sample_),
    fout(fout_),
    template_hist(template_hist_)
  {
    // sample = sample_;
    // fout = fout_;
    // template_hist = template_hist_;

    inclusive_hist = SetTitleAndName("inclusive","inclusive");
    ee_plus_hist = SetTitleAndName("ee_p","ee +");
    ee_minus_hist = SetTitleAndName("ee_m","ee -");
    em_bTight_plus_hist = SetTitleAndName("em_bt_p","em btight +");
    em_bTight_minus_hist = SetTitleAndName("em_bt_m","em btight -");
    em_bLoose_plus_hist = SetTitleAndName("em_bl_p","em bloose +");
    em_bLoose_minus_hist = SetTitleAndName("em_bl_m","em bloose -");
    mm_bTight_plus_hist = SetTitleAndName("mm_bt_p","mm btight +");
    mm_bTight_minus_hist = SetTitleAndName("mm_bt_m","mm btight -");
    mm_bLoose_plus_hist = SetTitleAndName("mm_bl_p","mm bloose +");
    mm_bLoose_minus_hist = SetTitleAndName("mm_bl_m","mm bloose -");
    tau_hist = SetTitleAndName("tau","tau");

  }//default constructor
  Sample sample;  
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
    //old shape
    // if ( ttbar_score <= -0.2) FillCategories(1, weight, flavor, isPlus, bTight, isTau);//-0.2 //-0.2=best
    // else if ( ttbar_score <= 0.1) FillCategories(2, weight, flavor, isPlus, bTight, isTau);//0.1 //0.1=best
    // else if ( ttbar_score <= 0.4 ) //0.4 //0.55=best
    //   {
    // 	if ( ttv_score <= 0.3 ) FillCategories(3, weight, flavor, isPlus, bTight, isTau); //0.3 //0.2=best
    // 	else  FillCategories(4, weight, flavor, isPlus, bTight, isTau);
    //   }
    // else if ( ttv_score <= 0.1 ) FillCategories(5, weight, flavor, isPlus, bTight, isTau);//0.1 //0.25=best
    // else if ( ttv_score <= 0.3 ) FillCategories(6, weight, flavor, isPlus, bTight, isTau); //0.4 //0.4=best 
    // else FillCategories(7, weight, flavor, isPlus, bTight, isTau);

    //new shape
    if ( ttbar_score <= -0.2) FillCategories(1, weight, flavor, isPlus, bTight, isTau);//-0.2 //-0.2=best
    else if ( ttbar_score <= 0.1) FillCategories(2, weight, flavor, isPlus, bTight, isTau);//0.1 //0.1=best
    else if ( ttbar_score <= 0.55 ) //0.4 //0.55=best
      {
    	if ( ttv_score <= 0.2 ) FillCategories(3, weight, flavor, isPlus, bTight, isTau); //0.3 //0.2=best
    	else  FillCategories(4, weight, flavor, isPlus, bTight, isTau);
      }
    else if ( ttv_score <= 0.3 ) FillCategories(5, weight, flavor, isPlus, bTight, isTau);//0.1 //0.25=best
    else if ( ttv_score <= 0.4 ) FillCategories(6, weight, flavor, isPlus, bTight, isTau); //0.4 //0.4=best 
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

    fout->cd();

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

class StackHelper
{
private:
  std::vector<PlotObject> sample_plots;
  THStack* inclusive_stack;
  THStack* ee_plus_stack;
  THStack* ee_minus_stack;
  THStack* em_bTight_plus_stack;
  THStack* em_bTight_minus_stack;
  THStack* em_bLoose_plus_stack;
  THStack* em_bLoose_minus_stack;
  THStack* mm_bTight_plus_stack;
  THStack* mm_bTight_minus_stack;
  THStack* mm_bLoose_plus_stack;
  THStack* mm_bLoose_minus_stack;
  THStack* tau_stack;

  double calculateSoSqrtB(TH1D* signal_hist_, vector<TH1D*> background_hists)
  {
    double sOverSqrtB = 0.;
    for (int bin=0; bin <= signal_hist_->GetNbinsX(); bin++)
      {
	double signal = 0.1e-20;
	double background = 0.1e-20;
	
	signal = signal_hist_->GetBinContent(bin);
	for (const auto & background_hist : background_hists)
	  {
	    background += background_hist->GetBinContent(bin);
	  }
	sOverSqrtB += signal / sqrt(background);
	//	sOverSqrtB += signal / background;
      }
    return sOverSqrtB;
  }
  
  void makeStacks(THStack* input_stack, double& sigOverSqrtBkg_)
  {
    TString input_stack_name = input_stack->GetName();
    TH1D* hist_to_stack;

    TH1D* signal_hist;
    vector<TH1D*> background_hists;
    //loop over samples
    for (const auto & myPlotObj : sample_plots)
      {
	if ( input_stack_name.CompareTo("inclusive")==0 ) hist_to_stack = myPlotObj.inclusive_hist; 
	else if ( input_stack_name.CompareTo("ee_p")==0 ) hist_to_stack = myPlotObj.ee_plus_hist; 
	else if ( input_stack_name.CompareTo("ee_m")==0 ) hist_to_stack = myPlotObj.ee_minus_hist; 
	else if ( input_stack_name.CompareTo("em_bt_p")==0 ) hist_to_stack = myPlotObj.em_bTight_plus_hist; 
	else if ( input_stack_name.CompareTo("em_bt_m")==0 ) hist_to_stack = myPlotObj.em_bTight_minus_hist; 
	else if ( input_stack_name.CompareTo("em_bl_p")==0 ) hist_to_stack = myPlotObj.em_bLoose_plus_hist; 
	else if ( input_stack_name.CompareTo("em_bl_m")==0 ) hist_to_stack = myPlotObj.em_bLoose_minus_hist; 
	else if ( input_stack_name.CompareTo("mm_bt_p")==0 ) hist_to_stack = myPlotObj.mm_bTight_plus_hist; 
	else if ( input_stack_name.CompareTo("mm_bt_m")==0 ) hist_to_stack = myPlotObj.mm_bTight_minus_hist; 
	else if ( input_stack_name.CompareTo("mm_bl_p")==0 ) hist_to_stack = myPlotObj.mm_bLoose_plus_hist; 
	else if ( input_stack_name.CompareTo("mm_bl_m")==0 ) hist_to_stack = myPlotObj.mm_bLoose_minus_hist;
	else if ( input_stack_name.CompareTo("tau")==0 ) hist_to_stack = myPlotObj.tau_hist;
	input_stack->Add(hist_to_stack);

	if ( myPlotObj.sample.legend_name.CompareTo("ttH") == 0) signal_hist = hist_to_stack;
	else background_hists.push_back( hist_to_stack );
      }
    
    if (signal_hist)
      {
	sigOverSqrtBkg_ += calculateSoSqrtB(signal_hist, background_hists);
      }
    cout << input_stack_name << ": " << setprecision(10) << sigOverSqrtBkg_ << endl;
  }

public:
  StackHelper(std::vector<PlotObject> sample_plots_)
  {
    sample_plots = sample_plots_;

    inclusive_stack = new THStack("inclusive","inclusive");
    ee_plus_stack = new THStack("ee_p","ee +");
    ee_minus_stack = new THStack("ee_m","ee -");
    em_bTight_plus_stack = new THStack("em_bt_p","em btight +");
    em_bTight_minus_stack = new THStack("em_bt_m","em btight -");
    em_bLoose_plus_stack = new THStack("em_bl_p","em bloose +");
    em_bLoose_minus_stack = new THStack("em_bl_m","em bloose -");
    mm_bTight_plus_stack = new THStack("mm_bt_p","mm btight +");
    mm_bTight_minus_stack = new THStack("mm_bt_m","mm btight -");
    mm_bLoose_plus_stack = new THStack("mm_bl_p","mm bloose +");
    mm_bLoose_minus_stack = new THStack("mm_bl_m","mm bloose -");
    tau_stack = new THStack("tau","tau");
  
    double sigOverSqrtB = 0.;
    double sigOverSqrtB_noCat = 0.;

    makeStacks(inclusive_stack, sigOverSqrtB_noCat);
    makeStacks(ee_plus_stack, sigOverSqrtB);
    makeStacks(ee_minus_stack, sigOverSqrtB);
    makeStacks(em_bTight_plus_stack, sigOverSqrtB);
    makeStacks(em_bTight_minus_stack, sigOverSqrtB);
    makeStacks(em_bLoose_plus_stack, sigOverSqrtB);
    makeStacks(em_bLoose_minus_stack, sigOverSqrtB);
    makeStacks(mm_bTight_plus_stack, sigOverSqrtB);
    makeStacks(mm_bTight_minus_stack, sigOverSqrtB);
    makeStacks(mm_bLoose_plus_stack, sigOverSqrtB);
    makeStacks(mm_bLoose_minus_stack, sigOverSqrtB);
    makeStacks(tau_stack, sigOverSqrtB);

    cout << "Signal / sqrt(Background) without categories = " << sigOverSqrtB_noCat << endl; 
    cout << "Signal / sqrt(Background) = " << sigOverSqrtB << endl; 

  }//default constructor
  void drawSingleHist(THStack* stack_to_draw_)
  {
    TString stack_name = stack_to_draw_->GetName();
    TString can_name = stack_name + "_can";
    TString save_name = stack_name + ".root";
    TCanvas* can = new TCanvas(can_name, can_name,10,32,530,580);
    //    TLegend *leg = new TLegend(0.4410646,0.7296544,0.8536122,0.8690078);
    //    leg->SetFillColor(0);
    stack_to_draw_->Draw();
    //    gPad->BuildLegend(0.4410646,0.7296544,0.8536122,0.8690078);
    //    can->SaveAs(save_name);
  }
  void Draw(void)
  {
    // drawSingleHist(inclusive_stack);
    // drawSingleHist(ee_plus_stack);
    // drawSingleHist(ee_minus_stack);
    // drawSingleHist(em_bTight_plus_stack);
    // drawSingleHist(em_bTight_minus_stack);
    // drawSingleHist(em_bLoose_plus_stack);
    // drawSingleHist(em_bLoose_minus_stack);
    // drawSingleHist(mm_bTight_plus_stack);
    // drawSingleHist(mm_bTight_minus_stack);
    // drawSingleHist(mm_bLoose_plus_stack);
    // drawSingleHist(mm_bLoose_minus_stack);
    // drawSingleHist(tau_stack);
  }
  virtual ~StackHelper(){}
};

void stackPlots(TH1D* input_hist, std::vector<Sample> sample_vector_, TFile* output_file_)
{
  vector<PlotObject> plotObject_vector;
  for(const auto & sample : sample_vector_)
    {
      PlotObject myPlotObj(input_hist, sample, output_file_);

      TFile* input_file = new TFile(sample.file_name,"READONLY");
      TTree* input_tree = (TTree*)input_file->Get("extraction_tree_v2");

      //loop over trees
      int chainentries = input_tree->GetEntries();

      double mcwgt_branch=-999.;
      double vs_ttbar_score_branch=-999.;
      double vs_ttbar_bdtReco_score_branch=-999.;
      double vs_ttv_score_branch=-999.;
      bool isBtight_branch=false;
      bool isPositive_branch=false;
      bool isTau_branch=false;
      TString *flavor_branch=0;

      //      input_tree->SetBranchStatus("*",0);
      //      input_tree->SetBranchStatus("mcwgt",1);
      
      input_tree->SetBranchAddress("mcwgt", &mcwgt_branch);
      input_tree->SetBranchAddress("vs_ttbar_bdt_score", &vs_ttbar_score_branch);
      input_tree->SetBranchAddress("vs_ttbar_bdtReco_bdt_score", &vs_ttbar_bdtReco_score_branch);
      input_tree->SetBranchAddress("vs_ttv_bdt_score", &vs_ttv_score_branch);
      input_tree->SetBranchAddress("bTight_category", &isBtight_branch);
      input_tree->SetBranchAddress("posCharge_category", &isPositive_branch);
      input_tree->SetBranchAddress("tau_category", &isTau_branch);
      input_tree->SetBranchAddress("flavor_category", &flavor_branch);

      Int_t cachesize = 250000000;   //250 MBytes
      input_tree->SetCacheSize(cachesize);
      input_tree->SetCacheLearnEntries(20); 
      for(int i=0; i<chainentries; i++)
	{
	  printProgress(i,chainentries);
	  input_tree->GetEntry(i);
	  //myPlotObj.Fill(vs_ttbar_score_branch, vs_ttv_score_branch, *flavor_branch, isPositive_branch, isBtight_branch, isTau_branch, mcwgt_branch);
	  myPlotObj.Fill(vs_ttbar_bdtReco_score_branch, vs_ttv_score_branch, *flavor_branch, isPositive_branch, isBtight_branch, isTau_branch, mcwgt_branch);
	}
      input_file->Close();
      myPlotObj.Write();
      plotObject_vector.push_back( myPlotObj );
    }

  StackHelper myStackHelper( plotObject_vector );
  myStackHelper.Draw();
  output_file_->Close();
}

void makeStackPlotsFinalShape(void)
{
  double tth_weight = 0.2586*(32206./2965618.);
  double ttbar_semilep_weight = 182.*(3090./112551635.);
  double ttw_weight = 0.2043*(3291./130274.);
  double ttz_weight = 0.2529*(1021./185229.);
  double ttbar_dilep_weight = 87.3*(833./30682157.);

  Sample tth("ttH", 2, 1, tth_weight, "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttH_aMCatNLO_bdtEval.root");
  Sample ttbar_fakes("fakes", 16, 1, ttbar_semilep_weight, "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttbar_powheg_bdtEval.root");
  Sample ttw("ttW", 32, 1, ttw_weight, "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttw_aMCatNLO_2lss_bdtEval_v1p5.root");
  Sample ttz("ttZ", 8, 1, ttz_weight, "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttz_aMCatNLO_2lss_bdtEval_v1p5.root");
  Sample ttbar_flips("flips", 1, 1, ttbar_dilep_weight, "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttbar_dilep_mg5mlm_2lss_bdtEval_v1p5.root");
  
  std::vector<Sample> sample_vector; //push back in order you want stacked
  sample_vector.push_back(tth);
  sample_vector.push_back(ttbar_fakes);
  sample_vector.push_back(ttw);
  sample_vector.push_back(ttz);
  sample_vector.push_back(ttbar_flips);

  TFile *output_file = new TFile("fatStackPlots.root", "RECREATE"); //"UPDATE");
  TH1D* input_hist = new TH1D("bdt_output_","BDT output 2lss",7,1,8);
  stackPlots(input_hist, sample_vector, output_file);
}
