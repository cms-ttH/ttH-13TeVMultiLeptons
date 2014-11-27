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
			
		void tree_add_branches();
		void initialize_variables();
	
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

		// tree branches:
				
		double mcwgt_intree;
		double wgt_intree;
		
		int numLooseMuons_intree;
		int numLooseElectrons_intree;
		int numTightMuons_intree;
		int numTightElectrons_intree;
		
		int numPreselectedLeptons_intree;
		int numTightLeptons_intree;
		int numLooseLeptons_intree;
		
		int numCernMuons_intree;
		int numCernElectrons_intree;
		int numCernLeptons_intree;
		int numCernJets_intree;

		double allJetCSV_intree;
		int numJets_intree;		
		vdouble testvect;
		


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




		TLorentzVectorCMS testTLV_intree;
		TLorentzVectorCMS MET_intree;
		//std::vector<math::XYZTLorentzVectorD> Jets_intree;
		vecTLorentzVectorCMS Jets_intree;
		vecTLorentzVectorCMS LooseElectrons_intree;
		vecTLorentzVectorCMS LooseMuons_intree;
		vecTLorentzVectorCMS TightElectrons_intree;
		vecTLorentzVectorCMS TightMuons_intree;
		vdouble	JetCSV_intree;

};

void OSTwoLepAna::tree_add_branches()
{
	
	// add the branches to the tree:
		
	summaryTree->Branch("mcwgt", &mcwgt_intree, "mcwgt/D");
	summaryTree->Branch("wgt", &wgt_intree, "wgt/D");

	summaryTree->Branch("numLooseMuons", &numLooseMuons_intree, "numLooseMuons/I");
      	summaryTree->Branch("numLooseElectrons", &numLooseElectrons_intree, "numLooseElectrons/I");
      	summaryTree->Branch("numTightMuons", &numTightMuons_intree, "numTightMuons/I");
      	summaryTree->Branch("numTightElectrons", &numTightElectrons_intree, "numTightElectrons/I");
      	
	//summaryTree->Branch("testvect", &testvect);
	//summaryTree->Branch("testTLV", &testTLV_intree);
	
	//summaryTree->Branch("Jets", "std::vector<TLorentzVector>", &Jets_intree);
	//summaryTree->Branch("Jets", "std::vector<math::XYZTLorentzVectorD>", &Jets_intree);
	summaryTree->Branch("Jets", &Jets_intree);
	summaryTree->Branch("MET", &MET_intree);
	summaryTree->Branch("LooseElectrons", &LooseElectrons_intree);
	summaryTree->Branch("LooseMuons", &LooseMuons_intree);
	summaryTree->Branch("TightElectrons", &TightElectrons_intree);
	summaryTree->Branch("TightMuons", &TightMuons_intree);
	summaryTree->Branch("JetCSV", &JetCSV_intree);




	summaryTree->Branch("num_BJetsLoose",&num_BJetsLoose);
	summaryTree->Branch("num_Jets",&num_Jets);

	summaryTree->Branch("num_Leptons",&num_preselectedLeptons);

	summaryTree->Branch("num_muons",&num_preselectedMuons);
	summaryTree->Branch("mu1_charge",&mu1_charge);
	summaryTree->Branch("mu2_charge",&mu2_charge);
	summaryTree->Branch("mu1_pt",&mu1_pt);
	summaryTree->Branch("mu2_pt",&mu2_pt);
	summaryTree->Branch("mu1_lepMVA",&mu1_lepMVA);
	summaryTree->Branch("mu2_lepMVA",&mu2_lepMVA);
	summaryTree->Branch("mu1_chargeFlip",&mu1_chargeFlip);
	summaryTree->Branch("mu2_chargeFlip",&mu2_chargeFlip);

	summaryTree->Branch("mu1_chreliso",&mu1_chRelIso);
	summaryTree->Branch("mu1_nureliso",&mu1_nuRelIso);
	summaryTree->Branch("mu1_jetdR",&mu1_jetdR);
	summaryTree->Branch("mu1_jetPtRatio",&mu1_jetPtRatio);
	summaryTree->Branch("mu1_bTagCSV",&mu1_bTagCSV);
	summaryTree->Branch("mu1_sip3d",&mu1_sip3d);

	summaryTree->Branch("num_electrons",&num_preselectedElectrons);
	summaryTree->Branch("ele1_charge",&ele1_charge);
	summaryTree->Branch("ele2_charge",&ele2_charge);
	summaryTree->Branch("ele1_pt",&ele1_pt);
	summaryTree->Branch("ele2_pt",&ele2_pt);
	summaryTree->Branch("ele1_lepMVA",&ele1_lepMVA);
	summaryTree->Branch("ele2_lepMVA",&ele2_lepMVA);
	summaryTree->Branch("ele1_chargeFlip",&ele1_chargeFlip);
	summaryTree->Branch("ele2_chargeFlip",&ele2_chargeFlip);

	summaryTree->Branch("ele1_chreliso",&ele1_chRelIso);
	summaryTree->Branch("ele1_nureliso",&ele1_nuRelIso);
	summaryTree->Branch("ele1_jetdR",&ele1_jetdR);
	summaryTree->Branch("ele1_jetPtRatio",&ele1_jetPtRatio);
	summaryTree->Branch("ele1_bTagCSV",&ele1_bTagCSV);
	summaryTree->Branch("ele1_sip3d",&ele1_sip3d);

	summaryTree->Branch("event",&eventnum);
	summaryTree->Branch("higgs_decay",&higgs_decay);



	
	
	
}

void OSTwoLepAna::initialize_variables()
{
	testTLV_intree.SetPxPyPzE(0.,0.,0.,0.);
	
	testvect.clear();
	
	mcwgt_intree = -9999.;
	wgt_intree = -9999.;
	
	numLooseMuons_intree = -1;
	numLooseElectrons_intree = -1;
	numTightMuons_intree = -1;
	numTightElectrons_intree = -1;
	
	Jets_intree.clear();
	MET_intree.SetPxPyPzE(0.,0.,0.,0.);
	LooseElectrons_intree.clear();
	LooseMuons_intree.clear();
	TightElectrons_intree.clear();
	TightMuons_intree.clear();
	JetCSV_intree.clear();
	
	num_BJetsLoose = -99;
	num_Jets = -99;

	num_preselectedLeptons = -99;

	num_preselectedMuons = -99;
        mu1_charge = -99;
        mu2_charge = -99;
        mu1_pt = -9.e6;
        mu2_pt = -9.e6;
        mu1_lepMVA = -9.e6;
        mu2_lepMVA = -9.e6;
        mu1_chargeFlip = -99;
	mu2_chargeFlip = -99;

        mu1_chRelIso = -9.e6;
        mu1_nuRelIso = -9.e6;
        mu1_jetdR = -9.e6;
        mu1_jetPtRatio = -9.e6;
        mu1_bTagCSV = -9.e6;
        mu1_sip3d = -9.e6;

	num_preselectedElectrons= -99;
	ele1_charge= -99;
	ele2_charge= -99;
        ele1_pt = -9.e6;
        ele2_pt = -9.e6;
        ele1_lepMVA = -9.e6;
        ele2_lepMVA = -9.e6;
        ele1_chargeFlip= -99;
        ele2_chargeFlip= -99;

	ele1_chRelIso = -9.e6;
	ele1_nuRelIso = -9.e6;
        ele1_jetdR = -9.e6;
        ele1_jetPtRatio = -9.e6;
        ele1_bTagCSV = -9.e6;
        ele1_sip3d = -9.e6;

        higgs_decay = -9e6;
	
}
