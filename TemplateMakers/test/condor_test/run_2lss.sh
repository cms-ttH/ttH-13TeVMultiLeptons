#!/bin/sh

process=$1

samples=( "WW_diboson" "ZZ_diboson" "WZ_diboson" "tttt" "tqZ" "WWqq_rares" "WW_doublescatering_rares" "WWZ_rares" "WZZ_rares" "ZZZ_rares" ) 
sample=${samples[$process]}


cd /afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/
export SCRAM_ARCH=slc6_amd64_gcc530
eval `scramv1 runtime -sh`
root -l -b -q makeSelectionTree.C+\(\""$sample"\"\)
#sleep 180
#date
#hostname
#printenv
