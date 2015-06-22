bool MakeGoodPlot::passes_common(int sample_number)
{
    
    auto taggedjetstight = keepTagged(*preselected_jets_intree,"M");
    auto taggedjetsloose = keepUnTagged(*preselected_jets_intree,"L");
    
    bool passes = true;
    
    if (!(((*preselected_leptons_intree).size()>3) || ((*tightMvaBased_leptons_intree).size()>1))) passes=false;       

    double mindilepmass = getTwoObjKineExtreme(*preselected_leptons_intree,"min","mass"); 
           
    if (!(mindilepmass>12)) passes=false;                 
//    if (!((*preselected_leptons_intree)[0].obj.Pt()>20 && (*preselected_leptons_intree)[1].obj.Pt()>10)) passes=false;        
    if (!((*preselected_jets_intree).size()>1)) passes=false;
    if (!( (taggedjetsloose.size()>1) || (taggedjetstight.size()>0) )) passes=false;
    
    return passes;

}
bool MakeGoodPlot::passes_SSee(int sample_number)
{
    bool passes = false;
    
    if ( ((*tightMvaBased_electrons_intree).size()==2) && ((*tightMvaBased_muons_intree).size()==0) && ((*looseMvaBased_leptons_intree).size()<4) ) 
    {
        if ((*tightMvaBased_electrons_intree)[0].charge==(*tightMvaBased_electrons_intree)[1].charge)
        {
            if ((*preselected_jets_intree).size()>3)
            {
                auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                double MHT_handle = objs_for_mht.Pt();
                double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                if (metLD_handle> 0.2)
                {
//                    if ((*tightMvaBased_electrons_intree)[0].obj.Pt()>20 && (*tightMvaBased_electrons_intree)[1].obj.Pt()>20)
//                    {
                        if (((*tightMvaBased_electrons_intree)[0].obj.Pt() + (*tightMvaBased_electrons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                        {
                            double vetoZmass = pickFromSortedTwoObjKine(*preselected_electrons_intree,"mass",1,91.2);

                            if (fabs(vetoZmass-91.2)>10)                     
                            {
                                if ((*tightMvaBased_electrons_intree)[0].isGsfCtfScPixChargeConsistent && (*tightMvaBased_electrons_intree)[1].isGsfCtfScPixChargeConsistent)
                                {
                                    passes = true;
                                }
                            }
                        }
//                    }
                }
            }
        }
    }
    
    return passes;
}
bool MakeGoodPlot::passes_SSmumu(int sample_number)
{
    bool passes = false;
    
    if ( ((*tightMvaBased_electrons_intree).size()==0) && ((*tightMvaBased_muons_intree).size()==2) && ((*looseMvaBased_leptons_intree).size()<4) ) 
    {
        if ((*tightMvaBased_muons_intree)[0].charge==(*tightMvaBased_muons_intree)[1].charge)
        {            
            if ((*preselected_jets_intree).size()>3)
            {                
                auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                double MHT_handle = objs_for_mht.Pt();
                double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                if (metLD_handle> 0.2)
                {                    
//                    if ((*tightMvaBased_muons_intree)[0].obj.Pt()>20 && (*tightMvaBased_muons_intree)[1].obj.Pt()>20)
//                    {                        
                        if (((*tightMvaBased_muons_intree)[0].obj.Pt() + (*tightMvaBased_muons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                        {                            
                            if ((*tightMvaBased_muons_intree)[0].chargeFlip<0.2 && (*tightMvaBased_muons_intree)[1].chargeFlip<0.2)
                            {                                    
                                passes = true;
                            }
                        }
//                    }
                }
            }
        }
    }
    
    return passes;
}
bool MakeGoodPlot::passes_SSemu(int sample_number)
{
    bool passes = false;
    
    if ( ((*tightMvaBased_electrons_intree).size()==1) && ((*tightMvaBased_muons_intree).size()==1) && ((*looseMvaBased_leptons_intree).size()<4) ) 
    {
        if ((*tightMvaBased_electrons_intree)[0].charge==(*tightMvaBased_muons_intree)[0].charge)
        {
            if ((*preselected_jets_intree).size()>3)
            {
                auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                double MHT_handle = objs_for_mht.Pt();
                double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                if (metLD_handle> 0.2)
                {
//                    if ((*tightMvaBased_muons_intree)[0].obj.Pt()>20 && (*tightMvaBased_electrons_intree)[0].obj.Pt()>20)
//                    {
                        if (((*tightMvaBased_muons_intree)[0].obj.Pt() + (*tightMvaBased_electrons_intree)[0].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                        {
                            if ((*tightMvaBased_muons_intree)[0].chargeFlip<0.2 && (*tightMvaBased_electrons_intree)[0].isGsfCtfScPixChargeConsistent)
                            {                                    
                                passes = true;
                            }
                        }
//                    }
                }
            }
        }
    }
    
    return passes;
}
bool MakeGoodPlot::passes_3l(int sample_number)
{
    bool passes = false;
    
    if ( ((*tightMvaBased_leptons_intree).size()==3) && ((*looseMvaBased_leptons_intree).size()<4) ) 
    {
        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
        double MHT_handle = objs_for_mht.Pt();
        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

        if ((metLD_handle>0.2) || ((*preselected_jets_intree).size()>3))
        {
            double vetoZmassSFOS = pickFromSortedTwoObjKine(*tightMvaBased_leptons_intree,"massSFOS",1,91.2);

            if (fabs(vetoZmassSFOS-91.2)>10.)                     
            {        
                passes = true;
            }
        }
    }
    
    return passes;
}
bool MakeGoodPlot::passes_4l(int sample_number)
{
    bool passes = false;
    
    if ((*looseMvaBased_leptons_intree).size()==4)
    {
        if ( ((*looseMvaBased_leptons_intree)[0].charge + (*looseMvaBased_leptons_intree)[1].charge + (*looseMvaBased_leptons_intree)[2].charge + (*looseMvaBased_leptons_intree)[3].charge)==0 )
        {
            double vetoZmassSFOS = pickFromSortedTwoObjKine(*looseMvaBased_leptons_intree,"massSFOS",1,91.2);

            if (fabs(vetoZmassSFOS-91.2)>10.)                     
            {        
                 passes = true;
            }
        }
    }
    
    return passes;
}

