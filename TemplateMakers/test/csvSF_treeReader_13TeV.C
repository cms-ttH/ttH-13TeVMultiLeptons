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
#include "TVector.h"
#include "TLorentzVector.h"
#include "Math/Interpolator.h"


#ifdef __MAKECINT__
#pragma link C++ class std::vector< TLorentzVector >+; 
#endif


#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


#if !defined(__CINT__) && !defined(__MAKECINT__)

//#include "ttH-LeptonPlusJets/AnalysisCode/interface/BEANloader.h"
//#include "ttH-LeptonPlusJets/AnalysisCode/interface/YggdrasilEventVars.h"
//#include "csvReweightingRun2/csvTreeMaker/interface/csvEventVars.h"

#endif


//*****************************************************************************
typedef std::vector< TLorentzVector >          vecTLorentzVector;
typedef std::vector<int>                       vint;
typedef std::vector<double>                    vdouble;
typedef std::vector<std::vector<double> >      vvdouble;



// ------------ csv applying functions -------------
void fillCSVhistos(TFile *fileHF, TFile *fileLF);
double get_csv_wgt( bool TaggerisCSV, vecTLorentzVector jets, vdouble jetCSV, vint jetFlavor, int iSys, double &csvWgtHF, double &csvWgtLF, double &csvWgtCF );

double reweightPU( int nPU, int iSys );

// CSV reweighting
TH1D* h_csv_wgt_hf[9][6];
TH1D* c_csv_wgt_hf[9][6];
TH1D* h_csv_wgt_lf[9][4][3];

