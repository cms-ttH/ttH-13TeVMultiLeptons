void MakeGoodPlot::print_cutflow(std::vector<int> samps)
{
    int numsamples = samps.size();

    load_samples(samps);

    vstring commoncuts_str;
    vstring ss_2e_cuts_str;
    vstring ss_2mu_cuts_str;
    vstring ss_emu_cuts_str;
    vstring threel_cuts_str;
    vstring fourl_cuts_str;
    
    // common cuts
    commoncuts_str.push_back(">=2 T lep or >=4 PS lep");
    commoncuts_str.push_back("minDilepMass>12");
    commoncuts_str.push_back("PS lep pt >20, >10");
    commoncuts_str.push_back("nJets>=2 (25GeV)");
    commoncuts_str.push_back(">=2 L bjets or >=1 M bjet");
    
    // ss
    ss_2e_cuts_str.push_back("2 tight eles");
    ss_2e_cuts_str.push_back("ss");
    ss_2e_cuts_str.push_back(">=4 jets");
    ss_2e_cuts_str.push_back("metLD>0.2");
    ss_2e_cuts_str.push_back("lep pt >20, >20");
    ss_2e_cuts_str.push_back("leppt1+leppt2+met>100");
    ss_2e_cuts_str.push_back("ee_Zveto");
    ss_2e_cuts_str.push_back("isGsfCtfScPixChargeConsistent (x2)");
        
    ss_emu_cuts_str.push_back("1 tight ele, 1 tight mu");
    ss_emu_cuts_str.push_back("ss");
    ss_emu_cuts_str.push_back(">=4 jets");
    ss_emu_cuts_str.push_back("metLD>0.2");
    ss_emu_cuts_str.push_back("lep pt >20, >20");
    ss_emu_cuts_str.push_back("leppt1+leppt2+met>100");
    ss_emu_cuts_str.push_back("chargeFlip+isGsfCtfScPixChargeConsistent");
        
    ss_2mu_cuts_str.push_back("2 tight mu");
    ss_2mu_cuts_str.push_back("ss");
    ss_2mu_cuts_str.push_back(">=4 jets");
    ss_2mu_cuts_str.push_back("metLD>0.2");
    ss_2mu_cuts_str.push_back("lep pt >20, >20");
    ss_2mu_cuts_str.push_back("leppt1+leppt2+met>100");
    ss_2mu_cuts_str.push_back("chargeFlip (x2)");
    
    // 3l
    threel_cuts_str.push_back("3 tight lep");
    threel_cuts_str.push_back(">=4 jets, or metLD>0.2");
    threel_cuts_str.push_back("SFOS Zveto");
    threel_cuts_str.push_back("2 T leps ss");
    
    // 4l    
    fourl_cuts_str.push_back("4 loose lep");
    fourl_cuts_str.push_back("neutral");
    fourl_cuts_str.push_back("SFOS Zveto");
     
//     double commoncuts[commoncuts_str.size()] = {};
//     double ss_2e_cuts[ss_2e_cuts_str.size()] = {};
//     double ss_2mu_cuts[ss_2mu_cuts_str.size()] = {};
//     double ss_emu_cuts[ss_emu_cuts_str.size()] = {};
//     double threel_cuts[threel_cuts_str.size()] = {};
//     double fourl_cuts[fourl_cuts_str.size()] = {};
//     annoying ...

    double commoncuts[20][20][6] = {{{}}};
    double ss_2e_cuts[20][20][6] = {{{}}};
    double ss_2mu_cuts[20][20][6] = {{{}}};
    double ss_emu_cuts[20][20][6] = {{{}}};
    double threel_cuts[20][20][6] = {{{}}};
    double fourl_cuts[20][20][6] = {{{}}};
    
    
    vstring ttHdecaystudy_str;
    ttHdecaystudy_str.push_back("H->bb");
    ttHdecaystudy_str.push_back("H->WW");
    ttHdecaystudy_str.push_back("H->tautau");
    ttHdecaystudy_str.push_back("H->ZZ");
    ttHdecaystudy_str.push_back("H->other");    
    ttHdecaystudy_str.push_back("no gen info");
    
    
    for (int i=0; i<numsamples; i++)
    {	
	int samp_int = samps[i];

	cout << "doing " << sample_names[samp_int] << endl;
        
        int samp_num_entries = ch[samp_int]->GetEntries();
        
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
        //ch[samp_int]->SetBranchAddress("loose_bJets", &loose_bJets_intree);
        //ch[samp_int]->SetBranchAddress("tight_bJets", &tight_bJets_intree);
        ch[samp_int]->SetBranchAddress("met", &met_intree);
        ch[samp_int]->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree); //<-


        for (Int_t j=0; j<samp_num_entries; j++)
        {
            ch[samp_int]->GetEntry(j);
        
            if (!(j % 100000)) cout << j << endl;
            // H decay studies
                        
            int gpsize = (*pruned_genParticles_intree).size();            
            int thechildpdgid = 0;         
            int hdecayindex = 0;
            
            
            //if (wgt_intree<0.0) continue;
            //if (wgt_intree>=0) continue;
                        
            
            for (int j=0; j<gpsize; j++)
            {
                int chil0 = (int)(*pruned_genParticles_intree)[j].child0;
                int chil1 = (int)(*pruned_genParticles_intree)[j].child1;
                // note: I don't think these are supposed to be status=62, but that is the only thing saved in the trees...
                if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil0<gpsize) && (*pruned_genParticles_intree)[j].status==62) thechildpdgid = (*pruned_genParticles_intree)[(*pruned_genParticles_intree)[j].child0].pdgID;
                else if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil1<gpsize) && (*pruned_genParticles_intree)[j].status==62) thechildpdgid = (*pruned_genParticles_intree)[(*pruned_genParticles_intree)[j].child1].pdgID;
            }
            
            if (abs(thechildpdgid)==0) hdecayindex = 5;
                       
            if (abs(thechildpdgid)!=0)
            {
                if (abs(thechildpdgid)==5) hdecayindex = 0;
                else if (abs(thechildpdgid)==24) hdecayindex = 1;
                else if (abs(thechildpdgid)==15) hdecayindex = 2;
                else if (abs(thechildpdgid)==23) hdecayindex = 3;
                else hdecayindex = 4;
            }
            
            
            // common
            auto tight_bJets_intree2 = keepTagged(*preselected_jets_intree,"M");
            auto loose_bJets_intree2 = keepUnTagged(*preselected_jets_intree,"L");
            
            if (!(((*preselected_leptons_intree).size()>3) || ((*tightMvaBased_leptons_intree).size()>1))) continue;                
            commoncuts[0][samp_int][hdecayindex] += wgt_intree;        

            double mindilepmass = getTwoObjKineExtreme(*preselected_leptons_intree,"min","mass");        
            if (!(mindilepmass>12)) continue;                
            commoncuts[1][samp_int][hdecayindex] += wgt_intree;       

            if (!((*preselected_leptons_intree)[0].obj.Pt()>20 && (*preselected_leptons_intree)[1].obj.Pt()>10)) continue;        
            commoncuts[2][samp_int][hdecayindex] += wgt_intree;

            if (!((*preselected_jets_intree).size()>1)) continue;
            commoncuts[3][samp_int][hdecayindex] += wgt_intree;

            if (!((loose_bJets_intree2.size()>1) || (tight_bJets_intree2.size()>0))) continue;
            commoncuts[4][samp_int][hdecayindex] += wgt_intree;

            // 2e

            //if ( ((*tightMvaBased_electrons_intree).size()==2) && ((*tightMvaBased_muons_intree).size()==0) && ((*loose_leptons_intree).size()<4) ) 
            if ( ((*tightMvaBased_electrons_intree).size()==2) && ((*tightMvaBased_muons_intree).size()==0) && ((*loose_leptons_intree).size()==2) && ((*preselected_leptons_intree).size()==2) )
            {
                //if (samp_int==5) wgt_intree *= 1.55; //ttjets
                ss_2e_cuts[0][samp_int][hdecayindex] += wgt_intree;

                if ((*tightMvaBased_electrons_intree)[0].charge==(*tightMvaBased_electrons_intree)[1].charge)
                {
                    ss_2e_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    if ((*preselected_jets_intree).size()>3)
                    {
                        ss_2e_cuts[2][samp_int][hdecayindex] += wgt_intree;

                        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                        double MHT_handle = objs_for_mht.Pt();
                        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                        if (metLD_handle> 0.2)
                        {
                            ss_2e_cuts[3][samp_int][hdecayindex] += wgt_intree;

                            if ((*tightMvaBased_electrons_intree)[0].obj.Pt()>20 && (*tightMvaBased_electrons_intree)[1].obj.Pt()>20)
                            {
                                ss_2e_cuts[4][samp_int][hdecayindex] += wgt_intree;

                                if (((*tightMvaBased_electrons_intree)[0].obj.Pt() + (*tightMvaBased_electrons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                                {
                                    ss_2e_cuts[5][samp_int][hdecayindex] += wgt_intree;

                                    double vetoZmass = pickFromSortedTwoObjKine(*preselected_electrons_intree,"mass",1,91.2);

                                    if (fabs(vetoZmass-91.2)>10)                     
                                    {
                                        ss_2e_cuts[6][samp_int][hdecayindex] += wgt_intree;

                                        if ((*tightMvaBased_electrons_intree)[0].isGsfCtfScPixChargeConsistent && (*tightMvaBased_electrons_intree)[1].isGsfCtfScPixChargeConsistent)
                                        {
                                            ss_2e_cuts[7][samp_int][hdecayindex] += wgt_intree;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // 2 mu

            //if ( ((*tightMvaBased_electrons_intree).size()==0) && ((*tightMvaBased_muons_intree).size()==2) && ((*loose_leptons_intree).size()<4) ) 
            if ( ((*tightMvaBased_electrons_intree).size()==0) && ((*tightMvaBased_muons_intree).size()==2) && ((*loose_leptons_intree).size()==2) && ((*preselected_leptons_intree).size()==2) )
            {
                //if (samp_int==5) wgt_intree *= 3.3; //ttjets
                ss_2mu_cuts[0][samp_int][hdecayindex] += wgt_intree;

                if ((*tightMvaBased_muons_intree)[0].charge==(*tightMvaBased_muons_intree)[1].charge)
                {
                    ss_2mu_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    if ((*preselected_jets_intree).size()>3)
                    {
                        ss_2mu_cuts[2][samp_int][hdecayindex] += wgt_intree;

                        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                        double MHT_handle = objs_for_mht.Pt();
                        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                        if (metLD_handle> 0.2)
                        {
                            ss_2mu_cuts[3][samp_int][hdecayindex] += wgt_intree;

                            if ((*tightMvaBased_muons_intree)[0].obj.Pt()>20 && (*tightMvaBased_muons_intree)[1].obj.Pt()>20)
                            {
                                ss_2mu_cuts[4][samp_int][hdecayindex] += wgt_intree;

                                if (((*tightMvaBased_muons_intree)[0].obj.Pt() + (*tightMvaBased_muons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                                {
                                    ss_2mu_cuts[5][samp_int][hdecayindex] += wgt_intree;

                                    if ((*tightMvaBased_muons_intree)[0].chargeFlip<0.2 && (*tightMvaBased_muons_intree)[1].chargeFlip<0.2)
                                    {                                    
                                        ss_2mu_cuts[6][samp_int][hdecayindex] += wgt_intree;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        
            // 1 mu, 1 ele
            
            //if ( ((*tightMvaBased_electrons_intree).size()==1) && ((*tightMvaBased_muons_intree).size()==1) && ((*loose_leptons_intree).size()<4) ) 
            if ( ((*tightMvaBased_electrons_intree).size()==1) && ((*tightMvaBased_muons_intree).size()==1) && ((*loose_leptons_intree).size()==2) && ((*preselected_leptons_intree).size()==2) )
            {
                //if (samp_int==5) wgt_intree *= 1.87; //ttjets
                ss_emu_cuts[0][samp_int][hdecayindex] += wgt_intree;

                if ((*tightMvaBased_electrons_intree)[0].charge==(*tightMvaBased_muons_intree)[0].charge)
                {
                    ss_emu_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    if ((*preselected_jets_intree).size()>3)
                    {
                        ss_emu_cuts[2][samp_int][hdecayindex] += wgt_intree;

                        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                        double MHT_handle = objs_for_mht.Pt();
                        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                        if (metLD_handle> 0.2)
                        {
                            ss_emu_cuts[3][samp_int][hdecayindex] += wgt_intree;

                            if ((*tightMvaBased_muons_intree)[0].obj.Pt()>20 && (*tightMvaBased_electrons_intree)[0].obj.Pt()>20)
                            {
                                ss_emu_cuts[4][samp_int][hdecayindex] += wgt_intree;

                                if (((*tightMvaBased_muons_intree)[0].obj.Pt() + (*tightMvaBased_electrons_intree)[0].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                                {
                                    ss_emu_cuts[5][samp_int][hdecayindex] += wgt_intree;

                                    if ((*tightMvaBased_muons_intree)[0].chargeFlip<0.2 && (*tightMvaBased_electrons_intree)[0].isGsfCtfScPixChargeConsistent)
                                    {                                    
                                        ss_emu_cuts[6][samp_int][hdecayindex] += wgt_intree;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
            // 3l
            
            //if ( ((*tightMvaBased_leptons_intree).size()==3) && ((*loose_leptons_intree).size()<4) ) 
            if ( ((*tightMvaBased_leptons_intree).size()==3) && ((*loose_leptons_intree).size()==3) && ((*preselected_leptons_intree).size()==3) )
            {
                //if (samp_int==5) wgt_intree *= 2.85; //ttjets
                threel_cuts[0][samp_int][hdecayindex] += wgt_intree;

                auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                double MHT_handle = objs_for_mht.Pt();
                double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                if ((metLD_handle>0.2) || ((*preselected_jets_intree).size()>3))
                {
                    threel_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    double vetoZmassSFOS = pickFromSortedTwoObjKine(*tightMvaBased_leptons_intree,"massSFOS",1,91.2);

                    if (fabs(vetoZmassSFOS-91.2)>10.)                     
                    {        
                          threel_cuts[2][samp_int][hdecayindex] += wgt_intree;  
                            
                    }
                }
            }
            
            // 4l
            
            if ((*loose_leptons_intree).size()==4 && ((*preselected_leptons_intree).size()==4) )
            {
                fourl_cuts[0][samp_int][hdecayindex] += wgt_intree;

                if ( ((*loose_leptons_intree)[0].charge + (*loose_leptons_intree)[1].charge + (*loose_leptons_intree)[2].charge + (*loose_leptons_intree)[3].charge)==0 )
                {
                    fourl_cuts[1][samp_int][hdecayindex] += wgt_intree;

                    double vetoZmassSFOS = pickFromSortedTwoObjKine(*loose_leptons_intree,"massSFOS",1,91.2);

                    if (fabs(vetoZmassSFOS-91.2)>10.)                     
                    {        
                          fourl_cuts[2][samp_int][hdecayindex] += wgt_intree;  
                            
                    }
                }
            }
            
            
//             // 3l test
//             
//             if ( ((*tightMvaBased_leptons_intree).size()>=2) && ((*preselected_leptons_intree).size()==3) ) 
//             {
//                 if (samp_int==5) wgt_intree *= 2.85; //ttjets
//                 threel_cuts[0][samp_int][hdecayindex] += wgt_intree;
// 
//                 auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
//                 double MHT_handle = objs_for_mht.Pt();
//                 double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;
// 
//                 if ((metLD_handle>0.2) || ((*preselected_jets_intree).size()>3))
//                 {
//                     threel_cuts[1][samp_int][hdecayindex] += wgt_intree;
// 
//                     double vetoZmassSFOS = pickFromSortedTwoObjKine(*preselected_leptons_intree,"massSFOS",1,91.2);
// 
//                     if (fabs(vetoZmassSFOS-91.2)>10.)                     
//                     {        
//                           threel_cuts[2][samp_int][hdecayindex] += wgt_intree;
//                           
//                           if ( (*tightMvaBased_leptons_intree)[0].charge==(*tightMvaBased_leptons_intree)[1].charge )
//                           {
//                                 
//                             threel_cuts[3][samp_int][hdecayindex] += wgt_intree;
//                           }
//                           
//                     }
//                 }
//             }
//             
//            
//             
//             
//             // 4l test
//             
//             if ((*tightMvaBased_leptons_intree).size()>=2 && (*preselected_leptons_intree).size()==4)
//             {
//                 fourl_cuts[0][samp_int][hdecayindex] += wgt_intree;
// 
//                 if ( ((*preselected_leptons_intree)[0].charge + (*preselected_leptons_intree)[1].charge + (*preselected_leptons_intree)[2].charge + (*preselected_leptons_intree)[3].charge)==0 && ((*tightMvaBased_leptons_intree)[0].charge==(*tightMvaBased_leptons_intree)[1].charge) )
//                 {
//                     fourl_cuts[1][samp_int][hdecayindex] += wgt_intree;
// 
//                     double vetoZmassSFOS = pickFromSortedTwoObjKine(*preselected_leptons_intree,"massSFOS",1,91.2);
// 
//                     if (fabs(vetoZmassSFOS-91.2)>10.)                     
//                     {        
//                           fourl_cuts[2][samp_int][hdecayindex] += wgt_intree;  
//                             
//                     }
//                 }
//             }
//             
            
            
            
            
            
            
            
       
                                  
        } // end event loop
    } // end sample loop 


///////////////////////////////////////////////////////////////////////////////////////////////
        
        // cut flow with h decay study:    
        
        
    cout << " " << endl;
    cout << " " << endl;
    cout << "raw mc" << endl;
    cout << " " << endl;
    

    cout << "common" << endl;
    cout << " " << endl;        
    printf ("%40s","cut");
    for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
    printf ("\n");        
    cout << " " << endl;

    for (int i=0; i<commoncuts_str.size(); i++)
    {
        printf ("%40s", commoncuts_str[i].c_str());

        for (int j=0; j<ttHdecaystudy_str.size(); j++)
        {    
            int samp_int = samps[0];      
            printf ("%15.2f", commoncuts[i][samp_int][j]);
        }

        printf ("\n");

    }



    cout << "ss 2 ele" << endl;
    cout << " " << endl;
    printf ("%40s","cut");
    for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
    printf ("\n");
    cout << " " << endl;

    for (int i=0; i<ss_2e_cuts_str.size(); i++)
    {
        printf ("%40s", ss_2e_cuts_str[i].c_str());

        for (int j=0; j<ttHdecaystudy_str.size(); j++)
        {    
            int samp_int = samps[0];            
            printf ("%15.2f", ss_2e_cuts[i][samp_int][j]);
        }

        printf ("\n");
    }

    cout << "ss 2 mu" << endl;
    cout << " " << endl;
    printf ("%40s","cut");
    for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
    printf ("\n");
    cout << " " << endl;        

    for (int i=0; i<ss_2mu_cuts_str.size(); i++)
    {
        printf ("%40s", ss_2mu_cuts_str[i].c_str());

        for (int j=0; j<ttHdecaystudy_str.size(); j++)
        {    
            int samp_int = samps[0];            
            printf ("%15.2f", ss_2mu_cuts[i][samp_int][j]);
        }

        printf ("\n");
    }

    cout << "ss e mu" << endl;
    cout << " " << endl;
    printf ("%40s","cut");
    for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
    printf ("\n");
    cout << " " << endl;        

    for (int i=0; i<ss_emu_cuts_str.size(); i++)
    {
        printf ("%40s", ss_emu_cuts_str[i].c_str());

        for (int j=0; j<ttHdecaystudy_str.size(); j++)
        {    
            int samp_int = samps[0];            
            printf ("%15.2f", ss_emu_cuts[i][samp_int][j]);
        }

        printf ("\n");
    }



    cout << "3 lep" << endl;
    cout << " " << endl;
    printf ("%40s","cut");
    for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
    printf ("\n");
    cout << " " << endl;        

    for (int i=0; i<threel_cuts_str.size(); i++)
    {
        printf ("%40s", threel_cuts_str[i].c_str());

        for (int j=0; j<ttHdecaystudy_str.size(); j++)
        {    
            int samp_int = samps[0];            
            printf ("%15.2f", threel_cuts[i][samp_int][j]);
        }

        printf ("\n");
    }


    cout << "4 lep" << endl;
    cout << " " << endl;
    printf ("%40s","cut");
    for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
    printf ("\n");
    cout << " " << endl;        

    for (int i=0; i<fourl_cuts_str.size(); i++)
    {
        printf ("%40s", fourl_cuts_str[i].c_str());

        for (int j=0; j<ttHdecaystudy_str.size(); j++)
        {    
            int samp_int = samps[0];            
            printf ("%15.2f", fourl_cuts[i][samp_int][j]);
        }

        printf ("\n");
    }



    
    
    cout << " " << endl;
    cout << " " << endl;
    cout << "predicted events" << endl;
    cout << " " << endl;
        
//    for (int j=0; j<ttHdecaystudy_str.size(); j++)
//    {
//        int samp_int = samps[0];
        
        cout << "common" << endl;
        cout << " " << endl;
        printf ("%40s","cut");
        for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
        printf ("\n");
        cout << " " << endl;
        
        for (int i=0; i<commoncuts_str.size(); i++)
        {
            printf ("%40s", commoncuts_str[i].c_str());
            
            for (int j=0; j<ttHdecaystudy_str.size(); j++)
            {    
                int samp_int = samps[0];        
                printf ("%15.2f", (10000.*commoncuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        cout << "ss 2 ele" << endl;
        cout << " " << endl;
        printf ("%40s","cut");
        for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<ss_2e_cuts_str.size(); i++)
        {               
            printf ("%40s", ss_2e_cuts_str[i].c_str());
            
            for (int j=0; j<ttHdecaystudy_str.size(); j++)
            {    
                int samp_int = samps[0];            
                printf ("%15.2f", (10000.*ss_2e_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        cout << "ss 2 mu" << endl;
        cout << " " << endl;
        printf ("%40s","cut");
        for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<ss_2mu_cuts_str.size(); i++)
        {
            printf ("%40s", ss_2mu_cuts_str[i].c_str());
            
            for (int j=0; j<ttHdecaystudy_str.size(); j++)
            {    
                int samp_int = samps[0];            
                printf ("%15.2f", (10000.*ss_2mu_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
                
        cout << "ss e mu" << endl;
        cout << " " << endl;
        printf ("%40s","cut");
        for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<ss_emu_cuts_str.size(); i++)
        {
            printf ("%40s", ss_emu_cuts_str[i].c_str());
            
            for (int j=0; j<ttHdecaystudy_str.size(); j++)
            {    
                int samp_int = samps[0];            
                printf ("%15.2f", (10000.*ss_emu_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        cout << "3l" << endl;
        cout << " " << endl;
        printf ("%40s","cut");
        for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<threel_cuts_str.size(); i++)
        {
            printf ("%40s", threel_cuts_str[i].c_str());
            
            for (int j=0; j<ttHdecaystudy_str.size(); j++)
            {    
                int samp_int = samps[0];            
                printf ("%15.2f", (10000.*threel_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
        }
        
        cout << "4l" << endl;
        cout << " " << endl;
        printf ("%40s","cut");
        for (int j=0; j<ttHdecaystudy_str.size(); j++) printf ("%15s", ttHdecaystudy_str[j].c_str());
        printf ("\n");
        cout << " " << endl;        
        
        for (int i=0; i<fourl_cuts_str.size(); i++)
        {
            printf ("%40s", fourl_cuts_str[i].c_str());
            
            for (int j=0; j<ttHdecaystudy_str.size(); j++)
            {    
                int samp_int = samps[0];            
                printf ("%15.2f", (10000.*fourl_cuts[i][samp_int][j]*xsecs[samp_int])/numgen[samp_int]);
            }
            
            printf ("\n");
         }
        
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////
        
        // cut flow with mult. samples:


//    cout << " " << endl;
//    cout << " " << endl;
//    cout << "raw mc" << endl;
//    cout << " " << endl;  
//        
//         cout << "common" << endl;
//         cout << " " << endl;        
//         printf ("%40s","cut");        
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");        
//         cout << " " << endl;
//         printf ("%40s", "no cuts");        
//         for (int j=0; j<numsamples; j++) printf ("%15.2f", numgen[samps[j]]);
//         printf ("\n");
//         
//         for (int i=0; i<commoncuts_str.size(); i++)
//         {
//             printf ("%40s", commoncuts_str[i].c_str());
//                         
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];      
//                 printf ("%15.2f", commoncuts[i][samp_int][0]);
//             }
//             
//             printf ("\n");
//         
//         }
//         
//         
//         
//         cout << "ss 2 ele" << endl;
//         cout << " " << endl;
//         //printf ("%40s%15s%15s%15s\n", "cut", "ttH", );
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;
//         
//         for (int i=0; i<ss_2e_cuts_str.size(); i++)
//         {
//             printf ("%40s", ss_2e_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];
//                 if (samp_int==5) ss_2e_cuts[i][samp_int][0] *= 1.55;
//                 printf ("%15.2f", ss_2e_cuts[i][samp_int][0]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "ss 2 mu" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<ss_2mu_cuts_str.size(); i++)
//         {
//             printf ("%40s", ss_2mu_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];  
//                 if (samp_int==5) ss_2mu_cuts[i][samp_int][0] *= 3.3;         
//                 printf ("%15.2f", ss_2mu_cuts[i][samp_int][0]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "ss e mu" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<ss_emu_cuts_str.size(); i++)
//         {
//             printf ("%40s", ss_emu_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j]; 
//                 if (samp_int==5) ss_emu_cuts[i][samp_int][0] *= 1.87;           
//                 printf ("%15.2f", ss_emu_cuts[i][samp_int][0]);
//             }
//             
//             printf ("\n");
//         }
// 
//         
//         
//         cout << "3 lep" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<threel_cuts_str.size(); i++)
//         {
//             printf ("%40s", threel_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];  
//                 if (samp_int==5) threel_cuts[i][samp_int][0] *= 2.85;          
//                 printf ("%15.2f", threel_cuts[i][samp_int][0]);
//             }
//             
//             printf ("\n");
//         }
//         
//         
//         cout << "4 lep" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<fourl_cuts_str.size(); i++)
//         {
//             printf ("%40s", fourl_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];            
//                 printf ("%15.2f", fourl_cuts[i][samp_int][0]);
//             }
//             
//             printf ("\n");
//         }
//         
//         
//        
//         
// 
// 
//     
//     
//     cout << " " << endl;
//     cout << " " << endl;
//     cout << "predicted events" << endl;
//     cout << " " << endl;
//         
//         
//         cout << "common" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;
//         printf ("%40s", "no cuts");        
//         for (int j=0; j<numsamples; j++) printf ("%15.2f", 10000.*xsecs[samps[j]]);
//         printf ("\n");
//         
//         for (int i=0; i<commoncuts_str.size(); i++)
//         {
//             printf ("%40s", commoncuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];        
//                 printf ("%15.2f", (10000.*commoncuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "ss 2 ele" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<ss_2e_cuts_str.size(); i++)
//         {               
//             printf ("%40s", ss_2e_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];            
//                 printf ("%15.2f", (10000.*ss_2e_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "ss 2 mu" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<ss_2mu_cuts_str.size(); i++)
//         {
//             printf ("%40s", ss_2mu_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];            
//                 printf ("%15.2f", (10000.*ss_2mu_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//                 
//         cout << "ss e mu" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<ss_emu_cuts_str.size(); i++)
//         {
//             printf ("%40s", ss_emu_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];            
//                 printf ("%15.2f", (10000.*ss_emu_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "3l" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<threel_cuts_str.size(); i++)
//         {
//             printf ("%40s", threel_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];            
//                 printf ("%15.2f", (10000.*threel_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
//         
//         cout << "4l" << endl;
//         cout << " " << endl;
//         //printf ("%40s %15s \n", "cut", "ttH");
//         printf ("%40s","cut");
//         for (int j=0; j<numsamples; j++) printf ("%15s", sample_names_std[samps[j]].c_str());
//         printf ("\n");
//         cout << " " << endl;        
//         
//         for (int i=0; i<fourl_cuts_str.size(); i++)
//         {
//             printf ("%40s", fourl_cuts_str[i].c_str());
//             
//             for (int j=0; j<numsamples; j++)
//             {    
//                 int samp_int = samps[j];            
//                 printf ("%15.2f", (10000.*fourl_cuts[i][samp_int][0]*xsecs[samp_int])/numgen[samp_int]);
//             }
//             
//             printf ("\n");
//         }
        
        
        

    
    
}
