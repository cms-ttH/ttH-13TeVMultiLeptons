{
#include <cmath>
#include <algorithm>

  TString year = "2012_53x"; //Year for the input trees
  TString label1 = "newLimits_v1"; //Label of the input trees
  TString label2 = "newLimits_v1"; //Label of the input trees
  TString extraLabel = ""; //Systematic of the input trees; set to "JESUp_" for JESUp, etc.
  TString WP = "000"; //100x probe jet working point - loose (224), medium (679), tight (898)
  TString lfSF = "10"; //10x Scale factor for light-flavor backgrounds (single top, Z+jets). 10 is nominal, 15 is 50% higher, 5 is 50% lower.
  bool EfficiencySF = false; //Set to true if you are measuring the efficiency for different CSV working points
  TString pt_lower = "0";
  TString pt_upper = "10000";
  TString eta_lower = "0.0";
  TString eta_upper = "5.0";
  
  TString lepselection1a = "(TwoMuon && isDoubleMuTriggerPass && PassZmask2==1 && met>50)"; //Selection for TwoMuon data events
  TString lepselection1b = "(TwoEle && isDoubleElectronTriggerPass && PassZmask2==1 && met>50)"; //Selection for TwoEle data events
  TString lepselection1c = "(MuonEle && isMuEGTriggerPass)"; //Selection for MuonEle data events
  //Selection for MC events
  TString lepselection2 = "( (TwoMuon && isDoubleMuTriggerPass && PassZmask2==1 && met>50) || (TwoEle && isDoubleElectronTriggerPass && PassZmask2==1 && met>50) || (MuonEle && isMuEGTriggerPass) ) ";
  TString jetselection1a = "(numJets == 2 && second_jet_CSV_unc > 0.679)"; //Tag jet requirement for probing first_jet
  TString jetselection1b = "(numJets == 2 && first_jet_CSV_unc > 0.679)"; //Tag jet requirement for probing second_jet
  TString jetselection2a = "(numJets == 2 && second_jet_CSV_unc > 0.679 "; //Probe jet requirement for first_jet
  jetselection2a += " && first_jet_CSV_unc > 0."+WP;
  jetselection2a += " && first_jet_pt >= "+pt_lower+" && first_jet_pt < "+pt_upper;
  jetselection2a += " && abs(first_jet_eta) >= "+eta_lower+" && abs(first_jet_eta) < "+eta_upper+")";
  TString jetselection2b = "(numJets == 2 && first_jet_CSV_unc > 0.679 "; //Probe jet requirement for second_jet
  jetselection2b += " && second_jet_CSV_unc > 0."+WP;
  jetselection2b += " && second_jet_pt >= "+pt_lower+" && second_jet_pt < "+pt_upper;
  jetselection2b += " && abs(second_jet_eta) >= "+eta_lower+" && abs(second_jet_eta) < "+eta_upper+")";
  TString trigselection = "((dR_leplep > 0.2) && (mass_leplep > 12) && (isCleanEvent == 1) && (oppositeLepCharge == 1))"; //General dilepton selection
  TString DataSample1a = "DoubleMu";
  TString DataSample1b = "DoubleElectron";
  TString DataSample1c = "MuEG";
  TString MCsample1 = "allMC";
  TString nonttbar = "( (Xsec>24.56 && Xsec<=24.57)*1 + (!(Xsec>24.56 && Xsec<=24.57))*("+lfSF+")*0.1)*"; //Scaling of the non-ttbar_ll background component
  TString lumi = "19450.0*"; //Nominal luminosity
  
  if (EfficiencySF) {
    TString varName = "jet_pt"; //Variable which the scale factor is a function of
    TString varName1 = "first_jet_pt"; //Variable which the scale factor is a function of
    TString varName2 = "second_jet_pt"; //Variable which the scale factor is a function of
  }
  else {
  TString varName = "jet_CSV_unc"; //Variable which the scale factor is a function of
  TString varName1 = "first_jet_CSV_unc"; //Variable which the scale factor is a function of
  TString varName2 = "second_jet_CSV_unc"; //Variable which the scale factor is a function of
  }
//   TFile * sourceFile1a = new TFile ("bin/treeFiles/dilSummaryTrees_"+DataSample1a+"_"+year+"_"+label1+"_all.root");
//   TFile * sourceFile1b = new TFile ("bin/treeFiles/dilSummaryTrees_"+DataSample1b+"_"+year+"_"+label1+"_all.root");
//   TFile * sourceFile1c = new TFile ("bin/treeFiles/dilSummaryTrees_"+DataSample1c+"_"+year+"_"+label1+"_all.root");
//   TFile * sourceFile2 = new TFile ("bin/dilSummaryTrees_"+MCsample1+"_"+year+"_"+label2+"_"+extraLabel+"all.root");

  TFile * sourceFile1a = new TFile ("bin/TwoMuon.root");
  TFile * sourceFile1b = new TFile ("bin/TwoEle.root");
  TFile * sourceFile1c = new TFile ("bin/MuonEle.root");
  TFile * sourceFile2 = new TFile ("bin/allMC.root");

  if (EfficiencySF) {
  double Xmin = 30; //Lower bound for x-axis
  double Xmax = 260; //Upper bound for x-axis
  int nBins = 10; //Number of bins
  Double_t xBins[11] = {30,40,50,60,70,80,100,120,160,210,260}; //Binning
  //  Double_t xBins[13] = {30,40,50,60,70,80,100,120,160,210,260,320,800};
  }
  else {
  double Xmin = 0; //Lower bound for x-axis
  double Xmax = 1.0; //Upper bound for x-axis
  int nBins = 15; //Number of bins
  Double_t xBins[16] = {0,0.061,0.122,0.183,0.244,0.389,0.534,0.679,0.752,0.825,0.898,0.932,0.966,0.99,0.999,1.0}; //Binning
  //  Double_t xBins[13] = {30,40,50,60,70,80,100,120,160,210,260,320,800};
  }
  
  TCanvas * can1a = new TCanvas ("can1a", "can1a");

  //DoubleMu
  sourceFile1a->cd();
  TH1F *histTemp1 = new TH1F("histTemp1", "histTemp1", nBins, xBins); //varName1, jetselection1a
  TH1F *histTemp2 = new TH1F("histTemp2", "histTemp2", nBins, xBins); //varName2, jetselection1b
  TH1F *histTemp3 = new TH1F("histTemp3", "histTemp3", nBins, xBins); //varName1, jetselection2a
  TH1F *histTemp4 = new TH1F("histTemp4", "histTemp4", nBins, xBins); //varName2, jetselection2b
  histTemp1->Sumw2();
  histTemp2->Sumw2();
  histTemp3->Sumw2();
  histTemp4->Sumw2();
  TH1 * sourceHisto1 = (TH1*) summaryTree->Draw(varName1+" >> histTemp1","weight*(Xsec/nGen)*("+lepselection1a+ " && "+trigselection+" && "+jetselection1a+")","");
  TH1 * sourceHisto2 = (TH1*) summaryTree->Draw(varName2+" >> histTemp2","weight*(Xsec/nGen)*("+lepselection1a+ " && "+trigselection+" && "+jetselection1b+")","");
  TH1 * sourceHisto3 = (TH1*) summaryTree->Draw(varName1+" >> histTemp3","weight*(Xsec/nGen)*("+lepselection1a+ " && "+trigselection+" && "+jetselection2a+")","");
  TH1 * sourceHisto4 = (TH1*) summaryTree->Draw(varName2+" >> histTemp4","weight*(Xsec/nGen)*("+lepselection1a+ " && "+trigselection+" && "+jetselection2b+")","");

  //DoubleElectron
  sourceFile1b->cd();
  TH1F *histTemp5 = new TH1F("histTemp5", "histTemp5", nBins, xBins); //varName1, jetselection1a 
  TH1F *histTemp6 = new TH1F("histTemp6", "histTemp6", nBins, xBins); //varName2, jetselection1b
  TH1F *histTemp7 = new TH1F("histTemp7", "histTemp7", nBins, xBins); //varName1, jetselection2a
  TH1F *histTemp8 = new TH1F("histTemp8", "histTemp8", nBins, xBins); //varName2, jetselection2b
  histTemp5->Sumw2();
  histTemp6->Sumw2();
  histTemp7->Sumw2();
  histTemp8->Sumw2();
  TH1 * sourceHisto5 = (TH1*) summaryTree->Draw(varName1+" >> histTemp5","weight*(Xsec/nGen)*("+lepselection1b+ " && "+trigselection+" && "+jetselection1a+")","");
  TH1 * sourceHisto6 = (TH1*) summaryTree->Draw(varName2+" >> histTemp6","weight*(Xsec/nGen)*("+lepselection1b+ " && "+trigselection+" && "+jetselection1b+")","");
  TH1 * sourceHisto7 = (TH1*) summaryTree->Draw(varName1+" >> histTemp7","weight*(Xsec/nGen)*("+lepselection1b+ " && "+trigselection+" && "+jetselection2a+")","");
  TH1 * sourceHisto8 = (TH1*) summaryTree->Draw(varName2+" >> histTemp8","weight*(Xsec/nGen)*("+lepselection1b+ " && "+trigselection+" && "+jetselection2b+")","");

  //MuEG
  sourceFile1c->cd();
  TH1F *histTemp9 = new TH1F("histTemp9", "histTemp9", nBins, xBins); //varName1, jetselection1a
  TH1F *histTemp10 = new TH1F("histTemp10", "histTemp10", nBins, xBins); //varName2, jetselection1b
  TH1F *histTemp11 = new TH1F("histTemp11", "histTemp11", nBins, xBins); //varName1, jetselection2a
  TH1F *histTemp12 = new TH1F("histTemp12", "histTemp12", nBins, xBins); //varName2, jetselection2b
  histTemp9->Sumw2();
  histTemp10->Sumw2();
  histTemp11->Sumw2();
  histTemp12->Sumw2();
  TH1 * sourceHisto9 = (TH1*) summaryTree->Draw(varName1+" >> histTemp9","weight*(Xsec/nGen)*("+lepselection1c+ " && "+trigselection+" && "+jetselection1a+")","");
  TH1 * sourceHisto10 = (TH1*) summaryTree->Draw(varName2+" >> histTemp10","weight*(Xsec/nGen)*("+lepselection1c+ " && "+trigselection+" && "+jetselection1b+")","");
  TH1 * sourceHisto11 = (TH1*) summaryTree->Draw(varName1+" >> histTemp11","weight*(Xsec/nGen)*("+lepselection1c+ " && "+trigselection+" && "+jetselection2a+")","");
  TH1 * sourceHisto12 = (TH1*) summaryTree->Draw(varName2+" >> histTemp12","weight*(Xsec/nGen)*("+lepselection1c+ " && "+trigselection+" && "+jetselection2b+")","");

  histTemp1->Add(histTemp2); //Add first and second jet distributions in DoubleMu
  histTemp1->Add(histTemp5); //Add first jet DoubleEle
  histTemp1->Add(histTemp6); //Add second jet DoubleEle
  histTemp1->Add(histTemp9); //Add first jet MuEG
  histTemp1->Add(histTemp10); //Add second jet MuEG
  
  histTemp3->Add(histTemp4); //Add first and second jet distributions in DoubleMu
  histTemp3->Add(histTemp7); //Add first jet DoubleEle 
  histTemp3->Add(histTemp8); //Add second jet DoubleEle
  histTemp3->Add(histTemp11); //Add first jet MuEG
  histTemp3->Add(histTemp12); //Add second jet MuEG
  
  float Data_tagged = histTemp3->Integral(); //Numerator
  float Data_untagged = histTemp1->Integral(); //Denominator
  if (EfficiencySF) {
    std::cout << "Data tagged: " << Data_tagged << endl;
    std::cout << "Data untagged: " << Data_untagged << endl;
    std::cout << "Data tag eff: " << Data_tagged/Data_untagged << endl;
  }
  else std::cout << "Data: " << Data_tagged << endl;
  if (EfficiencySF) histTemp3->Divide(histTemp3,histTemp1);
  histTemp3->SetMarkerStyle(8);
  histTemp3->SetLineColor(kBlack);
  histTemp3->SetTitle("Two leptons, Z-masked, ==2 jet");


  //MC
  sourceFile2->cd();
  TH1F *histTemp1a = new TH1F("histTemp1a", "histTemp1a", nBins, xBins);
  TH1F *histTemp2a = new TH1F("histTemp2a", "histTemp2a", nBins, xBins);
  TH1F *histTemp3a = new TH1F("histTemp3a", "histTemp3a", nBins, xBins);
  TH1F *histTemp4a = new TH1F("histTemp4a", "histTemp4a", nBins, xBins);
  histTemp1a->Sumw2();
  histTemp2a->Sumw2();
  histTemp3a->Sumw2();
  histTemp4a->Sumw2();
  TH1 * sourceHisto1a = (TH1*) summaryTree->Draw(varName1+" >> histTemp1a",nonttbar+lumi+"weight*(Xsec/nGen)*("+lepselection2+ " && "+trigselection+" && "+jetselection1a+")","");
  TH1 * sourceHisto2a = (TH1*) summaryTree->Draw(varName2+" >> histTemp2a",nonttbar+lumi+"weight*(Xsec/nGen)*("+lepselection2+ " && "+trigselection+" && "+jetselection1b+")","");
  TH1 * sourceHisto3a = (TH1*) summaryTree->Draw(varName1+" >> histTemp3a",nonttbar+lumi+"weight*(Xsec/nGen)*("+lepselection2+ " && "+trigselection+" && "+jetselection2a+")","");
  TH1 * sourceHisto4a = (TH1*) summaryTree->Draw(varName2+" >> histTemp4a",nonttbar+lumi+"weight*(Xsec/nGen)*("+lepselection2+ " && "+trigselection+" && "+jetselection2b+")","");

  histTemp1a->Add(histTemp2a);
  histTemp3a->Add(histTemp4a);
  float MC_tagged = histTemp3a->Integral();
  float MC_untagged = histTemp1a->Integral();
  if (EfficiencySF) {
    std::cout << "MC tagged: " << MC_tagged << endl;
    std::cout << "MC untagged: " << MC_untagged << endl;
    std::cout << "MC tag eff: " << MC_tagged/MC_untagged << endl;
    std::cout << "" << endl;
    std::cout << "Data/MC SF: " << (Data_tagged/Data_untagged)/(MC_tagged/MC_untagged) << endl;
  }
  else {
    std::cout << "MC: " << MC_tagged << endl;
    std::cout << "" << endl;
    std::cout << "Data/MC : " << Data_tagged/MC_tagged << endl;
    std::cout << "Rescaling MC to match data yields ..." << endl;
  }
  if (EfficiencySF) histTemp3a->Divide(histTemp3a,histTemp1a);
  else histTemp3a->Scale(Data_tagged/MC_tagged);
  histTemp3a->SetMarkerStyle(8);
  histTemp3a->SetMarkerColor(kRed);
  histTemp3a->SetLineColor(kRed);

  TH1F *hClone = (TH1F*)histTemp3->Clone("hClone");
  hClone->Divide(hClone,histTemp3a);
  hClone->SetMarkerStyle(8);
  hClone->SetMarkerColor(kBlue);
  hClone->SetLineColor(kBlue);

  if (EfficiencySF) {
    histTemp3->SetMaximum(1.1);
    histTemp3->SetMinimum(0.1);
  }
  else {
  histTemp3->SetMaximum(1.3);
  histTemp3->SetMinimum(0.7);
  }
  
  can1a->cd();

  //Overlay shapes
  if (EfficiencySF) {
    histTemp3->Draw("histE1");
    histTemp3a->Draw("histsameE1");
    hClone->Draw("histsameE1");
  }
  else hClone->Draw("histE1");
  can1a->Print("BtagReshaping/Efficiency_"+varName+"_"+WP+"_"+extraLabel+lfSF+".png");

// //Best fit for loose and medium CSV
//   TF1 *f1 = new TF1("f1","(x<-1*[4])*([0]+[1]*pow([2]*(x+[4]),3)) + (x>=-1*[4])*([0]+[3]*pow([2]*(x+[4]),2))");
//   f1->SetParLimits(0,0.9,1.1);
//   f1->SetParLimits(1,-0.5,-0.0001);
//   f1->SetParLimits(3,-0.5,-0.0001);  
//   f1->SetParLimits(2,0.0001,0.5);
//   f1->SetParLimits(4,-200,-80);
//   hClone->Draw("histE1");
//   hClone->Fit("f1");
//   can1a->Print("BtagReshaping/SF_"+varName+"_"+WP+"_"+extraLabel+lfSF+".png");

// //Best fit for tight CSV
//   TF1 *f2 = new TF1("f2","([0]+[1]*pow(fabs(x+[2]),2))");
//   f2->SetParLimits(0,0.5,1.5);
//   f2->SetParLimits(1,-0.001,0.001);
//   f2->SetParLimits(2,-100,100);
// //   f2->SetParLimits(3,2.0,4.0);
//   hClone->Draw("histE1");
//   hClone->Fit("f2");
//   can1a->Print("BtagReshaping/SF_"+varName+"_"+WP+"_"+extraLabel+lfSF+".png");

  
}  
  
