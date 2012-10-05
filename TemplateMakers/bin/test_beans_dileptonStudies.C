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

//#include "LumiReweightingStandAlone.h"
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



// headers for python config processing

#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "NtupleMaker/BEANmaker/interface/BtagWeight.h"
#include "NtupleMaker/BEANmaker/interface/BEANsUtilities.h"

#include "AnglesUtil.h"
#include "PhysicsTools/Utilities/interface/LumiReweightingStandAlone.h"
// For MVA reprocessing
//#include "TMVAGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"



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

// double getJERfactor( int returnType, double jetAbsETA, double genjetPT, double recojetPT );

// std::vector<double> getEffSF( int returnType, double jetPts, double jetEtas, double jetIds );      

//TFile *f_tag_eff_ = new TFile("mc_btag_efficiency_v4_histo.root");
// TH2D* h_jet_pt_eta_b_eff_ ;
// TH2D* h_jet_pt_eta_c_eff_ ;
// TH2D* h_jet_pt_eta_l_eff_ ;
// TH2D* h_jet_pt_eta_o_eff_ ;
                                                                                   
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
   //// switch between 2011 and 2012
   std::string selectionYear_ = anaParams.getParameter<std::string>("selectionYear");

   //JES
   int jes = anaParams.getParameter<int> ("jes");
   int jer = anaParams.getParameter<int> ("jer");
   int btagCSVShape = anaParams.getParameter<int> ("btagCSVShape");
   std::string sampleName = anaParams.getParameter<string>("sampleName");
   TString tmpName = sampleName;
   std::cout <<"CONFIG: using jes = " << jes << " jer = " << jer << " btagShape = " << btagCSVShape << std::endl; 

   //  Btag file

//    edm::FileInPath btagFileName = anaParams.getParameter<edm::FileInPath> ("btagFile");
//    edm::FileInPath puFileName = anaParams.getParameter<edm::FileInPath> ("puFile");
   //edm::FileInPath annFileName = anaParams.getParameter<edm::FileInPath> ("annFile");
   
   
   bool debug_ = false;

//    std::cout << "CONFIG: using btagFile = " << btagFileName.fullPath() << std::endl;

//    TFile * btagFile = new TFile (btagFileName.fullPath().c_str());

   //// Ht re-weighting
   TFile *f_Ht_rwt = new TFile("sum_jet_pt_rwt.root");
   TH1F* h_rwt_lowPV = (TH1F*)f_Ht_rwt->Get("sum_jet_pt_ratio_PV0");
   TH1F* h_rwt_medPV = (TH1F*)f_Ht_rwt->Get("sum_jet_pt_ratio_PV1");
   TH1F* h_rwt_highPV = (TH1F*)f_Ht_rwt->Get("sum_jet_pt_ratio_PV2");
   
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


  // data detection
  //
  bool isData = false;
  std::string sysType = "MC";
  if (TString(sampleName).Contains("DoubleElectron")
      || TString(sampleName).Contains("DoubleMu")
      || TString(sampleName).Contains("MuEG") ) {

    std::cout << "CONFIG: DATA detected for sample " << sampleName << std::endl;

    isData = true;
    sysType = "data";

  }

  //Sample numbers may not match event->sample; used for setMCsample() only
  std::string dset = "SingleMu" ;
  int sampleNumber = 999999;
  if (selectionYear_ == "2011") {
    if (tmpName.Contains("zjets_part")) sampleNumber = 2300; 
    if (sampleName == "zjets_lowmass") sampleNumber = 2310; 
    if (sampleName == "wjets") sampleNumber = 2400; 
    if (sampleName == "ttbar" || tmpName.Contains("ttbar_part") || sampleName == "ttbar_bb" || sampleName == "ttbar_cc") sampleNumber = 2500; 
    if (tmpName.Contains("scaleup_ttbar")) sampleNumber = 2510; 
    if (tmpName.Contains("scaledown_ttbar")) sampleNumber = 2511; 
    if (sampleName == "ttbarZ") sampleNumber = 2523; 
    if (sampleName == "ttbarW") sampleNumber = 2524; 
    if (tmpName.Contains("singlet")) sampleNumber = 2600; 
    if (sampleName == "ww") sampleNumber = 2700; 
    if (sampleName == "wz") sampleNumber = 2701; 
    if (sampleName == "zz") sampleNumber = 2702; 
    if (sampleName.find("ttH")!=std::string::npos) sampleNumber = 120;
  }
  else if (selectionYear_ == "2012") {
    if (tmpName.Contains("zjets_part")) sampleNumber = 2800; 
    if (sampleName == "zjets_lowmass") sampleNumber = 2850; 
    if (sampleName == "wjets") sampleNumber = 2400; 
    if (sampleName == "ttbar" || tmpName.Contains("ttbar_part") || sampleName == "ttbar_bb" || sampleName == "ttbar_cc") sampleNumber = 2500;  //// 12 parts???
    //if (sampleName == "ttbar_scaleup") sampleNumber = ; 
    //if (sampleName == "ttbar_scaledown") sampleNumber = ; 
    if (sampleName == "ttbarZ") sampleNumber = 2523; 
    if (sampleName == "ttbarW") sampleNumber = 2524; 
    if (sampleName == "singlet_s") sampleNumber = 2600; 
    if (sampleName == "singlet_t") sampleNumber = 2602; 
    if (sampleName == "singlet_tW") sampleNumber = 2504; 
    if (sampleName == "singletbar_s") sampleNumber = 2501; 
    if (sampleName == "singletbar_t") sampleNumber = 2503; 
    if (sampleName == "singletbar_tW") sampleNumber = 2505; 
    if (sampleName == "ww") sampleNumber = 2700; 
    if (sampleName == "wz") sampleNumber = 2701; 
    if (sampleName == "zz") sampleNumber = 2702;
//     if ((sampleName.find("ttH")!=std::string::npos) && (sampleName.find("FullSim")!=std::string::npos)) sampleNumber = 8120;
//     if ((sampleName.find("ttH")!=std::string::npos) && (sampleName.find("FastSim")!=std::string::npos)) sampleNumber = 9120;
    if (sampleName.find("ttH")!=std::string::npos) sampleNumber = 9120;
  }

  bool is8TeV = selectionYear_.find("2012")!=std::string::npos; 

  if (!isData)  {
    cout << "Calling setMCsample with arguments: sampleNumber = " << sampleNumber
         << ", is8TeV = " << is8TeV << ", dset = " << dset << endl;

    // bool argument isLJ is always false
    BEANs::setMCsample(sampleNumber,is8TeV, false, dset);
  } else {
    cout << "Calling setMCsample with sampleNumber = 2500, is8TeV = " << is8TeV
         << " and dset = " << dset << endl;
    // bool argument isLJ is always false
    BEANs::setMCsample(2500,is8TeV, false, dset);
  }
  



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
//   std::string histname = sampleName ;  
//   if( TString(sampleName).Contains("zjets"))      histname = "zjets";   // zjets_h,  zjets_lowmas  
//   else if( TString(sampleName).Contains("ttbar") && !(sampleName=="ttbarW" || sampleName=="ttbarZ") ) histname = "ttbar";  // ttbar, ttbar_bb, ttbar_cc   
//   else if( TString(sampleName).Contains("singlet") ) histname = "singlet";  // singlet_, singletbar_, 
//   else if( TString(sampleName).Contains("ttH") ) histname = "ttH120";  
  
//   // Initialize these global variables once, and then refer to then in a function below 
//   h_jet_pt_eta_b_eff_ = (TH2D*)btagFile->Get(std::string( histname + "_h_jet_pt_eta_b_eff" ).c_str());
//   h_jet_pt_eta_c_eff_ = (TH2D*)btagFile->Get(std::string( histname + "_h_jet_pt_eta_c_eff" ).c_str());
//   h_jet_pt_eta_l_eff_ = (TH2D*)btagFile->Get(std::string( histname + "_h_jet_pt_eta_l_eff" ).c_str());
//   // this histogram does not exist
//   h_jet_pt_eta_o_eff_ = (TH2D*)btagFile->Get(std::string( histname + "_h_jet_pt_eta_o_eff" ).c_str());





  // ================= TMVA STUFF  =====================

  // One NN for each category (just tag categories for now)
  // One NN for each category
  // 
  
  std::vector< TString >catList ;
  catList.push_back("ge3t");
  catList.push_back("e2je2t");   /////
  catList.push_back("e3je2t");   /////
  catList.push_back("ge4je2t");   /////
  catList.push_back("var_best8");
  catList.push_back("ge3t_new");
  const unsigned int nCat = catList.size();

  //Float_t fCFMlpANN[nCat];
  //TBranch* branchCFMlpANN[nCat] ;
  
  
  Float_t                 varfirst_jet_pt;
  Float_t                 varmin_dr_tagged_jets; 
  Float_t                 varnumJets_float; 
  Float_t                 varmindr_lep1_jet;
  Float_t                 varavg_btag_disc_btags;
  Float_t                 varHt;

  Float_t                 varavg_dr_tagged_jets;
  Float_t                 varavg_tagged_dijet_mass;
  Float_t                 varsecond_dibjet_mass;

  Float_t                 varmin_dr_jets; 
  Float_t                 varavg_dr_jets;
  Float_t                 varavg_dijet_mass;
  Float_t                 vardijet_mass_second;

  Float_t                 varCFMlpANN_var_best8;

  vector<TMVA::Reader *> reader;

  for( unsigned int j = 0 ; j < nCat ; ++j ){
      TString label = catList[j];
      reader.push_back( new TMVA::Reader( "!Color:!Silent" ));    
      if(j < 4) {
	reader[j]->AddVariable( "first_jet_pt",         &varfirst_jet_pt   );
	reader[j]->AddVariable( "min_dr_tagged_jets",         &varmin_dr_tagged_jets   ); 
	if (j==0)   reader[j]->AddVariable( "numJets_float",         &varnumJets_float   ); ///
	reader[j]->AddVariable( "mindr_lep1_jet",         &varmindr_lep1_jet   );
	reader[j]->AddVariable( "avg_btag_disc_btags",         &varavg_btag_disc_btags   );
	reader[j]->AddVariable( "Ht",         &varHt   );
      }
      else if (j==4){
	reader[j]->AddVariable( "min_dr_tagged_jets",         &varmin_dr_tagged_jets   ); 
	reader[j]->AddVariable( "avg_dr_tagged_jets",         &varavg_dr_tagged_jets   ); ///
	reader[j]->AddVariable( "avg_tagged_dijet_mass",         &varavg_tagged_dijet_mass   ); ///
	reader[j]->AddVariable( "second_dibjet_mass",         &varsecond_dibjet_mass   ); ///

	reader[j]->AddVariable( "min_dr_jets",         &varmin_dr_jets   ); 
	reader[j]->AddVariable( "avg_dr_jets",         &varavg_dr_jets   ); ///
	reader[j]->AddVariable( "avg_dijet_mass",         &varavg_dijet_mass   ); ///
	reader[j]->AddVariable( "dijet_mass_second",         &vardijet_mass_second   ); ///
      }
      else {
	reader[j]->AddVariable( "first_jet_pt",         &varfirst_jet_pt   );
	reader[j]->AddVariable( "min_dr_tagged_jets",         &varmin_dr_tagged_jets   ); 
	reader[j]->AddVariable( "numJets_float",         &varnumJets_float   ); ///
	reader[j]->AddVariable( "mindr_lep1_jet",         &varmindr_lep1_jet   );
	reader[j]->AddVariable( "avg_btag_disc_btags",         &varavg_btag_disc_btags   );
	reader[j]->AddVariable( "CFMlpANN_var_best8",         &varCFMlpANN_var_best8   );
	reader[j]->AddVariable( "Ht",         &varHt   );
      }

      TString dir    = "../../simpleweights/" + label + "/";
      TString prefix = "TMVAClassification";
      TString wfName = dir + prefix + TString("_CFMlpANN.weights.xml");

      std::cout << "Loading  weight file  " << wfName << std::endl; 
      
      
      // Book method(s)
      reader[j]->BookMVA( "CFMlpANN method", wfName);  
      

  }// end for each category 

  
  // Print out your config

  std::cout << "Using btag threshold " << btagThres << std::endl;

  
  // Creates a ChainEvent, allowing files to be linked   
  fwlite::ChainEvent ev(fileNames);   

  TFile histofile(outputFileName.c_str(),"recreate");

  histofile.cd();


  //////////////////////////////////////////////////////////////////////////
  ///  Booking Histograms
  //////////////////////////////////////////////////////////////////////////


  // Variables used for histogram ranges and binning
  // double metmax   = 500.;
  //double muptmax  = 350.;
  //double jetptmax = 500.;
  //double massmax  = 200.;

  //int NmetBins   = int( metmax/10. + 0.0001 );
  //int NmuptBins  = int( muptmax/10. + 0.0001 );
  //int NjetptBins = int( jetptmax/10. + 0.0001 );
  //int NmassBins  = int( massmax/1. + 0.0001 );


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

  //TH1D* h_met_pt = new TH1D("h_met_pt",";MET p_{T}", NmetBins, 0, metmax );
  //TH1D* h_met_phi = new TH1D("h_met_phi",";MET #phi", 16, -3.2, 3.2 );
  //TH1D* h_met_Upt = new TH1D("h_met_Upt",";MET raw p_{T}", NmetBins, 0, metmax );
  //TH1D* h_met_Uphi = new TH1D("h_met_Uphi",";MET raw #phi", 16, -3.2, 3.2 );

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
  intBranches["PassTwoLepton"] = new int (0);
  intBranches["TwoMuon"] = new int (0);
  intBranches["TwoEle"] = new int (0);
  intBranches["MuonEle"] = new int (0);

//   intBranches["numAllJets"] = new int(0);
//   intBranches["numBadJets"] = new int(0);
  intBranches["numJets"] = new int (0);
  intBranches["numTaggedJets"] = new int (0);
//   intBranches["numNonTaggedJets"] = new int (0);
  //intBranches["numHiggsJets"] = new int (0);
  //intBranches["numHiggsAllJets"] = new int (0);

  intBranches["numTightMuons"] = new int (0);
  intBranches["numLooseMuons"] = new int (0);
  intBranches["numTightElectrons"] = new int (0);
  intBranches["numLooseElectrons"] = new int (0);

  intBranches["isCleanEvent"] = new int (0);
  intBranches["isTriggerPass"] = new int (0);
//   intBranches["isTriggerPassPrescaled"] = new int (0);
  intBranches["isDoubleMuTriggerPass"] = new int (0);
  intBranches["isDoubleElectronTriggerPass"] = new int (0);
  intBranches["isMuEGTriggerPass"] = new int (0);
  intBranches["isMETTriggerPass"] = new int (0);
//   intBranches["isDoubleMuTriggerPS0"] = new int (0);
//   intBranches["isDoubleElectronTriggerPS0"] = new int (0);
//   intBranches["isMuEGTriggerPS0"] = new int (0);
//   intBranches["isMETTriggerPS0"] = new int (0);
  intBranches["isDoubleMu7Pass"] = new int (0);
  intBranches["isMu8Pass"] = new int (0);
  intBranches["isMu13_Mu8Pass"] = new int (0);
  intBranches["isMu17_Mu8Pass"] = new int (0);
  intBranches["isMu17_TkMu8Pass"] = new int (0);
  intBranches["isMu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVLPass"] = new int (0);
  intBranches["isMu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVLPass"] = new int (0);
  intBranches["isEle17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVLPass"] = new int (0);
  intBranches["isMu22_Photon22_CaloIdLPass"] = new int (0);
  intBranches["isMu30_Ele30_CaloIdLPass"] = new int (0);
  intBranches["isEle8_CaloIdL_CaloIsoVLPass"] = new int (0);
  intBranches["isDiCentralPFJet30_PFMET80_BTagCSV07Pass"] = new int(0);
  intBranches["isDiCentralPFJet50_PFMET80Pass"] = new int(0);
  intBranches["isMET120_HBHENoiseCleanedPass"] = new int(0);
  intBranches["isMET200Pass"] = new int(0);
  intBranches["isPFMET150Pass"] = new int(0);

  intBranches["HiggsDecayMode"] = new int(0); //CC=4,BB=5,TT=6,GG=21,ZZ=23,WW=24
//   intBranches["lep1Mother"] = new int(0);
//   intBranches["lep2Mother"] = new int(0);
//   intBranches["lep1Grandmother"] = new int(0);
//   intBranches["lep2Grandmother"] = new int(0);
  intBranches["PassZmask"] = new int (0);
  intBranches["PassZmask2"] = new int (0);
  intBranches["PassZmask3"] = new int (0);
  intBranches["oppositeLepCharge"] = new int (0);
  intBranches["oppositeGenLepCharge"] = new int (0);
  
  std::map<TString, unsigned int *> uintBranches;

  uintBranches["runNumber"] = new unsigned int (0);
  uintBranches["eventNumber"] = new unsigned int (0);
  uintBranches["luminosityBlock"] = new unsigned int (0);

  ////Robin ///------------variables--------------------
  std::map<TString, float *> floatBranches;
  /// MVA output var
  floatBranches["CFMlpANN_ge3t"] = new float(0.0);
  floatBranches["CFMlpANN_e2je2t"] = new float(0.0);
  floatBranches["CFMlpANN_e3je2t"] = new float(0.0);
  floatBranches["CFMlpANN_ge4je2t"] = new float(0.0);
  floatBranches["CFMlpANN_var_best8"] = new float(0.0);
  floatBranches["CFMlpANN_ge3t_new"] = new float(0.0);
  //Generator kinematics
  //floatBranches["higgs_pt"] = new float(0.0);
  //floatBranches["higgs_pz"] = new float(0.0);
  //floatBranches["top1_pt"] = new float(0.0);
  //floatBranches["top1_pz"] = new float(0.0);
  
  //b-tag reweight                                                                                                               
  floatBranches["prob"] = new float(0.0);                                                                                        
  floatBranches["prob_hfSFup"] = new float(0.0);                                                                                 
  floatBranches["prob_hfSFdown"] = new float(0.0);                                                                               
  floatBranches["prob_lfSFup"] = new float(0.0);                                                                                 
  floatBranches["prob_lfSFdown"] = new float(0.0);                                                                               

  //pile up
  floatBranches["numPV"] = new float(0.0);
  floatBranches["weight"] = new float(0.0);
  floatBranches["weight_PUup"] = new float(0.0);
  floatBranches["weight_PUdown"] = new float(0.0);

  //met
  floatBranches["met"] = new float(0.0);
  floatBranches["unc_met"] = new float(0.0);

  ///lepton variables
