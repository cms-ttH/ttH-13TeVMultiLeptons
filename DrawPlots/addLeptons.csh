if (! -d "TwoLep") then
  mkdir TwoLep
endif
if (! -d "SameLep") then
  mkdir SameLep
endif
#foreach mask ("Zmask" "noZmask" "Zpeak")
foreach mask ( "noZmask" )
#foreach year ("2011" "2012")
foreach year ("2012")
#foreach jetCat ("eq1t" "eq2jeq2t" "ge3jeq2t" "ge3t")
foreach jetCat ("eq2jeq2t" "ge3t")
  hadd -f SameLep/SameLep_${year}_${mask}_${jetCat}_SameLep.root TwoMuon/DoubleMu_${year}_${mask}_${jetCat}_TwoMuon.root TwoEle/DoubleElectron_${year}_${mask}_${jetCat}_TwoEle.root  
  hadd -f TwoLep/TwoLep_${year}_${mask}_${jetCat}_TwoLep.root MuonEle/MuEG_${year}_${mask}_${jetCat}_MuonEle.root TwoMuon/DoubleMu_${year}_${mask}_${jetCat}_TwoMuon.root TwoEle/DoubleElectron_${year}_${mask}_${jetCat}_TwoEle.root
  foreach sample ("singlet_s" "singlet_tW" "singlet_t" "singletbar_s" "singletbar_tW" "singletbar_t" "ttH120" "ttbarW" "ttbarZ" "ttbar_bb" "ttbar_cc" "ttbar" "wjets" "ww" "wz" "zjets" "zjets_lowmass" "zz" "ttH110" "ttH115" "ttH125" "ttH130" "ttH135" "ttH140")
    hadd -f SameLep/${sample}_${year}_${mask}_${jetCat}_SameLep.root TwoMuon/${sample}_${year}_${mask}_${jetCat}_TwoMuon.root TwoEle/${sample}_${year}_${mask}_${jetCat}_TwoEle.root
    hadd -f TwoLep/${sample}_${year}_${mask}_${jetCat}_TwoLep.root MuonEle/${sample}_${year}_${mask}_${jetCat}_MuonEle.root TwoMuon/${sample}_${year}_${mask}_${jetCat}_TwoMuon.root TwoEle/${sample}_${year}_${mask}_${jetCat}_TwoEle.root
  end
  rm TwoMuon/DoubleElectron_${year}_${mask}_${jetCat}_TwoMuon.root
  rm TwoMuon/MuEG_${year}_${mask}_${jetCat}_TwoMuon.root
  rm TwoEle/DoubleMu_${year}_${mask}_${jetCat}_TwoEle.root
  rm TwoEle/MuEG_${year}_${mask}_${jetCat}_TwoEle.root
  rm MuonEle/DoubleMu_${year}_${mask}_${jetCat}_MuonEle.root
  rm MuonEle/DoubleElectron_${year}_${mask}_${jetCat}_MuonEle.root
end	  
end
end
