/////////////////////////////////////
////////////  public fns ////////////
//  (drawing-specific functions): ///



// get several quantities to compare from ntuples, and plot them using compareplots
void MakeGoodPlot::draw_several_comparisons(std::vector<int> samps)
{
        bool debug = false;
        
        std::vector<TString> tempfilenames;
        int numsamples = samps.size();		
	load_samples(samps);	
        const int numplots = 13;
        
        TH1D *sample_hist[numplots][numsamples];
        TString xaxis_title[numplots];
        
        double first_bin_low_edge[numplots];
	double last_bin_up_edge[numplots];
	int bins[numplots];
        
        //// define some parameters for the plots:
        
	// title of plot (displayed below ratio plot)
	xaxis_title[0] = "preselected lepton pt";		
	first_bin_low_edge[0] = 0.;
	last_bin_up_edge[0] = 400.;
	bins[0] = 100;       
        
        
        xaxis_title[1] = "leading lep pt";		
	first_bin_low_edge[1] = 0.;
	last_bin_up_edge[1] = 400.;
	bins[1] = 100;
        
        
        xaxis_title[2] = "2nd lep pt";		
	first_bin_low_edge[2] = 0.;
	last_bin_up_edge[2] = 300.;
	bins[2] = 75;

        
        
        xaxis_title[3] = "MET";		
	first_bin_low_edge[3] = 0.;
	last_bin_up_edge[3] = 400.;
	bins[3] = 100;
        
        
        xaxis_title[4] = "MET phi";		
	first_bin_low_edge[4] = -4.;
	last_bin_up_edge[4] = 4.;
	bins[4] = 100;
        
        
        xaxis_title[5] = "num Jets";		
	first_bin_low_edge[5] = 0.;
	last_bin_up_edge[5] = 20.;
	bins[5] = 20;
                
        
        xaxis_title[6] = "Jet Energy";		
	first_bin_low_edge[6] = 0.;
	last_bin_up_edge[6] = 1000.;
	bins[6] = 100;
        
        
        xaxis_title[7] = "Leading Jet Energy";		
	first_bin_low_edge[7] = 0.;
	last_bin_up_edge[7] = 1000.;
	bins[7] = 100;
        
        xaxis_title[8] = "2nd Jet Energy";		
	first_bin_low_edge[8] = 0.;
	last_bin_up_edge[8] = 1000.;
	bins[8] = 100;
        
        xaxis_title[9] = "Lepton phi";		
	first_bin_low_edge[9] = -4.;
	last_bin_up_edge[9] = 4.;
	bins[9] = 100;
                
        xaxis_title[10] = "Lepton eta";		
	first_bin_low_edge[10] = -3.;
	last_bin_up_edge[10] = 3.;
	bins[10] = 100;
        
        xaxis_title[11] = "Jet phi";		
	first_bin_low_edge[11] = -4.;
	last_bin_up_edge[11] = 4.;
	bins[11] = 100;
        
        
        xaxis_title[12] = "Jet eta";		
	first_bin_low_edge[12] = -3.;
	last_bin_up_edge[12] = 3.;
	bins[12] = 100;
        
        
        
        
        
// 	int where_is_sig = -1;
// 	int where_is_data_mu = -1;
// 	int where_is_data_ele = -1;
	
	
        for (int i=0; i<numsamples; i++)
	{	
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
	
		// --------------
                
                if (debug) cout << "hey1" << endl;
                
                int theentries = ch[samp_int]->GetEntries();
                cout << ch[samp_int]->GetEntries() << endl;
                
                tempfilenames.push_back("temp_"+int2ss(i)+".root");
	        TFile newtempfile("temp_"+int2ss(i)+".root","RECREATE");
                
                if (debug) cout << "hey2" << endl;
                
	        ch[samp_int]->SetBranchAddress("mcwgt", &mcwgt_intree);
                ch[samp_int]->SetBranchAddress("wgt", &wgt_intree);

                ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
                ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
                ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);

                ch[samp_int]->SetBranchAddress("looseMvaBased_leptons", &loose_leptons_intree);
                ch[samp_int]->SetBranchAddress("looseMvaBased_electrons", &loose_electrons_intree);
                ch[samp_int]->SetBranchAddress("looseMvaBased_muons", &loose_muons_intree);

                ch[samp_int]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
                ch[samp_int]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
                ch[samp_int]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);

                ch[samp_int]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
                ch[samp_int]->SetBranchAddress("met", &met_intree);
                
                ch[samp_int]->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);
                
                for (int j=0;j<numplots;j++)
                {
                    sample_hist[j][i] = new TH1D("hist_"+int2ss(j),";"+xaxis_title[j],bins[j],first_bin_low_edge[j],last_bin_up_edge[j]);
                    sample_hist[j][i]->Sumw2();
                }
                
                int countbefore = 0;
                int countafter = 0;
                
                if (debug) cout << "hey3" << endl;
                
                for (int j=0;j<100000;j++)
	        {
		
                    ch[samp_int]->GetEntry(j);
								
		            weight = wgt_intree;
                    
                    bool keepthisevent = true;
                    countbefore++;
                    
                    if (debug) cout << "hey4" << endl;
                    
                    // picks only H->non-bb for consistancy between samples:
                    if (debug) cout << (*pruned_genParticles_intree).size() << endl;
                    
                    for (unsigned int k=0;k<(*pruned_genParticles_intree).size();k++)
                    {
                        if (debug) cout << "hey41" << endl;
                        if ((*pruned_genParticles_intree)[k].pdgID==25)
                        {
                            if (debug) cout << "hey411" << endl;
                            if (debug) cout << (*pruned_genParticles_intree)[k].child0 << endl;
                            if (debug) cout << (*pruned_genParticles_intree)[k].child1 << endl;
                            
                            if ((*pruned_genParticles_intree)[k].child0<(*pruned_genParticles_intree).size())
                            {    
                                if (abs((*pruned_genParticles_intree)[(*pruned_genParticles_intree)[k].child0].pdgID)==5)
                                {
                                    keepthisevent = false;
                                    if (debug) cout << "hey4111" << endl;
                                }
                            }
                            
                            if ((*pruned_genParticles_intree)[k].child1<(*pruned_genParticles_intree).size())
                            {    
                                if (abs((*pruned_genParticles_intree)[(*pruned_genParticles_intree)[k].child1].pdgID)==5)
                                {
                                    keepthisevent = false;
                                    if (debug) cout << "hey4111" << endl;
                                }
                            }
                                                                                   
                        
                        }
                    }
                    if (debug) cout << "hey41111" << endl;
                    if (!keepthisevent) continue;
                    if (debug) cout << "hey411111" << endl;
                    if ((*preselected_leptons_intree).size()==0) continue;
                    if (debug) cout << "hey4111111" << endl;
                    countafter++;
                    if (debug) cout << "hey5" << endl;
                    if (debug) cout << "hey41111111" << endl;
                    
                    //furthermore, make a basic 2lss req:
                    if ( (*preselected_leptons_intree).size()!=2 ) continue;
                    if ( (*preselected_leptons_intree)[0].charge != (*preselected_leptons_intree)[1].charge ) continue;
                    
                    for (unsigned int k=0;k<(*preselected_leptons_intree).size();k++)
                    {
                        sample_hist[0][i]->Fill( (*preselected_leptons_intree)[k].obj.Pt(), weight );
                        sample_hist[9][i]->Fill( (*preselected_leptons_intree)[k].obj.Phi(), weight );
                        sample_hist[10][i]->Fill( (*preselected_leptons_intree)[k].obj.Eta(), weight );                        
                    }
                    if (debug) cout << "hey6" << endl;
                    if ((*preselected_leptons_intree).size()>0) sample_hist[1][i]->Fill( (*preselected_leptons_intree)[0].obj.Pt(), weight );
                    if ((*preselected_leptons_intree).size()>1) sample_hist[2][i]->Fill( (*preselected_leptons_intree)[1].obj.Pt(), weight );
                    
                    for (unsigned int k=0;k<(*preselected_jets_intree).size();k++)
                    {
                        sample_hist[6][i]->Fill( (*preselected_jets_intree)[k].obj.E(), weight );
                        sample_hist[11][i]->Fill( (*preselected_jets_intree)[k].obj.Phi(), weight );
                        sample_hist[12][i]->Fill( (*preselected_jets_intree)[k].obj.Eta(), weight );
                    }
                    if (debug) cout << "hey7" << endl;
                    sample_hist[5][i]->Fill( (*preselected_jets_intree).size(), weight );                    
                    
                    if ((*preselected_jets_intree).size()>0) sample_hist[7][i]->Fill( (*preselected_jets_intree)[0].obj.E(), weight );
                    if ((*preselected_jets_intree).size()>1) sample_hist[8][i]->Fill( (*preselected_jets_intree)[1].obj.E(), weight );
                    
                    
                    sample_hist[3][i]->Fill( (*met_intree)[0].obj.Pt(), weight );
                    sample_hist[4][i]->Fill( (*met_intree)[0].obj.Phi(), weight );
                    
                    
                    
                    if (debug) cout << "hey8" << endl;
                   
                    
                }
                        
                cout << " " << endl;
		cout << "all events: " << countbefore << endl;
                cout << "all events passing sel: " << countafter << endl;
                cout << " " << endl;
                
                newtempfile.Write();
                newtempfile.Close();
                
        
        }
	   
        
    compareplots(samps, tempfilenames);
       
    
}
void MakeGoodPlot::draw_eff_curves(std::vector<int> samps)
{
		
	int numsamples = samps.size();
	int numhists = 6; // t,m,l POG IDs, and t,m,l lep MVA
        
        
	TH1F *dummy_hist;
        //TH1F *sample_hist2[6]; // numer
        //TH1F *sample_hist3[numhists]; // numer (bkd)
        
	
	load_samples(samps);

	
	//TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);  /// (0.3,0.77,0.7,0.88)
	//TLegend* leg = new TLegend(0.12,0.12,0.3,0.4);  /// bottom left
        TLegend* leg = new TLegend(0.55,0.12,0.87,0.5);  /// bottom right
        
	//TLegend* leg = new TLegend(0.14,0.75,0.94,0.89); // Darren format
	//TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.035);
	//leg->SetNColumns(5);
	
	int sig_hist_index = 1;
	
        Float_t bins[8] = {0,10,15,20,25,30,50,100}; // pt bins
        
	for (int i=0; i<numhists; i++)
	{
				
		//sample_hist_shared[i] = new TH1F("denom " + int2ss(i),"",7,bins);
                sample_hist_shared[i] = new TH1F("denom " + int2ss(i),"",16,-8,8);
                //sample_hist[samp_int] = new TH1F("BDT response, ss2l+6j " + sample_names[samp_int],"",10,-3.0,3.0);
                //sample_hist_shared[i]->Sumw2();                
                //sample_hist_shared2[i] = new TH1F("eff numer " + int2ss(i),"",7,bins);
                sample_hist_shared2[i] = new TH1F("eff numer " + int2ss(i),"",16,-8,8);
                //sample_hist2[samp_int] = new TH1F("cut, ss2l+6j " + sample_names[samp_int],"",10,-3.0,3.0);
                //sample_hist_shared2[i]->Sumw2();
                //sample_hist3[i] = new TH1F("eff2 numer " + int2ss(i),"",6,bins);
                //sample_hist3[samp_int] = new TH1F("cut, ss2l+6j " + sample_names[samp_int],"",10,-3.0,3.0);
                //sample_hist3[i]->Sumw2();
                
                
		//get_hist_of_simple_variable(sample_hist[samp_int],samp_int,sample_hist2[samp_int]);                                
                
                //sample_hist[i]->Divide(sample_hist2[i]);
                
                //leg->AddEntry(sample_hist[i],sample_names[samp_int],"l");
        }
	
        get_hist_of_simple_variable(dummy_hist,1);
        
        
	int j = 0;
        
	cout << "hey2" << endl;
        
	TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660);
	can1->SetGridx();
	can1->SetGridy();
        
        TGraphAsymmErrors *eff[10];
        
        for (int i=0; i<numhists; i++)
	{
        
            cout << "hey3" << endl;
            //->GetXaxis()->SetTitle
            //sample_hist_shared[i]->Divide(sample_hist_shared2[i]);
            eff[i] = new TGraphAsymmErrors(sample_hist_shared[i],sample_hist_shared2[i]);
            cout << "hey4" << endl;

            sample_hist_shared[i]->SetStats(0);
            sample_hist_shared[i]->SetLineWidth(2);
            sample_hist_shared[i]->SetLineColor(2+i);
	    
            eff[i]->SetLineWidth(2);
            
            if (i<3) eff[i]->SetLineColor(kRed+i);
            else eff[i]->SetLineColor(kGreen+i-3);
            
            //if (i==0) sample_hist_shared[i]->Draw("E");
            //else  sample_hist_shared[i]->Draw("Esame");
            
            //if (i==0) eff[i]->Draw("ap");
            //else  eff[i]->Draw("p,same");
            
            
            //sample_hist[1]->GetXaxis()->SetTitle("lep1 Pt");
            //sample_hist_shared[i]->GetXaxis()->SetTitle("mu p_{T}");
            //sample_hist_shared[i]->GetYaxis()->SetTitle("Eff");
            //sample_hist_shared[i]->GetYaxis()->SetRangeUser(0,1.1);
            
            //eff[i]->GetXaxis()->SetTitle("mu p_{T}");
            eff[i]->GetXaxis()->SetTitle("log(miniIso)<cut");
            eff[i]->GetYaxis()->SetTitle("Eff");
            eff[i]->GetYaxis()->SetRangeUser(0,1.1);
            eff[i]->GetXaxis()->SetRangeUser(-8,8);           
        }
        
        eff[0]->Draw("ap");
        eff[1]->Draw("p,same");
        //eff[5]->Draw("p,same");
        
        eff[0]->SetLineColor(kBlue);
        eff[1]->SetLineColor(kGreen+1);
        eff[2]->SetLineColor(kMagenta+1);
        eff[3]->SetLineColor(kRed);
        eff[4]->SetLineColor(kCyan+1);
        eff[5]->SetLineColor(kBlack);
        
        
        