//   floatBranches["fstMuPt"] = new float(0.0);
//   floatBranches["sndMuPt"] = new float(0.0);
//   floatBranches["fstElePt"] = new float(0.0);
//   floatBranches["sndElePt"] = new float(0.0);
  floatBranches["lep1Pt"] = new float(0.0);
  floatBranches["lep2Pt"] = new float(0.0);
  floatBranches["lep1Eta"] = new float(0.0);
  floatBranches["lep2Eta"] = new float(0.0);
  floatBranches["lep1Phi"] = new float(0.0);
  floatBranches["lep2Phi"] = new float(0.0);
  floatBranches["lep1Iso"] = new float(0.0);
  floatBranches["lep2Iso"] = new float(0.0);

  floatBranches["mass_leplep"] = new float(0.0);
  floatBranches["pt_leplep"] = new float(0.0);
  floatBranches["dPhi_leplep"] = new float(0.0);
  floatBranches["dEta_leplep"] = new float(0.0);
  floatBranches["dR_leplep"] = new float(0.0);
  floatBranches["correctedDZ_leplep"] = new float(0.0);
  floatBranches["correctedD0_leplep"] = new float(0.0);
  floatBranches["tkDZ_leplep"] = new float(0.0);
  floatBranches["lep1TkCharge"] = new float (0.0);
  floatBranches["lep1GenCharge"] = new float (0.0);
  floatBranches["lep2TkCharge"] = new float (0.0);
  floatBranches["lep2GenCharge"] = new float (0.0);
  intBranches["lep1GenMotherId"] = new int (0);
  intBranches["lep2GenMotherId"] = new int (0);
  floatBranches["lep1SF"] = new float (0.0);
  floatBranches["lep2SF"] = new float (0.0);
  floatBranches["lepTotalSF"] = new float (0.0);
//   intBranches["lep2IsGlobalMuon"] = new int (0);
//   intBranches["lep2IsTrackerMuon"] = new int (0);  
//   intBranches["lep2IsGlobalMuonPromptTight"] = new int (0);  
//   intBranches["lep2NumTrackHits"] = new int (0);  
//   intBranches["lep2NumPixelHits"] = new int (0);  
//   intBranches["lep2NumberOfMatches"] = new int (0);  
//   floatBranches["lep2Chi2"] = new float (0.0);
//   intBranches["lep2NumExpectedHits"] = new int (0);
  
  /// jet variables
  floatBranches["numJets_float"] = new float (0);
  floatBranches["numTaggedJets_float"] = new float (0);

  floatBranches["first_jet_pt"] = new float(0.0);
  floatBranches["second_jet_pt"] = new float(0.0);
  floatBranches["third_jet_pt"] = new float(0.0);
  floatBranches["fourth_jet_pt"] = new float(0.0);

  floatBranches["first_jet_eta"] = new float(0.0);
  floatBranches["second_jet_eta"] = new float(0.0);
  floatBranches["third_jet_eta"] = new float(0.0);
  floatBranches["fourth_jet_eta"] = new float(0.0);

  floatBranches["first_jet_CHEF"] = new float(0.0);
  floatBranches["second_jet_CHEF"] = new float(0.0);
  floatBranches["third_jet_CHEF"] = new float(0.0);
  floatBranches["fourth_jet_CHEF"] = new float(0.0);
  floatBranches["sum_jet_CHEF"] = new float(0.0);

  floatBranches["first_jet_charge"] = new float(0.0);
  floatBranches["second_jet_charge"] = new float(0.0);
  floatBranches["third_jet_charge"] = new float(0.0);
  floatBranches["fourth_jet_charge"] = new float(0.0);
  floatBranches["sum_jet_charge"] = new float(0.0);

//   floatBranches["dPhi_jet1jet2"] = new float(0.0);
//   floatBranches["dPhi_jet1jet3"] = new float(0.0);
//   floatBranches["dPhi_jet1jet4"] = new float(0.0);
//   floatBranches["dPhi_jet2jet3"] = new float(0.0);
//   floatBranches["dPhi_jet2jet4"] = new float(0.0);
//   floatBranches["dPhi_jet3jet4"] = new float(0.0);

//   floatBranches["first_allJet_pt"] = new float(0.0);
//   floatBranches["second_allJet_pt"] = new float(0.0);
//   floatBranches["third_allJet_pt"] = new float(0.0);
//   floatBranches["fourth_allJet_pt"] = new float(0.0);
  
  //floatBranches["higgs_dijet_mass"] = new float(0.0);
  floatBranches["higgsLike_dijet_mass"] = new float(0.0);
//   floatBranches["wLike_dijet_mass"] = new float(0.0);
//   floatBranches["topLike_trijet_mass"] = new float(0.0);
//   floatBranches["higgsLike_allDijet_mass"] = new float(0.0);
//   floatBranches["wLike_allDijet_mass"] = new float(0.0);
//   floatBranches["topLike_allTrijet_mass"] = new float(0.0);
  //floatBranches["higgs_genJet_mass"] = new float(0.0);
  //floatBranches["higgs_genParton_mass"] = new float(0.0);
  floatBranches["min_dr_tagged_jets"] = new float(0.0);
  floatBranches["avg_dr_tagged_jets"] = new float(0.0);
  floatBranches["mindr_lep1_jet"] = new float(0.0);
  floatBranches["mindr_lep2_jet"] = new float(0.0);
//   floatBranches["mindr_lep1_allJet"] = new float(0.0);
//   floatBranches["mindr_lep2_allJet"] = new float(0.0);
  floatBranches["avg_tagged_dijet_mass"] = new float(0.0);
  floatBranches["avg_untagged_dijet_mass"] = new float(0.0);
  floatBranches["closest_tagged_dijet_mass"] = new float(0.0);
  floatBranches["M2_of_closest_tagged_jets"] = new float(0.0);
  ////// ttbb bkg
  floatBranches["min_dr_jets"] = new float(0.0);
  floatBranches["avg_dr_jets"] = new float(0.0);
  floatBranches["avg_dijet_mass"] = new float(0.0);
  floatBranches["closest_dijet_mass"] = new float(0.0);
  floatBranches["M2_of_closest_jets"] = new float(0.0);

  floatBranches["m2H_btag"] = new float(0.0);
  floatBranches["first_dibjet_mass"] = new float(0.0);
  floatBranches["second_dibjet_mass"] = new float(0.0);
  floatBranches["third_dibjet_mass"] = new float(0.0);

  floatBranches["dijet_mass_m2H"] = new float(0.0);
  floatBranches["dijet_mass_first"] = new float(0.0);
  floatBranches["dijet_mass_second"] = new float(0.0);
  floatBranches["dijet_mass_third"] = new float(0.0);

  //floatBranches["min_dr_genB1_allJet"] = new float (0.0);
  //floatBranches["min_dr_genB2_allJet"] = new float (0.0);
  
  floatBranches["avg_btag_disc_btags"] = new float(0.0);
  floatBranches["avg_btag_disc_non_btags"] = new float(0.0);
  floatBranches["highest_btag_disc_non_btags"] = new float(0.0);
  floatBranches["dev_from_avg_disc_btags"] = new float(0.0);

  floatBranches["first_highest_btag"] = new float(0.0);
  floatBranches["second_highest_btag"] = new float(0.0);
  floatBranches["lowest_btag"] = new float(0.0);

  /////entire system variables
  floatBranches["mass_of_everything"] = new float(0.0);
  floatBranches["mass_MHT"] = new float(0.0);
//   floatBranches["mass_of_leps_and_allJets"] = new float(0.0);
  floatBranches["pt_of_everything"] = new float(0.0);
  floatBranches["pt_of_ttbar"] = new float(0.0);
  floatBranches["MHT"] = new float(0.0);
  floatBranches["MT_met_lep1"] = new float(0.0);
  floatBranches["MT_met_lep2"] = new float(0.0);
  floatBranches["dPhi_met_lep1"] = new float(0.0);
  floatBranches["dPhi_met_lep2"] = new float(0.0);
//   floatBranches["pt_of_leps_and_allJets"] = new float(0.0);
  floatBranches["sum_jet_pt"] = new float(0.0);
//   floatBranches["pt_total"] = new float(0.0);
  floatBranches["sum_pt"] = new float(0.0); 
