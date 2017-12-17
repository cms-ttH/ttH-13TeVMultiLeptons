#include "lepeff_plots.h" // include whatever plots you want here (can be multiple functions)
#include "jetcleaningstudies_plots.h"
#include "standard_plots.h"

void MakeGoodPlot::drawAll()
{
    // Functions only!! Can be more than one!!
    // whatever plots you want to make, actually
    // run the code that draws them here:
    
    //lepeff_plots();
    jetcleaning_plots();
    //standard_plots();


}



////// various helpers for saving the plots /////////

void MakeGoodPlot::drawAllToFile(string plotfile, string plotoption)
{
    gROOT->SetBatch(kTRUE);
    drawAll();
    
    if (plotoption=="root")
    {
        string plotfilename = plotfile+".root";
        TFile *theplotfile = new TFile(plotfilename.c_str(),"RECREATE");
        
        for (int i=0; i<canvas.GetEntries(); i++)
        {
            auto tmpcan = (TCanvas*)canvas[i];
            theplotfile->WriteTObject(tmpcan);
        }
    }
    
    else if (plotoption=="png" || plotoption=="pdf")
    {        
        for (int i=0; i<canvas.GetEntries(); i++)
        {
            auto tmpcan = (TCanvas*)canvas[i];
            TString plotfilename = plotfile+"_"+tmpcan->GetName()+"."+plotoption;
            tmpcan->SaveAs(plotfilename);
        }
    }    
    
    else cout << "Invalid option for saving plots. Choose from png, pdf or root" << endl;
    
}

void MakeGoodPlot::drawAllToWebArea(string plotfile, string plotoption)
{
    cout << "here2" << endl;
    if (plotoption=="root")
    {
        cout << "You're trying to write many root files to your web area;" << endl;
        cout << "this is not going to end well. Try a different file " << endl;
        cout << "format, or use drawAllToFile directly instead. Exiting." << endl;
        
        return;
    }
    
    plotfile = "~/www/"+plotfile;
    
    string syscmd = "mkdir "+plotfile;
    system(syscmd.c_str());
    
    syscmd = "cp index.php "+plotfile+"/.";
    system(syscmd.c_str());
    
    plotfile = plotfile+"/images";
    syscmd = "mkdir "+plotfile;
    system(syscmd.c_str());
    
    plotfile = plotfile+"/output";
    drawAllToFile(plotfile,plotoption);
    
}
