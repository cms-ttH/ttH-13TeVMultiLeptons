#!/bin/bash

cd /afs/crc.nd.edu/user/c/cmuelle2/CMSSW_7_4_16_patch2_combine/src/
export SCRAM_ARCH=slc6_amd64_gcc491
eval `scramv1 runtime -sh`
./mk_datacard ~/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/fatStackPlots.root
combine -M Asymptotic -m125 -d limits/125/ttH_ttl.txt