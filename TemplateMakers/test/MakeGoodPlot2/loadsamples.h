void MakeGoodPlot::load_samples(std::vector<int> samps)
{
	       
        TString basedir = "/store/ndpc5disk1/gesmith/crab/ttH_test_1_11_17/";     // The directory on ndpc disk where your samples are located.
        //TString basedir = "/store/ndpc6disk1/gesmith/sshjobs/ttH_test_17_10_17/";
        bool useNumInitialWeightedMCevents = true;                  // Set to false if for some reason this histo is not present in the trees (event yields will not be correct).


	int numsamples = samps.size(); 
               
	for (int i=0; i<numsamples; i++)
	{
                
                cout << samps[i] << endl;
                
		if (samps[i]==0) // data
		{
                        cout << "This sample has not been specified. See load_samples function." << endl;
                                   
		}
		if (samps[i]==1) // ttH
		{                        
                        //TString basedir_plus = "ttHToNonbb_M125_ttHtranche3_powheg_Moriond17/";     // subdirectory for this sample
                        //TString basedir_plus = "ttH125/";
                        TString basedir_plus = "";
                        TString thesample = basedir + basedir_plus + "*.root";
                        ch[1]->Add(thesample);
                        xsecs[1]=0.5085;                                                            // cross section for this process (needs to be set manually).
			numgen[1]=2600389.15887;                                                    // placeholder (deprecated)
                        if (useNumInitialWeightedMCevents) numgen[1] = getNumInitialMCevents(1);    // use this instead to get numgen
		}
		if (samps[i]==2) // (unused)
		{
                        cout << "This sample has not been specified. See load_samples function." << endl;
			
		}
		if (samps[i]==3) // (unused)
		{ 
                        cout << "This sample has not been specified. See load_samples function." << endl;
			
		}
		if (samps[i]==4) // (unused)
		{
                        cout << "This sample has not been specified. See load_samples function." << endl;

		}
		if (samps[i]==5) // TTJets
		{
			TString basedir_plus = "try1_ttWkevin_mAODV2/TTJets/";                                              // <-- to update
			TString thesample = basedir + basedir_plus + "*.root";
			ch[5]->Add(thesample);
			xsecs[5]=815.96; // at 173.2 GeV (top group twiki)
			numgen[5]=25446993.0;
                        if (useNumInitialWeightedMCevents) numgen[5] = getNumInitialMCevents(5);
		}
		if (samps[i]==6) // ZJets
		{
                        TString basedir_plus = "DYJetsToLL_M-50_13TeV-madgraph-pythia8/crab_zJets/150519_150537/0000/";     // <-- to update
			TString thesample = basedir + basedir_plus + "*.root";
			ch[6]->Add(thesample);    
                        xsecs[6]=2008.4;
                        numgen[6]=2829164.0;
                        if (useNumInitialWeightedMCevents) numgen[6] = getNumInitialMCevents(6);
		}
		if (samps[i]==7) // WJets
		{
                        TString basedir_plus = "WJetsToLNu_13TeV-madgraph-pythia8-tauola/crab_wJets/150519_150558/0000/";   // <-- to update
			TString thesample = basedir + basedir_plus + "*.root";
			ch[7]->Add(thesample);
                        xsecs[7]=20508.9;		
			numgen[7]=10017462.0;
                        if (useNumInitialWeightedMCevents) numgen[7] = getNumInitialMCevents(7);
		}
		if (samps[i]==8) // TTWJets
		{                        
                        TString basedir_plus = "ttWkevin/";                                                                 // <-- to update
                        TString thesample = basedir + basedir_plus + "*.root";
			ch[8]->Add(thesample);
			xsecs[8]=0.6647;
                        numgen[8]=246521.0;
                        if (useNumInitialWeightedMCevents) numgen[8] = getNumInitialMCevents(8);
		}
		if (samps[i]==9) // TTZJets
		{
                        TString basedir_plus = "TTZJets_Tune4C_13TeV-madgraph-tauola/crab_ttZjets/150519_150516/0000/";     // <-- to update
                        TString thesample = basedir + basedir_plus + "*.root";
			ch[9]->Add(thesample);
                        xsecs[9]=0.8565;
                        numgen[9]=249275.0;
                        if (useNumInitialWeightedMCevents) numgen[9] = getNumInitialMCevents(9);
		}
		if (samps[i]==10) // diboson (WZ)
		{
                        TString basedir_plus = "WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola/crab_wzJets/150519_150616/0000/"; // <-- to update
                        TString thesample = basedir + basedir_plus + "*.root";
			ch[10]->Add(thesample);
                        xsecs[10]=2.165;
			numgen[10]=237484.0;
                        if (useNumInitialWeightedMCevents) numgen[10] = getNumInitialMCevents(10);
		}
                
                if (samps[i]==11) // diboson (ZZ)
		{
                        TString basedir_plus = "ZZTo4L_Tune4C_13TeV-powheg-pythia8/crab_zzJets/150519_150636/0000/";        // <-- to update
                        TString thesample = basedir + basedir_plus + "*.root";
			ch[11]->Add(thesample);
                        xsecs[11]=0.325;
                        numgen[11]=2514003.0102;
                        if (useNumInitialWeightedMCevents) numgen[11] = getNumInitialMCevents(11);
		}
                
                if (samps[i]==12) // (unused)
		{
                        cout << "This sample has not been specified. See load_samples function." << endl;
		}
                
		if (samps[i]==13) // dilepton ttbar
		{
			TString basedir_plus = "TTJets_split_2lep/";                                                        // <-- to update
			TString thesample = basedir + basedir_plus + "*.root";
			ch[13]->Add(thesample);
			xsecs[13]=85.656; // at 173.2 GeV (top group twiki). == 815.96 (xsec) * 0.104976 (BR)
			numgen[13]=25446993.0;
                        if (useNumInitialWeightedMCevents) numgen[13] = getNumInitialMCevents(13);
                }
                
                if (samps[i]==14) // ttbar: 1l from top
		{
			TString basedir_plus = "TTJets_split_1lepFromT/";                                                   // <-- to update
			TString thesample = basedir + basedir_plus + "*.root";
			ch[14]->Add(thesample);
			xsecs[14]=178.71; // at 173.2 GeV (top group twiki). == 815.96 (xsec) * 0.219024 (BR)
			numgen[14]=25446993.0;
                        if (useNumInitialWeightedMCevents) numgen[14] = getNumInitialMCevents(14);
                }
                
                if (samps[i]==15) // ttbar: 1l from anti-top
		{
			TString basedir_plus = "TTJets_split_1lepFromTBar/";                                                // <-- to update
			TString thesample = basedir + basedir_plus + "*.root";
			ch[15]->Add(thesample);
			xsecs[15]=178.71; // at 173.2 GeV (top group twiki). == 815.96 (xsec) * 0.219024 (BR)
			numgen[15]=25446993.0;
                        if (useNumInitialWeightedMCevents) numgen[15] = getNumInitialMCevents(15);
                }
                
                if (samps[i]>15) cout << "This sample has not been specified. See load_samples function." << endl;
                
	}
        
        cout << "Samples loaded." << endl;
}

double PlotHelper::getNumInitialMCevents (int sample)
{
    // Derived from https://root.cern.ch/doc/master/classTChain.html#a4d491db32262125e6cb77a8f7a6bfd93.
    //
    // If the "numInitialWeightedMCevents" histo is present in the root files, it is extremely preferable to
    // use this function to automatically retrieve the initial number of mc events (useful for calculating 
    // event yields). 
    // 
    
    double returnedEvents=0.;
    TH1D *sumHist = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);
    
    TObjArray *fileElements=ch[sample]->GetListOfFiles();
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
