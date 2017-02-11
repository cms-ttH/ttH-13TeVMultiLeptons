#!/bin/sh

cd /afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/TemplateMakers/test/
export SCRAM_ARCH=slc6_amd64_gcc530
#printenv
#which scramv1
eval `scramv1 runtime -sh`
root -l -b -q branchAdder.C\($1,$2\)
#sleep 180
#date
#hostname
#printenv
