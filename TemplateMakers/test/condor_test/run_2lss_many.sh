#!/bin/sh

declare -A samples
#samples=( ["tth_powheg_jetClean_test"]=27 )
# ["ttbar_semiLep_jetClean_test"]=45 )
#samples=( ["ttbar_semiLep_jetClean_test"]=45 ["ttw_jetClean_test"]=32 )
#samples=( ["tth_powheg_old"]=17 
samples=( ["ttbar_semiLep_madgraph"]=89 )
#samples=( ["tth_aMC_old"]=84 ["ttbar_semiLep_powheg"]=60 ["ttbar_diLep_mg"]=151 ["ttW_aMCatNLO"]=2 ["ttZ_aMCatNLO"]=3 ["ttGammaStar"]=1 ["tttt"]=8 ["tZq"]=34 ["WW_diboson"]=10 ["ZZ_diboson"]=43 ["WZ_diboson"]=13 ["WWqq_rares"]=1 ["WW_doublescatering_rares"]=1 ["WWZ_rares"]=1 ["WZZ_rares"]=1 ["ZZZ_rares"]=1 ) 


for samp in "${!samples[@]}"
do
    sed -i 's/^sample = .*/sample = '"${samp}"'/' run_2lss.submit
    sed -i 's/^N = .*/N = '"${samples[${samp}]}"'/' run_2lss.submit
    condor_submit run_2lss.submit
done

