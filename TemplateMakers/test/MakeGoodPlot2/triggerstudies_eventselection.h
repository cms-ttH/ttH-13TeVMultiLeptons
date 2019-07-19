bool HistMaker::passes_common()
{
    
    auto taggedjetstight = keepTagged(*preselected_jets_intree,"DM");
    auto taggedjetsloose = keepUnTagged(*preselected_jets_intree,"DL");
    
    bool passes = true;
    
    auto cutleps = simpleCut(*tight_leptons_intree,"miniIso",0.4); //bandaid
    if (cutleps.size()!=tight_leptons_intree->size()) passes=false;
    
    if (!(((*preselected_leptons_intree).size()>3) || ((*tight_leptons_intree).size()>1))) passes=false;       

    double mindilepmass = getTwoObjKineExtreme(*preselected_leptons_intree,"min","mass");
           
    if (!(mindilepmass>12)) passes=false;                 
    //if (!((*preselected_leptons_intree)[0].obj.Pt()>20 && (*preselected_leptons_intree)[1].obj.Pt()>10)) passes=false;        
    //if (!((*preselected_jets_intree).size()>1)) passes=false;                                     // <<<---- commented out for trigger SF calc.
    //if (!( (taggedjetsloose.size()>1) || (taggedjetstight.size()>0) )) passes=false;              // <<<---- commented out for trigger SF calc.
    
    return passes;

}

bool HistMaker::passes_2lss()
{
  if ( !( ((*preselected_leptons_intree).size() ==2 && (*tight_leptons_intree).size() == 2) || ((*preselected_leptons_intree).size() == 3 && (*tight_leptons_intree).size() == 2 && (*preselected_leptons_intree)[2].obj.Pt() < (*tight_leptons_intree)[1].obj.Pt() ) ) ) return false;
  //if ( !((*preselected_leptons_intree).size() ==2 && (*tight_leptons_intree).size() == 2) ) return false;
  
  bool is_subleading_ele = (abs((*tight_leptons_intree)[1].pdgID)==11) ? true : false;
  
  if ((*tight_leptons_intree)[0].charge != (*tight_leptons_intree)[1].charge) return false;                                                   // <<<---- commented out for trigger SF calc.
  for (auto &ele: (*tight_electrons_intree)) if (!(ele.isGsfCtfScPixChargeConsistent)) return false;
  for (auto &mu: (*tight_muons_intree)) if (!(mu.chargeFlip < 0.2)) return false;
  if ( !( (*preselected_jets_intree).size()>3 ) ) return false;                                                                                               // <<<---- commented out for trigger SF calc.

  if ( is_subleading_ele && (!((*tight_leptons_intree)[0].obj.Pt()>20 && (*tight_leptons_intree)[1].obj.Pt()>15)) ) return false;
  if ( !((*tight_leptons_intree)[0].obj.Pt()>20 && (*tight_leptons_intree)[1].obj.Pt()>10) ) return false;
  //if ( !(((*tight_leptons_intree)[0].obj.Pt() + (*tight_leptons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.) ) return false;        // <<<---- commented out for trigger SF calc.
//   if ((*tight_electrons_intree).size() ==2 )
//   {
//     double vetoZmass = pickFromSortedTwoObjKine((*preselected_electrons_intree),"mass",1,91.2);
//     if ( !(fabs(vetoZmass-91.2)>10) ) return false;                                                                                                          // <<<---- commented out for trigger SF calc.
// 
//     auto objs_for_mht = getsumTLV((*preselected_leptons_intree),(*preselected_jets_intree));
//     double MHT_handle = objs_for_mht.Pt();
//     double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;
//     if ( !(metLD_handle> 0.2) ) return false;                                                                                                                // <<<---- commented out for trigger SF calc.
// 
//   }
  return true;
}

