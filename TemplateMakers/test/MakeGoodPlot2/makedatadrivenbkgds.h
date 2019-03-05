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
    
    //double weight = 0.;
    double factor = 0.;    
    auto leptons = fakeable_leptons;
    bool passedtrig = passesAnyTrigger();
    
    TH2D *elFRhist;
    TH2D *muFRhist;
    
    //cout << iSys << endl;
    
    if (iSys==3)
    {
        elFRhist = elFRsfs_up;
        muFRhist = muFRsfs_up;
    }
    else if (iSys==4)
    {
        elFRhist = elFRsfs_down; 
        muFRhist = muFRsfs_down;
    }
    else if (iSys==5)
    {
        elFRhist = elFRsfs_qcd;
        muFRhist = muFRsfs_qcd;
    }
    else if (iSys==6)
    {
        elFRhist = elFRsfs_ttbar;
        muFRhist = muFRsfs_ttbar;
    }
    else if (iSys==31)
    {
        elFRhist = elFRsfs_pt1;
        muFRhist = muFRsfs_pt1;
    }    
    else if (iSys==32)
    {
        elFRhist = elFRsfs_pt2;
        muFRhist = muFRsfs_pt2;
    }    
    else if (iSys==33)
    {
        elFRhist = elFRsfs_eta1;
        muFRhist = muFRsfs_eta1;
    }    
    else if (iSys==34)
    {
        elFRhist = elFRsfs_eta2;
        muFRhist = muFRsfs_eta2;
    }    
    
    else
    {
        elFRhist = elFRsfs;
        muFRhist = muFRsfs;
    }    
    
    iSys = iSys>2 ? 0 : iSys; // for category[iSys]
    
    //cout << "here" << endl;
    
    if (removeDatasetOverlaps() && passedtrig)
    {              

        if (category[iSys]!="null")
        {              
                              
            // could probably change this to a loop..
            
            if (category[iSys].substr(0,2)=="2l") 
            {
                
                //cout << "here2" << endl;

                double factor1 = 0.;
                double factor2 = 0.;
                bool firstNotTight = false;
                bool secondNotTight = false;
                
                if (!lep_tight(leptons[0]))
                {
                    //cout << "l1" << endl;
                    //cout << leptons[0].correctedPt << " " << leptons[0].obj.Eta() << endl;
                    
                    if (abs(leptons[0].pdgID)==11) factor1 = elFRhist->GetBinContent(elFRhist->FindBin(min(leptons[0].correctedPt,99.),min(abs(leptons[0].obj.Eta()),2.49))); // the newer cern ones only go up to 100 :P
                    if (abs(leptons[0].pdgID)==13) factor1 = muFRhist->GetBinContent(muFRhist->FindBin(min(leptons[0].correctedPt,99.),min(abs(leptons[0].obj.Eta()),2.49)));
                    
//                     if (iSys==3)
//                     {
//                         if (abs(leptons[0].pdgID)==11) factor1 += factor1*elFRhist->GetBinError(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
//                         if (abs(leptons[0].pdgID)==13) factor1 += factor1*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
//                     }
//                     if (iSys==4)
//                     {
//                         if (abs(leptons[0].pdgID)==11) factor1 -= factor1*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
//                         if (abs(leptons[0].pdgID)==13) factor1 -= factor1*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
//                     }
                    if (factor1<0.) factor1=0.;
                    firstNotTight = true;
                }
                if (!lep_tight(leptons[1]))
                {
                
                    //cout << "l2" << endl;
                    //cout << leptons[1].correctedPt << " " << leptons[1].obj.Eta() << endl;                   
                
                    if (abs(leptons[1].pdgID)==11) factor2 = elFRhist->GetBinContent(elFRhist->FindBin(min(leptons[1].correctedPt,99.),min(abs(leptons[1].obj.Eta()),2.49)));
                    if (abs(leptons[1].pdgID)==13) factor2 = muFRhist->GetBinContent(muFRhist->FindBin(min(leptons[1].correctedPt,99.),min(abs(leptons[1].obj.Eta()),2.49)));
                    
//                     if (iSys==3)
//                     {
//                         if (abs(leptons[1].pdgID)==11) factor2 += factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
//                         if (abs(leptons[1].pdgID)==13) factor2 += factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
//                     }
//                     if (iSys==4)
//                     {
//                         if (abs(leptons[1].pdgID)==11) factor2 -= factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
//                         if (abs(leptons[1].pdgID)==13) factor2 -= factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
//                     }                        
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
                
                
                //cout << "here3" << endl;
            }

            
            if (category[iSys].substr(0,2)=="3l") 
            {
                
                double factor1 = 0.;
                double factor2 = 0.;
                double factor3 = 0.;
                bool firstNotTight = false;
                bool secondNotTight = false;
                bool thirdNotTight = false;
                
                if (!lep_tight(leptons[0]))
                {
                    if (abs(leptons[0].pdgID)==11) factor1 = elFRhist->GetBinContent(elFRhist->FindBin(min(leptons[0].correctedPt,99.),min(abs(leptons[0].obj.Eta()),2.49)));
                    if (abs(leptons[0].pdgID)==13) factor1 = muFRhist->GetBinContent(muFRhist->FindBin(min(leptons[0].correctedPt,99.),min(abs(leptons[0].obj.Eta()),2.49)));
                    
//                     if (iSys==3)
//                     {
//                         if (abs(leptons[0].pdgID)==11) factor1 += factor1*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
//                         if (abs(leptons[0].pdgID)==13) factor1 += factor1*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
//                     }
//                     if (iSys==4)
//                     {
//                         if (abs(leptons[0].pdgID)==11) factor1 -= factor1*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
//                         if (abs(leptons[0].pdgID)==13) factor1 -= factor1*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[0].correctedPt,abs(leptons[0].obj.Eta())));
//                     }
                    if (factor1<0.) factor1=0.;
                    firstNotTight = true;
                }
                if (!lep_tight(leptons[1]))
                {
                    if (abs(leptons[1].pdgID)==11) factor2 = elFRhist->GetBinContent(elFRhist->FindBin(min(leptons[1].correctedPt,99.),min(abs(leptons[1].obj.Eta()),2.49)));
                    if (abs(leptons[1].pdgID)==13) factor2 = muFRhist->GetBinContent(muFRhist->FindBin(min(leptons[1].correctedPt,99.),min(abs(leptons[1].obj.Eta()),2.49)));
                    
//                     if (iSys==3)
//                     {
//                         if (abs(leptons[1].pdgID)==11) factor2 += factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
//                         if (abs(leptons[1].pdgID)==13) factor2 += factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
//                     }
//                     if (iSys==4)
//                     {
//                         if (abs(leptons[1].pdgID)==11) factor2 -= factor2*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
//                         if (abs(leptons[1].pdgID)==13) factor2 -= factor2*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[1].correctedPt,abs(leptons[1].obj.Eta())));
//                     }                        
                    if (factor2<0.) factor2=0.;
                    secondNotTight = true;
                }
                if (!lep_tight(leptons[2]))
                {
                    if (abs(leptons[2].pdgID)==11) factor3 = elFRhist->GetBinContent(elFRhist->FindBin(min(leptons[2].correctedPt,99.),min(abs(leptons[2].obj.Eta()),2.49)));
                    if (abs(leptons[2].pdgID)==13) factor3 = muFRhist->GetBinContent(muFRhist->FindBin(min(leptons[2].correctedPt,99.),min(abs(leptons[2].obj.Eta()),2.49)));
                    
//                     if (iSys==3)
//                     {
//                         if (abs(leptons[2].pdgID)==11) factor3 += factor3*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
//                         if (abs(leptons[2].pdgID)==13) factor3 += factor3*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
//                     }
//                     if (iSys==4)
//                     {
//                         if (abs(leptons[2].pdgID)==11) factor3 -= factor3*elFRsfs->GetBinError(elFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
//                         if (abs(leptons[2].pdgID)==13) factor3 -= factor3*muFRsfs->GetBinError(muFRsfs->FindBin(leptons[2].correctedPt,abs(leptons[2].obj.Eta())));
//                     }                        
                    if (factor3<0.) factor3=0.;
                    thirdNotTight = true;
                }                    
                if (firstNotTight || secondNotTight || thirdNotTight) factor = -1.;
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