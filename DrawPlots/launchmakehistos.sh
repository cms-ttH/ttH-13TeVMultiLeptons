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

#myusername='muell149'
joblabel='v2'									# label for these batch jobs
logdir='batch_logs'									
#sourcebasedir="/eos/cms/store/user/$myusername/ttH-leptons_Skims"				# input trees base dir

sourcebasedir="/afs/cern.ch/work/g/gesmith/ttH_multilepton_ana/newrepo/lepid_updates/CMSSW_7_2_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test"

declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets' 'ZZJets') 	# list of samples
#declare -a samples=('ttH125')
#declare -a leptoncats=('mu_mu' 'mu_ele' 'ele_ele')
#declare -a jettagcats=('eq3j' 'ge4j')
declare -a leptoncats=('mumu2lss' 'ee2lss' 'emu2lss' '3l' '4l')
#declare -a leptoncats=('mumu2lss')
declare -a jettagcats=('ge2j')
pfx='root://eoscms.cern.ch/'								# prefix (can be xrootd, if you save certificate in afs area, see runonesshbatch.sh)

source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh

mkdir $logdir
logdir=$logdir/$joblabel
mkdir $logdir

thisdir=$(pwd)
cmsenvdir="$CMSSW_BASE/src"


pausetime=0.5

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
#		thislog="$logdir/${joblabel}_${sample}_${count}.log"
#
#		echo "-- submitting job $count --"
#		echo "input file: $fin"
#		echo "log file: $thislog"
#		echo "cmsenvdir: $cmsenvdir"
#		echo "thisdir: $thisdir"
#		echo "sample: $sample"
#		echo "leptoncat: $leptoncat"
#		echo "jettagcat: $jettagcat"
#		
#		leptoncat="dummy"
#		jettagcat="dummy"
#		
#		ssh -f lxplus "$thisdir/runonemakehistosbatch.sh $fin $thislog $cmsenvdir $thisdir $sample $leptoncat $jettagcat"
#		
#		sleep $interjobspacing
#		echo " "
#		innercount=$(expr $innercount + 1)
#
#		check=$(($count % pausejobs))
#		if [ $check -eq 0 ]
#		then
#			sleep $pausetime
#		fi
#			
#		
#	done
#	
#	echo " "
#	sleep $intersamplespacing
#
#done


################################################################################################
# simpler version. if you have multiple input files per sample, then should be straightforward to adapt..

for sample in "${samples[@]}"
do
	echo "starting $sample ..."
	echo " " 	
        	
        fin="$sourcebasedir/$sample.root" #this assumes there is one input file per sample!
        
        echo "input: $fin"
        
	for jettagcat in "${jettagcats[@]}"
	do
		for leptoncat in "${leptoncats[@]}"
		do
			thislog="$logdir/${joblabel}_${sample}_${leptoncat}_${jettagcat}.log"

			echo "-- submitting job $count --"
			echo "input file: $fin"
			echo "log file: $thislog"
			echo "cmsenvdir: $cmsenvdir"
			echo "thisdir: $thisdir"
			echo "sample: $sample"
			echo "leptoncat: $leptoncat"
			echo "jettagcat: $jettagcat"

			ssh -f lxplus "$thisdir/runonemakehistosbatch.sh $fin $thislog $cmsenvdir $thisdir $sample $leptoncat $jettagcat"
                        
                        sleep $pausetime
		done
	done
done
################################################################################################
