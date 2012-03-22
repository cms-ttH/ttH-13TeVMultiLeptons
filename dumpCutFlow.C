{

  //TFile * myFile = new TFile ("test_beans_v1_histo.root");
  //TFile * myFile = new TFile ("batchBEAN/merged/ttH_m120_merged.root");

  //TFile * myFile = new TFile ("batchBEAN/merged/ttbar_merged.root");


  //TFile * myFile = new TFile ("batchBEAN/merged/wjets_muonPt_ge27_merged.root");



  // TString targetFilename = "batchBEAN/merged/ttH_m120_muonPt_ge27_merged.root";
  // TString targetFilename = "batchBEAN/merged/ttbar_muonPt_ge27_merged.root";
  // TString targetFilename = "batchBEAN/merged/wjets_muonPt_ge27_merged.root";

  // TString targetFilename = "batchBEAN/merged/ttH_m120_btagComboLoose_v2_merged.root";
  // TString targetFilename = "batchBEAN/merged/ttbar_btagComboLoose_v2_merged.root";
  // TString targetFilename = "batchBEAN/merged/wjets_btagComboLoose_v2_merged.root";


  //TString targetFilename = "batchBEAN/ttH_m120_testDilep_v2/test_beans_v1_ttH_m120_testDilep_v2_job_44.root";
  TString targetFilename = "batchBEAN/merged/ttbar_dileptonStudy_fix_v2_merged.root";
  //TString targetFilename = "batchBEAN/merged/ttH_m120_dileptonStudy_fix_v2_merged.root";
  
  
  cout << "Using file name " << targetFilename << endl;
  
  TFile * myFile = new TFile (targetFilename);


  //TFile * myFile = new TFile ("batchBEAN/ttH_m120_testComboLoose/test_beans_v1_ttH_m120_testComboLoose_job_11.root");

  //TFile * myFile = new TFile ("batchBEAN/ttH_m120/test_beans_v1_ttH_m120_job_11.root");
  
  myFile->cd();


  TH1 * cutHist = (TH1*) gDirectory->Get("h_cutflow_unwgt")->Clone("myCutflow");

  TAxis * cutAxis = cutHist->GetXaxis();
  for (int iBin =1; iBin < cutHist->GetNbinsX()+1; iBin++){
    cout << "iBin " << iBin << " = " << cutAxis->GetBinLabel(iBin)
         << "   "
         << std::fixed         
         << std::setw(12)
         << cutHist->GetBinContent(iBin) << endl;
  }



}
