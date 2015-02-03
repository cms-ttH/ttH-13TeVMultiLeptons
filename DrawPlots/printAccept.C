#include <cmath>      //necessary for absolute function fabs()     
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "math.h"
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <sstream>

//Root includes                                   
#include "TROOT.h"
#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TTree.h"
#include "TString.h"
#include "TMath.h"
#include "TAxis.h"

class varInfo {

public:
  TString var;
  TString hName;
  TString hTitle;
  int nBins;
  int min;
  int max;

  
  varInfo(): var(""), hName(""), hTitle(""), nBins(0), min(0), max(0) {}

  varInfo(TString varName, TString histName, TString histTitle, int numBins, int binMin, int binMax) : 
    var(varName), hName(histName), hTitle(histTitle), nBins(numBins), min(binMin), max(binMax) {}

};

void printAccept () {

  //----------------------------------
  //
  //  Global job params
  //  File names, etc
  //---------------------------------
  
  std::vector<string> InputFileNames;
  std::string InputDirName = "treeFiles/";

  std::vector<string> Outputs;
  std::vector<string> JetTagReqs;
//   Outputs.push_back("Mu");
//   Outputs.push_back("Ele");
//   Outputs.push_back("MuEG");
//   Outputs.push_back("MuLoose");
//   Outputs.push_back("EleLoose");
//   Outputs.push_back("MuEGLoose");
//   Outputs.push_back("MuZmask10");
//   Outputs.push_back("EleZmask10");
  Outputs.push_back("MuALL");
  Outputs.push_back("EleALL");
  Outputs.push_back("MuEGALL");
  
  //InputFileName format: "../batchBEAN/"+InputFileName+"/test_beans_v1_"+InputFileName+"_ALL.root"

  InputFileNames.push_back("singlet_s_JESDown_new");
  InputFileNames.push_back("singlet_s_JESUp_new");
  InputFileNames.push_back("singlet_s_nominal_new");
  InputFileNames.push_back("singlet_tW_JESDown_new");
  InputFileNames.push_back("singlet_tW_JESUp_new");
  InputFileNames.push_back("singlet_tW_nominal_new");
  InputFileNames.push_back("singlet_t_JESDown_new");
  InputFileNames.push_back("singlet_t_JESUp_new");
  InputFileNames.push_back("singlet_t_nominal_new");
  InputFileNames.push_back("singletbar_s_JESDown_new");
  InputFileNames.push_back("singletbar_s_JESUp_new");
  InputFileNames.push_back("singletbar_s_nominal_new");
  InputFileNames.push_back("singletbar_tW_JESDown_new");
  InputFileNames.push_back("singletbar_tW_JESUp_new");
  InputFileNames.push_back("singletbar_tW_nominal_new");
  InputFileNames.push_back("singletbar_t_JESDown_new");
  InputFileNames.push_back("singletbar_t_JESUp_new");
  InputFileNames.push_back("singletbar_t_nominal_new");
  InputFileNames.push_back("ttH120_JESDown_new");
  InputFileNames.push_back("ttH120_JESUp_new");
  InputFileNames.push_back("ttH120_nominal_new");
  InputFileNames.push_back("ttbarW_JESDown_new");
  InputFileNames.push_back("ttbarW_JESUp_new");
  InputFileNames.push_back("ttbarW_nominal_new");
  InputFileNames.push_back("ttbarZ_JESDown_new");
  InputFileNames.push_back("ttbarZ_JESUp_new");
  InputFileNames.push_back("ttbarZ_nominal_new");
  InputFileNames.push_back("ttbar_JESDown_new");
  InputFileNames.push_back("ttbar_JESUp_new");
  InputFileNames.push_back("ttbar_nominal_new");
  InputFileNames.push_back("ttbar_bb_JESDown_new");
  InputFileNames.push_back("ttbar_bb_JESUp_new");
  InputFileNames.push_back("ttbar_bb_nominal_new");
  InputFileNames.push_back("ttbar_cc_JESDown_new");
  InputFileNames.push_back("ttbar_cc_JESUp_new");
  InputFileNames.push_back("ttbar_cc_nominal_new");
  InputFileNames.push_back("wjets_JESDown_new");
  InputFileNames.push_back("wjets_JESUp_new");
  InputFileNames.push_back("wjets_nominal_new");
  InputFileNames.push_back("ww_JESDown_new");
  InputFileNames.push_back("ww_JESUp_new");
  InputFileNames.push_back("ww_nominal_new");
  InputFileNames.push_back("wz_JESDown_new");
  InputFileNames.push_back("wz_JESUp_new");
  InputFileNames.push_back("wz_nominal_new");
  InputFileNames.push_back("zjets_JESDown_new");
  InputFileNames.push_back("zjets_JESUp_new");
  InputFileNames.push_back("zjets_nominal_new");
  InputFileNames.push_back("zz_JESDown_new");
  InputFileNames.push_back("zz_JESUp_new");
  InputFileNames.push_back("zz_nominal_new");
 

  std::vector<varInfo*> varList;
  double pival = 3.14159;

  //varInfo *isTriggerPass = new varInfo("isTriggerPass", "isTriggerPass", "isTriggerPass", 2, 0, 2);
  //varList.push_back(isTriggerPass);
  varInfo *Ht = new varInfo("Ht", "Ht", "Ht", 1000, 0, 10000);
  varList.push_back(Ht);

  JetTagReqs.push_back("eq1t");
  JetTagReqs.push_back("eq2jeq2t");
  JetTagReqs.push_back("ge3jeq2t");
  JetTagReqs.push_back("ge3t");
//  JetTagReqs.push_back("eq4t");
//  JetTagReqs.push_back("ge4t");
  
  std::cout << " Jet Sel , Tag Sel , Lep Sel , Dataset , nGen , xSec , Lumi , nPass " << std::endl;

  const unsigned int nJetTagReqs = JetTagReqs.size();

  for( unsigned int k = 0; k < nJetTagReqs; k++) {  

      std::string JetTagReq = JetTagReqs[k];
      
      std::string JetReq = "holder";
      std::string TagReq = "holder";
      std::string ProbStr = "holder";
      std::string EffStr = "holder";
      std::string TrigStr = "holder";
      std::string WeightStr = "holder";
      
      if (JetTagReq == "eq1t") {
        JetReq = "numJets >= 2";
        TagReq = "numTaggedJets == 1";
      }
      else if (JetTagReq == "eq2jeq2t") {
        JetReq = "numJets == 2";
        TagReq = "numTaggedJets == 2";
      }
      else if (JetTagReq == "ge3jeq2t") {
        JetReq = "numJets >= 3";
        TagReq = "numTaggedJets == 2";
      }
      else if (JetTagReq == "ge3t") {
        JetReq = "numJets >= 3";
        TagReq = "numTaggedJets >= 3";
      }
      else if (JetTagReq == "eq4t") {
        JetReq = "numJets >= 4";
        TagReq = "numTaggedJets == 4";
      }
      else if (JetTagReq == "ge4t") {
        JetReq = "numJets >= 4";
        TagReq = "numTaggedJets >= 4";
      } 

      if (JetReq == "holder" || TagReq == "holder") {
        std::cout << "JetReq or TagReq == holder" << std::endl;
        continue;
      }

  const unsigned int nOutputs = Outputs.size();
  for (unsigned int j = 0; j < nOutputs; j++) {
    std::string OutputDirectory = Outputs[j];
    //std::cout << OutputDirectory << std::endl;
  
  const unsigned int nInputFiles = InputFileNames.size();
  double Integral = 0;
  for( unsigned int i = 0; i < nInputFiles; i++) {

    std::string InputFileLabel = InputFileNames[i];
    if (std::string::npos != InputFileLabel.find("JES")) {
          continue;
        }

    if (std::string::npos != InputFileLabel.find("Run20")) {
      ProbStr = "";
      EffStr = "";
      TrigStr = "";
      WeightStr = "";
      //std::cout << "Set prob2/probge3 to 1" << std::endl;
    }
    else {
      WeightStr = "weight * ";
      ProbStr = "prob * ";

      if (OutputDirectory == "Mu" || OutputDirectory == "MuLoose" || OutputDirectory ==  "MuZmask10" || OutputDirectory == "MuALL") {
        EffStr = "0.987 * 0.987 * ";
        TrigStr = "0.9885 * 0.9885 * ";
      }
      else if (OutputDirectory ==  "Ele" || OutputDirectory ==  "EleLoose" || OutputDirectory ==  "EleZmask10" || OutputDirectory == "EleALL") {
        EffStr = "1.004 * 1.004 * ";
        TrigStr = "";
      }
      else if (OutputDirectory ==  "MuEG" || OutputDirectory ==  "MuEGLoose" || OutputDirectory == "MuEGALL") {
        EffStr = "0.987 * 1.004 * ";
        TrigStr = "0.9885 * ";
      }
      else {
        std::cout << "No options for EffStr! continue ..." << std::endl;
        continue;
      } 
    } 
    
    TString InputFileName = InputDirName+InputFileLabel+".root";

    //std::cout << "==== Processing File " << InputFileLabel << " ==== " << std::endl;
    TFile * DileptonFile = new TFile(InputFileName);
    TTree * DileptonSummaryTree = (TTree *) DileptonFile->Get("summaryTree");

    //double Dilepton_numEvents = DileptonSummaryTree->GetEntries();

    for(std::vector<varInfo*>::iterator tIter1 = varList.begin(); tIter1 != varList.end(); tIter1++) {
      // Pass a pointer to variable info
      varInfo *u = *tIter1;

      //Selection string: ==2 tags or >=3 tags; DiMu, DiEle, MuEG, or DiMuZmask10
      std::string SelectionStr = "holder";
      std::string CleanTrig = "holder";
      

      if (u->hName == "isCleanEvent" || u->hName == "isTriggerPass") {
        CleanTrig = "";
      }
      else {
        CleanTrig = "(isCleanEvent == 1) && (isTriggerPass == 1) && ";
      }

      if (OutputDirectory == "Mu") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons == 2) && (numLooseMuons == 0) && (numTightElectrons == 0) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "Ele") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons == 2) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "MuLoose") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons == 1) && (numLooseMuons == 1) && (numTightElectrons == 0) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      } 
      else if (OutputDirectory == "EleLoose") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons == 1) && (numLooseElectrons == 1) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "MuEG") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons == 1) && (numLooseMuons == 0) && (numTightElectrons == 1) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "MuEGLoose") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons + numTightElectrons == 1) && (numLooseMuons + numLooseElectrons == 1) && (numTightMuons != numLooseMuons)  && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "MuZmask10") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( ((mass_leplep <= 81.2) || (mass_leplep >= 101.2)) && (dR_leplep > 0.2) && (mass_leplep > 12)  && (numTightMuons == 2) && (numLooseMuons == 0) && (numTightElectrons == 0) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "EleZmask10") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( ((mass_leplep <= 81.2) || (mass_leplep >= 101.2)) && (dR_leplep > 0.2) && (mass_leplep > 12)  && (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons == 2) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "MuLooseZmask10") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( ((mass_leplep <= 81.2) || (mass_leplep >= 101.2)) && (dR_leplep > 0.2) && (mass_leplep > 12)  && (numTightMuons == 1) && (numLooseMuons == 1) && (numTightElectrons == 0) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "EleLooseZmask10") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( ((mass_leplep <= 81.2) || (mass_leplep >= 101.2)) && (dR_leplep > 0.2) && (mass_leplep > 12)  && (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons == 1) && (numLooseElectrons == 1) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "MuALL") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons >= 1) && (numTightMuons + numLooseMuons == 2) && (numTightElectrons == 0) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      } 
      else if (OutputDirectory == "EleALL") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons >= 1) && (numTightElectrons + numLooseElectrons == 2) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "MuEGALL") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (dR_leplep > 0.2) && (mass_leplep > 12) && (numTightMuons + numLooseMuons == 1) && (numTightElectrons + numLooseElectrons == 1) && (numTightMuons + numTightElectrons >= 1) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }



      if (SelectionStr == "holder") {
        std::cout << "SelectionStr == holder" << std::endl;
        continue;
      }

      std::stringstream s3;
      std::stringstream s4;
      std::stringstream s5;
      s3 << u->nBins;
      s4 << u->min;
      s5 << u->max;
      TString n3 = s3.str();
      TString n4 = s4.str();
      TString n5 = s5.str();

      TH1 * IntegralHist = new TH1F ("temp", "temp", u->nBins, u->min, u->max);
      //DileptonSummaryTree->Draw(u->hName+">>"+u->hName+"("+n3+","+n4+","+n5+")",SelectionStr.c_str(),"goff");
      //SelectionStr = "(isTriggerPass == 1 && isCleanEvent == 1 && numPV >= 1 && (numTightMuons + numTightElectrons + numLooseMuons + numLooseElectrons) == 2 && (numTightMuons + numTightElectrons) >= 1)";
      //std::cout << SelectionStr << std::endl;
      DileptonSummaryTree->Draw(u->hName+">>temp",SelectionStr.c_str(),"goff");
      Integral = IntegralHist->Integral();
      //std::cout << OutputDirectory << "  " << u->hName << "  " << Integral << std::endl;

      
      
      if (std::string::npos != InputFileLabel.find("DoubleMu_Run2011-v1_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , DoubleMu  , 1 , 0.0002007226 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("DoubleElectron_Run2011-v1_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , DoubleEle  , 1 , 0.0002007226 , 4982.0 , " << Integral  << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("MuEG_Run2011-v1_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , MuEG  , 1 , 0.0002007226 , 4982.0 , " << Integral  << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("ttbar_bb_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ttbb , 52135272 , 157.7 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("ttbar_cc_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ttcc , 52135272 , 157.7 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("ttbar_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ttbar  , 52135272 , 157.7 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("DYJetsToLL_M-10To50_TuneZ2_7TeV-madgraph_v1_PUTAG")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ZJets_M10-50  , 31480628 , 12782.6 , 4982.0 , " << Integral << std::endl;
      }        
      else if (std::string::npos != InputFileLabel.find("zjets_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ZJets  , 35891264 , 3048.0 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("ww_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , WW  , 4225916 , 43.0 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("wz_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , WZ  , 4265241 , 18.0 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("zz_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ZZ  , 4191045 , 5.9 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("ttH120_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ttH_120  , 998833 , 0.098 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("ttbarW")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ttW  , 1085456 , 0.163 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("ttbarZ")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , ttZ  , 1458573  , 0.136 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("wjets_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , WJets , 81011945 , 31314 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("singlet_s_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , t_s , 259595 , 3.17 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("singlet_t_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , t_t , 3891841 , 41.92 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("singlet_tW_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , t_tW , 812600 , 7.87 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("singletbar_s_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , tbar_s , 137662 , 1.44 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("singletbar_t_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , tbar_t , 1939703 , 22.65 , 4982.0 , " << Integral << std::endl;
      }
      else if (std::string::npos != InputFileLabel.find("singletbar_tW_")) {
        std::cout << JetReq << " , " << TagReq << " , " << OutputDirectory << " , tbar_tW , 808200 , 7.87 , 4982.0 , " << Integral << std::endl;
      }

      //std::cout << "Drawing histogram " << u->hName << std::endl;
    }

  } // end files loop
  std::cout << std::endl;

  } //end outputs loop
} // end JetTagReqs loop
  // Write and close output file
}

