#include "wrapper.h"

void makegoodplot()
{     
    // vector of samples to include in the plot:
    std::vector<int> samples; // <- example
    
    samples.push_back(1); // ttH
    samples.push_back(5); // ttJets
    samples.push_back(8); // ttW
    samples.push_back(9); // ttZ
    
    cout << "about to start"  << endl;
    
    // then, simply:
    
    bool plotsonly = true;      // true: make plots from existing hists. false: remake hists before making plots.
    wrapper(samples,plotsonly);
    
}
