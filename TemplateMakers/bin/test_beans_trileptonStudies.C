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

// here is where you can change the btag threshold

// Medium combined tag threshold
double btagThres = 0.679;

// super loose combined tag threshold
//double btagThres = 0.244;

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
   std::string sampleName = anaParams.getParameter<string>("sampleName");
   TString tmpName = sampleName;
   std::cout <<"CONFIG: using jes = " << jes << " jer = " << jer << std::endl;

   bool debug_ = false;

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
  
  if (TString(sampleName).Contains("DoubleElectron")
      || TString(sampleName).Contains("DoubleMu")
      || TString(sampleName).Contains("MuEG") ) {

    std::cout << "CONFIG: DATA detected for sample " << sampleName << std::endl;

    isData = true;

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
  }



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

  ///////////////////////////////////////////////////////////////////
  //
  // Make a small tree called summaryTree that stores all your 
  // information event by events
  //
  ///////////////////////////////////////////////////////////////////

  std::map<TString, int *> intBranches;
  ///---- categories lable
  intBranches["PassThreeLepton"] = new int (0);
  intBranches["ThreeMuon"] = new int (0);
  intBranches["TwoMuonOneEle"] = new int (0);
  intBranches["TwoEleOneMuon"] = new int (0);
  intBranches["ThreeEle"] = new int (0);

  intBranches["numAllJets"] = new int(0);
  intBranches["numBadJets"] = new int(0);
  intBranches["numJets"] = new int (0);
  intBranches["numTaggedJets"] = new int (0);
  intBranches["numNonTaggedJets"] = new int (0);
  //intBranches["numHiggsJets"] = new int (0);
  //intBranches["numHiggsAllJets"] = new int (0);

  intBranches["numTightMuons"] = new int (0);
  intBranches["numLooseMuons"] = new int (0);
  intBranches["numTightElectrons"] = new int (0);
  intBranches["numLooseElectrons"] = new int (0);

  intBranches["isCleanEvent"] = new int (0);
  intBranches["isTriggerPass"] = new int (0);
  intBranches["isTriggerPassPrescaled"] = new int (0);
  intBranches["isDoubleMuTriggerPass"] = new int (0);
  intBranches["isDoubleElectronTriggerPass"] = new int (0);
  intBranches["isMuEGTriggerPass"] = new int (0);
  intBranches["isDoubleMuTriggerPS0"] = new int (0);
  intBranches["isDoubleElectronTriggerPS0"] = new int (0);
  intBranches["isMuEGTriggerPS0"] = new int (0);
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

  //intBranches["isHtoBB"] = new int(0);
  //intBranches["isHtoCC"] = new int(0);
  //intBranches["isHtoTT"] = new int(0);
  //intBranches["isHtoGG"] = new int(0);
  //intBranches["isHtoWW"] = new int(0);
  //  intBranches["PassZmask"] = new int (0);
  
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
  floatBranches["lep1Pt"] = new float(0.0);
  floatBranches["lep2Pt"] = new float(0.0);
  floatBranches["lep3Pt"] = new float(0.0);
  floatBranches["lep1Eta"] = new float(0.0);
  floatBranches["lep2Eta"] = new float(0.0);
  floatBranches["lep3Eta"] = new float(0.0);
  floatBranches["lep1Phi"] = new float(0.0);
  floatBranches["lep2Phi"] = new float(0.0);
  floatBranches["lep3Phi"] = new float(0.0);
  floatBranches["lep1Iso"] = new float(0.0);
  floatBranches["lep2Iso"] = new float(0.0);
  floatBranches["lep3Iso"] = new float(0.0);
