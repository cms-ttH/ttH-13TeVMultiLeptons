#!/bin/csh -f

set listFileName = $1
#set iJob = $2
#set nJobs = $3
set iLabel = $2
set iJes = $3

#set sample = ${listFileName:r}
set sample = ${listFileName}
set outDirName = batchBEAN/

if (! -e $outDirName) then
	mkdir -p $outDirName
endif

#shyft_pretag shyftPretag_main_condor.py $listFileName $iJob $nJobs \
#	>&! $outDirName/shyftPretag_${sample}_${iJob}.log
#

#mttbarTree mttbarTree_batch.py $listFileName $iJob $nJobs \
#   >&! $outDirName/shyftPretag_${sample}_${iJob}.log


#root -b -q head.C 'test_beans_dileptonStudies.C+(-1,"'${sample}'", '$iJob', "'$iLabel'")' >&! $outDirName/test_beans_dileptonStudies_${sample}_${iLabel}_${iJob}.log

HistosFromTreesBatch dilPlots_condor_cfg.py ${sample}  $iLabel $iJes > & ! $outDirName/dilAnalysis_${sample}_${iLabel}_${iJes}.log
