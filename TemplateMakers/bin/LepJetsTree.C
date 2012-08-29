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
//Root includes
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
//#include "PhysicsTools/FWLite/interface/TFileService.h"

#include "NtupleMaker/BEANmaker/interface/BEANsUtilities.h"
#include "NtupleMaker/BEANmaker/interface/BtagWeight.h" 

//#include "LumiReweightingStandAlone.h"
//#include "PUConstants.h"

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

#include "PhysicsTools/Utilities/interface/LumiReweightingStandAlone.h"


// headers for python config processing

#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

//#include "BtagWeight.h" 


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

std::vector<double> getEffSF( int returnType, double jetPts, double jetEtas, double jetIds );

double getSingleMuEffSF(double muEta);

// //TFile *f_tag_eff_ = new TFile("mc_btag_efficiency_v4_histo.root");                                                                               

TH2D* h_jet_pt_eta_b_eff_ ;
TH2D* h_jet_pt_eta_c_eff_ ;
TH2D* h_jet_pt_eta_l_eff_ ;
TH2D* h_jet_pt_eta_o_eff_ ;

                                                                                   
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

using namespace std;

int main ( int argc, char ** argv )
{
   // load framework libraries
   gSystem->Load( "libFWCoreFWLite" );
   AutoLibraryLoader::enable();

   //adding in python config parsing

   if ( argc < 2 ) {
        std::cout << "Usage : " << argv[0] << " [parameters.py]" << std::endl;
        return 2;
   }

   //////////////////////////////////////////////////////////////////
   //
   // Get the python configuration
   //
   // Configuration will have
   //   1. a process object that everyhting is attached to
   //   2. various parameter sets, including input and output
   //  
   /////////////////////////////////////////////////////////////////////
   
   cout << "Unpacking configuation parameters." << endl;
   PythonProcessDesc builder(argv[1],argc,argv);

   edm::ParameterSet const& inputs = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("inputs");
   edm::ParameterSet const& outputs = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("outputs");
   edm::ParameterSet const& anaParams = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("dilAnalysis");

   std::vector<std::string> inputFileNames = inputs.getParameter< std::vector<std::string> >("fileNames");
   std::string outputFileName = outputs.getParameter<std::string >("outputName");
   //JES
   int jes = anaParams.getParameter<int> ("jes");
   int jer = anaParams.getParameter<int> ("jer");
   cout << "About to read in the sample name" << endl;
   std::string sampleName = anaParams.getParameter<string>("sampleName");
   cout << "The sampleName: " << sampleName << endl; 

   //If you need to make cuts on the event flow
   //you can use the electron, muon and Jet selection
   bool useElectronSelection =  anaParams.getParameter<bool>("eleSel");
   bool useMuonSelection     =  anaParams.getParameter<bool>("muonSel");
   bool useJetSelection      =  anaParams.getParameter<bool>("jetSel");
   int minJets  = anaParams.getParameter<int>("minJets");
   double nTags = anaParams.getParameter<double>("btags");

   std::cout <<"CONFIG: using jes = " << jes << " jer = " << jer << std::endl;

   //  Btag file

   edm::FileInPath btagFileName = anaParams.getParameter<edm::FileInPath> ("btagFile");
   edm::FileInPath puFileName = anaParams.getParameter<edm::FileInPath> ("puFile");
   

   std::cout << "CONFIG: using btagFile = " << btagFileName.fullPath() << std::endl;

   TFile * btagFile = new TFile (btagFileName.fullPath().c_str());

   int maxNentries = inputs.getParameter<int> ("maxEvents");
   //string sampleName = "doubleEle2012_week02_52Xonly";

   //int iJob =1;
   //string iLabel = "testTree";

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



  // Load the files
  vstring fileNames = inputFileNames;

  if (fileNames.size() < 1 ){
    cout << "You don't have any files in your list... this is is probably bad... exiting" << endl;
    exit(22);
  }

  
  // Name of file containing histograms
  //std::stringstream outFileName;
  //outFileName <<"batchBEAN/" << sampleName << "_" << iLabel << "/test_beans_v1_" << sampleName << "_" << iLabel << "_job_" << iJob << ".root";
  //outFileName << "checkCode_" << sampleName << ".root";
  //std::string histofilename = outFileName.str();
  std::cout << "Writing out to file " << outputFileName << endl;

  

  ///btag efficiency  // file list name pattern   // ww, wz, zz                                                                                  
  std::string histname = sampleName ;  
  if( TString(sampleName).Contains("Zjets"))      histname = "zjets";   // zjets,  zjets_lowmas
  else if(TString(sampleName).Contains("Wjets"))      histname = "wjets";
  else if( TString(sampleName).Contains("TTbar") && !(sampleName=="ttbarW" || sampleName=="ttbarZ") ) histname = "ttbar";  // ttbar, ttbar_bb, ttbar_cc   
  else if( TString(sampleName).Contains("Single") || TString(sampleName).Contains("Chan") ) histname = "singlet";  // singlet_, singletbar_, 
  else if( TString(sampleName).Contains("ttH") ) histname = "ttH120";  
  
 
   // Initialize these global variables once, and then refer to then in a function below 
  h_jet_pt_eta_b_eff_ = (TH2D*)btagFile->Get(std::string( histname + "_h_jet_pt_eta_b_eff" ).c_str());                                         
  h_jet_pt_eta_c_eff_ = (TH2D*)btagFile->Get(std::string( histname + "_h_jet_pt_eta_c_eff" ).c_str());                                         
  h_jet_pt_eta_l_eff_ = (TH2D*)btagFile->Get(std::string( histname + "_h_jet_pt_eta_l_eff" ).c_str());                                         
  h_jet_pt_eta_o_eff_ = (TH2D*)btagFile->Get(std::string( histname + "_h_jet_pt_eta_o_eff" ).c_str());


 
  
  // Print out your config

  std::cout << "Using btag threshold " << btagThres << std::endl;

  
  // Creates a ChainEvent, allowing files to be linked   
  fwlite::ChainEvent ev(fileNames);   

  TFile histofile(outputFileName.c_str(),"recreate");

  histofile.cd();

  int sample = 0;
  //TString(sampleName).Contains("Wjets")
  if( TString(sampleName).Contains("SingleMu")  )       sample = -1;
  if( TString(sampleName).Contains("SingleElectron")  ) sample = -1;
  if( TString(sampleName).Contains("ElectronHad")  )    sample = -1;
  if( TString(sampleName).Contains("Data")  )           sample = -1;
  
  //data detection
  bool isData = false;
  if(sample==-1) isData = true;

  if( TString(sampleName).Contains("TTbar")  )          sample = 2500;
  if( TString(sampleName).Contains("T_sChan")  )        sample = 2600;
  if( TString(sampleName).Contains("T_tChan")  )        sample = 2602;
  if( TString(sampleName).Contains("T_tWChan")  )       sample = 2604;
  if( TString(sampleName).Contains("Tbar_sChan")  )     sample = 2501;
  if( TString(sampleName).Contains("Tbar_tChan")  )     sample = 2503;
  if( TString(sampleName).Contains("Tbar_tWChan")  )    sample = 2505;
  if( TString(sampleName).Contains("DYJetsToLL")  )     sample = 2800;
  if( TString(sampleName).Contains("ZJets")  )          sample = 2800;
  if( TString(sampleName).Contains("WJetsToLNu")  )     sample = 2400;
  if( TString(sampleName).Contains("WJets")  )     sample = 2400;
  if( TString(sampleName).Contains("WW")  )             sample = 2700;
  if( TString(sampleName).Contains("WZ")  )             sample = 2701;
  if( TString(sampleName).Contains("ZZ")  )             sample = 2702;
  if( TString(sampleName).Contains("FastSim")  )        sample = 9500;
  if( TString(sampleName).Contains("FullSim")  )        sample = 8500;

  cout << "Sample Name: " << sampleName<< "  Sample #:    " << sample << endl;
  BEANs::setMCsample(sample, true, true, "");
      
  
  //////////////////////////////////////////////////////////////////////////
  ///  Booking Histograms
  //////////////////////////////////////////////////////////////////////////
  // book a set of histograms
  cout << "Booking histograms." << endl;
  // fwlite::TFileService fs = fwlite::TFileService( outputs.getParameter<std::string>("outputName") );

  // std::map<TString,TH1*> histograms;
  
  // Variables used for histogram ranges and binning
  double metmax   = 500.;
  double muptmax  = 350.;
  double jetptmax = 500.;
  double massmax  = 200.;

  int NmetBins   = int( metmax/10. + 0.0001 );
  int NmuptBins  = int( muptmax/10. + 0.0001 );
  int NjetptBins = int( jetptmax/10. + 0.0001 );
  int NmassBins  = int( massmax/1. + 0.0001 );


//   // Book the histograms

  /////////////// split the nGen
  TH1D* h_nGen = new TH1D("h_nGen",";ttH decay", 9, 0, 9 );
  std::vector<std::string> ttHdecay_names;
  ttHdecay_names.push_back("2tWb");
  ttHdecay_names.push_back("qq_emu");
  ttHdecay_names.push_back("qq_emutau");
  ttHdecay_names.push_back("qq_emu_bb");
  ttHdecay_names.push_back("qq_emutau_bb");
  ttHdecay_names.push_back("2emu");
  ttHdecay_names.push_back("2emutau");
  ttHdecay_names.push_back("2emu_bb");
  ttHdecay_names.push_back("2emutau_bb");
  int numttHdecays = int(ttHdecay_names.size());

  for( int i=0; i<numttHdecays; i++ ){
    h_nGen->GetXaxis()->SetBinLabel(i+1,ttHdecay_names[i].c_str());
  }

  /////////////////

//   TH1D* h_mu_pt = new TH1D("h_mu_pt",";#mu p_{T}", NmuptBins, 0, muptmax );
//   TH1D* h_mu_phi = new TH1D("h_mu_phi",";#mu #phi", 16, -3.2, 3.2 );
//   TH1D* h_mu_eta = new TH1D("h_mu_eta",";#mu #eta", 25, -2.5, 2.5 );
//   TH1D* h_dR_mu_hlt = new TH1D("h_dR_mu_hlt",";#DeltaR(#mu,hlt #mu)", 120, 0., 6. );

//   TH1D* h_jet_pt = new TH1D("h_jet_pt",";jet p_{T}", NjetptBins, 0, jetptmax );
//   TH1D* h_jet_phi = new TH1D("h_jet_phi",";jet #phi", 16, -3.2, 3.2 );
//   TH1D* h_jet_eta = new TH1D("h_jet_eta",";jet #eta", 25, -2.5, 2.5 );

//   TH1D* h_jet_pt_b = new TH1D("h_jet_pt_b",";b jet p_{T}", NjetptBins, 0, jetptmax );
//   TH1D* h_jet_pt_c = new TH1D("h_jet_pt_c",";c jet p_{T}", NjetptBins, 0, jetptmax );
//   TH1D* h_jet_pt_l = new TH1D("h_jet_pt_l",";light jet p_{T}", NjetptBins, 0, jetptmax );

//   TH1D* h_jet_disc_b = new TH1D("h_jet_disc_b",";b jet SSVHE discriminant", 70, -1.0, 6.0 );
//   TH1D* h_jet_disc_c = new TH1D("h_jet_disc_c",";c jet SSVHE discriminant", 70, -1.0, 6.0 );
//   TH1D* h_jet_disc_l = new TH1D("h_jet_disc_l",";light jet SSHVE discriminant", 70, -1.0, 6.0 );


 //  TH1D* h_met_pt = new TH1D("h_met_pt",";MET p_{T}", NmetBins, 0, metmax );
//   TH1D* h_met_phi = new TH1D("h_met_phi",";MET #phi", 16, -3.2, 3.2 );
//   TH1D* h_met_Upt = new TH1D("h_met_Upt",";MET raw p_{T}", NmetBins, 0, metmax );
//   TH1D* h_met_Uphi = new TH1D("h_met_Uphi",";MET raw #phi", 16, -3.2, 3.2 );

 int maxJetPlot = 6; // this determines how many jet plots you make

//   //Muon Variable Plots
//   TH1F* h_muPt       = new TH1F("h_muPt", "Muon p_{T}", 500, 0, 500);
//   TH1F* h_muEta      = new TH1F("h_muEta", "Muon #eta}", 628,-3.14, 3.14);
//    for (int iJet = minJets; iJet <=maxJetPlot ; ++iJet) {
//     TString histName = "h_muPt_"; histName += iJet; histName += "j";
//     TString histTitle = "Muon p_{T} (GeV/c) (N_{jets}";
//     histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//     histTitle += iJet;
//     histTitle += ")";
//     histograms[histName] = fs.make<TH1F>(histName, histTitle, 500, 0., 500.);
//   }
//   for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//     TString histName = "h_muEta_"; histName += iJet; histName += "j";
//     TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//     histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//     histTitle += iJet;
//     histTitle += ")";
//     histograms[histName] = fs.make<TH1F>(histName, histTitle,628,-3.14, 3.14);
//  }
//   // W Variable Plots
//   TH1F* h_muMET      = new TH1F("h_muMET", "MET", 500, 0, 500);
//   TH1F* h_muMt       = new TH1F("h_muMt", "Transverse mass #mu + #nu", 500, 0, 500);
//   for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//     TString histName = "h_muMET_"; histName += iJet; histName += "j";
//     TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//     histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//     histTitle += iJet;
//     histTitle += ")";
//     histograms[histName] = fs.make<TH1F>(histName, histTitle, 500, 0., 500.);
//   }
//    for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//      TString histName = "h_muMt_"; histName += iJet; histName += "j";
//      TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//      histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//      histTitle += iJet;
//      histTitle += ")";
//      histograms[histName] = fs.make<TH1F>(histName, histTitle, 500, 0., 500.);
//   }
  
//   //Jet Variable Plots
//   TH1F* h_nJets      = new TH1F("h_nJets", "number of Jets", 6,-2.5, 8.5);
//   TH1F* h_muM3       = new TH1F("h_muM3", "M3", 2000, 0, 2000);
//      for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//      TString histName = "h_muM3_"; histName += iJet; histName += "j";
//      TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//      histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//      histTitle += iJet;
//      histTitle += ")";
//      histograms[histName] = fs.make<TH1F>(histName, histTitle, 2000, 0., 2000.);
//    }
//   //Individual jet plots
//   for (int iJet = 1; iJet <= maxJetPlot; ++iJet) {
//     TString histName = "h_jet"; histName += iJet;
//     TString histTitle = ""; histTitle += iJet;
//     switch (iJet) {
//     case 1:
//       histTitle += "st";
//       break;
//     case 2:
//       histTitle += "nd";
//       break;
//     case 3:
//       histTitle += "rd";
//       break;
//     default:
//       histTitle += "th";
//       break;
//     }
//     histTitle += " Leading Jet";
//     cout << "Jet Pt Hist Name " << histName + "Pt" << endl; 

//     histograms[histName + "Pt"] = fs.make<TH1F>( histName+"Pt",   histTitle + " p_{T}", 300, 0, 300);
//     histograms[histName + "Eta"] = fs.make<TH1F>( histName+"Eta",  histTitle + " #eta", 50, -3.0,   3.0);
  
//   //Now, get really crazy and separate the above histograms by jet bin (i.e. Jet1Pt_1j, Jet1Pt_2j, etc.)
//   for (int jJet = minJets; jJet <= maxJetPlot; ++jJet) {
//     TString histName2 = histName + "Pt_"; histName2 += jJet; histName2 += "j";
//     TString histTitle2 = histTitle + " p_{T} (";
//     histTitle2 += ((jJet == maxJetPlot) ? "#geq" : "=");
//     histTitle2 += jJet;
//     histTitle2 += "-Jet Bin)";
//     histograms[histName2] = fs.make<TH1F>(histName2, histTitle2, 500, 0., 500.);
//   }
  
//   for (int jJet = minJets; jJet <= maxJetPlot; ++jJet) {
//     TString histName2 = histName + "Eta_"; histName2 += jJet; histName2 += "j";
//     TString histTitle2 = histTitle + " #eta (";
//     histTitle2 += ((jJet == maxJetPlot) ? "#geq" : "=");
//     histTitle2 += jJet;
//     histTitle2 += "-Jet Bin)";
//     histograms[histName2] = fs.make<TH1F>(histName2, histTitle2, 600, -3, 3);
//   }
//   }
      

//   //TTbar Variable Plots
//   TH1F* h_muHt       = new TH1F("h_muHt", "h_{T}", 2000, 0, 2000);
//   TH1F* h_muMttbar   = new TH1F("h_muMttbar", "M_{ttbar}", 4000, 0, 4000);
//   TH1F* h_muTTbarPt  = new TH1F("h_muTTbarPt", "ttbar_{Pt}", 4000, 0, 4000);
//   TH1F* h_muTTbarEta = new TH1F("h_muTTbarEta", "ttbar_{Eta}", 628,-3.14, 3.14);
//   TH1F* h_muTTbarY   = new TH1F("h_muTTbarY", "ttbar_{Y}", 628,-3.14, 3.14);
//   for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//      TString histName = "h_muHt_"; histName += iJet; histName += "j";
//      TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//      histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//      histTitle += iJet;
//      histTitle += ")";
//      histograms[histName] = fs.make<TH1F>(histName, histTitle, 2000, 0., 2000.);
//   }

//    for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//      TString histName = "h_muMttbar_"; histName += iJet; histName += "j";
//      TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//      histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//      histTitle += iJet;
//      histTitle += ")";
//      histograms[histName] = fs.make<TH1F>(histName, histTitle, 4000, 0., 4000.);
//    }
//     for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//       TString histName = "h_muTTbarPt_"; histName += iJet; histName += "j";
//       TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//       histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//       histTitle += iJet;
//       histTitle += ")";
//       histograms[histName] = fs.make<TH1F>(histName, histTitle, 4000, 0., 4000.);
//    }
//     for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//       TString histName = "h_muTTbarEta_"; histName += iJet; histName += "j";
//       TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//       histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//       histTitle += iJet;
//       histTitle += ")";
//       histograms[histName] = fs.make<TH1F>(histName, histTitle, 628,-3.14, 3.14);
//    }
//     for(int iJet = minJets; iJet <=maxJetPlot ; ++iJet){
//       TString histName = "h_muTTbarY_"; histName += iJet; histName += "j";
//       TString histTitle = "Muon #eta (GeV/c) (N_{jets}";
//       histTitle += ((iJet == maxJetPlot) ? "#geq" : "=");
//       histTitle += iJet;
//       histTitle += ")";
//       histograms[histName] = fs.make<TH1F>(histName, histTitle, 628,-3.14, 3.14);
//    }
//   //Other Plots 
//     TH1F* h_nPV         = new TH1F("h_nPV", "Number of Primary Verticies", 50,-0.5,49.5);
//     TH1F* h_numTrueMCPV = new TH1F("h_numTrueMCPV", "Number of Primary Verticies in MC", 50,0,50);
//     TH1F* h_weight      = new TH1F("h_weight", "weights", 10000,0,100);
//     TH1F* h_PUweight    = new TH1F("h_PUweight", "Pile Up weights", 10000,0,100);
  
 

 
//   //Electron Variable Plots
    // TH1F* h_elePt = new TH1F("h_elePt", "Electron p_{T}", 500, 0, 500);

//   TH2D* h_W0_decay_W1_decay = new TH2D("h_W0_decay_W1_decay",";W0 decay;W1 decay", 13, 0, 13, 13, 0, 13 );
//   TH1D* h_H_decay = new TH1D("h_H_decay",";H decay", 9, 0, 9 );
//   TH1D* h_H_mass = new TH1D("h_H_mass",";H mass", NmassBins, 0, massmax );



//   std::vector<std::string> Wdecay_names;
//   Wdecay_names.push_back("ud");
//   Wdecay_names.push_back("us");
//   Wdecay_names.push_back("ub");
//   Wdecay_names.push_back("cd");
//   Wdecay_names.push_back("cs");
//   Wdecay_names.push_back("cb");
//   Wdecay_names.push_back("td");
//   Wdecay_names.push_back("ts");
//   Wdecay_names.push_back("tb");
//   Wdecay_names.push_back("e#nu");
//   Wdecay_names.push_back("#mu#nu");
//   Wdecay_names.push_back("#tau#nu");
//   Wdecay_names.push_back("Other");

//   int numWdecays = int(Wdecay_names.size());

//   for( int i=0; i<numWdecays; i++ ){
//     h_W0_decay_W1_decay->GetXaxis()->SetBinLabel(i+1,Wdecay_names[i].c_str());
//     h_W0_decay_W1_decay->GetYaxis()->SetBinLabel(i+1,Wdecay_names[i].c_str());
//   }

//   std::vector<std::string> Hdecay_names;
//   Hdecay_names.push_back("b#bar{b}");
//   Hdecay_names.push_back("WW");
//   Hdecay_names.push_back("#tau#tau");
//   Hdecay_names.push_back("gg");
//   Hdecay_names.push_back("#gamma#gamma");
//   Hdecay_names.push_back("ZZ");
//   Hdecay_names.push_back("c#bar{c}");
//   Hdecay_names.push_back("Z#gamma");
//   Hdecay_names.push_back("Other");

//   int numHdecays = int(Hdecay_names.size());

//   for( int i=0; i<numHdecays; i++ ) h_H_decay->GetXaxis()->SetBinLabel(i+1,Hdecay_names[i].c_str());


  // Used to determine number of events that pass each cut

//   std::vector<std::string> cutflow_name;
//   cutflow_name.push_back("All Events"); //0 
//   cutflow_name.push_back("Cleaning"); //1
//   cutflow_name.push_back("Trigger"); //2
//   cutflow_name.push_back("*** >=1 tight muon");//3
//   cutflow_name.push_back("==2 tight muon"); //4
//   cutflow_name.push_back(" >= 2 jets");//5
//   cutflow_name.push_back(">=2 b-tagged jets"); //6
//   cutflow_name.push_back(">=3 jets"); //7
//   cutflow_name.push_back(">=3 b-tagged jets"); //8
//   cutflow_name.push_back("*** ==1 mu && ==1 ele"); //9
//   cutflow_name.push_back(">=2 jets"); //10
//   cutflow_name.push_back(">=2 b-tagged jets"); //11
//   cutflow_name.push_back(">=3 jets"); //12
//   cutflow_name.push_back(">=3 b-tagged jets"); //13
//   cutflow_name.push_back("*** ==2 ele"); //14
//   cutflow_name.push_back(">=2 jets"); //15
//   cutflow_name.push_back(">=2 b-tagged jets"); //16
//   cutflow_name.push_back(">=3 b-tagged jets"); //17
//   cutflow_name.push_back(">=3 b-tagged jets"); //18


//   int Ncuts = int(cutflow_name.size());

//   // cutflow
//   TH1D* h_cutflow_unwgt = new TH1D("h_cutflow_unwgt","",Ncuts, 0, Ncuts);
//   TH1D* h_cutflow = new TH1D("h_cutflow","",Ncuts, 0, Ncuts);
//   for( int i=0; i<Ncuts; i++ ){
//     h_cutflow->GetXaxis()->SetBinLabel(i+1,cutflow_name[i].c_str());
//     h_cutflow_unwgt->GetXaxis()->SetBinLabel(i+1,cutflow_name[i].c_str());
//   }


//   std::vector<std::string> selector_name;

//   for( int i=0; i<int(cutflow_name.size()); i++ ) selector_name.push_back(cutflow_name[i]);

//   int numSelectors = selector_name.size();
//   std::vector<std::vector<double> > selected(numSelectors, std::vector<double>(3) );
//   std::vector<std::vector<double> > selected_wgt(numSelectors, std::vector<double>(3) );

//   TH2D* h_cutflow_expand = new TH2D("h_cutflow_expand","", 3, 0, 3, numSelectors, 0, numSelectors );
//   TH2D* h_cutflow_expand_wgt = new TH2D("h_cutflow_expand_wgt","", 3, 0, 3, numSelectors, 0, numSelectors );

//   for( int i=0; i<numSelectors; i++ ){
//     h_cutflow_expand->GetYaxis()->SetBinLabel(numSelectors-i,selector_name[i].c_str());
//     h_cutflow_expand_wgt->GetYaxis()->SetBinLabel(numSelectors-i,selector_name[i].c_str());
//     for( int j=0; j<3; j++ ){
//       selected[i][j]=0.;
//       selected_wgt[i][j]=0.;
//       if( i==0 ){
// 	if( j==0 ){
// 	  h_cutflow_expand->GetXaxis()->SetBinLabel(j+1,"Selected");
// 	  h_cutflow_expand_wgt->GetXaxis()->SetBinLabel(j+1,"Selected");
// 	}
// 	else if( j==1 ){
// 	  h_cutflow_expand->GetXaxis()->SetBinLabel(j+1,"N - 1");
// 	  h_cutflow_expand_wgt->GetXaxis()->SetBinLabel(j+1,"N - 1");
// 	}
// 	else if( j==2 ){
// 	  h_cutflow_expand->GetXaxis()->SetBinLabel(j+1,"Cumulative");
// 	  h_cutflow_expand_wgt->GetXaxis()->SetBinLabel(j+1,"Cumulative");
// 	}
//       }
//     }
//   }

  ///////////////////////////////////////////////////////////////////
  //
  // Make a small tree called summaryTree that stores all your 
  // information event by events
  //
  ///////////////////////////////////////////////////////////////////

  std::map<TString, int *> intBranches;
  ///---- categories lable
  //intBranches["PassTwoLepton"] = new int (0);
  //intBranches["TwoMuon"] = new int (0);
  //intBranches["TwoEle"] = new int (0);
  //intBranches["MuonEle"] = new int (0);

  intBranches["ExactOneTightMu"] = new int (0);
  intBranches["ExactOneTightEle"] = new int (0);
  
  intBranches["numJets"] = new int (0);
  intBranches["numTaggedJets"] = new int (0);
  intBranches["numNonTaggedJets"] = new int (0);

  intBranches["numTightMuons"] = new int (0);
  intBranches["numLooseMuons"] = new int (0);
  intBranches["numTightElectrons"] = new int (0);
  intBranches["numLooseElectrons"] = new int (0);

  intBranches["isMuonEvent"] = new int (0);
  intBranches["isElectronEvent"] = new int (0);

  intBranches["isCleanEvent"] = new int (0);
  intBranches["isTriggerPass"] = new int (0);

  std::map<TString, unsigned int *> uintBranches;

  uintBranches["runNumber"] = new unsigned int (0);
  uintBranches["eventNumber"] = new unsigned int (0);
  uintBranches["luminosityBlock"] = new unsigned int (0);

  ////Robin ///------------variables--------------------
  std::map<TString, float *> floatBranches;
  //b-tag reweight                                                                                                               
  floatBranches["prob"] = new float(0.0);                                                                                        
  floatBranches["prob_hfSFup"] = new float(0.0);                                                                                 
  floatBranches["prob_hfSFdown"] = new float(0.0);                                                                               
  floatBranches["prob_lfSFup"] = new float(0.0);                                                                                 
  floatBranches["prob_lfSFdown"] = new float(0.0);                                                                               

  //pile up
  floatBranches["numPV"] = new float(0.0);
  floatBranches["weight"] = new float(0.0);
  floatBranches["PUweight"] = new float(0.0);
  floatBranches["weight_PUup"] = new float(0.0);
  floatBranches["weight_PUdown"] = new float(0.0);

  //met
  floatBranches["met"] = new float(0.0);
  floatBranches["metTruth"] = new float(0.0);
  floatBranches["unc_met"] = new float(0.0);

  //mT
  floatBranches["mT"] =  new float(0.0);
  floatBranches["mTTruth"] =  new float(0.0);

  ///lepton variables
  floatBranches["leptonPt"] = new float(0.0);
  floatBranches["lepPtTruth"] = new float(0.0);
  floatBranches["leptonEta"] = new float(0.0);
  floatBranches["lepEtaTruth"] = new float(0.0);
  floatBranches["lep1Pt"] = new float(0.0);
  // floatBranches["lep2Pt"] = new float(0.0);
  floatBranches["lep1Eta"] = new float(0.0);
  // floatBranches["lep2Eta"] = new float(0.0);
  floatBranches["lep1Phi"] = new float(0.0);
  //floatBranches["lep2Phi"] = new float(0.0);
 //  floatBranches["mass_leplep"] = new float(0.0);
//   floatBranches["pt_leplep"] = new float(0.0);
//   floatBranches["dPhi_leplep"] = new float(0.0);
//   //  floatBranches["dEta_leplep"] = new float(0.0);
//   floatBranches["dR_leplep"] = new float(0.0);

  /// jet variables
  floatBranches["numJets_float"] = new float (0);
  floatBranches["numTaggedJets_float"] = new float (0);

  floatBranches["first_jet_pt"] = new float(0.0);
  floatBranches["second_jet_pt"] = new float(0.0);
  floatBranches["third_jet_pt"] = new float(0.0);
  floatBranches["fourth_jet_pt"] = new float(0.0);
  // floatBranches["first_jet_eta"] = new float(0.0);
//   floatBranches["second_jet_eta"] = new float(0.0);
//   floatBranches["third_jet_eta"] = new float(0.0);
//   floatBranches["fourth_jet_eta"] = new float(0.0);


  floatBranches["min_dr_tagged_jets"] = new float(0.0);
  floatBranches["avg_dr_tagged_jets"] = new float(0.0);
  //floatBranches["mindr_lep1_jet"] = new float(0.0);
  // floatBranches["mindr_lep2_jet"] = new float(0.0);
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
  floatBranches["m3"] = new float(0.0);
  floatBranches["m3Truth"] = new float(0.0);
  floatBranches["Mttbar"] = new float(0.0);
  floatBranches["MttbarTruth"] = new float(0.0);
  floatBranches["ttbarPt"] = new float(0.0);
  floatBranches["ttbarPtTruth"] = new float(0.0);
  floatBranches["ttbarEta"] = new float(0.0);
  floatBranches["ttbarEtaTruth"] = new float(0.0);
  floatBranches["ttbarY"] = new float(0.0);
  floatBranches["ttbarYTruth"] = new float(0.0);
  floatBranches["sum_pt"] = new float(0.0); 
  floatBranches["all_sum_pt"] = new float(0.0);
  floatBranches["Ht"] = new float(0.0);


  ////////////////////  
  histofile.cd();

 
  TTree * summaryTree = new TTree ("summaryTree", "Summary Event Values");
  //summaryTree.cd();

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

  bool verbose = false;
  TString histName;
  //
  // Loop over events
  //
  int nJets = -1;
  std::cout << "========  Starting Event Loop  ========" << std::endl;
  try { cout << "try? "<< endl;
    cout << "next" << endl;
    cout << "event begin?" << ev.toBegin()<< endl;
    for( ev.toBegin(); !ev.atEnd(); ++ev) {
      cnt++;
      if( cnt==1 )        std::cout << "     Event " << cnt << std::endl;
      if( cnt%1000==0 && cnt!=1 ) std::cout << "           " << cnt << "\t" 
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

      bool isMuonEvent = false;
      bool isEleEvent = false;

      if (verbose) std::cout << "Getting collections... " <<std::endl;
      //std::cout << "========  Event! ========" << std::endl;
      // Get Handle for each collection used
      fwlite::Handle<BNeventCollection> h_event;
      h_event.getByLabel(ev,"BNproducer");
      BNeventCollection const &events = *h_event;

      fwlite::Handle<BNmuonCollection> h_muons;
      h_muons.getByLabel(ev,"BNproducer","selectedPatMuonsPFlow");
      BNmuonCollection const &muons = *h_muons;

      fwlite::Handle<BNmetCollection> h_pfmet;
      h_pfmet.getByLabel(ev,"BNproducer","patMETsPFlow");
      BNmetCollection const &pfmets = *h_pfmet;

      fwlite::Handle<BNtriggerCollection> h_hlt;
      h_hlt.getByLabel(ev,"BNproducer","HLT");
      BNtriggerCollection const &hlt = *h_hlt;

     //  fwlite::Handle<BNtriggerCollection> h_tiggers;
//       h_triggers.getByLabel(ev,"BNproducer","HLT");
//       BNtriggerCollection const &tiggers = *h_triggers;

//       fwlite::Handle<BNtriggerCollection> h_tiggerobjs;
//       h_triggerobjs.getByLabel(ev,"BNproducer","HLT");
//       BNtriggerCollection const &triggerobj = *h_triggerobjs;

      fwlite::Handle<BNprimaryvertexCollection> h_pvs;
      h_pvs.getByLabel(ev,"BNproducer","offlinePrimaryVertices");
      BNprimaryvertexCollection const &pvs = *h_pvs;

      fwlite::Handle<BNjetCollection> h_pfjets;
      h_pfjets.getByLabel(ev,"BNproducer","selectedPatJetsPFlow");
      BNjetCollection const &pfjets = *h_pfjets;

      fwlite::Handle<BNelectronCollection> h_electrons;
      h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsPFlow");
      BNelectronCollection const &electrons = *h_electrons;

      fwlite::Handle<BNmcparticleCollection> h_mcparticles;
      h_mcparticles.getByLabel(ev,"BNproducer","MCstatus3");
      BNmcparticleCollection const &mcparticles = *h_mcparticles;

      fwlite::Handle<BNtrigobjCollection> h_hltobj;
      h_hltobj.getByLabel(ev,"BNproducer","HLT");
      BNtrigobjCollection const &hltobjs = *h_hltobj;

      if (verbose) std::cout << "Getting collections... " <<std::endl;

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

     
      double numTruePV = event->numTruePV;
      int numGenPV = event->numGenPV;

      //Pile Up Reweighting with BeanUtilities.h
      float PUwgt = 1;
      float PUwgt_up = 1;
      float PUwgt_down = 1;

      float wgt = 1 ;
      double PU = 0.0;
      double PUup = 0.0;
      double PUdown =0.0;
      BEANs::getPUwgt(numTruePV,PU,PUup,PUdown);
      PUwgt = PU;
      PUwgt_up = PUup;
      PUwgt_down = PUdown;
      if(isData) {
        PUwgt = 1;
        PUwgt_up = 1;
        PUwgt_down = 1;
      }

      wgt *= PUwgt;
      // cout << "PUwgt for this event: " << PUwgt  << " New weight: " << wgt << endl;



 

      //============================================
      //
      // Filter out different kinds of ttbar events
      //
      //
      //===========================================
      /////////  need modification for ttbar scale samples 
      //      cout << "Sample type is = " <<sample <<endl;

      if (sample == 2510 || sample == 2511){
	//        cout << "ERROR: incorrect sample number detected for scale up down samples "  << endl
	//             << "Resetting sample to 2500 "  <<endl;
	sample = 2500;
      }
      /////////////////////////////////////////
      //   Loop Over the Gen Particles
      /////////////////////////////////////////
       int nTop = 0;
        TLorentzVector ttbarTruthLV;
        TLorentzVector muonTruthLV;
        TLorentzVector neutrinoTruthLV;
        TLorentzVector WTruthLV;
        TLorentzVector WTransTruthLV;
        float muonTruthEta;
      for( unsigned i=0; i< mcparticles.size(); i++ ){
        int id = mcparticles.at(i).id;
        int motherID = mcparticles.at(i).motherId;
        int status = mcparticles.at(i).status;
        //tops
        if(abs(id) ==6 && status ==3){
           TLorentzVector topTruthLV;
           topTruthLV.SetPxPyPzE(mcparticles.at(i).px,mcparticles.at(i).py,mcparticles.at(i).pz,mcparticles.at(i).energy);
           ttbarTruthLV += topTruthLV;
           ++nTop;
        }//end tops

        //muons
        if(abs(id) ==13 && status ==3){
          if(abs(mcparticles.at(i).motherId) == 24 && abs(mcparticles.at(i).grandMotherId)==6){
            muonTruthLV.SetPxPyPzE(mcparticles.at(i).px,mcparticles.at(i).py,mcparticles.at(i).pz,mcparticles.at(i).energy);
            WTruthLV += muonTruthLV;
            muonTruthEta= mcparticles.at(i).eta;
          }
        }//end muons
         
        //muon neutrino
        if(abs(id) ==14 && status ==3){
          neutrinoTruthLV.SetPxPyPzE(mcparticles.at(i).px,mcparticles.at(i).py,mcparticles.at(i).pz,mcparticles.at(i).energy);
          WTruthLV += neutrinoTruthLV;
        }// end neutrinos
         

        }//end loop over mcparticles
      WTransTruthLV = WTruthLV;
      WTransTruthLV.SetPz(0.);
      WTransTruthLV.SetE(WTruthLV.Pt());

           
      if (sample==123){

        
        bool keepEvent = false;


        bool debug_ = false;
        if (debug_) cout << "GENCUT: Sample is 2500" << endl;
   
        int ttbarType_;

        TString ttbarName = sampleName ;
        if( ttbarName.EndsWith("ttbar") ) ttbarType_ = 0;
        else if (ttbarName.EndsWith("ttbar_bb")) ttbarType_ = 1;
        else if (ttbarName.EndsWith("ttbar_cc")) ttbarType_ = 2;
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

        cout << "Loop Over the Gen Particles " << endl;
       
       
       
        // check to see if the event has a c with a 
       //  // parent W
        for( unsigned i=0; i< mcparticles.size(); i++ ){
          int id = mcparticles.at(i).id;
          int motherID = mcparticles.at(i).motherId;
          int status = mcparticles.at(i).status;
          cout << "in Gen Partilce loop" << endl;
          //tops
          if(abs(id) ==6 && status ==3){
            ttbarTruthLV.SetPxPyPzE(mcparticles.at(i).px,mcparticles.at(i).py,mcparticles.at(i).pz,mcparticles.at(i).energy);
            cout << "Mttbar truth?: " << ttbarTruthLV.M() << endl;
            double ttbarPTtruth = mcparticles.at(i).pt;
            //double ttbarMtruth  = mcparticles.at(i).M;
          }

        }//end loop over mcparticles


 
//         bool isBBbarEvent = false;
//         bool isCCbarEvent = false;


//         bool gotB = false;
//         bool gotC = false;

//         int numBmomB=0;
//         int numBmomT=0;
//         int numBbarmomBbar=0;
//         int numBbarmomTbar=0;
//         int numCmomC=0;
//         int numCbarmomCbar=0;


        for( int i=0; i<int(pfjets.size()); i++ ){
          int id = pfjets.at(i).genPartonId;
          if( id==-99 ) continue;
          int motherID = pfjets.at(i).genPartonMotherId;

          // check to see if pf jets is from a  b/c and mother is a gluon
          // or, if mother is some light quark
          // if( abs(id)==5 && ( motherID==21 || abs(motherID)<abs(id) ) ) gotB=true;
          //if( abs(id)==4 && ( motherID==21 || abs(motherID)<abs(id) ) ) gotC=true;

         //  // if things are their own mother, 
//           // where are they from? Does this mean stable?
//           if( id==5  && motherID==id ) numBmomB++;
//           if( id==-5 && motherID==id ) numBbarmomBbar++;

//           if( id==4  && motherID==id ) numCmomC++;
//           if( id==-4 && motherID==id ) numCbarmomCbar++;

//           if( id==5  && motherID==6  ) numBmomT++;
//           if( id==-5 && motherID==-6 ) numBbarmomTbar++;
        }//loop over jets
        
       //  // if at least one b from b & one b from t, or if CC, and your jet was not b
//         if( ((numBmomB>=1 && numBmomT>=1) || (numBbarmomBbar>=1 && numBbarmomTbar>=1)) && !gotB ){
//           // for each jet that is  b from b
//           for( int i=0; i<int(pfjets.size()); i++ ){
//             int id0 = pfjets.at(i).genPartonId;
//             int motherID0 = pfjets.at(i).genPartonMotherId;
//             if( !(abs(id0)==5 && motherID0==id0) ) continue;

//             // for each jet that is b from t
//             for( int j=0; j<int(pfjets.size()); j++ ){
//               int id1 = pfjets.at(j).genPartonId;
//               int motherID1 = pfjets.at(j).genPartonMotherId;
//               if( !(id1==id0 && abs(motherID1)==6) ) continue;

//               // if delta r between b from b and b from t is big enough, then b in final state is OK
//               double dR = kinem::delta_R(pfjets.at(i).genPartonEta,
//                                          pfjets.at(i).genPartonPhi,
//                                          pfjets.at(j).genPartonEta,
//                                          pfjets.at(j).genPartonPhi);
//               if( dR>0.3 ){
//                 gotB = true;
//                 break;
//               }
//             }
//             if( gotB ) break;
//           }
//         }

//         if( (numCmomC>=1 || numCbarmomCbar>=1) && !isWtoCS ){
//           gotC = true;
//         }

//         if( gotB ) isBBbarEvent = true;
//         else if( gotC ) isCCbarEvent = true;
    
   
//         if( ttbarType_<0 || sample != 2500)       keepEvent = true;
//         else if( ttbarType_ ==0 && !isBBbarEvent && !isCCbarEvent ) keepEvent = true;
//         else if( ttbarType_ ==1 &&  isBBbarEvent && !isCCbarEvent ) keepEvent = true;
//         else if( ttbarType_ >1  && !isBBbarEvent && isCCbarEvent  ) keepEvent = true;

//         if (debug_) cout << "Filter result = " << keepEvent << endl
//                          << "isBBbarEvent = " << isBBbarEvent << endl
//                          << "isCCbarEvent = " << isCCbarEvent << endl
//                          << "... will we skip this? " << (!keepEvent) << endl;
        
//         // if you don't pass the filter, skip this event

//         if (debug_) cout << "Keep event no matter what" << endl;
//         //keepEvent = true;
        
//         if(!keepEvent) continue;
      }// end if you are a top sample

      //-------------------------------------
      //-------------------------------------

      if (verbose) std::cout << "met stuff " <<std::endl;
      
      MetIter pfmet = pfmets.begin();
      // MetIter calomet = calomets.begin();
      // MetIter tcmet = tcmets.begin();

   
    //   // Type I corrected MET
//       h_met_pt->Fill(pfmet->pt,wgt);
//       h_met_phi->Fill(pfmet->phi,wgt);
//       // Uncorrected / raw MET
//       h_met_Upt->Fill(pfmet->Upt,wgt);
//       h_met_Uphi->Fill(pfmet->Uphi,wgt);
     
      
      // Loop over and count the number of primary vertices
      int numpv = 0;
      for( int i=0; i<int(pvs.size()); i++ ){
	bool isGood = ( (pvs.at(i).ndof>=minNDOF) &&
			(fabs(pvs.at(i).z)<maxAbsZ) &&
			(fabs(pvs.at(i).rho)<maxd0) );
	bool isFake = ( pvs.at(i).isFake==1 );
	if( isGood && !isFake ) numpv++;
      }

      if (verbose) std::cout << "about to do pu reweight " <<std::endl;
      ///--------------------------------
     
     

      
      ///--------------------------------
      // Trigger Requirement
      bool triggerFound = false;
      bool triggerPass  = false;

      if (verbose) std::cout << "about to do pu reweight " <<std::endl;
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



      nevents++;
      nevents_wgt+=wgt;

//       int mcut = 0;
//       h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // preselection 0



      // Event cleaning requirements
      bool passGoodVertex = ( numpv>0 ) ? true : false;
      bool passFilterOutScraping = ( event->FilterOutScraping==1 ) ? true : false;
      bool passHBHENoiseFilter = ( event->HBHENoiseFilter==1 ) ? true : false;

      bool cleanEvent = ( passGoodVertex && passFilterOutScraping && passHBHENoiseFilter );
      cleanEvent = (isData) ? cleanEvent: true;


      //////////split nGen
      if( sample==120 ){
	bool has2tWb = false;
	bool has2tWb_Wqq_Wemu = false;
	bool has2tWb_Wqq_Wemutau = false;
	bool has2tWb_Wqq_Wemu_Hbb = false;
	bool has2tWb_Wqq_Wemutau_Hbb = false;
	bool has2tWb_2Wemu = false;
	bool has2tWb_2Wemutau = false;
	bool has2tWb_2Wemu_Hbb = false;
	bool has2tWb_2Wemutau_Hbb = false;

	int numWt=0, numbH=0, numqW=0, numlnuW=0, numlnutauW=0;
	for( int i=0; i<int(mcparticles.size()); i++ ){
	  int id = mcparticles.at(i).id;
	  int motherID = mcparticles.at(i).motherId;
	  int grandMotherID = mcparticles.at(i).grandMotherId;

	  if( abs(id)==24 && abs(motherID)==6 ) numWt++;
	  if( abs(id)==5 && abs(motherID)==25 ) numbH++;
	  if( abs(id)<=5 && abs(motherID)==24 && abs(grandMotherID)==6 ) numqW++;
	  if( (abs(id)>=11 && abs(id)<=14) && abs(motherID)==24 && abs(grandMotherID)==6 ) numlnuW++;
	  if( (abs(id)>=11 && abs(id)<=16) && abs(motherID)==24 && abs(grandMotherID)==6 ) numlnutauW++;
	}

	if( numWt==2 ) has2tWb = true;
	if( numqW==2 && numlnuW==2 ) has2tWb_Wqq_Wemu = true;
	if( numqW==2 && numlnutauW==2 ) has2tWb_Wqq_Wemutau = true;
	if( has2tWb_Wqq_Wemu && numbH==2 ) has2tWb_Wqq_Wemu_Hbb = true;
	if( has2tWb_Wqq_Wemutau && numbH==2 ) has2tWb_Wqq_Wemutau_Hbb = true;
	if( numlnuW==4 ) has2tWb_2Wemu = true;
	if( numlnutauW==4 ) has2tWb_2Wemutau = true;
	if( has2tWb_2Wemu && numbH==2 ) has2tWb_2Wemu_Hbb = true;
	if( has2tWb_2Wemutau && numbH==2 ) has2tWb_2Wemutau_Hbb = true;

    
	// if( has2tWb ) h_nGen->Fill(0);
// 	if( has2tWb_Wqq_Wemu ) h_nGen->Fill(1);
// 	if( has2tWb_Wqq_Wemutau ) h_nGen->Fill(2);
// 	if( has2tWb_Wqq_Wemu_Hbb ) h_nGen->Fill(3);
// 	if( has2tWb_Wqq_Wemutau_Hbb ) h_nGen->Fill(4);
// 	if( has2tWb_2Wemu ) h_nGen->Fill(5);
// 	if( has2tWb_2Wemutau ) h_nGen->Fill(6);
// 	if( has2tWb_2Wemu_Hbb ) h_nGen->Fill(7);
// 	if( has2tWb_2Wemutau_Hbb ) h_nGen->Fill(8);
      }
    
      //////////



      if (verbose) std::cout << "about to do ele selection " <<std::endl;

      
      /////////
      ///
      /// Electrons
      ///
      ////////
      float leptonPt = 0.0 ;
      float leptonEta = -5;
     
   
      std::vector<int> tight_ele_index;
      std::vector<int> loose_ele_index;
      std::vector<int> only_loose_ele_index;
      for( int i=0; i<int(electrons.size()); i++ ){
        double eleSCEta = electrons.at(i).scEta;
        double absSCeta = fabs(eleSCEta);
        double eleEta = electrons.at(i).eta;
        double mvaID = electrons.at(i).mvaTrigV0;
        float elePt = electrons.at(i).pt;
        bool isCrack = ( (absSCeta>1.4442) && (absSCeta<1.5660) );
      	bool kin = ( (elePt>20.) && (mvaID>0.0) && fabs(eleEta)<2.5 );

      	if( !kin ) continue; //check that ele passes loose kin cuts

        double chargedHadronIso = electrons.at(i).chargedHadronIso;
        double neutralHadronIso = electrons.at(i).neutralHadronIso;
        double photonIso = electrons.at(i).photonIso;
        double rhoCorr = electrons.at(i).AEffDr03*electrons.at(i).rhoPrime;
        
        double relIso = ( chargedHadronIso + max(0.0, neutralHadronIso + photonIso - rhoCorr )) * 1./elePt;
        bool looseIso = ( relIso < 0.2 );
        if( !looseIso ) continue; //check that ele passes loose pfIso cuts

        int eidBitTight = electrons.at(i).eidTight;
        bool eidTight = ( (eidBitTight & 1)==1 );
        bool d0 = ( fabs(electrons.at(i).correctedD0) < 0.02 );
        bool dZ = ( fabs(electrons.at(i).correctedDZ) < 1. );
        bool dist  = ( fabs(electrons.at(i).dist)<0.02 );
        bool dcot  = ( fabs(electrons.at(i).dcot)<0.02 );
        bool nlost = ( electrons.at(i).numberOfLostHits<1 );
        bool notConv = ( !(dist && dcot) && nlost );
        bool tightIso = ( relIso < 0.1 );
      	bool id = ( eidTight && d0 && dZ && notConv );
        if(useElectronSelection){
          if( ((elePt>20.) && id && tightIso) ) {
            tight_ele_index.push_back(i);
            leptonPt = elePt;
            leptonEta = eleEta;
            isEleEvent = true;
          }else {
            loose_ele_index.push_back(i);
          }
        }else{//end use exact electron selection
        if( (elePt>20.) && tightIso){
             tight_ele_index.push_back(i);
             leptonPt = elePt;
             leptonEta = eleEta;
             isEleEvent = true;
           }
        }
      }//end electron loop

      int numTightElectrons = int(tight_ele_index.size());
      int numLooseElectrons = int(loose_ele_index.size());


      /////////
      ///
      /// Muons
      ///
      ////////
      

      std::vector<int> tight_mu_index;
      std::vector<int> loose_mu_index;
      std::vector<int> only_loose_mu_index;
      for( int i=0; i<int(muons.size()); i++ ){
        float muPt  = muons.at(i).pt;
        double muEta = muons.at(i).eta;
        double muPhi = muons.at(i).phi;
        double muAbsEta = fabs(muEta);
        double chargedHadronIso = muons.at(i).pfIsoR04SumChargedHadronPt;
        double neutralHadronIso = muons.at(i).pfIsoR04SumNeutralHadronEt;
        double photonIso = muons.at(i).pfIsoR04SumPhotonEt;
        double deltaBetaCorr = muons.at(i).pfIsoR04SumPUPt;
        double relIso = ( chargedHadronIso + max(0.0, neutralHadronIso + photonIso - 0.5*deltaBetaCorr ) ) * 1./muPt;
        bool looseIso = ( relIso<0.2 );
        bool tightIso = ( relIso<0.12 );
        bool isGlobalMuon = ( muons.at(i).isGlobalMuon==1 );
        bool isTrackerMuon = (  muons.at(i).isTrackerMuon==1 );
        bool isGlobalMuonPromptTight = ( muons.at(i).isGlobalMuonPromptTight==1 );
        bool chiSq = ( muons.at(i).normalizedChi2 < 10);
        bool numLayerMeas = ( muons.at(i).numberOfLayersWithMeasurement > 5);
        bool validMuonHits = ( muons.at(i).numberOfValidMuonHits >0);
        bool passd0 = ( fabs(muons.at(i).correctedD0)<0.2 );
        bool passdz = ( fabs(muons.at(i).correctedDZ)<0.5 );
        bool validPixHits = ( muons.at(i).numberOfValidPixelHits >0);
        bool numberOfMatches = ( muons.at(i).numberOfMatches>1 );
        bool id = ( isTrackerMuon  && chiSq && numLayerMeas && validMuonHits &&  passd0 && passdz &&
                    validPixHits && numberOfMatches);
        if(useMuonSelection){
          bool kin = ( (muPt>10.) && (muAbsEta<2.5) );
          if( !kin ) continue; // mu passes loosse kin cuts 
          if( !(isGlobalMuon && looseIso) ) continue; // mu passes loosse kin cuts 
          if( ((muPt>26.) && (muAbsEta<2.1) && id && tightIso) ){
            tight_mu_index.push_back(i);
            leptonPt = muPt;
            leptonEta = muEta;
            isMuonEvent = true;
          	} // end if tight muon
          else {
            loose_mu_index.push_back(i);
          }
        }else{ //end use exact Muon Selection
          if(muPt>26 && tightIso){
            tight_mu_index.push_back(i);
            leptonPt = muPt;
            leptonEta = muEta;
            isMuonEvent = true;
          }
        }
      }// end muon loop
      if(tight_ele_index.size()>0) continue;
      if(tight_mu_index.size()>1) continue; //only ever look at mu+Jets
      if(useMuonSelection){
        if(loose_mu_index.size()>0) continue;
        if(loose_ele_index.size()>0) continue;
      }
      if(useMuonSelection && isMuonEvent && isEleEvent){cout << "Both muon and electron in this event!" << endl;}


      if (verbose) std::cout << "done with muons" <<std::endl;      

      int numTightMuons = int(tight_mu_index.size());
      int numLooseMuons = int(loose_mu_index.size());


//       if (numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons >= 2 )
//         std::cout << "Done with lepton selection... this event could be dilepton " << std::endl
//                                << "numTightMuons = " << numTightMuons << std::endl
//                                <<" numLooseMuons = " << numLooseMuons << std::endl
//                                << "numTightElectron = " << numTightElectrons << std::endl
//                                << "numLooseElectrons = " << numLooseElectrons << std::endl;
        
      //      if ( numLooseMuons != int(only_loose_mu_index.size()) ) std::cout << ".......failure, lalala............" << std::endl;     
      bool twoLeptons = (( numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons )== 2 && ( numTightMuons + numTightElectrons )> 0 );
      // if ( !twoLeptons ) continue ;
    
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
      vdouble jet_eta;
      vdouble jet_energy;

      int numGoodJets=0;
      int nJetsPlot=0;
      TLorentzVector jetV[100];
      std::list<float> jet_desc;      


      double totalDeltaPx = 0.0;
      double totalDeltaPy = 0.0;

      bool jerDebugPrint = false;

      /////////////////////////////////////////////////
      //
      //   Loop over jets
      //
      // 
      /////////////////////////////////////////////////

      if (jerDebugPrint || verbose)
        cout << "\n--------------new event------------------" << endl;

      int passingJets = 0;
      for( int i=0; i<int(pfjets.size()); i++ ){
        
        jet_px.push_back(pfjets.at(i).px);
        jet_py.push_back(pfjets.at(i).py);
        jet_pz.push_back(pfjets.at(i).pz);
        jet_pt.push_back(pfjets.at(i).pt);
        jet_eta.push_back(pfjets.at(i).eta);
        jet_energy.push_back(pfjets.at(i).energy);

        // Apply JES uncertainty to all jets
        double unc = pfjets.at(i).JESunc;
        
        jet_px[i] *= (1. + jes*unc);
        jet_py[i] *= (1. + jes*unc);
        jet_pz[i] *= (1. + jes*unc);
        jet_pt[i] *= (1. + jes*unc);
        jet_energy[i] *= (1. + jes*unc);

    	double jetPt = pfjets.at(i).pt;
        jetPt *= (1. + jes*unc);

        // Apply JER uncertainty to all jets

        // 0 for nominal, 1 for up, -1 for down
        double jetEta = pfjets.at(i).eta;
        double jetAbsEta = fabs(jetEta);
        double genJetPT = pfjets.at(i).genPartonPT;
        double jetPhi = pfjets.at(i).phi;
        
        double myJER = getJERfactor( jer, jetAbsEta, genJetPT, jetPt);

        if( isData){
          myJER = 1.0;
        }

        double deltaPx = jet_px[i] * (myJER - 1.0);
        double deltaPy = jet_py[i] * (myJER - 1.0);

        if (jerDebugPrint || verbose)
          std::cout << "Jet num " << i << "  Old px " << jet_px[i] << " new px " << jet_px[i]*myJER
                    << " delta px " << deltaPx << std::endl
                    << "      Old py " << jet_py[i] << " new py " << jet_py[i]*myJER
                    << " delta py " << deltaPy << std::endl;
        
        jet_px[i] *= myJER;
        jet_py[i] *= myJER;
        jet_pz[i] *= myJER;
        jet_pt[i] *= myJER;
        jet_energy[i] *= myJER;	
        jetPt *= myJER;
    

        bool tightJetPt = ( jetPt>30. );
        bool looseJetPt = ( jetPt>30. );//Tessa change this back to 20!!!
        bool eta = ( jetAbsEta<2.5 );
        //bool id  = ( pfjets.at(i).jetIDLoose==1 );
        bool id = (     (pfjets.at(i).nconstituents > 1)   &&
                        (pfjets.at(i).neutralHadronEnergyFraction < 0.99) &&
                        (pfjets.at(i).neutralEmEnergyFraction < 0.99)  &&
                        (pfjets.at(i).chargedEmEnergyFraction < 0.99 ||fabs(jetEta)<2.4 ) &&
                        (pfjets.at(i).chargedHadronEnergyFraction > 0 ||fabs(jetEta)<2.4) &&
                        (pfjets.at(i).chargedMultiplicity > 0 ||fabs(jetEta)<2.4)
                        );

        if( !(looseJetPt && eta && id) ) continue;
            
        jetV[numGoodJets].SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
        numGoodJets++;
        tight_pfjet_index.push_back(i);
        
        totalDeltaPx += deltaPx;
        totalDeltaPy += deltaPy;

        if (jerDebugPrint || verbose) 
          std::cout << "*** Tight Jet Num = " << i << "  Jet abs eta = " << jetAbsEta
                    << "  Gen Jet Pt = " << genJetPT << "  jetPt = " << jetPt
                    << "  JER factor = " << myJER << std::endl
                    << "    deltaPx = " << deltaPx << " deltaPy = " << deltaPy 
                    << "    totalDeltaPx = " << totalDeltaPx
                    << " totalDeltaPy = " << totalDeltaPy << std::endl ;

        // Use Combined tags
        // Loose Cut is 0.244
        // Medium Cut is 0.679
        // Tight Cut is 0.898
        float csv = pfjets.at(i).btagCombinedSecVertex;
        bool csvM (csv>btagThres);
        
        if( csvM ){
          tag_pfjet_index.push_back(i);
          jet_desc.push_back(csv);
        }else{untag_pfjet_index.push_back(i);}
	
        int flavor = pfjets.at(i).flavour;
        good_jet_pt.push_back(jetPt);
        good_jet_eta.push_back(jetEta);
        good_jet_tag.push_back(csv);
        good_jet_flavor.push_back(flavor);

      }// end for each pf jet
      
      //cut on number of jets
      if(numGoodJets < minJets){continue;}

      //Set up Jet bin plots
      nJetsPlot = numGoodJets;
      if(nJetsPlot > maxJetPlot) { nJetsPlot = maxJetPlot;}

      // Btag cut
      if (nTags >= 1){
        if(tag_pfjet_index.size()<nTags){continue;}
       }
      if(nTags == 0 ){
        if(tag_pfjet_index.size()> 0){continue;}
      }

     //  //Information about each event that passes cuts
//       cout << "This event has passed! "<< endl;
//       cout << "n btags: " <<tag_pfjet_index.size() << endl;
//       for( int i=0; i<int(muons.size()); i++ ){
//         cout << "mu " << i << ":  pt: " << muons.at(i).pt << endl;
//       }
//       cout << "njets passing? " << passingJets << endl;
//       for (int i=0; i<numGoodJets; i++ ){
//         cout << "jet " << i << ":  pt: " << jetV[i].Pt() << endl;
//         //  cout << "jet " << i << ":  pt: " << pfjets.at(i).pt << endl;
//       }

//Calculate the Single Muon ID and Trigger Efficiency
      double IDandTrigSF =0;
      if(isMuonEvent){
        IDandTrigSF = getSingleMuEffSF(leptonEta);
        // cout << "Scale Factor: " << IDandTrigSF << endl;
        wgt *= IDandTrigSF;
      }
           
      *(floatBranches["leptonPt"]) = leptonPt ;
      // *(floatBranches["leptonPtTruth"]) = muonTruthLV.Pt();
      *(floatBranches["leptonEta"]) = leptonEta ;
      // *(floatBranches["leptonEtaTruth"]) = muonTruthEta;
     //  if(isMuonEvent == true){
//            h_muPt->Fill(leptonPt,wgt);
//            histName = "h_muPt_";
//            histName += nJetsPlot;
//            histName += "j";
//            //           cout << "muPt Njet Hist Name: " << histName << " njets: " << numGoodJets
//            //   << " muPt: " << leptonPt << endl;
//         histograms[histName]->Fill(leptonPt,wgt);
//          h_muEta->Fill(leptonEta,wgt);
//         histName = "h_muEta_";
//         histName += nJetsPlot;
//         histName += "j";
//         histograms[histName]->Fill(leptonEta,wgt);
//       }
      //if(isEleEvent == true){h_elePt->Fill(leptonPt);}

      //------------------------
      int numJet = int(tight_pfjet_index.size());
      int numTag = int(tag_pfjet_index.size());
      int numNonTag = int(untag_pfjet_index.size());


//       bool oneTightLepton = (numTightMuons==1);
//       bool oneLooseLepton = (numLooseMuons==0);
//       bool oneTightSecondLepton = (numTightElectrons==0);
//       bool oneLooseSecondLepton = (numLooseElectrons==0);

      ///////

      //   cout << "numTightMuons: " <<  numTightMuons << " numTightEle: " << numTightElectrons
      //        << " numLooseMuons: " << numLooseMuons << " numLooseEle: "  << numLooseElectrons << endl;
      bool TightMuonLooseMuon = ((numTightMuons == 1) && (numLooseMuons==1));
      bool TightMuonLooseEle = ((numTightMuons == 1) && (numLooseElectrons==1));
      bool TightEleLooseMuon = ((numTightElectrons == 1) && (numLooseMuons==1));
      bool TightEleLooseEle = ((numTightElectrons == 1) && (numLooseElectrons==1));
      bool twoTightMuon = (numTightMuons == 2);
      bool oneEleOneMuon = ((numTightMuons ==1) && (numTightElectrons ==1));
      bool twoTightEle = (numTightElectrons ==2);


      bool oneTightMuon = ((numTightMuons ==1) && (numLooseMuons==0) && (numLooseElectrons==0));
      bool oneTightEle = ((numTightElectrons ==1) && (numLooseMuons==0) && (numLooseElectrons==0));
      
//       bool geOneTightMuon = (numTightMuons >=1);
//       bool geTwoJets = (numJet >=2 );
//       bool geThreeJets = (numJet >=3);
//       bool geTwoTags = (numTag >=2);
//       bool geThreeTags = (numTag >=3);

      //bool passTwoMuon = twoLeptons && ( twoTightMuon || TightMuonLooseMuon ) ;
      //bool passTwoEle = twoLeptons && ( twoTightEle || TightEleLooseEle ) ;
      //bool passMuonEle = twoLeptons && ( TightMuonLooseEle || TightEleLooseMuon || oneEleOneMuon );

      //*(intBranches["PassTwoLepton"]) =  twoLeptons ? 1 : 0;
      //*(intBranches["TwoMuon"]) = passTwoMuon ? 1 : 0;
      //*(intBranches["TwoEle"]) =  passTwoEle ? 1 : 0;
      //*(intBranches["MuonEle"]) = passMuonEle ? 1 : 0;

      *intBranches["ExactOneTightMu"] = oneTightMuon ? 1 : 0; 
      *intBranches["ExactOneTightEle"] = oneTightEle ? 1 : 0; 
        
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

      
      *(intBranches["isMuonEvent"]) = isMuonEvent;
      *(intBranches["isElectronEvent"]) = isEleEvent;


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
      double wgt_prob=0, wgt_prob_hfSFup=0, wgt_prob_hfSFdown=0, wgt_prob_lfSFup=0, wgt_prob_lfSFdown=0;                                  
      double wgt_prob_ge4=0, wgt_prob_ge4_hfSFup=0, wgt_prob_ge4_hfSFdown=0, wgt_prob_ge4_lfSFup=0, wgt_prob_ge4_lfSFdown=0;              

      if( (sample>=0 || sample==-2500) && !isData){
        std::vector<BTagWeight::JetInfo> myjetinfo;                                                                   
          std::vector<BTagWeight::JetInfo> myjetinfo_hfSFup;                                                            
          std::vector<BTagWeight::JetInfo> myjetinfo_hfSFdown;                                                          
          std::vector<BTagWeight::JetInfo> myjetinfo_lfSFup;                                                            
          std::vector<BTagWeight::JetInfo> myjetinfo_lfSFdown;

          if (verbose) std::cout << "Looping over  jets for btag uncert" <<std::endl;
          for( int j=0; j<int(good_jet_pt.size()); j++ ){
            if (verbose) std::cout << "calling btag sf" <<std::endl;
            if (verbose) std::cout << "one" <<std::endl;
            std::vector<double> myEffSF = getEffSF( 0, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j]);
            // vdouble myEffSF = BEANs::getEffSF( 0, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j],);
            if (verbose) std::cout << "return from getEffSF, try myjet" <<std::endl;
            BTagWeight::JetInfo myjet( myEffSF[0], myEffSF[1] );
            myjetinfo.push_back(myjet);
            if (verbose) std::cout << "two" <<std::endl;
            std::vector<double> myEffSF_hfSFup = getEffSF( 1, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j]);     
            BTagWeight::JetInfo myjet_hfSFup( myEffSF_hfSFup[0], myEffSF_hfSFup[1] );
            myjetinfo_hfSFup.push_back(myjet_hfSFup);                            
            if (verbose) std::cout << "three" <<std::endl;
            std::vector<double> myEffSF_hfSFdown = getEffSF( -1, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j]);                     
            BTagWeight::JetInfo myjet_hfSFdown( myEffSF_hfSFdown[0], myEffSF_hfSFdown[1] );                                                 
            myjetinfo_hfSFdown.push_back(myjet_hfSFdown);                                                                                   
            if (verbose) std::cout << "four" <<std::endl;
            std::vector<double> myEffSF_lfSFup = getEffSF( 2, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j]);                        
            BTagWeight::JetInfo myjet_lfSFup( myEffSF_lfSFup[0], myEffSF_lfSFup[1] );                                                       
            myjetinfo_lfSFup.push_back(myjet_lfSFup);                                                                                       
            if (verbose) std::cout << "five" <<std::endl;
            std::vector<double> myEffSF_lfSFdown = getEffSF( -2, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j]);                     
            BTagWeight::JetInfo myjet_lfSFdown( myEffSF_lfSFdown[0], myEffSF_lfSFdown[1] );                                                 
            myjetinfo_lfSFdown.push_back(myjet_lfSFdown);
            if (verbose) std::cout << "done calling sf calc " <<std::endl;
          }
          

          if (verbose) std::cout << "Now using btag weight" <<std::endl;

          
          BTagWeight bweight(1,1);                                                                                                          
          if( numTag<4 ){                                                         
            wgt_prob = bweight.weight(myjetinfo,numTag,numTag);                   
            wgt_prob_hfSFup   = bweight.weight(myjetinfo_hfSFup,numTag,numTag);   
            wgt_prob_hfSFdown = bweight.weight(myjetinfo_hfSFdown,numTag,numTag); 
            wgt_prob_lfSFup   = bweight.weight(myjetinfo_lfSFup,numTag,numTag);   
            wgt_prob_lfSFdown = bweight.weight(myjetinfo_lfSFdown,numTag,numTag); 
          }                                                                       
          else {                                                                  
            wgt_prob_ge4 = bweight.weight(myjetinfo,4,99);                        
            wgt_prob_ge4_hfSFup   = bweight.weight(myjetinfo_hfSFup,4,99);        
            wgt_prob_ge4_hfSFdown = bweight.weight(myjetinfo_hfSFdown,4,99);      
            wgt_prob_ge4_lfSFup   = bweight.weight(myjetinfo_lfSFup,4,99);        
            wgt_prob_ge4_lfSFdown = bweight.weight(myjetinfo_lfSFdown,4,99);      
          }
      }

    if (verbose) std::cout << "done with btag weight loop" <<std::endl;
    
        double wgt_btag = 1, wgt_btag_hfSFup = 1, wgt_btag_hfSFdown = 1, wgt_btag_lfSFup = 1, wgt_btag_lfSFdown = 1;                        
        if( (sample>=0 || sample==-2500) && !isData){                                                                                                                    
          if( numTag<4 ){                                                                                                                   
            wgt_btag = wgt_prob;                                                                                                        
            wgt_btag_hfSFup   = wgt_prob_hfSFup;                                                                                        
            wgt_btag_hfSFdown = wgt_prob_hfSFdown;                                                                                      
            wgt_btag_lfSFup   = wgt_prob_lfSFup;                                                                                        
            wgt_btag_lfSFdown = wgt_prob_lfSFdown;                                                                                      
          }   
          else {                                                                                                                            
            wgt_btag = wgt_prob_ge4;                                                                                                    
            wgt_btag_hfSFup   = wgt_prob_ge4_hfSFup;                                                                                    
            wgt_btag_hfSFdown = wgt_prob_ge4_hfSFdown;                                                                                  
            wgt_btag_lfSFup   = wgt_prob_ge4_lfSFup;                                                                                    
            wgt_btag_lfSFdown = wgt_prob_ge4_lfSFdown;                                                                                  
          }
        }

	//////
        *(floatBranches["prob"]) = wgt_btag;                                                                                         
        *(floatBranches["prob_hfSFdown"]) = wgt_btag_hfSFup;                                                                       
        *(floatBranches["prob_hfSFup"]) = wgt_btag_hfSFdown;                                                                           
        *(floatBranches["prob_lfSFdown"]) = wgt_btag_lfSFup;                                                                       
        *(floatBranches["prob_lfSFup"]) = wgt_btag_lfSFdown;                                                                           


       
      /////////////////////////////////
      ///////
      /////// final selection for neural net training:
      //////
      ////////////////////////////////

      //met

    double metx = pfmet->px;
    double mety = pfmet->py;
    double metpt = pfmet->pt;
    double metx_new = metx - totalDeltaPx;
    double mety_new = mety - totalDeltaPy;
    double metpt_new = sqrt(metx_new*metx_new + mety_new *mety_new);
    
    if (jerDebugPrint || verbose)
      cout << "---> MET " << endl
           << "     metx " << metx << endl
           << "     mety " << mety << endl
           << "     metpt " << metpt <<endl
           << "     totalDeltaPx " << totalDeltaPx << endl
           << "     totalDeltaPy " << totalDeltaPy << endl
           << "     metx_new " << metx_new  << endl
           << "     mety_new " << mety_new  << endl
           << "     metpt "    << metpt_new << endl;


   
      TLorentzVector metV(metx_new,mety_new,0.0,metpt_new);
      float met = metpt_new;
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
      // float min_jet_lep2_dR = 10000.;
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

 
      //    if ( twoLeptons ){  //////// number of jets and number of tags
	
	int iMuon1 = -10 ;
	int iMuon2 = -10 ;
	int iEle1 = -10 ;
	int iEle2 = -10 ;
	float lep1_pt = 0 ;
    //	float lep2_pt = 0 ;
	float lep1_et = 0 ;
	//float lep2_et = 0 ;
	float lep1_eta = 0 ;
	//float lep2_eta = 0 ;
	float lep1_phi = 0 ;
	//float lep2_phi = 0 ;
    if(oneTightMuon){
      iMuon1=tight_mu_index[0];
      lep1_pt = muons.at(iMuon1).pt;
      lep1_et = muons.at(iMuon1).et;
      lep1_eta = muons.at(iMuon1).eta;
      lep1_phi = muons.at(iMuon1).phi;
      lep_vect1.SetPxPyPzE(muons.at(iMuon1).px, muons.at(iMuon1).py, muons.at(iMuon1).pz, muons.at(iMuon1).energy);
      //lep_vect1.SetEta(lep1_eta);
    }
    if(oneTightEle){
      iEle1=tight_ele_index[0];
      lep1_pt = electrons.at(iEle1).pt;
      lep1_et = electrons.at(iEle1).et;
      lep1_eta = electrons.at(iEle1).eta;
      lep1_phi = electrons.at(iEle1).phi;
      lep_vect1.SetPxPyPzE(electrons.at(iEle1).px, electrons.at(iEle1).py, electrons.at(iEle1).pz, electrons.at(iEle1).energy);
      // lep_vect1.SetEta(lep1_eta);
    }

