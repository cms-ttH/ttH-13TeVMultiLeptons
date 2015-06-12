#include "TSystem.h"
#include "TFile.h"
#include "TFileCollection.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TText.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TKey.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath> 
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "TVector.h"
#include "TLorentzVector.h"
#include "TGraph.h"
// list of available variables:
#include "variables.h"

#include "ttH-13TeVMultiLeptons/TemplateMakers/src/LinkDef.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)

#include "TMVA/Config.h"
// #include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#endif

using namespace std;

typedef std::vector<std::vector<double> > vvdouble;
typedef std::vector<std::vector<std::string> > vvstring;
typedef std::vector<double> vdouble;
typedef std::vector<string> vstring;
typedef std::vector<bool> vbool;
typedef std::vector<int> vint;
typedef std::vector< TLorentzVector > vecTLorentzVector;


class MakeGoodPlot
{
	private:
		
		TChain *ch[20];
		TGraph *roc_curve[50];
		
		TH1F *sample_hist_shared[50][50];
		
		TString sample_names[20];
                string sample_names_std[20];
                double xsecs[20];
                double numgen[20];
		
		int single_sample;
		
		TTree *test_sample;
		TH2F *event_plot;
		
		int sample_raw_evts[10];
		int sample_weighted_evts[10];
		
		std::string cmsinfo;
		TLatex *CMSInfoLatex;
		TPaveText *pt[50];
		TPaveText *pt0;
		TPaveText *pt1;
		
		
		TLine *jet_line[50];
		//std::vector<TLine> *jet_line;
		TLine *lep_line;
		TLine *met_line;
		
		int numJets;
		int numTags;

		double weight;

		double tight_lepton_pt;

		double avg_dr_tagged_jets;
		double sphericity;
		double dr_between_lep_and_closest_jet;
		double avg_btag_disc_btags;
		double dev_from_avg_disc_btags;
		double h2;
		double lowest_btag;
		double avg_untagged_dijet_mass;
		double closest_tagged_dijet_mass;
		double h3;
		double h4;
		double second_highest_btag;
		double third_highest_btag;
		double fourth_highest_btag;

		double avg_btag_disc_non_btags;
		double tagged_dijet_mass_closest_to_125;


		double invariant_mass_of_everything;
		double best_higgs_mass;
		double minChi2;
		double dRbb;

		double bhmv2;
		double maxeta_jet_jet;
		double maxeta_jet_tag;
		double maxeta_tag_tag;
		double dEta_leptop_bb;
		double dEta_hadtop_bb;
		double dPhi_fn;
		double dEta_fn;
		double avg_eta_tops;
		double bb_eta;
		double angle_tops_bb;

		double dRbb_bhmv2;
		//	double bb_eta;
		double b1_eta;
		double b2_eta;
		double b1_pt;
		double b2_pt;

		double median_bb_mass;
		double min_dr_tagged_jets;

		double pt_all_jets_over_E_all_jets;


		double aplanarity;
		double MET;
		double MET_phi;
		double first_jet_pt;
		double second_jet_pt;
		double third_jet_pt;
		double fourth_jet_pt;
		double h0;
		double h1;
		double all_sum_pt_with_met;
		double HT;
		double MHT;
		double MHT_phi;

		double jet_tag_1_pt;
		double jet_tag_2_pt;
		double jet_tag_3_pt;
		double jet_tag_4_pt;


		double avg_tagged_dijet_mass;
		double tight_lepton_phi;
		double M3;
		double M3_1tag;
		double Mlb;
		double first_highest_btag;

		double ttbb_tth_ANN_output;
		
		float ttbb_tth_MVA_output_5j4t; // float!
		float ttbb_tth_MVA_output_6j3t; // float!
		float ttbb_tth_MVA_output_6j4t; // float!
		float var1 ;
		float var2 ;
		float var3 ;
		float var4 ;
		float var5 ;
		float var6 ;
		float var7 ;
		float var8 ;
		float var9 ;
		float var10;
		float var11;
		float var12;
		float var13;
		float var14;
		float var15;
		float var16;
		float var17;
		float var18;
		float var19;
		float var20;
		float var21;
		float var22;
		float var23;
		float var24;
		float var25;
		float var26;
		float var27;
		float var28;
		float var29;
		float var30;
		float var31;
		float var32;
		float var33;
		float var34;
		float var35;
		float var36;
		float var37;
		float var38;
		float var39;
		float var40;
		
		
		int syst;
		

                // tree branches:
		double mcwgt_intree;
		double wgt_intree;
		double wallTimePerEvent_intree;

		int eventnum_intree;
		int higgs_decay_intree;

		int lumiBlock_intree;
		int runNumber_intree;
		
                vector<ttH::Lepton> *preselected_leptons_intree;
		vector<ttH::Lepton> *loose_leptons_intree;
		vector<ttH::Lepton> *cutBased_leptons_intree;
		vector<ttH::Lepton> *looseMvaBased_leptons_intree;
		vector<ttH::Lepton> *tightMvaBased_leptons_intree;
 
		vector<ttH::Electron> *raw_electrons_intree;               
		vector<ttH::Electron> *preselected_electrons_intree;
		vector<ttH::Electron> *loose_electrons_intree;
		vector<ttH::Electron> *cutBased_electrons_intree;
		vector<ttH::Electron> *looseMvaBased_electrons_intree;
		vector<ttH::Electron> *tightMvaBased_electrons_intree;

		vector<ttH::Muon> *raw_muons_intree;
                vector<ttH::Muon> *preselected_muons_intree;
                vector<ttH::Muon> *loose_muons_intree;
                vector<ttH::Muon> *cutBased_muons_intree;
                vector<ttH::Muon> *looseMvaBased_muons_intree;
                vector<ttH::Muon> *tightMvaBased_muons_intree;

                vector<ttH::Jet> *preselected_jets_intree;
		vector<ttH::Jet> *loose_bJets_intree;
		vector<ttH::Jet> *tight_bJets_intree;
		
		vector<ttH::MET> *met_intree;
		
		vector<ttH::GenParticle> *pruned_genParticles_intree;
                
                
                
                
                
                //////////////////////////////////////////
                
		void initialize();
		void load_samples(std::vector<int> samps);
		void get_hist_of_tiered_MVA_response_for_one_sample_5j4t(TH1 *plot, int sample_number=1);
		void get_hist_of_tiered_MVA_response_for_one_sample_6j4t(TH1 *plot, int sample_number=1);
		void get_hist_MVA_response_for_one_sample_643203(TH1 *plot, int sample_number=1);
		void get_hist_of_tiered_MVA_response_for_one_sample_as_function_of_category(TH1 *plot, int sample_number=1, TString cat_num="000");
		void get_hist_of_tiered_MVA_response_for_one_sample_643900XX(int sample_number=1, int samp_it=0);
		//double get_gaus_shift(TString cat_num="000", int sample_number=1);
		double get_gaus_shift(int cat_num=0, int sample_number=1);
		void get_roc_curve(TH1F *sig, TH1F *bkgd, int roc_curve_index); //int &npts, double (&effS)[500], double (&bckR)[500]);
		void get_hist_of_simple_variable(TH1 *plot, int sample_number=1, TH1 *plot2 = 0, TH1 *plot3 = 0);

		void get_even_simpler_plot_my_trees(TH1 *plot, int sample_number=1);		

		
		//void get_lep_TLV(vdouble lep, TLorentzVector &lep_tlv);
		void convert_jets_to_TLVs(vvdouble jets, vecTLorentzVector &vect_of_jet_TLVs);
		void vect_of_tagged_TLVs(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_btag_TLVs);
		void vect_of_untagged_TLVs(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_nontagged_TLVs);
		void get_bs_from_reverse_engineered_bhm(vvdouble jets, vdouble jetCSV, double best_higgs_mass, TLorentzVector &bjet1, TLorentzVector &bjet2); // <-- tempory workaround .. should be depreciated now

		// algos:
		double w_mass_top(vvdouble jets, vdouble jetCSV);
		double had_top_mass(vvdouble jets, vdouble jetCSV);

		double ww_mass_nontop(vvdouble jets, vdouble jetCSV);
		void nontop_untags(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_nontagged_TLVs_not_top);
		double avg_pt_nontop_untags(vvdouble jets, vdouble jetCSV);

		double pt_E_ratio_jets(vvdouble jets);

		//void two_tagged_TLVs_from_bhm(TLorentzVector &firstb,TLorentzVector &secondb,int syst=0);
		double getBestHiggsMass(TLorentzVector lepton, TLorentzVector met, vecTLorentzVector jets, vdouble btag, double &minChi, double &dRbb, TLorentzVector &bjet1, TLorentzVector &bjet2);
		double getBestHiggsMass2(TLorentzVector lepton, TLorentzVector &met, vecTLorentzVector jets, vdouble btag, double &minChi, double &dRbb, TLorentzVector &bjet1, TLorentzVector &bjet2, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, TLorentzVector &toplep, TLorentzVector &tophad);
		double get_bhm_from_own_algo(double MET, double METphi, TLorentzVector &metv, vdouble lep, vvdouble jets, vdouble csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb);
		double study_tops_bb_syst (double MET, double METphi, TLorentzVector &metv, vdouble lep, vvdouble jets, vdouble csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb, double &testquant1, double &testquant2, double &testquant3, double &testquant4, double &testquant5, double &testquant6, double &testquant7, TLorentzVector &b1, TLorentzVector &b2);

		double get_jet_jet_etamax (vvdouble jets);
		double get_jet_tag_etamax (vvdouble jets, vdouble jetCSV);
		double get_tag_tag_etamax (vvdouble jets, vdouble jetCSV);
		double get_median_bb_mass (vvdouble jets, vdouble jetCSV);
		
		double get_avg_abs_deta_jets (vvdouble jets);
		
		TString int2ss(int theint);
		std::string TString2string(TString the_abomination);
                
                

	public:	
	        void compareplots(std::vector<int> samps, std::vector<TString> tempfiles);
		void draw_simple_curves_normalized(std::vector<int> samps);
		void make_simple_plot_mytrees(TString theshift="",int drawaxes=0);
		void draw_nice_stack_with_ratio(std::vector<int> samps, std::string mytitle="", std::string mylabel="");		
		void draw_nice_stack(std::vector<int> samps);
		void draw_ROC_curves(std::vector<int> samps, int which_one_is_the_signal_sample);
		void visualize_yggdrasil(int sample_number=1);
		void visualize_yggdrasil_Setup(TString tchain_cut);
		void visualize_yggdrasil_Update(); //int sample_number, int num_entries, TH2 *plot2);
		void print_geninfo_table(std::vector<int> samps);
		void make_eff_vs_var_separation_plot(std::vector<int> samps);
		void draw_corr_rand_gauss_2D(std::vector<int> samps, bool use_samps=false);
		void print_yields_given_syst(std::vector<int> samps);
                void print_cutflow(std::vector<int> samps);
                //void draw_ROC_iso(std::vector<int> samps);
		void draw_several_comparisons(std::vector<int> samps);
                
		MakeGoodPlot();
		MakeGoodPlot(std::vector<int> samps);
		~MakeGoodPlot();

};

//_______________________________________________________________

MakeGoodPlot::MakeGoodPlot() // default
{	
	syst = 0;
	initialize();
}
MakeGoodPlot::MakeGoodPlot(std::vector<int> samps) // alternative (interactive use, etc...)
{
	
	syst = 0;
	initialize();
	load_samples(samps);
	if (samps.size()==1) single_sample = samps[0];
	
}
MakeGoodPlot::~MakeGoodPlot() {}

//_______________________________________________________________



void MakeGoodPlot::print_yields_given_syst(std::vector<int> samps)
{

// from yggdrasil treemaker:

/*

	eve->wgt_[iSys] = wgt_lumi;

	// no systematic up/down for lepton SF for now
	if( iSys==1 )      eve->wgt_[iSys] *= leptonSF;
	else if( iSys==2 ) eve->wgt_[iSys] *= leptonSF;
	else               eve->wgt_[iSys] *= leptonSF;


	// PU weight up/down
	if( iSys==3 )      eve->wgt_[iSys] *= wgtPUup;
	else if( iSys==4 ) eve->wgt_[iSys] *= wgtPUdown;
	else               eve->wgt_[iSys] *= wgtPU;

	if( iSys==0 ) totalWgt *= leptonSF*wgtPU;

	sysType::sysType iSysType = sysType::NA;
	switch( iSys ){
	case 5 : iSysType = sysType::hfSFup;   break;
	case 6 : iSysType = sysType::hfSFdown; break;
	case 7 : iSysType = sysType::lfSFup;   break;
	case 8 : iSysType = sysType::lfSFdown; break;
	case 9 : iSysType = sysType::JERup;    break;
	case 10: iSysType = sysType::JERdown;  break;
	case 11: iSysType = sysType::JESup;    break;
	case 12: iSysType = sysType::JESdown;  break;

		// Add Q2scale systematic
	if( iSys==13 )      eve->wgt_[iSys] *= eve->Q2ScaleUpWgt_;
	else if( iSys==14 ) eve->wgt_[iSys] *= eve->Q2ScaleDownWgt_;


	// top pT reweight
	if( iSys==15 )      eve->wgt_[iSys] *= wgt_topPtSFUp;
	else if( iSys==16 ) eve->wgt_[iSys] *= wgt_topPtSFDown;
	else                eve->wgt_[iSys] *= wgt_topPtSF;

	case 17: iSysType = sysType::CSVLFup;         break;
	case 18: iSysType = sysType::CSVLFdown;       break;
	case 19: iSysType = sysType::CSVHFup;         break;
	case 20: iSysType = sysType::CSVHFdown;       break;
	case 21: iSysType = sysType::CSVHFStats1up;   break;
	case 22: iSysType = sysType::CSVHFStats1down; break;
	case 23: iSysType = sysType::CSVLFStats1up;   break;
	case 24: iSysType = sysType::CSVLFStats1down; break;
	case 25: iSysType = sysType::CSVHFStats2up;   break;
	case 26: iSysType = sysType::CSVHFStats2down; break;
	case 27: iSysType = sysType::CSVLFStats2up;   break;
	case 28: iSysType = sysType::CSVLFStats2down; break;
	case 29: iSysType = sysType::CSVCErr1up;   break;
	case 30: iSysType = sysType::CSVCErr1down; break;
	case 31: iSysType = sysType::CSVCErr2up;   break;
	case 32: iSysType = sysType::CSVCErr2down; break;
	default: iSysType = sysType::NA;       break;
	}

	if( iSys==0 ) totalWgt *= wgt_topPtSF;

	// Get Btag Weight
	int useBtagSys = 0;
	if( iSys==5 )      useBtagSys = 1;
	else if( iSys==6 ) useBtagSys = -1;
	else if( iSys==7 ) useBtagSys = 2;
	else if( iSys==8 ) useBtagSys = -2;
	
*/	
	
	int numsamples = samps.size();
	load_samples(samps);
	
	
	vector<int> upsysts;
	vector<int> dnsysts;
	vector<std::string> systname;
	
	
	// from above:
	///////////////////////////////////
		
	
	upsysts.push_back(1);
	dnsysts.push_back(2);
	systname.push_back("leptonSF");
	
	upsysts.push_back(3);
	dnsysts.push_back(4);
	systname.push_back("PU");
	
	upsysts.push_back(5);
	dnsysts.push_back(6);
	systname.push_back("hfSF");
	
	upsysts.push_back(7);
	dnsysts.push_back(8);
	systname.push_back("lfSF");
	
	upsysts.push_back(9);
	dnsysts.push_back(10);
	systname.push_back("JER");
	
	upsysts.push_back(11);	// JES up
	dnsysts.push_back(12);	// JES down
	systname.push_back("JES");
	
	upsysts.push_back(13);	// Q2scale up 
	dnsysts.push_back(14);	// Q2scale down 
	systname.push_back("Q2");
	
	upsysts.push_back(15);
	dnsysts.push_back(16);
	systname.push_back("topPtSF");
	
	
	upsysts.push_back(17);
	dnsysts.push_back(18);
	systname.push_back("CSVLF");
	
	
	upsysts.push_back(19);
	dnsysts.push_back(20);
	systname.push_back("CSVHF");
			
	
	upsysts.push_back(21);	// CSVHFStats1  up
	dnsysts.push_back(22);	// CSVHFStats1  down
	systname.push_back("CSVHFStats1");
	
		
	upsysts.push_back(23);	// CSVLFStats1 up
	dnsysts.push_back(24);	// CSVLFStats1 dn
	systname.push_back("CSVLFStats1");
	
	
	upsysts.push_back(25);
	dnsysts.push_back(26);
	systname.push_back("CSVHFStats2");
	
	
	upsysts.push_back(27);
	dnsysts.push_back(28);
	systname.push_back("CSVLFStats2");
	
	
	upsysts.push_back(29);
	dnsysts.push_back(30);
	systname.push_back("CSVCErr1");
		
	
	upsysts.push_back(31);
	dnsysts.push_back(32);
	systname.push_back("CSVCErr2");

			
	///////////////////////////////////
		
	int numupsysts = upsysts.size();
	int numdnsysts = dnsysts.size();
	
	if (numupsysts!=numdnsysts) { cout << "need same number of up and down systs" << endl; return; }
	
	double a62_nom[numsamples];
	double a43_nom[numsamples];
	double a53_nom[numsamples];
	double a63_nom[numsamples];
	double a44_nom[numsamples];
	double a54_nom[numsamples];
	double a64_nom[numsamples];
	
	double a62_up[numsamples][numupsysts];
	double a43_up[numsamples][numupsysts];
	double a53_up[numsamples][numupsysts];
	double a63_up[numsamples][numupsysts];
	double a44_up[numsamples][numupsysts];
	double a54_up[numsamples][numupsysts];
	double a64_up[numsamples][numupsysts];
	
	double a62_dn[numsamples][numdnsysts];
	double a43_dn[numsamples][numdnsysts];
	double a53_dn[numsamples][numdnsysts];
	double a63_dn[numsamples][numdnsysts];
	double a44_dn[numsamples][numdnsysts];
	double a54_dn[numsamples][numdnsysts];
	double a64_dn[numsamples][numdnsysts];
	
	
	for (int set0samps=0; set0samps<numsamples; set0samps++)
	{
		a62_nom[set0samps] = 0.;
		a43_nom[set0samps] = 0.;
		a53_nom[set0samps] = 0.;
		a63_nom[set0samps] = 0.;
		a44_nom[set0samps] = 0.;
		a54_nom[set0samps] = 0.;
		a64_nom[set0samps] = 0.;
		
		for (int set0systs=0; set0systs<numupsysts; set0systs++)
		{
		
			a62_up[set0samps][set0systs] = 0.;
			a43_up[set0samps][set0systs] = 0.;
			a53_up[set0samps][set0systs] = 0.;
			a63_up[set0samps][set0systs] = 0.;
			a44_up[set0samps][set0systs] = 0.;
			a54_up[set0samps][set0systs] = 0.;
			a64_up[set0samps][set0systs] = 0.;

			a62_dn[set0samps][set0systs] = 0.;
			a43_dn[set0samps][set0systs] = 0.;
			a53_dn[set0samps][set0systs] = 0.;
			a63_dn[set0samps][set0systs] = 0.;
			a44_dn[set0samps][set0systs] = 0.;
			a54_dn[set0samps][set0systs] = 0.;
			a64_dn[set0samps][set0systs] = 0.;
		}
	}
	
	
	
	
	
	for (int whichsamp=0; whichsamp<numsamples; whichsamp++)
	{
		
		int sample_number = samps[whichsamp];
		cout << sample_names[sample_number] << endl;
		
		//ch[sample_number]->SetBranchAddress( "eve.", &eve1 );

		//cout << sample_number << endl;
		//cout << ch[sample_number]->GetEntries() << endl;

		int samp_num_entries = ch[sample_number]->GetEntries();

		int rawcount = 0;
		double weightcount = 0.;

		for (Int_t i=0;i<samp_num_entries;i++)
		{
			ch[sample_number]->GetEntry(i);

// 			//bool is_sel_cat = (eve1->numJets_float_[syst]>=4)&&(eve1->numTags_float_[syst]>=2);
// 			//if (!is_sel_cat) continue;
// 
// 			// single ele data
// 			if (sample_number==10)
// 			{
// 				if (!eve1->leptonType_==0) continue;
// 				if (!(eve1->passElectronTrigger_ && eve1->matchSingleElectronTrigger_)) continue;
// 			}
// 
// 			// single mu data
// 			if (sample_number==0)
// 			{
// 				if (!eve1->leptonType_==1) continue;
// 				if (!(eve1->passMuonTrigger_ && eve1->matchSingleMuTrigger_)) continue;
// 			}
// 
// 
// 			// mc
// 			if (sample_number!=0&&sample_number!=10)
// 			{
// 				if (eve1->leptonType_==0) if (!(eve1->passElectronTrigger_ && eve1->matchSingleElectronTrigger_)) continue;
// 				if (eve1->leptonType_==1) if (!(eve1->passMuonTrigger_ && eve1->matchSingleMuTrigger_)) continue;
// 			}
// 
// 			if (sample_number==7&&eve1->evt_==90273686) continue;
// 			
// 			if ((eve1->numJets_float_[0]>=4)&&(eve1->numTags_float_[0]>=2))
// 			{
// 			
// 				rawcount++;
// 				weightcount += eve1->wgt_[0];
// 			}
// 
// 			for (int theupsyst=0; theupsyst<numupsysts; theupsyst++)
// 			{
// 				if (eve1->third_jet_pt_[upsysts[theupsyst]]<40.) continue;
// 				if (eve1->IsTauTauLeptonEvent_[upsysts[theupsyst]]==1) continue;
// 
// 				weight = eve1->wgt_[upsysts[theupsyst]];
// 
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]>=6)&&(eve1->numTags_float_[upsysts[theupsyst]]==2)) a62_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]==4)&&(eve1->numTags_float_[upsysts[theupsyst]]==3)) a43_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]==5)&&(eve1->numTags_float_[upsysts[theupsyst]]==3)) a53_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]>=6)&&(eve1->numTags_float_[upsysts[theupsyst]]==3)) a63_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]==4)&&(eve1->numTags_float_[upsysts[theupsyst]]==4)) a44_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]==5)&&(eve1->numTags_float_[upsysts[theupsyst]]>=4)) a54_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]>=6)&&(eve1->numTags_float_[upsysts[theupsyst]]>=4)) a64_up[whichsamp][theupsyst] += weight;
// 
// 			}
// 
// 
// 			for (int thednsyst=0; thednsyst<numdnsysts; thednsyst++)
// 			{
// 				if (eve1->third_jet_pt_[dnsysts[thednsyst]]<40.) continue;
// 				if (eve1->IsTauTauLeptonEvent_[dnsysts[thednsyst]]==1) continue;
// 
// 				weight = eve1->wgt_[dnsysts[thednsyst]];
// 
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]>=6)&&(eve1->numTags_float_[dnsysts[thednsyst]]==2)) a62_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]==4)&&(eve1->numTags_float_[dnsysts[thednsyst]]==3)) a43_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]==5)&&(eve1->numTags_float_[dnsysts[thednsyst]]==3)) a53_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]>=6)&&(eve1->numTags_float_[dnsysts[thednsyst]]==3)) a63_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]==4)&&(eve1->numTags_float_[dnsysts[thednsyst]]==4)) a44_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]==5)&&(eve1->numTags_float_[dnsysts[thednsyst]]>=4)) a54_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]>=6)&&(eve1->numTags_float_[dnsysts[thednsyst]]>=4)) a64_dn[whichsamp][thednsyst] += weight;
// 
// 			}
// 
// 			if ((eve1->third_jet_pt_[0]<40.)&&(eve1->IsTauTauLeptonEvent_[0]==1));
// 			{
// 
// 				weight = eve1->wgt_[0];
// 
// 				if ((eve1->numJets_float_[0]>=6)&&(eve1->numTags_float_[0]==2)) a62_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]==4)&&(eve1->numTags_float_[0]==3)) a43_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]==5)&&(eve1->numTags_float_[0]==3)) a53_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]>=6)&&(eve1->numTags_float_[0]==3)) a63_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]==4)&&(eve1->numTags_float_[0]==4)) a44_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]==5)&&(eve1->numTags_float_[0]>=4)) a54_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]>=6)&&(eve1->numTags_float_[0]>=4)) a64_nom[whichsamp] += weight;
// 
// 			}
// 
 		}
 		
		cout << " " << endl;
		cout << "raw " << rawcount << endl;
		cout << "weight " << weightcount << endl;
		
		
	}
		
		
	cout << "    "  << endl;
	cout << "    "  << endl;
	cout << "    "  << endl;
	cout << "    "  << endl;
	cout << "    "  << endl;

	double lumiscale = 19.3/19.5;

	for (int syst_print=0; syst_print<numupsysts; syst_print++)
	{
		cout << systname[syst_print] << endl;
		cout << "    "  << endl;
		cout << " syst up: " << upsysts[syst_print] << endl; // " syst down: " << dnsysts[syst_print] << endl;
		cout << "    "  << endl;
		//cout << "sample  " << "6jet 2tag   " << "4jet 3tag   " << "5jet 3tag   " <<  "6jet 3tag   " << "4jet 4tag   " << "5jet 4tag   " << "6jet 4tag   " << endl;
		
		printf ("%20s %20s %20s %20s %20s %20s %20s %20s \n", "sample", "6jet 2tag", "4jet 3tag", "5jet 3tag", "6jet 3tag", "4jet 4tag", "5jet 4tag", "6jet 4tag");
		
		for (int whichsamp=0; whichsamp<numsamples; whichsamp++)		
		{
			
			int sample_number = samps[whichsamp];
			//string holding_cs_hand = (char*)sample_names[sample_number];
			string holding_roots_hand = TString2string(sample_names[sample_number]);
			
			
			double up_62_pct = 100.*(a62_up[whichsamp][syst_print]- a62_nom[whichsamp]) / a62_nom[whichsamp];
			double up_43_pct = 100.*(a43_up[whichsamp][syst_print]- a43_nom[whichsamp]) / a43_nom[whichsamp];
			double up_53_pct = 100.*(a53_up[whichsamp][syst_print]- a53_nom[whichsamp]) / a53_nom[whichsamp];
			double up_63_pct = 100.*(a63_up[whichsamp][syst_print]- a63_nom[whichsamp]) / a63_nom[whichsamp];
			double up_44_pct = 100.*(a44_up[whichsamp][syst_print]- a44_nom[whichsamp]) / a44_nom[whichsamp];
			double up_54_pct = 100.*(a54_up[whichsamp][syst_print]- a54_nom[whichsamp]) / a54_nom[whichsamp];
			double up_64_pct = 100.*(a64_up[whichsamp][syst_print]- a64_nom[whichsamp]) / a64_nom[whichsamp]; 	  
			
			/*
			double up_62_pct = lumiscale*a62_nom[whichsamp];
			double up_43_pct = lumiscale*a43_nom[whichsamp];
			double up_53_pct = lumiscale*a53_nom[whichsamp];
			double up_63_pct = lumiscale*a63_nom[whichsamp];
			double up_44_pct = lumiscale*a44_nom[whichsamp];
			double up_54_pct = lumiscale*a54_nom[whichsamp];
			double up_64_pct = lumiscale*a64_nom[whichsamp];  	 
			*/	
			
			double dn_62_pct = 100.*(a62_dn[whichsamp][syst_print]- a62_nom[whichsamp]) / a62_nom[whichsamp];
			double dn_43_pct = 100.*(a43_dn[whichsamp][syst_print]- a43_nom[whichsamp]) / a43_nom[whichsamp];
			double dn_53_pct = 100.*(a53_dn[whichsamp][syst_print]- a53_nom[whichsamp]) / a53_nom[whichsamp];
			double dn_63_pct = 100.*(a63_dn[whichsamp][syst_print]- a63_nom[whichsamp]) / a63_nom[whichsamp];
			double dn_44_pct = 100.*(a44_dn[whichsamp][syst_print]- a44_nom[whichsamp]) / a44_nom[whichsamp];
			double dn_54_pct = 100.*(a54_dn[whichsamp][syst_print]- a54_nom[whichsamp]) / a54_nom[whichsamp];
			double dn_64_pct = 100.*(a64_dn[whichsamp][syst_print]- a64_nom[whichsamp]) / a64_nom[whichsamp]; 
			
					
			//cout << fixed << endl;
			//cout << setprecision(1) << sample_names[sample_number] << "    " << up_62_pct << "    "  << up_43_pct << "    "  << up_53_pct << "    "  << up_63_pct << "    "  << up_44_pct << "    "  << up_54_pct << "    "  << up_64_pct << endl; 
			
			//printf ("%20s %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f \n", holding_roots_hand.c_str(), up_62_pct, up_43_pct, up_53_pct, up_63_pct, up_44_pct, up_54_pct, up_64_pct);
		
			printf("%20s %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f \n", holding_roots_hand.c_str(), max(fabs(up_62_pct),fabs(dn_62_pct)), max(fabs(up_43_pct),fabs(dn_43_pct)), max(fabs(up_53_pct),fabs(dn_53_pct)), max(fabs(up_63_pct),fabs(dn_63_pct)), max(fabs(up_44_pct),fabs(dn_44_pct)), max(fabs(up_54_pct),fabs(dn_54_pct)), max(fabs(up_64_pct),fabs(dn_64_pct)));
		
		}
		
		/*
		
		cout << "  " << endl;
		cout << "  " << endl;
		cout << " syst down: " << dnsysts[syst_print] << endl;
		cout << "    "  << endl;
		//cout << "sample  " << "6jet 2tag   " << "4jet 3tag   " << "5jet 3tag   " <<  "6jet 3tag   " << "4jet 4tag   " << "5jet 4tag   " << "6jet 4tag   " << endl;
		
		printf ("%20s %20s %20s %20s %20s %20s %20s %20s \n", "sample", "6jet 2tag", "4jet 3tag", "5jet 3tag", "6jet 3tag", "4jet 4tag", "5jet 4tag", "6jet 4tag");
		

		for (int whichsamp=0; whichsamp<numsamples; whichsamp++)		
		{
			
			int sample_number = samps[whichsamp];
			//string holding_cs_hand = (char*)sample_names[sample_number];
			string holding_roots_hand = TString2string(sample_names[sample_number]);
						
			double dn_62_pct = 1.*(a62_dn[whichsamp][syst_print]- a62_nom[whichsamp]) / a62_nom[whichsamp];
			double dn_43_pct = 1.*(a43_dn[whichsamp][syst_print]- a43_nom[whichsamp]) / a43_nom[whichsamp];
			double dn_53_pct = 1.*(a53_dn[whichsamp][syst_print]- a53_nom[whichsamp]) / a53_nom[whichsamp];
			double dn_63_pct = 1.*(a63_dn[whichsamp][syst_print]- a63_nom[whichsamp]) / a63_nom[whichsamp];
			double dn_44_pct = 1.*(a44_dn[whichsamp][syst_print]- a44_nom[whichsamp]) / a44_nom[whichsamp];
			double dn_54_pct = 1.*(a54_dn[whichsamp][syst_print]- a54_nom[whichsamp]) / a54_nom[whichsamp];
			double dn_64_pct = 1.*(a64_dn[whichsamp][syst_print]- a64_nom[whichsamp]) / a64_nom[whichsamp]; 	
			
			//cout << fixed << endl;
			//cout << setprecision(1) << sample_names[sample_number] << "    " << dn_62_pct << "    "  << dn_43_pct << "    "  << dn_53_pct << "    "  << dn_63_pct << "    "  << dn_44_pct << "    "  << dn_54_pct << "    "  << dn_64_pct << endl; 
			printf ("%20s %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f \n", holding_roots_hand.c_str(), dn_62_pct, dn_43_pct, dn_53_pct, dn_63_pct, dn_44_pct, dn_54_pct, dn_64_pct);
		
		}		
		
		*/
		
		cout << "    "  << endl;
		cout << "    "  << endl;
		cout << "    "  << endl;
		cout << "    "  << endl;
		cout << " Next syst ..."  << endl;
		cout << "    "  << endl;
		cout << "    "  << endl;
	}


}