//   floatBranches["all_sum_pt"] = new float(0.0);
  floatBranches["Ht"] = new float(0.0);
  floatBranches["Q2ScaleUpWgt"] = new float(0.0);
  floatBranches["Q2ScaleDownWgt"] = new float(0.0);
  floatBranches["numTruePV"] = new float(0.0);
  floatBranches["numGenPV"] = new float(0.0);
  floatBranches["HtWgt"] = new float(0.0);
  floatBranches["HtWgtUp"] = new float(0.0);

  ////////////////////  
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


  ////// ============== trigger ===========
  vstring mc_hlt_DoubleMu_trigger_collection;
  vstring mc_hlt_DoubleElectron_trigger_collection;
  vstring mc_hlt_MuEG_trigger_collection;
  vstring mc_hlt_MET_trigger_collection;

  if( selectionYear_ == "2011"){
    mc_hlt_DoubleMu_trigger_collection.push_back("HLT_DoubleMu7_v");
    mc_hlt_DoubleMu_trigger_collection.push_back("HLT_Mu13_Mu8_v");
    mc_hlt_DoubleMu_trigger_collection.push_back("HLT_Mu17_Mu8_v");
    
    mc_hlt_DoubleElectron_trigger_collection.push_back("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v");
    mc_hlt_DoubleElectron_trigger_collection.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    mc_hlt_DoubleElectron_trigger_collection.push_back("HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v");
    
    mc_hlt_MuEG_trigger_collection.push_back("HLT_Mu17_Ele8_CaloIdL_v");
    mc_hlt_MuEG_trigger_collection.push_back("HLT_Mu8_Ele17_CaloIdL_v");
    mc_hlt_MuEG_trigger_collection.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v");
    mc_hlt_MuEG_trigger_collection.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v");
  }
  else {
    mc_hlt_DoubleMu_trigger_collection.push_back("HLT_Mu17_Mu8_v");
    mc_hlt_DoubleMu_trigger_collection.push_back("HLT_Mu17_TkMu8_v");
    mc_hlt_DoubleElectron_trigger_collection.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    mc_hlt_MuEG_trigger_collection.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    mc_hlt_MuEG_trigger_collection.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    mc_hlt_MET_trigger_collection.push_back("HLT_DiCentralPFJet30_PFMET80_BTagCSV07_v");
    mc_hlt_MET_trigger_collection.push_back("HLT_DiCentralPFJet50_PFMET80_v");
    mc_hlt_MET_trigger_collection.push_back("HLT_MET120_HBHENoiseCleaned_v");
    mc_hlt_MET_trigger_collection.push_back("HLT_MET200_v");
    mc_hlt_MET_trigger_collection.push_back("HLT_PFMET150_v");

  }

  ///
  double minNDOF = 4;
  double maxAbsZ = 24;
  double maxd0   = 2.;

  int nevents=0;
  //int nevents_pass_trigger=0;
  //int nevents_pass_cleaning=0;

  double nevents_wgt=0;
  //double nevents_pass_trigger_wgt=0;
  //double nevents_pass_cleaning_wgt=0;

  int nentries = ev.size();
  std::cout << "\n\t Number of entries = " << nentries << std::endl;
  std::cout << "\t Max number of entries = " << maxNentries << std::endl;
  std::cout << "\n" << std::endl;


  int cnt = 0;


  //int nEventsWhereJetRemoved = 0;

  bool verbose = false; //false;
  
  //
  // Loop over events
  //
  std::cout << "========  Starting Event Loop  ========" << std::endl;
  try {
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


      if (verbose) std::cout << "Getting collections... " <<std::endl;
      //std::cout << "========  Event! ========" << std::endl;
      // Get Handle for each collection used
      fwlite::Handle<BNeventCollection> h_event;
      h_event.getByLabel(ev,"BNproducer");
      BNeventCollection const &events = *h_event;

      fwlite::Handle<BNmuonCollection> h_muons;
      if ( selectionYear_ == "2011" ) h_muons.getByLabel(ev,"BNproducer","selectedPatMuonsLoosePFlow");
      else    h_muons.getByLabel(ev,"BNproducer","selectedPatMuonsPFlow");
      BNmuonCollection const &muons = *h_muons;

      fwlite::Handle<BNmetCollection> h_pfmet;
      if ( selectionYear_ == "2011" ) h_pfmet.getByLabel(ev,"BNproducer","patMETsTypeIPFlow");
      else h_pfmet.getByLabel(ev,"BNproducer","patMETsPFlow");
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
      if ( selectionYear_ == "2011" ) h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsLoosePFlow");
      else    h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsPFlow");
      BNelectronCollection const &electrons = *h_electrons;

      fwlite::Handle<BNmcparticleCollection> h_mcparticles;
      h_mcparticles.getByLabel(ev,"BNproducer","MCstatus3");
      BNmcparticleCollection const &mcparticles = *h_mcparticles;

      //fwlite::Handle<BNtrigobjCollection> h_hltobj;
      //h_hltobj.getByLabel(ev,"BNproducer","HLT");
      //BNtrigobjCollection const &hltobjs = *h_hltobj;

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

      int sample = event->sample;

      double numTruePV = event->numTruePV;
      double numGenPV = event->numGenPV;

      double Q2ScaleUpWgt = 1.0;
      double Q2ScaleDownWgt = 1.0; 

      //if (selectionYear_ == "2012") {
      if (sampleNumber == 2500) {
        Q2ScaleUpWgt = event->Q2ScaleUpWgt;
        Q2ScaleDownWgt = event->Q2ScaleDownWgt;
      }

      *(floatBranches["Q2ScaleUpWgt"]) = Q2ScaleUpWgt;
      *(floatBranches["Q2ScaleDownWgt"]) = Q2ScaleDownWgt;
      *(floatBranches["numTruePV"]) = numTruePV;
      *(floatBranches["numGenPV"]) = numGenPV;
      

      float wgt = 1 ;


      if(cnt<5)  std::cout << "CONFIG: Sample number from ntuple is: " << sample << std::endl;


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



      //============================================
      //
      // Filter out different kinds of ttbar events
      //
      //
      //===========================================
      /////////  need modification for ttbar scale samples 
      //      cout << "Sample type is = " <<sample <<endl;



      int HtoBB = 0;
      int HtoCC = 0;
      int HtoTT = 0;
      int HtoGG = 0;
      int HtoWW = 0;
      int HtoZZ = 0;
      int lep1Mother = 0;
      int lep2Mother = 0;
      int lep1Grandmother = 0;
      int lep2Grandmother = 0;
      
      float higgs_pt = 0.0;
      float higgs_pz = 0.0;
      float top1_pt = 0.0;
      float top1_pz = 0.0;

      vdouble muon_px;
      vdouble ele_px;
      vdouble muon_py;
      vdouble ele_py;
      vdouble muon_pz;
      vdouble ele_pz;
      vint muon_mother;
      vint ele_mother;
      vint muon_grandmother;
      vint ele_grandmother;
      
      TLorentzVector higgsGenBV[100];
        //std::cout << "Event: " << cnt << std::endl;
      for( unsigned i=0; i< mcparticles.size(); i++ ){
        int Aid = mcparticles.at(i).id;
        int AmotherID = mcparticles.at(i).motherId;
        int AgrandMotherID = mcparticles.at(i).grandMotherId;
        if ((Aid == 5 || Aid == -5) && AmotherID == 25) {
          if (HtoBB == 1) higgsGenBV[0].SetPtEtaPhiE(mcparticles.at(i).pt,mcparticles.at(i).eta,mcparticles.at(i).phi,mcparticles.at(i).energy);
          else higgsGenBV[1].SetPtEtaPhiE(mcparticles.at(i).pt,mcparticles.at(i).eta,mcparticles.at(i).phi,mcparticles.at(i).energy);
          HtoBB = 1;
        }
        if ((Aid == 4 || Aid == -4) && AmotherID == 25) HtoCC = 1;
        if ((Aid == 15 || Aid == -15) && AmotherID == 25) HtoTT = 1;
        if ((Aid == 21 || Aid == -21) && AmotherID == 25) HtoGG = 1;
        if ((Aid == 23 || Aid == -23) && AmotherID == 25) HtoZZ = 1;
        if ((Aid == 24 || Aid == -24) && AmotherID == 25) HtoWW = 1;

        if ((Aid == 11 || Aid == -11) && (AmotherID != 11 && AmotherID != -11 && AgrandMotherID != 11 && AgrandMotherID != -11)) {
          ele_px.push_back(mcparticles.at(i).px);
          ele_py.push_back(mcparticles.at(i).py);
          ele_pz.push_back(mcparticles.at(i).pz);
          ele_mother.push_back(AmotherID);
          ele_grandmother.push_back(AgrandMotherID);
        }
        if ((Aid == 13 || Aid == -13) && (AmotherID != 13 && AmotherID != -13 && AgrandMotherID != 13 && AgrandMotherID != -13)) {
          muon_px.push_back(mcparticles.at(i).px);
          muon_py.push_back(mcparticles.at(i).py);
          muon_pz.push_back(mcparticles.at(i).pz);
          muon_mother.push_back(AmotherID);
          muon_grandmother.push_back(AgrandMotherID);
        }

        if  (Aid == 25) {
          higgs_pt = mcparticles.at(i).pt;
          higgs_pz = mcparticles.at(i).pz;
        }
        if (Aid == 6 || Aid == -6) {
          top1_pt = mcparticles.at(i).pt;
          top1_pz = mcparticles.at(i).pz;
        }
        //std::cout << "Particle " << i << " is " << Aid << ", has mother " << AmotherID << " and grandmother " << AgrandMotherID << std::endl;
        if (debug_)
          std::cout <<"Print to remove warning messages: "
                    << HtoCC  << " "
                    << HtoTT << " "
                    << HtoGG << " "
                    << HtoWW << " "
                    << higgs_pt << " "
                    << higgs_pz << " "
                    << top1_pt << " "
                    << top1_pz << " "
                    << endl;
            

        
        }


      if (sample == 2510 || sample == 2511) {
	//        cout << "ERROR: incorrect sample number detected for scale up down samples "  << endl
	//             << "Resetting sample to 2500 "  <<endl;
	sample = 2500;
      }
      
      //      if (sample==2500) {
      if( tmpName.EndsWith("ttbar") || tmpName.Contains("ttbar_") ){   /////// 12 parts???       
        
        bool keepEvent = false;


        //bool debug_ = false;
        if (debug_) cout << "GENCUT: Sample is 2500" << endl;
   
        int ttbarType_ = 0;

        TString ttbarName = sampleName ;
        if( tmpName.EndsWith("ttbar") || tmpName.Contains("ttbar_part") ) ttbarType_ = 0;     /////// 12 parts??? 
        else if (ttbarName.EndsWith("ttbar_bb")) ttbarType_ = 1;
        else if (ttbarName.EndsWith("ttbar_cc")) ttbarType_ = 2;
        else {
          std::cout <<"ERROR: did not recognize ttbar sample type = " << sampleName
                    << std::endl
                    <<"Refusing to continue" << std::endl;
          assert(sampleName == "ttbar plus something");     
        }

        if (debug_) cout << "GENCUT: ttbarType_ is  " << ttbarType_ << endl;

        bool isWtoCS = false;

        if (debug_) cout << "Num MC particles = " << mcparticles.size() << std::endl
                         << "Num pfjets " <<  int(pfjets.size()) << std::endl
                         << "sample = " << sample;
   
        // check to see if the event has a c with a 
        // parent W
        for( unsigned i=0; i< mcparticles.size(); i++ ){
          int id = mcparticles.at(i).id;
          int motherID = mcparticles.at(i).motherId;
          int grandMotherID = mcparticles.at(i).grandMotherId;

          if (debug_) std::cout << "Particle " << i << " is " << id << ", has mother " << motherID << " and grandmother " << grandMotherID << std::endl;

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
        int numBmomHiggs=0;
        int numBbarmomBbar=0;
        int numBbarmomTbar=0;
        int numBbarmomHiggs=0;
        int numCmomC=0;
        int numCbarmomCbar=0;
        int numCmomHiggs=0;
        int numCbarmomHiggs=0;

        if (debug_) cout << "Starting loop over pf jet parton ids to see if you have a b" <<endl;

        for( int i=0; i<int(pfjets.size()); i++ ){


          
          int id = pfjets.at(i).genPartonId;
          if( id==-99 ) continue;
          int motherID = pfjets.at(i).genPartonMotherId;
          int mother0ID =  pfjets.at(i).genPartonMother0Id;
          int mother1ID =  pfjets.at(i).genPartonMother1Id;
          


          if (debug_) std::cout << "Jet index " << i << " is generator id " << id
                                << ", has mother " << motherID << ", mother0ID = " << mother0ID << ", mother1ID = " << mother1ID  << std::endl;
          
          // check to see if pf jets is from a  b/c and mother is a gluon
          // or, if mother is some light quark
          if( abs(id)==5 && ( motherID==21 || abs(motherID)<abs(id) ) ) gotB=true;
          if( abs(id)==4 && ( motherID==21 || abs(motherID)<abs(id) ) ) gotC=true;

          if (debug_) std::cout << "----------------> Got B = " << gotB << endl;
          // if things are their own mother, 
          // where are they from? Does this mean stable?
          if( id==5  && motherID==id ) numBmomB++;
          if( id==-5 && motherID==id ) numBbarmomBbar++;

          if( id==4  && motherID==id ) numCmomC++;
          if( id==-4 && motherID==id ) numCbarmomCbar++;

          if( id==5  && motherID==6  ) numBmomT++;
          if( id==-5 && motherID==-6 ) numBbarmomTbar++;

          if( id==5 && motherID==25 ) numBmomHiggs++;
          if( id==-5 && motherID==25 ) numBbarmomHiggs++;

          if( id==4 && motherID==25 ) numCmomHiggs++;
          if( id==-4 && motherID==25 ) numCbarmomHiggs++;
        }

        //std::cout << "b->b: " << numBmomB << " bbar->bbar: " << numBbarmomBbar << " t->b: " << numBmomT << " tbar->bbar: " << numBbarmomTbar << " H->b: " << numBmomHiggs << " H->bbar: " << numBbarmomHiggs << std::endl;
        //std::cout << "c->c: " << numCmomC << " cbar->cbar: " << numCbarmomCbar << " H->c: " << numCmomHiggs << " H->cbar: " << numCbarmomHiggs << std::endl;
        

        // if at least one b from b & one b from t, or if CC, and your jet was not b
        if( ((numBmomB>=1 && numBmomT>=1) || (numBbarmomBbar>=1 && numBbarmomTbar>=1)) && !gotB ){
          if (debug_) std::cout << "No sign of a b jet, but looping over jets again to check"
                                 <<std::endl;
          // for each jet that is  b from b
          for( int i=0; i<int(pfjets.size()); i++ ){
            cout << "LOOP: i = " << i << endl;
            int id0 = pfjets.at(i).genPartonId;
            int motherID0 = pfjets.at(i).genPartonMotherId;
            if( !(abs(id0)==5 && motherID0==id0) ) continue;

            if (debug_) std::cout << "Jet index " << i  << " is a bjet, let us see that it is not from top" <<std::endl;
            // for each jet that is b from t
            for( int j=0; j<int(pfjets.size()); j++ ){
              cout << "LOOP: j = " << j << endl;
              int id1 = pfjets.at(j).genPartonId;
              int motherID1 = pfjets.at(j).genPartonMotherId;
              if (debug_) std::cout << "LOOP: id0 = " << id0 << ", motherID0 = " << motherID0
                                    << ", id1 = " << id1 << ", motherID1 = " << motherID1 << endl
                                    << "continue? = " << !(id1==id0 && abs(motherID1)==6) << endl;
                
              if( !(id1==id0 && abs(motherID1)==6) ) continue;
              if (debug_) std::cout << "You didn't skip this event!" << endl;
              // if delta r between b from b and b from t is big enough, then b in final state is OK
              double dR = kinem::delta_R(pfjets.at(i).genPartonEta,
                                         pfjets.at(i).genPartonPhi,
                                         pfjets.at(j).genPartonEta,
                                         pfjets.at(j).genPartonPhi);
              if (debug_) std::cout << "dR = " << dR << endl;
              if (debug_) std::cout << "gotB = " << gotB << endl;
              if( dR>0.3 ){
                gotB = true;
                if (debug_) std::cout << "Found something with dR > 0.3... now gotB = " << gotB << endl;
                break;
              }
              if (debug_) std::cout << "SECOND: b not from top with dR = " << dR << " gotB = " << gotB << endl;
            }
            if( gotB ) break;
          }
        }

        if( (numCmomC>=1 || numCbarmomCbar>=1) && !isWtoCS ){
          gotC = true;
        }

        if( gotB ) isBBbarEvent = true;
        else if( gotC ) isCCbarEvent = true;


    
   
//         if( ttbarType_<0 || sample != 2500)       keepEvent = true;
//         else if( ttbarType_ ==0 && !isBBbarEvent && !isCCbarEvent ) keepEvent = true;
	if( ttbarType_ ==0 && !isBBbarEvent && !isCCbarEvent ) keepEvent = true;
        else if( ttbarType_ ==1 &&  isBBbarEvent && !isCCbarEvent ) keepEvent = true;
        else if( ttbarType_ >1  && !isBBbarEvent && isCCbarEvent  ) keepEvent = true;

        if (debug_) cout << "Filter result = " << keepEvent << endl
                         << "isBBbarEvent = " << isBBbarEvent << endl
                         << "isCCbarEvent = " << isCCbarEvent << endl
                         << "... will we skip this? " << (!keepEvent) << endl;
        
        // if you don't pass the filter, skip this event

        //if (debug_) cout << "Keep event no matter what" << endl;
        //keepEvent = true;


        TString wordsForType = "";
        if (ttbarType_ ==0 ) wordsForType = "ttbar";
        else if (ttbarType_ == 1) wordsForType = "ttbar_bb";
        else if (ttbarType_ >= 1) wordsForType = "ttbar_cc";

        bool externalKeepEvent = BEANs::ttPlusHeavyKeepEvent (mcparticles, pfjets, wordsForType, selectionYear_);

        if (debug_)
          std::cout << "externalKeepEvent = " << externalKeepEvent <<", localKeepEvent = " << keepEvent << std::endl;

        if ( keepEvent != externalKeepEvent)
          if (debug_) std::cout << "KEEPER CHECK: event filtering decisions did not match... this is ok for 2012" << std::endl;


        keepEvent = externalKeepEvent;
        
        if(!keepEvent) continue;
      }// end if you are a top sample

      //-------------------------------------
      //-------------------------------------

      if (verbose) std::cout << "met stuff " <<std::endl;
      
      MetIter pfmet = pfmets.begin();
      // MetIter calomet = calomets.begin();
      // MetIter tcmet = tcmets.begin();

      // Type I corrected MET
      //h_met_pt->Fill(pfmet->pt,wgt);
      //h_met_phi->Fill(pfmet->phi,wgt);
      // Uncorrected / raw MET
      //h_met_Upt->Fill(pfmet->Upt,wgt);
      //h_met_Uphi->Fill(pfmet->Uphi,wgt);

      
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
      // Pile-up reweighting  ////Robin
      double PUwgt = 1;
      double PUwgt_up = 1;
      double PUwgt_down = 1;

      //      if( (sample>=0 || sample==-2500) && !isData){
      if(!isData){
        if(selectionYear_ == "2011" && ((TString(sampleName).Contains("ttH")) || (sampleName=="ttbarW") || (sampleName=="ttbarZ")) ){
          BEANs::getPUwgt(numGenPV,PUwgt,PUwgt_up,PUwgt_down);
	}
        else {
          BEANs::getPUwgt(numTruePV,PUwgt,PUwgt_up,PUwgt_down);
        }
// 	if( (TString(sampleName).Contains("ttH")) || (sampleName=="ttbarW") || (sampleName=="ttbarZ") ){ 
//   //        if( (sample>=100 && sample<=140) || (sample==2523) || (sample==2524) ){
//           PUwgt      = h_pu_ratio->GetBinContent( h_pu_ratio->FindBin( numGenPV ) );
//           PUwgt_up   = h_pu_ratio_up->GetBinContent( h_pu_ratio_up->FindBin( numGenPV ) );
//           PUwgt_down = h_pu_ratio_down->GetBinContent( h_pu_ratio_down->FindBin( numGenPV ) );
//         }
//         else{
//           PUwgt      = h_pu_ratio->GetBinContent( h_pu_ratio->FindBin( numTruePV ) );
//           PUwgt_up   = h_pu_ratio_up->GetBinContent( h_pu_ratio_up->FindBin( numTruePV ) );
//           PUwgt_down = h_pu_ratio_down->GetBinContent( h_pu_ratio_down->FindBin( numTruePV ) );
//         }
      }
      wgt *= PUwgt;


      ///--------------------------------
      // Trigger Requirement
      bool triggerFound = false;
      bool DoubleMuTriggerFound = false;
      bool DoubleElectronTriggerFound = false;
      bool MuEGTriggerFound = false;
      bool METTriggerFound = false;
      bool triggerPass = false;
      bool triggerPassPrescaled = false;
      bool DoubleMuTriggerPass = false;
      bool DoubleElectronTriggerPass = false;
      bool MuEGTriggerPass = false;
      bool METTriggerPass = false;
      bool DoubleMuTriggerPS0 = false;
      bool DoubleElectronTriggerPS0 = false;
      bool MuEGTriggerPS0 = false;
      bool METTriggerPS0 = false;
      bool HLT_DoubleMu7_v = false;
      bool HLT_Mu8_v = false;
      bool HLT_Mu13_Mu8_v = false;
      bool HLT_Mu17_Mu8_v = false;
      bool HLT_Mu17_TkMu8_v = false;
      bool HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v = false;
      bool HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v = false;
      bool HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v = false;
      bool HLT_Ele8_CaloIdL_CaloIsoVL_v = false;
      bool HLT_Mu22_Photon22_CaloIdL_v = false;
      bool HLT_Mu30_Ele30_CaloIdL_v = false;
      bool HLT_DiCentralPFJet30_PFMET80_BTagCSV07_v = false;
      bool HLT_DiCentralPFJet50_PFMET80_v = false;
      bool HLT_MET120_HBHENoiseCleaned_v = false;
      bool HLT_MET200_v = false;
      bool HLT_PFMET150_v = false;
      if (verbose) std::cout << "about to do pu reweight " <<std::endl;
      //      if( sample>=0 ){
      std::string hlt_name = "holder";

	for( TrigIter hltbit = hlt.begin(); hltbit != hlt.end(); ++hltbit ){
      hlt_name = hltbit->name;
      if(hlt_name.find("HLT_Mu8_v")!=std::string::npos) HLT_Mu8_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_DoubleMu7_v")!=std::string::npos) HLT_DoubleMu7_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Mu13_Mu8_v")!=std::string::npos) HLT_Mu13_Mu8_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Mu17_Mu8_v")!=std::string::npos) HLT_Mu17_Mu8_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Mu17_TkMu8_v")!=std::string::npos) HLT_Mu17_TkMu8_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v")!=std::string::npos) HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v")!=std::string::npos) HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v")!=std::string::npos) HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Ele8_CaloIdL_CaloIsoVL_v")!=std::string::npos) HLT_Ele8_CaloIdL_CaloIsoVL_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Mu22_Photon22_CaloIdL_v")!=std::string::npos) HLT_Mu22_Photon22_CaloIdL_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_Mu30_Ele30_CaloIdL_v")!=std::string::npos) HLT_Mu30_Ele30_CaloIdL_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_DiCentralPFJet30_PFMET80_BTagCSV07_v")!=std::string::npos) HLT_DiCentralPFJet30_PFMET80_BTagCSV07_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_DiCentralPFJet50_PFMET80_v")!=std::string::npos) HLT_DiCentralPFJet50_PFMET80_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_MET120_HBHENoiseCleaned_v")!=std::string::npos) HLT_MET120_HBHENoiseCleaned_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_MET200_v")!=std::string::npos) HLT_MET200_v = ( hltbit->pass==1 );
      if(hlt_name.find("HLT_PFMET150_v")!=std::string::npos) HLT_PFMET150_v = ( hltbit->pass==1 );

      for( int t=0; t<int(mc_hlt_DoubleMu_trigger_collection.size()); t++ ){
        //hlt_name = hltbit->name;
	    if( (hlt_name.find(mc_hlt_DoubleMu_trigger_collection[t])!=std::string::npos) ) {
	      if( hltbit->prescale==1 || hltbit->prescale==0 ) {
            DoubleMuTriggerFound = true;
            DoubleMuTriggerPass = ( ( hltbit->pass==1 && hltbit->prescale==1 ) || DoubleMuTriggerPass);
            DoubleMuTriggerPS0 = ( ( hltbit->prescale==0 ) || DoubleMuTriggerPS0);
          }
          else triggerPassPrescaled = ( hltbit->pass==1 || triggerPassPrescaled);
        }
        if( DoubleMuTriggerPass ) break;
      }
      for( int t=0; t<int(mc_hlt_DoubleElectron_trigger_collection.size()); t++ ){
        //hlt_name = hltbit->name;
	    if( (hlt_name.find(mc_hlt_DoubleElectron_trigger_collection[t])!=std::string::npos) ) {
	      if( hltbit->prescale==1 || hltbit->prescale==0 ) {
            DoubleElectronTriggerFound = true;
            DoubleElectronTriggerPass = ( ( hltbit->pass==1 && hltbit->prescale==1 ) || DoubleElectronTriggerPass);
            DoubleElectronTriggerPS0 = ( ( hltbit->prescale==0 ) || DoubleElectronTriggerPS0);
          }
          else triggerPassPrescaled = ( hltbit->pass==1 || triggerPassPrescaled);
        }
        if( DoubleElectronTriggerPass ) break;
      }
      for( int t=0; t<int(mc_hlt_MuEG_trigger_collection.size()); t++ ){
        //hlt_name = hltbit->name;
	    if( (hlt_name.find(mc_hlt_MuEG_trigger_collection[t])!=std::string::npos) ) {
	      if( hltbit->prescale==1 || hltbit->prescale==0 ) {
            MuEGTriggerFound = true;
            MuEGTriggerPass = ( ( hltbit->pass==1 && hltbit->prescale==1 ) || MuEGTriggerPass);
            MuEGTriggerPS0 = ( ( hltbit->prescale==0 ) || MuEGTriggerPS0);
          }
          else triggerPassPrescaled = ( hltbit->pass==1 || triggerPassPrescaled);
        }
        if( MuEGTriggerPass ) break;
      }
      for( int t=0; t<int(mc_hlt_MET_trigger_collection.size()); t++ ){
        //hlt_name = hltbit->name;
	    if( (hlt_name.find(mc_hlt_MET_trigger_collection[t])!=std::string::npos) ) {
	      if( hltbit->prescale==1 || hltbit->prescale==0 ) {
            METTriggerFound = true;
            METTriggerPass = ( ( hltbit->pass==1 && hltbit->prescale==1 ) || METTriggerPass);
            METTriggerPS0 = ( ( hltbit->prescale==0 ) || METTriggerPS0);
          }
          else triggerPassPrescaled = ( hltbit->pass==1 || triggerPassPrescaled);
        }
        if( METTriggerPass ) break;
      }
      //if( triggerPass ) break;
    }
    if (DoubleMuTriggerPass || DoubleElectronTriggerPass || MuEGTriggerPass) triggerPass = true;
    if (DoubleMuTriggerFound || DoubleElectronTriggerFound || MuEGTriggerFound || METTriggerFound) triggerFound = true;


    if (debug_)
      cout << "More trigger printing to avoid warnings "
           << HLT_DoubleMu7_v << " " 
           << HLT_Mu8_v << " "
           << HLT_Mu13_Mu8_v << " "
           << HLT_Mu17_Mu8_v  << " "
           << HLT_Mu17_TkMu8_v << " "
           << HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v  << " "
           << HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v  << " "
           << HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v  << " "
           << HLT_Ele8_CaloIdL_CaloIsoVL_v  << " "
           << HLT_Mu22_Photon22_CaloIdL_v << " "
           << HLT_Mu30_Ele30_CaloIdL_v << " "
           << endl;
    
    
	//      }

      // Print triggers
      //triggerFound = false;
      /// make sure trigger used to tag exists in the event
    if( !triggerFound ){
      std::cout << "  error ===> Trigger not found!!!  Here are the available triggers: " << std::endl;
      for( TrigIter hltbit = hlt.begin(); hltbit != hlt.end(); ++hltbit ){
        hlt_name = hltbit->name;
        std::cout << "\t\t " << hlt_name << "\t\t prescale = " << hltbit->prescale << "\t\t pass = " << hltbit->pass << std::endl;
      }
//       break;
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
      cleanEvent = (isData) ?  cleanEvent : true;


      //////////split nGen
      if( sample==120 || sample==9120){                   ////// 2012 ???
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


	if( has2tWb ) h_nGen->Fill(0);
	if( has2tWb_Wqq_Wemu ) h_nGen->Fill(1);
	if( has2tWb_Wqq_Wemutau ) h_nGen->Fill(2);
	if( has2tWb_Wqq_Wemu_Hbb ) h_nGen->Fill(3);
	if( has2tWb_Wqq_Wemutau_Hbb ) h_nGen->Fill(4);
	if( has2tWb_2Wemu ) h_nGen->Fill(5);
	if( has2tWb_2Wemutau ) h_nGen->Fill(6);
	if( has2tWb_2Wemu_Hbb ) h_nGen->Fill(7);
	if( has2tWb_2Wemutau_Hbb ) h_nGen->Fill(8);
      }
      //////////

//      if( sample>=0 || sample==-2500){

// 	double binW0decay = -99;
// 	double binW1decay = -99;
// 	double binHdecay  = -99;

// 	// Get the decays product of the W
// 	int W0decay = event->W0decay;
// 	int W1decay = event->W1decay;

// 	// loop over status==3 mc particles
// 	std::vector<int> higgs_daughter_id;
// 	for( int i=0; i<int(mcparticles.size()); i++ ){
// 	  int id = mcparticles.at(i).id;
// 	  int motherID = mcparticles.at(i).motherId;
// 	  int motherAbsID = fabs(motherID);

// 	  if( motherAbsID==25 ) higgs_daughter_id.push_back(id);
// 	  if( abs(id)==25 ) h_H_mass->Fill(mcparticles.at(i).mass);
// 	}

// 	// Convert from decay to bin
// 	if( (W0decay==201 || W0decay==102) )      binW0decay=0.5;
// 	else if( (W0decay==203 || W0decay==302) ) binW0decay=1.5;
// 	else if( (W0decay==205 || W0decay==502) ) binW0decay=2.5;
// 	else if( (W0decay==401 || W0decay==104) ) binW0decay=3.5;
// 	else if( (W0decay==403 || W0decay==304) ) binW0decay=4.5;
// 	else if( (W0decay==405 || W0decay==504) ) binW0decay=5.5;
// 	else if( (W0decay==601 || W0decay==106) ) binW0decay=6.5;
// 	else if( (W0decay==603 || W0decay==306) ) binW0decay=7.5;
// 	else if( (W0decay==605 || W0decay==506) ) binW0decay=8.5;
// 	else if( (W0decay==1112 || W0decay==1211) ) binW0decay=9.5;
// 	else if( (W0decay==1314 || W0decay==1413) ) binW0decay=10.5;
// 	else if( (W0decay==1516 || W0decay==1615) ) binW0decay=11.5;
// 	else                                        binW0decay=12.5;

// 	if( (W1decay==201 || W1decay==102) )      binW1decay=0.5;
// 	else if( (W1decay==203 || W1decay==302) ) binW1decay=1.5;
// 	else if( (W1decay==205 || W1decay==502) ) binW1decay=2.5;
// 	else if( (W1decay==401 || W1decay==104) ) binW1decay=3.5;
// 	else if( (W1decay==403 || W1decay==304) ) binW1decay=4.5;
// 	else if( (W1decay==405 || W1decay==504) ) binW1decay=5.5;
// 	else if( (W1decay==601 || W1decay==106) ) binW1decay=6.5;
// 	else if( (W1decay==603 || W1decay==306) ) binW1decay=7.5;
// 	else if( (W1decay==605 || W1decay==506) ) binW1decay=8.5;
// 	else if( (W1decay==1112 || W1decay==1211) ) binW1decay=9.5;
// 	else if( (W1decay==1314 || W1decay==1413) ) binW1decay=10.5;
// 	else if( (W1decay==1516 || W1decay==1615) ) binW1decay=11.5;
// 	else                                        binW1decay=12.5;

// 	h_W0_decay_W1_decay->Fill(binW0decay,binW1decay,wgt);


// 	// Loop over Higgs daughters
// 	int d0 = -99, d1=-99;
// 	for( int d=0; d<int(higgs_daughter_id.size()); d++ ){
// 	  int id = higgs_daughter_id[d];
// 	  double absId = fabs(id);

// 	  if( d0==-99 ) d0 = absId;
// 	  else if( d1==-99 ) d1 = absId;
// 	}

// 	if( d0==5 && d1==5 )        binHdecay=0.5;
// 	else if( d0==24 && d1==24 ) binHdecay=1.5;
// 	else if( d0==15 && d1==15 ) binHdecay=2.5;
// 	else if( d0==21 && d1==21 ) binHdecay=3.5;
// 	else if( d0==22 && d1==22 ) binHdecay=4.5;
// 	else if( d0==23 && d1==23 ) binHdecay=5.5;
// 	else if( d0==4  && d1==4  ) binHdecay=6.5;
// 	else if( (d0==23 && d1==22) || (d1==23 && d0==22) ) binHdecay=7.5;
// 	else                        binHdecay=8.5;

// 	h_H_decay->Fill(binHdecay,wgt);
//     }


      if (verbose) std::cout << "about to do ele selection " <<std::endl;

      
      /////////
      ///
      /// Electrons
      ///
      ////////
      ////--------- using selectors in "BEANsUtilities.h"
      ////////////////////////////////
      std::vector<int> tight_ele_index;
      std::vector<int> loose_ele_index;
      std::vector<double> tightElectronSF;
      std::vector<double> looseElectronSF;
      std::vector<int> side_tight_ele_index;
      std::vector<int> side_loose_ele_index;
      std::vector<double> sideTightElectronSF;
      std::vector<double> sideLooseElectronSF;
      BEANs::electronSelector( electrons, false, sysType, selectionYear_, tight_ele_index, loose_ele_index, side_tight_ele_index, side_loose_ele_index, tightElectronSF, looseElectronSF, sideTightElectronSF, sideLooseElectronSF );

//       tight_ele_index = loose_ele_index;
//       side_tight_ele_index.insert(side_tight_ele_index.end(), side_loose_ele_index.begin(), side_loose_ele_index.end());
//       loose_ele_index = side_tight_ele_index;
//       tightElectronSF = looseElectronSF;
//       sideTightElectronSF.insert(sideTightElectronSF.end(), sideLooseElectronSF.begin(), sideLooseElectronSF.end());
//       looseElectronSF = sideTightElectronSF;

      int numTightElectrons = int(tight_ele_index.size());
      int numLooseElectrons = int(loose_ele_index.size());

      ////////////////////////////////
      ////--------- old frame work
      ////////////////////////////////
//       float fstElePt = 0.0 ;
//       float sndElePt = 0.0 ;

//       std::vector<int> tight_ele_index;
//       std::vector<int> loose_ele_index;
//       std::vector<int> only_loose_ele_index;
//       for( int i=0; i<int(electrons.size()); i++ ){

//         double eleSCEta = electrons.at(i).scEta;
//         double absSCeta = fabs(eleSCEta);
//         double eleEta = electrons.at(i).eta;
//         float elePt = electrons.at(i).pt;

// 	bool isCrack = ( (absSCeta>1.4442) && (absSCeta<1.5660) );

//       	bool kin = ( (elePt>10.) && !isCrack && fabs(eleEta)<2.5 );

//       	if( !kin ) continue;

// 	double chargedHadronIso = electrons.at(i).chargedHadronIso;
// 	double neutralHadronIso = electrons.at(i).neutralHadronIso;
// 	double photonIso = electrons.at(i).photonIso;

// 	double relIso = ( chargedHadronIso + neutralHadronIso + photonIso ) * 1./elePt;

//       	bool looseIso = ( relIso < 0.2 );

// 	if( !looseIso ) continue;

//       	loose_ele_index.push_back(i);

// 	int eidBitTight = electrons.at(i).eidTight;
// 	if( eidBitTight<0 ){
// 	  std::cout << "   ===>>>>  BREAK!!  eidBitTight = " << eidBitTight << std::endl;
// 	  break;
// 	}
// 	bool eidTight = ( (eidBitTight & 1)==1 );

// 	bool d0 = ( fabs(electrons.at(i).correctedD0) < 0.02 );
// 	bool dZ = ( fabs(electrons.at(i).correctedDZ) < 1. );

// 	bool dist  = ( fabs(electrons.at(i).dist)<0.02 );
// 	bool dcot  = ( fabs(electrons.at(i).dcot)<0.02 );
// 	bool nlost = ( electrons.at(i).numberOfLostHits<1 );
//         bool notConv = ( !(dist && dcot) && nlost );

// 	bool tightIso = ( relIso < 0.1 );

//       	bool id = ( eidTight && d0 && dZ && notConv );

//       	if( ((elePt>20.) && id && tightIso) ) {
// 	  tight_ele_index.push_back(i);
// 	  if (elePt > fstElePt) fstElePt = elePt;
// 	}
// 	else {
// 	  only_loose_ele_index.push_back(i);
// 	  if (elePt > sndElePt) sndElePt = elePt;
// 	}
//       }// end electron loop

//       int numTightElectrons = int(tight_ele_index.size());
//       int numLooseElectrons = int(loose_ele_index.size()) - numTightElectrons;


      /////////
      ///
      /// Muons
      ///
      ////////
      ////--------- using selectors in "BEANsUtilities.h"
      ////////////////////////////////
      std::vector<int> tight_mu_index;
      std::vector<int> loose_mu_index;
      std::vector<double> tightMuonSF;
      std::vector<double> looseMuonSF;
      std::vector<int> side_tight_mu_index;
      std::vector<int> side_loose_mu_index;
      std::vector<double> sideTightMuonSF;
      std::vector<double> sideLooseMuonSF;
      BEANs::muonSelector( muons, false, sysType, selectionYear_, tight_mu_index, loose_mu_index, side_tight_mu_index, side_loose_mu_index, tightMuonSF, looseMuonSF, sideTightMuonSF, sideLooseMuonSF );

//       tight_mu_index = loose_mu_index;
//       side_tight_mu_index.insert(side_tight_mu_index.end(), side_loose_mu_index.begin(), side_loose_mu_index.end());
//       loose_mu_index = side_tight_mu_index;
//       tightMuonSF = looseMuonSF;
//       sideTightMuonSF.insert(sideTightMuonSF.end(), sideLooseMuonSF.begin(), sideLooseMuonSF.end());
//       looseMuonSF = sideTightMuonSF;
      
      int numTightMuons = int(tight_mu_index.size());
      int numLooseMuons = int(loose_mu_index.size());

      ////////////////////////////////
      ////--------- old frame work
      ////////////////////////////////
//       float fstMuPt = 0.0 ;
//       float sndMuPt = 0.0 ;

//       std::vector<int> tight_mu_index;
//       std::vector<int> loose_mu_index;
//       std::vector<int> only_loose_mu_index;
//       for( int i=0; i<int(muons.size()); i++ ){

// 	float muPt  = muons.at(i).pt;
// 	double muEta = muons.at(i).eta;
// 	double muPhi = muons.at(i).phi;
// 	double muAbsEta = fabs(muEta);

// 	bool kin = ( (muPt>10.) && (muAbsEta<2.4) );

// 	if( !kin ) continue;

// 	double chargedHadronIso = muons.at(i).chargedHadronIso;
// 	double neutralHadronIso = muons.at(i).neutralHadronIso;
// 	double photonIso = muons.at(i).photonIso;

// 	double relIso = ( chargedHadronIso + neutralHadronIso + photonIso ) * 1./muPt;

// 	bool looseIso = ( relIso<0.2 );

// 	bool isGlobalMuon = ( muons.at(i).isGlobalMuon==1 );

// 	if( !(isGlobalMuon && looseIso) ) continue;

// 	loose_mu_index.push_back(i);

// 	bool isTrackerMuon = ( muons.at(i).isTrackerMuon==1 );
// 	bool isGlobalMuonPromptTight = ( muons.at(i).isGlobalMuonPromptTight==1 );

// 	bool numTrackHits = ( muons.at(i).numberOfValidTrackerHitsInnerTrack > 10 );
// 	bool numPixelHits = ( muons.at(i).pixelLayersWithMeasurement>0 );
// 	bool numberOfMatches = ( muons.at(i).numberOfMatches>1 );

// 	bool passd0 = ( fabs(muons.at(i).correctedD0)<0.02 );
// 	bool passdz = ( fabs(muons.at(i).correctedDZ)<1. );

// 	bool id = ( isTrackerMuon && isGlobalMuonPromptTight && numTrackHits && numPixelHits && numberOfMatches && passd0 && passdz );

// 	bool tightIso = ( relIso<0.125 );

//     // JMS Changed muon pt cut
//     // JMS used to be 30
//     // is now back to 30
    
// 	if( ((muPt>20.) && (muAbsEta<2.1) && id && tightIso) ){
// 	  tight_mu_index.push_back(i);
// // 	  h_mu_pt->Fill(muPt,wgt);
// // 	  h_mu_eta->Fill(muEta,wgt);
// // 	  h_mu_phi->Fill(muPhi,wgt);

// 	  if (muPt > fstMuPt) fstMuPt = muPt;  ///Robin

//       // just assert that you fired a double muon trigger
// 	  bool mu_fired_trigger = false;
//       mu_fired_trigger = true;

      
// 	  // for( TrigObjIter hltobj = hltobjs.begin(); hltobj != hltobjs.end(); ++hltobj ){
// // 	    //// Dump out filter name, pt, eta, phi for each HLT object
// // 	    //std::cout << "\t" << hltobj->filter << "\t pt, eta, phi = " << hltobj->pt << ",\t " << hltobj->eta << ",\t " << hltobj->phi << std::endl;
// // 	    if( hltobj->filter==mc_hlt_filter_names[0] ){
// // 	      double trigEta = hltobj->eta;
// // 	      double trigPhi = hltobj->phi;

// // 	      double dR_mu_hlt = kinem::delta_R(trigEta,trigPhi,muEta,muPhi);
// // 	      h_dR_mu_hlt->Fill(dR_mu_hlt,wgt);
// // 	      if( dR_mu_hlt<0.3 ){
// // 		mu_fired_trigger = true;
// // 		break;
// // 	      }
// // 	    }
// // 	  } // end for each trigger object
      
      
// 	} // end if tight muon
// 	else {
// 	  only_loose_mu_index.push_back(i);
// 	  if (muPt>sndMuPt) sndMuPt = muPt;      ///Robin
// 	}
//       }// end muon loop


//       if (verbose) std::cout << "done with muons" <<std::endl;      

//       int numTightMuons = int(tight_mu_index.size());
//       int numLooseMuons = int(loose_mu_index.size()) - numTightMuons;


//       if (numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons >= 2 )
//         std::cout << "Done with lepton selection... this event could be dilepton " << std::endl
//                                << "numTightMuons = " << numTightMuons << std::endl
//                                <<" numLooseMuons = " << numLooseMuons << std::endl
//                                << "numTightElectron = " << numTightElectrons << std::endl
//                                << "numLooseElectrons = " << numLooseElectrons << std::endl;
        
      //      if ( numLooseMuons != int(only_loose_mu_index.size()) ) std::cout << ".......failure, lalala............" << std::endl;     
      bool twoLeptons = (( numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons )== 2 && ( numTightMuons + numTightElectrons )> 0 );
      if ( !twoLeptons ) continue ;
    
      /////////
      ///
      /// Pfjets
      ///
      ////////
      std::vector<int> tight_pfjet_index;
      std::vector<int> all_pfjet_index;
      std::vector<int> tag_pfjet_index;
      std::vector<int> tag_pfjet_csvVal;
      std::vector<int> untag_pfjet_index;

      std::vector<double> good_jet_pt;
      std::vector<double> good_jet_eta;
      std::vector<double> good_jet_CHEF;
      std::vector<double> good_jet_charge;
      std::vector<double> good_jet_tag;
      std::vector<int>    good_jet_flavor;

      std::vector<int>    jet_motherID;
      
      vdouble jet_px;
      vdouble jet_py;
      vdouble jet_pz;
      vdouble jet_pt;
      vdouble jet_energy;
      vdouble jet_CHEF;
      vdouble jet_charge;

      int numGoodJets=0;
      int numHiggsJets=0;
      int numHiggsAllJets=0;
      int numGoodAndBadJets=0;
      TLorentzVector jetV[100];
      TLorentzVector allJetV[100];
      TLorentzVector higgsJetV[100];
      TLorentzVector higgsGenJetV[100];
      TLorentzVector higgsGenPartonV[100];
      
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
        
      for( int i=0; i<int(pfjets.size()); i++ ){
        
	jet_px.push_back(pfjets.at(i).px);
	jet_py.push_back(pfjets.at(i).py);
	jet_pz.push_back(pfjets.at(i).pz);
	jet_pt.push_back(pfjets.at(i).pt);
	jet_energy.push_back(pfjets.at(i).energy);
    jet_CHEF.push_back(pfjets.at(i).chargedHadronEnergyFraction);
    jet_charge.push_back(pfjets.at(i).charge);

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
    double genJetPT = pfjets.at(i).genJetPT;
    //double jetPhi = pfjets.at(i).phi;
    double jetCHEF = pfjets.at(i).chargedHadronEnergyFraction;
    double jetcharge = pfjets.at(i).charge;
    double myJER = BEANs::getJERfactor( jer, jetAbsEta, genJetPT, jetPt);

    //don't scale data jets
    if ( isData) {      
      myJER = 1.0;
    }
    // testing w/o   JER
    //myJER = 1.0;


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

    if (pfjets.at(i).genPartonMotherId == 25) {
      higgsJetV[numHiggsAllJets].SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
      higgsGenJetV[numHiggsAllJets].SetPtEtaPhiE(pfjets.at(i).genJetPT,pfjets.at(i).genJetEta,pfjets.at(i).genJetPhi,pfjets.at(i).genJetET/sin(2*atan(exp(-pfjets.at(i).genJetEta))));
      higgsGenPartonV[numHiggsAllJets].SetPtEtaPhiE(pfjets.at(i).genPartonPT,pfjets.at(i).genPartonEta,pfjets.at(i).genPartonPhi,pfjets.at(i).genPartonET/sin(2*atan(exp(-pfjets.at(i).genPartonEta))));
      numHiggsAllJets++;
    } 
    //std::cout << "Jet " << i << " ID: " << pfjets.at(i).genPartonMotherId << std::endl;
    jet_motherID.push_back(pfjets.at(i).genPartonMotherId);
//     if (pfjets.at(i).genPartonMotherId != 25  && pfjets.at(i).genPartonGrandMotherId != 99 && pfjets.at(i).genPartonGrandMotherId != -99) {
//       if (pfjets.at(i).genPartonGrandMotherId == 25) {
//         std::cout << "GrandMother for jet " << i << " is HIGGS and mother is " << pfjets.at(i).genPartonMotherId << std::endl;
//       }
//       else {
//         std::cout << "GrandMother for jet " << i << " is " << pfjets.at(i).genPartonGrandMotherId << std::endl;
//       }
//     }
    allJetV[numGoodAndBadJets].SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
    numGoodAndBadJets++;
    
	bool kin = ( jetPt>30. );
	bool eta = ( jetAbsEta<2.4 );
	bool id  = ( pfjets.at(i).jetIDLoose==1 );
    
	if( !(kin && eta && id) ) continue;

	if (pfjets.at(i).genPartonMotherId == 25) {
	  numHiggsJets++;
	} 

	/// remove dR_jet_lep cut
// 	bool hasCloseLepton = false;
// 	for( int m=0; m<int(tight_mu_index.size()); m++ ){
// 	  int mu_index = tight_mu_index[m];
// 	  double dR_mu_jet = kinem::delta_R(muons.at(mu_index).eta,muons.at(mu_index).phi,jetEta,jetPhi);
// 	  if( dR_mu_jet<0.3 ){
// 	    hasCloseLepton = true;
// 	    break;
// 	  }
// 	}
// 	for( int m=0; m<int(tight_ele_index.size()); m++ ){
// 	  int ele_index = tight_ele_index[m];
// 	  double dR_ele_jet = kinem::delta_R(electrons.at(ele_index).eta,electrons.at(ele_index).phi,jetEta,jetPhi);
// 	  if( dR_ele_jet<0.3 ){
// 	    hasCloseLepton = true;
// 	    break;
// 	  }
// 	}

// 	// this is probably too much... 
// 	if( hasCloseLepton ) {
// 	  nEventsWhereJetRemoved++;
// 	  continue;
// 	}
	
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


// 	h_jet_pt->Fill(jetPt,wgt);
// 	h_jet_eta->Fill(jetEta,wgt);
// 	h_jet_phi->Fill(jetPhi,wgt);



	// use sec vtx high eff
	
	//double svhe = pfjets.at(i).btagSecVertexHighEff;
	//bool svheL = ( svhe>1.74 );
	
	
	// Use Combined tags
	// Loose Cut is 0.244
	// Medium Cut is 0.679
	// Tight Cut is 0.898


    //------------- update this now

    float csv_old = pfjets.at(i).btagCombinedSecVertex;
    int iJetFlav = pfjets.at(i).flavour;
    std::string sysType = "regular";
    if (isData) {
      sysType = "data";
    } else if (btagCSVShape == 1) {
      sysType = "hfSFUp";
    } else if (btagCSVShape == -1) {
      sysType = "hfSFDown";
    } else if (btagCSVShape == 2) {
      sysType = "lfSFUp";
    } else if (btagCSVShape == -2) {
      sysType = "lfSFDown";
    }

    float csv = BEANs::reshape_csv( jetEta, jetPt, csv_old, iJetFlav, sysType ); 
	bool csvM = ( csv> btagThres );

	
	if( csvM ){
	  tag_pfjet_index.push_back(i);
	  jet_desc.push_back(csv);
      tag_pfjet_csvVal.push_back(csv);
	}
	else        untag_pfjet_index.push_back(i);
	
// 	int parId =  abs(pfjets.at(i).genPartonId);

// 	if( parId==5  ){
// 	  h_jet_pt_b->Fill(jetPt,wgt);
// 	  h_jet_disc_b->Fill(csv,wgt);
// 	}
// 	else if( parId==4  ){
// 	  h_jet_pt_c->Fill(jetPt,wgt);
// 	  h_jet_disc_c->Fill(csv,wgt);
// 	}
// 	else if( parId==1 || parId==2 || parId==3 || parId==21 ){
// 	  h_jet_pt_l->Fill(jetPt,wgt);
// 	  h_jet_disc_l->Fill(csv,wgt);
// 	}

	int flavor =  pfjets.at(i).flavour;

	good_jet_pt.push_back(jetPt);
	good_jet_eta.push_back(jetEta);
	good_jet_tag.push_back(csv);
	good_jet_flavor.push_back(flavor);
    good_jet_CHEF.push_back(jetCHEF);
    good_jet_charge.push_back(jetcharge);

      }// end for each pf jet
      
      //Robin
//       *(floatBranches["fstMuPt"]) = fstMuPt ;
//       *(floatBranches["sndMuPt"]) = sndMuPt ;

//       *(floatBranches["fstElePt"]) = fstElePt ;
//       *(floatBranches["sndElePt"]) = sndElePt ;

      //------------------------
      int numAllJet = numGoodAndBadJets;
      int numJet = int(tight_pfjet_index.size());
      int numBadJet = numAllJet - numJet;
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

//       bool geOneTightMuon = (numTightMuons >=1);
//       bool geTwoJets = (numJet >=2 );
//       bool geThreeJets = (numJet >=3);
//       bool geTwoTags = (numTag >=2);
//       bool geThreeTags = (numTag >=3);

      bool passTwoMuon = twoLeptons && ( twoTightMuon || TightMuonLooseMuon ) ;
      bool passTwoEle = twoLeptons && ( twoTightEle || TightEleLooseEle ) ;
      bool passMuonEle = twoLeptons && ( TightMuonLooseEle || TightEleLooseMuon || oneEleOneMuon );
      
      *(intBranches["PassTwoLepton"]) =  twoLeptons ? 1 : 0;
      *(intBranches["TwoMuon"]) = passTwoMuon ? 1 : 0;
      *(intBranches["TwoEle"]) =  passTwoEle ? 1 : 0;
      *(intBranches["MuonEle"]) = passMuonEle ? 1 : 0;
//       *(intBranches["isCleanEvent"]) = 1;
//       if( selectionYear_ == "2011") {
        *(intBranches["isCleanEvent"]) = cleanEvent ? 1 : 0;
//       }
      *(intBranches["isTriggerPass"]) = triggerPass ? 1 : 0;
//       *(intBranches["isTriggerPassPrescaled"]) = triggerPassPrescaled ? 1 : 0;
      *(intBranches["isDoubleMuTriggerPass"]) = DoubleMuTriggerPass ? 1 : 0;
      *(intBranches["isDoubleElectronTriggerPass"]) = DoubleElectronTriggerPass ? 1 : 0;
      *(intBranches["isMuEGTriggerPass"]) = MuEGTriggerPass ? 1 : 0;
      *(intBranches["isMETTriggerPass"]) = METTriggerPass ? 1 : 0;
//       *(intBranches["isDoubleMuTriggerPS0"]) = DoubleMuTriggerPS0 ? 1 : 0;
//       *(intBranches["isDoubleElectronTriggerPS0"]) = DoubleElectronTriggerPS0 ? 1 : 0;
//       *(intBranches["isMuEGTriggerPS0"]) = MuEGTriggerPS0 ? 1 : 0;
//       *(intBranches["isMETTriggerPS0"]) = METTriggerPS0 ? 1 : 0;
      *(intBranches["isMu8Pass"]) =  HLT_Mu8_v ? 1 : 0;
      *(intBranches["isDoubleMu7Pass"]) =  HLT_DoubleMu7_v ? 1 : 0;
      *(intBranches["isMu13_Mu8Pass"]) =  HLT_Mu13_Mu8_v ? 1 : 0;
      *(intBranches["isMu17_Mu8Pass"]) =  HLT_Mu17_Mu8_v ? 1 : 0;
      *(intBranches["isMu17_TkMu8Pass"]) =  HLT_Mu17_TkMu8_v ? 1 : 0;
      *(intBranches["isMu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVLPass"]) =  HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v ? 1 : 0;
      *(intBranches["isMu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVLPass"]) =  HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v ? 1 : 0;
      *(intBranches["isEle17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVLPass"]) =  HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v ? 1 : 0;
      *(intBranches["isEle8_CaloIdL_CaloIsoVLPass"]) =  HLT_Ele8_CaloIdL_CaloIsoVL_v ? 1 : 0;
      *(intBranches["isMu22_Photon22_CaloIdLPass"]) = HLT_Mu22_Photon22_CaloIdL_v ? 1 : 0;
      *(intBranches["isMu30_Ele30_CaloIdLPass"]) = HLT_Mu30_Ele30_CaloIdL_v ? 1 : 0;
      *(intBranches["isDiCentralPFJet30_PFMET80_BTagCSV07Pass"]) = HLT_DiCentralPFJet30_PFMET80_BTagCSV07_v ? 1 : 0;
      *(intBranches["isDiCentralPFJet50_PFMET80Pass"]) = HLT_DiCentralPFJet50_PFMET80_v ? 1 : 0;
      *(intBranches["isMET120_HBHENoiseCleanedPass"]) = HLT_MET120_HBHENoiseCleaned_v ? 1 : 0;
      *(intBranches["isMET200Pass"]) = HLT_MET200_v ? 1 : 0;
      *(intBranches["isPFMET150Pass"]) = HLT_PFMET150_v ? 1 : 0;

      
      *(intBranches["HiggsDecayMode"]) = HtoCC*4 + HtoBB*5 + HtoTT*6 + HtoGG*21 + HtoZZ*23 + HtoWW*24;

      *(intBranches["numJets"]) = numJet ;
//       *(intBranches["numAllJets"]) = numAllJet;
//       *(intBranches["numBadJets"]) = numBadJet;
      *(intBranches["numTaggedJets"]) = numTag;
//       *(intBranches["numNonTaggedJets"]) = numNonTag;
      //*(intBranches["numHiggsJets"]) = numHiggsJets;
      //*(intBranches["numHiggsAllJets"]) = numHiggsAllJets;
      
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
      double wgt_prob=0, wgt_prob_hfSFup=0, wgt_prob_hfSFdown=0, wgt_prob_lfSFup=0, wgt_prob_lfSFdown=0;
      double wgt_prob_ge4=0, wgt_prob_ge4_hfSFup=0, wgt_prob_ge4_hfSFdown=0, wgt_prob_ge4_lfSFup=0, wgt_prob_ge4_lfSFdown=0;


      //      if( (sample>=0 || sample==-2500) && !isData){
      if (!isData) {
          std::vector<BTagWeight::JetInfo> myjetinfo;                                                                   
          std::vector<BTagWeight::JetInfo> myjetinfo_hfSFup;                                                            
          std::vector<BTagWeight::JetInfo> myjetinfo_hfSFdown;                                                          
          std::vector<BTagWeight::JetInfo> myjetinfo_lfSFup;                                                            
          std::vector<BTagWeight::JetInfo> myjetinfo_lfSFdown;
          if (verbose) std::cout << "Looping over  jets for btag uncert" <<std::endl;
          for( int j=0; j<int(good_jet_pt.size()); j++ ){
            if (verbose) std::cout << "calling btag sf" <<std::endl;
            if (verbose) std::cout << "one" <<std::endl;
            std::vector<double> myEffSF = BEANs::getEffSF( 0, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j], selectionYear_ );
            if (verbose) std::cout << "return from getEffSF, try myjet" <<std::endl;
            BTagWeight::JetInfo myjet( myEffSF[0], myEffSF[1] ); 
            myjetinfo.push_back(myjet);

            if (verbose) std::cout << "two" <<std::endl;
            std::vector<double> myEffSF_hfSFup = BEANs::getEffSF( 1, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j], selectionYear_);
            BTagWeight::JetInfo myjet_hfSFup( myEffSF_hfSFup[0], myEffSF_hfSFup[1] );
            myjetinfo_hfSFup.push_back(myjet_hfSFup);
            if (verbose) std::cout << "three" <<std::endl;
            std::vector<double> myEffSF_hfSFdown = BEANs::getEffSF( -1, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j], selectionYear_ );
            BTagWeight::JetInfo myjet_hfSFdown( myEffSF_hfSFdown[0], myEffSF_hfSFdown[1] );
            myjetinfo_hfSFdown.push_back(myjet_hfSFdown);
            if (verbose) std::cout << "four" <<std::endl;
            std::vector<double> myEffSF_lfSFup = BEANs::getEffSF( 2, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j], selectionYear_  );
            BTagWeight::JetInfo myjet_lfSFup( myEffSF_lfSFup[0], myEffSF_lfSFup[1] );
            myjetinfo_lfSFup.push_back(myjet_lfSFup);
            if (verbose) std::cout << "five" <<std::endl;
            std::vector<double> myEffSF_lfSFdown = BEANs::getEffSF( -2, good_jet_pt[j], good_jet_eta[j], good_jet_flavor[j], selectionYear_ );
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
	//        if( (sample>=0 || sample==-2500) && !isData){
        if (!isData){
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
        *(floatBranches["prob_hfSFdown"]) = wgt_btag_hfSFdown;
        *(floatBranches["prob_hfSFup"]) = wgt_btag_hfSFup;
        *(floatBranches["prob_lfSFdown"]) = wgt_btag_lfSFdown;
        *(floatBranches["prob_lfSFup"]) = wgt_btag_lfSFup;


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

      //////  ttbb bkg -- dibjet mass combinations
      std::list<float> dibjet_mass_combinations;
      float m2H_btag = 0.0 ;

      std::list<float> dijet_mass_combinations;
      float dijet_mass_m2H = 0.0 ;

      //sum of all jets
      TLorentzVector sum_jet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_allJet_vect(0.0,0.0,0.0,0.0);
      
      for (int sumv=0; sumv < numJet; sumv++) {
	sum_jet_vect += jetV[sumv];
      }
      for (int sumv=0; sumv < numAllJet; sumv++) {
	sum_allJet_vect += allJetV[sumv];
      }


      
      TLorentzVector sum_higgs_dijet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_higgsLike_dijet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_higgsLike_allDijet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_topLike_trijet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_topLike_allTrijet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_higgs_genJet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_higgs_genParton_vect(0.0,0.0,0.0,0.0);
      
      float higgs_dijet_mass = -10.0;
      float higgsLike_dijet_mass1 = -10.0;
      float higgsLike_dijet_mass2 = -10.0;
      float wLike_dijet_mass1 = -10.0;
      float topLike_trijet_mass1 = -10.0;
      float topLike_trijet_mass2 = -10.0;
      float higgsLike_allDijet_mass1 = -10.0;
      float higgsLike_allDijet_mass2 = -10.0;
      float wLike_allDijet_mass1 = -10.0;
      float topLike_allTrijet_mass1 = -10.0;
      float topLike_allTrijet_mass2 = -10.0;
      float higgs_genJet_mass = -10.0;
      float higgs_genParton_mass = -10.0;
      
      if (numHiggsAllJets == 2) {
        sum_higgs_dijet_vect = higgsJetV[0] + higgsJetV[1];
        higgs_dijet_mass = sum_higgs_dijet_vect.M();
        sum_higgs_genJet_vect = higgsGenJetV[0] + higgsGenJetV[1];
        higgs_genJet_mass = sum_higgs_genJet_vect.M();
        sum_higgs_genParton_vect = higgsGenPartonV[0] + higgsGenPartonV[1];
        higgs_genParton_mass = sum_higgs_genParton_vect.M();
      }
      if (numHiggsAllJets > 2) {
        std::cout << "First three higgs jets have pt " << higgsJetV[0].Pt() << ", " << higgsJetV[1].Pt() << ", " << higgsJetV[2].Pt() << std::endl;
      }

      if (debug_)
        cout << "more printing to avoid warnings problems  "
             << higgs_dijet_mass << " "
             << higgs_genJet_mass << " "
             << higgs_genParton_mass << " "
             << endl;
      
      TLorentzVector dijet_vect;
      TLorentzVector lep_vect1;
      TLorentzVector lep_vect2;
      TLorentzVector lep_vect1_transverse;
      TLorentzVector lep_vect2_transverse;
      TLorentzVector jet_vect;
      TLorentzVector allJet_vect;
      
      TLorentzVector btag_vect1;
      TLorentzVector btag_vect2;

      // ttbb
      TLorentzVector jet_vect1;
      TLorentzVector jet_vect2;
      
      float first_jet_pt = 0.0 ;
      float second_jet_pt = 0.0 ;
      float third_jet_pt = 0.0 ;
      float fourth_jet_pt = 0.0 ;
      
      float first_jet_eta = 10000.;
      float second_jet_eta = 10000.;
      float third_jet_eta = 10000.;
      float fourth_jet_eta = 10000.;

      float first_jet_CHEF = 10000.;
      float second_jet_CHEF = 10000.;
      float third_jet_CHEF = 10000.;
      float fourth_jet_CHEF = 10000.;
      float sum_jet_CHEF = 0.0;
      
      float first_jet_charge = 10000.;
      float second_jet_charge = 10000.;
      float third_jet_charge = 10000.;
      float fourth_jet_charge = 10000.;
      float sum_jet_charge = 0.0;
      
      float dPhi_jet1jet2 = 10000.;
      float dPhi_jet1jet3 = 10000.;
      float dPhi_jet1jet4 = 10000.;
      float dPhi_jet2jet3 = 10000.;
      float dPhi_jet2jet4 = 10000.;
      float dPhi_jet3jet4 = 10000.;

      float first_allJet_pt = 0.0 ;
      float second_allJet_pt = 0.0 ;
      float third_allJet_pt = 0.0 ;
      float fourth_allJet_pt = 0.0 ;
      
      float min_jet_lep1_dR = 10000.;
      float min_jet_lep2_dR = 10000.;
      float min_allJet_lep1_dR = 10000.;
      float min_allJet_lep2_dR = 10000.;
      float min_tagged_jets_dR = 10000.;
      float min_jets_dR = 10000.;   //ttbb
      
      float denom_avg_cnt = 0.;
      float avg_btag_disc_btags = 0.;     
      float avg_btag_disc_non_btags = 0.;
      double highest_btag_disc_non_btags = 0.;
      float dev_from_avg_disc_btags = 0.;

      float sum_pt = 0.0 ;
      float sum_jet_pt = 0.0;
      float all_sum_pt = 0.0 ;
      float Ht = 0.0 ;
      //      float mass_of_everything = 0.0 ;
      //ttbb

      float dijet_mass_first  = 0.0;
      float dijet_mass_second = 0.0;
      float dijet_mass_third  = 0.0;

      float first_dibjet_mass  = 0.0;
      float second_dibjet_mass = 0.0;
      float third_dibjet_mass  = 0.0;

      float min_dr_jets = 0.0 ;
      float avg_dr_jets = 0.0 ;
      float avg_dijet_mass = 0.0 ;
      float closest_dijet_mass = 0.0 ;
      float M2_of_closest_jets = 0.0 ;
     
      float min_dr_tagged_jets = 0.0 ;
      float avg_dr_tagged_jets = 0.0 ;
      float avg_tagged_dijet_mass = 0.0 ;
      float closest_tagged_dijet_mass = 0.0 ;
      float M2_of_closest_tagged_jets = 0.0 ;
      float min_dr_genB1_allJet = -10.0;
      float min_dr_genB2_allJet = -10.0;
      
      TLorentzVector non_btag_vect1;
      TLorentzVector non_btag_vect2;
      float avg_untagged_dijet_mass = 0.0 ;

      if ( twoLeptons ){  //////// number of jets and number of tags
	
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
    float lep1_tkDZ = 0 ;
    float lep2_tkDZ = 0 ;
    float lep1_iso = 0 ;
    float lep2_iso = 0 ;
    float lep1_correctedDZ = 0 ;
    float lep2_correctedDZ = 0 ;
    float lep1_correctedD0 = 0 ;
    float lep2_correctedD0 = 0 ;
    float lep1TkCharge = -10;
    float lep1GenCharge = -10;
    float lep2TkCharge = -10;
    float lep2GenCharge = -10;
    int lep1GenMotherId = 0;
    int lep2GenMotherId = 0;
    float lep1SF = 1.0;
    float lep2SF = 1.0;
    int lep2IsGlobalMuon = 0;
    int lep2IsTrackerMuon = 0;
    int lep2IsGlobalMuonPromptTight = 0;
    int lep2NumTrackHits = 0;
    int lep2NumPixelHits = 0;
    int lep2NumberOfMatches = 0;
    float lep2Chi2 = 0;
    int lep2NumExpectedHits = 0;
    
	  if( twoTightMuon || TightMuonLooseMuon ){
	    if( twoTightMuon ) {
	      iMuon1 = tight_mu_index[0] ;
	      iMuon2 = tight_mu_index[1] ;
          lep1SF = tightMuonSF[0];
          lep2SF = tightMuonSF[1];
          
	      if(muons.at(iMuon1).pt < muons.at(iMuon2).pt) {
            iMuon1 = tight_mu_index[1] ;
            iMuon2 = tight_mu_index[0] ;
            lep1SF = tightMuonSF[1];
            lep2SF = tightMuonSF[0];
        
	      }
	    }
	    
	    if( TightMuonLooseMuon ) {
	      iMuon1 = tight_mu_index[0] ;
	      iMuon2 = loose_mu_index[0] ;
          lep1SF = tightMuonSF[0];
          lep2SF = looseMuonSF[0];
	    }

        
        
	    lep1_pt = muons.at(iMuon1).pt;
	    lep2_pt = muons.at(iMuon2).pt;
	    
	    lep1_et = muons.at(iMuon1).et;
	    lep2_et = muons.at(iMuon2).et;  

	    lep1_eta = muons.at(iMuon1).eta;
	    lep2_eta = muons.at(iMuon2).eta;  

	    lep1_phi = muons.at(iMuon1).phi;
	    lep2_phi = muons.at(iMuon2).phi;  

        lep1_tkDZ = muons.at(iMuon1).tkDZ;
        lep2_tkDZ = muons.at(iMuon2).tkDZ;

        lep1_correctedDZ = muons.at(iMuon1).correctedDZ;
        lep2_correctedDZ = muons.at(iMuon2).correctedDZ;

        lep1_correctedD0 = muons.at(iMuon1).correctedD0;
        lep2_correctedD0 = muons.at(iMuon2).correctedD0;
        
        lep1TkCharge = muons.at(iMuon1).tkCharge;
        lep2TkCharge = muons.at(iMuon2).tkCharge;

        lep1GenCharge = muons.at(iMuon1).genCharge;
        lep2GenCharge = muons.at(iMuon2).genCharge;

        lep1GenMotherId = muons.at(iMuon1).genMotherId;
        lep2GenMotherId = muons.at(iMuon2).genMotherId;

        lep2IsGlobalMuon = muons.at(iMuon2).isGlobalMuon;
        lep2IsTrackerMuon = muons.at(iMuon2).isTrackerMuon;
        lep2IsGlobalMuonPromptTight = muons.at(iMuon2).isGlobalMuonPromptTight;
        lep2NumTrackHits = muons.at(iMuon2).numberOfValidTrackerHitsInnerTrack;
        lep2NumPixelHits = muons.at(iMuon2).pixelLayersWithMeasurement;
        lep2NumberOfMatches = muons.at(iMuon2).numberOfMatchedStations;

        for (int ii=0; ii<int(muon_px.size()); ii++) {
          if (abs(muons.at(iMuon1).px-muon_px[ii])/max(abs(muons.at(iMuon1).px),10.0) < 0.3 && abs(muons.at(iMuon1).py-muon_py[ii])/max(abs(muons.at(iMuon1).py),10.0) < 0.3 && abs(muons.at(iMuon1).pz-muon_pz[ii])/max(abs(muons.at(iMuon1).pz),10.0) < 0.3) {
            lep1Mother = muon_mother[ii];
            lep1Grandmother = muon_grandmother[ii];
          }
          if (abs(muons.at(iMuon2).px-muon_px[ii])/max(abs(muons.at(iMuon2).px),10.0) < 0.3 && abs(muons.at(iMuon2).py-muon_py[ii])/max(abs(muons.at(iMuon2).py),10.0) < 0.3 && abs(muons.at(iMuon2).pz-muon_pz[ii])/max(abs(muons.at(iMuon2).pz),10.0) < 0.3) {
            lep2Mother = muon_mother[ii];
            lep2Grandmother = muon_grandmother[ii];
          }
        }

        if (selectionYear_ == "2011") {
          lep1_iso = (muons.at(iMuon1).chargedHadronIso + muons.at(iMuon1).neutralHadronIso + muons.at(iMuon1).photonIso) * 1.0 / lep1_pt;
          lep2_iso = (muons.at(iMuon2).chargedHadronIso + muons.at(iMuon2).neutralHadronIso + muons.at(iMuon2).photonIso) * 1.0 / lep2_pt;
        }
        if (selectionYear_ == "2012") {
          lep1_iso = (muons.at(iMuon1).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon1).pfIsoR04SumNeutralHadronEt + muons.at(iMuon1).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon1).pfIsoR04SumPUPt)) * 1.0 /lep1_pt;
          lep2_iso = (muons.at(iMuon2).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon2).pfIsoR04SumNeutralHadronEt + muons.at(iMuon2).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon2).pfIsoR04SumPUPt)) * 1.0 /lep2_pt;
        }

        lep_vect1.SetPxPyPzE(muons.at(iMuon1).px, muons.at(iMuon1).py, muons.at(iMuon1).pz, muons.at(iMuon1).energy);
	    lep_vect2.SetPxPyPzE(muons.at(iMuon2).px, muons.at(iMuon2).py, muons.at(iMuon2).pz, muons.at(iMuon2).energy);
        lep_vect1_transverse.SetPxPyPzE(muons.at(iMuon1).px, muons.at(iMuon1).py, 0.0, sqrt(pow(muons.at(iMuon1).energy,2) - pow(muons.at(iMuon1).pz,2)));
        lep_vect2_transverse.SetPxPyPzE(muons.at(iMuon2).px, muons.at(iMuon2).py, 0.0, sqrt(pow(muons.at(iMuon2).energy,2) - pow(muons.at(iMuon2).pz,2)));

	  }

	  if( twoTightEle || TightEleLooseEle ){
	    if( twoTightEle ){
	      iEle1 = tight_ele_index[0] ;
	      iEle2 = tight_ele_index[1] ;
          lep1SF = tightElectronSF[0];
          lep2SF = tightElectronSF[1];
          
	      if(electrons.at(iEle1).pt < electrons.at(iEle2).pt){
            iEle1 = tight_ele_index[1] ;
            iEle2 = tight_ele_index[0] ;
            lep1SF = tightElectronSF[1];
            lep2SF = tightElectronSF[0];
	      }
	    }

	    if( TightEleLooseEle ){
	      iEle1 = tight_ele_index[0] ;
	      iEle2 = loose_ele_index[0] ;
          lep1SF = tightElectronSF[0];
          lep2SF = looseElectronSF[0];
          
	    }
	  
	    lep1_pt = electrons.at(iEle1).pt;
	    lep2_pt = electrons.at(iEle2).pt;
	    
	    lep1_et = electrons.at(iEle1).et;
	    lep2_et = electrons.at(iEle2).et;  

	    lep1_eta = electrons.at(iEle1).eta;
	    lep2_eta = electrons.at(iEle2).eta;  

	    lep1_phi = electrons.at(iEle1).phi;
	    lep2_phi = electrons.at(iEle2).phi;  

        lep1_tkDZ = electrons.at(iEle1).tkDZ;
        lep2_tkDZ = electrons.at(iEle2).tkDZ;

        lep1_correctedDZ = electrons.at(iEle1).correctedDZ;
        lep2_correctedDZ = electrons.at(iEle2).correctedDZ;

        lep1_correctedD0 = electrons.at(iEle1).correctedD0;
        lep2_correctedD0 = electrons.at(iEle2).correctedD0;
        
        lep1TkCharge = electrons.at(iEle1).tkCharge;
        lep2TkCharge = electrons.at(iEle2).tkCharge;

        lep1GenCharge = electrons.at(iEle1).genCharge;
        lep2GenCharge = electrons.at(iEle2).genCharge;
        
        for (int ii=0; ii<int(ele_px.size()); ii++) {
          if (abs(electrons.at(iEle1).px-ele_px[ii])/max(abs(electrons.at(iEle1).px),10.0) < 0.3 && abs(electrons.at(iEle1).py-ele_py[ii])/max(abs(electrons.at(iEle1).py),10.0) < 0.3 && abs(electrons.at(iEle1).pz-ele_pz[ii])/max(abs(electrons.at(iEle1).pz),10.0) < 0.3) {
            lep1Mother = ele_mother[ii];
            lep1Grandmother = ele_grandmother[ii];
          }
          if (abs(electrons.at(iEle2).px-ele_px[ii])/max(abs(electrons.at(iEle2).px),10.0) < 0.3 && abs(electrons.at(iEle2).py-ele_py[ii])/max(abs(electrons.at(iEle2).py),10.0) < 0.3 && abs(electrons.at(iEle2).pz-ele_pz[ii])/max(abs(electrons.at(iEle2).pz),10.0) < 0.3) {
            lep2Mother = ele_mother[ii];
            lep2Grandmother = ele_grandmother[ii];
          }
        }

        if (selectionYear_ == "2011") {
          lep1_iso = (electrons.at(iEle1).chargedHadronIso + electrons.at(iEle1).neutralHadronIso + electrons.at(iEle1).photonIso) * 1.0 / lep1_pt;
          lep2_iso = (electrons.at(iEle2).chargedHadronIso + electrons.at(iEle2).neutralHadronIso + electrons.at(iEle2).photonIso) * 1.0 / lep2_pt;
        }
        if (selectionYear_ == "2012") {
          lep1_iso = ( electrons.at(iEle1).chargedHadronIso + std::max(0.0, electrons.at(iEle1).neutralHadronIso + electrons.at(iEle1).photonIso - electrons.at(iEle1).AEffDr03*electrons.at(iEle1).rhoPrime) ) * 1.0 /lep1_pt;
          lep2_iso = ( electrons.at(iEle2).chargedHadronIso + std::max(0.0, electrons.at(iEle2).neutralHadronIso + electrons.at(iEle2).photonIso - electrons.at(iEle2).AEffDr03*electrons.at(iEle2).rhoPrime) ) * 1.0 /lep2_pt;
        }

	    lep_vect1.SetPxPyPzE(electrons.at(iEle1).px, electrons.at(iEle1).py, electrons.at(iEle1).pz, electrons.at(iEle1).energy);
	    lep_vect2.SetPxPyPzE(electrons.at(iEle2).px, electrons.at(iEle2).py, electrons.at(iEle2).pz, electrons.at(iEle2).energy);
        lep_vect1_transverse.SetPxPyPzE(electrons.at(iEle1).px, electrons.at(iEle1).py, 0.0, sqrt(pow(electrons.at(iEle1).energy,2) - pow(electrons.at(iEle1).pz,2)));
	    lep_vect2_transverse.SetPxPyPzE(electrons.at(iEle2).px, electrons.at(iEle2).py, 0.0, sqrt(pow(electrons.at(iEle2).energy,2) - pow(electrons.at(iEle2).pz,2)));

        lep2NumTrackHits = electrons.at(iEle2).tkNumValidHits;
        lep2NumPixelHits = electrons.at(iEle2).numberOfValidPixelBarrelHits + electrons.at(iEle2).numberOfValidPixelEndcapHits;
        lep2NumberOfMatches = electrons.at(iEle2).numClusters;
        lep2Chi2 = electrons.at(iEle2).tkNormChi2;
        lep2NumExpectedHits = electrons.at(iEle2).numberOfExpectedInnerHits;
	  }
	  
	  int iMuon = -10 ;
	  int iEle = -10 ;
	  if( oneEleOneMuon || TightEleLooseMuon || TightMuonLooseEle){
	    if ( oneEleOneMuon ){
	      iMuon = tight_mu_index[0] ;
	      iEle = tight_ele_index[0] ;
          lep1SF = tightMuonSF[0];
          lep2SF = tightElectronSF[0];
          
	    }  
	    if ( TightEleLooseMuon ){
	      iMuon = loose_mu_index[0] ;
	      iEle = tight_ele_index[0] ;
          lep1SF = looseMuonSF[0];
          lep2SF = tightElectronSF[0];
	    }
	    if( TightMuonLooseEle ){
	      iMuon = tight_mu_index[0] ;
	      iEle = loose_ele_index[0] ;
          lep1SF = tightMuonSF[0];
          lep2SF = looseElectronSF[0];
	    }

	    lep1_pt = muons.at(iMuon).pt;
	    lep2_pt = electrons.at(iEle).pt;
	    
	    lep1_et = muons.at(iMuon).et;
	    lep2_et = electrons.at(iEle).et;  

	    lep1_eta = muons.at(iMuon).eta;
	    lep2_eta = electrons.at(iEle).eta;  

	    lep1_phi = muons.at(iMuon).phi;
	    lep2_phi = electrons.at(iEle).phi;  

        lep1_tkDZ = muons.at(iMuon).tkDZ;
        lep2_tkDZ = electrons.at(iEle).tkDZ;

        lep1_correctedDZ = muons.at(iMuon).correctedDZ;
        lep2_correctedDZ = electrons.at(iEle).correctedDZ;

        lep1_correctedD0 = muons.at(iMuon).correctedD0;
        lep2_correctedD0 = electrons.at(iEle).correctedD0;
        
        lep1TkCharge = muons.at(iMuon).tkCharge;
        lep2TkCharge = electrons.at(iEle).tkCharge;

        for (int ii=0; ii<int(muon_px.size()); ii++) {
          if (abs(muons.at(iMuon).px-muon_px[ii])/max(abs(muons.at(iMuon).px),10.0) < 0.3 && abs(muons.at(iMuon).py-muon_py[ii])/max(abs(muons.at(iMuon).py),10.0) < 0.3 && abs(muons.at(iMuon).pz-muon_pz[ii])/max(abs(muons.at(iMuon).pz),10.0) < 0.3) {
            lep1Mother = muon_mother[ii];
            lep1Grandmother = muon_grandmother[ii];
          }
        }
        for (int jj=0; jj<int(ele_px.size()); jj++) {
          if (abs(electrons.at(iEle).px-ele_px[jj])/max(abs(electrons.at(iEle).px),10.0) < 0.3 && abs(electrons.at(iEle).py-ele_py[jj])/max(abs(electrons.at(iEle).py),10.0) < 0.3 && abs(electrons.at(iEle).pz-ele_pz[jj])/max(abs(electrons.at(iEle).pz),10.0) < 0.3) {
            lep2Mother = ele_mother[jj];
            lep2Grandmother = ele_grandmother[jj];
          }
        }

        lep1GenCharge = muons.at(iMuon).genCharge;
        lep2GenCharge = electrons.at(iEle).genCharge;

        lep1GenMotherId = muons.at(iMuon).genMotherId;
        lep2GenMotherId = electrons.at(iEle).genMotherId;

        if (selectionYear_ == "2011") {
          lep1_iso = (muons.at(iMuon).chargedHadronIso + muons.at(iMuon).neutralHadronIso + muons.at(iMuon).photonIso) * 1.0 / lep1_pt;
          lep2_iso = (electrons.at(iEle).chargedHadronIso + electrons.at(iEle).neutralHadronIso + electrons.at(iEle).photonIso) * 1.0 / lep2_pt;
        }
        if (selectionYear_ == "2012") {
          lep1_iso = (muons.at(iMuon).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon).pfIsoR04SumNeutralHadronEt + muons.at(iMuon).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon).pfIsoR04SumPUPt)) * 1.0 /lep1_pt;
          lep2_iso = ( electrons.at(iEle).chargedHadronIso + std::max(0.0, electrons.at(iEle).neutralHadronIso + electrons.at(iEle).photonIso - electrons.at(iEle).AEffDr03*electrons.at(iEle).rhoPrime) ) * 1.0 /lep2_pt;
        }

	    lep_vect1.SetPxPyPzE(muons.at(iMuon).px, muons.at(iMuon).py, muons.at(iMuon).pz, muons.at(iMuon).energy);
	    lep_vect2.SetPxPyPzE(electrons.at(iEle).px, electrons.at(iEle).py, electrons.at(iEle).pz, electrons.at(iEle).energy);
        lep_vect1_transverse.SetPxPyPzE(muons.at(iMuon).px, muons.at(iMuon).py, 0.0, sqrt(pow(muons.at(iMuon).energy,2) - pow(muons.at(iMuon).pz,2)));
	    lep_vect2_transverse.SetPxPyPzE(electrons.at(iEle).px, electrons.at(iEle).py, 0.0, sqrt(pow(electrons.at(iEle).energy,2) - pow(electrons.at(iEle).pz,2)));

	  }


      float lepTotalSF = lep1SF * lep2SF;
      
      
      if (verbose) std::cout << "about to fill two lep vars " <<std::endl
                             << "TwoMuon = " << passTwoMuon << " twoTightMuon = " << twoTightMuon << " TightMuonLooseMuon = " << TightMuonLooseMuon   << endl
                             << "TwoEle = " << passTwoEle  << " twoTightEle = " << twoTightEle << " TightEleLooseEle  " << TightEleLooseEle << endl
                             << "MuonEle = " << passMuonEle << " TightMuonLooseEle = " << TightMuonLooseEle << " TightEleLooseMuon = " << TightEleLooseMuon << " oneEleOneMuon = " << endl
                             << "lep1SF = " << lep1SF << " lep2SF = " << lep2SF   << " lepTotalSF = " << lepTotalSF
                             << endl;
        
        


      
      
	  // two leptons
	  TLorentzVector two_lepton = lep_vect1 + lep_vect2;
      TLorentzVector met_lep1 = metV + lep_vect1_transverse;
      TLorentzVector met_lep2 = metV + lep_vect2_transverse;

      float mass_met_lep1_transverse = met_lep1.M();
      float mass_met_lep2_transverse = met_lep2.M();
      float dPhi_met_lep1 = lep_vect1.DeltaPhi(metV);
      float dPhi_met_lep2 = lep_vect2.DeltaPhi(metV);
	  float dilep_mass = two_lepton.M();
	  float dilep_pt = two_lepton.Pt();
	  float dPhi_dilep = lep_vect1.DeltaPhi(lep_vect2);
	  float dR_dilep = lep_vect1.DeltaR(lep_vect2);
      float dEta_dilep = lep_vect1.Eta() - lep_vect2.Eta();
      float correctedDZ_dilep = lep1_correctedDZ - lep2_correctedDZ;
      float correctedD0_dilep = lep1_correctedD0 - lep2_correctedD0;
      float tkDZ_dilep = lep1_tkDZ - lep2_tkDZ;

      int oppositeLepCharge = -1;
      int oppositeGenLepCharge = -1;
      // check to see if the product is negative
      // it can only be negative if the charges
      // have opposite signs
      if ((lep1TkCharge * lep2TkCharge) == -1) {
        oppositeLepCharge = 1;
      } else if ((lep1TkCharge * lep2TkCharge) == 1) {
        oppositeLepCharge = 0;
      } else if (fabs(lep2TkCharge) == 99) {
        oppositeLepCharge = -1;
      } else if (fabs(lep1TkCharge) == 99) {
        oppositeLepCharge = -2;
      }
      else std::cout << "Lep1 has charge " << lep1TkCharge << " and Lep2 has charge " << lep2TkCharge << std::endl;

      if ((lep1GenCharge * lep2GenCharge) == -1) {
        oppositeGenLepCharge = 1;
      } else if ((lep1GenCharge * lep2GenCharge) == 1) {
        oppositeGenLepCharge = 0;
      } else if (fabs(lep2GenCharge) == 99) {
        oppositeGenLepCharge = -1;
      } else if (fabs(lep1GenCharge) == 99) {
        oppositeGenLepCharge = -2;
      }
      else std::cout << "Lep1 has charge " << lep1GenCharge << " and Lep2 has charge " << lep2GenCharge << std::endl;

          
	  *(floatBranches["MT_met_lep1"]) = mass_met_lep1_transverse;
	  *(floatBranches["MT_met_lep2"]) = mass_met_lep2_transverse;
	  *(floatBranches["dPhi_met_lep1"]) = dPhi_met_lep1;
	  *(floatBranches["dPhi_met_lep2"]) = dPhi_met_lep2;
	  *(floatBranches["mass_leplep"]) = dilep_mass;
	  *(floatBranches["pt_leplep"]) = dilep_pt;
	  *(floatBranches["dPhi_leplep"]) = dPhi_dilep;
      *(floatBranches["dEta_leplep"]) = dEta_dilep;
	  *(floatBranches["dR_leplep"]) = dR_dilep;
      *(floatBranches["correctedDZ_leplep"]) = correctedDZ_dilep;
      *(floatBranches["correctedD0_leplep"]) = correctedD0_dilep;
      *(floatBranches["tkDZ_leplep"]) = tkDZ_dilep;

	  *(floatBranches["lep1Pt"]) =  lep1_pt;
	  *(floatBranches["lep2Pt"]) =  lep2_pt;
	  *(floatBranches["lep1Eta"]) = lep1_eta;
	  *(floatBranches["lep2Eta"]) = lep2_eta;
	  *(floatBranches["lep1Phi"]) = lep1_phi;
	  *(floatBranches["lep2Phi"]) = lep2_phi;
	  *(floatBranches["lep1Iso"]) = lep1_iso;
	  *(floatBranches["lep2Iso"]) = lep2_iso;

      *(floatBranches["lep1SF"]) = lep1SF;
      *(floatBranches["lep2SF"]) = lep2SF;
      *(floatBranches["lepTotalSF"]) = lepTotalSF;
      

      //*(floatBranches["higgs_pt"]) = higgs_pt;
      //*(floatBranches["higgs_pz"]) = higgs_pz;
      //*(floatBranches["top1_pt"]) = top1_pt;
      //*(floatBranches["top1_pz"]) = top1_pz;
      *(floatBranches["lep1TkCharge"]) = lep1TkCharge;
      *(floatBranches["lep2TkCharge"]) = lep2TkCharge;
      *(floatBranches["lep1GenCharge"]) = lep1GenCharge;
      *(floatBranches["lep2GenCharge"]) = lep2GenCharge;
      *(intBranches["lep1GenMotherId"]) = lep1GenMotherId;
      *(intBranches["lep2GenMotherId"]) = lep2GenMotherId;
