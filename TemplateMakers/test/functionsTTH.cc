#include "TFile.h"
#include "TH2.h"
#include "TH2Poly.h"
#include "TGraphAsymmErrors.h"

#include <iostream>

float ttH_MVAto1D_6_2lss_Marco (float kinMVA_2lss_ttbar, float kinMVA_2lss_ttV){

  return 2*((kinMVA_2lss_ttbar>=-0.2)+(kinMVA_2lss_ttbar>=0.3))+(kinMVA_2lss_ttV>=-0.1)+1;

}
float ttH_MVAto1D_3_3l_Marco (float kinMVA_3l_ttbar, float kinMVA_3l_ttV){

  if (kinMVA_3l_ttbar<0.3 && kinMVA_3l_ttV<-0.1) return 1;
  else if (kinMVA_3l_ttbar>=0.3 && kinMVA_3l_ttV>=-0.1) return 3;
  else return 2;

}

//#include "ttH-multilepton/binning_2d_thresholds.h"
// float ttH_MVAto1D_7_2lss_Marco (float kinMVA_2lss_ttbar, float kinMVA_2lss_ttV){
// 
// //________________
// //|   |   |   | 7 |
// //|   |   | 4 |___|
// //| 1 | 2 |___| 6 |
// //|   |   |   |___|
// //|   |   | 3 | 5 |
// //|___|___|___|___|
// //
// 
//   if (kinMVA_2lss_ttbar<cuts_2lss_ttbar0) return 1;
//   else if (kinMVA_2lss_ttbar<cuts_2lss_ttbar1) return 2;
//   else if (kinMVA_2lss_ttbar<cuts_2lss_ttbar2) return 3+(kinMVA_2lss_ttV>=cuts_2lss_ttV0);
//   else return 5+(kinMVA_2lss_ttV>=cuts_2lss_ttV1)+(kinMVA_2lss_ttV>=cuts_2lss_ttV2);
// 
// }
// float ttH_MVAto1D_5_3l_Marco (float kinMVA_3l_ttbar, float kinMVA_3l_ttV){
// 
//   int reg = 2*((kinMVA_3l_ttbar>=cuts_3l_ttbar1)+(kinMVA_3l_ttbar>=cuts_3l_ttbar2))+(kinMVA_3l_ttV>=cuts_3l_ttV1)+1;
//   if (reg==2) reg=1;
//   if (reg>2) reg = reg-1;
//   return reg;
// 
// }



float ttH_MVAto1D_6_flex (float kinMVA_2lss_ttbar, float kinMVA_2lss_ttV, int pdg1, int pdg2, float ttVcut, float ttcut1, float ttcut2){

  return 2*((kinMVA_2lss_ttbar>=ttcut1)+(kinMVA_2lss_ttbar>=ttcut2)) + (kinMVA_2lss_ttV>=ttVcut)+1;

}


int ttH_catIndex_2lss(int LepGood1_pdgId, int LepGood2_pdgId, int LepGood1_charge, int nBJetMedium25){

//2lss_ee_neg
//2lss_ee_pos
//2lss_em_bl_neg
//2lss_em_bl_pos
//2lss_em_bt_neg
//2lss_em_bt_pos
//2lss_mm_bl_neg
//2lss_mm_bl_pos
//2lss_mm_bt_neg
//2lss_mm_bt_pos
   
  if (abs(LepGood1_pdgId)==11 && abs(LepGood2_pdgId)==11 && LepGood1_charge<0) return 2-1;
  if (abs(LepGood1_pdgId)==11 && abs(LepGood2_pdgId)==11 && LepGood1_charge>0) return 3-1;
  if ((abs(LepGood1_pdgId) != abs(LepGood2_pdgId)) && LepGood1_charge<0 && nBJetMedium25 < 2) return 4-1;
  if ((abs(LepGood1_pdgId) != abs(LepGood2_pdgId)) && LepGood1_charge>0 && nBJetMedium25 < 2) return 5-1;
  if ((abs(LepGood1_pdgId) != abs(LepGood2_pdgId)) && LepGood1_charge<0 && nBJetMedium25 >= 2) return 6-1;
  if ((abs(LepGood1_pdgId) != abs(LepGood2_pdgId)) && LepGood1_charge>0 && nBJetMedium25 >= 2) return 7-1;
  if (abs(LepGood1_pdgId)==13 && abs(LepGood2_pdgId)==13 && LepGood1_charge<0 && nBJetMedium25 < 2) return 8-1;
  if (abs(LepGood1_pdgId)==13 && abs(LepGood2_pdgId)==13 && LepGood1_charge>0 && nBJetMedium25 < 2) return 9-1;
  if (abs(LepGood1_pdgId)==13 && abs(LepGood2_pdgId)==13 && LepGood1_charge<0 && nBJetMedium25 >= 2) return 10-1;
  if (abs(LepGood1_pdgId)==13 && abs(LepGood2_pdgId)==13 && LepGood1_charge>0 && nBJetMedium25 >= 2) return 11-1;

 return -1;

}

