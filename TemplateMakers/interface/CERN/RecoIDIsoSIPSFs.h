#ifndef _RecoIDIsoSIPSFs_h
#define _RecoIDIsoSIPSFs_h

class RecoIDIsoSIPSFs: public KinematicVariable<double> {

public:
  RecoIDIsoSIPSFs(int numLeps, string input_option_1 = "none");
  ~RecoIDIsoSIPSFs();
  void evaluate();
  double fetch(BNlepton* lepton, TH2D* histo);
  double fetchError(BNlepton* lepton, TH2D* histo);

  TFile electronFile;
  TFile muonFile;
  TH2D* electronSFHisto;
  TH2D* muonSFHisto;
  int numLeps;
  string option_1;
  int xBin;
  int yBin;
  TString branchName;
  TString branchNameUp;
  TString branchNameDown;
};

RecoIDIsoSIPSFs::RecoIDIsoSIPSFs(int numLeps, string input_option_1):
  electronFile((string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/CERN/eff_ele12.root").c_str()),
  muonFile((string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/CERN/eff_mu12.root").c_str()),
  numLeps(numLeps), option_1(input_option_1)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

  electronSFHisto = (TH2D*)electronFile.Get("h_electron_scale_factor_RECO_ID_ISO_SIP")->Clone();
  muonSFHisto = (TH2D*)muonFile.Get("TH2D_ALL_2012")->Clone();

  branchName = Form("RecoIDIsoSIPSF_%dlep", numLeps);
  branchNameUp = Form("RecoIDIsoSIPSFUp_%dlep", numLeps);
  branchNameDown = Form("RecoIDIsoSIPSFDown_%dlep", numLeps);
  branches[branchName] = BranchInfo<double>(branchName);
  if (option_1 != "skipSyst") {
    branches[branchNameUp] = BranchInfo<double>(branchNameUp);
    branches[branchNameDown] = BranchInfo<double>(branchNameDown);
  }
  
}

void RecoIDIsoSIPSFs::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  double SF = 1.0;
  double SFUp = 1.0;
  double SFDown = 1.0;
  double totalSF = 1.0;
  double totalSFUp = 1.0;
  double totalSFDown = 1.0;

  BNleptonCollection * leptons = this->blocks->tightLoosePreselectedLeptonCollection;

  numLeps = std::min(numLeps, int(leptons->size()));
  for (int i=0; i<numLeps; i++) {
    if (leptons->at(i)->isMuon) {
      SF = fetch(leptons->at(i), muonSFHisto);
      SFUp = SF + fetchError(leptons->at(i), muonSFHisto);
      SFDown = SF - fetchError(leptons->at(i), muonSFHisto);
    } else {
      SF = fetch(leptons->at(i), electronSFHisto);
      SFUp = SF + fetchError(leptons->at(i), electronSFHisto);
      SFDown = SF - fetchError(leptons->at(i), electronSFHisto);
    }

    totalSF *= SF;
    totalSFUp *= SFUp;
    totalSFDown *= SFDown;
  }

  branches[branchName].branchVal = totalSF;
  if (option_1 != "skipSyst") {
    branches[branchNameUp].branchVal = totalSFUp;
    branches[branchNameDown].branchVal = totalSFDown;
  }
}

double RecoIDIsoSIPSFs::fetch(BNlepton* lepton, TH2D* histo) {
  double SF = 1.0;

  xBin = std::min(histo->GetXaxis()->FindBin(lepton->pt), histo->GetXaxis()->GetNbins());
  yBin = std::min(histo->GetYaxis()->FindBin(abs(lepton->eta)), histo->GetYaxis()->GetNbins());

  SF = histo->GetBinContent(xBin, yBin);

  return SF;
}

double RecoIDIsoSIPSFs::fetchError(BNlepton* lepton, TH2D* histo) {
  double SF = 1.0;

  xBin = std::min(histo->GetXaxis()->FindBin(lepton->pt), histo->GetXaxis()->GetNbins());
  yBin = std::min(histo->GetYaxis()->FindBin(abs(lepton->eta)), histo->GetYaxis()->GetNbins());

  SF = histo->GetBinError(xBin, yBin);

  return SF;
}

RecoIDIsoSIPSFs::~RecoIDIsoSIPSFs() {
  delete electronSFHisto;
  delete muonSFHisto;

  electronFile.Close();
  muonFile.Close();
 }

#endif
