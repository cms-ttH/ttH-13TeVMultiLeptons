#!/bin/sh


#myusername='gesmith'
joblabel='ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150612_095852/0000'									                # label for these batch jobs			
#sourcebasedir="/eos/cms/store/user/$myusername/crabdir"					# input trees base dir
#sourcebasedir="/eos/cms/store/user/muell149/ttH-leptons_Skims"
sourcebasedir="/eos/cms/store/user/gesmith/crab3dir"
destbasedir="."					


#declare -a samples=('ttH125' 'ttJets' 'ttwJets' 'ttzJets' 'wJets' 'wzJets' 'zJets' 'zzJets') # charlie
#declare -a samples=('ttH125')
#declare -a samples=('test2ttH')
							                       
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets') 	        # list of samples
#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'TTJets' 'ZJets' 'WJets' 'WZJets' 'ZZJets')



###################################################################

## base eos directory containing the samples:
#sourcebasedir="/eos/cms/store/user/gesmith/crab3dir/"
sourcebasedir="/eos/cms/store/user/muell149/ttH-leptons_Skims"

## the crab 3 job that created these samples (directories start diverging from here):
#joblabel="test2ttH/"
#joblabel="v4p2p1"
#joblabel="trigtest3"
joblabel="acceptance_study"


## the samples to look for (the order will probably eventually matter, but not now):
declare -a samples=(
    'ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8'
    'TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola'
    'DYJetsToLL_M-50_13TeV-madgraph-pythia8'
    'WJetsToLNu_13TeV-madgraph-pythia8-tauola'
    'TTWJets_Tune4C_13TeV-madgraph-tauola'
    'TTZJets_Tune4C_13TeV-madgraph-tauola'
    'WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola'
    'ZZTo4L_Tune4C_13TeV-powheg-pythia8'
)




###################################################################





pfx='root://eoscms.cern.ch/'

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
	#sourcedir=$sourcebasedir/$sample/$joblabel
        #infilearray=($(eos ls $sourcedir/\*.root))
	infilearray=($(eos find -f $sourcedir | grep -ie ".root"))
        sourcedir=$pfx$sourcedir/
        
	echo "sourcedir: $sourcedir"
		
	#destdir=$destbasedir/$joblabel/$sample
	#eos mkdir $destdir
	#destdir=$rootdestbasedir/$sample
	
        destdir=$rootdestbasedir
        echo "destdir: $destdir"
	echo " "
	
        #infilearray=(${infilearray[@]/#/$sourcedir})
        infilearray=(${infilearray[@]/#/$pfx})
        
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
