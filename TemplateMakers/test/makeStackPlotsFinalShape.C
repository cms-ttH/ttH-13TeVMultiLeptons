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

double shift(double unshifted_value)
{
  //  double shift = 0.7;
  //  double shifted_value = ( unshifted_value + 1. )*( shift ) - 1.;
  double shifted_value = unshifted_value;
  if (unshifted_value >= 0.) shifted_value = unshifted_value-0.2;
  return shifted_value;
}

class Sample
{
private:
  TH1D* getEvtHist(void)
  {
    TString hist_file_name="";
    if (legend_name == "ttH") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/tth_aMC_old_selection_tree_2lss.root";
    else if (legend_name == "fakes") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttbar_semiLep_powheg_selection_2lss_original.root";
    else if (legend_name == "flips") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttbar_diLep_powheg_tranche3_selection_2lss.root";
    else if (legend_name == "ttW") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttW_aMCatNLO_selection_2lss.root";
    else if (legend_name == "ttZ") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttZ_aMCatNLO_selection_2lss.root";
    else if (legend_name == "ttGammaStar") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttGammaStar_selection_tree_2lss_original.root";
    else if (legend_name == "tttt") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/tttt_selection_2lss.root";
    else if (legend_name == "tqZ") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/tqZ_selection_2lss.root";
    else if (legend_name == "WWqq") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WWqq_rares_selection_2lss.root";
    else if (legend_name == "WWds") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WW_doublescatering_rares_selection_2lss.root";
    else if (legend_name == "WWZ") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WWZ_rares_selection_2lss.root";
    else if (legend_name == "WZZ") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WZZ_rares_selection_2lss.root";
    else if (legend_name == "ZZZ") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ZZZ_rares_selection_2lss.root";
    else if (legend_name == "WW_diboson") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WW_diboson_selection_2lss.root";
    else if (legend_name == "ZZ_diboson") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ZZ_diboson_selection_2lss.root";
    else if (legend_name == "WZ_diboson") hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WZ_diboson_selection_2lss.root";
    else  hist_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/tth_aMC_old_selection_tree_2lss.root";
    TFile* input_file_ = new TFile(hist_file_name,"READONLY");
    TH1D* sum_hist_ = (TH1D*)input_file_->Get("numInitialWeightedMCevents");
    return sum_hist_;
  }
public:
  Sample(TString leg_name_="sample", int fill_color_=1, int fill_style_=1, double xsec_=1., TString file_name_="file_name.root")
  {
    legend_name = leg_name_;
    fill_color = fill_color_;
    fill_style = fill_style_;
    file_name = file_name_;

     TH1D* sum_hist = getEvtHist();
     double total_events = sum_hist->GetBinContent(1);

    double integrated_lumi = 12900.; //integrated lumi in pb
    if (leg_name_ != "data_obs") xsec = xsec_ * integrated_lumi / total_events; //scale the xsec to #of events
    else xsec = xsec_;
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
    return_hist_->SetFillStyle(sample.fill_style);
    return_hist_->SetLineColor(1);
    return_hist_->SetMarkerColor(sample.fill_color);
    return return_hist_;
  }