int ttH_catIndex_3l(int LepGood1_charge, int LepGood2_charge, int LepGood3_charge, int nBJetMedium25){

//3l_bl_neg
//3l_bl_pos
//3l_bt_neg
//3l_bt_pos

  if ((LepGood1_charge+LepGood2_charge+LepGood3_charge)<0 && nBJetMedium25 < 2) return 11;
  if ((LepGood1_charge+LepGood2_charge+LepGood3_charge)>0 && nBJetMedium25 < 2) return 12;
  if ((LepGood1_charge+LepGood2_charge+LepGood3_charge)<0 && nBJetMedium25 >= 2) return 13;
  if ((LepGood1_charge+LepGood2_charge+LepGood3_charge)>0 && nBJetMedium25 >= 2) return 14;

 return -1;

}

TFile *_file_recoToLoose_leptonSF_mu1 = NULL;
TFile *_file_recoToLoose_leptonSF_mu2 = NULL;
TFile *_file_recoToLoose_leptonSF_mu3 = NULL;
TFile *_file_recoToLoose_leptonSF_mu4 = NULL;
TH2F *_histo_recoToLoose_leptonSF_mu1 = NULL;
TH2F *_histo_recoToLoose_leptonSF_mu2 = NULL;
TH2F *_histo_recoToLoose_leptonSF_mu3 = NULL;
TGraphAsymmErrors *_histo_recoToLoose_leptonSF_mu4 = NULL;
TFile *_file_recoToLoose_leptonSF_el = NULL;
TH2F *_histo_recoToLoose_leptonSF_el1 = NULL;
TH2F *_histo_recoToLoose_leptonSF_el2 = NULL;
TH2F *_histo_recoToLoose_leptonSF_el3 = NULL;
TFile *_file_recoToLoose_leptonSF_gsf = NULL;
TH2F *_histo_recoToLoose_leptonSF_gsf = NULL;

