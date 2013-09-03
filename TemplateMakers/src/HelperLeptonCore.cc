
#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"


using namespace std;




// constructor

HelperLeptonCore::HelperLeptonCore (): rawCollections() {

  verbose = true;
  
  if (verbose) std::cout << "Inside constructor" << std::endl;
  

}

void HelperLeptonCore::initializePUReweighting () {

  listOfCollisionDatasets = "2012A_13July, 2012A_06Aug, 2012B_13July, 2012C_PR, 2012C_24Aug, 2012D_PR";

  // this cannot be blank
  // but it is only used for 2011 PU reweighting
  // Options are SingleMu, and ElectronHad
  datasetForBEANHelper = "SingleMu";

}


BEANhelper * HelperLeptonCore::setupAnalysisParameters (string year, string inputName ) {

  analysisYear = year;
  sampleName = inputName;

  detectData (sampleName);
  convertSampleNameToNumber(sampleName);
  initializePUReweighting(); 

  // param 1: the era for your analysis
  // param 2: the type of analysis (DIL most of the time)
  // param 3: data or not?
  // param 4: dataset... for 2011 PU treatment
  // param 5: CSV reshaping on/off
  // param 6: use pf leptons?
  // param 8: list of collision datasets, which much be long


  bHelp.SetUp(analysisYear, sampleNumber, analysisType::DIL, isData, datasetForBEANHelper, false, true,listOfCollisionDatasets);


  return &bHelp;
  
}

bool HelperLeptonCore::detectData (string sampleName) {

  // data detection
  //
  isData = false;
  sysType_lep = "MC";
  if (TString(sampleName).Contains("DoubleElectron")
      || TString(sampleName).Contains("DoubleMu")
      || TString(sampleName).Contains("MuEG")
      || TString(sampleName).Contains("MET")) {

    std::cout << "CONFIG: DATA detected for sample " << sampleName << std::endl;

    isData = true;
    sysType_lep = "data";

  }

  return isData;

}


int HelperLeptonCore::convertSampleNameToNumber (string sampleName ) {
  
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
      nGen = 492779; Xsec = 11.1; }
    else if (sampleName == "singletbar_tW_lj") sampleNumber = 2555; 
    else if (sampleName == "singletbar_tW_jl") sampleNumber = 2565; 
    else if (sampleName == "singletbar_tW_ll") sampleNumber = 2535; 
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
      nGen = 1987010; Xsec = 32.3*0.324*0.101; }
    else if (sampleName == "wz_lljj") { sampleNumber = 2761;
      nGen = 3212461; Xsec = 32.3*0.101*(1-0.324); }
    else if (sampleName == "wz_ljj") { sampleNumber = 2791;
      nGen = 2906320; Xsec = 32.3*0.324*0.699; }
    else if (sampleName == "wzz") { sampleNumber = 2721;
      nGen = 219835; Xsec = 0.01922; } //AWB doesn't exist in new GT?
    else if (sampleName == "zz") { sampleNumber = 2702;
      nGen = 9755621; Xsec = 7.7; }
    else if (sampleName == "zz_llll") { sampleNumber = 2732;
      nGen = 4804217; Xsec = 7.7*0.101*0.101; }
    else if (sampleName == "zz_lljj") { sampleNumber = 2762;
      nGen = 1934806; Xsec = 7.7*2*0.101*0.699; }
    else if (sampleName == "zzz") { sampleNumber = 2722;
      nGen = 224519; Xsec = 0.004587; }
    else if (sampleName == "ttbarW") { sampleNumber = 2524;
      nGen = 195396; Xsec = 0.249; }
    else if (sampleName == "ttbarWW") { sampleNumber = 2534;
      nGen = 216867; Xsec = 0.002037; }
    else if (sampleName == "ttbarZ") { sampleNumber = 2523;
      nGen = 209512; Xsec = 0.208; }
    else if (sampleName == "ttbarG") { sampleNumber = 2560;
      nGen = 71405; Xsec = 0.0000001; } //AWB incorrect value
    else if (sampleName == "ttbarttbar") { sampleNumber = 2525;
      nGen = 99994; Xsec = 0.000716; } //AWB doesn't exist in new GT?
    else if (sampleName == "VH_tautau") { sampleNumber = 2915;
      nGen = 200124; Xsec = 0.07717352; } //AWB doesn't exist in new GT?
    else if (sampleName == "VH_ZZ") { sampleNumber = 2923;
      nGen = 500409; Xsec = 0.03223704; } //AWB doesn't exist in new GT?
    else if (sampleName == "VH_WW") { sampleNumber = 2924;
      nGen = 200408; Xsec = 0.2625365; } //AWB doesn't exist in new GT?
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

  // setup several  BN pointers
