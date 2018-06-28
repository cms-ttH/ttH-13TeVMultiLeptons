void HistMaker::standard_hists()
{
    bool debug = false;
    
    //cout << "what" << endl;
    
    double weight = *wgt_intree;
    
    vector<string> stdcategory = eventselections();
    vector<string> category;
    int doNtimes = 1;    
    
    ////////////////////////// 
    // charge flip / fake stuff    
    //
    // dochgfs and dofakes bools are set externally
    //
    
    vector<string> category2;
    
    if (!dochgfs && !dofakes) category = stdcategory;
    else if (dochgfs)
    {
        doNtimes = 2;
        for (string thiscat : stdcategory)
        {
            if (thiscat=="2los_ee" || thiscat=="2los_sfz_ee" )
            {
                //auto theqfsfs = getQFweights(thiscat);
                category.push_back("2lss_p_ee");
                category2.push_back("2lss_m_ee");
            }
            else if (thiscat=="2los_emu")
            {
                category.push_back("2lss_p_emu");
                category2.push_back("2lss_m_emu");
            }
            else
            {
                category.push_back("null");
                category2.push_back("null");
            }
        }
    }
    else if (dofakes)
    {
        category = eventselections(true); // true = do the event selection with fakeable leptons
    }
    ////////////////////////   
    
    th1d["numTruePVs"]->Fill((*numTruePVs_intree),weight);
        
    bool passedtrig = passesAnyTrigger();
    //passedtrig = true; // <<<---------------------------------------   comment me!!!!!!!!!!!!
        
    th1d["single_ele_trigs"]->Fill(passesDatasetDependentTriggers(101),weight);
    th1d["double_ele_trigs"]->Fill(passesDatasetDependentTriggers(103),weight);
    th1d["single_mu_trigs"]->Fill(passesDatasetDependentTriggers(100),weight);
    th1d["double_mu_trigs"]->Fill(passesDatasetDependentTriggers(102),weight);
    th1d["mu_ele_trigs"]->Fill(passesDatasetDependentTriggers(104),weight);
    th1d["all_trigs"]->Fill(passedtrig,weight);
    
    if (category[0]!="null")
    {
        th1d[category[0]+"__all_trigs"]->Fill(passedtrig,weight);
        th1d[category[0]+"__single_ele_trigs"]->Fill(passesDatasetDependentTriggers(101),weight);
        th1d[category[0]+"__double_ele_trigs"]->Fill(passesDatasetDependentTriggers(103),weight);
        th1d[category[0]+"__single_mu_trigs"]->Fill(passesDatasetDependentTriggers(100),weight);
        th1d[category[0]+"__double_mu_trigs"]->Fill(passesDatasetDependentTriggers(102),weight);
        th1d[category[0]+"__mu_ele_trigs"]->Fill(passesDatasetDependentTriggers(104),weight);
    }
    
    if (removeDatasetOverlaps() && passedtrig)
    {              
        for (int forchgfs=0; forchgfs<doNtimes; forchgfs++) // in the case of QF background (only), loop through twice
        {
            if (forchgfs==1) category = category2; // don't ever get here for nominal hists
            
            for (int sys=0; sys<category.size(); sys++)
            {   
                // these two conditionals skipped for nominal hists
                if (dochgfs)
                {
                    weight = *wgt_intree;
                    auto theqfsfs = getQFweights(stdcategory[sys]);
                    if (forchgfs==0) weight *= theqfsfs.first;
                    else weight *= theqfsfs.second;
                }
                if (dofakes)
                {
                    weight = *wgt_intree;
                    weight *= getFakeWeight(sys,category);
                }
                
                if (category[sys]!="null")
                {
                    if (sys==0)
                    {            
            
                        //std::vector<ttH::Jet> cutjets = simpleCut<std::vector<ttH::Jet> >(*loose_jets_intree,"pt",25.0); // need to be careful with this (problem if type not explicitly specified)
                        //std::vector<ttH::Jet> cleanedjets = cleanObjs(*preselected_jets_intree,*preselected_leptons_intree,0.4);
                        //auto cleanedjets = simpleCut(*preselected_jets_intree,"pt",30.0);
                        ///cleanedjets = simpleJetCut(cleanedjets,"passPUID",0);
                        auto cleanedjets = preselected_jets;
                    
                        //auto taggedjetsmedium = keepTagged(cutjets,"M");        
                        //auto taggedjetsloose = keepTagged(cutjets,"L");
                        auto taggedjetsmedium = keepTagged(cleanedjets,"DM"); // DM = DeepCSV Medium WP
                        auto taggedjetsloose = keepTagged(cleanedjets,"DL");
                        //auto taggedjetsmedium = keepTagged(*preselected_jets_intree,"DM"); // DM = DeepCSV Medium WP
                        //auto taggedjetsloose = keepTagged(*preselected_jets_intree,"DL");

                        // why are these doubles? ...
                        //double jetsize = cutjets.size();  
                        double jetsize = cleanedjets.size();  
                        //double jetsize = preselected_jets_intree->size();
                        double taggedjetssize = taggedjetsmedium.size();
                        double taggedjetsloosesize = taggedjetsloose.size();

                        
                        auto muons = tight_muons;
                        auto electrons = tight_electrons;
                        auto leptons = tight_leptons;
                        
                        if (dofakes)
                        {
                            muons = fakeable_muons;
                            electrons = fakeable_electrons;
                            leptons = fakeable_leptons;
                        }
                        
                        int nummuons = muons.size();
                        int numeles = electrons.size();
                        int numleps = leptons.size();
                    
                        // 2016 SFs for reference:
                        // this SF section eventually should be bigger / have more stuff:
            //         if (sample<100) 
            //         {
            //             for (const auto & lep : *tight_leptons_intree) 
            //             {
            //                 // For 2016 data/MC, this is the combined reco+POGID+lepMVA SF:
            //                 if (category.substr(0,2)=="2l") weight *= leptonSF_ttH(lep.pdgID, lep.obj.Pt(), lep.obj.Eta(), 2);
            //                 else if (category.substr(0,2)=="3l" || category.substr(0,2)=="41" || category.substr(0,2)=="ge") weight *= leptonSF_ttH(lep.pdgID, lep.obj.Pt(), lep.obj.Eta(), 3);
            //             }
            //             
            //             int ntpvs = *numTruePVs_intree;
            //             if ( ntpvs<0 ) ntpvs = 99;
            //             weight *= puw2016_nTrueInt_36fb(ntpvs);
            //         }
                    
                    
                        // 2017 SFs
                        if (sample<100) 
                        {
                            weight = *wgt_intree; // the data-driven background weights don't get applied to MC
                            weight *= totalSF(sys,category);
                        }
                    
                    
                        th1d[category[sys]+"__njets"]->Fill(jetsize,weight);               
                        th1d[category[sys]+"__nbjets"]->Fill(taggedjetssize,weight);        
                        th2d[category[sys]+"__nbjets_vs_njets"]->Fill(jetsize,taggedjetssize,weight);
                        th1d[category[sys]+"__numPVs"]->Fill((*numPVs_intree),weight);
                        th1d[category[sys]+"__numTruePVs"]->Fill((*numTruePVs_intree),weight);

                    
     
                        //for (const auto & jet : *preselected_jets_intree)
                        for (const auto & jet : cleanedjets)
                        {
                            th1d[category[sys]+"__jetpt"]->Fill(jet.obj.Pt(),weight);
                            th1d[category[sys]+"__jeteta"]->Fill(jet.obj.Eta(),weight);
                            th1d[category[sys]+"__jetcsv"]->Fill(jet.csv,weight);
                            th1d[category[sys]+"__jetDeepCSV"]->Fill(jet.DeepCSV,weight);
                            th1d[category[sys]+"__jetDeepCSVprobb"]->Fill(jet.DeepCSVprobb,weight);
                            th1d[category[sys]+"__jetDeepCSVprobbb"]->Fill(jet.DeepCSVprobbb,weight);
                            th1d[category[sys]+"__jetDeepCSVprobc"]->Fill(jet.DeepCSVprobc,weight);
                            th1d[category[sys]+"__jetDeepCSVprobudsg"]->Fill(jet.DeepCSVprobudsg,weight);
                            th1d[category[sys]+"__PUMVA"]->Fill(jet.PUMVA,weight);
                            th1d[category[sys]+"__qgid"]->Fill(jet.qgid,weight);
                        }
    
                        for (const auto & lep : leptons)
                        {
                            th1d[category[sys]+"__leppt"]->Fill(lep.obj.Pt(),weight);
                            th1d[category[sys]+"__lepeta"]->Fill(lep.obj.Eta(),weight);   
                            th1d[category[sys]+"__lepMVA"]->Fill(lep.lepMVA,weight);
                            th1d[category[sys]+"__dxy"]->Fill(lep.dxy,weight);
                            th1d[category[sys]+"__dz"]->Fill(lep.dz,weight);
                            th1d[category[sys]+"__miniIso"]->Fill(lep.miniIso,weight);
                            th1d[category[sys]+"__miniIsoR"]->Fill(lep.miniIsoR,weight);
                            th1d[category[sys]+"__miniIsoCharged"]->Fill(lep.miniIsoCharged,weight);
                            th1d[category[sys]+"__miniIsoNeutral"]->Fill(lep.miniIsoNeutral,weight);
                            th1d[category[sys]+"__jetPtRatio"]->Fill(lep.jetPtRatio,weight);
                            th1d[category[sys]+"__jetPtRel"]->Fill(lep.jetPtRel,weight);
                            th1d[category[sys]+"__nearestJetCSV"]->Fill(lep.csv,weight);
                            th1d[category[sys]+"__sip3D"]->Fill(lep.sip3D,weight);
                            th1d[category[sys]+"__jet_nCharged_tracks"]->Fill(lep.jet_nCharged_tracks,weight);
                            th1d[category[sys]+"__effArea"]->Fill(lep.effArea,weight);
                            th1d[category[sys]+"__rho"]->Fill(lep.rho,weight);
                            th1d[category[sys]+"__correctedPt"]->Fill(lep.correctedPt,weight);
                        
                        }
        
                        th1d[category[sys]+"__lep1pt"]->Fill(leptons[0].obj.Pt(),weight);
                        if (numleps>1)
                        {
                            th1d[category[sys]+"__lep2pt"]->Fill(leptons[1].obj.Pt(),weight);
                            auto obj12 = leptons[0].obj + leptons[1].obj;
                            th1d[category[sys]+"__llmass"]->Fill(obj12.M(),weight);
                        }
        
                        //auto allobjsTLV = getsumTLV(*tight_leptons_intree,*preselected_jets_intree);
                        auto allobjsTLV = getsumTLV(leptons,cleanedjets);
                        th1d[category[sys]+"__MHT"]->Fill(allobjsTLV.Pt(),weight);
                        th1d[category[sys]+"__met"]->Fill((*met_intree)[0].obj.Pt(),weight);
                        th1d[category[sys]+"__metphi"]->Fill((*met_intree)[0].obj.Phi(),weight);
        
     
                        int thisbin = th1d["category_yields"]->GetXaxis()->FindBin(category[sys].c_str());
                        th1d["category_yields"]->Fill(thisbin,weight);

                        //cout << "hey" << endl;

                        string jtcat = getjettagcategory(category[sys],jetsize,taggedjetssize);
                        string lbcat = gettagcategory(category[sys],taggedjetssize);
                    
                        if (debug) cout << jtcat << endl;
                        if (debug) cout << lbcat << endl;
                    
                        if (jtcat!="null" && category[sys].substr(0,2)!="1l")
                        {
                            if (debug) cout << "blah" << endl;
                        
                            int thisbin = th1d["category_yields_njets_nbjets"]->GetXaxis()->FindBin(jtcat.c_str());
                            th1d["category_yields_njets_nbjets"]->Fill(thisbin,weight);
                        
                            if (debug) cout << "blah1" << endl;
                        
                            if (lbcat!="null") 
                            {
                                if (debug) cout << "blahhh" << endl;
                                if (debug) cout << lbcat << endl;
                                if (debug) cout << jetsize << endl;
                                if (debug) cout << weight << endl;
                            
                                std::vector<WCPoint> event_wgts;
                                for (auto& kv: *eftwgts_intree) 
                                {
                                    WCPoint new_pt(kv.first,kv.second/2000.);
                                    //WCPoint new_pt(kv.first,kv.second / (*originalXWGTUP_intree));
                                    event_wgts.push_back(new_pt);
                                }
                                WCFit event_wgt_fit(event_wgts,"");
                                //th1d[lbcat+"."]->Fill(jetsize,weight); // regular TH1D
                                th1eft[lbcat+"."]->Fill(jetsize,weight,event_wgt_fit); // using the TH1EFT class
                                //fillQFHists(sys,category); // for this, really only care about data
                                //fillFakeHists(sys,category); // for this, really only care about data
                            
                            }
                            if (debug) cout << "blah2" << endl;
                        }
                    }
            
                    else if (sys==1)
                    {
                        //auto cleanedjets = simpleCut(preselected_jets_JECup,"pt",30.0);
                        auto cleanedjets = preselected_jets_JECup;
                        auto taggedjetsmedium = keepTagged(cleanedjets,"DM");
                        int jetsize = cleanedjets.size();
                        int taggedjetssize = taggedjetsmedium.size();
                    
                        string jtcat = getjettagcategory(category[sys],jetsize,taggedjetssize);
                        string lbcat = gettagcategory(category[sys],taggedjetssize);
                    
                        if (sample<100) 
                        {
                            weight = *wgt_intree;
                            weight *= totalSF(sys,category);
                        }
                    
                        if (debug) cout << "JESUP " << jtcat << endl;
                        if (debug) cout << "JESUP " << lbcat << endl;
                    
                        if (jtcat!="null" && category[sys].substr(0,2)!="1l")
                        {
                            if (debug) cout << "here" <<endl;
                            int thisbin = th1d["category_yields_njets_nbjets_JESUP"]->GetXaxis()->FindBin(jtcat.c_str());
                            if (debug) cout << "here0.1" <<endl;
                            th1d["category_yields_njets_nbjets_JESUP"]->Fill(thisbin,weight);
                            if (debug) cout << "here0.2" <<endl;
                            if (lbcat!="null")
                            {
                                if (debug) cout << "here0.3" <<endl;
                                std::vector<WCPoint> event_wgts;
                                for (auto kv: *eftwgts_intree) 
                                {
                                    WCPoint new_pt(kv.first,kv.second/2000.);
                                    //WCPoint new_pt(kv.first,kv.second / (*originalXWGTUP_intree));
                                    event_wgts.push_back(new_pt);
                                }
                                if (debug) cout << "here0.4" <<endl;
                                WCFit event_wgt_fit(event_wgts,"");
                                //th1d[lbcat+".JESUP"]->Fill(jetsize,weight); // regular TH1D
                                if (debug) cout <<"here2"<<endl;
                                th1eft[lbcat+".JESUP"]->Fill(jetsize,weight,event_wgt_fit); // using the TH1EFT class
                                if (debug) cout<<"here3"<<endl;
                                //fillQFHists(sys,category);
                                //fillFakeHists(sys,category);
                            }
                        }
                
                    }
            
                    else if (sys==2)
                    {
                    
                        //auto cleanedjets = simpleCut(preselected_jets_JECdown,"pt",30.0);
                        auto cleanedjets = preselected_jets_JECdown;
                        auto taggedjetsmedium = keepTagged(cleanedjets,"DM");
                        int jetsize = cleanedjets.size();
                        int taggedjetssize = taggedjetsmedium.size();
                    
                        string jtcat = getjettagcategory(category[sys],jetsize,taggedjetssize);
                        string lbcat = gettagcategory(category[sys],taggedjetssize);
                    
                        if (sample<100) 
                        {
                            weight = *wgt_intree;
                            weight *= totalSF(sys,category);
                        }

                        if (jtcat!="null" && category[sys].substr(0,2)!="1l")
                        {
                            int thisbin = th1d["category_yields_njets_nbjets_JESDOWN"]->GetXaxis()->FindBin(jtcat.c_str());
                            th1d["category_yields_njets_nbjets_JESDOWN"]->Fill(thisbin,weight);
                            if (lbcat!="null")
                            {
                                std::vector<WCPoint> event_wgts;
                                for (auto& kv: *eftwgts_intree) 
                                {
                                    WCPoint new_pt(kv.first,kv.second/2000.);
                                    //WCPoint new_pt(kv.first,kv.second / (*originalXWGTUP_intree));
                                    event_wgts.push_back(new_pt);
                                }
                                WCFit event_wgt_fit(event_wgts,"");
                                //th1d[lbcat+".JESDOWN"]->Fill(jetsize,weight); // regular TH1D
                                th1eft[lbcat+".JESDOWN"]->Fill(jetsize,weight,event_wgt_fit); // using the TH1EFT class
                                //fillQFHists(sys,category);
                                //fillFakeHists(sys,category);
                            }
                        }                    
                    }
                
                
                } // non-null cat
            } // end loop over systs
        } // end loop over filling of charge flip hists
    } // passed trig
}
