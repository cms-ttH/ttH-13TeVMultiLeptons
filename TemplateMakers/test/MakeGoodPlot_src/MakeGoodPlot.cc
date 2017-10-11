// created by Geoff Smith 2010.
//
// Flexible class for conveniently making plots, dumping tables, etc., usually from analysis trees.
// This is the main file that declares the MakeGoodPlot class and associated member variables/functions.
// See makegoodplot.C for how to use.
// You declare new stuff here, and then define it in separate header files (see below).
//

#include "TSystem.h"
#include "TFile.h"
#include "TColor.h"
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
#include "TChainElement.h"

#include "../variables.h"
#include "../sample_lists.h"

#include "ttH-13TeVMultiLeptons/TemplateMakers/test/eventReconstructor.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)

#include "TMVA/Config.h"
// #include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#pragma omp parallel for

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
                TH2D *mgp_sample_hist_2D[50][10];
		
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
		
                vector<std::string> *passTrigger_intree=0; // manually initialize this (ttH::* objects are intialized automatically)
                
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
                void setBranchAddresses(int sample_number);
		void get_hist_of_tiered_MVA_response_for_one_sample_5j4t(TH1 *plot, int sample_number=1);
		void get_hist_of_tiered_MVA_response_for_one_sample_6j4t(TH1 *plot, int sample_number=1);
		void get_hist_MVA_response_for_one_sample_643203(TH1 *plot, int sample_number=1);
		void get_hist_of_tiered_MVA_response_for_one_sample_as_function_of_category(TH1 *plot, int sample_number=1, TString cat_num="000");
		void get_hist_of_tiered_MVA_response_for_one_sample_643900XX(int sample_number=1, int samp_it=0);
		//double get_gaus_shift(TString cat_num="000", int sample_number=1);
		double get_gaus_shift(int cat_num=0, int sample_number=1);
		void get_roc_curve(TH1F *sig, TH1F *bkgd, int roc_curve_index); //int &npts, double (&effS)[500], double (&bckR)[500]);
		void get_hist_of_simple_variable(TH1 *plot, int sample_number=1, TH1 *plot2 = 0, TH1 *plot3 = 0);
                void get_hist_of_simple_variable_2D(int sample_number, int sample_index);
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
                
                bool passes_common(int sample_number);
                bool passes_2lss(int sample_number);
                bool passes_SSee(int sample_number);
                bool passes_SSemu(int sample_number);
                bool passes_SSmumu(int sample_number);
                bool passes_3l(int sample_number);
                bool passes_geq3l(int sample_number);
                bool passes_4l(int sample_number);
                bool passes_2lSS_Andrew(int sample_number);
                bool passes_2muSS_Andrew(int sample_number);
                
                template <typename almostTLVtype> TLorentzVector makeTLV( almostTLVtype thing );
                double getNumInitialMCevents (int sample);

	public:	
                void MatchTester_ttW_SS(std::vector<int> samps);
                void fourlstudies(std::vector<int> samps);
                void threelstudies(std::vector<int> samps);
                void lepstudies(std::vector<int> samps);
	        void lepptstudies(std::vector<int> samps);	        
                void trigger_studies(std::vector<int> samps);
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
                void draw_2D_plot(std::vector<int> samps);
                void addvarstotree(std::vector<int> samps);
                void draw_eff_curves(std::vector<int> samps);
		
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


// June 2015: moved a lot of member functions to separate header files.. to be included here.
// Oct 2017: moved the rest to separate header files. If you want to add some functionality,
// just implement it as a new member function and include it here. Take a look at the header
// files in this directory for examples.

#include "initialize.h"                 // <- always required (sets up tree branch addresses, etc.)
#include "loadsamplesNDPCs.h"           // <- always required (handles loading of samples)
#include "gethistofsimplevariable.h"    // <- often required
#include "draw.h"                       // <- often required
//#include "drawROCiso.h"
#include "drawROCcurvesold.h"
//#include "printcutflow.h"
#include "someutils.h"
#include "categories.h"
//#include "addvarstotree.h"
//#include "trigger_studies.h"
//#include "lepstudies.h"
//#include "4lstudies.h"
//#include "3lstudies.h"
//#include "lepptstudies.h"
//#include "matchtest.h"

//_______________________________________________________________

