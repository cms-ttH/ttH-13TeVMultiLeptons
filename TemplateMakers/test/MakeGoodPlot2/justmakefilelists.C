// usage: root -l justmakefilelists.C+
#include "includes.h" 

void justmakefilelists()
{
    vector<int> sv = 
    {
        84
    };
    
    //for (int i=84; i<89; i++) // 1-105
    for (auto i : sv)
    {
        // This will print some warnings; you can ignore them.
        TString samp = loadsample(i);
        if (samp!="none") cout << "Wrote txt file for " << samp << endl;
    }
}