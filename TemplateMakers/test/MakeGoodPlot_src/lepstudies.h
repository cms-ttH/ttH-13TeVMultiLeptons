void MakeGoodPlot::lepstudies(std::vector<int> samps) // really only one sample at a time (just easier to copy and paste existing code ..)
{
    bool debug = false;
    int numsamples = samps.size();		
    load_samples(samps);
    
    const int numplots = 5;

    TH1D *sample_hist_mu[numplots];
    TH1D *sample_hist_el[numplots];
    TString xaxis_title[numplots];
	
    THStack *nice_stack_mu[5];
    THStack *nice_stack_el[5];
    
    //TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);  /// (0.3,0.77,0.7,0.88)
    //TLegend* leg = new TLegend(0.14,0.75,0.94,0.89); // Darren format
    TLegend* leg1 = new TLegend(0.11,0.91,0.89,0.99); // above the plot

    leg1->SetFillColor(kWhite);
    leg1->SetLineColor(kWhite);
    leg1->SetShadowColor(kWhite);
    leg1->SetTextFont(42);
    //leg->SetTextSize(0.035);
    leg1->SetNColumns(5);
    
    
    TLegend* leg2 = new TLegend(0.11,0.91,0.89,0.99); // above the plot

    leg2->SetFillColor(kWhite);
    leg2->SetLineColor(kWhite);
    leg2->SetShadowColor(kWhite);
    leg2->SetTextFont(42);
    //leg->SetTextSize(0.035);
    leg2->SetNColumns(5);
    
    
    
    
    for (int j=0;j<numplots;j++)
    {
        sample_hist_mu[j] = new TH1D("hist_mu"+int2ss(j),";muon pt",150,0,150);
        //sample_hist_mu[j]->Sumw2();
        sample_hist_el[j] = new TH1D("hist_el"+int2ss(j),";electron pt",150,0,150);
        //sample_hist_el[j]->Sumw2();
        sample_hist_mu[j]->SetLineWidth(2);
        sample_hist_mu[j]->SetStats(0);
        sample_hist_el[j]->SetLineWidth(2);
        sample_hist_el[j]->SetStats(0);
        
        nice_stack_mu[j] = new THStack("stack1",";muon pt");
	nice_stack_el[j] = new THStack("stack2",";electron pt");
    
        
    }
    
    for (int i=0; i<numsamples; i++)
    {	
	int samp_int = samps[i];
		
	cout << "doing " << sample_names[samp_int] << endl;
        
        
        ch[samp_int]->SetBranchAddress("mcwgt", &mcwgt_intree);
        ch[samp_int]->SetBranchAddress("wgt", &wgt_intree);

        ch[samp_int]->SetBranchAddress("passTrigger", &passTrigger_intree);
        

        ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
        ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
        ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);

         ch[samp_int]->SetBranchAddress("looseMvaBased_leptons", &looseMvaBased_leptons_intree);
         ch[samp_int]->SetBranchAddress("looseMvaBased_electrons", &looseMvaBased_electrons_intree);
         ch[samp_int]->SetBranchAddress("looseMvaBased_muons", &looseMvaBased_muons_intree);
 
         ch[samp_int]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
         ch[samp_int]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
         ch[samp_int]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);
