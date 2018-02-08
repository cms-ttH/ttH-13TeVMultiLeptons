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
        TFile *f = new TFile(chEl->GetTitle());
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
    bool atND = true; // Choose whether files are located at ND or at CERN (on an ndpc).
    TString thisround = "EFT_test_19_12_17";
    
    TString basedir = "/hadoop/store/user/gesmith/crab/"+thisround+"/";     // The directory on hadoop where your samples are located.
    if (!atND) TString basedir = "/store/ndpc6disk2/gesmith/crab/";         // The directory on ndpc disk where your samples are located.

    
    TString thissample = "none";
    TString thissubsample = "";
    
    if (samp==0) // data
    {
        //thissample = "__SingleMuon"; // temp
        cout << "Using sample=0 for data is deprecated. Use 100-104 instead. See loadsample.h." << endl;
    }
    else if (samp==1) // ttH
    {                        
        thissample = "ttH";
    }        
    else if (samp==5) // TTJets
    {
	    thissample = "ttJets";
    }
    else if (samp==6) // ZJets (aka Drell Yan)
    {
        thissample = "DYJets_M50";
    }
    else if (samp==7) // WJets
    {
        thissample = "WJets";
    }
    else if (samp==8) // TTWJets
    {                        
        thissample = "ttW";
    }
    else if (samp==9) // TTZJets
    {
        thissample = "ttZ";
    }
    else if (samp==10) // diboson (WZ)
    {
        thissample = "WZ";
    }
    else if (samp==11) // diboson (ZZ)
    {
        thissample = "ZZ";
    }
    else if (samp==12) // diboson (WW)
    {
        thissample = "WW";
    }
    else if (samp==13) // dilepton ttbar
    {
	    thissample = "ttJets_Dilept";
    }
    else if (samp==14) // ttbar: 1l from top
    {
	    thissample = "ttJets_SingleLeptFromT";
    }
    else if (samp==15) // ttbar: 1l from anti-top
    {
	    thissample = "ttJets_SingleLeptFromTbar";  
    }
    else if (samp==16) // Drell Yan (low mass)
    {
	    thissample = "DYJets_M10to50";                                                // <-- to update     
    }
    else if (samp==17) // SingleTop_tWchan_top
    {
	    thissample = "SingleTop_tWchan_top";                                                // <-- to update     
    }
    else if (samp==18) // SingleTop_tWchan_antitop
    {
	    thissample = "SingleTop_tWchan_antitop";                                                // <-- to update      
    }
    else if (samp==19) // SingleTop_tchan_top
    {
	    thissample = "SingleTop_tchan_top";                                                // <-- to update     
    }
    else if (samp==20) // SingleTop_tchan_antitop
    {
	    thissample = "SingleTop_tchan_antitop";                                                // <-- to update  
    }
    else if (samp==21) // SingleTop_schan
    {
	    thissample = "SingleTop_schan";                                                // <-- to update
    }
    
    // data
    else if (samp==100 || (samp>=1000 && samp<1010)) // SingleMu data
    {
	    thissample = "SingleMuon";
    }    
    else if (samp==101 || (samp>=1010 && samp<1020)) // SingleElectron data
    {
	    thissample = "SingleElectron";
    }
    else if (samp==102 || (samp>=1020 && samp<1030)) // DoubleMu data
    {
	    thissample = "DoubleMuon";
    }    
    else if (samp==103 || (samp>=1030 && samp<1040)) // DoubleElectron data
    {
	    thissample = "DoubleEG";
    }    
    else if (samp==104 || (samp>=1040)) // Muon+Electron data
    {
	    thissample = "MuonEG";
    }     
        
    else cout << "This sample has not been specified. See loadsample." << endl;
    
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
        TString lsstring = "ls -d "+basedir+"*/crab_"+thisround+"__"+thissample+"*/*/*/*.root > inputfiles__"+thissample+".txt"; // .!
        if (samp>99 && samp<1000) lsstring = "find "+basedir+thissample+"/ -name \"*.root\" | grep -v \"failed\" > inputfiles__"+thissample+".txt";
        if (samp>999) lsstring = "find "+basedir+thissample+"/crab_"+thisround+"__"+thissample+thissubsample+" -name \"*.root\" | grep -v \"failed\" > inputfiles__"+thissample+thissubsample+".txt";
        // or, add " | sed 's#/hadoop/#root://deepthought.crc.nd.edu//#'" before the ">" if you want to use xrootd instead of fuse.
        //gROOT->ProcessLine(lsstring);
        system(lsstring);
        
        
        //TFileCollection fc("dum","","inputfiles__"+thissample+thissubsample+".txt");
        //ch.AddFileInfoList(fc.GetList());
    }
    
    //double numgen = 1.;
    //if (samp<100) numgen = getNumInitialMCevents(samp,ch); // use this to get numgen
    //return numgen;
    
    return thissample+thissubsample;
}
