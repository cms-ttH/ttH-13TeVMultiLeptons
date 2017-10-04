#!/bin/sh

#root -l -b -q makeEFTSelectionTree.C+\(\"ttW\"\)
#root -l -b -q makeEFTSelectionTree.C+\(\"ttW_extn\"\)
#root -l -b -q makeEFTSelectionTree.C+\(\"ttZ\"\)
#root -l -b -q makeEFTSelectionTree.C+\(\"ttZ_M1_10\"\)
#root -l -b -q makeEFTSelectionTree.C+\(\"tth_nonbb_aMCatNLO_\"\)
#root -l -b -q makeEFTSelectionTree.C+\(\"WZ_to3lnu\"\)
#root -l -b -q makeEFTSelectionTree.C+\(\"ZZ_to4l\"\)
#root -l -b -q makeEFTSelectionTree.C+\(\"WW_2l2nu\"\)

root -l -b -q makeEFTSelectionTree.C+\(\""ttZ"\",14,30\)
root -l -b -q makeEFTSelectionTree.C+\(\""ttZ"\",12,30\)
root -l -b -q makeEFTSelectionTree.C+\(\""ttZ"\",16,30\)
root -l -b -q makeEFTSelectionTree.C+\(\""ttZ"\",17,30\)
root -l -b -q makeEFTSelectionTree.C+\(\""ttZ"\",24,30\)

root -l -b -q makeEFTSelectionTree.C+\(\""tth_nonbb_aMCatNLO_"\",21,30\)
root -l -b -q makeEFTSelectionTree.C+\(\""tth_nonbb_aMCatNLO_"\",4,30\)


#root -l -b -q makeEFTSelectionTree.C+\(\""ttW"\",39,75\)