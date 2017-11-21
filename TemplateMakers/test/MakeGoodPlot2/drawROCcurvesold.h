void MakeGoodPlot::draw_ROC_curves()
{
	load_sample(1);
	
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
	
	TGraph *thisWP[10];
        
        int bins = 500;
        
//         sample_hist_shared[0] = new TH1F("eleMVA","eleMVA sig",bins,-1,1);
//         sample_hist_shared[1] = new TH1F("eleMVA","eleMVA bkd",bins,-1,1);
//         sample_hist_shared[2] = new TH1F("lepMVA","lepMVA sig",bins,-1,1);
//         sample_hist_shared[3] = new TH1F("lepMVA","lepMVA bkd",bins,-1,1);
//                 
//         
//         sample_hist_shared[4] = new TH1F("WPtight","WPtight sig",2,0,2);
//         sample_hist_shared[5] = new TH1F("WPtight","WPtight bkd",2,0,2);
//         sample_hist_shared[6] = new TH1F("WPmedium","WPmedium sig",2,0,2);
//         sample_hist_shared[7] = new TH1F("WPmedium","WPmedium bkd",2,0,2);
//         sample_hist_shared[8] = new TH1F("WPloose","WPloose sig",2,0,2);
//         sample_hist_shared[9] = new TH1F("WPloose","WPloose bkd",2,0,2);        
        
        
        sample_hist_shared[0] = new TH1F("eleMVA sig1","eleMVA sig1",bins,-1,1);
        sample_hist_shared[1] = new TH1F("eleMVA sig2","eleMVA sig2",bins,-1,1);
        sample_hist_shared[2] = new TH1F("eleMVA sig3","eleMVA sig3",bins,-1,1);

        sample_hist_shared[3] = new TH1F("lepMVA sig1","lepMVA sig1",bins,-1,1);    // -1,1 // -10,1.1
        sample_hist_shared[4] = new TH1F("lepMVA sig2","lepMVA sig2",bins,-1,1);
        sample_hist_shared[5] = new TH1F("lepMVA sig3","lepMVA sig3",bins,-1,1);

        sample_hist_shared[6] = new TH1F("eleMVA bkd1","eleMVA bkd1",bins,-1,1);
        sample_hist_shared[7] = new TH1F("eleMVA bkd2","eleMVA bkd2",bins,-1,1);
        sample_hist_shared[8] = new TH1F("eleMVA bkd3","eleMVA bkd3",bins,-1,1);

        sample_hist_shared[9] = new TH1F("lepMVA bkd1","lepMVA bkd1",bins,-1,1);
        sample_hist_shared[10] = new TH1F("lepMVA bkd2","lepMVA bkd2",bins,-1,1);
        sample_hist_shared[11] = new TH1F("lepMVA bkd3","lepMVA bkd3",bins,-1,1);
        
        sample_hist_shared[12] = new TH1F("sigmaIeatIeta var1 sig","",100,0,1);  //0.04
        sample_hist_shared[13] = new TH1F("sigmaIeatIeta var2 sig","",100,0,1);  //0.04
        sample_hist_shared[14] = new TH1F("sigmaIeatIeta var3 sig","",100,0,1);  //0.04
        sample_hist_shared[15] = new TH1F("sigmaIeatIeta var1 bkd","",100,0,1);  //0.04                                            
        sample_hist_shared[16] = new TH1F("sigmaIeatIeta var2 bkd","",100,0,1);  //0.04
        sample_hist_shared[17] = new TH1F("sigmaIeatIeta var3 bkd","",100,0,1);  //0.04
        
        
        TH1F *dummy_hist;                           // should really just make an overloaded function or something
        get_hist_of_simple_variable(dummy_hist,1); // sample_hist_shared[] is filled in here
        
//         get_roc_curve(sample_hist_shared[0], sample_hist_shared[1], 0);
//         get_roc_curve(sample_hist_shared[2], sample_hist_shared[3], 1);
        
        cout << "eleMVA (HZZ): pt<20" << endl;
        get_roc_curve(sample_hist_shared[0], sample_hist_shared[6], 0);
        cout << "eleMVA (HZZ): 20<pt<35" << endl;
        get_roc_curve(sample_hist_shared[1], sample_hist_shared[7], 1);
        cout << "eleMVA (HZZ): pt>35" << endl;
        get_roc_curve(sample_hist_shared[2], sample_hist_shared[8], 2);
        cout << "eleMVA (GP): pt<20" << endl;
        get_roc_curve(sample_hist_shared[3], sample_hist_shared[9], 3);
        cout << "eleMVA (GP): 20<pt<35" << endl;
        get_roc_curve(sample_hist_shared[4], sample_hist_shared[10], 4);
        cout << "eleMVA (GP): pt>35" << endl;
        get_roc_curve(sample_hist_shared[5], sample_hist_shared[11], 5);
        
        
        
        
//         double effsig_POG_WPtight[1];
//         double effbkd_POG_WPtight[1];
//         effsig_POG_WPtight[0] = sample_hist_shared[4]->GetBinContent(2) / sample_hist_shared[4]->Integral();
//         effbkd_POG_WPtight[0] = sample_hist_shared[5]->GetBinContent(1) / sample_hist_shared[5]->Integral();
//         
//         double effsig_POG_WPmedium[1];
//         double effbkd_POG_WPmedium[1];
//         effsig_POG_WPmedium[0] = sample_hist_shared[6]->GetBinContent(2) / sample_hist_shared[6]->Integral();
//         effbkd_POG_WPmedium[0] = sample_hist_shared[7]->GetBinContent(1) / sample_hist_shared[7]->Integral();
//         
//         double effsig_POG_WPloose[1];
//         double effbkd_POG_WPloose[1];
//         effsig_POG_WPloose[0] = sample_hist_shared[8]->GetBinContent(2) / sample_hist_shared[8]->Integral();
//         effbkd_POG_WPloose[0] = sample_hist_shared[9]->GetBinContent(1) / sample_hist_shared[9]->Integral();
//         
//         thisWP[0]= new TGraph(1,effsig_POG_WPtight,effbkd_POG_WPtight);
//         thisWP[1]= new TGraph(1,effsig_POG_WPmedium,effbkd_POG_WPmedium);
//         thisWP[2]= new TGraph(1,effsig_POG_WPloose,effbkd_POG_WPloose);
        
	roc_curve[2]->SetTitle("");
	roc_curve[2]->GetXaxis()->SetTitle("Signal Eff");
	roc_curve[2]->GetXaxis()->SetTitleColor(kBlack);
	roc_curve[2]->GetYaxis()->SetTitle("Bkg Rejection");
	roc_curve[2]->GetYaxis()->SetTitleColor(kBlack);    
	roc_curve[2]->GetYaxis()->SetRangeUser(0.9,1.05);
        roc_curve[2]->GetXaxis()->SetRangeUser(0.,1.1);

        roc_curve[0]->SetLineColor(kRed);
	roc_curve[0]->SetLineWidth(2);                                               
        roc_curve[1]->SetLineColor(kGreen);
        roc_curve[1]->SetLineWidth(2);
        roc_curve[2]->SetLineColor(kAzure+1);
	roc_curve[2]->SetLineWidth(2);                                               
        roc_curve[3]->SetLineColor(kRed+2);
        roc_curve[3]->SetLineWidth(2);
        roc_curve[4]->SetLineColor(kGreen+1);
	roc_curve[4]->SetLineWidth(2);                                                       
        roc_curve[5]->SetLineColor(kAzure);
        roc_curve[5]->SetLineWidth(2);

        
                
//         thisWP[0]->SetMarkerStyle(8);
//         thisWP[0]->SetMarkerColor(2);
//         thisWP[1]->SetMarkerStyle(8);
//         thisWP[1]->SetMarkerColor(3);
//         thisWP[2]->SetMarkerStyle(8);
//         thisWP[2]->SetMarkerColor(7);


// 	leg->AddEntry(roc_curve[1],"lepMVA","L");
// 	leg->AddEntry(roc_curve[0],"eleMVA","L");
//         leg->AddEntry(thisWP[2],"loose cut-based ID","P");
//         leg->AddEntry(thisWP[1],"medium cut-based ID","P");        
//         leg->AddEntry(thisWP[0],"tight cut-based ID","P");
	
//         //leg->AddEntry(roc_curve[0],"eleMVA (HZZ): pt<20","L");
//         leg->AddEntry(roc_curve[0],"POG cut on eleMVA (HZZ): pt<20","P");
//         //leg->AddEntry(roc_curve[3],"lepMVA: pt<20" ,"L");
//         leg->AddEntry(roc_curve[3],"eleMVA (HZZ): pt<20" ,"L");
//         //leg->AddEntry(roc_curve[1],"eleMVA (HZZ): 20<pt<35","L");
//         leg->AddEntry(roc_curve[1],"POG cut on eleMVA (HZZ): 20<pt<35","P");
//         //leg->AddEntry(roc_curve[4],"lepMVA: 20<pt<35","L");
//         leg->AddEntry(roc_curve[4],"eleMVA (HZZ): 20<pt<35","L");
//         //leg->AddEntry(roc_curve[2],"eleMVA (HZZ): pt>35" ,"L");  
//         leg->AddEntry(roc_curve[2],"POG cut on eleMVA (HZZ): pt>35" ,"P");                    
//         //leg->AddEntry(roc_curve[5],"lepMVA: pt>35","L");
//         leg->AddEntry(roc_curve[5],"eleMVA (HZZ): pt>35","L");
        
        leg->AddEntry(roc_curve[2],"POG cut on eleMVA (GP)" ,"P");
        leg->AddEntry(roc_curve[5],"eleMVA (GP)","L");
        
        TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660);
	can1->SetGridx();
	can1->SetGridy();
        roc_curve[0]->SetMarkerStyle(8);
        roc_curve[0]->SetMarkerColor(kRed);
        roc_curve[1]->SetMarkerStyle(8);
        roc_curve[1]->SetMarkerColor(kGreen);
        roc_curve[2]->SetMarkerStyle(8);   
        roc_curve[2]->SetMarkerColor(kAzure+1);
        //roc_curve[0]->Draw("AP");
        //roc_curve[1]->Draw("P");
        roc_curve[2]->Draw("AP");
        //roc_curve[3]->Draw("C");
        //roc_curve[4]->Draw("C");
        roc_curve[5]->Draw("C");


