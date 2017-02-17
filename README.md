#Notre Dame ttH multi-lepton framework

Analysis code for ttH H-->WW,ZZ,tautau-->2 or more leptons

The locations of the latest trees are [here](https://twiki.cern.ch/twiki/bin/view/CMS/NotreDameTrees).

## Installation

To get started tree-making from miniAOD (on an SL6 machine) do:        
        
        cmsrel CMSSW_8_0_20
        cd CMSSW_8_0_20/src
        cmsenv        
        git cms-addpkg CommonTools/Utils
        git cms-init
	git cms-merge-topic ikrav:egm_id_80X_v2
        git clone git@github.com:cms-ttH/MiniAOD.git
        git clone git@github.com:cms-ttH/ttH-LeptonID.git ttH/LeptonID
        git clone git@github.com:cms-ttH/ttH-13TeVMultiLeptons.git

For now, CMSSW_8_0_X (and later) seems to be broken so edit the following:

    	sed -i 's|Math/include|Math/interface|' CommonTools/Utils/interface/normalizedPhi.h

Then add the new Spring16 EleMVAID weights by doing:

	cd $CMSSW_BASE/external
	# below, you may have a different architecture, this is just one example from lxplus
	cd slc6_amd64_gcc530/
	git clone https://github.com/ikrav/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data
	cd data/RecoEgamma/ElectronIdentification/data
	git checkout egm_id_80X_v1
	# Go back to the src/
	cd $CMSSW_BASE/src


And compile (try again if it fails the first time):

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