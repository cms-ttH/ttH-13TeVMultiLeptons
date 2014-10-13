// created by Geoff Smith

#include "ttHMultileptonAnalysis/TemplateMakers/interface/OSTwoLepAna.h"

OSTwoLepAna::OSTwoLepAna(const edm::ParameterSet& iConfig){} //Anything that needs to be done at creation time
OSTwoLepAna::~OSTwoLepAna(){} //Anything that needs to be done at destruction time

void OSTwoLepAna::beginJob() {} // job setup
void OSTwoLepAna::endJob() {} // job completion (file writing, etc.)

void OSTwoLepAna::analyze(const edm::Event&, const edm::EventSetup&) // this function is called at each event
{
	// analysis goes here
	cout << "test" << endl;
	
} 

void OSTwoLepAna::beginRun(edm::Run const&, edm::EventSetup const&){} // anything special for the beginning of a run
void OSTwoLepAna::endRun(edm::Run const&, edm::EventSetup const&){} // anything special for the end of a run

void OSTwoLepAna::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){} // anything special for the beginning of a lumi block
void OSTwoLepAna::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){} // anything special for the end of a lumi block


DEFINE_FWK_MODULE(OSTwoLepAna);
