#!/bin/bash
#usage: ./hadd_many.sh

#samples=( "tth_powheg_genFilter" "tth_powheg_new" )
#samples=( "tth_powheg" "ttW" "ttZ_M10" "ttZ_M1to10" "WGToLNuG" "ZGTo2LG" "TGJets" "TTGJets" "WWqq_rares" "WW_doublescatering_rares" "WWW_rares" "WWZ_rares" "WZZ_rares" "ZZZ_rares" "tZq" "tttt" "WW_2l2nu" "ZZ_to4l" "WZ_to3lnu" "ST_sChan" "ST_tChan_top" "ST_tChan_antitop" "ST_tW" "tWll" "ttjets_dilep" "ttjets_semilep" "Wjets" "DY_M10_50" "DY_M50_LO" "DY_M50") 
#samples=( "data" )
samples=( "data2los_ar" "data2lss_lepMVA_ar" "data2lss_sr" )
#samples=( "data2lss_sr" )
#samples=( "ttjets_semilep_genFilter2lss_sr" "ttjets_semilep_genFilter2lss_training_fo" "ttjets_semilep_genFilter2lss_training_loose" "ttjets_semilep_genFilter_looseLepJetClean2lss_sr" "ttjets_semilep_genFilter_looseLepJetClean2lss_training_fo" "ttjets_semilep_genFilter_looseLepJetClean2lss_training_loose" "ttjets_semilep_noFilter2lss_sr" "ttjets_semilep_noFilter2lss_training_fo" "ttjets_semilep_noFilter2lss_training_loose" "ttjets_semilep_noFilter_looseLepJetClean2lss_sr" "ttjets_semilep_noFilter_looseLepJetClean2lss_training_fo" "ttjets_semilep_noFilter_looseLepJetClean2lss_training_loose" )
for i in "${samples[@]}"
do
    ./hadd_files.sh $i
done
