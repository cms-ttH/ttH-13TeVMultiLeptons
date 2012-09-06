#!/bin/csh -f

set listFileName = $1
set iJob = $2
set iLabel = $3
set Selection = $4


echo $listFileName

set sample = ${listFileName}
echo $sample

echo "Selection is turned" $Selection
if($Selection =~ On) then
	set Sel = 1
endif
if($Selection =~ Off) then
	set Sel = 0
endif
echo "Selection will be used? " $Sel
set outDirName = batchBEAN/${sample}_${iLabel}_Sel${Selection}/log
echo $outDirName


if (! -e $outDirName) then
	mkdir -p $outDirName
endif

echo "run LepJetsTree TreeLepJets_condor_cfg.py "${sample}" "$iJob" "$iLabel" "$Sel 
LepJetsTree TreeLepJets_condor_cfg.py ${sample} $iJob $iLabel $Sel  > & ! $outDirName/lepjetsAnalysis_${sample}_${iLabel}_${iJob}.log