float _get_recoToLoose_leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var){

  if (var!=0 && abs(pdgid)!=11) assert(0); // NOT IMPLEMENTED
  
  auto cmsswprefix = getenv("CMSSW_BASE");
  TString mypfx(cmsswprefix);
  mypfx = mypfx+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/";
  
  if (!_histo_recoToLoose_leptonSF_mu1) {
    _file_recoToLoose_leptonSF_mu1 = new TFile(mypfx+"CERN/leptonSF/TnP_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root","read");
    _file_recoToLoose_leptonSF_mu2 = new TFile(mypfx+"CERN/leptonSF/TnP_NUM_MiniIsoLoose_DENOM_LooseID_VAR_map_pt_eta.root","read");
    _file_recoToLoose_leptonSF_mu3 = new TFile(mypfx+"CERN/leptonSF/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root","read");
    _file_recoToLoose_leptonSF_mu4 = new TFile(mypfx+"CERN/leptonSF/ratios_HIP_trkEff.root","read");
    _histo_recoToLoose_leptonSF_mu1 = (TH2F*)(_file_recoToLoose_leptonSF_mu1->Get("SF"));
    _histo_recoToLoose_leptonSF_mu2 = (TH2F*)(_file_recoToLoose_leptonSF_mu2->Get("SF"));
    _histo_recoToLoose_leptonSF_mu3 = (TH2F*)(_file_recoToLoose_leptonSF_mu3->Get("SF"));
    _histo_recoToLoose_leptonSF_mu4 = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu4->Get("ratio_eta"));
  }
  if (!_histo_recoToLoose_leptonSF_el1) {
    _file_recoToLoose_leptonSF_el = new TFile(mypfx+"CERN/leptonSF/el_scaleFactors_Moriond17.root","read");
    _histo_recoToLoose_leptonSF_el1 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("GsfElectronToMVAVLooseFOIDEmuTightIP2D"));
    _histo_recoToLoose_leptonSF_el2 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("MVAVLooseElectronToMini4"));
    _histo_recoToLoose_leptonSF_el3 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("MVAVLooseElectronToConvVetoIHit1"));
  }
  if (!_histo_recoToLoose_leptonSF_gsf) {
    _file_recoToLoose_leptonSF_gsf = new TFile(mypfx+"CERN/leptonSF/egammaEffi.txt_EGM2D.root","read");
    _histo_recoToLoose_leptonSF_gsf = (TH2F*)(_file_recoToLoose_leptonSF_gsf->Get("EGamma_SF2D"));
  }

  if (abs(pdgid)==13){

    float out = 1;

    TH2F *hist = _histo_recoToLoose_leptonSF_mu1;
    int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
    out *= hist->GetBinContent(ptbin,etabin);

    hist = _histo_recoToLoose_leptonSF_mu2;
    ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
    out *= hist->GetBinContent(ptbin,etabin);

    hist = _histo_recoToLoose_leptonSF_mu3;
    ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
    out *= hist->GetBinContent(ptbin,etabin);

    TGraphAsymmErrors *hist1 = _histo_recoToLoose_leptonSF_mu4;
    float eta1 = std::max(float(hist1->GetXaxis()->GetXmin()+1e-5), std::min(float(hist1->GetXaxis()->GetXmax()-1e-5), eta));
    out *= hist1->Eval(eta1);

    return out;

  }

  if (abs(pdgid)==11){
    TH2F *hist = _histo_recoToLoose_leptonSF_el1;
    int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(eta)));
    float out = hist->GetBinContent(ptbin,etabin)+var*hist->GetBinError(ptbin,etabin);
    hist = _histo_recoToLoose_leptonSF_el2;
    ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(eta)));
    out *= hist->GetBinContent(ptbin,etabin)+var*hist->GetBinError(ptbin,etabin);
    hist = _histo_recoToLoose_leptonSF_el3;
    ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(eta)));
    out *= hist->GetBinContent(ptbin,etabin)+var*hist->GetBinError(ptbin,etabin);

    hist = _histo_recoToLoose_leptonSF_gsf;
    etabin = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(eta))); // careful, different convention
    ptbin  = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(pt)));
    out *= (hist->GetBinContent(etabin,ptbin)+var*(hist->GetBinError(ptbin,etabin) + 0.01*((pt<20) || (pt>80))));

    return out;
  }

  assert(0);
  return -999;

}

TFile *_file_looseToTight_leptonSF_mu_2lss = NULL;
TH2F *_histo_looseToTight_leptonSF_mu_2lss = NULL;
TFile *_file_looseToTight_leptonSF_el_2lss = NULL;
TH2F *_histo_looseToTight_leptonSF_el_2lss = NULL;
TFile *_file_looseToTight_leptonSF_mu_3l = NULL;
TH2F *_histo_looseToTight_leptonSF_mu_3l = NULL;
TFile *_file_looseToTight_leptonSF_el_3l = NULL;
TH2F *_histo_looseToTight_leptonSF_el_3l = NULL;

