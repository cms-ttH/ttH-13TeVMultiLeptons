//#include "proofofconcept.h"
#include "fixcols.h"
#include "lepeff_hists.h"
#include "jetcleaningstudies_hists.h"
#include "triggerstudies_hists.h"
#include "standard_hists.h"
#include "mc_validation_hists.h"

void HistMaker::doOneEvent()
{
    thisEventFit.clear();
    
    // simply (and only!) the functions that actually calculate / do physics stuff
    // just run the functions here.
    // functions only!!! the functions (probably) should be members of HistMaker
    // doesn't return anything; the hist map is also member of HistMaker!
    
    //proof_of_concept();
    fixcollections();
    standard_hists();
    
    //lepton_eff_studies();
    //trigger_studies();
    //jet_cleaning_studies();
    //mc_validation_hists(); 

}