// 	  if( twoTightMuon || TightMuonLooseMuon ){
// 	    if( twoTightMuon ) {
// 	      iMuon1 = tight_mu_index[0] ;
// 	      iMuon2 = tight_mu_index[1] ;
// 	      if(muons.at(iMuon1).pt < muons.at(iMuon2).pt) {
// 		iMuon1 = tight_mu_index[1] ;
// 		iMuon2 = tight_mu_index[0] ;
// 	      }
// 	    }
	    
// 	    if( TightMuonLooseMuon ) {
// 	      iMuon1 = tight_mu_index[0] ;
// 	      iMuon2 = only_loose_mu_index[0] ;
// 	    }
	    
// 	    lep1_pt = muons.at(iMuon1).pt;
// 	    lep2_pt = muons.at(iMuon2).pt;
	    
// 	    lep1_et = muons.at(iMuon1).et;
// 	    lep2_et = muons.at(iMuon2).et;  

// 	    lep1_eta = muons.at(iMuon1).eta;
// 	    lep2_eta = muons.at(iMuon2).eta;  

// 	    lep1_phi = muons.at(iMuon1).phi;
// 	    lep2_phi = muons.at(iMuon2).phi;  

// 	    lep_vect1.SetPxPyPzE(muons.at(iMuon1).px, muons.at(iMuon1).py, muons.at(iMuon1).pz, muons.at(iMuon1).energy);
// 	    lep_vect2.SetPxPyPzE(muons.at(iMuon2).px, muons.at(iMuon2).py, muons.at(iMuon2).pz, muons.at(iMuon2).energy);
	  