//*****************************************************************************
// old data 552.673 + 993.722 = 1546.395 ;  latest 924.846 + 1579.186 = 2504.032    //2549.850 ;2552.241 ; 2612.323 // 589.333 ////2068.329 //3992.165 //12900 //35867
// 2017 total lumi = 41370, B = 4764, CtoE = 22005, EtoF = 15187,
// void csvSF_treeReader_13TeV(bool isCSV=1, bool isHF=1, int verNum = 0, string JES="", int insample=1, int maxNentries=-1, int Njobs=1, int jobN=1, double intLumi= 41370) {
//   /// inclusive Selection or not
//   bool inclusiveSelection = !true;//false;
// 
//   //// speicify the runEras
//   string runEra = "full"; // blank means full data, "B", "CtoE", "EtoF"
//   if(runEra == "B") intLumi = 4764;
//   if(runEra == "CtoE") intLumi = 22005;
//   if(runEra == "EtoF") intLumi = 15187;
//   if( insample < 0 ){
//     std::cout << "Using data of Run "<< runEra << "; total lumi is "<< intLumi << std::endl;
//     std::cout << "======== make sure you are using the corresponding datafiles for different run Eras ========" << std::endl;
//   }
//   /// using MuonEG events only for HF?
//   bool emuOnlyHF = !true;
// 
//   ///// jet Pt cut
//   bool JetPtCut30 = false; //true;
//   /// remove PU jets
//   bool rmPUJet = true;
// 
//   /// tag and probe, jeremy's control region
//   bool tpj =  false; //true;
// 
//   //using cMVAv2 tagger to define the Control Regions
//   bool diffCR = false;
// 
//   //skipping runs/lumis
//   bool doSkip = false;
//   std::vector<int> runs={260532,260533,260536,260534,257822,257823,260431,260373,260627,256734,258443,260593,260576,260577,260575,260538,257490,259861,260541,260424,260425,260426,260427,259884,257400,256729,257487,257394,257395,257396,257397,257399};
// 
//   // set seed for reproducibility
//   TRandom3 r(12345);
// 
//   ////PU reweighting
//   TFile* f_PUwgt = new TFile ((string(getenv("CMSSW_BASE")) + "/src/csvReweightingRun2/csvTreeMaker/pileUp_wgts/PileUPReweighting.root").c_str());
//   TH1D* h_PU = (TH1D*)f_PUwgt->Get("numPVs_PUratio")->Clone();
//   bool applyPU = true;
//   ///// csv WPs // update to Moriond 2017 WPs
//   double Twp = 0.8001; //0.9535; //0.800;
//   double Mwp = 0.4941; //0.8484; //0.800;
//   double Lwp = 0.1522; //0.5426; //0.460;
//   if(!isCSV || diffCR){
//     Mwp =   0.8838; //0.4432; //0.185;// 0.725;
//     Lwp =   0.5803; //-0.5884; //-0.715;// 0.545;
//   }
// 
//   /// which btagger is used
//   string taggerName = "csv";
//   if(!isCSV) taggerName = "cMVA";
// 
//   ////////////////// 
//   /// JES uncertainty different jet collections and associated variables
//   //////////////////
//   int iSys = 0;
//   if (JES=="JESup" || JES=="JESUp")  iSys = 1;
//   if (JES=="JESdown" || JES=="JESDown") iSys = 2;
// 
//   if (JES=="JESFlavorQCDup" )  iSys = 3;
//   if (JES=="JESFlavorQCDdown" ) iSys = 4;
//   if (JES=="JESSinglePionHCALup" )  iSys = 5;
//   if (JES=="JESSinglePionHCALdown" ) iSys = 6;
//   if (JES=="JESAbsoluteScaleup" )  iSys = 7;
//   if (JES=="JESAbsoluteScaledown" ) iSys = 8;
//   if (JES=="JESAbsoluteMPFBiasup" )  iSys = 9;
//   if (JES=="JESAbsoluteMPFBiasdown" ) iSys = 10;
//   if (JES=="JESPileUpPtRefup" )  iSys = 11;
//   if (JES=="JESPileUpPtRefdown" ) iSys = 12;
// 
//   if (JES=="JESSinglePionECALup" )  iSys = 13;
//   if (JES=="JESSinglePionECALdown" ) iSys = 14;
//   if (JES=="JESPileUpPtBBup" )  iSys = 15;
//   if (JES=="JESPileUpPtBBdown" ) iSys = 16;
//   if (JES=="JESPileUpPtEC1up" )  iSys = 17;
//   if (JES=="JESPileUpPtEC1down" ) iSys = 18;
//   if (JES=="JESPileUpDataMCup" )  iSys = 19;
//   if (JES=="JESPileUpDataMCdown" ) iSys = 20;
//   if (JES=="JESRelativeFSRup" )  iSys = 21;
//   if (JES=="JESRelativeFSRdown" ) iSys = 22;
//   if (JES=="JESTimePtEtaup" )  iSys = 23;
//   if (JES=="JESTimePtEtadown" ) iSys = 24;
// 
//   
//   ////////
//   std::string inputFileHF = "data/csv_rwt_hf_IT.root";
//   std::string inputFileLF = "data/csv_rwt_lf_IT.root";
// 
//   if( verNum>0 ){
//     inputFileHF = Form("data/%s_rwt_fit_hf_v%i%s.root", taggerName.c_str(), verNum-1, JES.c_str());
//     inputFileLF = Form("data/%s_rwt_fit_lf_v%i%s.root", taggerName.c_str(), verNum-1, JES.c_str());
// 
//     /////// update file name
//     if(verNum > 3){
//       // inputFileHF = "data/csv_rwt_fit_hf_v2_final_2016_06_30test.root";
//       // inputFileLF = "data/csv_rwt_fit_lf_v2_final_2016_06_30test.root";
//       inputFileHF = "macros/csv_rwt_fit_hf_v2_final_2018_2_12test.root";
//       inputFileLF = "macros/csv_rwt_fit_lf_v2_final_2018_2_12test.root";
// 
//     }
// 
//     std::cout << "\t inputFileHF = " << inputFileHF << std::endl;
//     std::cout << "\t inputFileLF = " << inputFileLF << std::endl;
//   }
// 
//   TFile* f_CSVwgt_HF = new TFile ((string(getenv("CMSSW_BASE")) + "/src/csvReweightingRun2/csvTreeMaker/" + inputFileHF).c_str());
//   TFile* f_CSVwgt_LF = new TFile ((string(getenv("CMSSW_BASE")) + "/src/csvReweightingRun2/csvTreeMaker/" + inputFileLF).c_str());
// 
//   fillCSVhistos(f_CSVwgt_HF, f_CSVwgt_LF);
// 
//   std::cout << " ###===> iteration version " << verNum << std::endl;
// 
//   ////
//   std::cout << "   ===> load the root files! " << std::endl;
// 
//   // std::string sampleType = ( insample>=0 ) ? "mc" : "data";
//   std::string str_jobN;
//   std::stringstream stream;
//   stream << jobN;
//   str_jobN = stream.str();
// 
//   //https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
//   double mySample_xSec_ = 1.;
//   double mySample_nGen_ = 1.;
//   std::string mySample_sampleName_ = "delete";
//   std::string mySample_inputDir_ = "";
//   if( insample==2500 ){
//     mySample_xSec_ = 87.31;//831.76;//https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
//     mySample_nGen_ = 39784492; //39714128; //27562320; //38139240;(700)//30046510;//29222400;//29222400+51693000+45378000;//19757202+96834408; //19757190+96834559;//from DAS //19899500;
//     mySample_sampleName_ = "ttjets";//"TTJets";
//     // mySample_inputDir_ = "/eos/uscms/store/user/puigh/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150217_005136/0000/";
//     //mySample_inputDir_ = "/uscms_data/d2/dpuigh/TTH/miniAOD/CMSSW_7_2_3/src/ttH-LeptonPlusJets/YggdrasilTreeMaker/";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
//   else if( insample==2300 ){
//     mySample_xSec_ = 3*2008.4;//*1.3; // SF = 1.15 for DY
//     mySample_nGen_ = 85231710;//85121526; //18181997; //96658928; //49144252;//19198079;//AMC  //49877132;//MLM     //19259739;//19554161; //9006339; //----//19259101;//19310834; //28445565; 
//     mySample_sampleName_ = "zjets";//"DYJetsToLL";
//     // mySample_inputDir_ = "/eos/uscms/store/user/puigh/DYJetsToLL_M-50_13TeV-madgraph-pythia8/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150216_233924/0000/";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
//   else if( insample==2310 ){
//     mySample_xSec_ = 18610;//*1.3;//correctMe
//     mySample_nGen_ = 23023730; //21006092; //35291552; //35256264; //35079800;//Spring16 //22494699;//AMC  //35079776;//MLM   //22482549;//22460462;//21843377;//correctMe
//     mySample_sampleName_ = "lowMasszjets";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
//   else if( insample==2400 ){
//     mySample_xSec_ = 20508.9;  
//     mySample_nGen_ = 10017462;
//     mySample_sampleName_ = "WJetsToLNu";
//     mySample_inputDir_ = "/eos/uscms/store/user/puigh/WJetsToLNu_13TeV-madgraph-pythia8-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150217_010312/0000/";
//   }
//   else if( insample==2524 ){
//     mySample_xSec_ = 1.152;  
//     mySample_nGen_ = 246521;
//     mySample_sampleName_ = "TTWJets";
//     mySample_inputDir_ = "/eos/uscms/store/user/puigh/TTWJets_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150217_005352/0000/";
//   }
//   else if( insample==2523 ){
//     mySample_xSec_ = 2.232;  
//     mySample_nGen_ = 249275;
//     mySample_sampleName_ = "TTZJets";
//     mySample_inputDir_ = "/eos/uscms/store/user/puigh/TTZJets_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150217_005607/0000/";
//   }
//   else if( insample==2510 ){
//     mySample_xSec_ = 2.232;  
//     mySample_nGen_ = 500000;
//     mySample_sampleName_ = "TToLeptons_s";
//     mySample_inputDir_ = "/eos/uscms/store/user/puigh/TToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150217_005853/0000/";
//   }
//   else if( insample==2511 ){
//     mySample_xSec_ = 2.232;  
//     mySample_nGen_ = 250000;
//     mySample_sampleName_ = "TBarToLeptons_s";
//     mySample_inputDir_ = "/eos/uscms/store/user/puigh/TBarToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150217_004555/0000/";
//   }
//   else if( insample==2512 ){
//     mySample_xSec_ = 2.232;  
//     mySample_nGen_ = 3991000;
//     mySample_sampleName_ = "TToLeptons_t";
//     mySample_inputDir_ = "/eos/uscms/store/user/puigh/TToLeptons_t-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150217_005929/0000/";
//   }
//   else if( insample==2513 ){
//     mySample_xSec_ = 2.232;  
//     mySample_nGen_ = 1999800;
//     mySample_sampleName_ = "TBarToLeptons_t";
//     mySample_inputDir_ = "/eos/uscms/store/user/puigh/TBarToLeptons_t-channel_Tune4C_CSA14_13TeV-aMCatNLO-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1_yggdrasilTree_v1/150217_004732/0000/";
//   }
//   else if( insample==2514 ){
//     mySample_xSec_ = 35.6;  
//     mySample_nGen_ = 7636171;//4495030;//992024; //6952830;//998400;//1000000;//995600;
//     mySample_sampleName_ = "singletW";//"T_tW_DR";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
//   else if( insample==2515 ){
//     mySample_xSec_ = 35.6;  
//     mySample_nGen_ = 7756300;//5487976; //998276; //6933094;//985000;//999400;//988500;
//     mySample_sampleName_ = "singletbarW";//"Tbar_tW_DR";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
//   else if( insample==2600 ){
//     mySample_xSec_ =  12.178; // correctMe???
//     mySample_nGen_ = 1818828; //1408239; //1999000;//1996600;//1979988;//1999000;//1965200;
//     mySample_sampleName_ = "WW";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
//   else if( insample==9125 ){
//     mySample_xSec_ = 0.5085 * 1.0;// YR3 * BR(all)  
//     mySample_nGen_ = 199700;//199000;
//     mySample_sampleName_ = "TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola_PU20bx25_tsg_PHYS14_25_V1-v2";
//     mySample_inputDir_ = "/eos/uscms/store/user/puigh/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v2_v1_yggdrasilTree_v1/150217_004834/0000/";
//   }
//   else if( insample==-100 ){
//     mySample_xSec_ = 1; 
//     mySample_nGen_ = 1; 
//     mySample_sampleName_ = "DoubleEG";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
//   else if( insample==-200 ){
//     mySample_xSec_ = 1; 
//     mySample_nGen_ = 1; 
//     mySample_sampleName_ = "DoubleMuon";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
//   else if( insample==-300 ){
//     mySample_xSec_ = 1; 
//     mySample_nGen_ = 1; 
//     mySample_sampleName_ = "MuonEG";
//     mySample_inputDir_ = "/afs/cern.ch/work/l/lwming/public/";
//   }
// 
// 
//   std::string treefilename = mySample_inputDir_ + mySample_sampleName_ + "*.root";
//   //  // std::string treefilename = mySample_inputDir_ + mySample_sampleName_ + "_RunH2_6thJan.root";
// 
//   // std::string treefilename = mySample_inputDir_ + "csv_treeMaker*.root";
//   // std::string treefilename = "test/csv_treeMaker*.root";
//    // std::string treefilename = "/afs/cern.ch/work/l/lwming/public/DoubleMuon_Run2017B_17Nov2017_11thJan.root";
// 
//   std::string s_end = "_histo_" + str_jobN + ".root";
//   if( Njobs==1 ) s_end = "_histo.root";
//   if( Njobs==1 && inclusiveSelection) s_end = "_histo_All.root"; // tpj //change the output file name; checking different dilepton categories
// 
// 
//   std::string histofilename = Form("CSVHistoFiles/%s_rwt_hf_%s_v%i%s%s",taggerName.c_str(), mySample_sampleName_.c_str(), verNum, JES.c_str(), s_end.c_str());
//   if( !isHF ) histofilename = Form("CSVHistoFiles/%s_rwt_lf_%s_v%i%s%s",taggerName.c_str(), mySample_sampleName_.c_str(), verNum, JES.c_str(), s_end.c_str());
// 
//   std::cout << "  treefilename  = " << treefilename.c_str() << std::endl;
//   std::cout << "  histofilename = " << histofilename.c_str() << std::endl;
// 
//   TChain *chain = new TChain("ttHTreeMaker/worldTree");
//   chain->Add(treefilename.c_str());
// 
// 
//   //////////////////////////////////////////////////////////////////////////
//   ///  Tree branches/leaves
//   //////////////////////////////////////////////////////////////////////////
// 
//   EventVars *eve=0;
//   chain->SetBranchAddress("eve.", &eve );
// 
//   //////////////////////////////////////////////////////////////////////////
//   ///  Histogram making
//   //////////////////////////////////////////////////////////////////////////
// 
// 
//   TFile histofile(histofilename.c_str(),"recreate");
//   histofile.cd();
// 
// 
//   bool verbose = false;
// 
//   //////////////////////////////////////////////////////////////////////////
//   ///  Histograms
//   //////////////////////////////////////////////////////////////////////////
// 
//   TH1::SetDefaultSumw2();
//   double maxPt1 = 240. , maxPt2 = 160.;
//   if (!isHF) {maxPt1 = 160. ; maxPt2 = 80. ;}
//   TH1D* h_nJets_noSF  = new TH1D("h_nJets_noSF",";numJet", 10, 0, 10 );
//   TH1D* h_nJets  = new TH1D("h_nJets",";numJet", 10, 0, 10 );
//   TH1D* h_nJets30_noSF  = new TH1D("h_nJets30_noSF",";numJet", 10, 0, 10 );
//   TH1D* h_nJets30  = new TH1D("h_nJets30",";numJet", 10, 0, 10 );
// 
//   TH1D* h_nTags_noSF  = new TH1D("h_nTags_noSF",";numTag", 5, 0, 5 );
//   TH1D* h_nTags  = new TH1D("h_nTags",";numTag", 5, 0, 5 );
// 
//   int nBinsBTag = 102;
//   double xMinBTag = -0.01;
//   if(!isCSV){
//     nBinsBTag = 102;
//     xMinBTag = -0.01;
//   }
//   TString btags = taggerName;
//   if(isCSV) btags.ToUpper();
//   TH1D* h_probe_jet_csv = new TH1D("h_probe_jet_csv",";probe jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_probe_jet_csv_noSF = new TH1D("h_probe_jet_csv_noSF",";probe jet "+btags, nBinsBTag, xMinBTag, 1.01 );
// 
//   TH1D* h_probe_jet_pt = new TH1D("h_probe_jet_pt",";probe jet p_{T}", maxPt1, 0., maxPt1 );
//   TH1D* h_probe_jet_pt_noSF = new TH1D("h_probe_jet_pt_noSF",";probe jet p_{T}", maxPt1, 0., maxPt1 );
//   TH1D* h_probe_jet_flavour = new TH1D("h_probe_jet_flavour",";probe jet flavour", 28, -6, 22 );
//   TH1D* h_tag_jet_flavour = new TH1D("h_tag_jet_flavour",";tag jet flavour", 28, -6, 22 );
// 
//   TH1D* h_PU_jet_pt = new TH1D("h_PU_jet_pt","; PU jet p_{T}", 80, 0., 80 );
//   TH1D* h_PU_jet_csv = new TH1D("h_PU_jet_csv",";PU jet "+btags, nBinsBTag, xMinBTag, 1.01 );
// 
//   TH1D* h_all_jet_pt = new TH1D("h_all_jet_pt","; all jet p_{T}", maxPt1, 0., maxPt1 );
//   TH1D* h_all_jet_csv = new TH1D("h_all_jet_csv",";all jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_all_jet_csv_noSF = new TH1D("h_all_jet_csv_noSF",";all jet "+btags, nBinsBTag, xMinBTag, 1.01 );
// 
//   TH1D* h_first_jet_pt  = new TH1D("h_first_jet_pt",";first jet p_{T}", maxPt1, 0., maxPt1 );
//   TH1D* h_first_jet_eta = new TH1D("h_first_jet_eta",";first jet #eta", 70, -3.5, 3.5 );
//   TH1D* h_first_jet_csv = new TH1D("h_first_jet_csv",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_first_jet_csv_lowPU = new TH1D("h_first_jet_csv_lowPU",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_first_jet_csv_middlePU = new TH1D("h_first_jet_csv_middlePU",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_first_jet_csv_highPU = new TH1D("h_first_jet_csv_highPU",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
// 
//   TH1D* h_first_bjet_csv = new TH1D("h_first_bjet_csv",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_first_cjet_csv = new TH1D("h_first_cjet_csv",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_first_lfjet_csv = new TH1D("h_first_lfjet_csv",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_first_otherjet_csv = new TH1D("h_first_otherjet_csv",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_first_otherjet_csv_ee = new TH1D("h_first_otherjet_csv_ee",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_first_otherjet_csv_mm = new TH1D("h_first_otherjet_csv_mm",";first jet "+btags, nBinsBTag, xMinBTag, 1.01 );
// 
//   TH2D* h_jet_flavour_first_vs_second = new TH2D("h_jet_flavour_first_vs_second",";1st jet flavour;2nd jet flavour", 28, -6, 22, 28, -6, 22 );
//   TH1D* h_first_jet_flavour = new TH1D("h_first_jet_flavour",";first jet flavour", 28, -6, 22 );
//   TH1D* h_first_jet_partonflavour = new TH1D("h_first_jet_partonflavour",";first jet parton flavour", 28, -6, 22 );
//   TH2D* h_first_jet_flavour_hadron_vs_parton = new TH2D("h_first_jet_flavour_hadron_vs_parton",";hadron flavour;parton flavour", 28, -6, 22, 28, -6, 22 );
// 
//   TH1D* h_second_jet_pt  = new TH1D("h_second_jet_pt",";second jet p_{T}", maxPt2, 0., maxPt2 );
//   TH1D* h_second_jet_eta = new TH1D("h_second_jet_eta",";second jet #eta", 70, -3.5, 3.5 );
//   TH1D* h_second_jet_csv = new TH1D("h_second_jet_csv",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_second_jet_flavour = new TH1D("h_second_jet_flavour",";second jet flavour", 28, -6, 22 );
//   TH1D* h_second_jet_partonflavour = new TH1D("h_second_jet_partonflavour",";second jet parton flavour", 28, -6, 22 );
//   TH2D* h_second_jet_flavour_hadron_vs_parton = new TH2D("h_second_jet_flavour_hadron_vs_parton",";hadron flavour;parton flavour", 28, -6, 22, 28, -6, 22 );
// 
//   TH1D* h_second_jet_csv_lowPU = new TH1D("h_second_jet_csv_lowPU",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_second_jet_csv_middlePU = new TH1D("h_second_jet_csv_middlePU",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_second_jet_csv_highPU = new TH1D("h_second_jet_csv_highPU",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
// 
// 
//   TH1D* h_second_bjet_csv = new TH1D("h_second_bjet_csv",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_second_cjet_csv = new TH1D("h_second_cjet_csv",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_second_lfjet_csv = new TH1D("h_second_lfjet_csv",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_second_otherjet_csv = new TH1D("h_second_otherjet_csv",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_second_otherjet_csv_ee = new TH1D("h_second_otherjet_csv_ee",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
//   TH1D* h_second_otherjet_csv_mm = new TH1D("h_second_otherjet_csv_mm",";second jet "+btags, nBinsBTag, xMinBTag, 1.01 );
// 
// 
//   TH1D* h_dr_leplep  = new TH1D("h_dr_leplep",";dr leplep", 100, 0., 5 );
//   int massBin = 100;
//   double massMin = 0, massMax = 400;
//   if(!isHF) {massBin = 40; massMin = 70; massMax = 110;}; 
//   TH1D* h_mass_leplep  = new TH1D("h_mass_leplep",";mass leplep", massBin, massMin, massMax ); //100, 0., 500
//   TH1D* h_met_pt  = new TH1D("h_met_pt",";MET", maxPt1, 0., maxPt1 );
//   TH1D* h_mht_pt  = new TH1D("h_mht_pt",";MHT", maxPt1, 0., maxPt1 );
// 
//   TH2D* h_mll_vs_mht  = new TH2D("h_mll_vs_mht",";mass leplep;mht", 100, 0., 500, maxPt1, 0., maxPt1 );
// 
//   TH1D* h_1stlep_pt  = new TH1D("h_1stlep_pt",";lep1 p_{T}", 150, 0., 150 );
//   TH1D* h_2ndlep_pt  = new TH1D("h_2ndlep_pt",";lep2 p_{T}", 100, 0., 100 );
//   TH1D* h_lep_pt  = new TH1D("h_lep_pt",";lep p_{T}", 150, 0., 150 );
//   // TH2D* h_second_jet_pt_eta = new TH2D("h_second_jet_pt_eta",";second jet #eta;second jet p_{T}", 70, -3.5, 3.5, 100, 0., 500. );
//   // TH2D* h_second_jet_flavour_eta = new TH2D("h_second_jet_flavour_eta",";second jet #eta;second flavour", 70, -3.5, 3.5, 28, -6, 22 );
// 
//   TH1D* h_numPV = new TH1D("h_numPV",";numPV", 75, 0, 75 );
// 
//   int NumCutsHF = 10;
//   TH1D* h_hf_event_selection  = new TH1D("h_hf_event_selection",";cut", NumCutsHF, 0, NumCutsHF );
// 
//   h_hf_event_selection->GetXaxis()->SetBinLabel(1,"All");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(2,"==2 jets");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(3,"Dilepton trigger");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(4,"==2 leptons");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(5,"Opposite charge");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(6,"#Delta R(lep,lep) > 0.2");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(7,"M(lep,lep) > 12");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(8,"Zmass window");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(9,"MET > 30");
//   // h_hf_event_selection->GetXaxis()->SetBinLabel(8,"ZVeto");
//   // h_hf_event_selection->GetXaxis()->SetBinLabel(9,"MET > 50");
//   h_hf_event_selection->GetXaxis()->SetBinLabel(10,"jet passes medium b-tag");
// 
//   int NumCutsLF = 10;
//   TH1D* h_lf_event_selection  = new TH1D("h_lf_event_selection",";cut", NumCutsLF, 0, NumCutsLF );
// 
//   h_lf_event_selection->GetXaxis()->SetBinLabel(1,"All");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(2,"==2 jets");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(3,"Dilepton trigger");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(4,"==2 leptons");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(5,"Opposite charge");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(6,"#Delta R(lep,lep) > 0.2");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(7,"M(lep,lep) > 12");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(8,"Zmass window");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(9,"MET < 30");
//   h_lf_event_selection->GetXaxis()->SetBinLabel(10,"jet fails loose b-tag");
// 
//   // TH1D* h_numLooseLeptons = new TH1D("h_numLooseLeptons",";number of loose leptons", 5, 0, 5 );
// 
// 
//   /////////////
//   // pt eta bins, might change for 13TeV SFs
//   /////////////
//   int nPt = 6;
//   int nEta = 1;
//   if ( !isHF ){
//     nPt = 4; nEta = 3;
//   }
// 
// 
//   /////////////
//   ////// histograms saved to the output file and used for SF calculations
//   /////////////
//   TH1D* h_Data_jet_csv[6][3];
//   TH1D* h_MC_b_jet_csv[6][3];
//   TH1D* h_MC_nonb_jet_csv[6][3];
// 
// 
//   /////////////
//   // csv binning, might change for 13TeV SFs
//   /////////////
//   // CSVv2L =  0.605 , CSVv2M = 0.890 , CSVv2T = 0.970 
//   // int nBins = 18; //Number of bins 
//   // // double xBins_hf[19] = {-10.0, 0.0, 0.122, 0.244, 0.331, 0.418, 0.505, 0.592, 0.679, 0.7228, 0.7666, 0.8104, 0.8542, 0.898, 0.9184, 0.9388, 0.9592, 0.9796, 1.01};
//   // double xBins_hf[19] = {-10.0, 0.0, 0.3025, 0.605, 0.662, 0.719, 0.776, 0.833, 0.890, 0.906, 0.922, 0.938, 0.954, 0.970, 0.976, 0.982, 0.988, 0.994, 1.01};
// 
//   /// default -0.1 for csv < 0
//   int nBins = 22; //Number of bins 
//   // double xBins_hf[19] = {-10.0, 0.0, 0.122, 0.244, 0.331, 0.418, 0.505, 0.592, 0.679, 0.7228, 0.7666, 0.8104, 0.8542, 0.898, 0.9184, 0.9388, 0.9592, 0.9796, 1.01};
//   //  double xBins_hf[23] = {-10.0, 0.0, 0.101, 0.202, 0.303, 0.404, 0.505, 0.605, 0.662, 0.719, 0.776, 0.833, 0.890, 0.906, 0.922, 0.938, 0.954, 0.970, 0.976, 0.982, 0.988, 0.994, 1.01};
//   // double xBins_hf[23] = {-10.0, 0.0, 0.08, 0.16, 0.24, 0.32, 0.40, 0.460, 0.528, 0.596, 0.664, 0.732, 0.800, 0.827, 0.854, 0.881, 0.908, 0.935, 0.948, 0.961, 0.974, 0.987, 1.01};
//   //  double xBins_hf_cMVA[23] = {-10.0, 0.0, 0.0904, 0.1808, 0.2712, 0.3616, 0.452, 0.5426, 0.6036, 0.6648, 0.726, 0.7872, 0.8484, 0.8695, 0.8905, 0.9115, 0.9325, 0.9535, 0.9648, 0.9761, 0.9874, 0.9987, 1.01}; //csv 2017
//   double xBins_hf_cMVA[23] = {-10.0, 0.0, 0.0967, 0.1934, 0.2901, 0.3868, 0.4835, 0.5803, 0.641, 0.7017, 0.7624, 0.8231, 0.8838, 0.9009, 0.918, 0.9351, 0.9522, 0.9693, 0.97564, 0.98198, 0.98832, 0.99466, 1.01}; //csv 2018
// 
//   //  double xBins_hf_cMVA[23] = {-10.0, 0.0, 0.091, 0.182, 0.273, 0.364, 0.455, 0.545, 0.581, 0.617, 0.653, 0.689, 0.725, 0.751, 0.777, 0.803, 0.829, 0.855, 0.884, 0.913, 0.942, 0.971, 1.01};
//   // double xBins_hf_cMVA[23] = {-1.01, -0.9525, -0.905, -0.8575, -0.81, -0.7625, -0.715, -0.565, -0.415, -0.265, -0.115, 0.035, 0.185, 0.323, 0.461, 0.599, 0.737, 0.875, 0.902, 0.929, 0.956, 0.983, 1.01};
//   double xBins_hf[23] = {-2.01, 0.0, 0.0254, 0.0508, 0.0762, 0.1016, 0.127, 0.1522, 0.2205, 0.2889, 0.3573, 0.4257, 0.4941, 0.5553, 0.6165, 0.6777, 0.7389, 0.8001, 0.842, 0.884, 0.926, 0.968, 1.01};
// 
//   if(!isHF) nBins = 21;
//   // double xBins_lf[22] = {-10.0, 0.0, 0.04, 0.08, 0.12, 0.16, 0.2, 0.244, 0.331, 0.418, 0.505, 0.592, 0.679, 0.752, 0.825, 0.898, 0.915, 0.932, 0.949, 0.966, 0.983, 1.01};
//   // double xBins_lf[22] = {-10.0, 0.0, 0.101, 0.202, 0.303, 0.404, 0.505, 0.605, 0.662, 0.719, 0.776, 0.833, 0.890, 0.917, 0.944, 0.970, 0.975, 0.980, 0.985, 0.990, 0.995, 1.01};
//   // double xBins_lf[22] = {-10.0, 0.0, 0.08, 0.16, 0.24, 0.32, 0.40, 0.460, 0.528, 0.596, 0.664, 0.732, 0.800, 0.845, 0.890, 0.935, 0.946, 0.957, 0.968, 0.979, 0.990, 1.01};
//   //  double xBins_lf_cMVA[22] = {-10.0, 0.0, 0.0904, 0.1808, 0.2712, 0.3616, 0.452, 0.5426, 0.6036, 0.6648, 0.726, 0.7872, 0.8484, 0.8834, 0.9184, 0.9535, 0.963, 0.9724, 0.9818, 0.9912, 1.0006, 1.01}; //csv 2017
//   double xBins_lf_cMVA[22] = {-10.0, 0.0, 0.0967, 0.1934, 0.2901, 0.3868, 0.4835, 0.5803, 0.641, 0.7017, 0.7624, 0.8231, 0.8838, 0.9123, 0.9408, 0.9693, 0.97475, 0.9802, 0.98565, 0.9911, 0.99655, 1.01}; //csv 2018
//   //  double xBins_lf_cMVA[22] = {-10.0, 0.0, 0.091, 0.182, 0.273, 0.364, 0.455, 0.545, 0.581, 0.617, 0.653, 0.689, 0.725, 0.768, 0.811, 0.855, 0.879, 0.903, 0.927, 0.951, 0.975, 1.01};
//   // double xBins_lf_cMVA[22] = {-1.01, -0.9525, -0.905, -0.8575, -0.81, -0.7625, -0.715, -0.565, -0.415, -0.265, -0.115, 0.035, 0.185, 0.415, 0.645, 0.875, 0.8975, 0.92, 0.9425, 0.965, 0.9875, 1.01};
//   double xBins_lf[22] = {-2.01, 0.0, 0.0254, 0.0508, 0.0762, 0.1016, 0.127, 0.1522, 0.2205, 0.2889, 0.3573, 0.4257, 0.4941, 0.5961, 0.6981, 0.8001, 0.835, 0.87, 0.905, 0.94, 0.975, 1.01};
// 
// 
//   ////////
//   //// book the histograms with the appropriate names, binnings
//   for ( int iPt=0; iPt<nPt; iPt++){
//     for ( int iEta=0; iEta<nEta; iEta++){
// 
//       TString h_Data_Name = Form("csv_Data_Pt%i_Eta%i",iPt,iEta);
//       TString h_b_Name = Form("csv_MC_bjets_Pt%i_Eta%i",iPt,iEta);
//       TString h_nonb_Name = Form("csv_MC_nonbjets_Pt%i_Eta%i",iPt,iEta);
// 
//       /////
//       if ( isHF ){
// 	if(isCSV){
// 	  h_Data_jet_csv[iPt][iEta] = new TH1D(h_Data_Name, h_Data_Name, nBins, xBins_hf); 
// 	  h_MC_b_jet_csv[iPt][iEta] = new TH1D(h_b_Name, h_b_Name, nBins, xBins_hf); 
// 	  h_MC_nonb_jet_csv[iPt][iEta] = new TH1D(h_nonb_Name, h_nonb_Name, nBins, xBins_hf); 
// 	}
// 	else{
// 	  h_Data_jet_csv[iPt][iEta] = new TH1D(h_Data_Name, h_Data_Name, nBins, xBins_hf_cMVA); 
// 	  h_MC_b_jet_csv[iPt][iEta] = new TH1D(h_b_Name, h_b_Name, nBins, xBins_hf_cMVA); 
// 	  h_MC_nonb_jet_csv[iPt][iEta] = new TH1D(h_nonb_Name, h_nonb_Name, nBins, xBins_hf_cMVA); 
// 	}
//       }
//       else { 
// 	if(isCSV){
// 	  h_Data_jet_csv[iPt][iEta] = new TH1D(h_Data_Name, h_Data_Name, nBins, xBins_lf); 
// 	  h_MC_b_jet_csv[iPt][iEta] = new TH1D(h_b_Name, h_b_Name, nBins, xBins_lf); 
// 	  h_MC_nonb_jet_csv[iPt][iEta] = new TH1D(h_nonb_Name, h_nonb_Name, nBins, xBins_lf); 
// 	}
// 	else{
// 	  h_Data_jet_csv[iPt][iEta] = new TH1D(h_Data_Name, h_Data_Name, nBins, xBins_lf_cMVA); 
// 	  h_MC_b_jet_csv[iPt][iEta] = new TH1D(h_b_Name, h_b_Name, nBins, xBins_lf_cMVA); 
// 	  h_MC_nonb_jet_csv[iPt][iEta] = new TH1D(h_nonb_Name, h_nonb_Name, nBins, xBins_lf_cMVA); 
// 	}
//       }   
//     }
//   }
// 
//   //////////////////////////////////////////////////////////////////////////
//   /////
//   //////////////////////////////////////////////////////////////////////////
//  
//   int numEvents_all=0;
//   int numEvents_2jets=0;
// 
//   int numEvents_lepselection2=0;
//   int numEvents_lepselection1a=0;
//   int numEvents_lepselection1b=0;
//   int numEvents_lepselection1c=0;
// 
//   int numEvents_exselection=0;
// 
//   int nentries = chain->GetEntries();
//   std::cout << "\n\t Number of entries = " << nentries << std::endl;
//   std::cout << "\t Max number of entries = " << maxNentries << std::endl;
//   std::cout << "\n" << std::endl;
// 
//   int use_nentries = std::max( maxNentries, nentries);
// 
//   int NeventsPerJob = int( double(use_nentries)/double(Njobs) + 0.000001 ) + 1;
// 
//   int firstEvent = (jobN-1)*NeventsPerJob + 1;
//   int lastEvent  = firstEvent + NeventsPerJob;
//   if( jobN==Njobs ) lastEvent = -1;
//   if( jobN==1 ) firstEvent = 0;
// 
//   int cnt = 0;
//   int nPass = 0;
//   std::cout << "========  Starting Event Loop  ========" << std::endl;
//   for (Long64_t ievt=0; ievt<chain->GetEntries();ievt++) {    //Long64_t
//     cnt++;
//     if( ievt<firstEvent ) continue;
//     if( ievt==lastEvent ) break;
// 
//     if( ievt==1 )        std::cout << "     Event " << ievt << std::endl;
//     if( ievt%10000==0 && ievt!=1 ) std::cout << "           " << ievt << "\t" 
// 					     << int(double(ievt-firstEvent)/double(NeventsPerJob)*100) << "% done" << std::endl;
// 
//     //if( ievt==(maxNentries+1) ) break;
//     if( ievt==(maxNentries+1) && ievt!=0 ) break;
// 
// 
//     //////// DoubleEG_RunH2_* file check
//     // if(insample==-100){
//     //   if(eve->run_ == 283408 && (eve->lumi_ == 1157 || eve->lumi_ == 1156 || eve->lumi_ == 1129 || eve->lumi_ == 1130 || eve->lumi_ == 1128)) continue;
//     // }
// 
//     // if( int(double(ievt-firstEvent)/double(NeventsPerJob)*100) >= 65 && int(double(ievt-firstEvent)/double(NeventsPerJob)*100) < 66){
//     //   if(eve->run_ == 283408 && (eve->lumi_ == 1157 || eve->lumi_ == 1156 || eve->lumi_ == 1129 || eve->lumi_ == 1130 || eve->lumi_ == 1128)) {
//     // 	//	continue;
//     // 	std::cout<< "------run:event:lumi=" << eve->run_ << ":" << eve->evt_ << ":" << eve->lumi_ << std::endl;
//     //   }
//     // }
//     // else continue;
// 
// 
//     chain->GetEntry(ievt);
//     numEvents_all++;
//     //--- check all trigger paths 
//     // if (numEvents_all == 10) {
//     //   std::cout << "----------------------------" << std::endl;
//     //   std::cout << "----------------------------" << std::endl;
//     //   std::cout << "----------------------------" << std::endl;
// 
//     //   vstring hlt_paths = eve->TriggerPaths_ ;
//     //   vint hlt_acceps = eve->TriggerAcceps_ ;
//     //   for( unsigned int iPath=0; iPath<hlt_paths.size(); iPath++ ){
//     // 	std::string pathName = hlt_paths[iPath];
//     // 	int accept = hlt_acceps[iPath];
//     // 	std::cout << "trigger path name " << pathName << " ; acceptance is " << accept  << std::endl;
// 
//     //   }
//     //   std::cout << "----------------------------" << std::endl;
//     //   std::cout << "----------------------------" << std::endl;
// 
//     // }
// 
//     // Divide run E from run 304671
//     if(runEra == "CtoE") {
//       if( insample < 0 && eve->run_ > 304671 ) continue;
//     }
//     if(runEra == "EtoF") {
//       if( insample < 0 && eve->run_ <= 304671 ) continue;
//     }
// 
// 
//     //skipping runs/lumis for data
//     if(doSkip && insample < 0){
//       int runNumber = eve->run_;
//       bool skipEvent = false;
//       for(int iRun=0; iRun<int(runs.size()); iRun++ ){
// 	if(runNumber == runs[iRun]) {
// 	  skipEvent = true;
// 	  break;
// 	}
//       }
//       if (skipEvent) continue;
//     }
// 
//     //// --------- various weights: PU, topPt, triggerSF, leptonSF...
//     // double  wgt_topPtSF = eve->wgt_topPt_;
//     double Xsec = mySample_xSec_;//eve->wgt_xs_;
//     double nGen = ( maxNentries>0 ) ? maxNentries : mySample_nGen_;//eve->wgt_nGen_;
//     double lumi = ( intLumi > 0 ) ? intLumi : eve->wgt_lumi_ ;
//     if (insample < 0) lumi = 1;
//     double wgt_gen = ( insample==2300 || insample==2310) ? (eve->wgt_generator_/fabs(eve->wgt_generator_) ): 1;
//     double wgt = wgt_gen * lumi * (Xsec/nGen);//"weight_PU*topPtWgt*osTriggerSF*lepIDAndIsoSF*"; // various weights
// 
// 
//     // double totalWgt = eve->wgt_[iSys]; //  double totalWgt = leptonSF*wgtPU;
//     // wgt *= totalWgt;
// 
//     ///trigger Efficiency weights
//     int TwoMuon = eve->TwoMuon_;
//     int TwoElectron = eve->TwoElectron_ ;
//     int MuonElectron = eve->MuonElectron_ ;
// 
//     double triggerWgt = 1;
//       if(insample >= 0){
//         if(TwoMuon)           triggerWgt = (isHF) ? 0.983314 : 0.881084; //0.938895 : 0.878761; // 0.962157 : 1.08586; //0.981907 : 1.06953; //0.458962 : 0.560058;//0.624151 : 0.717502; //0.723 : 0.84; ///
//         else if(TwoElectron)  triggerWgt = (isHF) ? 0.882536 : 0.791254; //0.847295 : 0.78991; // 0.939806 : 1.05302; //0.982675 : 0.93381; //0.480722 : 0.579719;//0.65228 : 0.74553; //0.749 : 0.865;
//         else if(MuonElectron) triggerWgt = 0.901382; //0.887031; //0.916678; //0.905494; //0.517857;//0.67727; //0.7948;
// 
//         if(applyPU){
// 	  if(TwoMuon)           triggerWgt = (isHF) ? 0.8205 : 0.843079; //0.814563 : 0.8218; //0.965642 : 1.06555; //0.7277 : 0.8035; ///
// 	  else if(TwoElectron)  triggerWgt = (isHF) ? 0.733543 : 0.76543; //0.730297 : 0.745902; //0.939641 : 1.03338; //0.753 : 0.844;
// 	  else if(MuonElectron) triggerWgt = 0.796456; //0.784816; //0.919479; //0.7863;
//         }
//       }
//     wgt *= triggerWgt;
// 
//     ///// PU wgt
//     int numPVs = eve->numTruePV_ ; // official PU recipe, using numTruePV for MC
// 
//     double PUwgt = (insample < 0) ? 1 : h_PU->GetBinContent(h_PU->FindBin(numPVs));
//     // double PUwgt = (insample < 0) ? 1 : reweightPU( numPVs, 0 );
//     if(!applyPU) PUwgt = 1;
//     wgt *= PUwgt; // wait for data samples to get the new Pileup weights
// 
//     /// csv wgt
//     vecTLorentzVector jet_vect_TLV_tmp = eve->jet_vect_TLV_[iSys];
//     vdouble jet_CSV_tmp;
//     if(isCSV) jet_CSV_tmp = eve->jet_CSV_[iSys];
//     else  jet_CSV_tmp = eve->jet_cMVA_[iSys];
// 
//     vdouble jet_CMVA_tmp = eve->jet_cMVA_[iSys];
// 
//     vint jet_flavour_tmp = eve->jet_flavour_[iSys];
//     vint jet_partonflavour_tmp = eve->jet_partonflavour_[iSys];
// 
//     vint jet_PUID_passWPLoose_tmp = eve->jet_PUID_passWPLoose_[iSys];
// 
//     ////
// 
//     vecTLorentzVector jet_vect_TLV;
//     vdouble jet_CSV;
//     vdouble jet_CMVA;
//     vint jet_flavour;
//     vint jet_partonflavour;
//     vint jet_PUID_passWPLoose;
//     for( int iJet=0; iJet<int(jet_vect_TLV_tmp.size()); iJet++ ){
//       TLorentzVector myJet = jet_vect_TLV_tmp[iJet];
// 
//       double myCSV = jet_CSV_tmp[iJet];
//       double myCMVA = jet_CMVA_tmp[iJet];
//       double myJetPt = myJet.Pt();
//       int myFlavor = jet_flavour_tmp[iJet];
//       int mypartonFlavor = jet_partonflavour_tmp[iJet];
//       int myPUID = jet_PUID_passWPLoose_tmp[iJet];
// 
//       if(JetPtCut30 && myJetPt < 30) continue;
//       if(rmPUJet && !myPUID) continue;
// 
//       jet_vect_TLV.push_back(myJet);
//       jet_CSV.push_back(myCSV);
//       jet_CMVA.push_back(myCMVA);
//       jet_flavour.push_back(myFlavor);
//       jet_partonflavour.push_back(mypartonFlavor);
//       jet_PUID_passWPLoose.push_back(myPUID);
// 
//     }
// 
//     /////
//     double csvWgtHF, csvWgtLF, csvWgtCF;
//     double newCSVwgt = ( insample<0 || verNum==0 ) ? 1 : get_csv_wgt(1, jet_vect_TLV, jet_CSV, jet_flavour, 0, csvWgtHF, csvWgtLF, csvWgtCF);
//     double wgtfakeData = wgt*newCSVwgt; // 1 for data
//     if( verbose ) std::cout << " HF/LF csv wgts are: " << csvWgtHF << "/"<< csvWgtLF << "\t new CSV wgt = " << newCSVwgt << std::endl; 
//     ///// for iteration
//     if (verNum !=0 && insample>=0) {
//       if( verNum < 3 ){
// 	if ( isHF ) wgt *= csvWgtLF; // applying lfSFs
// 	else        wgt *= csvWgtHF; // applying lfSFs
//       }
//       else      wgt *= newCSVwgt;
//     }
// 
//     if (insample < 0) wgt = 1;
// 
//     ///////////////////
//     ////// selections
//     ///////////////////
// 
//     h_hf_event_selection->Fill(0.5, wgt);
//     h_lf_event_selection->Fill(0.5, wgt);
// 
// 
//     //////------- exactly 2 jets -----
//     int numJets = int(jet_vect_TLV.size()) ;
//     if (tpj || inclusiveSelection){
//       if (numJets < 2) continue;
//     }
//     else{
//       if (numJets != 2) continue; //// loosen nJets cut
//     }
//     numEvents_2jets++;
// 
//     h_hf_event_selection->Fill(1.5, wgt);
//     h_lf_event_selection->Fill(1.5, wgt);
// 
//     double jet1_btag = jet_CSV[0];
//     double jet2_btag = jet_CSV[1];
//     if(diffCR){
//       jet1_btag = jet_CMVA[0];
//       jet2_btag = jet_CMVA[1];
//     }
//     bool passTightBtag = false;
//     bool failLooseBtag = false;
//     if( jet1_btag>Mwp || jet2_btag>Mwp ) passTightBtag = true;
//     if( jet1_btag<Lwp || jet2_btag<Lwp ) failLooseBtag = true;
//     // if( jet1_btag<Lwp || jet2_btag<Lwp ) passTightBtag = true;
//     // if( jet1_btag>Twp && jet2_btag>Twp ) failLooseBtag = true;
// 
//     double MHT = eve->MHT_[iSys];
//     double met_pt = eve->MET_[iSys];
//     //    double met_pt = eve->METNoHF_[iSys]; //changed due to the use of silver json
// 
//     //////------- get two leptons variables from trees-----
//     // int TwoMuon = eve->TwoMuon_;
//     // int TwoElectron = eve->TwoElectron_ ;
//     // int MuonElectron = eve->MuonElectron_ ;
// 
//     bool PassZmask = eve->PassZmask_ ;
//     double mass_leplep = eve->mass_leplep_;
//     double dR_leplep = eve->dR_leplep_;
//     int oppositeLepCharge = eve->oppositeLepCharge_;
// 
//     vecTLorentzVector lepton_vect_TLV = eve->lepton_vect_TLV_;
//     // vint lepton_isTight = eve->lepton_isTight_;
//     // vint lepton_isLoose = eve->lepton_isLoose_;
//     vint lepton_trkCharge = eve->lepton_trkCharge_;
//     if (tpj){
//       if (! (lepton_vect_TLV[0].Pt()>20 && lepton_vect_TLV[1].Pt()>20) ) continue; //tpj
//       if (mass_leplep < 20 ) continue; //tpj
//     }
//     ////------- no need to calculate two-lepton variables any more
//     // int numLooseLeptons=0;
//     // for( int iLep=0; iLep<int(lepton_vect_TLV.size()); iLep++ ){
//     //   bool isLoose1 = lepton_isLoose[iLep];
//     //   if( !isLoose1 ) continue;
//     //   numLooseLeptons++;
// 
//     //   int charge1 = lepton_trkCharge[iLep];
// 
//     //   TLorentzVector myLep1 = lepton_vect_TLV[iLep];
//     //   // myLep1.SetPxPyPzE( lepton_vect_TLV[iLep][0], lepton_vect_TLV[iLep][1], lepton_vect_TLV[iLep][2], lepton_vect_TLV[iLep][3] );
// 
//     //   for( int jLep=iLep+1; jLep<int(lepton_vect_TLV.size()); jLep++ ){
//     // 	if( iLep==jLep ) continue;
//     // 	bool isLoose2 = lepton_isLoose[jLep];
//     // 	if( !isLoose2 ) continue;
// 
//     // 	int charge2 = lepton_trkCharge[jLep];
// 
//     // 	TLorentzVector myLep2;
//     // 	myLep2.SetPxPyPzE( lepton_vect_TLV[jLep][0], lepton_vect_TLV[jLep][1], lepton_vect_TLV[jLep][2], lepton_vect_TLV[jLep][3] );
// 
//     // 	TLorentzVector sum = myLep1 + myLep2;
//     // 	mass_leplep = sum.M();
// 
//     // 	dR_leplep = myLep1.DeltaR(myLep2);
// 
//     // 	if( (charge1 * charge2)==-1 )     oppositeLepCharge = 1;
//     // 	else if( (charge1 * charge2)==1 ) oppositeLepCharge = 0;
//     // 	else if( charge1==-99 )           oppositeLepCharge = -1;
//     // 	else if( charge2==-99 )           oppositeLepCharge = -2;
//     // 	else                              oppositeLepCharge = -3;
//     //   }
//     // }
// 
//     // h_numLooseLeptons->Fill(numLooseLeptons,wgt);
// 
//     // bool PassZmask = ( MuonElectron || 
//     // 		       (mass_leplep < (65.5 + 3*MHT/8)) || 
//     // 		       (mass_leplep > (108 - MHT/4)) || 
//     // 		       (mass_leplep < (79 - 3*MHT/4)) || 
//     // 		       (mass_leplep > (99 + MHT/2)) 
//     // 		       );
// 
//     
// 
//     /// triggers 
//     bool isDoubleMuTriggerPass = eve->passDoubleMuonTriggerNew_;//1;
//     bool isDoubleElectronTriggerPass = eve->passDoubleElectronTriggerNew_;//1;
//     bool isMuEGTriggerPass = eve->passElectronMuonTriggerNew_;//1;
// 
//     // if ( insample>0 ) {
//     //   isDoubleMuTriggerPass = 1;
//     //   isDoubleElectronTriggerPass = 1;
//     //   isMuEGTriggerPass = 1;
//     // }
// 
//     // for different datasets or sub-lep categories
//     ///// replace PassZmask and MET cuts M_ll & MET>30
//     bool lepselection1b = ( TwoMuon && isDoubleMuTriggerPass && abs(mass_leplep-91)>10 && (met_pt>30) ); //Selection for TwoMuon data events
//     bool lepselection1a = ( TwoElectron && isDoubleElectronTriggerPass && abs(mass_leplep-91)>10 && (met_pt>30) ); //Selection for TwoEle data events
// 
//     // bool lepselection1b = ( TwoMuon && isDoubleMuTriggerPass && (PassZmask==1) && (met_pt>50) ); //Selection for TwoMuon data events
//     // bool lepselection1a = ( TwoElectron && isDoubleElectronTriggerPass && (PassZmask==1) && (met_pt>50) ); //Selection for TwoEle data events
//     bool lepselection1c = ( MuonElectron && isMuEGTriggerPass ); //Selection for MuonEle data events
//     if (!isHF){
//       lepselection1b = ( TwoMuon && isDoubleMuTriggerPass && (PassZmask==0) && (met_pt<30) && abs(mass_leplep-91)<10 ); //Selection for TwoMuon data events
//       lepselection1a = ( TwoElectron && isDoubleElectronTriggerPass && (PassZmask==0) && (met_pt<30) && abs(mass_leplep-91)<10 ); //Selection for TwoEle data events
//       lepselection1c = 0; // ( MuonElectron && isMuEGTriggerPass ); //Selection for MuonEle data events
//     }
//     if ( isHF && emuOnlyHF ) {
//       lepselection1a = 0;
//       lepselection1b = 0;
//     }
//     // for MC events
//     bool lepselection2 = ( lepselection1a || lepselection1b || lepselection1c ) ;
//     if (tpj) {
//       if(isHF) lepselection2 = lepselection1c; // tpj, checking different dilepton categories
//       else   lepselection2 = (lepselection1a || lepselection1b);
//     }
//     // ///// different lepton flavor
//     // lepselection2 = lepselection1a;
// 
//     if ( insample == -100 ) lepselection2 = lepselection1a;
//     if ( insample == -200 ) lepselection2 = lepselection1b;
//     if ( insample == -300 ) lepselection2 = lepselection1c;
// 
//     // if (DataSet.find ("DoubleMuon") !=std::string::npos ) lepselection2 = lepselection1b;
//     // if (DataSet.find ("DoubleEG") !=std::string::npos ) lepselection2 = lepselection1a;
//     // if (DataSet.find ("MuonEG") !=std::string::npos )lepselection2 = lepselection1c;
// 
//     if( lepselection1a ) numEvents_lepselection1a++;
//     if( lepselection1b ) numEvents_lepselection1b++;
//     if( lepselection1c ) numEvents_lepselection1c++;
// 
// 
//     bool isCleanEvent = 1;
//     bool firstGoodPV = eve->GoodFirstPV_;
//     bool exselection = ((firstGoodPV) && (dR_leplep > 0.2) && (mass_leplep > 12) && (isCleanEvent == 1) && (oppositeLepCharge == 1)); //General dilepton selection   
//     // if( inclusiveSelection )  exselection = ((firstGoodPV) && (dR_leplep > 0.2) && (mass_leplep > 50) && (isCleanEvent == 1) && (oppositeLepCharge == 1)); 
// 
// 
//     // trigger
//     if(firstGoodPV){
//     if( isDoubleMuTriggerPass || isDoubleElectronTriggerPass || isMuEGTriggerPass ){
//       h_hf_event_selection->Fill(2.5, wgt);
//       if( TwoMuon || TwoElectron || MuonElectron ){
// 	h_hf_event_selection->Fill(3.5, wgt);
// 	if( oppositeLepCharge == 1 ){
// 	  h_hf_event_selection->Fill(4.5, wgt);
// 	  if( (dR_leplep > 0.2) ){
// 	    h_hf_event_selection->Fill(5.5, wgt);
// 	    if( mass_leplep > 12 ){
// 	      h_hf_event_selection->Fill(6.5, wgt);
// 	      if( fabs(mass_leplep-91)>10 ){
// 	      // if( PassZmask==1 && fabs(mass_leplep-91)>10 ){
// 		h_hf_event_selection->Fill(7.5, wgt);
// 		if( met_pt>30 ){
// 		  h_hf_event_selection->Fill(8.5, wgt);
// 		  if( passTightBtag ){
// 		    h_hf_event_selection->Fill(9.5, wgt);
// 		  }
// 		}
// 	      }
// 	    }
// 	  }
// 	}
//       }
//     }
// 
//     if( isDoubleMuTriggerPass || isDoubleElectronTriggerPass ){
//       h_lf_event_selection->Fill(2.5, wgt);
//       if( TwoMuon || TwoElectron ){
// 	h_lf_event_selection->Fill(3.5, wgt);
// 	if( oppositeLepCharge == 1 ){
// 	  h_lf_event_selection->Fill(4.5, wgt);
// 	  if( (dR_leplep > 0.2) ){
// 	    h_lf_event_selection->Fill(5.5, wgt);
// 	    if( mass_leplep > 12 ){
// 	      h_lf_event_selection->Fill(6.5, wgt);
// 	      if( PassZmask==0 && fabs(mass_leplep-91)<10 ){
// 		h_lf_event_selection->Fill(7.5, wgt);
// 		if( met_pt<30 ){
// 		  h_lf_event_selection->Fill(8.5, wgt);
// 		  if( failLooseBtag ){
// 		    h_lf_event_selection->Fill(9.5, wgt);
// 		  }
// 		}
// 	      }
// 	    }
// 	  }
// 	}
//       }
//     }
// 
//     }
//     if ( !lepselection2 ) continue;
//     numEvents_lepselection2++;
// 
// 
// 
//     /////------ extra seletions -----
//     if ( !exselection ) continue;
//     numEvents_exselection++;
// 
//     if(!tpj && !inclusiveSelection){
//       if(isHF && !passTightBtag) continue;
//       if(!isHF && !failLooseBtag) continue;
//     }
//     nPass++;
// 
//     int nPV = eve->numPVs_;
//     h_numPV->Fill(nPV, wgt);
// 
//     ///// --------jet variables
//     //    vint jet_partonflavour = eve->jet_partonflavour_[iSys];
// 
//     double first_jet_pt = -9.;
//     double first_jet_eta = -9.;
//     double first_jet_csv = -9.;
//     int    first_jet_flavour = -9;
//     int    first_jet_partonflavour = -9;
// 
//     double second_jet_pt = -9.;
//     double second_jet_eta = -9.;
//     double second_jet_csv = -9.;
//     int    second_jet_flavour = -9;
//     int    second_jet_partonflavour = -9;
// 
//     if( verbose ) std::cout << "--for event  "<< cnt << std::endl;    
//     if( verbose ) std::cout << " --number of jets is "<< numJets << std::endl;    
// 
//     // double minDR_lepton_first_jet = 99, minDR_lepton_second_jet = 99;
// 
//     int numTags = 0;
//     int numJets30 = 0;
//     for( int iJet=0; iJet<int(jet_vect_TLV.size()); iJet++ ){
//       TLorentzVector myJet = jet_vect_TLV[iJet];
//       // myJet.SetPxPyPzE( jet_vect_TLV[iJet][0], jet_vect_TLV[iJet][1], jet_vect_TLV[iJet][2], jet_vect_TLV[iJet][3] );
// 
//       double myCSV = jet_CSV[iJet];
//       double myJetPt = myJet.Pt();
//       double myJetEta = myJet.Eta();
//       int myFlavor = jet_flavour[iJet];
//       int mypartonFlavor = jet_partonflavour[iJet];
// 
//       //tpj
//       if(myJetPt > 30) numJets30++;
//       else if(tpj) continue;
// 
//       /// PU jets
//       int passPUWPLoose = jet_PUID_passWPLoose[iJet];
//       if(!rmPUJet && !passPUWPLoose){
// 	h_PU_jet_pt->Fill(myJetPt, wgt);
// 	h_PU_jet_csv->Fill(myCSV, wgt);
//       }
// 
//       h_all_jet_pt->Fill(myJetPt, wgt);
//       h_all_jet_csv->Fill(myCSV, wgt);
//       h_all_jet_csv_noSF->Fill(myCSV, wgt/newCSVwgt);
// 
//       if (myCSV > Mwp) numTags++;
// 
//       // if( iJet==0 ){
//       if( (tpj && numJets30==1) || (!tpj && iJet==0) ){ //tpj
// 	first_jet_pt = myJetPt;
// 	first_jet_eta = myJetEta;
// 	first_jet_csv = myCSV;
// 	first_jet_flavour = myFlavor;
// 	first_jet_partonflavour = mypartonFlavor;
// 
// 	// for( int iLep=0; iLep<int(lepton_vect_TLV.size()); iLep++ ){
// 	//   TLorentzVector myLep;
// 	//   myLep.SetPxPyPzE( lepton_vect_TLV[iLep][0], lepton_vect_TLV[iLep][1], lepton_vect_TLV[iLep][2], lepton_vect_TLV[iLep][3] );
// 
// 	//   double dR = myLep.DeltaR(myJet);
// 	//   if( dR<minDR_lepton_first_jet ) minDR_lepton_first_jet = dR;
// 
// 	//   TLorentzVector sum = myLep + myJet;
// 	//   h_mass_lepton_first_jet->Fill(sum.M());
// 	//   if( lepton_isTight[iLep] ) h_mass_tight_lepton_first_jet->Fill(sum.M());
// 	// }
//       }
//       // if( iJet==1 ){
//       if( (tpj && numJets30==2) || (!tpj && iJet==1) ){ //tpj
// 	second_jet_pt = myJetPt;
// 	second_jet_eta = myJetEta;
// 	second_jet_csv = myCSV;
// 	second_jet_flavour = myFlavor;
// 	second_jet_partonflavour = mypartonFlavor;
// 
// 	// for( int iLep=0; iLep<int(lepton_vect_TLV.size()); iLep++ ){
// 	//   TLorentzVector myLep;
// 	//   myLep.SetPxPyPzE( lepton_vect_TLV[iLep][0], lepton_vect_TLV[iLep][1], lepton_vect_TLV[iLep][2], lepton_vect_TLV[iLep][3] );
// 
// 	//   double dR = myLep.DeltaR(myJet);
// 	//   if( dR<minDR_lepton_second_jet ) minDR_lepton_second_jet = dR;
// 
// 	//   TLorentzVector sum = myLep + myJet;
// 	//   h_mass_lepton_second_jet->Fill(sum.M());
// 	//   h_mass_lepton_second_jet_eta->Fill(second_jet_eta,sum.M());
// 	//   if( lepton_isTight[iLep] ) h_mass_tight_lepton_second_jet->Fill(sum.M());
// 
// 	// }
//       }
// 
// 
//     } // end loop over jets
//     if (tpj && numJets30 != 2) continue; //tpj
// 
//     if( verbose ) std::cout << "   -first jet pt, eta is " << first_jet_pt << ";  "<<first_jet_eta << std::endl;
//     if( verbose ) std::cout << "   -second jet pt, eta is " << second_jet_pt << ";  "<<second_jet_eta << std::endl;
// 
//     h_nJets30->Fill(numJets30, wgt);
//     h_nJets30_noSF->Fill(numJets30, wgt/newCSVwgt);
//     h_nJets->Fill(numJets, wgt);
//     h_nJets_noSF->Fill(numJets, wgt/newCSVwgt);
//     h_nTags->Fill(numTags, wgt);
//     h_nTags_noSF->Fill(numTags, wgt/newCSVwgt);
// 
//     // h_all_jet_pt->Fill(first_jet_pt, wgt);
//     // h_all_jet_pt->Fill(second_jet_pt, wgt);
//     h_jet_flavour_first_vs_second->Fill(first_jet_flavour, second_jet_flavour, wgt);
//     h_first_jet_pt->Fill(first_jet_pt, wgt);
//     h_first_jet_eta->Fill(first_jet_eta, wgt);
//     h_first_jet_csv->Fill(first_jet_csv, wgt);
//     h_first_jet_flavour->Fill(first_jet_flavour, wgt);
//     h_first_jet_partonflavour->Fill(first_jet_partonflavour, wgt);
//     h_first_jet_flavour_hadron_vs_parton->Fill(first_jet_flavour, first_jet_partonflavour, wgt);
// 
//     if(numPVs<=10)     h_first_jet_csv_lowPU->Fill(first_jet_csv, wgt);
//     else if(numPVs>10 && numPVs<= 20)     h_first_jet_csv_middlePU->Fill(first_jet_csv, wgt);
//     else     h_first_jet_csv_highPU->Fill(first_jet_csv, wgt);
// 
//     if(numPVs<=10)     h_second_jet_csv_lowPU->Fill(second_jet_csv, wgt);
//     else if(numPVs>10 && numPVs<= 20)     h_second_jet_csv_middlePU->Fill(second_jet_csv, wgt);
//     else     h_second_jet_csv_highPU->Fill(second_jet_csv, wgt);
// 
//     h_second_jet_pt->Fill(second_jet_pt, wgt);
//     h_second_jet_eta->Fill(second_jet_eta, wgt);
//     h_second_jet_csv->Fill(second_jet_csv, wgt);
//     h_second_jet_flavour->Fill(second_jet_flavour, wgt);
//     h_second_jet_partonflavour->Fill(second_jet_partonflavour, wgt);
//     h_second_jet_flavour_hadron_vs_parton->Fill(second_jet_flavour, second_jet_partonflavour, wgt);
// 
//     if( abs(first_jet_partonflavour) == 5) h_first_bjet_csv->Fill(first_jet_csv, wgt);
//     else if( abs(first_jet_partonflavour) == 4) h_first_cjet_csv->Fill(first_jet_csv, wgt);
//     else  {
//       if(abs(first_jet_partonflavour) != 0) h_first_lfjet_csv->Fill(first_jet_csv, wgt);
//       else  {
// 	h_first_otherjet_csv->Fill(first_jet_csv, wgt);
// 	if (TwoElectron) h_first_otherjet_csv_ee->Fill(first_jet_csv, wgt);
// 	else if (TwoMuon) h_first_otherjet_csv_mm->Fill(first_jet_csv, wgt);
//       }
//     }
// 
//     if( abs(second_jet_partonflavour) == 5) h_second_bjet_csv->Fill(second_jet_csv, wgt);
//     else if( abs(second_jet_partonflavour) == 4) h_second_cjet_csv->Fill(second_jet_csv, wgt);
//     else  {
//       if(abs(second_jet_partonflavour) != 0) h_second_lfjet_csv->Fill(second_jet_csv, wgt);
//       else  {
// 	h_second_otherjet_csv->Fill(second_jet_csv, wgt);
// 	if (TwoElectron) h_second_otherjet_csv_ee->Fill(second_jet_csv, wgt);
// 	else if (TwoMuon) h_second_otherjet_csv_mm->Fill(second_jet_csv, wgt);
//       }
//     }
// 
//     h_dr_leplep->Fill(dR_leplep, wgt);
//     h_mass_leplep->Fill(mass_leplep, wgt);
//     h_met_pt->Fill(met_pt, wgt);
//     h_mht_pt->Fill(MHT, wgt);
// 
//     h_mll_vs_mht->Fill(mass_leplep, MHT, wgt);
//     // h_second_jet_pt_eta->Fill(second_jet_eta,second_jet_pt);
//     // h_second_jet_flavour_eta->Fill(second_jet_eta,second_jet_flavour);
//     h_1stlep_pt->Fill(lepton_vect_TLV[0].Pt(), wgt);
//     h_2ndlep_pt->Fill(lepton_vect_TLV[1].Pt(), wgt);
//     h_lep_pt->Fill(lepton_vect_TLV[0].Pt(), wgt);
//     h_lep_pt->Fill(lepton_vect_TLV[1].Pt(), wgt);
// 
// 
//     ///// ------  tag and proble jet selections --------
//     // 2nd jet --> tag, 1st jet --> probe
//     double tag2ndjet = jet2_btag; //second_jet_csv
//     bool jetselection2a = ( tag2ndjet > Mwp) ? 1:0; //Probe jet being the first_jet
//     bool firstjetb = ( abs(first_jet_flavour)==5 ) ? 1:0;
//     if(!isHF) {
//       jetselection2a = (tag2ndjet < Lwp) ? 1:0 ; 
//       firstjetb = ( abs(first_jet_flavour)==5 || abs(first_jet_flavour)==4 );
//     }
// 
//     // 1st jet --> tag, 2nd jet --> proble
//     double tag1stjet = jet1_btag; //first_jet_csv
//     bool jetselection2b = ( tag1stjet > Mwp ) ; //Probe jet being the second_jet
//     bool secondjetb = ( abs(second_jet_flavour)==5 );
//     if(!isHF) {
//       jetselection2b = ( tag1stjet < Lwp ) ? 1:0 ; 
//       secondjetb = ( abs(second_jet_flavour)==5 || abs(second_jet_flavour)==4 );
//     }
// 
//     /// closure test probe jet csv histogram
//     //tpj
//     if (tpj || (!tpj && jetselection2a)) {
//       h_probe_jet_csv->Fill(first_jet_csv, wgt);
//       h_probe_jet_csv_noSF->Fill(first_jet_csv, wgt/newCSVwgt);
// 
//       h_probe_jet_pt->Fill(first_jet_pt, wgt);
//       h_probe_jet_pt_noSF->Fill(first_jet_pt, wgt/newCSVwgt);
// 
//       h_probe_jet_flavour->Fill(first_jet_flavour, wgt);
//       h_tag_jet_flavour->Fill(second_jet_flavour, wgt);
//     }
//     if (tpj || (!tpj && jetselection2b)) {
//       h_probe_jet_csv->Fill(second_jet_csv, wgt);
//       h_probe_jet_csv_noSF->Fill(second_jet_csv, wgt/newCSVwgt);
// 
//       h_probe_jet_pt->Fill(second_jet_pt, wgt);
//       h_probe_jet_pt_noSF->Fill(second_jet_pt, wgt/newCSVwgt);
// 
//       h_probe_jet_flavour->Fill(second_jet_flavour, wgt);
//       h_tag_jet_flavour->Fill(first_jet_flavour, wgt);
//     }
// 
//     bool twoTagJet = ( (tag2ndjet > Mwp) && (tag1stjet > Mwp) );
//     if( !isHF ) twoTagJet = ( (tag2ndjet < Lwp) && (tag1stjet < Lwp) );
//     //// default setting
//     twoTagJet = false;
// 
//     if( twoTagJet ){
//     /// If you have two tag jets, choose one randomly
//       bool useFirstJet = ( r.Binomial(1,0.5) < 0.5 );
// 
//       double jetPt = -99;
//       double jetAbsEta = -99;
//       bool jetB = false;
//       double jetCSV = -99;
// 
//       if( useFirstJet ){
// 	jetPt = first_jet_pt;
// 	jetAbsEta = fabs(first_jet_eta);
// 	jetB = firstjetb;
// 	jetCSV = first_jet_csv;
//       }
//       else{
// 	jetPt = second_jet_pt;
// 	jetAbsEta = fabs(second_jet_eta);
// 	jetB = secondjetb;
// 	jetCSV = second_jet_csv;
//       }
// 
//       int iPt = -1; int iEta = -1;
//       if (jetPt >=19.99 && jetPt<30) iPt = 0;
//       else if (jetPt >=30 && jetPt<40) iPt = 1;
//       else if (jetPt >=40 && jetPt<60) iPt = 2;
//       else if (jetPt >=60 && jetPt<100) iPt = 3;
//       else if (jetPt >=100 && jetPt<160) iPt = 4;
//       else if (jetPt >=160 && jetPt<10000) iPt = 5;
// 
//       ////
//       if(isHF){
// 	if (jetPt >=19.99 && jetPt<30) iPt = 0;
// 	else if (jetPt >=30 && jetPt<50) iPt = 1;
// 	else if (jetPt >=50 && jetPt<70) iPt = 2;
// 	else if (jetPt >=70 && jetPt<100) iPt = 3;
// 	else if (jetPt >=100 && jetPt<160) iPt = 4;
// 	else if (jetPt >=160 && jetPt<10000) iPt = 5;
//       }
// 
//       if (jetAbsEta >=0 &&  jetAbsEta<0.8 ) iEta = 0;
//       else if ( jetAbsEta>=0.8 && jetAbsEta<1.6 )  iEta = 1;
//       else if ( jetAbsEta>=1.6 && jetAbsEta<2.51 ) iEta = 2;
// 
//       if (isHF && iEta>0) iEta=0;
//       if (!isHF && iPt>3) iPt=3;
//       if (isHF && iPt>4) iPt=4;
// 
//       if( insample<0 )	h_Data_jet_csv[iPt][iEta]->Fill(jetCSV); 
//       else{
// 	if( jetB ){
// 	  h_MC_b_jet_csv[iPt][iEta]->Fill(jetCSV, wgt);
// 	}
// 	else  {
// 	  h_MC_nonb_jet_csv[iPt][iEta]->Fill(jetCSV, wgt);
// 	}
//       }
// 
//     }
//     else{
//       /// Otherwise, do selection as before
// 
//     if ( jetselection2a ){
//       double jetPt = first_jet_pt;
//       double jetAbsEta = fabs(first_jet_eta);
// 
//       int iPt = -1; int iEta = -1;
//       if (jetPt >=19.99 && jetPt<30) iPt = 0;
//       else if (jetPt >=30 && jetPt<40) iPt = 1;
//       else if (jetPt >=40 && jetPt<60) iPt = 2;
//       else if (jetPt >=60 && jetPt<100) iPt = 3;
//       else if (jetPt >=100 && jetPt<160) iPt = 4;
//       else if (jetPt >=160 && jetPt<10000) iPt = 5;
//       
//       ////
//       if(isHF){
// 	if (jetPt >=19.99 && jetPt<30) iPt = 0;
// 	else if (jetPt >=30 && jetPt<50) iPt = 1;
// 	else if (jetPt >=50 && jetPt<70) iPt = 2;
// 	else if (jetPt >=70 && jetPt<100) iPt = 3;
// 	else if (jetPt >=100 && jetPt<160) iPt = 4;
// 	else if (jetPt >=160 && jetPt<10000) iPt = 5;
//       }
// 
//       if (jetAbsEta >=0 &&  jetAbsEta<0.8 ) iEta = 0;
//       else if ( jetAbsEta>=0.8 && jetAbsEta<1.6 )  iEta = 1;
//       else if ( jetAbsEta>=1.6 && jetAbsEta<2.51 ) iEta = 2;
// 
//       if (isHF && iEta>0) iEta=0;
//       if (isHF && iPt>4) iPt=4;
// 
//       if (!isHF && iPt>3) iPt=3;
//       if(tpj) iPt = iPt-1;
//       ///fake data
//       // h_Data_jet_csv[iPt][iEta]->Fill(first_jet_csv, wgtfakeData); 
// 
//       if( insample<0 )	h_Data_jet_csv[iPt][iEta]->Fill(first_jet_csv); 
//       else{
// 	if( firstjetb ){
// 	  h_MC_b_jet_csv[iPt][iEta]->Fill(first_jet_csv, wgt);
// 	}
// 	else  {
// 	  h_MC_nonb_jet_csv[iPt][iEta]->Fill(first_jet_csv, wgt);
// 	}
//       }
//     }
// 
// 
//     if ( jetselection2b ){
//       double jetPt = second_jet_pt;
//       double jetAbsEta = fabs(second_jet_eta);
// 
//       int iPt = -1; int iEta = -1;
//       if (jetPt >=19.99 && jetPt<30) iPt = 0;
//       else if (jetPt >=30 && jetPt<40) iPt = 1;
//       else if (jetPt >=40 && jetPt<60) iPt = 2;
//       else if (jetPt >=60 && jetPt<100) iPt = 3;
//       else if (jetPt >=100 && jetPt<160) iPt = 4;
//       else if (jetPt >=160 && jetPt<10000) iPt = 5;
//       
//       ////
//       if(isHF){
// 	if (jetPt >=19.99 && jetPt<30) iPt = 0;
// 	else if (jetPt >=30 && jetPt<50) iPt = 1;
// 	else if (jetPt >=50 && jetPt<70) iPt = 2;
// 	else if (jetPt >=70 && jetPt<100) iPt = 3;
// 	else if (jetPt >=100 && jetPt<160) iPt = 4;
// 	else if (jetPt >=160 && jetPt<10000) iPt = 5;
//       }
// 
//       if (jetAbsEta >=0 &&  jetAbsEta<0.8 ) iEta = 0;
//       else if ( jetAbsEta>=0.8 && jetAbsEta<1.6 )  iEta = 1;
//       else if ( jetAbsEta>=1.6 && jetAbsEta<2.51 ) iEta = 2;
// 
//       if (isHF && iEta>0) iEta=0;
//       if (isHF && iPt>4) iPt=4;
// 
//       if (!isHF && iPt>3) iPt=3;
//       if(tpj) iPt = iPt-1;
//       ///fake data
//       // h_Data_jet_csv[iPt][iEta]->Fill(second_jet_csv, wgtfakeData);       
// 
//       if( insample<0 )	h_Data_jet_csv[iPt][iEta]->Fill(second_jet_csv); 
//       else{
// 	if( secondjetb ){
// 	  h_MC_b_jet_csv[iPt][iEta]->Fill(second_jet_csv, wgt); 
// 	}
// 	else {
// 	  h_MC_nonb_jet_csv[iPt][iEta]->Fill(second_jet_csv, wgt); 
// 	}
//       }
//     }
//     }
// 
//   } // end loop over events
//   std::cout << "total selected events is " << nPass << std::endl;
// 
//   std::cout << "===========================================" << std::endl;
//   std::cout << "\t Number of all events = " << numEvents_all << std::endl;
//   std::cout << "\t Number of events with ==2 jets = " << numEvents_2jets << std::endl;
//   std::cout << "\t Number of events with lepselection2  = " << numEvents_lepselection2 << std::endl;
//   std::cout << "\t Number of events with lepselection1a = " << numEvents_lepselection1a << std::endl;
//   std::cout << "\t Number of events with lepselection1b = " << numEvents_lepselection1b << std::endl;
//   std::cout << "\t Number of events with lepselection1c = " << numEvents_lepselection1c << std::endl;
//   std::cout << "\t Number of events with exselection    = " << numEvents_exselection << std::endl;
//   std::cout << "===========================================" << std::endl;
// 
// 
//   std::cout << " Done! " << std::endl;
// 
//   histofile.Write();
//   histofile.Close();
// 
// }




