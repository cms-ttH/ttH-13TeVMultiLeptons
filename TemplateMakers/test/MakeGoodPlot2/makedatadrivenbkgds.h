std::pair<double,double> HistMaker::getQFweights(string category)
{
    // this returns the (++,--) factors.
    // category mapping is:
    // in       |  out
    // 2los_ee  | (2lss_p_ee,2lss_m_ee)
    // 2los_emu | (0,2lss_m_emu) or (2lss_p_emu,0)
    std::pair<double,double> factors;
    factors.first=0.;
    factors.second=0.;
    
    
    if (category=="2los_ee" || category=="2los_sfz_ee")
    {
        // use the tight leps (fakeable are for FR estimation)
        double ele_pt1 = tight_electrons[0].obj.Pt();
        double abseta1 = abs(tight_electrons[0].obj.Eta());
        double ele_pt2 = tight_electrons[1].obj.Pt();
        double abseta2 = abs(tight_electrons[1].obj.Eta());
        int chg1 = tight_electrons[0].charge;
        int chg2 = tight_electrons[1].charge;        
        double rateQF1 = elQFsfs->GetBinContent(elQFsfs->FindBin(max(15.,min(ele_pt1,999.)),min(abseta1,2.5)));
        double rateQF2 = elQFsfs->GetBinContent(elQFsfs->FindBin(max(15.,min(ele_pt2,999.)),min(abseta2,2.5)));
        
        if ( chg1==1 )
        {
            //fill e-e- (JESUP/DOWN, etc.) with weight
            //th1d["2lss_m_ee_2b_QFevents."+systint2str(iSys)]->Fill(rateQF1,weight); // no!
            factors.first=rateQF1;
        }
        else if ( chg1==-1 )
        {
            //fill e+e+
            //th1d["2lss_p_ee_2b_QFevents."+systint2str(iSys)]->Fill(rateQF1,weight);
            factors.second=rateQF1;
        }
        if ( chg2==1 )
        {
            //fill e-e-
            //th1d["2lss_m_ee_2b_QFevents."+systint2str(iSys)]->Fill(rateQF2,weight);
            factors.first=rateQF2;
        }
        else if ( chg2==-1 )
        {
            //fill e+e+
            //th1d["2lss_p_ee_2b_QFevents."+systint2str(iSys)]->Fill(rateQF2,weight);
            factors.second=rateQF2;
        }
    
    }
    
    else if (category=="2los_emu")
    {

        double ele_pt1 = tight_electrons[0].obj.Pt();
        double abseta1 = abs(tight_electrons[0].obj.Eta());       
        int chg1 = tight_electrons[0].charge;   
        double rateQF1 = elQFsfs->GetBinContent(elQFsfs->FindBin(max(15.,min(ele_pt1,999.)),min(abseta1,2.5)));
        
        if ( chg1==1 )
        {
            //fill e-mu- (JESUP/DOWN, etc.)
            //th1d["2lss_m_emu_2b_QFevents."+systint2str(iSys)]->Fill(rateQF1,weight);
            factors.second=rateQF1;
        }
        else if ( chg1==-1 )
        {
            //fill e+mu+
            //th1d["2lss_p_emu_2b_QFevents."+systint2str(iSys)]->Fill(rateQF1,weight);
            factors.first=rateQF1;
        }
    }
    
    return factors;
}

