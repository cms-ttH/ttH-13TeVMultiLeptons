if (! -d "TwoLep") then
  mkdir TwoLep
endif
if (! -d "SameLep") then
  mkdir SameLep
endif
set charge = "OS"
#foreach mask ("Zmask" "noZmask" "Zpeak")
#foreach mask ( "noZmask" "noZmask_lowPV" "noZmask_medPV" "noZmask_highPV")
foreach mask ( "Zmask" )
#foreach year ("2011" "2012")
foreach year ("2012_53x")
foreach jetCat ("eq2jeq2t" "eq3jeq2t" "ge4jeq2t" "ge3t" )
#foreach jetCat ("eq2jeq2t" "ge3t")
  echo "Processing ${year}_${mask}_${jetCat}"
#  hadd -v 0 -f SameLep/SameLep_${year}_${mask}_${jetCat}_SameLep.root TwoMuon/DoubleMu_${year}_${mask}_${jetCat}_TwoMuon.root TwoEle/DoubleElectron_${year}_${mask}_${jetCat}_TwoEle.root  
  hadd -v 0 -f TwoLep/TwoLep_${year}_${mask}_${charge}_${jetCat}_TwoLep.root MuonEle/MuEG_${year}_${mask}_${charge}_${jetCat}_MuonEle.root TwoMuon/DoubleMu_${year}_${mask}_${charge}_${jetCat}_TwoMuon.root TwoEle/DoubleElectron_${year}_${mask}_${charge}_${jetCat}_TwoEle.root
  foreach sample ("singlet_s" "singlet_tW" "singlet_t" "singletbar_s" "singletbar_tW" "singletbar_t" "ttbarW" "ttbarZ" "ttbar_bb" "ttbar_cc" "ttbar" "wjets" "zjets" "zjets_lowmass" "ww" "wz" "zz" "ttH110" "ttH115" "ttH120" "ttH125" "ttH130" "ttH135" "ttH140")
 #   hadd -v 0 -f SameLep/${sample}_${year}_${mask}_${jetCat}_SameLep.root TwoMuon/${sample}_${year}_${mask}_${jetCat}_TwoMuon.root TwoEle/${sample}_${year}_${mask}_${jetCat}_TwoEle.root
    hadd -v 0 -f TwoLep/${sample}_${year}_${mask}_${charge}_${jetCat}_TwoLep.root MuonEle/${sample}_${year}_${mask}_${charge}_${jetCat}_MuonEle.root TwoMuon/${sample}_${year}_${mask}_${charge}_${jetCat}_TwoMuon.root TwoEle/${sample}_${year}_${mask}_${charge}_${jetCat}_TwoEle.root
  end
  echo "Removing cross sample files"
  rm -f TwoMuon/DoubleElectron_${year}_${mask}_${charge}_${jetCat}_TwoMuon.root
  rm -f TwoMuon/MuEG_${year}_${mask}_${charge}_${jetCat}_TwoMuon.root
  rm -f TwoEle/DoubleMu_${year}_${mask}_${charge}_${jetCat}_TwoEle.root
  rm -f TwoEle/MuEG_${year}_${mask}_${charge}_${jetCat}_TwoEle.root
  rm -f MuonEle/DoubleMu_${year}_${mask}_${charge}_${jetCat}_MuonEle.root
  rm -f MuonEle/DoubleElectron_${year}_${mask}_${charge}_${jetCat}_MuonEle.root
end	  
end
end
