## Installation

See [here](https://github.com/cms-ttH/BEAN#boson-exploration-analysis-ntuple) for instructions to set up your `CMSSW` area.
See the [DIL twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) for more information about how to use some of these scripts.

To get started tree-making from miniAOD (on an SL6 machine) do:

	cmsrel CMSSW_7_2_3
	cd CMSSW_7_2_3/src/
	cmsenv	
	git clone git@github.com:cms-ttH/MiniAOD.git
	git clone git@github.com:cms-ttH/ttH-13TeVMultiLeptons.git
	git clone git@github.com:CERN-PH-CMG/cmg-cmssw.git
	cd cmg-cmssw
	git checkout -b noheppybranch CMGTools-NoHeppy-from-CMSSW_7_2_3
	cd ..
	mv cmg-cmssw/EgammaAnalysis .
	rm -rf cmg-cmssw
	gzip -d EgammaAnalysis/ElectronTools/data/*.gz
	scram b -j 8


Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
	cmsRun osTwoLep_cfg.py

To view the tth-specific classes' TLorentzVectors in the TBrowser, add the following to your rootlogon.C file (assuming you've setup cmssw):
   	
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");