// void MakeGoodPlot::draw_ROC_iso(std::vector<int> samps)
// {
//   int numsamples = samps.size();
//   //  load_samples(samps);
//   
//   ch[1]->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/multileptree.root");
// 
//   int NbinsX = 1600;
//   int Xmin = 0;
//   int Xmax = 13;
// 
//   TH1F *promptEle_relIso_hist = new TH1F("promptEle_relIso","",NbinsX,Xmin,Xmax);
//   TH1F *nonPromptEle_relIso_hist = new TH1F("nonPromptEle_relIso","",NbinsX,Xmin,Xmax);
//   TH1F *promptEle_miniIso_hist = new TH1F("promptEle_miniIso","",NbinsX,Xmin,Xmax);
//   TH1F *nonPromptEle_miniIso_hist = new TH1F("nonPromptEle_miniIso","",NbinsX,Xmin,Xmax);
//   
//   TH1F *promptMu_relIso_hist = new TH1F("promptMu_relIso","",NbinsX,Xmin,Xmax);
//   TH1F *nonPromptMu_relIso_hist = new TH1F("nonPromptMu_relIso","",NbinsX,Xmin,Xmax);
//   TH1F *promptMu_miniIso_hist = new TH1F("promptMu_miniIso","",NbinsX,Xmin,Xmax);
//   TH1F *nonPromptMu_miniIso_hist = new TH1F("nonPromptMu_miniIso","",NbinsX,Xmin,Xmax);
//   
//   for (int i=0; i<numsamples; i++)
//     {  
//       int samp_int = samps[i];
//       ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
//       ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
//       ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);
// 
//       int samp_num_entries = ch[samp_int]->GetEntries();
//       
//       for (Int_t j=0; j<samp_num_entries; j++)
// 	{
// 	  ch[samp_int]->GetEntry(j);
// 	  
// 	  for (const auto & lepton : *preselected_leptons_intree)
// 	    {
// 	      if (lepton.genMotherPdgID != 9999)
// 		{
// 		  if (abs(lepton.genMotherPdgID) == 24 || abs(lepton.genMotherPdgID) == 23)
// 		    {
// 		      if (abs(lepton.pdgID) == 11)
// 			{ 
// 			  promptEle_relIso_hist->Fill(lepton.relIso);
// 			  promptEle_miniIso_hist->Fill(lepton.miniIso);
// 			  // promptEle_relIso_hist->Fill(log(lepton.relIso));
// 			  // promptEle_miniIso_hist->Fill(log(lepton.miniIso));
// 			}
// 		      else 
// 			{
// 			  promptMu_relIso_hist->Fill(lepton.relIso);
// 			  promptMu_miniIso_hist->Fill(lepton.miniIso);
// 			  // // promptMu_relIso_hist->Fill(log(lepton.relIso));
// 			  // promptMu_miniIso_hist->Fill(log(lepton.miniIso));
// 			}
// 		    }
// 		  else
// 		    {
// 		      if (abs(lepton.pdgID) == 11)
// 			{
// 			  nonPromptEle_relIso_hist->Fill(lepton.relIso);
// 			  nonPromptEle_miniIso_hist->Fill(lepton.miniIso);
// 			  //nonPromptEle_relIso_hist->Fill(log(lepton.relIso));
// 			  //nonPromptEle_miniIso_hist->Fill(log(lepton.miniIso));
// 			}
// 		      else
// 			{
// 			  nonPromptMu_relIso_hist->Fill(lepton.relIso);
// 			  nonPromptMu_miniIso_hist->Fill(lepton.miniIso);
// 			  //nonPromptMu_relIso_hist->Fill(log(lepton.relIso));
// 			  //nonPromptMu_miniIso_hist->Fill(log(lepton.miniIso));
// 			}
// 		    }
// 		}
// 	    }
// 	}
//       //time to draw ROC curves...
//     }
//   
//   //  TLegend* leg = new TLegend(0.11,0.91,0.89,0.99);
//   TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);
//   leg->SetFillColor(kWhite);
//   //leg->SetLineColor(kWhite);
//   leg->SetShadowColor(kWhite);
//   leg->SetTextFont(42);
//   leg->SetTextSize(0.035);
//   //  leg->SetNColumns(5);
// 
//   // TLegend* legg = new TLegend(0.11,0.91,0.89,0.99);
//   // legg->SetFillColor(kWhite);
//   // legg->SetLineColor(kWhite);
//   // legg->SetShadowColor(kWhite);
//   // legg->SetTextFont(42);
//   // legg->SetTextSize(0.035);
//   // legg->SetNColumns(5);
//   // TCanvas *can0 = new TCanvas("can0","canvas0",150,10,990,660);
//   // nonPromptEle_relIso_hist->SetLineColor(1);
//   // promptEle_relIso_hist->SetLineColor(2);
//   // legg->AddEntry(promptEle_relIso_hist,"prompt electrons");
//   // legg->AddEntry(nonPromptEle_relIso_hist,"non-prompt electrons");
//   // nonPromptEle_relIso_hist->Draw();
//   // promptEle_relIso_hist->Draw("SAME");
//   // legg->SetFillColor(0);
//   // legg->Draw();
// 
//   TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660);
//   can1->SetGridx();
//   can1->SetGridy();
// 
//   get_roc_curve(promptEle_relIso_hist,nonPromptEle_relIso_hist,0);
//   get_roc_curve(promptEle_miniIso_hist,nonPromptEle_miniIso_hist,1);
//   get_roc_curve(promptMu_relIso_hist,nonPromptMu_relIso_hist,2);
//   get_roc_curve(promptMu_miniIso_hist,nonPromptMu_miniIso_hist,3);
// 
//   // get_roc_curve(nonPromptEle_relIso_hist,promptEle_relIso_hist,0);
//   // get_roc_curve(nonPromptEle_miniIso_hist,promptEle_miniIso_hist,1);
//   // get_roc_curve(nonPromptMu_relIso_hist,promptMu_relIso_hist,2);
//   // get_roc_curve(nonPromptMu_miniIso_hist,promptMu_miniIso_hist,3);
// 
//   roc_curve[0]->GetXaxis()->SetTitle("prompt Lepton efficiency");
//   roc_curve[0]->GetXaxis()->SetTitleColor(kBlack);
//   roc_curve[0]->GetYaxis()->SetTitle("non-prompt bkg rejection");
//   roc_curve[0]->GetYaxis()->SetTitleColor(kBlack);
// 
//   roc_curve[1]->GetXaxis()->SetTitle("prompt Lepton efficiency");
//   roc_curve[1]->GetXaxis()->SetTitleColor(kBlack);
//   roc_curve[1]->GetYaxis()->SetTitle("non-prompt bkg rejection");
//   roc_curve[1]->GetYaxis()->SetTitleColor(kBlack);
// 
//   roc_curve[2]->GetXaxis()->SetTitle("prompt Lepton efficiency");
//   roc_curve[2]->GetXaxis()->SetTitleColor(kBlack);
//   roc_curve[2]->GetYaxis()->SetTitle("non-prompt bkg rejection");
//   roc_curve[2]->GetYaxis()->SetTitleColor(kBlack);
// 
//   roc_curve[3]->GetXaxis()->SetTitle("prompt Lepton efficiency");
//   roc_curve[3]->GetXaxis()->SetTitleColor(kBlack);
//   roc_curve[3]->GetYaxis()->SetTitle("non-prompt bkg rejection");
//   roc_curve[3]->GetYaxis()->SetTitleColor(kBlack);
//   
//   roc_curve[0]->SetLineColor(1);
//   roc_curve[1]->SetLineColor(2);
//   roc_curve[2]->SetLineColor(3);
//   roc_curve[3]->SetLineColor(4);
// 
//   roc_curve[0]->SetTitle("");
//   roc_curve[1]->SetTitle("");
//   roc_curve[2]->SetTitle("");
//   roc_curve[3]->SetTitle("");
// 
//   roc_curve[0]->SetLineWidth(2);
//   roc_curve[1]->SetLineWidth(2);
//   roc_curve[2]->SetLineWidth(2);
//   roc_curve[3]->SetLineWidth(2);
// 
//   leg->AddEntry(roc_curve[0],"ele relIso","l");
//   leg->AddEntry(roc_curve[1],"ele miniIso","l");
//   leg->AddEntry(roc_curve[2],"mu relIso","l");
//   leg->AddEntry(roc_curve[3],"mu miniIso","l");
// 
//   roc_curve[0]->Draw("AL");
//   roc_curve[1]->Draw("L");
//   roc_curve[2]->Draw("L");
//   roc_curve[3]->Draw("L");
//   
//   leg->SetFillColor(0);
//   leg->Draw();
// 
// 
// }

