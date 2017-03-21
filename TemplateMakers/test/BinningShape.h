class BinningShape
{
 #include "TH2F.h"
 #include "TFile.h"
 private:
  TH2F *hBinning_2l;
 public:
  BinningShape(){
    
    TString file_str = "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/binning_2l.root"
    const char* env_p = std::getenv("CMSSW_BASE");
    std::string env_p_str = env_p;
    env_p_str += file_str;

    TFile *h_file = new TFile(env_p_str,"READONLY");
    hBinning_2l = (TH2F*)h_file->Get("hTargetBinning");
    hBinning_2l->SetDirectory(0); //reads hists into memory
    h_file->Close();

  };//default constructor

  int get_bin(double x, double y, bool classical = false)
  {
    if (!classical) return hBinning_2l->GetBinContent( hBinning_2l->FindBin(x,y) ) + 1;
    else
      {
	if      ((-1. < y ) && ( y <= 1)   && (-1.0 < y) && (y <= -0.2))  return 0+1;
	else if ((-1. < x ) && ( x <= 1)   && (-0.2 < y) && ( y  <=  0.1))  return 1+1;
	else if ((-1. < x ) && ( x <= 0.3) && (0.1  < y) && ( y  <=  0.4))  return 2+1;
	else if ((0.3 < x ) && ( x <= 1.)  && (0.1  < y) && ( y  <=  0.4))  return 3+1;
	else if ((-1. < x ) && ( x <= 0.1) && (0.4  < y) && ( y  <=  1.0))  return 4+1;
	else if ((0.1 < x ) && ( x <= 0.4) && (0.4  < y) && ( y  <=  1.0))  return 5+1;
	else if ((0.4 < x ) && ( x <= 1.)  && (0.4  < y) && ( y  <=  1.0))  return 6+1;
	else {
	  cout <<  "one bin is missing " << x << " " << y << endl;
	  return -1;
	}
      }
  }
  virtual ~BinningShape(){};
};