//   floatBranches["mass_leplep"] = new float(0.0);
//   floatBranches["pt_leplep"] = new float(0.0);
//   floatBranches["dPhi_leplep"] = new float(0.0);
//   floatBranches["dEta_leplep"] = new float(0.0);
//   floatBranches["dR_leplep"] = new float(0.0);
//   floatBranches["correctedDZ_leplep"] = new float(0.0);
//   floatBranches["tkDZ_leplep"] = new float(0.0);
  floatBranches["lep1TkCharge"] = new float (0.0);
  floatBranches["lep1GenCharge"] = new float (0.0);
  floatBranches["lep2TkCharge"] = new float (0.0);
  floatBranches["lep2GenCharge"] = new float (0.0);
  floatBranches["lep3TkCharge"] = new float (0.0);
  floatBranches["lep3GenCharge"] = new float (0.0);
  floatBranches["lep1SF"] = new float (0.0);
  floatBranches["lep2SF"] = new float (0.0);
  floatBranches["lep3SF"] = new float (0.0);
  floatBranches["lepTotalSF"] = new float (0.0);
  
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
  
  //floatBranches["higgs_dijet_mass"] = new float(0.0);
  floatBranches["higgsLike_dijet_mass"] = new float(0.0);
  floatBranches["higgsLike_allDijet_mass"] = new float(0.0);
  //floatBranches["higgs_genJet_mass"] = new float(0.0);
  //floatBranches["higgs_genParton_mass"] = new float(0.0);
  floatBranches["min_dr_tagged_jets"] = new float(0.0);
  floatBranches["avg_dr_tagged_jets"] = new float(0.0);
  floatBranches["mindr_lep1_jet"] = new float(0.0);
  floatBranches["mindr_lep2_jet"] = new float(0.0);
  floatBranches["mindr_lep3_jet"] = new float(0.0);
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
  floatBranches["dev_from_avg_disc_btags"] = new float(0.0);

  floatBranches["first_highest_btag"] = new float(0.0);
  floatBranches["second_highest_btag"] = new float(0.0);
  floatBranches["lowest_btag"] = new float(0.0);

  /////entire system variables
  //floatBranches["mass_of_everything"] = new float(0.0);
  floatBranches["mass_MHT"] = new float(0.0);
  floatBranches["mass_of_leps_and_allJets"] = new float(0.0);
  //floatBranches["pt_of_everything"] = new float(0.0);
  floatBranches["MHT"] = new float(0.0);
  floatBranches["pt_of_leps_and_allJets"] = new float(0.0);
  floatBranches["sum_pt"] = new float(0.0); 
  floatBranches["all_sum_pt"] = new float(0.0);
  floatBranches["Ht"] = new float(0.0);
  floatBranches["Q2ScaleUpWgt"] = new float(0.0);
  floatBranches["Q2ScaleDownWgt"] = new float(0.0);
  floatBranches["numTruePV"] = new float(0.0);
  floatBranches["numGenPV"] = new float(0.0);


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

      if (verbose) std::cout << "Getting collections... " <<std::endl;

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


      //============================================
      //
      // Filter out different kinds of ttbar events
      //
      //
      //===========================================
      /////////  need modification for ttbar scale samples 
      //      cout << "Sample type is = " <<sample <<endl;

      bool HtoBB = false;
      bool HtoCC = false;
      bool HtoTT = false;
      bool HtoGG = false;
      bool HtoWW = false;

      float higgs_pt = 0.0;
      float higgs_pz = 0.0;
      float top1_pt = 0.0;
      float top1_pz = 0.0;
      
      TLorentzVector higgsGenBV[100];
        //std::cout << "Event: " << cnt << std::endl;
      for( unsigned i=0; i< mcparticles.size(); i++ ){
        int Aid = mcparticles.at(i).id;
        int AmotherID = mcparticles.at(i).motherId;
        //int AgrandMotherID = mcparticles.at(i).grandMotherId;
        if ((Aid == 5 || Aid == -5) && AmotherID == 25) {
          if (HtoBB) higgsGenBV[0].SetPtEtaPhiE(mcparticles.at(i).pt,mcparticles.at(i).eta,mcparticles.at(i).phi,mcparticles.at(i).energy);
          else higgsGenBV[1].SetPtEtaPhiE(mcparticles.at(i).pt,mcparticles.at(i).eta,mcparticles.at(i).phi,mcparticles.at(i).energy);
          HtoBB = true;
        }
        if ((Aid == 4 || Aid == -4) && AmotherID == 25) HtoCC = true;
        if ((Aid == 15 || Aid == -15) && AmotherID == 25) HtoTT = true;
        if ((Aid == 21 || Aid == -21) && AmotherID == 25) HtoGG = true;
        if ((Aid == 24 || Aid == -24) && AmotherID == 25) HtoWW = true;

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
      }
      wgt *= PUwgt;


      ///--------------------------------
      // Trigger Requirement
      bool triggerFound = false;
      bool DoubleMuTriggerFound = false;
      bool DoubleElectronTriggerFound = false;
      bool MuEGTriggerFound = false;
      bool triggerPass = false;
      bool triggerPassPrescaled = false;
      bool DoubleMuTriggerPass = false;
      bool DoubleElectronTriggerPass = false;
      bool MuEGTriggerPass = false;
      bool DoubleMuTriggerPS0 = false;
      bool DoubleElectronTriggerPS0 = false;
      bool MuEGTriggerPS0 = false;
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
      //if( triggerPass ) break;
    }
    if (DoubleMuTriggerPass || DoubleElectronTriggerPass || MuEGTriggerPass) triggerPass = true;
    if (DoubleMuTriggerFound || DoubleElectronTriggerFound || MuEGTriggerFound) triggerFound = true;


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
      BEANs::electronSelector( electrons, false, selectionYear_, tight_ele_index, loose_ele_index, tightElectronSF, looseElectronSF );

      int numTightElectrons = int(tight_ele_index.size());
      int numLooseElectrons = int(loose_ele_index.size());


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
      BEANs::muonSelector( muons, false, selectionYear_, tight_mu_index, loose_mu_index, tightMuonSF, looseMuonSF );

      int numTightMuons = int(tight_mu_index.size());
      int numLooseMuons = int(loose_mu_index.size());

      bool threeLeptons = (( numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons )== 3 && ( numTightMuons + numTightElectrons )> 0 );

      if ( !threeLeptons ) continue ;
    
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
      std::vector<double> good_jet_CHEF;
      std::vector<double> good_jet_tag;
      std::vector<int>    good_jet_flavor;

      std::vector<int>    jet_motherID;
      
      vdouble jet_px;
      vdouble jet_py;
      vdouble jet_pz;
      vdouble jet_pt;
      vdouble jet_energy;
      vdouble jet_CHEF;

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
    //double jetPhi = pfjets.at(i).phi;
    double jetCHEF = pfjets.at(i).chargedHadronEnergyFraction;
    
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
	bool csvM = ( csv> btagThres );

	
	if( csvM ){
	  tag_pfjet_index.push_back(i);
	  jet_desc.push_back(csv);
	}
	else        untag_pfjet_index.push_back(i);
	
	int flavor =  pfjets.at(i).flavour;

	good_jet_pt.push_back(jetPt);
	good_jet_eta.push_back(jetEta);
	good_jet_tag.push_back(csv);
	good_jet_flavor.push_back(flavor);
    good_jet_CHEF.push_back(jetCHEF);

      }// end for each pf jet
      

      //------------------------
      int numAllJet = numGoodAndBadJets;
      int numJet = int(tight_pfjet_index.size());
      int numBadJet = numAllJet - numJet;
      int numTag = int(tag_pfjet_index.size());
      int numNonTag = int(untag_pfjet_index.size());

      bool passThreeMuon = threeLeptons && ( numTightMuons + numLooseMuons == 3 );
      bool passTwoMuonOneEle = threeLeptons && ( numTightMuons + numLooseMuons == 2) && ( numTightElectrons + numLooseElectrons == 1);
      bool passTwoEleOneMuon = threeLeptons && ( numTightMuons + numLooseMuons == 1) && ( numTightElectrons + numLooseElectrons == 2);
      bool passThreeEle = threeLeptons && ( numTightElectrons + numLooseElectrons == 3 );
      
      *(intBranches["PassThreeLepton"]) =  threeLeptons ? 1 : 0;
      *(intBranches["ThreeMuon"]) = passThreeMuon ? 1 : 0;
      *(intBranches["TwoMuonOneEle"]) = passTwoMuonOneEle ? 1  : 0;
      *(intBranches["TwoEleOneMuon"]) = passTwoEleOneMuon ? 1 : 0;
      *(intBranches["ThreeEle"]) = passThreeEle ? 1 : 0;

      *(intBranches["isCleanEvent"]) = cleanEvent ? 1 : 0;
      *(intBranches["isTriggerPass"]) = triggerPass ? 1 : 0;
      *(intBranches["isTriggerPassPrescaled"]) = triggerPassPrescaled ? 1 : 0;
      *(intBranches["isDoubleMuTriggerPass"]) = DoubleMuTriggerPass ? 1 : 0;
      *(intBranches["isDoubleElectronTriggerPass"]) = DoubleElectronTriggerPass ? 1 : 0;
      *(intBranches["isMuEGTriggerPass"]) = MuEGTriggerPass ? 1 : 0;
      *(intBranches["isDoubleMuTriggerPS0"]) = DoubleMuTriggerPS0 ? 1 : 0;
      *(intBranches["isDoubleElectronTriggerPS0"]) = DoubleElectronTriggerPS0 ? 1 : 0;
      *(intBranches["isMuEGTriggerPS0"]) = MuEGTriggerPS0 ? 1 : 0;
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
      
      //*(intBranches["isHtoBB"]) = HtoBB ? 1 : 0;
      //*(intBranches["isHtoCC"]) = HtoCC ? 1 : 0;
      //*(intBranches["isHtoTT"]) = HtoTT ? 1 : 0;
      //*(intBranches["isHtoGG"]) = HtoGG ? 1 : 0;
      //*(intBranches["isHtoWW"]) = HtoWW ? 1 : 0;
      *(intBranches["numJets"]) = numJet ;
      *(intBranches["numAllJets"]) = numAllJet;
      *(intBranches["numBadJets"]) = numBadJet;
      *(intBranches["numTaggedJets"]) = numTag;
      *(intBranches["numNonTaggedJets"]) = numNonTag;
      //*(intBranches["numHiggsJets"]) = numHiggsJets;
      //*(intBranches["numHiggsAllJets"]) = numHiggsAllJets;
      
      *(floatBranches["numJets_float"]) = float(numJet);
      *(floatBranches["numTaggedJets_float"]) = float(numTag);

      *(intBranches["numTightMuons"]) = numTightMuons;
      *(intBranches["numLooseMuons"]) = numLooseMuons;
      *(intBranches["numTightElectrons"]) = numTightElectrons;
      *(intBranches["numLooseElectrons"]) = numLooseElectrons;

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
      TLorentzVector sum_higgs_genJet_vect(0.0,0.0,0.0,0.0);
      TLorentzVector sum_higgs_genParton_vect(0.0,0.0,0.0,0.0);
      
      float higgs_dijet_mass = -10.0;
      float higgsLike_dijet_mass1 = -10.0;
      float higgsLike_dijet_mass2 = -10.0;
      float higgsLike_allDijet_mass1 = -10.0;
      float higgsLike_allDijet_mass2 = -10.0;
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
      TLorentzVector lep_vect3;
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
      float min_jet_lep3_dR = 10000.;
      float min_tagged_jets_dR = 10000.;
      float min_jets_dR = 10000.;   //ttbb
      
      float denom_avg_cnt = 0.;
      float avg_btag_disc_btags = 0.;     
      float avg_btag_disc_non_btags = 0.;     
      float dev_from_avg_disc_btags = 0.;

      float sum_pt = 0.0 ;
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

      if ( threeLeptons ) {  //////// number of jets and number of tags
	
	int iMuon1 = -10 ;
	int iMuon2 = -10 ;
	int iMuon3 = -10 ;
	int iEle1 = -10 ;
	int iEle2 = -10 ;
	int iEle3 = -10 ;
	float lep1_pt = 0 ;
	float lep2_pt = 0 ;
	float lep3_pt = 0 ;
	float lep1_et = 0 ;
	float lep2_et = 0 ;
	float lep3_et = 0 ;
	float lep1_eta = 0 ;
	float lep2_eta = 0 ;
	float lep3_eta = 0 ;
	float lep1_phi = 0 ;
	float lep2_phi = 0 ;
	float lep3_phi = 0 ;
    float lep1_tkDZ = 0 ;
    float lep2_tkDZ = 0 ;
    float lep3_tkDZ = 0 ;
    float lep1_iso = 0 ;
    float lep2_iso = 0 ;
    float lep3_iso = 0 ;
    float lep1_correctedDZ = 0 ;
    float lep2_correctedDZ = 0 ;
    float lep3_correctedDZ = 0 ;
    float lep1TkCharge = -10;
    float lep2TkCharge = -10;
    float lep3TkCharge = -10;
    float lep1GenCharge = -10;
    float lep2GenCharge = -10;
    float lep3GenCharge = -10;
    float lep1SF = 1.0;
    float lep2SF = 1.0;
    float lep3SF = 1.0;
    
    
	  if( passThreeMuon ) {
        iMuon1 = tight_mu_index[0] ;
        lep1SF = tightMuonSF[0];
	    if( numTightMuons == 3 ) {
	      iMuon2 = tight_mu_index[1] ;
	      iMuon3 = tight_mu_index[2] ;
          lep2SF = tightMuonSF[1];
          lep3SF = tightMuonSF[2];
          
	      if(muons.at(iMuon1).pt > muons.at(iMuon2).pt) {
            if(muons.at(iMuon1).pt > muons.at(iMuon3).pt) {
              if(muons.at(iMuon3).pt > muons.at(iMuon2).pt) {
                iMuon2 = tight_mu_index[2] ;
                iMuon3 = tight_mu_index[1] ;
                lep2SF = tightMuonSF[2];
                lep3SF = tightMuonSF[1];
              }
            }
            else {
              iMuon1 = tight_mu_index[2] ;
              iMuon2 = tight_mu_index[0] ;
              iMuon3 = tight_mu_index[1] ;
              lep1SF = tightMuonSF[2];
              lep2SF = tightMuonSF[0];
              lep3SF = tightMuonSF[1];
              }
          } //end if(muons.at(iMuon1).pt > muons.at(iMuon2).pt)
          else{
            if(muons.at(iMuon2).pt > muons.at(iMuon3).pt) {
              if(muons.at(iMuon1).pt > muons.at(iMuon3).pt) {
                iMuon1 = tight_mu_index[1] ;
                iMuon2 = tight_mu_index[0] ;
                lep1SF = tightMuonSF[1];
                lep2SF = tightMuonSF[0];
              }
              else {
                iMuon1 = tight_mu_index[1] ;
                iMuon2 = tight_mu_index[2] ;
                iMuon3 = tight_mu_index[0] ;
                lep1SF = tightMuonSF[1];
                lep2SF = tightMuonSF[2];
                lep3SF = tightMuonSF[0];
              }
            }
            else {
              iMuon1 = tight_mu_index[2] ;
              iMuon3 = tight_mu_index[0] ;
              lep1SF = tightMuonSF[2];
              lep3SF = tightMuonSF[0];
            }
          } // end if NOT (muons.at(iMuon1).pt > muons.at(iMuon2).pt)
        } // end if( numTightMuons == 3 )
        else if( numTightMuons == 2) {
	      iMuon2 = tight_mu_index[1] ;
	      iMuon3 = loose_mu_index[0] ;
          lep2SF = tightMuonSF[1];
          lep3SF = looseMuonSF[0];

          if (muons.at(iMuon2).pt > muons.at(iMuon1).pt) {
            iMuon1 = tight_mu_index[1] ;
            iMuon2 = tight_mu_index[2] ;
            lep1SF = tightMuonSF[1];
            lep2SF = tightMuonSF[2];
          }
        }
        else if( numTightMuons == 1) {
	      iMuon2 = loose_mu_index[0] ;
	      iMuon3 = loose_mu_index[1] ;
          lep2SF = looseMuonSF[0];
          lep3SF = looseMuonSF[1];

          if (muons.at(iMuon3).pt > muons.at(iMuon2).pt) {
            iMuon2 = loose_mu_index[2] ;
            iMuon3 = loose_mu_index[1] ;
            lep2SF = looseMuonSF[2];
            lep3SF = looseMuonSF[1];
          }
        }
	    lep1_pt = muons.at(iMuon1).pt;
	    lep2_pt = muons.at(iMuon2).pt;
	    lep3_pt = muons.at(iMuon3).pt;
	    
	    lep1_et = muons.at(iMuon1).et;
	    lep2_et = muons.at(iMuon2).et;  
	    lep3_et = muons.at(iMuon3).et;  

	    lep1_eta = muons.at(iMuon1).eta;
	    lep2_eta = muons.at(iMuon2).eta;  
	    lep3_eta = muons.at(iMuon3).eta;  

	    lep1_phi = muons.at(iMuon1).phi;
	    lep2_phi = muons.at(iMuon2).phi;  
	    lep3_phi = muons.at(iMuon3).phi;  

        lep1_tkDZ = muons.at(iMuon1).tkDZ;
        lep2_tkDZ = muons.at(iMuon2).tkDZ;
        lep3_tkDZ = muons.at(iMuon3).tkDZ;

        lep1_correctedDZ = muons.at(iMuon1).correctedDZ;
        lep2_correctedDZ = muons.at(iMuon2).correctedDZ;
        lep3_correctedDZ = muons.at(iMuon3).correctedDZ;

        lep1TkCharge = muons.at(iMuon1).tkCharge;
        lep2TkCharge = muons.at(iMuon2).tkCharge;
        lep3TkCharge = muons.at(iMuon3).tkCharge;

        lep1GenCharge = muons.at(iMuon1).genCharge;
        lep2GenCharge = muons.at(iMuon2).genCharge;
        lep3GenCharge = muons.at(iMuon3).genCharge;

        if (selectionYear_ == "2011") {
          lep1_iso = (muons.at(iMuon1).chargedHadronIso + muons.at(iMuon1).neutralHadronIso + muons.at(iMuon1).photonIso) * 1.0 / lep1_pt;
          lep2_iso = (muons.at(iMuon2).chargedHadronIso + muons.at(iMuon2).neutralHadronIso + muons.at(iMuon2).photonIso) * 1.0 / lep2_pt;
          lep3_iso = (muons.at(iMuon3).chargedHadronIso + muons.at(iMuon3).neutralHadronIso + muons.at(iMuon3).photonIso) * 1.0 / lep3_pt;
        }
        if (selectionYear_ == "2012") {
          lep1_iso = (muons.at(iMuon1).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon1).pfIsoR04SumNeutralHadronEt + muons.at(iMuon1).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon1).pfIsoR04SumPUPt)) * 1.0 /lep1_pt;
          lep2_iso = (muons.at(iMuon2).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon2).pfIsoR04SumNeutralHadronEt + muons.at(iMuon2).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon2).pfIsoR04SumPUPt)) * 1.0 /lep2_pt;
          lep3_iso = (muons.at(iMuon3).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon3).pfIsoR04SumNeutralHadronEt + muons.at(iMuon3).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon3).pfIsoR04SumPUPt)) * 1.0 /lep3_pt;
        }

        lep_vect1.SetPxPyPzE(muons.at(iMuon1).px, muons.at(iMuon1).py, muons.at(iMuon1).pz, muons.at(iMuon1).energy);
	    lep_vect2.SetPxPyPzE(muons.at(iMuon2).px, muons.at(iMuon2).py, muons.at(iMuon2).pz, muons.at(iMuon2).energy);
	    lep_vect3.SetPxPyPzE(muons.at(iMuon3).px, muons.at(iMuon3).py, muons.at(iMuon3).pz, muons.at(iMuon3).energy);

      } //end if(passThreeMuon)


      else if( passThreeEle ) {
        iEle1 = tight_ele_index[0] ;
        lep1SF = tightElectronSF[0];
	    if( numTightElectrons == 3 ) {
	      iEle2 = tight_ele_index[1] ;
	      iEle3 = tight_ele_index[2] ;
          lep2SF = tightElectronSF[1];
          lep3SF = tightElectronSF[2];
          
	      if(electrons.at(iEle1).pt > electrons.at(iEle2).pt) {
            if(electrons.at(iEle1).pt > electrons.at(iEle3).pt) {
              if(electrons.at(iEle3).pt > electrons.at(iEle2).pt) {
                iEle2 = tight_ele_index[2] ;
                iEle3 = tight_ele_index[1] ;
                lep2SF = tightElectronSF[2];
                lep3SF = tightElectronSF[1];
              }
            }
            else {
              iEle1 = tight_ele_index[2] ;
              iEle2 = tight_ele_index[0] ;
              iEle3 = tight_ele_index[1] ;
              lep1SF = tightElectronSF[2];
              lep2SF = tightElectronSF[0];
              lep3SF = tightElectronSF[1];
              }
          } //end if(electrons.at(iEle1).pt > electrons.at(iEle2).pt)
          else{
            if(electrons.at(iEle2).pt > electrons.at(iEle3).pt) {
              if(electrons.at(iEle1).pt > electrons.at(iEle3).pt) {
                iEle1 = tight_ele_index[1] ;
                iEle2 = tight_ele_index[0] ;
                lep1SF = tightElectronSF[1];
                lep2SF = tightElectronSF[0];
              }
              else {
                iEle1 = tight_ele_index[1] ;
                iEle2 = tight_ele_index[2] ;
                iEle3 = tight_ele_index[0] ;
                lep1SF = tightElectronSF[1];
                lep2SF = tightElectronSF[2];
                lep3SF = tightElectronSF[0];
              }
            }
            else {
              iEle1 = tight_ele_index[2] ;
              iEle3 = tight_ele_index[0] ;
              lep1SF = tightElectronSF[2];
              lep3SF = tightElectronSF[0];
            }
          } // end if NOT (electrons.at(iEle1).pt > electrons.at(iEle2).pt)
        } // end if( numTightElectrons == 3 )
        else if( numTightElectrons == 2) {
	      iEle2 = tight_ele_index[1] ;
	      iEle3 = loose_ele_index[0] ;
          lep2SF = tightElectronSF[1];
          lep3SF = looseElectronSF[0];

          if (electrons.at(iEle2).pt > electrons.at(iEle1).pt) {
            iEle1 = tight_ele_index[1] ;
            iEle2 = tight_ele_index[2] ;
            lep1SF = tightElectronSF[1];
            lep2SF = tightElectronSF[2];
          }
        }
        else if( numTightElectrons == 1) {
	      iEle2 = loose_ele_index[0] ;
	      iEle3 = loose_ele_index[1] ;
          lep2SF = looseElectronSF[0];
          lep3SF = looseElectronSF[1];

          if (electrons.at(iEle3).pt > electrons.at(iEle2).pt) {
            iEle2 = loose_ele_index[2] ;
            iEle3 = loose_ele_index[1] ;
            lep2SF = looseElectronSF[2];
            lep3SF = looseElectronSF[1];
          }
        }
	    lep1_pt = electrons.at(iEle1).pt;
	    lep2_pt = electrons.at(iEle2).pt;
	    lep3_pt = electrons.at(iEle3).pt;
	    
	    lep1_et = electrons.at(iEle1).et;
	    lep2_et = electrons.at(iEle2).et;  
	    lep3_et = electrons.at(iEle3).et;  

	    lep1_eta = electrons.at(iEle1).eta;
	    lep2_eta = electrons.at(iEle2).eta;  
	    lep3_eta = electrons.at(iEle3).eta;  

	    lep1_phi = electrons.at(iEle1).phi;
	    lep2_phi = electrons.at(iEle2).phi;  
	    lep3_phi = electrons.at(iEle3).phi;  

        lep1_tkDZ = electrons.at(iEle1).tkDZ;
        lep2_tkDZ = electrons.at(iEle2).tkDZ;
        lep3_tkDZ = electrons.at(iEle3).tkDZ;

        lep1_correctedDZ = electrons.at(iEle1).correctedDZ;
        lep2_correctedDZ = electrons.at(iEle2).correctedDZ;
        lep3_correctedDZ = electrons.at(iEle3).correctedDZ;

        lep1TkCharge = electrons.at(iEle1).tkCharge;
        lep2TkCharge = electrons.at(iEle2).tkCharge;
        lep3TkCharge = electrons.at(iEle3).tkCharge;

        lep1GenCharge = electrons.at(iEle1).genCharge;
        lep2GenCharge = electrons.at(iEle2).genCharge;
        lep3GenCharge = electrons.at(iEle3).genCharge;

        if (selectionYear_ == "2011") {
          lep1_iso = (electrons.at(iEle1).chargedHadronIso + electrons.at(iEle1).neutralHadronIso + electrons.at(iEle1).photonIso) * 1.0 / lep1_pt;
          lep2_iso = (electrons.at(iEle2).chargedHadronIso + electrons.at(iEle2).neutralHadronIso + electrons.at(iEle2).photonIso) * 1.0 / lep2_pt;
          lep3_iso = (electrons.at(iEle3).chargedHadronIso + electrons.at(iEle3).neutralHadronIso + electrons.at(iEle3).photonIso) * 1.0 / lep3_pt;
        }
        if (selectionYear_ == "2012") {
          lep1_iso = ( electrons.at(iEle1).chargedHadronIso + std::max(0.0, electrons.at(iEle1).neutralHadronIso + electrons.at(iEle1).photonIso - electrons.at(iEle1).AEffDr03*electrons.at(iEle1).rhoPrime) ) * 1.0 /lep1_pt;
          lep2_iso = ( electrons.at(iEle2).chargedHadronIso + std::max(0.0, electrons.at(iEle2).neutralHadronIso + electrons.at(iEle2).photonIso - electrons.at(iEle2).AEffDr03*electrons.at(iEle2).rhoPrime) ) * 1.0 /lep2_pt;
          lep3_iso = ( electrons.at(iEle3).chargedHadronIso + std::max(0.0, electrons.at(iEle3).neutralHadronIso + electrons.at(iEle3).photonIso - electrons.at(iEle3).AEffDr03*electrons.at(iEle3).rhoPrime) ) * 1.0 /lep3_pt;
        }

	    lep_vect1.SetPxPyPzE(electrons.at(iEle1).px, electrons.at(iEle1).py, electrons.at(iEle1).pz, electrons.at(iEle1).energy);
	    lep_vect2.SetPxPyPzE(electrons.at(iEle2).px, electrons.at(iEle2).py, electrons.at(iEle2).pz, electrons.at(iEle2).energy);
	    lep_vect3.SetPxPyPzE(electrons.at(iEle3).px, electrons.at(iEle3).py, electrons.at(iEle3).pz, electrons.at(iEle3).energy);

      } //end if(passThreeEle)

      else if( passTwoMuonOneEle ) {
	    if( numTightMuons == 2 ) {
          iMuon1 = tight_mu_index[0];
          iMuon2 = tight_mu_index[1];
          lep1SF = tightMuonSF[0];
          lep2SF = tightMuonSF[1];
          if(muons.at(iMuon2).pt > muons.at(iMuon1).pt) {
            iMuon1 = tight_mu_index[1];
            iMuon2 = tight_mu_index[0];
            lep1SF = tightMuonSF[1];
            lep2SF = tightMuonSF[0];
          }
        }
        else if( numTightMuons == 1) {
          iMuon1 = tight_mu_index[0];
          iMuon2 = loose_mu_index[0];
          lep1SF = tightMuonSF[0];
          lep2SF = looseMuonSF[0];
        }
        else {
          iMuon1 = loose_mu_index[0];
          iMuon2 = loose_mu_index[1];
          lep1SF = looseMuonSF[0];
          lep2SF = looseMuonSF[1];
          if(muons.at(iMuon2).pt > muons.at(iMuon1).pt) {
            iMuon1 = loose_mu_index[1];
            iMuon2 = loose_mu_index[0];
            lep1SF = looseMuonSF[1];
            lep2SF = looseMuonSF[0];
          }
        }
        if( numTightElectrons == 1 ) {
          iEle1 = tight_ele_index[0];
          lep3SF = tightElectronSF[0];
        }
        else {
          iEle1 = loose_ele_index[0];
          lep3SF = loose_ele_index[0];
        }

	    lep1_pt = muons.at(iMuon1).pt;
	    lep2_pt = muons.at(iMuon2).pt;
	    lep3_pt = electrons.at(iEle1).pt;
	    
	    lep1_et = muons.at(iMuon1).et;
	    lep2_et = muons.at(iMuon2).et;  
	    lep3_et = electrons.at(iEle1).et;  

	    lep1_eta = muons.at(iMuon1).eta;
	    lep2_eta = muons.at(iMuon2).eta;  
	    lep3_eta = electrons.at(iEle1).eta;  

	    lep1_phi = muons.at(iMuon1).phi;
	    lep2_phi = muons.at(iMuon2).phi;  
	    lep3_phi = electrons.at(iEle1).phi;  

        lep1_tkDZ = muons.at(iMuon1).tkDZ;
        lep2_tkDZ = muons.at(iMuon2).tkDZ;
        lep3_tkDZ = electrons.at(iEle1).tkDZ;

        lep1_correctedDZ = muons.at(iMuon1).correctedDZ;
        lep2_correctedDZ = muons.at(iMuon2).correctedDZ;
        lep3_correctedDZ = electrons.at(iEle1).correctedDZ;

        lep1TkCharge = muons.at(iMuon1).tkCharge;
        lep2TkCharge = muons.at(iMuon2).tkCharge;
        lep3TkCharge = electrons.at(iEle1).tkCharge;

        lep1GenCharge = muons.at(iMuon1).genCharge;
        lep2GenCharge = muons.at(iMuon2).genCharge;
        lep3GenCharge = electrons.at(iEle1).genCharge;

        if (selectionYear_ == "2011") {
          lep1_iso = (muons.at(iMuon1).chargedHadronIso + muons.at(iMuon1).neutralHadronIso + muons.at(iMuon1).photonIso) * 1.0 / lep1_pt;
          lep2_iso = (muons.at(iMuon2).chargedHadronIso + muons.at(iMuon2).neutralHadronIso + muons.at(iMuon2).photonIso) * 1.0 / lep2_pt;
          lep3_iso = (electrons.at(iEle1).chargedHadronIso + electrons.at(iEle1).neutralHadronIso + electrons.at(iEle1).photonIso) * 1.0 / lep3_pt;
        }
        if (selectionYear_ == "2012") {
          lep1_iso = (muons.at(iMuon1).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon1).pfIsoR04SumNeutralHadronEt + muons.at(iMuon1).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon1).pfIsoR04SumPUPt)) * 1.0 /lep1_pt;
          lep2_iso = (muons.at(iMuon2).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon2).pfIsoR04SumNeutralHadronEt + muons.at(iMuon2).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon2).pfIsoR04SumPUPt)) * 1.0 /lep2_pt;
          lep3_iso = ( electrons.at(iEle1).chargedHadronIso + std::max(0.0, electrons.at(iEle1).neutralHadronIso + electrons.at(iEle1).photonIso - electrons.at(iEle1).AEffDr03*electrons.at(iEle1).rhoPrime) ) * 1.0 /lep3_pt;
        }

        lep_vect1.SetPxPyPzE(muons.at(iMuon1).px, muons.at(iMuon1).py, muons.at(iMuon1).pz, muons.at(iMuon1).energy);
	    lep_vect2.SetPxPyPzE(muons.at(iMuon2).px, muons.at(iMuon2).py, muons.at(iMuon2).pz, muons.at(iMuon2).energy);
	    lep_vect3.SetPxPyPzE(electrons.at(iEle1).px, electrons.at(iEle1).py, electrons.at(iEle1).pz, electrons.at(iEle1).energy);
      }//if( passTwoMuonOneEle )
          
      //else if( passTwoEleOneMuon ) {
      else {
        if( numTightElectrons == 2 ) {
          iEle1 = tight_ele_index[0];
          iEle2 = tight_ele_index[1];
          lep2SF = tightElectronSF[0];
          lep3SF = tightElectronSF[1];
          if(electrons.at(iEle2).pt > electrons.at(iEle1).pt) {
            iEle1 = tight_ele_index[1];
            iEle2 = tight_ele_index[0];
            lep2SF = tightElectronSF[1];
            lep3SF = tightElectronSF[0];
          }
        }
        else if( numTightElectrons == 1) {
          iEle1 = tight_ele_index[0];
          iEle2 = loose_ele_index[0];
          lep2SF = tightElectronSF[0];
          lep3SF = looseElectronSF[0];
        }
        else {
          iEle1 = loose_ele_index[0];
          iEle2 = loose_ele_index[1];
          lep2SF = looseElectronSF[0];
          lep3SF = looseElectronSF[1];
          if(electrons.at(iEle2).pt > electrons.at(iEle1).pt) {
            iEle1 = loose_ele_index[1];
            iEle2 = loose_ele_index[0];
            lep2SF = looseElectronSF[1];
            lep3SF = looseElectronSF[0];
          }
        }
        if( numTightMuons == 1 ) {
          iMuon1 = tight_mu_index[0];
          lep1SF = tightMuonSF[0];
        }
        else {
          iMuon1 = loose_mu_index[0];
          lep1SF = loose_mu_index[0];
        }

	    lep1_pt = muons.at(iMuon1).pt;
	    lep2_pt = electrons.at(iEle1).pt;
	    lep3_pt = electrons.at(iEle2).pt;
	    
	    lep1_et = muons.at(iMuon1).et;
	    lep2_et = electrons.at(iEle1).et;  
	    lep3_et = electrons.at(iEle2).et;  

	    lep1_eta = muons.at(iMuon1).eta;
	    lep2_eta = electrons.at(iEle1).eta;  
	    lep3_eta = electrons.at(iEle2).eta;  

	    lep1_phi = muons.at(iMuon1).phi;
	    lep2_phi = electrons.at(iEle1).phi;  
	    lep3_phi = electrons.at(iEle2).phi;  

        lep1_tkDZ = muons.at(iMuon1).tkDZ;
        lep2_tkDZ = electrons.at(iEle1).tkDZ;
        lep3_tkDZ = electrons.at(iEle2).tkDZ;

        lep1_correctedDZ = muons.at(iMuon1).correctedDZ;
        lep2_correctedDZ = electrons.at(iEle1).correctedDZ;
        lep3_correctedDZ = electrons.at(iEle2).correctedDZ;

        lep1TkCharge = muons.at(iMuon1).tkCharge;
        lep2TkCharge = electrons.at(iEle1).tkCharge;
        lep3TkCharge = electrons.at(iEle2).tkCharge;

        lep1GenCharge = muons.at(iMuon1).genCharge;
        lep2GenCharge = electrons.at(iEle1).genCharge;
        lep3GenCharge = electrons.at(iEle2).genCharge;

        if (selectionYear_ == "2011") {
          lep1_iso = (muons.at(iMuon1).chargedHadronIso + muons.at(iMuon1).neutralHadronIso + muons.at(iMuon1).photonIso) * 1.0 / lep1_pt;
          lep2_iso = (electrons.at(iEle1).chargedHadronIso + electrons.at(iEle1).neutralHadronIso + electrons.at(iEle1).photonIso) * 1.0 / lep2_pt;
          lep3_iso = (electrons.at(iEle2).chargedHadronIso + electrons.at(iEle2).neutralHadronIso + electrons.at(iEle2).photonIso) * 1.0 / lep3_pt;
        }
        if (selectionYear_ == "2012") {
          lep1_iso = (muons.at(iMuon1).pfIsoR04SumChargedHadronPt + std::max(0.0, muons.at(iMuon1).pfIsoR04SumNeutralHadronEt + muons.at(iMuon1).pfIsoR04SumPhotonEt - 0.5*muons.at(iMuon1).pfIsoR04SumPUPt)) * 1.0 /lep1_pt;
          lep2_iso = ( electrons.at(iEle1).chargedHadronIso + std::max(0.0, electrons.at(iEle1).neutralHadronIso + electrons.at(iEle1).photonIso - electrons.at(iEle1).AEffDr03*electrons.at(iEle1).rhoPrime) ) * 1.0 /lep2_pt;
          lep3_iso = ( electrons.at(iEle2).chargedHadronIso + std::max(0.0, electrons.at(iEle2).neutralHadronIso + electrons.at(iEle2).photonIso - electrons.at(iEle2).AEffDr03*electrons.at(iEle2).rhoPrime) ) * 1.0 /lep3_pt;
        }

        lep_vect1.SetPxPyPzE(muons.at(iMuon1).px, muons.at(iMuon1).py, muons.at(iMuon1).pz, muons.at(iMuon1).energy);
	    lep_vect2.SetPxPyPzE(electrons.at(iEle1).px, electrons.at(iEle1).py, electrons.at(iEle1).pz, electrons.at(iEle1).energy);
	    lep_vect3.SetPxPyPzE(electrons.at(iEle2).px, electrons.at(iEle2).py, electrons.at(iEle2).pz, electrons.at(iEle2).energy);
      }//if( passTwoEleOneMuon )

      float lepTotalSF = lep1SF * lep2SF * lep3SF;
      
      