//       *(intBranches["lep1Mother"]) = lep1Mother;
//       *(intBranches["lep2Mother"]) = lep2Mother;
//       *(intBranches["lep1Grandmother"]) = lep1Grandmother;
//       *(intBranches["lep2Grandmother"]) = lep2Grandmother;
      
//       *(intBranches["lep2IsGlobalMuon"]) = lep2IsGlobalMuon;
//       *(intBranches["lep2IsTrackerMuon"]) = lep2IsTrackerMuon;
//       *(intBranches["lep2IsGlobalMuonPromptTight"]) = lep2IsGlobalMuonPromptTight;
//       *(intBranches["lep2NumTrackHits"]) = lep2NumTrackHits;
//       *(intBranches["lep2NumPixelHits"]) = lep2NumPixelHits;
//       *(intBranches["lep2NumberOfMatches"]) = lep2NumberOfMatches;
//       *(floatBranches["lep2Chi2"]) = lep2Chi2;
//       *(intBranches["lep2NumExpectedHits"]) = lep2NumExpectedHits;
      *(intBranches["oppositeLepCharge"]) = oppositeLepCharge;
      *(intBranches["oppositeGenLepCharge"]) = oppositeGenLepCharge;

	  sum_pt += lep1_pt;
	  Ht += lep1_et ;

	  sum_pt += lep2_pt;
	  Ht += lep2_et ;
	  
	  TLorentzVector everything_vect = metV + lep_vect1 + lep_vect2 + sum_jet_vect;
      TLorentzVector leps_and_jets_vect = lep_vect1 + lep_vect2 + sum_jet_vect;
      TLorentzVector leps_and_allJets_vect = lep_vect1 + lep_vect2 + sum_allJet_vect;
      TLorentzVector total_everything_vect = leps_and_allJets_vect + metV;
      float mass_of_everything = everything_vect.M();
      float mass_MHT = leps_and_jets_vect.M();
      float mass_of_leps_and_allJets = leps_and_allJets_vect.M();
      float pt_of_everything = everything_vect.Pt();
      float MHT = leps_and_jets_vect.Pt();
      float pt_of_leps_and_allJets = leps_and_allJets_vect.Pt();
      float total_pt = total_everything_vect.Pt();

	  *(floatBranches["mass_of_everything"]) = mass_of_everything;	  
      *(floatBranches["mass_MHT"]) = mass_MHT;
