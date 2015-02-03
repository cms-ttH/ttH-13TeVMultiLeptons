set treeStr = "/afs/crc.nd.edu/user/w/wluo1/LHCP_2013/CMSSW_5_3_8_patch1/src/BEAN/DrawPlots/bin/treeFiles/dilSummaryTrees"
set year = "2012_53x"
set label = "limits_v1_all.root"
hadd -f bin/allMC.root ${treeStr}_singlet*${year}_${label} ${treeStr}_ttbar*${year}_${label} ${treeStr}_w*${year}_${label} ${treeStr}_z*${year}_${label}
cp ${treeStr}_DoubleMu_${year}_${label} bin/TwoMuon.root 
cp ${treeStr}_DoubleElectron_${year}_${label} bin/TwoEle.root 
cp ${treeStr}_MuEG_${year}_${label} bin/MuonEle.root  
