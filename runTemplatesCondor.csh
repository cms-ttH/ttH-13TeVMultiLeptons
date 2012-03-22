#!/bin/csh -f

set listFileName = $1
set iJob = $2
#set nJobs = $3

#set sample = ${listFileName:r}
set sample = ${listFileName}
set outDirName = batchBEAN/$sample/log

if (! -e $outDirName) then
	mkdir -p $outDirName
endif

#shyft_pretag shyftPretag_main_condor.py $listFileName $iJob $nJobs \
#	>&! $outDirName/shyftPretag_${sample}_${iJob}.log
#

#mttbarTree mttbarTree_batch.py $listFileName $iJob $nJobs \
#   >&! $outDirName/shyftPretag_${sample}_${iJob}.log


root -b -q head.C 'test_beans_v1.C+(-1,"'${sample}'", '$iJob')' >&! $outDirName/test_beans_v1_${sample}_${iJob}.log
