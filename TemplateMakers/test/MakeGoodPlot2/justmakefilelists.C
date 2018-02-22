// usage: root -l justmakefilelists.C+
#include "includes.h" 

void justmakefilelists()
{
    for (int i=1; i<105; i++)
    {
        // This will print some warnings; you can ignore them.
        TString samp = loadsample(i);
        if (samp!="none") cout << "Wrote txt file for " << samp << endl;
    }
}