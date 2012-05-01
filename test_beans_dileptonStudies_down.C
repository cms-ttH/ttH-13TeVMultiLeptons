#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH3.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath> 
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"

#include "LumiReweightingStandAlone.h"
#include "PUConstants.h"

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

//Headers for the data items
#include "ProductArea/BNcollections/interface/BNelectron.h"
#include "ProductArea/BNcollections/interface/BNevent.h"
#include "ProductArea/BNcollections/interface/BNjet.h"
#include "ProductArea/BNcollections/interface/BNmcparticle.h"
#include "ProductArea/BNcollections/interface/BNmet.h"
#include "ProductArea/BNcollections/interface/BNmuon.h"
#include "ProductArea/BNcollections/interface/BNphoton.h"
#include "ProductArea/BNcollections/interface/BNsupercluster.h"
#include "ProductArea/BNcollections/interface/BNtrack.h"
#include "ProductArea/BNcollections/interface/BNtrigger.h"
#include "ProductArea/BNcollections/interface/BNskimbits.h"
#include "ProductArea/BNcollections/interface/BNtrigobj.h"
#include "ProductArea/BNcollections/interface/BNprimaryvertex.h"

#include "AnglesUtil.h"

#endif

using std::string;
using std::cout;
using std::endl;

//******************************************************************************
typedef std::vector<double> vdouble;
typedef std::vector<std::vector<double> > vvdouble;
typedef std::vector<std::vector<std::string> > vvstring;
typedef std::vector<string> vstring;
typedef std::vector<bool> vbool;
typedef std::vector<int> vint;

double getJERfactor( int returnType, double jetAbsETA, double genjetPT, double recojetPT );
void calculateTagProb( int useSample, std::vector<double> jetPts, std::vector<double> jetEtas, std::vector<double> jetTags, std::vector<int> jetIds, 
		       double &Prob0, double &ProbGEQ1, double &Prob1, double &ProbGEQ2, double &Prob2, double &ProbGEQ3,double &Prob3, double &ProbGEQ4,
		       int returnType, const double extraSFb, const double extraSFc, const double extraSFl ); 

double jetTagProb( double jetPT, double jetETA, double jetTag, int jetID, 
		  int returnType, const double extraSFb, const double extraSFc, const double extraSFl );

//bool filterTTbarPlusJets(string selectEventType, std::vector<BNmcparticle> mcparticles);

//******************************************************************************


// here is where you can change the btag threshold

// Medium combined tag threshold
double btagThres = 0.679;

// super loose combined tag threshold
//double btagThres = 0.244;

// declare additional functions:

//void getSp(TLorentzVector lepton, TLorentzVector met, TLorentzVector jets[100], int nJets, float &aplanarity, float &sphericity);
// void getFox(TLorentzVector lepton, TLorentzVector met, TLorentzVector jets[100], int nJets, float &h0, float &h1, float &h2, float &h3, float &h4);
// void getFox_mod(TLorentzVector lepton, TLorentzVector met, TLorentzVector jets[100], int nJets, float ht, float &h0_mod, float &h1_mod, float &h2_mod, float &h3_mod, float &h4_mod);
// void getFox_mod2(TLorentzVector lepton, TLorentzVector met, TLorentzVector jets[100], int nJets, float ht, float &h0_mod2, float &h1_mod2, float &h2_mod2, float &h3_mod2, float &h4_mod2,  float &h5_mod2,  float &h6_mod2, float &h7_mod2, float &h8_mod2, float &h9_mod2, float &h10_mod2);




