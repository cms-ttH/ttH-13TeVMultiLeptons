class FakeRateEvaluator
{
#include "TH2F.h"
#include "TFile.h"
 private:
  TH2F *mu_fr_data;
  TH2F *ele_fr_data;
  TH2F *flip_data;
 public:
  FakeRateEvaluator(void){};//default constructor

  void loadWeights(void){
    
    TFile *lepMVA_fr_file = new TFile("../data/CERN/fakerate/FR_data_ttH_mva.root","READONLY");
    mu_fr_data = (TH2F*)lepMVA_fr_file->Get("FR_mva090_mu_data_comb");
    ele_fr_data = (TH2F*)lepMVA_fr_file->Get("FR_mva090_el_data_comb_NC");
    mu_fr_data->SetDirectory(0); //reads hists into memory
    ele_fr_data->SetDirectory(0);
    lepMVA_fr_file->Close();

    TFile *flips_file = new TFile("../data/CERN/fakerate/QF_data_el.root","READONLY");
    flip_data = (TH2F*)flips_file->Get("chargeMisId");
    flip_data->SetDirectory(0);//
    flips_file->Close();
  }

  double get_fr(vector<ttH::Lepton> fakeableLeps)
  {
    std::sort(fakeableLeps.begin(), fakeableLeps.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.correctedPt > b.correctedPt;});
    double fr_weight = 1.;
    int bin;
    int count = 0;
    for (unsigned int i=0; i<=1; i++)
      {
	
	if (fakeableLeps[i].obj.pt() != fakeableLeps[i].correctedPt)
	  {
	    
	    if (abs(fakeableLeps[i].pdgID) == 11)
	      {
		bin = ele_fr_data->FindBin( min(99.,fakeableLeps[i].correctedPt), abs(fakeableLeps[i].obj.eta()));
		fr_weight *= ele_fr_data->GetBinContent(bin)/(1.-ele_fr_data->GetBinContent(bin));
		count ++;
	      }
	    else if (abs(fakeableLeps[i].pdgID) == 13)
	      {
		bin = mu_fr_data->FindBin( min(99.,fakeableLeps[i].correctedPt), abs(fakeableLeps[i].obj.eta()));
		fr_weight *= mu_fr_data->GetBinContent(bin)/(1.-mu_fr_data->GetBinContent(bin));
		count ++;
	      }
	  }
      }
    
    //if (fr_weight == 0) cout << "HELPPPPPPPP " << count << endl;
    if (count ==2 ) return -1.*fr_weight;
    else return fr_weight;

  }


  double flipProb(vector<ttH::Lepton> leps)
  {

    double flip_prob = 0.;
    int count = 0;
    int bin;

    for (const auto & lep: leps)
      {
	if (count >= 2) break; //only first two leps for 2lss
	if (abs(lep.pdgID) == 11)
	  {	    
	    bin = flip_data->FindBin( min(900.,lep.obj.pt()), abs(lep.obj.eta()));
	    flip_prob += flip_data->GetBinContent(bin);
	  }
	count ++;
      }
    return flip_prob;
  }
  

  virtual ~FakeRateEvaluator(){};
};
