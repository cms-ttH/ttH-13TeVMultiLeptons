// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MultileptonAna.h"

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
  else {
    assert (analysisYear == "either 2012_52x, 2012_53x, or 2011");
  }

  if (tmpName.Contains("wz") || tmpName.Contains("zz")) {
    if (tmpName.Contains("_lf")) sampleNumber = sampleNumber*10 + 1;
    if (tmpName.Contains("_cc")) sampleNumber = sampleNumber*10 + 2;
    if (tmpName.Contains("_bb")) sampleNumber = sampleNumber*10 + 4;
    else if (tmpName.Contains("_b")) sampleNumber = sampleNumber*10 + 3;
  }

  std::cout << "CONFIG: Sample Name = " << sampleName
            << ", sample Number = " << sampleNumber << endl;
  
  std::cout << weight_Xsec << nGen << Xsec << endl;
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
  EGammaMvaEleEstimatorFWLite::MVAType type_ = EGammaMvaEleEstimatorFWLite::kNonTrig;
  std::vector<std::string> mvaWeightFiles_;
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat1.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat2.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat3.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat4.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat5.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat6.weights.xml");
  mvaID_->initialize(method_, type_, useBinnedVersion_, mvaWeightFiles_);

  mu_reader_high_b = new TMVA::Reader( "!Color:!Silent" );
  mu_reader_high_e = new TMVA::Reader( "!Color:!Silent" );
  mu_reader_low_b = new TMVA::Reader( "!Color:!Silent" );
  mu_reader_low_e = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_high_cb = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_high_fb = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_high_ec = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_low_cb = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_low_fb = new TMVA::Reader( "!Color:!Silent" );
  ele_reader_low_ec = new TMVA::Reader( "!Color:!Silent" );

  ele_reader_high_cb->AddVariable( "neuRelIso", &varneuRelIso );
  ele_reader_high_cb->AddVariable( "chRelIso", &varchRelIso );
  ele_reader_high_cb->AddVariable( "jetDR_in", &varjetDR_in );
  ele_reader_high_cb->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  ele_reader_high_cb->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  ele_reader_high_cb->AddVariable( "sip3d", &varsip3d );
  ele_reader_high_cb->AddVariable( "mvaId", &varmvaId );
  ele_reader_high_cb->AddVariable( "innerHits", &varinnerHits );

  ele_reader_high_fb->AddVariable( "neuRelIso", &varneuRelIso );
  ele_reader_high_fb->AddVariable( "chRelIso", &varchRelIso );
  ele_reader_high_fb->AddVariable( "jetDR_in", &varjetDR_in );
  ele_reader_high_fb->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  ele_reader_high_fb->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  ele_reader_high_fb->AddVariable( "sip3d", &varsip3d );
  ele_reader_high_fb->AddVariable( "mvaId", &varmvaId );
  ele_reader_high_fb->AddVariable( "innerHits", &varinnerHits );

  ele_reader_high_ec->AddVariable( "neuRelIso", &varneuRelIso );
  ele_reader_high_ec->AddVariable( "chRelIso", &varchRelIso );
  ele_reader_high_ec->AddVariable( "jetDR_in", &varjetDR_in );
  ele_reader_high_ec->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  ele_reader_high_ec->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  ele_reader_high_ec->AddVariable( "sip3d", &varsip3d );
  ele_reader_high_ec->AddVariable( "mvaId", &varmvaId );
  ele_reader_high_ec->AddVariable( "innerHits", &varinnerHits );

  ele_reader_low_cb->AddVariable( "neuRelIso", &varneuRelIso );
  ele_reader_low_cb->AddVariable( "chRelIso", &varchRelIso );
  ele_reader_low_cb->AddVariable( "jetDR_in", &varjetDR_in );
  ele_reader_low_cb->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  ele_reader_low_cb->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  ele_reader_low_cb->AddVariable( "sip3d", &varsip3d );
  ele_reader_low_cb->AddVariable( "mvaId", &varmvaId );
  ele_reader_low_cb->AddVariable( "innerHits", &varinnerHits );

  ele_reader_low_fb->AddVariable( "neuRelIso", &varneuRelIso );
  ele_reader_low_fb->AddVariable( "chRelIso", &varchRelIso );
  ele_reader_low_fb->AddVariable( "jetDR_in", &varjetDR_in );
  ele_reader_low_fb->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  ele_reader_low_fb->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  ele_reader_low_fb->AddVariable( "sip3d", &varsip3d );
  ele_reader_low_fb->AddVariable( "mvaId", &varmvaId );
  ele_reader_low_fb->AddVariable( "innerHits", &varinnerHits );

  ele_reader_low_ec->AddVariable( "neuRelIso", &varneuRelIso );
  ele_reader_low_ec->AddVariable( "chRelIso", &varchRelIso );
  ele_reader_low_ec->AddVariable( "jetDR_in", &varjetDR_in );
  ele_reader_low_ec->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  ele_reader_low_ec->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  ele_reader_low_ec->AddVariable( "sip3d", &varsip3d );
  ele_reader_low_ec->AddVariable( "mvaId", &varmvaId );
  ele_reader_low_ec->AddVariable( "innerHits", &varinnerHits );

  mu_reader_high_b->AddVariable( "neuRelIso", &varneuRelIso );
  mu_reader_high_b->AddVariable( "chRelIso", &varchRelIso );
  mu_reader_high_b->AddVariable( "jetDR_in", &varjetDR_in );
  mu_reader_high_b->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  mu_reader_high_b->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  mu_reader_high_b->AddVariable( "sip3d", &varsip3d );
  mu_reader_high_b->AddVariable( "dxy", &vardxy );
  mu_reader_high_b->AddVariable( "dz", &vardz );

  mu_reader_high_e->AddVariable( "neuRelIso", &varneuRelIso );
  mu_reader_high_e->AddVariable( "chRelIso", &varchRelIso );
  mu_reader_high_e->AddVariable( "jetDR_in", &varjetDR_in );
  mu_reader_high_e->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  mu_reader_high_e->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  mu_reader_high_e->AddVariable( "sip3d", &varsip3d );
  mu_reader_high_e->AddVariable( "dxy", &vardxy );
  mu_reader_high_e->AddVariable( "dz", &vardz );

  mu_reader_low_b->AddVariable( "neuRelIso", &varneuRelIso );
  mu_reader_low_b->AddVariable( "chRelIso", &varchRelIso );
  mu_reader_low_b->AddVariable( "jetDR_in", &varjetDR_in );
  mu_reader_low_b->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  mu_reader_low_b->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  mu_reader_low_b->AddVariable( "sip3d", &varsip3d );
  mu_reader_low_b->AddVariable( "dxy", &vardxy );
  mu_reader_low_b->AddVariable( "dz", &vardz );

  mu_reader_low_e->AddVariable( "neuRelIso", &varneuRelIso );
  mu_reader_low_e->AddVariable( "chRelIso", &varchRelIso );
  mu_reader_low_e->AddVariable( "jetDR_in", &varjetDR_in );
  mu_reader_low_e->AddVariable( "jetPtRatio_in", &varjetPtRatio_in );
  mu_reader_low_e->AddVariable( "jetBTagCSV_in", &varjetBTagCSV_in );
  mu_reader_low_e->AddVariable( "sip3d", &varsip3d );
  mu_reader_low_e->AddVariable( "dxy", &vardxy );
  mu_reader_low_e->AddVariable( "dz", &vardz );

  mu_reader_high_b->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_high_b_BDTG.weights.xml");
  mu_reader_high_e->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_high_e_BDTG.weights.xml");
  mu_reader_low_b->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_low_b_BDTG.weights.xml");
  mu_reader_low_e->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/mu_pteta_low_e_BDTG.weights.xml");

  ele_reader_high_cb->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_high_cb_BDTG.weights.xml");
  ele_reader_high_fb->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_high_fb_BDTG.weights.xml");
  ele_reader_high_ec->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_high_ec_BDTG.weights.xml");
  ele_reader_low_cb->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_low_cb_BDTG.weights.xml");
  ele_reader_low_fb->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_low_fb_BDTG.weights.xml");
  ele_reader_low_ec->BookMVA( "BDTG method", string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/el_pteta_low_ec_BDTG.weights.xml");


  // mu_reader_high_b->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/mu_pteta_high_b_BDTG.weights.xml");
  // mu_reader_high_e->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/mu_pteta_high_e_BDTG.weights.xml");
  // mu_reader_low_b->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/mu_pteta_low_b_BDTG.weights.xml");
  // mu_reader_low_e->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/mu_pteta_low_e_BDTG.weights.xml");

  // ele_reader_high_cb->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/el_pteta_high_cb_BDTG.weights.xml");
  // ele_reader_high_fb->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/el_pteta_high_fb_BDTG.weights.xml");
  // ele_reader_high_ec->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/el_pteta_high_ec_BDTG.weights.xml");
  // ele_reader_low_cb->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/el_pteta_low_cb_BDTG.weights.xml");
  // ele_reader_low_fb->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/el_pteta_low_fb_BDTG.weights.xml");
  // ele_reader_low_ec->BookMVA( "BDTG method", "/afs/cern.ch/user/m/muell149/CMSSW_5_3_18/src/BEAN/BEANmaker/data/lepMVA/el_pteta_low_ec_BDTG.weights.xml");



  
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
vecPatLepton MultileptonAna::fillLeptons(vecPatMuon& muons, vecPatElectron& electrons)
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
 
vector<ttH::Lepton> MultileptonAna::GetCollection (vecPatLepton theobjs)
{
  vector<ttH::Lepton> lepCollection;
  for (vecPatLepton::const_iterator iLep = theobjs.begin(); iLep != theobjs.end(); iLep++)
    //  for (eleit iEle= theobjs.begin(); iEle != theobjs.end(); ++iEle)
    {
      ttH::Lepton lep;
      lep.pt = iLep->pt();
      lep.px = iLep->px();
      lep.py = iLep->py();
      lep.pz = iLep->pz();
      lep.energy = iLep->energy();
      lep.eta = iLep->eta();
      lep.phi = iLep->phi();
      lep.id = iLep->pdgId();
      lepCollection.push_back(lep);
    }
  return lepCollection;
}

vector<ttH::Electron> MultileptonAna::GetCollection (vecPatElectron theobjs, vecPatJet jets)
{
  vector<ttH::Electron> eleCollection;
  for (vecPatElectron::const_iterator iEle = theobjs.begin(); iEle != theobjs.end(); iEle++)
    {
      ttH::Electron ele;
      pat::Electron iElectron;
      iElectron = (*iEle);
      
      //calculate closest jet
      pat::Jet matchedJet = getClosestJet(jets,iElectron);
      double dR = MiniAODHelper::DeltaR(&matchedJet,&iElectron);

      ele.pt = iElectron.pt();
      ele.px = iElectron.px();
      ele.py = iElectron.py();
      ele.pz = iElectron.pz();
      ele.energy = iElectron.energy();
      ele.eta = iElectron.eta();
      ele.SCeta = abs(iElectron.superCluster()->position().eta());
      ele.phi = iElectron.phi();
      ele.pdgID = iElectron.pdgId();
      ele.dxy = fabs(iElectron.gsfTrack()->dxy(vertex.position()));
      ele.dz = fabs(iElectron.gsfTrack()->dz(vertex.position()));
      ele.charge = iElectron.charge();
      ele.isGsfCtfScPixChargeConsistent = iElectron.isGsfCtfScPixChargeConsistent();
      ele.numMissingInnerHits = iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
      ele.passConversioVeto = iElectron.passConversionVeto();
      ele.lepMVA = GetElectronLepMVA(iElectron, jets);
      ele.chreliso = iElectron.chargedHadronIso()/iElectron.pt();
      ele.nureliso = max(0.0,(iElectron.neutralHadronIso()+iElectron.photonIso())-0.5*iElectron.puChargedHadronIso())/iElectron.pt();
      ele.matchedJetdR = min(dR,0.5);
      ele.jetPtRatio = min(iElectron.pt()/matchedJet.pt(), float(1.5));
      ele.btagCSV = max(matchedJet.bDiscriminator("combinedSecondaryVertexBJetTags"), float(0.0));
      ele.sip3D = fabs(iElectron.dB(pat::Electron::PV3D)/iElectron.edB(pat::Electron::PV3D));
      ele.mvaID = mvaID_->mvaValue(iElectron,vertex,rho,true,false); //use full5x5=true, debug=false

      eleCollection.push_back(ele);
    }
  return eleCollection;
}

vector<ttH::Muon> MultileptonAna::GetCollection (vecPatMuon theobjs, vecPatJet jets)
{
  vector<ttH::Muon> muCollection;
  for (vecPatMuon::const_iterator iMu = theobjs.begin(); iMu != theobjs.end(); iMu++)
    {
      ttH::Muon mu;
      pat::Muon iMuon;
      iMuon = (*iMu);
      
      //calculate closest jet
      pat::Jet matchedJet = getClosestJet(jets,iMuon);
      double dR = MiniAODHelper::DeltaR(&matchedJet,&iMuon);

      mu.pt = iMuon.pt();
      mu.px = iMuon.px();
      mu.py = iMuon.py();
      mu.pz = iMuon.pz();
      mu.energy = iMuon.energy();
      mu.eta = iMuon.eta();
      mu.phi = iMuon.phi();
      mu.pdgID = iMuon.pdgId();
      mu.charge = iMuon.charge();
      mu.dxy = fabs(iMuon.innerTrack()->dxy(vertex.position()));
      mu.dz =fabs(iMuon.innerTrack()->dz(vertex.position()));
      mu.chargeFlip = iMuon.innerTrack()->ptError()/iMuon.innerTrack()->pt();
      mu.lepMVA = GetMuonLepMVA(iMuon, jets);
      mu.chreliso = iMuon.chargedHadronIso()/iMuon.pt();
      mu.nureliso = max(0.0,(iMuon.neutralHadronIso()+iMuon.photonIso())-0.5*iMuon.puChargedHadronIso())/iMuon.pt();
      mu.matchedJetdR = min(dR,0.5);
      mu.jetPtRatio = min(iMuon.pt()/matchedJet.pt(), float(1.5));
      mu.btagCSV = max(matchedJet.bDiscriminator("combinedSecondaryVertexBJetTags"), float(0.0));
      mu.sip3D = fabs(iMuon.dB(pat::Muon::PV3D)/iMuon.edB(pat::Muon::PV3D));

      muCollection.push_back(mu);
    }
  return muCollection;
}

vector<ttH::Jet> MultileptonAna::GetCollection (vecPatJet theobjs)
{
  vector<ttH::Jet> jetCollection;
  for (vecPatJet::const_iterator iJt = theobjs.begin(); iJt != theobjs.end(); iJt++)
    {
      ttH::Jet jet;
      pat::Jet iJet;
      iJet = (*iJt);

      jet.pt = iJet.pt();
      jet.energy = iJet.energy();
      jet.mass = iJet.mass();
      jet.eta = iJet.eta();
      jet.phi = iJet.phi();
      jet.pdgID = iJet.pdgId();
      jet.charge = iJet.jetCharge();
      jet.csv = iJet.bDiscriminator("combinedSecondaryVertexBJetTags");
      jetCollection.push_back(jet);

    }
  return jetCollection;
}



vecTLorentzVectorCMS MultileptonAna::Get_vecTLorentzVectorCMS (vecPatMuon theobjs)
{
	//int nobjs = theobjcollection.size();
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
//vecTLorentzVector Get_vecTLorentzVector_SubJets ()

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
	
	// assuming they are already sorted by pt, respectively:
	
	int size1 = leps1.size();
 	int size2 = leps2.size();
 	
 	if (size1==0||size2!=0) return leps2;
	if (size2==0||size1!=0) return leps1;
	if (size1==0&&size2==0) { TLorentzVectorCMS ret(0.,0.,0.,0.); newvecTLV.push_back(ret); return newvecTLV; } // <- should figure out something else for this case..
	
	int maxsize = max(size1,size2);
	int minsize = min(size1,size2);
	
	bool smallestis1 = (size1<size2) ? true : false;
	
	int i = 0;
	int j = 0;
	
	while (true)
	{
		if ((i==minsize&&smallestis1)||(j==minsize&&(!smallestis1))) break;

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
	if (smallestis1)
	{
		while (true)
		{
			if (j==maxsize) break;
			newvecTLV.push_back(leps2[j]);
			j++;
		}								
	}
	if (!smallestis1)
	{			
		while (true)
		{
			if (i==maxsize) break;
			newvecTLV.push_back(leps1[i]);
			i++;
		}
	}
	
//// above takes a time that is linear with size of the vectors.
//// brute force (if you aren't sure if they are sorted beforehand), takes
//// a time that is quadratic in size of the vector:
// 	
// 	leps1.insert(leps1.end(),leps2.begin(),leps2.end());
// 	vecTLorentzVector newvecTLV;
// 	
// 	//int startingpoint = 0;
// 	int size = leps1.size();
// 	
// 	for (int i=0; i<size; i++)
// 	{
// 		for (int j=0; j<size; j++)
// 		{
// 			bool isprevious = false;
// 			
// 			int max
			
	
//	TLorentzVector dummy;
//	dummy.SetPxPyPzE(0.,0.,0.,0.);
//	newvecTLV.push_back(dummy);

	return newvecTLV;
	
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



bool MultileptonAna::isGoodMuon(const pat::Muon& iMuon, const float iMinPt, const muonID::muonID iMuonID){
  
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
  bool isPFMuon         = false;
  bool passesTrackerID  = false;

  bool passesGlobalTrackID   = false;
  bool passesMuonBestTrackID = false;
  bool passesInnerTrackID    = false;
  bool passesTrackID         = false;

  
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
  case muonID::muonNoCuts:
    return true;
    break;
  case muonID::muonLoose:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) <= maxLooseMuonAbsEta));
    passesIso        = (GetMuonRelIsoR03(iMuon) < looseRelativeIso);
    isPFMuon         = true;
    passesID         = (( iMuon.isGlobalMuon() || iMuon.isTrackerMuon() ) && isPFMuon);
    break;
  case muonID::muonTight:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) <= maxTightMuonAbsEta));
    passesIso        = (GetMuonRelIsoR03(iMuon) < tightRelativeIso);
    isPFMuon         = true;

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

    passesID        = ((iMuon.isGlobalMuon() || iMuon.isTrackerMuon()) && isPFMuon && passesTrackerID);
    break;
  case muonID::muonPreselection:
    passesKinematics = ((iMuon.pt() > minMuonPt) && (fabs(iMuon.eta()) < 2.4));
    passesIso        = (GetMuonRelIsoR03(iMuon) < 0.4);
    isPFMuon         = iMuon.isPFMuon();
    if( iMuon.innerTrack().isAvailable() ){
      passesMuonBestTrackID = ( (fabs(iMuon.innerTrack()->dxy(vertex.position())) < 0.05)
                                && (fabs(iMuon.innerTrack()->dz(vertex.position())) < 0.2)
                                );
    }
    //need charge flip cuts...
    //    passesID         = (( iMuon.isGlobalMuon() || iMuon.isTrackerMuon() ) && isPFMuon && passesMuonBestTrackID );
    passesID         = (( iMuon.isGlobalMuon() || iMuon.isTrackerMuon() ) && isPFMuon && passesMuonBestTrackID );
    break;
  }
  
  return (passesKinematics && passesIso && passesID);
}

