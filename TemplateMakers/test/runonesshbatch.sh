#!/bin/sh

## meant to be used as part of non-interactive ssh job

infile=$1
outfile=$2
logfile=$3
cmsenvdir=$4
thisdir=$5

export SCRAM_ARCH=slc6_amd64_gcc481
source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh
#cd /afs/cern.ch/work/g/gesmith/ttH_multilepton_ana/newrepo/newversionofAna_check_out_for_first_time/CMSSW_7_2_3/src
cd $cmsenvdir
eval `scramv1 runtime -sh`
#cd ttH-13TeVMultiLeptons/TemplateMakers/test #this should not change
cd $thisdir

# Note:
# To use xrootd, first do grid-proxy-init locally, then cp /tmp/x509up_u11231 ~/proxies/x509up_u11231. Then, uncomment this line here:
# export X509_USER_PROXY=/afs/cern.ch/user/g/gesmith/proxies/x509up_u11231
# where you have replaced x509up_u11231 with the name of your cert file (it will start with x509)

#actually run the job:
python addvarstotree.py -b $infile $outfile >& $logfile
