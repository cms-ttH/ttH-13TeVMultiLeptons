## Installation

See [here](https://github.com/cms-ttH/BEAN#boson-exploration-analysis-ntuple) for instructions to set up your `CMSSW` area.
See the [DIL twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NovaDilWorkflow) for more information about how to use some of these scripts.
[PyYaml](http://pyyaml.org/wiki/PyYAML) is a pre-requisite.  Install it locally after executing `cmsenv`:

	cd /tmp
    wget --no-check-certificate -O - http://pyyaml.org/download/pyyaml/PyYAML-3.10.tar.gz|tar xzf -
    cd PyYAML-3.10/
    python setup.py install --user
    cd ..
    rm -rf PyYAML-3.10/

Next, clone this repository into your CMSSW source area:

    cd $CMSSW_BASE/src
    git clone https://github.com/cms-ttH/ttHMultileptonAnalysis.git
    cd ttHMultileptonAnalysis
    scram b -j32

