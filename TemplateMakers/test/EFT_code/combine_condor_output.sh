#!/bin/sh

set cmsswDir="/afs/crc.nd.edu/user/a/awightma/CMSSW_Releases/CMSSW_8_0_26_patch1/src"
set condorDir="/afs/crc.nd.edu/user/a/awightma/Public/condor_output"
set outDir="out"
set errDir="err"
set logFile=".logfile.log"

# tth_nonbb_aMCatNLO_ tth_aMC ttZ ttW
# ttjets_dilep ttjets_semilep
set samples = ("tth_aMC" "ttZ" "ttW" "ttjets_dilep" "ttjets_semilep")

set eventMapSource="_event_map_"
set eventMapTarget="_event_map.root"

set binSelection0 = "null"
set binSelection1 = "2los_6jets"
set binSelection2 = "2lss_p_6jets"
set binSelection3 = "2lss_m_6jets"
set binSelection4 = "3l_ppm_4jets"
set binSelection5 = "3l_mmp_4jets"
set binSelection6 = "4l_2jets"

set nJetDistSource1 = "_${binSelection0}_vs_${binSelection1}_nJet_dist_"
set nJetDistTarget1 = "_${binSelection0}_vs_${binSelection1}_nJet_dist.root"

set nJetDistSource2 = "_${binSelection1}_vs_${binSelection0}_nJet_dist_"
set nJetDistTarget2 = "_${binSelection1}_vs_${binSelection0}_nJet_dist.root"

set nJetDistSource3 = "_${binSelection1}_vs_${binSelection1}_nJet_dist_"
set nJetDistTarget3 = "_${binSelection1}_vs_${binSelection1}_nJet_dist.root"

cd "${cmsswDir}"

pwd

cmsenv

cd ${condorDir}

pwd

foreach sample ($samples)
    #echo ${condorDir}/${sample}{$eventMapTarget}
    hadd -f ${condorDir}/${sample}{$eventMapTarget} ${condorDir}/${sample}${eventMapSource}*.root
    #hadd -f ${condorDir}/${sample}{$nJetDistTarget1} ${condorDir}/${sample}${nJetDistSource1}*.root
    #hadd -f ${condorDir}/${sample}{$nJetDistTarget2} ${condorDir}/${sample}${nJetDistSource2}*.root
    #hadd -f ${condorDir}/${sample}{$nJetDistTarget3} ${condorDir}/${sample}${nJetDistSource3}*.root
end

#python mergeAcceptanceTables.py

