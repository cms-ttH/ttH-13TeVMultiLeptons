#!/bin/sh


#myusername='gesmith'
joblabel='ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150612_095852/0000'									                # label for these batch jobs			
#sourcebasedir="/eos/cms/store/user/$myusername/crabdir"					# input trees base dir
#sourcebasedir="/eos/cms/store/user/muell149/ttH-leptons_Skims"
sourcebasedir="/eos/cms/store/user/gesmith/crab3dir"
destbasedir="."					


#declare -a samples=('ttH125' 'ttJets' 'ttwJets' 'ttzJets' 'wJets' 'wzJets' 'zJets' 'zzJets') # charlie
#declare -a samples=('ttH125')
declare -a samples=('test2ttH')

							                       
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets') 	        # list of samples
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets' 'ZZJets')
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
	
	#sourcedir=$sourcebasedir/$joblabel/$sample
	sourcedir=$sourcebasedir/$sample/$joblabel
        infilearray=($(eos ls $sourcedir/\*.root))
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
  	fout="$destdir/${sample}_temp.root"

	echo "-- submitting job $count --"
	echo "input file: ${infilearray[@]}"
	echo "output file: $fout"

        hadd -f -T $fout ${infilearray[@]}
done 

for sample in "${samples[@]}"
do

    python printInitialWgtdMCEvents.py ${sample}_temp.root
    
done


########


#for sample in "${samples[@]}"
#do
#
#    mv ${sample}_temp.root ${sample}.root
#    
#done



#mv ttJets.root TTJets.root
#mv ttwJets.root TTWJets.root
#mv ttzJets.root TTZJets.root
#mv wJets.root WJets.root
#mv wzJets.root WZJets.root
#mv zJets.root ZJets.root
#mv zzJets.root ZZJets.root
