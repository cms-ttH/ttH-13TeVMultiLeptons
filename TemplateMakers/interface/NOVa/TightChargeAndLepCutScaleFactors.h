#ifndef _TightChargeAndLepCutScaleFactors_h
#define _TightChargeAndLepCutScaleFactors_h

class TightChargeAndLepCutScaleFactors: public KinematicVariable<double> {

public:
  TightChargeAndLepCutScaleFactors(int _numLeps, BNleptonCollection **_leptonsPtr, string _label);
  ~TightChargeAndLepCutScaleFactors();
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
  TString looseBranchName;
  TString tightBranchName;
  TString tightChargeBranchName;
  BNleptonCollection **leptonsPtr;
  string label;
};

TightChargeAndLepCutScaleFactors::TightChargeAndLepCutScaleFactors (int _numLeps, BNleptonCollection **_leptonsPtr, string _label = ""):
  leptonFile((string(getenv("CMSSW_BASE"))+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/NOVa/lepCut_weights/LepCutAndTightChargeSF.root").c_str()),
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

  looseBranchName = Form("lepCutLoose%dLepSF%s", numLeps, label.c_str());
  tightBranchName = Form("lepCutTight%dLepSF%s", numLeps, label.c_str());
  branches[looseBranchName] = BranchInfo<double>(looseBranchName);
  branches[tightBranchName] = BranchInfo<double>(tightBranchName);
  if (numLeps < 4) {
    tightChargeBranchName = Form("tightCharge%dLepSF%s", numLeps, label.c_str());
    branches[tightChargeBranchName] = BranchInfo<double>(tightChargeBranchName);
  }
}

void TightChargeAndLepCutScaleFactors::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BNleptonCollection * leptons = *leptonsPtr;
  double totalLooseSF = 1.0;
  double totalTightSF = 1.0;
  double totalTightChargeSF = 1.0;
  double looseSF = 1.0;
  double tightSF = 1.0;
  double tightChargeSF = 1.0;
  for (unsigned int i=0; i<numLeps; i++) {
    //For an event with 2 leptons, 3-lepton SF = 0
    if (i >= leptons->size()) {
      totalLooseSF *= 0;
      totalTightSF *= 0;
      totalTightChargeSF *= 0;
    } else {
      if (leptons->at(i)->isMuon) {
        looseSF = fetch(leptons->at(i), looseMuon2DSF);
        tightSF = fetch(leptons->at(i), tightMuon2DSF);
        tightChargeSF = fetch(leptons->at(i), tightChargeMuonSF2D);
      } else {
        looseSF = fetch(leptons->at(i), looseElectron2DSF);
        tightSF = fetch(leptons->at(i), tightElectron2DSF);
        tightChargeSF = fetch(leptons->at(i), tightChargeElectronSF2D);
      }
    totalLooseSF *= looseSF;
    totalTightSF *= tightSF;
    totalTightChargeSF *= tightChargeSF;
    }
  }
  branches[looseBranchName].branchVal = totalLooseSF;
  branches[tightBranchName].branchVal = totalTightSF;
  if (numLeps < 4) {
    branches[tightChargeBranchName].branchVal = totalTightChargeSF;
  }
}

double TightChargeAndLepCutScaleFactors::fetch(BNlepton* lepton, TH2D* histo) {
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

TightChargeAndLepCutScaleFactors::~TightChargeAndLepCutScaleFactors() {
  delete looseElectron2DSF;
  delete looseMuon2DSF;
  delete tightElectron2DSF;
  delete tightMuon2DSF;
  delete tightChargeElectronSF2D;
  delete tightChargeMuonSF2D;

  leptonFile.Close();
 }

#endif
