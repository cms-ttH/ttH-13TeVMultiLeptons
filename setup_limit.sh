#!/bin/sh

cat <<EOF
========================================================================
This script is creating a working directory for limit calculations of
the ttH analysis in 76X
Output is in setup_limit.log
========================================================================
EOF

(
   set -e
   set -o xtrace
   dcard="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/mk_datacard"
   cd ~/
   export SCRAM_ARCH=slc6_amd64_gcc491
   scramv1 project -n CMSSW_7_4_16_patch2_combine CMSSW CMSSW_7_4_16_patch2
   cd CMSSW_7_4_16_patch2_combine/src
   set +o xtrace
   eval $(scramv1 runtime -sh)
   set -o xtrace
   git cms-init > /dev/null

   git clone -b 74x-root6 https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
   git clone https://github.com/cms-analysis/CombineHarvester.git CombineHarvester

   cp -r $dcard .

   scram b -j 8
) > setup_limit.log


cat <<EOF
========================================================================
Output is in setup_limit.log
========================================================================
EOF

