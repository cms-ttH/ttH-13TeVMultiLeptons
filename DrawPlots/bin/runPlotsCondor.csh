#!/bin/csh -f

set listFileName = $1
#set iJob = $2
#set nJobs = $3
set iYear = $2
set iZmask = $3
set iLabel = $4
set iSkipSyst = $5
set iPV = $6
# set iJes = $5
# set iJer = $6
# set iPV = $7

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

HistosFromTreesBatch dilPlots_condor_cfg.py ${sample}  $iYear $iZmask $iLabel $iSkipSyst $iPV > & ! $outDirName/dilAnalysis_${sample}_${iYear}_${iZmask}_${iLabel}_${iPV}.log
#HistosFromTreesBatch dilPlots_condor_cfg.py ${sample}  $iYear $iZmask $iLabel $iJes $iJer > & ! $outDirName/dilAnalysis_${sample}_${iYear}_${iZmask}_${iLabel}.log
