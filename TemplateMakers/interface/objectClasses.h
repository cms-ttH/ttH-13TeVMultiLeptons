#ifndef TTH_OBJ_CLASSES
#define TTH_OBJ_CLASSES

#include <vector>

#include "TObject.h"
#include "Math/LorentzVector.h"

namespace ttH
{
  class Lepton
  {
  public:
    Lepton(){
      clear();
    } // default constructor
    
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    int pdgID; // this is the reco pdgID
    double dxy;
    double dz;
    int charge;
    double relIso;
    double miniIso;
    //gen info
    int genPdgID;
    bool isPromptFinalState;
    bool isDirectPromptTauDecayProductFinalState;
    int genMotherPdgID;
    int genGrandMotherPdgID;

    //lepMVA variables
    double lepMVA;
    double miniIsoCharged;
    double miniIsoNeutral;
    //double matchedJetdR;
    double jetPtRatio;
    double jetPtRel;
    double csv;
    double sip3D;
    int jet_nCharged_tracks;
    
    // extra for sync
    double miniAbsIsoCharged;
    double miniAbsIsoNeutral;
    double rho;
    double effArea;
    double miniIsoR;
    double miniAbsIsoNeutralcorr;    
    void clear(void)
    {

      obj.SetPxPyPzE(0.,0.,0.,0.);
      charge = 0;
      pdgID = -9999;
      genPdgID = -9999;
      genMotherPdgID = -9999;
      genGrandMotherPdgID = -9999;
      dxy = -99.;
      dz = -99.;
      relIso = -99.;
      miniIso = -99.;
      
      lepMVA = -99.;
      miniIsoCharged = -99.;
      miniIsoNeutral = -99.;
      //matchedJetdR = -99.;
      jetPtRatio = -99.;
      jetPtRel = -99.;
      csv = -99.;
      sip3D = -99.;
      jet_nCharged_tracks = -99;
      // extra for sync
      miniAbsIsoCharged = -99.;
      miniAbsIsoNeutral = -99.;
      rho = -99.;
      effArea = -99.;
      miniIsoR = -99.;
      miniAbsIsoNeutralcorr = -99.;    

    }
    
    
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
  
  class Tau // different enough to NOT make this public Lepton
  {
  public:
    Tau(){} // default constructor
    
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };    
    
    int charge;
    int genPdgID;
    int genMotherPdgID;
    int genGrandMotherPdgID;
    
    double dxy;
    double dz;
    double decayModeFinding;
    double mvaID;
    //double miniIso; // to be added..
    
    virtual ~Tau(){};
    ClassDef(Tau, 1); 

  };
   
  
  
  class Jet
  {
  public:
    Jet(){
      clear();
    } // default constructor
    
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    double charge;
    int genPdgID; // this is the matched genParton (not genJet)
    int genMotherPdgID;
    int genGrandMotherPdgID;
    double csv;
    double qgid;
    int pdgID; //place holder for Geoff's templated functions
    
    void clear(void)
    {
      obj.SetPxPyPzE(0.,0.,0.,0.); 
      charge = 0.;
      genPdgID = -9999;
      genMotherPdgID = -9999;
      genGrandMotherPdgID = -9999;
      csv = -.2;
      qgid = -99.;      
      pdgID = -9999;
    }

    virtual ~Jet(){};
    ClassDef(Jet, 1); 

  };

  class MET
  {
  public:
    MET(){} // default constructor

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };

    int pdgID; //place holder for Geoff's templated functions 
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

    //gen information
    bool isPromptFinalState;
    bool isPromptDecayed;
    bool isDirectPromptTauDecayProductFinalState;

    unsigned int child0;
    unsigned int child1;
    unsigned int mother;
    unsigned int grandmother;

    virtual ~GenParticle(){};
    ClassDef(GenParticle, 1); 
  };


} // end of namespace ttH

#endif