  double shiftWeights(TString sample_name, TString flav_, double weight_)
  {
    double output_weight = weight_;

    //version0?
    // if (flav_.CompareTo("ee")==0)
    //   {
    // 	///	if (sample_name == "fakes") output_weight*=(11.1/10.7)*(23.1/11.1);
    // 	// else if (sample_name == "flips") output_weight*=(5.8/8.8)*(6.7/5.8);
    // 	// else if (sample_name == "ttZ") output_weight*=(7.5/3.0);
    // 	//	 else if (sample_name == "ttW") output_weight*=(6.9/9.6);
    // 	// else if (sample_name == "ttH") output_weight*=(3.4/5.5);
    //   }
    // else if (flav_.CompareTo("em")==0)
    //   {
    // 	// if (sample_name == "fakes") output_weight*=(41.5/31.5)*(61.9/41.5);
    // 	// else if (sample_name == "flips") output_weight*=(6.6/17.6)*(10./6.6);
    // 	// else if (sample_name == "ttZ") output_weight*=(15.3/8.);
    // 	// else if (sample_name == "ttW") output_weight*=(24.6/33.5);
    // 	// else if (sample_name == "ttH") output_weight*=(11.3/17.4);
    //   }
    // else if (flav_.CompareTo("mm")==0)
    //   {
    // 	if (sample_name == "flips") output_weight*= 0.;
    // 	// else if (sample_name == "fakes") output_weight*= 1.5*(33.4/24.);
    // 	// else if (sample_name == "ttZ") output_weight*=(5.8/4.4);
    // 	// else if (sample_name == "ttW") output_weight*=(18.2/22.2);
    // 	// else if (sample_name == "ttH") output_weight*=(8./11.1);
    //   }

    if (flav_.CompareTo("ee")==0)
      {
	if (sample_name == "fakes") output_weight*=23.1/10.2;
	else if (sample_name == "flips") output_weight*=6.7/14.1*6.7/8.9;
	else if (sample_name == "ttZ" || sample_name == "ttGammaStar") output_weight*=7.5/4.6;
	else if (sample_name == "ttW") output_weight*=6.9/9.9;
	else if (sample_name == "ttH") output_weight*=3.4/5.4;
      }
    else if (flav_.CompareTo("em")==0)
      {
	if (sample_name == "fakes") output_weight*=61.9/30.1;
        else if (sample_name == "flips") output_weight*=10./43.1*10./8.7;
	else if (sample_name == "ttZ" || sample_name == "ttGammaStar") output_weight*=15.3/9.4;
	else if (sample_name == "ttW") output_weight*=24.6/33.3;
	else if (sample_name == "ttH") output_weight*=11.3/16.8;
      }
    else if (flav_.CompareTo("mm")==0)
      {
	if (sample_name == "flips") output_weight*= 0.;
	else if (sample_name == "fakes") output_weight*= 33.4/15.3;
	else if (sample_name == "ttZ" || sample_name == "ttGammaStar") output_weight*=5.8/5.4;
	else if (sample_name == "ttW") output_weight*=18.2/21.9;
	else if (sample_name == "ttH") output_weight*=8.0/10.6;
      }


    return output_weight;
  }

