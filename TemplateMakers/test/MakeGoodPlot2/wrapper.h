// Stuff used everywhere
#include "includes.h"
#include "utils.h"

// Stuff used by PlotHelper
#include "loadsample.h"
#include "PlotHelper.h"
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
    Int_t njobs = 8;                        
    ROOT::TTreeProcessorMP workers(njobs);   
           

    auto workItem = [](TTreeReader & reader)    // c++ lambda
    {      
        //TTree *dummy = reader.GetTree();
        //cout << dummy->GetCurrentFile()->GetName() << endl;
        //instantiate class here!
        PlotHelper *plothelper = new PlotHelper();
        plothelper->setBranchAddresses(reader);
        plothelper->bookHistos();
        plothelper->run(reader); // contains the while loop
        plothelper->collectResults();
        return plothelper->objArray;
    };

    
    std::vector<TObjArray> objarray_vect;
    
    if (!plotsonly)
    {    
        for (const auto sample : samples)
        {
            TChain ch("OSTwoLepAna/summaryTree");
            ch.SetCacheSize(200000000);             // 100000000
            ch.SetCacheLearnEntries(100);            // 20
            double scale = loadsample(sample,ch);
            cout << ch.GetEntries() << endl;        
            auto sumObjArray = workers.Process(ch, workItem, "OSTwoLepAna/summaryTree");
            objarray_vect.push_back(*sumObjArray);        

            //// If you want to dump the hists to a file:
            TFile tempfile("temp_"+int2ss(sample)+".root","RECREATE");
            sumObjArray->Write();
            TH1D *scalehist = new TH1D("NumInitialWeightedMCevents","NumInitialWeightedMCevents",1,1,2);
            scalehist->SetBinContent(1,scale);
            scalehist->Write();
            tempfile.Close();
        }    
    }
    
    //// This is how you access the hists from objarray_vect:
    //auto trytogethist = (TH1D*)objarray_vect[0].FindObject("lepMVA sig1 barrel");    
    //trytogethist->Draw();
    
    
    /////////////// drawing half ////////////////
    cout << "ehere" << endl;

    // do something with the hists (draw 'em, etc.)
    //MakeGoodPlot *newplot = new MakeGoodPlot(samples,objarray_vect);

    // or different constructor to load hists from file..
    MakeGoodPlot *newplot = new MakeGoodPlot(samples);

    // then, pick one of these:
    //newplot->drawAllToScreen();
    //newplot->drawAllToFile("plttest","pdf");
    newplot->drawAllToWebArea("EFTcategory_njets_nbjets_geq0__log__and_nbjet_vs_njet_2D_plots_trying_to_add_all_cuts__default_cut_on_jets_bjets","png");
    
}
