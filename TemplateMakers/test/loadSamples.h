#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TColor.h"

///////////////////////////
////
//// Choose a sample: ttH, ttW, ttbar
////
///////////////////////////

class FileLoader
{
 private:
  void loadFile(vector<TString> path_strs, int file_index)
  {
    

    TString pre_fix = "/hadoop/store/user/"; //FUSE method
    //    TString pre_fix = "root://deepthought.crc.nd.edu//store/user/"; //XROOTD method

    int file_count = 0;
    for (const auto & path_str : path_strs)
      {
	TString base_dir = pre_fix + path_str;    
	TSystemDirectory dir(base_dir, base_dir);
	TList *files = dir.GetListOfFiles();
	if (!files) continue; 
	TSystemFile *sys_file;
	TString fname;
	TIter next(files);
	while ((sys_file=(TSystemFile*)next()))
	  {
	    
	    fname = base_dir + sys_file->GetName();
	    if (!sys_file->IsDirectory() && fname.EndsWith(".root")) 
	      {
		
		if (file_index == -1 || file_count == file_index)
		  {
		    chain->Add(fname);
		    cout << "loading file: " << fname << endl;      
		  }
		
		if ( file_index == -1 || file_index == 0)
		  {
		    TFile* file = TFile::Open(fname,"READONLY");
		    if ( file )
		      {
			TH1D* hist = (TH1D*)file->Get("OSTwoLepAna/numInitialWeightedMCevents");
			hist_sum->Add(hist);
			file->Close();
		      }	
		    delete file;
		  }
		
		file_count +=1;
	      }
	  }
      }
    
    if (file_index >= file_count)
      {
	//NOTE: the file_index is 0-indexed!
	cout << "ERROR: Requesting more files than are available ("<< file_count <<") Check inputs and try again." << endl;
	throw "Requesting more files than are available!! Check inputs and try again.";
	//throw std::exception();
	//exit (EXIT_FAILURE);
      }
  }
public:
  FileLoader(void){};//default constructor

  //public members
  TChain *chain;
  TH1D* hist_sum;
  
  void loadFiles(TString sample, int file_index=-1)
    {
      chain = new TChain("OSTwoLepAna/summaryTree");
      hist_sum = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);      
 
      // lobster_test_nov18_ICHEP_attempt2 == old
      // lobster_test_feb2_ICHEP == new
     
