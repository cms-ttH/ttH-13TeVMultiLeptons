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
    int pdgID;
    double dxy;
    double dz;
    int charge;
    double relIso;

    //lepMVA variables
    double lepMVA;
    double chreliso;
    double nureliso;
    double matchedJetdR;
    double jetPtRatio;
    double csv;
    double sip3D;
    
    virtual ~Lepton(){};
    ClassDef(Lepton, 1);
    
  };

  class Electron : public Lepton
  {
  public:
    Electron(){} // default constructor
    
    double SCeta; //supercluster eta
    bool isGsfCtfScPixChargeConsistent;
    int numMissingInnerHits;
    bool passConversioVeto;
    double dEtaIn;
    double dPhiIn;
    double full5x5_sigmaIetaIeta;
    double hadronicOverEm;
    double mvaID;

    virtual ~Electron(){};
    ClassDef(Electron, 1); 

  };

  class Muon : public Lepton
  {
  public:
    Muon(){} // default constructor

    double chargeFlip;
    bool isPFMuon;
    bool isTrackerMuon;
    bool isGlobalMuon;
    double normalizedChi2;
    int numberOfValidMuonHits;
    int numberOfMatchedStations;
    int numberOfValidPixelHits;
    int trackerLayersWithMeasurement;
    //adding for medium ID
    double localChi2;
    double trKink;
    double validFrac;
    double segCompatibility;


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

  class GenParticle
  {
  public:
    GenParticle(){} // default constructor

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    int pdgID;
    int status;
    int mother_pdgID;
    int grandmother_pdgID;
    virtual ~GenParticle(){};
    ClassDef(GenParticle, 1); 
  };


} // end of namespace ttH
