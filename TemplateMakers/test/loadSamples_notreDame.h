///////////////////////////
////
//// Choose a sample: ttH, ttW, ttbar
////
///////////////////////////

class FileLoader
{
 private:

  void loadFile(TString path_str, vector<string> samples)
  {
    TString pre_fix = "/hadoop/store/user/";
    //"muell149/lobster_test__v0/";
    TString base_dir = pre_fix + path_str;
    for (const auto & sample : samples)
      {
	TString file_name = base_dir+sample;
	chain->Add(file_name);
	
	cout << "loading file: " << file_name << endl;      
	//for hist
	TFile* file = TFile::Open(file_name,"READONLY");
	if ( file )
	  {
	    TH1D* hist = (TH1D*)file->Get("OSTwoLepAna/numInitialWeightedMCevents");
	    hist_sum->Add(hist);
	    file->Close();
	  }
      }
  }
  
 public:
  FileLoader(TString sample)
    {
      chain = new TChain("OSTwoLepAna/summaryTree");
      hist_sum = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);
      
      if (sample == "tth_powheg_new")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_12267.root");
	  sample_vec.push_back("output_tree_17460.root");
	  sample_vec.push_back("output_tree_25775.root");
	  sample_vec.push_back("output_tree_30443.root");
	  sample_vec.push_back("output_tree_30444.root");
	  sample_vec.push_back("output_tree_3099.root");
	  sample_vec.push_back("output_tree_3813.root");
	  sample_vec.push_back("output_tree_4112.root");
	  sample_vec.push_back("output_tree_5780.root");
	  sample_vec.push_back("output_tree_9244.root");
	  loadFile( "muell149/lobster_test__v0/tth_nonbb_powheg_new/", sample_vec);
	}
      
      else if (sample == "tth_powheg_old")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_11717.root");
	  sample_vec.push_back("output_tree_2033.root");
	  sample_vec.push_back("output_tree_2176.root");
	  sample_vec.push_back("output_tree_23903.root");
	  sample_vec.push_back("output_tree_3635.root");
	  sample_vec.push_back("output_tree_4113.root");
	  sample_vec.push_back("output_tree_5994.root");
	  sample_vec.push_back("output_tree_7247.root");
	  sample_vec.push_back("output_tree_9245.root");
	  loadFile( "muell149/lobster_test__v0/tth_nonbb_powheg_old/", sample_vec);
	}
      
      else if (sample == "tth_aMC_old")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_11085.root");
	  sample_vec.push_back("output_tree_12601.root");
	  sample_vec.push_back("output_tree_14062.root");
	  sample_vec.push_back("output_tree_16007.root");
	  sample_vec.push_back("output_tree_19337.root");
	  sample_vec.push_back("output_tree_23833.root");
	  sample_vec.push_back("output_tree_2388.root");
	  sample_vec.push_back("output_tree_2389.root");
	  sample_vec.push_back("output_tree_25327.root");
	  sample_vec.push_back("output_tree_26593.root");
	  sample_vec.push_back("output_tree_2775.root");
	  sample_vec.push_back("output_tree_28664.root");
	  sample_vec.push_back("output_tree_30461.root");
	  sample_vec.push_back("output_tree_3814.root");
	  sample_vec.push_back("output_tree_3815.root");
	  sample_vec.push_back("output_tree_4114.root");
	  sample_vec.push_back("output_tree_6164.root");
	  sample_vec.push_back("output_tree_6348.root");
	  sample_vec.push_back("output_tree_6640.root");
	  loadFile( "muell149/lobster_test__v0/tth_nonbb_aMCatNLO_old/", sample_vec);
	  
	  sample_vec.clear();
	  sample_vec.push_back("output_tree_2034.root");
	  sample_vec.push_back("output_tree_3100.root");
	  sample_vec.push_back("output_tree_4115.root");
	  sample_vec.push_back("output_tree_5109.root");
	  sample_vec.push_back("output_tree_6280.root");
	  sample_vec.push_back("output_tree_7248.root");
	  sample_vec.push_back("output_tree_9246.root");
	  sample_vec.push_back("output_tree_11086.root");
	  sample_vec.push_back("output_tree_10162.root");
	  sample_vec.push_back("output_tree_11719.root");
	  sample_vec.push_back("output_tree_11718.root");
	  sample_vec.push_back("output_tree_12966.root");
	  sample_vec.push_back("output_tree_14063.root");
	  sample_vec.push_back("output_tree_19338.root");
	  sample_vec.push_back("output_tree_17461.root");
	  sample_vec.push_back("output_tree_20179.root");
	  sample_vec.push_back("output_tree_24479.root");
	  sample_vec.push_back("output_tree_24828.root");
	  sample_vec.push_back("output_tree_25023.root");
	  sample_vec.push_back("output_tree_25459.root");
	  sample_vec.push_back("output_tree_26167.root");
	  sample_vec.push_back("output_tree_28681.root");
	  sample_vec.push_back("output_tree_30563.root");
	  loadFile( "muell149/lobster_test__v0/tth_nonbb_aMCatNLOextn_old/", sample_vec);
	}
      
      else if (sample == "ttbar_semiLep_powheg")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_6349.root");
	  sample_vec.push_back("output_tree_6941.root");
	  sample_vec.push_back("output_tree_7246.root");
	  sample_vec.push_back("output_tree_8019.root");
	  sample_vec.push_back("output_tree_11087.root");
	  sample_vec.push_back("output_tree_34433.root");
	  loadFile( "muell149/lobster_test__v0/ttbar_semilep_powheg/", sample_vec);	  
	}

      else if (sample == "ttbar_semiLep_madgraph")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_16009.root");
	  loadFile( "muell149/lobster_test__v0/ttbar_semilep_fromTop_mg/", sample_vec);
	  
	  sample_vec.clear();
	  sample_vec.push_back("output_tree_4684.root");
	  sample_vec.push_back("output_tree_6942.root");
	  sample_vec.push_back("output_tree_28688.root");
	  loadFile( "muell149/lobster_test__v0/ttbar_semilep_fromTop_mg_extn/", sample_vec);
	  
	  sample_vec.clear();
	  sample_vec.push_back("output_tree_22700.root");
	  loadFile( "muell149/lobster_test__v0/ttbar_semilep_fromAntitop_mg/", sample_vec);
	  
	  sample_vec.clear();
	  sample_vec.push_back("output_tree_9247.root");
	  sample_vec.push_back("output_tree_7058.root");
	  sample_vec.push_back("output_tree_34431.root");
	  sample_vec.push_back("output_tree_34432.root");
	  loadFile( "muell149/lobster_test__v0/ttbar_semilep_fromAntitop_mg_extn/", sample_vec);
	}
      
      else if (sample == "ttbar_diLep_powheg_tranche3")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_653.root");
	  sample_vec.push_back("output_tree_918.root");
	  sample_vec.push_back("output_tree_1649.root");
	  sample_vec.push_back("output_tree_2135.root");
	  sample_vec.push_back("output_tree_1937.root");
	  sample_vec.push_back("output_tree_1839.root");
	  sample_vec.push_back("output_tree_1323.root");
	  sample_vec.push_back("output_tree_2434.root");
	  sample_vec.push_back("output_tree_2751.root");
	  sample_vec.push_back("output_tree_3757.root");
	  sample_vec.push_back("output_tree_4919.root");
	  sample_vec.push_back("output_tree_3772.root");
	  sample_vec.push_back("output_tree_4068.root");
	  sample_vec.push_back("output_tree_4915.root");
	  sample_vec.push_back("output_tree_4916.root");
	  sample_vec.push_back("output_tree_4918.root");
	  sample_vec.push_back("output_tree_4917.root");
	  sample_vec.push_back("output_tree_4920.root");
	  sample_vec.push_back("output_tree_5774.root");
	  sample_vec.push_back("output_tree_5772.root");
	  sample_vec.push_back("output_tree_5775.root");
	  sample_vec.push_back("output_tree_5773.root");
	  sample_vec.push_back("output_tree_6502.root");
	  sample_vec.push_back("output_tree_6503.root");
	  sample_vec.push_back("output_tree_9950.root");
	  sample_vec.push_back("output_tree_9984.root");
	  sample_vec.push_back("output_tree_10932.root");
	  sample_vec.push_back("output_tree_10934.root");
	  sample_vec.push_back("output_tree_11165.root");
	  sample_vec.push_back("output_tree_10956.root");
	  sample_vec.push_back("output_tree_11833.root");
	  sample_vec.push_back("output_tree_12042.root");
	  sample_vec.push_back("output_tree_12044.root");
	  sample_vec.push_back("output_tree_12045.root");
	  sample_vec.push_back("output_tree_12052.root");
	  sample_vec.push_back("output_tree_12088.root");
	  loadFile( "muell149/lobster_test__KevinTranche3_foreign/ttbar_DL_tranche3/", sample_vec);

	}
      
      else if (sample == "ttbar_allHad_madgraph")
	{
	  //stuff
	}
      
      else if (sample == "ttbar_inclusive_aMCatNLO")
	{      
	  //stuff
	}

      else if (sample == "ttbar_genFilter")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_273.root");
	  loadFile( "muell149/lobster_test__genFilterV0_and_TTLL/ttbar_semiLep_genFilter/", sample_vec);
	}
      
      else if (sample == "ttW_aMCatNLO")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_4116.root");
	  loadFile( "muell149/lobster_test__v0/ttW/", sample_vec);
	}

      else if (sample == "ttZ_aMCatNLO")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_16008.root");
	  loadFile( "muell149/lobster_test__v0/ttZ/", sample_vec);
	}

      else if (sample == "ttGammaStar")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_269.root");
	  loadFile( "muell149/lobster_test__genFilterV0_and_TTLL/ttll_m10/", sample_vec);
	}

      else if ( sample == "WW_diboson")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1071.root");
	  sample_vec.push_back("output_tree_1182.root");
	  sample_vec.push_back("output_tree_2201.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/WW_2l2nu/", sample_vec);
	}

      else if ( sample == "ZZ_diboson")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1057.root");
	  sample_vec.push_back("output_tree_1056.root");
	  sample_vec.push_back("output_tree_1062.root");
	  sample_vec.push_back("output_tree_1059.root");
	  sample_vec.push_back("output_tree_1061.root");
	  sample_vec.push_back("output_tree_1063.root");
	  sample_vec.push_back("output_tree_1065.root");
	  sample_vec.push_back("output_tree_1066.root");
	  sample_vec.push_back("output_tree_1069.root");
	  sample_vec.push_back("output_tree_1791.root");
	  sample_vec.push_back("output_tree_2204.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/ZZ_to4l/", sample_vec);
	}
      else if ( sample == "WZ_diboson")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1079.root");
	  sample_vec.push_back("output_tree_1064.root");
	  sample_vec.push_back("output_tree_1058.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/WZ_to3lnu/", sample_vec);
	}
      else if ( sample == "tttt")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1068.root");
	  sample_vec.push_back("output_tree_1995.root");
	  sample_vec.push_back("output_tree_2202.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/tttt/", sample_vec);
	}
      else if ( sample == "tqZ")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1060.root");
	  sample_vec.push_back("output_tree_1067.root");
	  sample_vec.push_back("output_tree_1070.root");
	  sample_vec.push_back("output_tree_1073.root");
	  sample_vec.push_back("output_tree_1078.root");
	  sample_vec.push_back("output_tree_1077.root");
	  sample_vec.push_back("output_tree_1285.root");
	  sample_vec.push_back("output_tree_1792.root");
	  sample_vec.push_back("output_tree_2097.root");
	  sample_vec.push_back("output_tree_2203.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/tZq/", sample_vec);
	}
      else if ( sample == "WWqq_rares")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1076.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/WWqq_rares/", sample_vec);
	}
      else if ( sample == "WW_doublescatering_rares")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1284.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/WW_DoubleScattering_rares/", sample_vec);
	}
      else if ( sample == "WWZ_rares")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1075.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/WWZ_rares/", sample_vec);
	}
      else if ( sample == "WZZ_rares")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1080.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/WZZ_rares/", sample_vec);
	}
      else if ( sample == "ZZZ_rares")
	{
	  vector<string> sample_vec;
	  sample_vec.push_back("output_tree_1072.root");
	  loadFile( "muell149/lobster_test__spring16_backgrounds/ZZZ_rares/", sample_vec);
	}
      else if (sample == "DY_M10_50")
	{
	  //stuff
	}
      
      else if (sample == "DY_M50")
	{
	  //stuff
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
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/tth_powheg_old_relaxed_2lss.root";
    }
  else if (sample_name == "ttbar_semiLep_madgraph")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttbar-semiLep-madgraph_relaxed_2lss.root";
    }
  else if (sample_name == "tth_aMC_old")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/tth_aMC_old_selection_2lss.root";
    }
  else if (sample_name == "ttbar_semiLep_powheg")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttbar_semiLep_powheg_selection_2lss.root";
    }
  else if (sample_name == "ttW_aMCatNLO")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttW_aMCatNLO_selection_2lss.root";
    }
  else if (sample_name == "ttZ_aMCatNLO")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttZ_aMCatNLO_selection_2lss.root";
    }

  else if (sample_name == "ttGammaStar")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttGammaStar_selection_tree_2lss.root";
    }

  else if (sample_name == "ttbar_genFilter_relaxed")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttbar_genFilter_Relaxedselection_tree_2lss.root";
    }

  else if (sample_name == "ttbar_genFilter")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttbar_genFilter_selection_tree_2lss.root";
    }

  else if (sample_name == "ttbar_diLep_madgraph")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ttbar_diLep_madgraph_selection_2lss.root";
    }
  else if (sample_name == "WW_diboson")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WW_diboson_selection_2lss.root";
    }
  else if (sample_name == "ZZ_diboson")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ZZ_diboson_selection_2lss.root";
    }
  else if (sample_name == "WZ_diboson")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WZ_diboson_selection_2lss.root";
    }
  else if (sample_name == "tttt")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/tttt_selection_2lss.root";
    }
  else if (sample_name == "tqZ")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/tqZ_selection_2lss.root";
    }
  else if (sample_name == "WWqq_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WWqq_rares_selection_2lss.root";
    }
  else if (sample_name == "WW_doublescatering_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WW_doublescatering_rares_selection_2lss.root";
    }
  else if (sample_name == "WWZ_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WWZ_rares_selection_2lss.root";
    }
  else if (sample_name == "WZZ_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/WZZ_rares_selection_2lss.root";
    }
  else if (sample_name == "ZZZ_rares")
    {
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/ZZZ_rares_selection_2lss.root";
    }
  else 
    {
      sample_name = "output";
      input_file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor_stageout/tth_aMC_old_selection_2lss.root";
    }

  return input_file_name;

}
