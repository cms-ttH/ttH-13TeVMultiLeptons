#!/bin/bash
#usage: ./hadd_many.sh

#samples=( "tth_powheg_genFilter" "tth_powheg_new" )
#samples=( "tth_powheg" "ttW_aMCatNLO" "ttZ_aMCatNLO" "ttGammaStar" "wGamma" "zGamma" "convs_sT" "convs_ttbar" "WWqq_rares" "WW_doublescatering_rares" "WWW_rares" "WWZ_rares" "WZZ_rares" "ZZZ_rares" "tZq" "tttt" "WW_diboson" "ZZ_diboson" "WZ_diboson" )
samples=( "data" )
for i in "${samples[@]}"
do
    ./hadd_files.sh $i
done
