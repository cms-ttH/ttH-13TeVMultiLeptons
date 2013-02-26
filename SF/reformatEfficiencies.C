// script to reformat the POG/PAG efficiencies

#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TH2F.h"
#include <vector>
#include <iostream>
#include <iomanip>


const static double lumiA = 0.802 + 0.082;
const static double lumiB = 4.403;
const static double lumiC = 6.388 + 0.494;
const static double lumiD = 7.274;

const static double lumiTotal = lumiA + lumiB + lumiC + lumiD;

class etaEffGroup {

public:
  double firstBin, secondBin, thirdBin;

  etaEffGroup(): firstBin(0.0), secondBin(0.0), thirdBin(0.0) {};
  
  
};

class dataPeriodGroup {

public:
  etaEffGroup A,B,C,D;


  dataPeriodGroup (): A(),B(),C(),D() {};

  void computelumiWeightedAverage (double & eta1, double & eta2, double & eta3) {

    eta1 = A.firstBin * lumiA + B.firstBin * lumiB
      + C.firstBin * lumiC + D.firstBin * lumiD;

    eta1 = eta1 / lumiTotal;

    eta2 = A.secondBin * lumiA + B.secondBin * lumiB
      + C.secondBin * lumiC + D.secondBin * lumiD;

    eta2 = eta2 / lumiTotal;
 
    eta3 = A.thirdBin * lumiA + B.thirdBin * lumiB
      + C.thirdBin * lumiC + D.thirdBin * lumiD;

    eta3 = eta3 / lumiTotal;
   
    return;
    
  };
  
};



TH1F *  convertGraphToHist ( TGraphAsymmErrors * myGraph) {

  if (myGraph == 0) {
    cout << "Null pointer given" << endl;
    return 0;
  }
    
  
  using namespace std;
  
  TH1F * myHist;

  int numBins = myGraph->GetN();

  // we need to clean this up
  double * myBinLowEdges = new double[numBins+1];

  // not sure who owns these
  Double_t * xValues = myGraph->GetX();
  Double_t * yValues = myGraph->GetY();
 

  for (int iBin =0; iBin < numBins; iBin++){

    double binCenter = xValues[iBin];
    double binLowEdge = binCenter - myGraph->GetErrorXlow(iBin);
    double binHighEdge = binCenter + myGraph->GetErrorXhigh(iBin);

    cout << "Bin = " << iBin
         << " center = " << xValues[iBin]
         << " low edge = " << binLowEdge
         << " high edge = " << binHighEdge
         << endl;

    myBinLowEdges[iBin] = binLowEdge;

    //---- Handle the end
    
    if (iBin == numBins-1) {
      myBinLowEdges[iBin+1] = binHighEdge;
    }
   
  }

  
  TString histName = TString(myGraph->GetName())+TString("_hist");
  TString histTitle = myGraph->GetTitle();
  myHist = new TH1F (histName, histTitle, numBins, myBinLowEdges);

  for (int iBin =1; iBin < numBins+1; iBin++){
    myHist->SetBinContent(iBin, yValues[iBin-1]);
    myHist->SetBinError(iBin, yValues[iBin-1]*0.01);
    
  }
  

  delete myBinLowEdges;

  return myHist;
  

  
}



