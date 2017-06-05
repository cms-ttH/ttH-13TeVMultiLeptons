#!/bin/sh

declare -A samples
#samples=( ["ttH"]=3 ["ttW"]=11 ["ttZ"]=2 ["ttZ_M1to10"]=1 ["WGToLNuG"]=1 ["ZGTo2LG"]=1 ["TGJets"]=1 ["TTGJets"]=1 ["WWqq_rares"]=1 ["WW_doublescatering_rares"]=1 ["WWW_rares"]=1 ["WWZ_rares"]=1 ["WZZ_rares"]=1 ["ZZZ_rares"]=1 ["tZq"]=4 ["tttt"]=1 ["WW_2l2nu"]=1 ["ZZ_to4l"]=1 ["WZ_to3lnu"]=1 ["ST_sChan"]=1 ["ST_tChan_top"]=1 ["ST_tChan_antitop"]=1 ["ST_tW"]=1 ["tWll"]=1 ["ttjets_dilep"]=1 ["ttjets_semilep"]=1 ["Wjets"]=1 ["DY_M10_50"]=1 ["DY_M50"]=1 )
samples=( ["data"]=1 ["fakes"]=1 ["flips"]=5 )
rm -rf condor_logs/*
for samp in "${!samples[@]}"
do
    sed -i 's/^sample = .*/sample = '"${samp}"'/' run_extraction.submit
    sed -i 's/^N = .*/N = '"${samples[${samp}]}"'/' run_extraction.submit
    condor_submit run_extraction.submit
done