//       if (verbose) std::cout << "about to fill two lep vars " <<std::endl
//                              << "TwoMuon = " << passTwoMuon << " twoTightMuon = " << twoTightMuon << " TightMuonLooseMuon = " << TightMuonLooseMuon   << endl
//                              << "TwoEle = " << passTwoEle  << " twoTightEle = " << twoTightEle << " TightEleLooseEle  " << TightEleLooseEle << endl
//                              << "MuonEle = " << passMuonEle << " TightMuonLooseEle = " << TightMuonLooseEle << " TightEleLooseMuon = " << TightEleLooseMuon << " oneEleOneMuon = " << endl
//                              << "lep1SF = " << lep1SF << " lep2SF = " << lep2SF   << " lepTotalSF = " << lepTotalSF
//                              << endl;

      
      
// 	  // two leptons
// 	  TLorentzVector two_lepton = lep_vect1 + lep_vect2;
// 	  float dilep_mass = two_lepton.M();
// 	  float dilep_pt = two_lepton.Pt();
// 	  float dPhi_dilep = lep_vect1.DeltaPhi(lep_vect2);
// 	  float dR_dilep = lep_vect1.DeltaR(lep_vect2);
//       float dEta_dilep = lep_vect1.Eta() - lep_vect2.Eta();
//       float correctedDZ_dilep = lep1_correctedDZ - lep2_correctedDZ;
//       float tkDZ_dilep = lep1_tkDZ - lep2_tkDZ;

