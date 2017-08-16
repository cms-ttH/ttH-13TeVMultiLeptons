#!/bin/sh

# "crawdad" v2, created by Geoff Smith
# 
# Use this on lxplus, after first doing grid proxy init
# 
# before using for first time, your .ssh/config should look like this:
# Host *
#	StrictHostKeyChecking no
#	GSSAPIAuthentication yes
#	GSSAPIDelegateCredentials yes
#	GSSAPITrustDNS yes
#	ForwardAgent yes
#
# then do kinit, then ./launchcmsRunbatchjobs.sh
# 
# **** You have to be on lxplus for this script to work! ****
# 


# ****** user params ************
myusername='gesmith'
joblabel='Moriond17_samps_for_EFT_tests_skim'									# label for these batch jobs	
ndpc="ndpc6"                                                                            # ndpc to push output to
ndpcDisk="/mnt/ndpc6disk1"		                                                # ndpc disk to push output to
interjobspacing=5 #5 									# seconds to wait before submitting next job
intersamplespacing=30 									# seconds to wait before submitting jobs for next sample
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets') 	# samples to run over (has to match array names in sampleLists.sh)
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'ZJets' 'WJets' 'WZJets')
#declare -a samples=('ttH125powheg')
#declare -a samples=('data2015DMET')
#declare -a samples=('ttWkevin')
#declare -a samples=('TTJets')
#declare -a samples=('TTJets_split_2lep')
#declare -a samples=('TTJets_split_1lepFromT' 'TTJets_split_1lepFromTBar') # 'TTJets_split_1lepFromTBar') # TTJets_split_1lepFromT
declare -a samples=('ttHToNonbb_M125_ttHtranche3_powheg_Moriond17' 'TTJets_split_1lepFromT' 'TTJets_split_1lepFromTBar')
#declare -a samples=('data2016DMET_ReReco_BthroughG')
#declare -a samples=('data2016DMET_Prompt_H')

# *******************************


#pfx='root://cms-xrd-global.cern.ch/' # which xroot rederict to use (if any)
#pfx='root://ndcms.crc.nd.edu/'
pfx='root://xrootd.ba.infn.it/'

#source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh
logdir='crawlog'
mkdir $logdir
logdir=$logdir/$joblabel
mkdir $logdir

thisdir=$(pwd)
source $thisdir/sampleLists.sh   # file containing lists of sample files
cmsenvdir="$CMSSW_BASE/src"
cp /tmp/x509up_u11231 ~/proxies/x509up_u11231

for sample in "${samples[@]}"
do
	echo "starting $sample ..."
	echo " " 	
	count=0	
		
	destdir=/tmp/$myusername/sshjobs/$joblabel/$sample
	echo "destdir: $destdir"
	echo " "
	
        finaldestdir=$ndpcDisk/$myusername/sshjobs/$joblabel/$sample        
        ssh -f $ndpc "mkdir -p $finaldestdir"
        echo "final dest dir: $finaldestdir"
        echo " "
        
        eval infilearray=(\$\{$sample\[\@\]\})
        echo "submitting ${#infilearray[@]} jobs"
        echo " "
        
	for fin in "${infilearray[@]}"
	do
  		fin=$pfx$fin
		count=$(expr $count + 1)
  		fout="$destdir/$count.root"
                ffout="$myusername@$ndpc:$finaldestdir/$count.root"
		thislog="$logdir/$sample$count.log"
		echo "-- submitting job $count --"
		echo "input file: $fin"
		echo "output file: $fout"
                echo "final output will be: $ffout"
		echo "log file: $thislog"
		ssh -f lxplus "$thisdir/runonesshbatch.sh $fin $fout $thislog $cmsenvdir $thisdir $ffout"
		sleep $interjobspacing
		echo " " 
	done
	echo " "
	sleep $intersamplespacing
done 


 
