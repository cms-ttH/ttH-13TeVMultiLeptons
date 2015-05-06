#include "TFile.h"
#include "TChain.h"
#include "THStack.h"
#include "TH1.h"
#include "TH3.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TList.h"
#include "TLatex.h"
#include "TLine.h"
#include "TObject.h"
#include "TDirectory.h"
#include "TKey.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath> 
#include <iomanip>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sstream>


void collect_results( int lepSelection=0, int ANNtype_=0 ) {


  ///////////////////////////////////////////////////////

  TString label = "eventselsyncV1";

  int Nsample = 38;
  int Nsignal = 9+72;
  int Nsample_all = Nsample + Nsignal;
  //TFile *file[Nsample_all];

  TString lepType = "";
  if( lepSelection==0 )      lepType = "mu_sel";
  else if( lepSelection==1 ) lepType = "ele_sel";
  else                       lepType = "lep_sel";

  //TString baseDir = "/home/puigh/work/physics/8TeV/CMSSW_5_2_6/src/Output/HistoFiles/treeReader/v22_newBEANs_noCharmCSVSF/";
  //TString baseDir = "/home/gsmith/cms_work/CMSSW_5_2_6/src/AnalysisCode/LeptonPlusJets/macros/make_var_plots_darren/tree_reader_test_out/";
  //TString baseDir = "/brew/users/gsmith/tree_reader_test_out/1pt0_trial1/";
  //TString baseDir = "/brew/users/gsmith/tree_reader_test_out/2pt8_trial1/";
  //TString baseDir = "/brew/users/gsmith/tree_reader_test_out/changing_corrs_sep_1pt0/corr_1pt0/";
  //TString baseDir = "/brew/users/gsmith/tree_reader_test_out/ttjets_corrd_ttH_corrd/changing_corrs_sep_2pt0/corr_1pt0/";
  
  TString baseDir = "/afs/cern.ch/work/g/gesmith/ttH_multilepton_ana/newrepo/lepid_updates/CMSSW_7_2_3/src/ttH-13TeVMultiLeptons/DrawPlots/histos/";
  
  TString histofilename = "/afs/cern.ch/work/g/gesmith/ttH_multilepton_ana/newrepo/lepid_updates/CMSSW_7_2_3/src/ttH-13TeVMultiLeptons/DrawPlots/collect_results2.root";
  
  
  
  //TString basePrefix = "yggdrasil_treeReader";
  TString basePrefix = "";
  //TString baseSuffix = "_" + lepType + "_histo.root";
  TString baseSuffix = ".root";
  
  std::vector<std::string> old_catNames;
  //old_catNames.push_back("2lss");
  old_catNames.push_back("mumu2lss");
  old_catNames.push_back("ee2lss");
  old_catNames.push_back("emu2lss");
  old_catNames.push_back("3l");
  old_catNames.push_back("4l");
  
  
  int secondFileDim = old_catNames.size();
  
  TFile *file[Nsample_all][secondFileDim];
  
  std::vector<TString> datasets(Nsample_all);
  
  for (int i=0; i<Nsample_all; i++)
  {
    datasets[i] = "";
  }
  
//   datasets[0]  = "SingleMu_2012ABCD_BEAN_53xOn53x";
   
   datasets[0]  = "ttH125";
   
//   //datasets[1]  = "DYJetsToLL_M50_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";

   datasets[1]  = "ZJets";

//   datasets[2]  = "DYJetsToLL_M10To50_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[3]  = "DY1JetsToLL_M50_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[4]  = "DY2JetsToLL_M50_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[5]  = "DY3JetsToLL_M50_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[6]  = "DY4JetsToLL_M50_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   //datasets[7]  = "WJetsToLNu_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";

   datasets[7]  = "WJets";

//   datasets[8]  = "W1JetsToLNu_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[9]  = "W2JetsToLNu_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[10] = "W3JetsToLNu_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[11] = "W4JetsToLNu_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[12] = "WW_TuneZ2Star_8TeV_pythia6Tauola_Summer12_53xOn53x";
//   //datasets[13] = "WZ_TuneZ2Star_8TeV_pythia6Tauola_Summer12_53xOn53x";

   datasets[13] = "WZJets";

   datasets[14] = "ZZJets";

//   datasets[15] = "T_s_channel_TuneZ2star_8TeV_powheg_Summer12_53xOn53x";
//   datasets[16] = "T_tW_channel_TuneZ2star_8TeV_powheg_Summer12_53xOn53x";
//   datasets[17] = "T_t_channel_TuneZ2star_8TeV_powheg_Summer12_53xOn53x";
//   datasets[18] = "Tbar_s_channel_TuneZ2star_8TeV_powheg_Summer12_53xOn53x";
//   datasets[19] = "Tbar_tW_channel_TuneZ2star_8TeV_powheg_Summer12_53xOn53x";
//   datasets[20] = "Tbar_t_channel_TuneZ2star_8TeV_powheg_Summer12_53xOn53x";
//   //datasets[21] = "TTWJets_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";

   datasets[21] = "TTWJets";

//   //datasets[22] = "TTZJets_TuneZ2Star_8TeV_madgraph_Summer12_53xOn53x";

   datasets[22] = "TTZJets";

//   datasets[23] = "TTJetsLF_HadronicMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";

   datasets[23] = "TTJets";

//   datasets[24] = "TTJetsLF_SemiLeptMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[25] = "TTJetsLF_FullLeptMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   //datasets[26] = "TTJetsLF_MassiveBinDECAY_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[27] = "TTJetsCC_HadronicMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[28] = "TTJetsCC_SemiLeptMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[29] = "TTJetsCC_FullLeptMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[30] = "TTJetsCC_MassiveBinDECAY_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[31] = "TTJetsBB_HadronicMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[32] = "TTJetsBB_SemiLeptMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[33] = "TTJetsBB_FullLeptMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[34] = "TTJetsBB_MassiveBinDECAY_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[35] = "TTJetsB_HadronicMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[36] = "TTJetsB_SemiLeptMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
//   datasets[37] = "TTJetsB_FullLeptMGDecays_TuneZ2star_8TeV_madgraph_Summer12_53xOn53x";
// 
//   datasets[38] = "TTH_Inclusive_M_110_8TeV_53xOn53x";
//   datasets[39] = "TTH_Inclusive_M_115_8TeV_53xOn53x";
//   datasets[40] = "TTH_Inclusive_M_120_8TeV_53xOn53x";
//   datasets[41] = "TTH_Inclusive_M_122p5_8TeV_53xOn53x";
//   //datasets[42] = "TTH_Inclusive_M_125_8TeV_53xOn53x";

   datasets[42] = "ttH125";

//   datasets[43] = "TTH_Inclusive_M_127p5_8TeV_53xOn53x";
//   datasets[44] = "TTH_Inclusive_M_130_8TeV_53xOn53x";
//   datasets[45] = "TTH_Inclusive_M_135_8TeV_53xOn53x";
//   datasets[46] = "TTH_Inclusive_M_140_8TeV_53xOn53x";
//   datasets[47] = "TTH_hbb_M_110_8TeV_53xOn53x";
//   datasets[48] = "TTH_hbb_M_115_8TeV_53xOn53x";
//   datasets[49] = "TTH_hbb_M_120_8TeV_53xOn53x";
//   datasets[50] = "TTH_hbb_M_122p5_8TeV_53xOn53x";
//   datasets[51] = "TTH_hbb_M_125_8TeV_53xOn53x";
//   datasets[52] = "TTH_hbb_M_127p5_8TeV_53xOn53x";
//   datasets[53] = "TTH_hbb_M_130_8TeV_53xOn53x";
//   datasets[54] = "TTH_hbb_M_135_8TeV_53xOn53x";
//   datasets[55] = "TTH_hbb_M_140_8TeV_53xOn53x";
//   datasets[56] = "TTH_hcc_M_110_8TeV_53xOn53x";
//   datasets[57] = "TTH_hcc_M_115_8TeV_53xOn53x";
//   datasets[58] = "TTH_hcc_M_120_8TeV_53xOn53x";
//   datasets[59] = "TTH_hcc_M_122p5_8TeV_53xOn53x";
//   datasets[60] = "TTH_hcc_M_125_8TeV_53xOn53x";
//   datasets[61] = "TTH_hcc_M_127p5_8TeV_53xOn53x";
//   datasets[62] = "TTH_hcc_M_130_8TeV_53xOn53x";
//   datasets[63] = "TTH_hcc_M_135_8TeV_53xOn53x";
//   datasets[64] = "TTH_hcc_M_140_8TeV_53xOn53x";
//   datasets[65] = "TTH_hww_M_110_8TeV_53xOn53x";
//   datasets[66] = "TTH_hww_M_115_8TeV_53xOn53x";
//   datasets[67] = "TTH_hww_M_120_8TeV_53xOn53x";
//   datasets[68] = "TTH_hww_M_122p5_8TeV_53xOn53x";
//   datasets[69] = "TTH_hww_M_125_8TeV_53xOn53x";
//   datasets[70] = "TTH_hww_M_127p5_8TeV_53xOn53x";
//   datasets[71] = "TTH_hww_M_130_8TeV_53xOn53x";
//   datasets[72] = "TTH_hww_M_135_8TeV_53xOn53x";
//   datasets[73] = "TTH_hww_M_140_8TeV_53xOn53x";
//   datasets[74] = "TTH_hzz_M_110_8TeV_53xOn53x";
//   datasets[75] = "TTH_hzz_M_115_8TeV_53xOn53x";
//   datasets[76] = "TTH_hzz_M_120_8TeV_53xOn53x";
//   datasets[77] = "TTH_hzz_M_122p5_8TeV_53xOn53x";
//   datasets[78] = "TTH_hzz_M_125_8TeV_53xOn53x";
//   datasets[79] = "TTH_hzz_M_127p5_8TeV_53xOn53x";
//   datasets[80] = "TTH_hzz_M_130_8TeV_53xOn53x";
//   datasets[81] = "TTH_hzz_M_135_8TeV_53xOn53x";
//   datasets[82] = "TTH_hzz_M_140_8TeV_53xOn53x";
//   datasets[83] = "TTH_htt_M_110_8TeV_53xOn53x";
//   datasets[84] = "TTH_htt_M_115_8TeV_53xOn53x";
//   datasets[85] = "TTH_htt_M_120_8TeV_53xOn53x";
//   datasets[86] = "TTH_htt_M_122p5_8TeV_53xOn53x";
//   datasets[87] = "TTH_htt_M_125_8TeV_53xOn53x";
//   datasets[88] = "TTH_htt_M_127p5_8TeV_53xOn53x";
//   datasets[89] = "TTH_htt_M_130_8TeV_53xOn53x";
//   datasets[90] = "TTH_htt_M_135_8TeV_53xOn53x";
//   datasets[91] = "TTH_htt_M_140_8TeV_53xOn53x";
//   datasets[92] = "TTH_hgg_M_110_8TeV_53xOn53x";
//   datasets[93] = "TTH_hgg_M_115_8TeV_53xOn53x";
//   datasets[94] = "TTH_hgg_M_120_8TeV_53xOn53x";
//   datasets[95] = "TTH_hgg_M_122p5_8TeV_53xOn53x";
//   datasets[96] = "TTH_hgg_M_125_8TeV_53xOn53x";
//   datasets[97] = "TTH_hgg_M_127p5_8TeV_53xOn53x";
//   datasets[98] = "TTH_hgg_M_130_8TeV_53xOn53x";
//   datasets[99] = "TTH_hgg_M_135_8TeV_53xOn53x";
//   datasets[100] = "TTH_hgg_M_140_8TeV_53xOn53x";
//   datasets[101] = "TTH_hjj_M_110_8TeV_53xOn53x";
//   datasets[102] = "TTH_hjj_M_115_8TeV_53xOn53x";
//   datasets[103] = "TTH_hjj_M_120_8TeV_53xOn53x";
//   datasets[104] = "TTH_hjj_M_122p5_8TeV_53xOn53x";
//   datasets[105] = "TTH_hjj_M_125_8TeV_53xOn53x";
//   datasets[106] = "TTH_hjj_M_127p5_8TeV_53xOn53x";
//   datasets[107] = "TTH_hjj_M_130_8TeV_53xOn53x";
//   datasets[108] = "TTH_hjj_M_135_8TeV_53xOn53x";
//   datasets[109] = "TTH_hjj_M_140_8TeV_53xOn53x";
//   datasets[110] = "TTH_hzg_M_110_8TeV_53xOn53x";
//   datasets[111] = "TTH_hzg_M_115_8TeV_53xOn53x";
//   datasets[112] = "TTH_hzg_M_120_8TeV_53xOn53x";
//   datasets[113] = "TTH_hzg_M_122p5_8TeV_53xOn53x";
//   datasets[114] = "TTH_hzg_M_125_8TeV_53xOn53x";
//   datasets[115] = "TTH_hzg_M_127p5_8TeV_53xOn53x";
//   datasets[116] = "TTH_hzg_M_130_8TeV_53xOn53x";
//   datasets[117] = "TTH_hzg_M_135_8TeV_53xOn53x";
//   datasets[118] = "TTH_hzg_M_140_8TeV_53xOn53x";
// 
// 
//   if( lepSelection==0 )      datasets[0]  = "SingleMu_2012ABCD_BEAN_53xOn53x";
//   else if( lepSelection==1 ) datasets[0]  = "SingleElectron_2012ABCD_BEAN_53xOn53x";
//   else                       datasets[0]  = "SingleLepton_2012ABCD_BEAN_53xOn53x";

  TString beanVer = "_beanVer2";

  for( int iSample=0; iSample<Nsample_all; iSample++ ){
    TString typePrefix = ( datasets[iSample].Contains("Single") ) ? "_data_" : "_mc_";
    
    //if( iSample<47 ) baseDir = "/home/puigh/work/physics/8TeV/CMSSW_5_2_6/src/Output/HistoFiles/treeReader/v22_newBEANs_noCharmCSVSF/";
     //if( iSample>=47 ) baseDir = "/home/puigh/work/physics/8TeV/CMSSW_5_2_6/src/Output/HistoFiles/treeReader/v24_newBEANs_noCharmCSVSF/";

    //file[iSample] = new TFile(baseDir+basePrefix+typePrefix+datasets[iSample]+beanVer+baseSuffix);
    
    for (int iCat=0; iCat<secondFileDim; iCat++)
    {
        if (datasets[iSample]!="") file[iSample][iCat] = new TFile(baseDir+label+"/"+old_catNames[iCat]+"/"+old_catNames[iCat]+"_ge2j_"+datasets[iSample]+"_"+label+"_"+datasets[iSample]+baseSuffix);
    }
    
  }



  std::vector<std::string> sample;
  sample.push_back("data_obs");
  sample.push_back("diboson");
  sample.push_back("zjets");
  sample.push_back("wjets");
//  sample.push_back("singlet");
  sample.push_back("ttjets");
//  sample.push_back("ttbarPlusCCbar");
//  sample.push_back("ttbarPlusBBbar");
//  sample.push_back("ttbarPlusB");
  sample.push_back("ttbarW");
  sample.push_back("ttbarZ");

//  sample.push_back("ttH110");
//  sample.push_back("ttH115");
//  sample.push_back("ttH120");
//  sample.push_back("ttH122");
  sample.push_back("ttH125");
//  sample.push_back("ttH127");
//  sample.push_back("ttH130");
//  sample.push_back("ttH135");
//  sample.push_back("ttH140");

/*
  sample.push_back("ttH110_hbb");
  sample.push_back("ttH115_hbb");
  sample.push_back("ttH120_hbb");
  sample.push_back("ttH122_hbb");
  sample.push_back("ttH125_hbb");
  sample.push_back("ttH127_hbb");
  sample.push_back("ttH130_hbb");
  sample.push_back("ttH135_hbb");
  sample.push_back("ttH140_hbb");

  sample.push_back("ttH110_hcc");
  sample.push_back("ttH115_hcc");
  sample.push_back("ttH120_hcc");
  sample.push_back("ttH122_hcc");
  sample.push_back("ttH125_hcc");
  sample.push_back("ttH127_hcc");
  sample.push_back("ttH130_hcc");
  sample.push_back("ttH135_hcc");
  sample.push_back("ttH140_hcc");

  sample.push_back("ttH110_hww");
  sample.push_back("ttH115_hww");
  sample.push_back("ttH120_hww");
  sample.push_back("ttH122_hww");
  sample.push_back("ttH125_hww");
  sample.push_back("ttH127_hww");
  sample.push_back("ttH130_hww");
  sample.push_back("ttH135_hww");
  sample.push_back("ttH140_hww");

  sample.push_back("ttH110_hzz");
  sample.push_back("ttH115_hzz");
  sample.push_back("ttH120_hzz");
  sample.push_back("ttH122_hzz");
  sample.push_back("ttH125_hzz");
  sample.push_back("ttH127_hzz");
  sample.push_back("ttH130_hzz");
  sample.push_back("ttH135_hzz");
  sample.push_back("ttH140_hzz");

  sample.push_back("ttH110_htt");
  sample.push_back("ttH115_htt");
  sample.push_back("ttH120_htt");
  sample.push_back("ttH122_htt");
  sample.push_back("ttH125_htt");
  sample.push_back("ttH127_htt");
  sample.push_back("ttH130_htt");
  sample.push_back("ttH135_htt");
  sample.push_back("ttH140_htt");

  sample.push_back("ttH110_hgg");
  sample.push_back("ttH115_hgg");
  sample.push_back("ttH120_hgg");
  sample.push_back("ttH122_hgg");
  sample.push_back("ttH125_hgg");
  sample.push_back("ttH127_hgg");
  sample.push_back("ttH130_hgg");
  sample.push_back("ttH135_hgg");
  sample.push_back("ttH140_hgg");

  sample.push_back("ttH110_hjj");
  sample.push_back("ttH115_hjj");
  sample.push_back("ttH120_hjj");
  sample.push_back("ttH122_hjj");
  sample.push_back("ttH125_hjj");
  sample.push_back("ttH127_hjj");
  sample.push_back("ttH130_hjj");
  sample.push_back("ttH135_hjj");
  sample.push_back("ttH140_hjj");

  sample.push_back("ttH110_hzg");
  sample.push_back("ttH115_hzg");
  sample.push_back("ttH120_hzg");
  sample.push_back("ttH122_hzg");
  sample.push_back("ttH125_hzg");
  sample.push_back("ttH127_hzg");
  sample.push_back("ttH130_hzg");
  sample.push_back("ttH135_hzg");
  sample.push_back("ttH140_hzg");
*/


  TString file_suffix = "_final10v1_8TeV_CFMlpANN.root";
  if( ANNtype_==10 )      file_suffix = "_final10v10_8TeV_BDT.root";
  else if( ANNtype_==15 ) file_suffix = "_final10v15_8TeV_BDT.root";
  else if( ANNtype_==16 ) file_suffix = "_final10v16_8TeV_BDT.root";
  else if( ANNtype_==17 ) file_suffix = "_final10v17_8TeV_BDT.root";
  else if( ANNtype_==18 ) file_suffix = "_final10v18_8TeV_BDT.root";
  else if( ANNtype_==19 ) file_suffix = "_final10v19_8TeV_BDT.root";

  else if( ANNtype_==20 ) file_suffix = "_final10v20_0pt5_8TeV_BDT.root";
  else if( ANNtype_==21 ) file_suffix = "_final10v20_1pt0_8TeV_BDT.root";
  else if( ANNtype_==22 ) file_suffix = "_final10v20_1pt5_8TeV_BDT.root";
  else if( ANNtype_==23 ) file_suffix = "_final10v20_2pt0_8TeV_BDT.root";
  else if( ANNtype_==24 ) file_suffix = "_final10v20_3pt0_8TeV_BDT.root";
  else if( ANNtype_==25 ) file_suffix = "_final10v20_4pt0_8TeV_BDT.root";
  
  else if( ANNtype_==27 ) file_suffix = "_asdf.root";







//  TString histofilename = "/home/puigh/work/physics/8TeV/CMSSW_5_2_6/src/AnalysisCode/LeptonPlusJets/HistoFiles/collect_disc_results_53x_histo_3rd40_2013_07_31_v1_LJ_"+lepType+file_suffix;

//  TString histofilename = "/home/gsmith/cms_work/CMSSW_5_2_6/src/AnalysisCode/LeptonPlusJets/macros/make_var_plots_darren/tree_reader_test_out/collect_results/collect_disc_results_53x_histo_3rd40_2013_11_13_v3_LJ_2pt8_"+lepType+file_suffix;

//  TString histofilename = "/home/gsmith/cms_work/CMSSW_5_2_6/src/AnalysisCode/LeptonPlusJets/macros/make_var_plots_darren/tree_reader_test_out/collect_results/collect_disc_results_53x_histo_3rd40_2014_01_09__LJ_2pt0_corr1pt0__notanti_"+lepType+file_suffix;

  //TString histofilename = "/afs/cern.ch/work/g/gesmith/ttH_multilepton_ana/newrepo/charlie_new_recipe/CMSSW_7_2_3/src/ttH-13TeVMultiLeptons/DrawPlots/collect_results.root";

//////TString histofilename = "/afs/cern.ch/work/g/gesmith/ttH_multilepton_ana/newrepo/charlie_new_recipe/CMSSW_7_2_3/src/ttH-13TeVMultiLeptons/DrawPlots/collect_results.root";

  TFile histofile(histofilename,"recreate");

  histofile.cd();



  std::vector<std::string> histoname1;
  if( ANNtype_==10)      histoname1.push_back("h_disc_final10v10_8TeV_CFMlpANN_BDT");
  else if( ANNtype_==15) histoname1.push_back("h_disc_final10v15_8TeV_CFMlpANN_BDT");
  else if( ANNtype_==16) histoname1.push_back("h_disc_final10v16_8TeV_CFMlpANN_BDT");
  else if( ANNtype_==17) histoname1.push_back("h_disc_final10v17_8TeV_CFMlpANN_BDT");
  else if( ANNtype_==18) histoname1.push_back("h_disc_final10v16_8TeV_CFMlpANN_BDT");
  else if( ANNtype_==19) histoname1.push_back("h_disc_final10v16_8TeV_CFMlpANN_BDT");

  else if( ANNtype_==20 ) histoname1.push_back("h_disc_final10v20_0pt5_8TeV_CFMlpANN_BDT"); 
  else if( ANNtype_==21 ) histoname1.push_back("h_disc_final10v20_1pt0_8TeV_CFMlpANN_BDT"); 
  else if( ANNtype_==22 ) histoname1.push_back("h_disc_final10v20_1pt5_8TeV_CFMlpANN_BDT"); 
  else if( ANNtype_==23 ) histoname1.push_back("h_disc_final10v20_2pt0_8TeV_CFMlpANN_BDT"); 
  else if( ANNtype_==24 ) histoname1.push_back("h_disc_final10v20_3pt0_8TeV_CFMlpANN_BDT"); 
  else if( ANNtype_==25 ) histoname1.push_back("h_disc_final10v20_4pt0_8TeV_CFMlpANN_BDT");
  
  else if( ANNtype_==27 ) histoname1.push_back("numJets");




//   std::vector<std::string> old_catNames;
//   old_catNames.push_back("4j2t");
//   old_catNames.push_back("4j3t");
//   old_catNames.push_back("4j4t");
//   old_catNames.push_back("5j2t");
//   old_catNames.push_back("5j3t");
//   old_catNames.push_back("5j4t");
//   old_catNames.push_back("6j2t");
//   old_catNames.push_back("6j3t");
//   old_catNames.push_back("6j4t");



  std::vector<std::string> old_sysLabels;
  old_sysLabels.push_back("");
//   // old_sysLabels.push_back("_PUUp");
//   // old_sysLabels.push_back("_PUDown");
//   // old_sysLabels.push_back("_hfSFUp");
//   // old_sysLabels.push_back("_hfSFDown");
//   // old_sysLabels.push_back("_lfSFUp");
//   // old_sysLabels.push_back("_lfSFDown");
//   // old_sysLabels.push_back("_JERUp");
//   // old_sysLabels.push_back("_JERDown");
//   
//   
//   old_sysLabels.push_back("_JESUp");
//   old_sysLabels.push_back("_JESDown");
//   old_sysLabels.push_back("_topPtcorrUp");
//   old_sysLabels.push_back("_topPtcorrDown");
//   old_sysLabels.push_back("_Q2scaleUp");
//   old_sysLabels.push_back("_Q2scaleDown");
//   //
//   old_sysLabels.push_back("_CSVLFUp");     //17
//   old_sysLabels.push_back("_CSVLFDown");   //18
//   old_sysLabels.push_back("_CSVHFUp");     //19
//   old_sysLabels.push_back("_CSVHFDown");   //20
//   old_sysLabels.push_back("_CSVHFStats1Up");     //21
//   old_sysLabels.push_back("_CSVHFStats1Down");   //22
//   old_sysLabels.push_back("_CSVLFStats1Up");     //23
//   old_sysLabels.push_back("_CSVLFStats1Down");   //24
//   old_sysLabels.push_back("_CSVHFStats2Up");     //25
//   old_sysLabels.push_back("_CSVHFStats2Down");   //26
//   old_sysLabels.push_back("_CSVLFStats2Up");     //27
//   old_sysLabels.push_back("_CSVLFStats2Down");   //28
//   old_sysLabels.push_back("_CSVCErr1Up");     //29
//   old_sysLabels.push_back("_CSVCErr1Down");   //30
//   old_sysLabels.push_back("_CSVCErr2Up");     //31
//   old_sysLabels.push_back("_CSVCErr2Down");   //32

  std::vector<std::string> new_sysLabels;
  new_sysLabels.push_back("");
//   // new_sysLabels.push_back("_CMS_ttH_puUp");
//   // new_sysLabels.push_back("_CMS_ttH_puDown");
//   // new_sysLabels.push_back("_CMS_eff_bUp");
//   // new_sysLabels.push_back("_CMS_eff_bDown");
//   // new_sysLabels.push_back("_CMS_fake_bUp");
//   // new_sysLabels.push_back("_CMS_fake_bDown");
//   // new_sysLabels.push_back("_CMS_res_jUp");
//   // new_sysLabels.push_back("_CMS_res_jDown");
//   
//   
//   new_sysLabels.push_back("_CMS_scale_jUp");
//   new_sysLabels.push_back("_CMS_scale_jDown");
//   new_sysLabels.push_back("_CMS_ttH_topPtcorrUp");
//   new_sysLabels.push_back("_CMS_ttH_topPtcorrDown");
//   new_sysLabels.push_back("_Q2scale_ttH_ttbarUp");
//   new_sysLabels.push_back("_Q2scale_ttH_ttbarDown");
//   
//   new_sysLabels.push_back("_CMS_ttH_CSVLFUp");     //17
//   new_sysLabels.push_back("_CMS_ttH_CSVLFDown");   //18
//   new_sysLabels.push_back("_CMS_ttH_CSVHFUp");     //19
//   new_sysLabels.push_back("_CMS_ttH_CSVHFDown");   //20
//   new_sysLabels.push_back("_CMS_ttH_CSVHFStats1Up");     //21
//   new_sysLabels.push_back("_CMS_ttH_CSVHFStats1Down");   //22
//   new_sysLabels.push_back("_CMS_ttH_CSVLFStats1Up");     //23
//   new_sysLabels.push_back("_CMS_ttH_CSVLFStats1Down");   //24
//   new_sysLabels.push_back("_CMS_ttH_CSVHFStats2Up");     //25
//   new_sysLabels.push_back("_CMS_ttH_CSVHFStats2Down");   //26
//   new_sysLabels.push_back("_CMS_ttH_CSVLFStats2Up");     //27
//   new_sysLabels.push_back("_CMS_ttH_CSVLFStats2Down");   //28
//   new_sysLabels.push_back("_CMS_ttH_CSVCErr1Up");     //29
//   new_sysLabels.push_back("_CMS_ttH_CSVCErr1Down");   //30
//   new_sysLabels.push_back("_CMS_ttH_CSVCErr2Up");     //31
//   new_sysLabels.push_back("_CMS_ttH_CSVCErr2Down");   //32



//   std::vector<std::string> new_catNames;
//   new_catNames.push_back("j4_t2");
//   new_catNames.push_back("j4_t3");
//   new_catNames.push_back("j4_t4");
//   new_catNames.push_back("j5_t2");
//   new_catNames.push_back("j5_t3");
//   new_catNames.push_back("j5_tge4");
//   new_catNames.push_back("jge6_t2");
//   new_catNames.push_back("jge6_t3");
//   new_catNames.push_back("jge6_tge4");

  std::vector<std::string> new_catNames = old_catNames;


  // zjets
  int bin_zjets = 1;
  int bin_zjets_lowmass = 2;
  int bin_zjets_1p = 3;
  int bin_zjets_2p = 4;
  int bin_zjets_3p = 5;
  int bin_zjets_4p = 6;

  // wjets
  int bin_wjets = 7;
  int bin_wjets_1p = 8;
  int bin_wjets_2p = 9;
  int bin_wjets_3p = 10;
  int bin_wjets_4p = 11;

  // diboson
  int bin_ww = 12;
  int bin_wz = 13;
  int bin_zz = 14;

  // single top
  int bin_t_s     = 15;
  int bin_t_tw    = 16;
  int bin_t_t     = 17;
  int bin_tbar_s  = 18;
  int bin_tbar_tw = 19;
  int bin_tbar_t  = 20;

  // ttV
  int bin_ttW     = 21;
  int bin_ttZ     = 22;

  // tt + lf
  int bin_ttbar = 23;
  int bin_ttbar_lf_jj = 23;
  int bin_ttbar_lf_lj = 24;
  int bin_ttbar_lf_ll = 25;
  // int bin_ttbar_lf    = 26;

  // tt + cc
  int bin_ttbar_cc_jj = 27;
  int bin_ttbar_cc_lj = 28;
  int bin_ttbar_cc_ll = 29;
  // int bin_ttbar_cc    = 30;

  // tt + bb
  int bin_ttbar_bb_jj = 31;
  int bin_ttbar_bb_lj = 32;
  int bin_ttbar_bb_ll = 33;
  // int bin_ttbar_bb    = 34;

  // tt + b
  int bin_ttbar_b_jj = 35;
  int bin_ttbar_b_lj = 36;
  int bin_ttbar_b_ll = 37;

  // ttH
  int bin_ttH110 = 38;
  int bin_ttH115 = 39;
  int bin_ttH120 = 40;
  int bin_ttH122 = 41;
  int bin_ttH125 = 42;
  int bin_ttH127 = 43;
  int bin_ttH130 = 44;
  int bin_ttH135 = 45;
  int bin_ttH140 = 46;

  int bin_ttH110_hbb = 47;
  int bin_ttH115_hbb = 48;
  int bin_ttH120_hbb = 49;
  int bin_ttH122_hbb = 50;
  int bin_ttH125_hbb = 51;
  int bin_ttH127_hbb = 52;
  int bin_ttH130_hbb = 53;
  int bin_ttH135_hbb = 54;
  int bin_ttH140_hbb = 55;

  int bin_ttH110_hcc = 56;
  int bin_ttH115_hcc = 57;
  int bin_ttH120_hcc = 58;
  int bin_ttH122_hcc = 59;
  int bin_ttH125_hcc = 60;
  int bin_ttH127_hcc = 61;
  int bin_ttH130_hcc = 62;
  int bin_ttH135_hcc = 63;
  int bin_ttH140_hcc = 64;

  int bin_ttH110_hww = 65;
  int bin_ttH115_hww = 66;
  int bin_ttH120_hww = 67;
  int bin_ttH122_hww = 68;
  int bin_ttH125_hww = 69;
  int bin_ttH127_hww = 70;
  int bin_ttH130_hww = 71;
  int bin_ttH135_hww = 72;
  int bin_ttH140_hww = 73;

  int bin_ttH110_hzz = 74;
  int bin_ttH115_hzz = 75;
  int bin_ttH120_hzz = 76;
  int bin_ttH122_hzz = 77;
  int bin_ttH125_hzz = 78;
  int bin_ttH127_hzz = 79;
  int bin_ttH130_hzz = 80;
  int bin_ttH135_hzz = 81;
  int bin_ttH140_hzz = 82;

  int bin_ttH110_htt = 83;
  int bin_ttH115_htt = 84;
  int bin_ttH120_htt = 85;
  int bin_ttH122_htt = 86;
  int bin_ttH125_htt = 87;
  int bin_ttH127_htt = 88;
  int bin_ttH130_htt = 89;
  int bin_ttH135_htt = 90;
  int bin_ttH140_htt = 91;

  int bin_ttH110_hgg = 92;
  int bin_ttH115_hgg = 93;
  int bin_ttH120_hgg = 94;
  int bin_ttH122_hgg = 95;
  int bin_ttH125_hgg = 96;
  int bin_ttH127_hgg = 97;
  int bin_ttH130_hgg = 98;
  int bin_ttH135_hgg = 99;
  int bin_ttH140_hgg = 100;

  int bin_ttH110_hjj = 101;
  int bin_ttH115_hjj = 102;
  int bin_ttH120_hjj = 103;
  int bin_ttH122_hjj = 104;
  int bin_ttH125_hjj = 105;
  int bin_ttH127_hjj = 106;
  int bin_ttH130_hjj = 107;
  int bin_ttH135_hjj = 108;
  int bin_ttH140_hjj = 109;

  int bin_ttH110_hzg = 110;
  int bin_ttH115_hzg = 111;
  int bin_ttH120_hzg = 112;
  int bin_ttH122_hzg = 113;
  int bin_ttH125_hzg = 114;
  int bin_ttH127_hzg = 115;
  int bin_ttH130_hzg = 116;
  int bin_ttH135_hzg = 117;
  int bin_ttH140_hzg = 118;

  std::vector<int> use_data;
  use_data.push_back(0);

  std::vector<int> bkg_ttjets; // inclusive
  bkg_ttjets.push_back(bin_ttbar);

  std::vector<int> bkg_ttbar_b;
  bkg_ttbar_b.push_back(bin_ttbar_b_jj);
  bkg_ttbar_b.push_back(bin_ttbar_b_lj);
  bkg_ttbar_b.push_back(bin_ttbar_b_ll);

  std::vector<int> bkg_ttbar_bbbar;
  bkg_ttbar_bbbar.push_back(bin_ttbar_bb_jj);
  bkg_ttbar_bbbar.push_back(bin_ttbar_bb_lj);
  bkg_ttbar_bbbar.push_back(bin_ttbar_bb_ll);

  std::vector<int> bkg_ttbar_ccbar;
  bkg_ttbar_ccbar.push_back(bin_ttbar_cc_jj);
  bkg_ttbar_ccbar.push_back(bin_ttbar_cc_lj);
  bkg_ttbar_ccbar.push_back(bin_ttbar_cc_ll);

  std::vector<int> bkg_ttbar_other;
  bkg_ttbar_other.push_back(bin_ttbar_lf_jj);
  bkg_ttbar_other.push_back(bin_ttbar_lf_lj);
  bkg_ttbar_other.push_back(bin_ttbar_lf_ll);

  std::vector<int> bkg_singlet;
  bkg_singlet.push_back(bin_t_s);
  bkg_singlet.push_back(bin_t_tw);
  bkg_singlet.push_back(bin_t_t);
  bkg_singlet.push_back(bin_tbar_s);
  bkg_singlet.push_back(bin_tbar_tw);
  bkg_singlet.push_back(bin_tbar_t);

  std::vector<int> bkg_ttZ;
  bkg_ttZ.push_back(bin_ttZ);
  std::vector<int> bkg_ttW;
  bkg_ttW.push_back(bin_ttW);

  std::vector<int> bkg_diboson;
//  bkg_diboson.push_back(bin_ww); // to do
  bkg_diboson.push_back(bin_wz);
  bkg_diboson.push_back(bin_zz);

  std::vector<int> bkg_wjets;
  bkg_wjets.push_back(bin_wjets);
  //bkg_wjets.push_back(bin_wjets_1p);
  //bkg_wjets.push_back(bin_wjets_2p);
  //bkg_wjets.push_back(bin_wjets_3p);
  //bkg_wjets.push_back(bin_wjets_4p);

  std::vector<int> bkg_zjets;
  bkg_zjets.push_back(bin_zjets);
  //bkg_zjets.push_back(bin_zjets_lowmass);
  //bkg_zjets.push_back(bin_zjets_1p);
  //bkg_zjets.push_back(bin_zjets_2p);
  //bkg_zjets.push_back(bin_zjets_3p);
  //bkg_zjets.push_back(bin_zjets_4p);


  std::vector<int> sig_ttH110;
  sig_ttH110.push_back(bin_ttH110);
  std::vector<int> sig_ttH115;
  sig_ttH115.push_back(bin_ttH115);
  std::vector<int> sig_ttH120;
  sig_ttH120.push_back(bin_ttH120);
  std::vector<int> sig_ttH122;
  sig_ttH122.push_back(bin_ttH122);
  std::vector<int> sig_ttH125;
  sig_ttH125.push_back(bin_ttH125);
  std::vector<int> sig_ttH127;
  sig_ttH127.push_back(bin_ttH127);
  std::vector<int> sig_ttH130;
  sig_ttH130.push_back(bin_ttH130);
  std::vector<int> sig_ttH135;
  sig_ttH135.push_back(bin_ttH135);
  std::vector<int> sig_ttH140;
  sig_ttH140.push_back(bin_ttH140);


  std::vector<int> sig_ttH110_hbb;
  sig_ttH110_hbb.push_back(bin_ttH110_hbb);
  std::vector<int> sig_ttH115_hbb;
  sig_ttH115_hbb.push_back(bin_ttH115_hbb);
  std::vector<int> sig_ttH120_hbb;
  sig_ttH120_hbb.push_back(bin_ttH120_hbb);
  std::vector<int> sig_ttH122_hbb;
  sig_ttH122_hbb.push_back(bin_ttH122_hbb);
  std::vector<int> sig_ttH125_hbb;
  sig_ttH125_hbb.push_back(bin_ttH125_hbb);
  std::vector<int> sig_ttH127_hbb;
  sig_ttH127_hbb.push_back(bin_ttH127_hbb);
  std::vector<int> sig_ttH130_hbb;
  sig_ttH130_hbb.push_back(bin_ttH130_hbb);
  std::vector<int> sig_ttH135_hbb;
  sig_ttH135_hbb.push_back(bin_ttH135_hbb);
  std::vector<int> sig_ttH140_hbb;
  sig_ttH140_hbb.push_back(bin_ttH140_hbb);

  std::vector<int> sig_ttH110_hcc;
  sig_ttH110_hcc.push_back(bin_ttH110_hcc);
  std::vector<int> sig_ttH115_hcc;
  sig_ttH115_hcc.push_back(bin_ttH115_hcc);
  std::vector<int> sig_ttH120_hcc;
  sig_ttH120_hcc.push_back(bin_ttH120_hcc);
  std::vector<int> sig_ttH122_hcc;
  sig_ttH122_hcc.push_back(bin_ttH122_hcc);
  std::vector<int> sig_ttH125_hcc;
  sig_ttH125_hcc.push_back(bin_ttH125_hcc);
  std::vector<int> sig_ttH127_hcc;
  sig_ttH127_hcc.push_back(bin_ttH127_hcc);
  std::vector<int> sig_ttH130_hcc;
  sig_ttH130_hcc.push_back(bin_ttH130_hcc);
  std::vector<int> sig_ttH135_hcc;
  sig_ttH135_hcc.push_back(bin_ttH135_hcc);
  std::vector<int> sig_ttH140_hcc;
  sig_ttH140_hcc.push_back(bin_ttH140_hcc);

  std::vector<int> sig_ttH110_hww;
  sig_ttH110_hww.push_back(bin_ttH110_hww);
  std::vector<int> sig_ttH115_hww;
  sig_ttH115_hww.push_back(bin_ttH115_hww);
  std::vector<int> sig_ttH120_hww;
  sig_ttH120_hww.push_back(bin_ttH120_hww);
  std::vector<int> sig_ttH122_hww;
  sig_ttH122_hww.push_back(bin_ttH122_hww);
  std::vector<int> sig_ttH125_hww;
  sig_ttH125_hww.push_back(bin_ttH125_hww);
  std::vector<int> sig_ttH127_hww;
  sig_ttH127_hww.push_back(bin_ttH127_hww);
  std::vector<int> sig_ttH130_hww;
  sig_ttH130_hww.push_back(bin_ttH130_hww);
  std::vector<int> sig_ttH135_hww;
  sig_ttH135_hww.push_back(bin_ttH135_hww);
  std::vector<int> sig_ttH140_hww;
  sig_ttH140_hww.push_back(bin_ttH140_hww);

  std::vector<int> sig_ttH110_hzz;
  sig_ttH110_hzz.push_back(bin_ttH110_hzz);
  std::vector<int> sig_ttH115_hzz;
  sig_ttH115_hzz.push_back(bin_ttH115_hzz);
  std::vector<int> sig_ttH120_hzz;
  sig_ttH120_hzz.push_back(bin_ttH120_hzz);
  std::vector<int> sig_ttH122_hzz;
  sig_ttH122_hzz.push_back(bin_ttH122_hzz);
  std::vector<int> sig_ttH125_hzz;
  sig_ttH125_hzz.push_back(bin_ttH125_hzz);
  std::vector<int> sig_ttH127_hzz;
  sig_ttH127_hzz.push_back(bin_ttH127_hzz);
  std::vector<int> sig_ttH130_hzz;
  sig_ttH130_hzz.push_back(bin_ttH130_hzz);
  std::vector<int> sig_ttH135_hzz;
  sig_ttH135_hzz.push_back(bin_ttH135_hzz);
  std::vector<int> sig_ttH140_hzz;
  sig_ttH140_hzz.push_back(bin_ttH140_hzz);

  std::vector<int> sig_ttH110_htt;
  sig_ttH110_htt.push_back(bin_ttH110_htt);
  std::vector<int> sig_ttH115_htt;
  sig_ttH115_htt.push_back(bin_ttH115_htt);
  std::vector<int> sig_ttH120_htt;
  sig_ttH120_htt.push_back(bin_ttH120_htt);
  std::vector<int> sig_ttH122_htt;
  sig_ttH122_htt.push_back(bin_ttH122_htt);
  std::vector<int> sig_ttH125_htt;
  sig_ttH125_htt.push_back(bin_ttH125_htt);
  std::vector<int> sig_ttH127_htt;
  sig_ttH127_htt.push_back(bin_ttH127_htt);
  std::vector<int> sig_ttH130_htt;
  sig_ttH130_htt.push_back(bin_ttH130_htt);
  std::vector<int> sig_ttH135_htt;
  sig_ttH135_htt.push_back(bin_ttH135_htt);
  std::vector<int> sig_ttH140_htt;
  sig_ttH140_htt.push_back(bin_ttH140_htt);

  std::vector<int> sig_ttH110_hgg;
  sig_ttH110_hgg.push_back(bin_ttH110_hgg);
  std::vector<int> sig_ttH115_hgg;
  sig_ttH115_hgg.push_back(bin_ttH115_hgg);
  std::vector<int> sig_ttH120_hgg;
  sig_ttH120_hgg.push_back(bin_ttH120_hgg);
  std::vector<int> sig_ttH122_hgg;
  sig_ttH122_hgg.push_back(bin_ttH122_hgg);
  std::vector<int> sig_ttH125_hgg;
  sig_ttH125_hgg.push_back(bin_ttH125_hgg);
  std::vector<int> sig_ttH127_hgg;
  sig_ttH127_hgg.push_back(bin_ttH127_hgg);
  std::vector<int> sig_ttH130_hgg;
  sig_ttH130_hgg.push_back(bin_ttH130_hgg);
  std::vector<int> sig_ttH135_hgg;
  sig_ttH135_hgg.push_back(bin_ttH135_hgg);
  std::vector<int> sig_ttH140_hgg;
  sig_ttH140_hgg.push_back(bin_ttH140_hgg);

  std::vector<int> sig_ttH110_hjj;
  sig_ttH110_hjj.push_back(bin_ttH110_hjj);
  std::vector<int> sig_ttH115_hjj;
  sig_ttH115_hjj.push_back(bin_ttH115_hjj);
  std::vector<int> sig_ttH120_hjj;
  sig_ttH120_hjj.push_back(bin_ttH120_hjj);
  std::vector<int> sig_ttH122_hjj;
  sig_ttH122_hjj.push_back(bin_ttH122_hjj);
  std::vector<int> sig_ttH125_hjj;
  sig_ttH125_hjj.push_back(bin_ttH125_hjj);
  std::vector<int> sig_ttH127_hjj;
  sig_ttH127_hjj.push_back(bin_ttH127_hjj);
  std::vector<int> sig_ttH130_hjj;
  sig_ttH130_hjj.push_back(bin_ttH130_hjj);
  std::vector<int> sig_ttH135_hjj;
  sig_ttH135_hjj.push_back(bin_ttH135_hjj);
  std::vector<int> sig_ttH140_hjj;
  sig_ttH140_hjj.push_back(bin_ttH140_hjj);

  std::vector<int> sig_ttH110_hzg;
  sig_ttH110_hzg.push_back(bin_ttH110_hzg);
  std::vector<int> sig_ttH115_hzg;
  sig_ttH115_hzg.push_back(bin_ttH115_hzg);
  std::vector<int> sig_ttH120_hzg;
  sig_ttH120_hzg.push_back(bin_ttH120_hzg);
  std::vector<int> sig_ttH122_hzg;
  sig_ttH122_hzg.push_back(bin_ttH122_hzg);
  std::vector<int> sig_ttH125_hzg;
  sig_ttH125_hzg.push_back(bin_ttH125_hzg);
  std::vector<int> sig_ttH127_hzg;
  sig_ttH127_hzg.push_back(bin_ttH127_hzg);
  std::vector<int> sig_ttH130_hzg;
  sig_ttH130_hzg.push_back(bin_ttH130_hzg);
  std::vector<int> sig_ttH135_hzg;
  sig_ttH135_hzg.push_back(bin_ttH135_hzg);
  std::vector<int> sig_ttH140_hzg;
  sig_ttH140_hzg.push_back(bin_ttH140_hzg);


///////////// specify samples /////////////

  std::vector<std::vector<int> > samples_to_use;
  samples_to_use.push_back(use_data);
  samples_to_use.push_back(bkg_diboson);
  samples_to_use.push_back(bkg_zjets);
  samples_to_use.push_back(bkg_wjets);
//  samples_to_use.push_back(bkg_singlet);
  samples_to_use.push_back(bkg_ttjets); // inclusive
//  samples_to_use.push_back(bkg_ttbar_other); // can't do this while doing the one above
//  samples_to_use.push_back(bkg_ttbar_ccbar);
//  samples_to_use.push_back(bkg_ttbar_bbbar);
//  samples_to_use.push_back(bkg_ttbar_b);
  samples_to_use.push_back(bkg_ttW);
  samples_to_use.push_back(bkg_ttZ);

//  samples_to_use.push_back(sig_ttH110);
//  samples_to_use.push_back(sig_ttH115);
//  samples_to_use.push_back(sig_ttH120);
//  samples_to_use.push_back(sig_ttH122);
  samples_to_use.push_back(sig_ttH125);
//  samples_to_use.push_back(sig_ttH127);
//  samples_to_use.push_back(sig_ttH130);
//  samples_to_use.push_back(sig_ttH135);
//  samples_to_use.push_back(sig_ttH140);


/*
  samples_to_use.push_back(sig_ttH110_hbb);
  samples_to_use.push_back(sig_ttH115_hbb);
  samples_to_use.push_back(sig_ttH120_hbb);
  samples_to_use.push_back(sig_ttH122_hbb);
  samples_to_use.push_back(sig_ttH125_hbb);
  samples_to_use.push_back(sig_ttH127_hbb);
  samples_to_use.push_back(sig_ttH130_hbb);
  samples_to_use.push_back(sig_ttH135_hbb);
  samples_to_use.push_back(sig_ttH140_hbb);

  samples_to_use.push_back(sig_ttH110_hcc);
  samples_to_use.push_back(sig_ttH115_hcc);
  samples_to_use.push_back(sig_ttH120_hcc);
  samples_to_use.push_back(sig_ttH122_hcc);
  samples_to_use.push_back(sig_ttH125_hcc);
  samples_to_use.push_back(sig_ttH127_hcc);
  samples_to_use.push_back(sig_ttH130_hcc);
  samples_to_use.push_back(sig_ttH135_hcc);
  samples_to_use.push_back(sig_ttH140_hcc);

  samples_to_use.push_back(sig_ttH110_hww);
  samples_to_use.push_back(sig_ttH115_hww);
  samples_to_use.push_back(sig_ttH120_hww);
  samples_to_use.push_back(sig_ttH122_hww);
  samples_to_use.push_back(sig_ttH125_hww);
  samples_to_use.push_back(sig_ttH127_hww);
  samples_to_use.push_back(sig_ttH130_hww);
  samples_to_use.push_back(sig_ttH135_hww);
  samples_to_use.push_back(sig_ttH140_hww);

  samples_to_use.push_back(sig_ttH110_hzz);
  samples_to_use.push_back(sig_ttH115_hzz);
  samples_to_use.push_back(sig_ttH120_hzz);
  samples_to_use.push_back(sig_ttH122_hzz);
  samples_to_use.push_back(sig_ttH125_hzz);
  samples_to_use.push_back(sig_ttH127_hzz);
  samples_to_use.push_back(sig_ttH130_hzz);
  samples_to_use.push_back(sig_ttH135_hzz);
  samples_to_use.push_back(sig_ttH140_hzz);

  samples_to_use.push_back(sig_ttH110_htt);
  samples_to_use.push_back(sig_ttH115_htt);
  samples_to_use.push_back(sig_ttH120_htt);
  samples_to_use.push_back(sig_ttH122_htt);
  samples_to_use.push_back(sig_ttH125_htt);
  samples_to_use.push_back(sig_ttH127_htt);
  samples_to_use.push_back(sig_ttH130_htt);
  samples_to_use.push_back(sig_ttH135_htt);
  samples_to_use.push_back(sig_ttH140_htt);

  samples_to_use.push_back(sig_ttH110_hgg);
  samples_to_use.push_back(sig_ttH115_hgg);
  samples_to_use.push_back(sig_ttH120_hgg);
  samples_to_use.push_back(sig_ttH122_hgg);
  samples_to_use.push_back(sig_ttH125_hgg);
  samples_to_use.push_back(sig_ttH127_hgg);
  samples_to_use.push_back(sig_ttH130_hgg);
  samples_to_use.push_back(sig_ttH135_hgg);
  samples_to_use.push_back(sig_ttH140_hgg);

  samples_to_use.push_back(sig_ttH110_hjj);
  samples_to_use.push_back(sig_ttH115_hjj);
  samples_to_use.push_back(sig_ttH120_hjj);
  samples_to_use.push_back(sig_ttH122_hjj);
  samples_to_use.push_back(sig_ttH125_hjj);
  samples_to_use.push_back(sig_ttH127_hjj);
  samples_to_use.push_back(sig_ttH130_hjj);
  samples_to_use.push_back(sig_ttH135_hjj);
  samples_to_use.push_back(sig_ttH140_hjj);

  samples_to_use.push_back(sig_ttH110_hzg);
  samples_to_use.push_back(sig_ttH115_hzg);
  samples_to_use.push_back(sig_ttH120_hzg);
  samples_to_use.push_back(sig_ttH122_hzg);
  samples_to_use.push_back(sig_ttH125_hzg);
  samples_to_use.push_back(sig_ttH127_hzg);
  samples_to_use.push_back(sig_ttH130_hzg);
  samples_to_use.push_back(sig_ttH135_hzg);
  samples_to_use.push_back(sig_ttH140_hzg);
*/

///////////////////////////////////////////

cout << "hey1" << endl;

  for( int iNSamp=0; iNSamp<int(sample.size()); iNSamp++ ){
cout << "hey2" << endl;
    for( int i=0; i<int(histoname1.size()); i++ ){
      std::string hname_tmp = histoname1[i];
cout << "hey3" << endl;
      for( int j=0; j<int(old_catNames.size()); j++ ){
cout << "hey4" << endl;
	if( (old_catNames[j].find("6j3t")!=std::string::npos) ){
	  if( ANNtype_==18 )      hname_tmp = "h_disc_final10v15_8TeV_CFMlpANN_BDT";
	}
	if( (old_catNames[j].find("5j4t")!=std::string::npos) ){
	  if( ANNtype_==19 )      hname_tmp = "h_disc_final10v15_8TeV_CFMlpANN_BDT";
	}

cout << "hey5" << endl;
	for( int k=0; k<int(old_sysLabels.size()); k++ ){
	  if( (sample[iNSamp].find("data")!=std::string::npos) && k!=0 ) continue;

	  //std::string hname = hname_tmp + "_" + old_catNames[j] + old_sysLabels[k];
          std::string hname = hname_tmp + old_sysLabels[k];
          std::string hname_use = hname_tmp + "_use_" + old_catNames[j] + old_sysLabels[k];
          
cout << "hey6" << endl;
	  bool firstSample = true;
	  TH1D* hist;
	  for( int iSample=0; iSample<Nsample_all; iSample++ ){
	    bool useSample = false;
	    for( int jSample=0; jSample<int(samples_to_use[iNSamp].size()); jSample++ ){
	      if( iSample==samples_to_use[iNSamp][jSample] ){
		useSample = true;
		break;
	      }
	    }
	    if( !useSample ) continue;
	    TH1D* hist_temp = (TH1D*)file[iSample][j]->Get(hname.c_str());
	    if( firstSample ){
	      hist = (TH1D*)hist_temp->Clone();
	      firstSample = false;
	    }
	    else hist->Add(hist_temp);
	  }

	  std::string temp = hname;
	  int rebin = 1;

	  TH1D* hist_use;
	  //if( (hname.find("disc")!=std::string::npos) && (hname.find("CFMlpANN")!=std::string::npos) ){
          if(hname.find("numJets")!=std::string::npos){                                                     //  <---- here
	    if( (hname.find("4t")!=std::string::npos) )      rebin = 2;
	    if( (hname.find("TTHTTBB")!=std::string::npos) ) rebin = 2;

	    hist_use = (TH1D*)hist->Clone(hname_use.c_str());
	    hist_use->Rebin(rebin);
	  }
	  else if( (hname.find("avg_btag_disc_btags")!=std::string::npos)){
	    if( (hname.find("4j1t")!=std::string::npos) )     rebin = 1;
	    else if( (hname.find("j2t")!=std::string::npos) ) rebin = 1;
	    else if( (hname.find("j3t")!=std::string::npos) ) rebin = 2;
	    else if( (hname.find("j4t")!=std::string::npos) ) rebin = 2;

	    hist_use = (TH1D*)hist->Clone(hname_use.c_str());
	    hist_use->Rebin(rebin);
	  }


	  int nbins = hist_use->GetNbinsX();
	  for( int bin=0; bin<nbins; bin++ ){
	    if( !(hist_use->GetBinContent(bin+1)>0.) ) hist_use->SetBinContent(bin+1,0.00001);
	  }

	  // std::string new_prefix = "CFMlpANN";
	  std::string new_prefix = "MVA";

	  std::string new_syst_label = new_sysLabels[k];
	  if( (new_sysLabels[k].find("Q2scale_ttH_ttbarUp")!=std::string::npos)  ){
	    if( (sample[iNSamp].find("ttbarPlusBB")!=std::string::npos)  )          new_syst_label = "_Q2scale_ttH_ttbar_bbUp";
	    else if( (sample[iNSamp].find("ttbarPlusB")!=std::string::npos)  )    new_syst_label = "_Q2scale_ttH_ttbar_bUp";
	    else if( (sample[iNSamp].find("ttbarPlusCCbar")!=std::string::npos)  ) new_syst_label = "_Q2scale_ttH_ttbar_ccUp";
	  }
	  else if( (new_sysLabels[k].find("Q2scale_ttH_ttbarDown")!=std::string::npos)  ){
	    if( (sample[iNSamp].find("ttbarPlusBB")!=std::string::npos)  )          new_syst_label = "_Q2scale_ttH_ttbar_bbDown";
	    else if( (sample[iNSamp].find("ttbarPlusB")!=std::string::npos)  )    new_syst_label = "_Q2scale_ttH_ttbar_bDown";
	    else if( (sample[iNSamp].find("ttbarPlusCCbar")!=std::string::npos)  ) new_syst_label = "_Q2scale_ttH_ttbar_ccDown";
	  }

	  std::string new_hname = sample[iNSamp] + "_" + new_prefix + "_multilep_" + new_catNames[j] + new_syst_label;

	  hist_use->Write(new_hname.c_str());
          
          cout << " " << endl;
          cout << hname << endl;
          cout << hname_use << endl;
          cout << new_hname << endl;
          cout << " " << endl;
          
	}
      }
    }
  }

cout << "hey7" << endl;

  histofile.Write();
  histofile.Close();

  // close all files
  for( int i=0; i<Nsample_all; i++ ) 
  {
    for( int j=0; j<secondFileDim; j++ )
    {
        if (datasets[i]!="") file[i][j]->Close();
    }
  }

cout << "hey8" << endl;

}



