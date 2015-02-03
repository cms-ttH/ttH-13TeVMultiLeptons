#!/bin/bash

## November 14 parameters
systFile=systsEnv_Nov14.txt
labelOrig_=Nov14_

SSttWvar=FinalBDT
threeLttWvar=FinalBDT
ttWvar=FinalBDT
threeLttZvar=FinalBDT
fourLttZvar=numMediumBJets
OSttZvar=BDT_zjets_ttbar

## Command line options
dimensionOpt=$1
dataOpt=$2
statOpt=$3
computeOpt=$4
blindOpt=$5
toysOpt=$6

dimensionOpt_=$1'_'
dataOpt_=$2'_'
statOpt_=$3'_'
label_=$labelOrig_$dimensionOpt_$dataOpt_$statOpt_

if [ "$dimensionOpt" = "-h" ] || [ "$dimensionOpt" = "-help" ]
then
	echo ""
	echo "###################################"
	echo "#######       HELP!!!       #######"
	echo "###################################"
	echo ""
	echo "generatePValue_ttV.sh is run as follows:"
	echo ""
	echo "./generatePValue_ttV.sh dimensionOpt dataOpt statOpt computeOpt blindOpt toysOpt"
	echo ""
	echo "dimensionOpt   takes values of '1D' or '2D', for generating 1D (ttW or ttZ) or 2D (ttW and ttZ) datacards"
	echo "dataOpt        takes values of 'realData', or 'bkgData', or 'sigBkgData', to use the real data or"
	echo "               a fake set of data from MC, with background only or SM signal plus background"
	echo "statOpt        takes values of 'noStat', 'someStat', 'ttHStat', or 'allStat' for bin-by-bin statistical uncertainties"
	echo "computeOpt     takes values of 'cardOnly' to only create the datacard, 'pVal' to compute the p-value,"
	echo "               'pValVerbose' to compute the p-value and include information on pulls, 'maxLike' to compute"
	echo "               the maximum likelihood signal strength, and 'maxLikeVerbose' to add pull information"
	echo "               'pVal' uses '-M HybridNew --testStat=PL --singlePoint 0 --onlyTestStat' as the combine command prefix"
	echo "               'maxLike' uses '-M MaxLikelihoodFit --minos all' as the combine command prefix"
	echo "blindOpt       takes values of 'blind' or 'unblind'"
	echo "               'blind' adds '-t -1 --expectSignal=1' to the combine command suffix"
	echo "toysOpt        takes values of 'toys' or 'noToys', to use or not use data to constrain systematics"
	echo "               'toys' adds '--toysFreq' to the combine command prefix"            
    echo ""
	echo "Here are some example commands:"
	echo ""
	echo "Only make 2D datacards with no stat uncertainties, don't compute any p-values:"
	echo "./generatePValue_ttV.sh 2D realData noStat cardOnly"
	echo ""
	echo "Compute 1D p-values with stat uncertainties, completely blind:"
	echo "./generatePValue_ttV.sh 1D realData allStat pVal blind noToys"
	echo ""
	echo "Compute 1D p-values and pulls with stat uncertainties, using data with signal fixed to 1"
	echo "./generatePValue_ttV.sh 1D realData allStat pValVerbose blind toys"
	echo ""
	echo "Compute 1D p-values and pulls with stat uncertainties, using data with signal unconstrained"
	echo "./generatePValue_ttV.sh 1D realData allStat pValVerbose unblind toys"
	
	exit
fi ##End of Help section

echo ""
echo "-----------------"
echo "Generating limits"
echo "-----------------"
echo ""

makeCardParamsOrig='--jet_tag --label'

## dimensionOpt
if [ "$dimensionOpt" = "1D" ]
then
	yamlSuffix=".yaml"
elif [ "$dimensionOpt" = "2D" ]
then
    yamlSuffix="_2D.yaml"
else
	echo "Invalid dimensionOpt! $dimensionOpt Exiting."
	exit
fi

## dataOpt
if [ "$dataOpt" = "realData" ]
then
	makeCardParamsData=$makeCardParamsOrig
elif [ "$dataOpt" = "bkgData" ]
then
	makeCardParamsData='--data_bkg '$makeCardParamsOrig
elif [ "$dataOpt" = "sigBkgData" ]
then
	makeCardParamsData='--data_sig_bkg '$makeCardParamsOrig
else
	echo "Invalid dataOpt! $dataOpt Exiting."
	exit
fi

## statOpt
if [ "$statOpt" = "noStat" ]
then
	makeCardParamsStat=$makeCardParamsData
elif [ "$statOpt" = "allStat" ]
then
	makeCardParamsStat='--stat_uncert=all '$makeCardParamsData
elif [ "$statOpt" = "someStat" ]
then
	makeCardParamsStat='--stat_uncert=some '$makeCardParamsData
elif [ "$statOpt" = "ttHStat" ]
then
	makeCardParamsStat='--stat_uncert=ttH '$makeCardParamsData
