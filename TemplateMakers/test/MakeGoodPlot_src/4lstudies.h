void MakeGoodPlot::fourlstudies(std::vector<int> samps) // really only one sample at a time (just easier to copy and paste existing code ..)
{
    bool debug = false;
    int numsamples = samps.size();		
    load_samples(samps);
    
	TH1D *higgsmass = new TH1D("higgsmass","higgsmass",100,0,400);
	TH1D *njets = new TH1D("njets","njets",50,0,50);
    TH1D *MET = new TH1D("MET","MET",100,0,400);
    TH1D *findtheZ = new TH1D("findtheZ","findtheZ",200,0,200);
        
    TH1D *higgsmass1 = new TH1D("higgsmass1","higgsmass1",100,0,400);
    TH1D *higgsmass2 = new TH1D("higgsmass2","higgsmass2",100,0,400);
    
    TH1D *higgsmassblah[20];
    
	THStack *nice_stack_mu = new THStack("stack1",";inv mass (4l)");
        
    TLegend* leg1 = new TLegend(0.11,0.91,0.89,0.99); // above the plot

    leg1->SetFillColor(kWhite);
    leg1->SetLineColor(kWhite);
    leg1->SetShadowColor(kWhite);
    leg1->SetTextFont(42);
    //leg->SetTextSize(0.035);
    leg1->SetNColumns(7);
        
    double preselcounter = 0.;
    double tightcounter = 0.;
    
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
         ch[samp_int]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
         ch[samp_int]->SetBranchAddress("met", &met_intree);
		

        
        int theEntries = ch[samp_int]->GetEntries();
        cout << theEntries << endl;
        
        higgsmassblah[samp_int] = new TH1D("higgsmass_"+int2ss(samp_int),";4l inv mass",100,0,400);
        
        if (samp_int==1) higgsmassblah[samp_int]->SetFillColor(kRed); // ttH
		if (samp_int==5) higgsmassblah[samp_int]->SetFillColor(kBlue); // ttjets
		if (samp_int==6) higgsmassblah[samp_int]->SetFillColor(kGreen+1); // zjets
		if (samp_int==7) higgsmassblah[samp_int]->SetFillColor(kOrange+1); //wjets
		if (samp_int==8) higgsmassblah[samp_int]->SetFillColor(kMagenta+1); //ttw
		if (samp_int==9) higgsmassblah[samp_int]->SetFillColor(kCyan-3); //ttz
		if (samp_int==10) higgsmassblah[samp_int]->SetFillColor(kBlue-6); // diboson
		
		leg1->AddEntry(higgsmassblah[samp_int],sample_names[samp_int],"F");
		
        for (int j=0;j<theEntries;j++)
        {

            ch[samp_int]->GetEntry(j);
				
            weight = wgt_intree; 
            
            int nummus = (*preselected_muons_intree).size();
            int numeles = (*preselected_electrons_intree).size();
            
            int nummusloose = (*looseMvaBased_muons_intree).size();
            int numelesloose = (*looseMvaBased_electrons_intree).size();
            
            int nummustight = (*tightMvaBased_muons_intree).size();
            int numelestight = (*tightMvaBased_electrons_intree).size();
            
            int numlepsloose = (*looseMvaBased_leptons_intree).size();
            
            int numlepstight = nummustight + numelestight;
            
            bool breakitoff = false;
            
            for (int k=0; k<(nummus + numeles); k++)
            {
            	if ( !( abs((*preselected_leptons_intree)[k].genMotherPdgID)==23 && abs((*preselected_leptons_intree)[k].genGrandMotherPdgID)==25 ) ) breakitoff=true;
            }          
            
            //if (breakitoff) continue;
        	
            if ( (nummus + numeles)==4 )
            {				
		        if ( ((*preselected_leptons_intree)[0].charge + (*preselected_leptons_intree)[1].charge + (*preselected_leptons_intree)[2].charge + (*preselected_leptons_intree)[3].charge)==0 )
        		{
				//if ( (*preselected_leptons_intree)[0].miniIso<0.4 + (*preselected_leptons_intree)[1].miniIso<0.4 + (*preselected_leptons_intree)[2].miniIso<0.4 + (*preselected_leptons_intree)[3].miniIso<0.4)
        			//{
						
                                    //if ((*met_intree)[0].obj.Pt()<60.)
                                    //{
                                                auto fourlobject = getsumTLV(*preselected_leptons_intree);
						double hm = fourlobject.M();
						if ( hm<130. && hm>118.) njets->Fill((*preselected_jets_intree).size(),weight);
                                                MET->Fill((*met_intree)[0].obj.Pt(),weight);
                                                
                                                
                                                bool foundtheZ=false;
                                                
                                                if (nummus==2 && numeles==2)
                                                {
                                                    auto muobj = getsumTLV(*preselected_muons_intree);
                                                    auto eleobj = getsumTLV(*preselected_electrons_intree);
                                                    findtheZ->Fill(muobj.M());
                                                    findtheZ->Fill(eleobj.M());
                                                    
                                                    if (fabs(muobj.M())<95. && fabs(muobj.M())>85.) foundtheZ=true;
                                                    if (fabs(eleobj.M())<95. && fabs(eleobj.M())>85.) foundtheZ=true;
                                                    
                                                }
                                                if (nummus==4 && numeles==0)
                                                {
                                                    
                                                    vector<int> poschgs;
                                                    vector<int> negchgs;
                                                    
                                                    for (int k=0; k<4; k++)
                                                    {
                                                        if ((*preselected_muons_intree)[k].charge<-0.0001) negchgs.push_back(k);
                                                        else poschgs.push_back(k);
                                                    }
                                                    
                                                    for (int k=0; k<3; k++)
                                                    {
                                                        for (int kk=(k+1); kk<4; kk++)
                                                        {
                                                        
                                                            if ( ((*preselected_muons_intree)[k].charge+(*preselected_muons_intree)[kk].charge)==0)
                                                            {
                                                                
                                                                auto muobj = (*preselected_muons_intree)[k].obj;
                                                                muobj += (*preselected_muons_intree)[kk].obj;
                                                                
                                                                findtheZ->Fill(muobj.M());
                                                                if (fabs(muobj.M())<95. && fabs(muobj.M())>85.) foundtheZ=true;
                                                                
                                                            
                                                            }                                                           
                                                            
                                                        }
                                                        
                                                    }
                                                    
                                                    
                                                }
                                                if (nummus==0 && numeles==4)
                                                {
                                                    
                                                    vector<int> poschgs;
                                                    vector<int> negchgs;
                                                    
                                                    for (int k=0; k<4; k++)
                                                    {
                                                        if ((*preselected_electrons_intree)[k].charge<-0.0001) negchgs.push_back(k);
                                                        else poschgs.push_back(k);
                                                    }
                                                    
                                                    for (int k=0; k<3; k++)
                                                    {
                                                        for (int kk=(k+1); kk<4; kk++)
                                                        {
                                                        
                                                            if ( ((*preselected_electrons_intree)[k].charge+(*preselected_electrons_intree)[kk].charge)==0)
                                                            {
                                                                
                                                                auto eleobj = (*preselected_electrons_intree)[k].obj;
                                                                eleobj += (*preselected_electrons_intree)[kk].obj;
                                                                
                                                                findtheZ->Fill(eleobj.M());
                                                                if (fabs(eleobj.M())<95. && fabs(eleobj.M())>85.) foundtheZ=true;
                                                                
                                                            }                                                           
                                                            
                                                        }
                                                        
                                                    }
                                                    
                                                    
                                                    
                                                    
                                                    
                                                }
                                                
                                                if (foundtheZ)
                                                {
                                                    higgsmass->Fill(hm); //,weight);
                                                    higgsmassblah[samp_int]->Fill(hm); // weight);
                                                    if (breakitoff) higgsmass1->Fill(hm,weight);
                                                    if (!breakitoff) higgsmass2->Fill(hm,weight);
                                                }
                                                
                                                
                                                
                                    //}
				
                                //}
			}
			
			
			
			
	    }
            
            if ( (nummus + numeles)>=2 && numlepstight>=1)
            {
            
                if ((*preselected_leptons_intree)[0].miniIso<0.4 && (*preselected_leptons_intree)[1].miniIso<0.4 && (*tightMvaBased_leptons_intree)[0].miniIso<0.4)
                {
            

            
                
                    //for (int k=0; k<(nummus + numeles); k++)
                    //{

                        if ( (*preselected_leptons_intree)[1].miniIso<0.4 && (
                        abs((*preselected_leptons_intree)[1].genMotherPdgID)==24
                        || (abs((*preselected_leptons_intree)[1].genMotherPdgID)==15 && abs((*preselected_leptons_intree)[1].genGrandMotherPdgID)==24)
                        || (abs((*preselected_leptons_intree)[1].genMotherPdgID)==15 && abs((*preselected_leptons_intree)[1].genGrandMotherPdgID)==25)
                        || (abs((*preselected_leptons_intree)[1].genMotherPdgID)==23 && abs((*preselected_leptons_intree)[1].genGrandMotherPdgID)==25) ) )
                        {

                            preselcounter += weight;
                        }

                    //}

            
                    if ( numlepstight>=2 )
                    {

                        //if ((*tightMvaBased_leptons_intree)[1].miniIso<0.4)
                        //{
                        
                        
                            //for (int k=0; k<numlepstight; k++)
                            //{

                                if ( /*(*tightMvaBased_leptons_intree)[1].miniIso<0.4 &&*/ (
                                abs((*tightMvaBased_leptons_intree)[1].genMotherPdgID)==24
                                || (abs((*tightMvaBased_leptons_intree)[1].genMotherPdgID)==15 && abs((*tightMvaBased_leptons_intree)[1].genGrandMotherPdgID)==24)
                                || (abs((*tightMvaBased_leptons_intree)[1].genMotherPdgID)==15 && abs((*tightMvaBased_leptons_intree)[1].genGrandMotherPdgID)==25)
                                || (abs((*tightMvaBased_leptons_intree)[1].genMotherPdgID)==23 && abs((*tightMvaBased_leptons_intree)[1].genGrandMotherPdgID)==25) ) )
                                {

                                    tightcounter += weight;
                                }



                            //}
                    
                        //}
                    
                    }
            
            
                }
            }
		
	}
	
	higgsmassblah[samp_int]->Scale( 10000. * xsecs[samp_int] / numgen[samp_int] );
	nice_stack_mu->Add(higgsmassblah[samp_int]);
	
    }

    //higgsmass->Draw("hist");
    //njets->Draw();
    //MET->Draw();
    //findtheZ->Draw();
    
    higgsmass1->SetLineColor(kRed);
    higgsmass1->SetFillColor(kRed);
    higgsmass2->SetLineColor(kGreen+1);
    higgsmass2->SetFillColor(kGreen+1);
        
    
    //leg1->AddEntry(higgsmass1,"H->non-ZZ","F");
    //leg1->AddEntry(higgsmass2,"H->ZZ","F");
    
    //nice_stack_mu->Add(higgsmass1);
    //nice_stack_mu->Add(higgsmass2);
     
    
    nice_stack_mu->Draw("hist");
    leg1->Draw("same");
    
    
    cout << preselcounter << endl;
    cout << tightcounter << endl;
    
    


}
                            
                
