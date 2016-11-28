#!/bin/sh

sample=$1
job_no=$2

cd /afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/
export SCRAM_ARCH=slc6_amd64_gcc530
eval `scramv1 runtime -sh`
root -l -b -q makeSelectionTree.C\(\""$sample"\",\""analysis"\",${job_no}\)
#root -l -b -q makeSelectionTree.C+\(\""$sample"\",${job_no}\)
#sleep 180
#date
#hostname
#printenv
