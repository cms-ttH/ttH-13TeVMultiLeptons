// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MultileptonAna.h"
#include <algorithm>

//// #if !defined( MULTILEPTONANA_CC )

MultileptonAna::MultileptonAna(){} // use EDAnalyzer constructor

MultileptonAna::~MultileptonAna(){} 


void MultileptonAna::detectData(string sampleName) {
  isData = false;
  string dataset = "MC";

  if (TString(sampleName).Contains("DoubleElectron")) dataset = "DoubleElectron";
  if (TString(sampleName).Contains("DoubleMu")) dataset = "DoubleMu";
  if (TString(sampleName).Contains("MuEG")) dataset = "MuEG";
  if (TString(sampleName).Contains("MET")) dataset = "MET";

  if (dataset != "MC") {
    std::cout << "CONFIG: DATA detected for sample " << sampleName << std::endl;
    isData = true;
  }
}

int MultileptonAna::convertSampleNameToNumber(string sampleName) {
  sampleNumber = 999999;
  double weight_Xsec = 1.0;
  int nGen = 1;
  float Xsec = 1.0;

  // make a TString version of this so you can use it for contains
  TString tmpName (sampleName);

  if (analysisYear == "2011") {
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
  else if (analysisYear == "2012_52x" || analysisYear == "2012_53x") {
    if (isData) sampleNumber = -1;
    else if (sampleName == "ttbar" || tmpName.Contains("ttbar_part")) { sampleNumber = 2500;
      nGen = 6912438+1362471; Xsec = 245.8; }
    else if (sampleName == "ttbar_bb" || tmpName.Contains("ttbar_bb_part")) { sampleNumber = 2555;
      nGen = 6912438+1362471; Xsec = 245.8; }
    else if (sampleName == "ttbar_cc" || tmpName.Contains("ttbar_cc_part")) { sampleNumber = 2544;
      nGen = 6912438+1362471; Xsec = 245.8; }
    else if (sampleName == "ttbar_scaleup") sampleNumber = 2511; 
    else if (sampleName == "ttbar_scaledown") sampleNumber = 2510; 
    else if (sampleName == "ttbar_matchingup") sampleNumber = 2513; 
    else if (sampleName == "ttbar_matchingdown") sampleNumber = 2512; 
    else if (sampleName == "ttbar_jj" || tmpName.Contains("ttbar_jj_part")) { sampleNumber = 2566;
      nGen = 31111456; Xsec = 0.457*245.8;
      weight_Xsec = ( 0.457 / 31111456 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_lj" || tmpName.Contains("ttbar_lj_part")) { sampleNumber = 2563;
      nGen = 25327478; Xsec = 0.438*245.8;
      weight_Xsec = ( 0.438 / 25327478 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_ll" || tmpName.Contains("ttbar_ll_part")) { sampleNumber = 2533;
      nGen = 12100452; Xsec = 0.105*245.8;
      weight_Xsec = ( 0.105 / 12100452 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_cc_jj" || tmpName.Contains("ttbar_cc_jj_part")) { sampleNumber = 2576;
      nGen = 31111456; Xsec = 0.457*245.8;
      weight_Xsec = ( 0.457 / 31111456 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_cc_lj" || tmpName.Contains("ttbar_cc_lj_part")) { sampleNumber = 2573;
      nGen = 25327478; Xsec = 0.438*245.8;
      weight_Xsec = ( 0.438 / 25327478 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_cc_ll" || tmpName.Contains("ttbar_cc_ll_part")) { sampleNumber = 2543;
      nGen = 12100452; Xsec = 0.105*245.8;
      weight_Xsec = ( 0.105 / 12100452 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_bb_jj" || tmpName.Contains("ttbar_bb_jj_part")) { sampleNumber = 2586;
      nGen = 31111456; Xsec = 0.457*245.8;
      weight_Xsec = ( 0.457 / 31111456 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_bb_lj" || tmpName.Contains("ttbar_bb_lj_part")) { sampleNumber = 2583;
      nGen = 25327478; Xsec = 0.438*245.8;
      weight_Xsec = ( 0.438 / 25327478 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_bb_ll" || tmpName.Contains("ttbar_bb_ll_part")) { sampleNumber = 2553;
      nGen = 12100452; Xsec = 0.105*245.8;
      weight_Xsec = ( 0.105 / 12100452 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_b_jj" || tmpName.Contains("ttbar_b_jj_part")) { sampleNumber = 2596;
      nGen = 31111456; Xsec = 0.457*245.8;
      weight_Xsec = ( 0.457 / 31111456 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_b_lj" || tmpName.Contains("ttbar_b_lj_part")) { sampleNumber = 2593;
      nGen = 25327478; Xsec = 0.438*245.8;
      weight_Xsec = ( 0.438 / 25327478 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_b_ll" || tmpName.Contains("ttbar_b_ll_part")) { sampleNumber = 2599;
      nGen = 12100452; Xsec = 0.105*245.8;
      weight_Xsec = ( 0.105 / 12100452 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "wjets" || tmpName.Contains("wjets_part")) { sampleNumber = 2400;
      nGen = 57536319; Xsec = 36257; }
    else if (sampleName == "wjets_0p" || tmpName.Contains("wjets_0p_part")) { sampleNumber = 2400;
      nGen = 57536319; Xsec = 36257; }
    else if (sampleName == "wjets_1p" || tmpName.Contains("wjets_1p_part")) { sampleNumber = 2400;
      nGen = 23134881; Xsec = 6440.4;
      weight_Xsec = ( 5400.0 / 23134881 ) / ( 30400.0 / 57536319 ); }
    else if (sampleName == "wjets_2p" || tmpName.Contains("wjets_2p_part")) { sampleNumber = 2400;
      nGen = 33933328; Xsec = 2087.2;
      weight_Xsec = ( 1750.0 / 339333285 ) / ( 30400.0 / 57536319 ); }
    else if (sampleName == "wjets_3p" || tmpName.Contains("wjets_3p_part")) { sampleNumber = 2400;
      nGen = 15463420; Xsec = 619.0;
      weight_Xsec = ( 519.0 / 15463420 ) / ( 30400.0 / 57536319 ); }
    else if (sampleName == "wjets_4p" || tmpName.Contains("wjets_4p_part")) { sampleNumber = 2400;
      nGen = 13365439; Xsec = 255.2;
      weight_Xsec = ( 214.0 / 13365439 ) / ( 30400.0 / 57536319 ); } 
    else if (sampleName == "zjets_lowmass" || tmpName.Contains("zjets_lowmass_part")) { sampleNumber = 2850;
      nGen = 37828841; Xsec = 14702; }
    else if (sampleName == "zjets_lowmass_1p" || tmpName.Contains("zjets_lowmass_1p_part")) { sampleNumber = 2851;
      weight_Xsec = ( 716.0 / 8039604 ) / ( 11050.0 / 37828841 ); }
    else if (sampleName == "zjets_lowmass_2p" || tmpName.Contains("zjets_lowmass_2p_part")) { sampleNumber = 2852;
      weight_Xsec = ( 309.7 / 30684442 ) / ( 11050.0 / 37828841 ); }
    else if (sampleName == "zjets" || tmpName.Contains("zjets_part")) { sampleNumber = 2800;
      nGen =  30072710; Xsec = 3505.7; }
    else if (sampleName == "zjets_0p" || tmpName.Contains("zjets_0p_part")) { sampleNumber = 2800;
      nGen =  30072710; Xsec = 3505.7; }
    else if (sampleName == "zjets_1p" || tmpName.Contains("zjets_1p_part")) { sampleNumber = 2801;
      nGen = 24032562; Xsec = 666.7;
      weight_Xsec = ( 561.0 / 24032562 ) / ( 2950.0 /  30072710 ); }
    else if (sampleName == "zjets_2p" || tmpName.Contains("zjets_2p_part")) { sampleNumber = 2802;
      nGen = 2350806; Xsec = 215.1;
      weight_Xsec = ( 181.0 / 2350806 ) / ( 2950.0 /  30072710 ); }
    else if (sampleName == "zjets_3p" || tmpName.Contains("zjets_3p_part")) { sampleNumber = 2803;
      nGen = 10753491; Xsec = 66.07;
      weight_Xsec = ( 55.6 / 10753491 ) / ( 2950.0 /  30072710 ); }
    else if (sampleName == "zjets_4p" || tmpName.Contains("zjets_4p_part")) { sampleNumber = 2804;
      nGen = 6370630; Xsec = 27.38;
      weight_Xsec = ( 23.04 /6370630 ) / ( 2950.0 /  30072710 ); }
    else if (sampleName == "singlet_s") { sampleNumber = 2600;
      nGen = 259657; Xsec = 3.79; }
    else if (sampleName == "singlet_s_ll") sampleNumber = 2630;
    else if (sampleName == "singletbar_s") { sampleNumber = 2601;
      nGen = 139835; Xsec = 1.76; }
    else if (sampleName == "singletbar_s_ll") sampleNumber = 2631; 
    else if (sampleName == "singlet_t") { sampleNumber = 2602;
      nGen = 3744404; Xsec = 56.4; }
    else if (sampleName == "singlet_t_ll") sampleNumber = 2632; 
    else if (sampleName == "singletbar_t") { sampleNumber = 2603;
      nGen = 1933504; Xsec = 30.7; }
    else if (sampleName == "singletbar_t_ll") sampleNumber = 2633; 
    else if (sampleName == "singlet_tW") { sampleNumber = 2604;
      nGen = 496918; Xsec = 11.1; }
    else if (sampleName == "singlet_tW_lj") sampleNumber = 2654; 
    else if (sampleName == "singlet_tW_jl") sampleNumber = 2664; 
    else if (sampleName == "singlet_tW_ll") sampleNumber = 2634; 
    else if (sampleName == "singletbar_tW") { sampleNumber = 2605;
      nGen = 492779; Xsec = 7.87; }
    else if (sampleName == "singletbar_tW_lj") sampleNumber = 2655; 
    else if (sampleName == "singletbar_tW_jl") sampleNumber = 2665; 
    else if (sampleName == "singletbar_tW_ll") sampleNumber = 2635; 
    else if (sampleName == "ww") { sampleNumber = 2700;
      nGen = 9955089; Xsec = 54.8; }
    else if (sampleName == "ww_ll") { sampleNumber = 2700;
      nGen = 1931931; Xsec = 54.8*0.324*0.324; }
    else if (sampleName == "www") { sampleNumber = 2710;
      nGen = 220040; Xsec =  0.08217; }
    else if (sampleName == "wwz") { sampleNumber = 2720;
      nGen = 221576; Xsec = 0.0633; }
    else if (sampleName == "wwG") { sampleNumber = 2720;
      nGen = 94500; Xsec = 0.0000001; } //AWB incorrect values
    else if (tmpName.Contains("wz") && !(tmpName.Contains("_ll") || tmpName.Contains("_lj"))) { sampleNumber = 2701;      
      nGen = 9931257; Xsec = 32.3; }
    else if (tmpName.Contains("wz") && tmpName.Contains("lll")) { sampleNumber = 2731;
      nGen = 1987010; Xsec = 1.057*1.10; } 
    else if (tmpName.Contains("wz") && tmpName.Contains("lljj")) { sampleNumber = 2761;
      nGen = 3212461; Xsec = 32.3*0.101*(1-0.324); }
    else if (tmpName.Contains("wz") && tmpName.Contains("ljj")) { sampleNumber = 2791;
      nGen = 2906320; Xsec = 32.3*0.324*0.699; }
    else if (sampleName == "wzz") { sampleNumber = 2721;
      nGen = 219835; Xsec = 0.01922; } 
    else if (tmpName.Contains("zz") && !tmpName.Contains("_ll")) { sampleNumber = 2702;
      nGen = 9755621; Xsec = 7.7; }
    else if (tmpName.Contains("zz") && tmpName.Contains("llll")) { sampleNumber = 2732;
      nGen = 4804217; Xsec = 0.157*1.21; } //why is it not (7.7*0.101*0.101) * 1.21?
    else if (tmpName.Contains("zz") && tmpName.Contains("lowmll")) { sampleNumber = 2732;
      nGen = 4804217; Xsec = 0.157*1.21; } //Incorrect nGen and Xsec
    else if (tmpName.Contains("zz") && tmpName.Contains("lljj")) { sampleNumber = 2762;
      nGen = 1934806; Xsec = 7.7*2*0.101*0.699; }
    else if (sampleName == "zzz") { sampleNumber = 2722;
      nGen = 224519; Xsec = 0.004587; }
    else if (sampleName == "ttbarW") { sampleNumber = 2524;
      nGen = 195396; Xsec = 0.249; }
    else if (sampleName == "ttbarWW") { sampleNumber = 2534;
      nGen = 216867; Xsec = 0.002037; }
    else if (sampleName == "ttbarZ") { sampleNumber = 2523;
      nGen = 209512; Xsec = 0.206; }
    else if (sampleName == "ttbarG") { sampleNumber = 2560;
      nGen = 71405; Xsec = 1.444*1.8; } 
    else if (sampleName == "ttbarGStar_ee") { sampleNumber = 2567;
      nGen = 13517; Xsec = 1.5*0.02724*0.104; } 
    else if (sampleName == "ttbarGStar_mm") { sampleNumber = 2568;
      nGen = 8019; Xsec = 1.5*0.01233*0.141; }
    else if (sampleName == "ttbarGStar_tt") { sampleNumber = 2569;
      nGen = 17289; Xsec = 1.5*0.00133*0.038; } 
    else if (sampleName == "tttt") { sampleNumber = 2525;
      nGen = 99994; Xsec = 0.000716; }
    else if (sampleName == "tbZ_ll") { sampleNumber = 2000;
      nGen = 148158; Xsec = 0.0114; }
    else if (sampleName == "WpWpqq") { sampleNumber = 2001;
      nGen = 99700; Xsec = 0.2482; }
    else if (sampleName == "WmWmqq") { sampleNumber = 2002;
      nGen = 1; Xsec = 0.0889; } //Not yet processed
    else if (sampleName == "WWDPI") { sampleNumber = 2003;
      nGen = 833755; Xsec = 0.5879; }
    else if (sampleName == "VH_tautau") { sampleNumber = 2915;
      nGen = 200124; Xsec = 0.07717352; } 
    else if (sampleName == "VH_TauMu") { sampleNumber = 2915; 
      nGen = 200124; Xsec = 0.07717352; }
    else if (sampleName == "VH_ZZ") { sampleNumber = 2923;
      nGen = 500409; Xsec = 0.03223704; } 
    else if (sampleName == "VH_WW") { sampleNumber = 2924;
      nGen = 200408; Xsec = 0.2625365; } 
    else if (tmpName.Contains("ttH") && analysisYear == "2012_52x") {
      if (tmpName.Contains("FullSim")) sampleNumber = 8120;
      else sampleNumber = 9120;
    }
    // hack hack hack to allow me to keep a separate list
    // treat this as a regular sample
    else if (sampleName == "ttbar_lj_passMva")  { sampleNumber = 2500;
      nGen = 25165429; Xsec = 98.65;
      weight_Xsec = ( 0.438 / 25165429 ) / ( 1.0 / ( 6889624 + 1362471 ));
    } 
    else if (tmpName.Contains("ttH") && analysisYear == "2012_53x") {
      if (tmpName.Contains("_tautau")) { sampleNumber = 7120;
        nGen = 992997; Xsec = 0.1302*0.1302; }
      else if (tmpName.Contains("_bb")) { sampleNumber = 8120;
        nGen = 980931; Xsec = 0.1302*0.577; }
      else { sampleNumber = 9120;
        nGen = 992997; Xsec = 0.1302; }
    }
    
    else assert (sampleName == "sampleName is not in the approved list");
  }
  
  else if (analysisYear == "2015_72x" || analysisYear == "2015_73x" || analysisYear == "2015_74x")
  {
    if (isData) sampleNumber = -1;
    else if (tmpName.Contains("ttH")) {
      sampleNumber = 9125;
      nGen = 200000; // phys14
      Xsec = 0.8696; //pb
      
    }
      
  } // 2015
  
  else {
    assert (analysisYear == "either 2012_52x, 2012_53x, 2011, or 2015_72X, etc.");
  }

  if (tmpName.Contains("wz") || tmpName.Contains("zz")) {
    if (tmpName.Contains("_lf")) sampleNumber = sampleNumber*10 + 1;
    if (tmpName.Contains("_cc")) sampleNumber = sampleNumber*10 + 2;
    if (tmpName.Contains("_bb")) sampleNumber = sampleNumber*10 + 4;
    else if (tmpName.Contains("_b")) sampleNumber = sampleNumber*10 + 3;
  }

  std::cout << "CONFIG: Sample Name = " << sampleName << ", sample Number = " << sampleNumber << endl;
  std::cout << "weight_Xsec: " << weight_Xsec << " (nGen: " << nGen << ", Xsec: " << Xsec << ") " << endl;
  
  return sampleNumber;
}



void MultileptonAna::parse_params()
{
	setupoptionsparams = 	entire_pset.getParameter<edm::ParameterSet> ("setupoptions");
	triggerparams = 	entire_pset.getParameter<edm::ParameterSet> ("triggers");
	muonparams = 		entire_pset.getParameter<edm::ParameterSet> ("muons");
      	electronparams = 	entire_pset.getParameter<edm::ParameterSet> ("electrons");
      	leptonparams = 		entire_pset.getParameter<edm::ParameterSet> ("leptons");
      	jetparams = 		entire_pset.getParameter<edm::ParameterSet> ("jets");
      	subjetparams = 		entire_pset.getParameter<edm::ParameterSet> ("fatjets");
      	btagparams = 		entire_pset.getParameter<edm::ParameterSet> ("btags");
      	metparams = 		entire_pset.getParameter<edm::ParameterSet> ("met");
	prunedparams =          entire_pset.getParameter<edm::ParameterSet> ("prunedgenparticles");
      	variableparams = 	entire_pset.getParameter<edm::ParameterSet> ("variables");
      	systparams = 		entire_pset.getParameter<edm::ParameterSet> ("systematics");
      	selectionparams = 	entire_pset.getParameter<edm::ParameterSet> ("eventselection");
	
}

void MultileptonAna::SetupOptions (const edm::Event& event)
{
	string rhostr = setupoptionsparams.getParameter<string> ("rhoHandle");
	edm::Handle<double> rhoHandle;
  	event.getByLabel(rhostr,rhoHandle);  //"fixedGridRhoAll");
  	rho = *rhoHandle;
	sampleName = setupoptionsparams.getParameter<string> ("sample");

}
vstring MultileptonAna::HLTInfo ()
{
	vstring HLT_triggers = triggerparams.getParameter<vstring> ("trigger_vstring");
	if (debug) cout << "triggers to include:" << endl;
	if (debug) for (unsigned int i=0; i<HLT_triggers.size(); i++) { cout << HLT_triggers[i] << endl; }
	hltTag = triggerparams.getParameter<string> ("hltlabel");
	
	return HLT_triggers;
}


void MultileptonAna::setupMva(){
  mvaID_ = new EGammaMvaEleEstimatorFWLite();
  bool useBinnedVersion_ = true;
  string method_ = "BDT";
  EGammaMvaEleEstimatorFWLite::MVAType type_ = EGammaMvaEleEstimatorFWLite::kNonTrigPhys14;
  std::vector<std::string> mvaWeightFiles_;


  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB1_10_oldscenario2phys14_BDT.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB1_5_oldscenario2phys14_BDT.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EE_10_oldscenario2phys14_BDT.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB2_10_oldscenario2phys14_BDT.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB2_5_oldscenario2phys14_BDT.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EE_5_oldscenario2phys14_BDT.weights.xml");

  mvaID_->initialize(method_, type_, useBinnedVersion_, mvaWeightFiles_);

  mu_reader_high_b = new TMVA::Reader( "!Color:!Silent" );
  mu_reader_high_e = new TMVA::Reader( "!Color:!Silent" );
  mu_reader_medium_b = new TMVA::Reader( "!Color:!Silent" );
  mu_reader_medium_e = new TMVA::Reader( "!Color:!Silent" );
  mu_reader_low = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_high_cb = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_high_fb = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_high_ec = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_medium_cb = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_medium_fb = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_medium_ec = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_low = new TMVA::Reader( "!Color:!Silent" );

  ele_reader_high_cb->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  ele_reader_high_cb->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  ele_reader_high_cb->AddVariable( "LepGood_jetDR", &varjetDR_in );
  ele_reader_high_cb->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  ele_reader_high_cb->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  ele_reader_high_cb->AddVariable( "LepGood_sip3d", &varsip3d );
  ele_reader_high_cb->AddVariable( "LepGood_dxy", &vardxy );
  ele_reader_high_cb->AddVariable( "LepGood_dz", &vardz );
  ele_reader_high_cb->AddVariable( "LepGood_mvaIdPhys14", &varmvaId );

  ele_reader_high_fb->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  ele_reader_high_fb->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  ele_reader_high_fb->AddVariable( "LepGood_jetDR", &varjetDR_in );
  ele_reader_high_fb->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  ele_reader_high_fb->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  ele_reader_high_fb->AddVariable( "LepGood_sip3d", &varsip3d );
  ele_reader_high_fb->AddVariable( "LepGood_dxy", &vardxy );
  ele_reader_high_fb->AddVariable( "LepGood_dz", &vardz );
  ele_reader_high_fb->AddVariable( "LepGood_mvaIdPhys14", &varmvaId );

  ele_reader_high_ec->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  ele_reader_high_ec->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  ele_reader_high_ec->AddVariable( "LepGood_jetDR", &varjetDR_in );
  ele_reader_high_ec->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  ele_reader_high_ec->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  ele_reader_high_ec->AddVariable( "LepGood_sip3d", &varsip3d );
  ele_reader_high_ec->AddVariable( "LepGood_dxy", &vardxy );
  ele_reader_high_ec->AddVariable( "LepGood_dz", &vardz );
  ele_reader_high_ec->AddVariable( "LepGood_mvaIdPhys14", &varmvaId );

  ele_reader_medium_cb->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  ele_reader_medium_cb->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  ele_reader_medium_cb->AddVariable( "LepGood_jetDR", &varjetDR_in );
  ele_reader_medium_cb->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  ele_reader_medium_cb->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  ele_reader_medium_cb->AddVariable( "LepGood_sip3d", &varsip3d );
  ele_reader_medium_cb->AddVariable( "LepGood_dxy", &vardxy );
  ele_reader_medium_cb->AddVariable( "LepGood_dz", &vardz );
  ele_reader_medium_cb->AddVariable( "LepGood_mvaIdPhys14", &varmvaId );

  ele_reader_medium_fb->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  ele_reader_medium_fb->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  ele_reader_medium_fb->AddVariable( "LepGood_jetDR", &varjetDR_in );
  ele_reader_medium_fb->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  ele_reader_medium_fb->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  ele_reader_medium_fb->AddVariable( "LepGood_sip3d", &varsip3d );
  ele_reader_medium_fb->AddVariable( "LepGood_dxy", &vardxy );
  ele_reader_medium_fb->AddVariable( "LepGood_dz", &vardz );
  ele_reader_medium_fb->AddVariable( "LepGood_mvaIdPhys14", &varmvaId );

  ele_reader_medium_ec->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  ele_reader_medium_ec->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  ele_reader_medium_ec->AddVariable( "LepGood_jetDR", &varjetDR_in );
  ele_reader_medium_ec->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  ele_reader_medium_ec->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  ele_reader_medium_ec->AddVariable( "LepGood_sip3d", &varsip3d );
  ele_reader_medium_ec->AddVariable( "LepGood_dxy", &vardxy );
  ele_reader_medium_ec->AddVariable( "LepGood_dz", &vardz );
  ele_reader_medium_ec->AddVariable( "LepGood_mvaIdPhys14", &varmvaId );

  ele_reader_low->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  ele_reader_low->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  ele_reader_low->AddVariable( "LepGood_jetDR", &varjetDR_in );
  ele_reader_low->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  ele_reader_low->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  ele_reader_low->AddVariable( "LepGood_sip3d", &varsip3d );
  ele_reader_low->AddVariable( "LepGood_dxy", &vardxy );
  ele_reader_low->AddVariable( "LepGood_dz", &vardz );
  ele_reader_low->AddVariable( "LepGood_mvaIdPhys14", &varmvaId );

  mu_reader_low->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  mu_reader_low->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  mu_reader_low->AddVariable( "LepGood_jetDR", &varjetDR_in );
  mu_reader_low->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  mu_reader_low->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  mu_reader_low->AddVariable( "LepGood_sip3d", &varsip3d );
  mu_reader_low->AddVariable( "LepGood_dxy", &vardxy );
  mu_reader_low->AddVariable( "LepGood_dz", &vardz );
  mu_reader_low->AddVariable( "LepGood_segmentCompatibility", &varSegCompat );

  mu_reader_medium_b->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  mu_reader_medium_b->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  mu_reader_medium_b->AddVariable( "LepGood_jetDR", &varjetDR_in );
  mu_reader_medium_b->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  mu_reader_medium_b->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  mu_reader_medium_b->AddVariable( "LepGood_sip3d", &varsip3d );
  mu_reader_medium_b->AddVariable( "LepGood_dxy", &vardxy );
  mu_reader_medium_b->AddVariable( "LepGood_dz", &vardz );
  mu_reader_medium_b->AddVariable( "LepGood_segmentCompatibility", &varSegCompat );

  mu_reader_medium_e->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  mu_reader_medium_e->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  mu_reader_medium_e->AddVariable( "LepGood_jetDR", &varjetDR_in );
  mu_reader_medium_e->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  mu_reader_medium_e->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  mu_reader_medium_e->AddVariable( "LepGood_sip3d", &varsip3d );
  mu_reader_medium_e->AddVariable( "LepGood_dxy", &vardxy );
  mu_reader_medium_e->AddVariable( "LepGood_dz", &vardz );
  mu_reader_medium_e->AddVariable( "LepGood_segmentCompatibility", &varSegCompat );

  mu_reader_high_b->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  mu_reader_high_b->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  mu_reader_high_b->AddVariable( "LepGood_jetDR", &varjetDR_in );
  mu_reader_high_b->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  mu_reader_high_b->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  mu_reader_high_b->AddVariable( "LepGood_sip3d", &varsip3d );
  mu_reader_high_b->AddVariable( "LepGood_dxy", &vardxy );
  mu_reader_high_b->AddVariable( "LepGood_dz", &vardz );
  mu_reader_high_b->AddVariable( "LepGood_segmentCompatibility", &varSegCompat );

  mu_reader_high_e->AddVariable( "LepGood_neuRelIso03", &varneuRelIso );
  mu_reader_high_e->AddVariable( "LepGood_chRelIso03", &varchRelIso );
  mu_reader_high_e->AddVariable( "LepGood_jetDR", &varjetDR_in );
  mu_reader_high_e->AddVariable( "LepGood_jetPtRatio", &varjetPtRatio_in );
  mu_reader_high_e->AddVariable( "LepGood_jetBTagCSV", &varjetBTagCSV_in );
  mu_reader_high_e->AddVariable( "LepGood_sip3d", &varsip3d );
  mu_reader_high_e->AddVariable( "LepGood_dxy", &vardxy );
  mu_reader_high_e->AddVariable( "LepGood_dz", &vardz );
  mu_reader_high_e->AddVariable( "LepGood_segmentCompatibility", &varSegCompat );

  mu_reader_high_b->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_high_b_BDTG.weights.xml");
  mu_reader_high_e->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_high_e_BDTG.weights.xml");
  mu_reader_medium_b->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_medium_b_BDTG.weights.xml");
  mu_reader_medium_e->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_medium_e_BDTG.weights.xml");
  mu_reader_low->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_low_BDTG.weights.xml");

  ele_reader_high_cb->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_high_cb_BDTG.weights.xml");
  ele_reader_high_fb->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_high_fb_BDTG.weights.xml");
  ele_reader_high_ec->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_high_ec_BDTG.weights.xml");
  ele_reader_medium_cb->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_medium_cb_BDTG.weights.xml");
  ele_reader_medium_fb->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_medium_fb_BDTG.weights.xml");
  ele_reader_medium_ec->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_medium_ec_BDTG.weights.xml");
  ele_reader_low->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_low_BDTG.weights.xml");
  
  
  
}





trigRes MultileptonAna::GetTriggers (const edm::Event& event)
{
	// hltTag already got by HLTInfo ...	
	edm::Handle<edm::TriggerResults> triggerResults;
	event.getByLabel(edm::InputTag("TriggerResults","", hltTag), triggerResults);
	return triggerResults;
}


patMuons MultileptonAna::GetMuons (const edm::Event& event)
{
	string muCollection = muonparams.getParameter<string> ("muonCollection");
	patMuons muonHandle; 
	event.getByLabel(muCollection,muonHandle);
	return muonHandle;
	
}
patElectrons MultileptonAna::GetElectrons (const edm::Event& event)
{
	string elCollection = electronparams.getParameter<string> ("electronCollection");
	patElectrons electronHandle; 
	event.getByLabel(elCollection,electronHandle);
	return electronHandle;
	
}
vecPatLepton MultileptonAna::fillLeptons(const vecPatMuon& muons, const vecPatElectron& electrons)
{
  vecPatLepton leptons;
  for (vecPatMuon::const_iterator iMu = muons.begin(); iMu != muons.end(); iMu++)
    {
      leptons.push_back(*iMu);
    }
  for (vecPatElectron::const_iterator iEle = electrons.begin(); iEle != electrons.end(); iEle++)
    {
      leptons.push_back(*iEle);
    }
  return leptons;
}

void MultileptonAna::GetLeptons (const edm::Event& event)
{
	bool are_electrons_added_to_leptons = leptonparams.getParameter<bool> ("useElectrons");
	bool are_muons_added_to_leptons = leptonparams.getParameter<bool> ("useMuons");
	
	if (debug) cout << are_electrons_added_to_leptons << " " << are_muons_added_to_leptons << endl;
	
	
}
patJets MultileptonAna::GetJets (const edm::Event& event)
{
	string mainjetCollection = jetparams.getParameter<string> ("jetCollection");
	patJets jetsHandle; 
	event.getByLabel(mainjetCollection,jetsHandle);
	return jetsHandle;
	
	
}
patJets MultileptonAna::GetSubJets (const edm::Event& event)
{
	string subjetCollection = subjetparams.getParameter<string> ("fatjetCollection");
	patJets subjetsHandle; 
	event.getByLabel(subjetCollection,subjetsHandle);
	return subjetsHandle;
	
}

prunedGenParticles MultileptonAna::GetPrunedGenParticles (const edm::Event& event)
{
  string pruneCollection = prunedparams.getParameter<string> ("prunedCollection");
  prunedGenParticles prunedHandle; 
  event.getByLabel(pruneCollection,prunedHandle);
  return prunedHandle;
  
}

packedGenParticles MultileptonAna::GetPackedGenParticles (const edm::Event& event)
{
  packedGenParticles packedHandle; 
  event.getByLabel("packedPFCandidates",packedHandle);
  return packedHandle;  
}

// recoBeamSpot MultileptonAna::GetBeamSpot (const edm::Event& event, const edm::ParameterSet& pset)
// {
//   //edm::EDGetTokenT<reco::BeamSpot> bsToken_;
//   //bsToken_(consumes<reco::BeamSpot>(pset.getParameter<edm::InputTag>("offlineBeamSpot")));
//   recoBeamSpot bsHandle;
//   event.getByToken(bsToken_,bsHandle);
//   return bsHandle;  
// }



void MultileptonAna::GetBtags (const edm::Event& event)
{
	
}
patMETs MultileptonAna::GetMet (const edm::Event& event)
{
	
	string metCollection = metparams.getParameter<string> ("METCollection");
	patMETs METsHandle; 
	event.getByLabel(metCollection,METsHandle);
	return METsHandle;
	
	
}

int MultileptonAna::GetVertices (const edm::Event& event)
{
	
	////////////////////////////////////////////////////////////
	//
	// count pvs for miniAODhelper
	//
	////////////////////////////////////////////////////////////

	//vars for vertex loop
	reco::Vertex vertex;
	double minNDOF = 4.0;
	double maxAbsZ = 24.0;
	double maxd0 = 2.;
	int numpv = 0;

	edm::Handle<reco::VertexCollection> vtxHandle;
	event.getByLabel("offlineSlimmedPrimaryVertices",vtxHandle);
	reco::VertexCollection primaryVertices = *vtxHandle;

	numpv = 0;

	for (reco::VertexCollection::const_iterator iPV = primaryVertices.begin(); iPV != primaryVertices.end(); ++iPV)
	{
		bool isGood = ( !(iPV->isFake()) && (iPV->ndof()>=minNDOF) && (abs(iPV->z())<=maxAbsZ) && (abs(iPV->position().Rho())<=maxd0));
		if ( !isGood ) continue;
		if ( numpv == 0 ) vertex = *iPV;
		numpv++;
	}

	//cout << "numpv = " << numpv << endl;
	if ( numpv > 0 )
	{
		//cout << "setting vertex, numpv > 0" << endl;
		//miniAODhelper.SetVertex(vertex);
		SetVertex(vertex);
	}

	return numpv;
	
}


// void MultileptonAna::Variables (const edm::Event& event)
// {
// 	//vstring variable_list = variableparams.getParameter<vstring> ("thevars");
// }
void MultileptonAna::Systematics (const edm::Event& event)
{
	
	//bool include_systematics = systparams.getParameter<bool> ("include_syst");
	//vstring vstring_of_systs = systparams.getParameter<vstring> ("syst_list");
	
}
void MultileptonAna::EventSelection (const edm::Event& event)
{
	//edm::ParameterSet lepselection_pset = selectionparams.getParameter<edm::ParameterSet> ("Leps");
	//string numJets_str = selectionparams.getParameter<string> ("numJets");
	//string numTags_str = selectionparams.getParameter<string> ("numTags");
	//double met_cut = selectionparams.getParameter<double> ("METcut");
	
}

int MultileptonAna::GetHiggsDaughterId(const std::vector<reco::GenParticle>& genParticles)
{
  int daughter_id = -99e6;
  for (std::vector<reco::GenParticle>::const_iterator genParticle = genParticles.begin(); genParticle != genParticles.end(); genParticle++)
    {
      
      if (genParticle->pdgId() == 25 && genParticle->numberOfDaughters() > 0 && abs(genParticle->daughter(0)->pdgId()) != 25)
	{
	  daughter_id = abs(genParticle->daughter(0)->pdgId());
	  // if (daughter_id == 25 && genParticle->numberOfDaughters() >= 1)
	  //   {
	  //     daughter_id = abs(genParticle->daughter(1)->pdgId());
	  //   }
	  break;
	}
    }
  return daughter_id;
}

vector<double> MultileptonAna::ReturnBTagDisc (vecPatJet theobjs)
{
	vector<double> thediscs;
	
	string thedisc = btagparams.getParameter<string> ("btagdisc");
	
	for (jetit iJet = theobjs.begin(); iJet != theobjs.end(); ++iJet)
	{
		double discOutput = iJet->bDiscriminator(thedisc);
		thediscs.push_back(discOutput);
	}
	
	return thediscs;
	
}

vector<double> MultileptonAna::ReturnPUJetID (vecPatJet theobjs)
{
	vector<double> thePUIDs;
	
	for (jetit iJet = theobjs.begin(); iJet != theobjs.end(); ++iJet)
	{
		double output = iJet->userFloat("pileupJetId:fullDiscriminant");
		thePUIDs.push_back(output);
	}
	
	return thePUIDs;
} 




vector<ttH::Lepton> MultileptonAna::GetCollection (vector<ttH::Muon> muObjs, vector<ttH::Electron>eleObjs)
{
  vector<ttH::Lepton> lepCollection(muObjs.begin(),muObjs.end());
  lepCollection.insert(lepCollection.end(),eleObjs.begin(),eleObjs.end());
  std::sort(lepCollection.begin(), lepCollection.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.obj.Pt() > b.obj.Pt();});
  return lepCollection;
}

vector<ttH::Electron> MultileptonAna::GetCollection (vecPatElectron theobjs, vecPatJet jets)
{
  ttH::Electron ele;
  vector<ttH::Electron> eleCollection;
  pat::Jet matchedJet;
  double dR;

  for (const auto & iEle: theobjs)
    {
      //calculate closest jet
      matchedJet = getClosestJet(jets,iEle);
      dR = MiniAODHelper::DeltaR(&matchedJet,&iEle);

      ele.obj = iEle.p4();
      ele.SCeta = abs(iEle.superCluster()->position().eta());
      ele.pdgID = iEle.pdgId();

      if (iEle.gsfTrack().isAvailable()){
	ele.dxy = fabs(iEle.gsfTrack()->dxy(vertex.position()));
	ele.dz = fabs(iEle.gsfTrack()->dz(vertex.position()));
	ele.numMissingInnerHits = iEle.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
      }
      else {
	ele.dxy = -9.e5;
	ele.dz = -9.e5;
	ele.numMissingInnerHits = -9e5;
      }

      ele.charge = iEle.charge();
      ele.isGsfCtfScPixChargeConsistent = iEle.isGsfCtfScPixChargeConsistent();
      ele.passConversioVeto = iEle.passConversionVeto();
      ele.relIso = GetElectronRelIso(iEle,coneSize::R03,corrType::rhoEA);
      ele.dEtaIn = iEle.deltaEtaSuperClusterTrackAtVtx();
      ele.dPhiIn = iEle.deltaPhiSuperClusterTrackAtVtx();
      ele.full5x5_sigmaIetaIeta = iEle.full5x5_sigmaIetaIeta();
      ele.hadronicOverEm = iEle.hadronicOverEm();
      
      ele.lepMVA = GetElectronLepMVA(iEle, jets);
      ele.chreliso = iEle.chargedHadronIso()/iEle.pt();
      ele.nureliso = max(0.0,(iEle.neutralHadronIso()+iEle.photonIso())-0.5*iEle.puChargedHadronIso())/iEle.pt();
      ele.matchedJetdR = min(dR,0.5);
      ele.jetPtRatio = min(iEle.pt()/matchedJet.pt(), float(1.5));
      ele.csv = max(matchedJet.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"), float(0.0));
      ele.sip3D = fabs(iEle.dB(pat::Electron::PV3D)/iEle.edB(pat::Electron::PV3D));
      ele.mvaID = mvaID_->mvaValue(iEle,false); //debug=false

      eleCollection.push_back(ele);
    }
  return eleCollection;
}

vector<ttH::Muon> MultileptonAna::GetCollection (vecPatMuon theobjs, vecPatJet jets)
{
  ttH::Muon mu;
  pat::Jet matchedJet;
  double dR;

  vector<ttH::Muon> muCollection;
  for(const auto & iMu: theobjs)
    {
      //calculate closest jet
      matchedJet = getClosestJet(jets,iMu);
      dR = MiniAODHelper::DeltaR(&matchedJet,&iMu);
      
      mu.obj = iMu.p4();
      mu.pdgID = iMu.pdgId();
      mu.charge = iMu.charge();
      mu.isPFMuon = iMu.isPFMuon();
      mu.isTrackerMuon = iMu.isTrackerMuon();
      mu.isGlobalMuon = iMu.isGlobalMuon();
      mu.relIso = GetMuonRelIso(iMu,coneSize::R03,corrType::rhoEA);
      mu.localChi2 = iMu.combinedQuality().chi2LocalPosition;
      mu.trKink = iMu.combinedQuality().trkKink;
      mu.segCompatibility = iMu.segmentCompatibility();
      
      if (iMu.innerTrack().isAvailable()){
	mu.dxy = fabs(iMu.innerTrack()->dxy(vertex.position()));
	mu.dz = fabs(iMu.innerTrack()->dz(vertex.position()));
	mu.numberOfValidPixelHits = iMu.innerTrack()->hitPattern().numberOfValidPixelHits();
	mu.trackerLayersWithMeasurement = iMu.innerTrack()->hitPattern().trackerLayersWithMeasurement();
	mu.chargeFlip = iMu.innerTrack()->ptError()/iMu.innerTrack()->pt();
	mu.lepMVA = GetMuonLepMVA(iMu, jets);
	mu.validFrac = iMu.innerTrack()->validFraction();
      }
      else {
	mu.dxy = -9.e5;
	mu.dz =  -9.e5;
	mu.numberOfValidPixelHits =  -9e5;
	mu.trackerLayersWithMeasurement = -9e5;
	mu.chargeFlip =  -9e5;
	mu.lepMVA =  -9.e5;
      }
      
      if(iMu.globalTrack().isAvailable()){
	mu.normalizedChi2 = iMu.globalTrack()->normalizedChi2();
	mu.numberOfValidMuonHits = iMu.globalTrack()->hitPattern().numberOfValidMuonHits();
      }
      else {
	mu.normalizedChi2 = -9.e5;
	mu.numberOfValidMuonHits = -9e5; 
      }
      
      mu.numberOfMatchedStations = iMu.numberOfMatchedStations();
      
      mu.chreliso = iMu.chargedHadronIso()/iMu.pt();
      mu.nureliso = max(0.0,(iMu.neutralHadronIso()+iMu.photonIso())-0.5*iMu.puChargedHadronIso())/iMu.pt();
      mu.matchedJetdR = min(dR,0.5);
      mu.jetPtRatio = min(iMu.pt()/matchedJet.pt(), float(1.5));
      mu.csv = max(matchedJet.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"), float(0.0));
      mu.sip3D = fabs(iMu.dB(pat::Muon::PV3D)/iMu.edB(pat::Muon::PV3D));

      muCollection.push_back(mu);
    }
  return muCollection;
}

vector<ttH::Jet> MultileptonAna::GetCollection (vecPatJet theobjs)
{
  ttH::Jet jet;
  vector<ttH::Jet> jetCollection;
  for(const auto & iJet: theobjs)
    {
      jet.obj = iJet.p4();
      jet.pdgID = iJet.pdgId();
      jet.charge = iJet.jetCharge();
      jet.csv = iJet.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
      jetCollection.push_back(jet);

    }
  return jetCollection;
}

vector<ttH::MET> MultileptonAna::GetCollection (patMETs theobjs)
{
  vector<ttH::MET> theMETs;
  ttH::MET theMET;
  pat::MET patMET = theobjs->front();

  theMET.obj = patMET.p4();
  theMET.pt_forSync = floor(patMET.pt()*100+0.5)/100;
  theMET.phi_forSync = floor(patMET.phi()*100+0.5)/100;

  theMETs.push_back(theMET);
  return theMETs;
}

std::vector<ttH::GenParticle> MultileptonAna::GetCollection (std::vector<reco::GenParticle> theobjs)
{
  ttH::GenParticle genParticle;
  std::vector<ttH::GenParticle> theGenParticles;
  const reco::Candidate* child0;
  const reco::Candidate* child1;
  const reco::Candidate* mother;
  const reco::Candidate* grandMother;
  std::pair<const reco::Candidate*, const reco::Candidate*> childPair;

  //  std::map<const double, std::vector<int>> family_tree;
  std::map<const double, unsigned int> family_tree;

  unsigned int i = 0;
  for (const auto & iGenParticle: theobjs)
    {
      genParticle.obj = iGenParticle.p4();
      genParticle.pdgID = iGenParticle.pdgId();
      genParticle.status = iGenParticle.status();
      genParticle.child0 = 9999;
      genParticle.child1 = 9999;
      genParticle.mother = 9999;
      genParticle.grandmother = 9999;

      family_tree[genParticle.obj.Pt()] = i;//need to decide if it's better to add the obj class pT of the pat obj pT
      theGenParticles.push_back(genParticle);
      i+=1;
    }

  i=0;
  for (const auto & iGenParticle : theobjs)
    {
      childPair = GetGenDaughterNoFsr(&iGenParticle);
      child0 = childPair.first;
      child1 = childPair.second;
      
      mother = GetGenMotherNoFsr(&iGenParticle);
      grandMother = GetGenMotherNoFsr(mother);
      
      if (child0->pdgId() != iGenParticle.pdgId() && family_tree.find(child0->pt()) != family_tree.end()) theGenParticles[i].child0 = family_tree[child0->pt()];
      if (child1->pdgId() != iGenParticle.pdgId() && family_tree.find(child1->pt()) != family_tree.end()) theGenParticles[i].child1 = family_tree[child1->pt()];
      if (family_tree.find(mother->pt()) != family_tree.end()) theGenParticles[i].mother = family_tree[mother->pt()];
      if (family_tree.find(grandMother->pt()) != family_tree.end()) theGenParticles[i].grandmother = family_tree[grandMother->pt()];

      i+=1;
    }

  return theGenParticles;
}

vdouble MultileptonAna::Get_Isos(vecPatMuon theobjs)
{
	vdouble isovec;
	
	int muonsize = theobjs.size();
	
	for (int i=0; i<muonsize; i++)
	{
		pat::Muon themuon = theobjs[i];
		double theiso = GetMuonRelIso(themuon);
		isovec.push_back(theiso);
	}
	
	return isovec;
}
	
vdouble MultileptonAna::Get_Isos(vecPatElectron theobjs)
{
	vdouble isovec;
	
	int elesize = theobjs.size();
	
	for (int i=0; i<elesize; i++)
	{
		pat::Electron theelectron = theobjs[i];
		double theiso = GetElectronRelIso(theelectron);
		isovec.push_back(theiso);
	}
	
	return isovec;
}




bool MultileptonAna::isGoodMuon(const pat::Muon& iMuon, const float iMinPt, const muonID::muonID iMuonID, const std::vector<pat::Jet>& iJets){
  
  CheckVertexSetUp();
  
  double minMuonPt = iMinPt;
  
  //float maxLooseMuonAbsEta = 2.5;
  float maxLooseMuonAbsEta = muonparams.getParameter<double> ("maxLooseMuonAbsEta");

  //float maxTightMuonAbsEta = 2.1;
//float maxTightMuonAbsEta = 0.25;
  float maxTightMuonAbsEta = muonparams.getParameter<double> ("maxTightMuonAbsEta");
  
  // Be skeptical about this muon making it through
  bool passesKinematics	= false;
  bool passesIso        = false;
  bool passesID         = false;
  bool passesTrackerID  = false;

  bool passesGlobalTrackID   = false;
  bool passesMuonBestTrackID = false;
  bool passesInnerTrackID    = false;
  bool passesTrackID         = false;
  bool passesCuts            = false;
  bool mediumID              = false;
  bool goodGlb               = false;


  double tightRelativeIso = muonparams.getParameter<double> ("tightRelativeIso");
  double looseRelativeIso = muonparams.getParameter<double> ("looseRelativeIso");
  double tightTrackNormalizedChi2 = muonparams.getParameter<double> ("tightTrackNormalizedChi2");
  int tightTrackNumberOfValidMuonHits = muonparams.getParameter<int> ("tightTrackNumberOfValidMuonHits");
  double tightTrackDxy = muonparams.getParameter<double> ("tightTrackDxy");
  double tightTrackDz = muonparams.getParameter<double> ("tightTrackDz");
  int tightNumberOfValidPixelHits = muonparams.getParameter<int> ("tightNumberOfValidPixelHits");
  int tightTrackerLayersWithMeasurement = muonparams.getParameter<int> ("tightTrackerLayersWithMeasurement");
  
  switch(iMuonID){
  case muonID::muonSide:
  case muonID::muonSideLooseMVA:
  case muonID::muonSideTightMVA:
  case muonID::muonPtOnly:
  case muonID::muonPtEtaOnly:
  case muonID::muonPtEtaIsoOnly:
  case muonID::muonPtEtaIsoTrackerOnly:
  case muonID::muonRaw:
    return true;
    break;
  case muonID::muonLooseMvaBased:
    // passesKinematics = true;
    // passesIso = true;
    // goodGlb = (iMuon.isGlobalMuon() &&  iMuon.globalTrack()->normalizedChi2() < 3
    // 	       && iMuon.combinedQuality().chi2LocalPosition < 12 &&
    // 	       iMuon.combinedQuality().trkKink < 20);
    // mediumID = (iMuon.innerTrack()->validFraction() >= 0.8 &&
    // 		  iMuon.segmentCompatibility() >= (goodGlb ? 0.303 : 0.451));
    // passesID = (GetMuonLepMVA(iMuon,jets) > 0.5 && mediumID );
    // break;
  case muonID::muonTightMvaBased:
    passesKinematics = true;
    passesIso = true;
    goodGlb = (iMuon.isGlobalMuon() &&  iMuon.globalTrack()->normalizedChi2() < 3
  	       && iMuon.combinedQuality().chi2LocalPosition < 12 &&
  	       iMuon.combinedQuality().trkKink < 20);
    mediumID = (iMuon.innerTrack()->validFraction() >= 0.8 &&
		  iMuon.segmentCompatibility() >= (goodGlb ? 0.303 : 0.451));
    passesID = (GetMuonLepMVA(iMuon,iJets) > 0.8 && mediumID );
    break;
  case muonID::muonCutBased:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) < 2.4));
    passesIso = (GetMuonRelIso(iMuon,coneSize::R03,corrType::rhoEA) < 0.1);
    passesCuts = (fabs(iMuon.dB(pat::Muon::PV3D)/iMuon.edB(pat::Muon::PV3D)) < 4.);
    goodGlb = (iMuon.isGlobalMuon() &&  iMuon.globalTrack()->normalizedChi2() < 3
  	       && iMuon.combinedQuality().chi2LocalPosition < 12 &&
  	       iMuon.combinedQuality().trkKink < 20);
    mediumID = (iMuon.innerTrack()->validFraction() >= 0.8 &&
		  iMuon.segmentCompatibility() >= (goodGlb ? 0.303 : 0.451));
    passesID = (passesCuts && mediumID);
    break;
  case muonID::muonLooseCutBased:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) < 2.4));
    passesIso = (GetMuonRelIso(iMuon,coneSize::R03,corrType::rhoEA) < 0.5);
    if( iMuon.innerTrack().isAvailable() ){
      passesMuonBestTrackID = ( (fabs(iMuon.innerTrack()->dxy(vertex.position())) < 0.05)
				&& (fabs(iMuon.innerTrack()->dz(vertex.position())) < 0.1)
				);
    }
    passesID        = (passesMuonBestTrackID && (iMuon.isGlobalMuon() || iMuon.isTrackerMuon()) && iMuon.isPFMuon());
    break;
  case muonID::muonTightCutBased:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) < 2.4));
    passesIso = (GetMuonRelIso(iMuon,coneSize::R03,corrType::rhoEA) < 0.1);
    
    if( iMuon.innerTrack().isAvailable() && iMuon.globalTrack().isAvailable() ){
      passesMuonBestTrackID = ( (fabs(iMuon.innerTrack()->dxy(vertex.position())) < 0.05)
				&& (fabs(iMuon.innerTrack()->dz(vertex.position())) < 0.1)
				);
      passesCuts = (iMuon.isGlobalMuon() && iMuon.isPFMuon() && 
		       iMuon.globalTrack()->normalizedChi2() < 10. &&
		       iMuon.globalTrack()->hitPattern().numberOfValidMuonHits() > 0 &&
		       iMuon.numberOfMatchedStations() > 1 &&
		       iMuon.innerTrack()->hitPattern().numberOfValidPixelHits() > 0 &&
		       iMuon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 && 
		       fabs(iMuon.dB(pat::Muon::PV3D)/iMuon.edB(pat::Muon::PV3D)) < 4.
		       );
    }
    passesID = (passesMuonBestTrackID && passesCuts);
    break;
  case muonID::muonLoose:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) <= maxLooseMuonAbsEta));
    passesIso        = (GetMuonRelIso(iMuon,coneSize::R03,corrType::deltaBeta) < looseRelativeIso);
    passesID         = (( iMuon.isGlobalMuon() || iMuon.isTrackerMuon() ) && iMuon.isPFMuon());
    break;
  case muonID::muonTight:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) <= maxTightMuonAbsEta));
    passesIso        = (GetMuonRelIso(iMuon,coneSize::R03,corrType::deltaBeta) < tightRelativeIso);

    if( iMuon.globalTrack().isAvailable() ){
      passesGlobalTrackID = ( (iMuon.globalTrack()->normalizedChi2() < tightTrackNormalizedChi2) 
			      && (iMuon.globalTrack()->hitPattern().numberOfValidMuonHits() > tightTrackNumberOfValidMuonHits)
			      );
    }
    if( iMuon.muonBestTrack().isAvailable() ){
      passesMuonBestTrackID = ( (fabs(iMuon.muonBestTrack()->dxy(vertex.position())) < tightTrackDxy)
				&& (fabs(iMuon.muonBestTrack()->dz(vertex.position())) < tightTrackDz)
				);
    }
    if( iMuon.innerTrack().isAvailable() )
      passesInnerTrackID = (iMuon.innerTrack()->hitPattern().numberOfValidPixelHits() > tightNumberOfValidPixelHits);
    if( iMuon.track().isAvailable() )
      passesTrackID = (iMuon.track()->hitPattern().trackerLayersWithMeasurement() > tightTrackerLayersWithMeasurement);

    passesTrackerID = ( passesGlobalTrackID && passesMuonBestTrackID && passesInnerTrackID && passesTrackID && (iMuon.numberOfMatchedStations() > 1) );

    passesID        = ((iMuon.isGlobalMuon() || iMuon.isTrackerMuon()) && iMuon.isPFMuon() && passesTrackerID);
    break;
  case muonID::muonPreselection:
    passesKinematics = ((iMuon.pt() > minMuonPt) && (fabs(iMuon.eta()) < 2.4));
    passesIso = (GetMuonRelIso(iMuon,coneSize::R03,corrType::rhoEA) < 0.5);
    if( iMuon.innerTrack().isAvailable() ){
      passesMuonBestTrackID = ( (fabs(iMuon.innerTrack()->dxy(vertex.position())) < 0.05)
                                && (fabs(iMuon.innerTrack()->dz(vertex.position())) < 0.1)
                                );}
    passesID         = (( iMuon.isGlobalMuon() || iMuon.isTrackerMuon() ) && iMuon.isPFMuon() && passesMuonBestTrackID );
    break;
  }
  
  return (passesKinematics && passesIso && passesID);
}

