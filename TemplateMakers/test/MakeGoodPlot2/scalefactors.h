void HistMaker::setupSFs()
{
    // This function is run in the HistMaker constructor
    
    TString basedir = getenv("CMSSW_BASE");
    auto pudatafile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/PU/2017PU_SFstest2.root");
    pileupSFs = (TH1D*)pudatafile->Get("pileupSF");
    pileupSFs_up = (TH1D*)pudatafile->Get("pileupSF_UP");
    pileupSFs_down = (TH1D*)pudatafile->Get("pileupSF_DOWN");
    
    auto hffile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/btag/Deepcsv_rwt_fit_hf_v2_final_2018_2_12test.root");
    auto lffile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/btag/Deepcsv_rwt_fit_lf_v2_final_2018_2_12test.root");
    fillCSVhistos(hffile,lffile);
    
    auto muSFfile1 = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/fits_mu_trkEffSF_2017_allTracks.root");
    auto muSFfile2 = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/RunBCDEF_SF_ID.root");
    auto muSFfile2b = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/RunBCDEF_SF_ID_ptLt30.root");
    auto muSFfile3 = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/loose_mu_to_ttH_loose_Sergio.root");
    
    muh1 = (TGraphAsymmErrors*)muSFfile1->Get("ratio_eff_eta3_dr030e030_corr");
    //muh2 = (TH2D*)muSFfile2->Get("NUM_MediumID_DEN_genTracks_pt_abseta"); // <- should be LooseID
    muh2 = (TH2D*)muSFfile2->Get("NUM_LooseID_DEN_genTracks_pt_abseta");
    muh2b = (TH2D*)muSFfile2b->Get("NUM_LooseID_DEN_genTracks_pt_abseta");
    muh3 = (TH2D*)muSFfile3->Get("NUM_ttHLoo_DEN_LooseID");

    auto eleSFfile1a = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
    auto eleSFfile1b = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/egammaEffi.txt_EGM2D_runBCDEF_passingRECO_lowEt.root");
    auto eleSFfile2 = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/el_reco_loose_SF.root");
     
    eleh1 = (TH2D*)eleSFfile1a->Get("EGamma_SF2D");
    eleh1lowpt = (TH2D*)eleSFfile1b->Get("EGamma_SF2D");
    eleh2 = (TH2D*)eleSFfile2->Get("EGamma_SF2D");

    auto lepMVASFfile_m_2lss = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/lepMVAEffSF2017_m_2lss.root");
    auto lepMVASFfile_e_3l = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/lepMVAEffSF2017_e_3l.root");
    auto lepMVASFfile_e_2lss = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/lepMVAEffSF2017_e_2lss.root");
    auto lepMVASFfile_m_3l = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/lepMVAEffSF2017_m_3l.root");
    
    muh4_2l = (TH2F*)lepMVASFfile_m_2lss->Get("sf");
    muh4_3l = (TH2F*)lepMVASFfile_m_3l->Get("sf");
    eleh4_2l = (TH2F*)lepMVASFfile_e_2lss->Get("sf");
    eleh4_3l = (TH2F*)lepMVASFfile_e_3l->Get("sf");
    
    // "SFs" for data-driven bkgds
    auto QFSFfile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/fakerate/ElectronChargeMisIdRates_2017.root");
    //min pt: 15, max pt : 1000
    elQFsfs = (TH2D*)QFSFfile->Get("eChargeMisIdRates");
    //auto FRSFfile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/fakerate/leptonFakeRates_Tallinn_2018May24.root");     // 2017 old
    auto FRSFfile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/fakerate/FR_lep_ttH_mva090_2017_CERN_2018May29.root"); // 2017 new
    
    elFRsfs = (TH2D*)FRSFfile->Get("FR_mva090_el_data_comb_NC"); // comb_NC -> conversion-corrected
    muFRsfs = (TH2D*)FRSFfile->Get("FR_mva090_mu_data_comb");

    elFRsfs_up = (TH2D*)FRSFfile->Get("FR_mva090_el_data_comb_NC_up"); // comb_NC -> conversion-corrected
    muFRsfs_up = (TH2D*)FRSFfile->Get("FR_mva090_mu_data_comb_up");
    
    elFRsfs_down = (TH2D*)FRSFfile->Get("FR_mva090_el_data_comb_NC_down"); // comb_NC -> conversion-corrected
    muFRsfs_down = (TH2D*)FRSFfile->Get("FR_mva090_mu_data_comb_down");
    
    elFRsfs_qcd = (TH2D*)FRSFfile->Get("FR_mva090_el_QCD_NC"); // QCD_NC -> conversion-corrected
    muFRsfs_qcd = (TH2D*)FRSFfile->Get("FR_mva090_mu_QCD");
    
    elFRsfs_ttbar = (TH2D*)FRSFfile->Get("FR_mva090_el_TT");
    muFRsfs_ttbar = (TH2D*)FRSFfile->Get("FR_mva090_mu_TT");    
    
    elFRsfs_pt1 = (TH2D*)FRSFfile->Get("FR_mva090_el_data_comb_NC_pt1"); // comb_NC -> conversion-corrected
    muFRsfs_pt1 = (TH2D*)FRSFfile->Get("FR_mva090_mu_data_comb_pt1");
    
    elFRsfs_pt2 = (TH2D*)FRSFfile->Get("FR_mva090_el_data_comb_NC_pt2"); // comb_NC -> conversion-corrected
    muFRsfs_pt2 = (TH2D*)FRSFfile->Get("FR_mva090_mu_data_comb_pt2");
    
    elFRsfs_eta1 = (TH2D*)FRSFfile->Get("FR_mva090_el_data_comb_NC_be1"); // comb_NC -> conversion-corrected
    muFRsfs_eta1 = (TH2D*)FRSFfile->Get("FR_mva090_mu_data_comb_be1");    
    
    elFRsfs_eta2 = (TH2D*)FRSFfile->Get("FR_mva090_el_data_comb_NC_be2"); // comb_NC -> conversion-corrected
    muFRsfs_eta2 = (TH2D*)FRSFfile->Get("FR_mva090_mu_data_comb_be2");
    
}

