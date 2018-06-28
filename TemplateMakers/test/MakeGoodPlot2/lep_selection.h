float POG_cut_on_HZZ_mva(float eta) // for pt>10 electrons
{
    if (fabs(eta)>1.479) return -0.763;
    else
    {
        if (fabs(eta)<0.8) return -0.870;
        else return -0.838;
    }
}

float POG_cut_on_GP_mva80(float eta) // for pt>10 electrons
{
    if (fabs(eta)>1.479) return 0.758;
    else
    {
        if (fabs(eta)<0.8) return 0.941;
        else return 0.899;
    }
}

// getting it from andrew's function
// float POG_cut_on_GP_mva90(float eta) // for pt>10 electrons
// {
//     if (fabs(eta)>1.479) return 0.357;
//     else
//     {
//         if (fabs(eta)<0.8) return 0.837;
//         else return 0.715;
//     }
// }


// ttH version of fakeable IDs
bool HistMaker::ele_fakeable(ttH::Electron ele)
{
    // this takes as input the preselected electrons
    if (ele.correctedPt>10. 
            && ele.passesEtaDepCuts // <- needs a few adjustments!
            && ele.numMissingInnerHits==0
            && ele.passConversioVeto
            && ( (ele.lepMVA>=0.90 && ele.deepcsv < 0.4941)
            || (ele.lepMVA<0.90 
                && ele.jetPtRatio>0.6 
                && ele.deepcsv<0.07
                && ele.mvaID>0.5) )) return true; // check that this is mvaIdFall17noIso > 0.5
        
    return false;
}
bool HistMaker::mu_fakeable(ttH::Muon mu)
{        
    // this takes as input the preselected muons
    if (mu.correctedPt > 10.
        && ( (mu.lepMVA>=0.90 && mu.deepcsv < 0.4941) 
        || (mu.lepMVA<0.90 && mu.jetPtRatio>0.6 && mu.deepcsv<0.07 && mu.segCompatibility>0.3) )) return true;

    return false;
}


// ttH version of tight IDs
bool HistMaker::ele_tight(ttH::Electron ele)
{
    if (ele_fakeable(ele) && ele.lepMVA>=0.9) return true;    
    return false;
}
bool HistMaker::mu_tight(ttH::Muon mu)
{
    if (mu_fakeable(mu) && mu.lepMVA>=0.9 && mu.idMediumPOG) return true;
    return false;
}
bool HistMaker::lep_tight(ttH::Lepton lep)
{
    // assumes that the input is a fakeable collection!
    if (abs(lep.pdgID)==11 && lep.lepMVA>=0.9) return true;    
    if (abs(lep.pdgID)==13 && lep.lepMVA>=0.9 && lep.idMediumPOG) return true;
    return false;
}

// for testing POG IDs...
// bool HistMaker::ele_tight(ttH::Electron ele)
// {
//     if (ele.obj.Pt()>10. 
//         && abs(ele.obj.Eta())<2.4 
//         && ele.miniIso<0.25 
//         && ele.sip3D<8 
//         && (fabs(ele.dxy)<0.05) 
//         && (fabs(ele.dz)<0.1) 
//         && (ele.numMissingInnerHits<=1) 
//         && ele.passConversioVeto 
//         && POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP) return true;
//         
//     else return false;
// }
// 
// bool HistMaker::mu_tight(ttH::Muon mu)
// {
//     if (mu.obj.Pt()>10. 
//         && abs(mu.obj.Eta())<2.4 
//         && mu.miniIso<0.25 
//         && mu.sip3D<8 
//         && (fabs(mu.dxy)<0.05) 
//         && (fabs(mu.dz)<0.1) 
//         && mu.idLoosePOG) return true;
//         
//     else return false;
// }



