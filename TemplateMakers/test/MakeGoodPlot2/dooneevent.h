//#include "proofofconcept.h"
#include "lepeff_hists.h"
#include "jetcleaningstudies_hists.h"

void PlotHelper::doOneEvent()
{
    // simply (and only!) the functions that actually calculate / do physics stuff
    // just run the functions here.
    // functions only!!! the functions (probably) should be members of PlotHelper
    // doesn't return anything; the hist map is also member of PlotHelper!
    
    //proof_of_concept();
    
    lepton_eff_studies();
    jet_cleaning_studies();
}
