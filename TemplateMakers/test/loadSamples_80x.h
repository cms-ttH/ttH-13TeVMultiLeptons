///////////////////////////
////
//// Choose a sample: ttH, ttW, ttbar
////
///////////////////////////

void loadFile(TChain* input_chain, TH1D* input_hist_, TString path_str, int start_file=1, int end_file=1)
{
  TString pre_fix = "root://eoscms.cern.ch//eos/cms";
  TString post_fix = ".root";
  TString base_dir = pre_fix + path_str + "tree_test__";
  for (int i=start_file; i <= end_file; i++)
    {
      if (i > end_file) break;
      TString file_num = std::to_string(i);
      TString file_name = base_dir+file_num+post_fix;
      input_chain->Add(file_name);

      cout << "loading file: " << i << " of "<< end_file << endl;      
      //for hist
      TFile* file = TFile::Open(file_name,"READONLY");
      if ( file )
	{
	  TH1D* hist = (TH1D*)file->Get("OSTwoLepAna/numInitialWeightedMCevents");
	  input_hist_->Add(hist);
	  file->Close();
	}
    }
}

TChain* loadFiles(TString sample, int start_file =0, int end_file=-1)
{
  
  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  TH1D* hist_sum = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);

  if (start_file == 0) start_file = 1;

  if (sample == "ttH-aMCatNLO")
    {
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125_aMC/160804_104730/0000/" ,1, 201);
    }
  
  else if (sample == "ttH-powheg")
    {
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/ttHToNonbb_M125_13TeV_powheg_pythia8/crab_ttH125_powheg/160802_215451/0000/" ,1, 78);
    }

  else if (sample == "ttbar-semiLep-powheg")
    {
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTToSemiLeptonic_13TeV-powheg/crab_TTJets_powheg/160804_104748/0000/" ,1, 167);
    }

  else if (sample == "ttbar-semiLep-madgraph")
    {
      //tbar
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_SemiLep_tbar/160810_172311/0000/" ,1, 24);
      //tbar ext
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_SemiLep_tbar_ext/160810_172323/0000/" ,1, 100);
      //t
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_SemiLep_t/160810_172334/0000/" ,1, 20);
      //t ext
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_SemiLep_t_ext/160810_172346/0000/" ,1, 93);
    }
  
  else if (sample == "ttbar-allHad-madgraph")
    {
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_MLM_fully_inclusive/160707_121042/0000/" ,1, 22);
    }

  else if (sample == "ttbar-inclusive-aMCatNLO")
    {      
       loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_ttbar_aMCatNLO_inclusive/160815_143425/0000/" ,1, 75);
    }
 
  else if (sample == "ttW-aMCatNLO")
    {
     loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW_aMC/160704_215140/0000/" ,1, 6);
    }

  else if (sample == "ttZ-aMCatNLO")
    {
     loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTZ_aMC/160707_112754/0000/" ,1, 8);
    }

  else if (sample == "DY_M10-50")
    {
     loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DY_M10-15_NLO/160802_215559/0000/" ,1, 63);
    }

  else if (sample == "DY_M50")
    {
      loadFile(chain, hist_sum, "/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DY_M50_NLO/160802_215621/0000/" ,1, 62);
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
  return chain;
}
