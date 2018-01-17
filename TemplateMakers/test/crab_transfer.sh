#!/bin/sh

# Script for use on lxplus to transfer output of completed crab jobs to ndpc disk. Need to source crab environment first.
# usage: ./crab_transfer.sh

user="gesmith"                                      # your user name
ndpc="ndpc6"                                        # the ndpc you are saving to
disk="disk2"                                        # disk on the ndpc

###########################################################
## only edit this section if you know what you are doing ##
whatToMount="$ndpc$disk/$user"
mkdir -p $whatToMount
sshfs -o cache=yes -o kernel_cache -o compression=no -o large_read -o Ciphers=arcfour $user@$ndpc:/mnt/$whatToMount/ $whatToMount
###########################################################

## crab commands ##

#outputSubDir="crab/EFT_test_19_12_17__ttH"               # subdirectory to save output to on ndpc disk. crab will create these if they don't exist. Note: this is the end of the path; i.e. crab will not create any other sub-directories).
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__ttH"   # crab project directory for these jobs
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
outputSubDir="crab/EFT_test_19_12_17__ttW"               
crabDir="crab_project_dir/crab_EFT_test_19_12_17__ttW"   
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__ttZ"                 
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__ttZ"   
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
##outputSubDir="crab/EFT_test_19_12_17__ttJets"                 
##crabDir="crab_project_dir/crab_EFT_test_19_12_17__ttJets"   
##crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__ttJets_SingleLeptFromT"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__ttJets_SingleLeptFromT"   
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-2761
#
#outputSubDir="crab/EFT_test_19_12_17__ttJets_SingleLeptFromTbar"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__ttJets_SingleLeptFromTbar"   
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-2665
#
#outputSubDir="crab/EFT_test_19_12_17__ttJets_Dilept"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__ttJets_Dilept"   
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1234
#
#outputSubDir="crab/EFT_test_19_12_17__DYJets_M50"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DYJets_M50"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-837
#
#outputSubDir="crab/EFT_test_19_12_17__DYJets_M10to50"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DYJets_M10to50"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-765
#
#
#outputSubDir="crab/EFT_test_19_12_17__WZ"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__WZ"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__ZZ"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__ZZ"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__WW"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__WW"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__WJets"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__WJets"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__SingleTop_tWchan_top"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleTop_tWchan_top"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__SingleTop_tWchan_antitop"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleTop_tWchan_antitop"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__SingleTop_tchan_top"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleTop_tchan_top"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__SingleTop_tchan_antitop"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleTop_tchan_antitop"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/EFT_test_19_12_17__SingleTop_schan"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleTop_schan"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/





###### Data #######