// 	  }

	 //  if( twoTightEle || TightEleLooseEle ){
// 	    if( twoTightEle ){
// 	      iEle1 = tight_ele_index[0] ;
// 	      iEle2 = tight_ele_index[1] ;
// 	      if(electrons.at(iEle1).pt < electrons.at(iEle2).pt){
// 		iEle1 = tight_ele_index[1] ;
// 		iEle2 = tight_ele_index[0] ;
// 	      }
// 	    }

// 	    if( TightEleLooseEle ){
// 	      iEle1 = tight_ele_index[0] ;
// 	      iEle2 = only_loose_ele_index[0] ;
// 	    }
	  
// 	    lep1_pt = electrons.at(iEle1).pt;
// 	    lep2_pt = electrons.at(iEle2).pt;
	    
// 	    lep1_et = electrons.at(iEle1).et;
// 	    lep2_et = electrons.at(iEle2).et;  

// 	    lep1_eta = electrons.at(iEle1).eta;
// 	    lep2_eta = electrons.at(iEle2).eta;  

// 	    lep1_phi = electrons.at(iEle1).phi;
// 	    lep2_phi = electrons.at(iEle2).phi;  

// 	    lep_vect1.SetPxPyPzE(electrons.at(iEle1).px, electrons.at(iEle1).py, electrons.at(iEle1).pz, electrons.at(iEle1).energy);
// 	    lep_vect2.SetPxPyPzE(electrons.at(iEle2).px, electrons.at(iEle2).py, electrons.at(iEle2).pz, electrons.at(iEle2).energy);
	  