//         thisWP[0]->Draw("P");
//         thisWP[1]->Draw("P");
//         thisWP[2]->Draw("P");

        sample_hist_shared[12]->SetLineColor(kRed);
        sample_hist_shared[12]->SetLineWidth(2);       
        sample_hist_shared[13]->SetLineColor(kGreen);
        sample_hist_shared[13]->SetLineWidth(2);
        sample_hist_shared[14]->SetLineColor(kAzure+1);
        sample_hist_shared[14]->SetLineWidth(2);       
        sample_hist_shared[15]->SetLineColor(kRed+2);
        sample_hist_shared[15]->SetLineWidth(2);
        sample_hist_shared[16]->SetLineColor(kGreen+1);
        sample_hist_shared[16]->SetLineWidth(2);       
        sample_hist_shared[17]->SetLineColor(kAzure);
        sample_hist_shared[17]->SetLineWidth(2);

//         leg->AddEntry(sample_hist_shared[12],"prompt: pt<20","L");             // sigma IetaIeta (prompt): pt<20","L");      
//         leg->AddEntry(sample_hist_shared[15],"nonprompt: pt<20" ,"L");         // sigma IetaIeta (nonprompt): pt<20" ,"L");  
//         leg->AddEntry(sample_hist_shared[13],"prompt: 20<pt<35","L");          // sigma IetaIeta (prompt): 20<pt<35","L");   
//         leg->AddEntry(sample_hist_shared[16],"nonprompt: 20<pt<35","L");       // sigma IetaIeta (nonprompt): 20<pt<35","L");
//         leg->AddEntry(sample_hist_shared[14],"prompt: pt>35" ,"L");            // sigma IetaIeta (prompt): pt>35" ,"L");                
//         leg->AddEntry(sample_hist_shared[17],"nonprompt: pt>35","L");          // sigma IetaIeta (nonprompt): pt>35","L");   
// 
//         sample_hist_shared[12]->DrawNormalized("hist");
//         sample_hist_shared[13]->DrawNormalized("hist,same");
//         sample_hist_shared[14]->DrawNormalized("hist,same");
//         sample_hist_shared[15]->DrawNormalized("hist,same");
//         sample_hist_shared[16]->DrawNormalized("hist,same");
//         sample_hist_shared[17]->DrawNormalized("hist,same");


        
	leg->Draw();        
        
        

}

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
