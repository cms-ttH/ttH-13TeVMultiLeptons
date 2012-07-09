//root -l -q -b /home/sixie/CMSSW_analysis/src/EWKAna/Hww/LeptonSelection/EvaluateElectronMVA.C+'("ElectronSelectionTraining.Fake.weighted.Subdet0LowPt.root","output/ElectronNtuple.Fake.Subdet0LowPt.root","Subdet0LowPt","Likelihood,LikelihoodD,BDT,BDTG,MLPBNN")'
//root -l -q -b /home/sixie/CMSSW_analysis/src/EWKAna/Hww/LeptonSelection/EvaluateElectronMVA.C+'("ElectronSelectionTraining.Real.weighted.Subdet0LowPt.root","output/ElectronNtuple.Real.Subdet0LowPt.root","Subdet0LowPt","Likelihood,LikelihoodD,BDT,BDTG,MLPBNN")'





/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TBranch.h"
#include "TRandom.h"

#include "Math/LorentzVector.h"
#include "Math/VectorUtil.h"
#include "TMath.h"

#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

using namespace std;
using namespace TMVA;
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector; 

//--------------------------------------------------------------------

void fillUnderOverFlow(TH1F *h1, float value, float weight = 1)
{
  float min = h1->GetXaxis()->GetXmin();
  float max = h1->GetXaxis()->GetXmax();

  if (value > max) value = h1->GetBinCenter(h1->GetNbinsX());
  if (value < min) value = h1->GetBinCenter(1);

  h1->Fill(value, weight);
}

//--------------------------------------------------------------------

