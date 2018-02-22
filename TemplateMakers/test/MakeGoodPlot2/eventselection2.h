string HistMaker::eventselection()
{
    //int numbjets = 0;
    
    //auto jets = simpleCut(*loose_jets_intree,"pt",25.0);
    
    //auto taggedjetsmedium = keepTagged(jets,"M");
    //auto taggedjetsloose = keepTagged(jets,"L");
    
    //int numjets = jets.size();
    int nummuons = tight_muons_intree->size();
    int numeles = tight_electrons_intree->size();
    
    int numleps = numeles+nummuons;        
    
    if (numleps>1)
    {    
        double mindilepmass = getTwoObjKineExtreme(*tight_leptons_intree,"min","mass");
           
        if (mindilepmass>12)
        {            
            if ((*tight_leptons_intree)[0].obj.Pt()>25 && (*tight_leptons_intree)[1].obj.Pt()>20)
            {
                for (const auto & ele : *tight_electrons_intree)
                {
                    if (!ele.isGsfCtfScPixChargeConsistent) return "null";
                    if (ele.lepMVA<0.5) return "null";
                }
                for (const auto & mu : *tight_muons_intree) 
                {
                    if (!(mu.chargeFlip<0.2)) return "null";
                    if (mu.lepMVA<0.5) return "null";
                    if (mu.idMediumPOG==false) return "null";
                }
                
                if (numleps==2)
                {
                    // SS2l
                    if ((*tight_leptons_intree)[0].charge == (*tight_leptons_intree)[1].charge)
                    {                
                        if ((*tight_leptons_intree)[0].charge+(*tight_leptons_intree)[1].charge == 2)
                        {                    
                            if (nummuons==2)
                            {
                                return "2lss_p_mumu";
                            }
                            else if (numeles==2)
                            {
                                return "2lss_p_ee";
                            }
                            else if (numeles==1 && nummuons==1)
                            {
                                return "2lss_p_emu";
                            }
                        }
                        else
                        {
                            if (nummuons==2)
                            {
                                return "2lss_m_mumu";
                            }
                            else if (numeles==2)
                            {
                                return "2lss_m_ee";
                            }
                            else if (numeles==1 && nummuons==1)
                            {
                                return "2lss_m_emu";
                            }                
                        }                   
                    }
                    // OS2l
                    else 
                    {
                        // SFOS
                        if (nummuons==2)
                        {
                            double vetoZmass = pickFromSortedTwoObjKine((*tight_muons_intree),"mass",1,91.2);                        
                            if (abs(vetoZmass-91.2)<10)
                            {
                                return "2los_sfz_mumu";
                            }
                            else
                            {
                                return "2los_mumu";
                            }
                        }
                        // SFOS                    
                        else if (numeles==2)
                        {
                            double vetoZmass = pickFromSortedTwoObjKine((*tight_electrons_intree),"mass",1,91.2);
                            if (abs(vetoZmass-91.2)<10)
                            {
                                 return "2los_sfz_ee";                           
                            }
                            else
                            {
                                return "2los_ee";                            
                            }
                        }
                        else if (numeles==1 && nummuons==1)
                        {
                            return "2los_emu";
                        }           
                    }
                }            
                else if (numleps==3)
                {                    
                    if ((*tight_leptons_intree)[0].charge + (*tight_leptons_intree)[1].charge + (*tight_leptons_intree)[2].charge == 3)
                    {
                        return "3l_ppp";
                    }
                    else if ((*tight_leptons_intree)[0].charge + (*tight_leptons_intree)[1].charge + (*tight_leptons_intree)[2].charge == -3)
                    {
                        return "3l_mmm";                    
                    }
                    else
                    {                    
                        double vetoZmass = pickFromSortedTwoObjKine((*tight_leptons_intree),"mass",1,91.2);
                        if (abs(vetoZmass-91.2)<10)
                        {
                            return "3l_mix_sfz";                           
                        }
                        else
                        {
                            return "3l_mix";                         
                        }                                         
                    }
                }
                else if (numleps>=4)
                {
                    return "ge4l";
                }                
            } // end lep pt req
        } // end dilep mass cut
    } // end ge2 leps
    else if (numleps==1)
    {
        if ((*tight_leptons_intree)[0].obj.Pt()>25)
        {
              
            // "poor man's" single lep (if you skimmed on >=2 preselected leptons)
            // bool isfake=false;
//             for (const auto & lep : *preselected_leptons_intree) 
//             {
//                 if (lep.lepMVA<0.5) isfake=true;
//             }
//             if (!isfake) return "null";
            
            
            if (nummuons==1)
            {   
                return "1l_mu";
            }
            else if (numeles==1)
            {
                return "1l_e";
            }
        }
    }
    return "null"; // <-- definitely can get here, especially if sample isn't a skim
} //end function