//       *(floatBranches["mass_of_leps_and_allJets"]) = mass_of_leps_and_allJets;
	  *(floatBranches["pt_of_everything"]) = pt_of_everything;
      *(floatBranches["MHT"]) = MHT;
//       *(floatBranches["pt_of_leps_and_allJets"]) = pt_of_leps_and_allJets;
//       *(floatBranches["pt_total"]) = total_pt;

      /// pt of ttbar
      if(numTag>1){
        float pt_of_ttbar = 0. ;

        int bjet1 = tag_pfjet_index[0] ;
        int bjet2 = tag_pfjet_index[1] ;

        TLorentzVector bjet1_vect;
        TLorentzVector bjet2_vect;

        bjet1_vect.SetPxPyPzE(jet_px[bjet1],jet_py[bjet1],jet_pz[bjet1],jet_energy[bjet1]);
        bjet2_vect.SetPxPyPzE(jet_px[bjet2],jet_py[bjet2],jet_pz[bjet2],jet_energy[bjet2]);

        TLorentzVector ttbar_vect = metV + lep_vect1 + lep_vect2 + bjet1_vect + bjet2_vect;
        pt_of_ttbar = ttbar_vect.Pt();
        
        *(floatBranches["pt_of_ttbar"]) = pt_of_ttbar;
      } 

	  ///loop jet

      for (int i=0; i<numGoodAndBadJets; i++) {
        allJet_vect.SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
        if (HtoBB == 1) {
          if (min_dr_genB1_allJet != -10.0 && higgsGenBV[0].DeltaR(allJet_vect) < min_dr_genB1_allJet) {
            min_dr_genB1_allJet = higgsGenBV[0].DeltaR(allJet_vect);
          }
          if (min_dr_genB2_allJet != -10.0 && higgsGenBV[1].DeltaR(allJet_vect) < min_dr_genB2_allJet) {
            min_dr_genB2_allJet = higgsGenBV[1].DeltaR(allJet_vect);
          }
        }
        
	    if (i==0)  first_allJet_pt = jet_pt[i];
	    if (i==1)  second_allJet_pt = jet_pt[i];
	    if (i==2)  third_allJet_pt = jet_pt[i];
	    if (i==3)  fourth_allJet_pt = jet_pt[i];
        
	    if (min_allJet_lep1_dR > lep_vect1.DeltaR(allJet_vect)){
	      min_allJet_lep1_dR = lep_vect1.DeltaR(allJet_vect); 
	    }
	    
	    if (min_allJet_lep2_dR > lep_vect2.DeltaR(allJet_vect)){
	      min_allJet_lep2_dR = lep_vect2.DeltaR(allJet_vect); 
	    }
        for (int j=i+1; j < numGoodAndBadJets; j++) {
          sum_higgsLike_allDijet_vect = allJetV[i] + allJetV[j];
          higgsLike_allDijet_mass2 = sum_higgsLike_allDijet_vect.M();
          if (pfjets.at(i).btagCombinedSecVertex > 0.679 || pfjets.at(j).btagCombinedSecVertex > 0.679) {
            if (fabs(110 - higgsLike_allDijet_mass1) > fabs(110 - higgsLike_allDijet_mass2) || higgsLike_allDijet_mass1 == -10.0) {
              higgsLike_allDijet_mass1 = higgsLike_allDijet_mass2;
            }
          }
          if (pfjets.at(i).btagCombinedSecVertex <= 0.679 && pfjets.at(j).btagCombinedSecVertex <= 0.679) {
            if (fabs(75 - wLike_allDijet_mass1) > fabs(75 - higgsLike_allDijet_mass2) || wLike_allDijet_mass1 == -10.0) {
              wLike_allDijet_mass1 = higgsLike_allDijet_mass2;
            }
          }
          for (int k=j+1; k < numGoodAndBadJets; k++) {
            sum_topLike_allTrijet_vect = allJetV[i] + allJetV[j] + allJetV[k];
            topLike_allTrijet_mass2 = sum_topLike_allTrijet_vect.M();
            if ((pfjets.at(i).btagCombinedSecVertex <= 0.679 && pfjets.at(j).btagCombinedSecVertex <= 0.679) || (pfjets.at(i).btagCombinedSecVertex <= 0.679 && pfjets.at(k).btagCombinedSecVertex <= 0.679) || (pfjets.at(j).btagCombinedSecVertex <= 0.679 && pfjets.at(k).btagCombinedSecVertex <= 0.679)) {
              if (fabs(160 - topLike_allTrijet_mass1) > fabs(160 - topLike_allTrijet_mass2) || topLike_allTrijet_mass1 == -10.0) {
                topLike_allTrijet_mass1 = topLike_allTrijet_mass2;
              }
            }
          }
          
        }
      }

        

	  for (int i=0; i < numGoodJets; i++) {
	    int iJet = tight_pfjet_index[i] ;
	    sum_pt += jet_pt[iJet];
        sum_jet_pt += jet_pt[iJet];
	    Ht += jet_energy[iJet];
        double iJet_csvVal = good_jet_tag[i];
        sum_jet_CHEF += jet_CHEF[iJet];
        sum_jet_charge += jet_charge[iJet];
	    
	    jet_vect.SetPxPyPzE(jet_px[iJet],jet_py[iJet],jet_pz[iJet],jet_energy[iJet]);

        for (int j=i+1; j < numGoodJets; j++) {
          sum_higgsLike_dijet_vect = jetV[i] + jetV[j];
          higgsLike_dijet_mass2 = sum_higgsLike_dijet_vect.M();
          if (pfjets.at(iJet).btagCombinedSecVertex > 0.679 || pfjets.at(tight_pfjet_index[j]).btagCombinedSecVertex > 0.679) {
            if (fabs(110 - higgsLike_dijet_mass1) > fabs(110 - higgsLike_dijet_mass2) || higgsLike_dijet_mass1 == -10.0) {
              higgsLike_dijet_mass1 = higgsLike_dijet_mass2;
            }
          }
          if (pfjets.at(iJet).btagCombinedSecVertex <= 0.679 && pfjets.at(tight_pfjet_index[j]).btagCombinedSecVertex <= 0.679) {
            if (fabs(75 - wLike_dijet_mass1) > fabs(75 - higgsLike_dijet_mass2) || wLike_dijet_mass1 == -10.0) {
              wLike_dijet_mass1 = higgsLike_dijet_mass2;
            }
          }
          for (int k=j+1; k < numGoodJets; k++) {
            sum_topLike_trijet_vect = jetV[i] + jetV[j] + jetV[k];
            topLike_trijet_mass2 = sum_topLike_trijet_vect.M();
            if ((pfjets.at(iJet).btagCombinedSecVertex <= 0.679 && pfjets.at(tight_pfjet_index[j]).btagCombinedSecVertex <= 0.679) || (pfjets.at(iJet).btagCombinedSecVertex <= 0.679 && pfjets.at(tight_pfjet_index[k]).btagCombinedSecVertex <= 0.679) || (pfjets.at(tight_pfjet_index[j]).btagCombinedSecVertex <= 0.679 && pfjets.at(tight_pfjet_index[k]).btagCombinedSecVertex <= 0.679)) {
              if (fabs(160 - topLike_trijet_mass1) > fabs(160 - topLike_trijet_mass2) || topLike_trijet_mass1 == -10.0) {
                topLike_trijet_mass1 = topLike_trijet_mass2;
              }
            }
          }
        }
        
	    if (i==0)  {        
          first_jet_pt = jet_pt[iJet];
          first_jet_eta = jet_vect.Eta();
          first_jet_CHEF = jet_CHEF[iJet];
          first_jet_charge = jet_charge[iJet];          
        }
	    if (i==1)  {
          second_jet_pt = jet_pt[iJet];
          second_jet_eta = jet_vect.Eta();
          second_jet_CHEF = jet_CHEF[iJet];
          second_jet_charge = jet_charge[iJet];
        }
	    if (i==2)  {
          third_jet_pt = jet_pt[iJet];
          third_jet_eta = jet_vect.Eta();
          third_jet_CHEF = jet_CHEF[iJet];
          third_jet_charge = jet_charge[iJet];
        }
	    if (i==3)  {
          fourth_jet_pt = jet_pt[iJet];
          fourth_jet_eta = jet_vect.Eta();
          fourth_jet_CHEF = jet_CHEF[iJet];
          fourth_jet_charge = jet_charge[iJet];
        }
	    
	    if (min_jet_lep1_dR > lep_vect1.DeltaR(jet_vect)){
	      min_jet_lep1_dR = lep_vect1.DeltaR(jet_vect); 
	    }
	    
	    if (min_jet_lep2_dR > lep_vect2.DeltaR(jet_vect)){
	      min_jet_lep2_dR = lep_vect2.DeltaR(jet_vect); 
	    }
	    
	    if (iJet_csvVal > 0.679){
	      avg_btag_disc_btags += iJet_csvVal;
	    }
	    
	    if (iJet_csvVal <= 0.679){
	      avg_btag_disc_non_btags += iJet_csvVal;
          highest_btag_disc_non_btags = std::max(highest_btag_disc_non_btags,iJet_csvVal);
	    }									
	  }
	  
	  *(floatBranches["first_jet_pt"]) = first_jet_pt;
	  *(floatBranches["second_jet_pt"]) = second_jet_pt;
	  *(floatBranches["third_jet_pt"]) = third_jet_pt;
	  *(floatBranches["fourth_jet_pt"]) = fourth_jet_pt;

      *(floatBranches["first_jet_eta"]) = first_jet_eta;
      *(floatBranches["second_jet_eta"]) = second_jet_eta;
      *(floatBranches["third_jet_eta"]) = third_jet_eta;
      *(floatBranches["fourth_jet_eta"]) = fourth_jet_eta;

      *(floatBranches["first_jet_CHEF"]) = first_jet_CHEF;
      *(floatBranches["second_jet_CHEF"]) = second_jet_CHEF;
      *(floatBranches["third_jet_CHEF"]) = third_jet_CHEF;
      *(floatBranches["fourth_jet_CHEF"]) = fourth_jet_CHEF;
      *(floatBranches["sum_jet_CHEF"]) = sum_jet_CHEF;

      *(floatBranches["first_jet_charge"]) = first_jet_charge;
      *(floatBranches["second_jet_charge"]) = second_jet_charge;
      *(floatBranches["third_jet_charge"]) = third_jet_charge;
      *(floatBranches["fourth_jet_charge"]) = fourth_jet_charge;
      *(floatBranches["sum_jet_charge"]) = sum_jet_charge;

