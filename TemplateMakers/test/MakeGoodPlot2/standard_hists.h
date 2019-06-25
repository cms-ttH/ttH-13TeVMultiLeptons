void HistMaker::standard_hists()
{
    // filter out spurious higgs events
    if (sample==85 || sample==86 || sample==87 || sample==8 || sample==9 || sample==26) 
    {
        for (const auto gp : *pruned_genParticles_intree) if (abs(gp.pdgID)==25) return;
    }
    
    bool debug = false;
    //bool fillCRhists = (sample>=84 && sample<=88) ? false : true; // usually the second one is "!isSR" instead of "true"
    //bool fillCRhists = !isSR;
    bool fillCRhists = true;
    
    vector<int> systs;
    
    double weight = *wgt_intree;
    
    vector<string> stdcategory = eventselections();
    vector<string> category;
    int doNtimes = 1;    
    
    ////////////////////////////////////////////////// 
    // charge flip / fake stuff    
    //
    // dochgfs and dofakes bools are set externally
    //
    
    vector<string> category2;
    
    if (!dochgfs && !dofakes)
    {
        category = stdcategory;
        systs = {0, 1, 2, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46};
    }
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
        systs = {0, 1, 2}; // , 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};  // Do we really want/need the JES up/down here?
    }
    else if (dofakes)
    {
        category = eventselections(true); // true = do the event selection with fakeable leptons
        systs = {0, 1, 2, 3, 4, 5, 6, 31, 32, 33, 34}; // Do we really want/need the JES up/down here?
    }
    
    ////////////////////////////////////////////////
    
    
    
    
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
            
            for (int sys : systs)
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
                    if (debug) cout << "before getFakeWeight" << endl;
                    weight *= getFakeWeight(sys,category);
                    if (debug) cout << "after getFakeWeight" << endl;
                    // if (category[sys]=="3l_mix_sfz")
//                     {
//                         cout << "found a 3l_mix_sfz event -- " << weight << endl;
//                     }
                }
                // if (category[sys]=="3l_mix_sfz")