//       int oppositeLepCharge = -1;
//       int oppositeGenLepCharge = -1;
//       // check to see if the product is negative
//       // it can only be negative if the charges
//       // have opposite signs
//       if ((lep1TkCharge * lep2TkCharge) == -1) {
//         oppositeLepCharge = 1;
//       } else if ((lep1TkCharge * lep2TkCharge) == 1) {
//         oppositeLepCharge = 0;
//       } else if (fabs(lep2TkCharge) == 99) {
//         oppositeLepCharge = -1;
//       } else if (fabs(lep1TkCharge) == 99) {
//         oppositeLepCharge = -2;
//       }
//       else std::cout << "Lep1 has charge " << lep1TkCharge << " and Lep2 has charge " << lep2TkCharge << std::endl;

//       if ((lep1GenCharge * lep2GenCharge) == -1) {
//         oppositeGenLepCharge = 1;
//       } else if ((lep1GenCharge * lep2GenCharge) == 1) {
//         oppositeGenLepCharge = 0;
//       } else if (fabs(lep2GenCharge) == 99) {
//         oppositeGenLepCharge = -1;
//       } else if (fabs(lep1GenCharge) == 99) {
//         oppositeGenLepCharge = -2;
//       }
//       else std::cout << "Lep1 has charge " << lep1GenCharge << " and Lep2 has charge " << lep2GenCharge << std::endl;

          
      
