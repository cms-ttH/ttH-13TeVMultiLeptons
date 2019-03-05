std::unordered_map<string,int> sample_TString2int_map()
{
    // Moving to centralized place for defining this string -> int mapping.
    // Should be used everywhere (loadsample, setup.h, macros, etc.).
    std::unordered_map<string,int> dummy;
    
    ///// signals /////
    // main signals
    dummy["ttH"] = 1; // ttH_NLO // ttH_LO_old
    dummy["ttW"] = 8;
    dummy["ttZ"] = 9;
    // additional signals
    dummy["tZq"] = 26;
    dummy["tttt"] = 27;
    dummy["ttWW"] = 28;
    dummy["ttWZ"] = 29;
    
    ///// backgrounds /////
    // V + jets
    dummy["DYJets_M50"] = 6;
    dummy["DYJets_M10to50"] = 16;
    dummy["WJets"] = 7;
    // diboson
    dummy["WZ"] = 10;    
    dummy["ZZ"] = 11;    
    dummy["WW"] = 12;
    // ttbar + jets
    dummy["ttJets"] = 5;
    //dummy["ttJets_Dilept"] = 13;
    //dummy["ttJets_SingleLeptFromT"] = 14;
    //dummy["ttJets_SingleLeptFromTbar"] = 15;    
    // single top
    dummy["SingleTop_tWchan_top"] = 17;  
    dummy["SingleTop_tWchan_antitop"] = 18;    
    dummy["SingleTop_tchan_top"] = 19;  
    dummy["SingleTop_tchan_antitop"] = 20;        
    dummy["SingleTop_schan"] = 21;
    // triboson
    dummy["WWW"] = 22;
    dummy["WWZ"] = 23;
    dummy["WZZ"] = 24;
    dummy["ZZZ"] = 25;
    
    dummy["ttGJets"] = 30;
    
    dummy["tHq"] = 31;
    
    // EFT samps
    
    
    //ttH_EFT
    dummy["ttH_cbW"]    = 40;
    dummy["ttH_cpQ3"]   = 41;
    dummy["ttH_cpQM"]   = 42;
    dummy["ttH_cptb"]   = 43;
    dummy["ttH_cpt"]    = 44;
    dummy["ttH_cQe1"]   = 45;
    dummy["ttH_ctG"]    = 46;
    dummy["ttH_ctl1"]   = 47;
    dummy["ttH_ctp"]    = 48;
    dummy["ttH_ctW"]    = 49;
    dummy["ttH_ctZ"]    = 50;
    
    //tllq_EFT
    // missing cbW for the moment = 51;
    dummy["tllq_cpQ3"]  = 52;          
    dummy["tllq_cpQM"]  = 53;          
    dummy["tllq_cptb"]  = 54;
    dummy["tllq_cpt"]   = 55;   
    dummy["tllq_cQe1"]  = 56;         
    dummy["tllq_ctG"]   = 57;        
    dummy["tllq_ctl1"]  = 58;         
    dummy["tllq_ctp"]   = 59;
    dummy["tllq_ctW"]   = 60;
    dummy["tllq_ctZ"]   = 61;  
    
    //ttll_EFT
    dummy["ttll_cbW"]   = 62;
    dummy["ttll_cpQ3"]  = 63;
    dummy["ttll_cpQM"]  = 64;
    dummy["ttll_cptb"]  = 65;
    dummy["ttll_cpt"]   = 66;
    dummy["ttll_cQe1"]  = 67;
    dummy["ttll_ctG"]   = 68;
    dummy["ttll_ctl1"]  = 69;
    dummy["ttll_ctp"]   = 70;
    dummy["ttll_ctW"]   = 71;
    dummy["ttll_ctZ"]   = 72;
    
    //ttlnu_EFT
    dummy["ttlnu_cbW"]  = 73;
    dummy["ttlnu_cpQ3"] = 74;
    dummy["ttlnu_cpQM"] = 75;
    dummy["ttlnu_cptb"] = 76;
    dummy["ttlnu_cpt"]  = 77;
    dummy["ttlnu_cQe1"] = 78;
    dummy["ttlnu_ctG"]  = 79;
    dummy["ttlnu_ctl1"] = 80;
    dummy["ttlnu_ctp"]  = 81;
    dummy["ttlnu_ctW"]  = 82;
    dummy["ttlnu_ctZ"]  = 83;
    
    // EFT multidim
    dummy["ttH_multidim"]   = 84;
    dummy["ttlnu_multidim"] = 85;
    dummy["ttll_multidim"]  = 86;
    dummy["tllq_multidim"]  = 87;
    dummy["tHq_multidim"]  = 88;
    
    
    //dummy["Diboson"] = 91; // actually, no, you can't do that
    //dummy["Triboson"] = 92; // actually, no, you can't do that
    // single top was 93..
    dummy["QFs"]  = 94;
    dummy["Fakes"]  = 95;

    ////// data /////
    dummy["SingleMuon"] = 100;
    dummy["SingleElectron"] = 101;
    dummy["DoubleMuon"] = 102;
    dummy["DoubleEG"] = 103;
    dummy["MuonEG"] = 104;
    
    dummy["MET"] = 105;
    
    ////// extra /////
    // in case you want to supply a one-off sample that's in a
    // different directory than usual, or in case you want to 
    // compare 2 versions of the same sample (e.g. for validation, etc.)
    dummy["ttGJets_ext"] = 0;
    
    return dummy;
}
std::unordered_map<int,string> sample_int2TString_map()
{
    std::unordered_map<int,string> reversedummy;
    auto dummy = sample_TString2int_map();
    // works as long as both keys and values are unique:
    for (const auto & it : dummy) reversedummy[it.second] = it.first;
    return reversedummy;
}
int sample_TString2int(TString tstrsamp)
{
    string strsamp = TString2string(tstrsamp);
    auto blah = sample_TString2int_map();
    if (!blah[strsamp]) cout << "Warning: sample may be unspecified. See loadsample.h." << endl;
    return blah[strsamp];
}
TString sample_int2TString(int intsamp)
{
    auto blah = sample_int2TString_map();
    if (blah[intsamp]=="")
    {
        cout << "Warning: unspecified sample. See loadsample.h." << endl;
        return "none";
    }
    return TString(blah[intsamp]);
}

