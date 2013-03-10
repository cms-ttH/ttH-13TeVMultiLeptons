void NonPromptSF(){

  gStyle->SetFillColor(0);

  TCanvas* c1 = new TCanvas();
  TCanvas* c2 = new TCanvas();
  TCanvas* c3 = new TCanvas();
  TCanvas* c4 = new TCanvas();
   
  TFile * file1a = TFile::Open("bin/TwoMuon.root");
  TTree * tree1a = (TTree*) file1a->Get("summaryTree");
  TFile * file1b = TFile::Open("bin/TwoEle.root");
  TTree * tree1b = (TTree*) file1b->Get("summaryTree");
  TFile * file1c = TFile::Open("bin/MuonEle.root");
  TTree * tree1c = (TTree*) file1c->Get("summaryTree");
    
  TFile * file2 = TFile::Open("bin/allMC.root");
  TTree * tree2 = (TTree*) file2->Get("summaryTree");

  TString lepSelectionSSa = "( TwoMuon && isDoubleMuTriggerPass )";
  TString lepSelectionSSb = "( TwoEle && isDoubleElectronTriggerPass && PassZmask == 1)";
  TString lepSelectionSSc = "( MuonEle && isMuEGTriggerPass )";
  TString lepSelectionSS = "( "+lepSelectionSSa+" || "+lepSelectionSSb+" || "+lepSelectionSSc+" )";
  TString lepSelectionOS = "( MuonEle && isMuEGTriggerPass )";
  TString jetSelectionSS = "(numJets == 2 || numJets == 3) && numTaggedJets == 1";
  TString jetSelectionOS = "numJets == 2 && numTaggedJets == 2";
  TString MCweight = "lepTotalSF*(weight*Xsec/nGen)*(19450.0)";
//   TString MCweight = "lepTotalSF*((lepTotalPromptSFUp+lepTotalPromptSFDown)/2)*(weight*Xsec/nGen)*(19450.0)"; //Use for weighted dist.
  TString lepCuts = "isCleanEvent == 1 && mass_leplep>12 && dR_leplep > 0.2"; 
  TString SScuts = lepCuts+" && oppositeLepCharge == 0 && lepTotalPassSSCut == 1 &&  (MHT + lep1Pt + lep2Pt > 85) && (mindr_lep1_allJet > 0.2) && (mindr_lep2_allJet > 0.2)";
  TString OScuts =  lepCuts+" && oppositeLepCharge == 1 && (mindr_lep1_allJet > 0.2) && (mindr_lep2_allJet > 0.2)";
//   TString lep2Choice = "lep2GsfCharge > -2"; //Use for electrons
  TString lep2Choice = "lep2GsfCharge < -2"; //Use for muons

  
  double ratioMin = 0.5;
  double ratioMax = 3.5;
  Int_t nBinsIso = 5;
  Double_t xBinsIso[6] = {0,0.001,0.02,0.06,0.12,0.2};
  Int_t nBinsPt = 6;
  Double_t xBinsPt[7] = {10,20,30,40,50,70,100};
  Int_t nBinsAbsEta = 4;
  Double_t xBinsAbsEta[5] = {0,0.8,1.3,2.1,2.5};

  // maxLepChargedIso
  TH1 * h1 = new TH1F("h1","h1",nBinsIso,xBinsIso);
  TH1 * h1a = new TH1F("h1a","h1a",nBinsIso,xBinsIso);
  TH1 * h2 = new TH1F("h2","h2",nBinsIso,xBinsIso);
  TH1 * h2a = new TH1F("h2a","h2a",nBinsIso,xBinsIso);

  // maxLepAbsEta
  TH1 * h3 = new TH1F("h3","h3",nBinsAbsEta,xBinsAbsEta);
  TH1 * h3a = new TH1F("h3a","h3a",nBinsAbsEta,xBinsAbsEta);
  TH1 * h4 = new TH1F("h4","h4",nBinsAbsEta,xBinsAbsEta);
  TH1 * h4a = new TH1F("h4a","h4a",nBinsAbsEta,xBinsAbsEta);

  // lep2ChargedIso
  TH1 * h5 = new TH1F("h5","h5",nBinsIso,xBinsIso);
  TH1 * h5a = new TH1F("h5a","h5a",nBinsIso,xBinsIso);
  TH1 * h6 = new TH1F("h6","h6",nBinsIso,xBinsIso);
  TH1 * h6a = new TH1F("h6a","h6a",nBinsIso,xBinsIso);

  // lep2Pt
  TH1 * h7 = new TH1F("h7","h7",nBinsPt,xBinsPt);
  TH1 * h7a = new TH1F("h7a","h7a",nBinsPt,xBinsPt);
  TH1 * h8 = new TH1F("h8","h8",nBinsPt,xBinsPt);
  TH1 * h8a = new TH1F("h8a","h8a",nBinsPt,xBinsPt);

  bool divide = false;

  h1->Sumw2();
  h1a->Sumw2();
  h2->Sumw2();
  h2a->Sumw2();
  h3->Sumw2();
  h3a->Sumw2();
  h4->Sumw2();
  h4a->Sumw2();
  h5->Sumw2();
  h5a->Sumw2();
  h6->Sumw2();
  h6a->Sumw2();
  h7->Sumw2();
  h7a->Sumw2();
  h8->Sumw2();
  h8a->Sumw2();

  ///////////// eta lep1

  c1->cd();

  tree1a->Draw("maxLepChargedIso >> h1","("+lepSelectionSSa+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree1b->Draw("maxLepChargedIso >>+ h1","("+lepSelectionSSb+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree1c->Draw("maxLepChargedIso >>+ h1","("+lepSelectionSSc+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree2->Draw("maxLepChargedIso >> h1a","("+lepSelectionSS+" &&  "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")*"+MCweight,"goff");
  double SS_data = h1->Integral();
  double SS_MC = h1a->Integral();
  cout << "SS data: " << SS_data << endl;
  cout << "SS MC: " << SS_MC << endl;
  cout << "SS data/MC: " << SS_data/SS_MC << endl;
  divide = h1->Divide(h1,h1a);

  h1->SetStats(kFALSE);

  tree1c->Draw("maxLepChargedIso >> h2","("+lepSelectionOS+" && "+jetSelectionOS+" &&  "+OScuts+" && "+lep2Choice+")","goff");
  tree2->Draw("maxLepChargedIso >> h2a","("+lepSelectionOS+" && "+jetSelectionOS+" &&  "+OScuts+" && "+lep2Choice+")*"+MCweight,"goff");
  double OS_data = h2->Integral();
  double OS_MC = h2a->Integral();
  cout << "OS data: " << OS_data << endl;
  cout << "OS MC: " << OS_MC << endl;
  cout << "OS data/MC: " << OS_data/OS_MC << endl;
  cout << "SS/OS scale factor: " << (SS_data/SS_MC)/(OS_data/OS_MC) << endl;
  divide = h2->Divide(h2,h2a);
  h2->SetStats(kFALSE);

  divide = h1->Divide(h1,h2);
  h1->SetTitle("(maxLepChargedIso TwoLep && numJets == 3(2) && numTaggedJets == 1(2) && "+lep2Choice+")"+" SS/(OS) Data/MC");
  h1->SetMarkerStyle(8);
  h1->SetLineColor(kRed);
  h1->GetYaxis()->SetRangeUser(ratioMin,ratioMax);
  h1->Draw("E1");

  ///////////// pt lep1

  c2->cd();

  tree1a->Draw("maxLepAbsEta >> h3","("+lepSelectionSSa+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree1b->Draw("maxLepAbsEta >>+ h3","("+lepSelectionSSb+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree1c->Draw("maxLepAbsEta >>+ h3","("+lepSelectionSSc+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree2->Draw("maxLepAbsEta >> h3a","("+lepSelectionSS+" &&  "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")*"+MCweight,"goff");
  divide = h3->Divide(h3,h3a);

  h3->SetStats(kFALSE);

  tree1c->Draw("maxLepAbsEta >> h4","("+lepSelectionOS+" && "+jetSelectionOS+" &&  "+OScuts+" && "+lep2Choice+")","goff");
  tree2->Draw("maxLepAbsEta >> h4a","("+lepSelectionOS+" && "+jetSelectionOS+" &&  "+OScuts+" && "+lep2Choice+")*"+MCweight,"goff");
  divide = h4->Divide(h4,h4a);
  h4->SetStats(kFALSE);

  divide = h3->Divide(h3,h4);
  h3->SetTitle("(maxLepAbsEta TwoLep && numJets == 3(2) && numTaggedJets == 1(2) && "+lep2Choice+")"+" SS/(OS) Data/MC");
  h3->SetMarkerStyle(8);
  h3->SetLineColor(kRed);  
  h3->GetYaxis()->SetRangeUser(ratioMin,ratioMax);
  h3->Draw("E1");

  ///////////// eta lep2

  c3->cd();

  tree1a->Draw("lep2ChargedIso >> h5","("+lepSelectionSSa+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree1b->Draw("lep2ChargedIso >>+ h5","("+lepSelectionSSb+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree1c->Draw("lep2ChargedIso >>+ h5","("+lepSelectionSSc+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree2->Draw("lep2ChargedIso >> h5a","("+lepSelectionSS+" &&  "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")*"+MCweight,"goff");
  divide = h5->Divide(h5,h5a);

  h5->SetStats(kFALSE);

  tree1c->Draw("lep2ChargedIso >> h6","("+lepSelectionOS+" && "+jetSelectionOS+" &&  "+OScuts+" && "+lep2Choice+")","goff");
  tree2->Draw("lep2ChargedIso >> h6a","("+lepSelectionOS+" && "+jetSelectionOS+" &&  "+OScuts+" && "+lep2Choice+")*"+MCweight,"goff");
  divide = h6->Divide(h6,h6a);
  h6->SetStats(kFALSE);

  divide = h5->Divide(h5,h6);
  h5->SetTitle("(lep2ChargedIso TwoLep && numJets == 3(2) && numTaggedJets == 1(2) && "+lep2Choice+")"+" SS/(OS) Data/MC");
  h5->SetMarkerStyle(8);
  h5->SetLineColor(kRed);
  h5->GetYaxis()->SetRangeUser(ratioMin,ratioMax);
  h5->Draw("E1");

  ///////////// pt lep2

  c4->cd();

  tree1a->Draw("lep2Pt >> h7","("+lepSelectionSSa+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree1b->Draw("lep2Pt >>+ h7","("+lepSelectionSSb+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree1c->Draw("lep2Pt >>+ h7","("+lepSelectionSSc+" && "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")","goff");
  tree2->Draw("lep2Pt >> h7a","("+lepSelectionSS+" &&  "+jetSelectionSS+" && "+SScuts+" && "+lep2Choice+")*"+MCweight,"goff");
  divide = h7->Divide(h7,h7a);

  h7->SetStats(kFALSE);

  tree1c->Draw("lep2Pt >> h8","("+lepSelectionOS+" && "+jetSelectionOS+" &&  "+OScuts+" && "+lep2Choice+")","goff");
  tree2->Draw("lep2Pt >> h8a","("+lepSelectionOS+" && "+jetSelectionOS+" &&  "+OScuts+" && "+lep2Choice+")*"+MCweight,"goff");
  divide = h8->Divide(h8,h8a);
  h8->SetStats(kFALSE);

  divide = h7->Divide(h7,h8);
  h7->SetTitle("(Lep2Pt TwoLep && numJets == 3(2) && numTaggedJets == 1(2) && "+lep2Choice+")"+" SS/(OS) Data/MC");
  h7->SetMarkerStyle(8);
  h7->SetLineColor(kRed);
  h7->GetYaxis()->SetRangeUser(ratioMin,ratioMax);
  h7->Draw("E1");
    
  ////////////////////////////////////////


  if (lep2Choice == "lep2GsfCharge > -2") {
    c1->Print("SF_plots/maxLepChargedIso_SSe3je1t_Ele_nonpromptSF.png","png");
    c2->Print("SF_plots/maxLepAbsEta_SSe3je1t_Ele_nonpromptSF.png","png");
    c3->Print("SF_plots/lep2ChargedIso_SSe3je1t_Ele_nonpromptSF.png","png");
    c4->Print("SF_plots/lep2Pt_SSe3je1t_Ele_nonpromptSF.png","png");  
    c1->Print("SF_plots/maxLepChargedIso_SSe3je1t_Ele_nonpromptSF.pdf","pdf");
    c2->Print("SF_plots/maxLepAbsEta_SSe3je1t_Ele_nonpromptSF.pdf","pdf");
    c3->Print("SF_plots/lep2ChargedIso_SSe3je1t_Ele_nonpromptSF.pdf","pdf");
    c4->Print("SF_plots/lep2Pt_SSe3je1t_Ele_nonpromptSF.pdf","pdf");
  }
  else {
    c1->Print("SF_plots/maxLepChargedIso_SSe3je1t_Mu_nonpromptSF.png","png");
    c2->Print("SF_plots/maxLepAbsEta_SSe3je1t_Mu_nonpromptSF.png","png");
    c3->Print("SF_plots/lep2ChargedIso_SSe3je1t_Mu_nonpromptSF.png","png");
    c4->Print("SF_plots/lep2Pt_SSe3je1t_Mu_nonpromptSF.png","png");  
    c1->Print("SF_plots/maxLepChargedIso_SSe3je1t_Mu_nonpromptSF.pdf","pdf");
    c2->Print("SF_plots/maxLepAbsEta_SSe3je1t_Mu_nonpromptSF.pdf","pdf");
    c3->Print("SF_plots/lep2ChargedIso_SSe3je1t_Mu_nonpromptSF.pdf","pdf");
    c4->Print("SF_plots/lep2Pt_SSe3je1t_Mu_nonpromptSF.pdf","pdf");
  }
}
