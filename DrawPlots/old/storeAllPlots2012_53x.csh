set rootfileStr = ""

foreach lepCat ( "TwoMuon" "TwoEle" "MuonEle")
    echo "  Plot for sublep cat ${lepCat} ==================================="

    foreach kind ( "eq2jeq2t" "eq3jeq2t" "ge4jeq2t" "ge3t" )
	echo "  --> then for jet tag cat ${kind} ========================"

	./storePlots_justOne_53x.py -b ${lepCat} ${kind}

    end

    foreach jettag ( "e2je2t" "e3je2t" "ge4je2t" "ge3t" )
	set rootfileStr = "${rootfileStr} histosForLimits_${lepCat}_2012_53x_${jettag}.root"
    end

end

hadd -f histosForLimits_AllLep_2012_53x_AllTag.root ${rootfileStr}

rm histosForLimits_TwoMuon_2012_53x_*.root
rm histosForLimits_TwoEle_2012_53x_*.root
rm histosForLimits_MuonEle_2012_53x_*.root
rm ratioHistFile.root