double HistMaker::pileupSF(int numtrueint, int sys)
{
    // assumes that setupSFs has been run already
    //numtrueint = min(numtrueint,199); // ok, done outside
    // if up / down ...
    if (sys==43) return pileupSFs_up->GetBinContent(numtrueint+1);
    if (sys==44) return pileupSFs_down->GetBinContent(numtrueint+1);
    return pileupSFs->GetBinContent(numtrueint+1);
}

// "v3" (SF using full njets range)
double HistMaker::adhocNjetSF(int bin, vector<string> category, int sys) 
{
    if (sample!=84 && sample!=85 && sample!=87) return 1.;
    double adhocSF = 1.;
    if (category[0].substr(0,2)=="3l")
    {
        //ttW:
        if (sample==85)
        {
            if (bin==1) adhocSF = 0.898273;
            if (bin==2) adhocSF = 1.10505;
            if (bin==3) adhocSF = 1.58784;
            if (bin==4) adhocSF = 2.52711;
        }    

        //ttH:
        if (sample==84)
        {
            if (bin==1) adhocSF = 0.915586;
            if (bin==2) adhocSF = 0.968141;
            if (bin==3) adhocSF = 1.11549;
            if (bin==4) adhocSF = 1.14007;
        }
        //tZq:
        if (sample==87)
        {
            if (bin==1) adhocSF = 0.97725;
            if (bin==2) adhocSF = 0.992164;
            if (bin==3) adhocSF = 0.948662;
            if (bin==4) adhocSF = 0.829534;
        }
        
    }
    else if (category[0].substr(0,4)=="2lss")
    {
        //ttW:
        if (sample==85)
        {
            if (bin==1) adhocSF = 1.00071;
            if (bin==2) adhocSF = 1.26732;
            if (bin==3) adhocSF = 1.66762;
            if (bin==4) adhocSF = 2.25097;
        }
        //ttH:
        if (sample==84)
        {
            if (bin==1) adhocSF = 0.959517;
            if (bin==2) adhocSF = 1.02484;
            if (bin==3) adhocSF = 1.16089;
            if (bin==4) adhocSF = 1.34144;
        }
        //tZq:
        if (sample==87)
        {
            // did a linear fit in this case due to low stats in last couple bins
            if (bin==1) adhocSF = 1.1793 - 0.0740338*4.5; // 4.5 instead of 4 because the fit is to the center of the bin
            if (bin==2) adhocSF = 1.1793 - 0.0740338*5.5;
            if (bin==3) adhocSF = 1.1793 - 0.0740338*6.5;
            if (bin==4) adhocSF = 1.1793 - 0.0740338*7.5;
        }
    }
    
    // adhocSF is the SF, up variation is applying twice the correction, down is applying no SF.
    if (sys==45) return 1. + 2.*(adhocSF-1.);         // twice the correction
    if (sys==46) return 1.;                         // fully uncorrected
    return adhocSF;                                 // nominal correction
}