else
	echo "Invalid statOpt! $statOpt Exiting."
	exit
fi

makeCardParams=$makeCardParamsStat

echo ""
echo "-----------------"
echo "Making shape cards"
echo "-----------------"
echo ""

echo "Datacards will have label $label_"
echo ""
echo "Making datacards using the following commands:"
echo ""
echo "python makeShapeCards.py yaml/limit_configuration_SS_ttW_2t_lepCut$yamlSuffix $SSttWvar $systFile $makeCardParams 2t_$label_$SSttWvar"
echo "python makeShapeCards.py yaml/limit_configuration_3l_ttW_2t_lepCut$yamlSuffix $threeLttWvar $systFile $makeCardParams 2t_$label_$threeLttWvar"
echo "python makeShapeCards.py yaml/limit_configuration_3l_ttZ_2t_lepCut$yamlSuffix $threeLttZvar $systFile $makeCardParams 2t_$label_$threeLttZvar"
echo "python makeShapeCards.py yaml/limit_configuration_4l_ttZ_4l_lepCut$yamlSuffix $fourLttZvar $systFile $makeCardParams 4l_$label_$fourLttZvar"
echo "python makeShapeCards.py yaml/limit_configuration_OS_ttZ_2l_lepCut$yamlSuffix $OSttZvar $systFile $makeCardParams 2l_$label_$OSttZvar"

python makeShapeCards.py yaml/limit_configuration_SS_ttW_2t_lepCut$yamlSuffix $SSttWvar     $systFile $makeCardParams 2t_$label_$SSttWvar
python makeShapeCards.py yaml/limit_configuration_3l_ttW_2t_lepCut$yamlSuffix $threeLttWvar $systFile $makeCardParams 2t_$label_$threeLttWvar
python makeShapeCards.py yaml/limit_configuration_3l_ttZ_2t_lepCut$yamlSuffix $threeLttZvar $systFile $makeCardParams 2t_$label_$threeLttZvar
python makeShapeCards.py yaml/limit_configuration_4l_ttZ_4l_lepCut$yamlSuffix $fourLttZvar  $systFile $makeCardParams 4l_$label_$fourLttZvar
python makeShapeCards.py yaml/limit_configuration_OS_ttZ_2l_lepCut$yamlSuffix $OSttZvar     $systFile $makeCardParams 2l_$label_$OSttZvar

echo ""
echo "-----------------"
echo "Combining cards"
echo "-----------------"
echo ""

combineCards.py ND_cards/ttW_2lss_*_*j_bloose_2t_$label_$SSttWvar.card.txt            > ND_cards/cardComb/ttW_2lss_bloose_2t_$label_$SSttWvar.card.txt
combineCards.py ND_cards/ttW_3l_*j_bloose_2t_$label_$threeLttWvar.card.txt            > ND_cards/cardComb/ttW_3l_bloose_2t_$label_$threeLttWvar.card.txt
combineCards.py ND_cards/ttZ_3l_*j_bloose_2t_$label_$threeLttZvar.card.txt            > ND_cards/cardComb/ttZ_3l_bloose_2t_$label_$threeLttZvar.card.txt
combineCards.py ND_cards/ttZ_4l_ge1j_Z*_mht30_1bloose_4l_$label_$fourLttZvar.card.txt > ND_cards/cardComb/ttZ_4l_ge1j_mht30_1bloose_4l_$label_$fourLttZvar.card.txt
combineCards.py ND_cards/ttZ_2los_*j_*t_2l_$label_$OSttZvar.card.txt                  > ND_cards/cardComb/ttZ_2los_2l_$label_$OSttZvar.card.txt

combineCards.py ND_cards/ttW_2lss_*_*j_bloose_2t_$label_$SSttWvar.card.txt ND_cards/ttW_3l_*j_bloose_2t_$label_$threeLttWvar.card.txt            > ND_cards/cardComb/ttW_23l_2t_$label_$ttWvar.card.txt
combineCards.py ND_cards/ttZ_3l_*j_bloose_2t_$label_$threeLttZvar.card.txt ND_cards/ttZ_4l_ge1j_Z*_mht30_1bloose_4l_$label_$fourLttZvar.card.txt > ND_cards/cardComb/ttZ_34l_$label_$threeLttZvar.card.txt
combineCards.py ND_cards/ttZ_3l_*j_bloose_2t_$label_$threeLttZvar.card.txt ND_cards/ttZ_4l_ge1j_Z*_mht30_1bloose_4l_$label_$fourLttZvar.card.txt ND_cards/ttZ_2los_*j_*t_2l_$label_$OSttZvar.card.txt > ND_cards/cardComb/ttZ_234l_$label_$threeLttZvar.card.txt

