#!/bin/sh

# Script for use on lxplus to transfer output of completed crab jobs to ndpc disk. Need to source crab environment first.
# usage: ./crab_transfer.sh

user="gesmith"                                      # your user name
ndpc="ndpc5"                                        # the ndpc you are saving to
disk="disk2"                                        # disk on the ndpc

###########################################################
## only edit this section if you know what you are doing ##
whatToMount="$ndpc$disk/$user"
mkdir -p $whatToMount
sshfs -o cache=yes -o kernel_cache -o compression=no -o large_read -o Ciphers=arcfour $user@$ndpc:/mnt/$whatToMount/ $whatToMount
###########################################################

## crab commands ##

#outputSubDir="crab/EFT_test_14_11_17__ttH"               # subdirectory to save output to on ndpc disk. crab will create these if they don't exist. Note: this is the end of the path; i.e. crab will not create any other sub-directories).
#crabDir="crab_project_dir/crab_EFT_test_14_11_17__ttH"   # crab project directory for these jobs
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/



## MET PDs for trigger studies
#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017A_PRv1"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017A_PRv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017A_PRv2"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017A_PRv2"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017A_PRv3"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017A_PRv3"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017B_PRv1"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017B_PRv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017B_PRv2"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017B_PRv2"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017C_PRv1"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017C_PRv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/
#
#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017C_PRv2"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017C_PRv2"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500     # crab only lets you do 500 at a time for some reason
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-539

outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017C_PRv3"
crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017C_PRv3"
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-559

#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017D_PRv1"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017D_PRv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/

outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017E_PRv1"
crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017E_PRv1"
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500

#outputSubDir="crab/crab_trigSF2017_test_28_11_17/MET_2017F_PRv1"
#crabDir="crab_project_dir/crab_trigSF2017_test_28_11_17__MET_2017F_PRv1"
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1-500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=501-1000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1001-1500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=1501-2000
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2001-2500
#crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/ --jobids=2500-2778





## do not remove this ##
fusermount -u $whatToMount