/// algos / supporting functions:

void fillCSVhistos(TFile* fileHF, TFile* fileLF){
  //// more pt bins ???
  int minPt = 0;//0; tpj // 1 for JetPtCut30, default 0
  int nPt = 5;//5-1; /// change
  int nPtLF = 4;//4-1;
  int nEta = 3;
  for( int iSys=0; iSys<9; iSys++ ){
    for( int iPt=minPt; iPt<nPt; iPt++ ) h_csv_wgt_hf[iSys][iPt] = NULL;
    for( int iPt=minPt; iPt<nPtLF; iPt++ ){
      for( int iEta=0; iEta<nEta; iEta++ )h_csv_wgt_lf[iSys][iPt][iEta] = NULL;
    }
  }
  for( int iSys=0; iSys<5; iSys++ ){
    for( int iPt=minPt; iPt<nPt; iPt++ ) c_csv_wgt_hf[iSys][iPt] = NULL;
  }

  // CSV reweighting /// only care about the nominal ones !!!
  for( int iSys=0; iSys<9; iSys++ ){
    TString syst_csv_suffix_hf = "final";
    TString syst_csv_suffix_c = "final";
    TString syst_csv_suffix_lf = "final";
    
    switch( iSys ){
    case 0:
      // this is the nominal case
      break;
    case 1:
      // JESUp
      syst_csv_suffix_hf = "final_JESUp"; syst_csv_suffix_lf = "final_JESUp";
      syst_csv_suffix_c  = "final_cErr1Up";
      break;
    case 2:
      // JESDown
      syst_csv_suffix_hf = "final_JESDown"; syst_csv_suffix_lf = "final_JESDown";
      syst_csv_suffix_c  = "final_cErr1Down";
      break;
    case 3:
      // purity up
      syst_csv_suffix_hf = "final_LFUp"; syst_csv_suffix_lf = "final_HFUp";
      syst_csv_suffix_c  = "final_cErr2Up";
      break;
    case 4:
      // purity down
      syst_csv_suffix_hf = "final_LFDown"; syst_csv_suffix_lf = "final_HFDown";
      syst_csv_suffix_c  = "final_cErr2Down";
      break;
    case 5:
      // stats1 up
      syst_csv_suffix_hf = "final_Stats1Up"; syst_csv_suffix_lf = "final_Stats1Up";
      break;
    case 6:
      // stats1 down
      syst_csv_suffix_hf = "final_Stats1Down"; syst_csv_suffix_lf = "final_Stats1Down";
      break;
    case 7:
      // stats2 up
      syst_csv_suffix_hf = "final_Stats2Up"; syst_csv_suffix_lf = "final_Stats2Up";
      break;
    case 8:
      // stats2 down
      syst_csv_suffix_hf = "final_Stats2Down"; syst_csv_suffix_lf = "final_Stats2Down";
      break;
    }

    for( int iPt=minPt; iPt<nPt; iPt++ ) h_csv_wgt_hf[iSys][iPt] = (TH1D*)fileHF->Get( Form("csv_ratio_Pt%i_Eta0_%s",iPt,syst_csv_suffix_hf.Data()) );

    if( iSys<5 ){
      for( int iPt=minPt; iPt<nPt; iPt++ ) c_csv_wgt_hf[iSys][iPt] = (TH1D*)fileHF->Get( Form("c_csv_ratio_Pt%i_Eta0_%s",iPt,syst_csv_suffix_c.Data()) );
    }
    
    for( int iPt=minPt; iPt<nPtLF; iPt++ ){
      for( int iEta=0; iEta<nEta; iEta++ )h_csv_wgt_lf[iSys][iPt][iEta] = (TH1D*)fileLF->Get( Form("csv_ratio_Pt%i_Eta%i_%s",iPt,iEta,syst_csv_suffix_lf.Data()) );
    }
  }

  return;
}

