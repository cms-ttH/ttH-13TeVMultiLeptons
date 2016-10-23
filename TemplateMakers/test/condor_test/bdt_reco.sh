#!/bin/sh

declare -A samples
#samples=( ["tth_powheg_old"]=81 ["ttbar_semiLep_madgraph"]=122 )
samples=( ["tth_aMC_old"]=213 ["ttbar-semiLep-powheg"]=3 ["ttbar-diLep-powheg_tranche3"]=3 ["ttW-aMCatNLO"]=7 ["ttZ-aMCatNLO"]=3 ["tttt"]=20 ["tqZ"]=6 ["WW_diboson"]=1 ["ZZ_diboson"]=1 ["WZ_diboson"]=1 ["WWqq_rares"]=1 ["WW_doublescatering_rares"]=1 ["WWZ_rares"]=1 ["WZZ_rares"]=1 ["ZZZ_rares"]=1 ) 

for samp in "${!samples[@]}"
do
    sed -i 's/^sample = .*/sample = '"${samp}"'/' /afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/condor_test/bdt_reco.submit
    sed -i 's/^N = .*/N = '"${samples[${samp}]}"'/' /afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/condor_test/bdt_reco.submit
    condor_submit bdt_reco.submit
done

