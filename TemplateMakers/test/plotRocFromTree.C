///////////////////////////
///
/// charlie mueller 2/24/2016
///
///////////////////////////

TString signal_file1 = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_weightedBkgSq/ttH_sum_v2.root";
TString background_file1 = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_weightedBkgSq/ttbar_sum_v2.root";

// TString signal_file2 = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_hiMatch_weightedBkg/ttH_sum.root";
// TString background_file2 = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_hiMatch_weightedBkg/ttbar_sum.root";

// TString signal_file3 = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_hiMatchBkg/ttH_sum.root";
// TString background_file3 = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_hiMatchBkg/ttbar_sum.root";

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
  if (selection == "2lss") chain_name = "ss2l_csvSorted_tree"; 
  else if (selection == "3l") chain_name = "threelep_tree"; 

  TChain *chain_sig = new TChain(chain_name);
  TChain *chain_bkg = new TChain(chain_name);

  if (sample == 1)
    {
      chain_sig->Add(signal_file1);
      chain_bkg->Add(background_file1);
    }
  // else if (sample == 2)
  //   {
  //     chain_sig->Add(signal_file2);
  //     chain_bkg->Add(background_file2);
  //   }
  // else if (sample == 3)
  //   {
  //     chain_sig->Add(signal_file3);
  //     chain_bkg->Add(background_file3);
  //   }

  TH1D* sig_h = new TH1D("sig_h","sig_h",num_bins,xmin,xmax);
  TH1D* bkg_h = new TH1D("bkg_h","bkg_h",num_bins,xmin,xmax);

  //  TCut cuts = "mcwgt*(tightMvaBased_leptons[[]].lepMVA > 0.75)";
  TCut cuts = "hadTop.M() < 220";
  TString draw_variable_signal = variable_name + " >> sig_h";
  TString draw_variable_background = variable_name + " >> bkg_h";

  chain_sig->Draw(draw_variable_signal, cuts, "goff");
  chain_bkg->Draw(draw_variable_background, cuts, "goff");

  if ( !reverse) return makeRoc(bkg_h,sig_h);
  else return makeRoc(sig_h,bkg_h);
}

void plotRocFromTree(void)
{

  TString variable_name = "hadTop.M()";
  int num_bins = 100;
  double xmin = 0;
  double xmax = 220;
  TGraph* roc_curve1 = getRoc(1,variable_name,num_bins,xmin,xmax,true);

  char label1[512];
  float roc_integral1 = roc_curve1->Integral()+0.5;
  sprintf(label1,"ROC: %.5f",roc_integral1);

  // TGraph* roc_curve2 = getRoc(2,variable_name,num_bins,xmin,xmax,true);
  // char label2[512];
  // float roc_integral2 = roc_curve2->Integral()+0.5;
  // sprintf(label2,"hiMatch, ROC: %.5f",roc_integral2);

  // TGraph* roc_curve3 = getRoc(3,variable_name,num_bins,xmin,xmax,true);
  // char label3[512];
  // float roc_integral3 = roc_curve3->Integral()+0.5;
  // sprintf(label3,"special , ROC: %.5f",roc_integral3);

  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("can", "can");
  can1->SetGrid();
  
  roc_curve1->SetLineColor(1);
  // roc_curve2->SetLineColor(2);
  // roc_curve3->SetLineColor(4);

  roc_curve1->Draw("AC");
  // roc_curve2->Draw("same");
  // roc_curve3->Draw("same");
  TLegend *leg = new TLegend(0.1925287,0.3474576,0.5732759,0.4661017,NULL,"brNDC");
  leg->SetTextSize(0.03); 
  leg->AddEntry(roc_curve1,label1,"l");
  // leg->AddEntry(roc_curve2,label2,"l");
  // leg->AddEntry(roc_curve3,label3,"l");
  leg->SetFillColor(0);
  leg->Draw("same");
  can1->SaveAs("roc.png");  

}


