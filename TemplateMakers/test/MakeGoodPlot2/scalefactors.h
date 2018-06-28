void HistMaker::setupSFs()
{
    // This function is run in the HistMaker constructor
    
    TString basedir = getenv("CMSSW_BASE");
    auto pudatafile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/PU/2017PU_SFstest.root");
    pileupSFs = (TH1D*)pudatafile->Get("pileupSF");
    
    auto hffile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/btag/Deepcsv_rwt_fit_hf_v2_final_2018_2_12test.root");
    auto lffile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/btag/Deepcsv_rwt_fit_lf_v2_final_2018_2_12test.root");
    fillCSVhistos(hffile,lffile);
    
    auto muSFfile1 = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/fits_mu_trkEffSF_2017_allTracks.root");
    auto muSFfile2 = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/RunBCDEF_SF_ID.root");
    //auto muSFfile3 = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/loose_mu_to_ttH_loose_Sergio.root"); // bug in the file
    
    muh1 = (TGraphAsymmErrors*)muSFfile1->Get("ratio_eff_eta3_dr030e030_corr");
    muh2 = (TH2D*)muSFfile2->Get("NUM_MediumID_DEN_genTracks_pt_abseta"); // <- should be LooseID


    auto eleSFfile1a = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
    auto eleSFfile1b = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/leptonSF/egammaEffi.txt_EGM2D_runBCDEF_passingRECO_lowEt.root");

    eleh1 = (TH2F*)eleSFfile1a->Get("EGamma_SF2D");
    eleh1lowpt = (TH2F*)eleSFfile1b->Get("EGamma_SF2D");


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
    auto FRSFfile = TFile::Open(basedir+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/fakerate/leptonFakeRates_Tallinn_2018May24.root");
    elFRsfs = (TH2D*)FRSFfile->Get("FR_mva090_el_data_comb");
    muFRsfs = (TH2D*)FRSFfile->Get("FR_mva090_mu_data_comb");

    
}

double HistMaker::pileupSF(int numtrueint)
{
    // assumes that setupSFs has been run already
    return pileupSFs->GetBinContent(numtrueint+1);
    // if up / down ...
}

double triggerSF(int pdgid1, int pdgid2, int nlep, double leadingleppt)
{
    if (nlep>=3) return 1.0;

    int comb = abs(pdgid1)+abs(pdgid2);
    
    if (comb==1010) comb = 22; //kludge
    if (comb==1012) comb = 26; //kludge
    
    if (comb==22) // ee
    {
        if (leadingleppt<30.) return 0.937;
        else return 0.991;
    }
    else if (comb==24)  // em
    {
        if (leadingleppt<35.) return 0.952;
        else if (leadingleppt>=35. && leadingleppt<50.) return 0.983;
        else return 1.0;
    }
    else if (comb==26)  // mm
    {
        if (leadingleppt<35.) return 0.972;
        else return 0.994;
    }
    return 1.;
}
double HistMaker::muonSF(double mu_pt, double mu_eta, int lepmult)
{
    double musf = 1.;
    double abseta = abs(mu_eta);
    
    //cout << mu_pt << endl;
    //cout << mu_eta << endl;
    
    //cout << "hey1" << endl;
    // tracking eff sf
    Double_t muSF1 = muh1->Eval(mu_eta); // this returns a linear interpolation between two points on a TGraphAsymErrors
    if (mu_pt>20) musf *= muSF1; // is there one for <20?
    //cout << "hey2" << endl;
    // loose ID sf
    musf *= muh2->GetBinContent(muh2->FindBin(max(20.,min(mu_pt,119.9)),min(abseta,2.39)));
    //cout << "hey3" << endl;
    // POG loose -> ttH loose SF
    //auto muh3 = muSFfile3->Get(""); // something wrong with the file
    
    // ID tight (lepMVA) sf
    if (lepmult==2)
    {   
        //cout << "hey4.0" << endl;
        musf *= muh4_2l->GetBinContent(muh4_2l->FindBin(min(mu_pt,99.9),min(abseta,2.49)));
        //cout << "hey4" << endl;
    }
    else if (lepmult>=3)
    {   
        //cout << "hey5.0" << endl;
        //cout << muh4_3l->FindBin(min(mu_pt,99.9),min(abseta,2.49)) << endl;
        musf *= muh4_3l->GetBinContent(muh4_3l->FindBin(min(mu_pt,99.9),min(abseta,2.49)));
        //cout << "hey5" << endl;
    }
    
    return musf;
    
}

double HistMaker::electronSF(double ele_pt, double ele_eta, int lepmult)
{
    double elesf = 1.;
    double abseta = abs(ele_eta);

    // todo: fill in this part...
    // its (eta,pt) for this one
    if (ele_pt>=20.) elesf *= eleh1->GetBinContent(eleh1->FindBin(ele_eta,min(ele_pt,499.)));
    else elesf *= eleh1lowpt->GetBinContent(eleh1lowpt->FindBin(ele_eta,min(ele_pt,19.9)));
    
    if (lepmult==2)
    {
        
        elesf *= eleh4_2l->GetBinContent(eleh4_2l->FindBin(min(ele_pt,99.9),min(abseta,2.49)));
    }
    else if (lepmult>=3)
    {
        
        elesf *= eleh4_3l->GetBinContent(eleh4_3l->FindBin(min(ele_pt,99.9),min(abseta,2.49)));
    }
    
    return elesf;
    
}

//double topPtWgt

double HistMaker::totalSF(int iSys, vector<string> category)
{
    // 2017 under construction
    // uncertainties? :P

    bool debug = false;
    
    double weight = 1.;
    
    auto deezleps = tight_leptons;
    
    std::vector<ttH::Jet> cleanedjets;
    if (iSys==0) cleanedjets = preselected_jets;
    if (iSys==1) cleanedjets = preselected_jets_JECup;
    if (iSys==2) cleanedjets = preselected_jets_JECdown;
    // if iSys==1 , JESup, etc.?
    
    //cleanedjets = simpleJetCut(cleanedjets,"pt",30.0);
    //jets = simpleJetCut(jets,"passPUID",0);
    
    // trigger SFs:
    int nlep = deezleps.size();
    double leadingleppt = nlep>0 ? deezleps[0].obj.Pt() : 0.;
    int lpdgID1 = nlep>0 ? deezleps[0].pdgID : -999;
    int lpdgID2 = nlep>1 ? deezleps[1].pdgID : -999;
    weight *= triggerSF(lpdgID1, lpdgID2, nlep, leadingleppt);
    
    
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
        if (abs(dislep.pdgID)==13) weight *= muonSF(dislep.obj.Pt(),dislep.obj.Eta(),nlep);
        else if (abs(dislep.pdgID)==11) weight *= electronSF(dislep.obj.Pt(),dislep.obj.Eta(),nlep);
    }
    //cout << "heyB" << endl;
    /////////////////////////////
    
    
    // PU reweighting:
    int ntpvs = *numTruePVs_intree;
    if ( ntpvs<0 ) ntpvs=0;
    if ( ntpvs>199 ) ntpvs=199;
    weight *= pileupSF(ntpvs);
    
    
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
        deepcsvwgt = get_csv_wgt(true, vectJetTLV, jetCSV, jetFlavor, 0, hfSF, lfSF, cSF); // iSys=0 for now-> fix
        weight *= deepcsvwgt;
    }
    if (debug) cout << " " << endl;
    if (debug) cout << "event DeepCSVSF,hfSF,lfSF,cSF: " << deepcsvwgt << ", " << hfSF << ", " << lfSF << ", " << cSF << endl;
    if (debug) cout << " " << endl;
    if (debug) cout << " " << endl;
    if (debug) cout << "next event..." << endl;
    
    return weight;
    
}