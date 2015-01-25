#include <vector>

#include "TObject.h"

namespace ttH
{
  class Lepton
  {
  public:
    Lepton(){} // default constructor
    
    //    int i;
    double px;
    double py;
    double pz;
    double pt;
    double energy;
    double eta;
    double phi;
    double id;
    
    virtual ~Lepton(){};
    ClassDef(Lepton, 1); // Lepton

  };

  class Electron
  {
  public:
    Electron(){} // default constructor
    
    double px;
    double py;
    double pz;
    double pt;
    double energy;
    double eta;
    double SCeta;
    double phi;
    double pdgID;
    double dxy;
    double dz;
    int charge;
    bool isGsfCtfScPixChargeConsistent;
    int numMissingInnerHits;
    bool passConversioVeto;
    double mvaID;
    //lepMVA variables
    double lepMVA;
    double chreliso;
    double nureliso;
    double matchedJetdR;
    double jetPtRatio;
    double btagCSV;
    double sip3D;


    virtual ~Electron(){};
    ClassDef(Electron, 1); 

  };

  class Muon
  {
  public:
    Muon(){} // default constructor
    
    double px;
    double py;
    double pz;
    double pt;
    double energy;
    double eta;
    double phi;
    double pdgID;
    double dxy;
    double dz;
    int charge;
    double chargeFlip;
    //lepMVA variables
    double lepMVA;
    double chreliso;
    double nureliso;
    double matchedJetdR;
    double jetPtRatio;
    double btagCSV;
    double sip3D;

    virtual ~Muon(){};
    ClassDef(Muon, 1); 

  };
  
  class Jet
  {
  public:
    Jet(){} // default constructor
    
    double pt;
    double energy;
    double mass;
    double eta;
    double phi;
    int charge;
    int pdgID;
    double csv;

    virtual ~Jet(){};
    ClassDef(Jet, 1); 

  };




} // end of namespace ttH
