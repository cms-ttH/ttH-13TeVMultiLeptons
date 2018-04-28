#include "includes.h"

void wrapper_lobster(TString sample, TString input_filenames)
{
    // input_filenames -> just "files.txt" provided by lobster. open and read files, add to chain as doing already below.

    bool debug=false;
    
    if (debug) cout << " " << endl;
    if (debug) cout << "At the top of wrapper function" << endl;    
    
    //////////////////////////////////////////////////
    // Set up tree reader    
    
    TChain *ch = new TChain("OSTwoLepAna/summaryTree");
    ch->SetCacheSize(200000000);             // 100000000
    ch->SetCacheLearnEntries(100);

    if (debug) cout << "Doing sample " << sample << endl;            

    TFileCollection fc("dum","",input_filenames);
    int numfiles = fc.GetNFiles();
    if (debug) cout << "About to run over " << numfiles << " files" << endl;
                
    ch->AddFileInfoList(fc.GetList());
    if (debug) cout << ch->GetEntries() << endl;
    TTreeReader reader(ch);

    //////////////////////////////////////////////////
    // Fill histograms
    
    HistMaker *histmaker = new HistMaker(sample); // <---------- update me
    histmaker->setBranchAddresses(reader);
    histmaker->bookHistos();
    histmaker->run(reader); // contains the while loop
    histmaker->collectResults();
    auto sumObjArray = histmaker->objArray;
    if (debug) cout << "Done with HistMaker" << endl;
    
    //////////////////////////////////////////////////
    // Dump histos to file
    
    double numgen = 1.;            
    numgen = getNumInitialMCevents(0,*ch); // use this to get numgen (To do -> should really remove the first arg as it's just a dummy int now)
    if (debug) cout << "Ran getNumInitialMCevents" << endl;

    //TFile tempfile("temp_"+int2ss(sample)+"_"+int2ss(i)+".root","RECREATE");
    TFile tempfile("output.root","RECREATE"); // the naming of this should now be handled by lobster
    sumObjArray->Write();
    if (debug) cout << "Hists dumped to file" << endl;           
    TH1D *scalehist = new TH1D("NumInitialWeightedMCevents","NumInitialWeightedMCevents",1,1,2);                    
    scalehist->SetBinContent(1,numgen);
    scalehist->Write();
    if (debug) cout << "Wrote NumInitialWeightedMCevents" << endl;
    tempfile.Close();
                

    //////////////////////////////////////////////////
    
    // garbage collection (if it becomes necessary):
//     delete scalehist;
//     delete sumObjArray;
//     delete histmaker;
//     // reader.SetTree(0); // ?
//     delete ch; // might have to do something with reader first..

}