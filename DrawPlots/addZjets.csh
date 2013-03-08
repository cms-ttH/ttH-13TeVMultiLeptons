

set year = "2012_53x"
set zmask = "Zmask"
set charge = "OS"

#foreach zmask ("noZmask" "noZmask_lowPV" "noZmask_medPV" "noZmask_highPV")

foreach lepCat ("TwoMuon" "TwoEle" "MuonEle")
  cd $lepCat
  echo "Now in $PWD"
  #foreach kind ("eq1t" "eq2jeq2t" "eq3jeq2t" "ge4jeq2t" "ge3t" )
  #foreach kind ("eq2jeq2t" "eq2jeq0t" "eq2jeq1t" "eq2jge0t")
  #foreach kind ("eq0j" "eq2jeq0t" "eq2jeq1t" "eq3jeq1t")
  foreach kind ("eq2jeq2t" "eq3jeq2t" "ge4jeq2t" "ge3t" )
    set zjets_1pPartString = ""
    set zjets_2pPartString = ""
    set zjets_3pPartString = ""
    set zjets_4pPartString = ""
	set zjets_lowmassPartString = ""
#     set zjets_lowmass_1pPartString = ""
#     set zjets_lowmass_2pPartString = ""
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
       set zjets_lowmassPartString = "${zjets_lowmassPartString} zjets_lowmass_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
    end
#     foreach iPart ("part1" "part2" "part3" "part4" "part5" "part6" "part7" "part8" "part9")
#        set zjets_lowmass_1pPartString = "${zjets_lowmass_1pPartString} zjets_lowmass_1p_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
#     end
#     foreach iPart ("part1" "part2" "part3" "part4" "part5" "part6" "part7" "part8" "part9" "part10" "part11")
#        set zjets_lowmass_2pPartString = "${zjets_lowmass_2pPartString} zjets_lowmass_2p_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
#     end
    foreach iPart ("part1" "part2" "part3" "part4" "part5" "part6" "part7" "part8" "part9" "part10" "part11" "part12" "part13")
       set ttbarPartString = "${ttbarPartString} ttbar_ll_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
       set ttbar_bbPartString = "${ttbar_bbPartString} ttbar_bb_ll_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
       set ttbar_ccPartString = "${ttbar_ccPartString} ttbar_cc_ll_${iPart}_${year}_${zmask}_${charge}_${kind}_${lepCat}.root" 
    end

#     hadd -v 0 -f zjets_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjetsPartString}
#     hadd -v 0 -f ttbar_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${ttbarPartString}
#     #echo "hadd -f zjets_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjetsPartString}"
#     #echo "hadd -f ttbar_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${ttbarPartString}"
    hadd -v 0 -f zjets_1p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_1pPartString}
    hadd -v 0 -f zjets_2p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_2pPartString}
    hadd -v 0 -f zjets_3p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_3pPartString}
    hadd -v 0 -f zjets_4p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_4pPartString}
    hadd -v 0 -f zjets_lowmass_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_lowmassPartString}
#     hadd -v 0 -f zjets_lowmass_1p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_lowmass_1pPartString}
#     hadd -v 0 -f zjets_lowmass_2p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${zjets_lowmass_2pPartString}
	hadd -v 0 -f zjets_${year}_${zmask}_${charge}_${kind}_${lepCat}.root zjets_1p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root zjets_2p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root  zjets_3p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root zjets_4p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root
# 	hadd -v 0 -f zjets_lowmass_${year}_${zmask}_${charge}_${kind}_${lepCat}.root zjets_lowmass_1p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root zjets_lowmass_2p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root
	hadd -v 0 -f wjets_${year}_${zmask}_${charge}_${kind}_${lepCat}.root wjets_1p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root wjets_2p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root  wjets_3p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root wjets_4p_${year}_${zmask}_${charge}_${kind}_${lepCat}.root
    hadd -v 0 -f ttbar_ll_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${ttbarPartString}
    hadd -v 0 -f ttbar_bb_ll_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${ttbar_bbPartString}
    hadd -v 0 -f ttbar_cc_ll_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ${ttbar_ccPartString}
	hadd -v 0 -f ttbar_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_jj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_lj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_ll_${year}_${zmask}_${charge}_${kind}_${lepCat}.root
	hadd -v 0 -f ttbar_bb_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_bb_jj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_bb_lj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_bb_ll_${year}_${zmask}_${charge}_${kind}_${lepCat}.root
	hadd -v 0 -f ttbar_cc_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_cc_jj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_cc_lj_${year}_${zmask}_${charge}_${kind}_${lepCat}.root ttbar_cc_ll_${year}_${zmask}_${charge}_${kind}_${lepCat}.root

  end
  cd ..
end

#end
