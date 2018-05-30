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
    double deepcsv;
    double sip3D;
    int jet_nCharged_tracks;
    double correctedPt;
    
    // extra for sync
    double miniAbsIsoCharged;
    double miniAbsIsoNeutral;
    double rho;
    double effArea;
    double miniIsoR;
    double miniAbsIsoNeutralcorr;    
    
    // POG IDs:
    bool idTightPOG;
    bool idMediumPOG;
    bool idLoosePOG;
    
    bool isPreselected;
    
    void clear(void)
    {
      obj.SetPxPyPzE(0.,0.,0.,0.);
      charge = 0;
      pdgID = -9999;
      genPdgID = -9999;
      genMotherPdgID = -9999;
      genGrandMotherPdgID = -9999;
      dxy = -99.;
      correctedPt = -99.;
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
      deepcsv = -99.;
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
    //ClassDef(Lepton, 1);
    
  };

  class Electron : public Lepton
  {
  public:
    Electron(){} // default constructor
    
    double SCeta; //supercluster eta
    bool isGsfCtfScPixChargeConsistent;
    bool isGsfScPixChargeConsistent;
    int numMissingInnerHits;
    bool passConversioVeto;
    double dEtaIn;
    double dPhiIn;
    double full5x5_sigmaIetaIeta;
    double hadronicOverEm;
    double mvaID;
    double mvaIDGP;
    bool passesEtaDepCuts;
    
    virtual ~Electron(){};
    //ClassDef(Electron, 1); 

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
    //ClassDef(Muon, 1); 

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
    //ClassDef(Tau, 1); 

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
    int flavor;
    double csv;
    double DeepCSV;
    double DeepCSVprobb;
    double DeepCSVprobbb;
    double DeepCSVprobc;
    double DeepCSVprobudsg;
    double qgid;
    bool passPUID; // only available in >90X MINIAOD
    double PUMVA;
    int pdgID; //place holder for Geoff's templated functions
    double ptD;
    double axis1;
    int mult;
    
    void clear(void)
    {
      obj.SetPxPyPzE(0.,0.,0.,0.); 
      charge = 0.;
      genPdgID = -9999;
      genMotherPdgID = -9999;
      genGrandMotherPdgID = -9999;
      flavor = -99;
      csv = -2.;
      DeepCSV = -2.;
      DeepCSVprobb = -2.;
      DeepCSVprobbb = -2.;
      DeepCSVprobc = -2.;
      DeepCSVprobudsg = -2.;      
      PUMVA = -2.;
      passPUID = false;
      qgid = -99.;      
      pdgID = -9999;
      ptD = -9999;
      axis1 = -9999;
      mult = -9999;
    }

    virtual ~Jet(){};
    //ClassDef(Jet, 1); 

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
    //ClassDef(MET, 1); 
  };

  class GenParticle
  {
  public:
    GenParticle(){
      clear();
    } // default constructor

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > obj; 
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > tlv() const { return  obj; };
    int pdgID;
    int status;
    double charge;
    //gen information
    bool isPromptFinalState;
    bool isPromptDecayed;
    bool isDirectPromptTauDecayProductFinalState;

    unsigned int child0;
    unsigned int child1;
    unsigned int mother;
    unsigned int grandmother;

    void clear(void)
    {
      obj.SetPxPyPzE(0.,0.,0.,0.); 
      charge = 0.;
      pdgID = -9999;
      status = 9999;
      isPromptFinalState = false;
      isDirectPromptTauDecayProductFinalState = false;
      child0 = 9999;
      child1 = 9999;
      mother = 9999;
      grandmother = 9999;
    }



    virtual ~GenParticle(){};
    //ClassDef(GenParticle, 1); 
  };


} // end of namespace ttH

#endif
