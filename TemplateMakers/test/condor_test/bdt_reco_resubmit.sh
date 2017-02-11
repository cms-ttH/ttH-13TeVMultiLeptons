#!/bin/sh

sed -i 's/^sample = .*/sample = tth_aMC_old/' bdt_reco_resubmit.submit
for job in 8
do
    sed -i 's/^job_no = .*/job_no = '$job'/' bdt_reco_resubmit.submit
    condor_submit bdt_reco_resubmit.submit
done

