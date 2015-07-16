void MakeGoodPlot::lepstudies(std::vector<int> samps) // really only one sample at a time (just easier to copy and paste existing code ..)
{
    bool debug = false;
    int numsamples = samps.size();		
    load_samples(samps);
    
    const int numplots = 5;

    
    TH1D *asdfasdf[numplots];
    

    TH1D *sample_hist_all[numplots];
    TH1D *sample_hist_mu[numplots];
    TH1D *sample_hist_el[numplots];
    
    TH1D *sample_hist_all_again[numplots];
    TH1D *sample_hist_mu_again[numplots];
    TH1D *sample_hist_el_again[numplots];
    
    
    
    TString xaxis_title[numplots];
    
    
    TH2D *sample_2Dhist_mu = new TH2D("sample_2Dhist_mu","sample_2Dhist_mu",30,-1.5,1.5,30,0,150);
    TH2D *sample_2Dhist_el = new TH2D("sample_2Dhist_el","sample_2Dhist_el",50,0,50,50,0,50);
    
    
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
        sample_hist_all[j] = new TH1D("hist_all"+int2ss(j),";lepton pt",15,0,150); // 150,0,150
        sample_hist_all[j]->Sumw2();        
        sample_hist_mu[j] = new TH1D("hist_mu"+int2ss(j),";muon pt",150,0,150); // 150,0,150
        sample_hist_mu[j]->Sumw2();
        sample_hist_el[j] = new TH1D("hist_el"+int2ss(j),";electron pt",150,0,150);
        sample_hist_el[j]->Sumw2();
        
        sample_hist_all_again[j] = new TH1D("hist_all_again"+int2ss(j),";lepton pt",15,0,150);
        sample_hist_all_again[j]->Sumw2();        
        sample_hist_mu_again[j] = new TH1D("hist_mu_again"+int2ss(j),";muon pt",15,0,150);
        sample_hist_mu_again[j]->Sumw2();
        sample_hist_el_again[j] = new TH1D("hist_el_again"+int2ss(j),";electron pt",15,0,150);
        sample_hist_el_again[j]->Sumw2();
        
        sample_hist_all[j]->SetLineWidth(2);
        sample_hist_all[j]->SetStats(0);  
        sample_hist_all_again[j]->SetLineWidth(2);
        sample_hist_all_again[j]->SetStats(0);  
                              
        sample_hist_mu[j]->SetLineWidth(2);
        sample_hist_mu[j]->SetStats(0);        
        sample_hist_mu_again[j]->SetLineWidth(2);
        sample_hist_mu_again[j]->SetStats(0);
                             
        sample_hist_el[j]->SetLineWidth(2);
        sample_hist_el[j]->SetStats(0);
        sample_hist_el_again[j]->SetLineWidth(2);
        sample_hist_el_again[j]->SetStats(0);
                
        
        nice_stack_mu[j] = new THStack("stack1",";muon pt");
	nice_stack_el[j] = new THStack("stack2",";electron pt");
        
        
        asdfasdf[j] = new TH1D("asdfasdf"+int2ss(j),";lep MVA",50,-2,2);
        asdfasdf[j]->Sumw2();
        asdfasdf[j]->SetLineWidth(2);
        asdfasdf[j]->SetStats(0);
        
    }
    
    sample_hist_all[0]->SetLineWidth(3);
    sample_hist_all_again[0]->SetLineWidth(3);
    
    
    
    
    
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
        
        cout << theEntries << endl;
        
        if (debug) cout << "hey1" << endl;
        
        for (int j=0;j<theEntries;j++)
        {
	    if (debug) cout << "hey1.01" << endl;
            ch[samp_int]->GetEntry(j);
	    if (debug) cout << "hey1.02" << endl;					
            weight = wgt_intree; 
            
            int nummus = (*preselected_muons_intree).size();
            int numeles = (*preselected_electrons_intree).size();
            
            int nummusloose = (*looseMvaBased_muons_intree).size();
            int numelesloose = (*looseMvaBased_electrons_intree).size();
            
            int nummustight = (*tightMvaBased_muons_intree).size();
            int numelestight = (*tightMvaBased_electrons_intree).size();
            
            int numlepsloose = (*looseMvaBased_leptons_intree).size();
            
            int numlepstight = nummustight + numelestight;
            
                        
            //if ( numlepsloose>0 )
            //{
                //if ((*preselected_leptons_intree)[0].miniIso<0.4 && (*looseMvaBased_leptons_intree)[0].miniIso<0.4)
                //{
                            
                
                   //for (int k=0; k<nummus; k++)
                    //if (nummus+numeles>=2)
                    //{
                        //if (!((*preselected_leptons_intree)[1].lepMVA>0.8)) continue;

                        //sample_hist_all[0]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);
                        //sample_hist_all[1]->Fill(sqrt((*preselected_leptons_intree)[1].obj.Px()*(*preselected_leptons_intree)[1].obj.Px() + (*preselected_leptons_intree)[1].obj.Py()*(*preselected_leptons_intree)[1].obj.Py()),weight);

                        if (abs((*preselected_leptons_intree)[1].genMotherPdgID)==24 && (*preselected_leptons_intree)[1].miniIso<0.4)
                        {
                            sample_hist_all_again[0]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);
                            sample_2Dhist_mu->Fill(abs((*preselected_leptons_intree)[1].lepMVA),abs((*preselected_leptons_intree)[1].obj.Pt()),weight);
                        }
                        if (abs((*preselected_leptons_intree)[1].genMotherPdgID)!=24 && (*preselected_leptons_intree)[1].miniIso<0.4)
                        {
                            if (abs((*preselected_leptons_intree)[1].genMotherPdgID)==15 && abs((*preselected_leptons_intree)[1].genGrandMotherPdgID)==24) sample_hist_all_again[1]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);
                            else if (abs((*preselected_leptons_intree)[1].genMotherPdgID)==15 && abs((*preselected_leptons_intree)[1].genGrandMotherPdgID)==25) sample_hist_all_again[2]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);
                            else if (abs((*preselected_leptons_intree)[1].genMotherPdgID)==23 && abs((*preselected_leptons_intree)[1].genGrandMotherPdgID)==25) sample_hist_all_again[3]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);
                            else sample_hist_all_again[4]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);

                            //sample_hist_all[2]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);
                            //sample_2Dhist_mu->Fill(abs((*preselected_leptons_intree)[1].genMotherPdgID),abs((*preselected_leptons_intree)[1].genGrandMotherPdgID),weight);
                        }
                        //if ((*preselected_leptons_intree)[1].lepMVA>0.8 && abs((*preselected_leptons_intree)[1].genMotherPdgID)==24) sample_hist_all[1]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);
                        //if ((*preselected_leptons_intree)[1].lepMVA>0.8 && abs((*preselected_leptons_intree)[1].genMotherPdgID)!=24) sample_hist_all[2]->Fill((*preselected_leptons_intree)[1].obj.Pt(),weight);

                    //}
                    //for (int k=0; k<numeles; k++) 




                    //for (int k=0; k<nummus; k++)
                    if (nummus>=2)
                    {
                        //if (!((*preselected_muons_intree)[1].lepMVA>0.8)) continue;

                        //sample_hist_mu[0]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                        //sample_hist_mu[1]->Fill(sqrt((*preselected_muons_intree)[1].obj.Px()*(*preselected_muons_intree)[1].obj.Px() + (*preselected_muons_intree)[1].obj.Py()*(*preselected_muons_intree)[1].obj.Py()),weight);

                        if (abs((*preselected_muons_intree)[1].genMotherPdgID)==24 && (*preselected_muons_intree)[1].miniIso<0.4) sample_hist_mu_again[0]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                        if (abs((*preselected_muons_intree)[1].genMotherPdgID)!=24 && (*preselected_muons_intree)[1].miniIso<0.4)
                        {
                            if (abs((*preselected_muons_intree)[1].genMotherPdgID)==15 && abs((*preselected_muons_intree)[1].genGrandMotherPdgID)==24) sample_hist_mu_again[1]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                            else if (abs((*preselected_muons_intree)[1].genMotherPdgID)==15 && abs((*preselected_muons_intree)[1].genGrandMotherPdgID)==25) sample_hist_mu_again[2]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                            else if (abs((*preselected_muons_intree)[1].genMotherPdgID)==23 && abs((*preselected_muons_intree)[1].genGrandMotherPdgID)==25) sample_hist_mu_again[3]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                            else sample_hist_mu_again[4]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);

                            //sample_hist_mu[2]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                            //sample_2Dhist_mu->Fill(abs((*preselected_muons_intree)[1].genMotherPdgID),abs((*preselected_muons_intree)[1].genGrandMotherPdgID),weight);
                        }
                        //if ((*preselected_muons_intree)[1].lepMVA>0.8 && abs((*preselected_muons_intree)[1].genMotherPdgID)==24) sample_hist_mu[1]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);
                        //if ((*preselected_muons_intree)[1].lepMVA>0.8 && abs((*preselected_muons_intree)[1].genMotherPdgID)!=24) sample_hist_mu[2]->Fill((*preselected_muons_intree)[1].obj.Pt(),weight);

                    }
                    //for (int k=0; k<numeles; k++)
                    if (numeles>=2)
                    {
                        //if (!((*preselected_electrons_intree)[1].lepMVA>0.8)) continue;
                        //sample_hist_el[0]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);


                        if (abs((*preselected_electrons_intree)[1].genMotherPdgID)==24 && (*preselected_electrons_intree)[1].miniIso<0.4) sample_hist_el_again[0]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                        if (abs((*preselected_electrons_intree)[1].genMotherPdgID)!=24 && (*preselected_electrons_intree)[1].miniIso<0.4)
                        {
                            if (abs((*preselected_electrons_intree)[1].genMotherPdgID)==15 && abs((*preselected_electrons_intree)[1].genGrandMotherPdgID)==24) sample_hist_el_again[1]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                            else if (abs((*preselected_electrons_intree)[1].genMotherPdgID)==15 && abs((*preselected_electrons_intree)[1].genGrandMotherPdgID)==25) sample_hist_el_again[2]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                            else if (abs((*preselected_electrons_intree)[1].genMotherPdgID)==23 && abs((*preselected_electrons_intree)[1].genGrandMotherPdgID)==25) sample_hist_el_again[3]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                            else sample_hist_el_again[4]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);

                            //sample_hist_el[2]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                            //sample_2Dhist_el->Fill(abs((*preselected_electrons_intree)[1].genMotherPdgID),abs((*preselected_electrons_intree)[1].genGrandMotherPdgID),weight);
                        }
                        //if ((*preselected_electrons_intree)[1].lepMVA>0.8 && abs((*preselected_electrons_intree)[1].genMotherPdgID)==24) sample_hist_el[1]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);
                        //if ((*preselected_electrons_intree)[1].lepMVA>0.8 && abs((*preselected_electrons_intree)[1].genMotherPdgID)!=24) sample_hist_el[2]->Fill((*preselected_electrons_intree)[1].obj.Pt(),weight);

                    }





                    if (numlepsloose>=2)
                    {

                        //sample_hist_all[0]->Fill((*looseMvaBased_leptons_intree)[1].obj.Pt(),weight);
                        //sample_hist_all[1]->Fill(sqrt((*looseMvaBased_leptons_intree)[1].obj.Px()*(*looseMvaBased_leptons_intree)[1].obj.Px() + (*looseMvaBased_leptons_intree)[1].obj.Py()*(*looseMvaBased_leptons_intree)[1].obj.Py()),weight);

                        if (abs((*looseMvaBased_leptons_intree)[1].genMotherPdgID)==24 && (*looseMvaBased_leptons_intree)[1].miniIso<0.4) sample_hist_all[0]->Fill((*looseMvaBased_leptons_intree)[1].obj.Pt(),weight);
                        if (abs((*looseMvaBased_leptons_intree)[1].genMotherPdgID)!=24 && (*looseMvaBased_leptons_intree)[1].miniIso<0.4)
                        {
                            if (abs((*looseMvaBased_leptons_intree)[1].genMotherPdgID)==15 && abs((*looseMvaBased_leptons_intree)[1].genGrandMotherPdgID)==24) sample_hist_all[1]->Fill((*looseMvaBased_leptons_intree)[1].obj.Pt(),weight);
                            else if (abs((*looseMvaBased_leptons_intree)[1].genMotherPdgID)==15 && abs((*looseMvaBased_leptons_intree)[1].genGrandMotherPdgID)==25) sample_hist_all[2]->Fill((*looseMvaBased_leptons_intree)[1].obj.Pt(),weight);
                            else if (abs((*looseMvaBased_leptons_intree)[1].genMotherPdgID)==23 && abs((*looseMvaBased_leptons_intree)[1].genGrandMotherPdgID)==25) sample_hist_all[3]->Fill((*looseMvaBased_leptons_intree)[1].obj.Pt(),weight);
                            else sample_hist_all[4]->Fill((*looseMvaBased_leptons_intree)[1].obj.Pt(),weight);

                            //sample_2Dhist_mu->Fill(abs((*looseMvaBased_leptons_intree)[1].genMotherPdgID),abs((*looseMvaBased_leptons_intree)[1].genGrandMotherPdgID),weight);
                        }


                    }




                    for (int k=0; k<nummustight; k++)
                    //if (nummustight>=2)
                    {
                        //sample_hist_mu[0]->Fill((*tightMvaBased_muons_intree)[k].obj.Pt(),weight);
                        //sample_hist_mu[1]->Fill(sqrt((*tightMvaBased_muons_intree)[k].obj.Px()*(*tightMvaBased_muons_intree)[k].obj.Px() + (*tightMvaBased_muons_intree)[k].obj.Py()*(*tightMvaBased_muons_intree)[k].obj.Py()),weight);

                        if (abs((*tightMvaBased_muons_intree)[k].genMotherPdgID)==24 && (*tightMvaBased_muons_intree)[k].miniIso<0.4) sample_hist_mu[0]->Fill((*tightMvaBased_muons_intree)[k].obj.Pt(),weight);
                        if (abs((*tightMvaBased_muons_intree)[k].genMotherPdgID)!=24 && (*tightMvaBased_muons_intree)[k].miniIso<0.4)
                        {
                            if (abs((*tightMvaBased_muons_intree)[k].genMotherPdgID)==15 && abs((*tightMvaBased_muons_intree)[k].genGrandMotherPdgID)==24) sample_hist_mu[1]->Fill((*tightMvaBased_muons_intree)[k].obj.Pt(),weight);
                            else if (abs((*tightMvaBased_muons_intree)[k].genMotherPdgID)==15 && abs((*tightMvaBased_muons_intree)[k].genGrandMotherPdgID)==25) sample_hist_mu[2]->Fill((*tightMvaBased_muons_intree)[k].obj.Pt(),weight);
                            else if (abs((*tightMvaBased_muons_intree)[k].genMotherPdgID)==23 && abs((*tightMvaBased_muons_intree)[k].genGrandMotherPdgID)==25) sample_hist_mu[3]->Fill((*tightMvaBased_muons_intree)[k].obj.Pt(),weight);
                            else sample_hist_mu[4]->Fill((*tightMvaBased_muons_intree)[k].obj.Pt(),weight);

                            //sample_2Dhist_mu->Fill(abs((*tightMvaBased_muons_intree)[k].genMotherPdgID),abs((*tightMvaBased_muons_intree)[k].genGrandMotherPdgID),weight);
                        }


                    }
                    for (int k=0; k<numelestight; k++)
                    //if (numelestight>=2)
                    {
                        //if (!((*tightMvaBased_electrons_intree)[k].lepMVA>0.8)) continue;
                        //sample_hist_el[0]->Fill((*tightMvaBased_electrons_intree)[k].obj.Pt(),weight);

                        if (abs((*tightMvaBased_electrons_intree)[k].genMotherPdgID)==24 && (*tightMvaBased_electrons_intree)[k].miniIso<0.4) sample_hist_el[0]->Fill((*tightMvaBased_electrons_intree)[k].obj.Pt(),weight);
                        if (abs((*tightMvaBased_electrons_intree)[k].genMotherPdgID)!=24 && (*tightMvaBased_electrons_intree)[k].miniIso<0.4)
                        {
                            if (abs((*tightMvaBased_electrons_intree)[k].genMotherPdgID)==15 && abs((*tightMvaBased_electrons_intree)[k].genGrandMotherPdgID)==24) sample_hist_el[1]->Fill((*tightMvaBased_electrons_intree)[k].obj.Pt(),weight);
                            else if (abs((*tightMvaBased_electrons_intree)[k].genMotherPdgID)==15 && abs((*tightMvaBased_electrons_intree)[k].genGrandMotherPdgID)==25) sample_hist_el[2]->Fill((*tightMvaBased_electrons_intree)[k].obj.Pt(),weight);
                            else if (abs((*tightMvaBased_electrons_intree)[k].genMotherPdgID)==23 && abs((*tightMvaBased_electrons_intree)[k].genGrandMotherPdgID)==25) sample_hist_el[3]->Fill((*tightMvaBased_electrons_intree)[k].obj.Pt(),weight);
                            else sample_hist_el[4]->Fill((*tightMvaBased_electrons_intree)[k].obj.Pt(),weight);

                            //sample_2Dhist_el->Fill(abs((*tightMvaBased_electrons_intree)[k].genMotherPdgID),abs((*tightMvaBased_electrons_intree)[k].genGrandMotherPdgID),weight);
                        }

                    }
                
                }
            
            //}
            
            for (int k=0; k<(nummus+numeles); k++)
            {
                if (abs((*preselected_leptons_intree)[k].genMotherPdgID)==24 && (*preselected_leptons_intree)[k].miniIso<0.4) asdfasdf[0]->Fill((*preselected_leptons_intree)[k].lepMVA,weight);
                if (abs((*preselected_leptons_intree)[k].genMotherPdgID)!=24 && (*preselected_leptons_intree)[k].miniIso<0.4)
                {
                    if (abs((*preselected_leptons_intree)[k].genMotherPdgID)==15 && abs((*preselected_leptons_intree)[k].genGrandMotherPdgID)==24) asdfasdf[1]->Fill((*preselected_leptons_intree)[k].lepMVA,weight);
                    else if (abs((*preselected_leptons_intree)[k].genMotherPdgID)==15 && abs((*preselected_leptons_intree)[k].genGrandMotherPdgID)==25) asdfasdf[2]->Fill((*preselected_leptons_intree)[k].lepMVA,weight);
                    else if (abs((*preselected_leptons_intree)[k].genMotherPdgID)==23 && abs((*preselected_leptons_intree)[k].genGrandMotherPdgID)==25) asdfasdf[3]->Fill((*preselected_leptons_intree)[k].lepMVA,weight);
                    else asdfasdf[4]->Fill((*preselected_leptons_intree)[k].lepMVA,weight);

                }
            }
            
            
        }
    }
    
    //TGraphAsymmErrors* testthing = new TGraphAsymmErrors();
    //testthing->BayesDivide(sample_hist_mu[0], sample_hist_mu_again[0]);
    
    
    
    for (int j=0;j<numplots;j++)
    {
        //sample_hist_mu[j]->Divide(sample_hist_mu[j],sample_hist_mu_again[j],1.,1.,"B");
        //sample_hist_el[j]->Divide(sample_hist_el[j],sample_hist_el_again[j],1.,1.,"B");
        
        sample_hist_all[j]->Divide(sample_hist_all_again[j]);
        //sample_hist_mu[j]->Divide(sample_hist_mu_again[j]);
        //sample_hist_el[j]->Divide(sample_hist_el_again[j]);
        
    }
    
    
    
    
    asdfasdf[0]->SetLineColor(kRed);
    asdfasdf[0]->SetFillColor(kRed);
    asdfasdf[1]->SetLineColor(kGreen+1);
    asdfasdf[1]->SetFillColor(kGreen+1);  
    asdfasdf[2]->SetLineColor(kOrange+1);
    asdfasdf[2]->SetFillColor(kOrange+1); 
    asdfasdf[3]->SetLineColor(kMagenta+2);
    asdfasdf[3]->SetFillColor(kMagenta+2);
    asdfasdf[4]->SetLineColor(kBlue);
    asdfasdf[4]->SetFillColor(kBlue);
    
        
    
    sample_hist_all[0]->SetLineColor(kRed);
    //sample_hist_all[0]->SetFillColor(kRed);
    sample_hist_all[1]->SetLineColor(kGreen+1);
    //sample_hist_all[1]->SetFillColor(kGreen+1);    
    sample_hist_all[2]->SetLineColor(kOrange+1);
    //sample_hist_all[2]->SetFillColor(kOrange+1);    
    sample_hist_all[3]->SetLineColor(kMagenta+2);
    //sample_hist_all[3]->SetFillColor(kMagenta+2);
    sample_hist_all[4]->SetLineColor(kBlue);
    //sample_hist_all[4]->SetFillColor(kBlue);
    
    
    sample_hist_mu[0]->SetLineColor(kRed);
    sample_hist_mu[0]->SetFillColor(kRed);
    sample_hist_mu[1]->SetLineColor(kGreen+1);
    sample_hist_mu[1]->SetFillColor(kGreen+1);    
    sample_hist_mu[2]->SetLineColor(kOrange+1);
    sample_hist_mu[2]->SetFillColor(kOrange+1);    
    sample_hist_mu[3]->SetLineColor(kMagenta+2);
    sample_hist_mu[3]->SetFillColor(kMagenta+2);
    sample_hist_mu[4]->SetLineColor(kBlue);
    sample_hist_mu[4]->SetFillColor(kBlue);

    sample_hist_el[0]->SetLineColor(kRed);
    sample_hist_el[0]->SetFillColor(kRed);
    sample_hist_el[1]->SetLineColor(kGreen+1);
    sample_hist_el[1]->SetFillColor(kGreen+1);
    sample_hist_el[2]->SetLineColor(kOrange+1);
    sample_hist_el[2]->SetFillColor(kOrange+1);
    sample_hist_el[3]->SetLineColor(kMagenta+2);
    sample_hist_el[3]->SetFillColor(kMagenta+2);
    sample_hist_el[4]->SetLineColor(kBlue);
    sample_hist_el[4]->SetFillColor(kBlue);


    
