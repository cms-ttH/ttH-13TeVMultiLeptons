
//////////////////////////////////////
////////////  private fns ////////////

void MakeGoodPlot::get_hist_of_simple_variable(TH1 *plot, int sample_number, TH1 *plot2, TH1 *plot3)
{
	
        setBranchAddresses(sample_number);
        
	cout << sample_number << endl;
	cout << ch[sample_number]->GetEntries() << endl;
        
	for (Int_t i=0;i<ch[sample_number]->GetEntries();i++)
	{
		if (i==100000) break;
                
                ch[sample_number]->GetEntry(i);
					
		weight = wgt_intree;		
                                

//                if (passes_2lSS_Andrew(sample_number))
//                {
                

                
                for (const auto & mu : *raw_muons_intree)
                {
                    
                    if (abs(mu.obj.Eta())>2.1) continue; // in eta plateau to measure pt eff.
                    
                    
                    // scan over miniIso cuts:
//                     if ( mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState )
//                     {
//                         
//                             double value = -9.;
//                             
//                             if(mu.miniIso!=0.)
//                             {
//                                 value = log(mu.miniIso);
//                             }
//                             
//                             for (int bin=-8; bin<8; bin++)
//                             {
//                                 if (value<bin && mu.idTightPOG) sample_hist_shared[0]->Fill(bin);
//                                 sample_hist_shared2[0]->Fill(bin);
//                             }
//                         
//                     }
//                     
//                     
//                     if ( !( mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState ) )
//                     {
//                         
//                             double value = -9.;
//                             
//                             if(mu.miniIso!=0.)
//                             {
//                                 value = log(mu.miniIso);
//                             }
//                             
//                             for (int bin=-8; bin<8; bin++)
//                             {
//                                 if (value<bin && mu.idTightPOG) sample_hist_shared[1]->Fill(bin);
//                                 sample_hist_shared2[1]->Fill(bin);
//                             }
//                         
//                     }
                    
                    
                    
                    // regular pt eff. hists:
                    
                    
                    //if ( mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState ) // sample_number!=1 && (!(mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState)) ) )
                    if ( !( mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState ) )
                    {                    
                        

                        
                        if (mu.idLoosePOG)
                        {

                            sample_hist_shared[0]->Fill(min(mu.obj.Pt(),99.9));
                            //sample_hist_shared->Fill(mu.obj.Eta());

                        //}
                        //if (mu.idMediumPOG)
                        if (fabs(mu.dxy < 0.05 ))
                        {

                            sample_hist_shared[1]->Fill(min(mu.obj.Pt(),99.9));
                            //sample_hist_shared->Fill(mu.obj.Eta());

                        }                        
                        //if (mu.idTightPOG)
                        if (fabs(mu.dz < 0.1 ))
                        {

                            sample_hist_shared[2]->Fill(min(mu.obj.Pt(),99.9));
                            //sample_hist_shared->Fill(mu.obj.Eta());

                        }                        
                        //if (mu.isPreselected)
                        //{

                            
                            
                            //if (mu.lepMVA>-0.5)
                            if (mu.sip3D < 8)
                            {
                                sample_hist_shared[3]->Fill(min(mu.obj.Pt(),99.9));
                            }
                                                        
                            //if (mu.lepMVA>0.)
                            if (mu.miniIso < 0.4)
                            {
                                sample_hist_shared[4]->Fill(min(mu.obj.Pt(),99.9));
                            }
                            
                            //if (mu.lepMVA>0.5)
                            if (mu.isPreselected)
                            {
                                sample_hist_shared[5]->Fill(min(mu.obj.Pt(),99.9));
                            }
                            
                            
                        }

                        for (int blah=0; blah<6; blah++) sample_hist_shared2[blah]->Fill(min(mu.obj.Pt(),99.9));
                      
                        
                    }

                }                                                            
                                            
	}

}


