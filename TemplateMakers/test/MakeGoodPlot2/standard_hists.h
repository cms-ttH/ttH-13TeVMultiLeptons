void HistMaker::standard_hists()
{
    double weight = *wgt_intree;
    
    string category = eventselection();
    
    if (category!="null") 
    {

        //std::vector<ttH::Jet> cutjets = simpleCut<std::vector<ttH::Jet> >(*loose_jets_intree,"pt",25.0); // need to be careful with this (problem if type not explicitly specified)
    
        //auto taggedjetsmedium = keepTagged(cutjets,"M");        
        //auto taggedjetsloose = keepTagged(cutjets,"L");
        auto taggedjetsmedium = keepTagged(*preselected_jets_intree,"M");
        auto taggedjetsloose = keepTagged(*preselected_jets_intree,"L");
    
    
        //double jetsize = cutjets.size();                
        double jetsize = preselected_jets_intree->size();
        double taggedjetssize = taggedjetsmedium.size();
        double taggedjetsloosesize = taggedjetsloose.size();
    
        bool pass = false;
        if (jetsize>2) // >3
        {
            pass=true;
            //if (taggedjetssize>0 || taggedjetsloosesize>1) pass=true;
        }
    
        if (!pass) return;
    
        // this SF section eventually should be bigger / have more stuff:
        if (sample<100) for (const auto & lep : *tight_leptons_intree) 
        {
            // For 2016 data/MC, this is the combined reco+POGID+lepMVA SF:
            if (category.substr(0,2)=="2l") weight *= leptonSF_ttH(lep.pdgID, lep.obj.Pt(), lep.obj.Eta(), 2);
            else weight *= leptonSF_ttH(lep.pdgID, lep.obj.Pt(), lep.obj.Eta(), 3);
        }
        
        bool passedtrig = passesAnyTrigger();
            
        th1d["single_ele_trigs"]->Fill(passesDatasetDependentTriggers(101),weight);
        th1d["double_ele_trigs"]->Fill(passesDatasetDependentTriggers(103),weight);
        th1d["single_mu_trigs"]->Fill(passesDatasetDependentTriggers(100),weight);
        th1d["double_mu_trigs"]->Fill(passesDatasetDependentTriggers(102),weight);
        th1d["mu_ele_trigs"]->Fill(passesDatasetDependentTriggers(104),weight);
        th1d["all_trigs"]->Fill(passedtrig,weight);
        th1d[category+"__all_trigs"]->Fill(passedtrig,weight);
        
        if (removeDatasetOverlaps() && passedtrig)
        {          
            
            th1d[category+"__njets"]->Fill(jetsize,weight);               
            th1d[category+"__nbjets"]->Fill(taggedjetssize,weight);        
            th2d[category+"__nbjets_vs_njets"]->Fill(jetsize,taggedjetssize,weight);
         
         
            for (const auto & jet : *preselected_jets_intree)
            {
            
                th1d[category+"__jetpt"]->Fill(jet.obj.Pt(),weight);
                th1d[category+"__jeteta"]->Fill(jet.obj.Eta(),weight);
                th1d[category+"__jetcsv"]->Fill(jet.csv,weight);
            
            }
        
            for (const auto & lep : *tight_leptons_intree)
            {
                th1d[category+"__leppt"]->Fill(lep.obj.Pt(),weight);
                th1d[category+"__lepeta"]->Fill(lep.obj.Eta(),weight);    
            }
        
            th1d[category+"__met"]->Fill((*met_intree)[0].obj.Pt(),weight);
            th1d[category+"__metphi"]->Fill((*met_intree)[0].obj.Phi(),weight);
         
         
            int thisbin = th1d["category_yields"]->GetXaxis()->FindBin(category.c_str());
            th1d["category_yields"]->Fill(thisbin,weight);

            //thisbin = th1d["category_yields_noOS"]->GetXaxis()->FindBin(category.c_str());
            //th1d["category_yields_noOS"]->Fill(thisbin,weight);

        
        

    //     int nummuons = (*tight_muons_intree).size();
    //     int numeles = (*tight_electrons_intree).size();    
    //     int numleps = numeles+nummuons;
    //     
    //     if (numleps>1)
    //     {    
    //         double mindilepmass = getTwoObjKineExtreme(*tight_leptons_intree,"min","mass");
    //            
    //         if (mindilepmass>12)
    //         {            
    //             if (numleps==2)
    //             {
    //                 // SS2l
    //                 if ((*tight_leptons_intree)[0].charge == (*tight_leptons_intree)[1].charge)
    //                 {                
    //                     if ((*tight_leptons_intree)[0].charge+(*tight_leptons_intree)[1].charge == -2)
    //                     {
    //                         if (nummuons==2)
    //                         {
    //                         
    //                             double jetsize = 0.;
    // 
    //                             for (int i=0; i<(*loose_jets_intree).size(); i++)
    //                             {
    //                                 if ( (*loose_jets_intree)[i].obj.Pt()>25.) 
    //                                 {
    //                                     jetsize += 1.0;
    //                                 }
    //                             }
    // 
    //                             if (weight!=1. &&  weight!=-1.) cout << weight << endl;
    //                             if (jetsize<0 || jetsize>100) cout << jetsize << endl;
    // 
    //                             //th1d[category+"__njets"]->Fill(jetsize,weight);
    //                             th1d["2lss_m_mumu__njets"]->Fill(jetsize,weight);
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }

        }
    }
}
