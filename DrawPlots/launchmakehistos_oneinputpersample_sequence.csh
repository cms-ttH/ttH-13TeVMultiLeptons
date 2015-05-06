#! /bin/csh

#setenv inputtreedir "/afs/cern.ch/work/g/gesmith/ttH_multilepton_ana/newrepo/lepid_updates/CMSSW_7_2_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test"

#./make_histos.py -s ttH125 -f $inputtreedir/ttH125.root multilepton.yaml &
./make_histos.py -s TTZJets -f $inputtreedir/TTZJets.root multilepton.yaml &
./make_histos.py -s TTWJets -f $inputtreedir/TTWJets.root multilepton.yaml &
./make_histos.py -s ZJets -f $inputtreedir/ZJets.root multilepton.yaml &
./make_histos.py -s WJets -f $inputtreedir/WJets.root multilepton.yaml &
./make_histos.py -s WZJets -f $inputtreedir/WZJets.root multilepton.yaml &
./make_histos.py -s ZZJets -f $inputtreedir/ZZJets.root multilepton.yaml &
./make_histos.py -s TTJets -f $inputtreedir/TTJets.root multilepton.yaml &




