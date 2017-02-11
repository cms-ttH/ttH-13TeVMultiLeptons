#!/bin/sh

sed -i 's/^sample = .*/sample = tth_aMC_old/' run_2lss_resubmit.submit
for job in 3 55
do
    sed -i 's/^job_no = .*/job_no = '$job'/' run_2lss_resubmit.submit
    condor_submit run_2lss_resubmit.submit
done

