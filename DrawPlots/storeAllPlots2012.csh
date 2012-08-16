./storePlots_justOne_threeTag2012.py -b TwoEle ge3t
echo "#############################################################################"
./storePlots_justOne_threeTag2012.py -b MuonEle ge3t
echo "#############################################################################"
./storePlots_justOne_threeTag2012.py -b TwoMuon ge3t
echo "#############################################################################"
./storePlots_justOne_twoTag2012.py -b TwoEle eq2jeq2t
echo "#############################################################################"
./storePlots_justOne_twoTag2012.py -b MuonEle eq2jeq2t
echo "#############################################################################"
./storePlots_justOne_twoTag2012.py -b TwoMuon eq2jeq2t
echo "#############################################################################"

hadd -f histosForLimits_AllLep_2012_ge3t.root histosForLimits_TwoEle_2012_ge3t.root histosForLimits_TwoMuon_2012_ge3t.root histosForLimits_MuonEle_2012_ge3t.root
hadd -f histosForLimits_AllLep_2012_e2je2t.root histosForLimits_TwoEle_2012_e2je2t.root histosForLimits_TwoMuon_2012_e2je2t.root histosForLimits_MuonEle_2012_e2je2t.root
hadd -f histosForLimits_AllLep_2012_AllTag.root histosForLimits_AllLep_2012_ge3t.root histosForLimits_AllLep_2012_e2je2t.root