void reformatEfficiencies () {

  using namespace std;

  TFile * pogInput = new TFile ("Muon_ID_iso_Efficiencies_Run_2012ABCD_53X.root");


  pogInput->cd();


  TGraphAsymmErrors * eta_lt_09 = (TGraphAsymmErrors *) gDirectory->Get("DATA_over_MC_Tight_pt_abseta<0.9_2012ABCD");
  TGraphAsymmErrors * eta_09_to_12 = (TGraphAsymmErrors *) gDirectory->Get("DATA_over_MC_Tight_pt_abseta0.9-1.2_2012ABCD");
  TGraphAsymmErrors * eta_12_to_21 = (TGraphAsymmErrors *) gDirectory->Get("DATA_over_MC_Tight_pt_abseta1.2-2.1_2012ABCD");


  TH1F * hist_lt_09 = convertGraphToHist(eta_lt_09);
  TH1F * hist_09_to_12 = convertGraphToHist(eta_09_to_12);
  TH1F * hist_12_to_21 = convertGraphToHist(eta_12_to_21);
  

//   TCanvas * graphCan = new TCanvas("graphCan", "graphCan");
//   graphCan->cd();

  
//   eta_lt_09->Draw("AP");
//   TH1F* drawnHisto = eta_lt_09->GetHistogram();
//   double gMax = drawnHisto->GetMaximum();
//   double gMin = drawnHisto->GetMinimum();

//   cout << "Graph min = " << gMin << " max = " << gMax << endl;
  
//   //eta_lt_09->SetMaximum(1.2*gMax);

//   //eta_lt_09->Draw("AP");

//   TCanvas * histCan = new TCanvas ("histCan", "histCan");
  
//   histCan->cd();
//   hist_lt_09->SetMaximum(gMax);
//   hist_lt_09->SetMinimum(gMin);
//   hist_lt_09->DrawCopy("pe");


  int numPtBins = hist_lt_09->GetNbinsX();
  double * lowEdgesPt = new double[numPtBins+1];

  cout << "Getting low edge of pt bins" << endl;
  hist_lt_09->GetLowEdge(lowEdgesPt);

  lowEdgesPt[numPtBins] = hist_lt_09->GetBinLowEdge(numPtBins+1);

  for (int iThing = 0; iThing < numPtBins+1; iThing++) {
    cout << "Check low edge num " << iThing << " value " << lowEdgesPt[iThing] << endl;
  }
  
  
  //
  cout << "Creating eta bin array" <<endl;
  const int numEtaBins = 3;
  double * lowEdgesEta = new double[numEtaBins+1];

  lowEdgesEta[0] = 0.0;
  lowEdgesEta[1] = 0.9;
  lowEdgesEta[2] = 1.2;
  lowEdgesEta[3] = 2.1;

  cout << "Creating 2d hist" << endl;


  TFile * myFile = new TFile ("lepton_SF_8TeV_53x.root", "RECREATE");
  
  TH2F * twoDimEfficiency = new TH2F ("mu_pt_eta_full_id_iso_8TeV", "ID*ISO", numPtBins, lowEdgesPt, numEtaBins, lowEdgesEta);
  

  
  TAxis * xAxis = twoDimEfficiency->GetXaxis();
  TAxis * yAxis = twoDimEfficiency->GetYaxis();

  cout << "Num x bins " << xAxis->GetNbins() << endl
       << "Num y bins " << yAxis->GetNbins() << endl;

  for (int xBin = 1; xBin < xAxis->GetNbins()+1; xBin ++) {
    cout << "=============================================" << endl
         << "xBin = " << xBin << endl;
    
    int globalBin_00_to_09 = twoDimEfficiency->FindBin(xAxis->GetBinCenter(xBin), yAxis->GetBinCenter(1));
    int globalBin_09_to_12 = twoDimEfficiency->FindBin(xAxis->GetBinCenter(xBin), yAxis->GetBinCenter(2));
    int globalBin_12_to_21 = twoDimEfficiency->FindBin(xAxis->GetBinCenter(xBin), yAxis->GetBinCenter(3));
    
    twoDimEfficiency->SetBinContent(globalBin_00_to_09, hist_lt_09->GetBinContent(xBin));
    twoDimEfficiency->SetBinContent(globalBin_09_to_12, hist_09_to_12->GetBinContent(xBin));
    twoDimEfficiency->SetBinContent(globalBin_12_to_21, hist_12_to_21->GetBinContent(xBin));


    cout << "For pt bin center " << xAxis->GetBinCenter(xBin) << endl
         << "  Eta 00-09 is global bin  " << twoDimEfficiency->GetBinContent(globalBin_00_to_09)  << endl
         << "  Eta 09-12 is global bin  " << twoDimEfficiency->GetBinContent(globalBin_09_to_12)  << endl
         << "  Eta 12-21 is global bin  " << twoDimEfficiency->GetBinContent(globalBin_12_to_21) << endl;
    
    
  }


  twoDimEfficiency->DrawCopy("colz");

  
  hist_lt_09->SetDirectory(myFile);
  hist_09_to_12->SetDirectory(myFile);
  hist_12_to_21->SetDirectory(myFile);

  twoDimEfficiency->SetDirectory(myFile);





  ////////////////////////////////////////////////////////////////////////
  //
  //  Switch Gears to open the trigger files, 
  //  then do a lumi-weighted averge
  //
  //
  /////////////////////////////////////////////////////////////////////////


  // 3 files, 4 data periods
  TFile * pogTrigAB = new TFile ("MuonEfficiencies_Run_2012A_2012B_53X.root");
  TFile * pogTrigC = new TFile  ("MuonEfficiencies_Run_2012C_53X.root");
  TFile * pogTrigD = new TFile  ("TriggerMuonEfficiencies_Run_2012D_53X.root");
                               
  //12 histograms total
  std::vector<TH1F *> triggerA;
  vector<TH1F *> triggerB;
  vector<TH1F *> triggerC;
  vector<TH1F *> triggerD;
  
  vector< vector<double> > summedEffs;
  

  triggerA.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigAB->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta<0.9_2012A")));
  triggerA.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigAB->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta0.9-1.2_2012A")));
  triggerA.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigAB->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta1.2-2.1_2012A")));
  
  triggerB.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigAB->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta<0.9_2012B")));
  triggerB.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigAB->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta0.9-1.2_2012B")));
  triggerB.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigAB->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta1.2-2.1_2012B")));


   triggerC.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigC->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta<0.9")));
   triggerC.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigC->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta0.9-1.2")));
   triggerC.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigC->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta1.2-2.1")));

   triggerD.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigD->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta<0.9_2012D")));
   triggerD.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigD->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta0.9-1.2_2012D")));
   triggerD.push_back(convertGraphToHist((TGraphAsymmErrors*) pogTrigD->Get("DATA_over_MC_IsoMu24_eta2p1_TightIso_pt_abseta1.2-2.1_2012D")));

  summedEffs.push_back(vector<double>());
  summedEffs.push_back(vector<double>());
  summedEffs.push_back(vector<double>());
  
  
  

  // Do the lumi average

//   double lumiA = 0.802 + 0.082;
//   double lumiB = 4.403;
//   double lumiC = 6.388 + 0.494;
//   double lumiD = 7.274;



  cout << "Total lumi is " << lumiTotal << endl;
  cout << "Total number of bins for trigger eff is " << triggerA[0]->GetNbinsX() << endl;

  for (int iBin = 1; iBin < triggerA[0]->GetNbinsX()+1; iBin++) {

    // three eta bins, 4 data periods;

    dataPeriodGroup effThisBin;
    
    cout << "iBin = " << iBin << " " << endl
         << " Period A, eta 00-09 = " << triggerA[0]->GetBinContent(iBin)  << endl
         << " Period B, eta 00-09 = " << triggerB[0]->GetBinContent(iBin) << endl
         << " Period C, eta 00-09 = " << triggerC[0]->GetBinContent(iBin) << endl
         << " Period D, eta 00-09 = " << triggerD[0]->GetBinContent(iBin) << endl
         << endl;

    effThisBin.A.firstBin = triggerA[0]->GetBinContent(iBin);
    effThisBin.A.secondBin = triggerA[1]->GetBinContent(iBin);
    effThisBin.A.thirdBin = triggerA[2]->GetBinContent(iBin);

    effThisBin.B.firstBin = triggerB[0]->GetBinContent(iBin);
    effThisBin.B.secondBin = triggerB[1]->GetBinContent(iBin);
    effThisBin.B.thirdBin = triggerB[2]->GetBinContent(iBin);

    effThisBin.C.firstBin = triggerC[0]->GetBinContent(iBin);
    effThisBin.C.secondBin = triggerC[1]->GetBinContent(iBin);
    effThisBin.C.thirdBin = triggerC[2]->GetBinContent(iBin);

    effThisBin.D.firstBin = triggerD[0]->GetBinContent(iBin);
    effThisBin.D.secondBin = triggerD[1]->GetBinContent(iBin);
    effThisBin.D.thirdBin = triggerD[2]->GetBinContent(iBin);

    double e1, e2, e3;
    effThisBin.computelumiWeightedAverage( e1, e2, e3);

    cout << "Average for eta 1 = " << e1 << endl
         << "Average for eta 2 = " << e2 << endl
         << "Average for eta 3 = " << e3 << endl
         << endl;

    summedEffs[0].push_back(e1);
    summedEffs[1].push_back(e2);
    summedEffs[2].push_back(e3);
    
    
  }

  cout << "Number of bins is " << summedEffs[0].size() << endl;
  // Bin harmonization 
  // In the trigger study the SF did not have the same bins.
  // Add an extra bin that is a copy of the last bin.

  summedEffs[0].push_back(summedEffs[0].back());
  summedEffs[1].push_back(summedEffs[1].back());
  summedEffs[2].push_back(summedEffs[2].back());

  cout << "After harmonization, number of bins is " << summedEffs[0].size() << endl;
  
  TH2F * avgTrigEff2d = (TH2F*) twoDimEfficiency->Clone("mu_pt_eta_full_id_iso_hlt_8TeV");
  avgTrigEff2d->SetTitle("ID*ISO*TRIG");

  TAxis * avgXaxis = avgTrigEff2d->GetXaxis();
  TAxis * avgYaxis = avgTrigEff2d->GetYaxis();

  // for each pt bin
  // but x-axis starts at 25 for trigger
  for (int xBin = 3; xBin < avgXaxis->GetNbins()+1; xBin++){
    int trigBin = xBin -3;
    cout << "====== filling eta for pt bin = " << xBin << " ===================" << endl;
    cout << " Corresponds to trigger efficiency bin = " << trigBin << endl;
    
    int globalBin_00_to_09 = avgTrigEff2d->FindBin(avgXaxis->GetBinCenter(xBin), avgYaxis->GetBinCenter(1));
    int globalBin_09_to_12 = avgTrigEff2d->FindBin(avgXaxis->GetBinCenter(xBin), avgYaxis->GetBinCenter(2));
    int globalBin_12_to_21 = avgTrigEff2d->FindBin(avgXaxis->GetBinCenter(xBin), avgYaxis->GetBinCenter(3));

    cout << "Original content pt bin = " << xBin << endl
         << "   eta (00-09), global bin " << globalBin_00_to_09
         << " = " << avgTrigEff2d->GetBinContent(globalBin_00_to_09) << endl
         << " trigger eff  = " << summedEffs[0][trigBin]      
         << endl;
    
    avgTrigEff2d->SetBinContent(globalBin_00_to_09, avgTrigEff2d->GetBinContent(globalBin_00_to_09) * summedEffs[0][trigBin]);
    avgTrigEff2d->SetBinContent(globalBin_09_to_12, avgTrigEff2d->GetBinContent(globalBin_09_to_12) * summedEffs[1][trigBin]);
    avgTrigEff2d->SetBinContent(globalBin_12_to_21, avgTrigEff2d->GetBinContent(globalBin_12_to_21) * summedEffs[2][trigBin]);

    cout << " new eff = " << avgTrigEff2d->GetBinContent(globalBin_00_to_09) << endl;
    
  }

  cout << "Done, closing files" << endl;


  for (unsigned iThing = 0; iThing < triggerA.size(); iThing++) {

    triggerA[iThing]->SetDirectory(myFile);
    triggerB[iThing]->SetDirectory(myFile);
    triggerC[iThing]->SetDirectory(myFile);
    
  }
  
  avgTrigEff2d->SetDirectory(myFile);



  // Now copy histos from other files over
  TFile * originalFile = new TFile ("lepton_SF_8TeV.root");

  TH2F * eleAllTrig = (TH2F*) originalFile->Get("ele_pt_eta_full_id_iso_hlt_8TeV")->Clone();

  eleAllTrig->SetDirectory(myFile);

  //New Ele SF
  int numElePtBins = 4;
  double * lowEdgesElePt = new double[numElePtBins+1];

  lowEdgesElePt[0] = 20.0;
  lowEdgesElePt[1] = 30.0;
  lowEdgesElePt[2] = 40.0;
  lowEdgesElePt[3] = 50.0;
  lowEdgesElePt[4] = 150.0;  

  const int numEleEtaBins = 3;
  double * lowEdgesEleEta = new double[numEtaBins+1];

  lowEdgesEleEta[0] = 0.0;
  lowEdgesEleEta[1] = 0.8;
  lowEdgesEleEta[2] = 1.48;
  lowEdgesEleEta[3] = 2.5;

  double bin_content[3][4] = {
    {0.975, 0.978, 0.979, 0.968},
    {0.953, 0.974, 0.979, 0.977},
    {0.930, 0.950, 0.974, 0.974}
  };

  TH2F * eleIDISO = new TH2F ("ele_pt_eta_full_id_iso_8TeV", "PF ID SF", numElePtBins, lowEdgesElePt, numEleEtaBins, lowEdgesEleEta);
    
  TAxis * x_axis = eleIDISO->GetXaxis();
  TAxis * y_axis = eleIDISO->GetYaxis();

  cout << "Making new Ele SF two dimensional plot" << endl
       << "Num x bins " << x_axis->GetNbins() << endl
       << "Num y bins " << y_axis->GetNbins() << endl;

  for (int xBin = 1; xBin < x_axis->GetNbins()+1; xBin ++) {
    cout << "=============================================" << endl
         << "xBin = " << xBin << endl;
    
    int globalBin_00_to_08 = eleIDISO->FindBin(x_axis->GetBinCenter(xBin), y_axis->GetBinCenter(1));
    int globalBin_08_to_148 = eleIDISO->FindBin(x_axis->GetBinCenter(xBin), y_axis->GetBinCenter(2));
    int globalBin_148_to_25 = eleIDISO->FindBin(x_axis->GetBinCenter(xBin), y_axis->GetBinCenter(3));
    
    eleIDISO->SetBinContent(globalBin_00_to_08, bin_content[0][xBin-1]);
    eleIDISO->SetBinContent(globalBin_08_to_148, bin_content[1][xBin-1]);
    eleIDISO->SetBinContent(globalBin_148_to_25, bin_content[2][xBin-1]);

    cout << "For pt bin center " << x_axis->GetBinCenter(xBin) << endl
         << "  Eta 0.0-0.8 is global bin  " << eleIDISO->GetBinContent(globalBin_00_to_08)  << endl
         << "  Eta 0.8-1.48 is global bin  " << eleIDISO->GetBinContent(globalBin_08_to_148)  << endl
         << "  Eta 1.48-2.5 is global bin  " << eleIDISO->GetBinContent(globalBin_148_to_25) << endl;
  }

  eleIDISO->DrawCopy("colz");
  eleIDISO->SetDirectory(myFile);
  
  myFile->Write();  
  myFile->Close();


  

}


