void MakeGoodPlot::draw_nice_stack_with_ratio(std::vector<int> samps, std::string mytitle, std::string mylabel)
{
	int numsamples = samps.size();
	TH1D *sample_hist[numsamples];	
	load_samples(samps);
	
	// title of plot (displayed below ratio plot)
	TString xaxis_title = "Gaussian Variable (4#sigma Separation), 6j4t";
	
        //TString xaxis_title = mytitle;
        
	// y-axis label (stack):
	
	// y-axis label (ratio):
	
	// range, bins (stack and ratio are same):
	double first_bin_low_edge = 0.;
	double last_bin_up_edge = 400.;
	int bins = 200;
		


	
	//Hack to get it plotted with ratio plot
	//TCanvas* myC = new TCanvas("myC_"+mylabel, "myC_"+mylabel, 600,700);
	TCanvas* myC = new TCanvas("myC_", "myC_", 600,700);
        gStyle->SetPadBorderMode(0);
	gStyle->SetFrameBorderMode(0);
	Float_t small = 1.e-5;
	myC->Divide(1,2,small,small);
	const float padding=1e-5; const float ydivide=0.3;
	myC->GetPad(1)->SetPad( padding, ydivide + padding , 1-padding, 1-padding);
	myC->GetPad(2)->SetPad( padding, padding, 1-padding, ydivide-padding);
	myC->GetPad(1)->SetLeftMargin(.11);
	myC->GetPad(2)->SetLeftMargin(.11);
	myC->GetPad(1)->SetRightMargin(.05);
	myC->GetPad(2)->SetRightMargin(.05);
	myC->GetPad(1)->SetBottomMargin(.3);
	myC->GetPad(2)->SetBottomMargin(.3);
	myC->GetPad(1)->Modified();
	myC->GetPad(2)->Modified();
	myC->cd(1);
	gPad->SetBottomMargin(small);
	gPad->Modified();	
	
	THStack *nice_stack = new THStack("stack1",";" + xaxis_title);
	TH1F *sum = new TH1F("sum bkgd","",bins,first_bin_low_edge,last_bin_up_edge);
	
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.028);
	leg->SetNColumns(3);
	
	int where_is_sig = -1;
	int where_is_data_mu = -1;
	int where_is_data_ele = -1;
	
	for (int i=0; i<numsamples; i++)
	{	
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
	
		// --------------

		sample_hist[i] = new TH1D(xaxis_title + " " + sample_names[samp_int],"",bins,first_bin_low_edge,last_bin_up_edge);
		get_hist_of_simple_variable(sample_hist[i],samp_int);
		// --------------
		

	
		float sample_evts = sample_hist[i]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();

		
		if (samp_int==0||samp_int==10)
		{
			sample_hist[i]->SetLineColor(1);
			sample_hist[i]->SetLineWidth(2);
			sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
			//if(samp_int==0) leg->AddEntry(sample_hist[i],sample_names[0] + " (" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
			sample_hist[i]->SetStats(0);
			sample_hist[i]->SetTitleSize(0);
			sample_hist[i]->Sumw2();
			if(samp_int==0) where_is_data_mu = i;
			if(samp_int==10) where_is_data_ele = i;
		}
		else
		{
			if (samp_int==1)
			{
				sample_hist[i]->SetLineColor(1+samp_int);
				sample_hist[i]->SetLineWidth(2);
				sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
				leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (15x" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
				sample_hist[i]->SetStats(0);
				sample_hist[i]->SetTitleSize(0);
				sample_hist[i]->Scale(15);
				where_is_sig = i;
			}
			else
			{
				if (samp_int<4) sample_hist[i]->SetFillColor(1+samp_int);		
				if (samp_int>=4) sample_hist[i]->SetFillColor(2+samp_int);

				sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
				//sample_hist[i]->SetLineWidth(2);
				leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (" + sample_evts_string + ")","F");  /// have ability to add # of evts per sample to legend... 
				//leg->AddEntry(sample_hist[i],sample_names[samp_int],"l");

				sample_hist[i]->SetStats(0);
				sample_hist[i]->SetTitleSize(0);

				nice_stack->Add(sample_hist[i]);
				sum->Add((TH1F*)sample_hist[i]);
			}
		}
	
	}
	
	
	double maxstack = nice_stack->GetMaximum();
	nice_stack->SetMaximum(1.25*maxstack);
	nice_stack->Draw();		
	
	if (where_is_sig>=0) sample_hist[where_is_sig]->Draw("same");
	if (where_is_data_mu>=0&&where_is_data_ele>=0)
	{
		sample_hist[where_is_data_mu]->Add(sample_hist[where_is_data_ele],1.0);
		float sample_evts = sample_hist[where_is_data_mu]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();
		leg->AddEntry(sample_hist[where_is_data_mu],("data (" + sample_evts_string + ")").c_str(),"LPE");
		sample_hist[where_is_data_mu]->Draw("esame");
	}

	leg->SetFillColor(0);
	leg->Draw("same");
	
	

	
	
	
	
}

