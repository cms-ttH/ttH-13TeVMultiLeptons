{
#include <cmath>
#include <algorithm>
  
  TString lepselection = "DiMuonAll";
  TString jetselection = "eq1t";
  TString MCsample1 = "ttbar_bb";
  TString MCsample2 = "ttH120";
  TString varName = "lep1Pt";
  
  TFile * sourceFile1 = new TFile ("root"+lepselection+"/"+MCsample1+"_nominal_new_"+jetselection+"_.root");
  TFile * sourceFile2 = new TFile ("root"+lepselection+"/"+MCsample2+"_nominal_new_"+jetselection+"_.root");

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
  double xMax = sourceHisto1->GetXaxis()->GetBinCenter(nBinsX) + sourceHisto1->GetXaxis()->GetBinWidth(1)/2;
  double n1 = sourceHisto1->Integral(1,10001);
  sourceHisto1->Scale(1/n1);
  sourceHisto1->SetLineColor(2);
  sourceHisto1->SetTitle(lepselection+"_"+jetselection+" "+varName);
  sourceHisto1->SetName(MCsample1);
  sourceHisto1->GetXaxis()->SetRange(minX,maxX);
  
  sourceFile2->cd();
  gDirectory->cd();
  TH1 * sourceHisto2 = (TH1*) gDirectory->Get(varName);
  double n2 = sourceHisto2->Integral(1,10001);
  sourceHisto2->Scale(1/n2);
  sourceHisto2->SetLineColor(4);
  sourceHisto2->SetName(MCsample2);
  sourceHisto2->GetXaxis()->SetRange(minX,maxX);

  sourceHisto1->SetMaximum(1.2*max(sourceHisto1->GetMaximum(),sourceHisto2->GetMaximum()));

  leg1 = new TLegend(0.75,0.80,0.999,0.999);
  leg1->AddEntry(sourceHisto1,sourceHisto1->GetName(),"l");
  leg1->AddEntry(sourceHisto2,sourceHisto2->GetName(),"l");
  
  can1a->cd();
  sourceHisto1->Draw("hist");
  sourceHisto2->Draw("histsame");
  leg1->Draw();
  can1a->SaveAs("overlay_"+lepselection+"_"+jetselection+"_"+varName+"_"+MCsample1+"_"+MCsample2+".png");
  
}  
  
