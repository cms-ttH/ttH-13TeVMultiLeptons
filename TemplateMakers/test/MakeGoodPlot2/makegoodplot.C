#include "wrapper.h"

void makegoodplot(int mode=2)   
{                               
    // mode=1: (re)make hists only
    // mode=2: (re)make plots only
    // mode=3: (re)make hists+plots
    //
    // The main use case for this is mode 2. In general, you should try not to use 
    // modes 1 or 3; instead use lobster or other batch option. For more info, 
    // see eft_makegoodplot2_tutorial.pdf.
    //

   
    // vector of samples to include in the plot:
    std::vector<int> samples;
    
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
    
    // Triboson
    samples.push_back(22);
    samples.push_back(23);
    samples.push_back(24);    
    samples.push_back(25);
    
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
    
    // new sigs
//     samples.push_back(26);
//     samples.push_back(27);
//     samples.push_back(28);
//     samples.push_back(29);
//     
// 
//     
//     // new data samples
//     samples.push_back(100); // single mu data
//     samples.push_back(101); // single ele data
//     samples.push_back(102); // double mu data
//     samples.push_back(103); // double ele data
//     samples.push_back(104); // mu+EG data
    
//    samples.push_back(0); // additional one-off sample
    
    cout << "About to start (inside makegoodplot.C)"  << endl;
    
    // then, simply:
    wrapper(samples,mode);
}