void test_beans_dileptonStudies_down( int maxNentries, string sampleName, int iJob, string iLabel ) {

  typedef BNeventCollection::const_iterator         EventIter;
  typedef BNelectronCollection::const_iterator      EleIter;
  typedef BNjetCollection::const_iterator           JetIter;
  typedef BNmcparticleCollection::const_iterator    MCparIter;
  typedef BNmetCollection::const_iterator           MetIter;
  typedef BNmuonCollection::const_iterator          MuonIter;
  typedef BNphotonCollection::const_iterator        PhotonIter;
  typedef BNprimaryvertexCollection::const_iterator PVIter;
  typedef BNskimbitsCollection::const_iterator      SkimBitIter;
  typedef BNsuperclusterCollection::const_iterator  SCIter;
  typedef BNtrackCollection::const_iterator         TrackIter;
  typedef BNtriggerCollection::const_iterator       TrigIter;
  typedef BNtrigobjCollection::const_iterator       TrigObjIter;


  // Used for PU re-weighting
  std::vector< float > DataDist2011_it;
  std::vector< float > MCDist2011_it;
  for( int i=0; i<35; i++ ){
    DataDist2011_it.push_back(pu::ObsDist2011_f[i]);
    MCDist2011_it.push_back(pu::PoissonOneXDist_f[i]);
  }
  reweight::LumiReWeighting lumiWeights_it = reweight::LumiReWeighting( MCDist2011_it, DataDist2011_it );

  ////pile up Robin
  TFile *f_pu = new TFile("collect_pileup_histos_v1_histo.root");

  std::string str_data;
  str_data = "SingleMu";
  //  str_data = "ElectronHad";

  TH1D* h_pu_data;
  TH1D* h_pu_data_up;
  TH1D* h_pu_data_down;
  TH1D* h_pu_mc;
  int insample = 0;
  if ( sampleName == "ttH_m120") insample = 120 ;

  if( (insample>=100 && insample<=140) || (insample==2523) || (insample==2524) ){
    h_pu_data      = (TH1D*)f_pu->Get((std::string("h_pileup_" + str_data + "_68000_observed")).c_str());
    h_pu_data_up   = (TH1D*)f_pu->Get((std::string("h_pileup_" + str_data + "_73440_observed")).c_str());
    h_pu_data_down = (TH1D*)f_pu->Get((std::string("h_pileup_" + str_data + "_62560_observed")).c_str());

    h_pu_mc = (TH1D*)f_pu->Get("h_ttH_numGenPV");
  }
  else{
    h_pu_data      = (TH1D*)f_pu->Get((std::string("h_pileup_" + str_data + "_68000_true")).c_str());
    h_pu_data_up   = (TH1D*)f_pu->Get((std::string("h_pileup_" + str_data + "_73440_true")).c_str());
    h_pu_data_down = (TH1D*)f_pu->Get((std::string("h_pileup_" + str_data + "_62560_true")).c_str());

    h_pu_mc = (TH1D*)f_pu->Get("F2011exp");
  }

  h_pu_data->Scale( 1./h_pu_data->Integral() );
  h_pu_data_up->Scale( 1./h_pu_data_up->Integral() );
  h_pu_data_down->Scale( 1./h_pu_data_down->Integral() );

  h_pu_mc->Scale( 1./h_pu_mc->Integral() );

  TH1D* h_pu_ratio      = (TH1D*)h_pu_data->Clone();
  TH1D* h_pu_ratio_up   = (TH1D*)h_pu_data_up->Clone();
  TH1D* h_pu_ratio_down = (TH1D*)h_pu_data_down->Clone();

  h_pu_ratio->Divide( h_pu_mc );
  h_pu_ratio_up->Divide( h_pu_mc );
  h_pu_ratio_down->Divide( h_pu_mc );


  // Load the files
  vstring fileNames;

  //fileNames.push_back("file:/store/user/slaunwhj/TTJets_TuneZ2_7TeV-madgraph-tauola/ttbar_BEAN_Fall11_atND_v1/bf3f7e6eadefdfce276392fc368ccaeb/pat_42x_fall11_withANDfilter_ttbar_366_1_sH5.root");



  //====================== TTH samples   ==============================

  string listFileName("lists/"+ sampleName + ".list");
  ifstream listOfFiles(listFileName.c_str());
  string iFileName;
  int nLines = 0;

  std::cout << "iJob = " << iJob << "  searching for input file in " << listFileName << "..." << std::endl;
  
  if (listOfFiles.is_open())
    {
      while ( listOfFiles.good() )
        {
          getline(listOfFiles, iFileName);
          
          if (iFileName.find(".root") != string::npos){
            if ( nLines == iJob ){
              cout << "Line = " << nLines << ", Name = " <<iFileName << endl;
              fileNames.push_back(iFileName);
            }
          } else {
            cout << "Line " << nLines << " doesn't have .root file in it " << endl;
          }
          nLines++;
        }
      listOfFiles.close();
    }

  if (fileNames.size() < 1 ){
    cout << "You don't have any files in your list... this is is probably bad... exiting" << endl;
    exit(22);
  }

  
  // Name of file containing histograms
  std::stringstream outFileName;
  outFileName <<"batchBEAN/" << sampleName << "_" << iLabel << "/test_beans_v1_" << sampleName << "_" << iLabel << "_job_" << iJob << ".root";
  std::string histofilename = outFileName.str();
  std::cout << "Writing out to file " << histofilename << endl;


  // Print out your config

  std::cout << "Using btag threshold " << btagThres << std::endl;

  
  // Creates a ChainEvent, allowing files to be linked   
  fwlite::ChainEvent ev(fileNames);   

  TFile histofile(histofilename.c_str(),"recreate");

  histofile.cd();


  //////////////////////////////////////////////////////////////////////////
  ///  Booking Histograms
  //////////////////////////////////////////////////////////////////////////


  // Variables used for histogram ranges and binning
  double metmax   = 500.;
  double muptmax  = 350.;
  double jetptmax = 500.;
  double massmax  = 200.;

  int NmetBins   = int( metmax/10. + 0.0001 );
  int NmuptBins  = int( muptmax/10. + 0.0001 );
  int NjetptBins = int( jetptmax/10. + 0.0001 );
  int NmassBins  = int( massmax/1. + 0.0001 );


  // Book the histograms

  TH1D* h_mu_pt = new TH1D("h_mu_pt",";#mu p_{T}", NmuptBins, 0, muptmax );
  TH1D* h_mu_phi = new TH1D("h_mu_phi",";#mu #phi", 16, -3.2, 3.2 );
  TH1D* h_mu_eta = new TH1D("h_mu_eta",";#mu #eta", 25, -2.5, 2.5 );
  TH1D* h_dR_mu_hlt = new TH1D("h_dR_mu_hlt",";#DeltaR(#mu,hlt #mu)", 120, 0., 6. );

  TH1D* h_jet_pt = new TH1D("h_jet_pt",";jet p_{T}", NjetptBins, 0, jetptmax );
  TH1D* h_jet_phi = new TH1D("h_jet_phi",";jet #phi", 16, -3.2, 3.2 );
  TH1D* h_jet_eta = new TH1D("h_jet_eta",";jet #eta", 25, -2.5, 2.5 );

  TH1D* h_jet_pt_b = new TH1D("h_jet_pt_b",";b jet p_{T}", NjetptBins, 0, jetptmax );
  TH1D* h_jet_pt_c = new TH1D("h_jet_pt_c",";c jet p_{T}", NjetptBins, 0, jetptmax );
  TH1D* h_jet_pt_l = new TH1D("h_jet_pt_l",";light jet p_{T}", NjetptBins, 0, jetptmax );

  TH1D* h_jet_disc_b = new TH1D("h_jet_disc_b",";b jet SSVHE discriminant", 70, -1.0, 6.0 );
  TH1D* h_jet_disc_c = new TH1D("h_jet_disc_c",";c jet SSVHE discriminant", 70, -1.0, 6.0 );
  TH1D* h_jet_disc_l = new TH1D("h_jet_disc_l",";light jet SSHVE discriminant", 70, -1.0, 6.0 );

  TH1D* h_met_pt = new TH1D("h_met_pt",";MET p_{T}", NmetBins, 0, metmax );
  TH1D* h_met_phi = new TH1D("h_met_phi",";MET #phi", 16, -3.2, 3.2 );
  TH1D* h_met_Upt = new TH1D("h_met_Upt",";MET raw p_{T}", NmetBins, 0, metmax );
  TH1D* h_met_Uphi = new TH1D("h_met_Uphi",";MET raw #phi", 16, -3.2, 3.2 );

  TH2D* h_W0_decay_W1_decay = new TH2D("h_W0_decay_W1_decay",";W0 decay;W1 decay", 13, 0, 13, 13, 0, 13 );
  TH1D* h_H_decay = new TH1D("h_H_decay",";H decay", 9, 0, 9 );
  TH1D* h_H_mass = new TH1D("h_H_mass",";H mass", NmassBins, 0, massmax );


  std::vector<std::string> Wdecay_names;
  Wdecay_names.push_back("ud");
  Wdecay_names.push_back("us");
  Wdecay_names.push_back("ub");
  Wdecay_names.push_back("cd");
  Wdecay_names.push_back("cs");
  Wdecay_names.push_back("cb");
  Wdecay_names.push_back("td");
  Wdecay_names.push_back("ts");
  Wdecay_names.push_back("tb");
  Wdecay_names.push_back("e#nu");
  Wdecay_names.push_back("#mu#nu");
  Wdecay_names.push_back("#tau#nu");
  Wdecay_names.push_back("Other");

  int numWdecays = int(Wdecay_names.size());

  for( int i=0; i<numWdecays; i++ ){
    h_W0_decay_W1_decay->GetXaxis()->SetBinLabel(i+1,Wdecay_names[i].c_str());
    h_W0_decay_W1_decay->GetYaxis()->SetBinLabel(i+1,Wdecay_names[i].c_str());
  }

  std::vector<std::string> Hdecay_names;
  Hdecay_names.push_back("b#bar{b}");
  Hdecay_names.push_back("WW");
  Hdecay_names.push_back("#tau#tau");
  Hdecay_names.push_back("gg");
  Hdecay_names.push_back("#gamma#gamma");
  Hdecay_names.push_back("ZZ");
  Hdecay_names.push_back("c#bar{c}");
  Hdecay_names.push_back("Z#gamma");
  Hdecay_names.push_back("Other");

  int numHdecays = int(Hdecay_names.size());

  for( int i=0; i<numHdecays; i++ ) h_H_decay->GetXaxis()->SetBinLabel(i+1,Hdecay_names[i].c_str());


  // Used to determine number of events that pass each cut

  std::vector<std::string> cutflow_name;
  cutflow_name.push_back("All Events"); //0 
  cutflow_name.push_back("Cleaning"); //1
  cutflow_name.push_back("Trigger"); //2
  cutflow_name.push_back("*** >=1 tight muon");//3
  cutflow_name.push_back("==2 tight muon"); //4
  cutflow_name.push_back(" >= 2 jets");//5
  cutflow_name.push_back(">=2 b-tagged jets"); //6
  cutflow_name.push_back(">=3 jets"); //7
  cutflow_name.push_back(">=3 b-tagged jets"); //8
  cutflow_name.push_back("*** ==1 mu && ==1 ele"); //9
  cutflow_name.push_back(">=2 jets"); //10
  cutflow_name.push_back(">=2 b-tagged jets"); //11
  cutflow_name.push_back(">=3 jets"); //12
  cutflow_name.push_back(">=3 b-tagged jets"); //13
  cutflow_name.push_back("*** ==2 ele"); //14
  cutflow_name.push_back(">=2 jets"); //15
  cutflow_name.push_back(">=2 b-tagged jets"); //16
  cutflow_name.push_back(">=3 b-tagged jets"); //17
  cutflow_name.push_back(">=3 b-tagged jets"); //18


  int Ncuts = int(cutflow_name.size());

  // cutflow
  TH1D* h_cutflow_unwgt = new TH1D("h_cutflow_unwgt","",Ncuts, 0, Ncuts);
  TH1D* h_cutflow = new TH1D("h_cutflow","",Ncuts, 0, Ncuts);
  for( int i=0; i<Ncuts; i++ ){
    h_cutflow->GetXaxis()->SetBinLabel(i+1,cutflow_name[i].c_str());
    h_cutflow_unwgt->GetXaxis()->SetBinLabel(i+1,cutflow_name[i].c_str());
  }


  std::vector<std::string> selector_name;

  for( int i=0; i<int(cutflow_name.size()); i++ ) selector_name.push_back(cutflow_name[i]);

  int numSelectors = selector_name.size();
  std::vector<std::vector<double> > selected(numSelectors, std::vector<double>(3) );
  std::vector<std::vector<double> > selected_wgt(numSelectors, std::vector<double>(3) );

  TH2D* h_cutflow_expand = new TH2D("h_cutflow_expand","", 3, 0, 3, numSelectors, 0, numSelectors );
  TH2D* h_cutflow_expand_wgt = new TH2D("h_cutflow_expand_wgt","", 3, 0, 3, numSelectors, 0, numSelectors );

  for( int i=0; i<numSelectors; i++ ){
    h_cutflow_expand->GetYaxis()->SetBinLabel(numSelectors-i,selector_name[i].c_str());
    h_cutflow_expand_wgt->GetYaxis()->SetBinLabel(numSelectors-i,selector_name[i].c_str());
    for( int j=0; j<3; j++ ){
      selected[i][j]=0.;
      selected_wgt[i][j]=0.;
      if( i==0 ){
	if( j==0 ){
	  h_cutflow_expand->GetXaxis()->SetBinLabel(j+1,"Selected");
	  h_cutflow_expand_wgt->GetXaxis()->SetBinLabel(j+1,"Selected");
	}
	else if( j==1 ){
	  h_cutflow_expand->GetXaxis()->SetBinLabel(j+1,"N - 1");
	  h_cutflow_expand_wgt->GetXaxis()->SetBinLabel(j+1,"N - 1");
	}
	else if( j==2 ){
	  h_cutflow_expand->GetXaxis()->SetBinLabel(j+1,"Cumulative");
	  h_cutflow_expand_wgt->GetXaxis()->SetBinLabel(j+1,"Cumulative");
	}
      }
    }
  }

  ///////////////////////////////////////////////////////////////////
  //
  // Make a small tree called summaryTree that stores all your 
  // information event by events
  //
  ///////////////////////////////////////////////////////////////////

  std::map<TString, int *> intBranches;
  ///---- categories lable
  intBranches["PassTwoLepton"] = new int (0);
  intBranches["TwoMuon"] = new int (0);
  intBranches["TwoEle"] = new int (0);
  intBranches["MuonEle"] = new int (0);

  intBranches["numJets"] = new int (0);
  intBranches["numTaggedJets"] = new int (0);
  intBranches["numNonTaggedJets"] = new int (0);

  intBranches["numTightMuons"] = new int (0);
  intBranches["numLooseMuons"] = new int (0);
  intBranches["numTightElectrons"] = new int (0);
  intBranches["numLooseElectrons"] = new int (0);

  intBranches["isCleanEvent"] = new int (0);
  intBranches["isTriggerPass"] = new int (0);

  std::map<TString, unsigned int *> uintBranches;

  uintBranches["runNumber"] = new unsigned int (0);
  uintBranches["eventNumber"] = new unsigned int (0);
  uintBranches["luminosityBlock"] = new unsigned int (0);

  ////Robin ///------------variables--------------------
  std::map<TString, float *> floatBranches;
  //b-tag probabilities
  floatBranches["prob0"] = new float(0.0);
  floatBranches["prob1"] = new float(0.0);
  floatBranches["prob2"] = new float(0.0);
  floatBranches["prob3"] = new float(0.0);

  floatBranches["probge1"] = new float(0.0);
  floatBranches["probge2"] = new float(0.0);
  floatBranches["probge3"] = new float(0.0);
  floatBranches["probge4"] = new float(0.0);

  //SF hf
  floatBranches["prob0_SFhfup"] = new float(0.0);
  floatBranches["prob1_SFhfup"] = new float(0.0);
  floatBranches["prob2_SFhfup"] = new float(0.0);
  floatBranches["prob3_SFhfup"] = new float(0.0);

  floatBranches["probge1_SFhfup"] = new float(0.0);
  floatBranches["probge2_SFhfup"] = new float(0.0);
  floatBranches["probge3_SFhfup"] = new float(0.0);
  floatBranches["probge4_SFhfup"] = new float(0.0);

  floatBranches["prob0_SFhfdown"] = new float(0.0);
  floatBranches["prob1_SFhfdown"] = new float(0.0);
  floatBranches["prob2_SFhfdown"] = new float(0.0);
  floatBranches["prob3_SFhfdown"] = new float(0.0);

  floatBranches["probge1_SFhfdown"] = new float(0.0);
  floatBranches["probge2_SFhfdown"] = new float(0.0);
  floatBranches["probge3_SFhfdown"] = new float(0.0);
  floatBranches["probge4_SFhfdown"] = new float(0.0);

  //SF lf
  floatBranches["prob0_SFlfup"] = new float(0.0);
  floatBranches["prob1_SFlfup"] = new float(0.0);
  floatBranches["prob2_SFlfup"] = new float(0.0);
  floatBranches["prob3_SFlfup"] = new float(0.0);

  floatBranches["probge1_SFlfup"] = new float(0.0);
  floatBranches["probge2_SFlfup"] = new float(0.0);
  floatBranches["probge3_SFlfup"] = new float(0.0);
  floatBranches["probge4_SFlfup"] = new float(0.0);

  floatBranches["prob0_SFlfdown"] = new float(0.0);
  floatBranches["prob1_SFlfdown"] = new float(0.0);
  floatBranches["prob2_SFlfdown"] = new float(0.0);
  floatBranches["prob3_SFlfdown"] = new float(0.0);

  floatBranches["probge1_SFlfdown"] = new float(0.0);
  floatBranches["probge2_SFlfdown"] = new float(0.0);
  floatBranches["probge3_SFlfdown"] = new float(0.0);
  floatBranches["probge4_SFlfdown"] = new float(0.0);


  //pile up
  floatBranches["numPV"] = new float(0.0);
  floatBranches["weight"] = new float(0.0);
  floatBranches["weight_PUup"] = new float(0.0);
  floatBranches["weight_PUdown"] = new float(0.0);

  //met
  floatBranches["met"] = new float(0.0);
  floatBranches["unc_met"] = new float(0.0);

  ///lepton variables
  floatBranches["fstMuPt"] = new float(0.0);
  floatBranches["sndMuPt"] = new float(0.0);
  floatBranches["fstElePt"] = new float(0.0);
  floatBranches["sndElePt"] = new float(0.0);
  floatBranches["lep1Pt"] = new float(0.0);
  floatBranches["lep2Pt"] = new float(0.0);
  floatBranches["lep1Eta"] = new float(0.0);
  floatBranches["lep2Eta"] = new float(0.0);
  floatBranches["lep1Phi"] = new float(0.0);
  floatBranches["lep2Phi"] = new float(0.0);
  floatBranches["mass_leplep"] = new float(0.0);
  floatBranches["pt_leplep"] = new float(0.0);
  floatBranches["dPhi_leplep"] = new float(0.0);
  //  floatBranches["dEta_leplep"] = new float(0.0);
  floatBranches["dR_leplep"] = new float(0.0);

  /// jet variables
  floatBranches["numJets_float"] = new float (0);
  floatBranches["numTaggedJets_float"] = new float (0);

  floatBranches["first_jet_pt"] = new float(0.0);
  floatBranches["second_jet_pt"] = new float(0.0);
  floatBranches["third_jet_pt"] = new float(0.0);
  floatBranches["fourth_jet_pt"] = new float(0.0);

  floatBranches["min_dr_tagged_jets"] = new float(0.0);
  floatBranches["avg_dr_tagged_jets"] = new float(0.0);
  floatBranches["mindr_lep1_jet"] = new float(0.0);
  floatBranches["mindr_lep2_jet"] = new float(0.0);
  floatBranches["avg_tagged_dijet_mass"] = new float(0.0);
  floatBranches["avg_untagged_dijet_mass"] = new float(0.0);
  floatBranches["closest_tagged_dijet_mass"] = new float(0.0);
  floatBranches["M2_of_closest_tagged_jets"] = new float(0.0);

  floatBranches["avg_btag_disc_btags"] = new float(0.0);
  floatBranches["avg_btag_disc_non_btags"] = new float(0.0);
  floatBranches["dev_from_avg_disc_btags"] = new float(0.0);

  floatBranches["first_highest_btag"] = new float(0.0);
  floatBranches["second_highest_btag"] = new float(0.0);
  floatBranches["lowest_btag"] = new float(0.0);

  /////entire system variables
  floatBranches["mass_of_everything"] = new float(0.0);
  floatBranches["pt_of_everything"] = new float(0.0);
  floatBranches["sum_pt"] = new float(0.0); 
  floatBranches["all_sum_pt"] = new float(0.0);
  floatBranches["Ht"] = new float(0.0);

  //shape info
//   floatBranches["aplanarity"] = new float(0.0);  
//   floatBranches["sphericity"] = new float(0.0);	   
//   floatBranches["h0"] = new float(0.0);
//   floatBranches["h1"] = new float(0.0);
//   floatBranches["h2"] = new float(0.0);
//   floatBranches["h3"] = new float(0.0);
//   floatBranches["h4"] = new float(0.0);

//   floatBranches["h0_mod"] = new float(0.0);
//   floatBranches["h1_mod"] = new float(0.0);
//   floatBranches["h2_mod"] = new float(0.0);
//   floatBranches["h3_mod"] = new float(0.0);
//   floatBranches["h4_mod"] = new float(0.0);

//   floatBranches["h0_mod2"] = new float(0.0);
//   floatBranches["h1_mod2"] = new float(0.0);
//   floatBranches["h2_mod2"] = new float(0.0);
//   floatBranches["h3_mod2"] = new float(0.0);
//   floatBranches["h4_mod2"] = new float(0.0);
//   floatBranches["h5_mod2"] = new float(0.0);
//   floatBranches["h6_mod2"] = new float(0.0);
//   floatBranches["h7_mod2"] = new float(0.0);
//   floatBranches["h8_mod2"] = new float(0.0);
//   floatBranches["h9_mod2"] = new float(0.0);
//   floatBranches["h10_mod2"] = new float(0.0);
  
  histofile.cd();


  TTree * summaryTree = new TTree ("summaryTree", "Summary Event Values");

  for (std::map<TString, int*>::iterator iBranchMap = intBranches.begin();
       iBranchMap != intBranches.end();
       iBranchMap ++) {

    cout << "Creating branch  " << (iBranchMap->first).Data() << endl;
    TString tempTreeType = iBranchMap->first;
    tempTreeType += "/I";
    summaryTree->Branch(iBranchMap->first, iBranchMap->second, tempTreeType);

  }


  for (std::map<TString, unsigned int *>::iterator uBranchMap = uintBranches.begin();
       uBranchMap != uintBranches.end();
       uBranchMap ++) {

    cout << "Creating branch  " << (uBranchMap->first).Data() << endl;
    TString tempTreeType = uBranchMap->first;
    tempTreeType += "/i";
    summaryTree->Branch(uBranchMap->first, uBranchMap->second, tempTreeType);

  }

  ////Robin 
  for (std::map<TString, float*>::iterator iDMap = floatBranches.begin();
       iDMap != floatBranches.end();
       iDMap ++) {
    
    std::cout << "Creating branch   " << (iDMap->first).Data() << endl;
    TString ttString = iDMap->first;
    ttString += "/F";
    summaryTree->Branch(iDMap->first, iDMap->second, ttString);       
  }
  
  

  //////////////////////////////////////////////////////////////////////////
  ///  Event variables
  //////////////////////////////////////////////////////////////////////////

  // Triggers to be used
  //  vstring mc_hlt_trigger_collection;
  //mc_hlt_trigger_collection.push_back("HLT_IsoMu24_v");
  //mc_hlt_trigger_collection.push_back("HLT_IsoMu24_eta2p1_v");
  //mc_hlt_trigger_collection.push_back("HLT_DoubleMu7_v");

  // Trigger filter name associated with trigger above
//   vstring mc_hlt_filter_names;
//   mc_hlt_filter_names.push_back("hltSingleMuIsoL3IsoFiltered24::HLT");

  ////// ============== trigger ===========
  vstring mc_hlt_trigger_collection;

  mc_hlt_trigger_collection.push_back("HLT_DoubleMu7_v");
  mc_hlt_trigger_collection.push_back("HLT_Mu13_Mu8_v");
  mc_hlt_trigger_collection.push_back("HLT_Mu17_Mu8_v");

  mc_hlt_trigger_collection.push_back("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v");
  mc_hlt_trigger_collection.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  mc_hlt_trigger_collection.push_back("HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v");

  mc_hlt_trigger_collection.push_back("HLT_Mu17_Ele8_CaloIdL_v");
  mc_hlt_trigger_collection.push_back("HLT_Mu8_Ele17_CaloIdL_v");
  mc_hlt_trigger_collection.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v");
  mc_hlt_trigger_collection.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v");

  ///
  double minNDOF = 4;
  double maxAbsZ = 24;
  double maxd0   = 2.;

  int nevents=0;
  int nevents_pass_trigger=0;
  int nevents_pass_cleaning=0;

  double nevents_wgt=0;
  double nevents_pass_trigger_wgt=0;
  double nevents_pass_cleaning_wgt=0;

  int nentries = ev.size();
  std::cout << "\n\t Number of entries = " << nentries << std::endl;
  std::cout << "\t Max number of entries = " << maxNentries << std::endl;
  std::cout << "\n" << std::endl;


  int cnt = 0;


  int nEventsWhereJetRemoved = 0;
  
  //
  // Loop over events
  //
  std::cout << "========  Starting Event Loop  ========" << std::endl;
  try {
    for( ev.toBegin(); !ev.atEnd(); ++ev) {

      cnt++;

      if( cnt==1 )        std::cout << "     Event " << cnt << std::endl;
      if( cnt%100000==0 && cnt!=1 ) std::cout << "           " << cnt << "\t" 
					      << int(double(cnt)/double(nentries)*100) << "% done" << std::endl;

      if( cnt==(maxNentries+1) ) break;

      // initialize tree values 
      for (std::map<TString, int*>::iterator iBranchMap = intBranches.begin();
           iBranchMap != intBranches.end();
           iBranchMap ++) {
        // the memory address whose pointer we've saved should be initialized
        // to -1
        *(iBranchMap->second) = -1;
      }

      for (std::map<TString, unsigned int*>::iterator uBranchMap = uintBranches.begin();
             uBranchMap != uintBranches.end();
           uBranchMap ++) {
        
        *(uBranchMap->second) = 0;
        
      }
      
      ////Robin
      for (std::map<TString, float*>::iterator iDMap = floatBranches.begin();
	   iDMap != floatBranches.end();
	   iDMap ++) {
	
	* (iDMap->second)  = -9.99e3;
      }

      
      //std::cout << "========  Event! ========" << std::endl;
      // Get Handle for each collection used
      fwlite::Handle<BNeventCollection> h_event;
      h_event.getByLabel(ev,"BNproducer");
      BNeventCollection const &events = *h_event;

      fwlite::Handle<BNmuonCollection> h_muons;
      h_muons.getByLabel(ev,"BNproducer","selectedPatMuonsLoosePFlow");
      BNmuonCollection const &muons = *h_muons;

      fwlite::Handle<BNmetCollection> h_pfmet;
      h_pfmet.getByLabel(ev,"BNproducer","patMETsTypeIPFlow");
      BNmetCollection const &pfmets = *h_pfmet;

      fwlite::Handle<BNtriggerCollection> h_hlt;
      h_hlt.getByLabel(ev,"BNproducer","HLT");
      BNtriggerCollection const &hlt = *h_hlt;

      fwlite::Handle<BNprimaryvertexCollection> h_pvs;
      h_pvs.getByLabel(ev,"BNproducer","offlinePrimaryVertices");
      BNprimaryvertexCollection const &pvs = *h_pvs;

      fwlite::Handle<BNjetCollection> h_pfjets;
      h_pfjets.getByLabel(ev,"BNproducer","selectedPatJetsPFlow");
      BNjetCollection const &pfjets = *h_pfjets;

      fwlite::Handle<BNelectronCollection> h_electrons;
      h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsLoosePFlow");
      BNelectronCollection const &electrons = *h_electrons;

      fwlite::Handle<BNmcparticleCollection> h_mcparticles;
      h_mcparticles.getByLabel(ev,"BNproducer","MCstatus3");
      BNmcparticleCollection const &mcparticles = *h_mcparticles;

      fwlite::Handle<BNtrigobjCollection> h_hltobj;
      h_hltobj.getByLabel(ev,"BNproducer","HLT");
      BNtrigobjCollection const &hltobjs = *h_hltobj;


      // Some of the other collections in the tree that are not used here

      // fwlite::Handle<BNmuonCollection> h_muons;
      // h_muons.getByLabel(ev,"BNproducer","selectedPatMuons");
      // BNmuonCollection const &muons = *h_muons;

      // fwlite::Handle<BNmetCollection> h_calomet;
      // h_calomet.getByLabel(ev,"BNproducer","patMETsAK5Calo");
      // BNmetCollection const &calomets = *h_calomet;

      // fwlite::Handle<BNmetCollection> h_tcmet;
      // h_tcmet.getByLabel(ev,"BNproducer","patMETsTC");
      // BNmetCollection const &tcmets = *h_tcmet;

      // fwlite::Handle<BNmcparticleCollection> h_mcparticles;
      // h_mcparticles.getByLabel(ev,"BNproducer","MCstatus3");
      // BNmcparticleCollection const &mcparticles = *h_mcparticles;

      // fwlite::Handle<BNtriggerCollection> h_l1talgo;
      // h_l1talgo.getByLabel(ev,"BNproducer","L1Talgo");
      // BNtriggerCollection const &l1talgo = *h_l1talgo;

      // fwlite::Handle<BNtrigobjCollection> h_l1tmuonobj;
      // h_l1tmuonobj.getByLabel(ev,"BNproducer","L1MuonParticles");
      // BNtrigobjCollection const &l1tmuonobjs = *h_l1tmuonobj;

      // fwlite::Handle<BNtrackCollection> h_tracks;
      // h_tracks.getByLabel(ev,"BNproducer","generalTracks");
      // BNtrackCollection const &tracks = *h_tracks;

      // fwlite::Handle<BNjetCollection> h_calojets;
      // h_calojets.getByLabel(ev,"BNproducer","selectedPatJetsAK5Calo");
      // BNjetCollection const &calojets = *h_calojets;

      // fwlite::Handle<BNmcparticleCollection> h_mcelectrons;
      // h_mcelectrons.getByLabel(ev,"BNproducer","MCeleStatus1");
      // BNmcparticleCollection const &mcelectrons = *h_mcelectrons;

      // fwlite::Handle<BNphotonCollection> h_photons;
      // h_photons.getByLabel(ev,"BNproducer","selectedPatPhotons");
      // BNphotonCollection const &photons = *h_photons;


      /////////
      ///
      /// Event / MET
      ///
      ////////

      EventIter event = events.begin();

      int sample = event->sample;
      float weight = event->weight;

      double numTruePV = event->numTruePV;
      int numGenPV = event->numGenPV;

      int n0  = event->n0;

      float prescale = 1.;

      // Luminosity reweighting for the MC samples
      // NOTE: if running over only a fraction of the sample, that must be included in the weight

      if( sample==3410 ) prescale *= 1.26;

      float intLumi = 4470.;

      if( sample>=100 && sample<=140 )  prescale *= intLumi * 1./4653;
      if( sample==120 )                 prescale *= 1000000 * 1./999900;
      
      //       float wgt = prescale * weight;
      float wgt = 1 ;

      

      //============================================
      //
      // Filter out different kinds of ttbar events
      //
      //
      //===========================================

      if (sample==2500){

        
        bool keepEvent = false;


        bool debug_ = false;
        if (debug_) cout << "GENCUT: Sample is 2500" << endl;
   
        int ttbarType_;


        if( sampleName == "ttbar" ) ttbarType_ = 0;
        else if (sampleName == "ttbar_bb") ttbarType_ = 1;
        else if (sampleName == "ttbar_cc") ttbarType_ = 2;
        else {
          std::cout <<"ERROR: did not recognize ttbar sample type = " << sampleName
                    << std::endl
                    <<"Refusing to continue" << std::endl;
          assert(sampleName == "ttbar plus something");     
        }

        cout << "GENCUT: ttbarType_ is  " << ttbarType_ << endl;

        bool isWtoCS = false;

        if (debug_) cout << "Num MC particles = " << mcparticles.size() << std::endl
                         << "Num pfjets " <<  int(pfjets.size()) << std::endl
                         << "sample = " << sample;
   
        // check to see if the event has a c with a 
        // parent W
        for( int i=0; i< mcparticles.size(); i++ ){
          int id = mcparticles.at(i).id;
          int motherID = mcparticles.at(i).motherId;

          if (debug_) cout <<" Particle " << i << " has id " << id << endl;
          if( abs(id)==4  && abs(motherID)==24 ){
            isWtoCS = true;
            break;
          }
        }



        bool isBBbarEvent = false;
        bool isCCbarEvent = false;


        bool gotB = false;
        bool gotC = false;

        int numBmomB=0;
        int numBmomT=0;
        int numBbarmomBbar=0;
        int numBbarmomTbar=0;
        int numCmomC=0;
        int numCbarmomCbar=0;


        for( int i=0; i<int(pfjets.size()); i++ ){
          int id = pfjets.at(i).genPartonId;
          if( id==-99 ) continue;
          int motherID = pfjets.at(i).genPartonMotherId;

          // check to see if pf jets is from a  b/c and mother is a gluon
          // or, if mother is some light quark
          if( abs(id)==5 && ( motherID==21 || abs(motherID)<abs(id) ) ) gotB=true;
          if( abs(id)==4 && ( motherID==21 || abs(motherID)<abs(id) ) ) gotC=true;

          // if things are their own mother, 
          // where are they from? Does this mean stable?
          if( id==5  && motherID==id ) numBmomB++;
          if( id==-5 && motherID==id ) numBbarmomBbar++;

          if( id==4  && motherID==id ) numCmomC++;
          if( id==-4 && motherID==id ) numCbarmomCbar++;

          if( id==5  && motherID==6  ) numBmomT++;
          if( id==-5 && motherID==-6 ) numBbarmomTbar++;
        }

        // if at least one b from b & one b from t, or if CC, and your jet was not b
        if( ((numBmomB>=1 && numBmomT>=1) || (numBbarmomBbar>=1 && numBbarmomTbar>=1)) && !gotB ){
          // for each jet that is  b from b
          for( int i=0; i<int(pfjets.size()); i++ ){
            int id0 = pfjets.at(i).genPartonId;
            int motherID0 = pfjets.at(i).genPartonMotherId;
            if( !(abs(id0)==5 && motherID0==id0) ) continue;

            // for each jet that is b from t
            for( int j=0; j<int(pfjets.size()); j++ ){
              int id1 = pfjets.at(j).genPartonId;
              int motherID1 = pfjets.at(j).genPartonMotherId;
              if( !(id1==id0 && abs(motherID1)==6) ) continue;

              // if delta r between b from b and b from t is big enough, then b in final state is OK
              double dR = kinem::delta_R(pfjets.at(i).genPartonEta,
                                         pfjets.at(i).genPartonPhi,
                                         pfjets.at(j).genPartonEta,
                                         pfjets.at(j).genPartonPhi);
              if( dR>0.3 ){
                gotB = true;
                break;
              }
            }
            if( gotB ) break;
          }
        }

        if( (numCmomC>=1 || numCbarmomCbar>=1) && !isWtoCS ){
          gotC = true;
        }

        if( gotB ) isBBbarEvent = true;
        else if( gotC ) isCCbarEvent = true;
    
   
        if( ttbarType_<0 || sample != 2500)       keepEvent = true;
        else if( ttbarType_ ==0 && !isBBbarEvent && !isCCbarEvent ) keepEvent = true;
        else if( ttbarType_ ==1 &&  isBBbarEvent && !isCCbarEvent ) keepEvent = true;
        else if( ttbarType_ >1  && !isBBbarEvent && isCCbarEvent  ) keepEvent = true;

        if (debug_) cout << "Filter result = " << keepEvent << endl
                         << "isBBbarEvent = " << isBBbarEvent << endl
                         << "isCCbarEvent = " << isCCbarEvent << endl
                         << "... will we skip this? " << (!keepEvent) << endl;
        
        // if you don't pass the filter, skip this event

        if (debug_) cout << "Keep event no matter what" << endl;
        //keepEvent = true;
        
        if(!keepEvent) continue;
      }// end if you are a top sample

      


//       if( sample==2500 )      wgt = 157.7 * intLumi * 1./3627909;     //NNLL
//       else if( sample==2300 ) wgt = 3048. * intLumi * 1./35504033;    // NNLO
//       else if( sample==2400 ) wgt = 31314. * intLumi * 1./70681213;  //NNLO
//       else if( sample==2455 ) wgt = 35.3 * intLumi * 1./21792790;    //LO
//       else if( sample==2600 ) wgt = 3.19 * intLumi * 1./259971; //NNLO
//       else if( sample==2601 ) wgt = 1.44 * intLumi * 1./137980; //NNLO
//       else if( sample==2602 ) wgt = 41.92 * intLumi * 1./3861170; //NNLO
//       else if( sample==2603 ) wgt = 22.65 * intLumi * 1./1944826; //NNLO
//       else if( sample==2604 ) wgt = 7.87 * intLumi * 1./814390; //NNLO
//       else if( sample==2605 ) wgt = 7.87 * intLumi * 1./809984; //NNLO


      // int run  = event->run;
      // int lumi = event->lumi;
      // long evt = event->evt;


      MetIter pfmet = pfmets.begin();
      // MetIter calomet = calomets.begin();
      // MetIter tcmet = tcmets.begin();

      // Type I corrected MET
      h_met_pt->Fill(pfmet->pt,wgt);
      h_met_phi->Fill(pfmet->phi,wgt);
      // Uncorrected / raw MET
      h_met_Upt->Fill(pfmet->Upt,wgt);
      h_met_Uphi->Fill(pfmet->Uphi,wgt);

      
      // Loop over and count the number of primary vertices
      int numpv = 0;
      for( int i=0; i<int(pvs.size()); i++ ){
	bool isGood = ( (pvs.at(i).ndof>=minNDOF) &&
			(fabs(pvs.at(i).z)<maxAbsZ) &&
			(fabs(pvs.at(i).rho)<maxd0) );
	bool isFake = ( pvs.at(i).isFake==1 );
	if( isGood && !isFake ) numpv++;
      }

      // Pile-up reweighting  ////Robin
      float PUwgt = 1;
      float PUwgt_up = 1;
      float PUwgt_down = 1;
//       if( sample>=0 ) PUwgt = lumiWeights_it.ITweight( n0 );

      if( sample>=0 ){
	if( (sample>=100 && sample<=140) || (sample==2523) || (sample==2524) ){
	  PUwgt      = h_pu_ratio->GetBinContent( h_pu_ratio->FindBin( numGenPV ) );
	  PUwgt_up   = h_pu_ratio_up->GetBinContent( h_pu_ratio_up->FindBin( numGenPV ) );
	  PUwgt_down = h_pu_ratio_down->GetBinContent( h_pu_ratio_down->FindBin( numGenPV ) );
	}
	else{
	  PUwgt      = h_pu_ratio->GetBinContent( h_pu_ratio->FindBin( numTruePV ) );
	  PUwgt_up   = h_pu_ratio_up->GetBinContent( h_pu_ratio_up->FindBin( numTruePV ) );
	  PUwgt_down = h_pu_ratio_down->GetBinContent( h_pu_ratio_down->FindBin( numTruePV ) );
	}
      }
      wgt *= PUwgt;



      // Trigger Requirement
      bool triggerFound = false;
      bool triggerPass  = false;

      // assert the trigger req to be true

//       triggerFound = true;
//       triggerPass = true;
      
      //      if( sample>=0 ){
	for( TrigIter hltbit = hlt.begin(); hltbit != hlt.end(); ++hltbit ){
	  for( int t=0; t<int(mc_hlt_trigger_collection.size()); t++ ){
	    std::string hlt_name = hltbit->name;
	    if( (hlt_name.find(mc_hlt_trigger_collection[t])!=std::string::npos) ){
	      if( hltbit->prescale!=1 ) continue;
              triggerFound = true;
              triggerPass = ( hltbit->pass==1 );
            }
            if( triggerPass ) break;
          }
          if( triggerPass ) break;
        }
	//      }

      // Print triggers
      //triggerFound = false;
      /// make sure trigger used to tag exists in the event
      if( !triggerFound ){
	std::cout << "  error ===> Trigger not found!!!  Here are the available triggers: " << std::endl;
	for( TrigIter hltbit = hlt.begin(); hltbit != hlt.end(); ++hltbit ){
	  std::string hlt_name = hltbit->name;
	  std::cout << "\t\t " << hlt_name << "\t\t prescale = " << hltbit->prescale << "\t\t pass = " << hltbit->pass << std::endl;
	}
	break;
      }

//       if( cnt==10 ) {
// 	for( TrigIter hltbit = hlt.begin(); hltbit != hlt.end(); ++hltbit ){
// 	  std::string hlt_name = hltbit->name;
// 	  std::cout << "==>" << hlt_name << "\t\t ps is  " << hltbit->prescale << endl; 
// 	   for( int t=0; t<int(mc_hlt_trigger_collection.size()); t++ ){
// 	     if(hlt_name.find(mc_hlt_trigger_collection[t])!=std::string::npos) {
// 	       std::cout << "--- we found " << hlt_name << " and ps is" << hltbit->prescale << endl;
// 	     }
// 	   }
// 	}
//       }

      nevents++;
      nevents_wgt+=wgt;

      int mcut = 0;
      h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // preselection 0



      // Event cleaning requirements
      bool passGoodVertex = ( numpv>0 ) ? true : false;
      bool passFilterOutScraping = ( event->FilterOutScraping==1 ) ? true : false;
      bool passHBHENoiseFilter = ( event->HBHENoiseFilter==1 ) ? true : false;

      bool cleanEvent = ( passGoodVertex && passFilterOutScraping && passHBHENoiseFilter );
      cleanEvent = ( cleanEvent || (sample>=0) );




      if( sample>=0 ){

	double binW0decay = -99;
	double binW1decay = -99;
	double binHdecay  = -99;

	// Get the decays product of the W
	int W0decay = event->W0decay;
	int W1decay = event->W1decay;

	// loop over status==3 mc particles
	std::vector<int> higgs_daughter_id;
	for( int i=0; i<int(mcparticles.size()); i++ ){
	  int id = mcparticles.at(i).id;
	  int motherID = mcparticles.at(i).motherId;
	  int motherAbsID = fabs(motherID);

	  if( motherAbsID==25 ) higgs_daughter_id.push_back(id);
	  if( abs(id)==25 ) h_H_mass->Fill(mcparticles.at(i).mass);
	}

	// Convert from decay to bin
	if( (W0decay==201 || W0decay==102) )      binW0decay=0.5;
	else if( (W0decay==203 || W0decay==302) ) binW0decay=1.5;
	else if( (W0decay==205 || W0decay==502) ) binW0decay=2.5;
	else if( (W0decay==401 || W0decay==104) ) binW0decay=3.5;
	else if( (W0decay==403 || W0decay==304) ) binW0decay=4.5;
	else if( (W0decay==405 || W0decay==504) ) binW0decay=5.5;
	else if( (W0decay==601 || W0decay==106) ) binW0decay=6.5;
	else if( (W0decay==603 || W0decay==306) ) binW0decay=7.5;
	else if( (W0decay==605 || W0decay==506) ) binW0decay=8.5;
	else if( (W0decay==1112 || W0decay==1211) ) binW0decay=9.5;
	else if( (W0decay==1314 || W0decay==1413) ) binW0decay=10.5;
	else if( (W0decay==1516 || W0decay==1615) ) binW0decay=11.5;
	else                                        binW0decay=12.5;

	if( (W1decay==201 || W1decay==102) )      binW1decay=0.5;
	else if( (W1decay==203 || W1decay==302) ) binW1decay=1.5;
	else if( (W1decay==205 || W1decay==502) ) binW1decay=2.5;
	else if( (W1decay==401 || W1decay==104) ) binW1decay=3.5;
	else if( (W1decay==403 || W1decay==304) ) binW1decay=4.5;
	else if( (W1decay==405 || W1decay==504) ) binW1decay=5.5;
	else if( (W1decay==601 || W1decay==106) ) binW1decay=6.5;
	else if( (W1decay==603 || W1decay==306) ) binW1decay=7.5;
	else if( (W1decay==605 || W1decay==506) ) binW1decay=8.5;
	else if( (W1decay==1112 || W1decay==1211) ) binW1decay=9.5;
	else if( (W1decay==1314 || W1decay==1413) ) binW1decay=10.5;
	else if( (W1decay==1516 || W1decay==1615) ) binW1decay=11.5;
	else                                        binW1decay=12.5;

	h_W0_decay_W1_decay->Fill(binW0decay,binW1decay,wgt);


	// Loop over Higgs daughters
	int d0 = -99, d1=-99;
	for( int d=0; d<int(higgs_daughter_id.size()); d++ ){
	  int id = higgs_daughter_id[d];
	  double absId = fabs(id);

	  if( d0==-99 ) d0 = absId;
	  else if( d1==-99 ) d1 = absId;
	}

	if( d0==5 && d1==5 )        binHdecay=0.5;
	else if( d0==24 && d1==24 ) binHdecay=1.5;
	else if( d0==15 && d1==15 ) binHdecay=2.5;
	else if( d0==21 && d1==21 ) binHdecay=3.5;
	else if( d0==22 && d1==22 ) binHdecay=4.5;
	else if( d0==23 && d1==23 ) binHdecay=5.5;
	else if( d0==4  && d1==4  ) binHdecay=6.5;
	else if( (d0==23 && d1==22) || (d1==23 && d0==22) ) binHdecay=7.5;
	else                        binHdecay=8.5;

	h_H_decay->Fill(binHdecay,wgt);
      }

      /////////
      ///
      /// Electrons
      ///
      ////////
      float fstElePt = 0.0 ;
      float sndElePt = 0.0 ;

      std::vector<int> tight_ele_index;
      std::vector<int> loose_ele_index;
      std::vector<int> only_loose_ele_index;
      for( int i=0; i<int(electrons.size()); i++ ){

        double eleSCEta = electrons.at(i).scEta;
        double absSCeta = fabs(eleSCEta);
        double eleEta = electrons.at(i).eta;
        float elePt = electrons.at(i).pt;

	bool isCrack = ( (absSCeta>1.4442) && (absSCeta<1.5660) );

      	bool kin = ( (elePt>10.) && !isCrack && fabs(eleEta)<2.5 );

      	if( !kin ) continue;

	double chargedHadronIso = electrons.at(i).chargedHadronIso;
	double neutralHadronIso = electrons.at(i).neutralHadronIso;
	double photonIso = electrons.at(i).photonIso;

	double relIso = ( chargedHadronIso + neutralHadronIso + photonIso ) * 1./elePt;

      	bool looseIso = ( relIso < 0.2 );

	if( !looseIso ) continue;

      	loose_ele_index.push_back(i);

	int eidBitTight = electrons.at(i).eidTight;
	if( eidBitTight<0 ){
	  std::cout << "   ===>>>>  BREAK!!  eidBitTight = " << eidBitTight << std::endl;
	  break;
	}
	bool eidTight = ( (eidBitTight & 1)==1 );

	bool d0 = ( fabs(electrons.at(i).correctedD0) < 0.02 );
	bool dZ = ( fabs(electrons.at(i).correctedDZ) < 1. );

	bool dist  = ( fabs(electrons.at(i).dist)<0.02 );
	bool dcot  = ( fabs(electrons.at(i).dcot)<0.02 );
	bool nlost = ( electrons.at(i).numberOfLostHits<1 );
        bool notConv = ( !(dist && dcot) && nlost );

	bool tightIso = ( relIso < 0.1 );

      	bool id = ( eidTight && d0 && dZ && notConv );

      	if( ((elePt>20.) && id && tightIso) ) {
	  tight_ele_index.push_back(i);
	  if (elePt > fstElePt) fstElePt = elePt;
	}
	else {
	  only_loose_ele_index.push_back(i);
	  if (elePt > sndElePt) sndElePt = elePt;
	}
      }// end electron loop

      int numTightElectrons = int(tight_ele_index.size());
      int numLooseElectrons = int(loose_ele_index.size()) - numTightElectrons;


      /////////
      ///
      /// Muons
      ///
      ////////
      float fstMuPt = 0.0 ;
      float sndMuPt = 0.0 ;

      std::vector<int> tight_mu_index;
      std::vector<int> loose_mu_index;
      std::vector<int> only_loose_mu_index;
      for( int i=0; i<int(muons.size()); i++ ){

	float muPt  = muons.at(i).pt;
	double muEta = muons.at(i).eta;
	double muPhi = muons.at(i).phi;
	double muAbsEta = fabs(muEta);

	bool kin = ( (muPt>10.) && (muAbsEta<2.4) );

	if( !kin ) continue;

	double chargedHadronIso = muons.at(i).chargedHadronIso;
	double neutralHadronIso = muons.at(i).neutralHadronIso;
	double photonIso = muons.at(i).photonIso;

	double relIso = ( chargedHadronIso + neutralHadronIso + photonIso ) * 1./muPt;

	bool looseIso = ( relIso<0.2 );

	bool isGlobalMuon = ( muons.at(i).isGlobalMuon==1 );

	if( !(isGlobalMuon && looseIso) ) continue;

	loose_mu_index.push_back(i);

	bool isTrackerMuon = ( muons.at(i).isTrackerMuon==1 );
	bool isGlobalMuonPromptTight = ( muons.at(i).isGlobalMuonPromptTight==1 );

	bool numTrackHits = ( muons.at(i).numberOfValidTrackerHitsInnerTrack > 10 );
	bool numPixelHits = ( muons.at(i).pixelLayersWithMeasurement>0 );
	bool numberOfMatches = ( muons.at(i).numberOfMatches>1 );

	bool passd0 = ( fabs(muons.at(i).correctedD0)<0.02 );
	bool passdz = ( fabs(muons.at(i).correctedDZ)<1. );

	bool id = ( isTrackerMuon && isGlobalMuonPromptTight && numTrackHits && numPixelHits && numberOfMatches && passd0 && passdz );

	bool tightIso = ( relIso<0.125 );

    // JMS Changed muon pt cut
    // JMS used to be 30
    // is now back to 30
    
	if( ((muPt>20.) && (muAbsEta<2.1) && id && tightIso) ){
	  tight_mu_index.push_back(i);
	  h_mu_pt->Fill(muPt,wgt);
	  h_mu_eta->Fill(muEta,wgt);
	  h_mu_phi->Fill(muPhi,wgt);

	  if (muPt > fstMuPt) fstMuPt = muPt;  ///Robin

      // just assert that you fired a double muon trigger
	  bool mu_fired_trigger = false;
      mu_fired_trigger = true;

      
	  // for( TrigObjIter hltobj = hltobjs.begin(); hltobj != hltobjs.end(); ++hltobj ){
// 	    //// Dump out filter name, pt, eta, phi for each HLT object
// 	    //std::cout << "\t" << hltobj->filter << "\t pt, eta, phi = " << hltobj->pt << ",\t " << hltobj->eta << ",\t " << hltobj->phi << std::endl;
// 	    if( hltobj->filter==mc_hlt_filter_names[0] ){
// 	      double trigEta = hltobj->eta;
// 	      double trigPhi = hltobj->phi;

// 	      double dR_mu_hlt = kinem::delta_R(trigEta,trigPhi,muEta,muPhi);
// 	      h_dR_mu_hlt->Fill(dR_mu_hlt,wgt);
// 	      if( dR_mu_hlt<0.3 ){
// 		mu_fired_trigger = true;
// 		break;
// 	      }
// 	    }
// 	  } // end for each trigger object
      
      
	} // end if tight muon
	else {
	  only_loose_mu_index.push_back(i);
	  if (muPt>sndMuPt) sndMuPt = muPt;      ///Robin
	}
      }// end muon loop


      int numTightMuons = int(tight_mu_index.size());
      int numLooseMuons = int(loose_mu_index.size()) - numTightMuons;

//       ///Robin
//       for( int m=0; m<int(tight_mu_index.size()); m++ ){
// 	double ptMax = muPt;
	
//       }



      if (numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons >= 2 )
        std::cout << "Done with lepton selection... this event could be dilepton " << std::endl
                               << "numTightMuons = " << numTightMuons << std::endl
                               <<" numLooseMuons = " << numLooseMuons << std::endl
                               << "numTightElectron = " << numTightElectrons << std::endl
                               << "numLooseElectrons = " << numLooseElectrons << std::endl;
        
      //      if ( numLooseMuons != int(only_loose_mu_index.size()) ) std::cout << ".......failure, lalala............" << std::endl;     
      bool twoLeptons = (( numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons )== 2 && ( numTightMuons + numTightElectrons )> 0 );
      if ( !twoLeptons ) continue ;
    
      /////////
      ///
      /// Pfjets
      ///
      ////////
      std::vector<int> tight_pfjet_index;
      std::vector<int> tag_pfjet_index;
      std::vector<int> untag_pfjet_index;

      std::vector<double> good_jet_pt;
      std::vector<double> good_jet_eta;
      std::vector<double> good_jet_tag;
      std::vector<int>    good_jet_flavor;

      vdouble jet_px;
      vdouble jet_py;
      vdouble jet_pz;
      vdouble jet_pt;
      vdouble jet_energy;

      int numGoodJets=0;
      TLorentzVector jetV[100];
      std::list<float> jet_desc;      

      //JES
      //      int jes = 0 ;   // nominal
      int jes = -1 ; // jes down
      //      int jes = 1 ; // jes up


      for( int i=0; i<int(pfjets.size()); i++ ){

	jet_px.push_back(pfjets.at(i).px);
	jet_py.push_back(pfjets.at(i).py);
	jet_pz.push_back(pfjets.at(i).pz);
	jet_pt.push_back(pfjets.at(i).pt);
	jet_energy.push_back(pfjets.at(i).energy);
	
	double unc = pfjets.at(i).JESunc;

	jet_px[i] *= (1. + jes*unc);
	jet_py[i] *= (1. + jes*unc);
	jet_pz[i] *= (1. + jes*unc);
	jet_pt[i] *= (1. + jes*unc);
	jet_energy[i] *= (1. + jes*unc);

	double jetPt = pfjets.at(i).pt;
	jetPt *= (1. + jes*unc);
	double jetEta = pfjets.at(i).eta;
	double jetPhi = pfjets.at(i).phi;
	double jetAbsEta = fabs(jetEta);

	bool kin = ( jetPt>30. );
	bool eta = ( jetAbsEta<2.4 );
	bool id  = ( pfjets.at(i).jetIDLoose==1 );

	if( !(kin && eta && id) ) continue;

	bool hasCloseLepton = false;
	for( int m=0; m<int(tight_mu_index.size()); m++ ){
	  int mu_index = tight_mu_index[m];
	  double dR_mu_jet = kinem::delta_R(muons.at(mu_index).eta,muons.at(mu_index).phi,jetEta,jetPhi);
	  if( dR_mu_jet<0.3 ){
	    hasCloseLepton = true;
	    break;
	  }
	}
	for( int m=0; m<int(tight_ele_index.size()); m++ ){
	  int ele_index = tight_ele_index[m];
	  double dR_ele_jet = kinem::delta_R(electrons.at(ele_index).eta,electrons.at(ele_index).phi,jetEta,jetPhi);
	  if( dR_ele_jet<0.3 ){
	    hasCloseLepton = true;
	    break;
	  }
	}

	// this is probably too much... 
	if( hasCloseLepton ) {
	  nEventsWhereJetRemoved++;
	  continue;
	}
	
	jetV[numGoodJets].SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
	numGoodJets++;
	tight_pfjet_index.push_back(i);


	h_jet_pt->Fill(jetPt,wgt);
	h_jet_eta->Fill(jetEta,wgt);
	h_jet_phi->Fill(jetPhi,wgt);



	// use sec vtx high eff
	
	//double svhe = pfjets.at(i).btagSecVertexHighEff;
	//bool svheL = ( svhe>1.74 );
	
	
	// Use Combined tags
	// Loose Cut is 0.244
	// Medium Cut is 0.679
	// Tight Cut is 0.898


	float csv = pfjets.at(i).btagCombinedSecVertex;
	bool csvM = ( csv> btagThres );

	
	if( csvM ){
	  tag_pfjet_index.push_back(i);
	  jet_desc.push_back(csv);
	}
	else        untag_pfjet_index.push_back(i);
	
	
	int parId =  abs(pfjets.at(i).genPartonId);
	int flavor =  pfjets.at(i).flavour;

	if( parId==5  ){
	  h_jet_pt_b->Fill(jetPt,wgt);
	  h_jet_disc_b->Fill(csv,wgt);
	}
	else if( parId==4  ){
	  h_jet_pt_c->Fill(jetPt,wgt);
	  h_jet_disc_c->Fill(csv,wgt);
	}
	else if( parId==1 || parId==2 || parId==3 || parId==21 ){
	  h_jet_pt_l->Fill(jetPt,wgt);
	  h_jet_disc_l->Fill(csv,wgt);
	}

	good_jet_pt.push_back(jetPt);
	good_jet_eta.push_back(jetEta);
	good_jet_tag.push_back(csv);
	good_jet_flavor.push_back(flavor);

      }// end for each pf jet
      
      //Robin
      *(floatBranches["fstMuPt"]) = fstMuPt ;
      *(floatBranches["sndMuPt"]) = sndMuPt ;

      *(floatBranches["fstElePt"]) = fstElePt ;
      *(floatBranches["sndElePt"]) = sndElePt ;

      //------------------------
      int numJet = int(tight_pfjet_index.size());
      int numTag = int(tag_pfjet_index.size());
      int numNonTag = int(untag_pfjet_index.size());


//       bool oneTightLepton = (numTightMuons==1);
//       bool oneLooseLepton = (numLooseMuons==0);
//       bool oneTightSecondLepton = (numTightElectrons==0);
//       bool oneLooseSecondLepton = (numLooseElectrons==0);

      ///////

      bool TightMuonLooseMuon = ((numTightMuons == 1) && (numLooseMuons==1));
      bool TightMuonLooseEle = ((numTightMuons == 1) && (numLooseElectrons==1));
      bool TightEleLooseMuon = ((numTightElectrons == 1) && (numLooseMuons==1));
      bool TightEleLooseEle = ((numTightElectrons == 1) && (numLooseElectrons==1));

      bool twoTightMuon = (numTightMuons == 2);
      bool oneEleOneMuon = ((numTightMuons ==1) && (numTightElectrons ==1));
      bool twoTightEle = (numTightElectrons ==2);

      bool geOneTightMuon = (numTightMuons >=1);
      bool geTwoJets = (numJet >=2 );
      bool geThreeJets = (numJet >=3);
      bool geTwoTags = (numTag >=2);
      bool geThreeTags = (numTag >=3);

      bool passTwoMuon = twoLeptons && ( twoTightMuon || TightMuonLooseMuon ) ;
      bool passTwoEle = twoLeptons && ( twoTightEle || TightEleLooseEle ) ;
      bool passMuonEle = twoLeptons && ( TightMuonLooseEle || TightEleLooseMuon || oneEleOneMuon );

      *(intBranches["PassTwoLepton"]) =  twoLeptons ? 1 : 0;
      *(intBranches["TwoMuon"]) = passTwoMuon ? 1 : 0;
      *(intBranches["TwoEle"]) =  passTwoEle ? 1 : 0;
      *(intBranches["MuonEle"]) = passMuonEle ? 1 : 0;

      *(intBranches["isCleanEvent"]) = cleanEvent ? 1 : 0;
      *(intBranches["isTriggerPass"]) = triggerPass ? 1 : 0;

      *(intBranches["numJets"]) = numJet ;
      *(intBranches["numTaggedJets"]) = numTag;
      *(intBranches["numNonTaggedJets"]) = numNonTag;

      *(floatBranches["numJets_float"]) = float(numJet);
      *(floatBranches["numTaggedJets_float"]) = float(numTag);

      *(intBranches["numTightMuons"]) = numTightMuons;
      *(intBranches["numLooseMuons"]) = numLooseMuons;
      *(intBranches["numTightElectrons"]) = numTightElectrons;
      *(intBranches["numLooseElectrons"]) = numLooseElectrons;

      //long tempLongEventNum = event->evt;
      //unsigned tempUEventNum = (unsigned) tempLongEventNum;
      //std::cout << "Check event num: long " << tempLongEventNum << " uint " << tempUEventNum << std::endl;
      
      *(uintBranches["runNumber"]) = event->run ;
      *(uintBranches["luminosityBlock"]) = event->lumi ;
      *(uintBranches["eventNumber"]) = unsigned(event->evt) ;
      
      //////////////////////////
      ////
      ////------------b-tag SF
      ////
      //////////////////////////
      double prob0,probge1,prob1,probge2,prob2,probge3,prob3,probge4;
      
      double prob0_SFhfup,probge1_SFhfup,prob1_SFhfup,probge2_SFhfup,prob2_SFhfup,probge3_SFhfup,prob3_SFhfup,probge4_SFhfup;
      double prob0_SFlfup,probge1_SFlfup,prob1_SFlfup,probge2_SFlfup,prob2_SFlfup,probge3_SFlfup,prob3_SFlfup,probge4_SFlfup;
      double prob0_SFhfdown,probge1_SFhfdown,prob1_SFhfdown,probge2_SFhfdown,prob2_SFhfdown,probge3_SFhfdown,prob3_SFhfdown,probge4_SFhfdown;
      double prob0_SFlfdown,probge1_SFlfdown,prob1_SFlfdown,probge2_SFlfdown,prob2_SFlfdown,probge3_SFlfdown,prob3_SFlfdown,probge4_SFlfdown;
	
	if( sample>=0 ){
	  // nominal
	  calculateTagProb( sample, good_jet_pt, good_jet_eta, good_jet_tag, good_jet_flavor, 
			    prob0, probge1, prob1, probge2, prob2, probge3, prob3, probge4, 
			    0, 1, 1, 1);

	  // SF, heavy and light flavors
	  calculateTagProb( sample, good_jet_pt, good_jet_eta, good_jet_tag, good_jet_flavor, 
			    prob0_SFhfdown, probge1_SFhfdown, prob1_SFhfdown, probge2_SFhfdown, prob2_SFhfdown, probge3_SFhfdown, prob3_SFhfdown, probge4_SFhfdown, 
			    -1, 1, 1, 1);
	  calculateTagProb( sample, good_jet_pt, good_jet_eta, good_jet_tag, good_jet_flavor, 
			    prob0_SFlfdown, probge1_SFlfdown, prob1_SFlfdown, probge2_SFlfdown, prob2_SFlfdown, probge3_SFlfdown, prob3_SFlfdown, probge4_SFlfdown, 
			    -2, 1, 1, 1);
	  calculateTagProb( sample, good_jet_pt, good_jet_eta, good_jet_tag, good_jet_flavor, 
			    prob0_SFhfup, probge1_SFhfup, prob1_SFhfup, probge2_SFhfup, prob2_SFhfup, probge3_SFhfup, prob3_SFhfup, probge4_SFhfup, 
			    1, 1, 1, 1);
	  calculateTagProb( sample, good_jet_pt, good_jet_eta, good_jet_tag, good_jet_flavor, 
			    prob0_SFlfup, probge1_SFlfup, prob1_SFlfup, probge2_SFlfup, prob2_SFlfup, probge3_SFlfup, prob3_SFlfup, probge4_SFlfup, 
			    2, 1, 1, 1);

	}
	else{ /// why 0 for data???
	  prob0=0; probge1=0; prob1=0; probge2=0; probge3=0; prob2=0;
	  prob0_SFhfup=0; probge1_SFhfup=0; prob1_SFhfup=0; probge2_SFhfup=0; probge3_SFhfup=0; prob2_SFhfup=0;
	  prob0_SFlfup=0; probge1_SFlfup=0; prob1_SFlfup=0; probge2_SFlfup=0; probge3_SFlfup=0; prob2_SFlfup=0;
	  prob0_SFhfdown=0; probge1_SFhfdown=0; prob1_SFhfdown=0; probge2_SFhfdown=0; probge3_SFhfdown=0; prob2_SFhfdown=0;
	  prob0_SFlfdown=0; probge1_SFlfdown=0; prob1_SFlfdown=0; probge2_SFlfdown=0; probge3_SFlfdown=0; prob2_SFlfdown=0;

	}

	*(floatBranches["prob0"]) = prob0;
	*(floatBranches["prob1"]) = prob1;
	*(floatBranches["prob2"]) = prob2;
	*(floatBranches["prob3"]) = prob3;

	*(floatBranches["probge1"]) = probge1;
	*(floatBranches["probge2"]) = probge2;
	*(floatBranches["probge3"]) = probge3;
	*(floatBranches["probge4"]) = probge4;
	//SF hf
	*(floatBranches["prob0_SFhfdown"]) = prob0_SFhfdown;
	*(floatBranches["prob1_SFhfdown"]) = prob1_SFhfdown;
	*(floatBranches["prob2_SFhfdown"]) = prob2_SFhfdown;
	*(floatBranches["prob3_SFhfdown"]) = prob3_SFhfdown;

	*(floatBranches["probge1_SFhfdown"]) = probge1_SFhfdown;
	*(floatBranches["probge2_SFhfdown"]) = probge2_SFhfdown;
	*(floatBranches["probge3_SFhfdown"]) = probge3_SFhfdown;
	*(floatBranches["probge4_SFhfdown"]) = probge4_SFhfdown;

	*(floatBranches["prob0_SFhfup"]) = prob0_SFhfup;
	*(floatBranches["prob1_SFhfup"]) = prob1_SFhfup;
	*(floatBranches["prob2_SFhfup"]) = prob2_SFhfup;
	*(floatBranches["prob3_SFhfup"]) = prob3_SFhfup;

	*(floatBranches["probge1_SFhfup"]) = probge1_SFhfup;
	*(floatBranches["probge2_SFhfup"]) = probge2_SFhfup;
	*(floatBranches["probge3_SFhfup"]) = probge3_SFhfup;
	*(floatBranches["probge4_SFhfup"]) = probge4_SFhfup;
	//SF lf
	*(floatBranches["prob0_SFlfdown"]) = prob0_SFlfdown;
	*(floatBranches["prob1_SFlfdown"]) = prob1_SFlfdown;
	*(floatBranches["prob2_SFlfdown"]) = prob2_SFlfdown;
	*(floatBranches["prob3_SFlfdown"]) = prob3_SFlfdown;

	*(floatBranches["probge1_SFlfdown"]) = probge1_SFlfdown;
	*(floatBranches["probge2_SFlfdown"]) = probge2_SFlfdown;
	*(floatBranches["probge3_SFlfdown"]) = probge3_SFlfdown;
	*(floatBranches["probge4_SFlfdown"]) = probge4_SFlfdown;

	*(floatBranches["prob0_SFlfup"]) = prob0_SFlfup;
	*(floatBranches["prob1_SFlfup"]) = prob1_SFlfup;
	*(floatBranches["prob2_SFlfup"]) = prob2_SFlfup;
	*(floatBranches["prob3_SFlfup"]) = prob3_SFlfup;

	*(floatBranches["probge1_SFlfup"]) = probge1_SFlfup;
	*(floatBranches["probge2_SFlfup"]) = probge2_SFlfup;
	*(floatBranches["probge3_SFlfup"]) = probge3_SFlfup;
	*(floatBranches["probge4_SFlfup"]) = probge4_SFlfup;



      /////////////////////////////////
      ///////
      /////// final selection for neural net training:
      //////
      ////////////////////////////////

      //met
      TLorentzVector metV(pfmet->px,pfmet->py,0.0,pfmet->pt);
      float met = pfmet->pt;
      float unc_met = pfmet->Upt;

      //sort btag descrminator
      jet_desc.sort();  
      std::vector<float> jet_sort_vect;			
      std::list<float>::iterator listint;			
      for (listint = jet_desc.begin(); listint != jet_desc.end(); listint++){
	jet_sort_vect.push_back(*listint);  //accessible form
      }

      //sum of all jets
      TLorentzVector sum_jet_vect(0.0,0.0,0.0,0.0);
      
      for (int sumv=0; sumv < numJet; sumv++) {
	sum_jet_vect += jetV[sumv];
      }

      TLorentzVector dijet_vect;
      TLorentzVector lep_vect1;
      TLorentzVector lep_vect2;
      TLorentzVector jet_vect;
      
      TLorentzVector btag_vect1;
      TLorentzVector btag_vect2;
      
      float first_jet_pt = 0.0 ;
      float second_jet_pt = 0.0 ;
      float third_jet_pt = 0.0 ;
      float fourth_jet_pt = 0.0 ;

      float min_jet_lep1_dR = 10000.;
      float min_jet_lep2_dR = 10000.;
      float min_tagged_jets_dR = 10000.;
 
      float denom_avg_cnt = 0.;
      float avg_btag_disc_btags = 0.;     
      float avg_btag_disc_non_btags = 0.;     
      float dev_from_avg_disc_btags = 0.;

      float sum_pt = 0.0 ;
      float all_sum_pt = 0.0 ;
      float Ht = 0.0 ;
      //      float mass_of_everything = 0.0 ;
     
      float min_dr_tagged_jets = 0.0 ;
      float avg_dr_tagged_jets = 0.0 ;
      float avg_tagged_dijet_mass = 0.0 ;
      float closest_tagged_dijet_mass = 0.0 ;
      float M2_of_closest_tagged_jets = 0.0 ;
 
      TLorentzVector non_btag_vect1;
      TLorentzVector non_btag_vect2;
      float avg_untagged_dijet_mass = 0.0 ;

//       float h0 = 0.0 ;
//       float h1 = 0.0 ;
//       float h2 = 0.0 ;
//       float h3 = 0.0 ;
//       float h4 = 0.0 ;

      if ( twoLeptons ){  //////// number of jets and number of tags
//      if ( twoLeptons && (numGoodJets > 0) && (numTag > 0)){  //////// number of jets and number of tags
	
	int iMuon1 = -10 ;
	int iMuon2 = -10 ;
	int iEle1 = -10 ;
	int iEle2 = -10 ;
	float lep1_pt = 0 ;
	float lep2_pt = 0 ;
	float lep1_et = 0 ;
	float lep2_et = 0 ;
	float lep1_eta = 0 ;
	float lep2_eta = 0 ;
	float lep1_phi = 0 ;
	float lep2_phi = 0 ;

	  if( twoTightMuon || TightMuonLooseMuon ){
	    if( twoTightMuon ) {
	      iMuon1 = tight_mu_index[0] ;
	      iMuon2 = tight_mu_index[1] ;
	      if(muons.at(iMuon1).pt < muons.at(iMuon2).pt) {
		iMuon1 = tight_mu_index[1] ;
		iMuon2 = tight_mu_index[0] ;
	      }
	    }
	    
	    if( TightMuonLooseMuon ) {
	      iMuon1 = tight_mu_index[0] ;
	      iMuon2 = only_loose_mu_index[0] ;
	    }
	    
	    lep1_pt = muons.at(iMuon1).pt;
	    lep2_pt = muons.at(iMuon2).pt;
	    
	    lep1_et = muons.at(iMuon1).et;
	    lep2_et = muons.at(iMuon2).et;  

	    lep1_eta = muons.at(iMuon1).eta;
	    lep2_eta = muons.at(iMuon2).eta;  

	    lep1_phi = muons.at(iMuon1).phi;
	    lep2_phi = muons.at(iMuon2).phi;  

	    lep_vect1.SetPxPyPzE(muons.at(iMuon1).px, muons.at(iMuon1).py, muons.at(iMuon1).pz, muons.at(iMuon1).energy);
	    lep_vect2.SetPxPyPzE(muons.at(iMuon2).px, muons.at(iMuon2).py, muons.at(iMuon2).pz, muons.at(iMuon2).energy);
	  
	  }

	  if( twoTightEle || TightEleLooseEle ){
	    if( twoTightEle ){
	      iEle1 = tight_ele_index[0] ;
	      iEle2 = tight_ele_index[1] ;
	      if(electrons.at(iEle1).pt < electrons.at(iEle2).pt){
		iEle1 = tight_ele_index[1] ;
		iEle2 = tight_ele_index[0] ;
	      }
	    }

	    if( TightEleLooseEle ){
	      iEle1 = tight_ele_index[0] ;
	      iEle2 = only_loose_ele_index[0] ;
	    }
	  
	    lep1_pt = electrons.at(iEle1).pt;
	    lep2_pt = electrons.at(iEle2).pt;
	    
	    lep1_et = electrons.at(iEle1).et;
	    lep2_et = electrons.at(iEle2).et;  

	    lep1_eta = electrons.at(iEle1).eta;
	    lep2_eta = electrons.at(iEle2).eta;  

	    lep1_phi = electrons.at(iEle1).phi;
	    lep2_phi = electrons.at(iEle2).phi;  

	    lep_vect1.SetPxPyPzE(electrons.at(iEle1).px, electrons.at(iEle1).py, electrons.at(iEle1).pz, electrons.at(iEle1).energy);
	    lep_vect2.SetPxPyPzE(electrons.at(iEle2).px, electrons.at(iEle2).py, electrons.at(iEle2).pz, electrons.at(iEle2).energy);
	  
	  }
	  
	  int iMuon = -10 ;
	  int iEle = -10 ;
	  if( oneEleOneMuon || TightEleLooseMuon || TightMuonLooseEle){
	    if ( oneEleOneMuon ){
	      iMuon = tight_mu_index[0] ;
	      iEle = tight_ele_index[0] ;
	    }  
	    if ( TightEleLooseMuon ){
	      iMuon = only_loose_mu_index[0] ;
	      iEle = tight_ele_index[0] ;
	    }
	    if( TightMuonLooseEle ){
	      iMuon = tight_mu_index[0] ;
	      iEle = only_loose_ele_index[0] ;
	    }

	    lep1_pt = muons.at(iMuon).pt;
	    lep2_pt = electrons.at(iEle).pt;
	    
	    lep1_et = muons.at(iMuon).et;
	    lep2_et = electrons.at(iEle).et;  

	    lep1_eta = muons.at(iMuon).eta;
	    lep2_eta = electrons.at(iEle).eta;  

	    lep1_phi = muons.at(iMuon).phi;
	    lep2_phi = electrons.at(iEle).phi;  
	    
	    lep_vect1.SetPxPyPzE(muons.at(iMuon).px, muons.at(iMuon).py, muons.at(iMuon).pz, muons.at(iMuon).energy);
	    lep_vect2.SetPxPyPzE(electrons.at(iEle).px, electrons.at(iEle).py, electrons.at(iEle).pz, electrons.at(iEle).energy);
	  
	  }	 
 
	  // two leptons
	  TLorentzVector two_lepton = lep_vect1 + lep_vect2;
	  float dilep_mass = two_lepton.M();
	  float dilep_pt = two_lepton.Pt();
	  float dPhi_dilep = lep_vect1.DeltaPhi(lep_vect2);
	  float dR_dilep = lep_vect1.DeltaR(lep_vect2);

	  *(floatBranches["mass_leplep"]) = dilep_mass;
	  *(floatBranches["pt_leplep"]) = dilep_pt;
	  *(floatBranches["dPhi_leplep"]) = dPhi_dilep;
	  *(floatBranches["dR_leplep"]) = dR_dilep;

	  *(floatBranches["lep1Pt"]) =  lep1_pt;
	  *(floatBranches["lep2Pt"]) =  lep2_pt;
	  *(floatBranches["lep1Eta"]) = lep1_eta;
	  *(floatBranches["lep2Eta"]) = lep2_eta;
	  *(floatBranches["lep1Phi"]) = lep1_phi;
	  *(floatBranches["lep2Phi"]) = lep2_phi;

	  sum_pt += lep1_pt;
	  Ht += lep1_et ;

	  sum_pt += lep2_pt;
	  Ht += lep2_et ;
	  
	  TLorentzVector everything_vect = metV + lep_vect1 + lep_vect2 + sum_jet_vect;
	  float mass_of_everything = everything_vect.M();
	  float pt_of_everything = everything_vect.Pt();
	  *(floatBranches["mass_of_everything"]) = mass_of_everything;	  
	  *(floatBranches["pt_of_everything"]) = pt_of_everything;	  

	  ///loop jet	  
	  for (int i=0; i < numGoodJets; i++) {
	    int iJet = tight_pfjet_index[i] ;
	    sum_pt += jet_pt[iJet];
	    Ht += jet_energy[iJet];
	    
	    jet_vect.SetPxPyPzE(jet_px[iJet],jet_py[iJet],jet_pz[iJet],jet_energy[iJet]);
	    
	    if (i==0)  first_jet_pt = jet_pt[iJet];
	    if (i==1)  second_jet_pt = jet_pt[iJet];
	    if (i==2)  third_jet_pt = jet_pt[iJet];
	    if (i==3)  fourth_jet_pt = jet_pt[iJet];
	    
	    if (min_jet_lep1_dR > lep_vect1.DeltaR(jet_vect)){
	      min_jet_lep1_dR = lep_vect1.DeltaR(jet_vect); 
	    }
	    
	    if (min_jet_lep2_dR > lep_vect2.DeltaR(jet_vect)){
	      min_jet_lep2_dR = lep_vect2.DeltaR(jet_vect); 
	    }
	    
	    if (pfjets.at(iJet).btagCombinedSecVertex > 0.679){
	      avg_btag_disc_btags += pfjets.at(iJet).btagCombinedSecVertex;
	    }
	    
	    if (pfjets.at(iJet).btagCombinedSecVertex <= 0.679){
	      avg_btag_disc_non_btags += pfjets.at(iJet).btagCombinedSecVertex;   		  
	    }												
	  }
	  
	  *(floatBranches["first_jet_pt"]) = first_jet_pt;
	  *(floatBranches["second_jet_pt"]) = second_jet_pt;
	  *(floatBranches["third_jet_pt"]) = third_jet_pt;
	  *(floatBranches["fourth_jet_pt"]) = fourth_jet_pt;
	  
	  float mindr_lep1_jet = min_jet_lep1_dR;
	  float mindr_lep2_jet = min_jet_lep2_dR;
	  *(floatBranches["mindr_lep1_jet"]) = mindr_lep1_jet;
	  *(floatBranches["mindr_lep2_jet"]) = mindr_lep2_jet;
	  
	  if ( numTag > 0 ) avg_btag_disc_btags /= numTag;
	  
	  if ((numGoodJets - numTag) != 0){
	    avg_btag_disc_non_btags /= (numGoodJets - numTag);
	  }
	  
	  for (int l=0; l < numTag; l++){
	    dev_from_avg_disc_btags += pow((pfjets.at(tag_pfjet_index[l]).btagCombinedSecVertex - avg_btag_disc_btags),2);
	  }
	  if ( numTag > 0 ) dev_from_avg_disc_btags /= numTag;

	  *(floatBranches["avg_btag_disc_btags"]) = avg_btag_disc_btags;
	  *(floatBranches["avg_btag_disc_non_btags"]) = avg_btag_disc_non_btags;
	  *(floatBranches["dev_from_avg_disc_btags"]) = dev_from_avg_disc_btags;

	  /////
	  all_sum_pt = sum_pt + met;
	  Ht += met;

	  *(floatBranches["numPV"]) = numpv ;
	  *(floatBranches["weight"]) = wgt ;
	  *(floatBranches["weight_PUup"]) = PUwgt_up ;
	  *(floatBranches["weight_PUdown"]) = PUwgt_down ;
	  *(floatBranches["met"]) = met;
	  *(floatBranches["unc_met"]) = unc_met;

	  *(floatBranches["sum_pt"]) = sum_pt; 
	  *(floatBranches["all_sum_pt"]) = all_sum_pt;
	  *(floatBranches["Ht"]) = Ht;

	  //// tagged jets
	  if (numTag > 1) {
	    for (int j=0; j < (numTag - 1); j++) {
	      int jbtag = tag_pfjet_index[j] ;
	      btag_vect1.SetPxPyPzE(jet_px[jbtag],jet_py[jbtag],jet_pz[jbtag],jet_energy[jbtag]);
	      
	      for (int k=j+1; k < numTag; k++) {
		int kbtag = tag_pfjet_index[k] ; 
		btag_vect2.SetPxPyPzE(jet_px[kbtag],jet_py[kbtag],jet_pz[kbtag],jet_energy[kbtag]);
		
		dijet_vect = btag_vect1 + btag_vect2;
		avg_tagged_dijet_mass += dijet_vect.M();
		avg_dr_tagged_jets += btag_vect1.DeltaR(btag_vect2);
		++denom_avg_cnt;		      
		
		if (min_tagged_jets_dR > btag_vect1.DeltaR(btag_vect2)){
		  min_tagged_jets_dR = btag_vect1.DeltaR(btag_vect2);
		  M2_of_closest_tagged_jets = dijet_vect.M2();	
		  closest_tagged_dijet_mass = dijet_vect.M();			
		}
		
	      }	
	    }
	    
	    avg_tagged_dijet_mass /= denom_avg_cnt; 
	    avg_dr_tagged_jets /= denom_avg_cnt;
	    
	  }
	  
	  min_dr_tagged_jets = min_tagged_jets_dR;
	  
	  ////non_tagged jets
	  
	  denom_avg_cnt = 0.;
	  int nonTags = untag_pfjet_index.size();
	  if (nonTags > 1){
	    for (int m=0; m < (nonTags - 1); m++){
	      int untag1 = untag_pfjet_index[m];
	      non_btag_vect1.SetPxPyPzE(jet_px[untag1],jet_py[untag1],jet_pz[untag1],jet_energy[untag1]);
	      for (int n=m+1; n < nonTags; n++){
		int untag2 = untag_pfjet_index[n];
		non_btag_vect2.SetPxPyPzE(jet_px[untag2],jet_py[untag2],jet_pz[untag2],jet_energy[untag2]);
		
		dijet_vect = non_btag_vect1 + non_btag_vect2;
		avg_untagged_dijet_mass += dijet_vect.M();
		++denom_avg_cnt;
	      }
	    }
	  
	    avg_untagged_dijet_mass /= denom_avg_cnt;
	  }
	  

	  
// 	  getSp(lep_vect,metV,jetV,numGoodJets,aplanarity,sphericity);				
//	  getFox(two_lepton,metV,jetV,numGoodJets,h0,h1,h2,h3,h4);
// 	  getFox_mod(lep_vect,metV,jetV,numGoodJets,Ht,h0_mod,h1_mod,h2_mod,h3_mod,h4_mod);
// 	  getFox_mod2(lep_vect,metV,jetV,numGoodJets,Ht,h0_mod2,h1_mod2,h2_mod2,h3_mod2,h4_mod2,h5_mod2,h6_mod2,h7_mod2,h8_mod2,h9_mod2,h10_mod2);
	  	 
	  if (numTag > 1){
	    *(floatBranches["min_dr_tagged_jets"]) = min_dr_tagged_jets;
	    *(floatBranches["avg_dr_tagged_jets"]) = avg_dr_tagged_jets;
	    *(floatBranches["avg_tagged_dijet_mass"]) = avg_tagged_dijet_mass;
	    *(floatBranches["closest_tagged_dijet_mass"]) = closest_tagged_dijet_mass;
	    *(floatBranches["M2_of_closest_tagged_jets"]) = M2_of_closest_tagged_jets;
	  }

	  if (nonTags > 1) *(floatBranches["avg_untagged_dijet_mass"]) = avg_untagged_dijet_mass;

	  if (numTag > 0 ){
	    float first_highest_btag = jet_sort_vect[numTag - 1];
	    float second_highest_btag = 0.;
	    if (numTag > 1) second_highest_btag = jet_sort_vect[numTag - 2];
	    float lowest_btag = jet_sort_vect[0];
	    
	    *(floatBranches["first_highest_btag"]) = first_highest_btag;
	    if (numTag > 1) *(floatBranches["second_highest_btag"]) = second_highest_btag;
	    *(floatBranches["lowest_btag"]) = lowest_btag;
	  }
// 	  *(floatBranches["h0"]) = h0;
// 	  *(floatBranches["h1"]) = h1;
// 	  *(floatBranches["h2"]) = h2;
// 	  *(floatBranches["h3"]) = h3;
// 	  *(floatBranches["h4"]) = h4;


	  

      } // end neural net selection

      //--------------------
      
      summaryTree->Fill();
      
      

      if( cleanEvent ){
        h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // cleaning 1
        nevents_pass_cleaning++;
        nevents_pass_cleaning_wgt += wgt;

        if( triggerPass ){
          h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // trigger 2
          nevents_pass_trigger++;
          nevents_pass_trigger_wgt += wgt;


          //////////////////////////////////////////////////////////////////
          //
          //    Two tight muons selection
          //
          //////////////////////////////////////////////////////////////////
      
          if( geOneTightMuon ){
            h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 1 good muon 3

            if( twoTightMuon ){
              h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // exactly two tight muons 4

              if( geTwoJets ){
                h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 jets 5 

                if( geTwoTags ){
                  h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 tags 6

                  if( geThreeJets ){
                    h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 4 jets 7 

                    if( geThreeTags ){
                      h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 3 tags 8


                    }
                  }
                }
              }
            }
          }// end >=1 tight muon

          /////////////////////////////////////////////////////////////
          //
          //   1 mu, 1 ele
          //
          /////////////////////////////////////////////////////////////


          // magic numbers ... skip to the start of the mu+ele selection

          mcut = 9;
          
          
          if( oneEleOneMuon  ){
            h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // 1muo + 1ele 9 


            if( geTwoJets ){
              h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 jets 10 

              if( geTwoTags ){
                h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 tags 11

                if( geThreeJets ){
                  h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 4 jets 12

                  if( geThreeTags ){
                    h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 3 tags 13

                  }
                }
              }
            }
            
          }// end ==1 muon && ==1 electron

          /////////////////////////////////////////////////////////////
          //
          //   2 ele
          //
          /////////////////////////////////////////////////////////////

          // magic numbers... skip to start of 2 ele cuts

          mcut = 14;

          
          if( twoTightEle  ){
            h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // == 2 ele 14


            if( geTwoJets ){
              h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 jets 15

              if( geTwoTags ){
                h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 tags 16

                if( geThreeJets ){
                  h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 4 jets 17

                  if( geThreeTags ){
                    h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 3 tags 18

                  }
                }
              }
            }
            
          }// end == 2 tight Ele

          
          
        }// end if trigger pass
      } // end clean event

//       bool passCleaning      = cleanEvent;
//       bool passTrigger       = ( triggerPass );
//       bool pass1TightLepton  = ( oneTightLepton );
//       bool passMin3jets      = ( numJet>=3 );
//       bool pass0LooseLeptons = ( oneLooseLepton );
//       bool pass0OtherLeptons = ( oneTightSecondLepton && oneLooseSecondLepton );
//       bool passMin4jets      = ( numJet>=4 );
//       bool passMin2tags      = ( numTag>=2 );
//       bool passMin5jets      = ( numJet>=5 );
//       bool passMin3tags      = ( numTag>=3 );

//       std::vector<bool> dec;
//       dec.push_back(true); // All Events
//       dec.push_back(cleanEvent);
//       dec.push_back(triggerPass);
//       dec.push_back(geOneTightMuon);
//       dec.push_back(twoTightMuon);
//       dec.push_back(geTwoJets);
//       dec.push_back(geTwoTags);
//       dec.push_back(geThreeJets);
//       dec.push_back(geThreeTags);
//       //dec.push_back(passMin5jets);
//       //dec.push_back(passMin3tags);


//       if( dec.size()!=selector_name.size() ){
//         std::cout << " ERROR!! dec.size()!=selector_name.size()" << std::endl;
//         break;
//       }

      
//       for( int j=0; j<numSelectors; j++ ){
//         bool Complementary = true, Cumulative = true;
//         if( dec[j] ){
//           selected_wgt[j][0]+=wgt;
//           selected[j][0]+=1;
//         }
//         for( int k=0; k<numSelectors; k++ ){
//           if( k==j ) continue;
//           if( !dec[k] ){
//             Complementary=false;
//             break;
//           }
//         }
//         if( Complementary ){
// 	  selected_wgt[j][1]+=wgt;
// 	  selected[j][1]+=1;
// 	}
//         for( int k=0; k<=j; k++ ){
//           if( !dec[k] ){
//             Cumulative=false;
//             break;
//           }
//         }
//         if( Cumulative ){
// 	  selected_wgt[j][2]+=wgt;
// 	  selected[j][2]+=1;
// 	}
//       }
//       dec.clear();


    } // end loop over events


  }// end try
  catch(std::exception& e) {
    std::cerr << " ==> caught exception " << e.what() << std::endl;
    //continue;
  }


  std::cout << "\n\nDone with loop over events\n\n" << std::endl;
  



  std::cout << " *********************************************************** " << std::endl;
  std::cout << "   Number of Events Processed (wgt)     = " << nevents << " (" << nevents_wgt << ")" << std::endl;
  std::cout << "   Number of Events Pass cleaning (wgt) = "   << nevents_pass_cleaning << " (" << nevents_pass_cleaning_wgt << ")" << std::endl;
  std::cout << "   Number of Events Passed HLT (wgt)    = " << nevents_pass_trigger << " (" << nevents_pass_trigger_wgt << ")" << std::endl;
  std::cout << " *********************************************************** " << std::endl;
  std::cout << "   Number of MC events " << std::endl;
  std::cout << std::setw(25) << " "
	    << std::setw(27) << "Selected"
	    << std::setw(27) << "N - 1"
	    << std::setw(27) << "Cumulative" << std::endl;
  for( int j=0; j<numSelectors; j++ ){
    std::cout << std::setw(25) << selector_name[j]
              << std::setw(15) << selected[j][0]
              << " [" << std::setw(12) << (selected[j][0]/nevents)*100.0 << "%], "
              << std::setw(15) << selected[j][1]
              << " [" << std::setw(12) << (selected[j][1]/nevents)*100.0 << "%], "
              << std::setw(15) << selected[j][2]
             << " [" << std::setw(12) << (selected[j][2]/nevents)*100.0 << "%] " << std::endl;
  }
  std::cout << " *********************************************************** " << std::endl;
  std::cout << "   Weighted number of MC events " << std::endl;
  std::cout << std::setw(25) << " "
	    << std::setw(27) << "Selected"
	    << std::setw(27) << "N - 1"
	    << std::setw(27) << "Cumulative" << std::endl;
  for( int j=0; j<numSelectors; j++ ){
    std::cout << std::setw(25) << selector_name[j]
              << std::setw(15) << selected_wgt[j][0]
              << " [" << std::setw(12) << (selected_wgt[j][0]/nevents_wgt)*100.0 << "%], "
              << std::setw(15) << selected_wgt[j][1]
              << " [" << std::setw(12) << (selected_wgt[j][1]/nevents_wgt)*100.0 << "%], "
              << std::setw(15) << selected_wgt[j][2]
             << " [" << std::setw(12) << (selected_wgt[j][2]/nevents_wgt)*100.0 << "%] " << std::endl;
  }
  std::cout << " *********************************************************** " << std::endl;

  for( int i=0; i<numSelectors; i++ ){
    for( int j=0; j<3; j++ ){
      h_cutflow_expand->Fill(j+0.5,numSelectors-i-0.5,selected[i][j]);
      h_cutflow_expand_wgt->Fill(j+0.5,numSelectors-i-0.5,selected_wgt[i][j]);
    }
  }

  std::cout << "How many events had jets close to leptons? " << nEventsWhereJetRemoved << endl;

  histofile.Write();
  histofile.Close();

  std::cout << " Done! " << std::endl;

}


