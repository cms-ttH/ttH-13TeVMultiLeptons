#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TString.h"

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
	if (files) 
	  {
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

		    if ( file_index == -1 || file_index == 0 )
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
  FileLoader(TString sample, int file_index=-1)
    {
      chain = new TChain("OSTwoLepAna/summaryTree");
      hist_sum = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);      
      
      if (sample == "tth_powheg_new")
	{
	  loadFile( {"muell149/lobster_test__v0/tth_nonbb_powheg_new/"} , file_index);
	}
      
      else if (sample == "tth_powheg_old")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/tth_nonbb_powheg_/"} , file_index);
      	}
      
      else if (sample == "tth_aMC_old")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_nov18_ICHEP_attempt2/tth_nonbb_aMCatNLO_/");
      	  sample_vec.push_back("muell149/lobster_test_nov18_ICHEP_attempt2/tth_nonbb_aMCatNLOextn_/");
      	  loadFile( sample_vec , file_index);
      	}
      
      else if (sample == "ttbar_semiLep_powheg")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/ttbar_semilep_powheg/"} , file_index);
      	}

      else if (sample == "ttbar_diLep_mg")
      	{

      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_nov18_ICHEP_attempt2/ttbar_dilep_mg/");
      	  sample_vec.push_back("muell149/lobster_test_nov18_ICHEP_attempt2/ttbar_dilep_mg_extn/");
      	  loadFile( sample_vec , file_index);
      	}

      else if (sample == "ttbar_semiLep_madgraph")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test__v0/ttbar_semilep_fromTop_mg/");
      	  sample_vec.push_back("muell149/lobster_test__v0/ttbar_semilep_fromTop_mg_extn/");
      	  sample_vec.push_back("muell149/lobster_test__v0/ttbar_semilep_fromAntitop_mg/");
      	  sample_vec.push_back("muell149/lobster_test__v0/ttbar_semilep_fromAntitop_mg_extn/");
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
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/ttW/"}, file_index);
      	}

      else if (sample == "ttZ_aMCatNLO")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/ttZ/"}, file_index);
      	}

      else if (sample == "ttGammaStar")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/ttll_m10/"}, file_index);
      	}

      else if ( sample == "WW_diboson")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/WW_2l2nu/"}, file_index);
      	}

      else if ( sample == "ZZ_diboson")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/ZZ_to4l/"}, file_index);
      	}
      else if ( sample == "WZ_diboson")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/WZ_to3lnu/"}, file_index);
      	}
      else if ( sample == "tttt")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/tttt/"}, file_index);
      	}
      else if ( sample == "tZq")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/tZq/"}, file_index);
      	}
      else if ( sample == "WWqq_rares")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/WWqq_rares/"}, file_index);
      	}
      else if ( sample == "WW_doublescatering_rares")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/WW_DoubleScattering_rares/"}, file_index);
      	}
      else if ( sample == "WWZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/WWZ_rares/"}, file_index);
      	}
      else if ( sample == "WZZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/WZZ_rares/"}, file_index);
      	}
      else if ( sample == "ZZZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_nov18_ICHEP_attempt2/ZZZ_rares/"}, file_index);
      	}
      else if (sample == "tth_powheg_jetClean_test")
      	{
	  loadFile( {"muell149/lobster_test__nov18_genFilter_altJetClean/tth_nonbb_powheg/"}, file_index);
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
    }//default constructor

  //public members
  TChain *chain;
  TH1D* hist_sum;
  
  virtual ~FileLoader(){}
};
 
TString getSelectionFile(TString sample_name)
{
  TString prefix = "/scratch365/cmuelle2/selection_trees/nov22_ICHEP_trees/";
  TString input_file_name = prefix;

  if (sample_name == "tth_powheg_old")                   input_file_name = "/scratch365/cmuelle2/selection_trees/nov22_ICHEP_trees/tth_powheg_old_2lss_selection.root";
  else if (sample_name == "tth_powheg_old_training")     input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training2_tests/tth_powheg_old_relaxed_training_2lss.root";
  else if (sample_name == "ttbar_semiLep_madgraph")      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttbar-semiLep-madgraph_relaxed_2lss.root";
  else if (sample_name == "tth_aMC_old")                 input_file_name += "tth_aMC_old_2lss_selection.root";
  else if (sample_name == "ttbar_semiLep_powheg")        input_file_name += "ttbar_semiLep_powheg_2lss_selection.root";
  else if (sample_name == "ttW_aMCatNLO")      input_file_name += "ttW_aMCatNLO_2lss_selection.root";
  else if (sample_name == "ttZ_aMCatNLO")      input_file_name += "ttZ_aMCatNLO_2lss_selection.root";
  else if (sample_name == "ttGammaStar")      input_file_name += "ttGammaStar_2lss_selection.root";
  else if (sample_name == "ttbar_diLep_mg")      input_file_name += "ttbar_diLep_mg_2lss_selection.root";
  else if (sample_name == "ttbar_diLep_powheg")      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/ttbar_diLep_powheg_tranche3_2lss.root";
  else if (sample_name == "WW_diboson")      input_file_name += "WW_diboson_2lss_selection.root";
  else if (sample_name == "ZZ_diboson")      input_file_name += "ZZ_diboson_2lss_selection.root";
  else if (sample_name == "WZ_diboson")      input_file_name += "WZ_diboson_2lss_selection.root";
  else if (sample_name == "tttt")      input_file_name += "tttt_2lss_selection.root";
  else if (sample_name == "tZq")      input_file_name += "tZq_2lss_selection.root";
  else if (sample_name == "WWqq_rares")      input_file_name += "WWqq_rares_2lss_selection.root";
  else if (sample_name == "WW_doublescatering_rares")      input_file_name += "WW_doublescatering_rares_2lss_selection.root";
  else if (sample_name == "WWZ_rares")      input_file_name += "WWZ_rares_2lss_selection.root";
  else if (sample_name == "WZZ_rares")      input_file_name += "WZZ_rares_2lss_selection.root";
  else if (sample_name == "ZZZ_rares")      input_file_name += "ZZZ_rares_2lss_selection.root";
  else if (sample_name == "ttbar_semiLep_genFilterTraining")      input_file_name = "/scratch365/cmuelle2/genFilter_trees/ttbar_semiLep_jetClean_test_genFilterTraining_2lss.root";
  else if (sample_name == "tth_powheg_genFilterTraining")      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov22_genFilterTrainingSelection_trees/tth_powheg_jetClean_test_recoBdt_2lss.root";
  else if (sample_name == "ttw_genFilterTraining")      input_file_name = "/scratch365/cmuelle2/genFilter_trees/ttw_jetClean_test_genFilterTraining_2lss.root";
  else if (sample_name == "tth_training_2lssos")      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training2_tests/tth_powheg_old_relaxed_training_2lss.root";
  else if (sample_name == "ttbar_training_2lss")      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training2_tests/ttbar_semiLep_madgraph_relaxed_training_2lss.root";
  else                                                  input_file_name = "/scratch365/cmuelle2/selection_trees/nov22_ICHEP_trees/tth_aMC_old_2lss_selection.root";

  return input_file_name;
}
