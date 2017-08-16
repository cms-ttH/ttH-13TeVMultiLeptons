
void MakeGoodPlot::draw_ROC_curves(std::vector<int> samps, int which_one_is_the_signal_sample)
{
	
	
	int numsamples = samps.size();
	
	TH1F *sample_hist[numsamples]; //[5]; //second one is different pt ranges
        TH1F *sample_hist2[numsamples]; //[5]; //second one is different pt ranges
//	TGraph *roc_curve[10];
	
        cout << "hey" << endl;
	load_samples(samps);
        cout << "hey1" << endl;
	
	//TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);  /// (0.3,0.77,0.7,0.88)
	TLegend* leg = new TLegend(0.12,0.12,0.3,0.4);  /// bottom left
        
	//TLegend* leg = new TLegend(0.14,0.75,0.94,0.89); // Darren format
	//TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.035);
	//leg->SetNColumns(5);
	
	int sig_hist_index = 1;
	
	TGraph *thislepmvaWP[10];
        
	for (int i=0; i<numsamples; i++)
	{
		
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
		
		sample_hist[i] = new TH1F("BDT response, ss2l+6j " + sample_names[samp_int],"",100,-1.0,1.0);
                sample_hist2[i] = new TH1F("cut, ss2l+6j " + sample_names[samp_int],"",1000,-700,10);
// 		sample_hist[i][1] = new TH1F("BDT response, ss2l+6j " + sample_names[samp_int]+" 1","",100,-1.0,1.0);
//                 sample_hist2[i][1] = new TH1F("cut, ss2l+6j " + sample_names[samp_int]+" 1","",1000,-700,10);
//                 sample_hist[i][2] = new TH1F("BDT response, ss2l+6j " + sample_names[samp_int]+" 2","",100,-1.0,1.0);
//                 sample_hist2[i][2] = new TH1F("cut, ss2l+6j " + sample_names[samp_int]+" 2","",1000,-700,10);
//                 sample_hist[i][3] = new TH1F("BDT response, ss2l+6j " + sample_names[samp_int]+" 3","",100,-1.0,1.0);
//                 sample_hist2[i][3] = new TH1F("cut, ss2l+6j " + sample_names[samp_int]+" 3","",1000,-700,10);
//                 sample_hist[i][4] = new TH1F("BDT response, ss2l+6j " + sample_names[samp_int]+" 4","",100,-1.0,1.0);
//                 sample_hist2[i][4] = new TH1F("cut, ss2l+6j " + sample_names[samp_int]+" 4","",1000,-700,10);
                
		//get_hist_of_tiered_MVA_response_for_one_sample_5j4t(sample_hist[i],samp_int);
		//get_hist_MVA_response_for_one_sample_643203(sample_hist[i],samp_int);
                
		get_hist_of_simple_variable(sample_hist[i],samp_int,sample_hist2[i]);                
                
		if (samp_int==which_one_is_the_signal_sample) sig_hist_index = i;

	}
	
	int j = 0;
	
	TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660);
	can1->SetGridx();
	can1->SetGridy();

        
	for (int i=0; (/*(i!=sig_hist_index)&&*/(i<numsamples)); i++)
	{
		if (i==sig_hist_index) continue;		
		
		int samp_int = samps[i];
		
		
//		double eff_S[500];
//		double bck_R[500];
//		int n_pts;
		
                
                double effsig_lepmvaWPtight[1];
                double effbkd_lepmvaWPtight[1];
		effsig_lepmvaWPtight[0] = sample_hist[sig_hist_index]->Integral(sample_hist[sig_hist_index]->FindBin(0.9),100) / sample_hist[sig_hist_index]->Integral();
                effbkd_lepmvaWPtight[0] = sample_hist[i]->Integral(1,sample_hist[i]->FindBin(0.9)) / sample_hist[i]->Integral();
		
                
                cout << effsig_lepmvaWPtight[0] << " " << effbkd_lepmvaWPtight[0] << endl;
                
                get_roc_curve(sample_hist[sig_hist_index], sample_hist[i], j); // n_pts, eff_S, bck_R);
                get_roc_curve(sample_hist2[sig_hist_index], sample_hist2[i], (j+25));
		
		
//		roc_curve[j] = new TGraph(n_pts,eff_S,bck_R);
		
                
                
                //TGraph thislepmvaWP(1,effsig_lepmvaWPtight,effbkd_lepmvaWPtight);		
		thislepmvaWP[j]= new TGraph(1,effsig_lepmvaWPtight,effbkd_lepmvaWPtight);
                
                
		//roc_curve[j]->SetTitle(title);
		roc_curve[j]->GetXaxis()->SetTitle("Signal Eff");
		roc_curve[j]->GetXaxis()->SetTitleColor(kBlack);
		roc_curve[j]->GetYaxis()->SetTitle("Bkg Rejection");
		roc_curve[j]->GetYaxis()->SetTitleColor(kBlack);    
		roc_curve[j]->GetYaxis()->SetRangeUser(0.8,1.05);
                
		//if (samp_int<4) roc_curve[j]->SetLineColor(1+samp_int-10);
		if (samp_int>=4) roc_curve[j]->SetLineColor(2*(j+1));
                thislepmvaWP[j]->SetMarkerStyle(8);
                thislepmvaWP[j]->SetMarkerColor(2*(j+1));
		
		roc_curve[j]->SetTitle("");
		roc_curve[j]->SetLineWidth(2);
		leg->AddEntry(roc_curve[j],sample_names[samp_int],"l");
		
                
		//roc_curve[j]->SetTitle(title);
		roc_curve[j+25]->GetXaxis()->SetTitle("Signal Eff");
		roc_curve[j+25]->GetXaxis()->SetTitleColor(kBlack);
		roc_curve[j+25]->GetYaxis()->SetTitle("Bkg Rejection");
		roc_curve[j+25]->GetYaxis()->SetTitleColor(kBlack);    
		
		//if (samp_int<4) roc_curve[j+25]->SetLineColor(1+samp_int);
		if (samp_int>=4) roc_curve[j+25]->SetLineColor(0);
		
                roc_curve[j+25]->SetMarkerStyle(8);
                roc_curve[j+25]->SetMarkerColor(2*(j+1)+1);
                
                
		roc_curve[j+25]->SetTitle("");
		roc_curve[j+25]->SetLineWidth(2);
                leg->AddEntry(thislepmvaWP[j],sample_names[samp_int]+" lepMVA tight WP","P");
		leg->AddEntry(roc_curve[j+25],sample_names[samp_int]+" POG tight ID","P");                
                
                		

		if (j==0) roc_curve[j]->Draw("AC");
		if (j!=0) roc_curve[j]->Draw("C");
                
                thislepmvaWP[j]->Draw("P");
                roc_curve[j+25]->Draw("P");
		
		j++;
		
		cout << j << endl;
	
	}
	
        
        
        
	leg->SetFillColor(0);
	leg->Draw();
	

}
