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
    double numgen = 1.;
    
    TString basedir = "/store/ndpc6disk2/gesmith/crab/";     // The directory on ndpc disk where your samples are located.

                
    if (samp==0) // data
    {
            cout << "This sample has not been specified. See loadsample." << endl;

    }
    else if (samp==1) // ttH
    {                        
            TString basedir_plus = "EFT_test_19_12_17__ttH/";                        // subdirectory for this sample
            TString thesample = basedir + basedir_plus + "*.root";
            ch.Add(thesample);
    }        
    else if (samp==5) // TTJets
    {
	    TString basedir_plus = "EFT_test_19_12_17__ttJets/";
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);             
    }
    else if (samp==6) // ZJets (aka Drell Yan)
    {
            TString basedir_plus = "EFT_test_19_12_17__DYJets_M50/";
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
    }
    else if (samp==7) // WJets
    {
            TString basedir_plus = "EFT_test_19_12_17__WJets/";
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);        
    }
    else if (samp==8) // TTWJets
    {                        
            TString basedir_plus = "EFT_test_19_12_17__ttW/";
            TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample); 
    }
    else if (samp==9) // TTZJets
    {
            TString basedir_plus = "EFT_test_19_12_17__ttZ/";
            TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
    }
    else if (samp==10) // diboson (WZ)
    {
            TString basedir_plus = "EFT_test_19_12_17__WZ/";
            TString thesample = basedir + basedir_plus + "*.root";
            ch.Add(thesample);
    }
    else if (samp==11) // diboson (ZZ)
    {
            TString basedir_plus = "EFT_test_19_12_17__ZZ/";
            TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
    }
    else if (samp==12) // diboson (WW)
    {
            TString basedir_plus = "EFT_test_19_12_17__WW/";
            TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
    }
    else if (samp==13) // dilepton ttbar
    {
	    TString basedir_plus = "EFT_test_19_12_17__ttJets_Dilept/";
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
    }
    else if (samp==14) // ttbar: 1l from top
    {
	    TString basedir_plus = "EFT_test_19_12_17__ttJets_SingleLeptFromT/";
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);       
    }
    else if (samp==15) // ttbar: 1l from anti-top
    {
	    TString basedir_plus = "EFT_test_19_12_17__ttJets_SingleLeptFromTbar/";
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);    
    }
    else if (samp==16) // Drell Yan (low mass)
    {
	    TString basedir_plus = "EFT_test_19_12_17__DYJets_M10to50/";                                                // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);         
    }
    else if (samp==17) // SingleTop_tWchan_top
    {
	    TString basedir_plus = "EFT_test_19_12_17__SingleTop_tWchan_top/";                                                // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);        
    }
    else if (samp==18) // SingleTop_tWchan_antitop
    {
	    TString basedir_plus = "EFT_test_19_12_17__SingleTop_tWchan_antitop/";                                                // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);          
    }
    else if (samp==19) // SingleTop_tchan_top
    {
	    TString basedir_plus = "EFT_test_19_12_17__SingleTop_tchan_top/";                                                // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);      
    }
    else if (samp==20) // SingleTop_tchan_antitop
    {
	    TString basedir_plus = "EFT_test_19_12_17__SingleTop_tchan_antitop/";                                                // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);     
    }
    else if (samp==21) // SingleTop_schan
    {
	    TString basedir_plus = "EFT_test_19_12_17__SingleTop_schan/";                                                // <-- to update
	    TString thesample = basedir + basedir_plus + "*.root";
	    ch.Add(thesample);
    }
    
    
    else cout << "This sample has not been specified. See loadsample." << endl;
    
    
    numgen = getNumInitialMCevents(samp,ch); // use this to get numgen
    return numgen;
}
