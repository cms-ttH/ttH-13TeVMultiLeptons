WCFit HistMaker::getEventFit(double weight)
{
    
    // only go here if haven't done the fit yet for this event
    // because doing the fit is expensive:
    if (thisEventFit.getDim()<=0)
    {
        std::vector<WCPoint> event_wgts;

        // loop over reweight points saved in tree for this event:
        for (auto& kv: *eftwgts_intree)
        {
            WCPoint new_pt(kv.first,kv.second);
            //WCPoint new_pt(kv.first,kv.second / (*originalXWGTUP_intree));
            event_wgts.push_back(new_pt);
        }

        WCFit event_wgt_fit(event_wgts,""); // actually do the fit to the reweight points
        thisEventFit = event_wgt_fit; // copy to Histmaker member
    }
    
    WCFit scaledFit = thisEventFit; // only scale copy of Histmaker member
    if (sample==84) scaledFit.scale(weight/42223.); // div by # of gridpacks // 23000 // 13400 // 2000
    else if (sample==85) scaledFit.scale(weight/41739.);
    else if (sample==86) scaledFit.scale(weight/23164.);
    else if (sample==87) scaledFit.scale(weight/22914.);
    else if (sample==88) scaledFit.scale(weight/9214.);
    else scaledFit.scale(weight/2000.); // div by # of gridpacks // 23000 // 13400 // 2000
    return scaledFit;
}

/*

Current:
ttH = 11635083.000000
ttll = 11639292.000000
tllq = 11531232.000000
ttlnu = 11327774.000000

~11500000 / 500 = 23000

jan 21: should now be:
ttH: 4767495 + 4759495 + 1967500 + 9616993 = 21111483  -> / 500 = 42223
ttll: 4824000 + 4864000 + 1894000 = 11582000 -> / 500 = 23164
tllq: 4770500 + 4736000 + 1950500 = 11457000 -> / 500 = 22914
ttlnu: 4788500 + 4770000 + 1937000 + 9374000 = 20869500 -> / 500 = 41739

feb. 23:
tHq: ~5000000 -> / 500 = 10000
Mar3: actually 4606820 -> / 500 = 9214
*/