// "v1", "v2": SFs derived only using analysis bins
// double HistMaker::adhocNjetSF(int bin, vector<string> category, int sys) 
// {
//     //if (!(sample>=84 && sample<=88)) return 1.;
//     if (!(sample>=84 && sample<=87) || sample==86) return 1.;
//     double adhocSF = 1.;
//     if (category[0].substr(0,2)=="3l")
//     {
//         //ttW:
//         if (sample==85)
//         {
//             if (bin==1) adhocSF = 0.859596;
//             if (bin==2) adhocSF = 1.04251;
//             if (bin==3) adhocSF = 1.56901;
//             if (bin==4) adhocSF = 2.44186;
//         }    
//         //ttZ: (not doing)
// //         if (sample==86)
// //         {
// //             if (bin==1) adhocSF = 1.02377;
// //             if (bin==2) adhocSF = 1.01088;
// //             if (bin==3) adhocSF = 0.974548;
// //             if (bin==4) adhocSF = 0.99366;
// //         }
//         //ttH:
//         if (sample==84)
//         {
//             if (bin==1) adhocSF = 0.894639;
//             if (bin==2) adhocSF = 0.941526;
//             if (bin==3) adhocSF = 1.06549;
//             if (bin==4) adhocSF = 1.17726;
//         }
//         //tZq:
//         if (sample==87)
//         {
//             if (bin==1) adhocSF = 0.985265;
//             if (bin==2) adhocSF = 1.01997;
//             if (bin==3) adhocSF = 1.0263;
//             if (bin==4) adhocSF = 1.05791;
//         }
// //         tHq: (not doing)
// //         if (sample==88)
// //         {
// //             if (bin==1) adhocSF = 1.88585;
// //             if (bin==2) adhocSF = 0.436247;
// //             if (bin==3) adhocSF = 0.188235;
// //             if (bin==4) adhocSF = 0.129871;
// //         }        
//     }
//     if (category[0].substr(0,4)=="2lss")
//     {
//         //ttW:
//         if (sample==85)
//         {
//             if (bin==1) adhocSF = 0.867116;
//             if (bin==2) adhocSF = 1.09907;
//             if (bin==3) adhocSF = 1.47473;
//             if (bin==4) adhocSF = 2.05149;
//         }
//         //ttZ: (not doing)
// //         if (sample==86)
// //         {
// //             if (bin==1) adhocSF = 1.08712;
// //             if (bin==2) adhocSF = 0.958936;
// //             if (bin==3) adhocSF = 0.951982;
// //             if (bin==4) adhocSF = 0.6606;
// //         }
//         //ttH:
//         if (sample==84)
//         {
//             if (bin==1) adhocSF = 0.911441;
//             if (bin==2) adhocSF = 0.970544;
//             if (bin==3) adhocSF = 1.14447;
//             if (bin==4) adhocSF = 1.30127;
//         }
//         //tZq:
//         if (sample==87)
//         {
//             if (bin==1) adhocSF = 1.07607;
//             if (bin==2) adhocSF = 1.08074;
//             if (bin==3) adhocSF = 0.215199;
//             if (bin==4) adhocSF = 0.23471;
//         }
//         //tHq: (not doing)
// //         if (sample==88)
// //         {
// //             if (bin==1) adhocSF = 1.49829;
// //             if (bin==2) adhocSF = 0.338653;
// //             if (bin==3) adhocSF = 0.322669;
// //             if (bin==4) adhocSF = 0.0001;
// //         }
//     }
//     if (category[0].substr(0,2)=="4l")
//     {
//         //ttW:
//         if (sample==85)
//         {
//             if (bin==2) adhocSF = 0.564873;
//             if (bin==3) adhocSF = 0.663006;
//             if (bin==4) adhocSF = 3.9067;
//         }
//         //ttH:
//         if (sample==84)
//         {
//             if (bin==2) adhocSF = 0.690122;
//             if (bin==3) adhocSF = 0.933003;
//             if (bin==4) adhocSF = 1.63881;
//         }
//         //tZq: (doing by hand)
// //         if (sample==87)
// //         {
// //             if (bin==2) adhocSF = 0.550709;
// //             if (bin==3) adhocSF = 596.482;
// //             if (bin==4) adhocSF = 0.52808;
// //         }
//         //tHq: (not doing)
// //         if (sample==88)
// //         {
// //             if (bin==2) adhocSF = 1.0778;
// //             if (bin==3) adhocSF = 0.738742;
// //             if (bin==4) adhocSF = 2.3202;
// //         }
//     }    
//     if (sample==87) // special case: SF=1, and "UP" variation is adhocSF, down is 1-(adhocSF-1).
//     {
//         if (sys==45) return adhocSF;
//         if (sys==46)
//         {
//             if (category[0].substr(0,2)!="4l")
//             {
//                 return 1. - (adhocSF-1.);
//             }
//         }
//         return 1.; // not a mistake that 4l sys 46 can get here
//     }
//     else // nominal case: adhocSF is the SF, up variation is applying twice the SF, down is applying no SF.
//     {
//         if (sys==45) 
//         {
//             double maxfactor = 2.;
//             if (category[0].substr(0,2)=="3l" && sample==88) maxfactor = 1./(1.-0.129871); // <- comes from solving 1+x*(adhocSF-1)=0
//             if (category[0].substr(0,4)=="2lss" && sample==88) maxfactor = 1.;
//             if (category[0].substr(0,4)=="2lss" && sample==87) maxfactor = 1./(1.-0.215199);
//             return 1. + maxfactor*(adhocSF-1.);         // twice the correction unless some bins pulled negative, in which case use the maximum factor possible that's <2
//         }
//         //if (sys==46) return 1. + 0.5*(adhocSF-1.);    // half the correction
//         if (sys==46) return 1.;                         // fully uncorrected
//         return adhocSF;                                 // nominal correction
//     }
// }

