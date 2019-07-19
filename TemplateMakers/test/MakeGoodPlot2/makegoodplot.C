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
    
    // data-driven backgrounds
      samples.push_back(94); // QFs
      samples.push_back(95); // Fakes
     
     // Single top
     //samples.push_back(17); // tW chan
     //samples.push_back(18); // tW chan
     //samples.push_back(19);
     //samples.push_back(20);
     //samples.push_back(21);
      
     //// Diboson
     samples.push_back(10);     
     samples.push_back(11);
     samples.push_back(12);
     
     //// Triboson
     samples.push_back(22);
     samples.push_back(23);
     samples.push_back(24);    
     samples.push_back(25);
 // //     
 // // //     // V+Jets
// // // //     samples.push_back(16);
// // // //     samples.push_back(6);
// // // //     samples.push_back(7);
// // // //     
// // // //     // ttbar
// // // //    samples.push_back(5);   // ttJets inclusive
// // //     //samples.push_back(13); // ttJets dilep
// // //     //samples.push_back(14); // ttJets single lep from t
// // //     //samples.push_back(15); // ttJets single lep from tbar
// // //     
// // //     // convs
     samples.push_back(30);

    
    //sigs
   //samples.push_back(8); // ttW   
   //samples.push_back(9); // ttZ    
   //samples.push_back(1); // ttH  
   //samples.push_back(26); // tZq
   //samples.push_back(31); // tHq
    
    //samples.push_back(27);
    //samples.push_back(28);
    //samples.push_back(29);
    
    
    ////EFT samples
    ////ttH_EFT
    ////samples.push_back(40);
//     samples.push_back(41);
//     samples.push_back(42);
//     samples.push_back(43);
//     samples.push_back(44);
//     samples.push_back(45);
//     samples.push_back(46);      // ctG (ttH)
//     samples.push_back(47);
//     samples.push_back(48);
//     samples.push_back(49);
//     samples.push_back(50);
//     ////tllq_EFT
//     //samples.push_back(51);
//     samples.push_back(52);
//     samples.push_back(53);
//     samples.push_back(54);
//     samples.push_back(55);
//     samples.push_back(56);
//     samples.push_back(57);      // ctG tllq
//     samples.push_back(58);
//     samples.push_back(59);
//     samples.push_back(60);
//     samples.push_back(61);
//     ////ttll_EFT
//     ////samples.push_back(62);
//     samples.push_back(63);
//     samples.push_back(64);
//     samples.push_back(65);
//     samples.push_back(66);
//     samples.push_back(67);
//     samples.push_back(68);      // ctG ttll
//     samples.push_back(69);
//     samples.push_back(70);
//     samples.push_back(71);
//     samples.push_back(72);
//     ////ttlnu_EFT
//     ////samples.push_back(73);
//     samples.push_back(74);
//     samples.push_back(75);
//     samples.push_back(76);
//     samples.push_back(77);
//     samples.push_back(78);
//     samples.push_back(79);      // ctG ttlnu
//     samples.push_back(80);
//     samples.push_back(81);
//     samples.push_back(82);
//     samples.push_back(83);


    //// samples.push_back(84); // ttH_multidim
    
    samples.push_back(85); // ttlnu_multidim
    samples.push_back(86); // ttll_multidim
    samples.push_back(84); // ttH_multidim
    samples.push_back(87); // tllq_multidim
    samples.push_back(88); // tHq_multidim

//     samples.push_back(8); // ttW   
//     samples.push_back(9); // ttZ    
//     samples.push_back(1); // ttH  
//     samples.push_back(26); // tZq
//    samples.push_back(31); // tHq
    
    //data samples
     samples.push_back(100); // single mu data
     samples.push_back(101); // single ele data
     samples.push_back(102); // double mu data
     samples.push_back(103); // double ele data
     samples.push_back(104); // mu+EG data

//    samples.push_back(105); // MET data for trigger studies
    



 
    //samples.push_back(0); // additional one-off sample





// --------------------------------------------------------------------------
    
    cout << "About to start (inside makegoodplot.C)"  << endl;
    
    // then, simply:
    wrapper(samples,mode);
}
