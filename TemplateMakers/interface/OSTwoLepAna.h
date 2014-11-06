// created by Geoff Smith

#include "ttHMultileptonAnalysis/TemplateMakers/src/MultileptonAna.cc"

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
		
		TTree * summaryTree;
		
		electronID::electronID electronTightID;
		electronID::electronID electronLooseID;
		electronID::electronID electronPreselectedID;

		muonID::muonID muonTightID;
		muonID::muonID muonLooseID;
		muonID::muonID muonPreselectedID;

		tauID::tauID tauTightID;
		// tauID::tauID tauLooseID = tauID::tauVLoose;
		tauID::tauID tauPreselectedID;
		vector<ArbitraryVariable*> kinVars;
		vector<ArbitraryVariable*> cutVars;
		
		
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
		TH1D *hlt_count_hist;		
		
		TH2D *lep1_lep2_pt;
		
		
		
};
