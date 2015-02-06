#! /bin/csh

#crab -create -cfg crab_ttH125.cfg	#done
#crab -submit
crab -create -cfg crab_ttjets.cfg
crab -submit 500			#25M events; using ~1/5 of that
crab -create -cfg crab_ttwjets.cfg 
crab -submit 
crab -create -cfg crab_ttzjets.cfg
crab -submit
#crab -create -cfg crab_wzjets.cfg	#done
#crab -submit

## didn't finish setting this up yet:
#crab -create -cfg crab_zjets.cfg
#crab -submit
#crab -create -cfg crab_wjets.cfg
#crab -submit
