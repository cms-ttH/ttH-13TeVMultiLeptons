#!/bin/csh -f

set listFileName = $1
set iJob = $2
#set nJobs = $3
set iLabel = $3
set iJes = $4
set iJer = $5
set iBSys = $6 #Btag Systematic
set iBtag = $7 #number of btags

echo $listFileName
#set sample = ${listFileName:r}
set sample = ${listFileName}
echo $sample
echo $iJes
echo $iJer
echo $iBSys


if ($iJes == 0) then
    if ($iJer == 0) then
		if ($iBSys == 0 ) then
			set outDirName = batchBEAN/${sample}_${iLabel}/log
		endif
		if ($iBSys == 1 ) then
			set outDirName = batchBEAN/${sample}_${iLabel}_BtagSFUp/log
		endif
		if ($iBSys == -1 ) then
			set outDirName = batchBEAN/${sample}_${iLabel}_BtagSFDown/log
		endif
		if ($iBSys == 2 ) then
			set outDirName = batchBEAN/${sample}_${iLabel}_LflvSFUp/log
		endif
		if ($iBSys == -2 ) then
			set outDirName = batchBEAN/${sample}_${iLabel}_LflvSFDown/log
		endif		   
    endif
    if ($iJer == -1) then
        set outDirName = batchBEAN/${sample}_${iLabel}_JerDown/log
    endif
    if ($iJer == 1) then
        set outDirName = batchBEAN/${sample}_${iLabel}_JerUp/log
    endif
endif
if ($iJes == -1) then
	set outDirName = batchBEAN/${sample}_${iLabel}_JesDown/log
endif
if ($iJes == 1) then
    set outDirName = batchBEAN/${sample}_${iLabel}_JesUp/log
endif

if (! -e $outDirName) then
	mkdir -p $outDirName
endif

#shyft_pretag shyftPretag_main_condor.py $listFileName $iJob $nJobs \
#	>&! $outDirName/shyftPretag_${sample}_${iJob}.log
#

#mttbarTree mttbarTree_batch.py $listFileName $iJob $nJobs \
#   >&! $outDirName/shyftPretag_${sample}_${iJob}.log


#root -b -q head.C 'test_beans_dileptonStudies.C+(-1,"'${sample}'", '$iJob', "'$iLabel'")' >&! $outDirName/test_beans_dileptonStudies_${sample}_${iLabel}_${iJob}.log

LepJets LepJetsAnalysis_condor_cfg.py ${sample} $iJob $iLabel $iJes $iJer $iBSys $iBtag > & ! $outDirName/lepjetsAnalysis_${sample}_${iLabel}_${iJob}.log
