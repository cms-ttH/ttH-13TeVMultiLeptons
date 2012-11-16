

set year = "2012"
set zmask = "noZmask"

#foreach zmask ("noZmask" "noZmask_lowPV" "noZmask_medPV" "noZmask_highPV")

foreach lepCat ("TwoMuon" "TwoEle" "MuonEle")
  cd $lepCat
  echo "Now in $PWD"
  foreach kind ("eq1t" "eq2jeq2t" "eq3jeq2t" "ge4jeq2t" "ge3t" )
    set zjetsPartString = ""
    set ttbarPartString = ""
    foreach iPart ("part1" "part2" "part3" "part4" "part5" "part6" "part7" "part8" "part9" "part10" "part11" "part12")
       set zjetsPartString = "${zjetsPartString} zjets_${iPart}_${year}_${zmask}_${kind}_${lepCat}.root" 
       set ttbarPartString = "${ttbarPartString} ttbar_${iPart}_${year}_${zmask}_${kind}_${lepCat}.root" 
    end

    hadd -f zjets_${year}_${zmask}_${kind}_${lepCat}.root ${zjetsPartString}
    hadd -f ttbar_${year}_${zmask}_${kind}_${lepCat}.root ${ttbarPartString}
    #echo "hadd -f zjets_${year}_${zmask}_${kind}_${lepCat}.root ${zjetsPartString}"
    #echo "hadd -f ttbar_${year}_${zmask}_${kind}_${lepCat}.root ${ttbarPartString}"
  end
  cd ..
end

#end
