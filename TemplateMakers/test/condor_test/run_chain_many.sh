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
#samples=( ["tth_powheg"]=8 ["ttW"]=16 ["ttZ_M10"]=7 ["ttZ_M1to10"]=1 ["WGToLNuG"]=1 ["ZGTo2LG"]=35 ["TGJets"]=2 ["TTGJets"]=12 ["WWqq_rares"]=1 ["WW_doublescatering_rares"]=2 ["WWW_rares"]=1 ["WWZ_rares"]=1 ["WZZ_rares"]=1 ["ZZZ_rares"]=1 ["tZq"]=77 ["tttt"]=1 ["WW_2l2nu"]=5 ["ZZ_to4l"]=18 ["WZ_to3lnu"]=5 ["ST_sChan"]=1 ["ST_tChan_top"]=5 ["ST_tChan_antitop"]=3 ["ST_tW"]=8 ["tWll"]=1 ["ttjets_dilep"]=127 ["ttjets_semilep"]=32 ["Wjets"]=1 ["DY_M10_50"]=9 ["DY_M50_LO"]=96 ["DY_M50"]=63)
samples=( ["data"]=207 )

##################
####
#### Gen filter studies
####
##################
#samples=( ["tth_powheg_genFilter"]=44 ["tth_powheg_noGenFilter"]=30 ["tth_powheg_genFilter_looseLepJetClean"]=27 )
#samples=( ["ttjets_semilep_genFilter"]=28 ["ttjets_semilep_genFilter_looseLepJetClean"]=28 ["ttjets_semilep_noFilter_looseLepJetClean"]=40 ["ttjets_semilep_noFilter"]=41 )

rm -rf condor_logs/*
for samp in "${!samples[@]}"
do
    sed -i 's/^sample = .*/sample = '"${samp}"'/' run_chain.submit
    sed -i 's/^N = .*/N = '"${samples[${samp}]}"'/' run_chain.submit
    condor_submit run_chain.submit
done