if [ "$dimensionOpt" = "2D" ]
then
	combineCards.py ND_cards/ttW_2lss_*_*j_bloose_2t_$label_$SSttWvar.card.txt ND_cards/ttW_3l_*j_bloose_2t_$label_$threeLttWvar.card.txt ND_cards/ttZ_3l_*j_bloose_2t_$label_$threeLttZvar.card.txt ND_cards/ttZ_4l_ge1j_Z*_mht30_1bloose_4l_$label_$fourLttZvar.card.txt ND_cards/ttZ_2los_*j_*t_2l_$label_$OSttZvar.card.txt > ND_cards/cardComb/ttW_23l_ttZ_234l_$label_.card.txt
fi

if [ "$computeOpt" = "cardOnly" ]
then
	echo "Only making datacards. Exiting."
	exit
fi

echo ""
echo "-----------------"
echo "Computing limits"
echo "-----------------"
echo ""

## computeOpt
if [ "$computeOpt" = "pVal" ]
then
	combinePrefixCompute='-M HybridNew --testStat=PL --singlePoint 0 --onlyTestStat'
elif [ "$computeOpt" = "pValVerbose" ]
then
	combinePrefixCompute='-M HybridNew --testStat=PL --singlePoint 0 --onlyTestStat -v 2'
elif [ "$computeOpt" = "maxLike" ]
then
	combinePrefixCompute='-M MaxLikelihoodFit --minos all'
elif [ "$computeOpt" = "maxLikeVerbose" ]
then
	combinePrefixCompute='-M MaxLikelihoodFit --minos all -v 2'
else
	echo "Invalid computeOpt! $computeOpt Exiting."
	exit
fi

## blindOpt
if [ "$blindOpt" = "blind" ]
then
	combineSuffix='-t -1 --expectSignal=1'
elif [ "$blindOpt" = "unblind" ]
then
	combineSuffix=''
else
	echo "Invalid blindOpt! $blindOpt Exiting."
	exit
fi

## toysOpt
if [ "$toysOpt" = "noToys" ]
then
	combinePrefixToys=$combinePrefixCompute
elif [ "$toysOpt" = "toys" ]
then
	combinePrefixToys=$combinePrefixCompute' --toysFreq'
else
	echo "Invalid toysOpt! $toysOpt Exiting."
	exit
fi

combinePrefix=$combinePrefixToys

echo "Running the following combine command:"
echo "combine $combinePrefix ND_cards/cardComb/datacard.card.txt $combineSuffix"

## get proper version of combine
cd /afs/crc.nd.edu/user/a/abrinke1/CMSSW_6_1_1/src/HiggsAnalysis/CombinedLimit
eval `scramv1 runtime -sh`
cd -

echo "-----------------"
echo "SS ttW limits - "$SSttWvar
echo "-----------------"
combine $combinePrefix ND_cards/cardComb/ttW_2lss_bloose_2t_$label_$SSttWvar.card.txt $combineSuffix
echo "-----------------"
echo "3l ttW limits - "$threeLttWvar
echo "-----------------"
combine $combinePrefix ND_cards/cardComb/ttW_3l_bloose_2t_$label_$threeLttWvar.card.txt $combineSuffix
echo "-----------------"
echo "3l ttZ limits - "$threeLttZvar
echo "-----------------"
combine $combinePrefix ND_cards/cardComb/ttZ_3l_bloose_2t_$label_$threeLttZvar.card.txt $combineSuffix
echo "-----------------"
echo "4l ttZ limits - "$fourLttZvar
echo "-----------------"
combine $combinePrefix ND_cards/cardComb/ttZ_4l_ge1j_mht30_1bloose_4l_$label_$fourLttZvar.card.txt $combineSuffix
echo "-----------------"
echo "OS ttZ limits - "$OSttZvar
echo "-----------------"
combine $combinePrefix ND_cards/cardComb/ttZ_2los_2l_$label_$OSttZvar.card.txt $combineSuffix
echo "-----------------"
echo "SS and 3l ttW limits - "$ttWvar
echo "-----------------"
combine $combinePrefix ND_cards/cardComb/ttW_23l_2t_$label_$ttWvar.card.txt $combineSuffix
echo "-----------------"
echo "3l and 4l ttZ limits - "$threeLttZvar
echo "-----------------"
combine $combinePrefix ND_cards/cardComb/ttZ_34l_$label_$threeLttZvar.card.txt $combineSuffix
echo "-----------------"
echo "3l, 4l, and OS ttZ limits - "$threeLttZvar
echo "-----------------"
combine $combinePrefix ND_cards/cardComb/ttZ_234l_$label_$threeLttZvar.card.txt $combineSuffix

if [ "$dimensionOpt" = "2D" ]
then
	echo "-----------------"
	echo "3l, 4l, SS, and OS ttW and ttZ limits"
	echo "-----------------"
	combine $combinePrefix ND_cards/cardComb/ttW_23l_ttZ_234l_$label_.card.txt $combineSuffix
fi

eval `scramv1 runtime -sh`

# grep -H -r "ln Q_{Profile}" log.txt | cut -f2- -d'='
# echo 'scale=30;sqrt(3)' | bc
