

set year = "2012_53x"
#set zmask = "noZmask"
set zmask = "Zmask"
set charge = "OS"

#foreach zmask ("noZmask" "noZmask_lowPV" "noZmask_medPV" "noZmask_highPV")

foreach lepCat ("TwoMuon" "TwoEle" "MuonEle")
  cd $lepCat
  echo "Now in $PWD"
  foreach kind ( "eq2jeq2t" "eq3jeq2t" "ge4jeq2t" "ge3t" )
    set zjets_0pPartString = ""
    set zjets_1pPartString = ""
    set zjets_2pPartString = ""
    set zjets_3pPartString = ""
    set zjets_4pPartString = ""
    set zjets_lowmassPartString = ""

    set ttbarPartString = ""
    set ttbar_bbPartString = ""
    set ttbar_ccPartString = ""
    foreach iPart ("part1" "part2" "part3" "part4" "part5" "part6" "part7" "part8" "part9" "part10" "part11" "part12")
       set zjets_1pPartString = "${zjets_1pPartString} zjets_1p_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
       set zjets_3pPartString = "${zjets_3pPartString} zjets_3p_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
    end
    foreach iPart ("part1" "part2" "part3")
       set zjets_2pPartString = "${zjets_2pPartString} zjets_2p_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
    end
    foreach iPart ("part1" "part2" "part3" "part4" "part5" "part6" "part7")
       set zjets_4pPartString = "${zjets_4pPartString} zjets_4p_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
    end
    foreach iPart ("part1" "part2" "part3" "part4" "part5" "part6" "part7" "part8" "part9" "part10" "part11")
       set zjets_0pPartString = "${zjets_0pPartString} zjets_0p_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
       set zjets_lowmassPartString = "${zjets_lowmassPartString} zjets_lowmass_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
    end

    foreach iPart ("part1" "part2" "part3" "part4" "part5" "part6" "part7" "part8" "part9" "part10" "part11" "part12" "part13")
       set ttbarPartString = "${ttbarPartString} ttbar_ll_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
       set ttbar_bbPartString = "${ttbar_bbPartString} ttbar_bb_ll_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
       set ttbar_ccPartString = "${ttbar_ccPartString} ttbar_cc_ll_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
    end


    hadd  -f zjets_lowmass_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_lowmassPartString}
    hadd  -f zjets_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_0pPartString} ${zjets_1pPartString} ${zjets_2pPartString} ${zjets_3pPartString} ${zjets_4pPartString}

    hadd  -f wjets_${year}_${zmask}_${charge}_${kind}_${lepCat}.root wjets_1p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root wjets_2p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root  wjets_3p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root wjets_4p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root wjets_0p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root

    hadd  -f ttbar_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_jj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_lj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${ttbarPartString}
    hadd  -f ttbar_bb_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_bb_jj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_bb_lj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${ttbar_bbPartString}
    hadd  -f ttbar_cc_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_cc_jj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_cc_lj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${ttbar_ccPartString}

  end
  cd ..
end

#end
