
#include "TString.h"
#include <vector>
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include <cmath>
#include <iomanip>
#include "TCanvas.h"
#include <iostream>
#include "TLegend.h"
#include "TChain.h"

///////////////////////////////////////////////
//
//    Load this up
//    .L thisFile.C+
//
///////////////////////////////////////////////


class HistoInfo {

public:
  TString canName;
  TString varName;
  TString binning;

  HistoInfo (TString cn, TString vn, TString bin):
    canName(cn), varName(vn), binning(bin)
  {};
  
};


void handleOverflow (TH1 * inputHisto ) {

  int numBins = inputHisto->GetNbinsX();
  
  inputHisto->SetBinContent(1, inputHisto->GetBinContent(0)+ inputHisto->GetBinContent(1));
  inputHisto->SetBinContent(0,0);

  inputHisto->SetBinContent(numBins, inputHisto->GetBinContent(numBins)+ inputHisto->GetBinContent(numBins+1));
  inputHisto->SetBinContent(numBins+1,0);
  
}


void drawTwoSummaryTrees () {

  //TFile * origFile = new TFile ("test_beans_v1_zjets_baselineJER_job_2.root");

  //TFile * newFile = new TFile ("dilSummaryTrees_checkJER_job002.root");

  TChain * origTree = new TChain ("summaryTree");
  origTree->AddFile("test_beans_v1_ttH120_robinUpdates_job_0.root");
  //origTree->AddFile("test_beans_v1_zjets_baselineJER_job_1.root");
  
  TChain * newTree = new TChain ("summaryTree");
  newTree->AddFile("dilSummaryTrees_robinUpdates_job000.root");
  //newTree->AddFile("dilSummaryTrees_checkJER_job001.root");
  

  

  newTree->SetLineColor(kRed);

  vector<HistoInfo> myHistos;
  myHistos.push_back(HistoInfo(TString("can1"), TString("first_jet_pt"), TString("(25,0,400)")));
  myHistos.push_back(HistoInfo(TString("can2"), TString("met"), TString("(25,0,100)")));
  myHistos.push_back(HistoInfo(TString("can3"), TString("pt_of_everything"), TString("(25,0,250)")));
  myHistos.push_back(HistoInfo(TString("can4"), TString("mindr_lep1_jet"), TString("(25,0,6)")));
  myHistos.push_back(HistoInfo(TString("can5"), TString("prob"), TString("(25,0,1.5)")));
  myHistos.push_back(HistoInfo(TString("can6"), TString("prob_hfSFup"), TString("(25,0,1.5)")));
  myHistos.push_back(HistoInfo(TString("can7"), TString("prob_hfSFdown"), TString("(25,0,1.5)")));
  myHistos.push_back(HistoInfo(TString("can8"), TString("prob_lfSFdown"), TString("(25,0,1.5)")));
  myHistos.push_back(HistoInfo(TString("can9"), TString("prob_lfSFup"), TString("(25,0,1.5)")));
  myHistos.push_back(HistoInfo(TString("can10"), TString("weight"), TString("(25,0,1.5)")));
  myHistos.push_back(HistoInfo(TString("can11"), TString("weight_PUdown"), TString("(25,0,1.5)")));
  myHistos.push_back(HistoInfo(TString("can12"), TString("weight_PUup"), TString("(25,0,1.5)")));
  
  

  TString selection = "numTightMuons==2 && numTightElectrons==0 && numLooseMuons==0 && numLooseElectrons==0 && numJets >= 2";

  for (vector<HistoInfo>::iterator iHisto = myHistos.begin();
       iHisto != myHistos.end();
       iHisto++){
    std::cout << "--------New histos-------" << std::endl;
    TCanvas * tempCan = new TCanvas (iHisto->canName, iHisto->canName, 600, 900);
    tempCan->Divide(1,2);
    TString numerName = "numerHist_" + iHisto->varName;
    TString denomName = "denomHist_" + iHisto->varName;
    TString drawNumer = iHisto->varName + " >> " + numerName + iHisto->binning;
    TString drawDenom = iHisto->varName + " >> " + denomName + iHisto->binning;
    TString titleString = iHisto->varName + ";" + iHisto->varName;
    TString imageNameString = iHisto->varName + ".png";
    
    
    std::cout << "Drawing " << drawNumer << std::endl;
    std::cout << "Drawing " << drawDenom << std::endl;
      
    tempCan->cd(1);
    origTree->Draw(drawDenom, selection, "goff");
    newTree->Draw(drawNumer, selection, "goff");

    TH1 * tempDenom = (TH1*) gDirectory->Get(denomName);
    TH1 * tempNumer = (TH1*) gDirectory->Get(numerName);

    tempDenom->SetTitle(titleString);
    handleOverflow(tempDenom);
    handleOverflow(tempNumer);

    TLegend * tempLeg = new TLegend (0.7, 0.7, 0.85, 0.85);

    tempLeg->AddEntry(tempDenom, "Original", "l");
    tempLeg->AddEntry(tempNumer, "WithJER", "l");
    

    tempDenom->DrawCopy();
    tempNumer->DrawCopy("same");
    tempLeg->Draw();
    

    TH1 * ratio = (TH1*) tempDenom->Clone("ratioHist");

    ratio->Reset("ICE");

    for (int iBin = 1; iBin < ratio->GetNbinsX() +1; iBin++){

      if (tempDenom->GetBinContent(iBin) == 0 ){
        ratio->SetBinContent(iBin, 0);
        ratio->SetBinError(iBin, 0);
      } else {
        double up = tempNumer->GetBinContent(iBin);
        double upError = sqrt(up);
        double down = tempDenom->GetBinContent(iBin);
        double downError = sqrt(down);
        double eff = up/down;       
        double errorEff = sqrt((upError/up)*(upError/up) +
                               (downError/down)*(downError/down));
        
        ratio->SetBinContent(iBin, eff);
        ratio->SetBinError(iBin, errorEff);
        
      }
    }

    tempCan->cd(2);
    ratio->SetMaximum(1.2);
    ratio->SetMinimum(0.8);

    ratio->Draw("pe");


    tempCan->SaveAs(imageNameString);
    

  }

  
  

  
}