vint MultileptonAna::Get_JetPartonFlavor(vecPatJet theobjs)
{	
	vint theflavors;
	
	int jetsize = theobjs.size();
	
	for (int i=0; i<jetsize; i++)
	{
		pat::Jet thejet = theobjs[i];
		int theflavor = thejet.partonFlavour();
		theflavors.push_back(theflavor);
	}
	
	return theflavors;
	
}


bool MultileptonAna::isGoodElectron(const pat::Electron& iElectron, const float iMinPt, const electronID::electronID iElectronID, const std::vector<pat::Jet>& iJets){

  CheckVertexSetUp();
  
  double minElectronPt = iMinPt;

  // float maxLooseElectronAbsEta = electronparams.getParameter<double> ("maxLooseElectronAbsEta");
  // float maxTightElectronAbsEta = electronparams.getParameter<double> ("maxTightElectronAbsEta");

  // string theElectronMVA = electronparams.getParameter<string> ("theElectronMVA");
  // double passMVAcut = electronparams.getParameter<double> ("passMVAcut");

  // double tightElectronIso = electronparams.getParameter<double> ("tightElectronIso");
  // double looseElectronIso = electronparams.getParameter<double> ("looseElectronIso");  
  // double tightDxy = electronparams.getParameter<double> ("tightDxy");
  // double looseDxy = electronparams.getParameter<double> ("looseDxy");
  // double dz = electronparams.getParameter<double> ("dZ");
  
  // Be skeptical about this electron making it through
  bool passesKinematics	= false;
  bool passesIso        = false;
  bool passesID         = false;

  // bool inCrack = false;
  // if( iElectron.superCluster().isAvailable() )
  //   inCrack = ( fabs(iElectron.superCluster()->position().eta())>1.4442 && fabs(iElectron.superCluster()->position().eta())<1.5660 ); // doesn't change

  //  bool myTrigPresel = true;

  // double eleID      = iElectron.electronID(theElectronMVA);
  // bool passMVAId53x = ( eleID > passMVAcut );  // For 2012_53x, tighter selection

  // bool d02 = false; 
  // bool d04 = false;
  // bool dZ  = false;
  bool passGsfTrackID = false;
  bool passesCuts = false; 

  // if( iElectron.gsfTrack().isAvailable() ){
  //   d02 = ( fabs(iElectron.gsfTrack()->dxy(vertex.position())) < tightDxy );
  //   d04 = ( fabs(iElectron.gsfTrack()->dxy(vertex.position())) < looseDxy );
  //   dZ = ( fabs(iElectron.gsfTrack()->dz(vertex.position())) < dz );
  // }
  bool passesMVA = false;
  bool mvaDebug = false;
  double eleMvaNonTrig = mvaID_->mvaValue(iElectron,mvaDebug);
  float scEta = abs(iElectron.superCluster()->position().eta());

  switch(iElectronID){
  case electronID::electronSide:
  case electronID::electronSideLooseMVA:
  case electronID::electronPhys14L:
  case electronID::electronPhys14M:
  case electronID::electronPhys14T:
  case electronID::electronSideTightMVA:
  case electronID::electronLooseMinusTrigPresel:
  case electronID::electronRaw:
    return true;
    break;
  case electronID::electronLooseMvaBased:
    passesKinematics = true;
    passesIso = true;
    passesID = (GetElectronLepMVA(iElectron,iJets) > 0.5 &&
		iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS)==0 &&
		iElectron.passConversionVeto());
    break;
  case electronID::electronTightMvaBased:
    passesKinematics = true;
    passesIso = true;
    passesID = (GetElectronLepMVA(iElectron,iJets) > 0.8 &&
		iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS)==0 &&
		iElectron.passConversionVeto());
    break;
  case electronID::electronCutBased:
    //Phys14 MVA ID (only for pT > 10 GeV) for now
    passesKinematics = ((iElectron.pt() >= minElectronPt) && (fabs(iElectron.eta()) < 2.5));
    if (iElectron.pt() > 10) {    //tight WP
      if ( scEta < 0.8) passesMVA = ( eleMvaNonTrig > 0.73 );
      else if ( scEta < 1.479) passesMVA = ( eleMvaNonTrig > 0.57 );
      else passesMVA = ( eleMvaNonTrig > 0.05 );
    }
    passesIso = (GetElectronRelIso(iElectron,coneSize::R03,corrType::rhoEA) < 0.1);
    passesID = (passesMVA && iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS)==0 && iElectron.passConversionVeto());
    break;
  case electronID::electronLooseCutBased:
    passesKinematics = ((iElectron.pt() >= minElectronPt) && (fabs(iElectron.eta()) < 2.5));
    passGsfTrackID = ( (fabs(iElectron.gsfTrack()->dxy(vertex.position())) < 0.05) && (fabs(iElectron.gsfTrack()->dz(vertex.position())) < 0.1) && iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS) <= 1 );
    passesIso        =  (GetElectronRelIso(iElectron,coneSize::R03,corrType::rhoEA) < 0.5);
    if (scEta <= 1.479)
      {
	passesCuts = ( fabs(iElectron.deltaEtaSuperClusterTrackAtVtx()) < 0.007 &&
			  fabs(iElectron.deltaPhiSuperClusterTrackAtVtx()) < 0.8 &&
			  iElectron.full5x5_sigmaIetaIeta() < 0.01 &&
			  iElectron.hadronicOverEm() < 0.15
			  );
      }
    else if (scEta > 1.479 && scEta < 2.5)
      {
	passesCuts = ( fabs(iElectron.deltaEtaSuperClusterTrackAtVtx()) < 0.01 &&
			  fabs(iElectron.deltaPhiSuperClusterTrackAtVtx()) < 0.7 &&
			  iElectron.full5x5_sigmaIetaIeta() < 0.03
			  );
      }
    passesID = (passesCuts && passGsfTrackID);
    break;
  case electronID::electronTightCutBased:
    passesKinematics = ((iElectron.pt() >= minElectronPt) && (fabs(iElectron.eta()) < 2.5));
    passGsfTrackID = ( (fabs(iElectron.gsfTrack()->dxy(vertex.position())) < 0.05) &&
		       (fabs(iElectron.gsfTrack()->dz(vertex.position())) < 0.1) &&
		       iElectron.isGsfCtfScPixChargeConsistent() &&
		       iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS) == 0 && 
		       fabs(iElectron.dB(pat::Electron::PV3D)/iElectron.edB(pat::Electron::PV3D)) < 4 );
    
    passesIso        =  (GetElectronRelIso(iElectron,coneSize::R03,corrType::rhoEA) < 0.1);
    
    if (scEta <= 1.479) 
      {
	passesCuts = ( fabs(iElectron.deltaEtaSuperClusterTrackAtVtx()) < 0.004 &&
			  fabs(iElectron.deltaPhiSuperClusterTrackAtVtx()) < 0.06 &&
			  iElectron.full5x5_sigmaIetaIeta() < 0.01 &&
			  iElectron.hadronicOverEm() < 0.12);
      }
    else if (scEta > 1.479 && scEta < 2.5)
      {
	passesCuts = ( fabs(iElectron.deltaEtaSuperClusterTrackAtVtx()) < 0.007 &&
			  fabs(iElectron.deltaPhiSuperClusterTrackAtVtx()) < 0.03 &&
			  iElectron.full5x5_sigmaIetaIeta() < 0.03 && 
			  iElectron.hadronicOverEm() < 0.10);
      }
    passesID = (passesCuts && passGsfTrackID);
    break;
  case electronID::electronLoose:
  case electronID::electronTightMinusTrigPresel:
  case electronID::electronTight:
  case electronID::electronPreselection:
    //Phys14 MVA ID (only for pT > 10 GeV) for now
    if (iElectron.pt() > 10) {    //loose WP
      if ( scEta < 0.8) passesMVA = ( eleMvaNonTrig > 0.35 );
      else if ( scEta < 1.479) passesMVA = ( eleMvaNonTrig > 0.2 );
      else passesMVA = ( eleMvaNonTrig > -0.52 );
    }
    if( iElectron.gsfTrack().isAvailable() ){
      passGsfTrackID = ( (fabs(iElectron.gsfTrack()->dxy(vertex.position())) < 0.05) && (fabs(iElectron.gsfTrack()->dz(vertex.position())) < 0.1) && iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS) <= 1 );
    }
    passesKinematics = ((iElectron.pt() > 10) && (fabs(iElectron.eta()) < 2.5));
    passesIso        =  (GetElectronRelIso(iElectron,coneSize::R03,corrType::rhoEA) < 0.5);
    passesID         = ( passGsfTrackID && passesMVA);    
    break;
  }
  
  return (passesKinematics && passesIso && passesID);
}

