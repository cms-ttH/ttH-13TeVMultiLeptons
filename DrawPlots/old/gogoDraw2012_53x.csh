
foreach kind ( "ge3t" "eq3jeq2t" "ge4jeq2t" "ge2t")
    echo "Plot for jet tag cat ${kind} ============================================="

    foreach lepCat ("TwoLep" ) ##"TwoMuon" "TwoEle" "MuonEle")
	echo "  ==>then for sublep cat ${lepCat} ==============================="

	./drawPlots2012_53x.py -b ${lepCat} ${kind}

end
end
