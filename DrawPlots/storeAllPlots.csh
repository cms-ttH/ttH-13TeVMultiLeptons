./storePlots_justOne_threeTag.py -b TwoEle ge3t
echo "#############################################################################"
./storePlots_justOne_threeTag.py -b MuonEle ge3t
echo "#############################################################################"
./storePlots_justOne_threeTag.py -b TwoMuon ge3t
echo "#############################################################################"
./storePlots_justOne_twoTag.py -b TwoEle eq2jeq2t
echo "#############################################################################"
./storePlots_justOne_twoTag.py -b MuonEle eq2jeq2t
echo "#############################################################################"
./storePlots_justOne_twoTag.py -b TwoMuon eq2jeq2t
echo "#############################################################################"


hadd -f histosForLimits_AllLep_2011_ge3t.root histosForLimits_TwoEle_2011_ge3t.root histosForLimits_TwoMuon_2011_ge3t.root histosForLimits_MuonEle_2011_ge3t.root
hadd -f histosForLimits_AllLep_2011_e2je2t.root histosForLimits_TwoEle_2011_e2je2t.root histosForLimits_TwoMuon_2011_e2je2t.root histosForLimits_MuonEle_2011_e2je2t.root
hadd -f histosForLimits_AllLep_2011_AllTag.root histosForLimits_AllLep_2011_ge3t.root histosForLimits_AllLep_2011_e2je2t.root