double get_csv_wgt( bool TaggerisCSV, vecTLorentzVector jets, vdouble jetCSV, vint jetFlavor, int iSys, double &csvWgtHF, double &csvWgtLF, double &csvWgtCF ){

  int iSysHF = 0;
  switch(iSys){
  case 11: iSysHF=1; break;
  case 12: iSysHF=2; break;
  case 17: iSysHF=3; break;
  case 18: iSysHF=4; break;
  case 21: iSysHF=5; break;
  case 22: iSysHF=6; break;
  case 25: iSysHF=7; break;
  case 26: iSysHF=8; break;
  default : iSysHF = 0; break;
  }

  int iSysC = 0;
  switch(iSys){
  case 29: iSysC=1; break;
  case 30: iSysC=2; break;
  case 31: iSysC=3; break;
  case 32: iSysC=4; break;
  default : iSysC = 0; break;
  }

  int iSysLF = 0;
  switch(iSys){
  case 11: iSysLF=1; break;
  case 12: iSysLF=2; break;
  case 19: iSysLF=3; break;
  case 20: iSysLF=4; break;
  case 23: iSysLF=5; break;
  case 24: iSysLF=6; break;
  case 27: iSysLF=7; break;
  case 28: iSysLF=8; break;
  default : iSysLF = 0; break;
  }

  double csvWgthf = 1.;
  double csvWgtC  = 1.;
  double csvWgtlf = 1.;
    
  //cout << "hey1" << endl;
    
  for( int iJet=0; iJet<int(jets.size()); iJet++ ){
    TLorentzVector myJet = jets[iJet];
    // myJet.SetPxPyPzE( jets[iJet][0], jets[iJet][1], jets[iJet][2], jets[iJet][3] );
	  
    double csv = jetCSV[iJet];
    double jetPt = myJet.Pt();
    double jetAbsEta = fabs(myJet.Eta());
    int flavor = jetFlavor[iJet];

    int iPt = -1; int iEta = -1;
    if (jetPt >=19.99 && jetPt<30) iPt = 0;
    else if (jetPt >=30 && jetPt<40) iPt = 1;
    else if (jetPt >=40 && jetPt<60) iPt = 2;
    else if (jetPt >=60 && jetPt<100) iPt = 3;
    else if (jetPt >=100 && jetPt<160) iPt = 4;
    else if (jetPt >=160 && jetPt<10000) iPt = 4;  //5; low stats. combine with Pt bin 4

      ////
      if(abs(flavor) == 5 || abs(flavor) == 4){
	if (jetPt >=19.99 && jetPt<30) iPt = 0;
	else if (jetPt >=30 && jetPt<50) iPt = 1;
	else if (jetPt >=50 && jetPt<70) iPt = 2;
	else if (jetPt >=70 && jetPt<100) iPt = 3;
	else if (jetPt >=100 && jetPt<160) iPt = 4;
	else if (jetPt >=160 && jetPt<10000) iPt = 4; //4
      }

    if (jetAbsEta >=0 &&  jetAbsEta<0.8 ) iEta = 0;
    else if ( jetAbsEta>=0.8 && jetAbsEta<1.6 )  iEta = 1;
    else if ( jetAbsEta>=1.6 && jetAbsEta<2.51 ) iEta = 2;

    if (iPt < 0 || iEta < 0) {
      std::cout << "Error, couldn't find Pt, Eta bins for this b-flavor jet, jetPt = " << jetPt << ", jetAbsEta = " << jetAbsEta << std::endl;
      continue;
    }
    //tpj
    // if(iPt==0) continue;
    // else iPt = iPt-1;

    //cout << "hey2" << endl;

    if (abs(flavor) == 5 ){
      //cout << "hey2.1" << endl;
      int useCSVBin = (!TaggerisCSV || csv>=0.) ? h_csv_wgt_hf[iSysHF][iPt]->FindBin(csv) : 1;
      double iCSVWgtHF = h_csv_wgt_hf[iSysHF][iPt]->GetBinContent(useCSVBin);
      if( iCSVWgtHF!=0 ) csvWgthf *= iCSVWgtHF;

      // if( iSysHF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      // 			     flavor, jetPt, iJet->eta, csv, iCSVWgtHF );
      
    }

    else if( abs(flavor) == 4 ){
      //cout << "hey2.2" << endl;
      int useCSVBin = (!TaggerisCSV || csv>=0.) ? c_csv_wgt_hf[iSysC][iPt]->FindBin(csv) : 1;
      double iCSVWgtC = c_csv_wgt_hf[iSysC][iPt]->GetBinContent(useCSVBin);
      if( iCSVWgtC!=0 ) csvWgtC *= iCSVWgtC;
      // if( iSysC==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //      flavor, jetPt, iJet->eta, csv, iCSVWgtC );
      
    }
    
    else {//tpj
      //cout << "hey2.3" << endl;
      if (iPt >=3) iPt=3;       /// [30-40], [40-60] and [60-10000] only 3 Pt bins for lf
      //cout << "hey2.3.1" << endl;
      //cout << iSysLF << " " << iPt << " " << iEta << " " << csv << endl;
      int useCSVBin = (!TaggerisCSV || csv>=0.) ? h_csv_wgt_lf[iSysLF][iPt][iEta]->FindBin(csv) : 1;
      //cout << "hey2.3.2" << endl;
      double iCSVWgtLF = h_csv_wgt_lf[iSysLF][iPt][iEta]->GetBinContent(useCSVBin);
      //cout << "hey2.3.3" << endl;
      if( iCSVWgtLF!=0 ) csvWgtlf *= iCSVWgtLF;

      // if( iSysLF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      // 			     flavor, jetPt, iJet->eta, csv, iCSVWgtLF );
      
    }
    
    //cout << "hey3" << endl;
  }

  double csvWgtTotal = csvWgthf * csvWgtC * csvWgtlf;

  csvWgtHF = csvWgthf;
  csvWgtLF = csvWgtlf;
  csvWgtCF = csvWgtC;

  return csvWgtTotal;
}