  void FillCategories(int bin_num_, double weight_, TString flav_, bool isPlus_, bool bTight_, bool isTau_)
  {
    
    if ( isTau_ ) tau_hist->Fill( bin_num_, weight_ );

    else if (flav_.CompareTo("ee")==0)
      {
	weight_ = shiftWeights(sample.legend_name,flav_,weight_);
	if ( isPlus_ ) ee_plus_hist->Fill( bin_num_, weight_ );
	else ee_minus_hist->Fill( bin_num_, weight_ );
      }
    else if (flav_.CompareTo("em")==0)
      {
	weight_ = shiftWeights(sample.legend_name,flav_,weight_);
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
	weight_ = shiftWeights(sample.legend_name,flav_,weight_);
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

    inclusive_hist->Fill( bin_num_, weight_ );

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
    //original shape
    if ( ttbar_score <= -0.2 ) FillCategories(1, weight, flavor, isPlus, bTight, isTau);//-0.2 //-0.2=best
    else if ( ttbar_score <= 0.1 ) FillCategories(2, weight, flavor, isPlus, bTight, isTau);//0.1 //0.1=best
    else if ( ttbar_score <= 0.4 ) //0.4 //0.55=best
      {
    	if ( ttv_score <= 0.3 ) FillCategories(3, weight, flavor, isPlus, bTight, isTau); //0.3 //0.2=best
    	else  FillCategories(4, weight, flavor, isPlus, bTight, isTau);
      }
    else if ( ttv_score <= 0.1 ) FillCategories(5, weight, flavor, isPlus, bTight, isTau);//0.1 //0.25=best
    else if ( ttv_score <= 0.4 ) FillCategories(6, weight, flavor, isPlus, bTight, isTau); //0.4 //0.4=best 
    else FillCategories(7, weight, flavor, isPlus, bTight, isTau);

    //new shape
    // if ( ttbar_score <= -0.1 ) FillCategories(1, weight, flavor, isPlus, bTight, isTau);//-0.2 //-0.2=best
    // else if ( ttbar_score <= 0.3 ) FillCategories(2, weight, flavor, isPlus, bTight, isTau);//0.1 //0.1=best
    // else if ( ttbar_score <= 0.6 ) //0.4 //0.55=best
    //   {
    // 	if ( ttv_score <= 0.3 ) FillCategories(3, weight, flavor, isPlus, bTight, isTau); //0.3 //0.2=best
    // 	else  FillCategories(4, weight, flavor, isPlus, bTight, isTau);
    //   }
    // else if ( ttv_score <= 0.1 ) FillCategories(5, weight, flavor, isPlus, bTight, isTau);//0.1 //0.25=best
    // else if ( ttv_score <= 0.4 ) FillCategories(6, weight, flavor, isPlus, bTight, isTau); //0.4 //0.4=best 
    // else FillCategories(7, weight, flavor, isPlus, bTight, isTau);

  }
  
  void Write(void)
  {
    double norm_factor;
    // if (sample.legend_name != "data_obs") norm_factor = sample.xsec * event_eff / inclusive_hist->Integral();
    // else norm_factor = sample.xsec / inclusive_hist->Integral();
    norm_factor = sample.xsec;

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
	    background += max(background_hist->GetBinContent(bin), 0.1e-20);
	  }
	sOverSqrtB += pow(signal / sqrt(background),2);
      }
    return sOverSqrtB;
  }
  
  void makeStacks(THStack* input_stack, double& sigOverSqrtBkg_)
  {
    TString input_stack_name = input_stack->GetName();
    TH1D* hist_to_stack;

    TH1D* signal_hist=0;
    vector<TH1D*> background_hists;
    //loop over samples
    for (const auto & myPlotObj : sample_plots)
      {
	if ( myPlotObj.sample.legend_name.CompareTo("data_obs") == 0) continue; //don't stack dummy-data
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

    inclusive_stack = new THStack("inclusive","");
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

    cout << "Signal / sqrt(Background) without categories = " << sqrt(sigOverSqrtB_noCat) << endl; 
    cout << "Signal / sqrt(Background) = " << sqrt(sigOverSqrtB) << endl; 

  }//default constructor
  void drawSingleHist(THStack* stack_to_draw_)
  {
    TString stack_name = stack_to_draw_->GetName();
    TString can_name = stack_name + "_can";
    TString save_name = stack_name + ".root";

    TCanvas* can = new TCanvas(can_name, can_name,10,32,530,580);
    //    TLegend *leg = new TLegend(0.4410646,0.7296544,0.8536122,0.8690078);
    //    leg->SetFillColor(0);
    
    stack_to_draw_->Draw("hist");
    stack_to_draw_->SetMaximum(179);//125
    stack_to_draw_->GetXaxis()->SetTitle("MVA (ttH,tt/ttV) bin");
    stack_to_draw_->Draw("hist");
    gPad->BuildLegend(0.4410646,0.7296544,0.8536122,0.8690078);
    gPad->SetTicky();
    can->SaveAs(save_name);
  }
  void Draw(void)
  {
    drawSingleHist(inclusive_stack);
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
      //      TTree* input_tree = (TTree*)input_file->Get("extraction_tree_standard");
      //      TTree* input_tree = (TTree*)input_file->Get("extraction_tree_recobdt");
      TTree* input_tree = (TTree*)input_file->Get("extraction_tree_recobdt_v1");

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

      int every_other = 3;
      for(int i=0; i<chainentries; i++)
	{
	  //	  printProgress(i,chainentries);
	  input_tree->GetEntry(i);

	  myPlotObj.Fill(vs_ttbar_score_branch, vs_ttv_score_branch, *flavor_branch, isPositive_branch, isBtight_branch, isTau_branch, mcwgt_branch);
	  //	  myPlotObj.Fill(vs_ttbar_bdtReco_score_branch, vs_ttv_score_branch, *flavor_branch, isPositive_branch, isBtight_branch, isTau_branch, mcwgt_branch);
	  
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
  // double tth_weight = 0.2586*(32206./2965618.);
  // double ttbar_semilep_weight = 182.*(3090./112551635.);
  // double ttw_weight = 0.2043*(3291./130274.);
  // double ttz_weight = 0.2529*(1021./185229.);
  // double ttbar_dilep_weight = 87.3*(833./30682157.);

  double tth_weight = 0.2586;
  double ttbar_semilep_weight = 182.;
  double ttw_weight = 0.2043;
  double ttz_weight = 0.2529;
  double ttGammaStar_weight = 0.0283;
  double ttbar_dilep_weight = 87.3;
  double tttt_weight = 0.009103;
  double tqZ_weight =  0.0758;
  double WW_diboson_weight = 10.481;
  double ZZ_diboson_weight = 1.256;
  double WZ_diboson_weight = 4.102;
  double WWqq_weight = 0.03711;
  double WWds_weight = 1.64;
  double WWZ_weight = 0.1651;
  double WZZ_weight = 0.05565;
  double ZZZ_weight = 0.01398;
  
  int diboson_color = 880;
  int rares_color = 860-9;

  Sample tth("ttH", 2, 1001, tth_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tth_aMC_old_selection_2lss.root");
  Sample ttbar_fakes("fakes", 1, 3005, ttbar_semilep_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_semiLep_powheg_selection_2lss.root");
  Sample ttw("ttW", 32, 1001, ttw_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttW_aMCatNLO_selection_2lss.root");
  Sample ttz("ttZ", 8, 1001, ttz_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttZ_aMCatNLO_selection_2lss.root");
  Sample ttGammaStar("ttGammaStar", 8, 1001, ttGammaStar_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttGammaStar.root");
  //Sample ttbar_flips("flips", 1, 3006, ttbar_dilep_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_diLep_powheg_tranche3_selection_2lss.root");
  Sample ttbar_flips("flips", 1, 3006, ttbar_dilep_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttbar-diLep-madgraph_selection_tree_2lss.root");
  Sample tttt("tttt", rares_color, 1001, tttt_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tttt_selection_2lss.root");
  Sample tqZ("tqZ", rares_color, 1001, tqZ_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tqZ_selection_2lss.root");
  Sample WW("WW_diboson", diboson_color, 1001, WW_diboson_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WW_diboson_selection_2lss.root");
  Sample ZZ("ZZ_diboson", diboson_color, 1001, ZZ_diboson_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ZZ_diboson_selection_2lss.root");
  Sample WZ("WZ_diboson", diboson_color, 1001, WZ_diboson_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WZ_diboson_selection_2lss.root");
  Sample WWqq("WWqq", rares_color, 1001, WWqq_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WWqq_rares_selection_2lss.root");
  Sample WWds("WWds", rares_color, 1001, WWds_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WW_doublescatering_rares_selection_2lss.root");
  Sample WWZ("WWZ", rares_color, 1001, WWZ_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WWZ_rares_selection_2lss.root");
  Sample WZZ("WZZ", rares_color, 1001, WZZ_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WZZ_rares_selection_2lss.root");
  Sample ZZZ("ZZZ", rares_color, 1001, ZZZ_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ZZZ_rares_selection_2lss.root");
  Sample psuedo_data("data_obs", 1, 3005, 1., "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_semiLep_powheg_selection_2lss.root");
  //ICHEP datasets
  // Sample tth("ttH", 2, 1001, tth_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/tth_aMC_old_selection_tree_2lss.root");
  // Sample ttbar_fakes("fakes", 1, 3005, ttbar_semilep_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttbar-semiLep-powheg_selection_tree_2lss.root");
  // Sample ttw("ttW", 32, 1001, ttw_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttW-aMCatNLO_selection_tree_2lss.root");
  // Sample ttz("ttZ", 8, 1001, ttz_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttZ-aMCatNLO_selection_tree_2lss.root");
  // Sample ttbar_flips("flips", 1, 3006, ttbar_dilep_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttbar-diLep-madgraph_selection_tree_2lss.root");
  // Sample psuedo_data("data_obs", 1, 3005, 1., "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/ttbar-semiLep-powheg_selection_tree_2lss.root");

  //old with wrong 2lss selection
  // Sample tth("ttH", 2, 1001, tth_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tth_aMC_old_selection_2lss.root");
  // Sample ttbar_fakes("fakes", 1, 3005, ttbar_semilep_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_semiLep_powheg_2lss.root");
  // Sample ttw("ttW", 32, 1001, ttw_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttW_aMCatNLO_2lss.root");
  // Sample ttz("ttZ", 8, 1001, ttz_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttZ_aMCatNLO_2lss.root");
  // Sample ttbar_flips("flips", 1, 3006, ttbar_dilep_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_diLep_madgraph_2lss.root");
  // Sample tttt("tttt", rares_color, 1001, tttt_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tttt_2lss.root");
  // Sample tqZ("tqZ", rares_color, 1001, tqZ_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tqZ_2lss.root");
  // Sample WW("WW_diboson", diboson_color, 1001, WW_diboson_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WZ_diboson_2lss.root");
  // Sample ZZ("ZZ_diboson", diboson_color, 1001, ZZ_diboson_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ZZ_diboson_2lss.root");
  // Sample WZ("WZ_diboson", diboson_color, 1001, WZ_diboson_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WZ_diboson_2lss.root");
  // Sample WWqq("WWqq", rares_color, 1001, WWqq_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WWqq_rares_2lss.root");
  // Sample WWds("WWds", rares_color, 1001, WWds_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WW_doublescatering_rares_2lss.root");
  // Sample WWZ("WWZ", rares_color, 1001, WWZ_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WWZ_rares_2lss.root");
  // Sample WZZ("WZZ", rares_color, 1001, WZZ_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WZZ_rares_2lss.root");
  // Sample ZZZ("ZZZ", rares_color, 1001, ZZZ_weight, "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ZZZ_rare_2lss.root");
  // Sample psuedo_data("data_obs", 1, 3005, 1., "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_semiLep_powheg_2lss.root");



  std::vector<Sample> sample_vector; //push back in order you want stacked
  sample_vector.push_back(ttbar_flips);
  sample_vector.push_back(ttbar_fakes);  
  sample_vector.push_back(tttt);
  sample_vector.push_back(tqZ);
  sample_vector.push_back(WWqq);
  sample_vector.push_back(WWds);
  sample_vector.push_back(WWZ);
  sample_vector.push_back(WZZ);
  sample_vector.push_back(ZZZ);
  sample_vector.push_back(WW);
  sample_vector.push_back(WZ);
  sample_vector.push_back(ZZ);
  sample_vector.push_back(ttGammaStar);
  sample_vector.push_back(ttz);
  sample_vector.push_back(ttw);
  sample_vector.push_back(tth);
  sample_vector.push_back(psuedo_data);

  TFile *output_file = new TFile("fatStackPlots.root", "RECREATE"); //"UPDATE");
  TH1D* input_hist = new TH1D("bdt_output_","BDT output 2lss",7,1,8);
  stackPlots(input_hist, sample_vector, output_file);
}