// 
//         ch[samp_int]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
//         ch[samp_int]->SetBranchAddress("met", &met_intree);
		

        
        int theEntries = ch[samp_int]->GetEntries();
        
        if (debug) cout << "hey1" << endl;
        
        for (int j=0;j<theEntries;j++)
        {
	    if (debug) cout << "hey1.01" << endl;
            ch[samp_int]->GetEntry(j);
	    if (debug) cout << "hey1.02" << endl;					
            weight = wgt_intree; 
            
            int nummus = (*preselected_muons_intree).size();
            int numeles = (*preselected_electrons_intree).size();
            
            for (int k=0; k<nummus; k++)
            //if (nummus>1)
            {
                
                //sample_hist_mu[0]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                //sample_hist_mu[1]->Fill(sqrt((*preselected_muons_intree)[k].obj.Px()*(*preselected_muons_intree)[k].obj.Px() + (*preselected_muons_intree)[k].obj.Py()*(*preselected_muons_intree)[k].obj.Py()),weight);
                
                //if (abs((*preselected_muons_intree)[1].genMotherPdgID)==24) sample_hist_mu[1]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                //if (abs((*preselected_muons_intree)[1].genMotherPdgID)!=24) sample_hist_mu[2]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                if ((*preselected_muons_intree)[k].lepMVA>0.8 && abs((*preselected_muons_intree)[k].genMotherPdgID)==24) sample_hist_mu[1]->Fill((*preselected_muons_intree)[k].obj.Pt(),weight);
                if ((*preselected_muons_intree)[k].lepMVA>0.8 && abs((*preselected_muons_intree)[k].genMotherPdgID)!=24) sample_hist_mu[2]->Fill((*preselected_muons_intree)[k].obj.Pt(),weight);
                
            }
            for (int k=0; k<numeles; k++)
            //if (numeles>1)
            {
                                
                //sample_hist_el[0]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                
                
                //if (abs((*preselected_electrons_intree)[1].genMotherPdgID)==24) sample_hist_el[1]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                //if (abs((*preselected_electrons_intree)[1].genMotherPdgID)!=24) sample_hist_el[2]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                if ((*preselected_electrons_intree)[k].lepMVA>0.8 && abs((*preselected_electrons_intree)[k].genMotherPdgID)==24) sample_hist_el[1]->Fill((*preselected_electrons_intree)[k].obj.Pt(),weight);
                if ((*preselected_electrons_intree)[k].lepMVA>0.8 && abs((*preselected_electrons_intree)[k].genMotherPdgID)!=24) sample_hist_el[2]->Fill((*preselected_electrons_intree)[k].obj.Pt(),weight);
                
            }
        }
    }
    
    sample_hist_mu[0]->SetLineColor(kRed);
    sample_hist_mu[1]->SetLineColor(kGreen+1);
    sample_hist_mu[1]->SetFillColor(kGreen+1);
    sample_hist_mu[2]->SetLineColor(kOrange+1);
    sample_hist_mu[2]->SetFillColor(kOrange+1);
    sample_hist_mu[3]->SetLineColor(kMagenta+2);
    sample_hist_mu[4]->SetLineColor(kBlue);

    sample_hist_el[0]->SetLineColor(kRed);
    sample_hist_el[1]->SetLineColor(kGreen+1);
    sample_hist_el[1]->SetFillColor(kGreen+1);
    sample_hist_el[2]->SetLineColor(kOrange+1);
    sample_hist_el[2]->SetFillColor(kOrange+1);
    sample_hist_el[3]->SetLineColor(kMagenta+2);
    sample_hist_el[4]->SetLineColor(kBlue);


    //leg1->AddEntry(sample_hist_mu[0],"presel muons","l");
    leg1->AddEntry(sample_hist_mu[1],"from W","F");
    leg1->AddEntry(sample_hist_mu[2],"not from W","F");
    //leg1->AddEntry(sample_hist_mu[3],"lepMVA>0.6","l");
    //leg1->AddEntry(sample_hist_mu[4],"lepMVA>0.8","l");
    
    //leg2->AddEntry(sample_hist_el[0],"presel eles","l");
    leg2->AddEntry(sample_hist_el[1],"from W","F");
    leg2->AddEntry(sample_hist_el[2],"not from W","F");
    //leg2->AddEntry(sample_hist_el[3],"lepMVA>0.6","l");
    //leg2->AddEntry(sample_hist_el[4],"lepMVA>0.8","l");
    
    
    TCanvas *hey1 = new TCanvas("hey1","hey1",150,10,990,660);
    
    nice_stack_mu[0]->Add(sample_hist_mu[1]);
    nice_stack_mu[0]->Add(sample_hist_mu[2]);
    nice_stack_mu[0]->GetYaxis()->SetRangeUser(0.,4000.);
    nice_stack_mu[0]->Draw("hist");
    
    
    //sample_hist_mu[0]->DrawNormalized("hist");
    //sample_hist_mu[1]->DrawNormalized("hist same");
    //sample_hist_mu[2]->DrawNormalized("hist same");
    //sample_hist_mu[3]->DrawNormalized("hist same");
    //sample_hist_mu[4]->DrawNormalized("hist same");
    
    leg1->Draw("same");
    
    
   TCanvas *hey2 = new TCanvas("hey2","hey2",150,10,990,660);
    
    nice_stack_el[0]->Add((TH1F*)sample_hist_el[1]);
    nice_stack_el[0]->Add((TH1F*)sample_hist_el[2]);
    nice_stack_el[0]->GetYaxis()->SetRangeUser(0.,3000.);
    nice_stack_el[0]->Draw("hist");
    
    //sample_hist_el[0]->DrawNormalized("hist");
    //sample_hist_el[1]->DrawNormalized("hist same");
    //sample_hist_el[2]->DrawNormalized("hist same");
    //sample_hist_el[3]->DrawNormalized("hist same");
    //sample_hist_el[4]->DrawNormalized("hist same");
    
    leg2->Draw("same"); 
    
    
    
}
    
    
    
    
    
      
            
            
            
