//#include "nicepalette.h"
#include "wrapper.h" /// yes

void makegoodplot()
{
    
//    set_plot_style(); // yes, but could get rid of / add to class
  
    // vector of samples to include in the plot:
    std::vector<int> samples; // <- example
    
    samples.push_back(1); // ttH
    
    // list/def. samples .. however you want to do it (int, string, enum ...)
    // each one can have it's own line/fill color + existing stuff
    
    cout << "about to start"  << endl;
    
    // then, simply:
    wrapper(samples);
    
}
