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
    
    int charge;
    bool isGsfCtfScPixChargeConsistent;
    bool numMissingInnerHits;
    bool passConversioVeto;

    //lepMVA variables
    double lepMVA;
    double chreliso;
    double nureliso;
    double matchedJetdR;
    double jetPtRatio;
    double btagCSV;
    double sip3D;
    double mvaID;

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
    double id;
    
    int charge;
    bool charge1;
    bool charge2;
    bool charge3;

    //lepMVA variables
    double lepMVA;
    double chreliso;
    double nureliso;
    double matchedJetdR;
    double jetPtRatio;
    double btagCSV;
    double sip3d;

    virtual ~Muon(){};
    ClassDef(Muon, 1); 

  };
  
  class Jet
  {
  public:
    Jet(){} // default constructor
    
    double px;
    double py;
    double pz;
    double pt;
    double energy;
    double eta;
    double phi;
    
    virtual ~Jet(){};
    ClassDef(Jet, 1); 

  };




} // end of namespace ttH
