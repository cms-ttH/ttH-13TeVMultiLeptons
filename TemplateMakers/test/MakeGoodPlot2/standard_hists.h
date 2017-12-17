void HistMaker::standard_hists()
{
    double weight = *wgt_intree;
    
    string category = eventselection();
    
    if (category!="null") 
    {
                
        std::vector<ttH::Jet> cutjets = simpleCut<std::vector<ttH::Jet> >(*loose_jets_intree,"pt",25.0); // need to be careful with this (problem if type not explicitly specified)
        
        auto taggedjetsmedium = keepTagged(cutjets,"M");        
        auto taggedjetsloose = keepTagged(cutjets,"L");

        double jetsize = cutjets.size();                
        double taggedjetssize = taggedjetsmedium.size();
        double taggedjetsloosesize = taggedjetsloose.size();
        
        bool pass = false;
        if (jetsize>3)
        {
            if (taggedjetssize>0 || taggedjetsloosesize>1) pass=true;
        }
        
        if (!pass) return;
        
        th1d[category+"__njets"]->Fill(jetsize,weight);               
        th1d[category+"__nbjets"]->Fill(taggedjetssize,weight);        
        th2d[category+"__nbjets_vs_njets"]->Fill(jetsize,taggedjetssize,weight);
         
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
