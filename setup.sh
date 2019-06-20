#!/bin/sh

cat <<EOF
========================================================================
This script is creating a working directory for ntuplizing and plotting
the EFT multilepton analysis in 94X
Output is in setup.log
========================================================================
EOF

(
   set -e
   set -o xtrace

   export SCRAM_ARCH=slc7_amd64_gcc630
   scramv1 project CMSSW CMSSW_9_4_6
   cd CMSSW_9_4_6/src
   set +o xtrace
   eval $(scramv1 runtime -sh)
   set -o xtrace

   git cms-init > /dev/null

   git clone -b cmssw940pre3 git@github.com:cms-ttH/MiniAOD.git
   git clone -b EFT_code git@github.com:cms-ttH/ttH-LeptonID.git ttH/LeptonID
   git clone -b EFT_code git@github.com:cms-ttH/ttH-13TeVMultiLeptons.git

   scram b -j 8

) > setup.log


cat <<EOF
========================================================================
Output is in setup.log
========================================================================
EOF
