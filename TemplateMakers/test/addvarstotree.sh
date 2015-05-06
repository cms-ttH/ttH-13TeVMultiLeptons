#!/bin/sh


#myusername='gesmith'
#joblabel='v4'									                # label for these batch jobs			
#sourcebasedir="/eos/cms/store/user/$myusername/crabdir"					# input trees base dir
myusername='muell149'
joblabel='v2'									                # label for these batch jobs			
sourcebasedir="/eos/cms/store/user/$myusername/ttH-leptons_Skims"					# input trees base dir

destbasedir="."					
									                       
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets') 	        # list of samples
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets' 'ZZJets')
#declare -a samples=('ttH125')
#declare -a samples=('ttH125' 'ttzJets' 'ttwJets' 'ttJets' 'zJets' 'wJets' 'wzJets' 'zzJets')    # charlie
declare -a samples=('ttzJets' 'ttwJets' 'ttJets' 'zJets' 'wJets' 'wzJets' 'zzJets')
pfx='root://eoscms.cern.ch/'								        # prefix (can be xrootd, if you save certificate in afs area, see runonesshbatch.sh)

source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh

rootdestbasedir=$destbasedir
thisdir=$(pwd)

for sample in "${samples[@]}"
do
	echo "starting $sample ..."
	echo " "	
	
	sourcedir=$sourcebasedir/$joblabel/$sample	
        sourcedir=$pfx$sourcedir
        
	echo "sourcedir: $sourcedir"	
	
        destdir=$rootdestbasedir
        echo "destdir: $destdir"
	echo " "
	
  	fout="$destdir/$sample.root"

	echo "output file: $fout"
        
        addvarscommand="root -l -b -q addvarstotree.C+'(\""
        addvarscommand=$addvarscommand$sourcedir
        commandmiddle="/*.root\",\""
        addvarscommand=$addvarscommand$commandmiddle
        commandsuffix="\")'"
        addvarscommand=$addvarscommand$fout$commandsuffix
        
        #### non-batch
        #eval $addvarscommand
        ####
        
        #### batch
        #scramcommand="eval \`scramv1 runtime -sh\`"
        #ssh -f lxplus "export SCRAM_ARCH=slc6_amd64_gcc481; source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh; cd $thisdir; $scramcommand"
        ssh -f lxplus "cd $thisdir; cmsenv; $addvarscommand >& $sample.log"
        
        ####
done 
