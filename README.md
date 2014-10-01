## Installation

See [here](https://github.com/cms-ttH/BEAN#boson-exploration-analysis-ntuple) for instructions to set up your `CMSSW` area.
See the [DIL twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) for more information about how to use some of these scripts.

To get started tree-making from miniAOD (on an SL6 machine) do:

	cmsrel CMSSW_7_0_7_patch1
	cd CMSSW_7_0_7_patch1/src/
	cmsenv	
	git clone git@github.com:cms-ttH/MiniAOD.git
	git clone git@github.com:cms-ttH/ttHMultileptonAnalysis.git -b 13TeV
	scram b -j 32


Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttHMultileptonAnalysis/TemplateMakers/test/
	osTwoLep ssCondor.py ttH125_miniAOD <your_label_here>