#outputSubDir="crab/EFT_test_19_12_17__DoubleMuon_Run2016H"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleMuon_Run2016H"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-989
#outputSubDir="crab/EFT_test_19_12_17__DoubleMuon_Run2016Bv2"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleMuon_Run2016Bv2"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-1677
#outputSubDir="crab/EFT_test_19_12_17__DoubleMuon_Run2016G"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleMuon_Run2016G"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-922
#outputSubDir="crab/EFT_test_19_12_17__DoubleMuon_Run2016D"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleMuon_Run2016D"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-686
#outputSubDir="crab/EFT_test_19_12_17__DoubleMuon_Run2016F"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleMuon_Run2016F"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="crab/EFT_test_19_12_17__DoubleMuon_Run2016C"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleMuon_Run2016C"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-569
#outputSubDir="crab/EFT_test_19_12_17__DoubleMuon_Run2016E"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleMuon_Run2016E"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-572
#outputSubDir="crab/EFT_test_19_12_17__DoubleMuon_Run2016Bv1"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleMuon_Run2016Bv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#
#outputSubDir="EFT_test_19_12_17__SingleMuon_Run2016Bv2"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleMuon_Run2016Bv2"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-3000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=3001-3259
#outputSubDir="EFT_test_19_12_17__SingleMuon_Run2016Bv1"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleMuon_Run2016Bv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="EFT_test_19_12_17__SingleMuon_Run2016F"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleMuon_Run2016F"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1359
#outputSubDir="EFT_test_19_12_17__SingleMuon_Run2016C"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleMuon_Run2016C"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1403
#outputSubDir="EFT_test_19_12_17__SingleMuon_Run2016D"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleMuon_Run2016D"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2030
#outputSubDir="EFT_test_19_12_17__SingleMuon_Run2016E"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleMuon_Run2016E"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-1887
#outputSubDir="EFT_test_19_12_17__SingleMuon_Run2016H"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleMuon_Run2016H"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-3000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=3001-3500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=3501-3614
#outputSubDir="EFT_test_19_12_17__SingleMuon_Run2016G"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleMuon_Run2016G"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-3000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=3001-3106
#
#
#
#
#outputSubDir="EFT_test_19_12_17__DoubleEG_Run2016Bv1"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleEG_Run2016Bv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="EFT_test_19_12_17__DoubleEG_Run2016D"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleEG_Run2016D"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1087
#outputSubDir="EFT_test_19_12_17__DoubleEG_Run2016G"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleEG_Run2016G"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-1606
#outputSubDir="EFT_test_19_12_17__DoubleEG_Run2016E"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleEG_Run2016E"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1016
#outputSubDir="EFT_test_19_12_17__DoubleEG_Run2016F"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleEG_Run2016F"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-705
#outputSubDir="EFT_test_19_12_17__DoubleEG_Run2016C"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleEG_Run2016C"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-980
#outputSubDir="EFT_test_19_12_17__DoubleEG_Run2016H"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleEG_Run2016H"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-1739
#outputSubDir="EFT_test_19_12_17__DoubleEG_Run2016Bv2"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__DoubleEG_Run2016Bv2"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-2937
#
#
#
#
#
#outputSubDir="EFT_test_19_12_17__SingleElectron_Run2016H"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleElectron_Run2016H"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-2655
#outputSubDir="EFT_test_19_12_17__SingleElectron_Run2016Bv1"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleElectron_Run2016Bv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="EFT_test_19_12_17__SingleElectron_Run2016D"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleElectron_Run2016D"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-3000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=3001-3130
#outputSubDir="EFT_test_19_12_17__SingleElectron_Run2016G"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleElectron_Run2016G"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-3000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=3001-3181
#outputSubDir="EFT_test_19_12_17__SingleElectron_Run2016C"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleElectron_Run2016C"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2059
#outputSubDir="EFT_test_19_12_17__SingleElectron_Run2016Bv2"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleElectron_Run2016Bv2"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2501-3000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=3001-3500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=3501-4000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=4001-4500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=4501-5000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=5001-5173
#outputSubDir="EFT_test_19_12_17__SingleElectron_Run2016E"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleElectron_Run2016E"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2461
#outputSubDir="EFT_test_19_12_17__SingleElectron_Run2016F"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__SingleElectron_Run2016F"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1473
#
#
#
#outputSubDir="EFT_test_19_12_17__MuonEG_Run2016G"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__MuonEG_Run2016G"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-685
#outputSubDir="EFT_test_19_12_17__MuonEG_Run2016Bv1"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__MuonEG_Run2016Bv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="EFT_test_19_12_17__MuonEG_Run2016C"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__MuonEG_Run2016C"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="EFT_test_19_12_17__MuonEG_Run2016E"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__MuonEG_Run2016E"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="EFT_test_19_12_17__MuonEG_Run2016H"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__MuonEG_Run2016H"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-589
#outputSubDir="EFT_test_19_12_17__MuonEG_Run2016D"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__MuonEG_Run2016D"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="EFT_test_19_12_17__MuonEG_Run2016F"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__MuonEG_Run2016F"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#outputSubDir="EFT_test_19_12_17__MuonEG_Run2016Bv2"
#crabDir="crab_project_dir/crab_EFT_test_19_12_17__MuonEG_Run2016Bv2"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-659


## do not remove this ##
fusermount -u $whatToMount
