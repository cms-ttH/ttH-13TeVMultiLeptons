#ifndef _TightChargeAndLepMVAScaleFactorsPerLepton_h
#define _TightChargeAndLepMVAScaleFactorsPerLepton_h

class TightChargeAndLepMVAScaleFactorsPerLepton: public KinematicVariable<double> {

public:
  TightChargeAndLepMVAScaleFactorsPerLepton(int _numLeps, BNleptonCollection **_tightLoosePreselectedLeptons);
  ~TightChargeAndLepMVAScaleFactorsPerLepton();
  void evaluate();
  double fetch(BNlepton* lepton, TH2D* histo);

  TFile electronFile;
  TFile muonFile;
  TH2D* looseElectron2DSF;
  TH2D* looseMuon2DSF;
  TH2D* tightElectron2DSF;
  TH2D* tightMuon2DSF;
  TH2D* tightChargeElectronSF2D;
  TH2D* tightChargeMuonSF2D;
  unsigned int numLeps;
  TString looseBranchName[6];
  TString tightBranchName[6];
  TString tightChargeBranchName[6];
  BNleptonCollection **tightLoosePreselectedLeptons;

};

TightChargeAndLepMVAScaleFactorsPerLepton::TightChargeAndLepMVAScaleFactorsPerLepton (int _numLeps, BNleptonCollection **_tightLoosePreselectedLeptons):
  electronFile((string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/CERN/lepMVA_weights/MVAandTightChargeSF_ele.root").c_str()),
  muonFile((string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/CERN/lepMVA_weights/MVAandTightChargeSF_mu.root").c_str()),
  numLeps(_numLeps),
  tightLoosePreselectedLeptons(_tightLoosePreselectedLeptons)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

  looseElectron2DSF = (TH2D*)electronFile.Get("LepMVALooseSF2D")->Clone("LepMVALooseSF2D_ele");
  looseMuon2DSF = (TH2D*)muonFile.Get("LepMVALooseSF2D")->Clone("LepMVALooseSF2D_mu");
  tightElectron2DSF = (TH2D*)electronFile.Get("LepMVATightSF2D")->Clone("LepMVATightSF2D_ele");
  tightMuon2DSF = (TH2D*)muonFile.Get("LepMVATightSF2D")->Clone("LepMVATightSF2D_mu");
  tightChargeElectronSF2D = (TH2D*)electronFile.Get("TightChargeSF2D")->Clone("TightChargeSF2D_ele");
  tightChargeMuonSF2D = (TH2D*)muonFile.Get("TightChargeSF2D")->Clone("TightChargeSF2D_mu");

  for (unsigned int i=0; i<numLeps; i++) {
    looseBranchName[i] = Form("lepMVALooseSF_Lep%d", i+1);
    tightBranchName[i] = Form("lepMVATightSF_Lep%d", i+1);
    tightChargeBranchName[i] = Form("tightChargeSF_Lep%d", i+1);
    branches[looseBranchName[i]] = BranchInfo<double>(looseBranchName[i]);
    branches[tightBranchName[i]] = BranchInfo<double>(tightBranchName[i]);
    branches[tightChargeBranchName[i]] = BranchInfo<double>(tightChargeBranchName[i]);
  }
}

void TightChargeAndLepMVAScaleFactorsPerLepton::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BNleptonCollection * leptons = *tightLoosePreselectedLeptons;
  double looseSF = 1.0;
  double tightSF = 1.0;
  double tightChargeSF = 1.0;
  for (unsigned int i=0; i<numLeps; i++) {
    if (leptons->at(i)->isMuon) {
      looseSF = fetch(leptons->at(i), looseMuon2DSF);
      tightSF = fetch(leptons->at(i), tightMuon2DSF);
      tightChargeSF = fetch(leptons->at(i), tightChargeMuonSF2D);
    } else {
      looseSF = fetch(leptons->at(i), looseElectron2DSF);
      tightSF = fetch(leptons->at(i), tightElectron2DSF);
      tightChargeSF = fetch(leptons->at(i), tightChargeElectronSF2D);
    }
    branches[looseBranchName[i]].branchVal = looseSF;
    branches[tightBranchName[i]].branchVal = tightSF;
    branches[tightChargeBranchName[i]].branchVal = tightChargeSF;
  }
}

double TightChargeAndLepMVAScaleFactorsPerLepton::fetch(BNlepton* lepton, TH2D* histo) {
  double minPt = histo->GetXaxis()->GetXmin()+1e-3;
  double maxPt = histo->GetXaxis()->GetXmax()-1e-3;
  double minEta = histo->GetYaxis()->GetXmin()+1e-3;
  double maxEta = histo->GetYaxis()->GetXmax()-1e-3;

  double pT = std::min(std::max(lepton->pt, minPt), maxPt);
  double eta = std::min(std::max(lepton->eta, minEta), maxEta);

  double xBin = histo->GetXaxis()->FindBin(pT);
  double yBin = histo->GetYaxis()->FindBin(eta);
  double SF = histo->GetBinContent(xBin, yBin);

  return SF;
}

TightChargeAndLepMVAScaleFactorsPerLepton::~TightChargeAndLepMVAScaleFactorsPerLepton() {
  delete looseElectron2DSF;
  delete looseMuon2DSF;
  delete tightElectron2DSF;
  delete tightMuon2DSF;
  delete tightChargeElectronSF2D;
  delete tightChargeMuonSF2D;

  electronFile.Close();
  muonFile.Close();
 }

#endif
