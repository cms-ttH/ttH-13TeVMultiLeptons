#!/bin/sh

declare -A samples
samples=( ["ttH"]=16 ["ttW"]=22 ["ttZ_M10"]=4 ["ttZ_M1to10"]=2 ["WGToLNuG"]=1 ["ZGTo2LG"]=1 ["TGJets"]=2 ["TTGJets"]=2 ["WWqq_rares"]=2 ["WW_doublescatering_rares"]=1 ["WWW_rares"]=1 ["WWZ_rares"]=1 ["WZZ_rares"]=1 ["ZZZ_rares"]=1 ["tZq"]=8 ["tttt"]=2 ["WW_2l2nu"]=1 ["ZZ_to4l"]=1 ["WZ_to3lnu"]=2 ["ST_sChan"]=1 ["ST_tChan_top"]=1 ["ST_tChan_antitop"]=1 ["ST_tW"]=1 ["tWll"]=1 ["ttjets_dilep"]=2 ["ttjets_semilep"]=2 ["Wjets"]=1 ["DY_M10_50"]=1 ["DY_M50"]=1 ["data"]=1 ["fakes"]=1 ["flips"]=10 )
#samples=( ["data"]=1 ["fakes"]=1 ["flips"]=5 )
rm -rf condor_logs/*
for samp in "${!samples[@]}"
do
    sed -i 's/^sample = .*/sample = '"${samp}"'/' run_extraction.submit
    sed -i 's/^N = .*/N = '"${samples[${samp}]}"'/' run_extraction.submit
    condor_submit run_extraction.submit
done

