#ifndef _ScaleFactorApplicator_h
#define _ScaleFactorApplicator_h

#include "TObject.h"
#include "TH2Poly.h"
#include "TGraphAsymmErrors.h"

class LeptonSF
{
 private:
  double triggerSF_intree;
  double leptonSF_intree;
  
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

  TFile *_file_looseToTight_leptonSF_mu_2lss = NULL;
  TH2F *_histo_looseToTight_leptonSF_mu_2lss = NULL;
  TFile *_file_looseToTight_leptonSF_el_2lss = NULL;
  TH2F *_histo_looseToTight_leptonSF_el_2lss = NULL;

  double _get_recoToLoose_leptonSF_ttH(int pdgid, float pt, float eta, float var=0.)
  {
    
    //var = 0. (no systs)

    if (abs(pdgid) == 13)
      {  
	double out = 1;
	
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
	double eta1 = std::max(float(hist1->GetXaxis()->GetXmin()+1e-5), std::min(float(hist1->GetXaxis()->GetXmax()-1e-5), eta));
	out *= hist1->Eval(eta1);
	
	return out;
      }
    
    if (abs(pdgid) == 11)
      {
	TH2F *hist = _histo_recoToLoose_leptonSF_el1;
	int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
	int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(eta)));
	double out = hist->GetBinContent(ptbin,etabin)+var*hist->GetBinError(ptbin,etabin);
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
    
    std::cout << "ERROR" << std::endl;
    std::abort();
    return -999;
  }
  
  double _get_looseToTight_leptonSF_ttH(int pdgid, float pt, float eta)
  {
    TH2F *hist = 0;
    if (abs(pdgid)==13) hist = _histo_looseToTight_leptonSF_mu_2lss;
    else if (abs(pdgid)==11) hist = _histo_looseToTight_leptonSF_el_2lss;
    if (!hist) {std::cout << "ERROR" << std::endl; std::abort();}
    int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
    return hist->GetBinContent(ptbin,etabin);
  }  
  


 public:
  LeptonSF(void){

    //loose eff
    if (!_histo_recoToLoose_leptonSF_mu1) {
      _file_recoToLoose_leptonSF_mu1 = new TFile("../data/CERN/leptonSF/TnP_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root","read");
      _file_recoToLoose_leptonSF_mu2 = new TFile("../data/CERN/leptonSF/TnP_NUM_MiniIsoLoose_DENOM_LooseID_VAR_map_pt_eta.root","read");
      _file_recoToLoose_leptonSF_mu3 = new TFile("../data/CERN/leptonSF/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root","read");
      _file_recoToLoose_leptonSF_mu4 = new TFile("../data/CERN/leptonSF/Tracking_EfficienciesAndSF_BCDEFGH.root","read");
      _histo_recoToLoose_leptonSF_mu1 = (TH2F*)(_file_recoToLoose_leptonSF_mu1->Get("SF"));
      _histo_recoToLoose_leptonSF_mu2 = (TH2F*)(_file_recoToLoose_leptonSF_mu2->Get("SF"));
      _histo_recoToLoose_leptonSF_mu3 = (TH2F*)(_file_recoToLoose_leptonSF_mu3->Get("SF"));
      _histo_recoToLoose_leptonSF_mu4 = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu4->Get("ratio_eff_eta3_dr030e030_corr"));
      
    }
    if (!_histo_recoToLoose_leptonSF_el1) {
      _file_recoToLoose_leptonSF_el = new TFile("../data/CERN/leptonSF/el_scaleFactors_Moriond17.root","readonly");
      _histo_recoToLoose_leptonSF_el1 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("GsfElectronToMVAVLooseFOIDEmuTightIP2D"));
      _histo_recoToLoose_leptonSF_el2 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("MVAVLooseElectronToMini4"));
      _histo_recoToLoose_leptonSF_el3 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("MVAVLooseElectronToConvVetoIHit1"));
    }
    if (!_histo_recoToLoose_leptonSF_gsf) {
      _file_recoToLoose_leptonSF_gsf = new TFile("../data/CERN/leptonSF/egammaEffi.txt_EGM2D.root","readonly");
      _histo_recoToLoose_leptonSF_gsf = (TH2F*)(_file_recoToLoose_leptonSF_gsf->Get("EGamma_SF2D"));
    }
    
    //tight eff
    if (!_histo_looseToTight_leptonSF_mu_2lss) {
      _file_looseToTight_leptonSF_mu_2lss = new TFile("../data/CERN/leptonSF/lepMVAEffSF_m_2lss.root","readonly");
      _histo_looseToTight_leptonSF_mu_2lss = (TH2F*)(_file_looseToTight_leptonSF_mu_2lss->Get("sf"));
    }
    if (!_histo_looseToTight_leptonSF_el_2lss) {
      _file_looseToTight_leptonSF_el_2lss = new TFile("../data/CERN/leptonSF/lepMVAEffSF_e_2lss.root","readonly");
      _histo_looseToTight_leptonSF_el_2lss = (TH2F*)(_file_looseToTight_leptonSF_el_2lss->Get("sf"));
    }
    
    
  } // default constructor

  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("trigger_SF", &triggerSF_intree);
    input_tree->Branch("lepton_SF", &leptonSF_intree);
  }


  void addTriggerSF(const vector<ttH::Lepton> *leptons_in)
  {
    int comb = abs((*leptons_in)[0].pdgID) + abs((*leptons_in)[1].pdgID);
    triggerSF_intree = 1.;
    if (comb==22) triggerSF_intree = 1.01; // ee
    else if (comb==24) triggerSF_intree = 1.01; // em
    else if (comb==26) triggerSF_intree = 1; // mm
  }

  void addLeptonSF(const vector<ttH::Lepton> *leptons_in)
  {
    leptonSF_intree = 1.;
    double looseSF;
    double tightSF;
    for (const auto & lep: *leptons_in)
      {
	looseSF = _get_recoToLoose_leptonSF_ttH(lep.pdgID,lep.obj.pt(),lep.obj.eta());
	tightSF = _get_looseToTight_leptonSF_ttH(lep.pdgID,lep.obj.pt(),lep.obj.eta());
	leptonSF_intree *= looseSF*tightSF;
      }
  }
  

  virtual ~LeptonSF(){};
};

#endif // _ScaleFactorApplicator_h
