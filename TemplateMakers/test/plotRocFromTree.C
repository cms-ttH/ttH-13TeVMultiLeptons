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
  roc_curve->SetTitle("ttH - 3l selection");
  roc_curve->GetXaxis()->SetTitle("signal efficiency");
  roc_curve->GetYaxis()->SetTitle("background rejection");
  roc_curve->SetLineWidth(2);
  return roc_curve;
}

TGraph* getRoc(TString file_name)
{

  TChain *chain = new TChain("threelep_tree");
  chain->Add(file_name);
  TH1D* sig_h = new TH1D("sig_h","sig_h",50,-1,1);
  TH1D* bkg_h = new TH1D("bkg_h","bkg_h",50,-1,1);
  chain->Draw("bdt_score >> sig_h","bdt_score > -9 && had_top_present","goff");
  chain->Draw("bdt_score >> bkg_h","bdt_score > -9 && !had_top_present","goff");
  return makeRoc(sig_h,bkg_h);  
}

//overloaded
TGraph* getRoc(TString file_name1, TString file_name2)
{

  TChain *chain1 = new TChain("threelep_tree");
  chain1->Add(file_name1);
  TChain *chain2 = new TChain("threelep_tree");
  chain2->Add(file_name2);
  TH1D* sig_h = new TH1D("sig_h","sig_h",50,-1,1);
  TH1D* bkg_h = new TH1D("bkg_h","bkg_h",50,-1,1);
  chain1->Draw("bdt_score >> sig_h","bdt_score > -9","goff");
  chain2->Draw("bdt_score >> bkg_h","bdt_score > -9","goff");
  return makeRoc(sig_h,bkg_h);  
}


void plotRocFromTree(void)
{

  // TGraph* roc_curve1 = getRoc("tth_trees.root","ttw_trees.root");
  // TGraph* roc_curve2 = getRoc("tth_trees_bdt_top_ratio.root","ttw_trees_bdt_top_ratio.root");
  TGraph* roc_curve1 = getRoc("tth_trees.root");
  TGraph* roc_curve2 = getRoc("tth_trees_bdtSelectionTraining.root");
  char label1[512];
  float roc_integral1 = roc_curve1->Integral();
  sprintf(label1,"BDT2, ROC: %.4f",roc_integral1);

  char label2[512];
  float roc_integral2 = roc_curve2->Integral();
  sprintf(label2,"BDT2 training selection (3l), ROC: %.4f",roc_integral2);

  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("can", "can");
  can1->SetGrid();
  
  roc_curve1->SetLineColor(1);
  roc_curve2->SetLineColor(2);

  roc_curve1->Draw("AC");
  roc_curve2->Draw("same");
  TLegend *leg = new TLegend(0.1925287,0.3474576,0.5732759,0.4661017,NULL,"brNDC");
  leg->SetTextSize(0.03); 
  leg->AddEntry(roc_curve1,label1,"l");
  leg->AddEntry(roc_curve2,label2,"l");
  leg->SetFillColor(0);
  leg->Draw("same");
  can1->SaveAs("roc.png");  

}


