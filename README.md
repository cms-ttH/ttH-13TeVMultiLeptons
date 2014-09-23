## Installation

See [here](https://github.com/cms-ttH/BEAN#boson-exploration-analysis-ntuple) for instructions to set up your `CMSSW` area.
See the [DIL twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) for more information about how to use some of these scripts.

To get started tree-making from miniAOD (on an SL6 machine) do:

	cmsrel CMSSW_7_0_7_patch1
	cd CMSSW_7_0_7_patch1/src/
	cmsenv	
	git clone git@github.com:cms-ttH/MiniAOD.git
	cd MiniAOD/
	git checkout -b MultiLeptons	
	cd -
	git clone git@github.com:cms-ttH/ttHMultileptonAnalysis.git
	cd ttHMultileptonAnalysis/
	git checkout -b 13TeV
	cd -
	scram b -j 32

Here are some temporary instructions to get the tree-making code to compile:

	cd ttHMultileptonAnalysis/
	rm -rf skim/
	rm -rf listsForSkims2012_v3/
	rm -rf listsForSkims2012_53x_v3_hadoop/
	rm -rf listsUnskimmed2012_53x_v3_hadoop/
	rm -rf DrawPlots/
	

Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttHMultileptonAnalysis/TemplateMakers/test/
	osTwoLep ssCondor.py ttH125_miniAOD <your_label_here>