// 	  }
	  
// 	  int iMuon = -10 ;
// 	  int iEle = -10 ;
// 	  if( oneEleOneMuon || TightEleLooseMuon || TightMuonLooseEle){
// 	    if ( oneEleOneMuon ){
// 	      iMuon = tight_mu_index[0] ;
// 	      iEle = tight_ele_index[0] ;
// 	    }  
// 	    if ( TightEleLooseMuon ){
// 	      iMuon = only_loose_mu_index[0] ;
// 	      iEle = tight_ele_index[0] ;
// 	    }
// 	    if( TightMuonLooseEle ){
// 	      iMuon = tight_mu_index[0] ;
// 	      iEle = only_loose_ele_index[0] ;
// 	    }

// 	    lep1_pt = muons.at(iMuon).pt;
// 	    lep2_pt = electrons.at(iEle).pt;
	    
// 	    lep1_et = muons.at(iMuon).et;
// 	    lep2_et = electrons.at(iEle).et;  

// 	    lep1_eta = muons.at(iMuon).eta;
// 	    lep2_eta = electrons.at(iEle).eta;  

// 	    lep1_phi = muons.at(iMuon).phi;
// 	    lep2_phi = electrons.at(iEle).phi;  
	    
// 	    lep_vect1.SetPxPyPzE(muons.at(iMuon).px, muons.at(iMuon).py, muons.at(iMuon).pz, muons.at(iMuon).energy);
// 	    lep_vect2.SetPxPyPzE(electrons.at(iEle).px, electrons.at(iEle).py, electrons.at(iEle).pz, electrons.at(iEle).energy);
	  