//                 {
//                     cout << "found a 3l_mix_sfz event -- " << weight << endl;
//                     cout << "fakeable leps size: " << fakeable_leptons.size() << endl;
//                     cout << "tight leps size: " << tight_leptons.size() << endl;
//                 }
                
                string systr = string(systint2str(sys));
                
                int catSys = sys>2 ? 0 : sys;   // catSys = 0, or 1 or 2 in the case of JESup/down. Should I think be fine as-is. 
                                                // q-flip, fake selections are special cases, which are already handled. 
                                                // lepID, btag systs are SF variations on already-selected events.
                
                if (category[catSys]!="null")
                {
                    WCPoint smpt = WCPoint();
                    
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

                        // why are these doubles? ... because of the "min" function below.
                        //double jetsize = cutjets.size();  
                        double jetsize = cleanedjets.size();  
                        //double jetsize = preselected_jets_intree->size();
                        
                        double taggedjetsmediumsize = taggedjetsmedium.size();                  // uncomment me!
                        double taggedjetsloosesize = taggedjetsloose.size();
                        //double taggedjetssize = taggedjetsloosesize;                        // test!
                        
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
                        
                        if (isSR)
                        {
                            string lbcatt = gettagcategory(category[sys],taggedjetsmediumsize,taggedjetsloosesize);
                            if (lbcatt=="null") continue;
                            // 2017 SFs
                            if (sample<90) // (Dec. 2018) in practice it's safe to do <100, but <90 is more clear
                            {
                                double njets4hist = min(jetsize,th1eft[lbcatt+"."]->GetXaxis()->GetXmax()-0.1);
                                int thebin = th1eft[lbcatt+"."]->FindBin(njets4hist);
                                weight = *wgt_intree; // the data-driven background weights don't get applied to MC
                                weight *= totalSF(sys,category,thebin);
                            }
                        }                        
                    
                        else
                        {
                            // 2017 SFs
                            if (sample<90) // (Dec. 2018) in practice it's safe to do <100, but <90 is more clear
                            {
                                weight = *wgt_intree; // the data-driven background weights don't get applied to MC
                                weight *= totalSF(sys,category);
                            }
                        }
                        if (sample>=84 && sample<=88) weight = getEventFit(weight).evalPoint(&smpt); // only for non-main-result hists!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        
                        if (fillCRhists) th1d[category[sys]+"__njets."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__njets."],jetsize),weight); // n.b.: to save fit using TH1EFT::Fill, separate last argument into 2 args: weight,getEventFit(weight)
                        if (fillCRhists) th1d[category[sys]+"__nbjets."]->Fill(taggedjetsloosesize,weight); 
                        if (fillCRhists) th1d[category[sys]+"__ntaus."]->Fill((*selected_taus_intree).size(),weight);
                        th2d[category[sys]+"__nbjets_vs_njets"]->Fill(jetsize,taggedjetsloosesize,weight);
                        th1d[category[sys]+"__numPVs"]->Fill((*numPVs_intree),weight);
                        th1d[category[sys]+"__numTruePVs"]->Fill((*numTruePVs_intree),weight);
                        
                        //th1d[category[sys]+"__nnpdfWeightUp"]->Fill((*nnpdfWeightUp_intree),weight);
                        //th1d[category[sys]+"__nnpdfWeightDown"]->Fill((*nnpdfWeightDown_intree),weight);
                        //th1d[category[sys]+"__muRWeightUp"]->Fill((*muRWeightUp_intree),weight);
                        //th1d[category[sys]+"__muRWeightDown"]->Fill((*muRWeightDown_intree),weight);
                        //th1d[category[sys]+"__muFWeightUp"]->Fill((*muFWeightUp_intree),weight);
                        //th1d[category[sys]+"__muFWeightDown"]->Fill((*muFWeightDown_intree),weight);

                        auto untaggedjetsmedium = keepUnTagged(cleanedjets,"DM"); // these only get used in the line below
                        if (fillCRhists) th1d[category[sys]+"__hadtopmass."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__hadtopmass."],had_top_mass(taggedjetsmedium,untaggedjetsmedium)),weight);
                    
                        double total_ht = 0.;
     
                        //for (const auto & jet : *preselected_jets_intree)
                        for (const auto & jet : cleanedjets)
                        {
                            if (fillCRhists) th1d[category[sys]+"__jetpt."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__jetpt."],jet.obj.Pt()),weight);
                            if (fillCRhists) th1d[category[sys]+"__jeteta."]->Fill(jet.obj.Eta(),weight);
                            th1d[category[sys]+"__jetcsv"]->Fill(jet.csv,weight);
                            if (fillCRhists) th1d[category[sys]+"__jetDeepCSV."]->Fill(jet.DeepCSV,weight);
                            th1d[category[sys]+"__jetDeepCSVprobb"]->Fill(jet.DeepCSVprobb,weight);
                            th1d[category[sys]+"__jetDeepCSVprobbb"]->Fill(jet.DeepCSVprobbb,weight);
                            th1d[category[sys]+"__jetDeepCSVprobc"]->Fill(jet.DeepCSVprobc,weight);
                            th1d[category[sys]+"__jetDeepCSVprobudsg"]->Fill(jet.DeepCSVprobudsg,weight);
                            if (fillCRhists) th1d[category[sys]+"__PUMVA."]->Fill(jet.PUMVA,weight);
                            th1d[category[sys]+"__qgid"]->Fill(jet.qgid,weight);
                            total_ht += jet.obj.Pt();
                        }
    
                        for (const auto & lep : leptons)
                        {
                            th1d[category[sys]+"__leppt"]->Fill(lep.obj.Pt(),weight);
                            if (fillCRhists) th1d[category[sys]+"__lepeta."]->Fill(lep.obj.Eta(),weight);   
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
                            total_ht += lep.obj.Pt();
                        }
                        
                        if (fillCRhists) th1d[category[sys]+"__HT."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__HT."],total_ht),weight);
                        
                        
                        if (fillCRhists) th1d[category[sys]+"__lep1pt."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__lep1pt."],leptons[0].obj.Pt()),weight);
                        if (numleps>1)
                        {
                            if (fillCRhists) th1d[category[sys]+"__lep2pt."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__lep2pt."],leptons[1].obj.Pt()),weight);
                            for (int i=0; i<(numleps-1); i++)
                            {
                                for (int j=i+1; j<numleps; j++)
                                {
                                    if ((leptons[i].charge+leptons[j].charge)==0)
                                    {
                                        auto obj12 = leptons[i].obj + leptons[j].obj;
                                        if (fillCRhists) th1d[category[sys]+"__llmass."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__llmass."],obj12.M()),weight);
                                        //th1d[category[sys]+"__llmass.envup"]->Fill(obj12.M(),weight);
                                        //th1d[category[sys]+"__llmass.envdown"]->Fill(obj12.M(),weight);
                                    }
                                }
                            }
                        }
        
                        //auto allobjsTLV = getsumTLV(*tight_leptons_intree,*preselected_jets_intree);
                        auto allobjsTLV = getsumTLV(leptons,cleanedjets);
                        if (fillCRhists) th1d[category[sys]+"__MHT."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__MHT."],allobjsTLV.Pt()),weight);
                        if (fillCRhists) th1d[category[sys]+"__met."]->Fill(fillHistOverflowAware(th1d[category[sys]+"__met."],(*met_intree)[0].obj.Pt()),weight);
                        th1d[category[sys]+"__metphi"]->Fill((*met_intree)[0].obj.Phi(),weight);
        
     
                        int thisbin = th1d["category_yields"]->GetXaxis()->FindBin(category[sys].c_str());
                        th1d["category_yields"]->Fill(thisbin,weight);

                        //cout << "hey" << endl;

                        string jtcat = getjettagcategory(category[sys],jetsize,taggedjetsloosesize);
                        string lbcat = gettagcategory(category[sys],taggedjetsmediumsize,taggedjetsloosesize);
                    
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
                                
                                double njets4hist = min(jetsize,th1eft[lbcat+"."]->GetXaxis()->GetXmax()-0.1);
                                if (sample<90)
                                {
                                    int thebin = th1eft[lbcat+"."]->FindBin(njets4hist);
                                    weight = *wgt_intree;
                                    weight *= totalSF(sys,category,thebin); // the weight is a fn of njet bin and sample (sample handled within totalSF)
                                }
                                //th1d[lbcat+"."]->Fill(jetsize,weight); // regular TH1D
                                th1eft[lbcat+"."]->Fill(njets4hist,weight,getEventFit(weight)); // using the TH1EFT class
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
                        auto taggedjetsloose = keepTagged(cleanedjets,"DL");
                        
                        double jetsize = cleanedjets.size();
                        
                        double taggedjetsmediumsize = taggedjetsmedium.size();
                        double taggedjetsloosesize = taggedjetsloose.size();
                    
                        string jtcat = getjettagcategory(category[sys],jetsize,taggedjetsloosesize);
                        string lbcat = gettagcategory(category[sys],taggedjetsmediumsize,taggedjetsloosesize);

                        if (isSR)
                        {
                            if (lbcat=="null") continue;
                                                        // 2017 SFs
                            if (sample<90) // (Dec. 2018) in practice it's safe to do <100, but <90 is more clear
                            {
                                double njets4hist = min(jetsize,th1eft[lbcat+".JESUP"]->GetXaxis()->GetXmax()-0.1);
                                int thebin = th1eft[lbcat+".JESUP"]->FindBin(njets4hist);
                                weight = *wgt_intree; // the data-driven background weights don't get applied to MC
                                weight *= totalSF(sys,category,thebin);
                            }
                        }
                        else
                        {
                            if (sample<90) 
                            {
                                weight = *wgt_intree;
                                weight *= totalSF(sys,category); // now includes JES btagging syst.
                            }
                        }
                        if (sample>=84 && sample<=88) weight = getEventFit(weight).evalPoint(&smpt); // only for non-main-result hists!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        
                        if (debug) cout << "JESUP " << jtcat << endl;
                        if (debug) cout << "JESUP " << lbcat << endl;
                        
                        if (fillCRhists) th1d[category[sys]+"__ntaus.JESUP"]->Fill((*selected_taus_intree).size(),weight);
                        
                        auto untaggedjetsmedium = keepUnTagged(cleanedjets,"DM"); // these only get used in the line below
                        if (fillCRhists) th1d[category[sys]+"__hadtopmass.JESUP"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__hadtopmass.JESUP"],had_top_mass(taggedjetsmedium,untaggedjetsmedium)),weight);
                        
                        auto leptons = tight_leptons;
                        if (dofakes) leptons = fakeable_leptons;
                        auto allobjsTLV = getsumTLV(leptons,cleanedjets);
                        if (fillCRhists) th1d[category[sys]+"__MHT.JESUP"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__MHT.JESUP"],allobjsTLV.Pt()),weight);
                        if (fillCRhists) th1d[category[sys]+"__met.JESUP"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__met.JESUP"],(*met_intree)[0].obj.Pt()),weight);
                        int numleps = leptons.size();
                        double total_ht = 0.;
                        if (fillCRhists) for (const auto & lep : leptons) 
                        {
                            th1d[category[sys]+"__lepeta.JESUP"]->Fill(lep.obj.Eta(),weight);
                            total_ht += lep.obj.Pt();
                        }
                        if (fillCRhists) th1d[category[sys]+"__njets.JESUP"]->Fill(jetsize,weight);
                        if (fillCRhists) th1d[category[sys]+"__nbjets.JESUP"]->Fill(taggedjetsloosesize,weight);
                        for (const auto & jet : cleanedjets)
                        {
                            if (fillCRhists) th1d[category[sys]+"__jetpt.JESUP"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__jetpt.JESUP"],jet.obj.Pt()),weight);
                            if (fillCRhists) th1d[category[sys]+"__jeteta.JESUP"]->Fill(jet.obj.Eta(),weight);
                            if (fillCRhists) th1d[category[sys]+"__jetDeepCSV.JESUP"]->Fill(jet.DeepCSV,weight);
                            if (fillCRhists) th1d[category[sys]+"__PUMVA.JESUP"]->Fill(jet.PUMVA,weight);
                            total_ht += jet.obj.Pt();
                        }
                        if (fillCRhists) th1d[category[sys]+"__HT.JESUP"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__HT.JESUP"],total_ht),weight);
                        if (fillCRhists) th1d[category[sys]+"__lep1pt.JESUP"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__lep1pt.JESUP"],leptons[0].obj.Pt()),weight);
                        if (numleps>1)
                        {
                            if (fillCRhists) th1d[category[sys]+"__lep2pt.JESUP"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__lep2pt.JESUP"],leptons[1].obj.Pt()),weight);
                            for (int i=0; i<(numleps-1); i++)
                            {
                                for (int j=i+1; j<numleps; j++)
                                {
                                    if ((leptons[i].charge+leptons[j].charge)==0)
                                    {
                                        auto obj12 = leptons[i].obj + leptons[j].obj;
                                        if (fillCRhists) th1d[category[sys]+"__llmass.JESUP"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__llmass.JESUP"],obj12.M()),weight);
                                    }
                                }
                            }
                        }
                        
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
                                
                                double njets4hist = min(jetsize,th1eft[lbcat+".JESUP"]->GetXaxis()->GetXmax()-0.1);

                                if (sample<90)
                                {
                                    int thebin = th1eft[lbcat+".JESUP"]->FindBin(njets4hist);
                                    weight = *wgt_intree;
                                    weight *= totalSF(sys,category,thebin);
                                }                                
                                
                                //th1d[lbcat+".JESUP"]->Fill(jetsize,weight); // regular TH1D
                                if (debug) cout <<"here2"<<endl;
                                th1eft[lbcat+".JESUP"]->Fill(njets4hist,weight,getEventFit(weight)); // using the TH1EFT class
                                if (debug) cout<<"here3"<<endl;

                            }
                        }
                
                    }
            
                    else if (sys==2)
                    {
                    
                        if (debug) cout << "inside " << systr << endl;
                        //auto cleanedjets = simpleCut(preselected_jets_JECdown,"pt",30.0);
                        auto cleanedjets = preselected_jets_JECdown;
                        auto taggedjetsmedium = keepTagged(cleanedjets,"DM");
                        auto taggedjetsloose = keepTagged(cleanedjets,"DL");
                        
                        double jetsize = cleanedjets.size();
                        
                        double taggedjetsmediumsize = taggedjetsmedium.size();
                        double taggedjetsloosesize = taggedjetsloose.size();
                        
                        string jtcat = getjettagcategory(category[sys],jetsize,taggedjetsloosesize);
                        string lbcat = gettagcategory(category[sys],taggedjetsmediumsize,taggedjetsloosesize);

                        if (isSR)
                        {
                            if (lbcat=="null") continue;
                                                        // 2017 SFs
                            if (sample<90) // (Dec. 2018) in practice it's safe to do <100, but <90 is more clear
                            {
                                double njets4hist = min(jetsize,th1eft[lbcat+".JESDOWN"]->GetXaxis()->GetXmax()-0.1);
                                int thebin = th1eft[lbcat+".JESDOWN"]->FindBin(njets4hist);
                                weight = *wgt_intree; // the data-driven background weights don't get applied to MC
                                weight *= totalSF(sys,category,thebin);
                            }
                        }
                        else
                        {
                            if (sample<90) 
                            {
                                weight = *wgt_intree;
                                weight *= totalSF(sys,category); // now includes JES btagging syst.
                            }
                        }
                        if (sample>=84 && sample<=88) weight = getEventFit(weight).evalPoint(&smpt); // only for non-main-result hists!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        
                        if (fillCRhists) th1d[category[sys]+"__ntaus.JESDOWN"]->Fill((*selected_taus_intree).size(),weight);

                        auto untaggedjetsmedium = keepUnTagged(cleanedjets,"DM"); // these only get used in the line below
                        if (fillCRhists) th1d[category[sys]+"__hadtopmass.JESDOWN"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__hadtopmass.JESDOWN"],had_top_mass(taggedjetsmedium,untaggedjetsmedium)),weight);

                        auto leptons = tight_leptons;
                        if (dofakes) leptons = fakeable_leptons;
                        auto allobjsTLV = getsumTLV(leptons,cleanedjets);
                        if (fillCRhists) th1d[category[sys]+"__MHT.JESDOWN"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__MHT.JESDOWN"],allobjsTLV.Pt()),weight);
                        if (fillCRhists) th1d[category[sys]+"__met.JESDOWN"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__met.JESDOWN"],(*met_intree)[0].obj.Pt()),weight);
                        int numleps = leptons.size();
                        double total_ht = 0.;
                        if (fillCRhists) for (const auto & lep : leptons) 
                        {
                            th1d[category[sys]+"__lepeta.JESDOWN"]->Fill(lep.obj.Eta(),weight);
                            total_ht += lep.obj.Pt();
                        }
                        if (fillCRhists) th1d[category[sys]+"__njets.JESDOWN"]->Fill(jetsize,weight);
                        if (fillCRhists) th1d[category[sys]+"__nbjets.JESDOWN"]->Fill(taggedjetsloosesize,weight);
                        for (const auto & jet : cleanedjets)
                        {
                            if (fillCRhists) th1d[category[sys]+"__jetpt.JESDOWN"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__jetpt.JESDOWN"],jet.obj.Pt()),weight);
                            if (fillCRhists) th1d[category[sys]+"__jeteta.JESDOWN"]->Fill(jet.obj.Eta(),weight);
                            if (fillCRhists) th1d[category[sys]+"__jetDeepCSV.JESDOWN"]->Fill(jet.DeepCSV,weight);
                            if (fillCRhists) th1d[category[sys]+"__PUMVA.JESDOWN"]->Fill(jet.PUMVA,weight);
                            total_ht += jet.obj.Pt();
                        }
                        if (fillCRhists) th1d[category[sys]+"__HT.JESDOWN"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__HT.JESDOWN"],total_ht),weight);                        
                        if (fillCRhists) th1d[category[sys]+"__lep1pt.JESDOWN"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__lep1pt.JESDOWN"],leptons[0].obj.Pt()),weight);
                        if (numleps>1)
                        {
                            if (fillCRhists) th1d[category[sys]+"__lep2pt.JESDOWN"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__lep2pt.JESDOWN"],leptons[1].obj.Pt()),weight);
                            for (int i=0; i<(numleps-1); i++)
                            {
                                for (int j=i+1; j<numleps; j++)
                                {
                                    if ((leptons[i].charge+leptons[j].charge)==0)
                                    {
                                        auto obj12 = leptons[i].obj + leptons[j].obj;
                                        if (fillCRhists) th1d[category[sys]+"__llmass.JESDOWN"]->Fill(fillHistOverflowAware(th1d[category[sys]+"__llmass.JESDOWN"],obj12.M()),weight);

                                    }
                                }
                            }                            
                        }

                        if (jtcat!="null" && category[sys].substr(0,2)!="1l")
                        {
                            int thisbin = th1d["category_yields_njets_nbjets_JESDOWN"]->GetXaxis()->FindBin(jtcat.c_str());
                            th1d["category_yields_njets_nbjets_JESDOWN"]->Fill(thisbin,weight);
                            if (lbcat!="null")
                            {
                                double njets4hist = min(jetsize,th1eft[lbcat+".JESDOWN"]->GetXaxis()->GetXmax()-0.1);
                                if (sample<90)
                                {
                                    int thebin = th1eft[lbcat+".JESDOWN"]->FindBin(njets4hist);
                                    weight = *wgt_intree;
                                    weight *= totalSF(sys,category,thebin); // the PS weight is a fn of njet bin
                                }
                                
                                //th1d[lbcat+".JESDOWN"]->Fill(jetsize,weight); // regular TH1D
                                th1eft[lbcat+".JESDOWN"]->Fill(njets4hist,weight,getEventFit(weight)); // using the TH1EFT class
                            }
                        }                    
                    }
                    else if (sys>=3 && sys<=6)
                    {
                        if (debug) cout << "inside " << systr << endl;
                        
                        auto cleanedjets = preselected_jets;
                        auto taggedjetsmedium = keepTagged(cleanedjets,"DM");
                        auto taggedjetsloose = keepTagged(cleanedjets,"DL");
                        double jetsize = cleanedjets.size();
                        
                        double taggedjetsmediumsize = taggedjetsmedium.size();
                        double taggedjetsloosesize = taggedjetsloose.size();
                        
                        string jtcat = getjettagcategory(category[0],jetsize,taggedjetsloosesize); // category[0] -> not a mistake!
                        string lbcat = gettagcategory(category[0],taggedjetsmediumsize,taggedjetsloosesize);

                        if (isSR)
                        {
                            if (lbcat=="null") continue;
                        }
                    
                        if (sample<90) 
                        {
                            cout << "trying to apply fake rate systs to non-data sample" << endl;
                        }
                        
                        if (fillCRhists) th1d[category[0]+"__ntaus."+systr]->Fill((*selected_taus_intree).size(),weight);

                        auto untaggedjetsmedium = keepUnTagged(cleanedjets,"DM"); // these only get used in the line below
                        if (fillCRhists) th1d[category[0]+"__hadtopmass."+systr]->Fill(fillHistOverflowAware(th1d[category[0]+"__hadtopmass."+systr],had_top_mass(taggedjetsmedium,untaggedjetsmedium)),weight);
                        
                        auto leptons = tight_leptons;
                        if (dofakes) leptons = fakeable_leptons;
                        auto allobjsTLV = getsumTLV(leptons,cleanedjets);
                        if (fillCRhists) th1d[category[0]+"__MHT."+systr]->Fill(fillHistOverflowAware(th1d[category[0]+"__MHT."+systr],allobjsTLV.Pt()),weight);
                        if (fillCRhists) th1d[category[0]+"__met."+systr]->Fill(fillHistOverflowAware(th1d[category[0]+"__met."+systr],(*met_intree)[0].obj.Pt()),weight);
                        int numleps = leptons.size();
                        double total_ht = 0.;
                        if (fillCRhists) for (const auto & lep : leptons) 
                        {
                            th1d[category[0]+"__lepeta."+systr]->Fill(lep.obj.Eta(),weight);
                            total_ht += lep.obj.Pt();
                        }
                        if (fillCRhists) th1d[category[0]+"__njets."+systr]->Fill(jetsize,weight);
                        if (fillCRhists) th1d[category[0]+"__nbjets."+systr]->Fill(taggedjetsloosesize,weight);
                        for (const auto & jet : cleanedjets)
                        {
                            if (fillCRhists) th1d[category[0]+"__jetpt."+systr]->Fill(fillHistOverflowAware(th1d[category[0]+"__jetpt."+systr],jet.obj.Pt()),weight);
                            if (fillCRhists) th1d[category[0]+"__jeteta."+systr]->Fill(jet.obj.Eta(),weight);
                            if (fillCRhists) th1d[category[0]+"__jetDeepCSV."+systr]->Fill(jet.DeepCSV,weight);
                            if (fillCRhists) th1d[category[0]+"__PUMVA."+systr]->Fill(jet.PUMVA,weight);
                            total_ht += jet.obj.Pt();
                        }
                        if (fillCRhists) th1d[category[0]+"__HT."+systr]->Fill(fillHistOverflowAware(th1d[category[0]+"__HT."+systr],total_ht),weight);                        
                        if (fillCRhists) th1d[category[0]+"__lep1pt."+systr]->Fill(fillHistOverflowAware(th1d[category[0]+"__lep1pt."+systr],leptons[0].obj.Pt()),weight);
                        if (numleps>1)
                        {
                            if (fillCRhists) th1d[category[0]+"__lep2pt."+systr]->Fill(fillHistOverflowAware(th1d[category[0]+"__lep2pt."+systr],leptons[1].obj.Pt()),weight);
                            for (int i=0; i<(numleps-1); i++)
                            {
                                for (int j=i+1; j<numleps; j++)
                                {
                                    if ((leptons[i].charge+leptons[j].charge)==0)
                                    {
                                        auto obj12 = leptons[i].obj + leptons[j].obj;
                                        if (fillCRhists) th1d[category[0]+"__llmass."+systr]->Fill(fillHistOverflowAware(th1d[category[0]+"__llmass."+systr],obj12.M()),weight);

                                    }
                                }
                            }                            
                        }
                        
                        if (jtcat!="null" && category[0].substr(0,2)!="1l")
                        {
                            if (lbcat!="null")
                            {
                                //th1d[lbcat+".JESDOWN"]->Fill(jetsize,weight); // regular TH1D
                                if (debug) cout << "inside fr systs" << endl;
                                if (sys==3) th1eft[lbcat+".FRUP"]->Fill(min(jetsize,th1eft[lbcat+".FRUP"]->GetXaxis()->GetXmax()-0.1),weight,getEventFit(weight)); // using the TH1EFT class
                                else if (sys==4) th1eft[lbcat+".FRDOWN"]->Fill(min(jetsize,th1eft[lbcat+".FRDOWN"]->GetXaxis()->GetXmax()-0.1),weight,getEventFit(weight)); // using the TH1EFT class
                                else if (sys==5) th1eft[lbcat+".FRQCD"]->Fill(min(jetsize,th1eft[lbcat+".FRQCD"]->GetXaxis()->GetXmax()-0.1),weight,getEventFit(weight)); // using the TH1EFT class
                                else if (sys==6) th1eft[lbcat+".FRTTBAR"]->Fill(min(jetsize,th1eft[lbcat+".FRTTBAR"]->GetXaxis()->GetXmax()-0.1),weight,getEventFit(weight)); // using the TH1EFT class
                            }
                        }                    
                    }                    
                    else
                    {
                        if (debug) cout << "inside " << systr << endl;
                        auto cleanedjets = preselected_jets;
                        auto taggedjetsmedium = keepTagged(cleanedjets,"DM");
                        auto taggedjetsloose = keepTagged(cleanedjets,"DL");
                        double jetsize = cleanedjets.size();
                        double taggedjetsmediumsize = taggedjetsmedium.size();
                        double taggedjetsloosesize = taggedjetsloose.size();
                        string jtcat = getjettagcategory(category[catSys],jetsize,taggedjetsloosesize);
                        string lbcat = gettagcategory(category[catSys],taggedjetsmediumsize,taggedjetsloosesize);
                        
                        if (isSR)
                        {
                            if (lbcat=="null") continue;
                            // 2017 SFs
                            if (sample<90) // (Dec. 2018) in practice it's safe to do <100, but <90 is more clear
                            {
                                double njets4hist = min(jetsize,th1eft[lbcat+"."+string(systr)]->GetXaxis()->GetXmax()-0.1);
                                int thebin = th1eft[lbcat+"."+string(systr)]->FindBin(njets4hist);
                                weight = *wgt_intree; // the data-driven background weights don't get applied to MC
                                weight *= totalSF(sys,category,thebin);
                            }
                        }                        
                        else
                        {
                            if (sample<90)
                            {
                                weight = *wgt_intree;
                                weight *= totalSF(sys,category);
                            }
                        }
                        if (sample>=84 && sample<=88) weight = getEventFit(weight).evalPoint(&smpt); // only for non-main-result hists!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                        if (fillCRhists) th1d[category[catSys]+"__ntaus."+systr]->Fill((*selected_taus_intree).size(),weight);

                        auto untaggedjetsmedium = keepUnTagged(cleanedjets,"DM"); // these only get used in the line below
                        if (fillCRhists) th1d[category[catSys]+"__hadtopmass."+systr]->Fill(fillHistOverflowAware(th1d[category[catSys]+"__hadtopmass."+systr],had_top_mass(taggedjetsmedium,untaggedjetsmedium)),weight);
                        
                        auto leptons = tight_leptons;
                        if (dofakes) leptons = fakeable_leptons;
                        auto allobjsTLV = getsumTLV(leptons,cleanedjets);
                        if (fillCRhists) th1d[category[catSys]+"__MHT."+systr]->Fill(fillHistOverflowAware(th1d[category[catSys]+"__MHT."+systr],allobjsTLV.Pt()),weight);
                        if (fillCRhists) th1d[category[catSys]+"__met."+systr]->Fill(fillHistOverflowAware(th1d[category[catSys]+"__met."+systr],(*met_intree)[0].obj.Pt()),weight);
                        int numleps = leptons.size();
                        double total_ht = 0.;
                        if (fillCRhists) for (const auto & lep : leptons) 
                        {
                            th1d[category[catSys]+"__lepeta."+systr]->Fill(lep.obj.Eta(),weight);
                            total_ht += lep.obj.Pt();
                        }
                        if (fillCRhists) th1d[category[catSys]+"__njets."+systr]->Fill(jetsize,weight);
                        if (fillCRhists) th1d[category[catSys]+"__nbjets."+systr]->Fill(taggedjetsloosesize,weight);
                        for (const auto & jet : cleanedjets)
                        {
                            if (fillCRhists) th1d[category[catSys]+"__jetpt."+systr]->Fill(fillHistOverflowAware(th1d[category[catSys]+"__jetpt."+systr],jet.obj.Pt()),weight);
                            if (fillCRhists) th1d[category[catSys]+"__jeteta."+systr]->Fill(jet.obj.Eta(),weight);
                            if (fillCRhists) th1d[category[catSys]+"__jetDeepCSV."+systr]->Fill(jet.DeepCSV,weight);
                            if (fillCRhists) th1d[category[catSys]+"__PUMVA."+systr]->Fill(jet.PUMVA,weight);
                            total_ht += jet.obj.Pt();
                        }
                        if (fillCRhists) th1d[category[catSys]+"__HT."+systr]->Fill(fillHistOverflowAware(th1d[category[catSys]+"__HT."+systr],total_ht),weight);                                                
                        if (fillCRhists) th1d[category[catSys]+"__lep1pt."+systr]->Fill(fillHistOverflowAware(th1d[category[catSys]+"__lep1pt."+systr],leptons[0].obj.Pt()),weight);
                        if (numleps>1)
                        {
                            if (fillCRhists) th1d[category[catSys]+"__lep2pt."+systr]->Fill(fillHistOverflowAware(th1d[category[catSys]+"__lep2pt."+systr],leptons[1].obj.Pt()),weight);
                            for (int i=0; i<(numleps-1); i++)
                            {
                                for (int j=i+1; j<numleps; j++)
                                {
                                    if ((leptons[i].charge+leptons[j].charge)==0)
                                    {
                                        auto obj12 = leptons[i].obj + leptons[j].obj;
                                        if (fillCRhists) th1d[category[catSys]+"__llmass."+systr]->Fill(fillHistOverflowAware(th1d[category[catSys]+"__llmass."+systr],obj12.M()),weight);

                                    }
                                }
                            }                            
                        }
                        
                        if (jtcat!="null" && category[catSys].substr(0,2)!="1l")
                        {
                            if (lbcat!="null")
                            {
                                double njets4hist = min(jetsize,th1eft[lbcat+"."+string(systr)]->GetXaxis()->GetXmax()-0.1);
                                //if ((sys==37 || sys==38 || sys==45 || sys==46) && sample<90)
                                if (sample<90)
                                {
                                    int thebin = th1eft[lbcat+"."+string(systr)]->FindBin(njets4hist);
                                    weight = *wgt_intree;
                                    weight *= totalSF(sys,category,thebin); // the PS weight is a fn of njet bin
                                }
                                th1eft[lbcat+"."+string(systr)]->Fill(njets4hist,weight,getEventFit(weight)); // using the TH1EFT class
                            }
                        }                    
                    }
                    
                
                } // non-null cat
            } // end loop over systs
        } // end loop over filling of charge flip hists
    } // passed trig
}
