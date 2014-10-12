// created by Geoff Smith

#include "ttHMultileptonAnalysis/TemplateMakers/interface/MultileptonAna.h"

class OSTwoLepAna: public MultileptonAna, public edm::EDAnalyzer
{
	private: //does this need to be private?
	
		virtual void beginJob() ;
      		virtual void analyze(const edm::Event&, const edm::EventSetup&);
      		virtual void endJob() ;
      		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      		virtual void endRun(edm::Run const&, edm::EventSetup const&);
      		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      		virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
	
	public:
		explicit OSTwoLepAna(const edm::ParameterSet&);
		~OSTwoLepAna();
};
