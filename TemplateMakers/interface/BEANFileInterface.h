
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
#include "BEAN/Collections/interface/BNlepton.h"
#include "BEAN/Collections/interface/BNleptonCollection.h"


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
    rawMuonCollection(0),
    tightMuonCollection(0),
    looseMuonCollection(0),
    preselectedMuonCollection(0),
    tightLooseMuonCollection(0),
    loosePreselectedMuonCollection(0),
    tightLoosePreselectedMuonCollection(0),
    rawElectronCollection(0),
    tightElectronCollection(0),
    looseElectronCollection(0),
    preselectedElectronCollection(0),
    tightLooseElectronCollection(0),
    loosePreselectedElectronCollection(0),
    tightLoosePreselectedElectronCollection(0),
    rawLeptonCollection(0),
    tightLeptonCollection(0),
    looseLeptonCollection(0),
    preselectedLeptonCollection(0),
    tightLooseLeptonCollection(0),
    loosePreselectedLeptonCollection(0),
    tightLoosePreselectedLeptonCollection(0),
    metCollection(0),
    jetCollection(0),
    jetCollectionLooseCSV(0),
    jetCollectionMediumCSV(0),
    mcParticleCollection(0),
    eventCollection(0),
    hltCollection (0),
    primaryVertexCollection(0),
    jetsForLepMVACollection(0)
  {};

  // Copy constructor
  // By default you'll get a shallow copy of all these pointers
  // which should be fine


  //important kinematic stuff
  BNmuonCollection *  rawMuonCollection;
  BNmuonCollection *  tightMuonCollection;
  BNmuonCollection *  looseMuonCollection;
  BNmuonCollection *  preselectedMuonCollection;
  BNmuonCollection *  tightLooseMuonCollection;
  BNmuonCollection *  loosePreselectedMuonCollection;
  BNmuonCollection *  tightLoosePreselectedMuonCollection;

  BNelectronCollection *  rawElectronCollection;
  BNelectronCollection *  tightElectronCollection;
  BNelectronCollection *  looseElectronCollection;
  BNelectronCollection *  preselectedElectronCollection;
  BNelectronCollection *  tightLooseElectronCollection;
  BNelectronCollection *  loosePreselectedElectronCollection;
  BNelectronCollection *  tightLoosePreselectedElectronCollection;

  BNleptonCollection *  rawLeptonCollection;
  BNleptonCollection *  tightLeptonCollection;
  BNleptonCollection *  looseLeptonCollection;
  BNleptonCollection *  preselectedLeptonCollection;
  BNleptonCollection *  tightLooseLeptonCollection;
  BNleptonCollection *  loosePreselectedLeptonCollection;
  BNleptonCollection *  tightLoosePreselectedLeptonCollection;


  BNmetCollection *   metCollection;
  BNjetCollection * jetCollection;
  BNjetCollection * jetCollectionLooseCSV;
  BNjetCollection * jetCollectionMediumCSV;    

  
  BNmcparticleCollection * mcParticleCollection;
  BNeventCollection * eventCollection;
  BNtriggerCollection * hltCollection;
  BNprimaryvertexCollection * primaryVertexCollection;

  // -- only need these for the lepMVA
  BNjetCollection * jetsForLepMVACollection;
  

  bool checkJets() {
    if (jetCollection == 0 )
      return false;
    return true;
  };

  bool checkRawMuons() {
    if (rawMuonCollection == 0 )
      return false;
    return true;
  };
  
  bool checkTightMuons() {
    if (tightMuonCollection == 0 )
      return false;
    return true;
  };
  
  bool checkLooseMuons() {
    if (looseMuonCollection == 0)
      return false;
    return true;
  };

  bool checkPreselectedMuons() {
    if (preselectedMuonCollection == 0 )
      return false;
    return true;
  };
  
  bool checkTightLooseMuons() {
    if (tightLooseMuonCollection == 0 )
      return false;
    return true;
  };
  
  bool checkLoosePreselectedMuons() {
    if (loosePreselectedMuonCollection == 0)
      return false;
    return true;
  };

  bool checkTightLoosePreselectedMuons() {
    if (tightLoosePreselectedMuonCollection == 0 )
      return false;
    return true;
  };
  
  bool checkRawElectrons() {
    if (rawElectronCollection == 0 )
      return false;
    return true;
  };
  
  bool checkTightElectrons() {
    if (tightElectronCollection == 0 )
      return false;
    return true;
  };
  
  bool checkLooseElectrons() {
    if (looseElectronCollection == 0)
      return false;
    return true;
  };

  bool checkPreselectedElectrons() {
    if (preselectedElectronCollection == 0 )
      return false;
    return true;
  };
  
  bool checkTightLooseElectrons() {
    if (tightLooseElectronCollection == 0 )
      return false;
    return true;
  };
  
  bool checkLoosePreselectedElectrons() {
    if (loosePreselectedElectronCollection == 0)
      return false;
    return true;
  };

  bool checkTightLoosePreselectedElectrons() {
    if (tightLoosePreselectedElectronCollection == 0 )
      return false;
    return true;
  };
  

  void print () {

    cout << "BEANFileIterface.print() ............." << endl
         << "    rawMuonCollection " << rawMuonCollection << endl
         << "    tightMuonCollection " << tightMuonCollection << endl
         << "    looseMuonCollection " << looseMuonCollection << endl
         << "    preselectedMuonCollection " << preselectedMuonCollection << endl
         << "    rawElectronCollection " << rawElectronCollection << endl
         << "    tightElectronCollection " << tightElectronCollection << endl
         << "    looseElectronCollection " << looseElectronCollection << endl
         << "    preselectedElectronCollection " << preselectedElectronCollection << endl
         << "    metCollection " << metCollection << endl
         << "    jetCollection " << jetCollection << endl
         << "    mcParticleCollection " << mcParticleCollection << endl
         << "    eventCollection " << eventCollection << endl
         << "    hltCollection  " << hltCollection << endl
         << "    primaryVertexCollection " << primaryVertexCollection << endl;

  };

};




#endif // BEANFileInterface
