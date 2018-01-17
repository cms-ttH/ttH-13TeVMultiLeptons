#include "wrapper.h"

void makegoodplot(bool plotsonly=true) // true: make plots from existing hists. false: remake hists before making plots.
{     
    // vector of samples to include in the plot:
    std::vector<int> samples; // <- example
    
//    samples.push_back(1); // ttH
    //samples.push_back(5); // ttJets inclusive
//    samples.push_back(8); // ttW
//    samples.push_back(9); // ttZ
//    samples.push_back(13); // ttJets dilep


    // different order
    
    // Single top
    samples.push_back(17);
    samples.push_back(18);
    samples.push_back(19);
    samples.push_back(20);
    samples.push_back(21);
    
    // Diboson
    samples.push_back(10);
    samples.push_back(11);
    samples.push_back(12);
    
    // V+Jets
    samples.push_back(16);
    samples.push_back(6);
    samples.push_back(7);
    
    
    // ttbar
    samples.push_back(13); // ttJets dilep
    samples.push_back(14); // ttJets single lep from t
    samples.push_back(15); // ttJets single lep from tbar
    
    // ttV/H
    samples.push_back(8); // ttW   
    samples.push_back(9); // ttZ    
    samples.push_back(1); // ttH  
    
    
    
    
    
    
    cout << "about to start"  << endl;
    
    // then, simply:
    wrapper(samples,plotsonly);
}
