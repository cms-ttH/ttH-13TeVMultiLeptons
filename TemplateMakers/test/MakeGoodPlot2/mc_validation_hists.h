void HistMaker::mc_validation_hists()
{
    double weight = *wgt_intree;
    
    
    //EFT reweighting...    
    if (sample>=40 && sample<100)
    {
        for (const auto thispair : *eftwgts_intree)
        {
            WCPoint thiswgt(thispair.first,thispair.second);
            if (thiswgt.isSMPoint()) // pick a point to reweight to
            {
                weight *= thispair.second / 2000.; // / (*originalXWGTUP_intree); // check this -> actually, don't think we want to divide by this here.
                break;
            }
        }
    }
    
    
    auto taggedjetsmedium = keepTagged(*preselected_jets_intree,"M"); // these are csv v2 tagged jets
    auto taggedjetsloose = keepTagged(*preselected_jets_intree,"L");


    //double jetsize = cutjets.size();                
    double jetsize = preselected_jets_intree->size();
    double taggedjetssize = taggedjetsmedium.size();
    double taggedjetsloosesize = taggedjetsloose.size();

    int nummuons = tight_muons_intree->size();
    int numeles = tight_electrons_intree->size();

    int numleps = numeles+nummuons;

    string category = "all";

    // filter on higgs decay:
    if (abs(*higgsdecay_intree)!=5)
    {     
            
        th1d[category+"__njets"]->Fill(jetsize,weight);               
        th1d[category+"__nbjets"]->Fill(taggedjetssize,weight);        
        //th2d[category+"__nbjets_vs_njets"]->Fill(jetsize,taggedjetssize,weight);
        th1d[category+"__numPVs"]->Fill((*numPVs_intree),weight);
 
        for (const auto & jet : *preselected_jets_intree)
        {
            th1d[category+"__jetpt"]->Fill(jet.obj.Pt(),weight);
            th1d[category+"__jeteta"]->Fill(jet.obj.Eta(),weight);
            th1d[category+"__jetcsv"]->Fill(jet.csv,weight);
            th1d[category+"__jetDeepCSVprobb"]->Fill(jet.DeepCSVprobb,weight);
            th1d[category+"__jetDeepCSVprobbb"]->Fill(jet.DeepCSVprobbb,weight);
            th1d[category+"__jetDeepCSVprobc"]->Fill(jet.DeepCSVprobc,weight);
            th1d[category+"__jetDeepCSVprobudsg"]->Fill(jet.DeepCSVprobudsg,weight);
            th1d[category+"__PUMVA"]->Fill(jet.PUMVA,weight);
            th1d[category+"__jet_pdgID"]->Fill(jet.genPdgID,weight);
            th1d[category+"__jet_mom_pdgID"]->Fill(jet.genMotherPdgID,weight);
            th1d[category+"__jet_gmom_pdgID"]->Fill(jet.genGrandMotherPdgID,weight);

        }

        for (const auto & lep : *tight_leptons_intree)
        {
            th1d[category+"__leppt"]->Fill(lep.obj.Pt(),weight);
            th1d[category+"__lepeta"]->Fill(lep.obj.Eta(),weight);   
            th1d[category+"__lepMVA"]->Fill(lep.lepMVA,weight);
            th1d[category+"__dxy"]->Fill(lep.dxy,weight);
            th1d[category+"__dz"]->Fill(lep.dz,weight);
            th1d[category+"__miniIso"]->Fill(lep.miniIso,weight);
        
        }
    
        if (numleps>0) th1d[category+"__lep1pt"]->Fill((*tight_leptons_intree)[0].obj.Pt(),weight);
        if (numleps>1)
        {
            th1d[category+"__lep2pt"]->Fill((*tight_leptons_intree)[1].obj.Pt(),weight);
            auto obj12 = (*tight_leptons_intree)[0].obj + (*tight_leptons_intree)[1].obj;
            th1d[category+"__llmass"]->Fill(obj12.M(),weight);
        }
    
        auto allobjsTLV = getsumTLV(*tight_leptons_intree,*preselected_jets_intree);
        th1d[category+"__MHT"]->Fill(allobjsTLV.Pt(),weight);
        th1d[category+"__met"]->Fill((*met_intree)[0].obj.Pt(),weight);
        th1d[category+"__metphi"]->Fill((*met_intree)[0].obj.Phi(),weight);
            
        for (const auto & genparticle : *pruned_genParticles_intree)
        {
            th1d["particle_pdgID"]->Fill(genparticle.pdgID,weight);
            th2d["status_vs_pdgID"]->Fill(genparticle.pdgID,genparticle.status,weight);
            
            if (genparticle.mother<pruned_genParticles_intree->size())
            {
                th1d["mom_pdgID"]->Fill((*pruned_genParticles_intree)[genparticle.mother].pdgID,weight);
                th2d["mom_vs_pdgID"]->Fill(genparticle.pdgID,(*pruned_genParticles_intree)[genparticle.mother].pdgID,weight);
            }   
            if (genparticle.grandmother<pruned_genParticles_intree->size())
            {            
                th1d["gmom_pdgID"]->Fill((*pruned_genParticles_intree)[genparticle.grandmother].pdgID,weight);
                th2d["gmom_vs_pdgID"]->Fill(genparticle.pdgID,(*pruned_genParticles_intree)[genparticle.grandmother].pdgID,weight);
            }
        }
        
        th1d["ngenjets"]->Fill(genJets_intree->size(),weight);
        
        for (const auto & genjet : *genJets_intree)
        {                    
            th1d["gen_jet_energy"]->Fill(genjet.obj.E(),weight);
            th1d["gen_jet_eta"]->Fill(genjet.obj.Eta(),weight);
            th1d["gen_jet_phi"]->Fill(genjet.obj.Phi(),weight);
        }
        
        
    
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