bool HistMaker::passes_geq3l()
{
    
    if (!((*tight_leptons_intree).size()>=3)) return false;            
    if (!( (*tight_leptons_intree)[0].obj.Pt()>20. && (*tight_leptons_intree)[1].obj.Pt()>10. && (*tight_leptons_intree)[2].obj.Pt()>10. )) return false;
    
    for (auto &ele: (*tight_electrons_intree)) if (!(ele.isGsfCtfScPixChargeConsistent)) return false;
    for (auto &mu: (*tight_muons_intree)) if (!(mu.chargeFlip < 0.2)) return false;    
    
    if (abs((*tight_leptons_intree)[0].charge + (*tight_leptons_intree)[1].charge + (*tight_leptons_intree)[2].charge)!=1) return false;    

    double vetoZmassSFOS = pickFromSortedTwoObjKine(*tight_leptons_intree,"massSFOS",1,91.2);
    if (!(fabs(vetoZmassSFOS-91.2)>10.)) return false;                  
    
    if ((*preselected_jets_intree).size()<4)
    {        
        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
        double MHT_handle = objs_for_mht.Pt();
        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;       
        
        if (metLD_handle<=0.2) return false;
        if ( (vetoZmassSFOS<0) && (metLD_handle<=0.3) ) return false;
    }
    
    return true;
}


//____________________________________________________________________________________________________________________


bool HistMaker::passes_mu2tau()
{
    
}

bool HistMaker::passes_ele2tau()
{
    
}



bool HistMaker::passes_SSee()
{
    bool passes = false;
    
    //if ( ((*tight_electrons_intree).size()==2) && ((*tight_muons_intree).size()==0) && ((*looseMvaBased_leptons_intree).size()<4) ) 
    if ( ((*tight_electrons_intree).size()==2) && ((*tight_muons_intree).size()==0) && ((*preselected_leptons_intree).size()==2) )
    {
        //if ((*tight_electrons_intree)[0].charge==(*tight_electrons_intree)[1].charge) // <<<---- commented out for trigger SF calc.
        //{
            //if ((*preselected_jets_intree).size()>3) // <<<---- commented out for trigger SF calc.
            //{
                auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                double MHT_handle = objs_for_mht.Pt();
                double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                //if (metLD_handle> 0.2)
                //{
//                    if ((*tight_electrons_intree)[0].obj.Pt()>20 && (*tight_electrons_intree)[1].obj.Pt()>20)
//                    {
                        //if (((*tight_electrons_intree)[0].obj.Pt() + (*tight_electrons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                        //{
                            double vetoZmass = pickFromSortedTwoObjKine(*preselected_electrons_intree,"mass",1,91.2);

                            if (fabs(vetoZmass-91.2)>10)                     
                            {
                                if ((*tight_electrons_intree)[0].isGsfCtfScPixChargeConsistent && (*tight_electrons_intree)[1].isGsfCtfScPixChargeConsistent)
                                {
                                    passes = true;
                                }
                            }
                        //}
//                    }
                //}
            //}
        //}
    }
    
    return passes;
}
bool HistMaker::passes_SSmumu()
{
    bool passes = false;
    
    //if ( ((*tight_electrons_intree).size()==0) && ((*tight_muons_intree).size()==2) && ((*looseMvaBased_leptons_intree).size()<4) ) 
    if ( ((*tight_electrons_intree).size()==0) && ((*tight_muons_intree).size()==2) && ((*preselected_leptons_intree).size()==2) )
    {
        //if ((*tight_muons_intree)[0].charge==(*tight_muons_intree)[1].charge) // <<<---- commented out for trigger SF calc.
        //{            
            //if ((*preselected_jets_intree).size()>3) // <<<---- commented out for trigger SF calc.
            //{                
                auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                double MHT_handle = objs_for_mht.Pt();
                double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                //if (metLD_handle> 0.2)
                //{                    
//                    if ((*tight_muons_intree)[0].obj.Pt()>20 && (*tight_muons_intree)[1].obj.Pt()>20)
//                    {                        
                        //if (((*tight_muons_intree)[0].obj.Pt() + (*tight_muons_intree)[1].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                        //{                            
                            if ((*tight_muons_intree)[0].chargeFlip<0.2 && (*tight_muons_intree)[1].chargeFlip<0.2)
                            {                                    
                                passes = true;
                            }
                        //}
//                    }
                //}
            //}
        //}
    }
    
    return passes;
}
bool HistMaker::passes_SSemu()
{
    bool passes = false;
    
    //if ( ((*tight_electrons_intree).size()==1) && ((*tight_muons_intree).size()==1) && ((*looseMvaBased_leptons_intree).size()<4) ) 
    if ( ((*tight_electrons_intree).size()==1) && ((*tight_muons_intree).size()==1) && ((*preselected_leptons_intree).size()==2) )
    {
        //if ((*tight_electrons_intree)[0].charge==(*tight_muons_intree)[0].charge) // <<<---- commented out for trigger SF calc.
        //{
            //if ((*preselected_jets_intree).size()>3) // <<<---- commented out for trigger SF calc.
            //{
                auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                double MHT_handle = objs_for_mht.Pt();
                double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                //if (metLD_handle> 0.2)
                //{
//                    if ((*tight_muons_intree)[0].obj.Pt()>20 && (*tight_electrons_intree)[0].obj.Pt()>20)
//                    {
                        //if (((*tight_muons_intree)[0].obj.Pt() + (*tight_electrons_intree)[0].obj.Pt() + (*met_intree)[0].obj.Pt())>100.)
                        //{
                            if ((*tight_muons_intree)[0].chargeFlip<0.2 && (*tight_electrons_intree)[0].isGsfCtfScPixChargeConsistent)
                            {                                    
                                passes = true;
                            }
                        //}
//                    }
                //}
            //}
        //}
    }
    
    return passes;
}



