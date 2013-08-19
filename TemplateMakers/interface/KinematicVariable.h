
#ifndef _KinematicVariable_h
#define _KinematicVariable_h


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

#include "BEAN/BEANmaker/interface/BtagWeight.h"
#include "BEAN/BEANmaker/interface/BEANhelper.h"

#include "BEAN/BEANmaker/interface/AnglesUtil.h"
#include "PhysicsTools/Utilities/interface/LumiReweightingStandAlone.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


#include "ttH-Multileptons/TemplateMakers/interface/BEANFileInterface.h"


using namespace std;

///////////////////////////////////////////////////
// 
//   Parent class describing how each kinematic
//     variable will work
//
//  Can't be abstract because you want to loop on it
//
//
//////////////////////////////////////////////////

class KinematicVariable {


public:

  // Do nothing
  KinematicVariable () {};

  BEANFileInterface *blocks;

  virtual void assignCollections( BEANFileInterface *col) {
    blocks = col;
  };
  
  virtual void evaluate ( ) {
    cout << "Error, you should not be using this function" << endl;
  };  
  virtual void attachToTree (TTree *)  {
    cout << "Error, you should not be using this funciton" << endl;
  };
  virtual void reset ( ) {
    cout << "Error, you should not be using this function"  << endl;
  };  

};


namespace KinematicVariableConstants {

  const float FLOAT_INIT = -9.0e20;
  const int INT_INIT = -99999999;

}

#endif // KinematicVariable
