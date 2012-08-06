
foreach lepCat ("TwoMuon" "TwoEle" "MuonEle")
  cd $lepCat
  echo "Now in $PWD"
  foreach kind ("eq2jeq2t" "eq1t" "ge3jeq2t" "ge3t" )
     hadd -f zjets_${kind}_${lepCat}.root zjets_part1_${kind}_${lepCat}.root zjets_part2_${kind}_${lepCat}.root zjets_part3_${kind}_${lepCat}.root zjets_part4_${kind}_${lepCat}.root zjets_part5_${kind}_${lepCat}.root zjets_part6_${kind}_${lepCat}.root zjets_part7_${kind}_${lepCat}.root zjets_part8_${kind}_${lepCat}.root zjets_part9_${kind}_${lepCat}.root zjets_part10_${kind}_${lepCat}.root zjets_part11_${kind}_${lepCat}.root  zjets_part12_${kind}_${lepCat}.root
  end
  cd ..
end
