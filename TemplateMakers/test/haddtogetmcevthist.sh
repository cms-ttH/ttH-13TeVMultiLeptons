#!/bin/sh


myusername='gesmith'
joblabel='v4'									                # label for these batch jobs			
sourcebasedir="/eos/cms/store/user/$myusername/crabdir"					# input trees base dir
destbasedir="."					
									                       
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets') 	        # list of samples
declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets' 'ZZJets')
pfx='root://eoscms.cern.ch/'								        # prefix (can be xrootd, if you save certificate in afs area, see runonesshbatch.sh)

source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh

rootdestbasedir=$destbasedir


thisdir=$(pwd)
cmsenvdir="$CMSSW_BASE/src"

for sample in "${samples[@]}"
do
	echo "starting $sample ..."
	echo " " 	
	count=0	
	
	sourcedir=$sourcebasedir/$joblabel/$sample
	infilearray=($(eos ls $sourcedir))
	sourcedir=$pfx$sourcedir/
        
	echo "sourcedir: $sourcedir"
		
	#destdir=$destbasedir/$joblabel/$sample
	#eos mkdir $destdir
	#destdir=$rootdestbasedir/$sample
	
        destdir=$rootdestbasedir
        echo "destdir: $destdir"
	echo " "
	
        infilearray=(${infilearray[@]/#/$sourcedir})
        
  	#fin=$sourcedir/$fin
	count=$(expr $count + 1)
  	fout="$destdir/$sample.root"

	echo "-- submitting job $count --"
	echo "input file: ${infilearray[@]}"
	echo "output file: $fout"

        hadd -T $fout ${infilearray[@]}
done 

for sample in "${samples[@]}"
do

    python printInitialWgtdMCEvents.py $sample.root
    
done
    