BEANFileInterface * HelperLeptonCore::initializeInputCollections (fwlite::ChainEvent & ev, bool isLepMVA) {

  // Each handle for a collection must be de-referenced to get the collection
  // Then you can store a pointer to the collection in a BEANFileInterface
  // then return a pointer to the BEANFileInterface for other folks to use.


  //------   Event 
  h_event.getByLabel(ev,"BNproducer");
  events = *h_event;
  rawCollections.eventCollection = &events;

  //------ MC particles 
  h_mcparticles.getByLabel(ev,"BNproducer","MCstatus3");
  mcparticles = *h_mcparticles;

  //----- hlt
  h_hlt.getByLabel(ev,"BNproducer","HLT");
  hltInfo = *h_hlt;
  rawCollections.hltCollection = &hltInfo;

  

  //------- Muons
  if ( analysisYear == "2012_52x" || analysisYear == "2012_53x" ) {
    
    if (!isLepMVA) {
      h_muons.getByLabel(ev,"BNproducer","selectedPatMuonsPFlow");
    } else {
      h_muons.getByLabel(ev, "BNproducer", "selectedPatMuonsLoosePFlow");
    }
    
  }
  else h_muons.getByLabel(ev,"BNproducer","selectedPatMuonsLoosePFlow");

  muonsRaw = *h_muons;
  rawCollections.rawMuonCollection = &muonsRaw;

  //-----  Electrons

  
  if ( analysisYear == "2012_52x" || analysisYear == "2012_53x" ) {

    if (!isLepMVA) {
      h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsPFlow");
    } else {
      h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsGSF");
    }
  }
  else h_electrons.getByLabel(ev,"BNproducer","selectedPatElectronsLoosePFlow");
  electronsRaw = * h_electrons;
  rawCollections.rawElectronCollection = &electronsRaw;

  
  
  //-----  Jets 
  h_pfjets.getByLabel(ev,"BNproducer","selectedPatJetsPFlow");
  pfjets = *h_pfjets; 
  rawCollections.jetCollection = &pfjets;

  //----- MET

  if ( analysisYear == "2011" ) h_pfmets.getByLabel(ev,"BNproducer","patMETsTypeIPFlow");
  else if ( analysisYear == "2012_52x" || analysisYear == "2012_53x" ) h_pfmets.getByLabel(ev,"BNproducer","patMETsPFlow");
  pfmets = * h_pfmets;
  rawCollections.metCollection = &pfmets;


  // ----- Primary Vertices
  
  h_pvs.getByLabel(ev,"BNproducer","offlinePrimaryVertices");
  pvs = *h_pvs;
  rawCollections.primaryVertexCollection = &pvs;


  // careful, not defined in every sample
  if (analysisYear == "2012_53x" && isLepMVA) {
    h_lepMvaJets.getByLabel(ev, "BNproducer", "patJetsAK5PF");
    lepMvaJets = *h_lepMvaJets;
    rawCollections.jetsForLepMVACollection = & lepMvaJets;
  }
  
  
  

  return & rawCollections;

}

void HelperLeptonCore::getTightLoosePreselectedElectrons (electronID::electronID tightID, electronID::electronID looseID, electronID::electronID preselectedID, BEANFileInterface * selectedCollections) {

  electronsTight = bHelp.GetSelectedElectrons(*(rawCollections.rawElectronCollection), tightID, rawCollections.jetsForLepMVACollection );

  electronsTightLoose = bHelp.GetSelectedElectrons(*(rawCollections.rawElectronCollection), looseID, rawCollections.jetsForLepMVACollection );
  electronsLoose = bHelp.GetDifference(electronsTightLoose, electronsTight);
  
  electronsTightLoosePreselected = bHelp.GetSelectedElectrons(*(rawCollections.rawElectronCollection), preselectedID, rawCollections.jetsForLepMVACollection );
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
 
  muonsTightLoose = bHelp.GetSelectedMuons(*(rawCollections.rawMuonCollection), looseID, rawCollections.jetsForLepMVACollection );
  muonsLoose = bHelp.GetDifference(muonsTightLoose, muonsTight);
  
  muonsTightLoosePreselected = bHelp.GetSelectedMuons(*(rawCollections.rawMuonCollection), preselectedID, rawCollections.jetsForLepMVACollection );
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

}

BNjetCollection * HelperLeptonCore::getCorrectedSelectedJets (double ptCut,
                                                 double etaCut,
                                                 jetID::jetID jetID,
                                                 const char csvWorkingPoint) {

  BNjetCollection tmpCorrJets = bHelp.GetCorrectedJets (*(rawCollections.jetCollection), jetEnergyShift);
  BNjetCollection tmpCorrSelJets = bHelp.GetSelectedJets(tmpCorrJets , ptCut, etaCut, jetID, csvWorkingPoint) ;
  BNjetCollection sortedCorrSelJets = bHelp.GetSortedByPt(tmpCorrSelJets);

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

  selectedCollections->metCollection = & metCorrected;

}

void HelperLeptonCore::fillLepCollectionWithSelectedLeptons (BEANFileInterface * selectedCollections) {

  // remove all entires first
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

