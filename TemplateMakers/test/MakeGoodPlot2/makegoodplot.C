#include "wrapper.h"

void makegoodplot(bool plotsonly=true) // true: make plots from existing hists. false: remake hists before making plots.
{     
    // vector of samples to include in the plot:
    std::vector<int> samples; // <- example
    
    samples.push_back(1); // ttH
    //samples.push_back(5); // ttJets inclusive
    samples.push_back(8); // ttW
    samples.push_back(9); // ttZ
    samples.push_back(13); // ttJets dilep
    samples.push_back(14); // ttJets single lep from t
    samples.push_back(15); // ttJets single lep from tbar
    
    cout << "about to start"  << endl;
    
    // then, simply:
    wrapper(samples,plotsonly);
}