//       *(floatBranches["dPhi_jet1jet2"]) = dPhi_jet1jet2;
//       *(floatBranches["dPhi_jet1jet3"]) = dPhi_jet1jet3;
//       *(floatBranches["dPhi_jet1jet4"]) = dPhi_jet1jet4;
//       *(floatBranches["dPhi_jet2jet3"]) = dPhi_jet2jet3;
//       *(floatBranches["dPhi_jet2jet4"]) = dPhi_jet2jet4;
//       *(floatBranches["dPhi_jet3jet4"]) = dPhi_jet3jet4;
//       *(floatBranches["first_allJet_pt"]) = first_allJet_pt;
// 	  *(floatBranches["second_allJet_pt"]) = second_allJet_pt;
// 	  *(floatBranches["third_allJet_pt"]) = third_allJet_pt;
// 	  *(floatBranches["fourth_allJet_pt"]) = fourth_allJet_pt;

      //*(floatBranches["min_dr_genB1_allJet"]) = min_dr_genB1_allJet;
      //*(floatBranches["min_dr_genB2_allJet"]) = min_dr_genB2_allJet;
      
	  float mindr_lep1_jet = min_jet_lep1_dR;
	  float mindr_lep2_jet = min_jet_lep2_dR;
	  float mindr_lep1_allJet = min_allJet_lep1_dR;
	  float mindr_lep2_allJet = min_allJet_lep2_dR;
	  *(floatBranches["mindr_lep1_jet"]) = mindr_lep1_jet;
	  *(floatBranches["mindr_lep2_jet"]) = mindr_lep2_jet;