double HistMaker::partonShowerSF(int bin, vector<string> category, int sys) 
{
    // this assumes we're looking at SRs, njets plots, all with ==4 bins.
    // should be handled by dedicated condition in standard hists
    // uses existing PSISRUP/DOWN
    
    if (!isSR) return 1.;
    if (bin<1) return 1.;
    
    // with 3jet bin:
//     if (category[0].substr(0,4)=="2lss")
//     {
//         if (bin==1)
//         {
//             if (sys==37) return 1.05;
//             if (sys==38) return 0.95;
//         }
//         if (bin==2) 
//         {
//             if (sys==37) return 1.025;
//             if (sys==38) return 0.975;
//         }
//         if (bin==3) 
//         {
//             if (sys==37) return 1.0;
//             if (sys==38) return 1.0;
//         }        
//         if (bin==4) 
//         {
//             if (sys==37) return 0.975;
//             if (sys==38) return 1.025;
//         }
//         if (bin==5) 
//         {
//             if (sys==37) return 0.95;
//             if (sys==38) return 1.05;
//         }
//     }


    //else if (category[0].substr(0,2)=="3l")
    // regular 3l, 2l:
//     if (category[0].substr(0,2)=="3l" || category[0].substr(0,4)=="2lss")
//     {
//         if (bin==1)
//         {
//             if (sys==37) return 1.05;
//             if (sys==38) return 0.95;
//         }
//         if (bin==2) 
//         {
//             if (sys==37) return 1.0 + (0.05/3.0);
//             if (sys==38) return 1.0 - (0.05/3.0);
//         }
//         if (bin==3) 
//         {
//             if (sys==37) return 1.0 - (0.05/3.0);
//             if (sys==38) return 1.0 + (0.05/3.0);
//         }        
//         if (bin==4) 
//         {
//             if (sys==37) return 0.95;
//             if (sys==38) return 1.05;
//         }
//     }


    // study combining last two bins:
//     if (category[0].substr(0,2)=="3l" || category[0].substr(0,4)=="2lss")
//     {
//         if (bin==1) 
//         {
//             if (sys==37) return 1.05;
//             if (sys==38) return 0.95;
//         }
//         if (bin==2) 
//         {
//             if (sys==37) return 1.0;
//             if (sys==38) return 1.0;
//         }        
//         if (bin==3) 
//         {
//             if (sys==37) return 0.95;
//             if (sys==38) return 1.05;
//         }
//     } 

    // study combining last three bins:
    if (category[0].substr(0,2)=="3l" || category[0].substr(0,4)=="2lss")
    {
        if (bin==1) 
        {
            if (sys==37) return 1.05;
            if (sys==38) return 0.95;
        }
        if (bin==2) 
        {
            if (sys==37) return 0.95;
            if (sys==38) return 1.05;
        }        
    } 
    else if (category[0].substr(0,2)=="4l")
    {   
        if (bin==2) 
        {
            if (sys==37) return 1.05;
            if (sys==38) return 0.95;
        }
        if (bin==3) 
        {
            if (sys==37) return 0.95;
            if (sys==38) return 1.05;
        }        
    } 

    // regular 4l:
//     else if (category[0].substr(0,2)=="4l")
//     {
//         if (bin==2) 
//         {
//             if (sys==37) return 1.05;
//             if (sys==38) return 0.95;
//         }
//         if (bin==3) 
//         {
//             if (sys==37) return 1.0;
//             if (sys==38) return 1.0;
//         }        
//         if (bin==4) 
//         {
//             if (sys==37) return 0.95;
//             if (sys==38) return 1.05;
//         }
//     }

    return 1.;
}
double triggerSF(int pdgid1, int pdgid2, int nlep, double leadingleppt, int sys=0)
{
    if (nlep>=3) 
    {
        if (sys==41) return 1.05;
        if (sys==42) return 0.95;
        return 1.0;    
    }
    int comb = abs(pdgid1)+abs(pdgid2);
    
    if (comb==1010) comb = 22; //kludge for 1l
    if (comb==1012) comb = 26; //kludge for 1l
    
    double sys_amt = 0.;
    
    if (comb==22) // ee
    {
        if (leadingleppt<30.)
        {
            if (sys==41) return 0.027+0.02+0.937;
            if (sys==42) return 0.937-(0.027+0.02);
            return 0.937;
        }
        else
        {
            if (sys==41) return 0.002+0.02+0.991;
            if (sys==42) return 0.991-(0.002+0.02);
            return 0.991;
        }
    }
    else if (comb==24)  // em
    {
        if (leadingleppt<35.) 
        {
            if (sys==41) return 0.008+0.02+0.952;
            if (sys==42) return 0.952-(0.008+0.02);
            return 0.952;
        }
        else if (leadingleppt>=35. && leadingleppt<50.) 
        {
            if (sys==41) return 0.003+0.02+0.983;
            if (sys==42) return 0.983-(0.003+0.02);
            return 0.983;
        }
        else 
        {
            if (sys==41) return 0.001+0.02+1.;
            if (sys==42) return 1.-(0.001+0.02);
            return 1.0;
        }
    }
    else if (comb==26)  // mm
    {
        if (leadingleppt<35.) 
        {
            if (sys==41) return 0.006+0.02+0.972;
            if (sys==42) return 0.972-(0.006+0.02);            
            return 0.972;
        }
        else
        {
            if (sys==41) return 0.001+0.02+0.994;
            if (sys==42) return 0.994-(0.001+0.02);
            return 0.994;
        }
    }
    return 1.;
}
double HistMaker::muonSF(double mu_pt, double mu_eta, int lepmult, int sys)
{
    double musf = 1.;
    double abseta = abs(mu_eta);
    
    bool debug = false;
    if (debug) cout << "inside muonSF..." << endl;
    
    // tracking eff sf
    Double_t muSF1 = muh1->Eval(mu_eta); //-2.8-2.8??? this returns a linear interpolation between two points on a TGraphAsymErrors
    if (mu_pt>10) musf *= muSF1; // is there one for <10? <- yes!
    
    if (debug) cout << musf << endl;
    
    double addnlpiece = 0.;
    
    // loose ID sf
    if (mu_pt>=30)
    {
        musf *= muh2->GetBinContent(muh2->FindBin( min(mu_pt,119.9), min(abseta,2.399) ) ); // 20-120; 0-2.4
        addnlpiece += pow(muh2->GetBinError(muh2->FindBin( min(mu_pt,119.9), min(abseta,2.399) ) ),2);

    }
    if (mu_pt<30) 
    {
        musf *= muh2b->GetBinContent(muh2b->FindBin( min(mu_pt,119.9), min(abseta,2.399) ) ); // like 3-40; 0-2.4
        addnlpiece += pow(muh2b->GetBinError(muh2b->FindBin( min(mu_pt,119.9), min(abseta,2.399) ) ),2);
        
    }
    if (debug) cout << musf << endl;
    
    // POG loose -> ttH loose SF
    //musf *= muh3->GetBinContent(muh3->FindBin(max(20.,min(mu_pt,119.9)),min(abseta,2.39)));
    musf *= muh3->GetBinContent(muh3->FindBin(min(mu_pt,119.9),abseta)); // 10-120; 0-2.4
    addnlpiece += pow(muh3->GetBinError(muh3->FindBin(min(mu_pt,119.9),abseta)),2);
    
    if (debug) cout << musf << endl;
    
    // ID tight (lepMVA) sf
    if (lepmult==2)
    {   
        musf *= muh4_2l->GetBinContent(muh4_2l->FindBin(min(mu_pt,99.9),min(abseta,2.49))); // 10-100; 0-2.5
        if (debug) cout << musf << "(lepmult==2)" << endl;
        addnlpiece += pow(muh4_2l->GetBinError(muh4_2l->FindBin(min(mu_pt,99.9),min(abseta,2.49))),2);
    }
    else if (lepmult>=3)
    {   
        //cout << muh4_3l->FindBin(min(mu_pt,99.9),min(abseta,2.49)) << endl;
        musf *= muh4_3l->GetBinContent(muh4_3l->FindBin(min(mu_pt,99.9),min(abseta,2.49))); // 10-100; 0-2.5
        if (debug) cout << musf << "(lepmult==3)" << endl;
        addnlpiece += pow(muh4_3l->GetBinError(muh4_3l->FindBin(min(mu_pt,99.9),min(abseta,2.49))),2);
        
    }
    
    addnlpiece += musf*musf*(2*0.005*0.005 + 0.01*0.01); // 0.5% tracking systematic, 1% ID systematic, and a 0.5% Iso systematic
    addnlpiece = sqrt(addnlpiece);
        
    if (sys==29) musf += addnlpiece;
    if (sys==30) musf -= addnlpiece;
    
    return musf;
    
}

