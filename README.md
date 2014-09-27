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

Here are some temporary instructions to get the tree-making code to compile:

	cd ttHMultileptonAnalysis/
	rm -rf skim/
	rm -rf listsForSkims2012_v3/
	rm -rf listsForSkims2012_53x_v3_hadoop/
	rm -rf listsUnskimmed2012_53x_v3_hadoop/
	rm -rf DrawPlots/
	rm -rf TemplateMakers/bean.tags

If code still does not compile, try removing the following:
	
	rm ttHMultileptonAnalysis/TemplateMakers/bin/matcher_ttV_SS.C
	rm ttHMultileptonAnalysis/TemplateMakers/bin/matcher_ttV.C
	rm ttHMultileptonAnalysis/TemplateMakers/bin/ttV.C
	rm ttHMultileptonAnalysis/TemplateMakers/bin/lepEff.C
	rm ttHMultileptonAnalysis/TemplateMakers/bin/ssTwoLep.C
	rm ttHMultileptonAnalysis/TemplateMakers/bin/csvSF.C
	rm ttHMultileptonAnalysis/TemplateMakers/bin/threeLepton.C
	rm ttHMultileptonAnalysis/TemplateMakers/bin/ttV_SS.C
	rm ttHMultileptonAnalysis/TemplateMakers/interface/TTreeWrapper.h
	rm ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h
	rm ttHMultileptonAnalysis/TemplateMakers/src/TTreeWrapper.cc

Then try running over some miniAOD:

	voms-proxy-init -voms cms
	cd ttHMultileptonAnalysis/TemplateMakers/test/
	osTwoLep ssCondor.py ttH125_miniAOD <your_label_here>

