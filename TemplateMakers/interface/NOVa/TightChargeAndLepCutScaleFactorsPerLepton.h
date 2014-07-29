#ifndef _TightChargeAndLepCutScaleFactorsPerLepton_h
#define _TightChargeAndLepCutScaleFactorsPerLepton_h

class TightChargeAndLepCutScaleFactorsPerLepton: public KinematicVariable<double> {

public:
  TightChargeAndLepCutScaleFactorsPerLepton(int _numLeps, BNleptonCollection **_leptonsPtr, string _label);
  ~TightChargeAndLepCutScaleFactorsPerLepton();
  void evaluate();
  double fetch(BNlepton* lepton, TH2D* histo);

  TFile leptonFile;
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
  BNleptonCollection **leptonsPtr;
  string label;

};

TightChargeAndLepCutScaleFactorsPerLepton::TightChargeAndLepCutScaleFactorsPerLepton (int _numLeps, BNleptonCollection **_leptonsPtr, string _label = ""):
  leptonFile((string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/NOVa/lepCut_weights/LepCutAndTightChargeSF.root").c_str()),
  numLeps(_numLeps),
  leptonsPtr(_leptonsPtr),
  label(_label)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

  looseElectron2DSF = (TH2D*)leptonFile.Get("loose_eff_SF_ele_ele")->Clone();
  looseMuon2DSF = (TH2D*)leptonFile.Get("loose_eff_SF_mu_mu")->Clone();
  tightElectron2DSF = (TH2D*)leptonFile.Get("tight_eff_SF_ele_ele")->Clone();
  tightMuon2DSF = (TH2D*)leptonFile.Get("tight_eff_SF_mu_mu")->Clone();
  tightChargeElectronSF2D = (TH2D*)leptonFile.Get("TC_eff_SF_ele_ele")->Clone();
  tightChargeMuonSF2D = (TH2D*)leptonFile.Get("TC_eff_SF_mu_mu")->Clone();

  for (unsigned int i=0; i<numLeps; i++) {
    looseBranchName[i] = Form("lepCutLooseSF%s_Lep%d", label.c_str(), i+1);
    tightBranchName[i] = Form("lepCutTightSF%s_Lep%d", label.c_str(), i+1);
    tightChargeBranchName[i] = Form("tightChargeSF%s_Lep%d", label.c_str(), i+1);
    branches[looseBranchName[i]] = BranchInfo<double>(looseBranchName[i]);
    branches[tightBranchName[i]] = BranchInfo<double>(tightBranchName[i]);
    branches[tightChargeBranchName[i]] = BranchInfo<double>(tightChargeBranchName[i]);
  }
}

void TightChargeAndLepCutScaleFactorsPerLepton::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BNleptonCollection * leptons = *leptonsPtr;
  double looseSF = 1.0;
  double tightSF = 1.0;
  double tightChargeSF = 1.0;
  for (unsigned int i=0; i<numLeps && i<leptons->size(); i++) {
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

double TightChargeAndLepCutScaleFactorsPerLepton::fetch(BNlepton* lepton, TH2D* histo) {
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

TightChargeAndLepCutScaleFactorsPerLepton::~TightChargeAndLepCutScaleFactorsPerLepton() {
  delete looseElectron2DSF;
  delete looseMuon2DSF;
  delete tightElectron2DSF;
  delete tightMuon2DSF;
  delete tightChargeElectronSF2D;
  delete tightChargeMuonSF2D;

  leptonFile.Close();
 }

#endif
