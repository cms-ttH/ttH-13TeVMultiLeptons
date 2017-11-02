#!/bin/sh
set subFile="run_EFTSelection.submit"

#sed -i 's/^sample = .*/sample = ttW/' $subFile
##condor_submit $subFile
##head $subFile
#echo ""
#
#sed -i 's/^sample = .*/sample = ttZ/' $subFile
##condor_submit $subFile
##head $subFile
#echo ""
#
#sed -i 's/^sample = .*/sample = tth_nonbb_aMCatNLO_/' $subFile
##condor_submit $subFile
##head $subFile
#echo ""
#
#sed -i 's/^sample = .*/sample = tth_aMC/' $subFile
##condor_submit $subFile
##head $subFile
#echo ""
#
#sed -i 's/^sample = .*/sample = ttjets_dilep/' $subFile
##condor_submit $subFile
##head $subFile
#echo ""
#
#sed -i 's/^sample = .*/sample = ttjets_semilep/' $subFile
##condor_submit $subFile
##head $subFile
#echo ""

#set samples = ("tth_aMC" "ttW" "ttZ")
#set samples = ("tth_aMC")
set samples = ("tth_aMC" "ttjets_dilep" "ttjets_semilep")

foreach sample ($samples)
    sed -i "s/^sample = .*/sample = ${sample}/" $subFile
    #head -n3 ${subFile}
    condor_submit $subFile
    echo ""
end