//////******************************************	
	
/// additional functions	
/////*******************************************

double getJERfactor( int returnType, double jetAbsETA, double genjetPT, double recojetPT){

  double factor = 1.;

  double scale_JER = 1., scale_JERup = 1., scale_JERdown = 1.;
  if( jetAbsETA<0.5 ){ 
    scale_JER = 1.052; scale_JERup = 1.052 + sqrt( 0.012*0.012 + 0.062*0.062 ); scale_JERdown = 1.052 - sqrt( 0.012*0.012 + 0.061*0.061 );
  }
  else if( jetAbsETA<1.1 ){ 
    scale_JER = 1.057; scale_JERup = 1.057 + sqrt( 0.012*0.012 + 0.056*0.056 ); scale_JERdown = 1.057 - sqrt( 0.012*0.012 + 0.055*0.055 );
  }
  else if( jetAbsETA<1.7 ){ 
    scale_JER = 1.096; scale_JERup = 1.096 + sqrt( 0.017*0.017 + 0.063*0.063 ); scale_JERdown = 1.096 - sqrt( 0.017*0.017 + 0.062*0.062 );
  }
  else if( jetAbsETA<2.3 ){ 
    scale_JER = 1.134; scale_JERup = 1.134 + sqrt( 0.035*0.035 + 0.087*0.087 ); scale_JERdown = 1.134 - sqrt( 0.035*0.035 + 0.085*0.085 );
  }
  else if( jetAbsETA<5.0 ){ 
    scale_JER = 1.288; scale_JERup = 1.288 + sqrt( 0.127*0.127 + 0.155*0.155 ); scale_JERdown = 1.288 - sqrt( 0.127*0.127 + 0.153*0.153 );
  }

  double jetPt_JER = recojetPT;
  double jetPt_JERup = recojetPT;
  double jetPt_JERdown = recojetPT;

  if( genjetPT>10. ){
    jetPt_JER = std::max( 0., genjetPT + scale_JER * ( recojetPT - genjetPT ) );
    jetPt_JERup = std::max( 0., genjetPT + scale_JERup * ( recojetPT - genjetPT ) );
    jetPt_JERdown = std::max( 0., genjetPT + scale_JERdown * ( recojetPT - genjetPT ) );
  }

  if( returnType==1 )       factor = jetPt_JERup/recojetPT;
  else if( returnType==-1 ) factor = jetPt_JERdown/recojetPT;
  else                      factor = jetPt_JER/recojetPT;

  if( !(genjetPT>10.) ) factor = 1.;

  return factor;
}


