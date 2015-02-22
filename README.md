#Notre Dame ttH Multi-lepton Framework

## Installation

See [here](https://github.com/cms-ttH/BEAN#boson-exploration-analysis-ntuple) for instructions to set up your `CMSSW` area.
See the [DIL twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) for more information about how to use some of these scripts.

To get started tree-making from miniAOD (on an SL6 machine) do:

	cmsrel CMSSW_7_2_3
	cd CMSSW_7_2_3/src/
	cmsenv
	git cms-merge-topic HuguesBrun:trigElecIdInCommonIsoSelection720	
	git clone git@github.com:cms-ttH/MiniAOD.git
	git clone git@github.com:cms-ttH/ttH-13TeVMultiLeptons.git
	scram b -j 8


Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
	cmsRun osTwoLep_cfg.py

To view the tth-specific classes' TLorentzVectors in the TBrowser, add the following to your rootlogon.C file (assuming you've setup cmssw):
   	
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");

## Running the full analysis chain

Several options exist for making trees and turning them into limits. 

### [Interative](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/INTERACTIVE.md)

### [Batch-ssh](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/SSH-BATCH.md)
