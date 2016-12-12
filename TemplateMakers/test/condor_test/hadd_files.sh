#!/bin/bash
#usage ./hadd_files.sh <prefix>
#      ./hadd_files.sh tth_powheg_old

prefix=$1

#target_dir="/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/nov21_genFilterTraining"
#target_dir="/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/condor"
#target_dir="/scratch365/cmuelle2/selection_trees/nov22_ICHEP_trees"
#target_dir="/scratch365/cmuelle2/extraction_trees/nov22_ICHEP_trees"
target_dir="/scratch365/cmuelle2/bdt_test/"
#target_dir="/scratch365/cmuelle2/extraction_trees/nov22_ICHEP_trees_with_WgtHist"

files="$target_dir/$prefix*.root" 

#postfix="_genFilterTraining_2lss.root"
#postfix="_2lss_extraction.root"
#postfix="_2lss_selection.root"
postfix="_2lss_trainingSelection.root"
output="$target_dir/../$prefix$postfix"

export SCRAM_ARCH=slc6_amd64_gcc530
eval `scramv1 runtime -sh`

if  [ $prefix ]
then
    hadd $output $files
    if [ "$?" = "0" ]
    then
	rm -rf $files
	mv $output "$target_dir/"
    else
	rm -rf $output
	echo "$files not found"
	exit 1
    fi
else
    echo "$prefix is not a valid argument"
fi