// 	  *(floatBranches["mindr_lep1_allJet"]) = mindr_lep1_allJet;
// 	  *(floatBranches["mindr_lep2_allJet"]) = mindr_lep2_allJet;
	  
	  if ( numTag > 0 ) avg_btag_disc_btags /= numTag;
	  
	  if ((numGoodJets - numTag) != 0){
	    avg_btag_disc_non_btags /= (numGoodJets - numTag);
	  }
	  
	  for (int l=0; l < numTag; l++){
        dev_from_avg_disc_btags += pow((tag_pfjet_csvVal[l] - avg_btag_disc_btags),2);
	  }
	  if ( numTag > 0 ) dev_from_avg_disc_btags /= numTag;

	  *(floatBranches["avg_btag_disc_btags"]) = avg_btag_disc_btags;
	  *(floatBranches["avg_btag_disc_non_btags"]) = avg_btag_disc_non_btags;
	  *(floatBranches["highest_btag_disc_non_btags"]) = highest_btag_disc_non_btags;
	  *(floatBranches["dev_from_avg_disc_btags"]) = dev_from_avg_disc_btags;

	  /////
	  all_sum_pt = sum_pt + MHT;
	  Ht += MHT;

	  *(floatBranches["numPV"]) = numpv ;
	  *(floatBranches["weight"]) = wgt ;
	  *(floatBranches["weight_PUup"]) = PUwgt_up ;
	  *(floatBranches["weight_PUdown"]) = PUwgt_down ;
	  *(floatBranches["met"]) = met;
	  *(floatBranches["unc_met"]) = unc_met;

      *(floatBranches["sum_jet_pt"]) = sum_jet_pt;
	  *(floatBranches["sum_pt"]) = sum_pt;
