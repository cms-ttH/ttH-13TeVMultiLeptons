#!/bin/bash
#usage: ./hadd_many.sh

#samples=( "tth_powheg_old" "ttbar_semiLep_madgraph" )
samples=( "tth_aMC_old" "ttbar_semiLep_powheg" )
#samples=( "tth_aMC_old" "ttbar_semiLep_powheg" "ttbar_diLep_powheg_tranche3" "ttW_aMCatNLO" "ttZ_aMCatNLO" "tttt" "tqZ" "WW_diboson" "ZZ_diboson" "WZ_diboson" "WWqq_rares" "WW_doublescatering_rares" "WWZ_rares" "WZZ_rares" "ZZZ_rares" ) 

for i in "${samples[@]}"
do
    ./hadd_files.sh $i
done
