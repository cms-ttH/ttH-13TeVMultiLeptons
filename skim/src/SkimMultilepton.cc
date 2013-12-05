#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "BEAN/BEANmaker/interface/BEANhelper.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"

class SkimMultilepton: public edm::EDFilter {
   public:
      explicit SkimMultilepton(const edm::ParameterSet&);
      ~SkimMultilepton();

   private:
      virtual void beginJob();
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob();

      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

    // ----------member data ---------------------------
    std::string era_;
    edm::InputTag eleSrc_, muoSrc_, lepMvaJetSrc_;
    muonID::muonID muonTightID_, muonLooseID_, muonPreselectedID_;
    electronID::electronID electronTightID_, electronLooseID_, electronPreselectedID_;
  //    BEANhelper beanHelper;
    HelperLeptonCore lepHelper;
    BEANFileInterface selectedCollections;
};

// constructors and destructor
SkimMultilepton::SkimMultilepton(const edm::ParameterSet& iConfig):
    era_(iConfig.getUntrackedParameter<std::string>("era")),
    muonTightID_(muonID::muonSideTightMVA),
    muonLooseID_(muonID::muonSideLooseMVA),
    muonPreselectedID_(muonID::muonSide),
    electronTightID_(electronID::electronSideTightMVA),
    electronLooseID_(electronID::electronSideLooseMVA),
    electronPreselectedID_(electronID::electronSide)
{
  //now do what ever initialization is needed

  //Check to make sure we're not doing anything in consistent
  // need to define an int for the sample... this doesn't matter, so hardcode to ttbar
  int nSample = 2500;
  std::string dataSetName = "ttbar";
  //  beanHelper.SetUp(era_, nSample, analysisType::DIL, false, dataSetName, false, true, "all");

  lepHelper.setupAnalysisParameters(era_, "ttbar");
}

SkimMultilepton::~SkimMultilepton()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}

// ------------ method called on each new Event  ------------
bool
SkimMultilepton::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  using namespace edm;

  //Check the primary vertex
  edm::Handle<BNprimaryvertexCollection> pvHandle;
  iEvent.getByLabel("BNproducer","offlinePrimaryVertices", pvHandle);
  BNprimaryvertexCollection const &pvs = *pvHandle;

  int numpv = 0;
  for(PVIter iPV = pvs.begin(); iPV != pvs.end(); ++iPV ){
	if ( (iPV->ndof>=4) &&
         (fabs(iPV->z)<24) &&
         (fabs(iPV->rho)<2) &&
         ! iPV->isFake) ++numpv;
  }

  //If we have no vertex, no point in going further...
  if (numpv == 0) return false;

  lepHelper.initializeInputCollections(iEvent, true, selectedCollections);
  lepHelper.fillSIP(*(lepHelper.rawCollections.rawMuonCollection), false);
  lepHelper.fillSIP(*(lepHelper.rawCollections.rawElectronCollection), false);
  lepHelper.fillLepJetPtRatio(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), false);
  lepHelper.fillLepJetPtRatio(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), false);
  lepHelper.fillLepJetDeltaR(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), false);
  lepHelper.fillLepJetDeltaR(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), false);
  lepHelper.fillLepJetBTagCSV(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection));
  lepHelper.fillLepJetBTagCSV(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection));

  lepHelper.getTightLoosePreselectedElectrons(electronTightID_, electronLooseID_, electronPreselectedID_, &selectedCollections);
  lepHelper.getTightLoosePreselectedMuons(muonTightID_, muonLooseID_, muonPreselectedID_, &selectedCollections);

  int numTightLoosePreselectedMuons = selectedCollections.tightLoosePreselectedMuonCollection->size();
  int numTightLoosePreselectedElectrons = selectedCollections.tightLoosePreselectedElectronCollection->size();

  if (numTightLoosePreselectedMuons + numTightLoosePreselectedElectrons < 2) return false;

  //Didn't find a reason to skip this event
  return true;
}

// ------------ method called once each job just before starting event loop  ------------
void
SkimMultilepton::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
SkimMultilepton::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool
SkimMultilepton::beginRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool
SkimMultilepton::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool
SkimMultilepton::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool
SkimMultilepton::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(SkimMultilepton);
