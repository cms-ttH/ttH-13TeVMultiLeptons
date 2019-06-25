# Notre Dame EFT multi-lepton framework (currently based on ttH framework)

The locations of the latest trees are [here](https://twiki.cern.ch/twiki/bin/view/CMS/NotreDameTrees).

## Installation

Setup CMSSW and clone repositories by running:        

	curl https://raw.githubusercontent.com/cms-ttH/ttH-13TeVMultiLeptons/EFT_code/setup.sh|sh -

You will then need to manually do the following:
    
    mkdir /tmp/$USER
    cmsrel /tmp/$USER/CMSSW_9_4_9
    cd CMSSW_9_4_9/src 
    cmsenv 
    git cms-merge-topic lathomas:L1Prefiring_9_4_9
    cd -
    cp -r /tmp/$USER/CMSSW_9_4_9/src/* .
    cmsenv
    scram b -j8

NOTE: Due to concurrent `scram` usage, these may fail with errors. In this case, run `scram b -j8` again. 
NOTE: If setup.sh is ever updated to CMSSW_9_4_13 or higher, the L1Prefiring-specific instructions above can be omitted.
Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
	cmsRun osTwoLep_cfg.py

To view our custom object classes' TLorentzVectors in the TBrowser, add the following to your [rootlogon.C](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/rootlogon.C) file (assuming you've setup cmssw):
   	
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");
