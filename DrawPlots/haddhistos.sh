#!/bin/sh

label='os_v9'
histdir='histos/os_v9'

#declare -a samples=('ttH125' 'TTZJets' 'TTWJets' 'ZJets' 'WJets' 'WZJets', 'TTJets')
declare -a samples=('WZJets')
declare -a leptoncats=('mu_mu' 'mu_ele' 'ele_ele')
declare -a jettagcats=('eq3j' 'ge4j')
interjobspacing=1


for leptoncat in "${leptoncats[@]}"
do			
	for jettagcat in "${jettagcats[@]}"
	do
		for sample in "${samples[@]}"
		do
			filestohadd="$histdir/$leptoncat/${leptoncat}_${jettagcat}_${sample}_${label}*.root"
			target="$histdir/$leptoncat/${leptoncat}_${jettagcat}_${sample}_${label}.root"
			
			hadd $target $filestohadd
		
			sleep $interjobspacing
			echo " "
		done
	done

done 
