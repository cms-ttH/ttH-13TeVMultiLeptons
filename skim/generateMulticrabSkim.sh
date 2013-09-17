#!/bin/bash

##########################################################################################
### Author........Nil Valls <nvallsve@nd.edu>                                          ###
### Created.......2012/10/28                                                           ###
### Modified......2012/11/01                                                           ###
### Description...This script will generate the multicrab output from a text file      ###
###    containing the pasted text from the ttH twiki tables containing the dataset     ###
###    information. The sample number must be in the first column, and the primary     ###
###    dataset in the second. The script will check DBS and figure out what dbs        ###
###    instance to find such PDS.                                                      ###
##########################################################################################

### User-defined parameters (change these as needed)
project="skimDilep_BEAN_GTV7G_V01_CV04"
workingDir="/afs/crc.nd.edu/user/a/awoodard/CMSSW_5_3_8_patch1/src/NtupleMaker/SkimDilep/BEAN_53xOn53x_V04_CV01"
pset="skimDilep_condor.py"
storageElement="T3_US_NotreDame"


##########################################################################################
### After this point, any modifications risk messing up the script. Hack responsibly!  ###
##########################################################################################
RED="\033[0;31m"
GRAY="\033[0;30m"
BLUE="\033[0;34m"
ORANGE="\033[0;33m"
PURPLE="\033[0;35m"
GREEN="\033[0;32m"
WHITE="\033[1;37m"
NOCOLOR="\e[0m"

#function echoWar(){ echo -e "$PURPLE$1$NOCOLOR"; }
#function echoInf(){ echo -e "$BLUE$1$NOCOLOR"; }
#function echoSuc(){ echo -e "$GREEN$1$NOCOLOR"; }
#function echoWar(){ echo -e "$PURPLE[ WARNING ] $1$NOCOLOR" >&2; exit 1; }
function echoWar(){ echo -e "$PURPLE[ WARNING ] $1$NOCOLOR" >&2; }
function echoErr(){ echo -e "$RED[  ERROR  ] $1$NOCOLOR" >&2; rm -rf "$tempfile" "$output"; exit 1; }

input="$1"
output="$2"
if [ -z "$input" ]; then echoErr "must provide input file as the first argument."; fi
if [ -z "$output" ]; then echoErr "must provide output file as the second argument."; fi
touch "$output" > /dev/null
if [ $? -ne 0 ]; then echoErr "output file '$output' unwritable."; fi

## Check that we have a valid proxy
proxyExpiration=`voms-proxy-info | grep timeleft | sed -e 's/.*:\ //g' -e 's/://g'`
if [[ $proxyExpiration -eq 0 ]]; then echo -n "[ ATTENTION ] You don't seem to have a valid proxy. Would you like to get one (Y) or skip the DBS instance autoquery (N)? ";
	read getProxy;
	while [[ "$getProxy" != "Y" ]] && [[ "$getProxy" != "y" ]] && [[ "$getProxy" != "N" ]] && [[ "$getProxy" != "n" ]]; do
		echo -n "Invalid answer, please say 'Y' or 'N': "; read getProxy;
	done
	if [[ "$getProxy" == "Y" ]] || [[ "$getProxy" == "y" ]]; then
		skipDBS=0;
		proxy=`voms-proxy-init -voms cms`
		if [ $? -ne 0 ]; then echoErr "Terminating."; fi
		echo "":
	else
		skipDBS=1;
	fi
fi


mkdir -p "/tmp/$USER/"
tempfile="/tmp/$USER/.samples_from_twiki"

## Parse input file into temp file
#grep 'AOD\|USER' $input | sed 's/AOD\s.*/AOD/' | sed 's/AODSIM\s.*/AODSIM/' | sed 's/USER\s.*/USER/' > "$tempfile"
grep 'USER' $input > "$tempfile"

## Common parts for multicrab
header="[MULTICRAB]
cfg                             = mcrab.cfg


[COMMON]
CRAB.jobtype                    = cmssw
CRAB.scheduler                  = condor
CRAB.cfg                        = crab.cfg
CRAB.jobtype                    = cmssw

CMSSW.pset                      = ${pset}
CMSSW.get_edm_output            = 1

USER.ui_working_dir             = $workingDir
USER.return_data                = 0
USER.copy_data                  = 1
USER.check_user_remote_dir      = 0
USER.storage_element            = ${storageElement}
USER.publish_data               = 1
USER.dbs_url_for_publication    = https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_01_writer/servlet/DBSServlet

