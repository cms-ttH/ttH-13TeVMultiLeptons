std::unordered_map<string,int> sample_TString2int_map()
{
    // Moving to centralized place for defining this string -> int mapping.
    // Should be used everywhere (loadsample, setup.h, macros, etc.).
    std::unordered_map<string,int> dummy;
    
    ///// signals /////
    // main signals
    dummy["ttH"] = 1;
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
    dummy["ttJets_Dilept"] = 13;
    dummy["ttJets_SingleLeptFromT"] = 14;
    dummy["ttJets_SingleLeptFromTbar"] = 15;    
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

    ////// data /////
    dummy["SingleMuon"] = 100;
    dummy["SingleElectron"] = 101;
    dummy["DoubleMuon"] = 102;
    dummy["DoubleEG"] = 103;
    dummy["MuonEG"] = 104;
    
    ////// extra /////
    // in case you want to supply a one-off sample that's in a
    // different directory than usual, or in case you want to 
    // compare 2 versions of the same sample (e.g. for validation, etc.)
    dummy["ttH_EFTtest1"] = 0;
    
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
    if (!blah[strsamp]) cout << "Warning: unspecified sample. See loadsample.h." << endl;
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

    TString thisround = "lobster_trees__EFT_test_14_4_18";
    
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
            if (samp>99 && samp<1000) lsstring = "find "+basedir+thissample+"_*/ -name \"*.root\" > inputfiles__"+thissample+".txt";
            
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