//-------- 76X pileUp reweighting
double reweightPU( int nPU, int iSys ){

  double PUscale[50];

  if( nPU>49 ) nPU = 49;

  if( iSys==0 ){
    PUscale[0] = 0.544141;
    PUscale[1] = 0.683152;
    PUscale[2] = 1.0588;
    PUscale[3] = 1.36648;
    PUscale[4] = 1.62214;
    PUscale[5] = 1.93965;
    PUscale[6] = 1.45916;
    PUscale[7] = 1.29301;
    PUscale[8] = 1.39344;
    PUscale[9] = 1.37393;
    PUscale[10] = 1.26638;
    PUscale[11] = 1.1637;
    PUscale[12] = 1.05777;
    PUscale[13] = 0.901478;
    PUscale[14] = 0.695434;
    PUscale[15] = 0.48665;
    PUscale[16] = 0.323436;
    PUscale[17] = 0.233179;
    PUscale[18] = 0.204042;
    PUscale[19] = 0.179695;
    PUscale[20] = 0.117906;
    PUscale[21] = 0.0535705;
    PUscale[22] = 0.0179761;
    PUscale[23] = 0.00486845;
    PUscale[24] = 0.00120473;
    PUscale[25] = 0.000306356;
    PUscale[26] = 8.44097e-05;
    PUscale[27] = 2.35712e-05;
    PUscale[28] = 6.33309e-06;
    PUscale[29] = 1.62779e-06;
    PUscale[30] = 3.92723e-07;
    PUscale[31] = 8.94453e-08;
    PUscale[32] = 1.90178e-08;
    PUscale[33] = 3.84203e-09;
    PUscale[34] = 7.38767e-10;
    PUscale[35] = 1.28456e-10;
    PUscale[36] = 2.08504e-11;
    PUscale[37] = 3.31182e-12;
    PUscale[38] = 4.63316e-13;
    PUscale[39] = 4.72854e-14;
    PUscale[40] = 0;
    PUscale[41] = 0;
    PUscale[42] = 0;
    PUscale[43] = 0;
    PUscale[44] = 0;
    PUscale[45] = 0;
    PUscale[46] = 0;
    PUscale[47] = 0;
    PUscale[48] = 0;
    PUscale[49] = 0;
  }
  else if( iSys==1 ){
    PUscale[0] = 0.458261;
    PUscale[1] = 0.626711;
    PUscale[2] = 0.971785;
    PUscale[3] = 1.21776;
    PUscale[4] = 1.34764;
    PUscale[5] = 1.4248;
    PUscale[6] = 0.922526;
    PUscale[7] = 0.744979;
    PUscale[8] = 0.913723;
    PUscale[9] = 1.06132;
    PUscale[10] = 1.11114;
    PUscale[11] = 1.12292;
    PUscale[12] = 1.13425;
    PUscale[13] = 1.10829;
    PUscale[14] = 1.00558;
    PUscale[15] = 0.83577;
    PUscale[16] = 0.639871;
    PUscale[17] = 0.469319;
    PUscale[18] = 0.361301;
    PUscale[19] = 0.306711;
    PUscale[20] = 0.237734;
    PUscale[21] = 0.142901;
    PUscale[22] = 0.0656738;
    PUscale[23] = 0.0238299;
    PUscale[24] = 0.00722283;
    PUscale[25] = 0.00197294;
    PUscale[26] = 0.000550982;
    PUscale[27] = 0.000165108;
    PUscale[28] = 5.14307e-05;
    PUscale[29] = 1.60005e-05;
    PUscale[30] = 4.76288e-06;
    PUscale[31] = 1.35321e-06;
    PUscale[32] = 3.62213e-07;
    PUscale[33] = 9.29401e-08;
    PUscale[34] = 2.28987e-08;
    PUscale[35] = 5.14682e-09;
    PUscale[36] = 1.08953e-09;
    PUscale[37] = 2.27672e-10;
    PUscale[38] = 4.24244e-11;
    PUscale[39] = 6.6564e-12;
    PUscale[40] = 1.21726e-12;
    PUscale[41] = 1.25024e-13;
    PUscale[42] = 0;
    PUscale[43] = 0;
    PUscale[44] = 0;
    PUscale[45] = 0;
    PUscale[46] = 0;
    PUscale[47] = 0;
    PUscale[48] = 0;
    PUscale[49] = 0;
  }
  else if( iSys==-1 ){
    PUscale[0] = 0.637352;
    PUscale[1] = 0.745524;
    PUscale[2] = 1.16977;
    PUscale[3] = 1.55999;
    PUscale[4] = 2.01896;
    PUscale[5] = 2.79883;
    PUscale[6] = 2.50005;
    PUscale[7] = 2.22714;
    PUscale[8] = 2.00474;
    PUscale[9] = 1.67907;
    PUscale[10] = 1.37446;
    PUscale[11] = 1.13578;
    PUscale[12] = 0.899819;
    PUscale[13] = 0.646461;
    PUscale[14] = 0.412783;
    PUscale[15] = 0.243661;
    PUscale[16] = 0.153684;
    PUscale[17] = 0.125858;
    PUscale[18] = 0.116543;
    PUscale[19] = 0.0860169;
    PUscale[20] = 0.0414331;
    PUscale[21] = 0.0133115;
    PUscale[22] = 0.00326222;
    PUscale[23] = 0.000723524;
    PUscale[24] = 0.000169442;
    PUscale[25] = 4.20509e-05;
    PUscale[26] = 1.04015e-05;
    PUscale[27] = 2.41401e-06;
    PUscale[28] = 5.19674e-07;
    PUscale[29] = 1.0525e-07;
    PUscale[30] = 1.97832e-08;
    PUscale[31] = 3.47419e-09;
    PUscale[32] = 5.63765e-10;
    PUscale[33] = 8.60403e-11;
    PUscale[34] = 1.23701e-11;
    PUscale[35] = 1.59276e-12;
    PUscale[36] = 1.89108e-13;
    PUscale[37] = 1.98468e-14;
    PUscale[38] = 0;
    PUscale[39] = 0;
    PUscale[40] = 0;
    PUscale[41] = 0;
    PUscale[42] = 0;
    PUscale[43] = 0;
    PUscale[44] = 0;
    PUscale[45] = 0;
    PUscale[46] = 0;
    PUscale[47] = 0;
    PUscale[48] = 0;
    PUscale[49] = 0;
  }

  return PUscale[nPU];
}
