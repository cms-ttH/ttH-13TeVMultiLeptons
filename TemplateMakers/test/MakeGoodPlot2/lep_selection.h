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

float POG_cut_on_GP_mva90(float eta) // for pt>10 electrons
{
    if (fabs(eta)>1.479) return 0.357;
    else
    {
        if (fabs(eta)<0.8) return 0.837;
        else return 0.715;
    }
}

bool HistMaker::ele_tight(ttH::Electron ele)
{
    if (ele.obj.Pt()>10. 
        && abs(ele.obj.Eta())<2.4 
        && ele.miniIso<0.25 
        && ele.sip3D<8 
        && (fabs(ele.dxy)<0.05) 
        && (fabs(ele.dz)<0.1) 
        && (ele.numMissingInnerHits<=1) 
        && ele.passConversioVeto 
        && POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP) return true;
        
    else return false;
}

bool HistMaker::mu_tight(ttH::Muon mu)
{
    if (mu.obj.Pt()>10. 
        && abs(mu.obj.Eta())<2.4 
        && mu.miniIso<0.25 
        && mu.sip3D<8 
        && (fabs(mu.dxy)<0.05) 
        && (fabs(mu.dz)<0.1) 
        && mu.idLoosePOG) return true;
        
    else return false;
}
