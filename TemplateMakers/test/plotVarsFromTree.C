void plotVarsFromTree(void)
{

  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/lxbatch_output/ttH_powheg.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/lxbatch_output/ttW.root";


  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_weightedBkgSq/ttH_sum_v2.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/comparison_bdt_weightedBkgSq/ttbar_sum_v2.root";
  // TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baselineBdt_v1/ttH_tree.root";
  // TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baselineBdt_v1/ttbar_tree.root";

  TString signal_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baseline_original_slimmed/ttH_bdtEval_slimmed_v0.root";
  TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baseline_original_slimmed/ttbar_bdtEval_slimmed_v0.root";

  //  TString background_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/lxbatch_output/ttbar_semiLep_powheg.root";


  TChain *chain1 = new TChain("ss2l_tree");
  chain1->Add(signal_file);
  TChain *chain2 = new TChain("ss2l_tree");
  chain2->Add(background_file);
  //  chain2->Add(background_file1);
  //  chain2->Add(background_file2);
  TH1D* sig_h = new TH1D("sig_h","sig_h",100,-1.3,1);
  TH1D* bkg_h = new TH1D("bkg_h","bkg_h",100,-1.3,1);

  //  TCut cut = "csv_sorted_jets[1].csv < .423 && matched_jets.obj.pt() < 300";
  //  TCut cut = "matched_jets.obj.pt() < 300";
  TCut cut = "@preselected_jets_uncor.size() >= 4";

  chain1->Draw("reco_score >> sig_h",cut,"goffnorm");
  chain2->Draw("reco_score >> bkg_h",cut,"goffnorm");

  // chain1->Draw("higgs.M() >> sig_h","mcwgt*(tightMvaBased_leptons[0].lepMVA > 0.75 && tightMvaBased_leptons[1].lepMVA > 0.75 && higgs.M() > 1)","goffnorm");
  // chain2->Draw("higgs.M() >> bkg_h","mcwgt*(tightMvaBased_leptons[0].lepMVA > 0.75 && tightMvaBased_leptons[1].lepMVA > 0.75 && higgs.M() > 1)","goffnorm");
  // chain1->Draw("higgs.M() >> sig_h","mcwgt*(tightMvaBased_leptons[0].lepMVA > 0.75 && tightMvaBased_leptons[1].lepMVA > 0.75)","goffnorm");
  // chain2->Draw("higgs.M() >> bkg_h","mcwgt*(tightMvaBased_leptons[0].lepMVA > 0.75 && tightMvaBased_leptons[1].lepMVA > 0.75)","goffnorm");

  // chain2->Draw("higgs.Pt() >> bkg_h","mcwgt*(1)","goffnorm");
  // chain1->Draw("higgs.Pt() >> sig_h","mcwgt*(1)","goffnorm");

//   chain1->Draw("(tightMvaBased_leptons[0].miniIso*tightMvaBased_leptons[0].sip3D/tightMvaBased_leptons[0].jetPtRel)
// +(tightMvaBased_leptons[1].miniIso*tightMvaBased_leptons[1].sip3D/tightMvaBased_leptons[1].jetPtRel)
// +(tightMvaBased_leptons[2].miniIso*tightMvaBased_leptons[2].sip3D/tightMvaBased_leptons[2].jetPtRel)
//  >> sig_h","mcwgt*(1)","goffnorm");
  
//   chain2->Draw("(tightMvaBased_leptons[0].miniIso*tightMvaBased_leptons[0].sip3D/tightMvaBased_leptons[0].jetPtRel)
// +(tightMvaBased_leptons[1].miniIso*tightMvaBased_leptons[1].sip3D/tightMvaBased_leptons[1].jetPtRel)
// +(tightMvaBased_leptons[2].miniIso*tightMvaBased_leptons[2].sip3D/tightMvaBased_leptons[2].jetPtRel)
//  >> bkg_h","mcwgt*(1)","goffnorm");

  // chain1->Draw("(tightMvaBased_leptons[0].miniIso*tightMvaBased_leptons[0].sip3D/tightMvaBased_leptons[0].jetPtRel)+(tightMvaBased_leptons[1].miniIso*tightMvaBased_leptons[1].sip3D/tightMvaBased_leptons[1].jetPtRel)>> sig_h","mcwgt*(1)","goffnorm");
  // chain2->Draw("(tightMvaBased_leptons[0].miniIso*tightMvaBased_leptons[0].sip3D/tightMvaBased_leptons[0].jetPtRel)+(tightMvaBased_leptons[1].miniIso*tightMvaBased_leptons[1].sip3D/tightMvaBased_leptons[1].jetPtRel)>> bkg_h","mcwgt*(1)","goffnorm");
  
  

  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  //  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("can", "can");
  can1->SetGrid();

  sig_h->SetTitle("reco score - 2lss selection");
  //sig_h->SetTitle("Higgs pt - 2lss selection");
  // sig_h->GetXaxis()->SetRangeUser(0.,1.4);
  sig_h->GetXaxis()->SetTitle("bdt score");
  //  sig_h->GetXaxis()->SetTitle("mass [GeV]");
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
  can1->SaveAs("roc.png");  

}


