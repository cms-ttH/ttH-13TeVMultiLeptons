#include <iostream>
#include "TH2.h"
#include "TROOT.h"
#include "TFile.h"

using namespace std;

class GetBinning
{
public:
  GetBinning();
  Int_t GetCluster2l(Double_t, Double_t);
protected:
  TFile* file2l;
  TH2F* hBinning2l;
};


GetBinning::GetBinning()
{
  TString fileName2l = "../data/CERN/binning_2l.root";
  file2l = (TFile*) gROOT->GetListOfFiles()->FindObject(fileName2l);
  if (!file2l || !file2l->IsOpen()) file2l = TFile::Open(fileName2l);
  hBinning2l = (TH2F*) file2l->Get("hTargetBinning");
}


Int_t GetBinning::GetCluster2l( Double_t x, Double_t y)
{
  return hBinning2l->GetBinContent( hBinning2l->FindBin(x,y) );
}

GetBinning ClusteringSuite;

Int_t OurBin2l(Double_t x, Double_t y)
{
  return ClusteringSuite.GetCluster2l(x,y)+1;

}