void calculateTagProb( int useSample, std::vector<double> jetPts, std::vector<double> jetEtas, std::vector<double> jetTags, std::vector<int> jetIds, 
		       double &Prob0, double &ProbGEQ1, double &Prob1, double &ProbGEQ2, double &Prob2, double &ProbGEQ3, double &Prob3, double &ProbGEQ4,
		       int returnType, const double extraSFb, const double extraSFc, const double extraSFl ){

  if( useSample<0 ) return;

  //must initialize correctly
  Prob2 = 0; Prob3 = 0;
  Prob0 = 1; Prob1 = 0; ProbGEQ1 = 1; ProbGEQ2 = 0; ProbGEQ3 = 0;

  for( int i=0; i<int(jetPts.size()); i++) {
    double subprob1=0, subprob2_j=0;
    double jet0Pt = jetPts[i];
    double jet0Tag = jetTags[i];
    double jet0Eta = jetEtas[i];
    int    jet0Id  = jetIds[i];

    double effi = jetTagProb(jet0Pt, jet0Eta, jet0Tag, jet0Id, returnType, extraSFb, extraSFc, extraSFl);
    Prob0 = Prob0* ( 1 - effi);
      
    double product = 1;
    for( int j=0; j<int(jetPts.size()); j++) {
      double subprob2_k=0;
      double jet1Pt = jetPts[j];
      double jet1Tag = jetTags[j];
      double jet1Eta = jetEtas[j];
      int    jet1Id  = jetIds[j];

      double effj = jetTagProb(jet1Pt, jet1Eta, jet1Tag, jet1Id, returnType, extraSFb, extraSFc, extraSFl);
      if( i != j ){
	product = product*(1-effj);
      }
      if( j > i ){
	double subproduct = 1;
	for( int k=0; k<int(jetPts.size()); k++ ){
	  double jet2Pt = jetPts[k];
	  double jet2Tag = jetTags[k];
	  double jet2Eta = jetEtas[k];
	  int    jet2Id  = jetIds[k];
	  
	  double effk = jetTagProb(jet2Pt, jet2Eta, jet2Tag, jet2Id, returnType, extraSFb, extraSFc, extraSFl);
	  if( k != j && k != i ){
	    subproduct = subproduct*(1-effk);
	  }
	  if( k > j ){
	    double subproduct1 = 1;
	    for( int l=0; l<int(jetPts.size()); l++ ){
	      double jet3Pt = jetPts[l];
	      double jet3Tag = jetTags[l];
	      double jet3Eta = jetEtas[l];
	      int    jet3Id  = jetIds[l];
	  
	      double effl = jetTagProb(jet3Pt, jet3Eta, jet3Tag, jet3Id, returnType, extraSFb, extraSFc, extraSFl);
	      if( l != k && l != j && l != i ){
		subproduct1 = subproduct1*(1-effl);
	      }
	    } //l loop
	    subprob2_k += effk*subproduct1;
	  }
	} //k loop
	subprob1 += effj*subproduct;
	subprob2_j += effj*subprob2_k;
      }

    }//j loop
    
    Prob1 += effi*product;
    Prob2 += effi*subprob1;
    Prob3 += effi*subprob2_j;

  } //i loop
  //*/

  //std::cout << "prob0 = " << Prob0 << ", prob1 = " << Prob1 << ", prob2 = " << Prob2 << std::endl;  

  ProbGEQ1 = 1 - Prob0;
  ProbGEQ2 = 1 - Prob1 - Prob0;
  ProbGEQ3 = 1 - Prob2 - Prob1 - Prob0;
  ProbGEQ4 = 1 - Prob3 - Prob2 - Prob1 - Prob0;

}

