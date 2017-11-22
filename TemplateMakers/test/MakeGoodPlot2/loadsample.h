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

double loadsample(const int samp, TChain &ch)
{
    double xsec = 1.;
    double numgen = 1.;
    
    TString basedir = "/store/ndpc5disk1/gesmith/crab/";     // The directory on ndpc disk where your samples are located.

                
    if (samp==0) // data
    {
            cout << "This sample has not been specified. See loadsample." << endl;

    }
    else if (samp==1) // ttH
    {                        
            TString basedir_plus = "EFT_test_14_11_17__ttH/";                        // subdirectory for this sample
            TString thesample = basedir + basedir_plus + "*.root";
            ch.Add(thesample);
            xsec=0.5085;                                                            // cross section for this process (needs to be set manually).
            numgen = getNumInitialMCevents(1,ch);    // use this instead to get numgen
    }    
    
    else if (samp==5) // TTJets
    {
	    TString basedir_plus = "EFT_test_14_11_17__ttJets/";                                              // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
	    xsec = 815.96; // at 173.2 GeV (top group twiki)
            numgen = getNumInitialMCevents(5,ch);
    }
    else if (samp==6) // ZJets
    {
            TString basedir_plus = "DYJetsToLL_M-50_13TeV-madgraph-pythia8/crab_zJets/150519_150537/0000/";     // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);    
            xsec=2008.4;
            numgen = getNumInitialMCevents(6,ch);
    }
    else if (samp==7) // WJets
    {
            TString basedir_plus = "WJetsToLNu_13TeV-madgraph-pythia8-tauola/crab_wJets/150519_150558/0000/";   // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
            xsec=20508.9;            
            numgen = getNumInitialMCevents(7,ch);
    }
    else if (samp==8) // TTWJets
    {                        
            TString basedir_plus = "EFT_test_14_11_17__ttW/";                                                                 // <-- to update
            TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
	    xsec=0.6647;
            numgen = getNumInitialMCevents(8,ch);
    }
    else if (samp==9) // TTZJets
    {
            TString basedir_plus = "EFT_test_14_11_17__ttZ/";     // <-- to update
            TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
            xsec=0.8565;
            numgen = getNumInitialMCevents(9,ch);
    }
    else if (samp==10) // diboson (WZ)
    {
            TString basedir_plus = "WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola/crab_wzJets/150519_150616/0000/"; // <-- to update
            TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
            xsec=2.165;
            numgen = getNumInitialMCevents(10,ch);
    }

    else if (samp==11) // diboson (ZZ)
    {
            TString basedir_plus = "ZZTo4L_Tune4C_13TeV-powheg-pythia8/crab_zzJets/150519_150636/0000/";        // <-- to update
            TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
            xsec=0.325;
            numgen = getNumInitialMCevents(11,ch);
    }

    else if (samp==12) // (unused)
    {
            cout << "This sample has not been specified. See load_samples function." << endl;
    }

    else if (samp==13) // dilepton ttbar
    {
	    TString basedir_plus = "TTJets_split_2lep/";                                                        // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
	    xsec=85.656; // at 173.2 GeV (top group twiki). == 815.96 (xsec) * 0.104976 (BR)
            numgen = getNumInitialMCevents(13,ch);
    }

    else if (samp==14) // ttbar: 1l from top
    {
	    TString basedir_plus = "TTJets_split_1lepFromT/";                                                   // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
	    xsec=178.71; // at 173.2 GeV (top group twiki). == 815.96 (xsec) * 0.219024 (BR)
            numgen = getNumInitialMCevents(14,ch);
    }

    else if (samp==15) // ttbar: 1l from anti-top
    {
	    TString basedir_plus = "TTJets_split_1lepFromTBar/";                                                // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
	    xsec=178.71; // at 173.2 GeV (top group twiki). == 815.96 (xsec) * 0.219024 (BR)
            numgen = getNumInitialMCevents(15,ch);
    }

    
    
    else cout << "This sample has not been specified. See loadsample." << endl;
    
    
    return xsec/numgen;
}
