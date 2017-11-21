void loadsample(const int samp, TChain &ch)
{
	       
    TString basedir = "/store/ndpc5disk1/gesmith/crab/ttH_test_1_11_17/";     // The directory on ndpc disk where your samples are located.
    //bool useNumInitialWeightedMCevents = true;                  // Set to false if for some reason this histo is not present in the trees (event yields will not be correct).

                
    if (samp==0) // data
    {
            cout << "This sample has not been specified. See load_samples function." << endl;

    }
    if (samp==1) // ttH
    {                        
            //TString basedir_plus = "ttHToNonbb_M125_ttHtranche3_powheg_Moriond17/";     // subdirectory for this sample
            //TString basedir_plus = "ttH125/";
            TString basedir_plus = "";
            TString thesample = basedir + basedir_plus + "*.root";
            ch.Add(thesample);
//             xsecs=0.5085;                                                            // cross section for this process (needs to be set manually).
// 	    numgen=2600389.15887;                                                    // placeholder (deprecated)
//             if (useNumInitialWeightedMCevents) numgen = getNumInitialMCevents(1);    // use this instead to get numgen
    }
}