double getNumInitialMCevents (int sample, TChain &ch)
{
    // Derived from https://root.cern.ch/doc/master/classTChain.html#a4d491db32262125e6cb77a8f7a6bfd93.
    //
    // If the "numInitialWeightedMCevents" histo is present in the root files, it is extremely preferable to
    // use this function to automatically retrieve the initial number of mc events (useful for calculating 
    // event yields). 
    // 
    
    double returnedEvents=0.;
    TH1D *sumHist = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);
    
    TObjArray *fileElements=ch.GetListOfFiles();
    TIter next(fileElements);
    TChainElement *chEl=0;
    while (( chEl=(TChainElement*)next() ))
    {
        // Do it this way because this is actually not a TFile 
        // (it's TNetXNGFile or similar) when opening remotely,
        // and you will not be able to access anything if you
        // declare it as a TFile:
        auto f = TFile::Open(chEl->GetTitle());
        TH1D *temphist = (TH1D*)f->Get("OSTwoLepAna/numInitialWeightedMCevents");
        sumHist->Add(temphist);
        f->Close();
    }
    returnedEvents = sumHist->Integral();
    delete sumHist;
    return returnedEvents;
}

//double loadsample(const int samp, TChain &ch)
TString loadsample(const int samp)
{
    bool atND = true;       // Choose whether files are located at ND or at CERN (on an ndpc).

    //TString thisround = "lobster_trees__EFT_test_28_4_18"; // 28 // 14
    //TString thisround = "lobster_trees__EFT_SingleMu_only_test_10_5_18";
    //TString thisround = "lobster_trees__EFT_noSkim_test_10_5_18";
    //TString thisround = "lobster_trees__EFT_for_trigSFs_15_5_18";
    //TString thisround = "lobster_trees__lobster_trees__EFT_test_25_5_18";
    //TString thisround = "lobster_trees__lobster_trees__EFT_test_14_6_18";
    //TString thisround = "lobster_trees__EFT_test_multidim_samps_ext_16_7_18";
    //TString thisround = "lobster_trees__EFT_test_for_pdfs_central_ttH_13_9_18";
    //TString thisround = "lobster_trees__EFT_test_for_pdfs_EFT_ttH_13_9_18";
    //TString thisround = "lobster_trees__EFT_test_multidim_samps_ext_11_10_18";
    //TString thisround = "lobster_trees__EFT_test_just_powheg_ttH_again_for_pdfs_11_10_18";
    //TString thisround = "lobster_trees__EFT_test_all_mc_bkds_for_pdfs_1_11_18_b";
    TString thisround = "lobster_trees__EFT_test_27_2_19_central";
    
    TString basedir = "/hadoop/store/user/gesmith/"+thisround+"/";  // The directory on hadoop where your samples are located.
    if (!atND) basedir = "/store/ndpc6disk2/gesmith/crab/";         // The directory on ndpc disk where your samples are located.

    
    TString thissample = "none";
    TString thissubsample = "";    
    
    
    //if (samp==0) // "extra"
    //{
        //cout << "Using sample=0 for data is deprecated. Use 100-104 instead. See loadsample.h." << endl;
    //}
    
    // Vast majority of the time we will want to use this method:
    if (samp<1000)
    {
        thissample = sample_int2TString(samp);
    }
    
    // In case we want to split up data by era:
    else if (samp>=1000 && samp<1010) // SingleMu data
    {
	    thissample = "SingleMuon";
    }    
    else if (samp>=1010 && samp<1020) // SingleElectron data
    {
	    thissample = "SingleElectron";
    }
    else if (samp>=1020 && samp<1030) // DoubleMu data
    {
	    thissample = "DoubleMuon";
    }    
    else if (samp>=1030 && samp<1040) // DoubleElectron data
    {
	    thissample = "DoubleEG";
    }    
    else if (samp>=1040) // Muon+Electron data
    {
	    thissample = "MuonEG";
    }     
        
    else cout << "This sample has not been specified. See loadsample." << endl;
    
    // In case we want to split up data by era (continued):
    if (samp>=1000)
    {
        if ((samp%10)==0)
        {
            thissubsample = "_Run2016Bv1";
        }
        else if ((samp%10)==1)
        {
            thissubsample = "_Run2016Bv2";
        }    
        else if ((samp%10)==2)
        {
            thissubsample = "_Run2016C";
        }    
        else if ((samp%10)==3)
        {
            thissubsample = "_Run2016D";
        }    
        else if ((samp%10)==4)
        {
            thissubsample = "_Run2016E";
        }    
        else if ((samp%10)==5)
        {
            thissubsample = "_Run2016F";
        }    
        else if ((samp%10)==6)
        {
            thissubsample = "_Run2016G";
        }    
        else if ((samp%10)==7)
        {
            thissubsample = "_Run2016H";
        }    
    
        else cout << "This sub-sample has not been specified. See loadsample." << endl;
    }
    
    if (thissample!="none")
    {
        // now actually add the files to the chain:
        if (!atND)
        {
            TString basedir_plus = thisround+"/"+thissample+"/";
            TString thesample = basedir + basedir_plus + "*.root";
            //ch.Add(thesample);
        }
        else
        {
            // Need to do it this way because crab creates multiple sub-dirs per sample and TChain isn't smart enough to handle that without some help:
            TString lsstring = "ls -d "+basedir+"*/crab_"+thisround+"__"+thissample+"*/*/*/*.root | grep -v \"failed\" > inputfiles__"+thissample+".txt"; // .!
            if (samp>99 && samp<1000) lsstring = "find "+basedir+thissample+"/ -name \"*.root\" | grep -v \"failed\" > inputfiles__"+thissample+".txt";
            if (samp>999) lsstring = "find "+basedir+thissample+"/crab_"+thisround+"__"+thissample+thissubsample+" -name \"*.root\" | grep -v \"failed\" > inputfiles__"+thissample+thissubsample+".txt";
            
            //if trees produced with lobster:
            lsstring = "ls -d "+basedir+thissample+"/*.root > inputfiles__"+thissample+".txt";
            if ((samp>99 && samp<1000) || (samp>83 && samp<89)) lsstring = "find "+basedir+thissample+"_*/ -name \"*.root\" > inputfiles__"+thissample+".txt";
            
            // should be able to add " | sed 's#/hadoop/#root://deepthought.crc.nd.edu//#'" before the ">" if you want to use xrootd instead of fuse.
            // note: i found that sed didn't seem to be working when i tried it here (though it's possible i was doing something wrong...)
            //gROOT->ProcessLine(lsstring);
            system(lsstring);
            //TFileCollection fc("dum","","inputfiles__"+thissample+thissubsample+".txt"); // <- now done elsewhere
            //ch.AddFileInfoList(fc.GetList()); // <- now done elsewhere
        }
    }
    
    return thissample+thissubsample;
}
