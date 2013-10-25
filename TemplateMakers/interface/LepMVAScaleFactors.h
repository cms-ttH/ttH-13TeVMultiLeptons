#ifndef _LepMVAScaleFactors_h
#define _LepMVAScaleFactors_h

class LepMVAScaleFactors: public KinematicVariable<double> {

public:
  LepMVAScaleFactors(int numLeps);
  virtual ~LepMVAScaleFactors();
  void evaluate();
  double fetch(BNlepton* lepton, TH2D* histo);

  TFile electronFile;
  TFile muonFile;
  TH2D* looseElectron2DSF;
  TH2D* looseMuon2DSF;
  TH2D* tightElectron2DSF;
  TH2D* tightMuon2DSF;
  int numLeps;
  TString looseBranchName;
  TString tightBranchName;
};

LepMVAScaleFactors::LepMVAScaleFactors (int numLeps):
  electronFile("../data/lepMVA_weights/MVAandTigthChargeSF_ele.root"),
  muonFile("../data/lepMVA_weights/MVAandTigthChargeSF_mu.root"),
  numLeps(numLeps)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

  looseElectron2DSF = (TH2D*)electronFile.Get("LepMVALooseSF2D")->Clone();
  looseMuon2DSF = (TH2D*)muonFile.Get("LepMVALooseSF2D")->Clone();
  tightElectron2DSF = (TH2D*)electronFile.Get("LepMVATightSF2D")->Clone();
  tightMuon2DSF = (TH2D*)muonFile.Get("LepMVATightSF2D")->Clone();

  looseBranchName = Form("lepMVALooseSF_%dlep", numLeps);
  tightBranchName = Form("lepMVATightSF_%dlep", numLeps);
  branches[looseBranchName] = BranchInfo<double>(looseBranchName);
  branches[tightBranchName] = BranchInfo<double>(tightBranchName);
}

void LepMVAScaleFactors::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BNleptonCollection * leptons = this->blocks->tightLoosePreselectedLeptonCollection;
  double totalLooseSF = 1.0;
  double totalTightSF = 1.0;
  double looseSF = 1.0;
  double tightSF = 1.0;
  for (int i=0; i<numLeps; i++) {
    if (leptons->at(i)->isMuon) {
      looseSF = fetch(leptons->at(i), looseMuon2DSF);
      tightSF = fetch(leptons->at(i), tightMuon2DSF);
    } else {
      looseSF = fetch(leptons->at(i), looseElectron2DSF);
      tightSF = fetch(leptons->at(i), tightElectron2DSF);
    }
    totalLooseSF *= looseSF;
    totalTightSF *= tightSF;
  }
  branches[looseBranchName].branchVal = totalLooseSF;
  branches[tightBranchName].branchVal = totalTightSF;
}

double LepMVAScaleFactors::fetch(BNlepton* lepton, TH2D* histo) {
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

LepMVAScaleFactors::~LepMVAScaleFactors() {
  electronFile.Close();
  muonFile.Close();
  delete looseElectron2DSF;
  delete looseMuon2DSF;
  delete tightElectron2DSF;
  delete tightMuon2DSF;
}

#endif
