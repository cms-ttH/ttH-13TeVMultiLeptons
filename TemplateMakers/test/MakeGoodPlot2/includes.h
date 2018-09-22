// Basic c++ and ROOT includes, and other external code goes here, as 
// well as some basic header files for the Histmaker and MakeGoodPlot
// classes. However, new code for filling histograms should be 
// included at the top of dooneevent.h. For new plots, code 
// should be included at the top of drawall.h. 

// c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath> 
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

//ROOT
#include "TSystem.h"
#include "TFile.h"
#include "TColor.h"
#include "TFileCollection.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TText.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TKey.h"
#include "TVector.h"
#include "TLorentzVector.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TChainElement.h"
#include "TTreeReader.h"
#include "ROOT/TProcessExecutor.hxx"
#include "ROOT/TTreeProcessorMP.hxx"
#include "TObjArray.h"


// Other stuff...
//#include "../variables.h"
//#include "../functionsTTH.cc" // should relocate this
#include "helperToolsEFT.h"
#include "variables.h"
#include "functionsTTH.cc"
#include "csvSF_treeReader_13TeV.C"

// #include "../sample_lists.h"
//#include "ttH-13TeVMultiLeptons/TemplateMakers/test/eventReconstructor.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
//#include "ttH-13TeVMultiLeptons/TemplateMakers/test/EFT_rwgt_fitting/TH1EFT.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)

// TMVA
#include "TMVA/Config.h"
// #include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

// #pragma omp parallel for // <- never got this to work

#endif

// end external includes

// --------- Header files in this (MakeGoodPlot2) directory ---------

#include "utils.h"
#include "loadsample.h"

// Stuff used by HistMaker
#include "HistMaker.h"
#include "datasets.h"
#include "bookhistos.h"
#include "setbranchaddresses.h"
#include "lep_selection.h"
#include "scalefactors.h"
#include "dooneevent.h" // <-- functions for filling hists are included inside this file
#include "run.h"
#include "collectresults.h"
#include "eventselection2.h"
#include "triggerstudies_eventselection.h"
#include "makedatadrivenbkgds.h"
#include "eventfit.h"


// Stuff used by MakeGoodPlot
#include "MakeGoodPlot.h"
#include "nicepalette.h"
#include "rateinfo.h"
#include "setup.h"
#include "GoodPlot.h"
#include "getroccurve.h"
#include "drawall.h" // <-- functions for making plots are included inside this file