double jetTagProb( double jetPT, double jetETA, double jetTag, int jetID, int returnType, 
		   const double extraSFb, const double extraSFc, const double extraSFl ){

  float ptmin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500};
  float ptmax[] = {40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 670};

  double tagprob=0;
  double pt  = jetPT;
  double eta = jetETA;
  double tag = jetTag;
  int flavor = jetID;

  //https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-mujet_payload.txt
  //Tagger: CSVM within 30 < pt < 670 GeV, abs(eta) < 2.4, x = pt
  if( tag<0.679 ) return 0.;

  double m_type = 0.;
  if( returnType==-1 )      m_type = -1.;
  else if( returnType==1 )  m_type = 1.;
  else                      m_type = 0.;

  double absEta = fabs(eta);

  double threshold = 670;
  pt = ( pt>threshold ) ? threshold-0.0000001 : pt;

  int use_bin=-1;
  for( int p=0; p<14; p++ ){
    if( pt>ptmin[p] && pt<ptmax[p] ){
      use_bin = p; break;
    }
  }
  if( use_bin<0 ) std::cout << "   ERROR!! use_bin < 0 " << std::endl;

  double SFb_error[] = {
    0.0295675,
    0.0295095,
    0.0210867,
    0.0219349,
    0.0227033,
    0.0204062,
    0.0185857,
    0.0256242,
    0.0383341,
    0.0409675,
    0.0420284,
    0.0541299,
    0.0578761,
    0.0655432 };


  double SFb = 0.6981*((1.+(0.414063*pt))/(1.+(0.300155*pt)));

  double SFc = SFb;

  SFb = SFb + m_type * SFb_error[use_bin];
  SFc = SFc + m_type * 2* SFb_error[use_bin];


  double SFl = 1.;
  if( returnType==-2 ){ // min
    if( absEta < 0.8 )                      SFl = ((0.972455+(7.51396e-06*pt))+(4.91857e-07*(pt*pt)))+(-1.47661e-09*(pt*(pt*pt)));
    else if( absEta < 1.6 && absEta > 0.8 ) SFl = ((1.02055+(-0.000378856*pt))+(1.49029e-06*(pt*pt)))+(-1.74966e-09*(pt*(pt*pt)));
    else if( absEta < 2.4 && absEta > 1.6 ) SFl = ((0.983476+(-0.000607242*pt))+(3.17997e-06*(pt*pt)))+(-4.01242e-09*(pt*(pt*pt)));
  }
  else if( returnType==2 ){ // max
    if( absEta < 0.8 )                      SFl = ((1.15116+(0.00122657*pt))+(-3.63826e-06*(pt*pt)))+(2.08242e-09*(pt*(pt*pt)));
    else if( absEta < 1.6 && absEta > 0.8 ) SFl = ((1.20146+(0.000359543*pt))+(-1.12866e-06*(pt*pt)))+(6.59918e-10*(pt*(pt*pt)));
    else if( absEta < 2.4 && absEta > 1.6 ) SFl = ((1.18654+(-0.000795808*pt))+(3.69226e-06*(pt*pt)))+(-4.22347e-09*(pt*(pt*pt)));
  }
  else { // mean
    if( absEta < 0.8 )                      SFl = ((1.06182+(0.000617034*pt))+(-1.5732e-06*(pt*pt)))+(3.02909e-10*(pt*(pt*pt)));
    else if( absEta < 1.6 && absEta > 0.8 ) SFl = ((1.111+(-9.64191e-06*pt))+(1.80811e-07*(pt*pt)))+(-5.44868e-10*(pt*(pt*pt)));
    else if( absEta < 2.4 && absEta > 1.6 ) SFl = ((1.08498+(-0.000701422*pt))+(3.43612e-06*(pt*pt)))+(-4.11794e-09*(pt*(pt*pt)));
  }


  // SFb = 1.;
  // SFc = 1.;
  // SFl = 1.;

  if( abs(flavor) == 5)       tagprob = SFb*extraSFb;
  else if( abs(flavor) == 4 ) tagprob = SFc*extraSFc;
  else if( abs(flavor) == 1 || abs(flavor) == 2 || abs(flavor) == 3 || abs(flavor) == 21 ) tagprob = SFl*extraSFl;
  else                        tagprob = SFl*extraSFl;

  return tagprob;

}