// 	  }
   
      if (verbose) std::cout << "about to fill two lep vars " <<std::endl;
 
	 //  // two leptons
// 	  TLorentzVector two_lepton = lep_vect1 + lep_vect2;
// 	  float dilep_mass = two_lepton.M();
// 	  float dilep_pt = two_lepton.Pt();
// 	  float dPhi_dilep = lep_vect1.DeltaPhi(lep_vect2);
// 	  float dR_dilep = lep_vect1.DeltaR(lep_vect2);
     
// 	  *(floatBranches["mass_leplep"]) = dilep_mass;
// 	  *(floatBranches["pt_leplep"]) = dilep_pt;
// 	  *(floatBranches["dPhi_leplep"]) = dPhi_dilep;
// 	  *(floatBranches["dR_leplep"]) = dR_dilep;

	  *(floatBranches["lep1Pt"]) =  lep1_pt;
      // *(floatBranches["lep2Pt"]) =  lep2_pt;
	  *(floatBranches["lep1Eta"]) = lep1_eta;
      // *(floatBranches["lep2Eta"]) = lep2_eta;
	  *(floatBranches["lep1Phi"]) = lep1_phi;
	  //*(floatBranches["lep2Phi"]) = lep2_phi;

	  sum_pt += lep1_pt;
	  Ht += lep1_et ;
 
      // sum_pt += lep2_pt;
      // Ht += lep2_et ;
	  TLorentzVector leptonTrans = lep_vect1;
      leptonTrans.SetPz(0.);
      leptonTrans.SetE(lep_vect1.Pt());
      TLorentzVector WTrans = metV + leptonTrans;
    
      *(floatBranches["mT"]) = WTrans.M();
      *(floatBranches["mTTruth"]) = WTransTruthLV.Et();
      //  if(isMuonEvent == true){