void MakeGoodPlot::draw_nice_stack(std::vector<int> samps)
{
	int numsamples = samps.size();
	TH1D *sample_hist[numsamples];
	//TH1D sample_hist[numsamples];
	
	//cout << "before load" << endl;
	
	load_samples(samps);
	
	//cout << "after load" << endl;

	TString xaxis_title = "Gaussian Variable (4#sigma Separation), 6j4t";
	
	THStack *nice_stack = new THStack("stack1",";" + xaxis_title);
	TH1F *sum = new TH1F("BDT response, 6j4t, sum bkgd","",20,-1.0,1.0);
	
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.028);
	leg->SetNColumns(3);
	
	int where_is_sig = -1;
	int where_is_data_mu = -1;
	int where_is_data_ele = -1;
	
	for (int i=0; i<numsamples; i++)
	{	
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
	
		// --------------
		//sample_hist[i] = new TH1D("Gaussian Variable (2#sigma Separation)" + sample_names[samp_int],"",24,-4,8);
		sample_hist[i] = new TH1D("Gaussian Variable (2#sigma Separation)" + sample_names[samp_int],"",200,0,400);
		get_hist_of_simple_variable(sample_hist[i],samp_int);
		// --------------
		
		/*
		for (int sp=0; sp<33; sp++)
		{
			TString shiftpoint = int2ss(sp);
			sample_hist_shared[i][sp] = new TH1F("BDT response, 6j4t " + sample_names[samp_int] + " " + shiftpoint,"",20,-1.0,1.0);
		}
			
		
		//get_hist_of_tiered_MVA_response_for_one_sample_643900XX( samp_int, i );
		//sample_hist[i] = (TH1D*)sample_hist_shared[i][16]->Clone();
		
		sample_hist[i] = new TH1D("BDT response, 6j4t " + sample_names[samp_int],"",20,-1.0,1.0);
		get_hist_of_tiered_MVA_response_for_one_sample_6j4t(sample_hist[i],samp_int);
		*/
		
		// --------------
		
		
		//TString xaxis_title = "Sigma(pt)/Sigma(E)";
		//TString xaxis_title = "BDT Response, 6j4t";
	
		float sample_evts = sample_hist[i]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();

		
		if (samp_int==0||samp_int==10)
		{
			sample_hist[i]->SetLineColor(1);
			sample_hist[i]->SetLineWidth(2);
			sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
			//if(samp_int==0) leg->AddEntry(sample_hist[i],sample_names[0] + " (" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
			sample_hist[i]->SetStats(0);
			sample_hist[i]->SetTitleSize(0);
			sample_hist[i]->Sumw2();
			if(samp_int==0) where_is_data_mu = i;
			if(samp_int==10) where_is_data_ele = i;
		}
		else
		{
			if (samp_int==1)
			{
				sample_hist[i]->SetLineColor(1+samp_int);
				sample_hist[i]->SetLineWidth(2);
				sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
				leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (15x" + sample_evts_string + ")","L");  /// have ability to add # of evts per sample to legend... 
				sample_hist[i]->SetStats(0);
				sample_hist[i]->SetTitleSize(0);
				sample_hist[i]->Scale(15);
				where_is_sig = i;
			}
			else
			{
				if (samp_int<4) sample_hist[i]->SetLineColor(1+samp_int);		
				if (samp_int>=4) sample_hist[i]->SetLineColor(2+samp_int);

				sample_hist[i]->GetXaxis()->SetTitle(xaxis_title);
				//sample_hist[i]->SetLineWidth(2);
				leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (" + sample_evts_string + ")","F");  /// have ability to add # of evts per sample to legend... 
				//leg->AddEntry(sample_hist[i],sample_names[samp_int],"l");

				sample_hist[i]->SetStats(0);
				sample_hist[i]->SetTitleSize(0);
				//if (!i) sample_hist[i]->DrawNormalized();
				//else sample_hist[i]->DrawNormalized("same");
				//if (!i) sample_hist[i]->Draw();
				//else sample_hist[i]->Draw("same");

				nice_stack->Add(sample_hist[i]);
				//sum->Add((TH1F*)sample_hist[i]);
			}
		}
	
	}
	
	
	double maxstack = nice_stack->GetMaximum();
	nice_stack->SetMaximum(1.25*maxstack);
	nice_stack->Draw();
	
		
	
	if (where_is_sig>=0) sample_hist[where_is_sig]->Draw("e2same");
	if (where_is_data_mu>=0&&where_is_data_ele>=0)
	{
		sample_hist[where_is_data_mu]->Add(sample_hist[where_is_data_ele],1.0);
		float sample_evts = sample_hist[where_is_data_mu]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();
		leg->AddEntry(sample_hist[where_is_data_mu],("data (" + sample_evts_string + ")").c_str(),"LPE");
		sample_hist[where_is_data_mu]->Draw("esame");
	}

	leg->SetFillColor(0);
	leg->Draw("same");
	
	// optional print stuff:
	//TH1F *thesighist = (TH1F*)sample_hist[where_is_sig]->Clone();
	//TH1F *thebackhist = (TH1F*)nice_stack->GetHistogram()->Clone();
	//get_roc_curve(thesighist, sum, 0);	
	//cout << "sig eff at 1% back eff: " << roc_curve[0]->Eval(0.99) << endl;
	//cout << "sig eff at 10% back eff: " << roc_curve[0]->Eval(0.90) << endl;
	//cout << "sig eff at 30% back eff: " << roc_curve[0]->Eval(0.70) << endl;
	
	//thesighist->Draw();
	//thebackhist->Draw("same");
	
	
}