float MultileptonAna::GetMuonRelIsoR03(const pat::Muon& iMuon) const
{
  float result = 9999;
  
  double pfIsoCharged = iMuon.pfIsolationR03().sumChargedHadronPt;
  double pfIsoNeutral = iMuon.pfIsolationR03().sumNeutralHadronEt + iMuon.pfIsolationR03().sumPhotonEt;
  
  double pfIsoPUSubtracted = std::max( 0.0, pfIsoNeutral - 0.5*iMuon.pfIsolationR03().sumPUPt );
  
  result = (pfIsoCharged + pfIsoPUSubtracted)/iMuon.pt();
  
  return result;
}


float MultileptonAna::GetMuonRelIsoR04(const pat::Muon& iMuon) const
{
  float result = 9999;
  
  double pfIsoCharged = iMuon.pfIsolationR04().sumChargedHadronPt;
  double pfIsoNeutral = iMuon.pfIsolationR04().sumNeutralHadronEt + iMuon.pfIsolationR04().sumPhotonEt;
  
  double pfIsoPUSubtracted = std::max( 0.0, pfIsoNeutral - 0.5*iMuon.pfIsolationR04().sumPUPt );
  
  result = (pfIsoCharged + pfIsoPUSubtracted)/iMuon.pt();
  
  return result;
}




