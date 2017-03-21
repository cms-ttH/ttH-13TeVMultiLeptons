#!/bin/sh

sed -i 's/^sample = .*/sample = tth_qgid/' bdt_reco_resubmit.submit
for job in 1 23
do
    sed -i 's/^job_no = .*/job_no = '$job'/' bdt_reco_resubmit.submit
    condor_submit bdt_reco_resubmit.submit
done

