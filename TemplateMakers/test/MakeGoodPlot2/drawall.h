#include "lepeff_plots.h" // include whatever plots you want here (can be multiple functions)
#include "jetcleaningstudies_plots.h"
#include "triggerstudies_plots.h"
#include "standard_plots.h"
#include "standard_plots_normalized.h"
#include "mc_validation_plots.h"
#include "save_analysis_hists.h"
#include "th1eft_dist_test_plots.h"
#include "fr_studies_plots.h"
#include "pdf_studies_plots.h"
#include "syst_sanity_check.h"
#include "derive_njet_sfs.h"

void MakeGoodPlot::drawAll()
{
    // Functions only!! Can be more than one!!
    // whatever plots you want to make, actually
    // run the code that draws them here:
    
    //lepeff_plots();
    //jetcleaning_plots();
    //triggerstudies_plots();
    standard_plots();
    //standard_plots_normalized();
    //mc_validation_plots();
    //save_analysis_hists();
    //th1eft_test_plots();
    //fr_studies_plots();
    //pdf_studies_plots();
    //syst_sanity_check();   
    //derive_njet_sfs();
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
            // //auto tmpcan = (TCanvas*)canvas[i];
            //auto tmpcan = (TH1*)canvas[i];
            //theplotfile->WriteTObject(tmpcan);
            theplotfile->WriteTObject(canvas[i]);
        }
        
        theplotfile->Close();
    }
    
    else if (plotoption=="png" || plotoption=="pdf" || plotoption==".png" || plotoption==".pdf" )
    {        
        
        ofstream htmlfile;
        string plotsfile = plotfile+"plots.html";
        htmlfile.open(plotsfile);
        
        for (int i=0; i<canvas.GetEntries(); i++)
        {
            auto tmpcan = (TCanvas*)canvas[i];
            TString plotfilename = plotfile+"output_"+tmpcan->GetName()+plotoption;
            tmpcan->SaveAs(plotfilename);
            plotfilename = "output_";
            plotfilename = plotfilename+tmpcan->GetName()+plotoption;
            TString htmlvoodoo = "<div class=\"pic photo-link smoothbox\" id=\""+plotfilename+"\"><a href=\""+plotfilename+"\" rel=\"gallery\"><img src=\""+plotfilename+"\" class=\"pic\"/></a><div class=\"desc\">"+tmpcan->GetName()+"</div></div>";
            htmlfile << htmlvoodoo << "\n";
        }
        
        htmlfile.close();
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
    
    plotfile = "/afs/crc.nd.edu/user/g/gsmith15/www/"+plotfile; // the "~" doesn't seem to work with ofstream files
    
    string syscmd = "mkdir "+plotfile;
    system(syscmd.c_str());
    
    syscmd = "cp index.html "+plotfile+"/.";
    system(syscmd.c_str());
         
    //plotfile = plotfile+"/images";
    //syscmd = "mkdir "+plotfile;
    //system(syscmd.c_str());
    
    //plotfile = plotfile+"/output";
    plotfile = plotfile+"/";
    drawAllToFile(plotfile,plotoption);
    
}
