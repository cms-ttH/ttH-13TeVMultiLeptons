#!/bin/sh

declare -A samples
#samples=( ["tth_powheg_old"]=81 ["ttbar_semiLep_madgraph"]=122 )
#samples=( ["tth_sigExtr_training_2lss"]=9 ["ttbar_sigExtr_training_2lss"]=14 )
#samples=( ["tth_powheg_genFilterTraining"]=250 ["ttbar_semiLep_genFilterTraining"]=80 ["ttw_genFilterTraining"]=125 )
#samples=( ["tth_aMC_old"]=214 ["ttbar_semiLep_powheg"]=2 ["ttbar_diLep_mg"]=1 ["ttW_aMCatNLO"]=7 ["ttZ_aMCatNLO"]=3 ["ttGammaStar"]=4 ["tttt"]=20 ["tZq"]=6 ["WW_diboson"]=1 ["ZZ_diboson"]=1 ["WZ_diboson"]=1 ["WWqq_rares"]=1 ["WW_doublescatering_rares"]=1 ["WWZ_rares"]=1 ["WZZ_rares"]=1 ["ZZZ_rares"]=1 )
#samples=( ["tth_qgid"]=24 ["ttw_qgid"]=1 ["ttz_qgid"]=1 )
samples=( ["tth_aMC"]=13 ["ttW_aMCatNLO"]=16 ["ttZ_aMCatNLO"]=7 ["ttbar_semiLep_madgraph"]=1 )


rm -rf condor_logs/*
for samp in "${!samples[@]}"
do
    sed -i 's/^sample = .*/sample = '"${samp}"'/' bdt_reco.submit
    sed -i 's/^N = .*/N = '"${samples[${samp}]}"'/' bdt_reco.submit
    condor_submit bdt_reco.submit
done