// 	  *(floatBranches["all_sum_pt"]) = all_sum_pt;
	  *(floatBranches["Ht"]) = Ht;

      /// Ht re-weighting
      float HtWgt = 1.0 ;
      float HtWgtUp = 1.0 ;

      if (!isData){
        if (numpv<11)  HtWgt = h_rwt_lowPV->GetBinContent(h_rwt_lowPV->FindBin(sum_jet_pt));
        else if (10<numpv && numpv<16)  HtWgt = h_rwt_medPV->GetBinContent(h_rwt_medPV->FindBin(sum_jet_pt));
        else   HtWgt = h_rwt_highPV->GetBinContent(h_rwt_highPV->FindBin(sum_jet_pt));

        HtWgtUp = 1 + 2*(HtWgt - 1);
      }

      *(floatBranches["HtWgt"]) = HtWgt;
      *(floatBranches["HtWgtUp"]) = HtWgtUp;

      bool passBigDiamondZmask = (passMuonEle || (dilep_mass < (65.5 + 3*MHT/8)) || (dilep_mass > (108 - MHT/4)) || (dilep_mass < (79 - 3*MHT/4)) || (dilep_mass > (99 + MHT/2)) );
      bool passBigDiamondZmask2 = (dilep_mass < (65.5 + 3*met/8)) || (dilep_mass > (108 - met/4)) || (dilep_mass < (79 - 3*met/4)) || (dilep_mass > (99 + met/2));
      bool passBigDiamondZmask3 = (dilep_mass < (65.5 + 3*pt_of_leps_and_allJets/8)) || (dilep_mass > (108 - pt_of_leps_and_allJets/4)) || (pt_of_leps_and_allJets < (79 - 3*pt_of_leps_and_allJets/4)) || (dilep_mass > (99 + pt_of_leps_and_allJets/2));
      *(intBranches["PassZmask"]) = passBigDiamondZmask ? 1 : 0;
      *(intBranches["PassZmask2"]) = passBigDiamondZmask2 ? 1 : 0;
      *(intBranches["PassZmask3"]) = passBigDiamondZmask3 ? 1 : 0;

	  //// tagged jets
	  float deltaHMass = 9999. ;
	  float deltaHMass2 = 9999. ;
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

		//////// ttbb bkg
		dibjet_mass_combinations.push_back(dijet_vect.M()); 
		float deltaHMassTemp = abs(120 - dijet_vect.M());
		if (deltaHMassTemp < deltaHMass) {
		  deltaHMass = deltaHMassTemp ;
		  m2H_btag = dijet_vect.M() ;
		}
		
	      }
	    }
	    
	    avg_tagged_dijet_mass /= denom_avg_cnt; 
	    avg_dr_tagged_jets /= denom_avg_cnt;
	    
	    min_dr_tagged_jets = min_tagged_jets_dR;


	    ///// ttbb bkg
	    *(floatBranches["m2H_btag"]) = m2H_btag;

	    dibjet_mass_combinations.sort();
	    std::vector<float> dibjet_mass_sort_vect;
	    std::list<float>::iterator listintaa;
	    for (listintaa = dibjet_mass_combinations.begin(); listintaa != dibjet_mass_combinations.end(); listintaa++){
	      dibjet_mass_sort_vect.push_back(*listintaa);  //accessible form
	    }
	    int numCom = dibjet_mass_sort_vect.size();
	    if (numCom > 2) {
	      first_dibjet_mass  = dibjet_mass_sort_vect[numCom - 1];
	      second_dibjet_mass = dibjet_mass_sort_vect[numCom - 2];
	      third_dibjet_mass  = dibjet_mass_sort_vect[numCom - 3];

	      *(floatBranches["first_dibjet_mass"]) =  first_dibjet_mass;
	      *(floatBranches["second_dibjet_mass"]) = second_dibjet_mass;
	      *(floatBranches["third_dibjet_mass"]) =  third_dibjet_mass;
	    }

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

	  
	  ///// ttbb dijet_mass
	  denom_avg_cnt = 0.;
	  if(numJet > 1 ){
	    for (int j=0; j < (numJet - 1); j++) {
	      int jJet = tight_pfjet_index[j] ;
	      jet_vect1.SetPxPyPzE(jet_px[jJet],jet_py[jJet],jet_pz[jJet],jet_energy[jJet]);
	      
	      for (int k=j+1; k < numJet; k++) {
		int kJet = tight_pfjet_index[k] ; 
		jet_vect2.SetPxPyPzE(jet_px[kJet],jet_py[kJet],jet_pz[kJet],jet_energy[kJet]);
		
		dijet_vect = jet_vect1 + jet_vect2;
		avg_dijet_mass += dijet_vect.M();
		avg_dr_jets += jet_vect1.DeltaR(jet_vect2);
		++denom_avg_cnt;		      
		
		if (min_jets_dR > jet_vect1.DeltaR(jet_vect2)){
		  min_jets_dR = jet_vect1.DeltaR(jet_vect2);
		  M2_of_closest_jets = dijet_vect.M2();	
		  closest_dijet_mass = dijet_vect.M();			
		}

		//////// ttbb bkg
		dijet_mass_combinations.push_back(dijet_vect.M()); 
		float deltaHMassTemp2 = abs(120 - dijet_vect.M());
		if (deltaHMassTemp2 < deltaHMass2) {
		  deltaHMass2 = deltaHMassTemp2 ;
		  dijet_mass_m2H = dijet_vect.M() ;
		}
		
	      }
	    }

	    avg_dijet_mass /= denom_avg_cnt; 
	    avg_dr_jets /= denom_avg_cnt;
	    
	    min_dr_jets = min_jets_dR;

	    *(floatBranches["min_dr_jets"]) = min_dr_jets;
	    *(floatBranches["avg_dr_jets"]) = avg_dr_jets;
	    *(floatBranches["avg_dijet_mass"]) = avg_dijet_mass;
	    *(floatBranches["closest_dijet_mass"]) = closest_dijet_mass;
	    *(floatBranches["M2_of_closest_jets"]) = M2_of_closest_jets;

	    *(floatBranches["dijet_mass_m2H"]) = dijet_mass_m2H;

	    dijet_mass_combinations.sort();
	    std::vector<float> dijet_mass_sort_vect; 
	    std::list<float>::iterator listintbb;
	    for (listintbb = dijet_mass_combinations.begin(); listintbb != dijet_mass_combinations.end(); listintbb++){
	      dijet_mass_sort_vect.push_back(*listintbb);  //accessible form
	    }
	    int numCom = dijet_mass_sort_vect.size();
	    if (numCom > 2) {
	      dijet_mass_first  = dijet_mass_sort_vect[numCom - 1];
	      dijet_mass_second = dijet_mass_sort_vect[numCom - 2];
	      dijet_mass_third  = dijet_mass_sort_vect[numCom - 3];

	      *(floatBranches["dijet_mass_first"]) =  dijet_mass_first;
	      *(floatBranches["dijet_mass_second"]) = dijet_mass_second;
	      *(floatBranches["dijet_mass_third"]) =  dijet_mass_third;
	    }

	  }

	  ////
      //*(floatBranches["higgs_dijet_mass"]) = higgs_dijet_mass;
      *(floatBranches["higgsLike_dijet_mass"]) = higgsLike_dijet_mass1;
//       *(floatBranches["higgsLike_allDijet_mass"]) = higgsLike_allDijet_mass1;
//       *(floatBranches["wLike_dijet_mass"]) = wLike_dijet_mass1;
//       *(floatBranches["wLike_allDijet_mass"]) = wLike_allDijet_mass1;
//       *(floatBranches["topLike_trijet_mass"]) = topLike_trijet_mass1;
//       *(floatBranches["topLike_allTrijet_mass"]) = topLike_allTrijet_mass1;
      //*(floatBranches["higgs_genJet_mass"]) = higgs_genJet_mass;
      //*(floatBranches["higgs_genParton_mass"]) = higgs_genParton_mass;
      
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


      //------------------------------------------
      //
      // Assign values to the vars the MVA will use
      // 
      //------------------------------------------

      varfirst_jet_pt = first_jet_pt;
      varmin_dr_tagged_jets 		  = min_dr_tagged_jets;  
      varnumJets_float 		  = float(numJet);       
      varmindr_lep1_jet		  = mindr_lep1_jet;      
      varavg_btag_disc_btags		  = avg_btag_disc_btags; 
      varHt                              = Ht;
      
      varavg_dr_tagged_jets	         =  avg_dr_tagged_jets;
      varavg_tagged_dijet_mass       =  avg_tagged_dijet_mass;
      varsecond_dibjet_mass	        =   second_dibjet_mass;

      varavg_dijet_mass =       avg_dijet_mass;	   
      vardijet_mass_second =    dijet_mass_second; 
      varmin_dr_jets = 	      min_dr_jets; 	   
      varavg_dr_jets =          avg_dr_jets;       
      

      //      std::cout << "-->error0 " << std::endl;
      Float_t  ttbbANN = 0.;
      for( unsigned int j = 0 ; j < nCat ; ++j ){
        // --- Return the MVA outputs and weights
	TMVA::Reader  *tmpReader = reader[j];  
        TString branchName = TString("CFMlpANN_") + catList[j];
	//        cout << "This is NN category " << catList[j] << " saving into branch " << branchName << endl;
	if( j < 5){
	  Float_t annOut  = tmpReader->EvaluateMVA( "CFMlpANN method" );
	  *(floatBranches[branchName]) = annOut;  
	  if ( j==4 ) ttbbANN = annOut ;
	}
	else {
	  varCFMlpANN_var_best8 = ttbbANN ;
	  Float_t annOut1  = tmpReader->EvaluateMVA( "CFMlpANN method" );
	  *(floatBranches[branchName]) = annOut1;  

	}
      } // End category loop



      

      } // end neural net selection

      //--------------------

      if (verbose) std::cout << "about to fill tree" <<std::endl;
      
      summaryTree->Fill();
      
      

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

  histofile.Write();
  histofile.Close();

  std::cout << " Done! " << std::endl;

}


//////******************************************	
	
/// additional functions	
/////*******************************************

// double getJERfactor( int returnType, double jetAbsETA, double genjetPT, double recojetPT){

//   double factor = 1.;

//   double scale_JER = 1., scale_JERup = 1., scale_JERdown = 1.;
//   if( jetAbsETA<0.5 ){ 
//     scale_JER = 1.052; scale_JERup = 1.052 + sqrt( 0.012*0.012 + 0.062*0.062 ); scale_JERdown = 1.052 - sqrt( 0.012*0.012 + 0.061*0.061 );
//   }
//   else if( jetAbsETA<1.1 ){ 
//     scale_JER = 1.057; scale_JERup = 1.057 + sqrt( 0.012*0.012 + 0.056*0.056 ); scale_JERdown = 1.057 - sqrt( 0.012*0.012 + 0.055*0.055 );
//   }
//   else if( jetAbsETA<1.7 ){ 
//     scale_JER = 1.096; scale_JERup = 1.096 + sqrt( 0.017*0.017 + 0.063*0.063 ); scale_JERdown = 1.096 - sqrt( 0.017*0.017 + 0.062*0.062 );
//   }
//   else if( jetAbsETA<2.3 ){ 
//     scale_JER = 1.134; scale_JERup = 1.134 + sqrt( 0.035*0.035 + 0.087*0.087 ); scale_JERdown = 1.134 - sqrt( 0.035*0.035 + 0.085*0.085 );
//   }
//   else if( jetAbsETA<5.0 ){ 
//     scale_JER = 1.288; scale_JERup = 1.288 + sqrt( 0.127*0.127 + 0.155*0.155 ); scale_JERdown = 1.288 - sqrt( 0.127*0.127 + 0.153*0.153 );
//   }

//   double jetPt_JER = recojetPT;
//   double jetPt_JERup = recojetPT;
//   double jetPt_JERdown = recojetPT;

//   if( genjetPT>10. ){
//     jetPt_JER = std::max( 0., genjetPT + scale_JER * ( recojetPT - genjetPT ) );
//     jetPt_JERup = std::max( 0., genjetPT + scale_JERup * ( recojetPT - genjetPT ) );
//     jetPt_JERdown = std::max( 0., genjetPT + scale_JERdown * ( recojetPT - genjetPT ) );
//   }

//   if( returnType==1 )       factor = jetPt_JERup/recojetPT;
//   else if( returnType==-1 ) factor = jetPt_JERdown/recojetPT;
//   else                      factor = jetPt_JER/recojetPT;

//   if( !(genjetPT>10.) ) factor = 1.;

//   return factor;
// }



/////////////////////
// std::vector<double> getEffSF( int returnType, double jetPt, double jetEta, double jetId ){

//   bool getEffVerbose = false;

    
//   if (getEffVerbose) std::cout  << "getEffSF called with arguments:" << std::endl
//                                 << "   returnType = " << returnType << std::endl
//                                 << "   jetPt = " << jetPt << std::endl
//                                 << "   jetEta = " << jetEta << std::endl
//                                 << "   jetId = " << jetId << std::endl;

  
    
//   double m_type = 0.;                                                                                                            
//   if( returnType==-1 )      m_type = -1.;                                                                                        
//   else if( returnType==1 )  m_type = 1.;                                                                                         
//   else                      m_type = 0.;                                                                                         
                                                                                                                                 
//   float ptmin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500};                                              
//   float ptmax[] = {40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 670};                                              
                                                                                                                                 
//   double SFb_error[] = {                                                                                                         
//     0.0295675,                                                                                                                   
//     0.0295095,                                                                                                                   
//     0.0210867,                                                                                                                   
//     0.0219349,                                                                                                                   
//     0.0227033,                                                                                                                   
//     0.0204062,                                                                                                                   
//     0.0185857,                                                                                                                   
//     0.0256242,                                                                                                                   
//     0.0383341,                                                                                                                   
//     0.0409675,                                                                                                                   
//     0.0420284,                                                                                                                   
//     0.0541299,                                                                                                                   
//     0.0578761,                                                                                                                   
//     0.0655432 };                                                                                                                 
                                                                                                                                 
//   double pt  = jetPt;                                                                                                            
//   double eta = jetEta;                                                                                                           
//   int flavor = jetId;                                                                                                            
                                                                                                                                 
//   double threshold = 670;                                                                                                        
//   pt = ( pt>threshold ) ? threshold-0.0000001 : pt;                                                                              
                                                                                                                                 
//   double absEta = fabs(eta);                                                                                                     
                                                                                                                                 
//   int use_bin=-1;                                                                                                                
//   for( int p=0; p<14; p++ ){                                                                                                     
//     if( pt>ptmin[p] && pt<ptmax[p] ){                                                                                            
//       use_bin = p; break;                                                                                                        
//     }                                                                                                                            
//   }
//   if (getEffVerbose) std::cout  << "Use bin = " << use_bin << std::endl;
  
//   if( use_bin<0 ) if (getEffVerbose) std::cout  << "   ERROR!! use_bin < 0 " << std::endl;                                                           


//   double SFb = 0.6981*((1.+(0.414063*pt))/(1.+(0.300155*pt)));                                                                              
                                                                                                                                            
//   double SFc = SFb;                                                                                                                         

//   if (getEffVerbose) std::cout  << "Getting error" << use_bin << std::endl;
//   SFb = SFb + m_type * SFb_error[use_bin];                                                                                                  
//   SFc = SFc + m_type * 2* SFb_error[use_bin];                                                                                               

//   if (getEffVerbose) std::cout  << "switch based on return type"  << std::endl;
//   double SFl = 1.;                                                                                                                          
//   if( returnType==-2 ){ // min                                                                                                              
//     if( absEta < 0.8 )                      SFl = ((0.972455+(7.51396e-06*pt))+(4.91857e-07*(pt*pt)))+(-1.47661e-09*(pt*(pt*pt)));          
//     else if( absEta < 1.6 && absEta > 0.8 ) SFl = ((1.02055+(-0.000378856*pt))+(1.49029e-06*(pt*pt)))+(-1.74966e-09*(pt*(pt*pt)));          
//     else if( absEta < 2.4 && absEta > 1.6 ) SFl = ((0.983476+(-0.000607242*pt))+(3.17997e-06*(pt*pt)))+(-4.01242e-09*(pt*(pt*pt)));         
//   }                                                                                                                                         
//   else if( returnType==2 ){ // max                                                                                                          
//     if( absEta < 0.8 )                      SFl = ((1.15116+(0.00122657*pt))+(-3.63826e-06*(pt*pt)))+(2.08242e-09*(pt*(pt*pt)));            
//     else if( absEta < 1.6 && absEta > 0.8 ) SFl = ((1.20146+(0.000359543*pt))+(-1.12866e-06*(pt*pt)))+(6.59918e-10*(pt*(pt*pt)));           
//     else if( absEta < 2.4 && absEta > 1.6 ) SFl = ((1.18654+(-0.000795808*pt))+(3.69226e-06*(pt*pt)))+(-4.22347e-09*(pt*(pt*pt)));          
//   }                                                                                                                                         
//   else { // mean                                                                                                                            
//     if( absEta < 0.8 )                      SFl = ((1.06182+(0.000617034*pt))+(-1.5732e-06*(pt*pt)))+(3.02909e-10*(pt*(pt*pt)));            
//     else if( absEta < 1.6 && absEta > 0.8 ) SFl = ((1.111+(-9.64191e-06*pt))+(1.80811e-07*(pt*pt)))+(-5.44868e-10*(pt*(pt*pt)));            
//     else if( absEta < 2.4 && absEta > 1.6 ) SFl = ((1.08498+(-0.000701422*pt))+(3.43612e-06*(pt*pt)))+(-4.11794e-09*(pt*(pt*pt)));          
//   }                                                                                                                                         

//   double SF=1;                                                                                                                              
                                                                                                                                            
//   double tagEff=0;
//   if (getEffVerbose) std::cout  << "Calling get bin content and find bin with flavor = " << flavor  << std::endl;

  
//   if( abs(flavor)==5 ){                                                                                                                     
//     tagEff = h_jet_pt_eta_b_eff_->GetBinContent( h_jet_pt_eta_b_eff_->FindBin( pt, absEta ) );                                              
//     SF = SFb;                                                                                                                               
//   }                                                                                                                                         
//   else if( abs(flavor)==4 ){                                                                                                                
//     tagEff = h_jet_pt_eta_c_eff_->GetBinContent( h_jet_pt_eta_c_eff_->FindBin( pt, absEta ) );                                              
//     SF = SFc;                                                                                                                               
//   }                                                                                                                                         
//   else if( abs(flavor)==1 || abs(flavor)==2 || abs(flavor)==3 || abs(flavor)==21 ){                                                         
//     tagEff = h_jet_pt_eta_l_eff_->GetBinContent( h_jet_pt_eta_l_eff_->FindBin( pt, absEta ) );                                              
//     SF = SFl;                                                                                                                               
//   }                                                                                                                                         
//   else {                                                                                                                                    
//     tagEff = h_jet_pt_eta_o_eff_->GetBinContent( h_jet_pt_eta_o_eff_->FindBin( pt, absEta ) );                                              
//     SF = SFl;                                                                                                                               
//   }                                                                                                                                         

//   if (getEffVerbose) std::cout  << "    Done with get bin, creating return vector" << std::endl;
                                                                                                                                            
//   std::vector<double> result;                                                                                                               
//   result.clear();                                                                                                                           
//   result.push_back(tagEff);                                                                                                                 
//   result.push_back(SF);                                                                                                                     

//   if (getEffVerbose) std::cout  << " returning " << std::endl;
//   return result;
  
// }



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
