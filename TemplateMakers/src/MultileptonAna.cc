// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MultileptonAna.h"
#include <algorithm>
#include <array>

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
	muonparams = 		entire_pset.getParameter<edm::ParameterSet> ("muonsOld");
      	electronparams = 	entire_pset.getParameter<edm::ParameterSet> ("electronsOld");
      	leptonparams = 		entire_pset.getParameter<edm::ParameterSet> ("leptons");
      	jetparams = 		entire_pset.getParameter<edm::ParameterSet> ("jets");
      	subjetparams = 		entire_pset.getParameter<edm::ParameterSet> ("fatjets");
      	btagparams = 		entire_pset.getParameter<edm::ParameterSet> ("btags");
      	metparams = 		entire_pset.getParameter<edm::ParameterSet> ("met");
	prunedparams =          entire_pset.getParameter<edm::ParameterSet> ("prunedgenparticles");
	packedparams =          entire_pset.getParameter<edm::ParameterSet> ("packedgenparticles");
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
  string packedCollection = packedparams.getParameter<string> ("packedCollection");
  packedGenParticles packedHandle; 
  event.getByLabel(packedCollection,packedHandle);
  return packedHandle;
  
}

patPackedCands MultileptonAna::GetPackedPFCandidates (const edm::Event& event)
{
  patPackedCands packedHandle; 
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
                
                // this just dumps all the available taggers.. should be commented out in normal operation!
//                 std::vector<std::pair<std::string, float> > dislist = iJet->getPairDiscri();
//                 for (auto pairit = dislist.begin(); pairit != dislist.end(); ++pairit)
//                 {
//                     cout << pairit->first << "  " << pairit->second << endl;
//                 }
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

vector<ttH::Electron> MultileptonAna::GetCollection (vecPatElectron theobjs)
{
  ttH::Electron ele;
  vector<ttH::Electron> eleCollection;

  for (const auto & iEle: theobjs)
    {
      ele.obj = iEle.p4();
      ele.SCeta = iEle.userFloat("superClusterEta");
      ele.pdgID = iEle.pdgId();
      ele.dxy = iEle.userFloat("dxy");
      ele.dz = iEle.userFloat("dxy");
      ele.numMissingInnerHits = iEle.userFloat("numMissingHits");
      ele.charge = iEle.charge();
      ele.isGsfCtfScPixChargeConsistent = iEle.isGsfCtfScPixChargeConsistent();
      ele.passConversioVeto = iEle.passConversionVeto();
      ele.relIso = iEle.userFloat("relIso");
      ele.miniIso = iEle.userFloat("miniIso");
      ele.dEtaIn = iEle.deltaEtaSuperClusterTrackAtVtx();
      ele.dPhiIn = iEle.deltaPhiSuperClusterTrackAtVtx();
      ele.full5x5_sigmaIetaIeta = iEle.full5x5_sigmaIetaIeta();
      ele.hadronicOverEm = iEle.hadronicOverEm();
      ele.lepMVA = iEle.userFloat("leptonMVA");
      ele.chreliso = iEle.userFloat("chargedRelIso");
      ele.nureliso = iEle.userFloat("neutralRelIso");
      ele.matchedJetdR = iEle.userFloat("nearestJetDr");
      ele.jetPtRatio = iEle.userFloat("nearestJetPtRatio");
      ele.csv = iEle.userFloat("nearestJetCsv");
      ele.sip3D = iEle.userFloat("sip3D");
      ele.mvaID = iEle.userFloat("eleMvaId");
      
      if (iEle.genParticle())
      {
        ele.genPdgID = iEle.genParticle()->pdgId();
	ele.isPromptFinalState = iEle.genParticle()->isPromptFinalState();
	ele.isDirectPromptTauDecayProductFinalState = iEle.genParticle()->isDirectPromptTauDecayProductFinalState();
	const reco::Candidate* genMother = GetGenMotherNoFsr(iEle.genParticle());
	ele.genMotherPdgID = genMother->pdgId();        
        const reco::Candidate* genGrandMother = GetGenMotherNoFsr(genMother);        
        ele.genGrandMotherPdgID = genGrandMother->pdgId();
      }
      else 
      {
        ele.genPdgID = 9999;
	ele.isPromptFinalState = false;
	ele.isDirectPromptTauDecayProductFinalState = false;
        ele.genMotherPdgID = 9999;
        ele.genGrandMotherPdgID = 9999;
      }
      eleCollection.push_back(ele);
    }
  return eleCollection;
}

vector<ttH::Muon> MultileptonAna::GetCollection (vecPatMuon theobjs)
{
  ttH::Muon mu;
  vector<ttH::Muon> muCollection;
  for(const auto & iMu: theobjs)
    {
      mu.obj = iMu.p4();
      mu.pdgID = iMu.pdgId();
      mu.charge = iMu.charge();
      mu.isPFMuon = iMu.isPFMuon();
      mu.isTrackerMuon = iMu.isTrackerMuon();
      mu.isGlobalMuon = iMu.isGlobalMuon();
      mu.relIso = iMu.userFloat("relIso");
      mu.miniIso = iMu.userFloat("miniIso");
      mu.localChi2 = iMu.userFloat("localChiSq");
      mu.trKink = iMu.userFloat("trackKink");
      mu.segCompatibility = iMu.segmentCompatibility();
      mu.dxy = iMu.userFloat("dxy");
      mu.dz = iMu.userFloat("dz");
      mu.numberOfValidPixelHits = iMu.userFloat("numValidPixelHits");
      mu.trackerLayersWithMeasurement = iMu.userFloat("trackerLayersWithMeasurement");
      mu.chargeFlip = iMu.userFloat("chargeFlip");
      mu.lepMVA = iMu.userFloat("leptonMVA");
      mu.validFrac = iMu.userFloat("validFraction");
      mu.normalizedChi2 = iMu.userFloat("normalizedChiSq");
      mu.numberOfValidMuonHits = iMu.userFloat("numValidMuonHits");
      mu.numberOfMatchedStations = iMu.numberOfMatchedStations();
      mu.chreliso = iMu.userFloat("chargedRelIso");
      mu.nureliso = iMu.userFloat("neutralRelIso");
      mu.matchedJetdR = iMu.userFloat("nearestJetDr");
      mu.jetPtRatio = iMu.userFloat("nearestJetPtRatio");
      mu.csv = iMu.userFloat("nearestJetCsv");
      mu.sip3D = iMu.userFloat("sip3D");

      if (iMu.genParticle())
	{
	  mu.genPdgID = iMu.genParticle()->pdgId();
	  mu.isPromptFinalState = iMu.genParticle()->isPromptFinalState();
	  mu.isDirectPromptTauDecayProductFinalState = iMu.genParticle()->isDirectPromptTauDecayProductFinalState();
	  const reco::Candidate* genMother = GetGenMotherNoFsr(iMu.genParticle());
	  mu.genMotherPdgID = genMother->pdgId();
	  const reco::Candidate* genGrandMother = GetGenMotherNoFsr(genMother);        
	  mu.genGrandMotherPdgID = genGrandMother->pdgId();
	}
      else
	{
	  mu.genPdgID = 9999;
	  mu.isPromptFinalState = false;
	  mu.isDirectPromptTauDecayProductFinalState = false;
	  mu.genMotherPdgID = 9999;
	  mu.genGrandMotherPdgID = 9999;
	}
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
      if (iJet.genParton())
      {
        jet.genPdgID = iJet.genParton()->pdgId();
        const reco::Candidate* genMother = GetGenMotherNoFsr(iJet.genParton());
	jet.genMotherPdgID = genMother->pdgId();
        const reco::Candidate* genGrandMother = GetGenMotherNoFsr(genMother);        
        jet.genGrandMotherPdgID = genGrandMother->pdgId();
      }
      else
      {
        jet.genPdgID = 9999;
        jet.genMotherPdgID = 9999;
        jet.genGrandMotherPdgID = 9999;
      }
      jet.charge = iJet.jetCharge();
      string thedisc = btagparams.getParameter<string> ("btagdisc");
      jet.csv = iJet.bDiscriminator(thedisc);
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
MultileptonAna::GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const float iMinPt, const muonID::muonID iMuonID){
  CheckSetUp();
  
  std::vector<pat::Muon> selectedMuons;

  for( const auto& mu: inputMuons)
    {
      bool passSelection = false;
      bool passPt = (mu.pt() >= iMinPt);
      switch(iMuonID)
	{
	default:
	case muonID::muonRaw: passSelection = true;
	case muonID::muonPreselection: passSelection = (mu.userFloat("idPreselection") > 0.5 && passPt);
	case muonID::muonLoose: passSelection = (mu.userFloat("idLooseCut") > 0.5 && passPt);
	case muonID::muonTight: passSelection = (mu.userFloat("idTightCut") > 0.5 && passPt);
	case muonID::muonLooseMvaBased: passSelection = (mu.userFloat("idLooseMVA") > 0.5 && passPt);
	case muonID::muonTightMvaBased: passSelection = (mu.userFloat("idTightMVA") > 0.5 && passPt);
	}

      if( passSelection ) selectedMuons.push_back(mu);
      else if (iMuonID == muonID::muonLooseMvaBased || iMuonID == muonID::muonTightMvaBased) break;

    }
  return selectedMuons;
}

std::vector<pat::Electron>
MultileptonAna::GetSelectedElectrons(const std::vector<pat::Electron>& inputElectrons, const float iMinPt, const electronID::electronID iElectronID){

  CheckSetUp();

  std::vector<pat::Electron> selectedElectrons;

  for(const auto& ele: inputElectrons){
      bool passSelection = false;
      bool passPt = (ele.pt() >= iMinPt);
      switch(iElectronID)
	{
	default:
	case electronID::electronRaw: passSelection = true;
	case electronID::electronPreselection: passSelection = (ele.userFloat("idPreselection") > 0.5 && passPt);
	case electronID::electronLoose: passSelection = (ele.userFloat("idLooseCut") > 0.5 && passPt);
	case electronID::electronTight: passSelection = (ele.userFloat("idTightCut") > 0.5 && passPt);
	case electronID::electronLooseMvaBased: passSelection = (ele.userFloat("idLooseMVA") > 0.5 && passPt);
	case electronID::electronTightMvaBased: passSelection = (ele.userFloat("idTightMVA") > 0.5 && passPt);
	}
    
    if( passSelection ) selectedElectrons.push_back(ele);
    else if (iElectronID == electronID::electronLooseMvaBased || iElectronID == electronID::electronTightMvaBased) break;
  }

  return selectedElectrons;
}

std::tuple<std::vector<pat::Muon>,std::vector<pat::Electron>>
MultileptonAna::pickLeptons(const vecPatMuon& iMuons, const muonID::muonID iMuonID, const float iMinMuPt, const vecPatElectron& iElectrons, const electronID::electronID iElectronID, const float iMinElePt)
{
  
  vecPatLepton iLeptons = fillLeptons(iMuons,iElectrons);
  iLeptons = MiniAODHelper::GetSortedByPt(iLeptons);
  
  unsigned int eleIdx = 0;
  unsigned int muIdx = 0;
  vecPatElectron theElectrons;
  vecPatMuon theMuons; 

  for (const auto & iLep : iLeptons)
    {
      if ( abs(iLep.pdgId()) == 11)
	{
	  pat::Electron ele = iElectrons[eleIdx];
	  bool passSelection = false;
	  bool passPt = (ele.pt() >= iMinElePt);
	  switch(iElectronID)
	    {
	    default:
	    case electronID::electronLoose: passSelection = (ele.userFloat("idLooseCut") > 0.5 && passPt);
	    case electronID::electronTight: passSelection = (ele.userFloat("idTightCut") > 0.5 && passPt);
	    case electronID::electronLooseMvaBased: passSelection = (ele.userFloat("idLooseMVA") > 0.5 && passPt);
	    case electronID::electronTightMvaBased: passSelection = (ele.userFloat("idTightMVA") > 0.5 && passPt);
	    }
	  if ( passSelection ) theElectrons.push_back(ele);
	  else break;
	  eleIdx+=1;
	}
      else if ( abs(iLep.pdgId()) == 13)
	{
	  pat::Muon mu = iMuons[muIdx];
	  bool passSelection = false;
	  bool passPt = (mu.pt() >= iMinMuPt);
	  switch(iMuonID)
	    {
	    default:
	    case muonID::muonLoose: passSelection = (mu.userFloat("idLooseCut") > 0.5 && passPt);
	    case muonID::muonTight: passSelection = (mu.userFloat("idTightCut") > 0.5 && passPt);
	    case muonID::muonLooseMvaBased: passSelection = (mu.userFloat("idLooseMVA") > 0.5 && passPt);
	    case muonID::muonTightMvaBased: passSelection = (mu.userFloat("idTightMVA") > 0.5 && passPt);
	    }
	  if ( passSelection ) theMuons.push_back(mu);
	  else break;
	  muIdx+=1;
	}
    }
  auto t = std::make_tuple(theMuons,theElectrons);
  return t;

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

//// #endif // !defined( MULTILEPTONANA_CC ) 
