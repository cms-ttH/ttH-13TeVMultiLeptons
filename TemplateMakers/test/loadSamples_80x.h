///////////////////////////
////
//// Choose a sample: ttH, ttW, ttbar
////
///////////////////////////

TChain* loadFiles(TString sample, int start_file =0, int end_file=-1)
{
  
  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  TString pre_fix = "root://eoscms.cern.ch//eos/cms";
  TString post_fix = ".root";

  if (start_file == 0) start_file = 1;

  if (sample == "ttH-aMC@NLO")
    {
      TString base_dir = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125_aMC/160804_104730/0000/tree_test__";
      if (end_file == -1 || end_file == 0) end_file = 201;
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir+file_num+post_fix;
	  chain->Add(file_name);
	}
    }
  
  else if (sample == "ttH-powheg")
    {
      TString base_dir = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/ttHToNonbb_M125_13TeV_powheg_pythia8/crab_ttH125_powheg/160802_215451/0000/tree_test__";
      if (end_file == -1 || end_file == 0) end_file = 78;
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir+file_num+post_fix;
	  chain->Add(file_name);
	}
    }

  else if (sample == "ttbar-semiLep-powheg")
    {
      TString base_dir = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTToSemiLeptonic_13TeV-powheg/crab_TTJets_powheg/160804_104748/0000/tree_test__";
      if (end_file == -1 || end_file == 0) end_file = 167; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir+file_num+post_fix;
	  chain->Add(file_name);
	}      
    }

  else if (sample == "ttbar-semiLep-madgraph")
    {
      //tbar
      TString base_dir = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_SemiLep_tbar/160810_172311/0000/tree_test__";
      //      if (end_file == -1 || end_file == 0) 
      end_file = 24; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir+file_num+post_fix;
	  chain->Add(file_name);
	}            
      //tbar ext
      TString base_dir1 = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_SemiLep_tbar_ext/160810_172323/0000/tree_test__";
      //      if (end_file == -1 || end_file == 0) end_file = 100; //num input files
      end_file = 100; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir1+file_num+post_fix;
	  chain->Add(file_name);
	}            
      //t
      TString base_dir2 = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_SemiLep_t/160810_172334/0000/tree_test__";
      //      if (end_file == -1 || end_file == 0)
      end_file = 20; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir2+file_num+post_fix;
	  chain->Add(file_name);
	}            
      //t ext
      TString base_dir3 = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_SemiLep_t_ext/160810_172346/0000/tree_test__";
      //      if (end_file == -1 || end_file == 0)
      end_file = 93; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir3+file_num+post_fix;
	  chain->Add(file_name);
	}            
    }
  
  else if (sample == "ttbar-inclusive-madgraph")
    {
      TString base_dir3 = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_fully_inclusive/160707_121042/0000/tree_test__";
      if (end_file == -1 || end_file == 0) end_file = 22; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir3+file_num+post_fix;
	  chain->Add(file_name);
	}            
    }


  else if (sample == "ttV")
    {
      TString base_dir = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW_aMC/160704_215140/0000/tree_test__";
      //      if (end_file == -1 || end_file == 0) 
      end_file = 6; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir+file_num+post_fix;
	  chain->Add(file_name);
	}            

      TString base_dir1 = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTZ_aMC/160707_112754/0000/tree_test__";
      //      if (end_file == -1 || end_file == 0) 
      end_file = 8; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir1+file_num+post_fix;
	  chain->Add(file_name);
	}            

      

    }

  else if (sample == "DY_M10-50")
    {
      TString base_dir = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DY_M10-15_NLO/160802_215559/0000/tree_test__";
      if (end_file == -1 || end_file == 0) end_file = 63; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir+file_num+post_fix;
	  chain->Add(file_name);
	}            
    }

  else if (sample == "DY_M50")
    {
      TString base_dir = pre_fix + "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DY_M50_NLO/160802_215621/0000/tree_test__";
      if (end_file == -1 || end_file == 0) end_file = 62; //num input files
      for (int i=start_file; i <= end_file; i++)
	{
	  if (i > end_file) break;
	  TString file_num = std::to_string(i);
	  TString file_name = base_dir+file_num+post_fix;
	  chain->Add(file_name);
	}            
    }

  else
    {
      cout << "=================================" << endl;
      cout << "=================================" << endl;
      cout << "please specify valid sample name" << endl;
      cout << "=================================" << endl;
      cout << "=================================" << endl;
    }
  
  return chain;
}
