#include <vector>

#include "TObject.h"
//#include "TLorentzVector.h"

//#include "DataFormats/Math/interface/LorentzVectorFwd.h"
//#include "DataFormats/Math/interface/LorentzVector.h"
//#include "TMath.h"
//#include "Math/Vector3D.h"
//#include "Math/Vector4D.h"
#include "Math/LorentzVector.h"

//typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > myLorentzVector;

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




} // end of namespace ttH
