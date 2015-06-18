#!/bin/sh

# makes c++ vectors of strings of the full paths to the ntuple files, organized by sample.
# usage: ./create_file_lists_cpp.sh >& sample_lists.h &

###################################################################

## base eos directory containing the samples:
#sourcebasedir="/eos/cms/store/user/gesmith/crab3dir/"
sourcebasedir="/eos/cms/store/user/muell149/ttH-leptons_Skims/"

## the crab 3 job that created these samples (directories start diverging from here):
#joblabel="test2ttH/"
joblabel="v3p1/"

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

pfx='root://eoscms.cern.ch/'


###################################################################
## actual script:

source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh

for sample in "${samples[@]}"
do

    sourcedir=$sourcebasedir/$joblabel/$sample
    
    sample=($(echo $sample | tr - _))
    
    echo "std::vector<std::string> $sample()"
    echo "{"
    echo "    std::vector<std::string> dummy;"
    echo "  "
    
    infilearray=($(eos find -f $sourcedir | grep -ie ".root"))

    for onefile in "${infilearray[@]}"
    do
        echo "    dummy.push_back(\"$pfx$onefile\");"
    done
    
    echo "  "
    echo "    return dummy;"  
    echo "}"    
    echo "  "
    echo "  "             
done

#it should go:
#
#std::vector<std::string> thestringvect;
#thestringvect.push_back ..., return thestringvect;
#TObjString *asdf = new TObjString("asdf")
#TList *thelistt = new TList()
#asdf->SetString(thestringvect[i].c_str())
#thelistt->Add(asdf)
#
#...
#
#thechain->Add(thelistt)