// void getFox(TLorentzVector lepton, TLorentzVector met, TLorentzVector jets[100], int nJets,
// 							float &h0, float &h1, float &h2, float &h3, float &h4) {

//   int visObjects = nJets;
//   //	if (visObjects < 100) {
//   //  		jets[visObjects] = lepton;
//   //		visObjects++;
//   //	}
  
//   float eVis = 0.0;
//   for (int i=0; i<visObjects; i++) {
//     eVis += jets[i].E();
//   }
  
//   h0 = 0.0;
//   h1 = 0.0;
//   h2 = 0.0;
//   h3 = 0.0;
//   h4 = 0.0;
//   for (int i=0; i<visObjects-1; i++) {
//     for (int j=i+1; j<visObjects; j++) {
//       float costh = cos(jets[i].Angle(jets[j].Vect()));
//       float p0 = 1.0;
//       float p1 = costh;
//       float p2 = 0.5*(3.0*costh*costh - 1.0);
//       float p3 = 0.5*(5.0*costh*costh - 3.0*costh);
//       float p4 = 0.125*(35.0*costh*costh*costh*costh - 30.0*costh*costh + 3.0);
//       float pipj = jets[i].P()*jets[j].P();
//       h0 += (pipj/(eVis*eVis))*p0;
//       h1 += (pipj/(eVis*eVis))*p1;
//       h2 += (pipj/(eVis*eVis))*p2;
//       h3 += (pipj/(eVis*eVis))*p3;
//       h4 += (pipj/(eVis*eVis))*p4;
//     }
//   }
  