//         leg->AddEntry(eff[0],"POG ID Loose","l");
//         leg->AddEntry(eff[1],"POG ID Med","l");
//         leg->AddEntry(eff[2],"POG ID Tight","l");
//         leg->AddEntry(eff[3],"LepMVA >-0.5","l");
//         leg->AddEntry(eff[4],"LepMVA >0","l");
//         leg->AddEntry(eff[5],"LepMVA >0.5","l");

//         leg->AddEntry(eff[0],"POG ID Loose","l");
//         leg->AddEntry(eff[3],"Preselection","l");
//         leg->AddEntry(eff[5],"LepMVA >0.5","l");


//         leg->AddEntry(eff[0],"POG ID Loose","l");
//         leg->AddEntry(eff[1],"dxy < 0.05","l");
//         leg->AddEntry(eff[2],"dz < 0.1","l");
//         leg->AddEntry(eff[3],"sip3D < 8","l");
//         leg->AddEntry(eff[4],"miniIso < 0.4","l");
//         leg->AddEntry(eff[5],"Full preselection","l");

         leg->AddEntry(eff[0],"prompt","l");
         leg->AddEntry(eff[1],"non-prompt","l");

        
 	leg->SetFillColor(0);
 	leg->Draw();
	

}

/// name says it all (uses get_hist_of_simple_variable)
void MakeGoodPlot::draw_simple_curves_normalized(std::vector<int> samps)
{
	
	int numsamples = samps.size();
	
	TH1F *sample_hist[numsamples];
	
//	load_samples(samps); // comment out for my trees
	load_samples(samps);
	
	//TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);  /// (0.3,0.77,0.7,0.88)
	//TLegend* leg = new TLegend(0.14,0.75,0.94,0.89); // Darren format
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	//leg->SetTextSize(0.035);
	leg->SetNColumns(5);
	
	
	
	for (int i=0; i<numsamples; i++)
	{
		
		int samp_int = samps[i];
		
		cout << "doing " << sample_names[samp_int] << endl;
		
		//sample_hist[i]->SetTitle("BDT response, 5j4t");
		//sample_hist[i]->SetBins(50,-1,1);
		
		//sample_hist[i] = new TH1F("BDT response, 5j4t " + sample_names[samp_int],"",20,-1,1);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";#Sigma jet p_{T}/#Sigma jet E",10,0,1);       // title  // #Sigma jet p_{T}/#Sigma jet E
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";sphericity",10,0,1);       // title  // #Sigma jet p_{T}/#Sigma jet E
		sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";average #DeltaR(jets)",10,0,4);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";Best Higgs Mass",25,0,500);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";Median Inv. Mass (tag,tag)",10,0,500);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";#sqrt{#Delta#eta(t_{lep},bb)#times#Delta#eta(t_{had},bb)}",10,0,6);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";best #DeltaR(b,b)",10,0,5);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";sum p_{T}(lepton,jets,MET)",25,0,1500);
		//sample_hist[i] = new TH1F("jet E " + sample_names[samp_int],";second highest CSV output (b-tags)",10,0.6,1);
		//sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";awert",1000,10000,10000);
		
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";abs(miniIso(lep1)+miniIso(lep2)+miniIso(lep3))",100,0,0.5);
		//sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";sum pt / sum E",100,0,1);
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";sum E",100,0,5000);
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";min pt",100,0,100);
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";W pt",100,0,1000);
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";status",2000,-1000,1000);
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";deltaR",100,0,10);
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";leading lep pt",100,0,500);
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";lep Mva (leptons in 2lss)",100,0.5,1.0);
                //sample_hist[i] = new TH1F("blah " + sample_names[samp_int],";lepton Eta (2lss)",100,-3,3);
                
		//get_hist_of_tiered_MVA_response_for_one_sample_5j4t(sample_hist[i],samp_int);
		//get_hist_MVA_response_for_one_sample_643203(sample_hist[i],samp_int);
		
		get_hist_of_simple_variable(sample_hist[i],samp_int);
		//get_even_simpler_plot_my_trees(sample_hist[i],samp_int);
		//get_hist_of_simple_variable(flavorhist[0],samp_int,flavorhist[1],flavorhist[2]);
		
		float sample_evts = sample_hist[i]->Integral();
		std::ostringstream sample_evts_ss;
		sample_evts_ss << sample_evts;
		std::string sample_evts_string = sample_evts_ss.str();
		
		/*
		if (samp_int<4) sample_hist[i]->SetLineColor(1+samp_int);		
		if (samp_int>=4) sample_hist[i]->SetLineColor(2+samp_int);
		*/
		
		
		if (samp_int==1) sample_hist[i]->SetLineColor(kRed); // ttH
		//if (samp_int==2) sample_hist[i]->SetLineColor(kGreen+1); //--
		//if (samp_int==3) sample_hist[i]->SetLineColor(kOrange+1); //--
		//if (samp_int==4) sample_hist[i]->SetLineColor(kMagenta+2); //--
		if (samp_int==5) sample_hist[i]->SetLineColor(kBlue); // ttjets
		if (samp_int==6) sample_hist[i]->SetLineColor(kGreen+1); // zjets
		if (samp_int==7) sample_hist[i]->SetLineColor(kOrange+1); //wjets
		if (samp_int==8) sample_hist[i]->SetLineColor(kMagenta+1); //ttw
		if (samp_int==9) sample_hist[i]->SetLineColor(kCyan-3); //ttz
		if (samp_int==10) sample_hist[i]->SetLineColor(kBlue-6); // diboson
                if (samp_int==13) sample_hist[i]->SetLineColor(kGreen+1); // ttjets (dilep)
		if (samp_int==14) sample_hist[i]->SetLineColor(kOrange+1); //ttjets (1 lep from t)
		if (samp_int==15) sample_hist[i]->SetLineColor(kMagenta+1); //ttjets (1 lep from tbar)
                
				
		//sample_hist[i]->GetXaxis()->SetTitle("pdgID");		
		sample_hist[i]->SetLineWidth(2);
		leg->AddEntry(sample_hist[i],sample_names[samp_int] + " (" + sample_evts_string + ")","l");  /// have ability to add # of evts per sample to legend... 
		//leg->AddEntry(sample_hist[i],sample_names[samp_int],"l");

		//sample_hist[i]->SetStats(0);
		//sample_hist[i]->SetTitleSize(0);		// <- works?
		
		
		if (!i)
		{
			//double maxstack = 
			//sample_hist[i]->SetMaximim(1.25*sample_hist[i]->GetMaximum());
			sample_hist[i]->DrawNormalized();			
		}
		else sample_hist[i]->DrawNormalized("same");
		//if (!i) sample_hist[i]->Draw();
		//else sample_hist[i]->Draw("same");
		
		
	}
	
	leg->SetFillColor(0);
	//leg->Draw("same");
	//CMSInfoLatex->Draw("same");
	
	//std::string selectioninfo = "#geq 6 jets + 2 b-tags";
	//std::string selectioninfo = "#geq 6 jets + 3 b-tags";
	//std::string selectioninfo = "#geq 6 jets + #geq 4 b-tags";
	//std::string selectioninfo = "5 jets + 3 b-tags";
	//std::string selectioninfo = "5 jets + #geq 4 b-tags";
	std::string selectioninfo = "#geq 2 tight leps";
	
	TLatex *SELECTIONInfoLatex = new TLatex(0.62, 0.84, selectioninfo.c_str());  		// right
	//TLatex *SELECTIONInfoLatex = new TLatex(0.15, 0.84, selectioninfo.c_str());  		// left
	
	
	SELECTIONInfoLatex->SetNDC();
	SELECTIONInfoLatex->SetTextFont(42);
	SELECTIONInfoLatex->SetTextSize(0.05);
	//SELECTIONInfoLatex->Draw("same");
	

	leg->Draw("same");
}



