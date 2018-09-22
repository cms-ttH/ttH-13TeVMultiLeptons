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
    scaledFit.scale(weight/2000.); // div by # of gridpacks
    return scaledFit;
}