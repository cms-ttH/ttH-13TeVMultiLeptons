#!/bin/sh

#samples=( 'ZZ_to4l:0,4' 'DY_M50_LO:6,44,55,30,93,79' 'DY_M50:26,20,37,57' 'tZq:65,13,54,16,39' 'ttjets_dilep:24,4,62,97,113,40,78,121,13' 'ZZZ_rares:0' 'ZGTo2LG:34' 'WGToLNuG:0' 'ST_tW:6' 'ttjets_semilep:29' 'ttW:6' 'tth__powheg_mWcutfix:12,16')
samples=( 'ttH:1,6')

# Loop over samples
for sample in ${samples[@]}
do
    # delete previous array/list (this is crucial!)
    unset jobs
    # split sub-list if available
    if [[ $sample == *":"* ]]
    then
        # split sample name from sub-list
        tmpArray=(${sample//:/ })
        sample=${tmpArray[0]}
        jobs=${tmpArray[1]}
        # make array from simple string
        jobs=(${jobs//,/ })
    fi

    sed -i 's/^sample = .*/sample = '$sample'/' run_extraction_resubmit.submit

    # Loop over jobs
    for job in ${jobs[@]}
    do
	sed -i 's/^job_no = .*/job_no = '$job'/' run_extraction_resubmit.submit
	condor_submit run_extraction_resubmit.submit
    done
done