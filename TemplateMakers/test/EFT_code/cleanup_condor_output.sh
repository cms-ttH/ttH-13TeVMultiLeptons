#!/bin/sh

set condorDir="/afs/crc.nd.edu/user/a/awightma/Public/condor_output"
set outDir="out"
set errDir="err"
set logFile=".logfile.log"

cd ${condorDir}

pwd

echo "Removing condor logs"
rm ${condorDir}/${outDir}/*
rm ${condorDir}/${errDir}/*
rm ${condorDir}/*${logFile}

# tth_nonbb_aMCatNLO_ tth_aMC ttZ ttW
# ttjets_dilep ttjets_semilep
#set samples = ("tth_aMC" "ttZ" "ttW" "ttjets_inclusive")

set samples = ("ttH_nonbb" "ttZ" "ttW" "ttjets_semilep" "ttjets_dilep")
#set samples = ("ttH_nonbb" "ttZ")

foreach sample ($samples)
    echo "Removing ${sample} segments..."
    rm ${condorDir}/${sample}_*_[0-9].root
    rm ${condorDir}/${sample}_*_[0-9][0-9].root
    rm ${condorDir}/${sample}_*_[0-9][0-9][0-9].root
end

#echo "Removing acceptance table segments"
#rm ${condorDir}/*"_acceptance_table_"*".txt"