GRID.proxy_server                    = myproxy.cern.ch
GRID.virtual_organization            = cms
GRID.rb                              = CERN
GRID.retry_count                     = 0
GRID.se_white_list                   = "


## This function echoes the first dbs instance where the input dataset is found (global, ph1, ph2)
function getDBSinstance(){
	if [[ $skipDBS -eq 1 ]]; then echo "<fill me>"; return; fi
	input_ds="$1";
	if [ -z "$input_ds" ]; then echoErr "getDBSinstance needs a dataset as argument"; fi

	urls=("http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
	"https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_01_writer/servlet/DBSServlet" \
	"https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet")

	for url in ${urls[@]}; do
			dbsout=`python $DBSCMD_HOME/dbsCommandLine.py -c search --url="$url" --query="find dataset where dataset=$input_ds" | grep "$input_ds"`
			#e="$?"; if [ $e -ne 0 ]; then echoErr "Problem with dbsCommandLine.py '$e'"; fi
			if [[ "$dbsout" == "$input_ds" ]]; then echo "$url"; return 0; fi
	done
	echo "";
	echoErr "dataset '$input_ds' not found in any DBS instance. Please check.";
}

function getRecoType(){
	ds="$1"
	dssub=`echo "$ds" | grep Run20 | sed -e 's/.*Run20....//' -e 's/\/AOD.*//'`

	if [ -z "$dssub" ]; then echoErr "Trying to obtain reco type for non collision dataset: $1"; fi

	promptreco=`echo "$dssub" | grep -i "PromptReco"`
	if [ ! -z "$promptreco" ]; then echo "PR"; return 0; fi

	recover=`echo "$dssub" | grep -i "recover"`
	if [ ! -z "$recover" ]; then echo "RRr"; return 0; fi

	echo "RR"; return 0;

}


## Function called for each task
function getBlock(){

	## Set up values
	DS="$1"
	NUM="$2"
	PARENT_DS="$4"
	DSU=`echo $PARENT_DS | sed "s/^\///" | sed "s/\//_/g" | sed "s/_AODSIM//g" | sed "s/_AOD//g" | sed "s/_USER//g"`

	## Determine era
	if [[ "$DS" == *Run2011* ]] || [[ "$DS" == *7TeV* ]]; then
		era="2011";
	elif [[ "$DS" == *Run2012* ]] || [[ "$DS" == *8TeV* ]]; then
		era="2012";
	fi

	## Determine subera
	  if [[ "$DS" == *Run${era}A* ]]; then 
		subEra="A";
	elif [[ "$DS" == *Run${era}B* ]]; then 
		subEra="B";
	elif [[ "$DS" == *Run${era}C* ]]; then 
		subEra="C";
	elif [[ "$DS" == *Run${era}D* ]]; then 
		subEra="D";
	fi

## Set up task
common="[$DSU]
CMSSW.datasetpath               = $DS
CMSSW.dbs_url                   = $(getDBSinstance $DS)
USER.publish_data_name          = ${DSU}_${project}"




if [[ "$PARENT_DS" == *Run20* ]]; then 
echo "$common
CMSSW.total_number_of_lumis     = -1
CMSSW.lumis_per_job             = 2000"
#CMSSW.pycfg_params              = jobParams=${era}_${subEra}_data-$(getRecoType $DS)_$NUM"
elif [[ "$DS" == */USER ]]; then 
echo "$common
CMSSW.total_number_of_events    = -1
CMSSW.events_per_job            = 1000000"
#CMSSW.pycfg_params              = jobParams=${era}_X_MC-bg_$NUM"
else
	echoErr "could not figure out sample type for '$DS'";
fi

	echo -ne "\n\n"
}


## Print the header
echo -ne "$header\n\n\n" > "$output"

## Print each task
echo "Found $(cat $tempfile | wc -l) datasets:"
while read line; do
	num=`echo $line | awk '{print $1}'`
	parent_ds=`echo $line | awk '{print $2}'`
	ds=`echo $line | awk '{print $4}'`
	echo -ne "${PURPLE}Preparing '${NOCOLOR}${ORANGE}$ds${PURPLE}'...${NOCOLOR}"
	getBlock "$ds" "$num" "$line" "$parent_ds" >> "$output"
	echo -e "${GREEN} done!${NOCOLOR}";
done < "$tempfile"

echo -e "\n${GREEN}\tAll done!\n${NOCOLOR}";


## Clean up
rm -rf "$tempfile"

#EOF
