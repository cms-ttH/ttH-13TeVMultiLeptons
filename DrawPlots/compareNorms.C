#include <utility>


void compareNorms (bool drawPlots = false, bool crossSyst = false) {


  //TFile * robinRef = new TFile ("result_combined.root");
  TFile * robinRef = new TFile ("histosForLimits_AllLep_2012_AllTag.root");
  TFile * newCombo = new TFile ("histosForLimits_afterCSVChange.root");
  

  std::vector<std::string> histNames;

  //////// Default names
  
//   histNames.push_back("ttH120_CFMlpANN_e2je2t");
//   histNames.push_back("ttbar_CFMlpANN_e2je2t");
//   histNames.push_back("ttbarPlusBBbar_CFMlpANN_e2je2t");
//   histNames.push_back("ttbarPlusCCbar_CFMlpANN_e2je2t");
//   histNames.push_back("zjets_h_CFMlpANN_e2je2t");
//   histNames.push_back("zjets_CFMlpANN_e2je2t");
//   histNames.push_back("zjets_lowmass_CFMlpANN_e2je2t");
//   histNames.push_back("WW_CFMlpANN_e2je2t");
//   histNames.push_back("diboson_CFMlpANN_e2je2t");
//   histNames.push_back("WZ_CFMlpANN_e2je2t");
//   histNames.push_back("ZZ_CFMlpANN_e2je2t");
//   histNames.push_back("singlet_s_CFMlpANN_e2je2t");
//   histNames.push_back("singlet_CFMlpANN_e2je2t");
//   histNames.push_back("singlet_t_CFMlpANN_e2je2t");
//   histNames.push_back("singlet_tW_CFMlpANN_e2je2t");
//   histNames.push_back("singletbar_s_CFMlpANN_e2je2t");
//   histNames.push_back("singletbar_t_CFMlpANN_e2je2t");
//   histNames.push_back("singletbar_tW_CFMlpANN_e2je2t");
//   histNames.push_back("ttbarW_CFMlpANN_e2je2t");
//   histNames.push_back("ttbarZ_CFMlpANN_e2je2t");
//   histNames.push_back("wjets_CFMlpANN_e2je2t");
//   histNames.push_back("data_obs_CFMlpANN_e2je2t");



  histNames.push_back("ttH120_CFMlpANN_e2je2t");
  histNames.push_back("ttbar_CFMlpANN_e2je2t");
  histNames.push_back("ttbarPlusBBbar_CFMlpANN_e2je2t");
  histNames.push_back("ttbarPlusCCbar_CFMlpANN_e2je2t");
  histNames.push_back("zjets_h_CFMlpANN_e2je2t");
  histNames.push_back("zjets_CFMlpANN_e2je2t");
  histNames.push_back("zjets_lowmass_CFMlpANN_e2je2t");
  histNames.push_back("WW_CFMlpANN_e2je2t");
  histNames.push_back("diboson_CFMlpANN_e2je2t");
  histNames.push_back("WZ_CFMlpANN_e2je2t");
  histNames.push_back("ZZ_CFMlpANN_e2je2t");
  histNames.push_back("singlet_s_CFMlpANN_e2je2t");
  histNames.push_back("singlet_CFMlpANN_e2je2t");
  histNames.push_back("singlet_t_CFMlpANN_e2je2t");
  histNames.push_back("singlet_tW_CFMlpANN_e2je2t");
  histNames.push_back("singletbar_s_CFMlpANN_e2je2t");
  histNames.push_back("singletbar_t_CFMlpANN_e2je2t");
  histNames.push_back("singletbar_tW_CFMlpANN_e2je2t");
  histNames.push_back("ttbarW_CFMlpANN_e2je2t");
  histNames.push_back("ttbarZ_CFMlpANN_e2je2t");
  histNames.push_back("wjets_CFMlpANN_e2je2t");
  histNames.push_back("data_obs_CFMlpANN_e2je2t");


  string systNameUp = "CMS_eff_bUp";
  string systNameDown = "CMS_eff_bDown";
  
  //histNames.push_back("data__CFMlpANN_e2je2t");

  int numPlots = 0; 
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

      if (drawPlots && oldHist && newHist) {

        TCanvas * myCan = new TCanvas (targetName.c_str(), targetName.c_str());
        //TCanvas * oldCan = new TCanvas ((targetName+"_OLD").c_str(), (targetName+"OLD").c_str());
        myCan->cd();

        //newHist->Scale(0.5);

        double maxOld = oldHist->GetMaximum();
        double maxNew = newHist->GetMaximum();
        double theMax = (maxOld > maxNew)? maxOld : maxNew;
        theMax *= 1.2;

        oldHist->SetFillColor(0);
        
        oldHist->SetMaximum(theMax);
        int numBin = oldHist->GetNbinsX();
        
        cout << "Maximum is " << theMax << "(old = " << maxOld << ", new = " << maxNew << endl;
        cout << "Num bins old = " << oldHist->GetNbinsX()
             << " new = " << newHist->GetNbinsX() << endl
             << " new min = " << newHist->GetBinLowEdge(1)
             << " new max = " << newHist->GetBinLowEdge(numBin+1) 
             << endl;

        
        
        


        myCan->cd();
        oldHist->DrawCopy("hist");
        newHist->DrawCopy("pe same");

        myCan->SaveAs((targetName+".png").c_str());

        myCan->Delete();

      }

      if (!oldHist || !newHist){
        cout << "    Can't find hist. Old file? " << (oldHist !=0) <<"  New File? " << (newHist !=0) <<  "... skipping" <<endl;
        continue;      
      }
    
      float oldInt = oldHist->Integral();
      float newInt = newHist->Integral();

      float oldEntries = oldHist->GetEntries();
      float newEntries = newHist->GetEntries();

      oldIntegrals[targetName] = oldInt;
      newIntegrals[targetName] = newInt;


      

      if (!crossSyst){
        cout << "  Old: " << oldInt << " (Entries: " << oldEntries << ")" << endl
             << "  New: " << newInt << " (Entries: " << newEntries << ")" << endl
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
    

    numPlots++;
    //if (numPlots > 0) break;
  }
    


}