//         h_muMt->Fill(WTrans.M(),wgt);
//         histName = "h_muMt_";
//         histName += nJetsPlot;
//         histName += "j";
//         histograms[histName]->Fill(WTrans.M(),wgt);
//       }

      TLorentzVector everything_vect = metV + lep_vect1 + sum_jet_vect; //Lept+Jets Mttbar
	  float ttbar_mass = everything_vect.M();
	  float ttbar_pt = everything_vect.Pt();
      float ttbar_eta = everything_vect.Eta();
      float ttbar_y = everything_vect.Rapidity();
	  *(floatBranches["Mttbar"]) = ttbar_mass;
      *(floatBranches["ttbarPt"]) = ttbar_pt;
      *(floatBranches["ttbarEta"]) = ttbar_eta;
      *(floatBranches["ttbarY"]) = ttbar_y;
      // if(isMuonEvent == true){
//         h_muMttbar->Fill(ttbar_mass,wgt);
//         h_muTTbarPt->Fill(ttbar_pt,wgt);
//         h_muTTbarEta->Fill(ttbar_eta,wgt);
//         h_muTTbarY->Fill(ttbar_y,wgt);
        
//         histName = "h_muMttbar_";
//         histName += nJetsPlot;
//         histName += "j";
//         histograms[histName]->Fill(ttbar_mass,wgt);
//         histName = "h_muTTbarPt_";
//         histName += nJetsPlot;
//         histName += "j";
//         histograms[histName]->Fill(ttbar_pt,wgt);
//         histName = "h_muTTbarEta_";
//         histName += nJetsPlot;
//         histName += "j";
//         histograms[histName]->Fill(ttbar_eta,wgt);
//         histName = "h_muTTbarY_";
//         histName += nJetsPlot;
//         histName += "j";
//         histograms[histName]->Fill(ttbar_y,wgt);
//       }
      //M3
      if(numGoodJets>=3){
        TLorentzVector top3Jets = jetV[0] +  jetV[1] +  jetV[2];
        *(floatBranches["m3"]) = top3Jets.M();
       //  h_muM3->Fill(top3Jets.M(),wgt);
//         histName = "h_muM3_";
//         histName += nJetsPlot;
//         histName += "j";
//         histograms[histName]->Fill(top3Jets.M(),wgt);
        
      }
     
      
	  ///loop jet
     //  h_nJets->Fill(nJetsPlot,wgt);
      for (int i=0; i < numGoodJets; i++){
              
	    int iJet = tight_pfjet_index[i];
    
	    sum_pt += jet_pt[iJet];
	    Ht += jet_energy[iJet];
       
	    jet_vect.SetPxPyPzE(jet_px[iJet],jet_py[iJet],jet_pz[iJet],jet_energy[iJet]);
            
	    if (i==0)  first_jet_pt = jet_pt[iJet];
        if (i==1)  second_jet_pt = jet_pt[iJet];
	    if (i==2)  third_jet_pt = jet_pt[iJet];
	    if (i==3)  fourth_jet_pt = jet_pt[iJet];
      
       //  TString histName = "h_jet";
//         histName += (i+1);
//         TString ptHistName = "h_jetPt";
             
         if((i+1)<=maxJetPlot){
           //histograms[histName + "Pt"]->Fill(jet_pt[iJet],wgt);
           //histograms[histName + "Eta"]->Fill(jet_eta[iJet],wgt);
       
         TString histName2 = histName + "Pt_"; histName2+= nJetsPlot; histName2 += "j";
         //histograms[histName2]->Fill(jet_pt[iJet],wgt);
         //histName2 = histName + "Eta_"; histName2+= nJetsPlot; histName2 += "j";
         // histograms[histName2]->Fill(jet_eta[iJet],wgt);
         }
             //  cout << "lep1 pt: " << lep_vect1.Pt() << " eta: " <<  lep_vect1.Eta() << endl;
// 	    if (min_jet_lep1_dR > lep_vect1.DeltaR(jet_vect)){
// 	      min_jet_lep1_dR = lep_vect1.DeltaR(jet_vect); 
// 	    }
	  
        //  if (min_jet_lep2_dR > lep_vect2.DeltaR(jet_vect)){
        // min_jet_lep2_dR = lep_vect2.DeltaR(jet_vect); 
        // }
	    
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
	  //float mindr_lep2_jet = min_jet_lep2_dR;
      //  *(floatBranches["mindr_lep1_jet"]) = mindr_lep1_jet;
	  //*(floatBranches["mindr_lep2_jet"]) = mindr_lep2_jet;
	 
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
 
	  //
	  all_sum_pt = sum_pt + met;
	  Ht += met;

//       h_nPV->Fill(numpv,wgt);
//       h_numTrueMCPV->Fill(numTruePV);
//       //      cout << "weight for event: "<< wgt << endl;
//       h_PUweight->Fill(PUwgt);
//       h_weight->Fill(wgt);
//       //  cout << "nPV: " << numpv << endl;
      
	  *(floatBranches["numPV"]) = numpv ;
	  *(floatBranches["weight"]) = wgt ;
      *(floatBranches["PUweight"]) = PUwgt;
	  *(floatBranches["weight_PUup"]) = PUwgt_up ;
	  *(floatBranches["weight_PUdown"]) = PUwgt_down ;
	  *(floatBranches["met"]) = met;
      *(floatBranches["metTruth"]) = neutrinoTruthLV.M();
	  *(floatBranches["unc_met"]) = unc_met;

	  *(floatBranches["sum_pt"]) = sum_pt; 
	  *(floatBranches["all_sum_pt"]) = all_sum_pt;
	  *(floatBranches["Ht"]) = Ht;

      //  if(isMuonEvent == true){
//           h_muMET->Fill(met,wgt);
//          histName = "h_muMET_";
//          histName += nJetsPlot;
//          histName += "j";
//          histograms[histName]->Fill(met,wgt);
//          h_muHt->Fill(Ht,wgt);
//          histName = "h_muHt_";
//          histName += nJetsPlot;
//          histName += "j";
//          histograms[histName]->Fill(Ht,wgt);
//        }

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
	    
	    min_dr_tagged_jets = min_tagged_jets_dR;
	  }
	  

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
    
	  ////	  	 
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
	  

      //  } // end neural net selection  //also end twoLeptons

      //--------------------

      if (verbose) std::cout << "about to fill tree" <<std::endl;
      // summaryTree.cd();
      summaryTree->Fill();
      // summaryTree->Write();
      // summaryTree->Close();
      //summaryTree.Fill();
      //summaryTree.Write();
      //summaryTree.Close();


