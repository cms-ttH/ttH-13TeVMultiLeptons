#!/bin/sh

sed -i 's/^sample = .*/sample = data/' run_2lss_resubmit.submit
for job in 179 85 132
do
    sed -i 's/^job_no = .*/job_no = '$job'/' run_2lss_resubmit.submit
    condor_submit run_2lss_resubmit.submit
done

