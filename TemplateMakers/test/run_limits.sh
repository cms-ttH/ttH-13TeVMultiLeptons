#!/bin/bash
#usage: ./run_limits.sh fatStackPlots.root

hists_file=$1
file_path="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/$hists_file"

if [ $hists_file ] && [ -a $file_path ]
    then
    cd /afs/crc.nd.edu/user/c/cmuelle2/CMSSW_7_4_16_patch2_combine/src/
    export SCRAM_ARCH=slc6_amd64_gcc491
    eval `scramv1 runtime -sh`
    ./mk_datacard $file_path
    combine -M Asymptotic -m125 -d limits/125/ttH_ttl.txt
else
    echo "Please specify file containing hists to calculate limits from."
    echo "Example: ./run_limits.sh fatStackPlots.root"
fi