/*

TH1D* h_data = (TH1D*)data_obs_CFMlpANN_ljets_jge6_tge4->Clone();

TH1D* h_bkg = (TH1D*)diboson_CFMlpANN_ljets_jge6_tge4->Clone();
h_bkg->Add(zjets_CFMlpANN_ljets_jge6_tge4);
h_bkg->Add(wjets_CFMlpANN_ljets_jge6_tge4);
h_bkg->Add(singlet_CFMlpANN_ljets_jge6_tge4);
h_bkg->Add(ttbar_CFMlpANN_ljets_jge6_tge4);
h_bkg->Add(ttbarPlusCCbar_CFMlpANN_ljets_jge6_tge4);
h_bkg->Add(ttbarPlusBBbar_CFMlpANN_ljets_jge6_tge4);
h_bkg->Add(ttbarW_CFMlpANN_ljets_jge6_tge4);
h_bkg->Add(ttbarZ_CFMlpANN_ljets_jge6_tge4);

TH1D* h_bkg_CMS_ttH_CSVLFUp = (TH1D*)diboson_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp->Clone();
h_bkg_CMS_ttH_CSVLFUp->Add(zjets_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp);
h_bkg_CMS_ttH_CSVLFUp->Add(wjets_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp);
h_bkg_CMS_ttH_CSVLFUp->Add(singlet_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp);
h_bkg_CMS_ttH_CSVLFUp->Add(ttbar_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp);
h_bkg_CMS_ttH_CSVLFUp->Add(ttbarPlusCCbar_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp);
h_bkg_CMS_ttH_CSVLFUp->Add(ttbarPlusBBbar_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp);
h_bkg_CMS_ttH_CSVLFUp->Add(ttbarW_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp);
h_bkg_CMS_ttH_CSVLFUp->Add(ttbarZ_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFUp);

TH1D* h_bkg_CMS_ttH_CSVLFDown = (TH1D*)diboson_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown->Clone();
h_bkg_CMS_ttH_CSVLFDown->Add(zjets_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown);
h_bkg_CMS_ttH_CSVLFDown->Add(wjets_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown);
h_bkg_CMS_ttH_CSVLFDown->Add(singlet_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown);
h_bkg_CMS_ttH_CSVLFDown->Add(ttbar_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown);
h_bkg_CMS_ttH_CSVLFDown->Add(ttbarPlusCCbar_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown);
h_bkg_CMS_ttH_CSVLFDown->Add(ttbarPlusBBbar_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown);
h_bkg_CMS_ttH_CSVLFDown->Add(ttbarW_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown);
h_bkg_CMS_ttH_CSVLFDown->Add(ttbarZ_CFMlpANN_ljets_jge6_tge4_CMS_ttH_CSVLFDown);

h_data->SetMarkerStyle(20);
h_bkg->SetLineWidth(2);
h_bkg_CMS_ttH_CSVLFUp->SetLineWidth(2);
h_bkg_CMS_ttH_CSVLFDown->SetLineWidth(2);

h_bkg->SetLineColor(kBlack);
h_bkg_CMS_ttH_CSVLFUp->SetLineColor(kRed);
h_bkg_CMS_ttH_CSVLFDown->SetLineColor(kBlue);


h_data->SetStats(0);

h_data->Draw("pe1");
h_bkg->Draw("histsame");
h_bkg_CMS_ttH_CSVLFUp->Draw("histsame");
h_bkg_CMS_ttH_CSVLFDown->Draw("histsame");


TFile* file_v16 = new TFile("HistoFiles/collect_disc_results_53x_histo_3rd40_2013_06_24_v1_LJ_lep_sel_final10v16_8TeV_BDT.root");
TFile* file_v19 = new TFile("HistoFiles/collect_disc_results_53x_histo_3rd40_2013_06_24_v1_LJ_lep_sel_final10v19_8TeV_BDT.root");

TH1D* ttH_v16 = (TH1D*)file_v16->Get("ttH125_MVA_ljets_jge6_t3");
TH1D* ttH_v19 = (TH1D*)file_v19->Get("ttH125_MVA_ljets_jge6_t3");

ttH_v16->Draw();
ttH_v19->Draw("histsame");






   1 & avg\_dr\_tagged\_jets               & 1.068e-01 \\
   2 & maxeta\_tag\_tag                   & 8.248e-02 \\
   3 & pt\_all\_jets\_over\_E\_all\_jets      & 7.428e-02 \\
   4 & h1                               & 6.709e-02 \\
   5 & tagged\_dijet\_mass\_closest\_to\_125 & 6.667e-02 \\
   6 & all\_sum\_pt\_with\_met              & 6.415e-02 \\
   7 & fourth\_highest\_btag              & 6.177e-02 \\
   8 & aplanarity                       & 6.070e-02 \\
   9 & h3                               & 5.450e-02 \\
  10 & MET                              & 3.341e-02 \\


   1 & h3                               & 2.854e-02 \\
   2 & maxeta\_tag\_tag                   & 2.824e-02 \\
   3 & dEta\_fn                          & 2.784e-02 \\
   4 & pt\_all\_jets\_over\_E\_all\_jets      & 2.664e-02 \\
   5 & abs\_dEta\_hadtop\_bb               & 2.374e-02 \\
   6 & tagged\_dijet\_mass\_closest\_to\_125 & 2.349e-02 \\
   7 & maxeta\_jet\_jet                   & 2.259e-02 \\
   8 & M3                               & 2.216e-02 \\
   9 & maxeta\_jet\_tag                   & 2.161e-02 \\
  10 & abs\_dEta\_leptop\_bb               & 2.098e-02 \\
  11 & h1                               & 1.991e-02 \\
  12 & sphericity                       & 1.923e-02 \\
  13 & aplanarity                       & 1.845e-02 \\
  14 & min\_dr\_tagged\_jets               & 1.579e-02 \\
  15 & third\_jet\_pt                     & 1.127e-02 \\


 */
