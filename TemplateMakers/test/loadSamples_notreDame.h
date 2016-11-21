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
		    //for hist
		    TFile* file = TFile::Open(fname,"READONLY");
		    if ( file )
		      {
			TH1D* hist = (TH1D*)file->Get("OSTwoLepAna/numInitialWeightedMCevents");
			hist_sum->Add(hist);
			file->Close();
		      }	
		    delete file;
		    
		    file_count +=1;
		  }
	      }
	  }
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
      	  loadFile( {"muell149/lobster_test__v0/tth_nonbb_powheg_old/"} , file_index);
      	}
      
      else if (sample == "tth_aMC_old")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test__v0/tth_nonbb_aMCatNLO_old/");
      	  sample_vec.push_back("muell149/lobster_test__v0/tth_nonbb_aMCatNLOextn_old/");
	  
      	  loadFile( sample_vec , file_index);
      	}
      
      else if (sample == "ttbar_semiLep_powheg")
      	{
      	  loadFile( {"muell149/lobster_test__v0/ttbar_semilep_powheg/"} , file_index);
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
      	  loadFile( {"muell149/lobster_test__v0/ttW/"}, file_index);
      	}

      else if (sample == "ttZ_aMCatNLO")
      	{
      	  loadFile( {"muell149/lobster_test__v0/ttZ/"}, file_index);
      	}

      else if (sample == "ttGammaStar")
      	{
      	  loadFile( {"muell149/lobster_test__genFilterV0_and_TTLL/ttll_m10/"}, file_index);
      	}

      else if ( sample == "WW_diboson")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/WW_2l2nu/"}, file_index);
      	}

      else if ( sample == "ZZ_diboson")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/ZZ_to4l/"}, file_index);
      	}
      else if ( sample == "WZ_diboson")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/WZ_to3lnu/"}, file_index);
      	}
      else if ( sample == "tttt")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/tttt/"}, file_index);
      	}
      else if ( sample == "tqZ")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/tZq/"}, file_index);
      	}
      else if ( sample == "WWqq_rares")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/WWqq_rares/"}, file_index);
      	}
      else if ( sample == "WW_doublescatering_rares")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/WW_DoubleScattering_rares/"}, file_index);
      	}
      else if ( sample == "WWZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/WWZ_rares/"}, file_index);
      	}
      else if ( sample == "WZZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/WZZ_rares/"}, file_index);
      	}
      else if ( sample == "ZZZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test__spring16_backgrounds/ZZZ_rares/"}, file_index);
      	}
      else if (sample == "tth_powheg_jetClean_test")
      	{
	  loadFile( {"muell149/lobster_test__tranche3_genFilter_altJetClean_part2/tth_nonbb_genFilter_altJetClean/"}, file_index);
      	}
      else if (sample == "ttbar_semiLep_jetClean_test")
      	{
      	  loadFile( {"muell149/lobster_test__tranche3_genFilter_altJetClean_part2/ttbar_semilep_genFilter_altJetClean/"}, file_index);
      	}
      else if (sample == "ttw_jetClean_test")
      	{
      	  loadFile( {"muell149/lobster_test__tranche3_genFilter_altJetClean_part2/ttw_genFilter_altJetClean/"}, file_index);
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
  TString input_file_name="";

  if (sample_name == "tth_powheg_old")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/tth_aMC_old_2lss.root";
    }

  else if (sample_name == "tth_powheg_old_altJetClean")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor/tth_powheg_jetClean_test_recoBdt_2lss.root";
    }

  else if (sample_name == "tth_powheg_old_training")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training2_tests/tth_powheg_old_relaxed_training_2lss.root";
    }


  else if (sample_name == "ttbar_semiLep_madgraph")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttbar-semiLep-madgraph_relaxed_2lss.root";
    }
  else if (sample_name == "tth_aMC_old")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/tth_aMC_old_2lss.root";
    }
  else if (sample_name == "ttbar_semiLep_powheg")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/ttbar_semiLep_powheg_2lss.root";
    }
  else if (sample_name == "ttW_aMCatNLO")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/ttW_aMCatNLO_2lss.root";
    }
  else if (sample_name == "ttZ_aMCatNLO")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/ttZ_aMCatNLO_2lss.root";
    }

  else if (sample_name == "ttGammaStar")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttGammaStar_selection_tree_2lss.root";
    }

  else if (sample_name == "ttbar_genFilter_relaxed")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/genFilter_tests/ttbar_genFilter_relaxed_training_2lss_kevin_v6.root";
    }

  else if (sample_name == "ttbar_genFilter")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/genFilter_tests/ttbar_genFilter_2lss_kevin_v6.root";
    }

  else if (sample_name == "ttbar_diLep_madgraph")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttbar_diLep_madgraph_selection_2lss.root";
    }

  else if (sample_name == "ttbar_diLep_powheg")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/ttbar_diLep_powheg_tranche3_2lss.root";
    }
  else if (sample_name == "WW_diboson")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/WW_diboson_2lss.root";
    }
  else if (sample_name == "ZZ_diboson")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/ZZ_diboson_2lss.root";
    }
  else if (sample_name == "WZ_diboson")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/WZ_diboson_2lss.root";
    }
  else if (sample_name == "tttt")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/tttt_2lss.root";
    }
  else if (sample_name == "tqZ")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/tqZ_2lss.root";
    }
  else if (sample_name == "WWqq_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/WWqq_rares_2lss.root";
    }
  else if (sample_name == "WW_doublescatering_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/WW_doublescatering_rares_2lss.root";
    }
  else if (sample_name == "WWZ_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/WWZ_rares_2lss.root";
    }
  else if (sample_name == "WZZ_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/WZZ_rares_2lss.root";
    }
  else if (sample_name == "ZZZ_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/nov8_trees/ZZZ_rares_2lss.root";
    }
  else if (sample_name == "ttbar_semiLep_jetClean_test")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/genFilter_tests/ttbar_semiLep_jetClean_test_training_tree_2lss.root";
    }

  else if (sample_name == "ttbar_semiLep_bdtTraining")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training2_tests/ttbar_semiLep_madgraph_relaxed_training_2lss.root";
    }

  else 
    {
      sample_name = "output";
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/tth_aMC_old_selection_tree_2lss.root";
    }

  return input_file_name;

}