bool MultileptonAna::isGoodElectron(const pat::Electron& iElectron, const float iMinPt, const electronID::electronID iElectronID){

  CheckVertexSetUp();
  
  double minElectronPt = iMinPt;

  float maxLooseElectronAbsEta = electronparams.getParameter<double> ("maxLooseElectronAbsEta");
  float maxTightElectronAbsEta = electronparams.getParameter<double> ("maxTightElectronAbsEta");
  string theElectronMVA = electronparams.getParameter<string> ("theElectronMVA");
  double passMVAcut = electronparams.getParameter<double> ("passMVAcut");
  double tightElectronIso = electronparams.getParameter<double> ("tightElectronIso");
  double looseElectronIso = electronparams.getParameter<double> ("looseElectronIso");  
  double tightDxy = electronparams.getParameter<double> ("tightDxy");
  double looseDxy = electronparams.getParameter<double> ("looseDxy");
  double dz = electronparams.getParameter<double> ("dZ");
  
  // Be skeptical about this electron making it through
  bool passesKinematics	= false;
  bool passesIso        = false;
  bool passesID         = false;

  bool inCrack = false;
  if( iElectron.superCluster().isAvailable() )
    inCrack = ( fabs(iElectron.superCluster()->position().eta())>1.4442 && fabs(iElectron.superCluster()->position().eta())<1.5660 ); // doesn't change


  // below should be made less confusing ...

  bool myTrigPresel = true;

  double eleID      = iElectron.electronID(theElectronMVA);
  bool passMVAId53x = ( eleID > passMVAcut );  // For 2012_53x, tighter selection

  bool d02 = false; 
  bool d04 = false;
  bool dZ  = false;
  bool no_exp_inner_trkr_hits = true; //false; // see below
  bool passGsfTrackID = false;
  if( iElectron.gsfTrack().isAvailable() ){
    d02 = ( fabs(iElectron.gsfTrack()->dxy(vertex.position())) < tightDxy );
    d04 = ( fabs(iElectron.gsfTrack()->dxy(vertex.position())) < looseDxy );
    //no_exp_inner_trkr_hits = ( iElectron.gsfTrack()->trackerExpectedHitsInner().numberOfHits() <= 0 ); // deprecated in 7_2_0 .. replace with ..?
    dZ = ( fabs(iElectron.gsfTrack()->dz(vertex.position())) < dz );
  }

  bool notConv = ( iElectron.passConversionVeto() );
  bool id      = ( passMVAId53x && d02 && dZ && notConv );

  switch(iElectronID){
  case electronID::electronSide:
  case electronID::electronSideLooseMVA:
  case electronID::electronSideTightMVA:
  case electronID::electronLooseMinusTrigPresel:
  case electronID::electronNoCuts:
    return true;
    break;
  case electronID::electronLoose:
    passesKinematics = ((iElectron.pt() >= minElectronPt) && (fabs(iElectron.eta()) <= maxLooseElectronAbsEta) && !inCrack);
    passesIso        = (GetElectronRelIso(iElectron) < looseElectronIso);
    passesID         = ( passMVAId53x && no_exp_inner_trkr_hits && d04 && notConv && myTrigPresel );
    break;
  case electronID::electronTightMinusTrigPresel:
  case electronID::electronTight:
    passesKinematics = ((iElectron.pt() >= minElectronPt) && (fabs(iElectron.eta()) <= maxTightElectronAbsEta) && !inCrack);
    passesIso        = (GetElectronRelIso(iElectron) < tightElectronIso);
    passesID         = ( id && no_exp_inner_trkr_hits && myTrigPresel );
    break;
  case electronID::electronPreselection:
    ///////
    //
    // ele mva id hack
    //
    //////
    bool passesMVA = false;
    bool useFull5x5 = true;
    bool mvaDebug = false;
    double eleMvaNonTrig = mvaID_->mvaValue(iElectron,vertex,rho,useFull5x5,mvaDebug);

    float SCeta = abs(iElectron.superCluster()->position().eta());

    if ( iElectron.pt() < 10 ){
      if ( SCeta < 0.8){
	passesMVA = ( eleMvaNonTrig > 0.47 );
      }
      else if ( SCeta < 1.479){
	passesMVA = ( eleMvaNonTrig > 0.004 );
      }
      else {
	passesMVA = ( eleMvaNonTrig > 0.295 );
      }
    }
    else {
      if ( SCeta < 0.8){
	passesMVA = ( eleMvaNonTrig > 0.5 );
      }
      else if ( SCeta < 1.479){
	passesMVA = ( eleMvaNonTrig > 0.12 );
      }
      else {
	passesMVA = ( eleMvaNonTrig > 0.60 );
      }
    }
    
    passesKinematics = ((iElectron.pt() > minElectronPt) && (fabs(iElectron.eta()) < 2.5));
    passesIso        = (GetElectronRelIso(iElectron) < 0.400);
    if( iElectron.gsfTrack().isAvailable() ){
      //old
      //      passGsfTrackID = ( (fabs(iElectron.gsfTrack()->dxy(vertex.position())) < 0.05) && (fabs(iElectron.gsfTrack()->dz(vertex.position())) < 0.2) && iElectron.gsfTrack()->trackerExpectedHitsInner().numberOfHits() <= 1 );
      //new
      passGsfTrackID = ( (fabs(iElectron.gsfTrack()->dxy(vertex.position())) < 0.05) && (fabs(iElectron.gsfTrack()->dz(vertex.position())) < 0.2) && iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS) <= 1 );
      //temporary
      //      passGsfTrackID = ( (fabs(iElectron.gsfTrack()->dxy(vertex.position())) < 0.05) && (fabs(iElectron.gsfTrack()->dz(vertex.position())) < 0.2) );
    }

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


float MultileptonAna::GetMuonLepMVA(const pat::Muon& iMuon, const std::vector<pat::Jet>& iJets){
  CheckSetUp();
  
  varchRelIso = iMuon.chargedHadronIso()/iMuon.pt();
  varneuRelIso = max(0.0,(iMuon.neutralHadronIso()+iMuon.photonIso())-0.5*iMuon.puChargedHadronIso())/iMuon.pt();
  //varchRelIso = iMuon.pfIsolationR04().sumChargedHadronPt/iMuon.pt();
  //varneuRelIso = GetMuonRelIsoR04(iMuon) - varchRelIso;
  
  pat::Jet matchedJet = getClosestJet(iJets,iMuon);
  double dR = MiniAODHelper::DeltaR(&matchedJet,&iMuon);
  varjetDR_in = min(dR,0.5);
  varjetPtRatio_in = min(iMuon.pt()/matchedJet.pt(), float(1.5));
  
  varjetBTagCSV_in = max(matchedJet.bDiscriminator("combinedSecondaryVertexBJetTags"), float(0.0));
  varsip3d = fabs(iMuon.dB(pat::Muon::PV3D)/iMuon.edB(pat::Muon::PV3D));
  //  vardxy = log(fabs(iMuon.muonBestTrack()->dxy(vertex.position())));
  //  vardz = log(fabs(iMuon.muonBestTrack()->dz(vertex.position())));
  vardxy = log(fabs(iMuon.innerTrack()->dxy(vertex.position())));
  vardz = log(fabs(iMuon.innerTrack()->dz(vertex.position())));

  // std::cout << "Mu charged Rel Iso = "<< varchRelIso << std::endl;
  // std::cout << "Mu neutral Rel Iso = "<< varneuRelIso << std::endl;
  // std::cout << "Mu jet dR = " << varjetDR_in << std::endl;
  // std::cout << "Mu jet pt ratio = "<< varjetPtRatio_in << std::endl;
  // std::cout << "Mu btag jet csv = " << varjetBTagCSV_in << std::endl;
  // std::cout << "Mu sip 3d = "<< varsip3d << std::endl;
  // std::cout << "Mu dxy = "<< vardxy << std::endl;
  // std::cout << "Mu dz = "<< vardz << std::endl;
  
  if (iMuon.pt() > 15 && fabs(iMuon.eta()) < 1.5) {
    //  std::cout << "Muon LepMVA: " << mu_reader_high_b->EvaluateMVA( "BDTG method" ) << std::endl;
    return mu_reader_high_b->EvaluateMVA( "BDTG method" );
  }
  else if (iMuon.pt() > 15 && fabs(iMuon.eta()) >= 1.5) {
    //std::cout << "Muon LepMVA: " << mu_reader_high_e->EvaluateMVA( "BDTG method" ) << std::endl;
    return mu_reader_high_e->EvaluateMVA( "BDTG method" );
  }
  else if (iMuon.pt() <= 15 && fabs(iMuon.eta()) < 1.5) {
    //std::cout << "Muon LepMVA: " << mu_reader_low_b->EvaluateMVA( "BDTG method" ) << std::endl;
    return mu_reader_low_b->EvaluateMVA( "BDTG method" );
  }
  else {
    //std::cout << "Muon LepMVA: " << mu_reader_low_e->EvaluateMVA( "BDTG method" ) << std::endl;
    return mu_reader_low_e->EvaluateMVA( "BDTG method" );
  }
 
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
  
  varjetBTagCSV_in = max(matchedJet.bDiscriminator("combinedSecondaryVertexBJetTags"), float(0.0));
  varsip3d = fabs(iElectron.dB(pat::Electron::PV3D)/iElectron.edB(pat::Electron::PV3D));
  
  bool useFull5x5 = true;
  bool mvaDebug = false;
  //  varmvaId = iElectron.electronID("mvaNonTrigV0");
  varmvaId = mvaID_->mvaValue(iElectron,vertex,rho,useFull5x5,mvaDebug);  
  
  //varinnerHits = iElectron.gsfTrack()->trackerExpectedHitsInner().numberOfHits(); // 70X
  varinnerHits = iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::TRACK_HITS); // 72X

  // std::cout << "Ele charged Rel Iso = "<< varchRelIso << std::endl;
  // std::cout << "Ele neutral Rel Iso = "<< varneuRelIso << std::endl;
  // std::cout << "Ele jet dR = " << varjetDR_in << std::endl;
  // std::cout << "Ele jet pt ratio = "<< varjetPtRatio_in << std::endl;
  // std::cout << "Ele btag jet csv = " << varjetBTagCSV_in << std::endl;
  // std::cout << "Ele sip 3d = "<< varsip3d << std::endl;
  // std::cout << "Ele mva id = "<< varmvaId << std::endl;
  
  if (iElectron.pt() >= 10 && fabs(iElectron.eta()) <= 0.8) {
    //std::cout << "Electron LepMVA: " << ele_reader_high_cb->EvaluateMVA( "BDTG method" ) << std::endl;
    return ele_reader_high_cb->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() >= 10 && fabs(iElectron.eta()) > 0.8 && fabs(iElectron.eta()) <= 1.479) {
    //std::cout << "Electron LepMVA: " << ele_reader_high_fb->EvaluateMVA( "BDTG method" ) << std::endl;
    return ele_reader_high_fb->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() >= 10 && fabs(iElectron.eta()) > 1.479) {
    ///std::cout << "Electron LepMVA: " << ele_reader_high_ec->EvaluateMVA( "BDTG method" ) << std::endl;
    return ele_reader_high_ec->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() < 10 && fabs(iElectron.eta()) <= 0.8) {
    //std::cout << "Electron LepMVA: " << ele_reader_low_cb->EvaluateMVA( "BDTG method" ) << std::endl;
    return ele_reader_low_cb->EvaluateMVA( "BDTG method" );
  }
  else if (iElectron.pt() < 10 && fabs(iElectron.eta()) > 0.8 && fabs(iElectron.eta()) <= 1.479) {
    //std::cout << "Electron LepMVA: " << ele_reader_low_fb->EvaluateMVA( "BDTG method" ) << std::endl;
    return ele_reader_low_fb->EvaluateMVA( "BDTG method" );
  }
  else {
    //std::cout << "Electron LepMVA: " << ele_reader_low_ec->EvaluateMVA( "BDTG method" ) << std::endl;
    return ele_reader_low_ec->EvaluateMVA( "BDTG method" );
  }
  
}

//// #endif // !defined( MULTILEPTONANA_CC ) 