      if (sample == "tth_powheg")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/tth_nonbb_powheg_/"} , file_index); //8
      	}

      else if (sample == "tth_aMC_new")
	{
	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/tth_nonbb_aMCatNLO_/"} , file_index); //21
	}
      
      else if (sample == "tth_aMC_old")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_feb2_ICHEP/tth_nonbb_aMCatNLO_/"); //37
      	  loadFile( sample_vec , file_index);
      	}
      
      else if (sample == "ttbar_semiLep_powheg")
      	{
      	  loadFile( {"muell149/lobster_test_feb2_ICHEP/ttbar_semilep_powheg/"} , file_index);
      	}

      else if (sample == "ttbar_diLep_mg")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_feb2_ICHEP/ttbar_dilep_mg/");
      	  sample_vec.push_back("muell149/lobster_test_feb2_ICHEP/ttbar_dilep_mg_extn/");
      	  loadFile( sample_vec , file_index);
      	}

      else if (sample == "ttbar_semiLep_madgraph")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_feb17_Moriond17_v0/ttbar_semilep_fromTop_mg/"); //9
      	  sample_vec.push_back("muell149/lobster_test_feb17_Moriond17_v0/ttbar_semilep_fromTop_mg_extn/"); //35
      	  sample_vec.push_back("muell149/lobster_test_feb17_Moriond17_v0/ttbar_semilep_fromAntitop_mg/"); //9
      	  sample_vec.push_back("muell149/lobster_test_feb17_Moriond17_v0/ttbar_semilep_fromAntitop_mg_extn/"); //33
      	  loadFile( sample_vec, file_index);
      	}
      
      else if (sample == "ttbar_diLep_powheg_tranche3")
      	{
      	  loadFile( {"muell149/lobster_test__KevinTranche3_foreign/ttbar_DL_tranche3/"} , file_index);
      	}
      
      else if (sample == "ttbar_genFilter")
      	{
      	  loadFile( {"muell149/lobster_test__genFilterV1/ttbar_semiLep_genFilter/"}, file_index);
      	  /* loadFile( {"muell149/lobster_test__genFilterV0_and_TTLL/ttbar_semiLep_genFilter/"}, file_index); */
      	}
      
      else if (sample == "ttW_aMCatNLO")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_march22_Moriond17_MC/ttW/"); //6
      	  sample_vec.push_back("muell149/lobster_test_march22_Moriond17_MC/ttW_extn/"); //9
	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "ttZ_aMCatNLO")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_march22_Moriond17_MC/ttZ/"); //7
	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "ttGammaStar")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_march22_Moriond17_MC/ttZ_M1_10/"); //7
	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "wGamma")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_march22_Moriond17_MC/wPlusJets/"); //1
	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "zGamma")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_march22_Moriond17_MC/zPlusJets/"); //35
	  loadFile( sample_vec, file_index);
      	}
      
      else if ( sample == "WW_diboson")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/WW_2l2nu/"}, file_index); //5
      	}

      else if ( sample == "ZZ_diboson")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/ZZ_to4l/"}, file_index);//19
      	}
      else if ( sample == "WZ_diboson")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/WZ_to3lnu/"}, file_index);//5
      	}

      else if (sample == "convs_sT")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_march22_Moriond17_MC/convs_sT/"); //1
      	  sample_vec.push_back("muell149/lobster_test_march22_Moriond17_MC/convs_sT_extn/"); //1
      	  loadFile( sample_vec, file_index);
      	}
      else if ( sample == "convs_ttbar")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/convs_ttbar/"}, file_index); //4
      	}
      else if ( sample == "tttt")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/tttt/"}, file_index); //1
      	}
      else if ( sample == "tZq")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/tZq/"}, file_index); //77
      	}
      else if ( sample == "WWqq_rares")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/WWqq_rares/"}, file_index); //1
      	}
      else if ( sample == "WW_doublescatering_rares")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/WW_DoubleScattering_rares/"}, file_index); //2
      	}
      else if ( sample == "WWZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/WWZ_rares/"}, file_index); //1
      	}
      else if ( sample == "WWW_rares")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/WWW_rares/"}, file_index); //1
      	}
      else if ( sample == "WZZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/WZZ_rares/"}, file_index); //1
      	}
      else if ( sample == "ZZZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_march22_Moriond17_MC/ZZZ_rares/"}, file_index); //1
      	}


      else if (sample == "tth_powheg_genFilter")
      	{
	  loadFile( {"muell149/lobster_test__marchGenFilterStudies/tth_nonbb_powheg_v1_part2_genFilter/"}, file_index); //44
      	}
      else if (sample == "tth_powheg_noGenFilter")
	{
	  loadFile( {"muell149/lobster_test__marchGenFilterStudies_noGenFilter/tth_nonbb_powheg/"}, file_index); //30
	}
      else if (sample == "tth_powheg_genFilter_looseLepJetClean")
      	{
	  loadFile( {"muell149/lobster_test__nov18_genFilter_altJetClean/tth_nonbb_powheg/"}, file_index); //27
      	}
      

      else if (sample == "ttbar_semiLep_jetClean_test")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test__nov18_genFilter_altJetClean/ttbar_semilep_v6_part6/");
      	  sample_vec.push_back("muell149/lobster_test__nov18_genFilter_altJetClean/ttbar_semilep_v6_parts4_5/");
      	  sample_vec.push_back("muell149/lobster_test__nov18_genFilter_altJetClean/ttbar_semilep/");
      	  loadFile( sample_vec, file_index);
      	}
      else if (sample == "ttw_jetClean_test")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test__nov18_genFilter_altJetClean/ttw_mg5/");
      	  sample_vec.push_back("muell149/lobster_test__nov18_genFilter_altJetClean/ttw_mg5_part2/");
      	  loadFile( sample_vec, file_index);
      	}


      else if (sample == "data")
	{
      	  vector<TString> sample_vec; //286 TOTAL

      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleMu2016B/"); //20
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleMu2016C/"); //12
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleMu2016D/"); //13
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleMu2016E/"); //13
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleMu2016F/"); //
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleMu2016G/"); //
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleMu2016H_pr2/"); //
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleMu2016H_pr3/"); //

      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleMu2016B/"); //11
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleMu2016C/"); //5
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleMu2016D/"); //7
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleMu2016E/"); //7
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleMu2016F/"); //6
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleMu2016G/"); //13
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleMu2016H_pr2/"); //15
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleMu2016H_pr3/"); //15

      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/MuonEg2016B/"); //2
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/MuonEg2016C/"); //1
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/MuonEg2016D/"); //1
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/MuonEg2016E/"); //1
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/MuonEg2016F/"); //1
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/MuonEg2016G/"); //2
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/MuonEg2016H_pr2/"); //2
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/MuonEg2016H_pr3/"); //2

      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleEg2016B/"); //6
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleEg2016C/"); //3
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleEg2016D/"); //4
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleEg2016E/"); //4
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleEg2016F/"); //3
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleEg2016G/"); //7
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleEg2016H_pr2/"); //7
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/doubleEg2016H_pr3/"); //7

      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleEle2016B/"); //6
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleEle2016C/"); //3
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleEle2016D/"); //4
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleEle2016E/"); //4
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleEle2016F/"); //3
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleEle2016G/"); //7
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleEle2016H_pr2/"); //7
      	  sample_vec.push_back("muell149/lobster_test__Moriond17_data_march22_v0/singleEle2016H_pr3/"); //7
      	  loadFile( sample_vec, file_index);
	} 


      else
	{
	  cout << "=================================" << endl;
	  cout << "=================================" << endl;
	  cout << "please specify valid sample name" << endl;
	  cout << "=================================" << endl;
	  cout << "=================================" << endl;
	}
      
      cout << "Weighted number of events in sample " << sample << " = " << setprecision(10) << hist_sum->GetBinContent(1) << endl;
      //  hist_sum->Draw();
      
    }

  virtual ~FileLoader(){}
};
 
