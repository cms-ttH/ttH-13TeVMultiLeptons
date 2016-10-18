#!/bin/sh
echo $@
date
hostname
printenv

echo _CONDOR_JOB_AD $_CONDOR_JOB_AD
if [ ! -z "$_CONDOR_JOB_AD" ]
then
	cat ${_CONDOR_JOB_AD}
fi

sleep 180

