{
#include <cmath>
#include <algorithm>
  
  TString lepselection = "DiMuonAll";
  TString jetselection = "eq1t";
  TString MCsample1 = "ttbb";
  TString MCsample2 = "ttH_m120_PUTAG";
  TString varName = "lep1Pt";
  

  
  TFile * sourceFile1 = new TFile ("root"+lepselection+"/"+MCsample1+"_"+jetselection+"_.root");
  TFile * sourceFile2 = new TFile ("root"+lepselection+"/"+MCsample2+"_"+jetselection+"_.root");
  double minX = 0;
  double maxX = 200;
  int nbins = 100;
  
  TCanvas * can1a = new TCanvas ("can1a", "can1a");

  sourceFile1->cd();
  gDirectory->cd();
  TH1 * sourceHisto1 = (TH1*) gDirectory->Get(varName);
  int nBinsX = sourceHisto1->GetNbinsX();
  int nBinsY = sourceHisto1->GetNbinsY();
  double xMin = sourceHisto1->GetXaxis()->GetBinCenter(1) - sourceHisto1->GetXaxis()->GetBinWidth(1)/2;
  double xMax = sourceHisto1->GetXaxis()->GetBinCenter(nBinsX)+ sourceHisto1->GetXaxis()->GetBinWidth(1)/2;
  double n1 = sourceHisto1->Integral(1,10001);
  sourceHisto1->Scale(1/n1);
  sourceHisto1->GetXaxis()->SetRange(minX,maxX);
  
  sourceFile2->cd();
  gDirectory->cd();
  TH1 * sourceHisto2 = (TH1*) gDirectory->Get(varName);
  double n2 = sourceHisto2->Integral(1,10001);
  sourceHisto2->Scale(1/n2);
  sourceHisto2->GetXaxis()->SetRange(minX,maxX);

  
  sourceHisto1->SetMaximum(1.2*max(sourceHisto1->GetMaximum(),sourceHisto2->GetMaximum()));
  
  can1a->cd();
  sourceHisto1->Draw("hist");
  sourceHisto2->Draw("histsame");
  can1a->SaveAs("overlay.png");
  
}  
  