double HistMaker::electronSF(double ele_pt, double ele_eta, int lepmult, int sys)
{
    double elesf = 1.;
    double abseta = abs(ele_eta);

    bool debug = false;
    if (debug) cout << "inside electronSF..." << endl;
    double addnlpiece = 0.;
    
    // its (eta,pt) for this one
    if (ele_pt>=20.)
    {
        elesf *= eleh1->GetBinContent(eleh1->FindBin(ele_eta,min(ele_pt,499.))); // -2.5-2.5; 20-500
        addnlpiece += pow(eleh1->GetBinError(eleh1->FindBin(ele_eta,min(ele_pt,499.))),2);
        
    }
    else
    {
        elesf *= eleh1lowpt->GetBinContent(eleh1lowpt->FindBin(ele_eta,min(ele_pt,19.9))); // -2.5-2.5; 10-20
        addnlpiece += pow(eleh1lowpt->GetBinError(eleh1lowpt->FindBin(ele_eta,min(ele_pt,19.9))),2);
        
    }
    if (debug) cout << elesf << endl;
    
    elesf *= eleh2->GetBinContent(eleh2->FindBin(ele_eta,min(ele_pt,499.))); // -2.5-2.5; 10-500
    if (debug) cout << elesf << endl;
    addnlpiece += pow(eleh2->GetBinError(eleh2->FindBin(ele_eta,min(ele_pt,499.))),2);
    
    if (lepmult==2)
    {        
        elesf *= eleh4_2l->GetBinContent(eleh4_2l->FindBin(min(ele_pt,99.9),min(abseta,2.49))); // 10-100; 0-2.5
        addnlpiece += pow(eleh4_2l->GetBinError(eleh4_2l->FindBin(min(ele_pt,99.9),min(abseta,2.49))),2);
        if (debug) cout << elesf << "(lepmult==2)" << endl;
    }
    else if (lepmult>=3)
    {
        elesf *= eleh4_3l->GetBinContent(eleh4_3l->FindBin(min(ele_pt,99.9),min(abseta,2.49))); // 10-100; 0-2.5
        addnlpiece += pow(eleh4_3l->GetBinError(eleh4_3l->FindBin(min(ele_pt,99.9),min(abseta,2.49))),2);
        if (debug) cout << elesf << "(lepmult==3)" << endl;
    }
    
    addnlpiece = sqrt(addnlpiece);
        
    if (sys==29) elesf += addnlpiece;
    if (sys==30) elesf -= addnlpiece;
    
    return elesf;
    
}