//   return;
// }



// bool
// filterTTbarPlusJets(string selectEventType, std::vector<BNmcparticle> mcparticles)
// {
//    using namespace edm;
//    using namespace std;
   
//    bool FilterResult = false;


//    bool debug_;
   
//    int ttbarType_;

//    //BNmcparticleCollection mcparticles;
//    BNjetCollection pfjets;

//    if( selectEventType == "tt+jets" ) ttbarType_ = 0;
//    else if (selectEventType == "tt+bb") ttbarType_ = 1;
//    else if (selectEventType == "tt+cc") ttbarType_ = 2;
//    else {
//      std::cout <<"ERROR: did not recognize selectEventType = " << selectEventType
//                << std::endl
//                <<"Refusing to continue" << std::endl;
//      assert(selectEventType == "tt+jets");
     
//    }


//    //Handle<BNmcparticleCollection> h_mcparticles;
//    //iEvent.getByLabel(InputTag("BNproducer","MCstatus3"), h_mcparticles);
//    //BNmcparticleCollection const &mcparticles = *h_mcparticles;

//    // Handle<BNjetCollection> h_pfjets;
//    //    iEvent.getByLabel(InputTag("BNproducer","selectedPatJetsPFlow"), h_pfjets);
//    //    BNjetCollection const &pfjets = *h_pfjets;

