#!/bin/sh
date

sample=$1
job_no=$2
total_jobs=$3

cd /afs/crc.nd.edu/user/a/awightma/CMSSW_Releases/CMSSW_8_0_26_patch1/src/ttH-13TeVMultiLeptons/TemplateMakers/test/EFT_code/
export SCRAM_ARCH=slc6_amd64_gcc530
eval `scramv1 runtime -sh`
hostname
root -l -b -q makeEFTSelectionTree.C+\(\""${sample}"\",${job_no},${total_jobs}\)

echo "Sample: ${sample}"
echo "Job: ${job_no}"

date