void EvaluateMVAOutput(
//   string inputFile      = "", 
//   string outputFile     = ""

  ) {   
#ifdef __CINT__
  gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

  //--------------------------------------------------------------------
  // path to weights dir (this is where MVA training info is stored)
  // output root file will be stored at [path]/output
  //--------------------------------------------------------------------
  
  vector<string> samples;
//   samples.push_back("ttH120.root");
//   samples.push_back("ttH120_jesUp.root");
//   samples.push_back("ttH120_jesDown.root");

//   samples.push_back("ttbar.root");
//   samples.push_back("ttbar_jesUp.root");
//   samples.push_back("ttbar_jesDown.root");

//   samples.push_back("zjets.root");
//   samples.push_back("zjets_JESUp.root");
//   samples.push_back("zjets_JESDown.root");

  samples.push_back("zjets_lowmass.root");
  samples.push_back("zjets_lowmass_JESUp.root");
  samples.push_back("zjets_lowmass_JESDown.root");

//   samples.push_back("WW.root");
//   samples.push_back("WW_JESUp.root");
//   samples.push_back("WW_JESDown.root");

//   samples.push_back("WZ.root");
//   samples.push_back("WZ_JESUp.root");
//   samples.push_back("WZ_JESDown.root");

//   samples.push_back("ZZ.root");
//   samples.push_back("ZZ_JESUp.root");
//   samples.push_back("ZZ_JESDown.root");

     ////////////
//   samples.push_back("ttH100.root");
//   samples.push_back("ttH100_JESUp.root");
//   samples.push_back("ttH100_JESDown.root");

//   samples.push_back("ttH105.root");
//   samples.push_back("ttH105_JESUp.root");
//   samples.push_back("ttH105_JESDown.root");

//   samples.push_back("ttH110.root");
//   samples.push_back("ttH110_JESUp.root");
//   samples.push_back("ttH110_JESDown.root");

//   samples.push_back("ttH115.root");
//   samples.push_back("ttH115_JESUp.root");
//   samples.push_back("ttH115_JESDown.root");

//   samples.push_back("ttH125.root");
//   samples.push_back("ttH125_JESUp.root");
//   samples.push_back("ttH125_JESDown.root");

//   samples.push_back("ttH130.root");
//   samples.push_back("ttH130_JESUp.root");
//   samples.push_back("ttH130_JESDown.root");

//   samples.push_back("ttH135.root");
//   samples.push_back("ttH135_JESUp.root");
//   samples.push_back("ttH135_JESDown.root");

//   samples.push_back("ttH140.root");
//   samples.push_back("ttH140_JESUp.root");
//   samples.push_back("ttH140_JESDown.root");

     //////////////
//   samples.push_back("ttbar.root");
//   samples.push_back("ttbar_JESUp.root");
//   samples.push_back("ttbar_JESDown.root");

//   samples.push_back("ttbar_bb.root");
//   samples.push_back("ttbar_bb_JESUp.root");
//   samples.push_back("ttbar_bb_JESDown.root");

//   samples.push_back("ttbar_cc.root");
//   samples.push_back("ttbar_cc_JESUp.root");
//   samples.push_back("ttbar_cc_JESDown.root");

//   samples.push_back("ttbarW.root");
//   samples.push_back("ttbarW_JESUp.root");
//   samples.push_back("ttbarW_JESDown.root");

//   samples.push_back("ttbarZ.root");
//   samples.push_back("ttbarZ_JESUp.root");
//   samples.push_back("ttbarZ_JESDown.root");

//   samples.push_back("singlet_s.root");
//   samples.push_back("singlet_s_JESUp.root");
//   samples.push_back("singlet_s_JESDown.root");

//   samples.push_back("singlet_t.root");
//   samples.push_back("singlet_t_JESUp.root");
//   samples.push_back("singlet_t_JESDown.root");

//   samples.push_back("singlet_tW.root");
//   samples.push_back("singlet_tW_JESUp.root");
//   samples.push_back("singlet_tW_JESDown.root");

//   samples.push_back("singletbar_s.root");
//   samples.push_back("singletbar_s_JESUp.root");
//   samples.push_back("singletbar_s_JESDown.root");

//   samples.push_back("singletbar_t.root");
//   samples.push_back("singletbar_t_JESUp.root");
//   samples.push_back("singletbar_t_JESDown.root");

//   samples.push_back("singletbar_tW.root");
//   samples.push_back("singletbar_tW_JESUp.root");
//   samples.push_back("singletbar_tW_JESDown.root");

//   samples.push_back("wjets.root");
//   samples.push_back("wjets_JESUp.root");
//   samples.push_back("wjets_JESDown.root");

//   samples.push_back("data_DiMuon.root");
//   samples.push_back("data_DiEle.root");
//   samples.push_back("data_MuEG.root");

//   samples.push_back("ttbar_scaleup.root");
//   samples.push_back("ttbarPlusBBbar_scaleup.root");
//   samples.push_back("ttbarPlusCCbar_scaleup.root");

//   samples.push_back("ttbar_scaledown.root");
//   samples.push_back("ttbarPlusBBbar_scaledown.root");
//   samples.push_back("ttbarPlusCCbar_scaledown.root");


  //--------------------------------------------------------------------------------
  // IMPORTANT: set the following variables to the same set used for MVA training!!!
  //--------------------------------------------------------------------------------

//   std::map<std::string,int> mvaVar;
//   mvaVar[ "first_jet_pt" ] = 1;
//   mvaVar[ "min_dr_tagged_jets" ] = 1; 
//   mvaVar[ "numJets_float" ] = 1; 
//   mvaVar[ "mindr_lep1_jet" ] = 1;
//   mvaVar[ "avg_btag_disc_btags" ] = 1;
//   mvaVar[ "Ht" ] = 1;
 

  //---------------------------------------------------------------
  // specifies the selection applied to events in the training
  //---------------------------------------------------------------

  // This loads the library
  TMVA::Tools::Instance();

  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;

  Use["CFMlpANN"] = 1;

  // ---------------------------------------------------------------
      
  std::cout << std::endl;
  std::cout << "==> Start TMVAClassificationApplication" << std::endl;

//   // Select methods (don't look at this code - not of interest)
//   if (myMethodList != "") {
//     for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

//     std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
//     for (UInt_t i=0; i<mlist.size(); i++) {
//       std::string regMethod(mlist[i]);

//       if (Use.find(regMethod) == Use.end()) {
//         std::cout << "Method \"" << regMethod 
//                   << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
//         for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
//           std::cout << it->first << " ";
//         }
//         std::cout << std::endl;
//         return;
//       }
//       Use[regMethod] = 1;
//     }
//   }

  // --------------------------------------------------------------------------------------------------

  std::vector< TString >catList ;
  catList.push_back("ge3t");
  catList.push_back("e2je2t");   /////
  const unsigned int nCat = catList.size();


  const unsigned int nsamples = samples.size();
  for( unsigned int i = 0 ; i < nsamples ; ++i ){

    string inputFile      = "../anaTree/" + samples[i] ;
    string outputFile     = "mva_" + samples[i] ;
    std::cout << " ********* starting processing sample " << inputFile << std::endl;
    //*****************************************************************************************
    //Prepare Output Tree
    //*****************************************************************************************
    TFile *tmpfile = new TFile(inputFile.c_str(), "READ");
    TTree *tmptree = (TTree*)tmpfile->Get("summaryTree");

    TString outdir = "output/" ;
    TFile *outFile = new TFile(outdir + outputFile, "RECREATE");
    TTree *OutputTree = tmptree->CloneTree(-1, "fast");

    tmpfile->Close();
    delete tmpfile;


    ///// reader variables
    Float_t                 varfirst_jet_pt;
    Float_t                 varmin_dr_tagged_jets; 
    Float_t                 varnumJets_float; 
    Float_t                 varmindr_lep1_jet;
    Float_t                 varavg_btag_disc_btags;
    Float_t                 varHt;

    Float_t fCFMlpANN[nCat];
    TBranch* branchCFMlpANN[nCat] ;
    // --- Create the Reader object

    TMVA::Reader *reader[nCat];
    for( unsigned int j = 0 ; j < nCat ; ++j ){
      TString label = catList[j];
      reader[j] = new TMVA::Reader( "!Color:!Silent" );    

      reader[j]->AddVariable( "first_jet_pt",         &varfirst_jet_pt   );
      reader[j]->AddVariable( "min_dr_tagged_jets",         &varmin_dr_tagged_jets   ); 
      if (j==0)   reader[j]->AddVariable( "numJets_float",         &varnumJets_float   ); ///
      reader[j]->AddVariable( "mindr_lep1_jet",         &varmindr_lep1_jet   );
      reader[j]->AddVariable( "avg_btag_disc_btags",         &varavg_btag_disc_btags   );
      reader[j]->AddVariable( "Ht",         &varHt   );


      // --- Book the MVA methods
      
      //--------------------------------------------------------------------------------------
      // tell evaluateMVA_smurf_hww where to find the weights dir, which contains the trained MVA's. 
      // In this example, the weights dir is located at [path]/[dir]
      // and the output root file is written to [path]/[output]
      //--------------------------------------------------------------------------------------
      
      TString dir    = "simpleweights/" + label + "/";
      TString prefix = "TMVAClassification";
      
      // Book method(s)
      if(Use["CFMlpANN"]) reader[j]->BookMVA( "CFMlpANN method", dir + prefix + TString("_CFMlpANN.weights.xml"));  
      
      //Add new branches for MVA output
      branchCFMlpANN[j] = 0 ; 
      TString branchName = "CFMlpANN_" + label;
      TString branchType = branchName + "/F";
      if(Use["CFMlpANN"])  branchCFMlpANN[j] = OutputTree->Branch( branchName, &fCFMlpANN[j], branchType );
      //    if(Use["CFMlpANN"])  branchCFMlpANN = OutputTree->Branch( "CFMlpANN" , &fCFMlpANN, "CFMlpANN/F" );
      
    }

    //*****************************************************************************************
    //Prepare Tree Variables
    //*****************************************************************************************
    //Variables
   
    Float_t first_jet_pt;
    Float_t min_dr_tagged_jets;
    Float_t numJets_float; 
    Float_t mindr_lep1_jet;
    Float_t avg_btag_disc_btags;
    Float_t Ht;
    Float_t numTag;

    //*****************************************************************************************
    //Prepare Input Tree
    //*****************************************************************************************
    TFile *inFile = new TFile(inputFile.c_str(), "READ");
    TTree *inTree = (TTree*)inFile->Get("summaryTree");
    //    if (!inTree) inTree = (TTree*)inFile->Get("summaryTreeTesting");
    assert(inTree);

    
    inTree->SetBranchAddress( "first_jet_pt", &first_jet_pt);

    inTree->SetBranchAddress( "min_dr_tagged_jets", &min_dr_tagged_jets);

    inTree->SetBranchAddress( "numJets_float", &numJets_float);

    inTree->SetBranchAddress( "mindr_lep1_jet", &mindr_lep1_jet);

    //   inTree->SetBranchAddress( "avg_tagged_dijet_mass", &avg_tagged_dijet_mass);

    inTree->SetBranchAddress( "avg_btag_disc_btags", &avg_btag_disc_btags);

    inTree->SetBranchAddress( "Ht", &Ht);
    
    inTree->SetBranchAddress( "numTaggedJets_float", &numTag);
    
    ////////////////////
    // --- Event loop
    ///////////////////
    std::cout << "--- Processing: " << inTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();

    int counts = 0;
    for (Long64_t ievt=0; ievt<inTree->GetEntries();ievt++) {

      if (ievt%100000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      inTree->GetEntry(ievt);

      //--------------------------------------------------------
      // important: here we associate branches to MVA variables
      //--------------------------------------------------------
   
      varfirst_jet_pt                    = first_jet_pt;            
      varmin_dr_tagged_jets 		  = min_dr_tagged_jets;  
      varnumJets_float 		  = numJets_float;       
      varmindr_lep1_jet		  = mindr_lep1_jet;      
      varavg_btag_disc_btags		  = avg_btag_disc_btags; 
      varHt                              = Ht;                      
      
      if ( Ht>0 && numTag>=3 )   counts++;
      ////////
      for( unsigned int j = 0 ; j < nCat ; ++j ){
	// --- Return the MVA outputs and weights
	TMVA::Reader  *tmpReader = reader[j];      
	if(Use["CFMlpANN"]) { 
	  fCFMlpANN[j]            = tmpReader->EvaluateMVA( "CFMlpANN method" );
	  branchCFMlpANN[j]->Fill();
	}
      } // End category loop
    
    }

    std::cout << "total counts is " << counts << endl;
    
    // Get elapsed time
    sw.Stop();
    std::cout << "--- End of event loop: "; sw.Print();

    for( unsigned int j = 0 ; j < nCat ; ++j ){    
      delete reader[j];   
    }

    //Write Output file
    outFile->Write();
    outFile->Close();

    std::cout << "==> TMVAClassificationApplication is done with sample " << samples.at(i) << endl << std::endl;
  } 
}

    //Spectator variables declared in the training have to be added to the reader, too
//     Float_t varMuPt, varMuEta, varEventNumberParity;
//     reader->AddSpectator( "eta",   &varMuEta );
//     reader->AddSpectator( "pt" ,   &varMuPt  );
//     reader->AddSpectator( "EventNumberParity",   &varEventNumberParity );