float _get_looseToTight_leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var){

  if (var!=0) assert(0); // NOT IMPLEMENTED

  auto cmsswprefix = getenv("CMSSW_BASE");
  TString mypfx(cmsswprefix);
  mypfx = mypfx+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/";

  if (!_histo_looseToTight_leptonSF_mu_2lss) {
    _file_looseToTight_leptonSF_mu_2lss = new TFile(mypfx+"CERN/leptonSF/lepMVAEffSF_m_2lss.root","read");
    _histo_looseToTight_leptonSF_mu_2lss = (TH2F*)(_file_looseToTight_leptonSF_mu_2lss->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_el_2lss) {
    _file_looseToTight_leptonSF_el_2lss = new TFile(mypfx+"CERN/leptonSF/lepMVAEffSF_e_2lss.root","read");
    _histo_looseToTight_leptonSF_el_2lss = (TH2F*)(_file_looseToTight_leptonSF_el_2lss->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_mu_3l) {
    _file_looseToTight_leptonSF_mu_3l = new TFile(mypfx+"CERN/leptonSF/lepMVAEffSF_m_3l.root","read");
    _histo_looseToTight_leptonSF_mu_3l = (TH2F*)(_file_looseToTight_leptonSF_mu_3l->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_el_3l) {
    _file_looseToTight_leptonSF_el_3l = new TFile(mypfx+"CERN/leptonSF/lepMVAEffSF_e_3l.root","read");
    _histo_looseToTight_leptonSF_el_3l = (TH2F*)(_file_looseToTight_leptonSF_el_3l->Get("sf"));
  }

  TH2F *hist = 0;
  if (abs(pdgid)==13) hist = (nlep>2) ? _histo_looseToTight_leptonSF_mu_3l : _histo_looseToTight_leptonSF_mu_2lss;
  else if (abs(pdgid)==11) hist = (nlep>2) ? _histo_looseToTight_leptonSF_el_3l : _histo_looseToTight_leptonSF_el_2lss;
  assert(hist);
  int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
  int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
  return hist->GetBinContent(ptbin,etabin);

}

float leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var=0){

  float recoToLoose = _get_recoToLoose_leptonSF_ttH(pdgid,pt,eta,nlep,var);
  float looseToTight = _get_looseToTight_leptonSF_ttH(pdgid,pt,eta,nlep,var);
  float res = recoToLoose*looseToTight;
  assert (res>0);
  return res;

}

//TFile *file_triggerSF_ttH = NULL;
//TH2Poly* t2poly_triggerSF_ttH_mm = NULL;
//TH2Poly* t2poly_triggerSF_ttH_ee = NULL;
//TH2Poly* t2poly_triggerSF_ttH_em = NULL;
//TH2Poly* t2poly_triggerSF_ttH_3l = NULL;

float triggerSF_ttH(int pdgid1, int pdgid2, int nlep){
  
  if (nlep>=3) return 1;
  
  int comb = abs(pdgid1)+abs(pdgid2);
  if (comb==22) return 1.01; // ee
  else if (comb==24) return 1.01; // em
  else if (comb==26) return 1; // mm

  return 1;

}

// for json up to 276811 (12.9/fb), pu true reweighting
float _puw2016_nTrueInt_13fb[60] = {0.0004627598152210959, 0.014334910915287028, 0.01754727657726197, 0.03181477917631854, 0.046128282569231016, 0.03929080994013006, 0.057066019809589925, 0.19570744862221007, 0.3720256062526554, 0.6440076202772811, 0.9218024454406528, 1.246743510634073, 1.5292543296414058, 1.6670061646418215, 1.7390553377117133, 1.6114721876895595, 1.4177294439817985, 1.420132866045718, 1.3157656415540477, 1.3365188060918483, 1.1191478126677334, 0.9731079434848392, 0.9219564145009487, 0.8811793391804676, 0.7627315352977334, 0.7265186492688713, 0.558602385324645, 0.4805954159733825, 0.34125298049234554, 0.2584848657646724, 0.1819638766151892, 0.12529545619337035, 0.11065705912071645, 0.08587356267495487, 0.09146322371620583, 0.11885517671051576, 0.1952483711863489, 0.23589115679998116, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
float puw2016_nTrueInt_13fb(int nTrueInt) { if (nTrueInt<60) return _puw2016_nTrueInt_13fb[nTrueInt]; else return 0; }

float _puw2016_nTrueInt_36fb[100] = {0.3505407355600995, 0.8996968628890968, 1.100322319466069, 0.9562526765089195, 1.0366251229154624, 1.0713954619016586, 0.7593488199769544, 0.47490309461978414, 0.7059895997695581, 0.8447022252423783, 0.9169159386164522, 1.0248924033173097, 1.0848877947714115, 1.1350984224561655, 1.1589888429954602, 1.169048420382294, 1.1650383018054549, 1.1507200023444994, 1.1152571438041776, 1.0739529436969637, 1.0458014000030829, 1.032500407707141, 1.0391236062781293, 1.041283620738903, 1.0412963370894526, 1.0558823002770783, 1.073481674823461, 1.0887053272606795, 1.1041701696801014, 1.123218903738397, 1.1157169321377927, 1.1052520327174429, 1.0697489590429388, 1.0144652740600584, 0.9402657069968621, 0.857142825520793, 0.7527112615290031, 0.6420618248685722, 0.5324755829715156, 0.4306470627563325, 0.33289171600176093, 0.24686361729094983, 0.17781595237914027, 0.12404411884835284, 0.08487088505600057, 0.056447805688061216, 0.03540829360547507, 0.022412461576677457, 0.013970541270658443, 0.008587896629717911, 0.004986410514292661, 0.00305102303701641, 0.001832072556146534, 0.0011570757619737708, 0.0008992999249003301, 0.0008241241729452477, 0.0008825716073180279, 0.001187003960081393, 0.0016454104270429153, 0.0022514113879764414, 0.003683196037880878, 0.005456695951503178, 0.006165248770884191, 0.007552675218762607, 0.008525338219226993, 0.008654690499815343, 0.006289068906974821, 0.00652551838513972, 0.005139581024893171, 0.005115751962934923, 0.004182527768384693, 0.004317593022028565, 0.0035749335962533355, 0.003773660372937113, 0.002618732319396435, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
float puw2016_nTrueInt_36fb(int nTrueInt) { if (nTrueInt<100) return _puw2016_nTrueInt_36fb[nTrueInt]; else return 0; }



//float triggerSF_ttH(int pdgid1, float pt1, int pdgid2, float pt2, int nlep, float var=0){
//
//  if (!file_triggerSF_ttH) {
//    file_triggerSF_ttH = new TFile("../../data/triggerSF/trig_eff_map_v4.root");
//    t2poly_triggerSF_ttH_mm = (TH2Poly*)(file_triggerSF_ttH->Get("SSuu2DPt_effic"));
//    t2poly_triggerSF_ttH_ee = (TH2Poly*)(file_triggerSF_ttH->Get("SSee2DPt__effic"));
//    t2poly_triggerSF_ttH_em = (TH2Poly*)(file_triggerSF_ttH->Get("SSeu2DPt_effic"));
//    t2poly_triggerSF_ttH_3l = (TH2Poly*)(file_triggerSF_ttH->Get("__3l2DPt_effic"));
//    if (!(t2poly_triggerSF_ttH_mm && t2poly_triggerSF_ttH_ee && t2poly_triggerSF_ttH_em && t2poly_triggerSF_ttH_3l)) {
//	std::cout << "Impossible to load trigger scale factors!" << std::endl;
//	file_triggerSF_ttH->ls();
//	file_triggerSF_ttH = NULL;
//      }
//  }
//  TH2Poly* hist = NULL;
//  if (nlep==2){
//    if (abs(pdgid1)==13 && abs(pdgid2)==13) hist = t2poly_triggerSF_ttH_mm;
//    else if (abs(pdgid1)==11 && abs(pdgid2)==11) hist = t2poly_triggerSF_ttH_ee;
//    else hist = t2poly_triggerSF_ttH_em;
//  }
//  else if (nlep==3) hist = t2poly_triggerSF_ttH_3l;
//  else std::cout << "Wrong options to trigger scale factors" << std::endl;
//  pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt1));
//  pt2 = std::max(float(hist->GetYaxis()->GetXmin()+1e-5), std::min(float(hist->GetYaxis()->GetXmax()-1e-5), pt2));
//  int bin = hist->FindBin(pt1,pt2);
//  float eff = hist->GetBinContent(bin) + var * hist->GetBinError(bin);
//
//  if (nlep>2) return eff;
//  int cat = (abs(pdgid1)==11) + (abs(pdgid2)==11);
//  if (cat==2) return eff*1.02;
//  else if (cat==1) return eff*1.02;
//  else return eff*1.01;
//
//
//}