// 	  *(floatBranches["mass_leplep"]) = dilep_mass;
// 	  *(floatBranches["pt_leplep"]) = dilep_pt;
// 	  *(floatBranches["dPhi_leplep"]) = dPhi_dilep;
//       *(floatBranches["dEta_leplep"]) = dEta_dilep;
// 	  *(floatBranches["dR_leplep"]) = dR_dilep;
//       *(floatBranches["correctedDZ_leplep"]) = correctedDZ_dilep;
//       *(floatBranches["tkDZ_leplep"]) = tkDZ_dilep;

	  *(floatBranches["lep1Pt"]) =  lep1_pt;
	  *(floatBranches["lep2Pt"]) =  lep2_pt;
	  *(floatBranches["lep3Pt"]) =  lep3_pt;
	  *(floatBranches["lep1Eta"]) = lep1_eta;
	  *(floatBranches["lep2Eta"]) = lep2_eta;
	  *(floatBranches["lep3Eta"]) = lep3_eta;
	  *(floatBranches["lep1Phi"]) = lep1_phi;
	  *(floatBranches["lep2Phi"]) = lep2_phi;
	  *(floatBranches["lep3Phi"]) = lep3_phi;
	  *(floatBranches["lep1Iso"]) = lep1_iso;
	  *(floatBranches["lep2Iso"]) = lep2_iso;
	  *(floatBranches["lep3Iso"]) = lep3_iso;

      *(floatBranches["lep1SF"]) = lep1SF;
      *(floatBranches["lep2SF"]) = lep2SF;
      *(floatBranches["lep3SF"]) = lep3SF;
      *(floatBranches["lepTotalSF"]) = lepTotalSF;
      

      //*(floatBranches["higgs_pt"]) = higgs_pt;
      //*(floatBranches["higgs_pz"]) = higgs_pz;
      //*(floatBranches["top1_pt"]) = top1_pt;
      //*(floatBranches["top1_pz"]) = top1_pz;
      *(floatBranches["lep1TkCharge"]) = lep1TkCharge;
      *(floatBranches["lep2TkCharge"]) = lep2TkCharge;
      *(floatBranches["lep3TkCharge"]) = lep3TkCharge;
      *(floatBranches["lep1GenCharge"]) = lep1GenCharge;
      *(floatBranches["lep2GenCharge"]) = lep2GenCharge;
      *(floatBranches["lep3GenCharge"]) = lep3GenCharge;