//       if( cleanEvent ){
//         h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // cleaning 1
//         nevents_pass_cleaning++;
//         nevents_pass_cleaning_wgt += wgt;

//         if( triggerPass ){
//           h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // trigger 2
//           nevents_pass_trigger++;
//           nevents_pass_trigger_wgt += wgt;


//           //////////////////////////////////////////////////////////////////
//           //
//           //    Two tight muons selection
//           //
//           //////////////////////////////////////////////////////////////////
      
//           if( geOneTightMuon ){
//             h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 1 good muon 3

//             if( twoTightMuon ){
//               h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // exactly two tight muons 4

//               if( geTwoJets ){
//                 h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 jets 5 

//                 if( geTwoTags ){
//                   h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 tags 6

//                   if( geThreeJets ){
//                     h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 4 jets 7 

//                     if( geThreeTags ){
//                       h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 3 tags 8


//                     }
//                   }
//                 }
//               }
//             }
//           }// end >=1 tight muon

//           /////////////////////////////////////////////////////////////
//           //
//           //   1 mu, 1 ele
//           //
//           /////////////////////////////////////////////////////////////


//           // magic numbers ... skip to the start of the mu+ele selection

//           mcut = 9;
          
          
//           if( oneEleOneMuon  ){
//             h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // 1muo + 1ele 9 


