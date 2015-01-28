#include <vector>

#include "TObject.h"
#include "Math/LorentzVector.h"

namespace ttH
{
  class Lepton
  {
  public:
    Lepton(){} // default constructor
    
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    double id;
    
    virtual ~Lepton(){};
    ClassDef(Lepton, 1);
    
  };

  class Electron
  {
  public:
    Electron(){} // default constructor
    
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    double SCeta; //supercluster eta
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
    
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    double pdgID;
    double dxy;
    double dz;
    int charge;
    double chargeFlip;
    bool isPFMuon;
    bool isTrackerMuon;
    bool isGlobalMuon;
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
    
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    int charge;
    int pdgID;
    double csv;

    virtual ~Jet(){};
    ClassDef(Jet, 1); 

  };

  class MET
  {
  public:
    MET(){} // default constructor

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    float pt_forSync;
    float phi_forSync;
    
    virtual ~MET(){};
    ClassDef(MET, 1); 
  };


} // end of namespace ttH
