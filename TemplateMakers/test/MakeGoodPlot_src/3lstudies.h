void MakeGoodPlot::threelstudies(std::vector<int> samps) // really only one sample at a time (just easier to copy and paste existing code ..)
{
    bool debug = false;
    int numsamples = samps.size();		
    load_samples(samps);
    
    TH1D *higgsmass = new TH1D("higgsmass","higgsmass",100,0,400);
    TH1D *njets[5];
    for (int aaaaaa=0; aaaaaa<5; aaaaaa++) njets[aaaaaa] = new TH1D("njets"+int2ss(aaaaaa),";njets",50,0,50);
    TH1D *MET = new TH1D("MET","MET",100,0,400);
    TH1D *findtheZ = new TH1D("findtheZ","findtheZ",200,0,200);
    TH1D *nbjets = new TH1D("nbjets","nbjets",50,0,50);
    TH1D *jetcsv = new TH1D("jetcsv","jetcsv",50,-1,1);
    
    TH1D *asdf = new TH1D("asdf","asdf",100,0,200);
    
    TLegend* leg1 = new TLegend(0.11,0.91,0.89,0.99); // above the plot

    leg1->SetFillColor(kWhite);
    leg1->SetLineColor(kWhite);
    leg1->SetShadowColor(kWhite);
    leg1->SetTextFont(42);
    //leg->SetTextSize(0.035);
    leg1->SetNColumns(7);
    
    

    
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
            
            int numleps = nummus + numeles;
            int numlepsloose = nummusloose + numelesloose;
            int numlepstight = nummustight + numelestight;
            int numjets = (*preselected_jets_intree).size();
            
            
            bool breakitoff = true;
            
            for (int k=0; k<numleps; k++)
            {
            	if ( abs((*preselected_leptons_intree)[k].genMotherPdgID)==15 && abs((*preselected_leptons_intree)[k].genGrandMotherPdgID)==25 ) breakitoff=false;
            }          
            
            //if (breakitoff) continue;
            
            
            auto lfjets = keepUnTagged(*preselected_jets_intree,"M");
            auto hfjets = keepTagged(*preselected_jets_intree,"M");
            
            int numlfjets = lfjets.size();
            int numhfjets = hfjets.size();
            
            //njets->Fill(numlfjets);
            //nbjets->Fill(numhfjets);
            
            for (int k=0; k<numjets; k++) { jetcsv->Fill((*preselected_jets_intree)[k].csv); }
            
            //if (!( numhfjets==2 && numlfjets==2 )) continue;
            
            bool gotZ = false;
            
            if ( numleps==3 )
            {				

                auto muobj = getsumTLV(*preselected_muons_intree);
                auto eleobj = getsumTLV(*preselected_electrons_intree);

                if (nummus==2 && fabs(muobj.M())<95. && fabs(muobj.M())>85.) gotZ=true;
                if (numeles==2 && fabs(eleobj.M())<95. && fabs(eleobj.M())>85.) gotZ=true;

                if (!gotZ) continue;
                
                if ( !((*preselected_leptons_intree)[0].miniIso<0.4 && (*preselected_leptons_intree)[1].miniIso<0.4 && (*preselected_leptons_intree)[2].miniIso<0.4) ) continue;
                
                if ( !((*preselected_leptons_intree)[0].lepMVA>0.7 && (*preselected_leptons_intree)[1].lepMVA>0.7 && (*preselected_leptons_intree)[2].lepMVA>0.7) ) continue;
                
                //double vetoZmassSFOS = pickFromSortedTwoObjKine(*tightMvaBased_leptons_intree,"massSFOS",1,91.2);

                //if (fabs(vetoZmassSFOS-91.2)<=10.) continue;                     

                
                
                double chosenmass = 0.;
                int rec_k = -1;
                int rec_kk= -1;
                
                //auto jetobj = lfjets[0].obj;
                //jetobj += lfjets[1].obj;
                //findtheZ->Fill(jetobj.M());
                
                njets[i]->Fill(numlfjets+numhfjets);
                nbjets->Fill(numhfjets);    
                

                
                if ( (*preselected_leptons_intree)[0].charge != (*preselected_leptons_intree)[1].charge)             
                {
                    auto oslepobj = (*preselected_leptons_intree)[0].obj;
                    oslepobj += (*preselected_leptons_intree)[1].obj;                    
                    asdf->Fill(oslepobj.M(),weight);
                }
                if ( (*preselected_leptons_intree)[0].charge != (*preselected_leptons_intree)[2].charge)
                {
                    auto oslepobj = (*preselected_leptons_intree)[0].obj;
                    oslepobj += (*preselected_leptons_intree)[2].obj;                    
                    asdf->Fill(oslepobj.M(),weight);
                }
                if ( (*preselected_leptons_intree)[1].charge != (*preselected_leptons_intree)[2].charge)
                {
                    auto oslepobj = (*preselected_leptons_intree)[1].obj;
                    oslepobj += (*preselected_leptons_intree)[2].obj;                    
                    asdf->Fill(oslepobj.M(),weight); 
                    
                }
                for (int k=0; k<(numlfjets-1); k++)
                {
                    for (int kk=k+1; kk<numlfjets; kk++)
                    {
                        for (int kkk=0; kkk<numhfjets; kkk++)
                        {
                            //auto jetobj = (*preselected_jets_intree)[k].obj;
                            //jetobj += (*preselected_jets_intree)[kk].obj;

                            auto jetobj = lfjets[k].obj;
                            jetobj += lfjets[kk].obj;
                            jetobj += hfjets[kkk].obj;

                            //findtheZ->Fill(jetobj.M());

                            double testmass = jetobj.M();

                            if (fabs(175. - testmass) < fabs(175. - chosenmass))
                            {
                                chosenmass = testmass;
                                rec_k = k;
                                rec_kk= kk;                 
                            }
                        }
                    }
                }
                
                for (int k=0; k<(numlfjets-1); k++)
                {
                    for (int kk=k+1; kk<numlfjets; kk++)
                    {
                    
                        if (!( k!=rec_k && kk!=rec_kk ))
                        {
                            auto jetobj = lfjets[k].obj;
                            jetobj += lfjets[kk].obj;
                            findtheZ->Fill(jetobj.M());
                        }
                    }
                }

                
            }
	}	
	
    }	
    
    //jetcsv->Draw();	
    njets[0]->DrawNormalized();
    njets[1]->DrawNormalized("same");
    njets[2]->DrawNormalized("same");
    njets[3]->DrawNormalized("same");
    
    
    
    //nbjets->Draw("same");
    //findtheZ->Draw();
    //asdf->Draw();

}
                            
                
