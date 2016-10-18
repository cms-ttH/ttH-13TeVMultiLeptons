#!/bin/bash
#usage: ./hadd_many.sh

#samples=( "tth_powheg_old" "ttbar_semiLep_madgraph" )
samples=( "tth_aMC_old" "ttbar_semiLep_powheg" "ttW_aMCatNLO" "ttZ_aMCatNLO" "ttbar_diLep_madgraph" )

for i in "${samples[@]}"
do
    ./hadd_files.sh $i
done