//             if( geTwoJets ){
//               h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 jets 10 

//               if( geTwoTags ){
//                 h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 tags 11

//                 if( geThreeJets ){
//                   h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 4 jets 12

//                   if( geThreeTags ){
//                     h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 3 tags 13

//                   }
//                 }
//               }
//             }
            
//           }// end ==1 muon && ==1 electron

//           /////////////////////////////////////////////////////////////
//           //
//           //   2 ele
//           //
//           /////////////////////////////////////////////////////////////

//           // magic numbers... skip to start of 2 ele cuts

//           mcut = 14;

          
//           if( twoTightEle  ){
//             h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // == 2 ele 14


//             if( geTwoJets ){
//               h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 jets 15

//               if( geTwoTags ){
//                 h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 2 tags 16

//                 if( geThreeJets ){
//                   h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 4 jets 17

//                   if( geThreeTags ){
//                     h_cutflow_unwgt->Fill(0.5 + mcut); h_cutflow->Fill(0.5 + (mcut++),wgt);  // >= 3 tags 18

//                   }
//                 }
//               }
//             }
            
//           }// end == 2 tight Ele

          
          
//         }// end if trigger pass
//       } // end clean event

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

    std::cerr << " Whatever it was, it probably wasn't good, so I will crash" << std::endl;
    bool foundException = true;
    assert (foundException == false);
    //continue;
  }


  std::cout << "\n\nDone with loop over events\n\n" << std::endl;
  



//   std::cout << " *********************************************************** " << std::endl;
//   std::cout << "   Number of Events Processed (wgt)     = " << nevents << " (" << nevents_wgt << ")" << std::endl;
//   std::cout << "   Number of Events Pass cleaning (wgt) = "   << nevents_pass_cleaning << " (" << nevents_pass_cleaning_wgt << ")" << std::endl;
//   std::cout << "   Number of Events Passed HLT (wgt)    = " << nevents_pass_trigger << " (" << nevents_pass_trigger_wgt << ")" << std::endl;
//   std::cout << " *********************************************************** " << std::endl;
//   std::cout << "   Number of MC events " << std::endl;
//   std::cout << std::setw(25) << " "
// 	    << std::setw(27) << "Selected"
// 	    << std::setw(27) << "N - 1"
// 	    << std::setw(27) << "Cumulative" << std::endl;
//   for( int j=0; j<numSelectors; j++ ){
//     std::cout << std::setw(25) << selector_name[j]
//               << std::setw(15) << selected[j][0]
//               << " [" << std::setw(12) << (selected[j][0]/nevents)*100.0 << "%], "
//               << std::setw(15) << selected[j][1]
//               << " [" << std::setw(12) << (selected[j][1]/nevents)*100.0 << "%], "
//               << std::setw(15) << selected[j][2]
//              << " [" << std::setw(12) << (selected[j][2]/nevents)*100.0 << "%] " << std::endl;
//   }
//   std::cout << " *********************************************************** " << std::endl;
//   std::cout << "   Weighted number of MC events " << std::endl;
//   std::cout << std::setw(25) << " "
// 	    << std::setw(27) << "Selected"
// 	    << std::setw(27) << "N - 1"
// 	    << std::setw(27) << "Cumulative" << std::endl;
//   for( int j=0; j<numSelectors; j++ ){
//     std::cout << std::setw(25) << selector_name[j]
//               << std::setw(15) << selected_wgt[j][0]
//               << " [" << std::setw(12) << (selected_wgt[j][0]/nevents_wgt)*100.0 << "%], "
//               << std::setw(15) << selected_wgt[j][1]
//               << " [" << std::setw(12) << (selected_wgt[j][1]/nevents_wgt)*100.0 << "%], "
//               << std::setw(15) << selected_wgt[j][2]
//              << " [" << std::setw(12) << (selected_wgt[j][2]/nevents_wgt)*100.0 << "%] " << std::endl;
//   }
//   std::cout << " *********************************************************** " << std::endl;

//   for( int i=0; i<numSelectors; i++ ){
//     for( int j=0; j<3; j++ ){
//       h_cutflow_expand->Fill(j+0.5,numSelectors-i-0.5,selected[i][j]);
//       h_cutflow_expand_wgt->Fill(j+0.5,numSelectors-i-0.5,selected_wgt[i][j]);
//     }
//   }

//   std::cout << "How many events had jets close to leptons? " << nEventsWhereJetRemoved << endl;
  histofile.cd();
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

double getSingleMuEffSF(double muEta){
  // cout << "get single muon efficiency for mu passing IsoMu24" << endl;
  double muonSF = 1;
  double muonTriggerSF;

  //muon ID and Trigger Eff from AN2012 218 v3
  //and are a function of eta for pt values of >26GeV Muon POG Tight Muons
  double muonIDSF= 0.999;

  double etaMin[12] = {-2.1, -1.6, -1.2, -0.6, -0.3, -0.2, 0.2, 0.3, 0.6, 0.9, 1.2, 1.6};
  double etaMax[12] = {-1.6, -1.2, -0.6, -0.3, -0.2, 0.2, 0.3, 0.6, 0.9, 1.2, 1.6, 2.1};

  double TrigSF[13] ={
    1.010,
    1.001,
    0.983,
    0.998,
    1.008,
    0.965,
    1.007,
    0.985,
    1.007,
    0.984,
    1.003,
    0.980,
    0.977};
    
  

  int use_bin=-1;                                                                                                                
  for( int e=0; e<12; e++ ){                                                                                                     
    if( muEta> etaMin[e] && muEta <etaMax[e] ){                                                                                            
      use_bin = e; break;                                                                                                        
    }                                                                                                                            
  }
  muonTriggerSF = TrigSF[use_bin];

  
  muonSF *= muonIDSF;
  muonSF *= muonTriggerSF;
   
  return muonSF;
}



/////////////////////
std::vector<double> getEffSF( int returnType, double jetPt, double jetEta, double jetId ){

  bool getEffVerbose = false;
  //cout << "GetEffSF function in LepJets.C" << endl;
    
  if (getEffVerbose) std::cout  << "getEffSF called with arguments:" << std::endl
                                << "   returnType = " << returnType << std::endl
                                << "   jetPt = " << jetPt << std::endl
                                << "   jetEta = " << jetEta << std::endl
                                << "   jetId = " << jetId << std::endl;

  
    
  double m_type = 0.;                                                                                                            
  if( returnType==-1 )      m_type = -1.;                                                                                        
  else if( returnType==1 )  m_type = 1.;                                                                                         
  else                      m_type = 0.;                                                                                         
                                                                                                                                 
  float ptmin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500};                                              
  float ptmax[] = {40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 670};                                              
                                                                                                                                 
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
                                                                                                                                 
  double pt  = jetPt;                                                                                                            
  double eta = jetEta;                                                                                                           
  int flavor = jetId;                                                                                                            
                                                                                                                                 
  double threshold = 670;                                                                                                        
  pt = ( pt>threshold ) ? threshold-0.0000001 : pt;                                                                              
                                                                                                                                 
  double absEta = fabs(eta);                                                                                                     
                                                                                                                                 
  int use_bin=-1;                                                                                                                
  for( int p=0; p<14; p++ ){                                                                                                     
    if( pt>ptmin[p] && pt<ptmax[p] ){                                                                                            
      use_bin = p; break;                                                                                                        
    }                                                                                                                            
  }
  if (getEffVerbose) std::cout  << "Use bin = " << use_bin << std::endl;
  
  if( use_bin<0 ) if (getEffVerbose) std::cout  << "   ERROR!! use_bin < 0 " << std::endl;                                                           


  double SFb = 0.6981*((1.+(0.414063*pt))/(1.+(0.300155*pt)));                                                                              
                                                                                                                                            
  double SFc = SFb;                                                                                                                         

  if (getEffVerbose) std::cout  << "Getting error" << use_bin << std::endl;
  SFb = SFb + m_type * SFb_error[use_bin];                                                                                                  
  SFc = SFc + m_type * 2* SFb_error[use_bin];                                                                                               

  if (getEffVerbose) std::cout  << "switch based on return type"  << std::endl;
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

  double SF=1;                                                                                                                              
                                                                                                                                            
  double tagEff=0;
  if (getEffVerbose) std::cout  << "Calling get bin content and find bin"  << std::endl;

  
  if( abs(flavor)==5 ){                                                                                                                     
    tagEff = h_jet_pt_eta_b_eff_->GetBinContent( h_jet_pt_eta_b_eff_->FindBin( pt, absEta ) );                                              
    SF = SFb;                                                                                                                               
  }                                                                                                                                         
  else if( abs(flavor)==4 ){                                                                                                                
    tagEff = h_jet_pt_eta_c_eff_->GetBinContent( h_jet_pt_eta_c_eff_->FindBin( pt, absEta ) );                                              
    SF = SFc;                                                                                                                               
  }                                                                                                                                         
  else if( abs(flavor)==1 || abs(flavor)==2 || abs(flavor)==3 || abs(flavor)==21 ){                                                         
    tagEff = h_jet_pt_eta_l_eff_->GetBinContent( h_jet_pt_eta_l_eff_->FindBin( pt, absEta ) );                                              
    SF = SFl;                                                                                                                               
  }                                                                                                                                         
  else {
    tagEff = h_jet_pt_eta_o_eff_->GetBinContent( h_jet_pt_eta_o_eff_->FindBin( pt, absEta ) );
    SF = SFl;
    
  }
 

  if (getEffVerbose) std::cout  << "    Done with get bin, creating return vector" << std::endl;
                                                                                                                                            
  std::vector<double> result;                                                                                                               
  result.clear();                                                                                                                           
  result.push_back(tagEff);                                                                                                                 
  result.push_back(SF);                                                                                                                     

  if (getEffVerbose) std::cout  << " returning " << std::endl;
  return result;
  
}



//       if( cnt==10 ) {
// 	for( TrigIter hltbit = hlt.begin(); hltbit != hlt.end(); ++hltbit ){
// 	  std::string hlt_name = hltbit->name;
// 	  if (getEffVerbose) std::cout  << "==>" << hlt_name << "\t\t ps is  " << hltbit->prescale << endl; 
// 	   for( int t=0; t<int(mc_hlt_trigger_collection.size()); t++ ){
// 	     if(hlt_name.find(mc_hlt_trigger_collection[t])!=std::string::npos) {
// 	       if (getEffVerbose) std::cout  << "--- we found " << hlt_name << " and ps is" << hltbit->prescale << endl;
// 	     }
// 	   }
// 	}
//       }