void MakeGoodPlot::print_cutflow(std::vector<int> samps)
{
    int numsamples = samps.size();

    load_samples(samps);

    vstring commoncuts_str;
    vstring ss_2e_cuts_str;
    vstring ss_2mu_cuts_str;
    vstring ss_emu_cuts_str;
    vstring threel_cuts_str;
    vstring fourl_cuts_str;
    
    // common cuts
    commoncuts_str.push_back(">=2 T lep or >=4 PS lep");
    commoncuts_str.push_back("minDilepMass>12");
    commoncuts_str.push_back("PS lep pt >20, >10");
    commoncuts_str.push_back("nJets>=2 (25GeV)");
    commoncuts_str.push_back(">=2 L bjets or >=1 M bjet");
    
    // ss
    ss_2e_cuts_str.push_back("2 tight eles");
    ss_2e_cuts_str.push_back("ss");
    ss_2e_cuts_str.push_back(">=4 jets");
    ss_2e_cuts_str.push_back("metLD>0.2");
    ss_2e_cuts_str.push_back("lep pt >20, >20");
    ss_2e_cuts_str.push_back("leppt1+leppt2+met>100");
    ss_2e_cuts_str.push_back("ee_Zveto");
    ss_2e_cuts_str.push_back("isGsfCtfScPixChargeConsistent (x2)");
        
    ss_emu_cuts_str.push_back("1 tight ele, 1 tight mu");
    ss_emu_cuts_str.push_back("ss");
    ss_emu_cuts_str.push_back(">=4 jets");
    ss_emu_cuts_str.push_back("metLD>0.2");
    ss_emu_cuts_str.push_back("lep pt >20, >20");
    ss_emu_cuts_str.push_back("leppt1+leppt2+met>100");
    ss_emu_cuts_str.push_back("chargeFlip+isGsfCtfScPixChargeConsistent");
        
    ss_2mu_cuts_str.push_back("2 tight mu");
    ss_2mu_cuts_str.push_back("ss");
    ss_2mu_cuts_str.push_back(">=4 jets");
    ss_2mu_cuts_str.push_back("metLD>0.2");
    ss_2mu_cuts_str.push_back("lep pt >20, >20");
    ss_2mu_cuts_str.push_back("leppt1+leppt2+met>100");
    ss_2mu_cuts_str.push_back("chargeFlip (x2)");
    
    // 3l
    threel_cuts_str.push_back("3 tight lep");
    threel_cuts_str.push_back(">=4 jets, or metLD>0.2");
    threel_cuts_str.push_back("SFOS Zveto");
    threel_cuts_str.push_back("2 T leps ss");
    
    // 4l    
    fourl_cuts_str.push_back("4 loose lep");
    fourl_cuts_str.push_back("neutral");
    fourl_cuts_str.push_back("SFOS Zveto");
     
//     double commoncuts[commoncuts_str.size()] = {};
//     double ss_2e_cuts[ss_2e_cuts_str.size()] = {};
//     double ss_2mu_cuts[ss_2mu_cuts_str.size()] = {};
//     double ss_emu_cuts[ss_emu_cuts_str.size()] = {};
//     double threel_cuts[threel_cuts_str.size()] = {};
//     double fourl_cuts[fourl_cuts_str.size()] = {};
//     annoying ...

    double commoncuts[20][20][6] = {{{}}};
    double ss_2e_cuts[20][20][6] = {{{}}};
    double ss_2mu_cuts[20][20][6] = {{{}}};
    double ss_emu_cuts[20][20][6] = {{{}}};
    double threel_cuts[20][20][6] = {{{}}};
    double fourl_cuts[20][20][6] = {{{}}};
    
    
    vstring ttHdecaystudy_str;
    ttHdecaystudy_str.push_back("H->bb");
    ttHdecaystudy_str.push_back("H->WW");
    ttHdecaystudy_str.push_back("H->tautau");
    ttHdecaystudy_str.push_back("H->ZZ");
    ttHdecaystudy_str.push_back("H->other");    
    ttHdecaystudy_str.push_back("no gen info");
    
    
    for (int i=0; i<numsamples; i++)
    {	
	int samp_int = samps[i];

	cout << "doing " << sample_names[samp_int] << endl;
        
        int samp_num_entries = ch[samp_int]->GetEntries();
        
        ch[samp_int]->SetBranchAddress("mcwgt", &mcwgt_intree);
        ch[samp_int]->SetBranchAddress("wgt", &wgt_intree);

        ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
        ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
        ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);

        ch[samp_int]->SetBranchAddress("looseMvaBased_leptons", &loose_leptons_intree);
        ch[samp_int]->SetBranchAddress("looseMvaBased_electrons", &loose_electrons_intree);
        ch[samp_int]->SetBranchAddress("looseMvaBased_muons", &loose_muons_intree);

        ch[samp_int]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
        ch[samp_int]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
        ch[samp_int]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);

        ch[samp_int]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
        ch[samp_int]->SetBranchAddress("loose_bJets", &loose_bJets_intree);
        ch[samp_int]->SetBranchAddress("tight_bJets", &tight_bJets_intree);
        ch[samp_int]->SetBranchAddress("met", &met_intree);
        //ch[samp_int]->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree); //<-


        for (Int_t j=0; j<samp_num_entries; j++)
        {
            ch[samp_int]->GetEntry(j);
        
            if (!(j % 100000)) cout << j << endl;
            // H decay studies
                        
            //int gpsize = (*pruned_genParticles_intree).size();            
            int thechildpdgid = 0;         
            int hdecayindex = 0;
            
            
            //if (wgt_intree<0.0) continue;
            //if (wgt_intree>=0) continue;
            
            
            
            // for (int j=0; j<gpsize; j++)
//             {
//                 int chil0 = (int)(*pruned_genParticles_intree)[j].child0;
//                 int chil1 = (int)(*pruned_genParticles_intree)[j].child1;
//                 if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil0<gpsize) && (*pruned_genParticles_intree)[j].status==22) thechildpdgid = (*pruned_genParticles_intree)[(*pruned_genParticles_intree)[j].child0].pdgID;
//                 else if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil1<gpsize) && (*pruned_genParticles_intree)[j].status==22) thechildpdgid = (*pruned_genParticles_intree)[(*pruned_genParticles_intree)[j].child1].pdgID;
//                 else if (thechildpdgid==0) hdecayindex = 5;
//                 else hdecayindex = 4;
//             }
//                        
//             
//             if (abs(thechildpdgid)==5) hdecayindex = 0;
//             if (abs(thechildpdgid)==24) hdecayindex = 1;
//             if (abs(thechildpdgid)==15) hdecayindex = 2;
//             if (abs(thechildpdgid)==23) hdecayindex = 3;
//         
            // common

            if (!(((*preselected_leptons_intree).size()>3) || ((*tightMvaBased_leptons_intree).size()>1))) continue;                
            commoncuts[0][samp_int][hdecayindex] += wgt_intree;        

            double mindilepmass = getTwoObjKineExtreme(*preselected_leptons_intree,"min","mass");        
            if (!(mindilepmass>12)) continue;                
            commoncuts[1][samp_int][hdecayindex] += wgt_intree;       

            if (!((*preselected_leptons_intree)[0].obj.Pt()>20 && (*preselected_leptons_intree)[1].obj.Pt()>10)) continue;        
            commoncuts[2][samp_int][hdecayindex] += wgt_intree;

            if (!((*preselected_jets_intree).size()>1)) continue;
            commoncuts[3][samp_int][hdecayindex] += wgt_intree;

            if (!(((*loose_bJets_intree).size()>1) || ((*tight_bJets_intree).size()>0))) continue;
            commoncuts[4][samp_int][hdecayindex] += wgt_intree;

            // 2e

            if ( ((*tightMvaBased_electrons_intree).size()==2) && ((*tightMvaBased_muons_intree).size()==0) && ((*loose_leptons_intree).size()<4) ) 
            {
                if (samp_int==5) wgt_intree *= 1.55; //ttjets
                ss_2e_cuts[0][samp_int][hdecayindex] += wgt_intree;

                if ((*tightMvaBased_electrons_intree)[0].charge==(*tightMvaBased_electrons_intree)[1].charge)
                {
                    ss_2e_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    if ((*preselected_jets_intree).size()>3)
                    {
                        ss_2e_cuts[2][samp_int][hdecayindex] += wgt_intree;

                        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                        double MHT_handle = objs_for_mht.Pt();
                        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                        if (metLD_handle> 0.2)
                        {
                            ss_2e_cuts[3][samp_int][hdecayindex] += wgt_intree;

                            if ((*tightMvaBased_electrons_intree)[0].obj.Pt()>20 && (*tightMvaBased_electrons_intree)[1].obj.Pt()>20)
                            {
                                ss_2e_cuts[4][samp_int][hdecayindex] += wgt_intree;

                                if (((*tightMvaBased_electrons_intree)[0].obj.Pt() + (*tightMvaBased_electrons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                                {
                                    ss_2e_cuts[5][samp_int][hdecayindex] += wgt_intree;

                                    double vetoZmass = pickFromSortedTwoObjKine(*preselected_electrons_intree,"mass",1,91.2);

                                    if (fabs(vetoZmass-91.2)>10)                     
                                    {
                                        ss_2e_cuts[6][samp_int][hdecayindex] += wgt_intree;

                                        if ((*tightMvaBased_electrons_intree)[0].isGsfCtfScPixChargeConsistent && (*tightMvaBased_electrons_intree)[1].isGsfCtfScPixChargeConsistent)
                                        {
                                            ss_2e_cuts[7][samp_int][hdecayindex] += wgt_intree;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // 2 mu

            if ( ((*tightMvaBased_electrons_intree).size()==0) && ((*tightMvaBased_muons_intree).size()==2) && ((*loose_leptons_intree).size()<4) ) 
            {
                if (samp_int==5) wgt_intree *= 3.3; //ttjets
                ss_2mu_cuts[0][samp_int][hdecayindex] += wgt_intree;

                if ((*tightMvaBased_muons_intree)[0].charge==(*tightMvaBased_muons_intree)[1].charge)
                {
                    ss_2mu_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    if ((*preselected_jets_intree).size()>3)
                    {
                        ss_2mu_cuts[2][samp_int][hdecayindex] += wgt_intree;

                        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                        double MHT_handle = objs_for_mht.Pt();
                        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                        if (metLD_handle> 0.2)
                        {
                            ss_2mu_cuts[3][samp_int][hdecayindex] += wgt_intree;

                            if ((*tightMvaBased_muons_intree)[0].obj.Pt()>20 && (*tightMvaBased_muons_intree)[1].obj.Pt()>20)
                            {
                                ss_2mu_cuts[4][samp_int][hdecayindex] += wgt_intree;

                                if (((*tightMvaBased_muons_intree)[0].obj.Pt() + (*tightMvaBased_muons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                                {
                                    ss_2mu_cuts[5][samp_int][hdecayindex] += wgt_intree;

                                    if ((*tightMvaBased_muons_intree)[0].chargeFlip<0.2 && (*tightMvaBased_muons_intree)[1].chargeFlip<0.2)
                                    {                                    
                                        ss_2mu_cuts[6][samp_int][hdecayindex] += wgt_intree;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        
            // 1 mu, 1 ele
            
            if ( ((*tightMvaBased_electrons_intree).size()==1) && ((*tightMvaBased_muons_intree).size()==1) && ((*loose_leptons_intree).size()<4) ) 
            {
                if (samp_int==5) wgt_intree *= 1.87; //ttjets
                ss_emu_cuts[0][samp_int][hdecayindex] += wgt_intree;

                if ((*tightMvaBased_electrons_intree)[0].charge==(*tightMvaBased_muons_intree)[0].charge)
                {
                    ss_emu_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    if ((*preselected_jets_intree).size()>3)
                    {
                        ss_emu_cuts[2][samp_int][hdecayindex] += wgt_intree;

                        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                        double MHT_handle = objs_for_mht.Pt();
                        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                        if (metLD_handle> 0.2)
                        {
                            ss_emu_cuts[3][samp_int][hdecayindex] += wgt_intree;

                            if ((*tightMvaBased_muons_intree)[0].obj.Pt()>20 && (*tightMvaBased_electrons_intree)[0].obj.Pt()>20)
                            {
                                ss_emu_cuts[4][samp_int][hdecayindex] += wgt_intree;

                                if (((*tightMvaBased_muons_intree)[0].obj.Pt() + (*tightMvaBased_electrons_intree)[0].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                                {
                                    ss_emu_cuts[5][samp_int][hdecayindex] += wgt_intree;

                                    if ((*tightMvaBased_muons_intree)[0].chargeFlip<0.2 && (*tightMvaBased_electrons_intree)[0].isGsfCtfScPixChargeConsistent)
                                    {                                    
                                        ss_emu_cuts[6][samp_int][hdecayindex] += wgt_intree;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
            // 3l
            
            if ( ((*tightMvaBased_leptons_intree).size()==3) && ((*loose_leptons_intree).size()<4) ) 
            {
                if (samp_int==5) wgt_intree *= 2.85; //ttjets
                threel_cuts[0][samp_int][hdecayindex] += wgt_intree;

                auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                double MHT_handle = objs_for_mht.Pt();
                double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                if ((metLD_handle>0.2) || ((*preselected_jets_intree).size()>3))
                {
                    threel_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    double vetoZmassSFOS = pickFromSortedTwoObjKine(*tightMvaBased_leptons_intree,"massSFOS",1,91.2);

                    if (fabs(vetoZmassSFOS-91.2)>10.)                     
                    {        
                          threel_cuts[2][samp_int][hdecayindex] += wgt_intree;  
                            
                    }
                }
            }
            
            // 4l
            
            if ((*loose_leptons_intree).size()==4)
            {
                fourl_cuts[0][samp_int][hdecayindex] += wgt_intree;

                if ( ((*loose_leptons_intree)[0].charge + (*loose_leptons_intree)[1].charge + (*loose_leptons_intree)[2].charge + (*loose_leptons_intree)[3].charge)==0 )
                {
                    fourl_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    double vetoZmassSFOS = pickFromSortedTwoObjKine(*loose_leptons_intree,"massSFOS",1,91.2);

                    if (fabs(vetoZmassSFOS-91.2)>10.)                     
                    {        
                          fourl_cuts[2][samp_int][hdecayindex] += wgt_intree;  
                            
                    }
                }
            }
            
            
//             // 3l test
//             
//             if ( ((*tightMvaBased_leptons_intree).size()>=2) && ((*preselected_leptons_intree).size()==3) ) 
//             {
//                 if (samp_int==5) wgt_intree *= 2.85; //ttjets
//                 threel_cuts[0][samp_int][hdecayindex] += wgt_intree;
// 
//                 auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
//                 double MHT_handle = objs_for_mht.Pt();
//                 double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;
// 
//                 if ((metLD_handle>0.2) || ((*preselected_jets_intree).size()>3))
//                 {
//                     threel_cuts[1][samp_int][hdecayindex] += wgt_intree;
// 
//                     double vetoZmassSFOS = pickFromSortedTwoObjKine(*preselected_leptons_intree,"massSFOS",1,91.2);
// 
//                     if (fabs(vetoZmassSFOS-91.2)>10.)                     
//                     {        
//                           threel_cuts[2][samp_int][hdecayindex] += wgt_intree;
//                           
//                           if ( (*tightMvaBased_leptons_intree)[0].charge==(*tightMvaBased_leptons_intree)[1].charge )
//                           {
//                                 
//                             threel_cuts[3][samp_int][hdecayindex] += wgt_intree;
//                           }
//                           
//                     }
//                 }
//             }
//             
//            
//             
//             
//             // 4l test
//             
//             if ((*tightMvaBased_leptons_intree).size()>=2 && (*preselected_leptons_intree).size()==4)
//             {
//                 fourl_cuts[0][samp_int][hdecayindex] += wgt_intree;
// 
//                 if ( ((*preselected_leptons_intree)[0].charge + (*preselected_leptons_intree)[1].charge + (*preselected_leptons_intree)[2].charge + (*preselected_leptons_intree)[3].charge)==0 && ((*tightMvaBased_leptons_intree)[0].charge==(*tightMvaBased_leptons_intree)[1].charge) )
//                 {
//                     fourl_cuts[1][samp_int][hdecayindex] += wgt_intree;
// 
//                     double vetoZmassSFOS = pickFromSortedTwoObjKine(*preselected_leptons_intree,"massSFOS",1,91.2);
// 
//                     if (fabs(vetoZmassSFOS-91.2)>10.)                     
//                     {        
//                           fourl_cuts[2][samp_int][hdecayindex] += wgt_intree;  
//                             
//                     }
//                 }
//             }
//             
            
            
            
            
            
            
            
       
                                  
        } // end event loop
    } // end sample loop 


///////////////////////////////////////////////////////////////////////////////////////////////
        
        // cut flow with h decay study:    
        
        
//     cout << " " << endl;
//     cout << " " << endl;
//     cout << "raw mc" << endl;
//     cout << " " << endl;
//     
// 
//     cout << "common" << endl;
//     cout << " " << endl;        
//     printf ("%40s","cut");
//     for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//     printf ("\n");        
//     cout << " " << endl;
// 
//     for (int i=0; i<commoncuts_str.size(); i++)
//     {
//         printf ("%40s", commoncuts_str[i].c_str());
// 
//         for (int j=0; j<ttHdecaystudy_str.size(); j++)
//         {    
//             int samp_int = samps[0];      
//             printf ("%15.2f", commoncuts[i][samp_int][j]);
//         }
// 
//         printf ("\n");
// 
//     }
// 
// 
// 
//     cout << "ss 2 ele" << endl;
//     cout << " " << endl;
//     printf ("%40s","cut");
//     for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//     printf ("\n");
//     cout << " " << endl;
// 
//     for (int i=0; i<ss_2e_cuts_str.size(); i++)
//     {
//         printf ("%40s", ss_2e_cuts_str[i].c_str());
// 
//         for (int j=0; j<ttHdecaystudy_str.size(); j++)
//         {    
//             int samp_int = samps[0];            
//             printf ("%15.2f", ss_2e_cuts[i][samp_int][j]);
//         }
// 
//         printf ("\n");
//     }
// 
//     cout << "ss 2 mu" << endl;
//     cout << " " << endl;
//     printf ("%40s","cut");
//     for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//     printf ("\n");
//     cout << " " << endl;        
// 
//     for (int i=0; i<ss_2mu_cuts_str.size(); i++)
//     {
//         printf ("%40s", ss_2mu_cuts_str[i].c_str());
// 
//         for (int j=0; j<ttHdecaystudy_str.size(); j++)
//         {    
//             int samp_int = samps[0];            
//             printf ("%15.2f", ss_2mu_cuts[i][samp_int][j]);
//         }
// 
//         printf ("\n");
//     }
// 
//     cout << "ss e mu" << endl;
//     cout << " " << endl;
//     printf ("%40s","cut");
//     for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//     printf ("\n");
//     cout << " " << endl;        
// 
//     for (int i=0; i<ss_emu_cuts_str.size(); i++)
//     {
//         printf ("%40s", ss_emu_cuts_str[i].c_str());
// 
//         for (int j=0; j<ttHdecaystudy_str.size(); j++)
//         {    
//             int samp_int = samps[0];            
//             printf ("%15.2f", ss_emu_cuts[i][samp_int][j]);
//         }
// 
//         printf ("\n");
//     }
// 
// 
// 
//     cout << "3 lep" << endl;
//     cout << " " << endl;
//     printf ("%40s","cut");
//     for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//     printf ("\n");
//     cout << " " << endl;        
// 
//     for (int i=0; i<threel_cuts_str.size(); i++)
//     {
//         printf ("%40s", threel_cuts_str[i].c_str());
// 
//         for (int j=0; j<ttHdecaystudy_str.size(); j++)
//         {    
//             int samp_int = samps[0];            
//             printf ("%15.2f", threel_cuts[i][samp_int][j]);
//         }
// 
//         printf ("\n");
//     }
// 
// 
//     cout << "4 lep" << endl;
//     cout << " " << endl;
//     printf ("%40s","cut");
//     for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//     printf ("\n");
//     cout << " " << endl;        
// 
//     for (int i=0; i<fourl_cuts_str.size(); i++)
//     {
//         printf ("%40s", fourl_cuts_str[i].c_str());
// 
//         for (int j=0; j<ttHdecaystudy_str.size(); j++)
//         {    
//             int samp_int = samps[0];            
//             printf ("%15.2f", fourl_cuts[i][samp_int][j]);
//         }
// 
//         printf ("\n");
//     }
// 
// 
// 
//     
//     
//     cout << " " << endl;
//     cout << " " << endl;
//     cout << "predicted events" << endl;
//     cout << " " << endl;
//         
// //    for (int j=0; j<ttHdecaystudy_str.size(); j++)
// //    {
// //        int samp_int = samps[0];
//         
//         cout << "common" << endl;
//         cout << " " << endl;
//         printf ("%40s","cut");
//         for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//         printf ("\n");
//         cout << " " << endl;
//         
//         for (int i=0; i<commoncuts_str.size(); i++)
//         {
//             printf ("%40s", commoncuts_str[i].c_str());
//             
//             for (int j=0; j<ttHdecaystudy_str.size(); j++)
//             {    
//                 int samp_int = samps[0];        
//                 printf ("%15.2f", (10000.*commoncuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "ss 2 ele" << endl;
//         cout << " " << endl;
//         printf ("%40s","cut");
//         for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<ss_2e_cuts_str.size(); i++)
//         {               
//             printf ("%40s", ss_2e_cuts_str[i].c_str());
//             
//             for (int j=0; j<ttHdecaystudy_str.size(); j++)
//             {    
//                 int samp_int = samps[0];            
//                 printf ("%15.2f", (10000.*ss_2e_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "ss 2 mu" << endl;
//         cout << " " << endl;
//         printf ("%40s","cut");
//         for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<ss_2mu_cuts_str.size(); i++)
//         {
//             printf ("%40s", ss_2mu_cuts_str[i].c_str());
//             
//             for (int j=0; j<ttHdecaystudy_str.size(); j++)
//             {    
//                 int samp_int = samps[0];            
//                 printf ("%15.2f", (10000.*ss_2mu_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//                 
//         cout << "ss e mu" << endl;
//         cout << " " << endl;
//         printf ("%40s","cut");
//         for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<ss_emu_cuts_str.size(); i++)
//         {
//             printf ("%40s", ss_emu_cuts_str[i].c_str());
//             
//             for (int j=0; j<ttHdecaystudy_str.size(); j++)
//             {    
//                 int samp_int = samps[0];            
//                 printf ("%15.2f", (10000.*ss_emu_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "3l" << endl;
//         cout << " " << endl;
//         printf ("%40s","cut");
//         for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<threel_cuts_str.size(); i++)
//         {
//             printf ("%40s", threel_cuts_str[i].c_str());
//             
//             for (int j=0; j<ttHdecaystudy_str.size(); j++)
//             {    
//                 int samp_int = samps[0];            
//                 printf ("%15.2f", (10000.*threel_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "4l" << endl;
//         cout << " " << endl;
//         printf ("%40s","cut");
//         for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<fourl_cuts_str.size(); i++)
//         {
//             printf ("%40s", fourl_cuts_str[i].c_str());
//             
//             for (int j=0; j<ttHdecaystudy_str.size(); j++)
//             {    
//                 int samp_int = samps[0];            
//                 printf ("%15.2f", (10000.*fourl_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//          }
//         
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////
        
        // cut flow with mult. samples:


   cout << " " << endl;
   cout << " " << endl;
   cout << "raw mc" << endl;
   cout << " " << endl;  
       
        cout << "common" << endl;
        cout << " " << endl;        
        printf ("%40s","cut");        
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");        
        cout << " " << endl;
        
        for (int i=0; i<commoncuts_str.size(); i++)
        {
            printf ("%40s", commoncuts_str[i].c_str());
                        
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];      
                printf ("%15.2f", commoncuts[i][samp_int][0]);
            }
            
            printf ("\n");
        
        }
        
        
        
        cout << "ss 2 ele" << endl;
        cout << " " << endl;
        //printf ("%40s%15s%15s%15s\n", "cut", "ttH", );
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;
        
        for (int i=0; i<ss_2e_cuts_str.size(); i++)
        {
            printf ("%40s", ss_2e_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", ss_2e_cuts[i][samp_int][0]);
            }
            
            printf ("\n");
        }
        
        cout << "ss 2 mu" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<ss_2mu_cuts_str.size(); i++)
        {
            printf ("%40s", ss_2mu_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", ss_2mu_cuts[i][samp_int][0]);
            }
            
            printf ("\n");
        }
        
        cout << "ss e mu" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<ss_emu_cuts_str.size(); i++)
        {
            printf ("%40s", ss_emu_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", ss_emu_cuts[i][samp_int][0]);
            }
            
            printf ("\n");
        }

        
        
        cout << "3 lep" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<threel_cuts_str.size(); i++)
        {
            printf ("%40s", threel_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", threel_cuts[i][samp_int][0]);
            }
            
            printf ("\n");
        }
        
        
        cout << "4 lep" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<fourl_cuts_str.size(); i++)
        {
            printf ("%40s", fourl_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", fourl_cuts[i][samp_int][0]);
            }
            
            printf ("\n");
        }
        
        
       
        


    
    
    cout << " " << endl;
    cout << " " << endl;
    cout << "predicted events" << endl;
    cout << " " << endl;
        
        
        cout << "common" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;
        
        for (int i=0; i<commoncuts_str.size(); i++)
        {
            printf ("%40s", commoncuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];        
                printf ("%15.2f", (10000.*commoncuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        cout << "ss 2 ele" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<ss_2e_cuts_str.size(); i++)
        {               
            printf ("%40s", ss_2e_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", (10000.*ss_2e_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        cout << "ss 2 mu" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<ss_2mu_cuts_str.size(); i++)
        {
            printf ("%40s", ss_2mu_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", (10000.*ss_2mu_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
                
        cout << "ss e mu" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<ss_emu_cuts_str.size(); i++)
        {
            printf ("%40s", ss_emu_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", (10000.*ss_emu_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        cout << "3l" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<threel_cuts_str.size(); i++)
        {
            printf ("%40s", threel_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", (10000.*threel_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        cout << "4l" << endl;
        cout << " " << endl;
        //printf ("%40s %15s \n", "cut", "ttH");
        printf ("%40s","cut");
        for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<fourl_cuts_str.size(); i++)
        {
            printf ("%40s", fourl_cuts_str[i].c_str());
            
            for (int j=0; j<numsamples; j++)
            {    
                int samp_int = samps[j];            
                printf ("%15.2f", (10000.*fourl_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        
        

    
    
}

void MakeGoodPlot::draw_several_comparisons(std::vector<int> samps)
{
        bool debug = false;
        
        std::vector<TString> tempfilenames;
        int numsamples = samps.size();		
	load_samples(samps);	
        const int numplots = 13;
        
        TH1D *sample_hist[numplots][numsamples];
        TString xaxis_title[numplots];
        
        double first_bin_low_edge[numplots];
	double last_bin_up_edge[numplots];
	int bins[numplots];
        
        //// define some parameters for the plots:
        
	// title of plot (displayed below ratio plot)
	xaxis_title[0] = "preselected lepton pt";		
	first_bin_low_edge[0] = 0.;
	last_bin_up_edge[0] = 400.;
	bins[0] = 100;       
        
        
        xaxis_title[1] = "leading lep pt";		
	first_bin_low_edge[1] = 0.;
	last_bin_up_edge[1] = 400.;
	bins[1] = 100;
        
        
        xaxis_title[2] = "2nd lep pt";		
	first_bin_low_edge[2] = 0.;
	last_bin_up_edge[2] = 300.;
	bins[2] = 75;
        
        
        xaxis_title[3] = "MET";		
	first_bin_low_edge[3] = 0.;
	last_bin_up_edge[3] = 400.;
	bins[3] = 100;
        
        
        xaxis_title[4] = "MET phi";		
	first_bin_low_edge[4] = -4.;
	last_bin_up_edge[4] = 4.;
	bins[4] = 100;
        
        
        xaxis_title[5] = "num Jets";		
	first_bin_low_edge[5] = 0.;
	last_bin_up_edge[5] = 20.;
	bins[5] = 20;
                
        
        xaxis_title[6] = "Jet Energy";		
	first_bin_low_edge[6] = 0.;
	last_bin_up_edge[6] = 1000.;
	bins[6] = 100;
        
        
        xaxis_title[7] = "Leading Jet Energy";		
	first_bin_low_edge[7] = 0.;
	last_bin_up_edge[7] = 1000.;
	bins[7] = 100;
        
        xaxis_title[8] = "2nd Jet Energy";		
	first_bin_low_edge[8] = 0.;
	last_bin_up_edge[8] = 1000.;
	bins[8] = 100;
        
        xaxis_title[9] = "Lepton phi";		
	first_bin_low_edge[9] = -4.;
	last_bin_up_edge[9] = 4.;
	bins[9] = 100;
                
        xaxis_title[10] = "Lepton eta";		
	first_bin_low_edge[10] = -3.;
	last_bin_up_edge[10] = 3.;
	bins[10] = 100;
        
        xaxis_title[11] = "Jet phi";		
	first_bin_low_edge[11] = -4.;
	last_bin_up_edge[11] = 4.;
	bins[11] = 100;
        
        
        xaxis_title[12] = "Jet eta";		
	first_bin_low_edge[12] = -3.;
	last_bin_up_edge[12] = 3.;
	bins[12] = 100;
        
        
        

       
//         TCanvas *myC[numplots];
//         THStack *nice_stack[numplots];
// 	TH1F *sum[numplots];
// 	TLegend *leg[numplots];
//         
//         for (int i=0; i<numplots; i++)	
//         {
// 
// 	    myC[i] = new TCanvas("myC_"+mylabel, "myC_"+mylabel, 600,700);
// 	    gStyle->SetPadBorderMode(0);
// 	    gStyle->SetFrameBorderMode(0);
// 	    Float_t small = 1.e-5;
// 	    myC[i]->Divide(1,2,small,small);
// 	    const float padding=1e-5; const float ydivide=0.3;
// 	    myC[i]->GetPad(1)->SetPad( padding, ydivide + padding , 1-padding, 1-padding);
// 	    myC[i]->GetPad(2)->SetPad( padding, padding, 1-padding, ydivide-padding);
// 	    myC[i]->GetPad(1)->SetLeftMargin(.11);
// 	    myC[i]->GetPad(2)->SetLeftMargin(.11);
// 	    myC[i]->GetPad(1)->SetRightMargin(.05);
// 	    myC[i]->GetPad(2)->SetRightMargin(.05);
// 	    myC[i]->GetPad(1)->SetBottomMargin(.3);
// 	    myC[i]->GetPad(2)->SetBottomMargin(.3);
// 	    myC[i]->GetPad(1)->Modified();
// 	    myC[i]->GetPad(2)->Modified();
// 	    myC[i]->cd(1);
// 	    gPad->SetBottomMargin(small);
// 	    gPad->Modified();	
//             leg[i] = new TLegend(0.11,0.91,0.89,0.99);
// 	    leg[i]->SetFillColor(kWhite);
// 	    leg[i]->SetLineColor(kWhite);
// 	    leg[i]->SetShadowColor(kWhite);
// 	    leg[i]->SetTextFont(42);
// 	    leg[i]->SetTextSize(0.028);
// 	    leg[i]->SetNColumns(3);
// 
//             nice_stack[i] = new THStack("stack_"+int2ss(i),";" + xaxis_title);
//             sum[i]; = new TH1F("sum bkgd "+int2ss(i),"",bins[i],first_bin_low_edge[i],last_bin_up_edge[i]);
//         }
        
        
        
// 	int where_is_sig = -1;
// 	int where_is_data_mu = -1;
// 	int where_is_data_ele = -1;
	
	
        for (int i=0; i<numsamples; i++)
	{	
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
	
		// --------------
                
                if (debug) cout << "hey1" << endl;
                
                int theentries = ch[samp_int]->GetEntries();
                cout << ch[samp_int]->GetEntries() << endl;
                
                tempfilenames.push_back("temp_"+int2ss(i)+".root");
	        TFile newtempfile("temp_"+int2ss(i)+".root","RECREATE");
                
                if (debug) cout << "hey2" << endl;
                
	        ch[samp_int]->SetBranchAddress("mcwgt", &mcwgt_intree);
                ch[samp_int]->SetBranchAddress("wgt", &wgt_intree);

                ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
                ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
                ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);

                ch[samp_int]->SetBranchAddress("looseMvaBased_leptons", &loose_leptons_intree);
                ch[samp_int]->SetBranchAddress("looseMvaBased_electrons", &loose_electrons_intree);
                ch[samp_int]->SetBranchAddress("looseMvaBased_muons", &loose_muons_intree);

                ch[samp_int]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
                ch[samp_int]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
                ch[samp_int]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);

                ch[samp_int]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
                ch[samp_int]->SetBranchAddress("met", &met_intree);
                
                ch[samp_int]->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);
                
                for (int j=0;j<numplots;j++)
                {
                    sample_hist[j][i] = new TH1D("hist_"+int2ss(j),";"+xaxis_title[j],bins[j],first_bin_low_edge[j],last_bin_up_edge[j]);
                    sample_hist[j][i]->Sumw2();
                }
                
                int countbefore = 0;
                int countafter = 0;
                
                if (debug) cout << "hey3" << endl;
                
                for (int j=0;j<theentries;j++)
	        {
		
                    ch[samp_int]->GetEntry(j);
								
		    weight = wgt_intree;
                    
                    bool keepthisevent = true;
                    countbefore++;
                    
                    if (debug) cout << "hey4" << endl;
                    
                    // picks only H->non-bb for consistancy between samples:
                    if (debug) cout << (*pruned_genParticles_intree).size() << endl;
                    
                    for (unsigned int k=0;k<(*pruned_genParticles_intree).size();k++)
                    {
                        if (debug) cout << "hey41" << endl;
                        if ((*pruned_genParticles_intree)[k].pdgID==25)
                        {
                            if (debug) cout << "hey411" << endl;
                            if (debug) cout << (*pruned_genParticles_intree)[k].child0 << endl;
                            if (debug) cout << (*pruned_genParticles_intree)[k].child1 << endl;
                            
                            if ((*pruned_genParticles_intree)[k].child0<(*pruned_genParticles_intree).size())
                            {    
                                if (abs((*pruned_genParticles_intree)[(*pruned_genParticles_intree)[k].child0].pdgID)==5)
                                {
                                    keepthisevent = false;
                                    if (debug) cout << "hey4111" << endl;
                                }
                            }
                            
                            if ((*pruned_genParticles_intree)[k].child1<(*pruned_genParticles_intree).size())
                            {    
                                if (abs((*pruned_genParticles_intree)[(*pruned_genParticles_intree)[k].child1].pdgID)==5)
                                {
                                    keepthisevent = false;
                                    if (debug) cout << "hey4111" << endl;
                                }
                            }
                                                                                   
                        
                        }
                    }
                    if (debug) cout << "hey41111" << endl;
                    if (!keepthisevent) continue;
                    if (debug) cout << "hey411111" << endl;
                    if ((*preselected_leptons_intree).size()==0) continue;
                    if (debug) cout << "hey4111111" << endl;
                    countafter++;
                    if (debug) cout << "hey5" << endl;
                    if (debug) cout << "hey41111111" << endl;
                    
                    
                    for (unsigned int k=0;k<(*preselected_leptons_intree).size();k++)
                    {
                        sample_hist[0][i]->Fill( (*preselected_leptons_intree)[k].obj.Pt(), weight );
                        sample_hist[9][i]->Fill( (*preselected_leptons_intree)[k].obj.Phi(), weight );
                        sample_hist[10][i]->Fill( (*preselected_leptons_intree)[k].obj.Eta(), weight );                        
                    }
                    if (debug) cout << "hey6" << endl;
                    if ((*preselected_leptons_intree).size()>0) sample_hist[1][i]->Fill( (*preselected_leptons_intree)[0].obj.Pt(), weight );
                    if ((*preselected_leptons_intree).size()>1) sample_hist[2][i]->Fill( (*preselected_leptons_intree)[1].obj.Pt(), weight );
                    
                    for (unsigned int k=0;k<(*preselected_jets_intree).size();k++)
                    {
                        sample_hist[6][i]->Fill( (*preselected_jets_intree)[k].obj.E(), weight );
                        sample_hist[11][i]->Fill( (*preselected_jets_intree)[k].obj.Phi(), weight );
                        sample_hist[12][i]->Fill( (*preselected_jets_intree)[k].obj.Eta(), weight );
                    }
                    if (debug) cout << "hey7" << endl;
                    sample_hist[5][i]->Fill( (*preselected_jets_intree).size(), weight );                    
                    
                    if ((*preselected_jets_intree).size()>0) sample_hist[7][i]->Fill( (*preselected_jets_intree)[0].obj.E(), weight );
                    if ((*preselected_jets_intree).size()>1) sample_hist[8][i]->Fill( (*preselected_jets_intree)[1].obj.E(), weight );
                    
                    
                    sample_hist[3][i]->Fill( (*met_intree)[0].obj.Pt(), weight );
                    sample_hist[4][i]->Fill( (*met_intree)[0].obj.Phi(), weight );
                    
                    
                    
                    if (debug) cout << "hey8" << endl;
                   
                    
                }
                        
                cout << " " << endl;
		cout << "all events: " << countbefore << endl;
                cout << "all events passing sel: " << countafter << endl;
                cout << " " << endl;
                
                newtempfile.Write();
                newtempfile.Close();
                
                
                // for (int j=0; j<numplots; j++)
//                 {
// 	
// 		    float sample_evts = sample_hist[i]->Integral();
// 		    std::ostringstream sample_evts_ss;
// 		    sample_evts_ss << sample_evts;
// 		    std::string sample_evts_string = sample_evts_ss.str();
// 
// 
// 		    if (samp_int==0||samp_int==10)
// 		    {
// 			    sample_hist[j][i]->SetLineColor(1);
// 			    sample_hist[j][i]->SetLineWidth(2);
// 			    sample_hist[j][i]->GetXaxis()->SetTitle(xaxis_title[j]);
// 			    //if(samp_int==0) leg->AddEntry(sample_hist[i],sample_names[0] + " (" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
// 			    sample_hist[j][i]->SetStats(0);
// 			    sample_hist[j][i]->SetTitleSize(0);
// 			    //sample_hist[j][i]->Sumw2();
// 			    if(samp_int==0) where_is_data_mu = i;
// 			    if(samp_int==10) where_is_data_ele = i;
// 		    }
// 		    else
// 		    {
// 			    if (samp_int==1)
// 			    {
// 				    sample_hist[j][i]->SetLineColor(1+samp_int);
// 				    sample_hist[j][i]->SetLineWidth(2);
// 				    sample_hist[j][i]->GetXaxis()->SetTitle(xaxis_title[j]);
// 				    leg[j]->AddEntry(sample_hist[j][i],sample_names[samp_int] + " (15x" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
// 				    sample_hist[j][i]->SetStats(0);
// 				    sample_hist[j][i]->SetTitleSize(0);
// 				    sample_hist[j][i]->Scale(15);
// 				    where_is_sig = i;
// 			    }
// 			    else
// 			    {
// 				    if (samp_int<4) sample_hist[j][i]->SetFillColor(1+samp_int);		
// 				    if (samp_int>=4) sample_hist[j][i]->SetFillColor(2+samp_int);
// 
// 				    sample_hist[j][i]->GetXaxis()->SetTitle(xaxis_title);
// 				    //sample_hist[i]->SetLineWidth(2);
// 				    leg[j]->AddEntry(sample_hist[j][i],sample_names[samp_int] + " (" + sample_evts_string + ")","F");  /// have ability to add # of evts per sample to legend... 
// 				    //leg->AddEntry(sample_hist[i],sample_names[samp_int],"l");
// 
// 				    sample_hist[j][i]->SetStats(0);
// 				    sample_hist[j][i]->SetTitleSize(0);
// 
// 				    nice_stack[j]->Add(sample_hist[j][i]);
// 				    sum[j]->Add((TH1F*)sample_hist[j][i]);
// 			    }
// 		    }
// 	
//                 }
        
        
	
        
        
        }
	
        
	
// 	double maxstack = nice_stack->GetMaximum();
// 	nice_stack->SetMaximum(1.25*maxstack);
// 	nice_stack->Draw();		
// 	
// 	if (where_is_sig>=0) sample_hist[where_is_sig]->Draw("same");
// 	if (where_is_data_mu>=0&&where_is_data_ele>=0)
// 	{
// 		sample_hist[where_is_data_mu]->Add(sample_hist[where_is_data_ele],1.0);
// 		float sample_evts = sample_hist[where_is_data_mu]->Integral();
// 		std::ostringstream sample_evts_ss;
// 		sample_evts_ss << sample_evts;
// 		std::string sample_evts_string = sample_evts_ss.str();
// 		leg->AddEntry(sample_hist[where_is_data_mu],("data (" + sample_evts_string + ")").c_str(),"LPE");
// 		sample_hist[where_is_data_mu]->Draw("esame");
// 	}
// 
// 	leg->SetFillColor(0);
// 	leg->Draw("same");
    
    
    
    
    compareplots(samps, tempfilenames);
    
    
    
    
    
}
void MakeGoodPlot::draw_simple_curves_normalized(std::vector<int> samps)
{
	
	int numsamples = samps.size();
	
	TH1F *sample_hist[numsamples];
	
//	load_samples(samps); // comment out for my trees
	load_samples(samps);
	
	//TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);  /// (0.3,0.77,0.7,0.88)
	//TLegend* leg = new TLegend(0.14,0.75,0.94,0.89); // Darren format
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	//leg->SetTextSize(0.035);
	leg->SetNColumns(5);
	
	
	TH1F *flavorhist[3];
	flavorhist[0] = new TH1F("ttbb",";CSV",50,-1,1);
	//flavorhist[0] = new TH1F("ttbb",";CSV",100,-50,50);
	flavorhist[1] = new TH1F("ttcc",";CSV",50,-1,1);
	flavorhist[2] = new TH1F("ttlf",";CSV",50,-1,1);
	
	for (int i=0; i<numsamples; i++)
	{
		
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
		
		//sample_hist[i]->SetTitle("BDT response, 5j4t");
		//sample_hist[i]->SetBins(50,-1,1);
		
		//sample_hist[i] = new TH1F("BDT response, 5j4t " + sample_names[samp_int],"",20,-1,1);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";#Sigma jet p_{T}/#Sigma jet E",10,0,1);       // title  // #Sigma jet p_{T}/#Sigma jet E
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";sphericity",10,0,1);       // title  // #Sigma jet p_{T}/#Sigma jet E
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";average #DeltaR(b-tags)",10,0,4);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";Best Higgs Mass",25,0,500);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";Median Inv. Mass (tag,tag)",10,0,500);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";#sqrt{#Delta#eta(t_{lep},bb)#times#Delta#eta(t_{had},bb)}",10,0,6);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";best #DeltaR(b,b)",10,0,5);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";sum p_{T}(lepton,jets,MET)",25,0,1500);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";second highest CSV output (b-tags)",10,0.6,1);
		sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";awert",150,-50,100);
		
		//get_hist_of_tiered_MVA_response_for_one_sample_5j4t(sample_hist[i],samp_int);
		//get_hist_MVA_response_for_one_sample_643203(sample_hist[i],samp_int);
		
		get_hist_of_simple_variable(sample_hist[i],samp_int);
		//get_even_simpler_plot_my_trees(sample_hist[i],samp_int);
		//get_hist_of_simple_variable(flavorhist[0],samp_int,flavorhist[1],flavorhist[2]);
		
		float sample_evts = sample_hist[i]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();
		
		/*
		if (samp_int<4) sample_hist[i]->SetLineColor(1+samp_int);		
		if (samp_int>=4) sample_hist[i]->SetLineColor(2+samp_int);
		*/
		
		// Darren:
		/*
		h_ttH->SetLineColor(kBlue);
		h_ttlf->SetLineColor(kRed);
		h_ttcc->SetLineColor(kMagenta+2);
		h_ttbb->SetLineColor(kGreen+1);
		h_ttb->SetLineColor(kOrange+1);
		*/
		
		if (samp_int==1) sample_hist[i]->SetLineColor(kRed); // ttH
		//if (samp_int==2) sample_hist[i]->SetLineColor(kGreen+1); //--
		//if (samp_int==3) sample_hist[i]->SetLineColor(kOrange+1); //--
		//if (samp_int==4) sample_hist[i]->SetLineColor(kMagenta+2); //--
		if (samp_int==5) sample_hist[i]->SetLineColor(kBlue); // ttjets
		if (samp_int==6) sample_hist[i]->SetLineColor(kGreen+1); // zjets
		if (samp_int==7) sample_hist[i]->SetLineColor(kOrange+1); //wjets
		if (samp_int==8) sample_hist[i]->SetLineColor(kMagenta+1); //ttw
		if (samp_int==9) sample_hist[i]->SetLineColor(kCyan-3); //ttz
		if (samp_int==10) sample_hist[i]->SetLineColor(kBlue-6); // diboson
                
                
				
		sample_hist[i]->GetXaxis()->SetTitle("3rd-highest lep MVA output");		
		sample_hist[i]->SetLineWidth(2);
		leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (" + sample_evts_string + ")","l");  /// have ability to add # of evts per sample to legend... 
		//leg->AddEntry(sample_hist[i],sample_names[samp_int],"l");

		//sample_hist[i]->SetStats(0);
		//sample_hist[i]->SetTitleSize(0);		// <- works?
		
		
		if (!i)
		{
			//double maxstack = 
			//sample_hist[i]->SetMaximim(1.25*sample_hist[i]->GetMaximum());
			sample_hist[i]->DrawNormalized();			
		}
		else sample_hist[i]->DrawNormalized("same");
		//if (!i) sample_hist[i]->Draw();
		//else sample_hist[i]->Draw("same");
		
		
	}
	
	leg->SetFillColor(0);
	//leg->Draw("same");
	//CMSInfoLatex->Draw("same");
	
	//std::string selectioninfo = "#geq 6 jets + 2 b-tags";
	//std::string selectioninfo = "#geq 6 jets + 3 b-tags";
	//std::string selectioninfo = "#geq 6 jets + #geq 4 b-tags";
	//std::string selectioninfo = "5 jets + 3 b-tags";
	//std::string selectioninfo = "5 jets + #geq 4 b-tags";
	std::string selectioninfo = "#geq 2 tight leps";
	
	TLatex *SELECTIONInfoLatex = new TLatex(0.62, 0.84, selectioninfo.c_str());  		// right
	//TLatex *SELECTIONInfoLatex = new TLatex(0.15, 0.84, selectioninfo.c_str());  		// left
	
	
	SELECTIONInfoLatex->SetNDC();
	SELECTIONInfoLatex->SetTextFont(42);
	SELECTIONInfoLatex->SetTextSize(0.05);
	SELECTIONInfoLatex->Draw("same");
	
	flavorhist[0]->SetLineWidth(2);
	flavorhist[0]->SetLineColor(kRed);
	flavorhist[0]->SetStats(0);
	flavorhist[1]->SetLineWidth(2);
	flavorhist[1]->SetLineColor(kBlue);
	flavorhist[1]->SetStats(0);
	flavorhist[2]->SetLineWidth(2);
	flavorhist[2]->SetLineColor(kGreen);
	flavorhist[2]->SetStats(0);	
	
	//leg->AddEntry(flavorhist[0],"b-jets","l");
	//leg->AddEntry(flavorhist[1],"c-jets","l");
	//leg->AddEntry(flavorhist[2],"other","l");
	
	//flavorhist[0]->DrawNormalized();
	//flavorhist[1]->DrawNormalized("same");
	//flavorhist[2]->DrawNormalized("same");
	leg->Draw("same");
}

void MakeGoodPlot::draw_nice_stack_with_ratio(std::vector<int> samps, std::string mytitle, std::string mylabel)
{
	int numsamples = samps.size();
	TH1D *sample_hist[numsamples];	
	load_samples(samps);
	
	// title of plot (displayed below ratio plot)
	TString xaxis_title = "Gaussian Variable (4#sigma Separation), 6j4t";
	
        //TString xaxis_title = mytitle;
        
	// y-axis label (stack):
	
	// y-axis label (ratio):
	
	// range, bins (stack and ratio are same):
	double first_bin_low_edge = 0.;
	double last_bin_up_edge = 400.;
	int bins = 200;
		


	
	//Hack to get it plotted with ratio plot
	//TCanvas* myC = new TCanvas("myC_"+mylabel, "myC_"+mylabel, 600,700);
	TCanvas* myC = new TCanvas("myC_", "myC_", 600,700);
        gStyle->SetPadBorderMode(0);
	gStyle->SetFrameBorderMode(0);
	Float_t small = 1.e-5;
	myC->Divide(1,2,small,small);
	const float padding=1e-5; const float ydivide=0.3;
	myC->GetPad(1)->SetPad( padding, ydivide + padding , 1-padding, 1-padding);
	myC->GetPad(2)->SetPad( padding, padding, 1-padding, ydivide-padding);
	myC->GetPad(1)->SetLeftMargin(.11);
	myC->GetPad(2)->SetLeftMargin(.11);
	myC->GetPad(1)->SetRightMargin(.05);
	myC->GetPad(2)->SetRightMargin(.05);
	myC->GetPad(1)->SetBottomMargin(.3);
	myC->GetPad(2)->SetBottomMargin(.3);
	myC->GetPad(1)->Modified();
	myC->GetPad(2)->Modified();
	myC->cd(1);
	gPad->SetBottomMargin(small);
	gPad->Modified();	
	
	THStack *nice_stack = new THStack("stack1",";" + xaxis_title);
	TH1F *sum = new TH1F("sum bkgd","",bins,first_bin_low_edge,last_bin_up_edge);
	
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.028);
	leg->SetNColumns(3);
	
	int where_is_sig = -1;
	int where_is_data_mu = -1;
	int where_is_data_ele = -1;
	
	for (int i=0; i<numsamples; i++)
	{	
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
	
		// --------------

		sample_hist[i] = new TH1D(xaxis_title + " " + sample_names[samp_int],"",bins,first_bin_low_edge,last_bin_up_edge);
		get_hist_of_simple_variable(sample_hist[i],samp_int);
		// --------------
		

	
		float sample_evts = sample_hist[i]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();

		
		if (samp_int==0||samp_int==10)
		{
			sample_hist[i]->SetLineColor(1);
			sample_hist[i]->SetLineWidth(2);
			sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
			//if(samp_int==0) leg->AddEntry(sample_hist[i],sample_names[0] + " (" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
			sample_hist[i]->SetStats(0);
			sample_hist[i]->SetTitleSize(0);
			sample_hist[i]->Sumw2();
			if(samp_int==0) where_is_data_mu = i;
			if(samp_int==10) where_is_data_ele = i;
		}
		else
		{
			if (samp_int==1)
			{
				sample_hist[i]->SetLineColor(1+samp_int);
				sample_hist[i]->SetLineWidth(2);
				sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
				leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (15x" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
				sample_hist[i]->SetStats(0);
				sample_hist[i]->SetTitleSize(0);
				sample_hist[i]->Scale(15);
				where_is_sig = i;
			}
			else
			{
				if (samp_int<4) sample_hist[i]->SetFillColor(1+samp_int);		
				if (samp_int>=4) sample_hist[i]->SetFillColor(2+samp_int);

				sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
				//sample_hist[i]->SetLineWidth(2);
				leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (" + sample_evts_string + ")","F");  /// have ability to add # of evts per sample to legend... 
				//leg->AddEntry(sample_hist[i],sample_names[samp_int],"l");

				sample_hist[i]->SetStats(0);
				sample_hist[i]->SetTitleSize(0);

				nice_stack->Add(sample_hist[i]);
				sum->Add((TH1F*)sample_hist[i]);
			}
		}
	
	}
	
	
	double maxstack = nice_stack->GetMaximum();
	nice_stack->SetMaximum(1.25*maxstack);
	nice_stack->Draw();		
	
	if (where_is_sig>=0) sample_hist[where_is_sig]->Draw("same");
	if (where_is_data_mu>=0&&where_is_data_ele>=0)
	{
		sample_hist[where_is_data_mu]->Add(sample_hist[where_is_data_ele],1.0);
		float sample_evts = sample_hist[where_is_data_mu]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();
		leg->AddEntry(sample_hist[where_is_data_mu],("data (" + sample_evts_string + ")").c_str(),"LPE");
		sample_hist[where_is_data_mu]->Draw("esame");
	}

	leg->SetFillColor(0);
	leg->Draw("same");
	
	

	
	
	
	
}

void MakeGoodPlot::draw_nice_stack(std::vector<int> samps)
{
	int numsamples = samps.size();
	TH1D *sample_hist[numsamples];
	//TH1D sample_hist[numsamples];
	
	//cout << "before load" << endl;
	
	load_samples(samps);
	
	//cout << "after load" << endl;

	TString xaxis_title = "Gaussian Variable (4#sigma Separation), 6j4t";
	
	THStack *nice_stack = new THStack("stack1",";" + xaxis_title);
	TH1F *sum = new TH1F("BDT response, 6j4t, sum bkgd","",20,-1.0,1.0);
	
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.028);
	leg->SetNColumns(3);
	
	int where_is_sig = -1;
	int where_is_data_mu = -1;
	int where_is_data_ele = -1;
	
	for (int i=0; i<numsamples; i++)
	{	
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
	
		// --------------
		//sample_hist[i] = new TH1D("Gaussian Variable (2#sigma Separation)" + sample_names[samp_int],"",24,-4,8);
		sample_hist[i] = new TH1D("Gaussian Variable (2#sigma Separation)" + sample_names[samp_int],"",200,0,400);
		get_hist_of_simple_variable(sample_hist[i],samp_int);
		// --------------
		
		/*
		for (int sp=0; sp<33; sp++)
		{
			TString shiftpoint = int2ss(sp);
			sample_hist_shared[i][sp] = new TH1F("BDT response, 6j4t " + sample_names[samp_int] + " " + shiftpoint,"",20,-1.0,1.0);
		}
			
		
		//get_hist_of_tiered_MVA_response_for_one_sample_643900XX( samp_int, i );
		//sample_hist[i] = (TH1D*)sample_hist_shared[i][16]->Clone();
		
		sample_hist[i] = new TH1D("BDT response, 6j4t " + sample_names[samp_int],"",20,-1.0,1.0);
		get_hist_of_tiered_MVA_response_for_one_sample_6j4t(sample_hist[i],samp_int);
		*/
		
		// --------------
		
		
		//TString xaxis_title = "Sigma(pt)/Sigma(E)";
		//TString xaxis_title = "BDT Response, 6j4t";
	
		float sample_evts = sample_hist[i]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();

		
		if (samp_int==0||samp_int==10)
		{
			sample_hist[i]->SetLineColor(1);
			sample_hist[i]->SetLineWidth(2);
			sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
			//if(samp_int==0) leg->AddEntry(sample_hist[i],sample_names[0] + " (" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
			sample_hist[i]->SetStats(0);
			sample_hist[i]->SetTitleSize(0);
			sample_hist[i]->Sumw2();
			if(samp_int==0) where_is_data_mu = i;
			if(samp_int==10) where_is_data_ele = i;
		}
		else
		{
			if (samp_int==1)
			{
				sample_hist[i]->SetLineColor(1+samp_int);
				sample_hist[i]->SetLineWidth(2);
				sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
				leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (15x" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
				sample_hist[i]->SetStats(0);
				sample_hist[i]->SetTitleSize(0);
				sample_hist[i]->Scale(15);
				where_is_sig = i;
			}
			else
			{
				if (samp_int<4) sample_hist[i]->SetLineColor(1+samp_int);		
				if (samp_int>=4) sample_hist[i]->SetLineColor(2+samp_int);

				sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
				//sample_hist[i]->SetLineWidth(2);
				leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (" + sample_evts_string + ")","F");  /// have ability to add # of evts per sample to legend... 
				//leg->AddEntry(sample_hist[i],sample_names[samp_int],"l");

				sample_hist[i]->SetStats(0);
				sample_hist[i]->SetTitleSize(0);
				//if (!i) sample_hist[i]->DrawNormalized();
				//else sample_hist[i]->DrawNormalized("same");
				//if (!i) sample_hist[i]->Draw();
				//else sample_hist[i]->Draw("same");

				nice_stack->Add(sample_hist[i]);
				//sum->Add((TH1F*)sample_hist[i]);
			}
		}
	
	}
	
	
	double maxstack = nice_stack->GetMaximum();
	nice_stack->SetMaximum(1.25*maxstack);
	nice_stack->Draw();
	
		
	
	if (where_is_sig>=0) sample_hist[where_is_sig]->Draw("e2same");
	if (where_is_data_mu>=0&&where_is_data_ele>=0)
	{
		sample_hist[where_is_data_mu]->Add(sample_hist[where_is_data_ele],1.0);
		float sample_evts = sample_hist[where_is_data_mu]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();
		leg->AddEntry(sample_hist[where_is_data_mu],("data (" + sample_evts_string + ")").c_str(),"LPE");
		sample_hist[where_is_data_mu]->Draw("esame");
	}

	leg->SetFillColor(0);
	leg->Draw("same");
	
	// optional print stuff:
	//TH1F *thesighist = (TH1F*)sample_hist[where_is_sig]->Clone();
	//TH1F *thebackhist = (TH1F*)nice_stack->GetHistogram()->Clone();
	//get_roc_curve(thesighist, sum, 0);	
	//cout << "sig eff at 1% back eff: " << roc_curve[0]->Eval(0.99) << endl;
	//cout << "sig eff at 10% back eff: " << roc_curve[0]->Eval(0.90) << endl;
	//cout << "sig eff at 30% back eff: " << roc_curve[0]->Eval(0.70) << endl;
	
	//thesighist->Draw();
	//thebackhist->Draw("same");
	
	
}
void MakeGoodPlot::get_even_simpler_plot_my_trees(TH1 *plot, int sample_number)
{
	
	TChain thetree("tree_of_knowledge");

	cout << sample_number << endl;

	if (sample_number==1) thetree.Add("ttH_temp_tree_22_with_BDT_ttbbttHBDT__using_eq_num_evts__640203_15_bestsep__removed_angle_tops_bb_added_avg_btag_disc_btags_trial2__10bestsep_ttbbttHBDT_in_5j4t__15bestsep_ttbbttHBDT_in_6j3t_.root");
	else if (sample_number==2) thetree.Add("tt2b_ge4j_ge2t.root");
	else if (sample_number==3) thetree.Add("tt1b_ge4j_ge2t.root");
	else if (sample_number==4) thetree.Add("ttcc_temp_tree_22_with_BDT_ttbbttHBDT__using_eq_num_evts__640203_15_bestsep__removed_angle_tops_bb_added_avg_btag_disc_btags_trial2__10bestsep_ttbbttHBDT_in_5j4t__15bestsep_ttbbttHBDT_in_6j3t.root");
	else if (sample_number==5) thetree.Add("ttlf_temp_tree_22_with_BDT_ttbbttHBDT__using_eq_num_evts__640203_15_bestsep__removed_angle_tops_bb_added_avg_btag_disc_btags_trial2__10bestsep_ttbbttHBDT_in_5j4t__15bestsep_ttbbttHBDT_in_6j3t.root");
	else return;
	
	int numentrs = thetree.GetEntries();
		
	double thewgt = 0.;
	double thevar = 99999.;
	
	int numj = 0;
	int numt = 0;
	 
	cout << numentrs << endl;
	
	//thetree.SetBranchAddress("numJets", &numj);
	//thetree.SetBranchAddress("numTags", &numt);
	
	thetree.SetBranchAddress("wgt", &thewgt);
	
	//thetree.SetBranchAddress("pt_all_jets_over_E_all_jets", &thevar);		//<-
	//thetree.SetBranchAddress("sphericity", &thevar);		//<-
	//thetree.SetBranchAddress("avg_dr_tagged_jets", &thevar);
	//thetree.SetBranchAddress("best_higgs_mass", &thevar);
	//thetree.SetBranchAddress("median_bb_mass", &thevar);
	//thetree.SetBranchAddress("dEta_fn", &thevar);
	//thetree.SetBranchAddress("dRbb", &thevar);
	//thetree.SetBranchAddress("all_sum_pt_with_met", &thevar);
	//thetree.SetBranchAddress("third_highest_btag", &thevar);
	//thetree.SetBranchAddress("second_highest_btag", &thevar);
	
        //thetree.SetBranchAddress("M3", &thevar);
	
        for (int i=0; i<numentrs; i++)
	{
		thetree.GetEntry(i);
		
		if (!((numj==4)&&(numt==3))) continue;					//<-
	
		plot->Fill(thevar,thewgt);
		//if (thevar>499.9) plot->Fill(499,thewgt);
		//else plot->Fill(thevar,thewgt);
	}
	
	
	
}
void MakeGoodPlot::make_simple_plot_mytrees(TString theshift,int drawaxes)
{
	
	TChain tth("tree_of_knowledge");
	TChain ttjets("tree_of_knowledge");
	
	tth.Add("ttH_temp_tree_v25_6j4t_with_pseudoexp_vars_all-30-are-same-for-ttH__with_corrvars_" + theshift + "_.root");
	ttjets.Add("tt*_temp_tree_v25_6j4t_with_pseudoexp_vars_allttjets_100pctcorr__with_corrvars_" + theshift + ".root");
	
	int tth_events = tth.GetEntries();
	int ttjets_events = ttjets.GetEntries();
	
	TH1F *plot_tth[11];
	TH1F *plot_ttjets[11];
	
	for (int gah=0; gah<11; gah++)
	{
		TString stupidint = int2ss(gah);
		plot_tth[gah] = new TH1F("plot1"+stupidint,"",100,-10,10);
		plot_ttjets[gah] = new TH1F("plot2"+stupidint,"",100,-10,10);
	}
	
	
	double tthvar[11] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
	double ttjetsvar[11] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
	
	
	tth.SetBranchAddress("pseudoexp_var34",&tthvar[0]);
	ttjets.SetBranchAddress("pseudoexp_var34",&ttjetsvar[0]);
	tth.SetBranchAddress("pseudoexp_var35",&tthvar[1]);
	ttjets.SetBranchAddress("pseudoexp_var35",&ttjetsvar[1]);
	tth.SetBranchAddress("pseudoexp_var36",&tthvar[2]);
	ttjets.SetBranchAddress("pseudoexp_var36",&ttjetsvar[2]);
	tth.SetBranchAddress("pseudoexp_var37",&tthvar[3]);
	ttjets.SetBranchAddress("pseudoexp_var37",&ttjetsvar[3]);
	tth.SetBranchAddress("pseudoexp_var38",&tthvar[4]);
	ttjets.SetBranchAddress("pseudoexp_var38",&ttjetsvar[4]);
	tth.SetBranchAddress("pseudoexp_var39",&tthvar[5]);
	ttjets.SetBranchAddress("pseudoexp_var39",&ttjetsvar[5]);
	tth.SetBranchAddress("pseudoexp_var40",&tthvar[6]);
	ttjets.SetBranchAddress("pseudoexp_var40",&ttjetsvar[6]);
	tth.SetBranchAddress("pseudoexp_var41",&tthvar[7]);
	ttjets.SetBranchAddress("pseudoexp_var41",&ttjetsvar[7]);
	tth.SetBranchAddress("pseudoexp_var42",&tthvar[8]);
	ttjets.SetBranchAddress("pseudoexp_var42",&ttjetsvar[8]);
	tth.SetBranchAddress("pseudoexp_var43",&tthvar[9]);
	ttjets.SetBranchAddress("pseudoexp_var43",&ttjetsvar[9]);
	tth.SetBranchAddress("pseudoexp_var44",&tthvar[10]);
	ttjets.SetBranchAddress("pseudoexp_var44",&ttjetsvar[10]);
	
	
	
	
	
	for (int isttjets=0; isttjets<2; isttjets++)
	{
		int entries;
		
		if (!isttjets) entries = tth_events;
		if (isttjets) entries = ttjets_events;
		
		for (int i=0; i<entries; i++)
		{
			if (!isttjets) tth.GetEntry(i);
			if (isttjets) ttjets.GetEntry(i);
			
			for (int j=0; j<11; j++)
			{
				if (!isttjets) plot_tth[j]->Fill(tthvar[j]);
				if (isttjets) plot_ttjets[j]->Fill(ttjetsvar[j]);
			}
		}
	}
	
	//plot_tth->SetLineColor(1);
	//plot_ttjets->SetLineColor(2);
	//plot_tth->DrawNormalized();
	//plot_ttjets->DrawNormalized("same");
	
	//get_roc_curve(plot_tth,plot_ttjets,0);
	
	
	
	TH1F *finalplt = new TH1F("asdf_"+theshift,"",11,-0.05,1.05);
	
	for (int i=0; i<11; i++)
	{
		get_roc_curve(plot_ttjets[i],plot_tth[i],i);	
		double rocint = roc_curve[i]->Integral();	
		cout << rocint+0.5 << endl;
		finalplt->Fill(0.1*i,rocint+0.5);
	}
	
/*	TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);
	
	leg->SetFillColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.035);
	
	
	leg->AddEntry(,sample_names[samp_int],"l");  */
	
	finalplt->SetStats(0);
	
	if (drawaxes)finalplt->Draw();
	else finalplt->Draw("same");
}
void MakeGoodPlot::draw_ROC_curves(std::vector<int> samps, int which_one_is_the_signal_sample)
{
	
	
	int numsamples = samps.size();
	
	TH1F *sample_hist[numsamples];
//	TGraph *roc_curve[10];
	
	load_samples(samps);
	
	//TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);  /// (0.3,0.77,0.7,0.88)
	//TLegend* leg = new TLegend(0.14,0.75,0.94,0.89); // Darren format
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.035);
	leg->SetNColumns(5);
	
	int sig_hist_index = 1;
	
	
	for (int i=0; i<numsamples; i++)
	{
		
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
		
		sample_hist[i] = new TH1F("BDT response, 5j4t " + sample_names[samp_int],"",100,-1.0,1.0);
		
		get_hist_of_tiered_MVA_response_for_one_sample_5j4t(sample_hist[i],samp_int);
		//get_hist_MVA_response_for_one_sample_643203(sample_hist[i],samp_int);
		
		if (samp_int==which_one_is_the_signal_sample) sig_hist_index = i;

	}
	
	int j = 0;
	
	TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660);
	can1->SetGridx();
	can1->SetGridy();
	
	for (int i=0; (/*(i!=sig_hist_index)&&*/(i<numsamples)); i++)
	{
		if (i==sig_hist_index) continue;
		
		cout << i << j << endl;
		
		int samp_int = samps[i];
		
		cout << "blah1" << endl;
		
//		double eff_S[500];
//		double bck_R[500];
//		int n_pts;
		
		cout << "blah2" << endl;
		
		get_roc_curve(sample_hist[sig_hist_index], sample_hist[i], j); // n_pts, eff_S, bck_R);
		
		cout << "blah3" << endl;
		
//		roc_curve[j] = new TGraph(n_pts,eff_S,bck_R);
		
		cout << "blah4" << endl;
		
		
		//roc_curve[j]->SetTitle(title);
		roc_curve[j]->GetXaxis()->SetTitle("Signal Eff");
		roc_curve[j]->GetXaxis()->SetTitleColor(kBlack);
		roc_curve[j]->GetYaxis()->SetTitle("Bkg Rejection");
		roc_curve[j]->GetYaxis()->SetTitleColor(kBlack);    
		
		if (samp_int<4) roc_curve[j]->SetLineColor(1+samp_int);
		if (samp_int>=4) roc_curve[j]->SetLineColor(2+samp_int);
		
		roc_curve[j]->SetTitle("");
		roc_curve[j]->SetLineWidth(2);
		leg->AddEntry(roc_curve[j],sample_names[samp_int],"l");

		
		

		if (j==0) roc_curve[j]->Draw("AC");
		if (j!=0) roc_curve[j]->Draw("C");
		
		j++;
		
		cout << j << endl;
	
	}
	
	leg->SetFillColor(0);
	leg->Draw();
	

}

void MakeGoodPlot::get_hist_MVA_response_for_one_sample_643203(TH1 *plot, int sample_number)
{
	
    return;
}


void MakeGoodPlot::get_hist_of_tiered_MVA_response_for_one_sample_5j4t(TH1 *plot, int sample_number)
{
	
    return;
	
}

void MakeGoodPlot::get_hist_of_tiered_MVA_response_for_one_sample_6j4t(TH1 *plot, int sample_number)
{
	
    return;
	
}

void MakeGoodPlot::get_roc_curve(TH1F *sig, TH1F *bkgd, int roc_curve_index) //int &npts, double (&effS)[500], double (&bckR)[500])
{
		
	int npts = 0;

	TH1F *intHist1 = (TH1F*)sig->Clone();
	TH1F *InvIntHist1 = (TH1F*)sig->Clone();
	TH1F *hist1N = (TH1F*)sig->Clone();

	TH1F *intHist2 = (TH1F*)bkgd->Clone();
	TH1F *InvIntHist2 = (TH1F*)bkgd->Clone();
	TH1F *hist2N = (TH1F*)bkgd->Clone();
		
	intHist1->Scale(1./intHist1->Integral());
	InvIntHist1->Scale(1./InvIntHist1->Integral());
	hist1N->Scale(1./hist1N->Integral());

	intHist2->Scale(1./intHist2->Integral());
	InvIntHist2->Scale(1./InvIntHist2->Integral());
	hist2N->Scale(1./hist2N->Integral());

	intHist1->Reset();
	intHist1->SetNameTitle("intHist1","Integral");

	InvIntHist1->Reset();
	InvIntHist1->SetNameTitle("InvIntHist1","InvIntegral");
  
	int size = hist1N->GetNbinsX()+1;
	
	double effS[size];
	double bckR[size];
	// double effS[500];
	// double bckR[500];

	// Now Loop over the histogram and do bin by bin.
	float intval = 0.0;
	for(int i=0; i<(hist1N->GetNbinsX())+1; i++)
	{
		intval = intval+(hist1N->GetBinContent(i));
		//if(prtLvl >= 2) printf(" Bin %i Int %f \n",i,intval);
		intHist1->SetBinContent(i,intval);	    
		InvIntHist1->SetBinContent(i,1.-intval);
		//	  	effS[i] = 1.0 - intval;
	  	effS[i] = intval;
	  	npts++;
	}

	intHist2->Reset();
	intHist2->SetNameTitle("intHist2","Integral");
	
	InvIntHist2->Reset();
	InvIntHist2->SetNameTitle("InvIntHist2","InvIntegral");


	// Now Loop over the histogram and do bin by bin.
	intval = 0.0;
	for(int j=0; j<(hist2N->GetNbinsX())+1; j++)
	{
		intval = intval+(hist2N->GetBinContent(j));
		//if(prtLvl >= 2) printf(" Bin %i Int %f \n",j,intval);
		intHist2->SetBinContent(j,intval);
		InvIntHist2->SetBinContent(j,1.-intval);	
		//		bckR[j] = intval;    
		bckR[j] = 1.0 - intval;    
	}
	
	
	roc_curve[roc_curve_index] = new TGraph(npts,effS,bckR);  	// <-- usual plot
	//	roc_curve[roc_curve_index] = new TGraph(npts,bckR,effS);  	// <-- for use with "->Eval(..." at a given background rejection

}

void MakeGoodPlot::get_hist_of_simple_variable(TH1 *plot, int sample_number, TH1 *plot2, TH1 *plot3)
{
	
	//ch[sample_number]->SetBranchAddress( "preselected_leptons", &preselected_leptons_intree );
	ch[sample_number]->SetBranchAddress( "pruned_genParticles", &pruned_genParticles_intree );
        ch[sample_number]->SetBranchAddress( "wgt", &wgt_intree );
        
	cout << sample_number << endl;
	cout << ch[sample_number]->GetEntries() << endl;
	
	for (Int_t i=0;i<ch[sample_number]->GetEntries();i++)
	{
		ch[sample_number]->GetEntry(i);
				
		
		
		weight = wgt_intree;
				
		
		//pt_all_jets_over_E_all_jets = pt_E_ratio_jets(eve1->jet_vect_TLV_[syst]);
		////plot->Fill(pt_all_jets_over_E_all_jets,weight);
		
                int gpsize = (*pruned_genParticles_intree).size();
                
                for (int j=0; j<gpsize; j++)
                {
                    int chil0 = (int)(*pruned_genParticles_intree)[j].child0;
                    //if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil0<gpsize)) plot->Fill( (*pruned_genParticles_intree)[(*pruned_genParticles_intree)[j].child0].pdgID, weight);
                    if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil0<gpsize)) plot->Fill( (*pruned_genParticles_intree)[j].status, weight);
                    
                    
                    //chil0 = gpsize - chil0;
                    //if ((*pruned_genParticles_intree)[j].pdgID==25) plot->Fill( chil0, weight );
                }
                
                
                
                
                
                ////////////////////////
                // vdouble lepmvas;
//                 int lepsize = (*preselected_leptons_intree).size();
//                 
//                 for (int j=0; j<lepsize; j++)
//                 {
//                     lepmvas.push_back((*preselected_leptons_intree)[j].lepMVA);
//                 }
//                 
//                 //sort(lepmvas.begin(), lepmvas.end());
//                 //if (lepsize>2 && lepmvas[lepsize-1]>0.8 && lepmvas[lepsize-2]>0.8) plot->Fill(lepmvas[lepsize-3],weight);
//                 //if (lepsize>2 && lepmvas[0]>0.8 && lepmvas[1]>0.8) plot->Fill(lepmvas[2],weight);
//                 if (lepsize>0) plot->Fill(lepmvas[0],weight);
                ////////////////////////
                
                
                //if ((*preselected_leptons_intree).size()) plot->Fill((*preselected_leptons_intree)[0].obj.Pt(),weight);
                
		
		//plot->Fill(eve1->higgsDecayType_);
		
		/*
		vecTLorentzVector thejets;
		convert_jets_to_TLVs(eve1->jet_vect_TLV_[syst],thejets);
		
		double firsthighest = -999.;
		double secondhighest = -9999.;
		
		int firsthighest_index = 0;
		int secondhighest_index = 0;
		
		for (int thejetit=0; thejetit< thejets.size();thejetit++)
		{
			if ((eve1->jet_CSV_[syst][thejetit]<=1)&&(eve1->jet_CSV_[syst][thejetit]>firsthighest))
			{
				secondhighest = firsthighest;
				secondhighest_index = firsthighest_index;
				
				firsthighest = eve1->jet_CSV_[syst][thejetit];
				firsthighest_index = thejetit;
			}
			else if ((eve1->jet_CSV_[syst][thejetit]<=1)&&(eve1->jet_CSV_[syst][thejetit]>secondhighest))
			{
				secondhighest = eve1->jet_CSV_[syst][thejetit];
				secondhighest_index = thejetit;
			}
		}
		
		for (int thejetit=0; thejetit< thejets.size();thejetit++)
		{
			
			
			if ((eve1->jet_CSV_[syst][thejetit]>=0)&&(eve1->jet_CSV_[syst][thejetit]<=1)&&(thejetit!=firsthighest_index)&&(thejetit!=secondhighest_index))
			{
				if (abs(eve1->jet_genId_[syst][thejetit])==5) plot->Fill(eve1->jet_CSV_[syst][thejetit],weight);
				else if (abs(eve1->jet_genId_[syst][thejetit])==4) plot2->Fill(eve1->jet_CSV_[syst][thejetit],weight);
				else plot3->Fill(eve1->jet_CSV_[syst][thejetit],weight);
			}
				
			else if ((thejetit!=firsthighest_index)&&(thejetit!=secondhighest_index))
			{
				if (abs(eve1->jet_genId_[syst][thejetit])==5) plot->Fill(-1,weight);
				else if (abs(eve1->jet_genId_[syst][thejetit])==4) plot2->Fill(-1,weight);
				else plot3->Fill(-1,weight);
			}	
			
			
			//if (abs(eve1->jet_genParentId_[syst][thejetit])==25) plot->Fill(eve1->jet_genId_[syst][thejetit]);
			//if (abs(eve1->jet_genParentId_[syst][thejetit])==25) plot->Fill(eve1->higgsDecayType_);
			

				
		}
		*/

		/*
		vecTLorentzVector btag_vect;
		vdouble theCSV = eve1->jet_CSV_[syst];
		vect_of_tagged_TLVs(eve1->jet_vect_TLV_[syst], theCSV, btag_vect); // CSV L

		int size = btag_vect.size();
		
		if (size>=4) // CSV L btags
		{
			double avgcsv = 0.;
			for (int i=0; i<theCSV.size(); i++) if (theCSV[i]>=0.244) avgcsv += theCSV[i];
			avgcsv = avgcsv/size;
			plot->Fill(avgcsv,weight);
		}
		*/
		
		
		
		/*
		TRandom3 random_normal_dist;							
		random_normal_dist.SetSeed(0);							
		double random_gaussian_mean_zero_sigma_1 = random_normal_dist.Gaus();				
		if (sample_number!=1) random_gaussian_mean_zero_sigma_1 += 4.0;
		
		plot->Fill(random_gaussian_mean_zero_sigma_1,weight);
		*/
	}
		
		//if( insample==2403 && lepSel!=0 && evt==90273686 ) continue;


}

void MakeGoodPlot::make_eff_vs_var_separation_plot(std::vector<int> samps)
{
	
    return;
	
}

void MakeGoodPlot::compareplots(std::vector<int> samps, std::vector<TString> tempfiles)
{
  
  // compares multiple hists that should already be saved to some temp files //
  
  vector<TFile*> files;
  
  for (int itempfile=0; itempfile<tempfiles.size(); itempfile++)
  {
    files.push_back(new TFile(tempfiles[itempfile]));   
  }


  vector<TString> names;
  
  for (int iName=0; iName<samps.size(); iName++)
  {
    TString iNametemp = sample_names[samps[iName]];
    names.push_back(iNametemp);
  }

  TFile *vergleich = new TFile("comparison_output.root","RECREATE");


  // Show no statistics box
  gStyle->SetOptStat(0);

  //TH1::SetDefaultSumw2();

  // Main program part
  TIter nextkey(files.at(0)->GetListOfKeys());
  TKey *key;
  bool first=true;
  TCanvas* c = new TCanvas();
  c->Print("comparisonPlots.pdf[");

  // Save also as pictures
  int pictureNumber = 0;

  int run = 0;
  
  while ( (key = (TKey*)nextkey()) )
  {
    pictureNumber++;
    TString pictureName = TString::Format("%d.png",pictureNumber);

    vector<TH1F*> histos;
    histos.push_back((TH1F*)key->ReadObj());
    histos[0]->SetName(key->GetName());
    
    for(size_t i=1;i<files.size();i++)
    {
      histos.push_back((TH1F*)files.at(i)->Get(histos.at(0)->GetName()));
	histos[i]->SetName(key->GetName());
    }
    
    c->SetName(key->GetName());
		       
    for(size_t i=0;i<histos.size();i++)
    {
      if(i == 0){
	histos.at(i)->SetLineColor(kBlack);
      }
      if(i == 1){
	histos.at(i)->SetLineColor(kRed);
      }
      if(i == 2){
	histos.at(i)->SetLineColor(kBlue);
      }
      if(i == 3){
	histos.at(i)->SetLineColor(kGreen+2);
      }
      if(i == 4){
	histos.at(i)->SetLineColor(kMagenta-7);
      }
      if(i == 5){
	histos.at(i)->SetLineColor(kOrange+7);
      }
    }
    
    for(size_t i=0;i<histos.size();i++)
    {
      //histos.at(i)->Sumw2();
      histos.at(i)->Scale(1./histos.at(i)->Integral(),"width");
    }

    // Set axis title
    histos.at(0)->GetYaxis()->SetTitle("Normalized units"); 
    std::string const histogramName = histos.at(0)->GetName();
    histos.at(0)->GetXaxis()->SetLabelSize(0.06);
    histos.at(0)->GetXaxis()->SetLabelOffset(0.006);
    histos.at(0)->GetYaxis()->SetLabelSize(0.06);
    histos.at(0)->GetYaxis()->SetLabelOffset(0.006);
    histos.at(0)->GetXaxis()->SetTitleSize(0.06);
    histos.at(0)->GetXaxis()->SetTitleOffset(1.1);
    histos.at(0)->GetYaxis()->SetTitleSize(0.06);
    histos.at(0)->GetYaxis()->SetTitleOffset(1.08);


    // c->SetName(histos.at(0)->GetName())
    //histos.at(0)->GetXaxis()->SetTitle(histos.at(0)->GetName());
    //histos.at(0)->GetXaxis()->SetTitle(histos.at(0)->GetXaxis()->GetTitle());

    run = run+1;
    if(run == (3*8))
    {
        run = 0;
    }
    // If only two histograms per plot make a ratio plot
    if(histos.size() == 2)
    {

        //create main pad  

        TPad *mainPad = new TPad("","",0.0,0.3,1.0,1.0);
        mainPad->SetNumber(1);
        mainPad->SetBottomMargin(0.0);
        mainPad->SetRightMargin(0.04);
        mainPad->SetLeftMargin(0.13);
        mainPad->SetGridx(1);
        mainPad->SetGridy(1);
        mainPad->SetLogy(1);
        mainPad->Draw();

        //create ratio pad                                                                                                                                                           
        TPad *ratioPad = new TPad("","",0.0,0.0,1.0,0.3);
        ratioPad->SetTopMargin(0.0);
        ratioPad->SetBottomMargin(0.4);
        ratioPad->SetLeftMargin(0.13);                                                                                                                                             
        ratioPad->SetRightMargin(0.04);
        gStyle->SetOptTitle(0);
        ratioPad->SetFillColor(0);
        ratioPad->SetNumber(2);
        ratioPad->SetGridy();                                                                                                                                                      
        ratioPad->Draw();

        // Draw both histograms first
        c->cd(1);
        //c->mainPad()->SetLogy(1);  // <<<<------- set log scale
        histos.at(0)->Draw("histo E");
        histos.at(1)->Draw("histo same E");

        // Show legend and statistical tests in first pad
        for(size_t i=0;i<histos.size()-1;i=i+2)
        {

          double ksresult = histos.at(i)->KolmogorovTest(histos.at(i+1));
          ksresult=floor(ksresult*1000+0.5)/1000;
          double chi2result =histos.at(i)->Chi2Test(histos.at(i+1),"WW");
          chi2result=floor(chi2result*1000+0.5)/1000;

          stringstream ss;
          ss << "     KS: " <<std::setprecision(3) << ksresult << " chi2: " <<std::setprecision(3) << chi2result; // << " Private Work"; 
          //const char * notmych = & ss.str().c_str();
          TLatex * ks = new TLatex(0.1, 0.9-0.03*i, ss.str().c_str());
          ks->SetTextColor(histos.at(i)->GetLineColor());
          ks->SetNDC();
          ks->Draw("");      

        }

        TLegend* l = new TLegend(0.55,0.9,0.69,0.99);
        // Options for legend
        l->SetBorderSize(0);
        l->SetLineStyle(0);
        l->SetTextSize(0.049);
        l->SetFillStyle(0);
        for(size_t i=0;i<names.size();i++)
        {
          l->AddEntry(histos.at(i),names.at(i),"L");
        }
        l->Draw("same");

        // Clone histograms and draw ratio plot
        c->cd(2);
         TH1F* ratioHisto = (TH1F*)histos.at(0)->Clone();
        ratioHisto->Add(histos.at(1),-1);
        ratioHisto->Divide(histos.at(1));
        ratioHisto->SetLineColor(kBlue);
        ratioHisto->SetStats(false);
        ratioHisto->GetYaxis()->SetTitle("Ratio #frac{new-old}{old}");
        // Same Size like in histogram
        ratioHisto->SetLabelSize(histos.at(0)->GetLabelSize() * 0.7 / 0.3);
        ratioHisto->SetTitleOffset((histos.at(0)->GetTitleOffset("Y") * 0.3 / 0.7), "Y");
        ratioHisto->SetTitleSize((histos.at(0)->GetTitleSize("Y") * 0.7 / 0.3), "Y");
        ratioHisto->SetTitleOffset((histos.at(0)->GetTitleOffset("X")), "X");
        ratioHisto->SetTitleSize((histos.at(0)->GetTitleSize("X") * 0.7 / 0.3), "X");
        // Use nicer range
        ratioHisto->GetYaxis()->SetRangeUser(-1.5, 1.5);
        ratioHisto->GetYaxis()->SetNdivisions(503);
        ratioHisto->GetYaxis()->SetLabelSize(0.06 * 0.7 / 0.3);
        ratioHisto->Draw();
    }
    else
    {

        histos.at(0)->Draw("histo E");
        for(size_t i=0;i<histos.size();i++)
        {
          histos.at(i)->Draw("histo same E");
        }


        for(size_t i=0;i<histos.size()-1;i=i+2)
        {

          double ksresult = histos.at(i)->KolmogorovTest(histos.at(i+1));
          ksresult=floor(ksresult*1000+0.5)/1000;
          double chi2result =histos.at(i)->Chi2Test(histos.at(i+1),"WW");
          chi2result=floor(chi2result*1000+0.5)/1000;

          stringstream ss;
          ss << "KS: " <<std::setprecision(3) << ksresult << " chi2: " <<std::setprecision(3) << chi2result; 
          //const char notmych = ss.str().c_str();
          TText * ks = new TText(0.1, 0.9-0.03*i, ss.str().c_str());
          ks->SetTextColor(histos.at(i)->GetLineColor());
          ks->SetNDC();
          ks->Draw("");      

        }

        TLegend* l = new TLegend(0.65,0.5,0.9,0.7);
        l->SetBorderSize(0);
        l->SetLineStyle(0);
        //    l->SetTextSize(0.039);
        l->SetFillStyle(0);
        for(size_t i=0;i<names.size();i++)
        {
          l->AddEntry(histos.at(i),names.at(i),"L");
        }
        l->Draw("same");
    }

    c->Print("comparisonPlots.pdf");
    c->SaveAs(pictureName);
    vergleich->WriteTObject(c);

  }
  
  c->Print("comparisonPlots.pdf]");

}

void MakeGoodPlot::print_geninfo_table(std::vector<int> samps)
{
	load_samples(samps);
	int numsamps = samps.size();
	
	struct event_geninfo
	{
		int both_higgs;
		int both_higgs_tagged;
		int both_higgs_one_tagged;
		int both_higgs_both_untagged;
		int one_higgs_not_tagged;
		int one_higgs_tagged;

		int both_W_jets;
		int both_W_jets_tagged;
		int both_W_jets_one_tagged;
		int both_W_jets_both_untagged;
		int one_W_jets_not_tagged;
		int one_W_jets_tagged;

		int both_bsfromtop;
		int both_bsfromtop_tagged;
		int both_bsfromtop_one_tagged;
		int both_bsfromtop_both_untagged;
		int one_bsfromtop_not_tagged;
		int one_bsfromtop_tagged;

		// just both higgs jets present (no tag req)
		int both_higgs_both_W_jets;
		int both_higgs_both_W_jets_tagged;
		int both_higgs_both_W_jets_one_tagged;
		int both_higgs_both_W_jets_both_untagged;
		int both_higgs_one_W_jets_not_tagged;
		int both_higgs_one_W_jets_tagged;	             
		int both_higgs_both_bsfromtop;
		int both_higgs_both_bsfromtop_tagged;
		int both_higgs_both_bsfromtop_one_tagged;
		int both_higgs_both_bsfromtop_both_untagged;
		int both_higgs_one_bsfromtop_not_tagged;
		int both_higgs_one_bsfromtop_tagged;	

		// both higgs jets present (tag req)
		int both_higgs_tagged_both_W_jets;
		int both_higgs_tagged_both_W_jets_tagged;
		int both_higgs_tagged_both_W_jets_one_tagged;
		int both_higgs_tagged_both_W_jets_both_untagged;
		int both_higgs_tagged_one_W_jets_not_tagged;
		int both_higgs_tagged_one_W_jets_tagged;  	 	
		int both_higgs_tagged_both_bsfromtop;
		int both_higgs_tagged_both_bsfromtop_tagged;
		int both_higgs_tagged_both_bsfromtop_one_tagged;	 	
		int both_higgs_tagged_both_bsfromtop_both_untagged;
		int both_higgs_tagged_one_bsfromtop_not_tagged;
		int both_higgs_tagged_one_bsfromtop_tagged;

		// tops	
		int both_W_jets_both_bsfromtop;
		int both_W_jets_both_bsfromtop_tagged;
		int both_W_jets_both_bsfromtop_one_tagged;
		int both_W_jets_both_bsfromtop_both_untagged;
		int both_W_jets_one_bsfromtop_not_tagged;
		int both_W_jets_one_bsfromtop_tagged;

		int both_W_jets_tagged_both_bsfromtop;
		int both_W_jets_tagged_both_bsfromtop_tagged;
		int both_W_jets_tagged_both_bsfromtop_one_tagged;
		int both_W_jets_tagged_both_bsfromtop_both_untagged;
		int both_W_jets_tagged_one_bsfromtop_not_tagged;
		int both_W_jets_tagged_one_bsfromtop_tagged;

		int both_W_jets_one_tagged_both_bsfromtop;
		int both_W_jets_one_tagged_both_bsfromtop_tagged;
		int both_W_jets_one_tagged_both_bsfromtop_one_tagged;
		int both_W_jets_one_tagged_both_bsfromtop_both_untagged;
		int both_W_jets_one_tagged_one_bsfromtop_not_tagged;
		int both_W_jets_one_tagged_one_bsfromtop_tagged;

		int both_W_jets_both_untagged_both_bsfromtop;
		int both_W_jets_both_untagged_both_bsfromtop_tagged;	// <--
		int both_W_jets_both_untagged_both_bsfromtop_one_tagged;
		int both_W_jets_both_untagged_both_bsfromtop_both_untagged;
		int both_W_jets_both_untagged_one_bsfromtop_not_tagged;
		int both_W_jets_both_untagged_one_bsfromtop_tagged;

		int one_W_jets_not_tagged_both_bsfromtop;
		int one_W_jets_not_tagged_both_bsfromtop_tagged;
		int one_W_jets_not_tagged_both_bsfromtop_one_tagged;
		int one_W_jets_not_tagged_both_bsfromtop_both_untagged;
		int one_W_jets_not_tagged_one_bsfromtop_not_tagged;
		int one_W_jets_not_tagged_one_bsfromtop_tagged;

		int one_W_jets_tagged_both_bsfromtop;
		int one_W_jets_tagged_both_bsfromtop_tagged;
		int one_W_jets_tagged_both_bsfromtop_one_tagged;
		int one_W_jets_tagged_both_bsfromtop_both_untagged;
		int one_W_jets_tagged_one_bsfromtop_not_tagged;
		int one_W_jets_tagged_one_bsfromtop_tagged;
		
		// tops (both higgs present)
		// ...
		// tops (both tagged higgs present)
		// ...
		
		int nothing;
		int num_events;
	};

	
	std::vector<event_geninfo> event_geninfo_vect;
	

			 
	for (int samp_i=0; samp_i<numsamps; samp_i++)
	{
		int sample_number = samps[samp_i];
		
		//ch[sample_number]->SetBranchAddress( "eve.", &eve1 );

		event_geninfo sample_event_geninfo = {0};
		
		int numevents = 0;
		
		for (Int_t i=0;i<ch[sample_number]->GetEntries();i++)
		{
			ch[sample_number]->GetEntry(i);
// 			bool is_sel_cat = (eve1->numJets_float_[syst]>=6&&eve1->numTags_float_[syst]>=4);
// 			if (!is_sel_cat) continue;
// 
// 			// single ele data
// 			if (sample_number==10)
// 			{
// 				if (!eve1->leptonType_==0) continue;
// 				if (!(eve1->passElectronTrigger_ && eve1->matchSingleElectronTrigger_)) continue;
// 			}
// 
// 			// single mu data
// 			if (sample_number==0)
// 			{
// 				if (!eve1->leptonType_==1) continue;
// 				if (!(eve1->passMuonTrigger_ && eve1->matchSingleMuTrigger_)) continue;
// 			}
// 
// 			// mc
// 			if (sample_number!=0&&sample_number!=10)
// 			{
// 				if (eve1->leptonType_==0) if (!(eve1->passElectronTrigger_ && eve1->matchSingleElectronTrigger_)) continue;
// 				if (eve1->leptonType_==1) if (!(eve1->passMuonTrigger_ && eve1->matchSingleMuTrigger_)) continue;
// 			}
// 
// 			if (eve1->third_jet_pt_[syst]<40.) continue;
// 			if (eve1->IsTauTauLeptonEvent_[syst]==1) continue;
// 			if (sample_number==7&&eve1->evt_==90273686) continue;
			
			numevents++;
			
			int numjets; // = eve1->jet_genId_[syst].size();
			
			vint genIDs; // = eve1->jet_genId_[syst];
			vint genParentIDs; // = eve1->jet_genParentId_[syst];
			vdouble theCSVs; // = eve1->jet_CSV_[syst];
			
			int numWjets = 0;
			int numWjets_tagged = 0;
			int numBsfromtop = 0;
			int numBsfromtop_tagged = 0;
			int numHiggsjets = 0;
			int numHiggsjets_tagged = 0;
			
			for (int jet=0; jet<numjets; jet++)
			{
				if (abs(genParentIDs[jet])==24) numWjets++;
				if (abs(genParentIDs[jet])==6&&abs(genIDs[jet])==5) numBsfromtop++;
				if (abs(genParentIDs[jet])==25) numHiggsjets++;
				if (abs(genParentIDs[jet])==24&&theCSVs[jet]>=0.679) numWjets_tagged++;
				if ( (abs(genParentIDs[jet])==6)&&(abs(genIDs[jet])==5)&&(theCSVs[jet]>=0.679) ) numBsfromtop_tagged++;
				if (abs(genParentIDs[jet])==25&&theCSVs[jet]>=0.679) numHiggsjets_tagged++;
			}
			
			if (numHiggsjets==2) sample_event_geninfo.both_higgs++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2) sample_event_geninfo.both_higgs_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==1) sample_event_geninfo.both_higgs_one_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==0) sample_event_geninfo.both_higgs_both_untagged++;
			if (numHiggsjets==1&&numHiggsjets_tagged==0) sample_event_geninfo.one_higgs_not_tagged++;
			if (numHiggsjets==1&&numHiggsjets_tagged==1) sample_event_geninfo.one_higgs_tagged++;

			if (numWjets==2) sample_event_geninfo.both_W_jets++;
			if (numWjets==2&&numWjets_tagged==2) sample_event_geninfo.both_W_jets_tagged++;
			if (numWjets==2&&numWjets_tagged==1) sample_event_geninfo.both_W_jets_one_tagged++;
			if (numWjets==2&&numWjets_tagged==0) sample_event_geninfo.both_W_jets_both_untagged++;
			if (numWjets==1&&numWjets_tagged==0) sample_event_geninfo.one_W_jets_not_tagged++;
			if (numWjets==1&&numWjets_tagged==1) sample_event_geninfo.one_W_jets_tagged++;

			if (numBsfromtop==2) sample_event_geninfo.both_bsfromtop++;
			if (numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_bsfromtop_tagged++;
			if (numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_bsfromtop_one_tagged++;
			if (numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_bsfromtop_both_untagged++;
			if (numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.one_bsfromtop_not_tagged++;
			if (numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.one_bsfromtop_tagged++;

			if (numHiggsjets==2&&numWjets==2) sample_event_geninfo.both_higgs_both_W_jets++;
			if (numHiggsjets==2&&numWjets==2&&numWjets_tagged==2) sample_event_geninfo.both_higgs_both_W_jets_tagged++;
			if (numHiggsjets==2&&numWjets==2&&numWjets_tagged==1) sample_event_geninfo.both_higgs_both_W_jets_one_tagged++;
			if (numHiggsjets==2&&numWjets==2&&numWjets_tagged==0) sample_event_geninfo.both_higgs_both_W_jets_both_untagged++;
			if (numHiggsjets==2&&numWjets==1&&numWjets_tagged==0) sample_event_geninfo.both_higgs_one_W_jets_not_tagged++;
			if (numHiggsjets==2&&numWjets==1&&numWjets_tagged==1) sample_event_geninfo.both_higgs_one_W_jets_tagged++;			
			if (numHiggsjets==2&&numBsfromtop==2) sample_event_geninfo.both_higgs_both_bsfromtop++;
			if (numHiggsjets==2&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_higgs_both_bsfromtop_tagged++;
			if (numHiggsjets==2&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_higgs_both_bsfromtop_one_tagged++;
			if (numHiggsjets==2&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_higgs_both_bsfromtop_both_untagged++;
			if (numHiggsjets==2&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_higgs_one_bsfromtop_not_tagged++;
			if (numHiggsjets==2&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_higgs_one_bsfromtop_tagged++;	

			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==2) sample_event_geninfo.both_higgs_tagged_both_W_jets++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==2&&numWjets_tagged==2) sample_event_geninfo.both_higgs_tagged_both_W_jets_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==2&&numWjets_tagged==1) sample_event_geninfo.both_higgs_tagged_both_W_jets_one_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==2&&numWjets_tagged==0) sample_event_geninfo.both_higgs_tagged_both_W_jets_both_untagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==1&&numWjets_tagged==0) sample_event_geninfo.both_higgs_tagged_one_W_jets_not_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==1&&numWjets_tagged==1) sample_event_geninfo.both_higgs_tagged_one_W_jets_tagged++;		   
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==2) sample_event_geninfo.both_higgs_tagged_both_bsfromtop++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_higgs_tagged_both_bsfromtop_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_higgs_tagged_both_bsfromtop_one_tagged++;		   
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_higgs_tagged_both_bsfromtop_both_untagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_higgs_tagged_one_bsfromtop_not_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_higgs_tagged_one_bsfromtop_tagged++;

			if (numWjets==2&&numBsfromtop==2) sample_event_geninfo.both_W_jets_both_bsfromtop++;
			if (numWjets==2&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_W_jets_both_bsfromtop_tagged++;
			if (numWjets==2&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_both_bsfromtop_one_tagged++;
			if (numWjets==2&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_both_bsfromtop_both_untagged++;
			if (numWjets==2&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_one_bsfromtop_not_tagged++;
			if (numWjets==2&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_one_bsfromtop_tagged++;

			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==2) sample_event_geninfo.both_W_jets_tagged_both_bsfromtop++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_W_jets_tagged_both_bsfromtop_tagged++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_tagged_both_bsfromtop_one_tagged++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_tagged_both_bsfromtop_both_untagged++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_tagged_one_bsfromtop_not_tagged++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_tagged_one_bsfromtop_tagged++;

			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==2) sample_event_geninfo.both_W_jets_one_tagged_both_bsfromtop++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_W_jets_one_tagged_both_bsfromtop_tagged++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_one_tagged_both_bsfromtop_one_tagged++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_one_tagged_both_bsfromtop_both_untagged++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_one_tagged_one_bsfromtop_not_tagged++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_one_tagged_one_bsfromtop_tagged++;

			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==2) sample_event_geninfo.both_W_jets_both_untagged_both_bsfromtop++;
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_W_jets_both_untagged_both_bsfromtop_tagged++;  
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_both_untagged_both_bsfromtop_one_tagged++;
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_both_untagged_both_bsfromtop_both_untagged++;
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_both_untagged_one_bsfromtop_not_tagged++;
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_both_untagged_one_bsfromtop_tagged++;

			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==2) sample_event_geninfo.one_W_jets_not_tagged_both_bsfromtop++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.one_W_jets_not_tagged_both_bsfromtop_tagged++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.one_W_jets_not_tagged_both_bsfromtop_one_tagged++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.one_W_jets_not_tagged_both_bsfromtop_both_untagged++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.one_W_jets_not_tagged_one_bsfromtop_not_tagged++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.one_W_jets_not_tagged_one_bsfromtop_tagged++;

			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==2) sample_event_geninfo.one_W_jets_tagged_both_bsfromtop++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.one_W_jets_tagged_both_bsfromtop_tagged++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.one_W_jets_tagged_both_bsfromtop_one_tagged++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.one_W_jets_tagged_both_bsfromtop_both_untagged++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.one_W_jets_tagged_one_bsfromtop_not_tagged++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.one_W_jets_tagged_one_bsfromtop_tagged++;
		
			if ((numWjets+numBsfromtop+numHiggsjets)==0) sample_event_geninfo.nothing++;
		
		}
		
		sample_event_geninfo.num_events = numevents;
		
		//sample_event_geninfo /= numevents;
		
		event_geninfo_vect.push_back(sample_event_geninfo);
	}
			
	// print ...

	printf("\n");

	// percentage version:
	// for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25.1f",(100.0/(float)event_geninfo_vect[sample_number].num_events)*event_geninfo_vect[sample_number].both_higgs);

	
	/*
	printf("%-60s","");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25s",sample_names[samps[sample_number]].c_str());
	*/
	printf("\n");
	printf("\n");
	printf("%-60s","both_higgs");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs);
	printf("\n");
	printf("%-60s","both_higgs_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged);
	printf("\n");
	printf("%-60s","both_higgs_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_untagged);
	printf("\n");
	printf("%-60s","one_higgs_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_higgs_not_tagged);
	printf("\n");
	printf("%-60s","one_higgs_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_higgs_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_W_jets");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets);
	printf("\n");
	printf("%-60s","both_W_jets_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_bsfromtop);
	printf("\n");
	printf("%-60s","both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_bsfromtop_tagged);
	printf("\n");
	printf("\n");

	printf("%-60s","both_higgs_both_W_jets");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_W_jets);
	printf("\n");
	printf("%-60s","both_higgs_both_W_jets_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_W_jets_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_W_jets_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_W_jets_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_W_jets_both_untagged);
	printf("\n");
	printf("%-60s","both_higgs_one_W_jets_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_W_jets_not_tagged);
	printf("\n");
	printf("%-60s","both_higgs_one_W_jets_tagged");			 
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_higgs_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_higgs_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_higgs_one_bsfromtop_tagged");    
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");

	printf("%-60s","both_higgs_tagged_both_W_jets");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_W_jets);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_W_jets_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_W_jets_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_W_jets_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_W_jets_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_W_jets_both_untagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_one_W_jets_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_one_W_jets_not_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_one_W_jets_tagged");		    
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_one_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_bsfromtop_one_tagged");		    
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");

	printf("%-60s","both_W_jets_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_W_jets_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_W_jets_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_both_bsfromtop_tagged");    // <--
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","one_W_jets_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","nothing");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].nothing);
	printf("\n");	
	printf("\n");
	printf("%-60s","total num events");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].num_events);
	printf("\n");	
	printf("\n");
	
	
	
	
	
			
			
}
void MakeGoodPlot::load_samples(std::vector<int> samps)
{
	
	TString eosprfx = "root://eoscms.cern.ch/";
        //TString basedir = "/eos/cms/store/user/gesmith/crabdir/v5/";
        TString oldbasedir = "/eos/cms/store/user/muell149/ttH-leptons_Skims/v3p1/";
        TString basedir = "/eos/cms/store/user/gesmith/crab3dir/";
        //TString eosprfx = "";        
        //TString basedir = "/tmp/gesmith/ttjetstemp/";
        
        
	TString thesample = "";
	TString basedir_plus = "";
	
        basedir = eosprfx + basedir;
        oldbasedir = eosprfx + oldbasedir;
	
	int numsamples = samps.size();
	 
        
        
	for (int i=0; i<numsamples; i++)
	{
//		sample_raw_evts[10];
//		sample_weighted_evts[10];
		
		if (samps[i]==0)
		{
                        // prob. will just be all data ..
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_data_SingleMu_2012ABCD_BEAN_53xOn53x_beanVer2*.root";
// 			ch[0]->Add(thesample);
// 			//cout << thesample << endl;
                                   
		}
		if (samps[i]==1)
		{
			basedir_plus = "test1ttH/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150610_082426/0000/";
                        //thesample = basedir + basedir_plus + "multileptree_2_1_yTv.root";
                        //thesample = thesample + " " + basedir + basedir_plus + "multileptree_7_1_AwJ.root";
			thesample = basedir + basedir_plus + "*.root";
                        ch[1]->Add(thesample);
                        xsecs[1]=0.5085;
			numgen[1]=999.; // not actual number
		}
		if (samps[i]==2)
		{
			// //thesample = basedir + "v19_newBEANs/yggdrasil_treeMaker_mc_TTJetsBB_SemiLeptMGDecays*.root";
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsBB_SemiLeptMGDecays*.root";
// 			ch[2]->Add(thesample);
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsBB_FullLeptMGDecays*.root";
// 			ch[2]->Add(thesample);
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsBB_HadronicMGDecays*.root";
// 			ch[2]->Add(thesample);
			
			
		}
		if (samps[i]==3)
		{
			// //thesample = basedir + "v19_newBEANs/yggdrasil_treeMaker_mc_TTJetsB_SemiLeptMGDecays*.root";
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsB_SemiLeptMGDecays*.root";
// 			ch[3]->Add(thesample);
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsB_FullLeptMGDecays*.root";
// 			ch[3]->Add(thesample);
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsB_HadronicMGDecays*.root";
// 			ch[3]->Add(thesample);
			
			
		}
		if (samps[i]==4)
		{

			//basedir_plus = "ZZJets/";
                        basedir_plus = "zzJets/";
                        thesample = basedir + basedir_plus + "*.root";
			ch[4]->Add(thesample);
                        xsecs[4]=0.325;
			//numgen[4]=2514024.1998;
                        numgen[4]=2514003.0102;
		}
		if (samps[i]==5)
		{
                        // was ttlf
                        //basedir_plus = "TTJets/";
                        basedir_plus = "ttJets/";
                        //basedir_plus = "";
			thesample = basedir + basedir_plus + "*.root";
			ch[5]->Add(thesample);
			xsecs[5]=815.96; // at 173.2 GeV (top group twiki)
			numgen[5]=25446993.0;
                        

		}
		if (samps[i]==6)
		{
                        // was single top                                
                        basedir_plus = "zJets/";
			thesample = basedir + basedir_plus + "*.root";
			ch[6]->Add(thesample);    
                        xsecs[6]=2008.4;
                        numgen[6]=2829164.0;
		}
		if (samps[i]==7)
		{
			basedir_plus = "wJets/";
			thesample = basedir + basedir_plus + "*.root";
			ch[7]->Add(thesample);
                        xsecs[7]=20508.9;		
			numgen[7]=10017462.0;
		}
		if (samps[i]==8)
		{
			basedir_plus = "ttwJets/";
                        thesample = basedir + basedir_plus + "*.root";
			ch[8]->Add(thesample);
			xsecs[8]=0.6647;
                        numgen[8]=246521.0;
		}
		if (samps[i]==9)
		{
			basedir_plus = "ttzJets/";
                        thesample = basedir + basedir_plus + "*.root";
			ch[9]->Add(thesample);
                        xsecs[9]=0.8565;
                        numgen[9]=249275.0;
		}
		if (samps[i]==10)
		{
			// all diboson...
                        //thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_ZZ_*.root";
			//ch[10]->Add(thesample);
			basedir_plus = "wzJets/";
                        thesample = basedir + basedir_plus + "*.root";
			ch[10]->Add(thesample);
			//thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_WW_*.root";
			//ch[10]->Add(thesample);
                        xsecs[10]=2.165;
			numgen[10]=237484.0;
		}
                
                if (samps[i]==11)
		{
			// all diboson...
                        //thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_ZZ_*.root";
			//ch[10]->Add(thesample);
			basedir_plus = "zzJets/";
                        thesample = basedir + basedir_plus + "*.root";
			ch[11]->Add(thesample);
			//thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_WW_*.root";
			//ch[10]->Add(thesample);
                        xsecs[11]=0.325;
			//numgen[11]=2514024.;
                        numgen[11]=2514003.0102;
		}
                
                if (samps[i]==12)
		{
			basedir_plus = "TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/crab_ttH125/150519_150413/0000/";
                        //thesample = basedir + basedir_plus + "multileptree_2_1_yTv.root";
                        //thesample = thesample + " " + basedir + basedir_plus + "multileptree_7_1_AwJ.root";
			thesample = oldbasedir + basedir_plus + "*.root";
                        ch[12]->Add(thesample);
                        xsecs[12]=0.5085;                // you can't use "i" here, idiot ...
                        //numgen[1]=89671.4186331;
			//numgen[1]=80535.2587694;
			numgen[12]=89671.4186331; //charlie
		}
                
	}
}

void MakeGoodPlot::initialize()
{
	
        TString treename = "OSTwoLepAna/summaryTree";
	
        ch[0] = new TChain(treename);
	ch[1] = new TChain(treename);
	ch[2] = new TChain(treename);
	ch[3] = new TChain(treename);
	ch[4] = new TChain(treename);
	ch[5] = new TChain(treename);
	ch[6] = new TChain(treename);
	ch[7] = new TChain(treename);
	ch[8] = new TChain(treename);
	ch[9] = new TChain(treename);
	ch[10] = new TChain(treename);
        ch[11] = new TChain(treename);
        ch[12] = new TChain(treename);
	
	sample_names[0] = "data"; //"data (mu)";
	sample_names[1] = "t#bar{t}H (H->non-bb) Summer15"; //"t#bar{t}H(125)";
	sample_names[2] = "(none)"; //"t#bar{t} + b#bar{b}";
	sample_names[3] = "(none)"; //"t#bar{t} + b";
	sample_names[4] = "(none)"; //"t#bar{t} + c#bar{c}";
	sample_names[5] = "t#bar{t}+Jets"; //"t#bar{t} + lf";
	sample_names[6] = "Z+Jets"; //"single t";
	sample_names[7] = "W+Jets"; // "V + Jets"
	sample_names[8] = "t#bar{t}+W"; // "t#bar{t} + W,Z";
	sample_names[9] = "t#bar{t}+Z"; // "WW, WZ, ZZ";
	sample_names[10] = "WZ"; // "data (ele)";
	sample_names[11] = "ZZ"; // "data (ele)";
        sample_names[12] = "t#bar{t}H PHYS14";
        
        sample_names_std[0]  = sample_names[0]; 
        sample_names_std[1]  = sample_names[1]; 
        sample_names_std[2]  = sample_names[2]; 
        sample_names_std[3]  = sample_names[3]; 
        sample_names_std[4]  = sample_names[4]; 
        sample_names_std[5]  = sample_names[5]; 
        sample_names_std[6]  = sample_names[6];
        sample_names_std[7]  = sample_names[7];
        sample_names_std[8]  = sample_names[8]; 
        sample_names_std[9]  = sample_names[9]; 
        sample_names_std[10] = sample_names[10];
        sample_names_std[11] = sample_names[11];
        sample_names_std[12] = sample_names[12];
        
        Int_t cachesize = 100000000;   //100 MBytes
        
        ch[0]->SetCacheSize(cachesize);
        ch[1]->SetCacheSize(cachesize);
        ch[2]->SetCacheSize(cachesize);
        ch[3]->SetCacheSize(cachesize);
        ch[4]->SetCacheSize(cachesize);
        ch[5]->SetCacheSize(cachesize);
        ch[6]->SetCacheSize(cachesize);
        ch[7]->SetCacheSize(cachesize);
        ch[8]->SetCacheSize(cachesize);
        ch[9]->SetCacheSize(cachesize);
        ch[10]->SetCacheSize(cachesize);
        ch[11]->SetCacheSize(cachesize);
        ch[12]->SetCacheSize(cachesize);
        
        ch[0]->SetCacheLearnEntries(20);
        ch[1]->SetCacheLearnEntries(20);
        ch[2]->SetCacheLearnEntries(20);
        ch[3]->SetCacheLearnEntries(20);
        ch[4]->SetCacheLearnEntries(20);
        ch[5]->SetCacheLearnEntries(20);
        ch[6]->SetCacheLearnEntries(20);
        ch[7]->SetCacheLearnEntries(20);
        ch[8]->SetCacheLearnEntries(20);
        ch[9]->SetCacheLearnEntries(20);
        ch[10]->SetCacheLearnEntries(20);
        ch[11]->SetCacheLearnEntries(20);
        ch[12]->SetCacheLearnEntries(20);
        
        xsecs[0]=-999.;
        xsecs[1]=-999.;
        xsecs[2]=-999.;
        xsecs[3]=-999.;
        xsecs[4]=-999.;
        xsecs[5]=-999.;
        xsecs[6]=-999.;
        xsecs[7]=-999.;
        xsecs[8]=-999.;
        xsecs[9]=-999.;
        xsecs[10]=-999.;
        xsecs[11]=-999.;
        xsecs[12]=-999.;
              
        numgen[0]=-999.;
        numgen[1]=-999.;
        numgen[2]=-999.;
        numgen[3]=-999.;
        numgen[4]=-999.;
        numgen[5]=-999.;
        numgen[6]=-999.;
        numgen[7]=-999.;
        numgen[8]=-999.;
        numgen[9]=-999.;
        numgen[10]=-999.;
        numgen[11]=-999.;
        numgen[12]=-999.;
        
        
        mcwgt_intree = -9999.;
	wgt_intree = -9999.;
	wallTimePerEvent_intree = -9999.;

	eventnum_intree = -99;
	lumiBlock_intree = -99;
	runNumber_intree = -99;
	
	preselected_leptons_intree=0;
	preselected_electrons_intree=0;
	preselected_muons_intree=0;
	loose_leptons_intree=0;
	loose_electrons_intree=0;
	loose_muons_intree=0;

	cutBased_leptons_intree=0;
	cutBased_electrons_intree=0;
	cutBased_muons_intree=0;

	looseMvaBased_leptons_intree=0;
	looseMvaBased_electrons_intree=0;
	looseMvaBased_muons_intree=0;

	tightMvaBased_leptons_intree=0;
	tightMvaBased_electrons_intree=0;
	tightMvaBased_muons_intree=0;


	raw_electrons_intree=0;
	raw_muons_intree=0;

	preselected_jets_intree=0;
	loose_bJets_intree=0;
	tight_bJets_intree=0;
	
	met_intree=0;

	pruned_genParticles_intree=0;

        higgs_decay_intree = -9e6;
        
        
        
	
	numJets = 0;
	numTags = 0;
	
	weight = 0.;
	
	tight_lepton_pt = 0.;
	
	avg_dr_tagged_jets = 0.;
	sphericity = 0.;
	dr_between_lep_and_closest_jet = 0.;
	avg_btag_disc_btags = 0.;
	dev_from_avg_disc_btags = 0.;
	h2 = 0.;
	lowest_btag = 0.;
	avg_untagged_dijet_mass = 0.;
	closest_tagged_dijet_mass = 0.;
	h3 = 0.;
	h4 = 0.;
	second_highest_btag = 0.;
	third_highest_btag = 0.;
	fourth_highest_btag = 0.;
	
	avg_btag_disc_non_btags = 0.;
	tagged_dijet_mass_closest_to_125 = 0.;
	
	
	invariant_mass_of_everything = 0.;
	best_higgs_mass = 0.;
	minChi2 = 0.;
	dRbb = 0.;

	bhmv2 = 0.;
	maxeta_jet_jet = 0.;
	maxeta_jet_tag = 0.;
	maxeta_tag_tag = 0.;
	dEta_leptop_bb = 0.;
	dEta_hadtop_bb = 0.;
	dPhi_fn = 0.;
	dEta_fn = 0.;
	avg_eta_tops = 0.;
	bb_eta = 0.;
	angle_tops_bb = 0.;
	
	dRbb_bhmv2 = 0.;
//	bb_eta = 0.;
	b1_eta = 0.;
	b2_eta = 0.;
	b1_pt = 0.;
	b2_pt = 0.;
	
	median_bb_mass = 0.;
	min_dr_tagged_jets = 0.;
	
	pt_all_jets_over_E_all_jets = 0.;
	
	
	aplanarity = 0.;
	MET = 0.;
	MET_phi = 0.;
	first_jet_pt = 0.;
	second_jet_pt = 0.;
	third_jet_pt = 0.;
	fourth_jet_pt = 0.;
	h0 = 0.;
	h1 = 0.;
	all_sum_pt_with_met = 0.;
	HT = 0.;
	MHT = 0.;
	MHT_phi = 0.;
	
	jet_tag_1_pt = 0.;
	jet_tag_2_pt = 0.;
	jet_tag_3_pt = 0.;
	jet_tag_4_pt = 0.;


	avg_tagged_dijet_mass = 0.;
	tight_lepton_phi = 0.;
	M3 = 0.;
	M3_1tag = 0.;
	Mlb = 0.;
	first_highest_btag = 0.;
	
	ttbb_tth_ANN_output = 0.;
	ttbb_tth_MVA_output_5j4t = 0.;
	ttbb_tth_MVA_output_6j3t = 0.;
	
	var1 = 0.;
	var2 = 0.;
	var3 = 0.;
	var4 = 0.;
	var5 = 0.;
	var6 = 0.;
	var7 = 0.;
	var8 = 0.;
	var9 = 0.;
	var10= 0.;
	var11= 0.;
	var12= 0.;
	var13= 0.;
	var14= 0.;
	var15= 0.;
	var16= 0.;
	var17= 0.;
	var18= 0.;
	var19= 0.;
	var20= 0.;
	var21= 0.;
	var22= 0.;
	var23= 0.;
	var24= 0.;
	var25= 0.;
	var26= 0.;
	var27= 0.;
	var28= 0.;
	var29= 0.;
	var30= 0.;
	var31= 0.;
	var32= 0.;
	var33= 0.;
	var34= 0.;
	var35= 0.;
	var36= 0.;
	var37= 0.;
	var38= 0.;
	var39= 0.;
	var40= 0.;

	cmsinfo = "CMS Preliminary  #sqrt{s} = 8 TeV, L = 19.4 fb^{-1}";
	CMSInfoLatex = new TLatex(0.48, 0.91, cmsinfo.c_str());
	CMSInfoLatex->SetNDC();
	CMSInfoLatex->SetTextFont(42);
	// CMSInfoLatex.SetTextSize(0.055);
	CMSInfoLatex->SetTextSize(0.035);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/// algos / function definitions:



double MakeGoodPlot::get_bhm_from_own_algo(double MET, double METphi, TLorentzVector &metv, vdouble lep, vvdouble jets, vdouble csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb)
{
	metv.SetPtEtaPhiE(MET,0.,METphi,MET);
	TLorentzVector lepton;
	lepton.SetPxPyPzE(lep[0],lep[1],lep[2],lep[3]);
	vecTLorentzVector jet_TLVs;	
	convert_jets_to_TLVs(jets, jet_TLVs);
		
	//double minChi;
	//double dRbb;
	TLorentzVector bjet1;
	TLorentzVector bjet2;
	
	TLorentzVector test1;
	TLorentzVector test2;
	
	double bhm = getBestHiggsMass2(lepton, metv, jet_TLVs, csv, minChi, dRbb, bjet1, bjet2, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, test1, test2); // Jon T. version 2

	return bhm;
}


void MakeGoodPlot::get_bs_from_reverse_engineered_bhm(vvdouble jets, vdouble jetCSV, double best_higgs_mass, TLorentzVector &bjet1, TLorentzVector &bjet2)
{

	// this is temporary due to accidentally leaving out some info in trees
	
	double testmass = 0.;
	
	vecTLorentzVector btag_TLV_vect;
		
	vect_of_tagged_TLVs(jets, jetCSV, btag_TLV_vect);
	
	for (int i=0; i<btag_TLV_vect.size(); i++)
	{
		for (int j=0; j<btag_TLV_vect.size(); j++)
		{
			if (i!=j)
			{
				TLorentzVector tempvect = btag_TLV_vect[i]+btag_TLV_vect[j];
				testmass = tempvect.M();
				if (testmass==best_higgs_mass)
				{
					bjet1 = btag_TLV_vect[i];
					bjet2 = btag_TLV_vect[j];
					break;
				}
			}
		}		
		if (testmass==best_higgs_mass) break;
	}
}



double MakeGoodPlot::getBestHiggsMass(TLorentzVector lepton, TLorentzVector met, vecTLorentzVector jets, vdouble btag, double &minChi, double &dRbb, TLorentzVector &bjet1, TLorentzVector &bjet2)
{

  int nJets = int(jets.size());

  double chi_top_lep=10000;
  double chi_top_had=10000;
  //double chi_W_lep=10000; //isn't really used
  double chi_W_had=10000;

  minChi = 1000000;
  dRbb = 1000000;
  double btagCut = 0.679;
  double W_mass = 80.0;
  double top_mass = 172.5;
  //double H_mass=120.0;

  // updated 8/22/2012 from J. Timcheck
  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  double sigma_hadW   = 12.77;
  double sigma_hadTop = 18.9;
  double sigma_lepTop = 32.91;

  // //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  // double sigma_hadW   = 12.59;
  // double sigma_hadTop = 19.9;
  // double sigma_lepTop = 39.05;

  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttJets
  /*double sigma_hadW		= 12.72,
    sigma_hadTop	= 18.12,
    sigma_lepTop	= 38.72;
  */

  double metPz[2];
  double chi=999999;

  //stuff to find:
  double higgs_mass_high_energy=0;

  int nBtags = 0;
  for(int i=0;i<nJets;i++){
    if(btag[i]>btagCut) nBtags++;
  }

  int nUntags = nJets-nBtags;

  double lowest_btag = 99.;
  double second_lowest_btag = 999.;
  int ind_lowest_btag = 999;
  int ind_second_lowest_btag = 999;

  if( nJets>=6 && nBtags>=4 ){
    if( nUntags<2 ){
      for(int i=0;i<nJets;i++){
	if( btag[i]<lowest_btag ){
	  second_lowest_btag = lowest_btag;
	  ind_second_lowest_btag = ind_lowest_btag;

	  lowest_btag = btag[i];
	  ind_lowest_btag = i;
	}
	else if( btag[i]<second_lowest_btag ){
	  second_lowest_btag = btag[i];
	  ind_second_lowest_btag = i;
	}
      }
    }
  }

  // First get the neutrino z
  double energyLep = lepton.E();
  double a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
  double radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
  radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
  if (radical < 0.0) radical = 0.0;
  metPz[0] = (lepton.Pz()*a/energyLep) + 0.5*sqrt(radical);
  metPz[0] = metPz[0] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));
  metPz[1] = (lepton.Pz()*a/energyLep) - 0.5*sqrt(radical);
  metPz[1] = metPz[1] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));


  // Loop over all jets, both Pz, calcaulte chi-square
  TLorentzVector metNew;
  for( int ipznu=0; ipznu<2; ipznu++ ){
    metNew.SetXYZM(met.Px(),met.Py(),metPz[ipznu],0.0); //neutrino has mass 0
    //with b-tag info
    if( nJets>=6 && nBtags>=4 ){
      vecTLorentzVector not_b_tagged,b_tagged;
      //fill not_b_tagged and b_tagged
      for( int i=0;i<nJets;i++ ){
	if( btag[i]>btagCut && i!=ind_second_lowest_btag && i!=ind_lowest_btag) b_tagged.push_back(jets[i]);
	else not_b_tagged.push_back(jets[i]);
      }
      //first make possible t_lep's with b-tagged jets (includes making W_lep)
      for( int i=0; i<int(b_tagged.size()); i++ ){
	TLorentzVector W_lep=metNew+lepton; //used for histogram drawing only
	TLorentzVector top_lep=metNew+lepton+b_tagged.at(i);
	chi_top_lep=pow((top_lep.M()-top_mass)/sigma_lepTop,2);
	//next make possible W_had's with not b-tagged jets
	for( int j=0; j<int(not_b_tagged.size()); j++ ){
	  for( int k=0; k<int(not_b_tagged.size()); k++ ){
	    if( j!=k ){
	      TLorentzVector W_had=not_b_tagged.at(j)+not_b_tagged.at(k);
	      chi_W_had=pow((W_had.M()-W_mass)/sigma_hadW,2);
	      //now make possible top_had's (using the W_had + some b-tagged jet)
	      for( int l=0; l<int(b_tagged.size()); l++ ){
		if( l!=i ){
		  TLorentzVector top_had=W_had+b_tagged.at(l);
		  chi_top_had=pow((top_had.M()-top_mass)/sigma_hadTop,2);
		  chi=chi_top_lep+chi_W_had+chi_top_had;
		  //accept the lowest chi
		  if( chi<minChi ){
		    minChi=chi;
		    //pick the other two b's that have the highest et (energy in transverse plane) as higgs mass constituents
		    TLorentzVector H2;
		    int numH2Constituents=0;
		    
		    TLorentzVector bBest[2];
		    
		    for( int m=0; m<int(b_tagged.size()); m++ ){
		      if( m!=i && m!=l && numH2Constituents<2 ){
			bBest[numH2Constituents] = b_tagged.at(m);
			numH2Constituents++;
			H2+=b_tagged.at(m);
		      }
		    }
		    dRbb = bBest[0].DeltaR( bBest[1] );
		    higgs_mass_high_energy=H2.M();
		    bjet1 = bBest[0];
		    bjet2 = bBest[1];
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  return higgs_mass_high_energy;
}

double MakeGoodPlot::getBestHiggsMass2(TLorentzVector lepton, TLorentzVector &met, vecTLorentzVector jets, vdouble btag, double &minChi, double &dRbb, TLorentzVector &bjet1, TLorentzVector &bjet2, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, TLorentzVector &toplep, TLorentzVector &tophad)
{

  int nJets = int(jets.size());
  double pfmet_px=met.Px(), pfmet_py=met.Py();
  double chi_top_lep=10000;
  double chi_top_had=10000;
  //double chi_W_lep=10000; //isn't really used
  double chi_W_had=10000;

  minChi = 1000000;
  dRbb = 1000000;
  double btagCut = 0.679;
  double W_mass = 80.0;
  double top_mass = 172.5;
  //double H_mass=120.0;

  // updated 8/22/2012 from J. Timcheck
  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  double sigma_hadW   = 12.77;
  double sigma_hadTop = 18.9;
  //double sigma_lepTop = 32.91;
  double sigma_lepTop = 18.9;

  // //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  // double sigma_hadW   = 12.59;
  // double sigma_hadTop = 19.9;
  // double sigma_lepTop = 39.05;

  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttJets
  /*double sigma_hadW		= 12.72,
    sigma_hadTop	= 18.12,
    sigma_lepTop	= 38.72;
  */
  
  /// more initializitions
  
  bjet1.SetPxPyPzE(1.,1.,1.,2.);
  bjet2.SetPxPyPzE(1.,1.,1.,2.);
//  chi2lepW = 0.;
//  chi2leptop = 0.;
//  chi2hadtop = 0.;
  mass_lepW = 0.;
  mass_leptop = 0.;
  mass_hadW = 0.;
  mass_hadtop = 0.;
  toplep.SetPxPyPzE(1.,1.,1.,2.);
  tophad.SetPxPyPzE(1.,1.,1.,2.);
  
  
  double metPz[2];
  double chi=999999;

  //stuff to find:
  double higgs_mass_high_energy=0;

  int nBtags = 0;
  for(int i=0;i<nJets;i++){
    if(btag[i]>btagCut) nBtags++;
  }

  int nUntags = nJets-nBtags;

  double lowest_btag = 99.;
  double second_lowest_btag = 999.;
  int ind_lowest_btag = 999;
  int ind_second_lowest_btag = 999;

  vdouble btag_sorted = btag;
  int ind_fourth_highest = 999;

  if( nJets>=6 && nBtags>=4 ){
    
    if( nUntags<2 ){
      for(int i=0;i<nJets;i++){
	if( btag[i]<lowest_btag ){
	  second_lowest_btag = lowest_btag;
	  ind_second_lowest_btag = ind_lowest_btag;

	  lowest_btag = btag[i];
	  ind_lowest_btag = i;
	}
	else if( btag[i]<second_lowest_btag ){
	  second_lowest_btag = btag[i];
	  ind_second_lowest_btag = i;
	}
      }
    }
    /*
    if( nBtags==3 )
    {
	sort(btag_sorted.begin(),btag_sorted.end());
	double fourth_highest_csv = btag_sorted[nJets-4];
	
	for (int f=0; f<nJets; f++)
	{
		if (btag[f]==fourth_highest_csv) ind_fourth_highest = f;
	}

    }
    */
  }

    //Handle 6j3t.
  int ind_promoted_btag = 999;

  if( nJets>=6 && nBtags==3 ){
    for(int i=0;i<nJets;i++){
      int rank = 0;
      for(int j=0;j<nJets;j++){
	if( btag[j] > btag[i] ){
	  rank++;
	}
      }
      if( rank == 3 ) ind_promoted_btag = i;
    }
  }


  // First get the neutrino z
  double energyLep = lepton.E();
  double a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
  double radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
  radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
  
  bool imaginary = false;

if (radical < 0.0)
{
	imaginary=true;
}
if(imaginary)
{
	radical=-1.0;
	double value=.001;
	while(true)
	{
		met.SetPxPyPzE(pfmet_px,pfmet_py,0.0,sqrt(pow(pfmet_px,2)+pow(pfmet_py,2))); //neutrino mass 0, pt = sqrt(px^2+py^2)
//			energyLep = lepton.E();
		a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
		radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
		radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
		if(radical>=0)
			break;
		pfmet_px-=pfmet_px*value;
		pfmet_py-=pfmet_py*value;
	}
}


  metPz[0] = (lepton.Pz()*a/energyLep) + 0.5*sqrt(radical);
  metPz[0] = metPz[0] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));
  metPz[1] = (lepton.Pz()*a/energyLep) - 0.5*sqrt(radical);
  metPz[1] = metPz[1] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));



  // Loop over all jets, both Pz, calcaulte chi-square
  TLorentzVector metNew;
  for( int ipznu=0; ipznu<2; ipznu++ ){
    metNew.SetXYZM(met.Px(),met.Py(),metPz[ipznu],0.0); //neutrino has mass 0
    //with b-tag info
    if(( nJets>=6 && nBtags>=4 )||( nJets>=6 && nBtags==3 )){
      vecTLorentzVector not_b_tagged,b_tagged;
      //fill not_b_tagged and b_tagged
      for( int i=0;i<nJets;i++ ){
      
        //if (nBtags>=4)
	//{
		if( (btag[i]>btagCut && i!=ind_second_lowest_btag && i!=ind_lowest_btag) || (i==ind_promoted_btag) ) b_tagged.push_back(jets[i]);
		else not_b_tagged.push_back(jets[i]);
	//}
	/*
	if (nBtags==3)
	{
      		if( btag[i]>btagCut || i==ind_fourth_highest) b_tagged.push_back(jets[i]);
		else not_b_tagged.push_back(jets[i]);
      	}
 	*/
      
      }
      //first make possible t_lep's with b-tagged jets (includes making W_lep)
      for( int i=0; i<int(b_tagged.size()); i++ ){
	TLorentzVector W_lep=metNew+lepton; //used for histogram drawing only
	TLorentzVector top_lep=metNew+lepton+b_tagged.at(i);
	chi_top_lep=pow((top_lep.M()-top_mass)/sigma_lepTop,2);
	//next make possible W_had's with not b-tagged jets
	for( int j=0; j<int(not_b_tagged.size()); j++ ){
	  for( int k=0; k<int(not_b_tagged.size()); k++ ){
	    if( j!=k ){
	      TLorentzVector W_had=not_b_tagged.at(j)+not_b_tagged.at(k);
	      chi_W_had=pow((W_had.M()-W_mass)/sigma_hadW,2);
	      //now make possible top_had's (using the W_had + some b-tagged jet)
	      for( int l=0; l<int(b_tagged.size()); l++ ){
		if( l!=i ){
		  TLorentzVector top_had=W_had+b_tagged.at(l);
		  chi_top_had=pow((top_had.M()-top_mass)/sigma_hadTop,2);
		  chi=chi_top_lep+chi_W_had+chi_top_had;
		  //accept the lowest chi
		  if( chi<minChi ){
		    minChi=chi;
		    //pick the other two b's that have the highest et (energy in transverse plane) as higgs mass constituents
		    TLorentzVector H2;
		    int numH2Constituents=0;
		    
		    TLorentzVector bBest[2];
		    
		    for( int m=0; m<int(b_tagged.size()); m++ ){
		      if( m!=i && m!=l && numH2Constituents<2 ){
			bBest[numH2Constituents] = b_tagged.at(m);
			numH2Constituents++;
			H2+=b_tagged.at(m);
		      }
		    }
		    dRbb = bBest[0].DeltaR( bBest[1] );
		    higgs_mass_high_energy=H2.M();
		    bjet1 = bBest[0];
		    bjet2 = bBest[1];
		    
		    mass_lepW = W_mass;
		    mass_leptop = top_lep.M();
		    mass_hadW = W_had.M();
		    mass_hadtop = top_had.M();
		    toplep = top_lep;
		    tophad = top_had;
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  
chi2lepW = 0.;
chi2leptop = chi_top_lep;
chi2hadtop = chi_top_had;
chi2hadW = chi_W_had;



  
  return higgs_mass_high_energy;

}

double MakeGoodPlot::get_avg_abs_deta_jets (vvdouble jets)
{
	
	vecTLorentzVector thejets;
	convert_jets_to_TLVs(jets, thejets);
	
	int count=0;
	double avgval=0.;
	
	for (int i=0; i<(thejets.size()-1); i++)
	{
		for (int j=i+1; j<thejets.size(); j++)
		{
				
				avgval += fabs(thejets[i].Eta()-thejets[j].Eta());
				count++;
		}
	}
	
	if (count) avgval /= count;
	
	return avgval;
	
}

/*
void two_tagged_TLVs_from_bhm(TLorentzVector &firstb,TLorentzVector &secondb,int syst=0)
{
	firstb.SetPxPyPzE(eve1->minChi2_bjet1_px_[syst],eve1->minChi2_bjet1_py_[syst],eve1->minChi2_bjet1_pz_[syst],eve1->minChi2_bjet1_E_[syst]);
	secondb.SetPxPyPzE(eve1->minChi2_bjet2_px_[syst],eve1->minChi2_bjet2_py_[syst],eve1->minChi2_bjet2_pz_[syst],eve1->minChi2_bjet2_E_[syst]);
	
}
*/

double MakeGoodPlot::get_jet_jet_etamax (vvdouble jets)
{
	vecTLorentzVector thejets;
	convert_jets_to_TLVs(jets, thejets);
	
	int count=0;
	double avgval=0.;
	
	for (int i=0; i<(thejets.size()-1); i++)
	{
		for (int j=i+1; j<thejets.size(); j++)
		{
				
				avgval += thejets[i].Eta()-thejets[j].Eta();
				count++;
		}
	}
	
	avgval /= count;
	
	double imax = 0.;
	double etamax=0.;
	
	for (int k=0; k<thejets.size(); k++)
	{
		imax = abs(thejets[k].Eta()-avgval);
		
		if(imax>etamax)
		{
			etamax = imax;
		}
	}

	return etamax;

}
double MakeGoodPlot::get_jet_tag_etamax (vvdouble jets, vdouble jetCSV)
{
	vecTLorentzVector thejets;
	convert_jets_to_TLVs(jets, thejets);
	
	int count=0;
	double avgval=0.;
	
	for (int i=0; i<(thejets.size()-1); i++)
	{
		for (int j=i+1; j<thejets.size(); j++)
		{
				
				avgval += thejets[i].Eta()-thejets[j].Eta();
				count++;
		}
	}
	
	avgval /= count;
	
	double imax = 0.;
	double etamax=0.;
	
	
	vecTLorentzVector thetags;
	vect_of_tagged_TLVs(jets, jetCSV, thetags);
	
	
	for (int k=0; k<thetags.size(); k++)
	{
		imax = abs(thetags[k].Eta()-avgval);
		
		if(imax>etamax)
		{
			etamax = imax;
		}
	}

	return etamax;

}


double MakeGoodPlot::get_tag_tag_etamax (vvdouble jets, vdouble jetCSV)
{

	vecTLorentzVector thetags;
	vect_of_tagged_TLVs(jets, jetCSV, thetags);
		
	int count=0;
	double avgval=0.;
	
	for (int i=0; i<(thetags.size()-1); i++)
	{
		for (int j=i+1; j<thetags.size(); j++)
		{
				
				avgval += thetags[i].Eta()-thetags[j].Eta();
				count++;
		}
	}
	
	avgval /= count;
	
	double imax = 0.;
	double etamax=0.;
	
	
	for (int k=0; k<thetags.size(); k++)
	{
		imax = abs(thetags[k].Eta()-avgval);
		
		if(imax>etamax)
		{
			etamax = imax;
		}
	}

	return etamax;

}







void MakeGoodPlot::vect_of_tagged_TLVs(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_btag_TLVs)
{
	TLorentzVector tagged_jet;
	
	int nJets = jets.size();
	//double btagCut = 0.679; // M
	double btagCut = 0.244; // L
	
	for(int i=0;i<nJets;i++)
	{
		if (jetCSV[i]>=btagCut)
		{
		
			tagged_jet.SetPxPyPzE(jets[i][0],jets[i][1],jets[i][2],jets[i][3]);
			vect_of_btag_TLVs.push_back(tagged_jet);
		}
	}
}

void MakeGoodPlot::vect_of_untagged_TLVs(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_nontagged_TLVs)
{
	TLorentzVector untagged_jet;
	
	int nJets = jets.size();
	double btagCut = 0.679;
	
	for(int i=0;i<nJets;i++)
	{
		if (!(jetCSV[i]>btagCut))
		{
			untagged_jet.SetPxPyPzE(jets[i][0],jets[i][1],jets[i][2],jets[i][3]);
			vect_of_nontagged_TLVs.push_back(untagged_jet);
		}
	}
}

void MakeGoodPlot::convert_jets_to_TLVs(vvdouble jets, vecTLorentzVector &vect_of_jet_TLVs)
{
	TLorentzVector jet;	
	int nJets = jets.size();
	
	for(int i=0;i<nJets;i++)
	{
		jet.SetPxPyPzE(jets[i][0],jets[i][1],jets[i][2],jets[i][3]);
		vect_of_jet_TLVs.push_back(jet);
	}
}

double MakeGoodPlot::w_mass_top(vvdouble jets, vdouble jetCSV)
{
	double mass = -1.;
	
	vecTLorentzVector vect_of_btags;
	vecTLorentzVector vect_of_untags;
	
	vect_of_tagged_TLVs(jets,jetCSV,vect_of_btags);
	vect_of_untagged_TLVs(jets,jetCSV,vect_of_untags);

	double chi=999999.;
	double chi_top_had=10000.;
	double chi_W_had=10000.;
	
	double minChi = 1000000.;
	
	double W_mass = 80.0;
	double top_mass = 172.5;
	double H_mass=120.0;

	double sigma_hadW 	= 12.59,
		sigma_hadTop 	= 19.9,
		sigma_lepTop	= 39.05;
			 
	double sigma_H		= 15.79;
	
	
	int ntags = vect_of_btags.size();
	int untags = vect_of_untags.size();


	for(int j=0;j<untags;j++)
	{
		for(int k=0;k<untags;k++)
		{
			if(j!=k)
			{
				TLorentzVector W_had = vect_of_untags.at(j)+vect_of_untags.at(k);
				chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);

				for(int l=0;l<ntags;l++)
				{
					TLorentzVector top_had = W_had + vect_of_btags.at(l);
					chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
					chi = chi_W_had + chi_top_had;
					
					if(chi<minChi)
					{
						minChi = chi;
						mass = W_had.M();
					}
				}
			}
		}
	}
	
	return mass;	
}
double MakeGoodPlot::had_top_mass(vvdouble jets, vdouble jetCSV)
{
	double mass = -1.;
	
	vecTLorentzVector vect_of_btags;
	vecTLorentzVector vect_of_untags;
	
	vect_of_tagged_TLVs(jets,jetCSV,vect_of_btags);
	vect_of_untagged_TLVs(jets,jetCSV,vect_of_untags);

	double chi=999999.;
	double chi_top_had=10000.;
	double chi_W_had=10000.;
	
	double minChi = 1000000.;
	
	double W_mass = 80.0;
	double top_mass = 172.5;
	double H_mass=120.0;

	double sigma_hadW 	= 12.59,
		sigma_hadTop 	= 19.9,
		sigma_lepTop	= 39.05;
			 
	double sigma_H		= 15.79;
	
	
	int ntags = vect_of_btags.size();
	int untags = vect_of_untags.size();


	for(int j=0;j<untags;j++)
	{
		for(int k=0;k<untags;k++)
		{
			if(j!=k)
			{
				TLorentzVector W_had = vect_of_untags.at(j)+vect_of_untags.at(k);
				chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);

				for(int l=0;l<ntags;l++)
				{
					TLorentzVector top_had = W_had + vect_of_btags.at(l);
					chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
					chi = chi_W_had + chi_top_had;
					
					if(chi<minChi)
					{
						minChi = chi;
						mass = top_had.M();
					}
				}
			}
		}
	}
	
	return mass;	
}

double MakeGoodPlot::ww_mass_nontop(vvdouble jets, vdouble jetCSV)
{

	double mass = -1.;
	
	vecTLorentzVector vect_of_btags;
	vecTLorentzVector vect_of_untags;
	
	vect_of_tagged_TLVs(jets,jetCSV,vect_of_btags);
	vect_of_untagged_TLVs(jets,jetCSV,vect_of_untags);

	double chi=999999.;
	double chi_top_had=10000.;
	double chi_W_had=10000.;
	
	double minChi = 1000000.;
	
	double W_mass = 80.0;
	double top_mass = 172.5;
	double H_mass=120.0;

	double sigma_hadW 	= 12.59,
		sigma_hadTop 	= 19.9,
		sigma_lepTop	= 39.05;
			 
	double sigma_H		= 15.79;
	
	
	int ntags = vect_of_btags.size();
	int untags = vect_of_untags.size();

	TLorentzVector mydummyguy;
	mydummyguy.SetPxPyPzE(0,0,0,0);

	for(int j=0;j<untags;j++)
	{
		for(int k=0;k<untags;k++)
		{
			if(j!=k)
			{
				TLorentzVector W_had = vect_of_untags.at(j)+vect_of_untags.at(k);
				chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);

				for(int l=0;l<ntags;l++)
				{
					TLorentzVector top_had = W_had + vect_of_btags.at(l);
					chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
					chi = chi_W_had + chi_top_had;
					
					if(chi<minChi)
					{
						minChi = chi;
						TLorentzVector H2 = mydummyguy;
						
						for(int m=0; m<untags; m++)
						{
							if((m!=j) && (m!=k))
							{												
								H2 += vect_of_untags.at(m);
							}
						}

						mass = H2.M();
					}
				}
			}
		}
	}
	
	return mass;
}

void MakeGoodPlot::nontop_untags(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_nontagged_TLVs_not_top)
{

	double mass = -1.;
	
	vecTLorentzVector vect_of_btags;
	vecTLorentzVector vect_of_untags;
	
	vect_of_tagged_TLVs(jets,jetCSV,vect_of_btags);
	vect_of_untagged_TLVs(jets,jetCSV,vect_of_untags);

	double chi=999999.;
	double chi_top_had=10000.;
	double chi_W_had=10000.;
	
	double minChi = 1000000.;
	
	double W_mass = 80.0;
	double top_mass = 172.5;
	double H_mass=120.0;

	double sigma_hadW 	= 12.59,
		sigma_hadTop 	= 19.9,
		sigma_lepTop	= 39.05;
			 
	double sigma_H		= 15.79;
	
	
	int ntags = vect_of_btags.size();
	int untags = vect_of_untags.size();


	for(int j=0;j<untags;j++)
	{
		for(int k=0;k<untags;k++)
		{
			if(j!=k)
			{
				TLorentzVector W_had = vect_of_untags.at(j)+vect_of_untags.at(k);
				chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);

				for(int l=0;l<ntags;l++)
				{
					TLorentzVector top_had = W_had + vect_of_btags.at(l);
					chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
					chi = chi_W_had + chi_top_had;
					
					if(chi<minChi)
					{
						minChi = chi;
						vecTLorentzVector result;
						
						for(int m=0; m<untags; m++)
						{
							if((m!=j) && (m!=k))
							{												
								result.push_back(vect_of_untags.at(m));
							}
						}
						
						
						vect_of_nontagged_TLVs_not_top = result;
					}
				}
			}
		}
	}
	
}

double MakeGoodPlot::avg_pt_nontop_untags(vvdouble jets, vdouble jetCSV)
{
	double avgpt = 0.;
	vecTLorentzVector vTLV_untags;
	nontop_untags(jets, jetCSV, vTLV_untags);	
	int asdf = vTLV_untags.size();

	for (int i=0; i<asdf; i++)
	{
		avgpt += vTLV_untags[i].Perp();
	}
	
	avgpt = avgpt / asdf;	
	return avgpt;
}

double MakeGoodPlot::pt_E_ratio_jets(vvdouble jets)
{
	double ratio = 0.;
	double ptsum = 0.;
	double Esum = 0.;
	
	vecTLorentzVector jetvect;
	convert_jets_to_TLVs(jets,jetvect);
	
	for (int i=0; i<jetvect.size(); i++)
	{
		ptsum += jetvect[i].Pt();
		Esum += jetvect[i].E();
	}
	
	ratio = ptsum / Esum;
	
	return ratio;
}

double MakeGoodPlot::study_tops_bb_syst (double MET, double METphi, TLorentzVector &metv, vdouble lep, vvdouble jets, vdouble csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb, double &testquant1, double &testquant2, double &testquant3, double &testquant4, double &testquant5, double &testquant6, double &testquant7, TLorentzVector &b1, TLorentzVector &b2)
{
	double pi = 3.14;
	
	metv.SetPtEtaPhiE(MET,0.,METphi,MET);
	TLorentzVector lepton;
	lepton.SetPxPyPzE(lep[0],lep[1],lep[2],lep[3]);
	vecTLorentzVector jet_TLVs;	
	convert_jets_to_TLVs(jets, jet_TLVs);
		
	//double minChi;
	//double dRbb;
	TLorentzVector bjet1;
	TLorentzVector bjet2;
	TLorentzVector leptop;
	TLorentzVector hadtop;
	
	
	double bhm = getBestHiggsMass2(lepton, metv, jet_TLVs, csv, minChi, dRbb, bjet1, bjet2, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, leptop, hadtop); // Jon T. version 2

	
	b1 = bjet1;
	b2 = bjet2;
	
	TLorentzVector bsyst = bjet1+bjet2;
	TLorentzVector topsyst = leptop+hadtop;
	
	//testquant1 = bsyst.Angle(leptop.Vect());
	//testquant2 = bsyst.Angle(hadtop.Vect());
	
	//testquant1 = bsyst.DeltaPhi(leptop);
	//testquant2 = bsyst.DeltaPhi(hadtop);
	
	//testquant1 = bsyst.Eta() - leptop.Eta();
	//testquant2 = bsyst.Eta() - hadtop.Eta();
	
	//testquant1 = bsyst.Eta() - hadtop.Eta();
	//testquant2 = bsyst.DeltaPhi(hadtop);
	
	
	//testquant2 = bsyst.Eta();
	
	//testquant1 = topsyst.Phi();
	//testquant2 = bsyst.Phi();
	
	
	//testquant2 = bsyst.Angle(hadtop.Vect());
	
	
	//dphi, deta stuff	
	
	
	
	testquant1 = bsyst.Eta() - leptop.Eta();	
	testquant2 = bsyst.Eta() - hadtop.Eta();
	
	
	double dphihad = bsyst.DeltaPhi(hadtop);
	double dphilep = bsyst.DeltaPhi(leptop);
	testquant3 = fabs((dphilep - pi)*(dphilep + pi)) + pow(dphihad,2);
	testquant3 = sqrt(testquant3 / (2.0*pow(pi,2)));
		
	
	testquant4 = bsyst.Eta();
	
	testquant5 = (hadtop.Eta() + leptop.Eta())/2;
	
	
	testquant6 = sqrt(abs((bsyst.Eta() - leptop.Eta())*(bsyst.Eta() - hadtop.Eta())));
	
	
	testquant7 = bsyst.Angle(topsyst.Vect());
	
	return bhm;
}

double MakeGoodPlot::get_median_bb_mass (vvdouble jets, vdouble jetCSV)
{

	// all btags
	vecTLorentzVector all_btags;
	TLorentzVector bb;

	vect_of_tagged_TLVs(jets, jetCSV, all_btags);

	int bbcount = 0;
	vector<double> median_vect;
	double median_mass = 0.;


	for (int asdf=0; asdf<(all_btags.size()-1); asdf++)
	{
		for (int j=asdf+1; j<all_btags.size(); j++)
		{	

			bb = all_btags[asdf]+all_btags[j];

			median_vect.push_back(bb.M());

			bbcount++;

		}
	}

	float vectpos = (float)median_vect.size();

	vectpos = floor(vectpos/2)-1; // all these are even -> gets lower one

	sort(median_vect.begin(),median_vect.end());

	median_mass = median_vect[vectpos+1]; // gets upper one


	return median_mass;

}
//double MakeGoodPlot::get_gaus_shift(TString cat_num, int sample_number)
double MakeGoodPlot::get_gaus_shift(int cat_num, int sample_number)
{
	double theshift = 0.;
	
		
	double range1 = 0.25;	// range to do the shifts over in sigma
	double range2 = 1.;	// range to do the shifts over in sigma
	double range3 = 4.;	// range to do the shifts over in sigma
		
	/*		
	if (cat_num== "64390001")  theshift = 0.;
	if (cat_num== "64390002")  theshift = range1 / 10.;
	if (cat_num== "64390003")  theshift = 2.*range1 / 10.;
	if (cat_num== "64390004")  theshift = 3.*range1 / 10.;
	if (cat_num== "64390005")  theshift = 4.*range1 / 10.;
	if (cat_num== "64390006")  theshift = 5.*range1 / 10.;
	if (cat_num== "64390007")  theshift = 6.*range1 / 10.;  
	if (cat_num== "64390008")  theshift = 7.*range1 / 10.;  
	if (cat_num== "64390009")  theshift = 8.*range1 / 10.;  
	if (cat_num== "64390010")  theshift = 9.*range1 / 10.;  
	if (cat_num== "64390011")  theshift = range1;
	if (cat_num== "64390012")  theshift = 0.;
	if (cat_num== "64390013")  theshift = range2 / 10.;
	if (cat_num== "64390014")  theshift = 2.*range2 / 10.;  
	if (cat_num== "64390015")  theshift = 3.*range2 / 10.;  
	if (cat_num== "64390016")  theshift = 4.*range2 / 10.;  
	if (cat_num== "64390017")  theshift = 5.*range2 / 10.;  
	if (cat_num== "64390018")  theshift = 6.*range2 / 10.;  
	if (cat_num== "64390019")  theshift = 7.*range2 / 10.;  
	if (cat_num== "64390020")  theshift = 8.*range2 / 10.;  
	if (cat_num== "64390021")  theshift = 9.*range2 / 10.;  
	if (cat_num== "64390022")  theshift = range2;	        
	if (cat_num== "64390023")  theshift = 0.;	        
	if (cat_num== "64390024")  theshift = range3 / 10.;     
	if (cat_num== "64390025")  theshift = 2.*range3 / 10.;  
	if (cat_num== "64390026")  theshift = 3.*range3 / 10.;  
	if (cat_num== "64390027")  theshift = 4.*range3 / 10.;  
	if (cat_num== "64390028")  theshift = 5.*range3 / 10.;  
	if (cat_num== "64390029")  theshift = 6.*range3 / 10.;  
	if (cat_num== "64390030")  theshift = 7.*range3 / 10.;  
	if (cat_num== "64390031")  theshift = 8.*range3 / 10.;  
	if (cat_num== "64390032")  theshift = 9.*range3 / 10.;  
	if (cat_num== "64390033")  theshift = range3;	        	
	*/	
	
	cat_num = cat_num+1;
	
	if (cat_num== 1)  theshift = 0.;
	if (cat_num== 2)  theshift = range1 / 10.;
	if (cat_num== 3)  theshift = 2.*range1 / 10.;
	if (cat_num== 4)  theshift = 3.*range1 / 10.;
	if (cat_num== 5)  theshift = 4.*range1 / 10.;
	if (cat_num== 6)  theshift = 5.*range1 / 10.;
	if (cat_num== 7)  theshift = 6.*range1 / 10.;  
	if (cat_num== 8)  theshift = 7.*range1 / 10.;  
	if (cat_num== 9)  theshift = 8.*range1 / 10.;  
	if (cat_num== 10)  theshift = 9.*range1 / 10.;  
	if (cat_num== 11)  theshift = range1;
	if (cat_num== 12)  theshift = 0.;
	if (cat_num== 13)  theshift = range2 / 10.;
	if (cat_num== 14)  theshift = 2.*range2 / 10.;  
	if (cat_num== 15)  theshift = 3.*range2 / 10.;  
	if (cat_num== 16)  theshift = 4.*range2 / 10.;  
	if (cat_num== 17)  theshift = 5.*range2 / 10.;  
	if (cat_num== 18)  theshift = 6.*range2 / 10.;  
	if (cat_num== 19)  theshift = 7.*range2 / 10.;  
	if (cat_num== 20)  theshift = 8.*range2 / 10.;  
	if (cat_num== 21)  theshift = 9.*range2 / 10.;  
	if (cat_num== 22)  theshift = range2;		
	if (cat_num== 23)  theshift = 0.;		
	if (cat_num== 24)  theshift = range3 / 10.;	
	if (cat_num== 25)  theshift = 2.*range3 / 10.;  
	if (cat_num== 26)  theshift = 3.*range3 / 10.;  
	if (cat_num== 27)  theshift = 4.*range3 / 10.;  
	if (cat_num== 28)  theshift = 5.*range3 / 10.;  
	if (cat_num== 29)  theshift = 6.*range3 / 10.;  
	if (cat_num== 30)  theshift = 7.*range3 / 10.;  
	if (cat_num== 31)  theshift = 8.*range3 / 10.;  
	if (cat_num== 32)  theshift = 9.*range3 / 10.;  
	if (cat_num== 33)  theshift = range3;				
	
	return theshift;
}
TString MakeGoodPlot::int2ss(int theint)
{
	std::ostringstream thess;
	thess << theint;
	TString string_out = thess.str();
	return string_out;
}
std::string MakeGoodPlot::TString2string(TString the_abomination)
{
	std::ostringstream thess;
	thess << the_abomination;
	std::string string_out = thess.str();
	return string_out;
}
