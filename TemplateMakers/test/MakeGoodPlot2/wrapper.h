// Stuff used everywhere
#include "includes.h"
#include "utils.h"

// Stuff used by HistMaker
#include "loadsample.h"
#include "HistMaker.h"
#include "bookhistos.h"
#include "setbranchaddresses.h"
#include "lep_selection.h"
#include "dooneevent.h"
#include "run.h"
#include "collectresults.h"
#include "eventselection2.h"

// Stuff used by MakeGoodPlot
#include "MakeGoodPlot.h"
#include "nicepalette.h"
#include "rateinfo.h"
#include "setup.h"
#include "GoodPlot.h"
#include "getroccurve.h"
#include "drawall.h"

void wrapper(std::vector<int> samples, bool plotsonly=true) // (int/string/whatever samples) ...
{
      
    /////////////// histo making half /////////////
    
    // See https://root.cern.ch/doc/v608/mp102__readNtuplesFillHistosAndFit_8C.html
    Int_t njobs = 12;   // The ndpcs have 8 cores x 2 threads/core = max ~16 threads/machine.
                        // Remains to be seen what is the optimal number of threads (using
                        // a guess of 12 for now).
    
    ROOT::TTreeProcessorMP workers(njobs);              

    auto workItem = [](TTreeReader & reader)    // c++ lambda
    {      
        //instantiate class here!
        HistMaker *histmaker = new HistMaker();
        histmaker->setBranchAddresses(reader);
        histmaker->bookHistos();
        histmaker->run(reader); // contains the while loop
        histmaker->collectResults();
        return histmaker->objArray;
    };

    
    if (!plotsonly)
    {    
        for (const auto sample : samples)
        {
            TChain ch("OSTwoLepAna/summaryTree");
            ch.SetCacheSize(200000000);             // 100000000
            ch.SetCacheLearnEntries(100);            // 20
            double scale = loadsample(sample,ch);
            cout << "Doing sample " << sample << ", " << ch.GetEntries() << " events." << endl;
            
            // This actually runs the hist maker and grabs the output in the form of a TObjArray:
            auto sumObjArray = workers.Process(ch, workItem, "OSTwoLepAna/summaryTree");                    

            //// Dump the hists to a file:
            TFile tempfile("temp_"+int2ss(sample)+".root","RECREATE");
            sumObjArray->Write();
            TH1D *scalehist = new TH1D("NumInitialWeightedMCevents","NumInitialWeightedMCevents",1,1,2);
            scalehist->SetBinContent(1,scale);
            scalehist->Write();
            tempfile.Close();
        }    
    }
    
    //// This is an example of how you access the hists from objarray_vect:
    //auto trytogethist = (TH1D*)objarray_vect[0].FindObject("lepMVA sig1 barrel");    
    //trytogethist->Draw();
    
    
    /////////////// drawing half ////////////////

    // Now do something with the hists (draw 'em, etc.)

    // This loads the hists from file and prepares to make the plots:
    MakeGoodPlot *newplots = new MakeGoodPlot(samples);

    // Then, picking one of these will run the "drawall" function (see drawall.h), and save resulting plots to
    // file/web area, or plot directly to screen (in x-windows):
    
    //newplots->drawAllToScreen();
    //newplots->drawAllToFile("plttest","pdf");
    newplots->drawAllToWebArea("jetclean_scalar_momentum_subtraction_not_norm__tryingsomething","png");
    
}
