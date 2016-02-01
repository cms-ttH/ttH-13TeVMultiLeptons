void MakeGoodPlot::get_roc_curve(TH1F *sig, TH1F *bkgd, int roc_curve_index) //int &npts, double (&effS)[500], double (&bckR)[500])
{
		
	int npts = 0;

	TH1F *intHist1 = (TH1F*)sig->Clone();
	TH1F *InvIntHist1 = (TH1F*)sig->Clone();
	TH1F *hist1N = (TH1F*)sig->Clone();

	TH1F *intHist2 = (TH1F*)bkgd->Clone();
	TH1F *InvIntHist2 = (TH1F*)bkgd->Clone();
	TH1F *hist2N = (TH1F*)bkgd->Clone();
		
	intHist1->Scale(1./intHist1->Integral());
	InvIntHist1->Scale(1./InvIntHist1->Integral());
	hist1N->Scale(1./hist1N->Integral());

	intHist2->Scale(1./intHist2->Integral());
	InvIntHist2->Scale(1./InvIntHist2->Integral());
	hist2N->Scale(1./hist2N->Integral());

	intHist1->Reset();
	intHist1->SetNameTitle("intHist1","Integral");

	InvIntHist1->Reset();
	InvIntHist1->SetNameTitle("InvIntHist1","InvIntegral");
  
	int size = hist1N->GetNbinsX()+1;
	
	double effS[size];
	double bckR[size];
	// double effS[500];
	// double bckR[500];

	// Now Loop over the histogram and do bin by bin.
	float intval = 0.0;
	for(int i=0; i<(hist1N->GetNbinsX())+1; i++)
	{
		intval = intval+(hist1N->GetBinContent(i));
		//if(prtLvl >= 2) printf(" Bin %i Int %f \n",i,intval);
		intHist1->SetBinContent(i,intval);	    
		InvIntHist1->SetBinContent(i,1.-intval);
		effS[i] = 1.0 - intval;
		std::cout << "sig interval: " << effS[i] << std::endl;
	  	//effS[i] = intval;
	  	npts++;
	}

	intHist2->Reset();
	intHist2->SetNameTitle("intHist2","Integral");
	
	InvIntHist2->Reset();
	InvIntHist2->SetNameTitle("InvIntHist2","InvIntegral");


	// Now Loop over the histogram and do bin by bin.
	intval = 0.0;
	for(int j=0; j<(hist2N->GetNbinsX())+1; j++)
	{
		intval = intval+(hist2N->GetBinContent(j));
		//if(prtLvl >= 2) printf(" Bin %i Int %f \n",j,intval);
		intHist2->SetBinContent(j,intval);
		InvIntHist2->SetBinContent(j,1.-intval);	
		bckR[j] = intval;    
		std::cout << "bckg interval: " << intval << std::endl;
		//bckR[j] = 1.0 - intval;    
	}
	
	roc_curve[roc_curve_index] = new TGraph(npts,effS,bckR);  	// <-- usual plot
	//	roc_curve[roc_curve_index] = new TGraph(npts,bckR,effS);  	// <-- for use with "->Eval(..." at a given background rejection

}