//     leg1->AddEntry(sample_hist_all[0],"W->l","L");
//     leg1->AddEntry(sample_hist_all[1],"W->#tau->l","L");
//     leg1->AddEntry(sample_hist_all[2],"H->#tau->l","L");
//     leg1->AddEntry(sample_hist_all[3],"H->Z->l","L");
//     leg1->AddEntry(sample_hist_all[4],"other->l","L");
            
    leg1->AddEntry(sample_hist_mu[0],"W->#mu","F");
    leg1->AddEntry(sample_hist_mu[1],"W->#tau->#mu","F");
    leg1->AddEntry(sample_hist_mu[2],"H->#tau->#mu","F");
    leg1->AddEntry(sample_hist_mu[3],"H->Z->#mu","F");
    leg1->AddEntry(sample_hist_mu[4],"other->#mu","F");
    
//     leg2->AddEntry(asdfasdf[0],"W->e","L");
//     leg2->AddEntry(asdfasdf[1],"W->#tau->e","L");
//     leg2->AddEntry(asdfasdf[2],"H->#tau->e","L");
//     leg2->AddEntry(asdfasdf[3],"H->Z->e","L");
//     leg2->AddEntry(asdfasdf[4],"other->e","L");
        
    
    leg2->AddEntry(sample_hist_el[0],"W->e","F");
    leg2->AddEntry(sample_hist_el[1],"W->#tau->e","F");
    leg2->AddEntry(sample_hist_el[2],"H->#tau->e","F");
    leg2->AddEntry(sample_hist_el[3],"H->Z->e","F");
    leg2->AddEntry(sample_hist_el[4],"other->e","F");
    
    
    sample_2Dhist_mu->GetYaxis()->SetTitle("abs(Grandmother ID)");
    sample_2Dhist_mu->GetXaxis()->SetTitle("abs(Mother ID)");    
    sample_2Dhist_mu->SetTitle("");
    sample_2Dhist_el->GetYaxis()->SetTitle("abs(Grandmother ID)");
    sample_2Dhist_el->GetXaxis()->SetTitle("abs(Mother ID)");
    sample_2Dhist_el->SetTitle("");
    
    
    
    TCanvas *hey1 = new TCanvas("hey1","hey1",150,10,990,660);
    
    nice_stack_mu[0]->Add(sample_hist_mu[0]);
    nice_stack_mu[0]->Add(sample_hist_mu[1]);
    nice_stack_mu[0]->Add(sample_hist_mu[2]);
    nice_stack_mu[0]->Add(sample_hist_mu[3]);
    nice_stack_mu[0]->Add(sample_hist_mu[4]);
    //nice_stack_mu[0]->GetYaxis()->SetRangeUser(0.,4000.);
    nice_stack_mu[0]->Draw("hist");
    
    
    //sample_hist_mu[0]->DrawNormalized("hist");
    //sample_hist_mu[1]->DrawNormalized("hist same");
    //sample_hist_mu[2]->DrawNormalized("hist same");
    //sample_hist_mu[3]->DrawNormalized("hist same");
    //sample_hist_mu[4]->DrawNormalized("hist same");

    //sample_hist_mu[0]->Draw("E0"); // L,X0,E0,E1
    //sample_hist_mu[1]->Draw("same");
    //sample_hist_mu[2]->Draw("same");
    //sample_hist_mu[3]->Draw("same");
    //sample_hist_mu[4]->Draw("same");
    
    // sample_hist_all[1]->Draw("E1"); // L,X0,E0,E1
