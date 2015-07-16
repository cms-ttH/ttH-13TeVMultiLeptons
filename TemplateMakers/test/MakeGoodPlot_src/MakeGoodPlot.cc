// created by Geoff Smith

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

#include "../variables.h"
//#include "../sample_lists.h"
//#include "justtthhnonbb_with_triggervect.h"
//
#include "justtthhnonbb_without_miniso.h"
//#include "justtthhnonbb_charlie_acceptance.h"


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
                bool passes_SSee(int sample_number);
                bool passes_SSemu(int sample_number);
                bool passes_SSmumu(int sample_number);
                bool passes_3l(int sample_number);
                bool passes_4l(int sample_number);

	public:	
                void fourlstudies(std::vector<int> samps);
                void threelstudies(std::vector<int> samps);
                void lepstudies(std::vector<int> samps);
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


//// June 2015: moved a lot of member functions to separate header files.. to be included here:


#include "initialize.h"  // <- required
#include "loadsamples2.h"  // <- required
//#include "drawROCiso.h"
#include "printcutflow.h"
#include "someutils.h"
#include "categories.h"
//#include "trigger_studies.h"
//#include "lepstudies.h"
//#include "4lstudies.h"
#include "3lstudies.h"

//_______________________________________________________________

// what is left (mainly drawing-specific functions):



/////////////////////////////////////
////////////  public fns ////////////

// get several quantities to compare from ntuples, and plot them using compareplots
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
                
        
        }
	   
        
    compareplots(samps, tempfilenames);
       
    
}


/// name says it all (uses get_hist_of_simple_variable)
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



void MakeGoodPlot::draw_2D_plot(std::vector<int> samps)
{
    
    	int numsamples = samps.size();
	
	//TH2D *sample_hist[numsamples][5];
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
	
	
	for (int i=0; i<numsamples; i++)
	{
            int samp_int = samps[i];
    
            cout << "doing " << sample_names[samp_int] << endl;
            for (int blah=0; blah<5; blah++) 
	    {
                mgp_sample_hist_2D[i][blah] = new TH2D("blah " + sample_names[samp_int] + int2ss(blah),";awert",20,0,25,20,0,25);
                mgp_sample_hist_2D[i][blah]->Sumw2();
            }
            
            get_hist_of_simple_variable_2D(samp_int,i);
            
	    // float sample_evts = sample_hist[i]->Integral();
// 	    std::ostringstream sample_evts_ss;
// 	    sample_evts_ss << sample_evts;
// 	    std::string sample_evts_string = sample_evts_ss.str();
            for (int blah=0; blah<5; blah++) 
	    {
                //mgp_sample_hist_2D[i][blah]->Scale(10000. * xsecs[samp_int] / (400.*numgen[samp_int]) ); // scaling is AVGD over 400 bins
                for (int k=1; k<=20; k++)
                {
                    for (int j=1; j<=20; j++)
                    {
                        double bincont = mgp_sample_hist_2D[i][blah]->GetBinContent(k,j);
                        mgp_sample_hist_2D[i][blah]->SetBinContent(k,j, (bincont * 10000. * xsecs[samp_int] / numgen[samp_int]) ); // each individual bin is scaled
                    }
                }
                
            }
            
            
            
        }
    
                
        
        // do s/sqrt(b) study (where you know which one is the signal):
        
        TH2D *sumbkgd[5];
        TH2D *signal[5];
        
        for (int blah=0; blah<5; blah++) 
	{
        

            signal[blah] = (TH2D*)mgp_sample_hist_2D[0][blah]->Clone("signal"+int2ss(blah));

            for (int i=1; i<numsamples; i++)
	    {
                if (i==1) sumbkgd[blah] = (TH2D*)mgp_sample_hist_2D[i][blah]->Clone("sumbkgd"+int2ss(blah));
                else sumbkgd[blah]->Add(mgp_sample_hist_2D[i][blah]);
            }


            for (int i=1; i<=20; i++)
            {
                for (int j=1; j<=20; j++)
                {
                    double bincont = sumbkgd[blah]->GetBinContent(i,j);
                    sumbkgd[blah]->SetBinContent(i,j,sqrt(bincont));
                }
            }

            //signal[blah]->Divide(sumbkgd[blah]);

            signal[blah]->SetStats(0);
            signal[blah]->GetXaxis()->SetTitle("lep 1 pt");
            signal[blah]->GetYaxis()->SetTitle("lep 2 pt");
            
            TCanvas *heybuddy = new TCanvas("hey"+int2ss(blah),"hey"+int2ss(blah),150,10,990,660);
            
            signal[blah]->Draw("COLZ,TEXT");   
    
        }
    
}
//_______________________________________________________________





//////////////////////////////////////
////////////  private fns ////////////

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
		
                int gpsize = (*pruned_genParticles_intree).size();
                
                for (int j=0; j<gpsize; j++)
                {
                    int chil0 = (int)(*pruned_genParticles_intree)[j].child0;
                    //if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil0<gpsize)) plot->Fill( (*pruned_genParticles_intree)[(*pruned_genParticles_intree)[j].child0].pdgID, weight);
                    if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil0<gpsize)) plot->Fill( (*pruned_genParticles_intree)[j].status, weight);
                                        
                    //chil0 = gpsize - chil0;
                    //if ((*pruned_genParticles_intree)[j].pdgID==25) plot->Fill( chil0, weight );
                }                

	}

}


