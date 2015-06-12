
void MakeGoodPlot::draw_ROC_curves(std::vector<int> samps, int which_one_is_the_signal_sample)
{
	
	
	int numsamples = samps.size();
	
	TH1F *sample_hist[numsamples];
//	TGraph *roc_curve[10];
	
	load_samples(samps);
	
	//TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);  /// (0.3,0.77,0.7,0.88)
	//TLegend* leg = new TLegend(0.14,0.75,0.94,0.89); // Darren format
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.035);
	leg->SetNColumns(5);
	
	int sig_hist_index = 1;
	
	
	for (int i=0; i<numsamples; i++)
	{
		
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
		
		sample_hist[i] = new TH1F("BDT response, 5j4t " + sample_names[samp_int],"",100,-1.0,1.0);
		
		get_hist_of_tiered_MVA_response_for_one_sample_5j4t(sample_hist[i],samp_int);
		//get_hist_MVA_response_for_one_sample_643203(sample_hist[i],samp_int);
		
		if (samp_int==which_one_is_the_signal_sample) sig_hist_index = i;

	}
	
	int j = 0;
	
	TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660);
	can1->SetGridx();
	can1->SetGridy();
	
	for (int i=0; (/*(i!=sig_hist_index)&&*/(i<numsamples)); i++)
	{
		if (i==sig_hist_index) continue;
		
		cout << i << j << endl;
		
		int samp_int = samps[i];
		
		cout << "blah1" << endl;
		
//		double eff_S[500];
//		double bck_R[500];
//		int n_pts;
		
		cout << "blah2" << endl;
		
		get_roc_curve(sample_hist[sig_hist_index], sample_hist[i], j); // n_pts, eff_S, bck_R);
		
		cout << "blah3" << endl;
		
//		roc_curve[j] = new TGraph(n_pts,eff_S,bck_R);
		
		cout << "blah4" << endl;
		
		
		//roc_curve[j]->SetTitle(title);
		roc_curve[j]->GetXaxis()->SetTitle("Signal Eff");
		roc_curve[j]->GetXaxis()->SetTitleColor(kBlack);
		roc_curve[j]->GetYaxis()->SetTitle("Bkg Rejection");
		roc_curve[j]->GetYaxis()->SetTitleColor(kBlack);    
		
		if (samp_int<4) roc_curve[j]->SetLineColor(1+samp_int);
		if (samp_int>=4) roc_curve[j]->SetLineColor(2+samp_int);
		
		roc_curve[j]->SetTitle("");
		roc_curve[j]->SetLineWidth(2);
		leg->AddEntry(roc_curve[j],sample_names[samp_int],"l");

		
		

		if (j==0) roc_curve[j]->Draw("AC");
		if (j!=0) roc_curve[j]->Draw("C");
		
		j++;
		
		cout << j << endl;
	
	}
	
	leg->SetFillColor(0);
	leg->Draw();
	

}