void MakeGoodPlot::get_hist_of_simple_variable_2D(int sample_number, int sample_index)
{
	        
        ch[sample_number]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
        ch[sample_number]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
        ch[sample_number]->SetBranchAddress("preselected_muons", &preselected_muons_intree);

        ch[sample_number]->SetBranchAddress("looseMvaBased_leptons", &looseMvaBased_leptons_intree);
        ch[sample_number]->SetBranchAddress("looseMvaBased_electrons", &looseMvaBased_electrons_intree);
        ch[sample_number]->SetBranchAddress("looseMvaBased_muons", &looseMvaBased_muons_intree);

        ch[sample_number]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
        ch[sample_number]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
        ch[sample_number]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);
        
        ch[sample_number]->SetBranchAddress("met", &met_intree);
        
        ch[sample_number]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
        ch[sample_number]->SetBranchAddress( "wgt", &wgt_intree );
        
	cout << sample_number << endl;
	cout << ch[sample_number]->GetEntries() << endl;
	
        int theEntries = ch[sample_number]->GetEntries();
        
	for (Int_t i=0;i<theEntries;i++)
	{
		int catswitch=-1;
                
                ch[sample_number]->GetEntry(i);
	        
                //if (!(i%10000)) cout << i << endl;
                		
		weight = wgt_intree;
                
                double step = 1.25;                
                double lowpt = 0.;
                double highpt = 25.;
                
                int numits = (highpt - lowpt) / step;
                                                                
                //if (!(passes_common(sample_number) && passes_SSee(sample_number))) continue;                
                //if (sample_number==5) weight *= 1.55;
                
//                 switch (catswitch)
//                 {                
//                     case 1: if (!(passes_common(sample_number) && passes_SSee(sample_number))) {continue;} break;   
//                     case 2: if (!(passes_common(sample_number) && passes_SSmumu(sample_number))) {continue;} break;
//                     case 3: if (!(passes_common(sample_number) && passes_SSemu(sample_number))) {continue;} break;
//                     case 4: if (!(passes_common(sample_number) && passes_3l(sample_number))) {continue;} break;
//                     case 5: if (!(passes_common(sample_number) && passes_4l(sample_number))) {continue;} break;
//                 }
                
                if (passes_common(sample_number))
                {
                    if (passes_SSee(sample_number)) catswitch=0;
                    else if (passes_SSmumu(sample_number)) catswitch=1;
                    else if (passes_SSemu(sample_number)) catswitch=2;
                    else if (passes_3l(sample_number)) catswitch=3;
                    else if (passes_4l(sample_number)) catswitch=4;
                }
                
                
                if (catswitch>-1)
                {
                    
                    if (sample_number==5) // ttjets
                    {
                        switch (catswitch)
                        {
                            case 0: weight *= 1.55; break;
                            case 1: weight *= 3.3; break;
                            case 2: weight *= 1.87; break;
                            case 3: weight *= 2.85; break;
                            case 4: break;
                        }
                    }
                    
                    
                    double ptcutx = 0.;

                    for (int i=0; i<=numits; i++)
                    {
                        double ptcuty = 0.;

                        for (int j=0; j<=numits; j++)
                        {                
                            if ((*preselected_leptons_intree).size()>1)
                            {                        
                                
                                if (catswitch<3 && (*tightMvaBased_leptons_intree).size()==2 && (*looseMvaBased_leptons_intree).size()<4)
                                {                                                                
                                    if ( ((*tightMvaBased_leptons_intree)[0].obj.Pt()>ptcutx) && ((*tightMvaBased_leptons_intree)[1].obj.Pt()>ptcuty) )
                                    {                                
                                        mgp_sample_hist_2D[sample_index][catswitch]->Fill(ptcutx,ptcuty,weight);
                                    }
                                }
                                
                                if (catswitch==3 && (*tightMvaBased_leptons_intree).size()==3 && (*looseMvaBased_leptons_intree).size()<4)
                                {
                                    if ( ((*tightMvaBased_leptons_intree)[0].obj.Pt()>ptcutx) && ((*tightMvaBased_leptons_intree)[1].obj.Pt()>ptcuty) )
                                    {                                
                                        mgp_sample_hist_2D[sample_index][catswitch]->Fill(ptcutx,ptcuty,weight);
                                    }
                                
                                }
                                
                                if (catswitch==4 && (*looseMvaBased_leptons_intree).size()==4)
                                {
                                    if ( ((*looseMvaBased_leptons_intree)[0].obj.Pt()>ptcutx) && ((*looseMvaBased_leptons_intree)[1].obj.Pt()>ptcuty) )
                                    {                                
                                        mgp_sample_hist_2D[sample_index][catswitch]->Fill(ptcutx,ptcuty,weight);
                                    }
                                
                                
                                }
                            }

                            ptcuty += step;

                        }

                        ptcutx += step;
                    }
                }
                
                

	}

}
