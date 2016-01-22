#Notre Dame ttH multi-lepton framework

Analysis code for ttH H-->WW,ZZ,tautau-->2 or more leptons

The locations of the latest trees are [here](https://twiki.cern.ch/twiki/bin/view/CMS/NotreDameTrees).

## Installation

See the 8 TeV-based [DIL twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) for more information.

To get started tree-making from miniAOD (on an SL6 machine) do:        
        
        cmsrel CMSSW_7_6_3
        cd CMSSW_7_6_3/src
        cmsenv        
        git cms-init
        git clone git@github.com:cms-ttH/MiniAOD.git
        git clone git@github.com:cms-ttH/ttH-LeptonID.git ttH/LeptonID
        git clone git@github.com:cms-ttH/ttH-13TeVMultiLeptons.git
        scram b -j 8

Coming soon (with new lMVA vars):

	wget -P ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/ https://github.com/CERN-PH-CMG/cmg-cmssw/blob/CMGTools-from-CMSSW_7_4_12/CMGTools/TTHAnalysis/data/leptonMVA/tth/el_BDTG.weights.xml
	wget -P ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/lepMVA_weights/ https://github.com/CERN-PH-CMG/cmg-cmssw/blob/CMGTools-from-CMSSW_7_4_12/CMGTools/TTHAnalysis/data/leptonMVA/tth/mu_BDTG.weights.xml

Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
	cmsRun osTwoLep_cfg.py

To view the tth-specific classes' TLorentzVectors in the TBrowser, add the following to your [rootlogon.C](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/rootlogon.C) file (assuming you've setup cmssw):
   	
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");

## Running the full chain

### See [Here](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/GENERAL.md)