//       *(intBranches["oppositeLepCharge"]) = oppositeLepCharge;
//       *(intBranches["oppositeGenLepCharge"]) = oppositeGenLepCharge;

	  sum_pt += lep1_pt;
	  Ht += lep1_et ;

	  sum_pt += lep2_pt;
	  Ht += lep2_et ;

      sum_pt += lep3_pt;
	  Ht += lep3_et ;

	  TLorentzVector everything_vect = metV + lep_vect1 + lep_vect2 + lep_vect3 + sum_jet_vect;
      TLorentzVector leps_and_jets_vect = lep_vect1 + lep_vect2 + lep_vect3 + sum_jet_vect;
      TLorentzVector leps_and_allJets_vect = lep_vect1 + lep_vect2 + lep_vect3 + sum_allJet_vect;
	  //float mass_of_everything = everything_vect.M();
      float mass_MHT = leps_and_jets_vect.M();
      float mass_of_leps_and_allJets = leps_and_allJets_vect.M();
      //float pt_of_everything = everything_vect.Pt();
      float MHT = leps_and_jets_vect.Pt();
      float pt_of_leps_and_allJets = leps_and_allJets_vect.Pt();
	  //*(floatBranches["mass_of_everything"]) = mass_of_everything;	  
      *(floatBranches["mass_MHT"]) = mass_MHT;
      *(floatBranches["mass_of_leps_and_allJets"]) = mass_of_leps_and_allJets;
	  //*(floatBranches["pt_of_everything"]) = pt_of_everything;
      *(floatBranches["MHT"]) = MHT;
      *(floatBranches["pt_of_leps_and_allJets"]) = pt_of_leps_and_allJets;


	  ///loop jet

      for (int i=0; i<numGoodAndBadJets; i++) {
        allJet_vect.SetPxPyPzE(jet_px[i],jet_py[i],jet_pz[i],jet_energy[i]);
        if (HtoBB) {
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
        
        for (int j=i+1; j < numGoodAndBadJets; j++) {
          sum_higgsLike_allDijet_vect = allJetV[i] + allJetV[j];
          higgsLike_allDijet_mass2 = sum_higgsLike_allDijet_vect.M();
          if (fabs(110 - higgsLike_allDijet_mass1) > fabs(110 - higgsLike_allDijet_mass2) || higgsLike_allDijet_mass1 == -10.0) {
            higgsLike_allDijet_mass1 = higgsLike_allDijet_mass2;
          }
        }
      }

        

	  for (int i=0; i < numGoodJets; i++) {
	    int iJet = tight_pfjet_index[i] ;
	    sum_pt += jet_pt[iJet];
	    Ht += jet_energy[iJet];
	    
	    jet_vect.SetPxPyPzE(jet_px[iJet],jet_py[iJet],jet_pz[iJet],jet_energy[iJet]);

        for (int j=i+1; j < numGoodJets; j++) {
          sum_higgsLike_dijet_vect = jetV[i] + jetV[j];
          higgsLike_dijet_mass2 = sum_higgsLike_dijet_vect.M();
          if (fabs(110 - higgsLike_dijet_mass1) > fabs(110 - higgsLike_dijet_mass2) || higgsLike_dijet_mass1 == -10.0) {
            higgsLike_dijet_mass1 = higgsLike_dijet_mass2;
          }
        }
        
	    if (i==0)  {        
          first_jet_pt = jet_pt[iJet];
          first_jet_eta = jet_vect.Eta();
          first_jet_CHEF = jet_CHEF[iJet];
          
        }
	    if (i==1)  {
          second_jet_pt = jet_pt[iJet];
          second_jet_eta = jet_vect.Eta();
          second_jet_CHEF = jet_CHEF[iJet];
        }
	    if (i==2)  {
          third_jet_pt = jet_pt[iJet];
          third_jet_eta = jet_vect.Eta();
          third_jet_CHEF = jet_CHEF[iJet];
        }
	    if (i==3)  {
          fourth_jet_pt = jet_pt[iJet];
          fourth_jet_eta = jet_vect.Eta();
          fourth_jet_CHEF = jet_CHEF[iJet];
        }
	    
	    if (min_jet_lep1_dR > lep_vect1.DeltaR(jet_vect)){
	      min_jet_lep1_dR = lep_vect1.DeltaR(jet_vect); 
	    }
	    
	    if (min_jet_lep2_dR > lep_vect2.DeltaR(jet_vect)){
	      min_jet_lep2_dR = lep_vect2.DeltaR(jet_vect); 
	    }

	    if (min_jet_lep3_dR > lep_vect3.DeltaR(jet_vect)){
	      min_jet_lep3_dR = lep_vect3.DeltaR(jet_vect); 
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

      *(floatBranches["first_jet_eta"]) = first_jet_eta;
      *(floatBranches["second_jet_eta"]) = second_jet_eta;
      *(floatBranches["third_jet_eta"]) = third_jet_eta;
      *(floatBranches["fourth_jet_eta"]) = fourth_jet_eta;

      *(floatBranches["first_jet_CHEF"]) = first_jet_CHEF;
      *(floatBranches["second_jet_CHEF"]) = second_jet_CHEF;
      *(floatBranches["third_jet_CHEF"]) = third_jet_CHEF;
      *(floatBranches["fourth_jet_CHEF"]) = fourth_jet_CHEF;

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

      //*(floatBranches["min_dr_genB1_allJet"]) = min_dr_genB1_allJet;
      //*(floatBranches["min_dr_genB2_allJet"]) = min_dr_genB2_allJet;
      
	  float mindr_lep1_jet = min_jet_lep1_dR;
	  float mindr_lep2_jet = min_jet_lep2_dR;
	  float mindr_lep3_jet = min_jet_lep3_dR;
	  *(floatBranches["mindr_lep1_jet"]) = mindr_lep1_jet;
	  *(floatBranches["mindr_lep2_jet"]) = mindr_lep2_jet;
	  *(floatBranches["mindr_lep3_jet"]) = mindr_lep3_jet;
	  
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
	  all_sum_pt = sum_pt + MHT;
	  Ht += MHT;

	  *(floatBranches["numPV"]) = numpv ;
	  *(floatBranches["weight"]) = wgt ;
	  *(floatBranches["weight_PUup"]) = PUwgt_up ;
	  *(floatBranches["weight_PUdown"]) = PUwgt_down ;
	  *(floatBranches["met"]) = met;
	  *(floatBranches["unc_met"]) = unc_met;

	  *(floatBranches["sum_pt"]) = sum_pt; 
	  *(floatBranches["all_sum_pt"]) = all_sum_pt;
	  *(floatBranches["Ht"]) = Ht;

//       bool passBigDiamondZmask = (passMuonEle || (dilep_mass < (65.5 + 3*MHT/8)) || (dilep_mass > (108 - MHT/4)) || (dilep_mass < (79 - 3*MHT/4)) || (dilep_mass > (99 + MHT/2)) );
//       *(intBranches["PassZmask"]) = passBigDiamondZmask ? 1 : 0;

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
      *(floatBranches["higgsLike_allDijet_mass"]) = higgsLike_allDijet_mass1;
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