//double topPtWgt

double HistMaker::totalSF(int iSys, vector<string> category, int bin)
{

    if (sample==94 || sample==95 || sample>=100) // in practice should never get to 94 or 95, but doesn't hurt
    {
	    cout << "You are trying to apply MC SFs to data or data-driven background." << endl;
	    cout << "Consequently, this program will now exit via \'exit(EXIT_FAILURE)\'." << endl;
	    exit(EXIT_FAILURE);
    }
    
    bool debug = false;
    
    double weight = 1.;
    
    auto deezleps = tight_leptons;
    
    std::vector<ttH::Jet> cleanedjets;
    if (iSys==1) cleanedjets = preselected_jets_JECup;
    else if (iSys==2) cleanedjets = preselected_jets_JECdown;
    else cleanedjets = preselected_jets;    
    

    //if ( !(cleanedjets.size()>=2 && tight_leptons.size()>=2 && iSys==0) ) debug=false;
    //cleanedjets = simpleJetCut(cleanedjets,"pt",30.0);
    //jets = simpleJetCut(jets,"passPUID",0);
    
    // trigger SFs:
    int nlep = deezleps.size();
    double leadingleppt = nlep>0 ? deezleps[0].obj.Pt() : 0.; // should be correctedPt ?
    int lpdgID1 = nlep>0 ? deezleps[0].pdgID : -999;
    int lpdgID2 = nlep>1 ? deezleps[1].pdgID : -999;
    
    if (debug) cout << " " << endl;
    //if (debug) cout << "Next event... " << endl;    
    if (debug) cout << " " << endl;
    if (debug) cout << "nmuons, nelectrons, njets:  " << tight_muons.size() << ", " << tight_electrons.size() << ", " << cleanedjets.size() << endl;
    double triggersf = triggerSF(lpdgID1, lpdgID2, nlep, leadingleppt, iSys);
    if (debug) cout << "trigger SF: " << triggersf << endl;
    
    weight *= triggersf;
    
    // parton shower SF (comment out ones below if using this)
    if (iSys==37 || iSys==38) weight *= partonShowerSF(bin, category, iSys);
    //weight *= adhocNjetSF(bin, category, iSys);                                                                                                           //////////    <<-----------------------  !!!!!!! don't leave commented !!!!!!!
    
    ///////////  lep SFs ///////////
    // see email from Marco, etc. See also here for prelim. lepMVA sfs:
    // /afs/cern.ch/work/s/sesanche/public/forTTH/SFs_may17/
    //
    // tbd if we stay with lepMVA or move to POG ele mva 80 or 90 WP (due to lack of loose WP sfs)
    //
    // Muon ID SFs:
    //   (tracking eff, reco, loose POG ID, tight lepMVA ID) // <-- Sergio provided part of this? (the loose -> preselected?)
    //   I think all the pieces of this are there, just need to confirm / gather. "Iso" sfs needed? see what was done in past
    //   files:
    //   fits_mu_trkEffSF_2017_allTracks.root = tracking eff (ratio_eff_eta3_dr030e030_corr)
    //   RunBCDEF_SF_ID.root = to loose (or medium? do we need the separate low pt one?)
    //   loose_mu_to_ttH_loose_Sergio.root = the sort of looseMuon id to "loose ttH" ID by Sergio
    //   then the lepMVA ones for muons
    //   
    //
    // Electron ID SFs:
    //   (reco, loose P0G ID (or 80/90 WP if not using lepMVA), tight lepMVA ID (if using))
    //   In principle have reco and tight lepMVA. Missing other(s).
    //   then the lepMVA one for eles
    //
    //
    // ttH-leptons email threads:
    // "First version of tight/loose scale factors"
    // "MC samples needed to estimate conversion background and data/MC SF for loose lepton selection efficiency"
    
    //cout << "heyA" << endl;
    for (const auto dislep : deezleps)
    {
        if (abs(dislep.pdgID)==13)
        {
            double mSF = muonSF(dislep.obj.Pt(),dislep.obj.Eta(),nlep,iSys);
            if (debug) cout << "mu pt, eta, SF:  " << dislep.obj.Pt() << ", " <<  dislep.obj.Eta() << ", " << mSF << endl;   
            weight *= mSF;
        }
        else if (abs(dislep.pdgID)==11)
        {
            double eSF = electronSF(dislep.obj.Pt(),dislep.obj.Eta(),nlep,iSys); 
            if (debug) cout << "el pt, eta, SF:  " << dislep.obj.Pt() << ", " <<  dislep.obj.Eta() << ", " << eSF << endl;                    
            weight *= eSF;
        }
    }
    //cout << "heyB" << endl;
    /////////////////////////////
    
    
    // PU reweighting:
    int ntpvs = *numTruePVs_intree;
    if ( ntpvs<0 ) ntpvs=0;
    if ( ntpvs>199 ) ntpvs=199;
    weight *= pileupSF(ntpvs,iSys);
    
    
    // DeepCSV reweighting:
    double hfSF=1.;
    double lfSF=1.;
    double cSF=1.;
    vint jetFlavor;
    vdouble jetCSV;
    vecTLorentzVector vectJetTLV;
    //for (const auto & jet : *preselected_jets_intree)
    for (const auto & jet : cleanedjets)
    {
        jetCSV.push_back(jet.DeepCSV);
        vectJetTLV.push_back(makeRealTLV(jet.obj));
        jetFlavor.push_back(jet.flavor);
        if (debug) cout << " " << endl;
        if (debug) cout << "jet pt,eta,phi,flavor,DeepCSV: " << jet.obj.Pt() << ", " << jet.obj.Eta() << ", " << jet.obj.Phi() << ", " << jet.flavor << ", " << jet.DeepCSV << endl;
    }
    double deepcsvwgt = 1.;
    if (cleanedjets.size()>0)
    {
        if (debug) cout << "getRobinBtagSyst(iSys): " << getRobinBtagSyst(iSys) << endl;
        deepcsvwgt = get_csv_wgt(true, vectJetTLV, jetCSV, jetFlavor, getRobinBtagSyst(iSys), hfSF, lfSF, cSF);
        weight *= deepcsvwgt;
    }
    if (debug) cout << " " << endl;
    if (debug) cout << "event DeepCSVSF,hfSF,lfSF,cSF: " << deepcsvwgt << ", " << hfSF << ", " << lfSF << ", " << cSF << endl;
    if (debug) cout << " " << endl;
    if (debug) cout << " " << endl;
    if (debug) cout << "Total SF: " << weight << endl;
    if (debug) cout << "next event..." << endl;
    
    
    
//// btag syst mapping:
// CMS_ttHl_btag_cErr1 - up : 29
// CMS_ttHl_btag_cErr2 - up : 31
// CMS_ttHl_btag_HF - up : 17
// CMS_ttHl_btag_LF - up : 19
// CMS_ttHl16_btag_HFStats1 - up : 21
// CMS_ttHl16_btag_HFStats2 - up : 25
// CMS_ttHl16_btag_LFStats1 - up : 23
// CMS_ttHl16_btag_LFStats2 - up : 27
//     
// CMS_ttHl_btag_cErr1 - down : 30
// CMS_ttHl_btag_cErr2 - down : 32
// CMS_ttHl_btag_HF - down : 18
// CMS_ttHl_btag_LF - down : 20
// CMS_ttHl16_btag_HFStats1 - down : 22
// CMS_ttHl16_btag_HFStats2 - down : 26
// CMS_ttHl16_btag_LFStats1 - down : 24
// CMS_ttHl16_btag_LFStats2 - down : 28

                        
    if (iSys==23) weight *= (*nnpdfWeightUp_intree);
    if (iSys==24) weight *= (*nnpdfWeightDown_intree);
    if (iSys==25) weight *= (*muRWeightUp_intree);     
    if (iSys==26) weight *= (*muRWeightDown_intree);   
    if (iSys==27) weight *= (*muFWeightUp_intree);     
    if (iSys==28) weight *= (*muFWeightDown_intree);
    
    // commented out since using function above now
    //if (iSys==37) weight *= (*preshowerISRweightUp_intree);
    //if (iSys==38) weight *= (*preshowerISRweightDown_intree);
    //if (iSys==39) weight *= (*preshowerFSRweightUp_intree);
    //if (iSys==40) weight *= (*preshowerFSRweightDown_intree);
    

    // this is not set up this way, at the end of this function, by mistake:
    if (iSys==35) weight *= (*prefiringweightup_intree);
    else if (iSys==36) weight *= (*prefiringweightdown_intree);
    else weight *= (*prefiringweight_intree); // we really do want this applied in all cases except sys 35 or 36

    return weight;
    
    
}
