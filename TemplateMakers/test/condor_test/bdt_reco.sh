#!/bin/sh

events_per_job=$1
job_no=$2




cd /afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/
export SCRAM_ARCH=slc6_amd64_gcc530
#printenv
#which scramv1
eval `scramv1 runtime -sh`
root -l -b -q evaluateRecoBdt.C\(\""$1"\",$2,$3\)
#root -l -b -q evaluateRecoBdt.C+\(\""$1"\",$2,$3\)


#sleep 180
#date
#hostname
#printenv
