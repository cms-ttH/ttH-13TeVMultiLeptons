#Notre Dame ttH multi-lepton framework

Analysis code for ttH H-->WW,ZZ,tautau-->2 or more leptons


## Installation

Setup CMSSW and clone repositories by running:        

	curl https://raw.githubusercontent.com/cms-ttH/ttH-13TeVMultiLeptons/master/setup.sh|sh -

To create release for running lmits, use:

	curl https://raw.githubusercontent.com/cms-ttH/ttH-13TeVMultiLeptons/master/setup_limit.sh|sh-

NOTE: Due to concurrent `scram` usage, these may fail with errors. In this case, run  `scram b -j32` again. 
Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
	cmsRun osTwoLep_cfg.py

To view the tth-specific classes' TLorentzVectors in the TBrowser, add the following to your [rootlogon.C](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/rootlogon.C) file (assuming you've setup cmssw):
   	
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");

## Running limits

If curious look inside setup_limit.sh to see what it is doing. Now, make the histograms for the datacard:
   	   
      cd TemplateMakers/test/
      cmsenv
      root -l makeStackPlotsFinalShape.C+

## Running the full chain

### See [Here](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/GENERAL.md)

## 8 TeV reference twiki

### See [Here](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) 
