#!/bin/sh

#samples=('TTGJets:9' 'ttjets_semilep:3,13,28' 'ttjets_dilep:84,102,1,16,26,27,31,35,37,40,51,56,67,85,89,94,117,118,3,121,122,70,105,60' 'ST_tW:1,6' 'ST_tChan_top:1,2' 'DY_M50_LO:53,18,39,20,50,58,65,70,78,86,10' 'DY_M50:8,19,20,27,35,50,52,54' 'WW_doublescatering_rares:0' 'tZq:7,30,32,48,49,56,23,64,75' 'ZGTo2LG:8,17,19,33,34' 'ZZ_to4l:10,12' 'WWqq_rares:0')
samples=( 'ttW:1' 'tZq:27' 'ttjets_semilep:26,31'  )

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

    sed -i 's/^sample = .*/sample = '$sample'/' run_2lss_resubmit.submit

    # Loop over jobs
    for job in ${jobs[@]}
    do
	sed -i 's/^job_no = .*/job_no = '$job'/' run_2lss_resubmit.submit
	condor_submit run_2lss_resubmit.submit
    done
done