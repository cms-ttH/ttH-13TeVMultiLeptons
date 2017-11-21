// Stuff used everywhere
#include "includes.h"
#include "utils.h"

// Stuff used by PlotHelper
#include "loadsample.h"
#include "PlotHelper.h"
#include "bookhistos.h"
#include "setbranchaddresses.h"
#include "dooneevent.h"
#include "run.h"
#include "collectresults.h"

// Stuff used by MakeGoodPlot
#include "MakeGoodPlot.h"
#include "nicepalette.h"
#include "setup.h"
#include "getroccurve.h"
#include "drawall.h"

void wrapper(std::vector<int> samples) // (int/string/whatever samples) ...
{
    // to do: split this function in 2 parts...
    
    
    /////////////// histo making half /////////////
    
    // put the lambda in here
    // most stuff should be done here
    
    // idea: change so that MakeGoodPlot handles all the plotting, PlotHelper handles the
    // hist making!! -> in prog.
    
    
    Int_t njobs = 8;                        // the whole reason we're doing this. (16 ? .. )
    ROOT::TTreeProcessorMP workers(njobs);  // https://root.cern.ch/doc/v608/mp102__readNtuplesFillHistosAndFit_8C.html 
           

    auto workItem = [](TTreeReader & reader)    // c++ lambda
    {      
        //instantiate class here!
        PlotHelper *plothelper = new PlotHelper();
        plothelper->setBranchAddresses(reader);
        plothelper->bookHistos();
        plothelper->run(reader); // contains the while loop
        plothelper->collectResults();
        return plothelper->objArray;
    };

    
    std::vector<TObjArray> objarray_vect;
    
//     for (const auto sample : samples)
//     {
//         TChain ch("OSTwoLepAna/summaryTree");
//         ch.SetCacheSize(100000000);
//         ch.SetCacheLearnEntries(20);
//         loadsample(sample,ch);
//         cout << ch.GetEntries() << endl;        
//         auto sumObjArray = workers.Process(ch, workItem, "OSTwoLepAna/summaryTree");
//         objarray_vect.push_back(*sumObjArray);        
//         
//         //// If you want to dump the hists to a file:
//         TFile tempfile("temp_"+int2ss(sample)+".root","RECREATE");
//         sumObjArray->Write();
//         tempfile.Close();
//     }
    
    //// This is how you access the hists from objarray_vect:
    //auto trytogethist = (TH1D*)objarray_vect[0].FindObject("lepMVA sig1 barrel");    
    //trytogethist->Draw();
    
    
    
    
    /////////////// drawing half ////////////////
    
//     // do something with the hists (draw 'em, etc.):
    //MakeGoodPlot *newplot = new MakeGoodPlot(samples,objarray_vect);
//     //or different constructor to load hists from file..
    MakeGoodPlot *newplot = new MakeGoodPlot(samples);
//    newplot->lepeff_plots(); //test
//     
//     // then, for example:
//    newplot->drawAllToScreen();
    //newplot->drawAllToFile("plttest","pdf");
    newplot->drawAllToWebArea("plttest","png");

//     // overloaded could have drawSinglePlot, etc.
    
}
