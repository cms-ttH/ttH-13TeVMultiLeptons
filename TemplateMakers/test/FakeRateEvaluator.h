class FakeRateEvaluator
{
 #include "TH2F.h"
 #include "TFile.h"
 private:
  TH2F *mu_fr_data;
  TH2F *ele_fr_data;
 public:
  FakeRateEvaluator(){
    
    TFile *lepMVA_fr_file = new TFile("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/TemplateMakers/test/FR_data_ttH_mva.root","READONLY");
    mu_fr_data = (TH2F*)lepMVA_fr_file->Get("FR_mva075_mu_data_comb");
    ele_fr_data = (TH2F*)lepMVA_fr_file->Get("FR_mva075_el_data_comb");
    mu_fr_data->SetDirectory(0); //reads hists into memory
    ele_fr_data->SetDirectory(0);
    lepMVA_fr_file->Close();

  };//default constructor

  double get_fr(vector<ttH::Lepton> fakeableLeps)
  {
    std::sort(fakeableLeps.begin(), fakeableLeps.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.correctedPt > b.correctedPt;});
    double fr_weight = 1.;
    int bin;
    for (unsigned int i=0; i <=1; i++)
      {
	bool isTight = false;	
	if (fakeableLeps[i].obj.pt() == fakeableLeps[i].correctedPt) isTight = true;

	if (!isTight)
	  {
	    if (abs(fakeableLeps[i].pdgID) == 11)
	      {
		bin = ele_fr_data->FindBin( min(99.,fakeableLeps[i].correctedPt), abs(fakeableLeps[i].obj.eta()));
		fr_weight *= ele_fr_data->GetBinContent(bin)/(1.-ele_fr_data->GetBinContent(bin));
	      }
	    else if (abs(fakeableLeps[i].pdgID) == 13)
	      {
		bin = mu_fr_data->FindBin( min(99.,fakeableLeps[i].correctedPt), abs(fakeableLeps[i].obj.eta()));
		fr_weight *= mu_fr_data->GetBinContent(bin)/(1.-mu_fr_data->GetBinContent(bin));
	      }
	  }
      }

    return fr_weight;

  }


  double flipProb(vector<ttH::Lepton> leps)
  {
    double flip_prob = 0.;
    int count = 0;
    for (const auto & lep: leps)
      {
	if (count >= 2) break; //only first two leps for 2lss
	if (abs(lep.pdgID) == 11)
	  {
	    if (lep.obj.pt() < 25)
	      {
		if (abs(lep.obj.eta()) < 1.479)	flip_prob += 0.0442;
		else flip_prob += 0.1329;
	      }
	    else if (lep.obj.pt() < 50)
	      {
		if (abs(lep.obj.eta()) < 1.479)	flip_prob += 0.0179;
		else flip_prob += 0.1898;
	      }
	    else 
	      {
		if (abs(lep.obj.eta()) < 1.479)	flip_prob += 0.0262;
		else flip_prob += 0.3067;
	      }
	  }
	count ++;
      }
    if (flip_prob == 0.) return 1.;
    else return flip_prob;
  }
  

  virtual ~FakeRateEvaluator(){};
};
