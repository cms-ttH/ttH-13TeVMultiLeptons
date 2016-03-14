///////////////////////////
////
//// Choose a sample: ttH, ttW, ttbar
////
///////////////////////////

TChain* loadFiles(TString sample)
{
  
  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  char filePath[512];
  TString file_path;

  if (sample == "ttH")
    {

      /* for (int i=1; i < 170; i++) */
      /* 	{ */
      /* 	  char filePath[512]; */
      /* 	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125_aMC/160219_093049/0000/tree_BDT2_orig_%d.root",i); */
      /* 	  chain->Add(filePath); */
      /* 	} */
      /* for (int i=1; i < 200; i++) */
      /* 	{ */
      /* 	  char filePath[512]; */
      /* 	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125_aMC_extn/160219_093101/0000/tree_BDT2_orig_%d.root",i); */
      /* 	  chain->Add(filePath); */
      /* 	} */
      for (int i=1; i < 83; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/ttHToNonbb_M125_13TeV_powheg_pythia8/crab_ttH125_powheg/160219_093036/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
    }
  else if (sample == "ttbar")
    {

      for (int i=1; i < 714; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTToSemiLeptonic_13TeV-powheg/crab_TTJets_powheg/160219_093217/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}

      for (int i=1; i < 104; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM3/160219_093153/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
      
      for (int i=1; i < 30; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM4/160219_093206/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
      
      for (int i=1; i < 106; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM1/160219_093129/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
      
      for (int i=1; i < 30; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM2/160219_093141/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
      
      for (int i=1; i < 80; i++)
	{
	  char filePath[512];
	  sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_ttbar_aMC/160219_093117/0000/tree_BDT2_orig_%d.root",i);
	  chain->Add(filePath);
	}
    }

  else if (sample == "ttW")
    {
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_1.root");
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_2.root");    
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_3.root");    
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_4.root");    
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_5.root");    
      chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_6.root");
    }
  else
    {
      cout << "please specify valid sample name" << endl;
    }
  
  return chain;
}
