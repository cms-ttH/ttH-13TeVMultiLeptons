#include "includes.h"

void wrapper_lobster(TString sample, TString input_filenames, bool doQFs=false, bool dofakes=false)
{
    // input_filenames -> just "files.txt" provided by lobster. open and read files, add to chain as doing already below.

    bool debug = false;
    
    if (debug) cout << " " << endl;
    if (debug) cout << "At the top of wrapper function" << endl;    
    
    //////////////////////////////////////////////////
    // Set up tree reader    
    
    TChain *ch = new TChain("OSTwoLepAna/summaryTree");
    //ch->SetCacheSize(200000000);             // 100000000 // 200000000
    ch->SetCacheLearnEntries(100);

    if (debug) cout << "Doing sample " << sample << endl;            

    TFileCollection fc("dum","",input_filenames);
    int numfiles = fc.GetNFiles();
    if (debug) cout << "About to run over " << numfiles << " files" << endl;
                
    ch->AddFileInfoList(fc.GetList());
    //if (debug) cout << ch->GetEntries() << endl;

    
    //bool split = (sample_TString2int(sample)>=84 && sample_TString2int(sample)<=88) ? true : false;
    bool split = false;
    
    if (!split)
    {
        TTreeReader reader(ch);
        // Fill histograms
        if (debug) cout << "Before Histmaker" << endl;
        unique_ptr<HistMaker> histmaker(new HistMaker(sample,doQFs,dofakes));
        if (debug) cout << "Before setBranchAddresses" << endl;
        histmaker->setBranchAddresses(reader);
        if (debug) cout << "Before bookHistos" << endl;
        histmaker->bookHistos();
        if (debug) cout << "Before run" << endl;
        histmaker->run(reader); // contains the while loop
        if (debug) cout << "Before collectResults" << endl;
        histmaker->collectResults();
        auto sumObjArray = histmaker->objArray;
        if (debug) cout << "Done with HistMaker" << endl;
    
        //////////////////////////////////////////////////
        // Dump histos to file
    
        double numgen = 1.;            
        numgen = getNumInitialMCevents(0,*ch); // use this to get numgen (To do -> should really remove the first arg as it's just a dummy int now)
        if (debug) cout << "Ran getNumInitialMCevents" << endl;
    
        //TString supl="_Nom";
        //if (doQFs) supl="_ChargeFlips";
        //if (dofakes) supl="_Fakes";
    
        //TFile tempfile("temp_"+int2ss(sample)+"_"+int2ss(i)+".root","RECREATE");
        TFile tempfile("output.root","RECREATE"); // the naming of this should now be handled by lobster
        sumObjArray->Write();
        if (debug) cout << "Hists dumped to file" << endl;           
        TH1D *scalehist = new TH1D("NumInitialWeightedMCevents","NumInitialWeightedMCevents",1,1,2);                    
        scalehist->SetBinContent(1,numgen);
        scalehist->Write();
        if (debug) cout << "Wrote NumInitialWeightedMCevents" << endl;
        tempfile.Close();
    }    
    else
    {
        int entries = ch->GetEntries();
        //int entries = 2000;
        int eventsperloop = 5000; // adjust as needed
        int maxloops = ceil((double)entries/(double)eventsperloop);
        //////////////////////////////////////////////////
        
        for (int i=0; i<maxloops; i++)
        {
            int firstevent = i*eventsperloop;
            int lastevent = min(entries,firstevent+eventsperloop);
            // Fill histograms
            if (debug) cout << "Before Histmaker" << endl;
            TTreeReader reader(ch);
            //HistMaker *histmaker = new HistMaker(sample,doQFs,dofakes);
            unique_ptr<HistMaker> histmaker(new HistMaker(sample,doQFs,dofakes));
            if (debug) cout << "Before setBranchAddresses" << endl;
            histmaker->setBranchAddresses(reader);
            if (debug) cout << "Before bookHistos" << endl;
            histmaker->bookHistos();
            if (debug) cout << "Before run" << endl;
            histmaker->run(reader,firstevent,lastevent); // actually only goes to lastevent-1
            if (debug) cout << "Before collectResults" << endl;
            histmaker->collectResults();
            auto sumObjArray = histmaker->objArray;
            if (debug) cout << "Done with HistMaker" << endl;
    
            //////////////////////////////////////////////////
            // Dump histos to file
    
            TFile tempfile("output_temp"+int2ss(i)+".root","RECREATE"); // the naming of this should now be handled by lobster
            sumObjArray->Write();
            if (debug) cout << "Hists dumped to file" << endl;           
            tempfile.Close();
            //delete sumObjArray;
            //delete histmaker;
            //system("hadd -a -k output.root output_temp.root");
        }
        
        system("hadd output.root output_temp*.root");
        double numgen = 1.;            
        numgen = getNumInitialMCevents(0,*ch); // use this to get numgen (To do -> should really remove the first arg as it's just a dummy int now)
        if (debug) cout << "Ran getNumInitialMCevents" << endl;
        TFile tempfile("output.root","UPDATE");
        TH1D *scalehist = new TH1D("NumInitialWeightedMCevents","NumInitialWeightedMCevents",1,1,2);                    
        scalehist->SetBinContent(1,numgen);
        scalehist->Write();
        if (debug) cout << "Wrote NumInitialWeightedMCevents" << endl;
        tempfile.Close();
        TRandom3 rand;
        rand.SetSeed(0);
        int secs = ceil(45.*60.*rand.Rndm());
        system("sleep "+int2ss(secs)); // spread out transfers to solve issue with deepthought server overloading
    }

    //////////////////////////////////////////////////
    
    // garbage collection (if it becomes necessary):
//     delete scalehist;
//     delete sumObjArray;
//     delete histmaker;
//     // reader.SetTree(0); // ?
//     delete ch; // might have to do something with reader first..
//
//     feb 2019: it did become necessary. See Histmaker dtor.

}