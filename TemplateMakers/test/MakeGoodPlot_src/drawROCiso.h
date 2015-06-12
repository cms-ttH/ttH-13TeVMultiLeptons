void MakeGoodPlot::draw_ROC_iso(std::vector<int> samps)
{
  int numsamples = samps.size();
  //  load_samples(samps);
  
  ch[1]->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/multileptree.root");

  int NbinsX = 1600;
  int Xmin = 0;
  int Xmax = 13;

  TH1F *promptEle_relIso_hist = new TH1F("promptEle_relIso","",NbinsX,Xmin,Xmax);
  TH1F *nonPromptEle_relIso_hist = new TH1F("nonPromptEle_relIso","",NbinsX,Xmin,Xmax);
  TH1F *promptEle_miniIso_hist = new TH1F("promptEle_miniIso","",NbinsX,Xmin,Xmax);
  TH1F *nonPromptEle_miniIso_hist = new TH1F("nonPromptEle_miniIso","",NbinsX,Xmin,Xmax);
  
  TH1F *promptMu_relIso_hist = new TH1F("promptMu_relIso","",NbinsX,Xmin,Xmax);
  TH1F *nonPromptMu_relIso_hist = new TH1F("nonPromptMu_relIso","",NbinsX,Xmin,Xmax);
  TH1F *promptMu_miniIso_hist = new TH1F("promptMu_miniIso","",NbinsX,Xmin,Xmax);
  TH1F *nonPromptMu_miniIso_hist = new TH1F("nonPromptMu_miniIso","",NbinsX,Xmin,Xmax);
  
  for (int i=0; i<numsamples; i++)
    {  
      int samp_int = samps[i];
      ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
      ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
      ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);

      int samp_num_entries = ch[samp_int]->GetEntries();
      
      for (Int_t j=0; j<samp_num_entries; j++)
	{
	  ch[samp_int]->GetEntry(j);
	  
	  for (const auto & lepton : *preselected_leptons_intree)
	    {
	      if (lepton.genMotherPdgID != 9999)
		{
		  if (abs(lepton.genMotherPdgID) == 24 || abs(lepton.genMotherPdgID) == 23)
		    {
		      if (abs(lepton.pdgID) == 11)
			{ 
			  promptEle_relIso_hist->Fill(lepton.relIso);
			  promptEle_miniIso_hist->Fill(lepton.miniIso);
			  // promptEle_relIso_hist->Fill(log(lepton.relIso));
			  // promptEle_miniIso_hist->Fill(log(lepton.miniIso));
			}
		      else 
			{
			  promptMu_relIso_hist->Fill(lepton.relIso);
			  promptMu_miniIso_hist->Fill(lepton.miniIso);
			  // // promptMu_relIso_hist->Fill(log(lepton.relIso));
			  // promptMu_miniIso_hist->Fill(log(lepton.miniIso));
			}
		    }
		  else
		    {
		      if (abs(lepton.pdgID) == 11)
			{
			  nonPromptEle_relIso_hist->Fill(lepton.relIso);
			  nonPromptEle_miniIso_hist->Fill(lepton.miniIso);
			  //nonPromptEle_relIso_hist->Fill(log(lepton.relIso));
			  //nonPromptEle_miniIso_hist->Fill(log(lepton.miniIso));
			}
		      else
			{
			  nonPromptMu_relIso_hist->Fill(lepton.relIso);
			  nonPromptMu_miniIso_hist->Fill(lepton.miniIso);
			  //nonPromptMu_relIso_hist->Fill(log(lepton.relIso));
			  //nonPromptMu_miniIso_hist->Fill(log(lepton.miniIso));
			}
		    }
		}
	    }
	}
      //time to draw ROC curves...
    }
  
  //  TLegend* leg = new TLegend(0.11,0.91,0.89,0.99);
  TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);
  leg->SetFillColor(kWhite);
  //leg->SetLineColor(kWhite);
  leg->SetShadowColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  //  leg->SetNColumns(5);

  // TLegend* legg = new TLegend(0.11,0.91,0.89,0.99);
  // legg->SetFillColor(kWhite);
  // legg->SetLineColor(kWhite);
  // legg->SetShadowColor(kWhite);
  // legg->SetTextFont(42);
  // legg->SetTextSize(0.035);
  // legg->SetNColumns(5);
  // TCanvas *can0 = new TCanvas("can0","canvas0",150,10,990,660);
  // nonPromptEle_relIso_hist->SetLineColor(1);
  // promptEle_relIso_hist->SetLineColor(2);
  // legg->AddEntry(promptEle_relIso_hist,"prompt electrons");
  // legg->AddEntry(nonPromptEle_relIso_hist,"non-prompt electrons");
  // nonPromptEle_relIso_hist->Draw();
  // promptEle_relIso_hist->Draw("SAME");
  // legg->SetFillColor(0);
  // legg->Draw();

  TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660);
  can1->SetGridx();
  can1->SetGridy();

  get_roc_curve(promptEle_relIso_hist,nonPromptEle_relIso_hist,0);
  get_roc_curve(promptEle_miniIso_hist,nonPromptEle_miniIso_hist,1);
  get_roc_curve(promptMu_relIso_hist,nonPromptMu_relIso_hist,2);
  get_roc_curve(promptMu_miniIso_hist,nonPromptMu_miniIso_hist,3);

  // get_roc_curve(nonPromptEle_relIso_hist,promptEle_relIso_hist,0);
  // get_roc_curve(nonPromptEle_miniIso_hist,promptEle_miniIso_hist,1);
  // get_roc_curve(nonPromptMu_relIso_hist,promptMu_relIso_hist,2);
  // get_roc_curve(nonPromptMu_miniIso_hist,promptMu_miniIso_hist,3);

  roc_curve[0]->GetXaxis()->SetTitle("prompt Lepton efficiency");
  roc_curve[0]->GetXaxis()->SetTitleColor(kBlack);
  roc_curve[0]->GetYaxis()->SetTitle("non-prompt bkg rejection");
  roc_curve[0]->GetYaxis()->SetTitleColor(kBlack);

  roc_curve[1]->GetXaxis()->SetTitle("prompt Lepton efficiency");
  roc_curve[1]->GetXaxis()->SetTitleColor(kBlack);
  roc_curve[1]->GetYaxis()->SetTitle("non-prompt bkg rejection");
  roc_curve[1]->GetYaxis()->SetTitleColor(kBlack);

  roc_curve[2]->GetXaxis()->SetTitle("prompt Lepton efficiency");
  roc_curve[2]->GetXaxis()->SetTitleColor(kBlack);
  roc_curve[2]->GetYaxis()->SetTitle("non-prompt bkg rejection");
  roc_curve[2]->GetYaxis()->SetTitleColor(kBlack);

  roc_curve[3]->GetXaxis()->SetTitle("prompt Lepton efficiency");
  roc_curve[3]->GetXaxis()->SetTitleColor(kBlack);
  roc_curve[3]->GetYaxis()->SetTitle("non-prompt bkg rejection");
  roc_curve[3]->GetYaxis()->SetTitleColor(kBlack);
  
  roc_curve[0]->SetLineColor(1);
  roc_curve[1]->SetLineColor(2);
  roc_curve[2]->SetLineColor(3);
  roc_curve[3]->SetLineColor(4);

  roc_curve[0]->SetTitle("");
  roc_curve[1]->SetTitle("");
  roc_curve[2]->SetTitle("");
  roc_curve[3]->SetTitle("");

  roc_curve[0]->SetLineWidth(2);
  roc_curve[1]->SetLineWidth(2);
  roc_curve[2]->SetLineWidth(2);
  roc_curve[3]->SetLineWidth(2);

  leg->AddEntry(roc_curve[0],"ele relIso","l");
  leg->AddEntry(roc_curve[1],"ele miniIso","l");
  leg->AddEntry(roc_curve[2],"mu relIso","l");
  leg->AddEntry(roc_curve[3],"mu miniIso","l");

  roc_curve[0]->Draw("AL");
  roc_curve[1]->Draw("L");
  roc_curve[2]->Draw("L");
  roc_curve[3]->Draw("L");
  
  leg->SetFillColor(0);
  leg->Draw();


}
