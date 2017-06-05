#!/bin/sh

samples=('ttW:6')

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