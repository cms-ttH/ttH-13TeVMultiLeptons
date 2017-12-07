#!/bin/sh
set subFile="run_EFTSelection.submit"

#set samples = ("ttH_nonbb" "ttZ" "ttW" "ttjets_inclusive" "ttjets_semilep" "ttjets_dilep")
set samples = ("ttH_nonbb" "ttZ" "ttW" "ttjets_semilep" "ttjets_dilep")
#set samples = ("ttjets_semilep")

foreach sample ($samples)
    sed -i "s/^sample = .*/sample = ${sample}/" $subFile
    #head -n3 ${subFile}
    condor_submit $subFile
    echo ""
end

condor_q