bool MultileptonAna::isGoodTau(const pat::Tau& iTau, const float iMinPt, const tauID::tauID iTauID){

  CheckVertexSetUp();
 
  double minTauPt = iMinPt;
  
  //double tauMinPt
  //double tauMaxAbsEta = 
  
  bool passesKinematics = false;
  passesKinematics = (iTau.pt() >= 20) && (fabs(iTau.eta()) <= 2.1) && (iTau.pt() > minTauPt); //minTauPt vs. 20?
  return passesKinematics;
}

bool MultileptonAna::isGoodJet(const pat::Jet& iJet, const float iMinPt, const float iMaxAbsEta, const jetID::jetID iJetID, const char iCSVworkingPoint){

  CheckVertexSetUp();

  
//   neutralHadronEnergyFraction
//   chargedEmEnergyFraction
//   neutralEmEnergyFraction
//   numberOfDaughters
//   chargedHadronEnergyFraction
//   chargedMultiplicity

  // Transverse momentum requirement
  if( iJet.pt() < iMinPt ) return false;

  // Absolute eta requirement
  if( fabs(iJet.eta()) > iMaxAbsEta ) return false;

  bool loose = (

		iJet.neutralHadronEnergyFraction() < 0.99 &&
		iJet.chargedEmEnergyFraction() < 0.99 &&
		iJet.neutralEmEnergyFraction() < 0.99 &&
		iJet.numberOfDaughters() > 1

		);

  if( fabs(iJet.eta())<2.4 ){ // endcaps
    loose = ( loose &&
	      iJet.chargedHadronEnergyFraction() > 0.0 &&
	      iJet.chargedMultiplicity() > 0
	      );
  }

  bool passesPUJetID = true;
  float puMvaId = iJet.userFloat("pileupJetId:fullDiscriminant");
  // Jet ID
  switch(iJetID){
  case jetID::none:
    break;
  case jetID::jetPU:
    if (fabs(iJet.eta()) > 0. && fabs(iJet.eta()) <2.5)
      {
        passesPUJetID = (puMvaId > -0.63);
      }
    else if (fabs(iJet.eta()) >= 2.5 && fabs(iJet.eta()) < 2.75)
      {
        passesPUJetID = (puMvaId > -0.60);
      }
    else if (fabs(iJet.eta()) >= 2.75 && fabs(iJet.eta()) < 3.0)
      {
	passesPUJetID = (puMvaId > -0.55);
      }
    else if (fabs(iJet.eta()) >= 3.0 && fabs(iJet.eta()) <= 5.2)
      {
        passesPUJetID = (puMvaId > -0.45);
      }
    //    return passesPUJetID;
    break;
  case jetID::jetMinimal:
  case jetID::jetLooseAOD:
  case jetID::jetLoose:
  case jetID::jetTight:
    if( !loose ) return false;
    break;
  default:
    break;
  }
  
  //  if( !PassesCSV(iJet, iCSVworkingPoint) ) return false;
  //  return true;
  
  return (PassesCSV(iJet, iCSVworkingPoint) && passesPUJetID);
}

