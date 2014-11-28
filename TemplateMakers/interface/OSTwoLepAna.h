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

		// OSTwoLep-specific
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
				
		int num_BJetsLoose_intree;
		int num_Jets_intree;

		int num_preselectedLeptons_intree;

		int num_preselectedMuons_intree;
		int mu1_charge_intree;
		int mu2_charge_intree;
		float mu1_pt_intree;
		float mu2_pt_intree;
		float mu1_lepMVA_intree;
		float mu2_lepMVA_intree;
		int mu1_chargeFlip_intree;
		int mu2_chargeFlip_intree;
		
		float mu1_chRelIso_intree;
		float mu1_nuRelIso_intree;
		float mu1_jetdR_intree;
		float mu1_jetPtRatio_intree;
		float mu1_bTagCSV_intree;
		float mu1_sip3d_intree;

		int num_preselectedElectrons_intree;
		int ele1_charge_intree;
		int ele2_charge_intree;
		float ele1_pt_intree;
		float ele2_pt_intree;
		float ele1_lepMVA_intree;
		float ele2_lepMVA_intree;
		int ele1_chargeFlip_intree;
		int ele2_chargeFlip_intree;

		float ele1_chRelIso_intree;
		float ele1_nuRelIso_intree;
		float ele1_jetdR_intree;
		float ele1_jetPtRatio_intree;
		float ele1_bTagCSV_intree;
		float ele1_sip3d_intree;
		int eventnum_intree;
		int higgs_decay_intree;


		TLorentzVectorCMS testTLV_intree;
		TLorentzVectorCMS MET_intree;
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
      	
	summaryTree->Branch("Jets", &Jets_intree);
	summaryTree->Branch("MET", &MET_intree);
	summaryTree->Branch("LooseElectrons", &LooseElectrons_intree);
	summaryTree->Branch("LooseMuons", &LooseMuons_intree);
	summaryTree->Branch("TightElectrons", &TightElectrons_intree);
	summaryTree->Branch("TightMuons", &TightMuons_intree);
	summaryTree->Branch("JetCSV", &JetCSV_intree);

	summaryTree->Branch("num_BJetsLoose",&num_BJetsLoose_intree);
	summaryTree->Branch("num_Jets",&num_Jets_intree);

	summaryTree->Branch("num_Leptons",&num_preselectedLeptons_intree);

	summaryTree->Branch("num_muons",&num_preselectedMuons_intree);
	summaryTree->Branch("mu1_charge",&mu1_charge_intree);
	summaryTree->Branch("mu2_charge",&mu2_charge_intree);
	summaryTree->Branch("mu1_pt",&mu1_pt_intree);
	summaryTree->Branch("mu2_pt",&mu2_pt_intree);
	summaryTree->Branch("mu1_lepMVA",&mu1_lepMVA_intree);
	summaryTree->Branch("mu2_lepMVA",&mu2_lepMVA_intree);
	summaryTree->Branch("mu1_chargeFlip",&mu1_chargeFlip_intree);
	summaryTree->Branch("mu2_chargeFlip",&mu2_chargeFlip_intree);

	summaryTree->Branch("mu1_chreliso",&mu1_chRelIso_intree);
	summaryTree->Branch("mu1_nureliso",&mu1_nuRelIso_intree);
	summaryTree->Branch("mu1_jetdR",&mu1_jetdR_intree);
	summaryTree->Branch("mu1_jetPtRatio",&mu1_jetPtRatio_intree);
	summaryTree->Branch("mu1_bTagCSV",&mu1_bTagCSV_intree);
	summaryTree->Branch("mu1_sip3d",&mu1_sip3d_intree);

	summaryTree->Branch("num_electrons",&num_preselectedElectrons_intree);
	summaryTree->Branch("ele1_charge",&ele1_charge_intree);
	summaryTree->Branch("ele2_charge",&ele2_charge_intree);
	summaryTree->Branch("ele1_pt",&ele1_pt_intree);
	summaryTree->Branch("ele2_pt",&ele2_pt_intree);
	summaryTree->Branch("ele1_lepMVA",&ele1_lepMVA_intree);
	summaryTree->Branch("ele2_lepMVA",&ele2_lepMVA_intree);
	summaryTree->Branch("ele1_chargeFlip",&ele1_chargeFlip_intree);
	summaryTree->Branch("ele2_chargeFlip",&ele2_chargeFlip_intree);

	summaryTree->Branch("ele1_chreliso",&ele1_chRelIso_intree);
	summaryTree->Branch("ele1_nureliso",&ele1_nuRelIso_intree);
	summaryTree->Branch("ele1_jetdR",&ele1_jetdR_intree);
	summaryTree->Branch("ele1_jetPtRatio",&ele1_jetPtRatio_intree);
	summaryTree->Branch("ele1_bTagCSV",&ele1_bTagCSV_intree);
	summaryTree->Branch("ele1_sip3d",&ele1_sip3d_intree);

	summaryTree->Branch("event",&eventnum_intree);
	summaryTree->Branch("higgs_decay",&higgs_decay_intree);



	
	
	
}

void OSTwoLepAna::initialize_variables()
{
	testTLV_intree.SetPxPyPzE(0.,0.,0.,0.);
	
	
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
	
	num_BJetsLoose_intree = -99;
	num_Jets_intree= -99;

	num_preselectedLeptons_intree = -99;

	num_preselectedMuons_intree = -99;
        mu1_charge_intree = -99;
        mu2_charge_intree = -99;
        mu1_pt_intree = -9.e6;
        mu2_pt_intree = -9.e6;
        mu1_lepMVA_intree = -9.e6;
        mu2_lepMVA_intree = -9.e6;
        mu1_chargeFlip_intree = -99;
	mu2_chargeFlip_intree = -99;

        mu1_chRelIso_intree = -9.e6;
        mu1_nuRelIso_intree = -9.e6;
        mu1_jetdR_intree = -9.e6;
        mu1_jetPtRatio_intree = -9.e6;
        mu1_bTagCSV_intree = -9.e6;
        mu1_sip3d_intree = -9.e6;

	num_preselectedElectrons_intree= -99;
	ele1_charge_intree= -99;
	ele2_charge_intree= -99;
        ele1_pt_intree = -9.e6;
        ele2_pt_intree = -9.e6;
        ele1_lepMVA_intree = -9.e6;
        ele2_lepMVA_intree = -9.e6;
        ele1_chargeFlip_intree= -99;
        ele2_chargeFlip_intree= -99;

	ele1_chRelIso_intree = -9.e6;
	ele1_nuRelIso_intree = -9.e6;
        ele1_jetdR_intree = -9.e6;
        ele1_jetPtRatio_intree = -9.e6;
        ele1_bTagCSV_intree = -9.e6;
        ele1_sip3d_intree = -9.e6;

        higgs_decay_intree = -9e6;
	
}