//    bool isWtoCS = false;

//    if (debug_) cout << "Num MC particles = " << mcparticles.size() << std::endl
//                     << "Num pfjets " <<  int(pfjets.size()) << std::endl;
   
//    // check to see if the event has a c with a 
//    // parent W
//    for( int i=0; i< mcparticles.size(); i++ ){
//      int id = mcparticles.at(i).id;
//      int motherID = mcparticles.at(i).motherId;

//      if (debug_) cout <<" Particle " << i << " has id " << id << endl;
//      if( abs(id)==4  && abs(motherID)==24 ){
//        isWtoCS = true;
//        break;
//      }
//    }



//    bool isBBbarEvent = false;
//    bool isCCbarEvent = false;


//    bool gotB = false;
//    bool gotC = false;

//    int numBmomB=0;
//    int numBmomT=0;
//    int numBbarmomBbar=0;
//    int numBbarmomTbar=0;
//    int numCmomC=0;
//    int numCbarmomCbar=0;


//    for( int i=0; i<int(pfjets.size()); i++ ){
//      int id = pfjets.at(i).genPartonId;
//      if( id==-99 ) continue;
//      int motherID = pfjets.at(i).genPartonMotherId;

//      // check to see if pf jets is from a  b/c and mother is a gluon
//      // or, if mother is some light quark
//      if( abs(id)==5 && ( motherID==21 || abs(motherID)<abs(id) ) ) gotB=true;
//      if( abs(id)==4 && ( motherID==21 || abs(motherID)<abs(id) ) ) gotC=true;

//      // if things are their own mother, 
//      // where are they from? Does this mean stable?
//      if( id==5  && motherID==id ) numBmomB++;
//      if( id==-5 && motherID==id ) numBbarmomBbar++;

//      if( id==4  && motherID==id ) numCmomC++;
//      if( id==-4 && motherID==id ) numCbarmomCbar++;

//      if( id==5  && motherID==6  ) numBmomT++;
//      if( id==-5 && motherID==-6 ) numBbarmomTbar++;
//    }

//    // if at least one b from b & one b from t, or if CC, and your jet was not b
//    if( ((numBmomB>=1 && numBmomT>=1) || (numBbarmomBbar>=1 && numBbarmomTbar>=1)) && !gotB ){
//      // for each jet that is  b from b
//      for( int i=0; i<int(pfjets.size()); i++ ){
//        int id0 = pfjets.at(i).genPartonId;
//        int motherID0 = pfjets.at(i).genPartonMotherId;
//        if( !(abs(id0)==5 && motherID0==id0) ) continue;

//        // for each jet that is b from t
//        for( int j=0; j<int(pfjets.size()); j++ ){
//          int id1 = pfjets.at(j).genPartonId;
//          int motherID1 = pfjets.at(j).genPartonMotherId;
//          if( !(id1==id0 && abs(motherID1)==6) ) continue;

//          // if delta r between b from b and b from t is big enough, then b in final state is OK
//          double dR = kinem::delta_R(pfjets.at(i).genPartonEta,
//                                     pfjets.at(i).genPartonPhi,
//                                     pfjets.at(j).genPartonEta,
//                                     pfjets.at(j).genPartonPhi);
//          if( dR>0.3 ){
//            gotB = true;
//            break;
//          }
//        }
//        if( gotB ) break;
//      }
//    }

//    if( (numCmomC>=1 || numCbarmomCbar>=1) && !isWtoCS ){
//      gotC = true;
//    }

//    if( gotB ) isBBbarEvent = true;
//    else if( gotC ) isCCbarEvent = true;
    
   
//    if( ttbarType_<0 )       FilterResult = true;
//    else if( ttbarType_ ==0 && !isBBbarEvent && !isCCbarEvent ) FilterResult = true;
//    else if( ttbarType_ ==1 &&  isBBbarEvent && !isCCbarEvent ) FilterResult = true;
//    else if( ttbarType_ >1  && !isBBbarEvent && isCCbarEvent  ) FilterResult = true;

//    if (debug_) cout << "Filter result = " << FilterResult << endl
//                     << "isBBbarEvent = " << isBBbarEvent << endl
//                     << "isCCbarEvent = " << isCCbarEvent << endl;
   
//    return FilterResult;

// }