TString getSelectionFile(TString sample_name)
{
  TString prefix = "/scratch365/cmuelle2/selection_trees/march14_moriond17/";
  TString input_file_name = prefix;

  if (sample_name == "tth_powheg")                   input_file_name += "tth_powheg_2lss_selection.root";
  else if (sample_name == "ttW_aMCatNLO")      input_file_name += "ttW_aMCatNLO_2lss_selection.root";
  else if (sample_name == "ttZ_aMCatNLO")      input_file_name += "ttZ_aMCatNLO_2lss_selection.root";
  else if (sample_name == "ttGammaStar")      input_file_name += "ttGammaStar_2lss_selection.root";
  else if (sample_name == "wGamma")      input_file_name += "wGamma_2lss_selection.root";
  else if (sample_name == "zGamma")      input_file_name += "zGamma_2lss_selection.root";
  else if (sample_name == "convs_sT")      input_file_name += "convs_sT_2lss_selection.root";
  else if (sample_name == "convs_ttbar")      input_file_name += "convs_ttbar_2lss_selection.root";
  else if (sample_name == "WWqq_rares")      input_file_name += "WWqq_rares_2lss_selection.root";
  else if (sample_name == "WW_doublescatering_rares")      input_file_name += "WW_doublescatering_rares_2lss_selection.root";
  else if (sample_name == "WWW_rares")      input_file_name += "WWW_rares_2lss_selection.root";
  else if (sample_name == "WWZ_rares")      input_file_name += "WWZ_rares_2lss_selection.root";
  else if (sample_name == "WZZ_rares")      input_file_name += "WZZ_rares_2lss_selection.root";
  else if (sample_name == "ZZZ_rares")      input_file_name += "ZZZ_rares_2lss_selection.root";
  else if (sample_name == "tZq")      input_file_name += "tZq_2lss_selection.root";
  else if (sample_name == "tttt")      input_file_name += "tttt_2lss_selection.root";
  else if (sample_name == "WW_diboson")      input_file_name += "WW_diboson_2lss_selection.root";
  else if (sample_name == "ZZ_diboson")      input_file_name += "ZZ_diboson_2lss_selection.root";
  else if (sample_name == "WZ_diboson")      input_file_name += "WZ_diboson_2lss_selection.root";
  else if (sample_name == "fakes")      input_file_name = "fakes_2lss_selection.root";
  else if (sample_name == "flips")      input_file_name = "flips_2lss_selection.root";
  else if (sample_name == "data")      input_file_name = "data_2lss_selection.root";
  else                                 input_file_name = "data_2lss_selection.root";


  /* else if (sample_name == "tth_powheg_old_training")     input_file_name += "tth_powheg_old_2lss_training.root"; */
  /* else if (sample_name == "ttbar_semiLep_madgraph")      input_file_name += "ttbar_semiLep_madgraph_2lss_extraction.root"; */
  /* else if (sample_name == "tth_aMC")                 input_file_name += "tth_aMC_new_2lss_extraction.root"; */
  /* else if (sample_name == "ttbar_semiLep_powheg")        input_file_name += "ttbar_semiLep_powheg_2lss_selection.root"; */
  /* else if (sample_name == "ttbar_diLep_mg")      input_file_name += "ttbar_diLep_mg_2lss_selection.root"; */
  /* else if (sample_name == "ttbar_diLep_powheg")      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/ttbar_diLep_powheg_tranche3_2lss.root"; */
  /* else if (sample_name == "ttbar_semiLep_genFilterTraining")      input_file_name = "/scratch365/cmuelle2/genFilter_trees/ttbar_semiLep_jetClean_test_genFilterTraining_2lss.root"; */
  /* else if (sample_name == "tth_powheg_genFilterTraining")      input_file_name = "/scratch365/cmuelle2/genFilter_trees/tth_powheg_jetClean_test_genFilterTraining_2lss.root"; */
  /* else if (sample_name == "ttw_genFilterTraining")      input_file_name = "/scratch365/cmuelle2/genFilter_trees/ttw_jetClean_test_genFilterTraining_2lss.root"; */
  /* else if (sample_name == "tth_sigExtr_training_2lss")      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training2_tests/tth_powheg_old_relaxed_training_2lss.root"; */
  /* else if (sample_name == "ttbar_sigExtr_training_2lss")      input_file_name = "/scratch365/cmuelle2/selection_trees/jan25_ichep_trees/ttbar_semiLep_madgraph_2lss_trainingSelection.root"; */

  /* //temporary */
  /* else if (sample_name == "tth_qgid")      input_file_name = "/scratch365/cmuelle2/selection_trees/feb6_ichep_trees/tth_aMC_old_2lss_selection.root"; */
  /* else if (sample_name == "ttw_qgid")      input_file_name = "/scratch365/cmuelle2/selection_trees/feb6_ichep_trees/ttW_aMCatNLO_2lss_selection.root"; */
  /* else if (sample_name == "ttz_qgid")      input_file_name = "/scratch365/cmuelle2/selection_trees/feb6_ichep_trees/ttZ_aMCatNLO_2lss_selection.root"; */
  /* else                                                  input_file_name = "/scratch365/cmuelle2/selection_trees/nov22_ICHEP_trees/tth_aMC_old_2lss_selection.root"; */
  //  else if (sample_name == "ttbar_sigExtr_training_2lss")      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training2_tests/ttbar_semiLep_madgraph_relaxed_training_2lss.root";

  return input_file_name;
}

