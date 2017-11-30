#include "wrapper.h"

void makegoodplot()
{     
    // vector of samples to include in the plot:
    std::vector<int> samples; // <- example
    
//     samples.push_back(1); // ttH
//     samples.push_back(5); // ttJets
//     samples.push_back(8); // ttW
//     samples.push_back(9); // ttZ
    
//    samples.push_back(20); // data: MET 2017A
    samples.push_back(21); // data: MET 2017B
    samples.push_back(22); // data: MET 2017C
    samples.push_back(23); // data: MET 2017D
//    samples.push_back(24); // data: MET 2017E
    samples.push_back(25); // data: MET 2017F
    
    cout << "about to start"  << endl;
    
    // then, simply:
    
    bool plotsonly = false;      // true: make plots from existing hists. false: remake hists before making plots.
    wrapper(samples,plotsonly);
    
}
