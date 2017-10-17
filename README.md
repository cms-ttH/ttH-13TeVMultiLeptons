#Notre Dame EFT multi-lepton framework (currently based on ttH framework)

The locations of the latest trees are [here](https://twiki.cern.ch/twiki/bin/view/CMS/NotreDameTrees).

## Installation

Setup CMSSW and clone repositories by running:        

	curl https://raw.githubusercontent.com/cms-ttH/ttH-13TeVMultiLeptons/EFT_code/setup.sh|sh -

NOTE: Due to concurrent `scram` usage, these may fail with errors. In this case, run  `scram b -j8` again. 
Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
	cmsRun osTwoLep_cfg.py

To view our custom object classes' TLorentzVectors in the TBrowser, add the following to your [rootlogon.C](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/rootlogon.C) file (assuming you've setup cmssw):
   	
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");

## Running limits

To create release for running lmits, use:

	curl https://raw.githubusercontent.com/cms-ttH/ttH-13TeVMultiLeptons/master/setup_limit.sh|sh-
        
If curious look inside setup_limit.sh to see what it is doing. Now, make the histograms for the datacard (note: for the EFT analysis this will not yet produce a meaningful result):
   	   
      cd TemplateMakers/test/
      cmsenv
      root -l makeStackPlotsFinalShape.C+
