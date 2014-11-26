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
		int num_BJetsLoose = -99;
		int num_Jets = -99;

		int num_preselectedLeptons = -99;

		int num_preselectedMuons = -99;
		int mu1_charge = -99;
		int mu2_charge = -99;
		float mu1_pt = -9.e6;
		float mu2_pt = -9.e6;
		float mu1_lepMVA = -9.e6;
		float mu2_lepMVA = -9.e6;
		int mu1_chargeFlip = -99;
		int mu2_chargeFlip = -99;
		
		float mu1_chRelIso = -9.e6;
		float mu1_nuRelIso = -9.e6;
		float mu1_jetdR = -9.e6;
		float mu1_jetPtRatio = -9.e6;
		float mu1_bTagCSV = -9.e6;
		float mu1_sip3d = -9.e6;



		int num_preselectedElectrons= -99;
		int ele1_charge= -99;
		int ele2_charge= -99;
		float ele1_pt = -9.e6;
		float ele2_pt = -9.e6;
		float ele1_lepMVA = -9.e6;
		float ele2_lepMVA = -9.e6;
		int ele1_chargeFlip= -99;
		int ele2_chargeFlip= -99;

		float ele1_chRelIso = -9.e6;
		float ele1_nuRelIso = -9.e6;
		float ele1_jetdR = -9.e6;
		float ele1_jetPtRatio = -9.e6;
		float ele1_bTagCSV = -9.e6;
		float ele1_sip3d = -9.e6;	
		int eventnum;
		int higgs_decay;
};
