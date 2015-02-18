#!/bin/sh

# "crawdad" v1, created by Geoff Smith
# 
# Use this on lxplus
# if you don't have an eos store/user space,
# you can use store/temp/user, or anywhere else on lxplus
# before using for first time, your .ssh/config should look like this:
# Host *
#	StrictHostKeyChecking no
#	GSSAPIAuthentication yes
#	GSSAPIDelegateCredentials yes
#	GSSAPITrustDNS yes
#	ForwardAgent yes
#
# then do kinit
# 
# **** You have to be on lxplus and do kinit first for this script to work! ****
# 

myusername='gesmith'
joblabel='os_v9'									# label for these batch jobs
logdir='batch_logs'									
sourcebasedir="/eos/cms/store/user/$myusername/treedir/test1"				# input trees base dir
#destbasedir="/eos/cms/store/user/$myusername/treedir"					# output trees base dir
interjobspacing=1									# seconds to wait before submitting next job
pausetime=10										# pause this number of seconds each pausejobs
pausejobs=50										# take a quick pause after this number of jobs submitted
intersamplespacing=30 									# seconds to wait before submitting jobs for next sample
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets') 	# list of samples
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'ZJets' 'WJets' 'WZJets') # 'TTJets')
declare -a samples=('TTJets')
declare -a leptoncats=('mu_mu' 'mu_ele' 'ele_ele')
declare -a jettagcats=('eq3j' 'ge4j')
pfx='root://eoscms.cern.ch/'								# prefix (can be xrootd, if you save certificate in afs area, see runonesshbatch.sh)



source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh

mkdir $logdir
logdir=$logdir/$joblabel
mkdir $logdir

thisdir=$(pwd)
cmsenvdir="$CMSSW_BASE/src"

#for sample in "${samples[@]}"
#do
#	echo "starting $sample ..."
#	echo " " 	
#	count=0	
#	innercount=0
#	
#	sourcedir=$sourcebasedir/$sample
#	infilearray=($(eos ls $sourcedir))
#	sourcedir=$pfx$sourcedir
#	echo "sourcedir: $sourcedir"
#		
#	
#	for fin in "${infilearray[@]}"
#	do		
#		fin=$sourcedir/$fin
#		count=$(expr $count + 1)		
#		
#		for jettagcat in "${jettagcats[@]}"
#		do
#			for leptoncat in "${leptoncats[@]}"
#			do
#				thislog="$logdir/${joblabel}_${sample}_${leptoncat}_${jettagcat}_${count}.log"
#
#				echo "-- submitting job $count --"
#				echo "input file: $fin"
#				echo "log file: $thislog"
#				echo "cmsenvdir: $cmsenvdir"
#				echo "thisdir: $thisdir"
#				echo "sample: $sample"
#				echo "leptoncat: $leptoncat"
#				echo "jettagcat: $jettagcat"
#				#if [ $count -eq 22 ]
#				#then
#				ssh -f lxplus "$thisdir/runonemakehistosbatch.sh $fin $thislog $cmsenvdir $thisdir $sample $leptoncat $jettagcat"
#				#fi
#				sleep $interjobspacing
#				echo " "
#				innercount=$(expr $innercount + 1)
#				
#				check=$(($count % pausejobs))
#				if [ $check -eq 0 ]
#				then
#					sleep $pausetime
#				fi
#			done
#		done
#	done
#	
#	echo " "
#	sleep $intersamplespacing
#
#done

for sample in "${samples[@]}"
do
	echo "starting $sample ..."
	echo " " 	
	count=0	
	innercount=0
	
	sourcedir=$sourcebasedir/$sample
	infilearray=($(eos ls $sourcedir))
	sourcedir=$pfx$sourcedir
	echo "sourcedir: $sourcedir"
		
	
	for fin in "${infilearray[@]}"
	do		
		fin=$sourcedir/$fin
		count=$(expr $count + 1)		
		
		thislog="$logdir/${joblabel}_${sample}_${count}.log"

		echo "-- submitting job $count --"
		echo "input file: $fin"
		echo "log file: $thislog"
		echo "cmsenvdir: $cmsenvdir"
		echo "thisdir: $thisdir"
		echo "sample: $sample"
		echo "leptoncat: $leptoncat"
		echo "jettagcat: $jettagcat"
		
		leptoncat="dummy"
		jettagcat="dummy"
		
		ssh -f lxplus "$thisdir/runonemakehistosbatch.sh $fin $thislog $cmsenvdir $thisdir $sample $leptoncat $jettagcat"
		
		sleep $interjobspacing
		echo " "
		innercount=$(expr $innercount + 1)

		check=$(($count % pausejobs))
		if [ $check -eq 0 ]
		then
			sleep $pausetime
		fi
			
		
	done
	
	echo " "
	sleep $intersamplespacing

done
