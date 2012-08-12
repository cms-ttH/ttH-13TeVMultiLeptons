#include <utility>


void compareNorms (bool crossSyst) {


  TFile * robinRef = new TFile ("result_combined.root");
  TFile * newCombo = new TFile ("histosForLimits_AllLep_ge3t.root");

  std::vector<std::string> histNames;

  //////// Default names
  
//   histNames.push_back("ttH120_CFMlpANN_ge3t");
//   histNames.push_back("ttbar_CFMlpANN_ge3t");
//   histNames.push_back("ttbarPlusBBbar_CFMlpANN_ge3t");
//   histNames.push_back("ttbarPlusCCbar_CFMlpANN_ge3t");
//   histNames.push_back("zjets_h_CFMlpANN_ge3t");
//   histNames.push_back("zjets_CFMlpANN_ge3t");
//   histNames.push_back("zjets_lowmass_CFMlpANN_ge3t");
//   histNames.push_back("WW_CFMlpANN_ge3t");
//   histNames.push_back("diboson_CFMlpANN_ge3t");
//   histNames.push_back("WZ_CFMlpANN_ge3t");
//   histNames.push_back("ZZ_CFMlpANN_ge3t");
//   histNames.push_back("singlet_s_CFMlpANN_ge3t");
//   histNames.push_back("singlet_CFMlpANN_ge3t");
//   histNames.push_back("singlet_t_CFMlpANN_ge3t");
//   histNames.push_back("singlet_tW_CFMlpANN_ge3t");
//   histNames.push_back("singletbar_s_CFMlpANN_ge3t");
//   histNames.push_back("singletbar_t_CFMlpANN_ge3t");
//   histNames.push_back("singletbar_tW_CFMlpANN_ge3t");
//   histNames.push_back("ttbarW_CFMlpANN_ge3t");
//   histNames.push_back("ttbarZ_CFMlpANN_ge3t");
//   histNames.push_back("wjets_CFMlpANN_ge3t");
//   histNames.push_back("data_obs_CFMlpANN_ge3t");



  histNames.push_back("ttH120_CFMlpANN_ge3t");
  histNames.push_back("ttbar_CFMlpANN_ge3t");
  histNames.push_back("ttbarPlusBBbar_CFMlpANN_ge3t");
  histNames.push_back("ttbarPlusCCbar_CFMlpANN_ge3t");
  histNames.push_back("zjets_h_CFMlpANN_ge3t");
  histNames.push_back("zjets_CFMlpANN_ge3t");
  histNames.push_back("zjets_lowmass_CFMlpANN_ge3t");
  histNames.push_back("WW_CFMlpANN_ge3t");
  histNames.push_back("diboson_CFMlpANN_ge3t");
  histNames.push_back("WZ_CFMlpANN_ge3t");
  histNames.push_back("ZZ_CFMlpANN_ge3t");
  histNames.push_back("singlet_s_CFMlpANN_ge3t");
  histNames.push_back("singlet_CFMlpANN_ge3t");
  histNames.push_back("singlet_t_CFMlpANN_ge3t");
  histNames.push_back("singlet_tW_CFMlpANN_ge3t");
  histNames.push_back("singletbar_s_CFMlpANN_ge3t");
  histNames.push_back("singletbar_t_CFMlpANN_ge3t");
  histNames.push_back("singletbar_tW_CFMlpANN_ge3t");
  histNames.push_back("ttbarW_CFMlpANN_ge3t");
  histNames.push_back("ttbarZ_CFMlpANN_ge3t");
  histNames.push_back("wjets_CFMlpANN_ge3t");
  histNames.push_back("data_obs_CFMlpANN_ge3t");


  string systNameUp = "CMS_eff_bUp";
  string systNameDown = "CMS_eff_bDown";
  
  //histNames.push_back("data__CFMlpANN_ge3t");
  
  for ( std::vector<std::string>::iterator iName = histNames.begin();
        iName != histNames.end();
        iName ++ ) {

    string baseName = (*iName);
    string upName = (*iName) + "_" +  systNameUp;
    string downName = (*iName) + "_" +  systNameDown;

    vector<string> allNames;
    allNames.push_back(baseName);
    allNames.push_back(upName);
    allNames.push_back(downName);

    std::map < string, float > oldIntegrals;
    std::map < string, float > newIntegrals;
    
    for ( unsigned jName = 0; jName < allNames.size(); jName++){
      string targetName = allNames[jName];
      cout << "Comparing " << targetName  << std::endl;

      TH1* oldHist = (TH1*) robinRef->Get( targetName.c_str());
      TH1* newHist = (TH1*) newCombo->Get( targetName.c_str());

      if (!oldHist || !newHist){
        cout << "    Can't find hist. Old file? " << (oldHist !=0) <<"  New File? " << (newHist !=0) <<  "... skipping" <<endl;
        continue;      
      }
    
      float oldInt = oldHist->Integral();
      float newInt = newHist->Integral();

      oldIntegrals[targetName] = oldInt;
      newIntegrals[targetName] = newInt;


      

      if (!crossSyst){
        cout << "  Old: " << oldInt << endl
             << "  New: " << newInt << endl
             << "Ratio: " << newInt/oldInt << endl;
      }
      
    }
    
    if (crossSyst) {
      cout << "Doing " << upName << " to " << downName << endl
           << "  Old: " << oldIntegrals[downName] << endl
           << "  New: " << newIntegrals[upName] << endl
           << "Ratio: " << newIntegrals[upName] /oldIntegrals[downName]
           << endl;

      cout << "Now doing " << downName << " to " << upName << endl
           << "  Old: " << oldIntegrals[upName] << endl
           << "  New: " << newIntegrals[downName] << endl
           << "Ratio: " << newIntegrals[downName] /oldIntegrals[upName]
           << endl;

           
    }
    

  }
    


}
