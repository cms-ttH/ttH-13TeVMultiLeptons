
#ifndef _TTreeWrapper_h
#define _TTreeWrapper_h


#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH3.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
//Root includes
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

//#include "LumiReweightingStandAlone.h"
//#include "PUConstants.h"

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

//Headers for the data items
#include "BEAN/Collections/interface/BNelectron.h"
#include "BEAN/Collections/interface/BNevent.h"
#include "BEAN/Collections/interface/BNjet.h"
#include "BEAN/Collections/interface/BNmcparticle.h"
#include "BEAN/Collections/interface/BNmet.h"
#include "BEAN/Collections/interface/BNmuon.h"
#include "BEAN/Collections/interface/BNphoton.h"
#include "BEAN/Collections/interface/BNsupercluster.h"
#include "BEAN/Collections/interface/BNtrack.h"
#include "BEAN/Collections/interface/BNtrigger.h"
#include "BEAN/Collections/interface/BNskimbits.h"
#include "BEAN/Collections/interface/BNtrigobj.h"
#include "BEAN/Collections/interface/BNprimaryvertex.h"


// headers for python config processing

//#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
//#include "FWCore/ParameterSet/interface/ProcessDesc.h"
//#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "BEAN/BEANmaker/interface/BtagWeight.h"
#include "BEAN/BEANmaker/interface/BEANhelper.h"

#include "BEAN/BEANmaker/interface/AnglesUtil.h"
#include "PhysicsTools/Utilities/interface/LumiReweightingStandAlone.h"
// For MVA reprocessing
//#include "TMVAGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"




#endif



////////////////////////////////////////////////////
//
// The tree making code has grown very large 
// and interconnected.
//
// This class attempts to factorize some of it
// 
//
//////////////////////////////////////////////////


class TTreeWrapper {

public:

  TTreeWrapper ();

  void initializeTree(TTree * inputTree);

  bool checkInit () ;

  void resetBranches ();
  void dumpBranches ();

  void addBranch(string bName, string type );
  
  void fillBranch(string bName, float val);
  void fillBranch(string bName, int val);
  void fillBranch(string bName, unsigned val);

  void fillTree () ;


  map<string, int*> intBranches;
  map<string, float*> floatBranches;
  map<string, unsigned int*> uintBranches;

  TTree * myTree;

  bool isOK;

  bool myVerboseFlag;

  //Sample numbers may not match event->sample; used for setMCsample() only
  static const int dInt = -9000000;
  static constexpr  float dFloat = -9000000.0;


};





#endif 
