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
 
      if (sample == "tth_powheg")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/ttH_nonbb_powheg/"} , file_index); //8
      	}

      else if (sample == "tth_aMC")
	{
	  loadFile( {"muell149/lobster_test_may22_Moriond17/ttH_nonbb_mWcutfix/"} , file_index); //20
	}
      
      else if (sample == "ttW")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttW/"); //7
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttW_extn/"); //9
	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "ttZ")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttZ/");
	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "ttZ_M1to10")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttZ_M1to10/"); //7
	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "WGToLNuG")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/WGToLNuG/"); //1
      	  //sample_vec.push_back("muell149/lobster_test_may22_Moriond17/WGToLNuG_extn/"); //1
	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "ZGTo2LG")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ZGTo2LG/"); //35
	  loadFile( sample_vec, file_index);
      	}
     
      else if ( sample == "WW_2l2nu")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/WW_2l2nu/"}, file_index); //5
      	}
      else if ( sample == "ZZ_to4l")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/ZZ_to4l/"}, file_index);//18
      	}
      else if ( sample == "WZ_to3lnu")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/WZ_to3lnu/"}, file_index);//5
      	}
      else if ( sample == "tWll")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/tWll/"}, file_index);//1
      	}
      else if ( sample == "ST_sChan")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/ST_sChan/"}, file_index);//1
      	}
      else if ( sample == "ST_tW")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ST_tW_top/"); //4
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ST_tW_antitop/"); //4
      	  loadFile( sample_vec, file_index);
      	}
      else if ( sample == "ST_tChan_top")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/ST_tChan_top/"}, file_index);//5
      	}
      else if ( sample == "ST_tChan_antitop")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/ST_tChan_antitop/"}, file_index);//3
      	}
      else if ( sample == "ttjets_dilep")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttjets_dilep/"); //26
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttjets_dilep_extn/"); //101
      	  loadFile( sample_vec, file_index);
      	}
      else if ( sample == "ttjets_semilep")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttjets_semilep_antitop/"); //4
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttjets_semilep_antitop_extn/"); //12
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttjets_semilep_top/"); //3
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/ttjets_semilep_top_extn/"); //13
      	  loadFile( sample_vec, file_index);
      	}
      else if ( sample == "Wjets")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/Wjets/"}, file_index); //1
      	}
      else if ( sample == "DY_M10_50")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/DY_M10_50/"}, file_index); //9
      	}
      else if ( sample == "DY_M50")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/DY_M50/"}, file_index); //63
      	}
      else if ( sample == "DY_M50_LO")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/DY_M50_LO/"}, file_index); //96
      	}
      else if (sample == "TGJets")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/TGJets/"); //1
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/TGJets_extn/"); //1
      	  loadFile( sample_vec, file_index);
      	}
      else if ( sample == "TTGJets")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/TTGJets/"); //4
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/TTGJets_extn/"); //8
      	  loadFile( sample_vec, file_index);
      	}
      else if ( sample == "tttt")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/tttt/"}, file_index); //1
      	}
      else if ( sample == "tZq")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/tZq/"}, file_index); //77
      	}
      else if ( sample == "WWqq_rares")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/WWqq_rares/"}, file_index); //1
      	}
      else if ( sample == "WW_doublescatering_rares")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/WW_DoubleScattering_rares/"}, file_index); //2
      	}
      else if ( sample == "WWZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/WWZ_rares/"}, file_index); //1
      	}
      else if ( sample == "WWW_rares")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/WWW_rares/"}, file_index); //1
      	}
      else if ( sample == "WZZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/WZZ_rares/"}, file_index); //1
      	}
      else if ( sample == "ZZZ_rares")
      	{
      	  loadFile( {"muell149/lobster_test_may22_Moriond17/ZZZ_rares/"}, file_index); //1
      	}


      /////////////////////////
      //////////
      ////////// gen filter studies
      //////////
      /////////////////////////


      else if (sample == "tth_powheg_genFilter")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/tth_nonbb_powheg_v1_genFilter/"); //14
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/tth_nonbb_powheg_v1_part2_genFilter/"); //22
      	  loadFile( sample_vec, file_index);
      	}
      else if (sample == "tth_powheg_genFilter_looseLepJetClean")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/tth_nonbb_powheg_v1_genFilter_looseLepJetClean/"); //14
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/tth_nonbb_powheg_v1_part2_genFilter_looseLepJetClean/"); //22
      	  loadFile( sample_vec, file_index);
      	}
      else if (sample == "tth_powheg_noGenFilter")
	{
	  loadFile( {"muell149/lobster_test__may25GenFilter/tth_nonbb_powheg_noFilter/"}, file_index); //11
	}
      else if (sample == "tth_powheg_noGenFilter_looseLepJetClean")
	{
	  loadFile( {"muell149/lobster_test__may25GenFilter/tth_nonbb_powheg_noFilter_looseLepJetClean/"}, file_index); //11
	}
      else if (sample == "ttjets_semilep_genFilter")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/ttbar_semilep_v6_part4/"); //2
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/ttbar_semilep_v6_part5/"); //3
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/ttbar_semilep_v6_part6/"); //7
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/ttbar_semilep_v6_part7/"); //16
      	  loadFile( sample_vec, file_index);
      	}
      else if (sample == "ttjets_semilep_genFilter_looseLepJetClean")
      	{
      	  vector<TString> sample_vec;
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/ttbar_semilep_v6_part4_looseLepJetClean/"); //2
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/ttbar_semilep_v6_part5_looseLepJetClean/"); //3
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/ttbar_semilep_v6_part6_looseLepJetClean/"); //7
      	  sample_vec.push_back("muell149/lobster_test__may25GenFilter/ttbar_semilep_v6_part7_looseLepJetClean/"); //16
      	  loadFile( sample_vec, file_index);
      	}

      else if (sample == "ttjets_semilep_noFilter")
	{
	  loadFile( {"muell149/lobster_test__may25NoFilter/ttbar_SL_tranche3/"}, file_index); //41
	}
      else if (sample == "ttjets_semilep_noFilter_looseLepJetClean")
	{
	  loadFile( {"muell149/lobster_test__may25NoFilter/ttbar_SL_tranche3_looseLepJetClean/"}, file_index); //40
	}
      
      
      else if (sample == "data")
	{
      	  vector<TString> sample_vec; //207 total

      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleMu2016B/"); //20
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleMu2016C/"); //12
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleMu2016D/"); //13
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleMu2016E/"); //13
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleMu2016F/"); //
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleMu2016G/"); //
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleMu2016H_pr2/"); //
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleMu2016H_pr3/"); //

      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleMu2016B/"); //11
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleMu2016C/"); //5
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleMu2016D/"); //7
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleMu2016E/"); //7
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleMu2016F/"); //6
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleMu2016G/"); //13
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleMu2016H_pr2/"); //15
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleMu2016H_pr3/"); //15

      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/MuonEg2016B/"); //2
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/MuonEg2016C/"); //1
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/MuonEg2016D/"); //1
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/MuonEg2016E/"); //1
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/MuonEg2016F/"); //1
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/MuonEg2016G/"); //2
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/MuonEg2016H_pr2/"); //2
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/MuonEg2016H_pr3/"); //2

      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleEg2016B/"); //6
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleEg2016C/"); //3
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleEg2016D/"); //4
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleEg2016E/"); //4
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleEg2016F/"); //3
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleEg2016G/"); //7
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleEg2016H_pr2/"); //7
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/doubleEg2016H_pr3/"); //7

      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleEle2016B/"); //6
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleEle2016C/"); //3
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleEle2016D/"); //4
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleEle2016E/"); //4
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleEle2016F/"); //3
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleEle2016G/"); //7
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleEle2016H_pr2/"); //7
      	  sample_vec.push_back("muell149/lobster_test_may22_Moriond17/singleEle2016H_pr3/"); //7
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

  return input_file_name;
}

