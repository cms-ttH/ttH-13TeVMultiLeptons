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
#include <random>
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
#include "NtupleMaker/BEANmaker/interface/BEANhelper.h"

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
typedef std::vector<float> vfloat;
typedef std::vector<std::vector<float> > vvfloat;
typedef std::vector<std::vector<std::string> > vvstring;
typedef std::vector<string> vstring;
typedef std::vector<bool> vbool;
typedef std::vector<int> vint;


// here is where you can change the btag threshold
// Medium combined tag threshold
float btagThres = 0.679;

// super loose combined tag threshold
//float btagThres = 0.244;

using namespace std;

int main ( int argc, char ** argv )
{
   // load framework libraries
   gSystem->Load( "libFWCoreFWLite" );
   gSystem->Load("libNtupleMakerBEANmaker.so");
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
   std::string selectionYearStr = anaParams.getParameter<std::string>("selectionYear");
//    int selectionYearInt = -99;
//    if (selectionYearStr == "2011") {
//      selectionYearInt = 2011;
//    }
//    else if (selectionYearStr == "2012_52x") {
//      selectionYearInt = 2012;
//    }
//    else if (selectionYearStr == "2012_53x") {
//      selectionYearInt = 2012;
//    }
//    else {
//      assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
//    } 
       
   //JES
   int jes = anaParams.getParameter<int> ("jes");
   int jer = anaParams.getParameter<int> ("jer");
   int btagCSVShape = anaParams.getParameter<int> ("btagCSVShape");
   std::string sampleName = anaParams.getParameter<string>("sampleName");
   TString tmpName = sampleName;
   std::cout <<"CONFIG: using jes = " << jes << " jer = " << jer << " btagShape = " << btagCSVShape << std::endl; 
   if (jes != 0 && jer != 0) {
     cout << "JES and JER are both non-0 ... exiting" << endl;
     exit(22);
   }   
   
   bool debug_ = false;

   //// Ht re-weighting 
   TString rwtFileName = "sum_jet_pt_rwt.root";
   if ( selectionYearStr == "2011") rwtFileName = "sum_jet_pt_rwt_2011.root"; 
   TFile *f_Ht_rwt = new TFile(rwtFileName);
   TH1F* h_rwt_lowPV = (TH1F*)f_Ht_rwt->Get("sum_jet_pt_ratio_PV0");
   TH1F* h_rwt_medPV = (TH1F*)f_Ht_rwt->Get("sum_jet_pt_ratio_PV1");
   TH1F* h_rwt_highPV = (TH1F*)f_Ht_rwt->Get("sum_jet_pt_ratio_PV2");
   
   int maxNentries = inputs.getParameter<int> ("maxEvents");

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
  std::string sysType_lep = "MC";
  if (TString(sampleName).Contains("DoubleElectron")
      || TString(sampleName).Contains("DoubleMu")
      || TString(sampleName).Contains("MuEG")
      || TString(sampleName).Contains("MET")) {

    std::cout << "CONFIG: DATA detected for sample " << sampleName << std::endl;

    isData = true;
    sysType_lep = "data";

  }

  sysType::sysType iSysTypeJE = sysType::NA;
  if (isData || (jer==0 && jes==0)) {
    iSysTypeJE = sysType::NA;
  } else if (jer == 1) {
    iSysTypeJE = sysType::JERup;
  } else if (jer == -1) {
    iSysTypeJE = sysType::JERdown;
  } else if (jes == 1) {
    iSysTypeJE = sysType::JESup;
  } else if (jes == -1) {
    iSysTypeJE = sysType::JESdown;
  }

  sysType::sysType iSysTypeCSV = sysType::NA;
  if (isData || btagCSVShape==0) {
    iSysTypeCSV = sysType::NA;
  } else if (btagCSVShape == 1) {
    iSysTypeCSV = sysType::hfSFup;
  } else if (btagCSVShape == -1) {
    iSysTypeCSV = sysType::hfSFdown;
  } else if (btagCSVShape == 2) {
    iSysTypeCSV = sysType::lfSFup;
  } else if (btagCSVShape == -2) {
    iSysTypeCSV = sysType::lfSFdown;
  }

  sysType::sysType iSysType = sysType::NA;
  if (btagCSVShape == 0) iSysType = iSysTypeJE;
  else iSysType = iSysTypeCSV;
  

  //Sample numbers may not match event->sample; used for setMCsample() only
  std::string dset = "SingleMu" ;
  int sampleNumber = 999999;

  if (selectionYearStr == "2011") {
    if (isData) sampleNumber = -1;
    else if (sampleName == "zjets" || tmpName.Contains("zjets_part")) sampleNumber = 2300; 
    else if (sampleName == "zjets_lowmass") sampleNumber = 2310; 
    else if (sampleName == "wjets") sampleNumber = 2400; 
    else if (sampleName == "ttbar" || tmpName.Contains("ttbar_part")) sampleNumber = 2500;
    else if (sampleName == "ttbar_bb" ) sampleNumber = 2555; 
    else if (sampleName == "ttbar_cc") sampleNumber = 2544; 
    else if (tmpName.Contains("scaleup_ttbar")) sampleNumber = 2510; 
    else if (tmpName.Contains("scaledown_ttbar")) sampleNumber = 2511; 
    else if (sampleName == "ttbarZ") sampleNumber = 2523; 
    else if (sampleName == "ttbarW") sampleNumber = 2524; 
    else if (tmpName.Contains("singlet")) sampleNumber = 2600; 
    else if (sampleName == "ww") sampleNumber = 2700; 
    else if (sampleName == "wz") sampleNumber = 2701; 
    else if (sampleName == "zz") sampleNumber = 2702; 
    else if (tmpName.Contains("ttH")) sampleNumber = 120;
    else assert (sampleName == "sampleName is not in the approved list");
  }
  else if (selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x") {
    if (isData) sampleNumber = -1;
    else if (sampleName == "ttbar" || tmpName.Contains("ttbar_part")) sampleNumber = 2500;
    else if (sampleName == "ttbar_bb" || tmpName.Contains("ttbar_bb_part")) sampleNumber = 2555;
    else if (sampleName == "ttbar_cc" || tmpName.Contains("ttbar_cc_part")) sampleNumber = 2544;
    else if (sampleName == "ttbar_scaleup") sampleNumber = 2511; 
    else if (sampleName == "ttbar_scaledown") sampleNumber = 2510; 
    else if (sampleName == "ttbar_matchingup") sampleNumber = 2513; 
    else if (sampleName == "ttbar_matchingdown") sampleNumber = 2512; 
    else if (sampleName == "ttbar_jj" || tmpName.Contains("ttbar_jj_part")) sampleNumber = 2500;
    else if (sampleName == "ttbar_lj" || tmpName.Contains("ttbar_lj_part")) sampleNumber = 2500;
    else if (sampleName == "ttbar_ll" || tmpName.Contains("ttbar_ll_part")) sampleNumber = 2500;
    else if (sampleName == "ttbar_cc_jj" || tmpName.Contains("ttbar_cc_jj_part")) sampleNumber = 2576;
    else if (sampleName == "ttbar_cc_lj" || tmpName.Contains("ttbar_cc_lj_part")) sampleNumber = 2573;
    else if (sampleName == "ttbar_cc_ll" || tmpName.Contains("ttbar_cc_ll_part")) sampleNumber = 2543;
    else if (sampleName == "ttbar_bb_jj" || tmpName.Contains("ttbar_bb_jj_part")) sampleNumber = 2586;
    else if (sampleName == "ttbar_bb_lj" || tmpName.Contains("ttbar_bb_lj_part")) sampleNumber = 2583;
    else if (sampleName == "ttbar_bb_ll" || tmpName.Contains("ttbar_bb_ll_part")) sampleNumber = 2553;
    else if (sampleName == "wjets" || tmpName.Contains("wjets_part")) sampleNumber = 2400; 
    else if (sampleName == "wjets_1p" || tmpName.Contains("wjets_1p_part")) sampleNumber = 2400; 
    else if (sampleName == "wjets_2p" || tmpName.Contains("wjets_2p_part")) sampleNumber = 2400; 
    else if (sampleName == "wjets_3p" || tmpName.Contains("wjets_3p_part")) sampleNumber = 2400; 
    else if (sampleName == "wjets_4p" || tmpName.Contains("wjets_4p_part")) sampleNumber = 2400; 
    else if (sampleName == "zjets_lowmass" || tmpName.Contains("zjets_lowmass_part")) sampleNumber = 2850;
    else if (sampleName == "zjets_lowmass_1p" || tmpName.Contains("zjets_lowmass_1p_part")) sampleNumber = 2851;
    else if (sampleName == "zjets_lowmass_2p" || tmpName.Contains("zjets_lowmass_2p_part")) sampleNumber = 2852;
    else if (sampleName == "zjets" || tmpName.Contains("zjets_part")) sampleNumber = 2800; 
    else if (sampleName == "zjets_1p" || tmpName.Contains("zjets_1p_part")) sampleNumber = 2801;
    else if (sampleName == "zjets_2p" || tmpName.Contains("zjets_2p_part")) sampleNumber = 2802;
    else if (sampleName == "zjets_3p" || tmpName.Contains("zjets_3p_part")) sampleNumber = 2803;
    else if (sampleName == "zjets_4p" || tmpName.Contains("zjets_4p_part")) sampleNumber = 2804;
    else if (sampleName == "singlet_s") sampleNumber = 2600; 
    else if (sampleName == "singlet_s_ll") sampleNumber = 2630; 
    else if (sampleName == "singletbar_s") sampleNumber = 2601; 
    else if (sampleName == "singletbar_s_ll") sampleNumber = 2631; 
    else if (sampleName == "singlet_t") sampleNumber = 2602; 
    else if (sampleName == "singlet_t_ll") sampleNumber = 2632; 
    else if (sampleName == "singletbar_t") sampleNumber = 2603; 
    else if (sampleName == "singletbar_t_ll") sampleNumber = 2633; 
    else if (sampleName == "singlet_tW") sampleNumber = 2604; 
    else if (sampleName == "singlet_tW_lj") sampleNumber = 2654; 
    else if (sampleName == "singlet_tW_jl") sampleNumber = 2664; 
    else if (sampleName == "singlet_tW_ll") sampleNumber = 2634; 
    else if (sampleName == "singletbar_tW") sampleNumber = 2605; 
    else if (sampleName == "singletbar_tW_lj") sampleNumber = 2555; 
    else if (sampleName == "singletbar_tW_jl") sampleNumber = 2565; 
    else if (sampleName == "singletbar_tW_ll") sampleNumber = 2535; 
    else if (sampleName == "ww") sampleNumber = 2700; 
    else if (sampleName == "www") sampleNumber = 2710; 
    else if (sampleName == "wwz") sampleNumber = 2720; 
    else if (sampleName == "wz") sampleNumber = 2701; 
    else if (sampleName == "wzz") sampleNumber = 2721; 
    else if (sampleName == "zz") sampleNumber = 2702;
    else if (sampleName == "zzz") sampleNumber = 2722; 
    else if (sampleName == "ttbarW") sampleNumber = 2524; 
    else if (sampleName == "ttbarWW") sampleNumber = 2534; 
    else if (sampleName == "ttbarZ") sampleNumber = 2523; 
    else if (sampleName == "ttbartbar") sampleNumber = 2525;
    else if (tmpName.Contains("ttH") && selectionYearStr == "2012_52x") {
      if (tmpName.Contains("FullSim")) sampleNumber = 8120;
      else sampleNumber = 9120;
    }
    else if (tmpName.Contains("ttH") && selectionYearStr == "2012_53x") {
      if (tmpName.Contains("_tautau")) sampleNumber = 7120;
      else if (tmpName.Contains("_bb")) sampleNumber = 8120;
      else sampleNumber = 9120;
    }
    else assert (sampleName == "sampleName is not in the approved list");
  }
  else {
    assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
  }
  
  BEANhelper beanHelper;
  //BEANhelper::SetUp(string iEra, int iSampleNumber, bool iIsLJ, bool iIsData, string iDataset, bool iReshapeCSV, bool iPfLeptons = true)
  if (debug_) std::cout << "BEANhelper::SetUp(string iEra, int iSampleNumber, bool iIsLJ, bool iIsData, string iDataset, bool iReshapeCSV, bool iPfLeptons = true)" << std::endl;
  if (debug_) std::cout << "beanHelper.SetUp(" << selectionYearStr << " , "
                        << sampleNumber << " , false  " << isData << " , "
                        << dset << " , true, true );" << std::endl;
  beanHelper.SetUp(selectionYearStr,sampleNumber,false,isData,dset,true,true);
  if (debug_) std::cout << "beanHelper.SetUp successful" << std::endl;
  
  // Load the files
  vstring fileNames = inputFileNames;

  if (fileNames.size() < 1 ){
    cout << "You don't have any files in your list... this is is probably bad... exiting" << endl;
    exit(22);
  }

  
  // Name of file containing histograms
  std::cout << "Writing out to file " << outputFileName << endl;


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

  
  ///////////////////////////////////////////////////////////////////
  //
  // Make a small tree called summaryTree that stores all your 
  // information event by events
  //
  ///////////////////////////////////////////////////////////////////

  bool CoreVariables = true;
  bool ExtraLeptonVariables = false;
  bool ExtraJetVariables = false;
  bool ExtraKinematicVariables = false;
  //bool ExtraEventVariables = false;
  bool ExtraTriggerVariables = false;
  bool ExtraGenVariables = false;
  bool ExtraHiggsVariables = false;
  bool ArtificialJetPt = false;
  
  std::map<TString, int *> intBranches;
  std::map<TString, unsigned int *> uintBranches;  
  std::map<TString, float *> floatBranches;

  // Core Variables
  if (CoreVariables) {

    //event variables
    intBranches["PassTwoLepton"] = new int (0);
    intBranches["TwoMuon"] = new int (0);
    intBranches["TwoEle"] = new int (0);
    intBranches["MuonEle"] = new int (0);

    intBranches["numTightMuons"] = new int (0);
    intBranches["numLooseMuons"] = new int (0);
    intBranches["numTightElectrons"] = new int (0);
    intBranches["numLooseElectrons"] = new int (0);

    intBranches["numJets"] = new int (0);
    intBranches["numTaggedJets"] = new int (0);
    floatBranches["numJets_float"] = new float (0);
    floatBranches["numTaggedJets_float"] = new float (0);

    intBranches["isCleanEvent"] = new int (0);
    intBranches["isTriggerPass"] = new int (0);
    intBranches["isDoubleMuTriggerPass"] = new int (0);
    intBranches["isDoubleElectronTriggerPass"] = new int (0);
    intBranches["isMuEGTriggerPass"] = new int (0);
    intBranches["isMETTriggerPass"] = new int (0);

    intBranches["PassZmask"] = new int (0);
    intBranches["PassZmask2"] = new int (0);
    
    intBranches["oppositeLepCharge"] = new int (0);
    intBranches["oppositeGenLepCharge"] = new int (0);

    uintBranches["runNumber"] = new unsigned int (0);
    uintBranches["eventNumber"] = new unsigned int (0);
    uintBranches["luminosityBlock"] = new unsigned int (0);

    /// MVA output variables
    floatBranches["CFMlpANN_ge3t"] = new float(0.0);
    floatBranches["CFMlpANN_e2je2t"] = new float(0.0);
    floatBranches["CFMlpANN_e3je2t"] = new float(0.0);
    floatBranches["CFMlpANN_ge4je2t"] = new float(0.0);
    floatBranches["CFMlpANN_var_best8"] = new float(0.0);
    floatBranches["CFMlpANN_ge3t_new"] = new float(0.0);

    //pile up
    floatBranches["numPV"] = new float(0.0);
    floatBranches["numTruePV"] = new float(0.0);
    floatBranches["numGenPV"] = new float(0.0);

    //weights
    floatBranches["weight"] = new float(0.0);
    floatBranches["weight_PUup"] = new float(0.0);
    floatBranches["weight_PUdown"] = new float(0.0);
    floatBranches["HtWgt"] = new float(0.0);
    floatBranches["HtWgtUp"] = new float(0.0);
    floatBranches["Q2ScaleUpWgt"] = new float(0.0);
    floatBranches["Q2ScaleDownWgt"] = new float(0.0);
    floatBranches["lep1SF"] = new float (0.0);
    floatBranches["lep2SF"] = new float (0.0);
    floatBranches["lepTotalSF"] = new float (0.0);
    
    //met
    floatBranches["met"] = new float(0.0);
    floatBranches["unc_met"] = new float(0.0);
    floatBranches["MHT"] = new float(0.0);

    //lepton variables
    floatBranches["lep1Pt"] = new float(0.0);
    floatBranches["lep2Pt"] = new float(0.0);
    floatBranches["lep1Eta"] = new float(0.0);
    floatBranches["lep2Eta"] = new float(0.0);
    floatBranches["lep1Phi"] = new float(0.0);
    floatBranches["lep2Phi"] = new float(0.0);
    floatBranches["lep1Iso"] = new float(0.0);
    floatBranches["lep2Iso"] = new float(0.0);
    floatBranches["lep1TkCharge"] = new float (0.0);
    floatBranches["lep1GenCharge"] = new float (0.0);
    floatBranches["lep2TkCharge"] = new float (0.0);
    floatBranches["lep2GenCharge"] = new float (0.0);

    // jet variables
    floatBranches["first_jet_pt"] = new float(0.0);
    floatBranches["second_jet_pt"] = new float(0.0);
    floatBranches["third_jet_pt"] = new float(0.0);
    floatBranches["fourth_jet_pt"] = new float(0.0);

    floatBranches["first_jet_eta"] = new float(0.0);
    floatBranches["second_jet_eta"] = new float(0.0);
    floatBranches["third_jet_eta"] = new float(0.0);
    floatBranches["fourth_jet_eta"] = new float(0.0);

    //kinematic variables
    ////ANN neural net inputs
    floatBranches["mass_of_everything"] = new float(0.0);
    floatBranches["min_dr_tagged_jets"] = new float(0.0);
    floatBranches["mindr_lep1_jet"] = new float(0.0);
    floatBranches["avg_btag_disc_btags"] = new float(0.0);
    floatBranches["Ht"] = new float(0.0);
    ////leptons
    floatBranches["mass_leplep"] = new float(0.0);
    floatBranches["pt_leplep"] = new float(0.0);
    floatBranches["dPhi_leplep"] = new float(0.0);
    floatBranches["dR_leplep"] = new float(0.0);
    floatBranches["correctedDZ_leplep"] = new float(0.0);
    floatBranches["correctedD0_leplep"] = new float(0.0);
    floatBranches["tkDZ_leplep"] = new float(0.0);
    floatBranches["mindr_lep2_jet"] = new float(0.0);
    ////everything
    floatBranches["sum_pt"] = new float(0.0); 
    floatBranches["sum_jet_pt"] = new float(0.0);
    floatBranches["pt_of_everything"] = new float(0.0);
    floatBranches["pz_of_everything"] = new float(0.0);

  } //End if (CoreVariables)


  if (ExtraHiggsVariables) {
    
    intBranches["numHiggsJets"] = new int (0);
    intBranches["numHiggsAllJets"] = new int (0);
    intBranches["HiggsDecayMode"] = new int(0); //CC=4,BB=5,TT=6,GG=21,ZZ=23,WW=24
    floatBranches["higgs_pt"] = new float(0.0);
    floatBranches["higgs_pz"] = new float(0.0);
    floatBranches["higgs_genJet_mass"] = new float(0.0);
    floatBranches["higgs_genParton_mass"] = new float(0.0);
    floatBranches["higgsLike_dijet_mass"] = new float(0.0);
    floatBranches["higgsLike_diBjet_mass"] = new float(0.0);
    floatBranches["higgsLike_allDijet_mass"] = new float(0.0);
    floatBranches["higgsLike_dijet_dR"] = new float(0.0);
    floatBranches["higgsLike_dijet_pt"] = new float(0.0);
    floatBranches["higgsLike_dijet_eta"] = new float(0.0);
    floatBranches["higgsLike_dijet_jet1_pt"] = new float(0.0);
    floatBranches["higgsLike_dijet_jet2_pt"] = new float(0.0);
    intBranches["numHiggsLike_dijet_10"] = new int (0);
    intBranches["numHiggsLike_dijet_15"] = new int (0);
    intBranches["numHiggsLike_dijet_20"] = new int (0);
    intBranches["numHiggsLike_dijet_25"] = new int (0);
    intBranches["numHiggsLike_diBjet_10"] = new int (0);
    intBranches["numHiggsLike_diBjet_15"] = new int (0);
    intBranches["numHiggsLike_diBjet_20"] = new int (0);
    intBranches["numHiggsLike_diBjet_25"] = new int (0);
    

    floatBranches["higgs_dijet_mass"] = new float(0.0);
    floatBranches["higgs_dijet_pt"] = new float(0.0);
    floatBranches["higgs_dijet_pz"] = new float(0.0);
    floatBranches["higgs_dijet_dR"] = new float(0.0);
    floatBranches["higgs_dijet_dPhi"] = new float(0.0);
    floatBranches["higgs_dijet_jet1_pt"] = new float(0.0);
    floatBranches["higgs_dijet_jet2_pt"] = new float(0.0);
    floatBranches["higgs_dijet_jet1_eta"] = new float(0.0);
    floatBranches["higgs_dijet_jet2_eta"] = new float(0.0);
    floatBranches["higgs_dijet_jet1_csv"] = new float(0.0);   
    floatBranches["higgs_dijet_jet2_csv"] = new float(0.0);   
    floatBranches["higgs_dijet_jet1_Nconst"] = new float(0.0);
    floatBranches["higgs_dijet_jet2_Nconst"] = new float(0.0);
    floatBranches["higgs_dijet_jet1_btagSoftMuon"] = new float(0.0); 
    floatBranches["higgs_dijet_jet2_btagSoftMuon"] = new float(0.0); 
    floatBranches["higgs_dijet_jet1_btagSoftEle"] = new float(0.0); 
    floatBranches["higgs_dijet_jet2_btagSoftEle"] = new float(0.0); 
    floatBranches["higgs_dijet_jet1_leadCandPt"] = new float(0.0);  
    floatBranches["higgs_dijet_jet2_leadCandPt"] = new float(0.0);  
    floatBranches["higgs_dijet_jet1_leadCandDistFromPV"] = new float(0.0);   
    floatBranches["higgs_dijet_jet2_leadCandDistFromPV"] = new float(0.0);
    floatBranches["higgs_dijet_genJet1_pt"] = new float(0.0);
    floatBranches["higgs_dijet_genJet2_pt"] = new float(0.0);
    floatBranches["higgs_dijet_genParton1_pt"] = new float(0.0);
    floatBranches["higgs_dijet_genParton2_pt"] = new float(0.0);
    floatBranches["higgs_dijet_jet1_muon_dR"] = new float(0.0);
    floatBranches["higgs_dijet_jet2_muon_dR"] = new float(0.0);
    floatBranches["higgs_dijet_jet1_electron_dR"] = new float(0.0);
    floatBranches["higgs_dijet_jet2_electron_dR"] = new float(0.0);
    floatBranches["higgs_dijet_jet1_track_pt"] = new float(0.0);
    floatBranches["higgs_dijet_jet2_track_pt"] = new float(0.0);
    floatBranches["higgs_dijet_jet1_track_dR"] = new float(0.0);
    floatBranches["higgs_dijet_jet2_track_dR"] = new float(0.0);
    
  } //End if (ExtraHiggsVariables)

  if (ExtraJetVariables) {
    
    intBranches["numAllJets"] = new int(0);

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
  
    floatBranches["first_jet_charge"] = new float(0.0);
    floatBranches["second_jet_charge"] = new float(0.0);
    floatBranches["third_jet_charge"] = new float(0.0);
    floatBranches["fourth_jet_charge"] = new float(0.0);

    floatBranches["dPhi_jet1jet2"] = new float(0.0);
    floatBranches["dPhi_jet1jet3"] = new float(0.0);
    floatBranches["dPhi_jet1jet4"] = new float(0.0);
    floatBranches["dPhi_jet2jet3"] = new float(0.0);
    floatBranches["dPhi_jet2jet4"] = new float(0.0);
    floatBranches["dPhi_jet3jet4"] = new float(0.0);
  
    floatBranches["first_allJet_pt"] = new float(0.0);
    floatBranches["second_allJet_pt"] = new float(0.0);
    floatBranches["third_allJet_pt"] = new float(0.0);
    floatBranches["fourth_allJet_pt"] = new float(0.0);

    floatBranches["first_dibjet_mass"] = new float(0.0);
    floatBranches["second_dibjet_mass"] = new float(0.0);
    floatBranches["third_dibjet_mass"] = new float(0.0);
    
    floatBranches["dijet_mass_m2H"] = new float(0.0);
    floatBranches["dijet_mass_first"] = new float(0.0);
    floatBranches["dijet_mass_second"] = new float(0.0);
    floatBranches["dijet_mass_third"] = new float(0.0);

    floatBranches["min_dr_genB1_allJet"] = new float (0.0);
    floatBranches["min_dr_genB2_allJet"] = new float (0.0);

  } //End if (ExtraJetVariables)

  if (ExtraTriggerVariables) {
    
    intBranches["isTriggerPassPrescaled"] = new int (0);
    intBranches["isDoubleMuTriggerPS0"] = new int (0);
    intBranches["isDoubleElectronTriggerPS0"] = new int (0);
    intBranches["isMuEGTriggerPS0"] = new int (0);
    intBranches["isMETTriggerPS0"] = new int (0);

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

  } //End if (ExtraTriggerVariables)

  if (ExtraGenVariables) {
    
    intBranches["lep1Mother"] = new int(0);
    intBranches["lep2Mother"] = new int(0);
    intBranches["lep1Grandmother"] = new int(0);
    intBranches["lep2Grandmother"] = new int(0);
    intBranches["lep1GenMotherId"] = new int (0);
    intBranches["lep2GenMotherId"] = new int (0);
    floatBranches["top1_pt"] = new float(0.0);
    floatBranches["top1_pz"] = new float(0.0);

  } //End if (ExtraGenVariables)

  if (ExtraKinematicVariables) {
    ////objects
    floatBranches["wLike_dijet_mass"] = new float(0.0);
    floatBranches["topLke_trijet_mass"] = new float(0.0);
    floatBranches["m2H_btag"] = new float(0.0);
    floatBranches["wLike_allDijet_mass"] = new float(0.0);
    floatBranches["topLike_allTrijet_mass"] = new float(0.0);
    floatBranches["pt_of_ttbar"] = new float(0.0);
    ////leptons
    floatBranches["dEta_leplep"] = new float(0.0);
    floatBranches["mindr_lep1_allJet"] = new float(0.0);
    floatBranches["mindr_lep2_allJet"] = new float(0.0);
    floatBranches["MT_met_lep1"] = new float(0.0);
    floatBranches["MT_met_lep2"] = new float(0.0);
    floatBranches["dPhi_met_lep1"] = new float(0.0);
    floatBranches["dPhi_met_lep2"] = new float(0.0);
    ////everything
    intBranches["PassZmask3"] = new int (0);
    
    floatBranches["min_dr_jets"] = new float(0.0);
    floatBranches["avg_dr_jets"] = new float(0.0);    
    floatBranches["avg_dr_tagged_jets"] = new float(0.0);
    
    floatBranches["avg_tagged_dijet_mass"] = new float(0.0);
    floatBranches["avg_untagged_dijet_mass"] = new float(0.0);
    floatBranches["avg_dijet_mass"] = new float(0.0);
    floatBranches["M2_of_closest_jets"] = new float(0.0);
    floatBranches["M2_of_closest_tagged_jets"] = new float(0.0);
    floatBranches["closest_dijet_mass"] = new float(0.0);
    floatBranches["closest_tagged_dijet_mass"] = new float(0.0);
    
    floatBranches["avg_btag_disc_non_btags"] = new float(0.0);
    floatBranches["highest_btag_disc_non_btags"] = new float(0.0);
    floatBranches["dev_from_avg_disc_btags"] = new float(0.0);
    floatBranches["first_highest_btag"] = new float(0.0);
    floatBranches["second_highest_btag"] = new float(0.0);
    floatBranches["lowest_btag"] = new float(0.0);

    floatBranches["mass_MHT"] = new float(0.0);
    floatBranches["all_sum_pt"] = new float(0.0);
    floatBranches["mass_of_leps_and_allJets"] = new float(0.0);
    floatBranches["pt_of_leps_and_allJets"] = new float(0.0);
    floatBranches["pt_total"] = new float(0.0);
    
  } //End if (ExtraKinematicVariables)


  if (ExtraLeptonVariables) {
    
  intBranches["lep2IsGlobalMuon"] = new int (0);
  intBranches["lep2IsTrackerMuon"] = new int (0);  
  intBranches["lep2IsGlobalMuonPromptTight"] = new int (0);  
  intBranches["lep2NumTrackHits"] = new int (0);  
  intBranches["lep2NumPixelHits"] = new int (0);  
  intBranches["lep2NumberOfMatches"] = new int (0);  
  floatBranches["lep2Chi2"] = new float (0.0);
  intBranches["lep2NumExpectedHits"] = new int (0);

  } //End if (ExtraLeptonVariables)

  int dInt = -9*pow(10,20);
  float dFloat = -9.0*pow(10,20);

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

  if( selectionYearStr == "2011"){
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
  else if( selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x") {
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
  else {
    assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
  } 

  ///
  float minNDOF = 4;
  float maxAbsZ = 24;
  float maxd0   = 2.;

  int nevents=0;
  float nevents_wgt=0;

  int nentries = ev.size();
  std::cout << "\n\t Number of entries = " << nentries << std::endl;
  std::cout << "\t Max number of entries = " << maxNentries << std::endl;
  std::cout << "\n" << std::endl;

  int cnt = 0;

  bool verbose = false; //false;
  
  //
  // Loop over events
  //
  std::cout << "========  Starting Event Loop  ========" << std::endl;
  try {
    for( ev.toBegin(); !ev.atEnd(); ++ev) {

      cnt++;

      if( cnt==1 )        std::cout << "     Event " << cnt << std::endl;
      if( cnt%100==0 && cnt!=1 ) std::cout << "Helper events " << cnt << "\t" 
					      << int(float(cnt)/float(nentries)*100) << "% done" << std::endl;

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
      if ( selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x" ) h_muons.getByLabel(ev,"BNproducer","selectedPatMuonsPFlow");
      else h_muons.getByLabel(ev,"BNproducer","selectedPatMuonsLoosePFlow");
      BNmuonCollection const &muons = *h_muons;

      fwlite::Handle<BNmuonCollection> h_muons_loose;
      if ( selectionYearStr == "2011" ) h_muons_loose.getByLabel(ev,"BNproducer","selectedPatMuonsLoosePFlow");
      else if ( selectionYearStr == "2012_53x" ) h_muons_loose.getByLabel(ev,"BNproducer","selectedPatMuonsLoosePFlow");
      else if ( selectionYearStr == "2012_52x" ) h_muons_loose.getByLabel(ev,"BNproducer","selectedPatMuonsPFlow");
      else assert ( selectionYearStr == "2012_52x, 2012_53x, or 2011" );
      BNmuonCollection const &looseMuons = *h_muons_loose;
      
      fwlite::Handle<BNmetCollection> h_pfmet;
      if ( selectionYearStr == "2011" ) h_pfmet.getByLabel(ev,"BNproducer","patMETsTypeIPFlow");
      else if ( selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x" ) h_pfmet.getByLabel(ev,"BNproducer","patMETsPFlow");
      else assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
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
      if ( selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x" ) h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsPFlow");
      else h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsLoosePFlow");
      BNelectronCollection const &electrons = *h_electrons;

      fwlite::Handle<BNelectronCollection> h_electrons_loose;
      if ( selectionYearStr == "2011" ) h_electrons_loose.getByLabel(ev,"BNproducer","selectedPatElectronsLoosePFlow");
      else if ( selectionYearStr == "2012_53x" ) h_electrons_loose.getByLabel(ev,"BNproducer","selectedPatElectronsLoosePFlow");
      else if ( selectionYearStr == "2012_52x" ) h_electrons_loose.getByLabel(ev,"BNproducer","selectedPatElectronsPFlow");
      else assert ( selectionYearStr == "2012_52x, 2012_53x, or 2011" );
      BNelectronCollection const &looseElectrons = *h_electrons_loose;
      
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

      fwlite::Handle<BNtrackCollection> h_tracks;
      h_tracks.getByLabel(ev,"BNproducer","generalTracks");
      BNtrackCollection const &tracks = *h_tracks;

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

      int eventSampleNumber = event->sample;

      float numTruePV = event->numTruePV;
      double numGenPV = event->numGenPV;

      float Q2ScaleUpWgt = 1.0;
      float Q2ScaleDownWgt = 1.0; 

      if (sampleNumber == 2500 || sampleNumber == 2544 || sampleNumber == 2555) {
        Q2ScaleUpWgt = event->Q2ScaleUpWgt;
        Q2ScaleDownWgt = event->Q2ScaleDownWgt;
      }

      float weight = 1.0 ;

      if(cnt<5)  std::cout << "CONFIG: Sample number from ntuple is: " << eventSampleNumber << std::endl;

     //// specific to ttH signal sample???
      int HtoBB = 0;
      int HtoCC = 0;
      int HtoTT = 0;
      int HtoGG = 0;
      int HtoWW = 0;
      int HtoZZ = 0;
      int lep1Mother = dInt;
      int lep2Mother = dInt;
      int lep1Grandmother = dInt;
      int lep2Grandmother = dInt;
      
      float higgs_pt = dFloat;
      float higgs_pz = dFloat;
      float top1_pt = dFloat;
      float top1_pz = dFloat;

      vfloat muon_px;
      vfloat ele_px;
      vfloat muon_py;
      vfloat ele_py;
      vfloat muon_pz;
      vfloat ele_pz;
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

      }

      if( (sampleName == "ttbar" || tmpName.Contains("ttbar_" )) && !tmpName.Contains("ttbar_scale") && !tmpName.Contains("ttbar_matching")) {       
        
        bool keepEvent = false;

        keepEvent = beanHelper.ttPlusHeavyKeepEvent (mcparticles, pfjets );

        if(!keepEvent) continue;
      }// end if you are a top sample

      //-------------------------------------
      //-------------------------------------

      if (verbose) std::cout << "met stuff " <<std::endl;
      
      MetIter pfmet = pfmets.begin();
      BNmet pfmetSelected = beanHelper.GetCorrectedMET(pfmets.at(0),pfjets,iSysType);
      
      // Loop over and count the number of primary vertices
      int numPV = 0;
      for( int i=0; i<int(pvs.size()); i++ ){
        bool isGood = ( (pvs.at(i).ndof>=minNDOF) &&
                        (fabs(pvs.at(i).z)<maxAbsZ) &&
                        (fabs(pvs.at(i).rho)<maxd0) );
        bool isFake = ( pvs.at(i).isFake==1 );
        if( isGood && !isFake ) numPV++;
      }

      if (verbose) std::cout << "about to do pu reweight " <<std::endl;
      ///--------------------------------
      // Pile-up reweighting  ////Robin
      double weight_PUnominal = 1.0;
      double weight_PUup = 1.0;
      double weight_PUdown = 1.0;

      if(!isData){
        if(selectionYearStr == "2011") {
          if ((TString(sampleName).Contains("ttH")) || (sampleName=="ttbarW") || (sampleName=="ttbarZ")) {
            beanHelper.getPUwgt(numGenPV,weight_PUnominal,weight_PUup,weight_PUdown);
          }
          else {
            beanHelper.getPUwgt(numTruePV,weight_PUnominal,weight_PUup,weight_PUdown);
          }
        }
        else if(selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x") {
          beanHelper.getPUwgt(numTruePV,weight_PUnominal,weight_PUup,weight_PUdown);
        }
        else {
          assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
        }
      }
      weight *= weight_PUnominal;


      ///--------------------------------
      // Trigger Requirement
      bool triggerFound = false;
      bool DoubleMuTriggerFound = false;
      bool DoubleElectronTriggerFound = false;
      bool MuEGTriggerFound = false;
      bool METTriggerFound = false;
      bool isTriggerPass = false;
      bool isTriggerPassPrescaled = false;
      bool isDoubleMuTriggerPass = false;
      bool isDoubleElectronTriggerPass = false;
      bool isMuEGTriggerPass = false;
      bool isMETTriggerPass = false;
      bool isDoubleMuTriggerPS0 = false;
      bool isDoubleElectronTriggerPS0 = false;
      bool isMuEGTriggerPS0 = false;
      bool isMETTriggerPS0 = false;
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
      //      if( eventSampleNumber>=0 ){
      std::string hlt_name = "holder";

	for( TrigIter hltbit = hlt.begin(); hltbit != hlt.end(); ++hltbit ) {
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
            isDoubleMuTriggerPass = ( ( hltbit->pass==1 && hltbit->prescale==1 ) || isDoubleMuTriggerPass);
            isDoubleMuTriggerPS0 = ( ( hltbit->prescale==0 ) || isDoubleMuTriggerPS0);
          }
          else isTriggerPassPrescaled = ( hltbit->pass==1 || isTriggerPassPrescaled);
        }
        if( isDoubleMuTriggerPass ) break;
      }
      for( int t=0; t<int(mc_hlt_DoubleElectron_trigger_collection.size()); t++ ){
        //hlt_name = hltbit->name;
	    if( (hlt_name.find(mc_hlt_DoubleElectron_trigger_collection[t])!=std::string::npos) ) {
	      if( hltbit->prescale==1 || hltbit->prescale==0 ) {
            DoubleElectronTriggerFound = true;
            isDoubleElectronTriggerPass = ( ( hltbit->pass==1 && hltbit->prescale==1 ) || isDoubleElectronTriggerPass);
            isDoubleElectronTriggerPS0 = ( ( hltbit->prescale==0 ) || isDoubleElectronTriggerPS0);
          }
          else isTriggerPassPrescaled = ( hltbit->pass==1 || isTriggerPassPrescaled);
        }
        if( isDoubleElectronTriggerPass ) break;
      }
      for( int t=0; t<int(mc_hlt_MuEG_trigger_collection.size()); t++ ){
        //hlt_name = hltbit->name;
	    if( (hlt_name.find(mc_hlt_MuEG_trigger_collection[t])!=std::string::npos) ) {
	      if( hltbit->prescale==1 || hltbit->prescale==0 ) {
            MuEGTriggerFound = true;
            isMuEGTriggerPass = ( ( hltbit->pass==1 && hltbit->prescale==1 ) || isMuEGTriggerPass);
            isMuEGTriggerPS0 = ( ( hltbit->prescale==0 ) || isMuEGTriggerPS0);
          }
          else isTriggerPassPrescaled = ( hltbit->pass==1 || isTriggerPassPrescaled);
        }
        if( isMuEGTriggerPass ) break;
      }
      for( int t=0; t<int(mc_hlt_MET_trigger_collection.size()); t++ ){
        //hlt_name = hltbit->name;
	    if( (hlt_name.find(mc_hlt_MET_trigger_collection[t])!=std::string::npos) ) {
	      if( hltbit->prescale==1 || hltbit->prescale==0 ) {
            METTriggerFound = true;
            isMETTriggerPass = ( ( hltbit->pass==1 && hltbit->prescale==1 ) || isMETTriggerPass);
            isMETTriggerPS0 = ( ( hltbit->prescale==0 ) || isMETTriggerPS0);
          }
          else isTriggerPassPrescaled = ( hltbit->pass==1 || isTriggerPassPrescaled);
        }
        if( isMETTriggerPass ) break;
      }
      //if( isTriggerPass ) break;
    }
    if (isDoubleMuTriggerPass || isDoubleElectronTriggerPass || isMuEGTriggerPass) isTriggerPass = true;
    if (DoubleMuTriggerFound || DoubleElectronTriggerFound || MuEGTriggerFound || METTriggerFound) triggerFound = true;


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
    nevents_wgt+=weight;
    

    // Event cleaning requirements
    bool passGoodVertex = ( numPV>0 ) ? true : false;
    bool passFilterOutScraping = ( event->FilterOutScraping==1 ) ? true : false;
    bool passHBHENoiseFilter = ( event->HBHENoiseFilter==1 ) ? true : false;
    
    bool isCleanEvent = ( passGoodVertex && passFilterOutScraping && passHBHENoiseFilter );
    isCleanEvent = (isData) ?  isCleanEvent : true;
    

    //////////split nGen
    if( (eventSampleNumber>=100 && eventSampleNumber<=300)
        || (eventSampleNumber>=7100 && eventSampleNumber<=7300)
        || (eventSampleNumber>=8100 && eventSampleNumber<=8300)
        || (eventSampleNumber>=9100 && eventSampleNumber<=9300) ) {

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

    if (verbose) std::cout << "about to do ele selection " <<std::endl;

      
    /////////
    ///
    /// Electrons
    ///
    ////////
    ////--------- using selectors in "beanHelper.h"
    ////////////////////////////////

    BNelectronCollection electronsTight;
    BNelectronCollection electronsInclusivelyLoose;
    BNelectronCollection electronsInclusivelySide;
    BNelectronCollection electronsLoose;
    BNelectronCollection electronsSide;
    BNelectronCollection electronsTL;
    BNelectronCollection electronsTS;
    BNelectronCollection electronsSelected;

    int numTightElectrons = dInt;
    int numLooseElectrons = dInt;
    int numSideElectrons = dInt;

    if (selectionYearStr == "2011") {
      electronsTight = beanHelper.GetSelectedElectrons(looseElectrons,electronID::electronTight);
      electronsInclusivelyLoose = beanHelper.GetSelectedElectrons(looseElectrons,electronID::electronLoose);
      electronsInclusivelySide = beanHelper.GetSelectedElectrons(looseElectrons,electronID::electronSide);
    }
    else if (selectionYearStr == "2012_52x") {
      electronsTight = beanHelper.GetSelectedElectrons(electrons,electronID::electronTight);
      electronsInclusivelyLoose = beanHelper.GetSelectedElectrons(electrons,electronID::electronLoose);
    }
    else if (selectionYearStr == "2012_53x") {
      electronsTight = beanHelper.GetSelectedElectrons(electrons,electronID::electronTight);
      electronsInclusivelyLoose = beanHelper.GetSelectedElectrons(electrons,electronID::electronLoose);
      electronsInclusivelySide = beanHelper.GetSelectedElectrons(looseElectrons,electronID::electronSide);
    }
    else {
      assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
    }

    try { electronsLoose = beanHelper.GetSymmetricDifference(electronsInclusivelyLoose,electronsTight); }
    catch(...) { std::cerr << " exception in GetSymmetricDifference" << std::endl; continue; } //Don't segfault if two leptons have same eta,phi but different pt
    try { electronsTL = beanHelper.GetUnionUnsorted(beanHelper.GetSortedByPt(electronsTight),beanHelper.GetSortedByPt(electronsInclusivelyLoose)); }
    catch(...) { std::cerr << " exception in GetUnionUnsorted" << std::endl; continue; } //Don't segfault if two leptons have same eta,phi but different pt
    if (selectionYearStr == "2011" || selectionYearStr == "2012_53x") {
      try { electronsSide = beanHelper.GetSymmetricDifference(electronsInclusivelySide,electronsInclusivelyLoose); }
      catch(...) { std::cerr << " exception in GetUnionUnsorted" << std::endl; continue; } //Don't segfault if two leptons have same eta,phi but different pt
      try { electronsTS = beanHelper.GetUnionUnsorted(beanHelper.GetSortedByPt(electronsTight),beanHelper.GetSortedByPt(electronsSide)); }
      catch(...) { std::cerr << " exception in GetUnionUnsorted" << std::endl; continue; } //Don't segfault if two leptons have same eta,phi but different pt
      numSideElectrons = electronsSide.size();
    }
    electronsSelected = electronsTL;
    
    numTightElectrons = electronsTight.size();
    numLooseElectrons = electronsTL.size() - electronsTight.size();
    
    /////////
    ///
    /// Muons
    ///
    ////////
    ////--------- using selectors in "beanHelper.h"
    ////////////////////////////////

    BNmuonCollection muonsTight;
    BNmuonCollection muonsInclusivelyLoose;
    BNmuonCollection muonsInclusivelySide;
    BNmuonCollection muonsLoose;
    BNmuonCollection muonsSide;
    BNmuonCollection muonsTL;
    BNmuonCollection muonsTS;
    BNmuonCollection muonsSelected;

    int numTightMuons = dInt;
    int numLooseMuons = dInt;
    int numSideMuons = dInt;
    
    if (selectionYearStr == "2011") {
      muonsTight = beanHelper.GetSelectedMuons(looseMuons,muonID::muonTight);
      muonsInclusivelyLoose = beanHelper.GetSelectedMuons(looseMuons,muonID::muonLoose);
      muonsInclusivelySide = beanHelper.GetSelectedMuons(looseMuons,muonID::muonSide);
    }
    else if (selectionYearStr == "2012_52x") {
      muonsTight = beanHelper.GetSelectedMuons(muons,muonID::muonTight);
      muonsInclusivelyLoose = beanHelper.GetSelectedMuons(muons,muonID::muonLoose);
    }
    else if (selectionYearStr == "2012_53x") {
      muonsTight = beanHelper.GetSelectedMuons(muons,muonID::muonTight);
      muonsInclusivelyLoose = beanHelper.GetSelectedMuons(muons,muonID::muonLoose);
      muonsInclusivelySide = beanHelper.GetSelectedMuons(looseMuons,muonID::muonSide);
    }
    else {
      assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
    }

    try { muonsLoose = beanHelper.GetSymmetricDifference(muonsInclusivelyLoose,muonsTight); }
    catch(...) { std::cerr << " exception in GetSymmetricDifference" << std::endl; continue; } //Don't segfault if two leptons have same eta,phi but different pt
    try { muonsTL = beanHelper.GetUnionUnsorted(beanHelper.GetSortedByPt(muonsTight),beanHelper.GetSortedByPt(muonsInclusivelyLoose)); }
    catch(...) { std::cerr << " exception in GetUnionUnsorted" << std::endl; continue; } //Don't segfault if two leptons have same eta,phi but different pt
    if (selectionYearStr == "2011" || selectionYearStr == "2012_53x") {    
      try { muonsSide = beanHelper.GetSymmetricDifference(muonsInclusivelySide,muonsInclusivelyLoose); }
      catch(...) { std::cerr << " exception in GetSymmetricDifference" << std::endl; continue; } //Don't segfault if two leptons have same eta,phi but different pt
      try { muonsTS = beanHelper.GetUnionUnsorted(beanHelper.GetSortedByPt(muonsTight),beanHelper.GetSortedByPt(muonsSide)); }
      catch(...) { std::cerr << " exception in GetUnionUnsorted" << std::endl; continue; } //Don't segfault if two leptons have same eta,phi but different pt
      numSideMuons = muonsSide.size();
    }
    muonsSelected = muonsTL;
    
    numTightMuons = muonsTight.size();
    numLooseMuons = muonsTL.size() - muonsTight.size();
    //numLooseMuons = muonsLoose.size();

    bool PassTwoLepton = (( numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons )== 2 && ( numTightMuons + numTightElectrons )> 0 );
    //if ( !PassTwoLepton ) continue ;
    if ( debug_ && muons.size() + electrons.size() < 2 ) cout << "Event " << cnt << ", input collection of leptons less than 2" << endl;
    if ( debug_ && muons.size() + electrons.size() > 2 ) cout << "Event " << cnt << ", Input collection of leptons greater than 2" << endl;
    if ( !PassTwoLepton ) {
      if (debug_) cout << "Too few leptons, even on a skimmed file" << endl;
      if (debug_) cout << "Muons: " << muons.size() << ", tight: " << numTightMuons << ", loose: " << numLooseMuons << endl;
      if (debug_) cout << "Electrons: " << electrons.size() << ", tight: " << numTightElectrons << ", loose: " << numLooseElectrons << endl;
      continue;
    }
      
    /////////
    ///
    /// Pfjets
    ///
    ////////

    //beanHelper.GetSelectedJets(const BNjetCollection& iJets, const float iMinPt, const float iMaxAbsEta, const jetID::jetID iJetID, const char iCSVwp)
    //beanHelper.GetUncorrectedJets(const BNjetCollection& iCorrectedJets, const BNjetCollection& iOriginalJets)
    
      std::vector<int> tight_pfjet_index;
      std::vector<int> all_pfjet_index;
      std::vector<int> tag_pfjet_index;
      std::vector<int> tag_pfjet_csvVal;
      std::vector<int> untag_pfjet_index;

      std::vector<float> good_jet_pt;
      std::vector<float> good_jet_eta;
      std::vector<float> good_jet_CHEF;
      std::vector<float> good_jet_charge;
      std::vector<float> good_jet_tag;
      std::vector<int>    good_jet_flavor;

      std::vector<int>    jet_motherID;
      
      vfloat jet_px;
      vfloat jet_py;
      vfloat jet_pz;
      vfloat jet_pt;
      vfloat jet_energy;
      vfloat jet_CHEF;
      vfloat jet_charge;

      int numGoodJets=0;
      int numHiggsJets=0;
      int numHiggsAllJets=0;
      int numGoodAndBadJets=0;
      TLorentzVector jetV[100];
      TLorentzVector allJetV[100];
      TLorentzVector higgsJetV[100];
      TLorentzVector higgsGenJetV[100];
      TLorentzVector higgsGenPartonV[100];
      TLorentzVector muonTemp(0.0,0.0,0.0,0.0);
      TLorentzVector electronTemp(0.0,0.0,0.0,0.0);
      TLorentzVector trackTemp(0.0,0.0,0.0,0.0);
      TLorentzVector higgsClosestMuonV[100];
      TLorentzVector higgsClosestElectronV[100];
      TLorentzVector higgsClosestTrackV[100];

      float higgs_dijet_jet1_csv = dFloat;
      float higgs_dijet_jet2_csv = dFloat;
      float higgs_dijet_jet1_btagSoftMuon = dFloat;
      float higgs_dijet_jet2_btagSoftMuon = dFloat;
      float higgs_dijet_jet1_btagSoftEle = dFloat;
      float higgs_dijet_jet2_btagSoftEle = dFloat;
      float higgs_dijet_jet1_Nconst = dFloat;
      float higgs_dijet_jet2_Nconst = dFloat;
      //float higgs_dijet_jet1_mass = dFloat;
      //float higgs_dijet_jet2_mass = dFloat;
      //float higgs_dijet_jet1_area = dFloat;
      //float higgs_dijet_jet2_area = dFloat;
      //float higgs_dijet_jet1_charge = dFloat;
      //float higgs_dijet_jet2_charge = dFloat;
      float higgs_dijet_jet1_leadCandPt = dFloat;
      float higgs_dijet_jet2_leadCandPt = dFloat;
      float higgs_dijet_jet1_leadCandDistFromPV= dFloat;
      float higgs_dijet_jet2_leadCandDistFromPV = dFloat;
      

      
      std::list<float> jet_CSV;      

      bool jerDebugPrint = false;

      /////////////////////////////////////////////////
      //
      //   Loop over jets
      //
      // 
      /////////////////////////////////////////////////

      if (jerDebugPrint || verbose)
        cout << "\n--------------new event------------------" << endl;

      BNjetCollection const &pfjetsSelected = beanHelper.GetCorrectedJets(pfjets,iSysType);

      for( int i=0; i<int(pfjetsSelected.size()); i++ ){

	float jetPt = pfjetsSelected.at(i).pt;
    float jetEta = pfjetsSelected.at(i).eta;	
    float jetAbsEta = fabs(jetEta);
    float genJetPT = pfjetsSelected.at(i).genJetPT;
    float jetPhi = pfjetsSelected.at(i).phi;
    float jetCHEF = pfjetsSelected.at(i).chargedHadronEnergyFraction;
    float jetcharge = pfjetsSelected.at(i).charge;
    //float myJER = beanHelper.getJERfactor( jer, jetAbsEta, genJetPT, jetPt);

    if (ArtificialJetPt) {
      std::random_device rd;
      std::mt19937 generator(rd());
      double mean = 1.0;
      double std  = 0.15*sqrt(50.0)/sqrt(max(pfjetsSelected.at(i).genPartonPT,20.0));
      std::normal_distribution<double> normal(mean, std);
      double jet_scale = normal(generator)*pfjetsSelected.at(i).genPartonPT/pfjetsSelected.at(i).pt;
      jetPt *= jet_scale;
      jet_px.push_back(pfjetsSelected.at(i).px*jet_scale);
      jet_py.push_back(pfjetsSelected.at(i).py*jet_scale);
      jet_pz.push_back(pfjetsSelected.at(i).pz*jet_scale);
      jet_pt.push_back(pfjetsSelected.at(i).pt*jet_scale);
      jet_energy.push_back(pfjetsSelected.at(i).energy*jet_scale);
    }
    else {
      jet_px.push_back(pfjetsSelected.at(i).px);
      jet_py.push_back(pfjetsSelected.at(i).py);
      jet_pz.push_back(pfjetsSelected.at(i).pz);
      jet_pt.push_back(pfjetsSelected.at(i).pt);
      jet_energy.push_back(pfjetsSelected.at(i).energy);
    }
    jet_CHEF.push_back(pfjetsSelected.at(i).chargedHadronEnergyFraction);
    jet_charge.push_back(pfjetsSelected.at(i).charge);    
      
    if ( (tmpName.Contains("ttH") && pfjetsSelected.at(i).genPartonMotherId == 25) ||
         (sampleName == "ttbar_bb" && abs(pfjetsSelected.at(i).genPartonId) == 5 && abs(pfjetsSelected.at(i).genPartonMotherId) != 6) ||
         (sampleName == "ttbarW" && abs(pfjetsSelected.at(i).genPartonId) != 5 && abs(pfjetsSelected.at(i).genPartonMotherId) == 24) ||
         (sampleName == "ttbarZ" && abs(pfjetsSelected.at(i).genPartonId) != 5 && abs(pfjetsSelected.at(i).genPartonMotherId) == 23) ) {
      higgsJetV[numHiggsAllJets].SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
      higgsGenJetV[numHiggsAllJets].SetPtEtaPhiE(pfjetsSelected.at(i).genJetPT,pfjetsSelected.at(i).genJetEta,pfjetsSelected.at(i).genJetPhi,pfjetsSelected.at(i).genJetET/sin(2*atan(exp(-pfjetsSelected.at(i).genJetEta))));
      higgsGenPartonV[numHiggsAllJets].SetPtEtaPhiE(pfjetsSelected.at(i).genPartonPT,pfjetsSelected.at(i).genPartonEta,pfjetsSelected.at(i).genPartonPhi,pfjetsSelected.at(i).genPartonET/sin(2*atan(exp(-pfjetsSelected.at(i).genPartonEta))));
      higgsClosestMuonV[numHiggsAllJets].SetPxPyPzE(-jet_px[i],-jet_py[i],-jet_pz[i],jet_energy[i]);
      higgsClosestElectronV[numHiggsAllJets].SetPxPyPzE(-jet_px[i],-jet_py[i],-jet_pz[i],jet_energy[i]);
      higgsClosestTrackV[numHiggsAllJets].SetPxPyPzE(-jet_px[i],-jet_py[i],-jet_pz[i],jet_energy[i]);
      for (unsigned int ii = 0; ii < muonsSide.size(); ii++) {
        muonTemp.SetPxPyPzE(muonsSide.at(ii).px,muonsSide.at(ii).py,muonsSide.at(ii).pz,muonsSide.at(ii).energy);
        if ( higgsJetV[numHiggsAllJets].DeltaR(muonTemp) < higgsJetV[numHiggsAllJets].DeltaR(higgsClosestMuonV[numHiggsAllJets]) ) {
          higgsClosestMuonV[numHiggsAllJets].SetPxPyPzE(muonsSide.at(ii).px,muonsSide.at(ii).py,muonsSide.at(ii).pz,muonsSide.at(ii).energy);
        }
      }
      for (unsigned int ii = 0; ii < electronsSide.size(); ii++) {
        electronTemp.SetPxPyPzE(electronsSide.at(ii).px,electronsSide.at(ii).py,electronsSide.at(ii).pz,electronsSide.at(ii).energy);
        if ( higgsJetV[numHiggsAllJets].DeltaR(electronTemp) < higgsJetV[numHiggsAllJets].DeltaR(higgsClosestElectronV[numHiggsAllJets]) ) {
          higgsClosestElectronV[numHiggsAllJets].SetPxPyPzE(electronsSide.at(ii).px,electronsSide.at(ii).py,electronsSide.at(ii).pz,electronsSide.at(ii).energy);
        }
      }
      for (unsigned int ii = 0; ii < tracks.size(); ii++) {
        trackTemp.SetPxPyPzE(tracks.at(ii).px,tracks.at(ii).py,tracks.at(ii).pz,sqrt ( pow(tracks.at(ii).px,2) + pow(tracks.at(ii).py,2) + pow(tracks.at(ii).pz,2) ));
        if ( higgsJetV[numHiggsAllJets].DeltaR(trackTemp) < 0.7 ) {
          if (higgsJetV[numHiggsAllJets].DeltaR(higgsClosestTrackV[numHiggsAllJets]) > 0.7 || trackTemp.Pt() > higgsJetV[numHiggsAllJets].Pt() ) {
            higgsClosestTrackV[numHiggsAllJets].SetPxPyPzE(tracks.at(ii).px,tracks.at(ii).py,tracks.at(ii).pz,sqrt ( pow(tracks.at(ii).px,2) + pow(tracks.at(ii).py,2) + pow(tracks.at(ii).pz,2) ));
          }
        }
      }
      if (numHiggsAllJets==0) {
        higgs_dijet_jet1_csv  = pfjetsSelected.at(i).btagCombinedSecVertex;
        higgs_dijet_jet1_btagSoftMuon  = pfjetsSelected.at(i).btagSoftMuon;
        higgs_dijet_jet1_btagSoftEle  = pfjetsSelected.at(i).btagSoftEle;
        higgs_dijet_jet1_Nconst  = pfjetsSelected.at(i).Nconst;
        //higgs_dijet_jet1_mass  = pfjetsSelected.at(i).mass;
        //higgs_dijet_jet1_area  = pfjetsSelected.at(i).area;
        //higgs_dijet_jet1_charge  = pfjetsSelected.at(i).charge;
        higgs_dijet_jet1_leadCandPt  = pfjetsSelected.at(i).leadCandPt;
        higgs_dijet_jet1_leadCandDistFromPV = pfjetsSelected.at(i).leadCandDistFromPV;
      }
      else if (numHiggsAllJets==1) {
        higgs_dijet_jet2_csv  = pfjetsSelected.at(i).btagCombinedSecVertex;
        higgs_dijet_jet2_btagSoftMuon  = pfjetsSelected.at(i).btagSoftMuon;
        higgs_dijet_jet2_btagSoftEle  = pfjetsSelected.at(i).btagSoftEle;
        higgs_dijet_jet2_Nconst  = pfjetsSelected.at(i).Nconst;
        //higgs_dijet_jet2_mass  = pfjetsSelected.at(i).mass;
        //higgs_dijet_jet2_area  = pfjetsSelected.at(i).area;
        //higgs_dijet_jet2_charge  = pfjetsSelected.at(i).charge;
        higgs_dijet_jet2_leadCandPt  = pfjetsSelected.at(i).leadCandPt;
        higgs_dijet_jet2_leadCandDistFromPV = pfjetsSelected.at(i).leadCandDistFromPV;
      }        

      numHiggsAllJets++;
    } 

    //std::cout << "Jet " << i << " ID: " << pfjetsSelected.at(i).genPartonMotherId << std::endl;
    jet_motherID.push_back(pfjetsSelected.at(i).genPartonMotherId);
//     if (pfjetsSelected.at(i).genPartonMotherId != 25  && pfjetsSelected.at(i).genPartonGrandMotherId != 99 && pfjetsSelected.at(i).genPartonGrandMotherId != -99) {
//       if (pfjetsSelected.at(i).genPartonGrandMotherId == 25) {
//         std::cout << "GrandMother for jet " << i << " is HIGGS and mother is " << pfjetsSelected.at(i).genPartonMotherId << std::endl;
//       }
//       else {
//         std::cout << "GrandMother for jet " << i << " is " << pfjetsSelected.at(i).genPartonGrandMotherId << std::endl;
//       }
//     }
    allJetV[numGoodAndBadJets].SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
    numGoodAndBadJets++;
    
	bool kin = ( jetPt>30. );
	bool eta = ( jetAbsEta<2.4 );
	bool id  = ( pfjetsSelected.at(i).jetIDLoose==1 );
    
	if( !(kin && eta && id) ) continue;

	if (tmpName.Contains("ttH") && pfjetsSelected.at(i).genPartonMotherId == 25) {
	  numHiggsJets++;
	} 
	else if (sampleName == "ttbar_bb" && abs(pfjetsSelected.at(i).genPartonId) == 5 && abs(pfjetsSelected.at(i).genPartonMotherId) != 6) {
	  numHiggsJets++;
	} 

	jetV[numGoodJets].SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
	numGoodJets++;
	tight_pfjet_index.push_back(i);

	// Use Combined tags
	// Loose Cut is 0.244
	// Medium Cut is 0.679
	// Tight Cut is 0.898


    //int iJetFlav = pfjetsSelected.at(i).flavour;
    
    float csv = pfjetsSelected.at(i).btagCombinedSecVertex;
	bool csvM = ( csv > btagThres );

	
	if( csvM ){
	  tag_pfjet_index.push_back(i);
	  jet_CSV.push_back(csv);
      tag_pfjet_csvVal.push_back(csv);
	}
	else        untag_pfjet_index.push_back(i);
	
	int flavor =  pfjetsSelected.at(i).flavour;

	good_jet_pt.push_back(jetPt);
	good_jet_eta.push_back(jetEta);
	good_jet_tag.push_back(csv);
	good_jet_flavor.push_back(flavor);
    good_jet_CHEF.push_back(jetCHEF);
    good_jet_charge.push_back(jetcharge);

      }// end for each pf jet
      
      //------------------------
      int numAllJet = numGoodAndBadJets;
      int numJets = int(tight_pfjet_index.size());
      // Only select events with at least two jets
      if (numJets < 2) continue;
      int numTaggedJets = int(tag_pfjet_index.size());

      ///////

      bool TightMuonLooseMuon = ((numTightMuons == 1) && (numLooseMuons==1));
      bool TightMuonLooseEle = ((numTightMuons == 1) && (numLooseElectrons==1));
      bool TightEleLooseMuon = ((numTightElectrons == 1) && (numLooseMuons==1));
      bool TightEleLooseEle = ((numTightElectrons == 1) && (numLooseElectrons==1));

      bool twoTightMuon = (numTightMuons == 2);
      bool oneEleOneMuon = ((numTightMuons ==1) && (numTightElectrons ==1));
      bool twoTightEle = (numTightElectrons ==2);

      bool TwoMuon = PassTwoLepton && ( twoTightMuon || TightMuonLooseMuon ) ;
      bool TwoEle = PassTwoLepton && ( twoTightEle || TightEleLooseEle ) ;
      bool MuonEle = PassTwoLepton && ( TightMuonLooseEle || TightEleLooseMuon || oneEleOneMuon );


      
      //long tempLongEventNum = event->evt;
      //unsigned tempUEventNum = (unsigned) tempLongEventNum;
      //std::cout << "Check event num: long " << tempLongEventNum << " uint " << tempUEventNum << std::endl;
      

      /////////////////////////////////
      ///////
      /////// final selection for neural net training:
      //////
      ////////////////////////////////

      //met

    float metx = pfmet->px;
    float mety = pfmet->py;
    float metpt = pfmet->pt;
    float metx_new = pfmetSelected.px;
    float mety_new = pfmetSelected.py;
    float metpt_new = pfmetSelected.pt;
    
    if (jerDebugPrint || verbose)
      cout << "---> MET " << endl
           << "     metx " << metx << endl
           << "     mety " << mety << endl
           << "     metpt " << metpt <<endl
           << "     metx_new " << metx_new  << endl
           << "     mety_new " << mety_new  << endl
           << "     metpt "    << metpt_new << endl;


    
      TLorentzVector metV(metx_new,mety_new,0.0,metpt_new);
      float met = metpt_new;
      float unc_met = pfmet->Upt;


      //sort btag discriminator
      jet_CSV.sort();  
      std::vector<float> jet_CSV_sorted_vect;			
      std::list<float>::iterator listint;			
      for (listint = jet_CSV.begin(); listint != jet_CSV.end(); listint++){
	jet_CSV_sorted_vect.push_back(*listint);  //accessible form
      }

      //////  ttbb bkg -- dibjet mass combinations
      std::list<float> dibjet_mass_combinations;
      float m2H_btag = dFloat ;

      std::list<float> dijet_mass_combinations;
      float dijet_mass_m2H = dFloat ;

      //sum of all jets
      TLorentzVector sum_jet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_allJet_vect(0.0,0.0,0.0,0.0);
      
      for (int sumv=0; sumv < numJets; sumv++) {
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
      
      float higgs_dijet_mass = dFloat;
      float higgs_dijet_pt = dFloat;
      float higgs_dijet_pz = dFloat;
      float higgs_dijet_dR = dFloat;
      float higgs_dijet_dPhi = dFloat;
      float higgs_dijet_jet1_pt= dFloat;
      float higgs_dijet_jet2_pt = dFloat;
      float higgs_dijet_jet1_eta = dFloat;
      float higgs_dijet_jet2_eta = dFloat;
      float higgs_dijet_jet1_muon_dR= dFloat;
      float higgs_dijet_jet2_muon_dR = dFloat;
      //float higgs_dijet_jet1_muon_pt= dFloat;
      //float higgs_dijet_jet2_muon_pt = dFloat;
      float higgs_dijet_jet1_electron_dR= dFloat;
      float higgs_dijet_jet2_electron_dR = dFloat;
      //float higgs_dijet_jet1_electron_pt= dFloat;
      //float higgs_dijet_jet2_electron_pt = dFloat;
      float higgs_dijet_jet1_track_dR= dFloat;
      float higgs_dijet_jet2_track_dR = dFloat;
      float higgs_dijet_jet1_track_pt= dFloat;
      float higgs_dijet_jet2_track_pt = dFloat;
      float higgsLike_dijet_mass1 = dFloat;
      float higgsLike_dijet_mass2 = dFloat;
      float higgsLike_diBjet_mass1 = dFloat;
      float higgsLike_dijet_dR = dFloat;
      float higgsLike_dijet_pt = dFloat;
      float higgsLike_dijet_eta = dFloat;
      float higgsLike_dijet_jet1_pt = dFloat;
      float higgsLike_dijet_jet2_pt = dFloat;
      int numHiggsLike_dijet_10 = 0;
      int numHiggsLike_dijet_15 = 0;
      int numHiggsLike_dijet_20 = 0;
      int numHiggsLike_dijet_25 = 0;
      int numHiggsLike_diBjet_10 = 0;
      int numHiggsLike_diBjet_15 = 0;
      int numHiggsLike_diBjet_20 = 0;
      int numHiggsLike_diBjet_25 = 0;
      float higgs_dijet_genJet1_pt= dFloat;
      float higgs_dijet_genJet2_pt = dFloat;
      float higgs_dijet_genParton1_pt= dFloat;
      float higgs_dijet_genParton2_pt = dFloat;
      float wLike_dijet_mass1 = dFloat;
      float topLike_trijet_mass1 = dFloat;
      float topLike_trijet_mass2 = dFloat;
      float higgsLike_allDijet_mass1 = dFloat;
      float higgsLike_allDijet_mass2 = dFloat;
      float wLike_allDijet_mass1 = dFloat;
      float topLike_allTrijet_mass1 = dFloat;
      float topLike_allTrijet_mass2 = dFloat;
      float higgs_genJet_mass = dFloat;
      float higgs_genParton_mass = dFloat;
      
      if (numHiggsAllJets == 2) {
        sum_higgs_dijet_vect = higgsJetV[0] + higgsJetV[1];
        higgs_dijet_mass = sum_higgs_dijet_vect.M();
        higgs_dijet_pt = sum_higgs_dijet_vect.Pt();
        higgs_dijet_pz = sum_higgs_dijet_vect.Pz();
        higgs_dijet_dR = higgsJetV[0].DeltaR(higgsJetV[1]);
        higgs_dijet_dPhi = higgsJetV[0].DeltaPhi(higgsJetV[1]);
        higgs_dijet_jet1_pt = higgsJetV[0].Pt();
        higgs_dijet_jet2_pt = higgsJetV[1].Pt();
        higgs_dijet_jet1_eta = higgsJetV[0].Eta();
        higgs_dijet_jet2_eta = higgsJetV[1].Eta();
        higgs_dijet_genJet1_pt = higgsGenJetV[0].Pt();
        higgs_dijet_genJet2_pt = higgsGenJetV[1].Pt();
        higgs_dijet_genParton1_pt = higgsGenPartonV[0].Pt();
        higgs_dijet_genParton2_pt = higgsGenPartonV[1].Pt();
        higgs_dijet_jet1_muon_dR = higgsJetV[0].DeltaR(higgsClosestMuonV[0]);
        higgs_dijet_jet2_muon_dR = higgsJetV[1].DeltaR(higgsClosestMuonV[1]);
        //higgs_dijet_jet1_muon_pt = higgsClosestMuonV[0].Pt();
        //higgs_dijet_jet2_muon_pt = higgsClosestMuonV[1].Pt();
        higgs_dijet_jet1_electron_dR = higgsJetV[0].DeltaR(higgsClosestElectronV[0]);
        higgs_dijet_jet2_electron_dR = higgsJetV[1].DeltaR(higgsClosestElectronV[1]);
        //higgs_dijet_jet1_electron_pt = higgsClosestElectronV[0].Pt();
        //higgs_dijet_jet2_electron_pt = higgsClosestElectronV[1].Pt();
        higgs_dijet_jet1_track_dR = higgsJetV[0].DeltaR(higgsClosestTrackV[0]);
        higgs_dijet_jet2_track_dR = higgsJetV[1].DeltaR(higgsClosestTrackV[1]);
        higgs_dijet_jet1_track_pt = higgsClosestTrackV[0].Pt();
        higgs_dijet_jet2_track_pt = higgsClosestTrackV[1].Pt();
        sum_higgs_genJet_vect = higgsGenJetV[0] + higgsGenJetV[1];
        higgs_genJet_mass = sum_higgs_genJet_vect.M();
        sum_higgs_genParton_vect = higgsGenPartonV[0] + higgsGenPartonV[1];
        higgs_genParton_mass = sum_higgs_genParton_vect.M();
      }
      if (numHiggsAllJets > 2) {
        std::cout << "First three higgs jets have pt " << higgsJetV[0].Pt() << ", " << higgsJetV[1].Pt() << ", " << higgsJetV[2].Pt() << std::endl;
      }

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
      
      float first_jet_pt = dFloat ;
      float second_jet_pt = dFloat ;
      float third_jet_pt = dFloat ;
      float fourth_jet_pt = dFloat ;
      
      float first_jet_eta = dFloat;
      float second_jet_eta = dFloat;
      float third_jet_eta = dFloat;
      float fourth_jet_eta = dFloat;

      float first_jet_CHEF = dFloat;
      float second_jet_CHEF = dFloat;
      float third_jet_CHEF = dFloat;
      float fourth_jet_CHEF = dFloat;
      float sum_jet_CHEF = dFloat;
      
      float first_jet_CSV = dFloat ;
      float second_jet_CSV = dFloat ;
      float third_jet_CSV = dFloat ;
      float fourth_jet_CSV = dFloat ;

      float first_jet_charge = dFloat;
      float second_jet_charge = dFloat;
      float third_jet_charge = dFloat;
      float fourth_jet_charge = dFloat;
      float sum_jet_charge = dFloat;
      
      float dPhi_jet1jet2 = dFloat;
      float dPhi_jet1jet3 = dFloat;
      float dPhi_jet1jet4 = dFloat;
      float dPhi_jet2jet3 = dFloat;
      float dPhi_jet2jet4 = dFloat;
      float dPhi_jet3jet4 = dFloat;

      float first_allJet_pt = dFloat ;
      float second_allJet_pt = dFloat ;
      float third_allJet_pt = dFloat ;
      float fourth_allJet_pt = dFloat ;
      
      float mindr_lep1_jet = dFloat;
      float mindr_lep2_jet = dFloat;
      float mindr_lep1_allJet = dFloat;
      float mindr_lep2_allJet = dFloat;
      float min_dr_tagged_jets = dFloat;
      float min_dr_jets = dFloat;
      
      float denom_avg_cnt = dFloat;
      float avg_btag_disc_btags = dFloat;     
      float avg_btag_disc_non_btags = dFloat;
      float highest_btag_disc_non_btags = dFloat;
      float dev_from_avg_disc_btags = dFloat;
      float first_highest_btag = dFloat;
      float second_highest_btag = dFloat;
      float lowest_btag = dFloat;

      float sum_pt = dFloat;
      float sum_jet_pt = dFloat;
      float all_sum_pt = dFloat;
      float Ht = dFloat;

      //ttbb
      float dijet_mass_first  = dFloat;
      float dijet_mass_second = dFloat;
      float dijet_mass_third  = dFloat;

      float first_dibjet_mass  = dFloat;
      float second_dibjet_mass = dFloat;
      float third_dibjet_mass  = dFloat;

      float avg_dr_jets = dFloat;
      float avg_dijet_mass = dFloat;
      float closest_dijet_mass = dFloat;
      float M2_of_closest_jets = dFloat;
     
      float avg_dr_tagged_jets = dFloat;
      float avg_tagged_dijet_mass = dFloat;
      float closest_tagged_dijet_mass = dFloat;
      float M2_of_closest_tagged_jets = dFloat;
      float min_dr_genB1_allJet = dFloat;
      float min_dr_genB2_allJet = dFloat;
      
      TLorentzVector non_btag_vect1;
      TLorentzVector non_btag_vect2;
      float avg_untagged_dijet_mass = dFloat;

      if ( PassTwoLepton ){  //////// number of jets and number of tags
	
	float lep1Pt = dFloat;
	float lep2Pt = dFloat;
	float lep1_et = dFloat;
	float lep2_et = dFloat;
	float lep1Eta = dFloat;
	float lep2Eta = dFloat;
	float lep1Phi = dFloat;
	float lep2Phi = dFloat;
    float lep1_tkDZ = dFloat;
    float lep2_tkDZ = dFloat;
    float lep1Iso = dFloat;
    float lep2Iso = dFloat;
    float lep1_correctedDZ = dFloat;
    float lep2_correctedDZ = dFloat;
    float lep1_correctedD0 = dFloat;
    float lep2_correctedD0 = dFloat;
    float lep1TkCharge = dFloat;
    float lep1GenCharge = dFloat;
    float lep2TkCharge = dFloat;
    float lep2GenCharge = dFloat;
    int lep1GenMotherId = dInt;
    int lep2GenMotherId = dInt;
    float lep1SF = dFloat;
    float lep2SF = dFloat;
    int lep2IsGlobalMuon = dInt;
    int lep2IsTrackerMuon = dInt;
    int lep2IsGlobalMuonPromptTight = dInt;
    int lep2NumTrackHits = dInt;
    int lep2NumPixelHits = dInt;
    int lep2NumberOfMatches = dInt;
    float lep2Chi2 = dFloat;
    int lep2NumExpectedHits = dInt;
    
	  if( twoTightMuon || TightMuonLooseMuon ) {
        
        lep1SF = beanHelper.GetMuonSF(muonsSelected.at(0));
        lep2SF = beanHelper.GetMuonSF(muonsSelected.at(1));

	    lep1Pt = muonsSelected.at(0).pt;
	    lep2Pt = muonsSelected.at(1).pt;
	    
	    lep1_et = muonsSelected.at(0).et;
	    lep2_et = muonsSelected.at(1).et;  

	    lep1Eta = muonsSelected.at(0).eta;
	    lep2Eta = muonsSelected.at(1).eta;  

	    lep1Phi = muonsSelected.at(0).phi;
	    lep2Phi = muonsSelected.at(1).phi;  

        lep1_tkDZ = muonsSelected.at(0).tkDZ;
        lep2_tkDZ = muonsSelected.at(1).tkDZ;

        lep1_correctedDZ = muonsSelected.at(0).correctedDZ;
        lep2_correctedDZ = muonsSelected.at(1).correctedDZ;

        lep1_correctedD0 = muonsSelected.at(0).correctedD0;
        lep2_correctedD0 = muonsSelected.at(1).correctedD0;
        
        lep1TkCharge = muonsSelected.at(0).tkCharge;
        lep2TkCharge = muonsSelected.at(1).tkCharge;

        lep1GenCharge = muonsSelected.at(0).genCharge;
        lep2GenCharge = muonsSelected.at(1).genCharge;

        lep1GenMotherId = muonsSelected.at(0).genMotherId;
        lep2GenMotherId = muonsSelected.at(1).genMotherId;

        lep2IsGlobalMuon = muonsSelected.at(1).isGlobalMuon;
        lep2IsTrackerMuon = muonsSelected.at(1).isTrackerMuon;
        lep2IsGlobalMuonPromptTight = muonsSelected.at(1).isGlobalMuonPromptTight;
        lep2NumTrackHits = muonsSelected.at(1).numberOfValidTrackerHitsInnerTrack;
        lep2NumPixelHits = muonsSelected.at(1).pixelLayersWithMeasurement;
        lep2NumberOfMatches = muonsSelected.at(1).numberOfMatchedStations;

        for (int ii=0; ii<int(muon_px.size()); ii++) {
          if (abs(muonsSelected.at(0).px-muon_px[ii])/max(abs(muonsSelected.at(0).px),10.0) < 0.3
              && abs(muonsSelected.at(0).py-muon_py[ii])/max(abs(muonsSelected.at(0).py),10.0) < 0.3
              && abs(muonsSelected.at(0).pz-muon_pz[ii])/max(abs(muonsSelected.at(0).pz),10.0) < 0.3) {
            lep1Mother = muon_mother[ii];
            lep1Grandmother = muon_grandmother[ii];
          }
          if (abs(muonsSelected.at(1).px-muon_px[ii])/max(abs(muonsSelected.at(1).px),10.0) < 0.3
              && abs(muonsSelected.at(1).py-muon_py[ii])/max(abs(muonsSelected.at(1).py),10.0) < 0.3
              && abs(muonsSelected.at(1).pz-muon_pz[ii])/max(abs(muonsSelected.at(1).pz),10.0) < 0.3) {
            lep2Mother = muon_mother[ii];
            lep2Grandmother = muon_grandmother[ii];
          }
        }

        if (selectionYearStr == "2011") {
          lep1Iso = (muonsSelected.at(0).chargedHadronIso
                      + muonsSelected.at(0).neutralHadronIso
                      + muonsSelected.at(0).photonIso) * 1.0 / lep1Pt;
          lep2Iso = (muonsSelected.at(1).chargedHadronIso
                      + muonsSelected.at(1).neutralHadronIso
                      + muonsSelected.at(1).photonIso) * 1.0 / lep2Pt;
        }
        else if (selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x") {
          lep1Iso = (muonsSelected.at(0).pfIsoR04SumChargedHadronPt
                      + max(0.0, muonsSelected.at(0).pfIsoR04SumNeutralHadronEt
                                 + muonsSelected.at(0).pfIsoR04SumPhotonEt
                                 - 0.5*muonsSelected.at(0).pfIsoR04SumPUPt)) * 1.0 /lep1Pt;
          lep2Iso = (muonsSelected.at(1).pfIsoR04SumChargedHadronPt
                      + max(0.0, muonsSelected.at(1).pfIsoR04SumNeutralHadronEt
                                 + muonsSelected.at(1).pfIsoR04SumPhotonEt
                                 - 0.5*muonsSelected.at(1).pfIsoR04SumPUPt)) * 1.0 /lep2Pt;
        }
        else {
          assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
        }
        
        lep_vect1.SetPxPyPzE(muonsSelected.at(0).px, muonsSelected.at(0).py, muonsSelected.at(0).pz, muonsSelected.at(0).energy);
	    lep_vect2.SetPxPyPzE(muonsSelected.at(1).px, muonsSelected.at(1).py, muonsSelected.at(1).pz, muonsSelected.at(1).energy);
        lep_vect1_transverse.SetPxPyPzE(muonsSelected.at(0).px, muonsSelected.at(0).py,
                                        0.0, sqrt(pow(muonsSelected.at(0).energy,2) - pow(muonsSelected.at(0).pz,2)));
        lep_vect2_transverse.SetPxPyPzE(muonsSelected.at(1).px, muonsSelected.at(1).py,
                                        0.0, sqrt(pow(muonsSelected.at(1).energy,2) - pow(muonsSelected.at(1).pz,2)));
	  }

	  if( twoTightEle || TightEleLooseEle ) {

        lep1SF = beanHelper.GetElectronSF(electronsSelected.at(0));
        lep2SF = beanHelper.GetElectronSF(electronsSelected.at(1));
	  
	    lep1Pt = electronsSelected.at(0).pt;
	    lep2Pt = electronsSelected.at(1).pt;
	    
	    lep1_et = electronsSelected.at(0).et;
	    lep2_et = electronsSelected.at(1).et;  

	    lep1Eta = electronsSelected.at(0).eta;
	    lep2Eta = electronsSelected.at(1).eta;  

	    lep1Phi = electronsSelected.at(0).phi;
	    lep2Phi = electronsSelected.at(1).phi;  

        lep1_tkDZ = electronsSelected.at(0).tkDZ;
        lep2_tkDZ = electronsSelected.at(1).tkDZ;

        lep1_correctedDZ = electronsSelected.at(0).correctedDZ;
        lep2_correctedDZ = electronsSelected.at(1).correctedDZ;

        lep1_correctedD0 = electronsSelected.at(0).correctedD0;
        lep2_correctedD0 = electronsSelected.at(1).correctedD0;
        
        lep1TkCharge = electronsSelected.at(0).tkCharge;
        lep2TkCharge = electronsSelected.at(1).tkCharge;

        lep1GenCharge = electronsSelected.at(0).genCharge;
        lep2GenCharge = electronsSelected.at(1).genCharge;
        
        for (int ii=0; ii<int(ele_px.size()); ii++) {
          if (abs(electronsSelected.at(0).px-ele_px[ii])/max(abs(electronsSelected.at(0).px),10.0) < 0.3
              && abs(electronsSelected.at(0).py-ele_py[ii])/max(abs(electronsSelected.at(0).py),10.0) < 0.3
              && abs(electronsSelected.at(0).pz-ele_pz[ii])/max(abs(electronsSelected.at(0).pz),10.0) < 0.3) {
            lep1Mother = ele_mother[ii];
            lep1Grandmother = ele_grandmother[ii];
          }
          if (abs(electronsSelected.at(1).px-ele_px[ii])/max(abs(electronsSelected.at(1).px),10.0) < 0.3
              && abs(electronsSelected.at(1).py-ele_py[ii])/max(abs(electronsSelected.at(1).py),10.0) < 0.3
              && abs(electronsSelected.at(1).pz-ele_pz[ii])/max(abs(electronsSelected.at(1).pz),10.0) < 0.3) {
            lep2Mother = ele_mother[ii];
            lep2Grandmother = ele_grandmother[ii];
          }
        }

        if (selectionYearStr == "2011") {
          lep1Iso = (electronsSelected.at(0).chargedHadronIso
                      + electronsSelected.at(0).neutralHadronIso
                      + electronsSelected.at(0).photonIso) * 1.0 / lep1Pt;
          lep2Iso = (electronsSelected.at(1).chargedHadronIso
                      + electronsSelected.at(1).neutralHadronIso
                      + electronsSelected.at(1).photonIso) * 1.0 / lep2Pt;
        }
        else if (selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x") {
          lep1Iso = ( electronsSelected.at(0).chargedHadronIso
                       + max(0.0, electronsSelected.at(0).neutralHadronIso
                                  + electronsSelected.at(0).photonIso
                                  - electronsSelected.at(0).AEffDr03*electronsSelected.at(0).rhoPrime) ) * 1.0 /lep1Pt;
          lep2Iso = ( electronsSelected.at(1).chargedHadronIso
                       + max(0.0, electronsSelected.at(1).neutralHadronIso
                                  + electronsSelected.at(1).photonIso
                                  - electronsSelected.at(1).AEffDr03*electronsSelected.at(1).rhoPrime) ) * 1.0 /lep2Pt;
        }
        else {
          assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
        }

	    lep_vect1.SetPxPyPzE(electronsSelected.at(0).px, electronsSelected.at(0).py, electronsSelected.at(0).pz, electronsSelected.at(0).energy);
	    lep_vect2.SetPxPyPzE(electronsSelected.at(1).px, electronsSelected.at(1).py, electronsSelected.at(1).pz, electronsSelected.at(1).energy);
        lep_vect1_transverse.SetPxPyPzE(electronsSelected.at(0).px, electronsSelected.at(0).py,
                                        0.0, sqrt(pow(electronsSelected.at(0).energy,2) - pow(electronsSelected.at(0).pz,2)));
	    lep_vect2_transverse.SetPxPyPzE(electronsSelected.at(1).px, electronsSelected.at(1).py,
                                        0.0, sqrt(pow(electronsSelected.at(1).energy,2) - pow(electronsSelected.at(1).pz,2)));

        lep2NumTrackHits = electronsSelected.at(1).tkNumValidHits;
        lep2NumPixelHits = electronsSelected.at(1).numberOfValidPixelBarrelHits + electronsSelected.at(1).numberOfValidPixelEndcapHits;
        lep2NumberOfMatches = electronsSelected.at(1).numClusters;
        lep2Chi2 = electronsSelected.at(1).tkNormChi2;
        lep2NumExpectedHits = electronsSelected.at(1).numberOfExpectedInnerHits;
	  }
	  
	  if( oneEleOneMuon || TightEleLooseMuon || TightMuonLooseEle){

        lep1SF = beanHelper.GetMuonSF(muonsSelected.at(0));
        lep2SF = beanHelper.GetElectronSF(electronsSelected.at(0));

	    lep1Pt = muonsSelected.at(0).pt;
	    lep2Pt = electronsSelected.at(0).pt;
	    
	    lep1_et = muonsSelected.at(0).et;
	    lep2_et = electronsSelected.at(0).et;  

	    lep1Eta = muonsSelected.at(0).eta;
	    lep2Eta = electronsSelected.at(0).eta;  

	    lep1Phi = muonsSelected.at(0).phi;
	    lep2Phi = electronsSelected.at(0).phi;  

        lep1_tkDZ = muonsSelected.at(0).tkDZ;
        lep2_tkDZ = electronsSelected.at(0).tkDZ;

        lep1_correctedDZ = muonsSelected.at(0).correctedDZ;
        lep2_correctedDZ = electronsSelected.at(0).correctedDZ;

        lep1_correctedD0 = muonsSelected.at(0).correctedD0;
        lep2_correctedD0 = electronsSelected.at(0).correctedD0;
        
        lep1TkCharge = muonsSelected.at(0).tkCharge;
        lep2TkCharge = electronsSelected.at(0).tkCharge;

        for (int ii=0; ii<int(muon_px.size()); ii++) {
          if (abs(muonsSelected.at(0).px-muon_px[ii])/max(abs(muonsSelected.at(0).px),10.0) < 0.3
              && abs(muonsSelected.at(0).py-muon_py[ii])/max(abs(muonsSelected.at(0).py),10.0) < 0.3
              && abs(muonsSelected.at(0).pz-muon_pz[ii])/max(abs(muonsSelected.at(0).pz),10.0) < 0.3) {
            lep1Mother = muon_mother[ii];
            lep1Grandmother = muon_grandmother[ii];
          }
        }
        for (int jj=0; jj<int(ele_px.size()); jj++) {
          if (abs(electronsSelected.at(0).px-ele_px[jj])/max(abs(electronsSelected.at(0).px),10.0) < 0.3
              && abs(electronsSelected.at(0).py-ele_py[jj])/max(abs(electronsSelected.at(0).py),10.0) < 0.3
              && abs(electronsSelected.at(0).pz-ele_pz[jj])/max(abs(electronsSelected.at(0).pz),10.0) < 0.3) {
            lep2Mother = ele_mother[jj];
            lep2Grandmother = ele_grandmother[jj];
          }
        }

        lep1GenCharge = muonsSelected.at(0).genCharge;
        lep2GenCharge = electronsSelected.at(0).genCharge;

        lep1GenMotherId = muonsSelected.at(0).genMotherId;
        lep2GenMotherId = electronsSelected.at(0).genMotherId;

        if (selectionYearStr == "2011") {
          lep1Iso = (muonsSelected.at(0).chargedHadronIso
                      + muonsSelected.at(0).neutralHadronIso
                      + muonsSelected.at(0).photonIso) * 1.0 / lep1Pt;
          lep2Iso = (electronsSelected.at(0).chargedHadronIso + electronsSelected.at(0).neutralHadronIso + electronsSelected.at(0).photonIso) * 1.0 / lep2Pt;
        }
        else if (selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x") {
          lep1Iso = (muonsSelected.at(0).pfIsoR04SumChargedHadronPt
                      + max(0.0, muonsSelected.at(0).pfIsoR04SumNeutralHadronEt
                                 + muonsSelected.at(0).pfIsoR04SumPhotonEt
                                 - 0.5*muonsSelected.at(0).pfIsoR04SumPUPt)) * 1.0 /lep1Pt;
          lep2Iso = ( electronsSelected.at(0).chargedHadronIso
                       + max(0.0, electronsSelected.at(0).neutralHadronIso
                                  + electronsSelected.at(0).photonIso
                                  - electronsSelected.at(0).AEffDr03*electronsSelected.at(0).rhoPrime) ) * 1.0 /lep2Pt;
        }
        else {
          assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
        }
        
	    lep_vect1.SetPxPyPzE(muonsSelected.at(0).px, muonsSelected.at(0).py, muonsSelected.at(0).pz, muonsSelected.at(0).energy);
	    lep_vect2.SetPxPyPzE(electronsSelected.at(0).px, electronsSelected.at(0).py, electronsSelected.at(0).pz, electronsSelected.at(0).energy);
        lep_vect1_transverse.SetPxPyPzE(muonsSelected.at(0).px, muonsSelected.at(0).py,
                                        0.0, sqrt(pow(muonsSelected.at(0).energy,2) - pow(muonsSelected.at(0).pz,2)));
	    lep_vect2_transverse.SetPxPyPzE(electronsSelected.at(0).px, electronsSelected.at(0).py,
                                        0.0, sqrt(pow(electronsSelected.at(0).energy,2) - pow(electronsSelected.at(0).pz,2)));

	  }


      float lepTotalSF = lep1SF * lep2SF;
      
      
      if (verbose) std::cout << "about to fill two lep vars " <<std::endl
                             << "TwoMuon = " << TwoMuon << " twoTightMuon = " << twoTightMuon << " TightMuonLooseMuon = " << TightMuonLooseMuon   << endl
                             << "TwoEle = " << TwoEle  << " twoTightEle = " << twoTightEle << " TightEleLooseEle  " << TightEleLooseEle << endl
                             << "MuonEle = " << MuonEle << " TightMuonLooseEle = " << TightMuonLooseEle << " TightEleLooseMuon = " << TightEleLooseMuon << " oneEleOneMuon = " << endl
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
	  float mass_leplep = two_lepton.M();
	  float pt_leplep = two_lepton.Pt();
	  float dPhi_leplep = lep_vect1.DeltaPhi(lep_vect2);
	  float dR_leplep = lep_vect1.DeltaR(lep_vect2);
      float dEta_leplep = lep_vect1.Eta() - lep_vect2.Eta();
      float correctedDZ_leplep = lep1_correctedDZ - lep2_correctedDZ;
      float correctedD0_leplep = lep1_correctedD0 - lep2_correctedD0;
      float tkDZ_leplep = lep1_tkDZ - lep2_tkDZ;

      int oppositeLepCharge = dInt;
      int oppositeGenLepCharge = dInt;
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

      if (sum_pt == dFloat) sum_pt = 0.0;
      if (Ht == dFloat) Ht = 0.0;
	  sum_pt += lep1Pt;
	  Ht += lep1_et ;

	  sum_pt += lep2Pt;
	  Ht += lep2_et ;
	  
	  TLorentzVector everything_vect = metV + lep_vect1 + lep_vect2 + sum_jet_vect;
      TLorentzVector leps_and_jets_vect = lep_vect1 + lep_vect2 + sum_jet_vect;
      TLorentzVector leps_and_allJets_vect = lep_vect1 + lep_vect2 + sum_allJet_vect;
      TLorentzVector allEverything_vect = leps_and_allJets_vect + metV;
      float mass_of_everything = everything_vect.M();
      float mass_MHT = leps_and_jets_vect.M();
      float mass_of_leps_and_allJets = leps_and_allJets_vect.M();
      float pt_of_everything = everything_vect.Pt();
      float pz_of_everything = everything_vect.Pz();
      float MHT = leps_and_jets_vect.Pt();
      float pt_of_leps_and_allJets = leps_and_allJets_vect.Pt();
      float pt_of_allEverything = allEverything_vect.Pt();

      /// pt of ttbar
      float pt_of_ttbar = dFloat;
      if(numTaggedJets>1){

        int bjet1 = tag_pfjet_index[0] ;
        int bjet2 = tag_pfjet_index[1] ;

        TLorentzVector bjet1_vect;
        TLorentzVector bjet2_vect;

        bjet1_vect.SetPxPyPzE(jet_px[bjet1],jet_py[bjet1],jet_pz[bjet1],jet_energy[bjet1]);
        bjet2_vect.SetPxPyPzE(jet_px[bjet2],jet_py[bjet2],jet_pz[bjet2],jet_energy[bjet2]);

        TLorentzVector ttbar_vect = metV + lep_vect1 + lep_vect2 + bjet1_vect + bjet2_vect;
        pt_of_ttbar = ttbar_vect.Pt();
        
      } 

	  ///loop jet

      for (int i=0; i<numGoodAndBadJets; i++) {
        allJet_vect.SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
        if (HtoBB == 1) {
          if (higgsGenBV[0].DeltaR(allJet_vect) < min_dr_genB1_allJet || min_dr_genB1_allJet == dFloat) {
            min_dr_genB1_allJet = higgsGenBV[0].DeltaR(allJet_vect);
          }
          if (higgsGenBV[1].DeltaR(allJet_vect) < min_dr_genB2_allJet || min_dr_genB2_allJet == dFloat) {
            min_dr_genB2_allJet = higgsGenBV[1].DeltaR(allJet_vect);
          }
        }
        
	    if (i==0)  first_allJet_pt = jet_pt[i];
	    if (i==1)  second_allJet_pt = jet_pt[i];
	    if (i==2)  third_allJet_pt = jet_pt[i];
	    if (i==3)  fourth_allJet_pt = jet_pt[i];
        
	    if (mindr_lep1_allJet > lep_vect1.DeltaR(allJet_vect) || mindr_lep1_allJet == dFloat){
	      mindr_lep1_allJet = lep_vect1.DeltaR(allJet_vect); 
	    }

	    if (mindr_lep2_allJet > lep_vect2.DeltaR(allJet_vect) || mindr_lep2_allJet == dFloat){
	      mindr_lep2_allJet = lep_vect2.DeltaR(allJet_vect); 
	    }
        for (int j=i+1; j < numGoodAndBadJets; j++) {
          sum_higgsLike_allDijet_vect = allJetV[i] + allJetV[j];
          higgsLike_allDijet_mass2 = sum_higgsLike_allDijet_vect.M();
          if (pfjetsSelected.at(i).btagCombinedSecVertex > 0.679 || pfjetsSelected.at(j).btagCombinedSecVertex > 0.679) {
            if (fabs(125 - higgsLike_allDijet_mass1) > fabs(125 - higgsLike_allDijet_mass2) || higgsLike_allDijet_mass1 == dFloat) {
              higgsLike_allDijet_mass1 = higgsLike_allDijet_mass2;
            }
          }
          if (pfjetsSelected.at(i).btagCombinedSecVertex <= 0.679 && pfjetsSelected.at(j).btagCombinedSecVertex <= 0.679) {
            if (fabs(81 - wLike_allDijet_mass1) > fabs(81 - higgsLike_allDijet_mass2) || wLike_allDijet_mass1 == dFloat) {
              wLike_allDijet_mass1 = higgsLike_allDijet_mass2;
            }
          }
          for (int k=j+1; k < numGoodAndBadJets; k++) {
            sum_topLike_allTrijet_vect = allJetV[i] + allJetV[j] + allJetV[k];
            topLike_allTrijet_mass2 = sum_topLike_allTrijet_vect.M();
            if ((pfjetsSelected.at(i).btagCombinedSecVertex <= 0.679 && pfjetsSelected.at(j).btagCombinedSecVertex <= 0.679)
                || (pfjetsSelected.at(i).btagCombinedSecVertex <= 0.679 && pfjetsSelected.at(k).btagCombinedSecVertex <= 0.679)
                || (pfjetsSelected.at(j).btagCombinedSecVertex <= 0.679 && pfjetsSelected.at(k).btagCombinedSecVertex <= 0.679)) {
              if (fabs(160 - topLike_allTrijet_mass1) > fabs(160 - topLike_allTrijet_mass2) || topLike_allTrijet_mass1 == dFloat) {
                topLike_allTrijet_mass1 = topLike_allTrijet_mass2;
              }
            }
          }
          
        }
      }

        

	  for (int i=0; i < numGoodJets; i++) {
	    int iJet = tight_pfjet_index[i] ;
        if (sum_jet_pt == dFloat) sum_jet_pt = 0.0;
        if (sum_jet_CHEF == dFloat) sum_jet_CHEF = 0.0;
        if (sum_jet_charge == dFloat) sum_jet_charge = 0.0;

	    sum_pt += jet_pt[iJet];
        sum_jet_pt += jet_pt[iJet];
	    Ht += jet_energy[iJet];
        float iJet_csvVal = good_jet_tag[i];
        sum_jet_CHEF += jet_CHEF[iJet];
        sum_jet_charge += jet_charge[iJet];
	    
	    jet_vect.SetPxPyPzE(jet_px[iJet],jet_py[iJet],jet_pz[iJet],jet_energy[iJet]);

        for (int j=i+1; j < numGoodJets; j++) {
          sum_higgsLike_dijet_vect = jetV[i] + jetV[j];
          higgsLike_dijet_mass2 = sum_higgsLike_dijet_vect.M();
          if (pfjetsSelected.at(iJet).btagCombinedSecVertex > 0.679
              || pfjetsSelected.at(tight_pfjet_index[j]).btagCombinedSecVertex > 0.679) {
            if (fabs(125 - higgsLike_dijet_mass1) > fabs(125 - higgsLike_dijet_mass2)
                || higgsLike_dijet_mass1 == dFloat) {
              higgsLike_dijet_mass1 = higgsLike_dijet_mass2;
              higgsLike_dijet_dR = jetV[i].DeltaR(jetV[j]);
              higgsLike_dijet_pt = sum_higgsLike_dijet_vect.Pt();
              higgsLike_dijet_eta = sum_higgsLike_dijet_vect.Eta();
              higgsLike_dijet_jet1_pt = max(jetV[i].Pt(),jetV[j].Pt());
              higgsLike_dijet_jet2_pt = min(jetV[i].Pt(),jetV[j].Pt());
            }
            if (fabs(125 - higgsLike_dijet_mass2) < 10) numHiggsLike_dijet_10++;
            if (fabs(125 - higgsLike_dijet_mass2) < 15) numHiggsLike_dijet_15++;
            if (fabs(125 - higgsLike_dijet_mass2) < 20) numHiggsLike_dijet_20++;
            if (fabs(125 - higgsLike_dijet_mass2) < 25) numHiggsLike_dijet_25++;
            if (pfjetsSelected.at(iJet).btagCombinedSecVertex > 0.679
                && pfjetsSelected.at(tight_pfjet_index[j]).btagCombinedSecVertex > 0.679) {
              if (fabs(125 - higgsLike_diBjet_mass1) > fabs(125 - higgsLike_dijet_mass2)
                  || higgsLike_diBjet_mass1 == dFloat)  higgsLike_diBjet_mass1 = higgsLike_dijet_mass2;
              if (fabs(125 - higgsLike_dijet_mass2) < 10) numHiggsLike_diBjet_10++;
              if (fabs(125 - higgsLike_dijet_mass2) < 15) numHiggsLike_diBjet_15++;
              if (fabs(125 - higgsLike_dijet_mass2) < 20) numHiggsLike_diBjet_20++;
              if (fabs(125 - higgsLike_dijet_mass2) < 25) numHiggsLike_diBjet_25++;
            }
          }
          if (pfjetsSelected.at(iJet).btagCombinedSecVertex <= 0.679
              && pfjetsSelected.at(tight_pfjet_index[j]).btagCombinedSecVertex <= 0.679) {
            if (fabs(81 - wLike_dijet_mass1) > fabs(81 - higgsLike_dijet_mass2) || wLike_dijet_mass1 == dFloat) {
              wLike_dijet_mass1 = higgsLike_dijet_mass2;
            }
          }
          for (int k=j+1; k < numGoodJets; k++) {
            sum_topLike_trijet_vect = jetV[i] + jetV[j] + jetV[k];
            topLike_trijet_mass2 = sum_topLike_trijet_vect.M();
            if ((pfjetsSelected.at(iJet).btagCombinedSecVertex <= 0.679 && pfjetsSelected.at(tight_pfjet_index[j]).btagCombinedSecVertex <= 0.679)
                || (pfjetsSelected.at(iJet).btagCombinedSecVertex <= 0.679 && pfjetsSelected.at(tight_pfjet_index[k]).btagCombinedSecVertex <= 0.679)
                || (pfjetsSelected.at(tight_pfjet_index[j]).btagCombinedSecVertex <= 0.679 && pfjetsSelected.at(tight_pfjet_index[k]).btagCombinedSecVertex <= 0.679)) {
              if (fabs(160 - topLike_trijet_mass1) > fabs(160 - topLike_trijet_mass2) || topLike_trijet_mass1 == dFloat) {
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
          first_jet_CSV = pfjetsSelected.at(iJet).btagCombinedSecVertex;
        }
	    if (i==1)  {
          second_jet_pt = jet_pt[iJet];
          second_jet_eta = jet_vect.Eta();
          second_jet_CHEF = jet_CHEF[iJet];
          second_jet_charge = jet_charge[iJet];
          second_jet_CSV = pfjetsSelected.at(iJet).btagCombinedSecVertex;
        }
	    if (i==2)  {
          third_jet_pt = jet_pt[iJet];
          third_jet_eta = jet_vect.Eta();
          third_jet_CHEF = jet_CHEF[iJet];
          third_jet_charge = jet_charge[iJet];
          third_jet_CSV = pfjetsSelected.at(iJet).btagCombinedSecVertex;
        }
	    if (i==3)  {
          fourth_jet_pt = jet_pt[iJet];
          fourth_jet_eta = jet_vect.Eta();
          fourth_jet_CHEF = jet_CHEF[iJet];
          fourth_jet_charge = jet_charge[iJet];
          fourth_jet_CSV = pfjetsSelected.at(iJet).btagCombinedSecVertex;
        }
	    
	    if (mindr_lep1_jet > lep_vect1.DeltaR(jet_vect) || mindr_lep1_jet == dFloat){
	      mindr_lep1_jet = lep_vect1.DeltaR(jet_vect); 
	    }
	    
	    if (mindr_lep2_jet > lep_vect2.DeltaR(jet_vect) || mindr_lep2_jet == dFloat){
	      mindr_lep2_jet = lep_vect2.DeltaR(jet_vect); 
	    }
	    
	    if (iJet_csvVal > 0.679){
          if (avg_btag_disc_btags == dFloat) avg_btag_disc_btags = 0.0;
	      avg_btag_disc_btags += iJet_csvVal;
	    }
	    
	    if (iJet_csvVal <= 0.679){
          if (avg_btag_disc_non_btags == dFloat) avg_btag_disc_non_btags = 0.0;
	      avg_btag_disc_non_btags += iJet_csvVal;
          highest_btag_disc_non_btags = max(highest_btag_disc_non_btags,iJet_csvVal);
	    }									
	  } // End of loop over numGoodJets
	  
	  if ( numTaggedJets > 0 ) avg_btag_disc_btags /= numTaggedJets;
	  
	  if ((numGoodJets - numTaggedJets) != 0){
	    avg_btag_disc_non_btags /= (numGoodJets - numTaggedJets);
	  }
	  
	  for (int l=0; l < numTaggedJets; l++){
        if (dev_from_avg_disc_btags == dFloat) dev_from_avg_disc_btags = 0.0;
        dev_from_avg_disc_btags += pow((tag_pfjet_csvVal[l] - avg_btag_disc_btags),2);
	  }
	  if ( numTaggedJets > 0 ) dev_from_avg_disc_btags /= numTaggedJets;

	  /////
	  all_sum_pt = sum_pt + MHT;
	  Ht += MHT;

      /// Ht re-weighting
      float HtWgt = dFloat;
      float HtWgtUp = dFloat;
      ////////////// mistake  for 2011
      if (!isData){
        if (sum_jet_pt == dFloat) sum_jet_pt = 0.0;
        if(selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x"){
          if (numPV<11)  HtWgt = h_rwt_lowPV->GetBinContent(h_rwt_lowPV->FindBin(sum_jet_pt));
          else if (10<numPV && numPV<16)  HtWgt = h_rwt_medPV->GetBinContent(h_rwt_medPV->FindBin(sum_jet_pt));
          else   HtWgt = h_rwt_highPV->GetBinContent(h_rwt_highPV->FindBin(sum_jet_pt));
        }
        else if(selectionYearStr == "2011") {  /// 2011
          if (numPV<6)  HtWgt = h_rwt_lowPV->GetBinContent(h_rwt_lowPV->FindBin(sum_jet_pt));
          else if (5<numPV && numPV<9)  HtWgt = h_rwt_medPV->GetBinContent(h_rwt_medPV->FindBin(sum_jet_pt));
          else   HtWgt = h_rwt_highPV->GetBinContent(h_rwt_highPV->FindBin(sum_jet_pt));
        }
        else {
          assert (selectionYearStr == "either 2012_52x, 2012_53x, or 2011");
        }
        
        HtWgtUp = 1 + 2*(HtWgt - 1);
        if (sum_jet_pt == 0.0) sum_jet_pt = dFloat;
      }

      bool passBigDiamondZmask = (MuonEle || (mass_leplep < (65.5 + 3*MHT/8)) || (mass_leplep > (108 - MHT/4)) || (mass_leplep < (79 - 3*MHT/4)) || (mass_leplep > (99 + MHT/2)) );
      bool passBigDiamondZmask2 = (mass_leplep < (65.5 + 3*met/8)) || (mass_leplep > (108 - met/4)) || (mass_leplep < (79 - 3*met/4)) || (mass_leplep > (99 + met/2));
      bool passBigDiamondZmask3 = (mass_leplep < (65.5 + 3*pt_of_leps_and_allJets/8)) || (mass_leplep > (108 - pt_of_leps_and_allJets/4)) || (pt_of_leps_and_allJets < (79 - 3*pt_of_leps_and_allJets/4)) || (mass_leplep > (99 + pt_of_leps_and_allJets/2));

	  //// tagged jets
	  float deltaHMass = 9999. ;
	  float deltaHMass2 = 9999. ;
      denom_avg_cnt = 0.0;
	  if (numTaggedJets > 1) {
	    for (int j=0; j < (numTaggedJets - 1); j++) {
	      int jbtag = tag_pfjet_index[j] ;
	      btag_vect1.SetPxPyPzE(jet_px[jbtag],jet_py[jbtag],jet_pz[jbtag],jet_energy[jbtag]);
	      
	      for (int k=j+1; k < numTaggedJets; k++) {
		int kbtag = tag_pfjet_index[k] ; 
		btag_vect2.SetPxPyPzE(jet_px[kbtag],jet_py[kbtag],jet_pz[kbtag],jet_energy[kbtag]);
		
		dijet_vect = btag_vect1 + btag_vect2;
        if (avg_tagged_dijet_mass == dFloat) avg_tagged_dijet_mass = 0.0;
		avg_tagged_dijet_mass += dijet_vect.M();
        if (avg_dr_tagged_jets == dFloat) avg_dr_tagged_jets = 0.0;
		avg_dr_tagged_jets += btag_vect1.DeltaR(btag_vect2);
		++denom_avg_cnt;		      
		
		if (min_dr_tagged_jets > btag_vect1.DeltaR(btag_vect2) || min_dr_tagged_jets == dFloat){
		  min_dr_tagged_jets = btag_vect1.DeltaR(btag_vect2);
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
		
	      } // End loop for k < numTaggedJets
	    } // End loop for j < numTaggedJets
	    
	    avg_tagged_dijet_mass /= denom_avg_cnt; 
	    avg_dr_tagged_jets /= denom_avg_cnt;
	    
	    ///// ttbb bkg

	    dibjet_mass_combinations.sort();
	    std::vector<float> dibjet_mass_sort_vect;
	    std::list<float>::iterator listintaa;
	    for (listintaa = dibjet_mass_combinations.begin(); listintaa != dibjet_mass_combinations.end(); listintaa++){
	      dibjet_mass_sort_vect.push_back(*listintaa);  //accessible form
	    }
	    int numCom = dibjet_mass_sort_vect.size();
        if (numCom > 0) first_dibjet_mass  = dibjet_mass_sort_vect[numCom - 1];
        if (numCom > 1) second_dibjet_mass = dibjet_mass_sort_vect[numCom - 2];
        if (numCom > 2) third_dibjet_mass  = dibjet_mass_sort_vect[numCom - 3];

	  } // End if numTaggedJets > 1

	  
	  ////non_tagged jets
	  
	  denom_avg_cnt = 0.0;
	  int nonTags = untag_pfjet_index.size();
	  if (nonTags > 1){
	    for (int m=0; m < (nonTags - 1); m++){
	      int untag1 = untag_pfjet_index[m];
	      non_btag_vect1.SetPxPyPzE(jet_px[untag1],jet_py[untag1],jet_pz[untag1],jet_energy[untag1]);
	      for (int n=m+1; n < nonTags; n++){
		int untag2 = untag_pfjet_index[n];
		non_btag_vect2.SetPxPyPzE(jet_px[untag2],jet_py[untag2],jet_pz[untag2],jet_energy[untag2]);
		
		dijet_vect = non_btag_vect1 + non_btag_vect2;
        if (avg_untagged_dijet_mass == dFloat) avg_untagged_dijet_mass = 0.0;
		avg_untagged_dijet_mass += dijet_vect.M();
		++denom_avg_cnt;
	      }
	    }
	  
	    avg_untagged_dijet_mass /= denom_avg_cnt;
	  } // End if nonTags > 1

	  
	  ///// ttbb dijet_mass
	  denom_avg_cnt = 0.0;
	  if(numJets > 1 ){
	    for (int j=0; j < (numJets - 1); j++) {
	      int jJet = tight_pfjet_index[j] ;
	      jet_vect1.SetPxPyPzE(jet_px[jJet],jet_py[jJet],jet_pz[jJet],jet_energy[jJet]);
	      
	      for (int k=j+1; k < numJets; k++) {
		int kJet = tight_pfjet_index[k] ; 
		jet_vect2.SetPxPyPzE(jet_px[kJet],jet_py[kJet],jet_pz[kJet],jet_energy[kJet]);
		
		dijet_vect = jet_vect1 + jet_vect2;
        if (avg_dijet_mass == dFloat) avg_dijet_mass = 0.0;
		avg_dijet_mass += dijet_vect.M();
        if (avg_dr_jets == dFloat) avg_dr_jets = 0.0;
		avg_dr_jets += jet_vect1.DeltaR(jet_vect2);
		++denom_avg_cnt;		      
		
		if (min_dr_jets > jet_vect1.DeltaR(jet_vect2) || min_dr_jets == dFloat){
		  min_dr_jets = jet_vect1.DeltaR(jet_vect2);
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
	    }

	  }

	  ////
      
	  
	  if (numTaggedJets > 0 ){
	    first_highest_btag = jet_CSV_sorted_vect[numTaggedJets - 1];
	    if (numTaggedJets > 1) second_highest_btag = jet_CSV_sorted_vect[numTaggedJets - 2];
	    lowest_btag = jet_CSV_sorted_vect[0];	    
	  }

      //------------------------------------------
      //
      // Assign values to the vars the MVA will use
      // 
      //------------------------------------------

      varfirst_jet_pt = first_jet_pt;
      varmin_dr_tagged_jets 		  = min_dr_tagged_jets;  
      varnumJets_float 		  = float(numJets);       
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

      if (CoreVariables) {

        //event variables
        *(intBranches["PassTwoLepton"]) =  PassTwoLepton ? 1 : 0;
        *(intBranches["TwoMuon"]) = TwoMuon ? 1 : 0;
        *(intBranches["TwoEle"]) =  TwoEle ? 1 : 0;
        *(intBranches["MuonEle"]) = MuonEle ? 1 : 0;

        *(intBranches["numTightMuons"]) = numTightMuons;
        *(intBranches["numLooseMuons"]) = numLooseMuons;
        *(intBranches["numTightElectrons"]) = numTightElectrons;
        *(intBranches["numLooseElectrons"]) = numLooseElectrons;

        *(intBranches["numJets"]) = numJets ;
        *(intBranches["numTaggedJets"]) = numTaggedJets;
        *(floatBranches["numJets_float"]) = float(numJets);
        *(floatBranches["numTaggedJets_float"]) = float(numTaggedJets);

        *(intBranches["isCleanEvent"]) = isCleanEvent ? 1 : 0;
        *(intBranches["isTriggerPass"]) = isTriggerPass ? 1 : 0;
        *(intBranches["isDoubleMuTriggerPass"]) = isDoubleMuTriggerPass ? 1 : 0;
        *(intBranches["isDoubleElectronTriggerPass"]) = isDoubleElectronTriggerPass ? 1 : 0;
        *(intBranches["isMuEGTriggerPass"]) = isMuEGTriggerPass ? 1 : 0;
        *(intBranches["isMETTriggerPass"]) = isMETTriggerPass ? 1 : 0;

        *(intBranches["PassZmask"]) = passBigDiamondZmask ? 1 : 0;
        *(intBranches["PassZmask2"]) = passBigDiamondZmask2 ? 1 : 0;

        *(intBranches["oppositeLepCharge"]) = oppositeLepCharge;
        *(intBranches["oppositeGenLepCharge"]) = oppositeGenLepCharge;
        
        *(uintBranches["runNumber"]) = event->run ;
        *(uintBranches["luminosityBlock"]) = event->lumi ;
        *(uintBranches["eventNumber"]) = unsigned(event->evt) ;

        //pile up
        *(floatBranches["numPV"]) = numPV ;
        *(floatBranches["numTruePV"]) = numTruePV;
        *(floatBranches["numGenPV"]) = numGenPV;

        //weights
        *(floatBranches["weight"]) = weight ;
        *(floatBranches["weight_PUup"]) = weight_PUup ;
        *(floatBranches["weight_PUdown"]) = weight_PUdown ;
        *(floatBranches["HtWgt"]) = HtWgt;
        *(floatBranches["HtWgtUp"]) = HtWgtUp;
        *(floatBranches["Q2ScaleUpWgt"]) = Q2ScaleUpWgt;
        *(floatBranches["Q2ScaleDownWgt"]) = Q2ScaleDownWgt;
        *(floatBranches["lep1SF"]) = lep1SF;
        *(floatBranches["lep2SF"]) = lep2SF;
        *(floatBranches["lepTotalSF"]) = lepTotalSF;

        //met
        *(floatBranches["met"]) = met;
        *(floatBranches["unc_met"]) = unc_met;
        *(floatBranches["MHT"]) = MHT;

        //lepton variables
        *(floatBranches["lep1Pt"]) =  lep1Pt;
        *(floatBranches["lep2Pt"]) =  lep2Pt;
        *(floatBranches["lep1Eta"]) = lep1Eta;
        *(floatBranches["lep2Eta"]) = lep2Eta;
        *(floatBranches["lep1Phi"]) = lep1Phi;
        *(floatBranches["lep2Phi"]) = lep2Phi;
        *(floatBranches["lep1Iso"]) = lep1Iso;
        *(floatBranches["lep2Iso"]) = lep2Iso;
        *(floatBranches["lep1TkCharge"]) = lep1TkCharge;
        *(floatBranches["lep2TkCharge"]) = lep2TkCharge;
        *(floatBranches["lep1GenCharge"]) = lep1GenCharge;
        *(floatBranches["lep2GenCharge"]) = lep2GenCharge;

        // jet variables
        *(floatBranches["first_jet_pt"]) = first_jet_pt;
        *(floatBranches["second_jet_pt"]) = second_jet_pt;
        *(floatBranches["third_jet_pt"]) = third_jet_pt;
        *(floatBranches["fourth_jet_pt"]) = fourth_jet_pt;
        
        *(floatBranches["first_jet_eta"]) = first_jet_eta;
        *(floatBranches["second_jet_eta"]) = second_jet_eta;
        *(floatBranches["third_jet_eta"]) = third_jet_eta;
        *(floatBranches["fourth_jet_eta"]) = fourth_jet_eta;

        //kinematic variables
        ////ANN neural net inputs
        *(floatBranches["mass_of_everything"]) = mass_of_everything;
	    *(floatBranches["min_dr_tagged_jets"]) = min_dr_tagged_jets;
        *(floatBranches["mindr_lep1_jet"]) = mindr_lep1_jet;
        *(floatBranches["avg_btag_disc_btags"]) = avg_btag_disc_btags;
        *(floatBranches["Ht"]) = Ht;
        ////leptons
        *(floatBranches["mass_leplep"]) = mass_leplep;
        *(floatBranches["pt_leplep"]) = pt_leplep;
        *(floatBranches["dPhi_leplep"]) = dPhi_leplep;
        *(floatBranches["dR_leplep"]) = dR_leplep;
        *(floatBranches["correctedDZ_leplep"]) = correctedDZ_leplep;
        *(floatBranches["correctedD0_leplep"]) = correctedD0_leplep;
        *(floatBranches["tkDZ_leplep"]) = tkDZ_leplep;
        *(floatBranches["mindr_lep2_jet"]) = mindr_lep2_jet;
        ////everything
        *(floatBranches["sum_pt"]) = sum_pt;
        *(floatBranches["sum_jet_pt"]) = sum_jet_pt;
        *(floatBranches["pt_of_everything"]) = pt_of_everything;
        *(floatBranches["pz_of_everything"]) = pz_of_everything;

      } //End if (CoreVariables)
        
        
      if (ExtraHiggsVariables) {

        *(intBranches["numHiggsJets"]) = numHiggsJets;
        *(intBranches["numHiggsAllJets"]) = numHiggsAllJets;
        *(intBranches["HiggsDecayMode"]) = HtoCC*4 + HtoBB*5 + HtoTT*15 + HtoGG*21 + HtoZZ*23 + HtoWW*24;
        *(floatBranches["higgs_pt"]) = higgs_pt;
        *(floatBranches["higgs_pz"]) = higgs_pz;
        *(floatBranches["higgs_genJet_mass"]) = higgs_genJet_mass;
        *(floatBranches["higgs_genParton_mass"]) = higgs_genParton_mass;
        *(floatBranches["higgsLike_dijet_mass"]) = higgsLike_dijet_mass1;
        *(floatBranches["higgsLike_diBjet_mass"]) = higgsLike_diBjet_mass1;
        *(floatBranches["higgsLike_allDijet_mass"]) = higgsLike_allDijet_mass1;
        *(floatBranches["higgsLike_dijet_dR"]) = higgsLike_dijet_dR;
        *(floatBranches["higgsLike_dijet_pt"]) = higgsLike_dijet_pt;
        *(floatBranches["higgsLike_dijet_eta"]) = higgsLike_dijet_eta;
        *(floatBranches["higgsLike_dijet_jet1_pt"]) = higgsLike_dijet_jet1_pt;
        *(floatBranches["higgsLike_dijet_jet2_pt"]) = higgsLike_dijet_jet2_pt;
        *(intBranches["numHiggsLike_dijet_10"]) = numHiggsLike_dijet_10;
        *(intBranches["numHiggsLike_dijet_15"]) = numHiggsLike_dijet_15;
        *(intBranches["numHiggsLike_dijet_20"]) = numHiggsLike_dijet_20;
        *(intBranches["numHiggsLike_dijet_25"]) = numHiggsLike_dijet_25;
        *(intBranches["numHiggsLike_diBjet_10"]) = numHiggsLike_diBjet_10;
        *(intBranches["numHiggsLike_diBjet_15"]) = numHiggsLike_diBjet_15;
        *(intBranches["numHiggsLike_diBjet_20"]) = numHiggsLike_diBjet_20;
        *(intBranches["numHiggsLike_diBjet_25"]) = numHiggsLike_diBjet_25;
        
        *(floatBranches["higgs_dijet_mass"]) = higgs_dijet_mass;
        *(floatBranches["higgs_dijet_pt"]) = higgs_dijet_pt;
        *(floatBranches["higgs_dijet_pz"]) = higgs_dijet_pz;
        *(floatBranches["higgs_dijet_dR"]) = higgs_dijet_dR;
        *(floatBranches["higgs_dijet_dPhi"]) = higgs_dijet_dPhi;
        *(floatBranches["higgs_dijet_jet1_pt"]) = higgs_dijet_jet1_pt;
        *(floatBranches["higgs_dijet_jet2_pt"]) = higgs_dijet_jet2_pt;
        *(floatBranches["higgs_dijet_jet1_eta"]) = higgs_dijet_jet1_eta;
        *(floatBranches["higgs_dijet_jet2_eta"]) = higgs_dijet_jet2_eta;
        *(floatBranches["higgs_dijet_jet1_csv"]) = higgs_dijet_jet1_csv;
        *(floatBranches["higgs_dijet_jet2_csv"]) = higgs_dijet_jet2_csv;
        *(floatBranches["higgs_dijet_jet1_Nconst"]) = higgs_dijet_jet1_Nconst;
        *(floatBranches["higgs_dijet_jet2_Nconst"]) = higgs_dijet_jet2_Nconst;
        *(floatBranches["higgs_dijet_jet1_btagSoftMuon"]) = higgs_dijet_jet1_btagSoftMuon;
        *(floatBranches["higgs_dijet_jet2_btagSoftMuon"]) = higgs_dijet_jet2_btagSoftMuon;
        *(floatBranches["higgs_dijet_jet1_btagSoftEle"]) = higgs_dijet_jet1_btagSoftEle;
        *(floatBranches["higgs_dijet_jet2_btagSoftEle"]) = higgs_dijet_jet2_btagSoftEle;
        *(floatBranches["higgs_dijet_jet1_leadCandPt"]) = higgs_dijet_jet1_leadCandPt;
        *(floatBranches["higgs_dijet_jet2_leadCandPt"]) = higgs_dijet_jet2_leadCandPt;
        *(floatBranches["higgs_dijet_jet1_leadCandDistFromPV"]) = higgs_dijet_jet1_leadCandDistFromPV;
        *(floatBranches["higgs_dijet_jet2_leadCandDistFromPV"]) = higgs_dijet_jet2_leadCandDistFromPV;
        *(floatBranches["higgs_dijet_genJet1_pt"]) = higgs_dijet_genJet1_pt;
        *(floatBranches["higgs_dijet_genJet2_pt"]) = higgs_dijet_genJet2_pt;
        *(floatBranches["higgs_dijet_genParton1_pt"]) = higgs_dijet_genParton1_pt;
        *(floatBranches["higgs_dijet_genParton2_pt"]) = higgs_dijet_genParton2_pt;
        *(floatBranches["higgs_dijet_jet1_muon_dR"]) = higgs_dijet_jet1_muon_dR;
        *(floatBranches["higgs_dijet_jet2_muon_dR"]) = higgs_dijet_jet2_muon_dR;
        *(floatBranches["higgs_dijet_jet1_electron_dR"]) = higgs_dijet_jet1_electron_dR;
        *(floatBranches["higgs_dijet_jet2_electron_dR"]) = higgs_dijet_jet2_electron_dR;
        *(floatBranches["higgs_dijet_jet1_track_dR"]) = higgs_dijet_jet1_track_dR;
        *(floatBranches["higgs_dijet_jet2_track_dR"]) = higgs_dijet_jet2_track_dR;
        *(floatBranches["higgs_dijet_jet1_track_pt"]) = higgs_dijet_jet1_track_pt;
        *(floatBranches["higgs_dijet_jet2_track_pt"]) = higgs_dijet_jet2_track_pt;
        
      } //End if (ExtraHiggsVariables)

      if (ExtraJetVariables) {

        *(intBranches["numAllJets"]) = numAllJet;

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

        *(floatBranches["first_jet_CSV"]) = first_jet_CSV;
        *(floatBranches["second_jet_CSV"]) = second_jet_CSV;
        *(floatBranches["third_jet_CSV"]) = third_jet_CSV;
        *(floatBranches["fourth_jet_CSV"]) = fourth_jet_CSV;

        *(floatBranches["dPhi_jet1jet2"]) = dPhi_jet1jet2;
        *(floatBranches["dPhi_jet1jet3"]) = dPhi_jet1jet3;
        *(floatBranches["dPhi_jet1jet4"]) = dPhi_jet1jet4;
        *(floatBranches["dPhi_jet2jet3"]) = dPhi_jet2jet3;
        *(floatBranches["dPhi_jet2jet4"]) = dPhi_jet2jet4;
        *(floatBranches["dPhi_jet3jet4"]) = dPhi_jet3jet4;

        *(floatBranches["first_allJet_pt"]) = first_allJet_pt;
        *(floatBranches["second_allJet_pt"]) = second_allJet_pt;
        *(floatBranches["third_allJet_pt"]) = third_allJet_pt;
        *(floatBranches["fourth_allJet_pt"]) = fourth_allJet_pt;

        *(floatBranches["first_dibjet_mass"]) =  first_dibjet_mass;
        *(floatBranches["second_dibjet_mass"]) = second_dibjet_mass;
        *(floatBranches["third_dibjet_mass"]) =  third_dibjet_mass;

	    *(floatBranches["dijet_mass_m2H"]) = dijet_mass_m2H;
        *(floatBranches["dijet_mass_first"]) =  dijet_mass_first;
        *(floatBranches["dijet_mass_second"]) = dijet_mass_second;
        *(floatBranches["dijet_mass_third"]) =  dijet_mass_third;

        *(floatBranches["min_dr_genB1_allJet"]) = min_dr_genB1_allJet;
        *(floatBranches["min_dr_genB2_allJet"]) = min_dr_genB2_allJet;

      } //End if (ExtraJetVariables)
        
      if (ExtraTriggerVariables) {
      
        *(intBranches["isTriggerPassPrescaled"]) = isTriggerPassPrescaled ? 1 : 0;
        *(intBranches["isDoubleMuTriggerPS0"]) = isDoubleMuTriggerPS0 ? 1 : 0;
        *(intBranches["isDoubleElectronTriggerPS0"]) = isDoubleElectronTriggerPS0 ? 1 : 0;
        *(intBranches["isMuEGTriggerPS0"]) = isMuEGTriggerPS0 ? 1 : 0;
        *(intBranches["isMETTriggerPS0"]) = isMETTriggerPS0 ? 1 : 0;

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

      } //End if (ExtraTriggerVariables)

      if (ExtraGenVariables) {

        *(intBranches["lep1Mother"]) = lep1Mother;
        *(intBranches["lep2Mother"]) = lep2Mother;
        *(intBranches["lep1Grandmother"]) = lep1Grandmother;
        *(intBranches["lep2Grandmother"]) = lep2Grandmother;
        *(intBranches["lep1GenMotherId"]) = lep1GenMotherId;
        *(intBranches["lep2GenMotherId"]) = lep2GenMotherId;
        *(floatBranches["top1_pt"]) = top1_pt;
        *(floatBranches["top1_pz"]) = top1_pz;

      } //End if (ExtraGenVariables)
      

      if (ExtraKinematicVariables) {
        ////objects
        *(floatBranches["wLike_dijet_mass"]) = wLike_dijet_mass1;
        *(floatBranches["topLike_trijet_mass"]) = topLike_trijet_mass1;
	    *(floatBranches["m2H_btag"]) = m2H_btag;        
        *(floatBranches["wLike_allDijet_mass"]) = wLike_allDijet_mass1;
        *(floatBranches["topLike_allTrijet_mass"]) = topLike_allTrijet_mass1;
        *(floatBranches["pt_of_ttbar"]) = pt_of_ttbar;

        ////leptons
        *(floatBranches["dEta_leplep"]) = dEta_leplep;
        *(floatBranches["mindr_lep1_allJet"]) = mindr_lep1_allJet;
        *(floatBranches["mindr_lep2_allJet"]) = mindr_lep2_allJet;
        *(floatBranches["MT_met_lep1"]) = mass_met_lep1_transverse;
        *(floatBranches["MT_met_lep2"]) = mass_met_lep2_transverse;
        *(floatBranches["dPhi_met_lep1"]) = dPhi_met_lep1;
        *(floatBranches["dPhi_met_lep2"]) = dPhi_met_lep2;
        ////everything
        *(intBranches["PassZmask3"]) = passBigDiamondZmask3 ? 1 : 0;

        *(floatBranches["min_dr_jets"]) = min_dr_jets;
	    *(floatBranches["avg_dr_jets"]) = avg_dr_jets;
	    *(floatBranches["avg_dr_tagged_jets"]) = avg_dr_tagged_jets;
	    *(floatBranches["avg_tagged_dijet_mass"]) = avg_tagged_dijet_mass;
        *(floatBranches["avg_untagged_dijet_mass"]) = avg_untagged_dijet_mass;

	    *(floatBranches["avg_dijet_mass"]) = avg_dijet_mass;
	    *(floatBranches["M2_of_closest_jets"]) = M2_of_closest_jets;
	    *(floatBranches["M2_of_closest_tagged_jets"]) = M2_of_closest_tagged_jets;
	    *(floatBranches["closest_dijet_mass"]) = closest_dijet_mass;
        *(floatBranches["closest_tagged_dijet_mass"]) = closest_tagged_dijet_mass;

        *(floatBranches["avg_btag_disc_non_btags"]) = avg_btag_disc_non_btags;
        *(floatBranches["highest_btag_disc_non_btags"]) = highest_btag_disc_non_btags;
        *(floatBranches["dev_from_avg_disc_btags"]) = dev_from_avg_disc_btags;
	    *(floatBranches["first_highest_btag"]) = first_highest_btag;
	    *(floatBranches["second_highest_btag"]) = second_highest_btag;
	    *(floatBranches["lowest_btag"]) = lowest_btag;

        *(floatBranches["mass_MHT"]) = mass_MHT;
        *(floatBranches["all_sum_pt"]) = all_sum_pt;
        *(floatBranches["mass_of_leps_and_allJets"]) = mass_of_leps_and_allJets;
        *(floatBranches["pt_of_leps_and_allJets"]) = pt_of_leps_and_allJets;
        *(floatBranches["pt_of_allEverything"]) = pt_of_allEverything;

      } //End if (ExtraKinematicVariables)

      if (ExtraLeptonVariables) {

        *(intBranches["lep2IsGlobalMuon"]) = lep2IsGlobalMuon;
        *(intBranches["lep2IsTrackerMuon"]) = lep2IsTrackerMuon;
        *(intBranches["lep2IsGlobalMuonPromptTight"]) = lep2IsGlobalMuonPromptTight;
        *(intBranches["lep2NumTrackHits"]) = lep2NumTrackHits;
        *(intBranches["lep2NumPixelHits"]) = lep2NumPixelHits;
        *(intBranches["lep2NumberOfMatches"]) = lep2NumberOfMatches;
        *(floatBranches["lep2Chi2"]) = lep2Chi2;
        *(intBranches["lep2NumExpectedHits"]) = lep2NumExpectedHits;

      } //End if (ExtraLeptonVariables)
        
      if (debug_) std::cout << "OUTPUT VARIABLES: " <<
        "runNumber : " << event->run << " , " <<  
        "eventNumber : " << event->lumi << " , " << 
        "luminosityBlock : " << event->evt << " , " << 
        "numTightMuons : " << numTightMuons << " , " << 
        "numTightElectrons : " << numTightElectrons << " , " << 
        "numLooseMuons : " << numLooseMuons << " , " << 
        "numLooseElectrons : " << numLooseElectrons << " , " << 
        "numJets : " << numJets << " , " << 
        "numTaggedJets : " << numTaggedJets << " , " << 
        "numPV : " << numPV << " , " << 
        "lep1Pt : " << setprecision(3) << lep1Pt << " , " << 
        "lep1Eta : " << setprecision(3) << lep1Eta << " , " << 
        "lep1Iso : " << setprecision(3) << lep1Iso << " , " << 
        "lep2Pt : " << setprecision(3) << lep2Pt << " , " << 
        "lep2Eta : " << setprecision(3) << lep2Eta << " , " << 
        "lep2Iso : " << setprecision(3) << lep2Iso << " , " << 
        "met : " << setprecision(3) << met << " , " << 
        "Ht : " << setprecision(3) << Ht << " , " << 
        "first_jet_pt : " << setprecision(3) << first_jet_pt << " , " << 
        "first_jet_eta : " << setprecision(3) << first_jet_eta << " , " << 
        "second_jet_pt : " << setprecision(3) << second_jet_pt << " , " << 
        "second_jet_eta : " << setprecision(3) << second_jet_eta << " , " << 
        "avg_btag_disc_btags : " << setprecision(3) << avg_btag_disc_btags << " , " <<
        "highest_btag_disc_non_btags : " << setprecision(3) << highest_btag_disc_non_btags << " , " <<
        "first_jet_CSV : " << setprecision(3) << first_jet_CSV << " , " << 
        "second_jet_CSV : " << setprecision(3) << second_jet_CSV << " , " << 
        "weight : " << setprecision(3) << weight << " , " << 
        "weight_PUup : " << setprecision(3) << weight_PUup << " , " << 
        "weight_PUdown : " << setprecision(3) << weight_PUdown << " , " << 
        "HtWgt : " << setprecision(3) << HtWgt << " , " << 
        "HtWgtUp : " << setprecision(3) << HtWgtUp << " , " << 
        "Q2ScaleUpWgt : " << setprecision(3) << Q2ScaleUpWgt << " , " << 
        "Q2ScaleDownWgt : " << setprecision(3) << Q2ScaleDownWgt << " , " << 
        std::endl;

      

      } // end neural net selection

      //--------------------

      if (verbose) std::cout << "about to fill tree" <<std::endl;
      
      summaryTree->Fill();
      

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
  
  histofile.Write();
  histofile.Close();

  std::cout << " Done! " << std::endl;

}
