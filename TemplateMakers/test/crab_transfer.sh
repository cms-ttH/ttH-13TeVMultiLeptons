#!/bin/sh

# Script for use on lxplus to transfer output of completed crab jobs to ndpc disk. Need to source crab environment first.
# usage: ./crab_transfer.sh

user="gesmith"                                      # your user name
ndpc="ndpc5"                                        # the ndpc you are saving to
disk="disk1"                                        # disk on the ndpc

###########################################################
## only edit this section if you know what you are doing ##
whatToMount="$ndpc$disk/$user"
mkdir -p $whatToMount
sshfs -o cache=yes -o kernel_cache -o compression=no -o large_read -o Ciphers=arcfour $user@$ndpc:/mnt/$whatToMount/ $whatToMount
###########################################################

## crab commands ##

outputSubDir="crab/EFT_test_14_11_17__ttH"               # subdirectory to save output to on ndpc disk. crab will create these if they don't exist. Note: this is the end of the path; i.e. crab will not create any other sub-directories).
crabDir="crab_project_dir/crab_EFT_test_14_11_17__ttH"   # crab project directory for these jobs
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/

outputSubDir="crab/EFT_test_14_11_17__ttW"               
crabDir="crab_project_dir/crab_EFT_test_14_11_17__ttW"   
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/

outputSubDir="crab/EFT_test_14_11_17__ttZ"                 
crabDir="crab_project_dir/crab_EFT_test_14_11_17__ttZ"   
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/

outputSubDir="crab/EFT_test_14_11_17__ttJets"                 
crabDir="crab_project_dir/crab_EFT_test_14_11_17__ttJets"   
crab getoutput -d $crabDir --outputpath=$whatToMount/$outputSubDir/



## do not remove this ##
fusermount -u $whatToMount
