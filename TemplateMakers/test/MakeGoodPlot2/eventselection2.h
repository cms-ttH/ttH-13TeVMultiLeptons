string HistMaker::eventselection(std::vector<ttH::Jet> thejets, bool useFakeable)
{
    //int numbjets = 0;
    
    auto jets = thejets;
    //auto jets = simpleJetCut(thejets,"pt",30.0);
    //jets = simpleJetCut(jets,"passPUID",0);
    
    bool tightercuts = false;
    
    //auto taggedjetsmedium = keepTagged(*preselected_jets_intree,"DM");
    auto taggedjetsmedium = keepTagged(jets,"DM");
    auto taggedjetsloose = keepTagged(jets,"DL");
    
    
    int jetsize = jets.size();
    int tagsize = taggedjetsmedium.size();
    int tagsizeL = taggedjetsloose.size();
    
    vector<ttH::Lepton> leptons;
    vector<ttH::Electron> electrons;
    vector<ttH::Muon> muons;
      
    
    //bool sshelper = false;
    
    if (!useFakeable)
    {
        leptons = tight_leptons;
        electrons = tight_electrons;
        muons = tight_muons;   
    }
    else
    {
        leptons = fakeable_leptons;
        electrons = fakeable_electrons;
        muons = fakeable_muons;
    }
    
    int nummuons = muons.size();
    int numeles = electrons.size();
    int numleps = leptons.size();    
    
    int numPSmuons = preselected_muons_intree->size();
    int numPSeles = preselected_electrons_intree->size();
    int numPSleps = preselected_leptons_intree->size();
    
    //if (numleps>=3) cout << "found one" << endl;
    
    // SRs and CRs
    //bool cr2lss = jetsize>=2 && jetsize<=3 && tagsize>=1;
    //bool cr2lss = jetsize>=1;
    //bool cr2lss = jetsize>=2 && tagsize==1;
    bool cr2lss = jetsize>=1 &&  jetsize<=2 && tagsize==1 && tagsizeL==1; // jetsize>=1 &&  jetsize<=2 && tagsize==1 && tagsizeL==1;
    bool cr3l = jetsize>=1 && tagsize==0 && tagsizeL==0; // jetsize>=1 && tagsize==0 && tagsizeL==0;
    bool sr2lss = jetsize>=4 && (tagsizeL>=2 || tagsize>=1); // jetsize>=4 && tagsize>=2; // jetsize>=4 && (tagsizeL>=2 || tagsize>=1); // jetsize>=4 && tagsizeL>=1;
    bool sr3l = jetsize>=2 && tagsize>=1; // jetsize>=2 && tagsize>=1; // jetsize>=2 && (tagsizeL>=2 || tagsize>=1); // jetsize>=2 && tagsizeL>=1;
    
    bool jetbpass2l = false;                                                                                   // change this if switching between SRs / CRs!!!!!
    bool jetbpass3l = false;                                                                                     // change this if switching between SRs / CRs!!!!!
    
    
    if (isSR) // see ctr
    {
        jetbpass2l = sr2lss;       
        jetbpass3l = sr3l;
    }
    else
    {
        jetbpass2l = cr2lss;  
        jetbpass3l = cr3l;
    }
    
    // temp!!!
    //jetbpass2l = true;
    //jetbpass3l = true;
    
    
    bool testcutpass = true;
    
//     for (const auto & leptest : *preselected_leptons_intree)
//     {
//         //if (!leptest.idMediumPOG) testcutpass = false;
//         //if (leptest.csv>0.8484) testcutpass = false;
//         if (leptest.lepMVA<0.9) testcutpass = false;
//     }
    
    if (numleps>1 && testcutpass)
    {    
        double mindilepmass = getTwoObjKineExtreme(leptons,"min","mass"); // might need to be over more leps (to check)
           
        if (mindilepmass>12)
        {            
            //if (numleps>=3) cout << "here1" << endl;
            if ( (leptons[0].correctedPt>25) && (leptons[1].correctedPt>20 || (leptons[1].correctedPt>15 && !tightercuts)) ) 
            {
                //if (numleps>=3) cout << "here2" << endl;
                //if ( (numleps==2 || (useFakeable && numleps>=2)) && jetbpass2l)
                if ( numleps==2 && jetbpass2l )
                {
                    // SS2l
                    if (leptons[0].charge == leptons[1].charge)
                    {                
                        for (const auto & ele : electrons)
                        {
                            if (!ele.isGsfCtfScPixChargeConsistent) return "null";
                            //if (ele.lepMVA<0.5) return "null";
                        }
                        for (const auto & mu : muons) 
                        {
                            if (!(mu.chargeFlip<0.2)) return "null";
                            //if (mu.lepMVA<0.5) return "null";
                            //if (mu.idMediumPOG==false) return "null";
                        }
                        
                        if (leptons[0].charge+leptons[1].charge == 2)
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
                            // the following cut is temporary!
                            //if (tightercuts && (muons)[0].correctedPt<30.) return "null"; // for triggering on 1mu only
                            
                            double vetoZmass = pickFromSortedTwoObjKine(muons,"mass",1,91.2);                        
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
                            //if (tightercuts && (*tight_electrons_intree)[0].correctedPt<40.) return "null"; // for triggering on 1ele only
                            
                            double vetoZmass = pickFromSortedTwoObjKine(electrons,"mass",1,91.2);
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
                            // the following 2 cuts are temporary!
                            //if (tightercuts && (*tight_muons_intree)[0].correctedPt<30.) return "null"; // for triggering on 1mu only
                            //if ((*met_intree)[0].correctedPt<100.) return "null"; // for triggering on 1mu only
                            
                            return "2los_emu";
                        }           
                    }
                }            
                //else if ((numleps==3 || (useFakeable && numleps>=3)) && jetbpass3l)
                if ((numleps==3 || (useFakeable && numleps>=3)) && jetbpass3l)                
                {                    
                    if (leptons[2].correctedPt>10.)
                    {
                        if (leptons[0].charge + leptons[1].charge + leptons[2].charge == 3)
                        {
                            return "3l_ppp";
                        }
                        else if (leptons[0].charge + leptons[1].charge + leptons[2].charge == -3)
                        {
                            return "3l_mmm";                    
                        }
                        else
                        {                    
                            double vetoZmass = pickFromSortedTwoObjKine(leptons,"massSFOS",1,91.2);
                            if (abs(vetoZmass-91.2)<10)
                            {
                                return "3l_mix_sfz";                           
                            }
                            else
                            {
                                if (leptons[0].charge + leptons[1].charge + leptons[2].charge == 1)
                                {
                                    return "3l_mix_p";
                                }
                                else
                                {
                                    return "3l_mix_m";
                                }   
                                                   
                            }                                         
                        }
                    }
                }
                else if (numleps>=4) // && jetsize>0 && tagsize>0) // check this. it's >1, >0 according to AN.
                {
                    return "4l";
                }
                //else if (numleps>=5) // && jetsize>0 && tagsize>0) // combine with 4l!
                //{
                //    return "ge5l";
                //}
                                
            } // end lep pt req
        } // end dilep mass cut
    } // end ge2 leps
    if ((numleps==1 || (useFakeable && numleps>=1)) && jetsize>=4 && tagsize>=2 && testcutpass) // jetsize>=1 && tagsize==0
    {
        if (leptons[0].correctedPt>40.) // should really be >35, at least for eles
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

vector<string> HistMaker::eventselections(bool useFakeable)
{
    vector<string> myselections;
    
    //std::vector<ttH::Jet> cleanedjets = cleanObjs(*preselected_jets_intree,*preselected_leptons_intree,0.4);
    
    //myselections.push_back(eventselection(cleanedjets)); // nominal
    //myselections.push_back(eventselection(*preselected_jets_JECup_intree)); // event selection with JESup jets
    //myselections.push_back(eventselection(*preselected_jets_JECdown_intree)); // event selection with JESdown jets
    
    myselections.push_back(eventselection(preselected_jets,useFakeable)); // nominal
    myselections.push_back(eventselection(preselected_jets_JECup,useFakeable)); // event selection with JESup jets
    myselections.push_back(eventselection(preselected_jets_JECdown,useFakeable)); // event selection with JESdown jets    
    
    return myselections;
}
