// usage: root -l justmakefilelists.C+
#include "includes.h" 

void justmakefilelists()
{
    for (int i=84; i<85; i++) // 1-105
    {
        // This will print some warnings; you can ignore them.
        TString samp = loadsample(i);
        if (samp!="none") cout << "Wrote txt file for " << samp << endl;
    }
}