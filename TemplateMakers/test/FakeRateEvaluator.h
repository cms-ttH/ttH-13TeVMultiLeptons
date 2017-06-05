class FakeRateEvaluator
{
#include "TH2F.h"
#include "TFile.h"
 private:
  TH2F *mu_fr_data;
  TH2F *ele_fr_data;
  TH2F *flip_data;

  bool isMedium(ttH::Muon in_mu)
  {
    bool goodGlob = in_mu.isGlobalMuon &&
      in_mu.normalizedChi2 < 3 &&
      in_mu.localChi2 < 12 &&
      in_mu.trKink < 20;
    bool isMedium_ = in_mu.validFrac > 0.8 &&
      in_mu.segCompatibility > (goodGlob ? 0.303 : 0.451);
    return isMedium_;
  }

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

  double get_fr(vector<ttH::Lepton> fakeableLeps, vector<ttH::Electron> fakeableEles, vector<ttH::Muon> fakeableMus)
  {
    std::sort(fakeableLeps.begin(), fakeableLeps.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.correctedPt > b.correctedPt;});
    double fr_weight = 1.;
    int bin;
    int count = 0;


    for (const auto & lep: fakeableLeps)
      {
	//if (count > 1) break;
	//if (lep.lepMVA >=0.9 ) continue;
	if ( float(lep.obj.pt()) == float(lep.correctedPt) ) continue;
	//if (abs(lep.pdgID)==11 && lep.lepMVA >=0.9 ) continue;
	//else if (abs(lep.pdgID)==13 && lep.obj.pt() == lep.correctedPt)
	  {
	    /* bool isTight = false; */
	    /* for (const auto & mu: fakeableMus) */
	    /*   { */
	    /* 	if (lep.obj.pt() == mu.obj.pt() && lep.lepMVA >=0.9  && isMedium(mu)) */
	    /* 	  { */
	    /* 	    isTight = true; */
	    /* 	    break; */
	    /* 	  } */
	    /*   } */
	    /* if (isTight) continue; */
	    //continue;
	  }
	float _f = 0.;

	if (abs(lep.pdgID) == 11)
	  {

	    bin = ele_fr_data->FindBin( min(99.,lep.correctedPt), min(abs(lep.obj.eta()),2.49) );
	    _f = ele_fr_data->GetBinContent(bin);
	  }
	else
	  {
	    
	    for (const auto & mu: fakeableMus)
	      {
		if (lep.obj.pt() == mu.obj.pt())
		  {
		    if (mu.chargeFlip > 0.2) return 0.;
		  }
	      }

	    double pt = 0.9*lep.obj.pt()/lep.jetPtRatio;
	    bin = mu_fr_data->FindBin( min(99., pt ), min(abs(lep.obj.eta()),2.39) );
	    _f = mu_fr_data->GetBinContent(bin);
	  }
	fr_weight *= _f/(1.-_f);
	count +=1;
      }
    
    if (count >0) fr_weight *= pow(-1.,count+1);
    return fr_weight;
  }
  /* for (unsigned int i=0; i<=1; i++) */
    /*   { */
	
    /* 	if (fakeableLeps[i].obj.pt() != fakeableLeps[i].correctedPt) */
    /* 	  { */
	    
    /* 	    if (abs(fakeableLeps[i].pdgID) == 11) */
    /* 	      { */
    /* 		bin = ele_fr_data->FindBin( min(99.,fakeableLeps[i].correctedPt), abs(fakeableLeps[i].obj.eta())); */
    /* 		fr_weight *= ele_fr_data->GetBinContent(bin)/(1.-ele_fr_data->GetBinContent(bin)); */
    /* 		count ++; */
    /* 	      } */
    /* 	    else if (abs(fakeableLeps[i].pdgID) == 13) */
    /* 	      { */
    /* 		bin = mu_fr_data->FindBin( min(99.,fakeableLeps[i].correctedPt), abs(fakeableLeps[i].obj.eta())); */
    /* 		fr_weight *= mu_fr_data->GetBinContent(bin)/(1.-mu_fr_data->GetBinContent(bin)); */
    /* 		count ++; */
    /* 	      } */
    /* 	  } */
    /*   } */
    
    /* //if (fr_weight == 0) cout << "HELPPPPPPPP " << count << endl; */
    /* if (count ==2 ) return -1.*fr_weight; */
    /* else return fr_weight; */
    //}


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
