#! /bin/csh

crab -create -cfg crab_ttH125.cfg
crab -submit
crab -create -cfg crab_ttjets.cfg
crab -submit
crab -create -cfg crab_ttwjets.cfg 
crab -submit 
crab -create -cfg crab_ttzjets.cfg
crab -submit
crab -create -cfg crab_wzjets.cfg
crab -submit
crab -create -cfg crab_zzjets.cfg
crab -submit
crab -create -cfg crab_zjets.cfg
crab -submit
crab -create -cfg crab_wjets.cfg
crab -submit