std::vector<pat::Muon>
MultileptonAna::GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const float iMinPt, const muonID::muonID iMuonID, const std::vector<pat::Jet>& iJets){
  CheckSetUp();
  
  std::vector<pat::Muon> selectedMuons;
  
  for( std::vector<pat::Muon>::const_iterator it = inputMuons.begin(), ed = inputMuons.end(); it != ed; ++it ){
    if( isGoodMuon(*it,iMinPt,iMuonID,iJets) ){
      selectedMuons.push_back(*it);
    }
    else if (iMuonID == muonID::muonLooseMvaBased || iMuonID == muonID::muonTightMvaBased) break;
  }
  
  return selectedMuons;
}

std::vector<pat::Electron>
MultileptonAna::GetSelectedElectrons(const std::vector<pat::Electron>& inputElectrons, const float iMinPt, const electronID::electronID iElectronID, const std::vector<pat::Jet>& iJets){

  CheckSetUp();

  std::vector<pat::Electron> selectedElectrons;

  for( std::vector<pat::Electron>::const_iterator it = inputElectrons.begin(), ed = inputElectrons.end(); it != ed; ++it ){
    if( isGoodElectron(*it,iMinPt,iElectronID,iJets) ){
      selectedElectrons.push_back(*it);
    }
    else if (iElectronID == electronID::electronLooseMvaBased || iElectronID == electronID::electronTightMvaBased) break;
  }

  return selectedElectrons;
}