class Sample
{
private:
public:
 Sample(TString sample_name_="name"):
  sample_name(sample_name_)
  {
    //TString prefix = "/scratch365/cmuelle2/selection_trees/may30_m17/";
    TString prefix = "/scratch365/cmuelle2/extraction_trees/may31_extractionTest/";
    input_file_name = prefix;
    
    if (sample_name == "ttH")
      {
	input_file_name += "ttH.root";
	legend_name = "ttH";
	fill_color = kOrange+10;
	fill_style = 1001;
	xsec = 0.5071*0.418;
      }
    else if (sample_name == "ttW")
      {
	input_file_name += "ttW.root";
	legend_name = "TTW";
	fill_color = kGreen-5;
	fill_style = 1001;
	xsec = 0.196;
      }
    else if (sample_name == "ttZ")
      {
	input_file_name += "ttZ.root";
	legend_name = "TTZ";
	fill_color = kSpring+2;
	fill_style = 1001;
	xsec = 0.2728;
      }
    else if (sample_name == "ttZ_M1to10")
      {
	input_file_name += "ttZ_M1to10.root";
	legend_name = "TTZ";
	fill_color = kSpring+2;
	fill_style = 1001;
	xsec = 0.0493;
      }
    else if (sample_name == "TTGJets")
      {
	input_file_name += "TTGJets.root";
	legend_name = "Convs";
	fill_color = kOrange;
	fill_style = 1001;
	xsec = 3.70;
      }
    else if (sample_name == "TGJets")
      {
	input_file_name += "TGJets.root";
	legend_name = "Convs";
	fill_color = kOrange;
	fill_style = 1001;
	xsec = 2.97;
      }
    else if (sample_name == "WGToLNuG")
      {
	input_file_name += "WGToLNuG.root";
	legend_name = "Convs";
	fill_color = kOrange;
	fill_style = 1001;
	xsec = 585.8;
      }
    else if (sample_name == "ZGTo2LG")
      {
	input_file_name += "ZGTo2LG.root";
	legend_name = "Convs";
	fill_color = kOrange;
	fill_style = 1001;
	xsec = 131.3;
      }
    else if (sample_name == "WWqq_rares")
      {
	input_file_name += "WWqq_rares.root";
	legend_name = "wwqq";
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
    else if (sample_name == "WW_2l2nu") 
      {
	input_file_name += "WW_2l2nu.root";
	legend_name = "Rares";
	fill_color = kOrange+10;
	fill_style = 1001;
	xsec = 10.481;
      }
    else if (sample_name == "ZZ_to4l")
      {
	input_file_name += "ZZ_to4l.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 1.256;
      }
    else if (sample_name == "WZ_to3lnu")
      {
	input_file_name += "WZ_to3lnu.root";
	legend_name = "WZ";
	fill_color = kViolet-4;
	fill_style = 1001;
	xsec = 4.429;
      }
    else if (sample_name=="Wjets")
      {
	input_file_name += "Wjets.root";
	legend_name = "WZ";
	fill_color = kViolet-4;
	fill_style = 1001;
	xsec = 61526.7;
      }
    else if (sample_name=="ST_tChan_top")
      {
	input_file_name += "ST_tChan_top.root";
	legend_name = "DY";
	fill_color = kBlack;
	fill_style = 1001;
	xsec = 136.;
      }
    else if (sample_name=="ST_tChan_antitop")
      {
	input_file_name += "ST_tChan_antitop.root";
	legend_name = "DY";
	fill_color = kBlack;
	fill_style = 1001;
	xsec = 81.;
      }
    else if (sample_name=="ST_sChan")
      {
	input_file_name += "ST_sChan.root";
	legend_name = "DY";
	fill_color = kBlack;
	fill_style = 1001;
	xsec = 3.68;
      }
    else if (sample_name=="DY_M50")
      {
	input_file_name += "DY_M50.root";
	legend_name = "DY";
	fill_color = kCyan+1;
	fill_style = 1001;
	xsec = 6025.2;
      }
    else if (sample_name=="DY_M10_50")
      {
	input_file_name += "DY_M10_50.root";
	legend_name = "DY";
	fill_color = kCyan+1;
	fill_style = 1001;
	xsec = 18610.;
      }
    else if (sample_name=="ST_tW")
      {
	input_file_name += "ST_tW.root";
	legend_name = "DY";
	fill_color = kBlack;
	fill_style = 1001;
	xsec = 35.6;
      }
    else if (sample_name=="ttjets_semilep")
      {
	input_file_name += "ttjets_semilep.root";
	legend_name = "TTZ";
	fill_color = kSpring+2;
	fill_style = 1001;
	xsec = 182.18;
      }
    else if (sample_name=="ttjets_dilep")
      {
	input_file_name += "ttjets_dilep.root";
	legend_name = "TTZ";
	fill_color = kSpring+2;
	fill_style = 1001;
	xsec = 87.3;
      }
    else if (sample_name=="tWll")
      {
	input_file_name += "tWll.root";
	legend_name = "Rares";
	fill_color = kAzure-9;
	fill_style = 1001;
	xsec = 0.01123;
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
  TString input_file_name;
  TString sample_name;
  TString legend_name;
  int fill_color;
  int fill_style;
  double xsec; //13 TeV xsec in pb

  virtual ~Sample(){}
};

