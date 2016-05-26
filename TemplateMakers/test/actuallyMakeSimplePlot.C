#include "variables.h"
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include "TString.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include <cmath>
#include <array>

#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"


void actuallyMakeSimplePlot(TString inputfiles="input.root")
{
    ///////////////////////////////////////////////////////////////////////////
    // Script to make simple plots from trees. 
    // See Templatemakers/interface/objectClasses.h for available options.
    // Usage:
    // root actuallyMakeSimplePlot.C+'("/path/to/treefiles*.root")'
    // 


    TChain *tree = new TChain("OSTwoLepAna/summaryTree");
    tree->Add(inputfiles);
    int entries = tree->GetEntries();

    // specify max num events to process (-1 = all events):
    int numevents = -1;

    cout << " " << endl;
    cout <<  "tree has " << entries << " entries." << endl;
    cout <<  "processing " << numevents << " of those." << endl;

    // initialize the histogram:
    TH1D *hist1 = new TH1D("hist1","hist1",50,0,400);


    vector<ttH::Lepton> *preselected_leptons_intree;
    preselected_leptons_intree=0;
    tree->SetBranchAddress("preselected_leptons",&preselected_leptons_intree);

    ///////////////////////////////////////////////////////////////////////////
    // loop over events:

    for (int i=0; i<entries; i++)
    {

        // end the loop after numevents:
        if ((numevents>=0) && (i>numevents)) break;

        tree->GetEntry(i);

        // if there is at least one lepton, fill histogram with the pt of the highest-pt preselected lepton:
        if ((*preselected_leptons_intree).size())
        {
            hist1->Fill((*preselected_leptons_intree)[0].obj.Pt());
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    

    //Draw the histogram:		
    hist1->Draw();
}
