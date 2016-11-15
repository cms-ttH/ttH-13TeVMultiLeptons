//Charlie Mueller 10/20/2016
#include <iostream>
#include "TSystem.h"
#include "TKey.h"
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

class Sample
{
private:
public:
  Sample(string name_ = "sample")
  {
    sample_name = name_;
    ee_count = 0.;
    em_count = 0.;
    mm_count = 0.;
  }

  void update(TH1D* hist_)
  {
    string hist_title = hist_->GetName();//.c_str();
    if ( hist_title.find(sample_name) == std::string::npos ) return;
    double integral = hist_->Integral();
    if ( hist_title.find("_ee_") != std::string::npos ) ee_count += integral;
    if ( hist_title.find("_em_") != std::string::npos ) em_count += integral;
    if ( hist_title.find("_mm_") != std::string::npos ) mm_count += integral;
  }

  string sample_name;
  double ee_count;
  double em_count;
  double mm_count;
};

void tableMaker(void)
{
  Sample ttH("ttH");
  Sample ttW("ttW");
  Sample ttZ("ttZ");
  Sample ttGammaStar("ttGammaStar");
  Sample fakes("fakes");
  Sample flips("flips");  
  std::vector<Sample*> samples = {&ttH, &ttW, &ttZ, &ttGammaStar, &fakes, &flips};

  TFile* input_file_ = new TFile("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/fatStackPlots.root","READONLY");
  //  TFile* input_file_ = new TFile("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/fatStackPlots_ichep.root","READONLY");
  TIter next(input_file_->GetListOfKeys());
  TKey *key;
  while ( ( key = (TKey*)next()) )
    {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if ( !cl->InheritsFrom("TH1") ) continue;
      TH1D *hist = (TH1D*)key->ReadObj();
      for (const auto & sample_ : samples) (*sample_).update(hist);
    }

  std::ofstream output; output.open("yields_2lss.txt");

  output << setiosflags(ios::fixed) << setw(20) << setprecision(1);
  output <<
    setw(10) << "Process" <<
    setw(10) << "mm" << 
    setw(10) << "ee" << 
    setw(10) << "em" << endl;
  for (const auto & sample_ : samples)
    {
      output << setiosflags(ios::fixed) << setprecision(1);
      output << 
	setw(10) << sample_->sample_name <<
	setw(10) << sample_->mm_count <<
	setw(10) << sample_->ee_count <<
	setw(10) <<sample_->em_count << endl;
    }

 }