void MakeGoodPlot::draw_2D_plot(std::vector<int> samps)
{
    
    	int numsamples = samps.size();
	
	//TH2D *sample_hist[numsamples][5];
	load_samples(samps);
	
	//TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);  /// (0.3,0.77,0.7,0.88)
	//TLegend* leg = new TLegend(0.14,0.75,0.94,0.89); // Darren format
	TLegend* leg = new TLegend(0.11,0.91,0.89,0.99); // above the plot
	
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	//leg->SetTextSize(0.035);
	leg->SetNColumns(5);
	
	
	for (int i=0; i<numsamples; i++)
	{
            int samp_int = samps[i];
    
            cout << "doing " << sample_names[samp_int] << endl;
            for (int blah=0; blah<5; blah++) 
	    {
                mgp_sample_hist_2D[i][blah] = new TH2D("blah " + sample_names[samp_int] + int2ss(blah),";awert",20,0,25,20,0,25);
                mgp_sample_hist_2D[i][blah]->Sumw2();
            }
            
            get_hist_of_simple_variable_2D(samp_int,i);
            
	    // float sample_evts = sample_hist[i]->Integral();
// 	    std::ostringstream sample_evts_ss;
// 	    sample_evts_ss << sample_evts;
// 	    std::string sample_evts_string = sample_evts_ss.str();
            for (int blah=0; blah<5; blah++) 
	    {
                //mgp_sample_hist_2D[i][blah]->Scale(10000. * xsecs[samp_int] / (400.*numgen[samp_int]) ); // scaling is AVGD over 400 bins
                for (int k=1; k<=20; k++)
                {
                    for (int j=1; j<=20; j++)
                    {
                        double bincont = mgp_sample_hist_2D[i][blah]->GetBinContent(k,j);
                        mgp_sample_hist_2D[i][blah]->SetBinContent(k,j, (bincont * 10000. * xsecs[samp_int] / numgen[samp_int]) ); // each individual bin is scaled
                    }
                }
                
            }
            
            
            
        }
    
                
        
        // do s/sqrt(b) study (where you know which one is the signal):
        
        TH2D *sumbkgd[5];
        TH2D *signal[5];
        
        for (int blah=0; blah<5; blah++) 
	{
        

            signal[blah] = (TH2D*)mgp_sample_hist_2D[0][blah]->Clone("signal"+int2ss(blah));

            for (int i=1; i<numsamples; i++)
	    {
                if (i==1) sumbkgd[blah] = (TH2D*)mgp_sample_hist_2D[i][blah]->Clone("sumbkgd"+int2ss(blah));
                else sumbkgd[blah]->Add(mgp_sample_hist_2D[i][blah]);
            }


            for (int i=1; i<=20; i++)
            {
                for (int j=1; j<=20; j++)
                {
                    double bincont = sumbkgd[blah]->GetBinContent(i,j);
                    sumbkgd[blah]->SetBinContent(i,j,sqrt(bincont));
                }
            }

            //signal[blah]->Divide(sumbkgd[blah]);

            signal[blah]->SetStats(0);
            signal[blah]->GetXaxis()->SetTitle("lep 1 pt");
            signal[blah]->GetYaxis()->SetTitle("lep 2 pt");
            
            TCanvas *heybuddy = new TCanvas("hey"+int2ss(blah),"hey"+int2ss(blah),150,10,990,660);
            
            signal[blah]->Draw("COLZ,TEXT");   
    
        }
    
}

