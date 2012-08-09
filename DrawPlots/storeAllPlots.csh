./storePlots_justOne_threeTag.py -b TwoEle ge3t > & ! logOfplots.log
./storePlots_justOne_threeTag.py -b MuonEle ge3t > & ! logOfplots.log
./storePlots_justOne_threeTag.py -b TwoMuon ge3t > & ! logOfplots.log
./storePlots_justOne_twoTag.py -b TwoEle eq2jeq2t > & ! logOfplots.log
./storePlots_justOne_twoTag.py -b MuonEle eq2jeq2t > & ! logOfplots.log
./storePlots_justOne_twoTag.py -b TwoMuon eq2jeq2t > & ! logOfplots.log


hadd -f histosForLimits_AllLep_ge3t.root histosForLimits_TwoEle_ge3t.root histosForLimits_TwoMuon_ge3t.root histosForLimits_MuonEle_ge3t.root
hadd -f histosForLimits_AllLep_e2je2t.root histosForLimits_TwoEle_e2je2t.root histosForLimits_TwoMuon_e2je2t.root histosForLimits_MuonEle_e2je2t.root
hadd -f histosForLimit_AllLep_AllTag.root histosForLimits_AllLep_ge3t.root histosForLimits_AllLep_e2je2t.root
