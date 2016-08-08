void plotHist(TH1D* sig_h, TH1D* bkg_h, TString title)
{
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  //  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("can", "can");
  can1->SetGrid();

  sig_h->SetTitle("");
  // sig_h->GetXaxis()->SetRangeUser(0.,1.4);
  sig_h->GetXaxis()->SetTitle(title);
  sig_h->GetYaxis()->SetTitle("normalized units");

  sig_h->SetFillColor(2);  
  bkg_h->SetFillColor(4);
  bkg_h->SetFillStyle(3001);
  sig_h->Draw("hist");
  bkg_h->Draw("histsame");
  
  if (sig_h->GetMaximum() < bkg_h->GetMaximum())
    {
      sig_h->SetMaximum(bkg_h->GetMaximum()*1.1);
    }
  
  TLegend *leg = new TLegend(0.6135057,0.7097458,0.8563218,0.8283898,NULL,"brNDC");
  leg->AddEntry(sig_h,"ttH","F");
  leg->AddEntry(bkg_h,"ttbar","F");
  leg->SetFillColor(0);
  leg->Draw("same");
  can1->SaveAs("plot.png");  

}

void plotRoc(TH1D* sig, TH1D* bkg, TString title)
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
  TString hist_title = title + " - 2lss";
  roc_curve->SetTitle(hist_title);
  roc_curve->GetXaxis()->SetRangeUser(0.,1.);
  roc_curve->GetYaxis()->SetRangeUser(0.,1.);
  roc_curve->GetXaxis()->SetTitle("signal efficiency");
  roc_curve->GetYaxis()->SetTitle("background rejection");
  roc_curve->SetLineWidth(2);

  char label1[512];
  float roc_integral1 = roc_curve->Integral()+0.5;
  sprintf(label1,"ROC: %.5f",roc_integral1);

  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("roc can", "roc can");
  can1->SetGrid();

  roc_curve->SetLineColor(2);
  roc_curve->Draw("AC");
  TLegend *leg = new TLegend(0.1925287,0.3474576,0.5732759,0.4661017,NULL,"brNDC");
  leg->SetTextSize(0.03); 
  leg->AddEntry(roc_curve,label1,"l");

  leg->SetFillColor(0);
  leg->Draw("same");
  can1->SaveAs("roc.png");  
}

void plotVarsFromTree(void)
{

  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_weightedBkgSq/ttH_sum_v2.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_weightedBkgSq/ttbar_sum_v2.root";
  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baselineBdt_v1/ttH_tree.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baselineBdt_v1/ttbar_tree.root";

  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v0p6/ttH-powheg_batch_bdtEval.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v0p6/ttbar-semiLep-powheg_batch_bdtEval.root";

  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v0_July12_1541/ttH_tree.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v0_July12_1541/ttbar_tree.root";

  TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1_Aug8/ttH_tree.root";
  TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1_Aug8/ttbar_tree.root";

  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reconsruction_study_ttH_nonBest.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reconsruction_study_ttbar__nonBest.root";
  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reconsruction_study_ttH.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reconsruction_study_ttbar.root";


  TChain *chain1 = new TChain("ss2l_tree");
  chain1->Add(signal_file);
  TChain *chain2 = new TChain("ss2l_tree");
  chain2->Add(background_file);

  TCut cut = "";
  //  TString var = "lepTop_hadTop_dR"; TString title = "dR(lep top, had top)";
  //  TString var = "hadTop_tlv.M()"; TString title = "hadronic top mass"; int nBins = 20; double xMin = 0; double xMax = 300;
  TString var = "reco_score"; TString title = "bdt v0p6"; int nBins = 30; double xMin = -1.; double xMax = 1.;
  //  TString var = "lepTop_tlv.M()"; TString title = "leptonic top mass"; int nBins = 30; double xMin = 0; double xMax = 700;
  //  TString var = "lepTop_tlv.Pt()"; TString title = "leptonic top pt"; int nBins = 20; double xMin = 0; double xMax = 800;
  //  TString var = "hadTop_tlv.Pt()"; TString title = "hadronic top pt"; int nBins = 30; double xMin = 0; double xMax = 600;
  //  TString var = "hadTop_tlv.M() + lepTop_tlv.M()"; TString title = "top sys mass"; int nBins = 30; double xMin = 0; double xMax = 1000;
  //  TString var = "ttbar_tlv.Pt()"; TString title = "top sys pt"; int nBins = 30; double xMin = 0; double xMax = 700;
  //  TString var = "abs(ttbar_tlv.Eta())"; TString title = "top sys eta"; int nBins = 30; double xMin = 0; double xMax = 5;
  //  TString var = "abs(lepTop_tlv.Eta())"; TString title = "lep top eta"; int nBins = 30; double xMin = 0; double xMax = 5;
  //  TString var = "abs(hadTop_tlv.Eta())"; TString title = "had top eta"; int nBins = 30; double xMin = 0; double xMax = 5;
  //  TString var = "lepTop_T_tlv.M()"; TString title = "lep top transverse mass"; int nBins = 30; double xMin = 0; double xMax = 700;
  TString draw_sig = var + " >> sig_h";
  TString draw_bkg = var + " >> bkg_h";

  TH1D* sig_h = new TH1D("sig_h","sig_h",nBins,xMin,xMax);
  TH1D* bkg_h = new TH1D("bkg_h","bkg_h",nBins,xMin,xMax);

  chain2->Draw(draw_bkg,cut,"goffnorm");
  chain1->Draw(draw_sig,cut,"goffnorm");



  plotHist(sig_h, bkg_h, title);
  plotRoc(sig_h, bkg_h, title);
  //  plotRoc(bkg_h, sig_h, title);
  

}


