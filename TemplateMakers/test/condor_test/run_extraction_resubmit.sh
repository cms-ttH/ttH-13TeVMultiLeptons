#!/bin/sh

sed -i 's/^sample = .*/sample = tth_qgid/' run_extraction_resubmit.submit
for job in 1 23
do
    sed -i 's/^job_no = .*/job_no = '$job'/' run_extraction_resubmit.submit
    condor_submit run_extraction_resubmit.submit
done

