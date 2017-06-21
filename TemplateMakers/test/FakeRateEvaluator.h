class FakeRateEvaluator
{
#include "TH2F.h"
#include "TFile.h"
 private:
  TH2F *FR_mva090_mu_data_comb_hist;
  TH2F *FR_mva090_mu_data_comb_up_hist;
  TH2F *FR_mva090_mu_data_comb_down_hist;
  TH2F *FR_mva090_mu_data_comb_pt1_hist;
  TH2F *FR_mva090_mu_data_comb_pt2_hist;
  TH2F *FR_mva090_mu_data_comb_be1_hist;
  TH2F *FR_mva090_mu_data_comb_be2_hist;
  TH2F *FR_mva090_el_data_comb_NC_hist;
  TH2F *FR_mva090_el_data_comb_NC_up_hist;
  TH2F *FR_mva090_el_data_comb_NC_down_hist;
  TH2F *FR_mva090_el_data_comb_NC_pt1_hist;
  TH2F *FR_mva090_el_data_comb_NC_pt2_hist;
  TH2F *FR_mva090_el_data_comb_NC_be1_hist;
  TH2F *FR_mva090_el_data_comb_NC_be2_hist;
  TH2F *chargeMisId_hist;

  double fr_mva090_intree;
  double fr_mva090_up_intree;
  double fr_mva090_down_intree;
  double fr_mva090_pt1_intree;
  double fr_mva090_pt2_intree;
  double fr_mva090_be1_intree;
  double fr_mva090_be2_intree;
  double chargeMisId_intree;

  double get_fakeRate(vector<ttH::Lepton> leps, TH2F* mu_fake_h, TH2F* el_fake_h)
  {
    double fr_weight = 1.;
    int bin;
    int count = 0;
    for (const auto & lep: leps)
      {
	if ( float(lep.obj.pt()) == float(lep.correctedPt) ) continue;
	float _f = 0.;

	if (abs(lep.pdgID) == 11)
	  {
	    bin = el_fake_h->FindBin( min(99.,lep.correctedPt), min(abs(lep.obj.eta()),2.49) );
	    _f = el_fake_h->GetBinContent(bin);
	  }
	else
	  {
	    bin = mu_fake_h->FindBin( min(99., lep.correctedPt ), min(abs(lep.obj.eta()),2.39) );
	    _f = mu_fake_h->GetBinContent(bin);
	  }
	fr_weight *= _f/(1.-_f);
	count +=1;
      }
    
    if (count >0) fr_weight *= pow(-1.,count+1);
    return fr_weight; 
  }
  
 public:
  FakeRateEvaluator(void){
    TFile *lepMVA_fr_file = new TFile("../data/CERN/fakerate/FR_data_ttH_mva.root","READONLY");
    FR_mva090_mu_data_comb_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_mu_data_comb");
    FR_mva090_mu_data_comb_up_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_mu_data_comb_up");
    FR_mva090_mu_data_comb_down_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_mu_data_comb_down");
    FR_mva090_mu_data_comb_pt1_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_mu_data_comb_pt1");
    FR_mva090_mu_data_comb_pt2_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_mu_data_comb_pt2");
    FR_mva090_mu_data_comb_be1_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_mu_data_comb_be1");
    FR_mva090_mu_data_comb_be2_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_mu_data_comb_be2");
    FR_mva090_el_data_comb_NC_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_el_data_comb_NC");
    FR_mva090_el_data_comb_NC_up_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_el_data_comb_NC_up");
    FR_mva090_el_data_comb_NC_down_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_el_data_comb_NC_down");
    FR_mva090_el_data_comb_NC_pt1_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_el_data_comb_NC_pt1");
    FR_mva090_el_data_comb_NC_pt2_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_el_data_comb_NC_pt2");
    FR_mva090_el_data_comb_NC_be1_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_el_data_comb_NC_be1");
    FR_mva090_el_data_comb_NC_be2_hist = (TH2F*)lepMVA_fr_file->Get("FR_mva090_el_data_comb_NC_be2");

    //reads hists into memory
    FR_mva090_mu_data_comb_hist->SetDirectory(0);
    FR_mva090_mu_data_comb_up_hist->SetDirectory(0);
    FR_mva090_mu_data_comb_down_hist->SetDirectory(0);
    FR_mva090_mu_data_comb_pt1_hist->SetDirectory(0);
    FR_mva090_mu_data_comb_pt2_hist->SetDirectory(0);
    FR_mva090_mu_data_comb_be1_hist->SetDirectory(0);    
    FR_mva090_mu_data_comb_be2_hist->SetDirectory(0);
    FR_mva090_el_data_comb_NC_hist->SetDirectory(0);
    FR_mva090_el_data_comb_NC_up_hist->SetDirectory(0);
    FR_mva090_el_data_comb_NC_down_hist->SetDirectory(0);
    FR_mva090_el_data_comb_NC_pt1_hist->SetDirectory(0);
    FR_mva090_el_data_comb_NC_pt2_hist->SetDirectory(0);
    FR_mva090_el_data_comb_NC_be1_hist->SetDirectory(0);
    FR_mva090_el_data_comb_NC_be2_hist->SetDirectory(0);

    lepMVA_fr_file->Close();

    TFile *flips_file = new TFile("../data/CERN/fakerate/QF_data_el.root","READONLY");
    chargeMisId_hist = (TH2F*)flips_file->Get("chargeMisId");
    chargeMisId_hist->SetDirectory(0);//
    flips_file->Close();
  };//default constructor

  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("fr_mva090", &fr_mva090_intree);
    input_tree->Branch("fr_mva090_up", &fr_mva090_up_intree);
    input_tree->Branch("fr_mva090_down", &fr_mva090_down_intree);
    input_tree->Branch("fr_mva090_pt1", &fr_mva090_pt1_intree);
    input_tree->Branch("fr_mva090_pt2", &fr_mva090_pt2_intree);
    input_tree->Branch("fr_mva090_be1", &fr_mva090_be1_intree);
    input_tree->Branch("fr_mva090_be2", &fr_mva090_be2_intree);
    input_tree->Branch("chargeMisId", &chargeMisId_intree);
  }


  void addFakeRates(vector<ttH::Lepton> fakeableLeps)
  {
    std::sort(fakeableLeps.begin(), fakeableLeps.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.correctedPt > b.correctedPt;});
    
    fr_mva090_intree = get_fakeRate(fakeableLeps,FR_mva090_mu_data_comb_hist,FR_mva090_el_data_comb_NC_hist);
    fr_mva090_up_intree = get_fakeRate(fakeableLeps,FR_mva090_mu_data_comb_up_hist,FR_mva090_el_data_comb_NC_up_hist);
    fr_mva090_down_intree = get_fakeRate(fakeableLeps,FR_mva090_mu_data_comb_down_hist,FR_mva090_el_data_comb_NC_down_hist);
    fr_mva090_pt1_intree = get_fakeRate(fakeableLeps,FR_mva090_mu_data_comb_pt1_hist,FR_mva090_el_data_comb_NC_pt1_hist);
    fr_mva090_pt2_intree = get_fakeRate(fakeableLeps,FR_mva090_mu_data_comb_pt2_hist,FR_mva090_el_data_comb_NC_pt2_hist);
    fr_mva090_be1_intree = get_fakeRate(fakeableLeps,FR_mva090_mu_data_comb_be1_hist,FR_mva090_el_data_comb_NC_be1_hist);
    fr_mva090_be2_intree = get_fakeRate(fakeableLeps,FR_mva090_mu_data_comb_be2_hist,FR_mva090_el_data_comb_NC_be2_hist);
    
  }

  void addFlipRates(vector<ttH::Lepton> leps)
  {
    chargeMisId_intree = 0.;
    int count = 0;
    int bin;
    
    for (const auto & lep: leps)
      {
	if (count >= 2) break; //only first two leps for 2lss
	if (abs(lep.pdgID) == 11)
	  {	    
	    bin = chargeMisId_hist->FindBin( min(900.,lep.obj.pt()), abs(lep.obj.eta()));
	    chargeMisId_intree += chargeMisId_hist->GetBinContent(bin);
	  }
	count ++;
      }
  }
  
  
  

  virtual ~FakeRateEvaluator(){};
};
