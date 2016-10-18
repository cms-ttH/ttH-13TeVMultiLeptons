#Notre Dame ttH multi-lepton framework

Analysis code for ttH H-->WW,ZZ,tautau-->2 or more leptons

The locations of the latest trees are [here](https://twiki.cern.ch/twiki/bin/view/CMS/NotreDameTrees).

## Installation

To get started tree-making from miniAOD (on an SL6 machine) do:        
        
        cmsrel CMSSW_8_0_14
        cd CMSSW_8_0_14/src
        cmsenv        
        git cms-init
        git clone git@github.com:cms-ttH/MiniAOD.git
        git clone git@github.com:cms-ttH/ttH-LeptonID.git ttH/LeptonID
        git clone git@github.com:cms-ttH/ttH-13TeVMultiLeptons.git

For now, CMSSW_8_0_13 (and later) seems to be broken so check out an additional package and edit the following:

	git cms-addpkg CommonTools/Utils
	emacs CommonTools/Utils/interface/normalizedPhi.h

Replace:

	#include "DataFormats/Math/include/normalizedPhi.h"

With:

	#include "DataFormats/Math/interface/normalizedPhi.h"

And compile:

        scram b -j 8

Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
	cmsRun osTwoLep_cfg.py

To view the tth-specific classes' TLorentzVectors in the TBrowser, add the following to your [rootlogon.C](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/rootlogon.C) file (assuming you've setup cmssw):
   	
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");

## Running limits

Setup the cmssw env for running combine:
      
      cd ttH-13TeVMultiLeptons
      chmod 744 setup_limit.sh
      ./setup_limit.sh
      
If curious look inside setup_limit.sh to see what it is doing. Now, make the histgograms for the datacard:
   	   
      cd TemplateMakers/test/
      cmsenv
      root -l makeStackPlotsFinalShape.C+

This produces fatStackPlots.root. Now make the datacard and produce the limits in a single step:

     chmod 744 run_limits.sh
     ./run_limits.sh fatStackPlots.root

## Running the full chain

### See [Here](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/GENERAL.md)

## 8 TeV reference twiki

### See [Here](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) 