void MakeGoodPlot::compareplots(std::vector<int> samps, std::vector<TString> tempfiles)
{
  
  // compares multiple hists that should already be saved to some temp files //
  gROOT->SetBatch(kTRUE); // suppress display of the canvas
  vector<TFile*> files;
  
  for (int itempfile=0; itempfile<tempfiles.size(); itempfile++)
  {
    files.push_back(new TFile(tempfiles[itempfile]));   
  }


  vector<TString> names;
  
  for (int iName=0; iName<samps.size(); iName++)
  {
    TString iNametemp = sample_names[samps[iName]];
    names.push_back(iNametemp);
  }

  TFile *vergleich = new TFile("comparison_output.root","RECREATE");


  // no statistics box
  gStyle->SetOptStat(0);

  //TH1::SetDefaultSumw2();

  // Main program part
  TIter nextkey(files.at(0)->GetListOfKeys());
  TKey *key;
  bool first=true;
  TCanvas* c = new TCanvas();
  c->Print("comparisonPlots.pdf[");

  // Save also as pictures
  int pictureNumber = 0;

  int run = 0;
  
  while ( (key = (TKey*)nextkey()) )
  {
    pictureNumber++;
    TString pictureName = TString::Format("%d.png",pictureNumber);

    vector<TH1F*> histos;
    histos.push_back((TH1F*)key->ReadObj());
    histos[0]->SetName(key->GetName());
    
    for(size_t i=1;i<files.size();i++)
    {
      histos.push_back((TH1F*)files.at(i)->Get(histos.at(0)->GetName()));
	histos[i]->SetName(key->GetName());
    }
    
    c->SetName(key->GetName());
		       
    for(size_t i=0;i<histos.size();i++)
    {
      if(i == 0){
	histos.at(i)->SetLineColor(kBlack);
      }
      if(i == 1){
	histos.at(i)->SetLineColor(kRed);
      }
      if(i == 2){
	histos.at(i)->SetLineColor(kBlue);
      }
      if(i == 3){
	histos.at(i)->SetLineColor(kGreen+2);
      }
      if(i == 4){
	histos.at(i)->SetLineColor(kMagenta-7);
      }
      if(i == 5){
	histos.at(i)->SetLineColor(kOrange+7);
      }
    }
    
    for(size_t i=0;i<histos.size();i++)
    {
      //histos.at(i)->Sumw2();
      if ( strncmp (histos.at(i)->GetName(), "Match_ttH_SS_Bqq_eff",23) !=0)
	{
	  histos.at(i)->Scale(1./histos.at(i)->Integral(),"width");
	}
    }

    // Set axis title
    histos.at(0)->GetYaxis()->SetTitle("Normalized units"); 
    if ( strncmp (histos.at(0)->GetName(), "Match_ttH_SS_Bqq_eff",23) ==0) histos.at(0)->GetYaxis()->SetTitle("mis-tag efficiency"); 
    std::string const histogramName = histos.at(0)->GetName();
    histos.at(0)->GetXaxis()->SetLabelSize(0.04);
    histos.at(0)->GetXaxis()->SetLabelOffset(0.006);
    histos.at(0)->GetYaxis()->SetLabelSize(0.04);
    histos.at(0)->GetYaxis()->SetLabelOffset(0.006);
    histos.at(0)->GetXaxis()->SetTitleSize(0.04);
    histos.at(0)->GetXaxis()->SetTitleOffset(1.1); //1.1
    histos.at(0)->GetYaxis()->SetTitleSize(0.04);
    histos.at(0)->GetYaxis()->SetTitleOffset(1.3); //1.08


    // c->SetName(histos.at(0)->GetName())
    //histos.at(0)->GetXaxis()->SetTitle(histos.at(0)->GetName());
    //histos.at(0)->GetXaxis()->SetTitle(histos.at(0)->GetXaxis()->GetTitle());

    run = run+1;
    if(run == (3*8))
    {
        run = 0;
    }
    // If only two histograms per plot make a ratio plot
    if(histos.size() == 0)
    {

        //create main pad  

        TPad *mainPad = new TPad("","",0.0,0.3,1.0,1.0);
        mainPad->SetNumber(1);
        mainPad->SetBottomMargin(0.0);
        mainPad->SetRightMargin(0.04);
        mainPad->SetLeftMargin(0.13);
        mainPad->SetGridx(1);
        mainPad->SetGridy(1);
        mainPad->SetLogy(1);
        mainPad->Draw();

        //create ratio pad                                                                                                                                                           
        TPad *ratioPad = new TPad("","",0.0,0.0,1.0,0.3);
        ratioPad->SetTopMargin(0.0);
        ratioPad->SetBottomMargin(0.4);
        ratioPad->SetLeftMargin(0.13);                                                                                                                                             
        ratioPad->SetRightMargin(0.04);
        gStyle->SetOptTitle(0);
        ratioPad->SetFillColor(0);
        ratioPad->SetNumber(2);
        ratioPad->SetGridy();                                                                                                                                                      
        ratioPad->Draw();

        // Draw both histograms first
        c->cd(1);
        //c->mainPad()->SetLogy(1);  // <<<<------- set log scale
        histos.at(0)->Draw("histo E");
        histos.at(1)->Draw("histo same E");

        // Show legend and statistical tests in first pad
        for(size_t i=0;i<histos.size()-1;i=i+2)
        {

          //double ksresult = histos.at(i)->KolmogorovTest(histos.at(i+1));
          double ksresult = 1.0;
          ksresult=floor(ksresult*1000+0.5)/1000;
          //double chi2result =histos.at(i)->Chi2Test(histos.at(i+1),"WW");
          double chi2result = 1.0;
          chi2result=floor(chi2result*1000+0.5)/1000;

          stringstream ss;
          ss << "     KS: " <<std::setprecision(3) << ksresult << " chi2: " <<std::setprecision(3) << chi2result; // << " Private Work"; 
          //const char * notmych = & ss.str().c_str();
          TLatex * ks = new TLatex(0.1, 0.9-0.03*i, ss.str().c_str());
          ks->SetTextColor(histos.at(i)->GetLineColor());
          ks->SetNDC();
          ks->Draw("");      

        }

        TLegend* l = new TLegend(0.55,0.9,0.69,0.99);
        // Options for legend
        l->SetBorderSize(0);
        l->SetLineStyle(0);
        l->SetTextSize(0.049);
        l->SetFillStyle(0);
        for(size_t i=0;i<names.size();i++)
        {
          l->AddEntry(histos.at(i),names.at(i),"L");
        }
        l->Draw("same");

        // Clone histograms and draw ratio plot
        c->cd(2);
         TH1F* ratioHisto = (TH1F*)histos.at(0)->Clone();
        ratioHisto->Add(histos.at(1),-1);
        ratioHisto->Divide(histos.at(1));
        ratioHisto->SetLineColor(kBlue);
        ratioHisto->SetStats(false);
        ratioHisto->GetYaxis()->SetTitle("Ratio #frac{new-old}{old}");
        // Same Size like in histogram
        ratioHisto->SetLabelSize(histos.at(0)->GetLabelSize() * 0.7 / 0.3);
        ratioHisto->SetTitleOffset((histos.at(0)->GetTitleOffset("Y") * 0.3 / 0.7), "Y");
        ratioHisto->SetTitleSize((histos.at(0)->GetTitleSize("Y") * 0.7 / 0.3), "Y");
        ratioHisto->SetTitleOffset((histos.at(0)->GetTitleOffset("X")), "X");
        ratioHisto->SetTitleSize((histos.at(0)->GetTitleSize("X") * 0.7 / 0.3), "X");
        // Use nicer range
        ratioHisto->GetYaxis()->SetRangeUser(-1.5, 1.5);
        ratioHisto->GetYaxis()->SetNdivisions(503);
        ratioHisto->GetYaxis()->SetLabelSize(0.06 * 0.7 / 0.3);
        ratioHisto->Draw();
    }
    else
    {

      if ( strncmp (histos.at(0)->GetName(), "Match_ttH_SS_Bqq_eff",23) ==0)
	{
	  histos.at(0)->SetMaximum(1.1);  
	  histos.at(0)->SetMinimum(0);
	  histos.at(0)->Draw();
	}
      else histos.at(0)->Draw("histo");
      //      histos.at(0)->Draw("histo");

        for(size_t i=0;i<histos.size();i++)
        {
          if ( strncmp (histos.at(i)->GetName(), "Match_ttH_SS_Bqq_eff",23) ==0) histos.at(i)->Draw("same");
          else histos.at(i)->Draw("histo same");
          //histos.at(i)->Draw("histo same");
        }


        for(size_t i=0;i<histos.size()-1;i=i+2)
        {

          //double ksresult = histos.at(i)->KolmogorovTest(histos.at(i+1));
          double ksresult = 1.0;
          ksresult=floor(ksresult*1000+0.5)/1000;
          //double chi2result =histos.at(i)->Chi2Test(histos.at(i+1),"WW");
          double chi2result = 1.0;
          chi2result=floor(chi2result*1000+0.5)/1000;
          
          stringstream ss;
          ss << "KS: " <<std::setprecision(3) << ksresult << " chi2: " <<std::setprecision(3) << chi2result; 
          //const char notmych = ss.str().c_str();
          TText * ks = new TText(0.1, 0.9-0.03*i, ss.str().c_str());
          ks->SetTextColor(histos.at(i)->GetLineColor());
          ks->SetNDC();
          //ks->Draw("");      

        }
	
	//FOM calculation
	//	for(size_t i=0;i<histos.size();i++) std::cout << "hist name: " << histos.at(i)->GetName() << std::endl;

        TLegend* l = new TLegend(0.11,0.91,0.89,0.99); // 0.11,0.75,0.89,0.89
        l->SetBorderSize(0);
        l->SetLineStyle(0);
        //    l->SetTextSize(0.039);
        l->SetFillStyle(0);
        l->SetTextFont(42);
        l->SetTextSize(0.04);
        l->SetNColumns((files.size()+1));
	TString legend_text;
        for(size_t i=0;i<names.size();i++)
        {
	  if ( strncmp (histos.at(i)->GetName(), "Match_ttH_SS_Bqq_FOM",23) ==0)
	    {
	      l->SetTextSize(0.03);
	      float FOM = histos.at(i)->GetBinContent(2) + histos.at(i)->GetBinContent(3)*2. + histos.at(i)->GetBinContent(4)*3.;
	      legend_text = names.at(i) + "   FOM: " + std::to_string(FOM);
	    }
	  else
	    {
	      l->SetTextSize(0.04);
	      legend_text = names.at(i);
	    }
	  
          l->AddEntry(histos.at(i),legend_text,"L");
        }
        l->Draw("same");
    }
    
    vergleich->WriteTObject(c);
    c->Print("comparisonPlots.pdf");
    c->SaveAs(pictureName);
 
  }
 
  c->Print("comparisonPlots.pdf]");
 }

template <typename almostTLVtype> TLorentzVector MakeGoodPlot::makeTLV( almostTLVtype thing )
{
    TLorentzVector thereturnedTLV;
    thereturnedTLV.SetPxPyPzE(thing.Px(), thing.Py(), thing.Pz(), thing.E());
    return thereturnedTLV;
}

TString MakeGoodPlot::int2ss(int theint)
{
	std::ostringstream thess;
	thess << theint;
	TString string_out = thess.str();
	return string_out;
}
std::string MakeGoodPlot::TString2string(TString the_abomination)
{
	std::ostringstream thess;
	thess << the_abomination;
	std::string string_out = thess.str();
	return string_out;
}
