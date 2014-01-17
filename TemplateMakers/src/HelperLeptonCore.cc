#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"

using namespace std;

// constructor
HelperLeptonCore::HelperLeptonCore(): rawCollections() {
  verbose = true;
  if (verbose) std::cout << "Inside constructor" << std::endl;
  gSmearer = new TRandom3(0);
}

void HelperLeptonCore::initializePUReweighting () {
  listOfCollisionDatasets = "2012A_13July, 2012A_06Aug, 2012B_13July, 2012C_PR, 2012C_24Aug, 2012D_PR";
  // this cannot be blank
  // but it is only used for 2011 PU reweighting
  // Options are SingleMu, and ElectronHad
  datasetForBEANHelper = "SingleMu";
}

BEANhelper * HelperLeptonCore::setupAnalysisParameters(string year, string inputName) {
  analysisYear = year;
  sampleName = inputName;

  detectData(sampleName);
  convertSampleNameToNumber(sampleName);
  initializePUReweighting();

  // param 1: the era for your analysis
  // param 2: the type of analysis (DIL most of the time)
  // param 3: data or not?
  // param 4: dataset... for 2011 PU treatment
  // param 5: CSV reshaping on/off
  // param 6: use pf leptons?
  // param 8: list of collision datasets, which much be long

  bHelp.SetUp(analysisYear, sampleNumber, analysisType::DIL, isData, datasetForBEANHelper, false, true, listOfCollisionDatasets);

  return &bHelp;
}

void HelperLeptonCore::detectData(string sampleName) {
  isData = false;
  dataset = "MC";

  if (TString(sampleName).Contains("DoubleElectron")) dataset = "DoubleElectron";
  if (TString(sampleName).Contains("DoubleMu")) dataset = "DoubleMu";
  if (TString(sampleName).Contains("MuEG")) dataset = "MuEG";
  if (TString(sampleName).Contains("MET")) dataset = "MET";

  if (dataset != "MC") {
    std::cout << "CONFIG: DATA detected for sample " << sampleName << std::endl;
    isData = true;
  }
}


