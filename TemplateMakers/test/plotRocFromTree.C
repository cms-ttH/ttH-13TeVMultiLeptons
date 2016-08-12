///////////////////////////
///
/// charlie mueller 2/24/2016
///
///////////////////////////

TString signal_file1 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttH_aMCatNLO_bdtEval.root";
TString background_file1 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttbar_powheg_bdtEval.root";

TString signal_file2 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5/ttH_bdtEval.root";
TString background_file2 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5/ttbar_bdtEval.root";

// TString signal_file2 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1_Aug8/ttH_tree.root";
// TString background_file2 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1_Aug8/ttbar_tree.root";

TString signal_file3 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v0_July12_1541/ttH_tree.root";
TString background_file3 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v0_July12_1541/ttbar_tree.root";

TString signal_file4 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v0/ttH_tree.root";
TString background_file4 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v0/ttbar_tree.root";



TString selection = "2lss";
//TString selection = "3l";

TGraph * makeRoc(TH1D* sig, TH1D* bkg)
{
  int num_bins = sig->GetNbinsX()+1;
  double sig_eff[num_bins];
  double bkg_rej[num_bins];  
  float full_integral_sig = sig->Integral();
  float full_integral_bkg = bkg->Integral();
  float integral_sig = 0.;
  float integral_bkg = 0.;
  for (int bin=0; bin < num_bins; bin++)
    {
      integral_sig += sig->GetBinContent(bin);
      integral_bkg += bkg->GetBinContent(bin);
      
      sig_eff[bin] = (full_integral_sig - integral_sig) / full_integral_sig;
      bkg_rej[bin] = integral_bkg / full_integral_bkg;      
    }

  TGraph* roc_curve = new TGraph(num_bins,sig_eff,bkg_rej);
  TString hist_title = "ttH vs. ttbar BDT score - " + selection;
  roc_curve->SetTitle(hist_title);
  roc_curve->GetXaxis()->SetRangeUser(0.,1.);
  roc_curve->GetYaxis()->SetRangeUser(0.,1.);
  roc_curve->GetXaxis()->SetTitle("signal efficiency");
  roc_curve->GetYaxis()->SetTitle("background rejection");
  roc_curve->SetLineWidth(2);
  return roc_curve;
}

TGraph* getRoc(int sample, TString variable_name, int num_bins, double xmin, double xmax, bool reverse=false)
{
  TString chain_name;
  if (selection == "2lss") chain_name = "ss2l_tree"; 
  else if (selection == "3l") chain_name = "threelep_tree"; 

  TChain *chain_sig = new TChain(chain_name);
  TChain *chain_bkg = new TChain(chain_name);

  if (sample == 1)
    {
      chain_sig->Add(signal_file1);
      chain_bkg->Add(background_file1);
    }
  else if (sample == 2)
    {
      chain_sig->Add(signal_file2);
      chain_bkg->Add(background_file2);
    }
  else if (sample == 3)
    {
      chain_sig->Add(signal_file3);
      chain_bkg->Add(background_file3);
    }
  else if (sample == 4)
    {
      chain_sig->Add(signal_file4);
      chain_bkg->Add(background_file4);
    }

  TH1D* sig_h = new TH1D("sig_h","sig_h",num_bins,xmin,xmax);
  TH1D* bkg_h = new TH1D("bkg_h","bkg_h",num_bins,xmin,xmax);

  //  TCut cuts = "mcwgt*(tightMvaBased_leptons[[]].lepMVA > 0.75)";
  TCut cuts = "mcwgt*(1.0)";
  TString draw_variable_signal = variable_name + " >> sig_h";
  TString draw_variable_background = variable_name + " >> bkg_h";

  chain_sig->Draw(draw_variable_signal, cuts, "goff");
  chain_bkg->Draw(draw_variable_background, cuts, "goff");

  if ( !reverse) return makeRoc(bkg_h,sig_h);
  else return makeRoc(sig_h,bkg_h);
}

void plotRocFromTree(void)
{

  TString variable_name = "reco_score";
  int num_bins = 100;
  double xmin = -1;
  double xmax = 1;

  TGraph* roc_curve1 = getRoc(1,variable_name,num_bins,xmin,xmax,true);
  char label1[512];
  float roc_integral1 = roc_curve1->Integral()+0.5;
  sprintf(label1,"v1.5 bT/L ROC: %.5f",roc_integral1);

  TGraph* roc_curve2 = getRoc(2,variable_name,num_bins,xmin,xmax,true);
  char label2[512];
  float roc_integral2 = roc_curve2->Integral()+0.5;
  sprintf(label2,"v1.5 ROC: %.5f",roc_integral2);

  TGraph* roc_curve3 = getRoc(3,variable_name,num_bins,xmin,xmax,true);
  char label3[512];
  float roc_integral3 = roc_curve3->Integral()+0.5;
  sprintf(label3,"v0 ROC: %.5f",roc_integral3);

  TGraph* roc_curve4 = getRoc(4,variable_name,num_bins,xmin,xmax,true);
  char label4[512];
  float roc_integral4 = roc_curve4->Integral()+0.5;
  sprintf(label4,"ICHEP ROC: %.5f",roc_integral4);

  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("can", "can");
  can1->SetGrid();
  
  roc_curve1->SetLineColor(1);
  roc_curve2->SetLineColor(2);
  roc_curve3->SetLineColor(4);
  roc_curve4->SetLineColor(6);

  roc_curve1->Draw("AC");
  roc_curve2->Draw("same");
  roc_curve3->Draw("same");
  roc_curve4->Draw("same");
  TLegend *leg = new TLegend(0.1925287,0.3474576,0.5732759,0.4661017,NULL,"brNDC");
  leg->SetTextSize(0.03); 
  leg->AddEntry(roc_curve1,label1,"l");
  leg->AddEntry(roc_curve2,label2,"l");
  leg->AddEntry(roc_curve3,label3,"l");
  leg->AddEntry(roc_curve4,label4,"l");
  leg->SetFillColor(0);
  leg->Draw("same");
  can1->SaveAs("roc.png");  

}


