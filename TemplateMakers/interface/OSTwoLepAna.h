// created by Geoff Smith

#include "ttHMultileptonAnalysis/TemplateMakers/src/MultileptonAna.cc"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/EGammaMvaEleEstimatorFWLite.h"

class OSTwoLepAna: public MultileptonAna, public edm::EDAnalyzer
{
	private:
		
		// EDAnalyzer-specific:
		virtual void beginJob() ;
      		virtual void analyze(const edm::Event&, const edm::EventSetup&);
      		virtual void endJob() ;
      		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      		virtual void endRun(edm::Run const&, edm::EventSetup const&);
      		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      		virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);		
		
		
		// OSTwoLep-specific vars (here, a bunch of trigger studies/counting stuff)
		double doublemucount;
		double doublemucount2;
		double doublemucount3;
		double doublemucount4;
		double doublemucount5;
		
		double doubleelecount;
		double doubleelecount2;
		
		double muelecount;
		double elemucount; 
		
		double tripelcount;
		
		double allcount_mumu[1000];
		double allcount_elel[1000];
		double allcount_muel[1000];
		double allcount_elmu[1000];		
		
		int numpassedcuts;
		double numpassedmumucuts;
		double numpassedelelcuts;
		double numpassedmuelcuts;
		double numpassedelmucuts;
		
		vstring alltriggerstostudy;
		vstring mumutriggerstostudy;
		vstring eleltriggerstostudy;
		vstring mueltriggerstostudy;
		vstring elmutriggerstostudy;
		vstring tripeltriggerstostudy;		
		
	
	public:
		explicit OSTwoLepAna(const edm::ParameterSet&);
		~OSTwoLepAna();
		
		// declare the tree
		TTree * summaryTree;
		
		// declare any histos
		TH1D *numtighteles;
		TH1D *numlooseeles;
		TH1D *numtightmuons;
		TH1D *numloosemuons;
		TH1D *numrawjets;
		TH1D *numjetsnoele;
		TH1D *numjetsnomu;
		TH1D *numjetsnomuorele;
		TH1D *numjetscorrected;
		TH1D *numjetsselectedloose;
		TH1D *numbtagsselectedlooseCSVM;
		TH1D *leadingtightmupt;
		TH1D *subleadingtightmupt;
		TH1D *leadingtightelept;
		TH1D *subleadingtightelept;
		TH1D *leadingtightleppt;
		TH1D *subleadingtightleppt;
		TH1D *jet1pt;
		TH1D *jet2pt;
		TH1D *jet3pt;
		TH1D *jet4pt;
		TH1D *met_pt;
		TH1D *hlt_count_hist;		
		
		
		TH2D *lep1_lep2_pt;

		//initialize collections
		//vecPatElectron selectedElectrons_loose_notight;

		//GenericCollectionSizeVariable2<std::vector<pat::Electron>>
		//numTightElectronz(vecPatElectron &, string);


		
};