void MakeGoodPlot::get_hist_of_simple_variable_2D(int sample_number, int sample_index)
{
	        
        ch[sample_number]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
        ch[sample_number]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
        ch[sample_number]->SetBranchAddress("preselected_muons", &preselected_muons_intree);

        ch[sample_number]->SetBranchAddress("looseMvaBased_leptons", &looseMvaBased_leptons_intree);
        ch[sample_number]->SetBranchAddress("looseMvaBased_electrons", &looseMvaBased_electrons_intree);
        ch[sample_number]->SetBranchAddress("looseMvaBased_muons", &looseMvaBased_muons_intree);

        ch[sample_number]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
        ch[sample_number]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
        ch[sample_number]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);
        
        ch[sample_number]->SetBranchAddress("met", &met_intree);
        
        ch[sample_number]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
        ch[sample_number]->SetBranchAddress( "wgt", &wgt_intree );
        
	cout << sample_number << endl;
	cout << ch[sample_number]->GetEntries() << endl;
	
        int theEntries = ch[sample_number]->GetEntries();
        
	for (Int_t i=0;i<theEntries;i++)
	{
		int catswitch=-1;
                
                ch[sample_number]->GetEntry(i);
	        
                //if (!(i%10000)) cout << i << endl;
                		
		weight = wgt_intree;
                
                double step = 1.25;                
                double lowpt = 0.;
                double highpt = 25.;
                
                int numits = (highpt - lowpt) / step;
                                                                
                //if (!(passes_common(sample_number) && passes_SSee(sample_number))) continue;                
                //if (sample_number==5) weight *= 1.55;
                
//                 switch (catswitch)
//                 {                
//                     case 1: if (!(passes_common(sample_number) && passes_SSee(sample_number))) {continue;} break;   
//                     case 2: if (!(passes_common(sample_number) && passes_SSmumu(sample_number))) {continue;} break;
//                     case 3: if (!(passes_common(sample_number) && passes_SSemu(sample_number))) {continue;} break;
//                     case 4: if (!(passes_common(sample_number) && passes_3l(sample_number))) {continue;} break;
//                     case 5: if (!(passes_common(sample_number) && passes_4l(sample_number))) {continue;} break;
//                 }
                
                if (passes_common(sample_number))
                {
                    if (passes_SSee(sample_number)) catswitch=0;
                    else if (passes_SSmumu(sample_number)) catswitch=1;
                    else if (passes_SSemu(sample_number)) catswitch=2;
                    else if (passes_3l(sample_number)) catswitch=3;
                    else if (passes_4l(sample_number)) catswitch=4;
                }
                
                
                if (catswitch>-1)
                {
                    
                    if (sample_number==5) // ttjets
                    {
                        switch (catswitch)
                        {
                            case 0: weight *= 1.55; break;
                            case 1: weight *= 3.3; break;
                            case 2: weight *= 1.87; break;
                            case 3: weight *= 2.85; break;
                            case 4: break;
                        }
                    }
                    
                    
                    double ptcutx = 0.;

                    for (int i=0; i<=numits; i++)
                    {
                        double ptcuty = 0.;

                        for (int j=0; j<=numits; j++)
                        {                
                            if ((*preselected_leptons_intree).size()>1)
                            {                        
                                
                                if (catswitch<3 && (*tightMvaBased_leptons_intree).size()==2 && (*looseMvaBased_leptons_intree).size()<4)
                                {                                                                
                                    if ( ((*tightMvaBased_leptons_intree)[0].obj.Pt()>ptcutx) && ((*tightMvaBased_leptons_intree)[1].obj.Pt()>ptcuty) )
                                    {                                
                                        mgp_sample_hist_2D[sample_index][catswitch]->Fill(ptcutx,ptcuty,weight);
                                    }
                                }
                                
                                if (catswitch==3 && (*tightMvaBased_leptons_intree).size()==3 && (*looseMvaBased_leptons_intree).size()<4)
                                {
                                    if ( ((*tightMvaBased_leptons_intree)[0].obj.Pt()>ptcutx) && ((*tightMvaBased_leptons_intree)[1].obj.Pt()>ptcuty) )
                                    {                                
                                        mgp_sample_hist_2D[sample_index][catswitch]->Fill(ptcutx,ptcuty,weight);
                                    }
                                
                                }
                                
                                if (catswitch==4 && (*looseMvaBased_leptons_intree).size()==4)
                                {
                                    if ( ((*looseMvaBased_leptons_intree)[0].obj.Pt()>ptcutx) && ((*looseMvaBased_leptons_intree)[1].obj.Pt()>ptcuty) )
                                    {                                
                                        mgp_sample_hist_2D[sample_index][catswitch]->Fill(ptcutx,ptcuty,weight);
                                    }
                                
                                
                                }
                            }

                            ptcuty += step;

                        }

                        ptcutx += step;
                    }
                }
                
                

	}

}




