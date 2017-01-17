#!/bin/bash
#usage: ./hadd_many.sh

#samples=( "tth_powheg_jetClean_test" "ttbar_semiLep_jetClean_test" "ttw_jetClean_test" )
#samples=( "ttbar_semiLep_jetClean_test" "ttw_jetClean_test" )
#samples=( "tth_sigExtr_training_2lss" "ttbar_sigExtr_training_2lss" )
#samples=( "tth_powheg_genFilterTraining" "ttbar_semiLep_genFilterTraining" "ttw_genFilterTraining" )
samples=( "tth_aMC_old" "ttbar_semiLep_powheg" "ttbar_diLep_mg" "ttW_aMCatNLO" "ttZ_aMCatNLO" "ttGammaStar" "tttt" "tZq" "WW_diboson" "ZZ_diboson" "WZ_diboson" "WWqq_rares" "WW_doublescatering_rares" "WWZ_rares" "WZZ_rares" "ZZZ_rares" ) 

for i in "${samples[@]}"
do
    ./hadd_files.sh $i
done