int HelperLeptonCore::convertSampleNameToNumber(string sampleName) {
  sampleNumber = 999999;
  weight_Xsec = 1.0;
  nGen = 1;
  Xsec = 1.0;

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
    else if (sampleName == "wz") { sampleNumber = 2701;
      nGen = 9931257; Xsec = 32.3; }
    else if (sampleName == "wz_lll") { sampleNumber = 2731;
      nGen = 1987010; Xsec = 1.057*1.10; } 
    else if (sampleName == "wz_lljj") { sampleNumber = 2761;
      nGen = 3212461; Xsec = 32.3*0.101*(1-0.324); }
    else if (sampleName == "wz_ljj") { sampleNumber = 2791;
      nGen = 2906320; Xsec = 32.3*0.324*0.699; }
    else if (sampleName == "wzz") { sampleNumber = 2721;
      nGen = 219835; Xsec = 0.01922; } 
    else if (sampleName == "zz") { sampleNumber = 2702;
      nGen = 9755621; Xsec = 7.7; }
    else if (sampleName == "zz_llll") { sampleNumber = 2732;
      nGen = 4804217; Xsec = 0.157*1.21; } //why is it not (7.7*0.101*0.101) * 1.21?
    else if (sampleName == "zz_lljj") { sampleNumber = 2762;
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

  std::cout << "CONFIG: Sample Name = " << sampleName
            << ", sample Number = " << sampleNumber << endl;

  return sampleNumber;
}

void HelperLeptonCore::initializeInputCollections(edm::EventBase& ev, bool isLepMVA, BEANFileInterface& collections) {
  // Each handle for a collection must be de-referenced to get the collection
  // Then you can store a pointer to the collection in a BEANFileInterface
  // then return a pointer to the BEANFileInterface for other folks to use.

  //------   Event
  edm::InputTag eventTag("BNproducer");
  ev.getByLabel(eventTag, h_event);

  events = *h_event;
  collections.eventCollection = &events;

  //------ MC particles
  edm::InputTag mcTag("BNproducer","MCstatus3");
  ev.getByLabel(mcTag, h_mcparticles);
  mcparticles = *h_mcparticles;
  collections.mcParticleCollection = &mcparticles;

  //----- hlt
  edm::InputTag hltTag("BNproducer","HLT");
  ev.getByLabel(hltTag, h_hlt);
  hltInfo = *h_hlt;
  collections.hltCollection = &hltInfo;

  //------- Muons
  if ( analysisYear == "2012_52x" || analysisYear == "2012_53x" ) {
    if (!isLepMVA) {
      edm::InputTag muonTag("BNproducer","selectedPatMuonsPFlow"); //It looks like there isn't a way to set an input tag except in the constructor, unless I'm missing something obvious (likely)
      ev.getByLabel(muonTag, h_muons);
    } else {
      edm::InputTag muonTag("BNproducer","selectedPatMuonsLoosePFlow");
      ev.getByLabel(muonTag, h_muons);
    }
  }
  else {
    edm::InputTag muonTag("BNproducer","selectedPatMuonsLoosePFlow");
    ev.getByLabel(muonTag, h_muons);
  }

  muonsRaw = *h_muons;
  collections.rawMuonCollection = &muonsRaw;

  //-----  Electrons
  if ( analysisYear == "2012_52x" || analysisYear == "2012_53x" ) {
    if (!isLepMVA) {
      edm::InputTag electronTag("BNproducer","selectedPatElectronsPFlow");
      ev.getByLabel(electronTag, h_electrons);
    } else {
      edm::InputTag electronTag("BNproducer","selectedPatElectronsGSF");
      ev.getByLabel(electronTag, h_electrons);
    }
  }
  else {
    edm::InputTag electronTag("BNproducer","selectedPatElectronsLoosePFlow");
    ev.getByLabel(electronTag, h_electrons);
  }

  electronsRaw = *h_electrons;
  collections.rawElectronCollection = &electronsRaw;

  //-----  Jets
  edm::InputTag jetTag("BNproducer","selectedPatJetsPFlow");
  ev.getByLabel(jetTag, h_pfjets);
  pfjets = *h_pfjets;
  collections.jetCollection = &pfjets;

  //----- MET
  if (analysisYear == "2011") {
    edm::InputTag metTag("BNproducer","patMETsTypeIPFlow");
    ev.getByLabel(metTag, h_pfmets);
  }
  else if (analysisYear == "2012_52x" || analysisYear == "2012_53x") {
    edm::InputTag metTag("BNproducer","patMETsPFlow");
    ev.getByLabel(metTag, h_pfmets);
  }

  pfmets = *h_pfmets;
  collections.metCollection = &pfmets;

  // ----- Primary Vertices
  edm::InputTag pvTag("BNproducer","offlinePrimaryVertices");
  ev.getByLabel(pvTag, h_pvs);
  pvs = *h_pvs;
  collections.primaryVertexCollection = &pvs;

  // careful, not defined in every sample
  if (analysisYear == "2012_53x" && isLepMVA) {
    edm::InputTag lepMVAJetTag("BNproducer", "patJetsAK5PF");
    ev.getByLabel(lepMVAJetTag, h_lepMvaJets);
    lepMvaJets = *h_lepMvaJets;
    collections.jetsForLepMVACollection = &lepMvaJets;
  }

  rawCollections = collections;
}

void HelperLeptonCore::getTightLoosePreselectedElectrons (electronID::electronID tightID, electronID::electronID looseID, electronID::electronID preselectedID, BEANFileInterface * selectedCollections) {
  electronsTight = bHelp.GetSelectedElectrons(*(rawCollections.rawElectronCollection), tightID);
  electronsTightLoose = bHelp.GetSelectedElectrons(*(rawCollections.rawElectronCollection), looseID);
  electronsLoose = bHelp.GetDifference(electronsTightLoose, electronsTight);

  if ( preselectedID==electronID::electronNoCuts ) electronsTightLoosePreselected = *(rawCollections.rawElectronCollection);
  else electronsTightLoosePreselected = bHelp.GetSelectedElectrons(*(rawCollections.rawElectronCollection), preselectedID);
  electronsPreselected = bHelp.GetDifference(electronsTightLoosePreselected, electronsTightLoose);
  electronsLoosePreselected = bHelp.GetUnion(electronsLoose, electronsPreselected);

  selectedCollections->tightElectronCollection = &electronsTight;
  selectedCollections->looseElectronCollection = &electronsLoose;
  selectedCollections->preselectedElectronCollection = &electronsPreselected;

  selectedCollections->tightLooseElectronCollection = &electronsTightLoose;
  selectedCollections->loosePreselectedElectronCollection = &electronsLoosePreselected;
  selectedCollections->tightLoosePreselectedElectronCollection = &electronsTightLoosePreselected;
}

void HelperLeptonCore::getTightLoosePreselectedMuons (muonID::muonID tightID, muonID::muonID looseID, muonID::muonID preselectedID, BEANFileInterface * selectedCollections) {
  muonsTight = bHelp.GetSelectedMuons(*(rawCollections.rawMuonCollection), tightID, rawCollections.jetsForLepMVACollection );
  muonsTightLoose = bHelp.GetSelectedMuons(*(rawCollections.rawMuonCollection), looseID);
  muonsLoose = bHelp.GetDifference(muonsTightLoose, muonsTight);

  if ( preselectedID==muonID::muonNoCuts ) muonsTightLoosePreselected = *(rawCollections.rawMuonCollection);
  else muonsTightLoosePreselected = bHelp.GetSelectedMuons(*(rawCollections.rawMuonCollection), preselectedID);
  muonsPreselected = bHelp.GetDifference(muonsTightLoosePreselected, muonsTightLoose);
  muonsLoosePreselected = bHelp.GetUnion(muonsLoose, muonsPreselected);

  selectedCollections->tightMuonCollection = &muonsTight;
  selectedCollections->looseMuonCollection = &muonsLoose;
  selectedCollections->preselectedMuonCollection = &muonsPreselected;

  selectedCollections->tightLooseMuonCollection = &muonsTightLoose;
  selectedCollections->loosePreselectedMuonCollection = &muonsLoosePreselected;
  selectedCollections->tightLoosePreselectedMuonCollection = &muonsTightLoosePreselected;
}


void HelperLeptonCore::getTightCorrectedJets (double ptCut,
                                              double etaCut,
                                              jetID::jetID tightID,
                                              BEANFileInterface * selectedCollections) {

    BNjetCollection tmpCorrJets = bHelp.GetCorrectedJets (*(rawCollections.jetCollection), jetEnergyShift);
    BNjetCollection tmpCorrSelJets = bHelp.GetSelectedJets(tmpCorrJets , ptCut, etaCut, tightID, '-' ) ;

    jetsTight = bHelp.GetSortedByPt(tmpCorrSelJets);
    selectedCollections->jetCollection = &jetsTight;

    tmpCorrSelJets = bHelp.GetSelectedJets(tmpCorrJets , ptCut, etaCut, tightID, 'L');
    jetsLooseCSV = bHelp.GetSortedByPt(tmpCorrSelJets);
    selectedCollections->jetCollectionLooseCSV = &jetsLooseCSV;

    jetsNotLooseCSV = bHelp.GetSortedByPt(bHelp.GetDifference(jetsTight,jetsLooseCSV));
    selectedCollections->jetCollectionNotLooseCSV = &jetsNotLooseCSV;
    
    tmpCorrSelJets = bHelp.GetSelectedJets(tmpCorrJets , ptCut, etaCut, tightID, 'M');
    jetsMediumCSV = bHelp.GetSortedByPt(tmpCorrSelJets);
    selectedCollections->jetCollectionMediumCSV = &jetsMediumCSV;

    jetsNotMediumCSV = bHelp.GetSortedByPt(bHelp.GetDifference(jetsTight,jetsMediumCSV));
    selectedCollections->jetCollectionNotMediumCSV = &jetsNotMediumCSV;

    tmpCorrSelJets = bHelp.GetSelectedJets(tmpCorrJets , ptCut, etaCut, tightID, 'T');
    jetsTightCSV = bHelp.GetSortedByPt(tmpCorrSelJets);
    selectedCollections->jetCollectionTightCSV = &jetsTightCSV;

    jetsNotTightCSV = bHelp.GetSortedByPt(bHelp.GetDifference(jetsTight,jetsTightCSV));
    selectedCollections->jetCollectionNotTightCSV = &jetsNotTightCSV;
}

BNjetCollection * HelperLeptonCore::getCorrectedSelectedJets (double ptCut,
                                                 double etaCut,
                                                 jetID::jetID jetID,
                                                 const char csvWorkingPoint) {
  sortedCorrSelJets.clear();

  BNjetCollection tmpCorrJets = bHelp.GetCorrectedJets (*(rawCollections.jetCollection), jetEnergyShift);
  BNjetCollection tmpCorrSelJets = bHelp.GetSelectedJets(tmpCorrJets , ptCut, etaCut, jetID, csvWorkingPoint);
  sortedCorrSelJets = bHelp.GetSortedByPt(tmpCorrSelJets);

  return &sortedCorrSelJets;

}

void HelperLeptonCore::getCorrectedMet (BEANFileInterface * selectedCollections, sysType::sysType shift ) {

  // make sure you clear this out
  // before you add something into again
  metCorrected.clear();

  //--- Important notice from BEANhelper
  //--- Use unselected jets for correction 
  //--- Use uncorrected jets to correct the met

  BNmet tmpMet = bHelp.GetCorrectedMET( rawCollections.metCollection->at(0), *rawCollections.jetCollection, shift);

  metCorrected.push_back(tmpMet);

  selectedCollections->metCollection = &metCorrected;
}

void HelperLeptonCore::fillLepCollectionWithSelectedLeptons(BEANFileInterface * selectedCollections) {
  // remove all entries first
  leptonsTight.clear();
  leptonsLoose.clear();
  leptonsPreselected.clear();
  leptonsTightLoose.clear();
  leptonsLoosePreselected.clear();
  leptonsTightLoosePreselected.clear();

  leptonsTight.push_back(*(selectedCollections->tightMuonCollection));
  leptonsTight.push_back(*(selectedCollections->tightElectronCollection));
  leptonsLoose.push_back(*(selectedCollections->looseMuonCollection));
  leptonsLoose.push_back(*(selectedCollections->looseElectronCollection));
  leptonsPreselected.push_back(*(selectedCollections->preselectedMuonCollection));
  leptonsPreselected.push_back(*(selectedCollections->preselectedElectronCollection));
  leptonsTightLoose.push_back(*(selectedCollections->tightLooseMuonCollection));
  leptonsTightLoose.push_back(*(selectedCollections->tightLooseElectronCollection));
  leptonsLoosePreselected.push_back(*(selectedCollections->loosePreselectedMuonCollection));
  leptonsLoosePreselected.push_back(*(selectedCollections->loosePreselectedElectronCollection));
  leptonsTightLoosePreselected.push_back(*(selectedCollections->tightLoosePreselectedMuonCollection));
  leptonsTightLoosePreselected.push_back(*(selectedCollections->tightLoosePreselectedElectronCollection));
      
  // sort them by pt
  leptonsTight.sort();
  leptonsLoose.sort();
  leptonsPreselected.sort();
  leptonsTightLoose.sort();
  leptonsLoosePreselected.sort();
  leptonsTightLoosePreselected.sort();

  selectedCollections->tightLeptonCollection = &leptonsTight;
  selectedCollections->looseLeptonCollection = &leptonsLoose;
  selectedCollections->preselectedLeptonCollection = &leptonsPreselected;
  selectedCollections->tightLooseLeptonCollection = &leptonsTightLoose;
  selectedCollections->loosePreselectedLeptonCollection = &leptonsLoosePreselected;
  selectedCollections->tightLoosePreselectedLeptonCollection = &leptonsTightLoosePreselected;

}

void HelperLeptonCore::fillZLepCollectionWithSelectedLeptons(BEANFileInterface * selectedCollections,
                                                             TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myZLikeMassLepLepSFOS_tight,
                                                             TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myZLikeMassLepLepSFOS_tightLoose,
                                                             TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myZLikeMassLepLepSFOS_all) {

  leptonsTightZ.clear();
  leptonsTightNonZ.clear();
  leptonsTightLooseZ.clear();
  leptonsTightLooseNonZ.clear();
  leptonsTightLoosePreselectedZ.clear();
  leptonsTightLoosePreselectedNonZ.clear();

  //Leptons from Z decay and not from Z decay
  myZLikeMassLepLepSFOS_tight->reset();
  myZLikeMassLepLepSFOS_tight->evaluate();
  myZLikeMassLepLepSFOS_tightLoose->reset();
  myZLikeMassLepLepSFOS_tightLoose->evaluate();
  myZLikeMassLepLepSFOS_all->reset();
  myZLikeMassLepLepSFOS_all->evaluate();
  float ZLikeMassLepLepSFOS_tight = (*myZLikeMassLepLepSFOS_tight).myVars[0].branchVal;
  float ZLikeMassLepLepSFOS_tightLoose = (*myZLikeMassLepLepSFOS_tightLoose).myVars[0].branchVal;
  float ZLikeMassLepLepSFOS_all = (*myZLikeMassLepLepSFOS_all).myVars[0].branchVal;
  TLorentzVector vect1;
  TLorentzVector vect2;
  TLorentzVector vect12;
  bool NonZ;

  for (auto& lepton1: leptonsTight) {
    NonZ = true;
    for (auto& lepton2: leptonsTight) {
      vect1.SetPtEtaPhiE(lepton1->pt, lepton1->eta, lepton1->phi, lepton1->energy);
      vect2.SetPtEtaPhiE(lepton2->pt, lepton2->eta, lepton2->phi, lepton2->energy);
      vect12 = vect1 + vect2;
      if ( abs ( 1 - abs( vect12.M() / ZLikeMassLepLepSFOS_tight ) ) < 0.001 ) {
        leptonsTightZ.push_back(lepton1);
        NonZ = false;
      }
    }
    if ( NonZ ) {
      leptonsTightNonZ.push_back(lepton1);
    }
  }
  
  for (auto& lepton1: leptonsTightLoose) {
    NonZ = true;
    for (auto& lepton2: leptonsTightLoose) {
      vect1.SetPtEtaPhiE(lepton1->pt, lepton1->eta, lepton1->phi, lepton1->energy);
      vect2.SetPtEtaPhiE(lepton2->pt, lepton2->eta, lepton2->phi, lepton2->energy);
      vect12 = vect1 + vect2;
      if ( abs ( 1 - abs( vect12.M() / ZLikeMassLepLepSFOS_tightLoose ) ) < 0.001 ) {
        leptonsTightLooseZ.push_back(lepton1);
        NonZ = false;
      }
    }
    if ( NonZ ) {
      leptonsTightLooseNonZ.push_back(lepton1);
    }
  }

  for (auto& lepton1: leptonsTightLoosePreselected) {
    NonZ = true;
    for (auto& lepton2: leptonsTightLoosePreselected) {
      vect1.SetPtEtaPhiE(lepton1->pt, lepton1->eta, lepton1->phi, lepton1->energy);
      vect2.SetPtEtaPhiE(lepton2->pt, lepton2->eta, lepton2->phi, lepton2->energy);
      vect12 = vect1 + vect2;
      if ( abs ( 1 - abs( vect12.M() / ZLikeMassLepLepSFOS_all ) ) < 0.001 ) {
        leptonsTightLoosePreselectedZ.push_back(lepton1);
        NonZ = false;
      }
    }
    if ( NonZ ) {
      leptonsTightLoosePreselectedNonZ.push_back(lepton1);
    }
  }

  leptonsTightZ.sort();
  leptonsTightNonZ.sort();
  leptonsTightLooseZ.sort();
  leptonsTightLooseNonZ.sort();
  leptonsTightLoosePreselectedZ.sort();
  leptonsTightLoosePreselectedNonZ.sort();

  selectedCollections->tightZLeptonCollection = &leptonsTightZ;
  selectedCollections->tightNonZLeptonCollection = &leptonsTightNonZ;
  selectedCollections->tightLooseZLeptonCollection = &leptonsTightLooseZ;
  selectedCollections->tightLooseNonZLeptonCollection = &leptonsTightLooseNonZ;
  selectedCollections->tightLoosePreselectedZLeptonCollection = &leptonsTightLoosePreselectedZ;
  selectedCollections->tightLoosePreselectedNonZLeptonCollection = &leptonsTightLoosePreselectedNonZ;

}

bool HelperLeptonCore::isFromB(BNmcparticle particle) {
  auto isB = [] (int& id) {return ((abs(id) / 1000) == 5 || (abs(id) / 100) == 5 || (abs(id) == 5));};

  if (isB(particle.motherId)) return true;
  if (isB(particle.mother0Id)) return true;
  if (isB(particle.mother1Id)) return true;

  if ((particle.mother0Status == 2) && (isB(particle.grandMother00Id) || isB(particle.grandMother01Id))) return true;
  if ((particle.mother1Status == 2) && (isB(particle.grandMother10Id) || isB(particle.grandMother11Id))) return true;

  return false;
}

double HelperLeptonCore::scaleIPVarsMC(double ipvar, int genID, double pt, double eta, int mcMatchID, int mcMatchAny) {
  if (abs(genID) == 13) {
    if (mcMatchID != -99 || mcMatchAny <= 1) {
      return ipvar * (abs(eta) < 1.5 ? 1.04 : 1.10);
    } else {
      return ipvar * 0.95;
    }
  } else {
    if (mcMatchID != -99 || mcMatchAny <= 1) {
      return ipvar * (abs(eta) < 1.479 ? 1.02 : 1.07);
    } else {
      return ipvar * 0.95;
    }
  }
}

double HelperLeptonCore::scaleSIPMC(double& sip, int& genID, double& pt, int& mcMatchID, int& mcMatchAny, double& eta) {
  if (abs(genID) == 11 && (mcMatchID != -99 || mcMatchAny <= 1) && abs(eta) >= 1.479) {
    return logSmearMC(gSmearer, sip, 0.10, 0.2);
  }
  return scaleIPVarsMC(sip, genID, pt, eta, mcMatchID, mcMatchAny);
}

double HelperLeptonCore::scaleDZMC(double dz, int genID, double pt, double eta, int mcMatchID, int mcMatchAny) {
  if (abs(genID) == 11 && (mcMatchID != -99 || mcMatchAny <= 1) && abs(eta) >= 1.479) {
    return logSmearMC(gSmearer, dz, 0.20, 0.3);
  }
  return scaleIPVarsMC(dz, genID, pt, eta, mcMatchID, mcMatchAny);
}

double HelperLeptonCore::scaleDXYMC(double dxy, int genID, double pt, double eta, int mcMatchID, int mcMatchAny) {
  if (abs(genID) == 11 && (mcMatchID != -99 || mcMatchAny <= 1) && abs(eta) >= 1.479) {
    return logSmearMC(gSmearer, dxy, 0.07, 0.3);
  }
  return scaleIPVarsMC(dxy, genID, pt, eta, mcMatchID, mcMatchAny);
}

double HelperLeptonCore::scaleLepJetPtRatioMC(double jetPtRatio, int genID, double pt, double eta, int mcMatchID, int mcMatchAny) {
  if (mcMatchAny >= 2) {
    if (pt < 15 && jetPtRatio == 1) {
      if (gSmearer->Rndm() < 0.2) {
        if (abs(eta) < 1.5) {
          return gSmearer->Gaus(0.35,0.10);
        } else {
          return gSmearer->Gaus(0.47,0.20);
        }
      }
    }
    if (abs(eta) < 1.5) {
      return (jetPtRatio == 1.0 ? 1.0 : jetPtRatio * 0.95);
    } else {
      // pull closer to central value
      return (jetPtRatio == 1.0 ? 1.0 : 0.95*jetPtRatio + 0.05*0.45);
    }
  }
  if (abs(eta) < 1.5) {
    if (jetPtRatio == 1) return 1;
    return jetPtRatio * 0.98;
  } else {
    if (jetPtRatio == 1) return 1;
    return 0.95*(jetPtRatio*0.972) + 0.05*0.8374; // pull closer to central value
  }
}

double HelperLeptonCore::scaleLepJetDRMC(double jetDR, int genID, double pt, double eta, int mcMatchID, int mcMatchAny) {
  if (jetDR == 0.) return 0.;
  if (abs(genID) == 13) {
    if (mcMatchAny >= 2) return jetDR;
    if (pt > 15) { // muons, high pt
      if (abs(eta) < 1.5) {
        return jetDR * 1.01;
      } else {
        return log(1 + jetDR * (eta * eta) * 0.95) / (eta * eta); // pull closer to zero
      }
    } else { // muons, low pt
      if (abs(eta) < 1.5) {
        return jetDR * 1.01;
      } else if (abs(eta) < 1.9) {
        return log(1 + jetDR * 0.5) / 0.5;
      } else {
        return log(1 + jetDR * 2 * 0.95) / 2;
      }
    }
  } else { // electrons
    if (mcMatchAny >= 2) return jetDR;
    //if (pt > 0) { // electrons, any pt for now
    if (abs(eta) < 1.5) {
      return jetDR * 1.01;
    } else if (abs(eta) < 2.0) {
      return log(1 + jetDR * 0.5) / 0.5;
    } else {
      return log(1 + jetDR * 5 * 0.95) / 5;
    }
    //}
  }
}