bool HistMaker::passes_3l()
{
    bool passes = false;
    
    //if ( ((*tight_leptons_intree).size()==3) && ((*looseMvaBased_leptons_intree).size()<4) ) 
    //    if ( ((*tight_leptons_intree).size()==3) && ((*looseMvaBased_leptons_intree).size()==3) && ((*preselected_leptons_intree).size()==3) )
    if ( ((*tight_leptons_intree).size()>=3) && ((*preselected_leptons_intree).size()>=3) )
    {
        auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
        double MHT_handle = objs_for_mht.Pt();
        double metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

        //if ((metLD_handle>0.2) || ((*preselected_jets_intree).size()>3))
        //{
            double vetoZmassSFOS = pickFromSortedTwoObjKine(*tight_leptons_intree,"massSFOS",1,91.2);

            //if (fabs(vetoZmassSFOS-91.2)>10.)                     
            //{        
                passes = true;
            //}
        //}
    }
    
    return passes;
}
bool HistMaker::passes_4l()
{
    bool passes = false;
    
    //if ((*looseMvaBased_leptons_intree).size()==4)
    if ((*looseMvaBased_leptons_intree).size()==4 && ((*preselected_leptons_intree).size()==4) )
    {
        if ( ((*looseMvaBased_leptons_intree)[0].charge + (*looseMvaBased_leptons_intree)[1].charge + (*looseMvaBased_leptons_intree)[2].charge + (*looseMvaBased_leptons_intree)[3].charge)==0 )
        {
            double vetoZmassSFOS = pickFromSortedTwoObjKine(*looseMvaBased_leptons_intree,"massSFOS",1,91.2);
            if (fabs(vetoZmassSFOS-91.2)>10.) passes = true;
        }
    }
    
    return passes;
}

bool HistMaker::passes_2l2b2qtest()
{
    bool passes = false;
    
    if ( (*tight_leptons_intree).size()==2 && (*preselected_leptons_intree).size()==2 ) //&& (*preselected_muons_intree).size()>=1 && (*preselected_electrons_intree).size()>=1 )
    {
        if ( (*tight_leptons_intree)[0].charge != (*tight_leptons_intree)[1].charge )
        {
        
            if ( (*preselected_jets_intree).size()==4 )
            {   
                auto taggedjets = keepTagged(*preselected_jets_intree,"M");
                auto untaggedjets = keepUnTagged(*preselected_jets_intree,"M");            

                if (taggedjets.size()==2)
                {                
                    if (taggedjets.size()!=untaggedjets.size()) cout << "problem in event sel" << endl;
                    passes = true;
                }
            }
        
        }
    }
    
    return passes;
}