float MultileptonAna::GetMuonLepMVA(const pat::Muon& iMuon, const std::vector<pat::Jet>& iJets){
  CheckSetUp();
  
  varchRelIso = iMuon.chargedHadronIso()/iMuon.pt();
  varneuRelIso = max(0.0,(iMuon.neutralHadronIso()+iMuon.photonIso())-0.5*iMuon.puChargedHadronIso())/iMuon.pt();
  
  pat::Jet matchedJet = getClosestJet(iJets,iMuon);
  double dR = MiniAODHelper::DeltaR(&matchedJet,&iMuon);
  varjetDR_in = min(dR,0.5);
  varjetPtRatio_in = min(iMuon.pt()/matchedJet.pt(), float(1.5));
  
  varjetBTagCSV_in = max(matchedJet.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"), float(0.0));
  varsip3d = fabs(iMuon.dB(pat::Muon::PV3D)/iMuon.edB(pat::Muon::PV3D));
  //  vardxy = log(fabs(iMuon.muonBestTrack()->dxy(vertex.position())));
  //  vardz = log(fabs(iMuon.muonBestTrack()->dz(vertex.position())));
  vardxy = log(fabs(iMuon.innerTrack()->dxy(vertex.position())));
  vardz = log(fabs(iMuon.innerTrack()->dz(vertex.position())));
  varSegCompat = iMuon.segmentCompatibility();
  
  if (iMuon.pt() <= 10){
    return mu_reader_low->EvaluateMVA( "BDTG method" );
  }
  else if (iMuon.pt() > 10 && iMuon.pt() <= 25 && fabs(iMuon.eta()) < 1.5) {
    return mu_reader_medium_b->EvaluateMVA( "BDTG method" );
  }
  else if (iMuon.pt() > 10 && iMuon.pt() <= 25 && fabs(iMuon.eta()) >= 1.5) {
    return mu_reader_medium_e->EvaluateMVA( "BDTG method" );
  }
  else if (iMuon.pt() > 25 && fabs(iMuon.eta()) < 1.5) {
    return mu_reader_high_b->EvaluateMVA( "BDTG method" );
  }
  else if (iMuon.pt() > 25 && fabs(iMuon.eta()) >= 1.5) {
    return mu_reader_high_e->EvaluateMVA( "BDTG method" );
  }
  else return -99999.;
  

 
}


float MultileptonAna::GetElectronLepMVA(const pat::Electron& iElectron, const std::vector<pat::Jet>& iJets){
  CheckSetUp();
  
  varchRelIso = iElectron.chargedHadronIso()/iElectron.pt();
  //varchRelIso = iElectron.pfIsolationVariables().sumChargedHadronPt;
  //varneuRelIso = GetElectronRelIso(iElectron) - varchRelIso;
  varneuRelIso = max(0.0,(iElectron.neutralHadronIso()+iElectron.photonIso())-0.5*iElectron.puChargedHadronIso())/iElectron.pt();
  
  pat::Jet matchedJet = getClosestJet(iJets,iElectron);
  double dR = MiniAODHelper::DeltaR(&matchedJet,&iElectron);
  varjetDR_in = min(dR,0.5);
  varjetPtRatio_in = min(iElectron.pt()/matchedJet.pt(), float(1.5));
  
  varjetBTagCSV_in = max(matchedJet.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"), float(0.0));
  varsip3d = fabs(iElectron.dB(pat::Electron::PV3D)/iElectron.edB(pat::Electron::PV3D));
  vardxy = log(fabs(iElectron.gsfTrack()->dxy(vertex.position())));
  vardz = log(fabs(iElectron.gsfTrack()->dz(vertex.position())));
  bool mvaDebug = false;
  varmvaId = mvaID_->mvaValue(iElectron,mvaDebug);  

  if (iElectron.pt() <= 10){
    return ele_reader_low->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() > 10 && iElectron.pt() <= 25 && fabs(iElectron.eta()) < 0.8){
    return ele_reader_medium_cb->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() > 10 && iElectron.pt() <= 25 && fabs(iElectron.eta()) >= 0.8 && fabs(iElectron.eta()) < 1.479){
    return ele_reader_medium_fb->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() > 10 && iElectron.pt() <= 25 && fabs(iElectron.eta()) >= 1.479) {
    return ele_reader_medium_ec->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() > 25 && fabs(iElectron.eta()) < 0.8) {
    return ele_reader_high_cb->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() > 25 && fabs(iElectron.eta()) >= 0.8 && fabs(iElectron.eta()) < 1.479) {
    return ele_reader_high_fb->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() > 25 && fabs(iElectron.eta()) >= 1.479) {
    return ele_reader_high_ec->EvaluateMVA( "BDTG method" );
  }
  else return -99999.;
}

vecPatElectron MultileptonAna::Get_vecPatElectron_Passing_ElectronLepMVA(const vecPatElectron& electrons, const std::vector<pat::Jet>& iJets, double MVA_Cut)
{
	vecPatElectron passobjs;
	for (vecPatElectron::const_iterator iEle = electrons.begin(); iEle != electrons.end(); ++iEle)
  	{
		double value = GetElectronLepMVA(*iEle,iJets);
		if (value>MVA_Cut) passobjs.push_back(*iEle);
    	}
  	return passobjs;
}

vecPatMuon MultileptonAna::Get_vecPatMuon_Passing_MuonLepMVA(const vecPatMuon& muons, const std::vector<pat::Jet>& iJets, double MVA_Cut)
{
	vecPatMuon passobjs;
	for (vecPatMuon::const_iterator iMu = muons.begin(); iMu != muons.end(); ++iMu)
  	{
		double value = GetMuonLepMVA(*iMu,iJets);
		if (value>MVA_Cut) passobjs.push_back(*iMu);
    	}
  	return passobjs;
}


const reco::Candidate* MultileptonAna::GetGenMotherNoFsr(const reco::Candidate* theobj)
{
  if (theobj->numberOfMothers()>0)
    {
      const reco::Candidate* mother = theobj->mother(0);
      if (mother->pdgId() != theobj->pdgId()) return mother;
      else return GetGenMotherNoFsr(mother);
    }
  else 
    {
      return theobj;
    }
}

std::pair<const reco::Candidate*, const reco::Candidate*> MultileptonAna::GetGenDaughterNoFsr(const reco::Candidate* theobj)
{
  const reco::Candidate* returnDau0 = theobj;
  const reco::Candidate* returnDau1 = theobj;

  if (theobj->numberOfDaughters()>0)
    {
      const reco::Candidate* daughter = theobj->daughter(0);
      if (daughter->pdgId() != theobj->pdgId()) returnDau0 = daughter;
      else returnDau0 = GetGenDaughterNoFsr(daughter).first;
    
      if (theobj->numberOfDaughters()>1)
	{
	  daughter = theobj->daughter(1);
	  if (daughter->pdgId() != theobj->pdgId()) returnDau1 = daughter;
	  else returnDau1 = GetGenDaughterNoFsr(daughter).second;
	}
    }
  std::pair<const reco::Candidate*, const reco::Candidate*> returnPair(returnDau0,returnDau1);
  return returnPair;
}


///stuff for TriggerAna.cc
vecTLorentzVectorCMS MultileptonAna::Get_vecTLorentzVectorCMS (vecPatMuon theobjs)
{
  vecTLorentzVectorCMS theobjs_vecTLV;
  for (muit iMuon= theobjs.begin(); iMuon != theobjs.end(); ++iMuon)
    {
      TLorentzVectorCMS tempTLV;
      tempTLV.SetPxPyPzE(iMuon->px(),iMuon->py(),iMuon->pz(),iMuon->energy());
      theobjs_vecTLV.push_back(tempTLV);
    }
  return theobjs_vecTLV;
}
vecTLorentzVectorCMS MultileptonAna::Get_vecTLorentzVectorCMS (vecPatElectron theobjs)
{
  vecTLorentzVectorCMS theobjs_vecTLV;
  for (eleit iEle= theobjs.begin(); iEle != theobjs.end(); ++iEle)
    {
      TLorentzVectorCMS tempTLV;
      tempTLV.SetPxPyPzE(iEle->px(),iEle->py(),iEle->pz(),iEle->energy());
      theobjs_vecTLV.push_back(tempTLV);
    }
  return theobjs_vecTLV;
}
vecTLorentzVectorCMS MultileptonAna::Get_vecTLorentzVectorCMS (vecPatJet theobjs)
{
  vecTLorentzVectorCMS theobjs_vecTLV;
  for (jetit iJet = theobjs.begin(); iJet != theobjs.end(); ++iJet)
    {
      TLorentzVectorCMS tempTLV;
      tempTLV.SetPxPyPzE(iJet->px(),iJet->py(),iJet->pz(),iJet->energy());
      theobjs_vecTLV.push_back(tempTLV);
    }
  return theobjs_vecTLV;
}

TLorentzVectorCMS MultileptonAna::Get_TLorentzVectorCMS (patMETs theobjs)
{
  pat::MET theMET = theobjs->front();
  TLorentzVectorCMS metTLV(theMET.px(),theMET.py(),0.0,theMET.pt());
  return metTLV;
}
TLorentzVectorCMS MultileptonAna::Get_TLorentzVectorCMS (pat::MET theMET)
{
  //pat::MET theMET = theobj;
  TLorentzVectorCMS metTLV(theMET.px(),theMET.py(),0.0,theMET.pt());
  return metTLV;
}
vecTLorentzVectorCMS MultileptonAna::Get_vecTLorentzVectorCMS_sorted_leptons (vecTLorentzVectorCMS leps1, vecTLorentzVectorCMS leps2)
{
  vecTLorentzVectorCMS newvecTLV;
  newvecTLV.clear();
  // assuming they are already sorted by pt, respectively:
  int size1 = leps1.size();
  int size2 = leps2.size();
  if (size1==0 && size2!=0) return leps2;
  if (size2==0 && size1!=0) return leps1;
  if (size1==0 && size2==0) return newvecTLV;
  //int maxsize = max(size1,size2);
  //int minsize = min(size1,size2);
  int i = 0;
  int j = 0;
  while (true)
    {
      if ((i==size1)||(j==size2)) break;
      else
	{
	  if (leps1[i].Pt() < leps2[j].Pt())
	    {
	      newvecTLV.push_back(leps2[j]);
	      j++;
	    }
	  else
	    {
	      newvecTLV.push_back(leps1[i]);
	      i++;
	    }
	}
    }
  while (true)
    {
      if (j==size2) break;
      newvecTLV.push_back(leps2[j]);
      j++;
    }
  while (true)
    {
      if (i==size1) break;
      newvecTLV.push_back(leps1[i]);
      i++;
    }
  return newvecTLV;
}

//// #endif // !defined( MULTILEPTONANA_CC ) 
