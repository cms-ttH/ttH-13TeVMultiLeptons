
#ifndef _BEANFileInterface_h
#define _BEANFileInterface_h


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


////////////////////////////////////////////////////////
//
//  Class description:
//    
//    Collect a big group of pointers
//    that you will use to look at the contents 
//    of any BEAN file. 
//
//
////////////////////////////////////////////////////////




class BEANFileInterface {


public:

  BEANFileInterface () :
    muonCollection(0),
    looseMuonCollection(0),
    metCollection(0),
    jetCollection(0),
    eleCollection(0),
    looseEleCollection(0),
    mcParticleCollection(0),
    eventCollection(0),
    hltCollection (0),
    primaryVertexCollection(0)
  {};

  // Copy constructor
  // By default you'll get a shallow copy of all these pointers
  // which should be fine


  //important kinematic stuff
  BNmuonCollection *  muonCollection;
  BNmuonCollection *  looseMuonCollection;
  
  BNmetCollection *   metCollection;
  BNjetCollection * jetCollection;

  BNelectronCollection * eleCollection;
  BNelectronCollection * looseEleCollection;
  
  BNmcparticleCollection * mcParticleCollection;
  BNeventCollection * eventCollection;
  BNtriggerCollection * hltCollection;
  BNprimaryvertexCollection * primaryVertexCollection;
  

  bool checkJets() {
    if (jetCollection == 0 )
      return false;
    return true;
  };

  bool checkMuons() {
    if (muonCollection==0 )
      return false;
    return true;
  };

  bool checkElectrons() {
    if (eleCollection==0)
      return false;
    return true;
  };


};




#endif // BEANFileInterface
