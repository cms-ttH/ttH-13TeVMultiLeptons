void HistMaker::sync_hists()
{
    bool debug = false;
              
    vector<string> category;
    category.push_back("all");
    int sys=0;
    double weight = 1.;

      
    //std::vector<ttH::Jet> cutjets = simpleCut<std::vector<ttH::Jet> >(*loose_jets_intree,"pt",25.0); // need to be careful with this (problem if type not explicitly specified)
    //std::vector<ttH::Jet> cleanedjets = cleanObjs(*preselected_jets_intree,*preselected_leptons_intree,0.4);
    //auto cleanedjets = simpleCut(*preselected_jets_intree,"pt",30.0);
    ///cleanedjets = simpleJetCut(cleanedjets,"passPUID",0);
    
    auto cleanedjets = *preselected_jets_intree;

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
    
    auto muons = *preselected_muons_intree;
    auto electrons = *preselected_electrons_intree;
    //auto leptons = *preselected_leptons_intree;
    

    
    int nummuons = muons.size();
    int numeles = electrons.size();




    th1d[category[sys]+"__njets"]->Fill(jetsize,weight);   
                
//     th1d[category[sys]+"__nbjets."]->Fill(taggedjetsloosesize,weight);        
//     th2d[category[sys]+"__nbjets_vs_njets"]->Fill(jetsize,taggedjetsloosesize,weight);
//     th1d[category[sys]+"__numPVs"]->Fill((*numPVs_intree),weight);
//     th1d[category[sys]+"__numTruePVs"]->Fill((*numTruePVs_intree),weight);
//     
// 
// 
// 
//     //for (const auto & jet : *preselected_jets_intree)
//     for (const auto & jet : cleanedjets)
//     {
//         th1d[category[sys]+"__jetpt."]->Fill(jet.obj.Pt(),weight);
//         th1d[category[sys]+"__jeteta."]->Fill(jet.obj.Eta(),weight);
//         th1d[category[sys]+"__jetcsv"]->Fill(jet.csv,weight);
//         th1d[category[sys]+"__jetDeepCSV."]->Fill(jet.DeepCSV,weight);
//         th1d[category[sys]+"__jetDeepCSVprobb"]->Fill(jet.DeepCSVprobb,weight);
//         th1d[category[sys]+"__jetDeepCSVprobbb"]->Fill(jet.DeepCSVprobbb,weight);
//         th1d[category[sys]+"__jetDeepCSVprobc"]->Fill(jet.DeepCSVprobc,weight);
//         th1d[category[sys]+"__jetDeepCSVprobudsg"]->Fill(jet.DeepCSVprobudsg,weight);
//         th1d[category[sys]+"__PUMVA"]->Fill(jet.PUMVA,weight);
//         th1d[category[sys]+"__qgid"]->Fill(jet.qgid,weight);
//     }

    
    
    
    
    auto leptons = electrons;
    int numleps = leptons.size();
    int thislep = 1;
    
    if (numleps>=2)
    {
        th1d[category[sys]+"__leppt"]->Fill(leptons[thislep].obj.Pt(),weight);
        th1d[category[sys]+"__lepeta."]->Fill(leptons[thislep].obj.Eta(),weight);   
        th1d[category[sys]+"__lepMVA"]->Fill(leptons[thislep].lepMVA,weight);
        th1d[category[sys]+"__dxy"]->Fill(leptons[thislep].dxy,weight);
        th1d[category[sys]+"__dz"]->Fill(leptons[thislep].dz,weight);
        th1d[category[sys]+"__miniIso"]->Fill(leptons[thislep].miniIso,weight);
        th1d[category[sys]+"__miniIsoR"]->Fill(leptons[thislep].miniIsoR,weight);
        th1d[category[sys]+"__miniIsoCharged"]->Fill(leptons[thislep].miniIsoCharged,weight);
        th1d[category[sys]+"__miniIsoNeutral"]->Fill(leptons[thislep].miniIsoNeutral,weight);
        th1d[category[sys]+"__jetPtRatio"]->Fill(leptons[thislep].jetPtRatio,weight);
        th1d[category[sys]+"__jetPtRel"]->Fill(leptons[thislep].jetPtRel,weight);
        th1d[category[sys]+"__jetcsv"]->Fill(max(leptons[thislep].csv,0.),weight);
        th1d[category[sys]+"__sip3D"]->Fill(leptons[thislep].sip3D,weight);
        th1d[category[sys]+"__jet_nCharged_tracks"]->Fill(leptons[thislep].jet_nCharged_tracks,weight);
        th1d[category[sys]+"__effArea"]->Fill(leptons[thislep].effArea,weight);
        th1d[category[sys]+"__rho"]->Fill(leptons[thislep].rho,weight);
        th1d[category[sys]+"__correctedPt"]->Fill(leptons[thislep].correctedPt,weight);
    
    }

    

    //auto allobjsTLV = getsumTLV(*tight_leptons_intree,*preselected_jets_intree);
//     auto allobjsTLV = getsumTLV(leptons,cleanedjets);
//     th1d[category[sys]+"__MHT"]->Fill(allobjsTLV.Pt(),weight);
//     th1d[category[sys]+"__met"]->Fill((*met_intree)[0].obj.Pt(),weight);
//     th1d[category[sys]+"__metphi"]->Fill((*met_intree)[0].obj.Phi(),weight);
        
                    
            

}
