#!/bin/sh

declare -A samples
##################
####
#### ICHEP16 Samples
####
##################
#samples=( ["tth_powheg_jetClean_test"]=27 ["ttbar_semiLep_jetClean_test"]=45 )
#samples=( ["ttbar_semiLep_jetClean_test"]=45 ["ttw_jetClean_test"]=32 )
#samples=( ["tth_powheg_old"]=17 
#samples=( ["ttbar_semiLep_madgraph"]=89 )
#samples=( ["tth_aMC_old"]=83 ["ttbar_semiLep_powheg"]=61 ["ttbar_diLep_mg"]=151 ["ttW_aMCatNLO"]=2 ["ttZ_aMCatNLO"]=3 ["ttGammaStar"]=1 ["tttt"]=8 ["tZq"]=34 ["WW_diboson"]=10 ["ZZ_diboson"]=43 ["WZ_diboson"]=13 ["WWqq_rares"]=1 ["WW_doublescatering_rares"]=1 ["WWZ_rares"]=1 ["WZZ_rares"]=1 ["ZZZ_rares"]=1 ) 

##################
####
#### Moriond '17 Samples
####
##################
#samples=( ["tth_powheg_genFilter"]=44 ["tth_powheg_new"]=30 )
#samples=( ["tth_powheg"]=8 ["ttW_aMCatNLO"]=15 ["ttZ_aMCatNLO"]=7 ["ttGammaStar"]=7 ["wGamma"]=1 ["zGamma"]=35 ["convs_sT"]=2 ["convs_ttbar"]=4 ["WWqq_rares"]=1 ["WW_doublescatering_rares"]=2 ["WWW_rares"]=1 ["WWZ_rares"]=1 ["WZZ_rares"]=1 ["ZZZ_rares"]=1 ["tZq"]=74 ["tttt"]=1 ["WW_diboson"]=5 ["ZZ_diboson"]=19 ["WZ_diboson"]=5)
samples=( ["data"]=209 )

rm -rf condor_logs/*
for samp in "${!samples[@]}"
do
    sed -i 's/^sample = .*/sample = '"${samp}"'/' run_2lss.submit
    sed -i 's/^N = .*/N = '"${samples[${samp}]}"'/' run_2lss.submit
    condor_submit run_2lss.submit
done