//     sample_hist_all[3]->Draw("E1,same");
//     sample_hist_all[2]->Draw("E1,same");
//     sample_hist_all[4]->Draw("E1,same");
//     sample_hist_all[0]->Draw("E1,same");
    
    
    leg1->Draw("same");
    //gStyle->SetPalette(56);
    //sample_2Dhist_mu->Draw("COLZ");
    
    TCanvas *hey2 = new TCanvas("hey2","hey2",150,10,990,660);
    
    nice_stack_el[0]->Add(sample_hist_el[0]);
    nice_stack_el[0]->Add(sample_hist_el[1]);
    nice_stack_el[0]->Add(sample_hist_el[2]);
    nice_stack_el[0]->Add(sample_hist_el[3]);
    nice_stack_el[0]->Add(sample_hist_el[4]);
    
    //nice_stack_el[0]->GetYaxis()->SetRangeUser(0.,3000.);
    nice_stack_el[0]->Draw("hist");
    
    //sample_hist_el[0]->DrawNormalized("hist");
    //sample_hist_el[1]->DrawNormalized("hist same");
    //sample_hist_el[2]->DrawNormalized("hist same");
    //sample_hist_el[3]->DrawNormalized("hist same");
    //sample_hist_el[4]->DrawNormalized("hist same");
    
    //sample_hist_el[0]->Draw("E1");
    //sample_hist_el[1]->Draw("E1,same");
    //sample_hist_el[2]->Draw("E1,same");
    //sample_hist_el[3]->Draw("E1,same");
    //sample_hist_el[4]->Draw("E1,same");
    
    
    leg2->Draw("same"); 
    //sample_2Dhist_el->Draw("COLZ");
    
    
}
    
    // Michael:
    
//    TGraphAsymmErrors* eff_HLT_OR_eta_unseeded = new TGraphAsymmErrors();
//eff_HLT_OR_eta_unseeded->BayesDivide(PROBE_HLT_OR_eta_unseeded, TAG_HLT_eta_unseeded);
    
      
            
            
            