class Sample
{
private:
public:
 Sample(TString sample_name_="name"):
  sample_name(sample_name_)
  {
    TString prefix = "/scratch365/cmuelle2/selection_trees/may10_m17/";
    TString input_file_name = prefix;
    
    if (sample_name == "ttH")
      {
	input_file_name += "tth_powheg.root";
	legend_name = "ttH";
	fill_color = kOrange+10;
	fill_style = 1001;
	xsec = 0.5071*0.418;
      }
    else if (sample_name == "ttW")
      {
	input_file_name += "ttW_aMCatNLO.root";
	legend_name = "TTW";
	fill_color = kGreen-5;
	fill_style = 1001;
	xsec = 0.196;
      }
    else if (sample_name == "ttZ")
      {
	input_file_name += "ttZ_aMCatNLO.root";
	legend_name = "TTZ";
	fill_color = kSpring+2;
	fill_style = 1001;
	xsec = 0.2728;
      }
    else if (sample_name == "ttZ_M1to10")
      {
	input_file_name += "ttZ_XXX.root";
	legend_name = "TTZ";
	fill_color = kSpring+2;
	fill_style = 1001;
	xsec = 0.0493;
      }
    else if (sample_name == "TTGJets")
      {
	input_file_name += "cons_ttbar.root";
	legend_name = "Convs";
	fill_color = kOrange;
	fill_style = 1001;
	xsec = 3.70;
      }
    else if (sample_name == "TGJets")
      {
	input_file_name += "convs_sT.root";
	legend_name = "Convs";
	fill_color = kOrange;
	fill_style = 1001;
	xsec = 2.97;
      }
    else if (sample_name == "WGToLNuG")
      {
	input_file_name += "wGamma.root";
	legend_name = "Convs";
	fill_color = kOrange;
	fill_style = 1001;
	xsec = 585.8;
      }
    else if (sample_name == "ZGTo2LG")
      {
	input_file_name += "zGamma.root";
	legend_name = "Convs";
	fill_color = kOrange;
	fill_style = 1001;
	xsec = 131.3;
      }
    else if (sample_name == "WWqq_rares")
      {
	input_file_name += "WWqq_rares.root";
	legend_name = "Rares";
	fill_color = kOrange-3;
	fill_style = 1001;
	xsec = 0.03711;
      }
    else if (sample_name == "WW_doublescatering_rares")
      {
	input_file_name += "WW_doublescatering_rares.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 0.1729;
      }
    else if (sample_name == "WWW_rares")
      {
	input_file_name += "WWW_rares.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 0.2086;
      }
    else if (sample_name == "WWZ_rares")
      {
	input_file_name += "WWZ_rares.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 0.1651;
      }
    else if (sample_name == "WZZ_rares")
      {
	input_file_name += "WZZ_rares.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 0.05565;
      }
    else if (sample_name == "ZZZ_rares")
      {
	input_file_name += "ZZZ_rares.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 0.01398;
      }
    else if (sample_name == "tZq")
      {
	input_file_name += "tZq.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 0.0758;
      }
    else if (sample_name == "tttt")
      {
	input_file_name += "tttt.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 0.009103;
      }
    else if (sample_name == "WW_diboson") 
      {
	//this might not be used.....
	input_file_name += "WW_diboson.root";
	legend_name = "Rares";
	fill_color = kOrange+10;
	fill_style = 1001;
	xsec = 10.481;
      }
    else if (sample_name == "ZZ_diboson")
      {
	input_file_name += "ZZ_diboson.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 1.256;
      }
    else if (sample_name == "WZ_diboson")
      {
	input_file_name += "WZ_diboson.root";
	legend_name = "WZ";
	fill_color = kViolet-4;
	fill_style = 1001;
	xsec = 4.429;
      }
    else if (sample_name == "fakes")
      {
	input_file_name += "fakes.root";
	legend_name = "Fakes";
	fill_color = kBlack;
	fill_style = 3345;
	xsec = 1.;
      }
    else if (sample_name == "flips")
      {
	input_file_name += "flips.root";
	legend_name = "Flips";
	fill_color = kBlack;
	fill_style = 3006;
	xsec = 1.;
      }
    else if (sample_name == "data")
      {
	input_file_name += "data.root";
	legend_name = "Data";
	fill_color = kBlack;
	fill_style = 3005;
	xsec = 1.;
      }
    else
      {
	input_file_name = "data.root";
	legend_name = "TEST";
	fill_color = kBlack;
	fill_style = 1001;
	xsec = 1.;
      }
    
    file_name = input_file_name;
    TFile* input_file_ = new TFile(input_file_name,"READONLY");
    tree = (TTree*)input_file_->Get("ss2l_tree");
    
    if (sample_name != "data" && sample_name != "fakes" && sample_name != "flips" )
      {
	double integrated_lumi = 35900.; //integrated lumi in pb
	TH1D* sum_hist = (TH1D*)input_file_->Get("numInitialWeightedMCevents");
	double total_events = sum_hist->GetBinContent(1);
	xsec = xsec * integrated_lumi / total_events; //scale the xsec to #of events
      }

  } //default constructor

  TTree* tree;
  TString sample_name;
  TString legend_name;
  int fill_color;
  int fill_style;
  double xsec; //13 TeV xsec in pb

  virtual ~Sample(){}
};

