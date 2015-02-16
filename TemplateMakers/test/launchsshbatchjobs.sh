#!/bin/sh

# "crawdad" v1, created by Geoff Smith
# 
# Use this on lxplus
# if you don't have an eos store/user space,
# you can use store/temp/user, or anywhere else on lxplus
# before using for first time, add the following line to ~/.ssh/
# 
# then do kinit
# 
# **** You have to be on lxplus and do kinit first for this script to work! ****
# 

myusername='gesmith'
joblabel='test1'									# label for these batch jobs			
sourcebasedir="/eos/cms/store/user/$myusername/crabdir"					# input trees base dir
destbasedir="/eos/cms/store/user/$myusername/treedir"					# output trees base dir
interjobspacing=2 									# seconds to wait before submitting next job
intersamplespacing=120 									# seconds to wait before submitting jobs for next sample
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets') 	# list of samples
declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'ZJets' 'WJets' 'WZJets')
pfx='root://eoscms.cern.ch/'								# prefix (can be xrootd, if you save certificate in afs area, see runonesshbatch.sh)

source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh
#alias eos="/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select"
eos mkdir $destbasedir/$joblabel
rootdestbasedir=$pfx$destbasedir/$joblabel
logdir='crawlog'
mkdir $logdir
logdir=$logdir/$joblabel
mkdir $logdir

thisdir=$(pwd)
cmsenvdir="$CMSSW_BASE/src"

for sample in "${samples[@]}"
do
	echo "starting $sample ..."
	echo " " 	
	count=0	
	
	sourcedir=$sourcebasedir/$sample
	infilearray=($(eos ls $sourcedir))
	sourcedir=$pfx$sourcedir
	echo "sourcedir: $sourcedir"
		
	destdir=$destbasedir/$joblabel/$sample
	eos mkdir $destdir
	destdir=$rootdestbasedir/$sample
	echo "destdir: $destdir"
	echo " "
	
	for fin in "${infilearray[@]}"
	do
  		fin=$sourcedir/$fin
		count=$(expr $count + 1)
  		fout="$destdir/$count.root"
		thislog="$logdir/$sample$count.log"
		echo "-- submitting job $count --"
		echo "input file: $fin"
		echo "output file: $fout"
		echo "log file: $thislog"
#  		ssh -f $myusername@lxplus 'bash -s' < "runonesshbatch.sh $fin $fout $thislog $cmsenvdir $thisdir"
		ssh -f lxplus "$thisdir/runonesshbatch.sh $fin $fout $thislog $cmsenvdir $thisdir"
		sleep $interjobspacing
		echo " " 
	done
	echo " "
	sleep $intersamplespacing
done 


 
