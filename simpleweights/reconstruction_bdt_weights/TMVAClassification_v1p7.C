// @(#)root/tmva $Id$
/**********************************************************************************
 * Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Root Macro: TMVAClassification                                                 *
 *                                                                                *
 * This macro provides examples for the training and testing of the               *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *                                                                                *
 *    root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)                     *
 *                                                                                *
 * (note that the backslashes are mandatory)                                      *
 * If no method given, a default set of classifiers is used.                      *
 *                                                                                *
 * The output file "TMVA.root" can be analysed with the use of dedicated          *
 * macros (simply say: root -l <macro.C>), which can be conveniently              *
 * invoked through a GUI that will appear at the end of the run of this macro.    *
 * Launch the GUI via the command:                                                *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 *                                                                                *
 * You can also compile and run the example with the following commands           *
 *                                                                                *
 *    make                                                                        *
 *    ./TMVAClassification <Methods>                                              *
 *                                                                                *
 * where: <Methods> = "method1 method2"                                           *
 *        are the TMVA classifier names                                           *
 *                                                                                *
 * example:                                                                       *
 *    ./TMVAClassification Fisher LikelihoodPCA BDT                               *
 *                                                                                *
 * If no method given, a default set is of classifiers is used                    *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int TMVAClassification_v1p7( TString input_string = "" )
{
  
  TString myMethodList = "";
  // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
  // if you use your private .rootrc, or run from a different directory, please copy the
  // corresponding lines from .rootrc

   // methods to be processed can be given as an argument; use format:
   //
   // mylinux~> root -l TMVAClassification_v1p7.C\(\"myMethod1,myMethod2,myMethod3\"\)
   //
   // if you like to use a method via the plugin mechanism, we recommend using
   //
   // mylinux~> root -l TMVAClassification_v1p7.C\(\"P_myMethod\"\)
   // (an example is given for using the BDT as plugin (see below),
   // but of course the real application is when you write your own
   // method based)

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Boosted Decision Trees
   Use["BDTG"]            = 1; // uses Gradient Boost
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return 1;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outFileNameStr = "TMVA_"+input_string+".root";
   TString outfileName( outFileNameStr );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is 
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TString arg1 = "TMVAClassification_"+input_string;

   TMVA::Factory *factory = new TMVA::Factory( arg1, outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;

   (TMVA::gConfig().GetIONames()).fWeightFileDir = "jan25_recoBdt";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   // factory->AddVariable( "myvar1 := var1+var2", 'F' );
   // factory->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'F' );
   // factory->AddVariable( "var3",                "Variable 3", "units", 'F' );
   // factory->AddVariable( "var4",                "Variable 4", "units", 'F' );

   factory->AddVariable( "b_from_leptop_bdt.csv","b leptop csv","csv",'D');
   factory->AddVariable( "b_from_hadtop_bdt.csv","b hadtop csv","csv",'D');
   factory->AddVariable( "hadTop_tlv_bdt.Pt()","had top pt","pt",'D');
   factory->AddVariable( "w_from_hadtop_tlv_bdt.M()","w frm had top mass","mass",'D');
   factory->AddVariable( "hadTop_tlv_bdt.M()","had top mass","mass",'D'); 
   //factory->AddVariable( "higgs_tlv_bdt.M()","higgs mass","mass",'D'); 
   //factory->AddVariable( "lep_from_higgs_bdt.obj.pt()","lep from higgs pt","pt",'D');
   //factory->AddVariable( "lep_from_leptop_bdt.obj.pt()","lep from top pt","pt",'D');
   factory->AddVariable( "lep_from_leptop_bdt.obj.pt()/lep_from_higgs_bdt.obj.pt()","lep pt ratio","pt",'D');
   //factory->AddVariable( "(lep_from_leptop_bdt.obj.pt()-lep_from_higgs_bdt.obj.pt())/(lep_from_leptop_bdt.obj.pt()+lep_from_higgs_bdt.obj.pt())","lep pt asym","asym",'D');
   
   factory->AddVariable( "dr_lepFromTop_bFromLepTop","dR(b_leptop,lep_top)","dR",'D'); 
   factory->AddVariable( "dr_lepFromTop_bFromHadTop","dR(b_hadtop,lep_top)","dR",'D'); 
   factory->AddVariable( "dr_lepFromHiggs_bFromLepTop","dR(b_leptop,lep_higgs)","dR",'D'); 

   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables
   // factory->AddSpectator( "spec1 := var1*2",  "Spectator 1", "units", 'F' );
   // factory->AddSpectator( "spec2 := var1*3",  "Spectator 2", "units", 'F' );

   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   //   TString fname = "./tmva_class_example.root";

   // TString fname_sig = "/scratch365/cmuelle2/training_trees/reco_bdt_factorized/tth_genFilter_recoBdtTraining_2lss.root";
   // TString fname_bkg = "/scratch365/cmuelle2/training_trees/reco_bdt_factorized_noHiggsLoops/ttbar_recoBdtTraining.root";
   //TString fname_bkg = "/scratch365/cmuelle2/training_trees/reco_bdt_factorized/ttbar_genFilter_bdtTraining_2lss.root";
   
   TString fname_sig = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training/ttH_powheg_relaxed_2lssos.root";
   TString fname_bkg = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training/ttbar_semilep_madgraph_recoBdtTraining.root";
   //   TString fname_bkg = "/scratch365/cmuelle2/training_trees/jan28_bkg_conePt_fr/ttbar_bdtReco_training.root";
   
   if (gSystem->AccessPathName( fname_sig ))  // file does not exist in local directory
      gSystem->Exec("curl -O http://root.cern.ch/files/tmva_class_example.root");
   
   TFile *input_sig = TFile::Open( fname_sig );
   TFile *input_bkg = TFile::Open( fname_bkg );
   
   std::cout << "--- TMVAClassification       : Using input file: " << input_sig->GetName() << std::endl;
   
   // --- Register the training and test trees

   TTree *signal     = (TTree*)input_sig->Get("signal_tree");
   TTree *background = (TTree*)input_bkg->Get("background_tree");

   signal->SetBranchStatus("*",0);
   signal->SetBranchStatus("b_from_leptop_bdt*",1);
   signal->SetBranchStatus("b_from_hadtop_bdt*",1);
   signal->SetBranchStatus("hadTop_tlv_bdt*",1);
   signal->SetBranchStatus("w_from_hadtop_tlv_bdt*",1);
   signal->SetBranchStatus("dr_lepFromHiggs_bFromHadTop",1);
   signal->SetBranchStatus("dr_lepFromTop_bFromLepTop",1);
   signal->SetBranchStatus("dr_lepFromTop_bFromHadTop",1);
   signal->SetBranchStatus("dr_lepFromHiggs_bFromLepTop",1);

   background->SetBranchStatus("*",0);
   background->SetBranchStatus("b_from_leptop_bdt*",1);
   background->SetBranchStatus("b_from_hadtop_bdt*",1);
   background->SetBranchStatus("hadTop_tlv_bdt*",1);
   background->SetBranchStatus("w_from_hadtop_tlv_bdt*",1);
   background->SetBranchStatus("dr_lepFromHiggs_bFromHadTop",1);
   background->SetBranchStatus("dr_lepFromTop_bFromLepTop",1);
   background->SetBranchStatus("dr_lepFromTop_bFromHadTop",1);
   background->SetBranchStatus("dr_lepFromHiggs_bFromLepTop",1);
   
   
   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
   
   // You can add an arbitrary number of signal or background trees
   factory->AddSignalTree    ( signal,     signalWeight     );
   factory->AddBackgroundTree( background, backgroundWeight );
   
   // To give different trees for training and testing, do as follows:
   //    factory->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
   //    factory->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );
   
   // Use the following code instead of the above two or four lines to add signal and background
   // training and test events "by hand"
   // NOTE that in this case one should not give expressions (such as "var1+var2") in the input
   //      variable definition, but simply compute the expression before adding the event
   //
   //     // --- begin ----------------------------------------------------------
   //     std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
   //     Float_t  treevars[4], weight;
   //     
   //     // Signal
   //     for (UInt_t ivar=0; ivar<4; ivar++) signal->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   //     for (UInt_t i=0; i<signal->GetEntries(); i++) {
   //        signal->GetEntry(i);
   //        for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //        // add training and test events; here: first half is training, second is testing
   //        // note that the weight can also be event-wise
   //        if (i < signal->GetEntries()/2.0) factory->AddSignalTrainingEvent( vars, signalWeight );
   //        else                              factory->AddSignalTestEvent    ( vars, signalWeight );
   //     }
   //   
   //     // Background (has event weights)
   //     background->SetBranchAddress( "weight", &weight );
   //     for (UInt_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   //     for (UInt_t i=0; i<background->GetEntries(); i++) {
   //        background->GetEntry(i);
   //        for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //        // add training and test events; here: first half is training, second is testing
   //        // note that the weight can also be event-wise
   //        if (i < background->GetEntries()/2) factory->AddBackgroundTrainingEvent( vars, backgroundWeight*weight );
   //        else                                factory->AddBackgroundTestEvent    ( vars, backgroundWeight*weight );
   //     }
         // --- end ------------------------------------------------------------
   //
   // --- end of tree registration 

   // Set individual event weights (the variables must exist in the original TTree)
   //    for signal    : factory->SetSignalWeightExpression    ("weight1*weight2");
   //    for background: factory->SetBackgroundWeightExpression("weight1*weight2");
   factory->SetBackgroundWeightExpression( "mcwgt" );

   // Apply additional cuts on the signal and background samples (can be different)
   // TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   // TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

   // TCut lep_wrong = "lep_from_leptop_bdt.obj.pt() != lep_from_leptop_reco_truth.obj.pt()";
   // TCut bjet_wrong = "b_from_leptop_bdt.obj.pt() != b_from_leptop_reco_truth.obj.pt() && b_from_hadtop_bdt.obj.pt() != b_from_hadtop_reco_truth.obj.pt()";
   TCut non_zero_leps = "lep_from_leptop_bdt.obj.pt()*lep_from_higgs_bdt.obj.pt()>0";
   TCut bTight; 
   
   if (input_string == "btight") bTight = "@bTight_jets.size() > 1";
   else if (input_string == "bloose") bTight = "@bTight_jets.size() < 2";
   else bTight = "";

   TCut mycuts = bTight && non_zero_leps;
   TCut mycutb = mycuts;

   // Tell the factory how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used 
   // for training, and the other half for testing:
   //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   // To also specify the number of testing events, use:
   //    factory->PrepareTrainingAndTestTree( mycut,
   //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
   
   if (input_string == "btight")
     {
       factory->PrepareTrainingAndTestTree( mycuts, mycutb,
					    "nTrain_Signal=13000:nTrain_Background=90000:SplitMode=Random:NormMode=NumEvents:!V" );//btight ss
     }
   else if (input_string == "bloose")
     {
       factory->PrepareTrainingAndTestTree( mycuts, mycutb,
					    "nTrain_Signal=19000:nTrain_Background=90000:SplitMode=Random:NormMode=NumEvents:!V" );//bloose ss        
     }
   else 
     {
       factory->PrepareTrainingAndTestTree( mycuts, mycutb,
					    "nTrain_Signal=34000:nTrain_Background=90000:SplitMode=Random:NormMode=NumEvents:!V" );//inclsuive ss
     }
   
   
   //"nTrain_Signal=110000:nTrain_Background=200000:SplitMode=Random:NormMode=NumEvents:!V" );//bloose gen-filter hybrid
   //"nTrain_Signal=60000:nTrain_Background=110000:SplitMode=Random:NormMode=NumEvents:!V" );//btight gen-filter hybrid
   //"nTrain_Signal=180000:nTrain_Background=180000:SplitMode=Random:NormMode=NumEvents:!V" );//inclus gen-filter hybrid

   //"nTrain_Signal=60000:nTrain_Background=70000:nTest_Background=70000:SplitMode=Random:NormMode=NumEvents:!V" );//btight gen-filter
   //"nTrain_Signal=110000:nTrain_Background=150000:nTest_Background=150000:SplitMode=Random:NormMode=NumEvents:!V" );//bloose gen-filter
   //"nTrain_Signal=180000:nTrain_Background=150000:nTest_Background=150000:SplitMode=Random:NormMode=NumEvents:!V" );//inclus gen-filter
   

   //"nTrain_Signal=70000:nTrain_Background=180000:SplitMode=Random:NormMode=NumEvents:!V" );//inclsuive os 
   //"nTrain_Signal=28000:nTrain_Background=110000:SplitMode=Random:NormMode=NumEvents:!V" );//btight os
   //"nTrain_Signal=41000:nTrain_Background=200000:SplitMode=Random:NormMode=NumEvents:!V" );//bloose os
   




   // ---- Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=1000:MinNodeSize=4.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=8" );


   // --------------------------------------------------------------------------------------------------

   // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

   // ---- STILL EXPERIMENTAL and only implemented for BDT's ! 
   // factory->OptimizeAllMethods("SigEffAt001","Scan");
   // factory->OptimizeAllMethods("ROCIntegral","FitGA");

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   return 0;
}

int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList; 
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(","); 
      methodList += regMethod;
   }
   return TMVAClassification_v1p7(methodList); 
}
