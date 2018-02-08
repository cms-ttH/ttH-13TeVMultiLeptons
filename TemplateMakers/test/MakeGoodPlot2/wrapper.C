#include "wrapper.h"

void wrapper(int sample, int mode=2)
{
    // For use with batch script.
    // If running interactive jobs then use
    // makegoodplot.C instead.
    
    std::vector<int> dummyvect;
    dummyvect.push_back(sample);
    wrapper(dummyvect, mode);
}