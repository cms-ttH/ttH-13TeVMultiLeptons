#Notre Dame ttH multi-lepton framework

Analysis code for ttH H-->WW,ZZ,tautau-->2 or more leptons

The locations of the latest trees are [here](https://twiki.cern.ch/twiki/bin/view/CMS/NotreDameTrees).

## Installation

See the 8 TeV-based [DIL twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) for more information.

To get started tree-making from miniAOD (on an SL6 machine) do:        
        
        cmsrel CMSSW_7_4_7
        cd CMSSW_7_4_7/src
        cmsenv
        
        git cms-init
        git remote add cmg-central https://github.com/CERN-PH-CMG/cmg-cmssw.git
        git fetch cmg-central
        echo "/.gitignore/" >> .git/info/sparse-checkout
        echo "/CMGTools/TTHAnalysis/data/" >> .git/info/sparse-checkout
        echo "/EgammaAnalysis/ElectronTools/" >> .git/info/sparse-checkout
        git checkout -b CMGTools-from-CMSSW_7_4_7 cmg-central/CMGTools-from-CMSSW_7_4_7
        git clone git@github.com:cms-ttH/MiniAOD.git
        git clone git@github.com:cms-ttH/ttH-LeptonID.git ttH/LeptonID
        git clone git@github.com:cms-ttH/ttH-13TeVMultiLeptons.git
        gzip -d EgammaAnalysis/ElectronTools/data/PHYS14/*.gz
        
        scram b -j 8

Install [PyYAML](http://pyyaml.org/wiki/PyYAML) if you don't have it already:

	cd /tmp
	wget --no-check-certificate -O - http://pyyaml.org/download/pyyaml/PyYAML-3.10.tar.gz|tar xzf -
	cd PyYAML-3.10/
	python setup.py install --user
	cd ..
	rm -rf PyYAML-3.10/

Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
	cmsRun osTwoLep_cfg.py

To view the tth-specific classes' TLorentzVectors in the TBrowser, add the following to your [rootlogon.C](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/rootlogon.C) file (assuming you've setup cmssw):
   	
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");

## Running the full chain

### See [Here](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/master/doc/GENERAL.md)