double HistMaker::getFakeWeight(int iSys, vector<string> category)
{
    //vector<string> category = eventselections(true); // true=do the selection with fakeable leptons
    
    //double weight = 0.;
    double factor = 0.;    
    auto leptons = fakeable_leptons;
    bool passedtrig = passesAnyTrigger();
    
    
    if (removeDatasetOverlaps() && passedtrig)
    {              

        if (category[iSys]!="null")
        {              
                              
            // could probably change this to a loop..
            
            if (category[iSys].substr(0,2)=="2l") 
            {


                double factor1 = 0.;
                double factor2 = 0.;
                bool firstNotTight = false;
                bool secondNotTight = false;
                
                if (!lep_tight(leptons[0]))
                {
                    if (abs(leptons[0].pdgID)==11) factor1 = elFRsfs->GetBinContent(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                    if (abs(leptons[0].pdgID)==13) factor1 = muFRsfs->GetBinContent(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                    
                    if (iSys==3)
                    {
                        if (abs(leptons[0].pdgID)==11) factor1 += factor1*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                        if (abs(leptons[0].pdgID)==13) factor1 += factor1*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                    }
                    if (iSys==4)
                    {
                        if (abs(leptons[0].pdgID)==11) factor1 -= factor1*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                        if (abs(leptons[0].pdgID)==13) factor1 -= factor1*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                    }
                    if (factor1<0.) factor1=0.;
                    firstNotTight = true;
                }
                if (!lep_tight(leptons[1]))
                {
                    if (abs(leptons[1].pdgID)==11) factor2 = elFRsfs->GetBinContent(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                    if (abs(leptons[1].pdgID)==13) factor2 = muFRsfs->GetBinContent(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                    
                    if (iSys==3)
                    {
                        if (abs(leptons[1].pdgID)==11) factor2 += factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                        if (abs(leptons[1].pdgID)==13) factor2 += factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                    }
                    if (iSys==4)
                    {
                        if (abs(leptons[1].pdgID)==11) factor2 -= factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                        if (abs(leptons[1].pdgID)==13) factor2 -= factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                    }                        
                    if (factor2<0.) factor2=0.;
                    secondNotTight = true;
                }
                
                if (firstNotTight && !secondNotTight)
                {
                    factor = factor1 / (1. - factor1);
                }
                if (secondNotTight && !firstNotTight)
                {
                    factor = factor2 / (1. - factor2);
                }                    
                if (secondNotTight && firstNotTight)
                {
                    //if (factor1<=0. || factor2<=0.) cout << "Warning, non-pos-definite FR!" << endl;
                    factor = 0. - ( factor1*factor2 / ((1.-factor1)*(1.-factor2)) );
                }
                
                //th1d[category[sys]+"_Fakes."+systint2str(sys)]->Fill(,factor*weight); // not here..
                
            }

            
            if (category[iSys].substr(0,2)=="3l") 
            {
                factor = -1.;
                
                double factor1 = 0.;
                double factor2 = 0.;
                double factor3 = 0.;
                bool firstNotTight = false;
                bool secondNotTight = false;
                bool thirdNotTight = false;
                
                if (!lep_tight(leptons[0]))
                {
                    if (abs(leptons[0].pdgID)==11) factor1 = elFRsfs->GetBinContent(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                    if (abs(leptons[0].pdgID)==13) factor1 = muFRsfs->GetBinContent(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                    
                    if (iSys==3)
                    {
                        if (abs(leptons[0].pdgID)==11) factor1 += factor1*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                        if (abs(leptons[0].pdgID)==13) factor1 += factor1*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                    }
                    if (iSys==4)
                    {
                        if (abs(leptons[0].pdgID)==11) factor1 -= factor1*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                        if (abs(leptons[0].pdgID)==13) factor1 -= factor1*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
                    }
                    if (factor1<0.) factor1=0.;
                    firstNotTight = true;
                }
                if (!lep_tight(leptons[1]))
                {
                    if (abs(leptons[1].pdgID)==11) factor2 = elFRsfs->GetBinContent(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                    if (abs(leptons[1].pdgID)==13) factor2 = muFRsfs->GetBinContent(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                    
                    if (iSys==3)
                    {
                        if (abs(leptons[1].pdgID)==11) factor2 += factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                        if (abs(leptons[1].pdgID)==13) factor2 += factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                    }
                    if (iSys==4)
                    {
                        if (abs(leptons[1].pdgID)==11) factor2 -= factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                        if (abs(leptons[1].pdgID)==13) factor2 -= factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
                    }                        
                    if (factor2<0.) factor2=0.;
                    secondNotTight = true;
                }
                if (!lep_tight(leptons[2]))
                {
                    if (abs(leptons[2].pdgID)==11) factor3 = elFRsfs->GetBinContent(elFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
                    if (abs(leptons[2].pdgID)==13) factor3 = muFRsfs->GetBinContent(muFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
                    
                    if (iSys==3)
                    {
                        if (abs(leptons[2].pdgID)==11) factor3 += factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
                        if (abs(leptons[2].pdgID)==13) factor3 += factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
                    }
                    if (iSys==4)
                    {
                        if (abs(leptons[2].pdgID)==11) factor3 -= factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
                        if (abs(leptons[2].pdgID)==13) factor3 -= factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
                    }                        
                    if (factor3<0.) factor3=0.;
                    thirdNotTight = true;
                }                    
                if (firstNotTight)
                {
                    factor *= -factor1 / (1. - factor1);
                }
                if (secondNotTight)
                {
                    factor *= -factor2 / (1. - factor2);
                }                    
                if (thirdNotTight)
                {
                    factor *= -factor3 / (1. - factor3);
                }
                
            }                    

        
        }
        
    }
    
    return factor;
    
    
    // basically have to re-do standardhists, calling the 
    
    // need to:
    //   load the sf file (done in the usual place)
    // get the category[sys]
    // probably need the lep collection, either from tree or by hand passing presel leps to helper function (if doing that, need to shove that funciton into eventselection also inside that conditional)
    // find out which leps pass tight cuts, which don't
    // get appropriate weight, fill hist(s)
    
}