void MakeGoodPlot::standard_plots()
{
    
    GoodPlot *can1     = new GoodPlot("category_yields","darren"); // above
    GoodPlot *cancategory_yields_njets_nbjets     = new GoodPlot("category_yields_njets_nbjets","darren");
    
    GoodPlot *can2     = new GoodPlot("2los_ee__njets","darren");
    GoodPlot *can3     = new GoodPlot("2los_emu__njets","darren");
    GoodPlot *can4     = new GoodPlot("2los_mumu__njets","darren");
    GoodPlot *can5     = new GoodPlot("2los_sfz_ee__njets","darren");
    //GoodPlot *can6     = new GoodPlot("2los_sfz_emu__njets","darren");
    GoodPlot *can7     = new GoodPlot("2los_sfz_mumu__njets","darren");
    GoodPlot *can8     = new GoodPlot("2lss_p_ee__njets","darren");
    GoodPlot *can9     = new GoodPlot("2lss_p_emu__njets","darren");
    GoodPlot *can10     = new GoodPlot("2lss_p_mumu__njets","darren");
    GoodPlot *can11     = new GoodPlot("2lss_m_ee__njets","darren");
    GoodPlot *can12     = new GoodPlot("2lss_m_emu__njets","darren");
    GoodPlot *can13     = new GoodPlot("2lss_m_mumu__njets","darren");
    GoodPlot *can14     = new GoodPlot("3l_ppp__njets","darren");
    GoodPlot *can15     = new GoodPlot("3l_mmm__njets","darren");
    GoodPlot *can16     = new GoodPlot("3l_mix__njets","darren");
    GoodPlot *can17     = new GoodPlot("3l_mix_sfz__njets","darren");
    GoodPlot *can18     = new GoodPlot("ge4l__njets","darren");
    GoodPlot *can1l_mu__njets     = new GoodPlot("1l_mu__njets","darren");
    GoodPlot *can1l_e__njets     = new GoodPlot("1l_e__njets","darren");


    GoodPlot *can19     = new GoodPlot("2los_ee__nbjets","darren");
    GoodPlot *can20     = new GoodPlot("2los_emu__nbjets","darren");
    GoodPlot *can21     = new GoodPlot("2los_mumu__nbjets","darren");
    GoodPlot *can22     = new GoodPlot("2los_sfz_ee__nbjets","darren");
    //GoodPlot *can23     = new GoodPlot("2los_sfz_emu__nbjets","darren");
    GoodPlot *can24     = new GoodPlot("2los_sfz_mumu__nbjets","darren");
    GoodPlot *can25     = new GoodPlot("2lss_p_ee__nbjets","darren");
    GoodPlot *can26     = new GoodPlot("2lss_p_emu__nbjets","darren");
    GoodPlot *can27     = new GoodPlot("2lss_p_mumu__nbjets","darren");
    GoodPlot *can28     = new GoodPlot("2lss_m_ee__nbjets","darren");
    GoodPlot *can29     = new GoodPlot("2lss_m_emu__nbjets","darren");
    GoodPlot *can30     = new GoodPlot("2lss_m_mumu__nbjets","darren");
    GoodPlot *can31     = new GoodPlot("3l_ppp__nbjets","darren");
    GoodPlot *can32     = new GoodPlot("3l_mmm__nbjets","darren");
    GoodPlot *can33     = new GoodPlot("3l_mix__nbjets","darren");
    GoodPlot *can34     = new GoodPlot("3l_mix_sfz__nbjets","darren");
    GoodPlot *can35     = new GoodPlot("ge4l__nbjets","darren");   
    GoodPlot *can1l_mu__nbjets     = new GoodPlot("1l_mu__nbjets","darren");
    GoodPlot *can1l_e__nbjets     = new GoodPlot("1l_e__nbjets","darren");
    

    
    GoodPlot *can2los_ee__jetpt     = new GoodPlot("2los_ee__jetpt","darren");
    GoodPlot *can2los_emu__jetpt     = new GoodPlot("2los_emu__jetpt","darren");
    GoodPlot *can2los_mumu__jetpt     = new GoodPlot("2los_mumu__jetpt","darren");
    GoodPlot *can2los_sfz_ee__jetpt     = new GoodPlot("2los_sfz_ee__jetpt","darren");
    GoodPlot *can2los_sfz_mumu__jetpt     = new GoodPlot("2los_sfz_mumu__jetpt","darren");
    GoodPlot *can2lss_p_ee__jetpt     = new GoodPlot("2lss_p_ee__jetpt","darren");
    GoodPlot *can2lss_p_emu__jetpt     = new GoodPlot("2lss_p_emu__jetpt","darren");
    GoodPlot *can2lss_p_mumu__jetpt     = new GoodPlot("2lss_p_mumu__jetpt","darren");
    GoodPlot *can2lss_m_ee__jetpt     = new GoodPlot("2lss_m_ee__jetpt","darren");
    GoodPlot *can2lss_m_emu__jetpt     = new GoodPlot("2lss_m_emu__jetpt","darren");
    GoodPlot *can2lss_m_mumu__jetpt     = new GoodPlot("2lss_m_mumu__jetpt","darren");
    GoodPlot *can3l_ppp__jetpt     = new GoodPlot("3l_ppp__jetpt","darren");
    GoodPlot *can3l_mmm__jetpt     = new GoodPlot("3l_mmm__jetpt","darren");
    GoodPlot *can3l_mix__jetpt     = new GoodPlot("3l_mix__jetpt","darren");
    GoodPlot *can3l_mix_sfz__jetpt     = new GoodPlot("3l_mix_sfz__jetpt","darren");
    GoodPlot *cange4l__jetpt     = new GoodPlot("ge4l__jetpt","darren");
    GoodPlot *can1l_mu__jetpt     = new GoodPlot("1l_mu__jetpt","darren");
    GoodPlot *can1l_e__jetpt     = new GoodPlot("1l_e__jetpt","darren");

    GoodPlot *can2los_ee__jeteta     = new GoodPlot("2los_ee__jeteta","darren");
    GoodPlot *can2los_emu__jeteta     = new GoodPlot("2los_emu__jeteta","darren");
    GoodPlot *can2los_mumu__jeteta     = new GoodPlot("2los_mumu__jeteta","darren");
    GoodPlot *can2los_sfz_ee__jeteta     = new GoodPlot("2los_sfz_ee__jeteta","darren");
    GoodPlot *can2los_sfz_mumu__jeteta     = new GoodPlot("2los_sfz_mumu__jeteta","darren");
    GoodPlot *can2lss_p_ee__jeteta     = new GoodPlot("2lss_p_ee__jeteta","darren");
    GoodPlot *can2lss_p_emu__jeteta     = new GoodPlot("2lss_p_emu__jeteta","darren");
    GoodPlot *can2lss_p_mumu__jeteta     = new GoodPlot("2lss_p_mumu__jeteta","darren");
    GoodPlot *can2lss_m_ee__jeteta     = new GoodPlot("2lss_m_ee__jeteta","darren");
    GoodPlot *can2lss_m_emu__jeteta     = new GoodPlot("2lss_m_emu__jeteta","darren");
    GoodPlot *can2lss_m_mumu__jeteta     = new GoodPlot("2lss_m_mumu__jeteta","darren");
    GoodPlot *can3l_ppp__jeteta     = new GoodPlot("3l_ppp__jeteta","darren");
    GoodPlot *can3l_mmm__jeteta     = new GoodPlot("3l_mmm__jeteta","darren");
    GoodPlot *can3l_mix__jeteta     = new GoodPlot("3l_mix__jeteta","darren");
    GoodPlot *can3l_mix_sfz__jeteta     = new GoodPlot("3l_mix_sfz__jeteta","darren");
    GoodPlot *cange4l__jeteta     = new GoodPlot("ge4l__jeteta","darren");
    GoodPlot *can1l_mu__jeteta     = new GoodPlot("1l_mu__jeteta","darren");
    GoodPlot *can1l_e__jeteta     = new GoodPlot("1l_e__jeteta","darren");


    GoodPlot *can2los_ee__jetcsv     = new GoodPlot("2los_ee__jetcsv","darren");
    GoodPlot *can2los_emu__jetcsv     = new GoodPlot("2los_emu__jetcsv","darren");
    GoodPlot *can2los_mumu__jetcsv     = new GoodPlot("2los_mumu__jetcsv","darren");
    GoodPlot *can2los_sfz_ee__jetcsv     = new GoodPlot("2los_sfz_ee__jetcsv","darren");
    GoodPlot *can2los_sfz_mumu__jetcsv     = new GoodPlot("2los_sfz_mumu__jetcsv","darren");
    GoodPlot *can2lss_p_ee__jetcsv     = new GoodPlot("2lss_p_ee__jetcsv","darren");
    GoodPlot *can2lss_p_emu__jetcsv     = new GoodPlot("2lss_p_emu__jetcsv","darren");
    GoodPlot *can2lss_p_mumu__jetcsv     = new GoodPlot("2lss_p_mumu__jetcsv","darren");
    GoodPlot *can2lss_m_ee__jetcsv     = new GoodPlot("2lss_m_ee__jetcsv","darren");
    GoodPlot *can2lss_m_emu__jetcsv     = new GoodPlot("2lss_m_emu__jetcsv","darren");
    GoodPlot *can2lss_m_mumu__jetcsv     = new GoodPlot("2lss_m_mumu__jetcsv","darren");
    GoodPlot *can3l_ppp__jetcsv     = new GoodPlot("3l_ppp__jetcsv","darren");
    GoodPlot *can3l_mmm__jetcsv     = new GoodPlot("3l_mmm__jetcsv","darren");
    GoodPlot *can3l_mix__jetcsv     = new GoodPlot("3l_mix__jetcsv","darren");
    GoodPlot *can3l_mix_sfz__jetcsv     = new GoodPlot("3l_mix_sfz__jetcsv","darren");
    GoodPlot *cange4l__jetcsv     = new GoodPlot("ge4l__jetcsv","darren");
    GoodPlot *can1l_mu__jetcsv     = new GoodPlot("1l_mu__jetcsv","darren");
    GoodPlot *can1l_e__jetcsv     = new GoodPlot("1l_e__jetcsv","darren");


    GoodPlot *can2los_ee__leppt     = new GoodPlot("2los_ee__leppt","darren");
    GoodPlot *can2los_emu__leppt     = new GoodPlot("2los_emu__leppt","darren");
    GoodPlot *can2los_mumu__leppt     = new GoodPlot("2los_mumu__leppt","darren");
    GoodPlot *can2los_sfz_ee__leppt     = new GoodPlot("2los_sfz_ee__leppt","darren");
    GoodPlot *can2los_sfz_mumu__leppt     = new GoodPlot("2los_sfz_mumu__leppt","darren");
    GoodPlot *can2lss_p_ee__leppt     = new GoodPlot("2lss_p_ee__leppt","darren");
    GoodPlot *can2lss_p_emu__leppt     = new GoodPlot("2lss_p_emu__leppt","darren");
    GoodPlot *can2lss_p_mumu__leppt     = new GoodPlot("2lss_p_mumu__leppt","darren");
    GoodPlot *can2lss_m_ee__leppt     = new GoodPlot("2lss_m_ee__leppt","darren");
    GoodPlot *can2lss_m_emu__leppt     = new GoodPlot("2lss_m_emu__leppt","darren");
    GoodPlot *can2lss_m_mumu__leppt     = new GoodPlot("2lss_m_mumu__leppt","darren");
    GoodPlot *can3l_ppp__leppt     = new GoodPlot("3l_ppp__leppt","darren");
    GoodPlot *can3l_mmm__leppt     = new GoodPlot("3l_mmm__leppt","darren");
    GoodPlot *can3l_mix__leppt     = new GoodPlot("3l_mix__leppt","darren");
    GoodPlot *can3l_mix_sfz__leppt     = new GoodPlot("3l_mix_sfz__leppt","darren");
    GoodPlot *cange4l__leppt     = new GoodPlot("ge4l__leppt","darren");
    GoodPlot *can1l_mu__leppt     = new GoodPlot("1l_mu__leppt","darren");
    GoodPlot *can1l_e__leppt     = new GoodPlot("1l_e__leppt","darren");

    GoodPlot *can2los_ee__lep1pt     = new GoodPlot("2los_ee__lep1pt","darren");
    GoodPlot *can2los_emu__lep1pt     = new GoodPlot("2los_emu__lep1pt","darren");
    GoodPlot *can2los_mumu__lep1pt     = new GoodPlot("2los_mumu__lep1pt","darren");
    GoodPlot *can2los_sfz_ee__lep1pt     = new GoodPlot("2los_sfz_ee__lep1pt","darren");
    GoodPlot *can2los_sfz_mumu__lep1pt     = new GoodPlot("2los_sfz_mumu__lep1pt","darren");
    GoodPlot *can2lss_p_ee__lep1pt     = new GoodPlot("2lss_p_ee__lep1pt","darren");
    GoodPlot *can2lss_p_emu__lep1pt     = new GoodPlot("2lss_p_emu__lep1pt","darren");
    GoodPlot *can2lss_p_mumu__lep1pt     = new GoodPlot("2lss_p_mumu__lep1pt","darren");
    GoodPlot *can2lss_m_ee__lep1pt     = new GoodPlot("2lss_m_ee__lep1pt","darren");
    GoodPlot *can2lss_m_emu__lep1pt     = new GoodPlot("2lss_m_emu__lep1pt","darren");
    GoodPlot *can2lss_m_mumu__lep1pt     = new GoodPlot("2lss_m_mumu__lep1pt","darren");
    GoodPlot *can3l_ppp__lep1pt     = new GoodPlot("3l_ppp__lep1pt","darren");
    GoodPlot *can3l_mmm__lep1pt     = new GoodPlot("3l_mmm__lep1pt","darren");
    GoodPlot *can3l_mix__lep1pt     = new GoodPlot("3l_mix__lep1pt","darren");
    GoodPlot *can3l_mix_sfz__lep1pt     = new GoodPlot("3l_mix_sfz__lep1pt","darren");
    GoodPlot *cange4l__lep1pt     = new GoodPlot("ge4l__lep1pt","darren");
    GoodPlot *can1l_mu__lep1pt     = new GoodPlot("1l_mu__lep1pt","darren");
    GoodPlot *can1l_e__lep1pt     = new GoodPlot("1l_e__lep1pt","darren");

    GoodPlot *can2los_ee__lep2pt     = new GoodPlot("2los_ee__lep2pt","darren");
    GoodPlot *can2los_emu__lep2pt     = new GoodPlot("2los_emu__lep2pt","darren");
    GoodPlot *can2los_mumu__lep2pt     = new GoodPlot("2los_mumu__lep2pt","darren");
    GoodPlot *can2los_sfz_ee__lep2pt     = new GoodPlot("2los_sfz_ee__lep2pt","darren");
    GoodPlot *can2los_sfz_mumu__lep2pt     = new GoodPlot("2los_sfz_mumu__lep2pt","darren");
    GoodPlot *can2lss_p_ee__lep2pt     = new GoodPlot("2lss_p_ee__lep2pt","darren");
    GoodPlot *can2lss_p_emu__lep2pt     = new GoodPlot("2lss_p_emu__lep2pt","darren");
    GoodPlot *can2lss_p_mumu__lep2pt     = new GoodPlot("2lss_p_mumu__lep2pt","darren");
    GoodPlot *can2lss_m_ee__lep2pt     = new GoodPlot("2lss_m_ee__lep2pt","darren");
    GoodPlot *can2lss_m_emu__lep2pt     = new GoodPlot("2lss_m_emu__lep2pt","darren");
    GoodPlot *can2lss_m_mumu__lep2pt     = new GoodPlot("2lss_m_mumu__lep2pt","darren");
    GoodPlot *can3l_ppp__lep2pt     = new GoodPlot("3l_ppp__lep2pt","darren");
    GoodPlot *can3l_mmm__lep2pt     = new GoodPlot("3l_mmm__lep2pt","darren");
    GoodPlot *can3l_mix__lep2pt     = new GoodPlot("3l_mix__lep2pt","darren");
    GoodPlot *can3l_mix_sfz__lep2pt     = new GoodPlot("3l_mix_sfz__lep2pt","darren");
    GoodPlot *cange4l__lep2pt     = new GoodPlot("ge4l__lep2pt","darren");


    GoodPlot *can2los_ee__lepeta     = new GoodPlot("2los_ee__lepeta","darren");
    GoodPlot *can2los_emu__lepeta     = new GoodPlot("2los_emu__lepeta","darren");
    GoodPlot *can2los_mumu__lepeta     = new GoodPlot("2los_mumu__lepeta","darren");
    GoodPlot *can2los_sfz_ee__lepeta     = new GoodPlot("2los_sfz_ee__lepeta","darren");
    GoodPlot *can2los_sfz_mumu__lepeta     = new GoodPlot("2los_sfz_mumu__lepeta","darren");
    GoodPlot *can2lss_p_ee__lepeta     = new GoodPlot("2lss_p_ee__lepeta","darren");
    GoodPlot *can2lss_p_emu__lepeta     = new GoodPlot("2lss_p_emu__lepeta","darren");
    GoodPlot *can2lss_p_mumu__lepeta     = new GoodPlot("2lss_p_mumu__lepeta","darren");
    GoodPlot *can2lss_m_ee__lepeta     = new GoodPlot("2lss_m_ee__lepeta","darren");
    GoodPlot *can2lss_m_emu__lepeta     = new GoodPlot("2lss_m_emu__lepeta","darren");
    GoodPlot *can2lss_m_mumu__lepeta     = new GoodPlot("2lss_m_mumu__lepeta","darren");
    GoodPlot *can3l_ppp__lepeta     = new GoodPlot("3l_ppp__lepeta","darren");
    GoodPlot *can3l_mmm__lepeta     = new GoodPlot("3l_mmm__lepeta","darren");
    GoodPlot *can3l_mix__lepeta     = new GoodPlot("3l_mix__lepeta","darren");
    GoodPlot *can3l_mix_sfz__lepeta     = new GoodPlot("3l_mix_sfz__lepeta","darren");
    GoodPlot *cange4l__lepeta     = new GoodPlot("ge4l__lepeta","darren");
    GoodPlot *can1l_mu__lepeta     = new GoodPlot("1l_mu__lepeta","darren");
    GoodPlot *can1l_e__lepeta     = new GoodPlot("1l_e__lepeta","darren");


    GoodPlot *can2los_ee__met     = new GoodPlot("2los_ee__met","darren");
    GoodPlot *can2los_emu__met     = new GoodPlot("2los_emu__met","darren");
    GoodPlot *can2los_mumu__met     = new GoodPlot("2los_mumu__met","darren");
    GoodPlot *can2los_sfz_ee__met     = new GoodPlot("2los_sfz_ee__met","darren");
    GoodPlot *can2los_sfz_mumu__met     = new GoodPlot("2los_sfz_mumu__met","darren");
    GoodPlot *can2lss_p_ee__met     = new GoodPlot("2lss_p_ee__met","darren");
    GoodPlot *can2lss_p_emu__met     = new GoodPlot("2lss_p_emu__met","darren");
    GoodPlot *can2lss_p_mumu__met     = new GoodPlot("2lss_p_mumu__met","darren");
    GoodPlot *can2lss_m_ee__met     = new GoodPlot("2lss_m_ee__met","darren");
    GoodPlot *can2lss_m_emu__met     = new GoodPlot("2lss_m_emu__met","darren");
    GoodPlot *can2lss_m_mumu__met     = new GoodPlot("2lss_m_mumu__met","darren");
    GoodPlot *can3l_ppp__met     = new GoodPlot("3l_ppp__met","darren");
    GoodPlot *can3l_mmm__met     = new GoodPlot("3l_mmm__met","darren");
    GoodPlot *can3l_mix__met     = new GoodPlot("3l_mix__met","darren");
    GoodPlot *can3l_mix_sfz__met     = new GoodPlot("3l_mix_sfz__met","darren");
    GoodPlot *cange4l__met     = new GoodPlot("ge4l__met","darren");
    GoodPlot *can1l_mu__met     = new GoodPlot("1l_mu__met","darren");
    GoodPlot *can1l_e__met     = new GoodPlot("1l_e__met","darren");

    GoodPlot *can2los_ee__metphi     = new GoodPlot("2los_ee__metphi","darren");
    GoodPlot *can2los_emu__metphi     = new GoodPlot("2los_emu__metphi","darren");
    GoodPlot *can2los_mumu__metphi     = new GoodPlot("2los_mumu__metphi","darren");
    GoodPlot *can2los_sfz_ee__metphi     = new GoodPlot("2los_sfz_ee__metphi","darren");
    GoodPlot *can2los_sfz_mumu__metphi     = new GoodPlot("2los_sfz_mumu__metphi","darren");
    GoodPlot *can2lss_p_ee__metphi     = new GoodPlot("2lss_p_ee__metphi","darren");
    GoodPlot *can2lss_p_emu__metphi     = new GoodPlot("2lss_p_emu__metphi","darren");
    GoodPlot *can2lss_p_mumu__metphi     = new GoodPlot("2lss_p_mumu__metphi","darren");
    GoodPlot *can2lss_m_ee__metphi     = new GoodPlot("2lss_m_ee__metphi","darren");
    GoodPlot *can2lss_m_emu__metphi     = new GoodPlot("2lss_m_emu__metphi","darren");
    GoodPlot *can2lss_m_mumu__metphi     = new GoodPlot("2lss_m_mumu__metphi","darren");
    GoodPlot *can3l_ppp__metphi     = new GoodPlot("3l_ppp__metphi","darren");
    GoodPlot *can3l_mmm__metphi     = new GoodPlot("3l_mmm__metphi","darren");
    GoodPlot *can3l_mix__metphi     = new GoodPlot("3l_mix__metphi","darren");
    GoodPlot *can3l_mix_sfz__metphi     = new GoodPlot("3l_mix_sfz__metphi","darren");
    GoodPlot *cange4l__metphi     = new GoodPlot("ge4l__metphi","darren");
    GoodPlot *can1l_mu__metphi     = new GoodPlot("1l_mu__metphi","darren");
    GoodPlot *can1l_e__metphi     = new GoodPlot("1l_e__metphi","darren");

    GoodPlot *can2los_ee__numPVs     = new GoodPlot("2los_ee__numPVs","darren");
    GoodPlot *can2los_emu__numPVs     = new GoodPlot("2los_emu__numPVs","darren");
    GoodPlot *can2los_mumu__numPVs     = new GoodPlot("2los_mumu__numPVs","darren");
    GoodPlot *can2los_sfz_ee__numPVs     = new GoodPlot("2los_sfz_ee__numPVs","darren");
    GoodPlot *can2los_sfz_mumu__numPVs     = new GoodPlot("2los_sfz_mumu__numPVs","darren");
    GoodPlot *can2lss_p_ee__numPVs     = new GoodPlot("2lss_p_ee__numPVs","darren");
    GoodPlot *can2lss_p_emu__numPVs     = new GoodPlot("2lss_p_emu__numPVs","darren");
    GoodPlot *can2lss_p_mumu__numPVs     = new GoodPlot("2lss_p_mumu__numPVs","darren");
    GoodPlot *can2lss_m_ee__numPVs     = new GoodPlot("2lss_m_ee__numPVs","darren");
    GoodPlot *can2lss_m_emu__numPVs     = new GoodPlot("2lss_m_emu__numPVs","darren");
    GoodPlot *can2lss_m_mumu__numPVs     = new GoodPlot("2lss_m_mumu__numPVs","darren");
    GoodPlot *can3l_ppp__numPVs     = new GoodPlot("3l_ppp__numPVs","darren");
    GoodPlot *can3l_mmm__numPVs     = new GoodPlot("3l_mmm__numPVs","darren");
    GoodPlot *can3l_mix__numPVs     = new GoodPlot("3l_mix__numPVs","darren");
    GoodPlot *can3l_mix_sfz__numPVs     = new GoodPlot("3l_mix_sfz__numPVs","darren");
    GoodPlot *cange4l__numPVs     = new GoodPlot("ge4l__numPVs","darren");
    GoodPlot *can1l_mu__numPVs     = new GoodPlot("1l_mu__numPVs","darren");
    GoodPlot *can1l_e__numPVs     = new GoodPlot("1l_e__numPVs","darren");
    
    GoodPlot *can2los_ee__llmass     = new GoodPlot("2los_ee__llmass","darren");
    GoodPlot *can2los_emu__llmass     = new GoodPlot("2los_emu__llmass","darren");
    GoodPlot *can2los_mumu__llmass     = new GoodPlot("2los_mumu__llmass","darren");
    GoodPlot *can2los_sfz_ee__llmass     = new GoodPlot("2los_sfz_ee__llmass","darren");
    GoodPlot *can2los_sfz_mumu__llmass     = new GoodPlot("2los_sfz_mumu__llmass","darren");
    GoodPlot *can2lss_p_ee__llmass     = new GoodPlot("2lss_p_ee__llmass","darren");
    GoodPlot *can2lss_p_emu__llmass     = new GoodPlot("2lss_p_emu__llmass","darren");
    GoodPlot *can2lss_p_mumu__llmass     = new GoodPlot("2lss_p_mumu__llmass","darren");
    GoodPlot *can2lss_m_ee__llmass     = new GoodPlot("2lss_m_ee__llmass","darren");
    GoodPlot *can2lss_m_emu__llmass     = new GoodPlot("2lss_m_emu__llmass","darren");
    GoodPlot *can2lss_m_mumu__llmass     = new GoodPlot("2lss_m_mumu__llmass","darren");

    
    GoodPlot *can2los_ee__MHT     = new GoodPlot("2los_ee__MHT","darren");
    GoodPlot *can2los_emu__MHT     = new GoodPlot("2los_emu__MHT","darren");
    GoodPlot *can2los_mumu__MHT     = new GoodPlot("2los_mumu__MHT","darren");
    GoodPlot *can2los_sfz_ee__MHT     = new GoodPlot("2los_sfz_ee__MHT","darren");
    GoodPlot *can2los_sfz_mumu__MHT     = new GoodPlot("2los_sfz_mumu__MHT","darren");
    GoodPlot *can2lss_p_ee__MHT     = new GoodPlot("2lss_p_ee__MHT","darren");
    GoodPlot *can2lss_p_emu__MHT     = new GoodPlot("2lss_p_emu__MHT","darren");
    GoodPlot *can2lss_p_mumu__MHT     = new GoodPlot("2lss_p_mumu__MHT","darren");
    GoodPlot *can2lss_m_ee__MHT     = new GoodPlot("2lss_m_ee__MHT","darren");
    GoodPlot *can2lss_m_emu__MHT     = new GoodPlot("2lss_m_emu__MHT","darren");
    GoodPlot *can2lss_m_mumu__MHT     = new GoodPlot("2lss_m_mumu__MHT","darren");
    GoodPlot *can3l_ppp__MHT     = new GoodPlot("3l_ppp__MHT","darren");
    GoodPlot *can3l_mmm__MHT     = new GoodPlot("3l_mmm__MHT","darren");
    GoodPlot *can3l_mix__MHT     = new GoodPlot("3l_mix__MHT","darren");
    GoodPlot *can3l_mix_sfz__MHT     = new GoodPlot("3l_mix_sfz__MHT","darren");
    GoodPlot *cange4l__MHT     = new GoodPlot("ge4l__MHT","darren");
    GoodPlot *can1l_mu__MHT     = new GoodPlot("1l_mu__MHT","darren");
    GoodPlot *can1l_e__MHT     = new GoodPlot("1l_e__MHT","darren");    
    
//     GoodPlot *can2los_ee__lepMVA     = new GoodPlot("2los_ee__lepMVA","darren");
//     GoodPlot *can2los_emu__lepMVA     = new GoodPlot("2los_emu__lepMVA","darren");
//     GoodPlot *can2los_mumu__lepMVA     = new GoodPlot("2los_mumu__lepMVA","darren");
//     GoodPlot *can2los_sfz_ee__lepMVA     = new GoodPlot("2los_sfz_ee__lepMVA","darren");
//     GoodPlot *can2los_sfz_mumu__lepMVA     = new GoodPlot("2los_sfz_mumu__lepMVA","darren");
//     GoodPlot *can2lss_p_ee__lepMVA     = new GoodPlot("2lss_p_ee__lepMVA","darren");
//     GoodPlot *can2lss_p_emu__lepMVA     = new GoodPlot("2lss_p_emu__lepMVA","darren");
//     GoodPlot *can2lss_p_mumu__lepMVA     = new GoodPlot("2lss_p_mumu__lepMVA","darren");
//     GoodPlot *can2lss_m_ee__lepMVA     = new GoodPlot("2lss_m_ee__lepMVA","darren");
//     GoodPlot *can2lss_m_emu__lepMVA     = new GoodPlot("2lss_m_emu__lepMVA","darren");
//     GoodPlot *can2lss_m_mumu__lepMVA     = new GoodPlot("2lss_m_mumu__lepMVA","darren");
//     GoodPlot *can3l_ppp__lepMVA     = new GoodPlot("3l_ppp__lepMVA","darren");
//     GoodPlot *can3l_mmm__lepMVA     = new GoodPlot("3l_mmm__lepMVA","darren");
//     GoodPlot *can3l_mix__lepMVA     = new GoodPlot("3l_mix__lepMVA","darren");
//     GoodPlot *can3l_mix_sfz__lepMVA     = new GoodPlot("3l_mix_sfz__lepMVA","darren");
//     GoodPlot *cange4l__lepMVA     = new GoodPlot("ge4l__lepMVA","darren");
//     GoodPlot *can1l_mu__lepMVA     = new GoodPlot("1l_mu__lepMVA","darren");
//     GoodPlot *can1l_e__lepMVA     = new GoodPlot("1l_e__lepMVA","darren");    
    
    GoodPlot *can2los_ee__PUMVA     = new GoodPlot("2los_ee__PUMVA","darren");
    GoodPlot *can2los_emu__PUMVA     = new GoodPlot("2los_emu__PUMVA","darren");
    GoodPlot *can2los_mumu__PUMVA     = new GoodPlot("2los_mumu__PUMVA","darren");
    GoodPlot *can2los_sfz_ee__PUMVA     = new GoodPlot("2los_sfz_ee__PUMVA","darren");
    GoodPlot *can2los_sfz_mumu__PUMVA     = new GoodPlot("2los_sfz_mumu__PUMVA","darren");
    GoodPlot *can2lss_p_ee__PUMVA     = new GoodPlot("2lss_p_ee__PUMVA","darren");
    GoodPlot *can2lss_p_emu__PUMVA     = new GoodPlot("2lss_p_emu__PUMVA","darren");
    GoodPlot *can2lss_p_mumu__PUMVA     = new GoodPlot("2lss_p_mumu__PUMVA","darren");
    GoodPlot *can2lss_m_ee__PUMVA     = new GoodPlot("2lss_m_ee__PUMVA","darren");
    GoodPlot *can2lss_m_emu__PUMVA     = new GoodPlot("2lss_m_emu__PUMVA","darren");
    GoodPlot *can2lss_m_mumu__PUMVA     = new GoodPlot("2lss_m_mumu__PUMVA","darren");
    GoodPlot *can3l_ppp__PUMVA     = new GoodPlot("3l_ppp__PUMVA","darren");
    GoodPlot *can3l_mmm__PUMVA     = new GoodPlot("3l_mmm__PUMVA","darren");
    GoodPlot *can3l_mix__PUMVA     = new GoodPlot("3l_mix__PUMVA","darren");
    GoodPlot *can3l_mix_sfz__PUMVA     = new GoodPlot("3l_mix_sfz__PUMVA","darren");
    GoodPlot *cange4l__PUMVA     = new GoodPlot("ge4l__PUMVA","darren");
    GoodPlot *can1l_mu__PUMVA     = new GoodPlot("1l_mu__PUMVA","darren");
    GoodPlot *can1l_e__PUMVA     = new GoodPlot("1l_e__PUMVA","darren");     
    
    
    
    
    

    for (int i=0; i<numsamples; i++)
    //for (int i=(numsamples-1); i>=0; i--)
    {    
        cout << "Doing " << sample_names[samples[i]] << endl;
        if (samples[i]>99)
        {

            can1->addPlotData(*this,"category_yields",i,"samp",-1,"E");
            cancategory_yields_njets_nbjets->addPlotData(*this,"category_yields_njets_nbjets",i,"samp",-1,"E");
            can2->addPlotData(*this,"2los_ee__njets",i,"samp",-1,"E");
            can3->addPlotData(*this,"2los_emu__njets",i,"samp",-1,"E");
            can4->addPlotData(*this,"2los_mumu__njets",i,"samp",-1,"E");
            can5->addPlotData(*this,"2los_sfz_ee__njets",i,"samp",-1,"E");
            can7->addPlotData(*this,"2los_sfz_mumu__njets",i,"samp",-1,"E");
//            can8->addPlotData(*this,"2lss_p_ee__njets",i,"samp",-1,"E");
//             can9->addPlotData(*this,"2lss_p_emu__njets",i,"samp",-1,"E");
//             can10->addPlotData(*this,"2lss_p_mumu__njets",i,"samp",-1,"E");
//             can11->addPlotData(*this,"2lss_m_ee__njets",i,"samp",-1,"E");
//             can12->addPlotData(*this,"2lss_m_emu__njets",i,"samp",-1,"E");
//             can13->addPlotData(*this,"2lss_m_mumu__njets",i,"samp",-1,"E");
//             can14->addPlotData(*this,"3l_ppp__njets",i,"samp",-1,"E");
//             can15->addPlotData(*this,"3l_mmm__njets",i,"samp",-1,"E");
//             can16->addPlotData(*this,"3l_mix__njets",i,"samp",-1,"E");
//             can17->addPlotData(*this,"3l_mix_sfz__njets",i,"samp",-1,"E");
//             can18->addPlotData(*this,"ge4l__njets",i,"samp",-1,"E");
            can1l_mu__njets->addPlotData(*this,"1l_mu__njets",i,"samp",-1,"E");
            can1l_e__njets->addPlotData(*this,"1l_e__njets",i,"samp",-1,"E");


            can19->addPlotData(*this,"2los_ee__nbjets",i,"samp",-1,"E");
            can20->addPlotData(*this,"2los_emu__nbjets",i,"samp",-1,"E");
            can21->addPlotData(*this,"2los_mumu__nbjets",i,"samp",-1,"E");
            can22->addPlotData(*this,"2los_sfz_ee__nbjets",i,"samp",-1,"E");
            can24->addPlotData(*this,"2los_sfz_mumu__nbjets",i,"samp",-1,"E");
//             can25->addPlotData(*this,"2lss_p_ee__nbjets",i,"samp",-1,"E");
//             can26->addPlotData(*this,"2lss_p_emu__nbjets",i,"samp",-1,"E");
//             can27->addPlotData(*this,"2lss_p_mumu__nbjets",i,"samp",-1,"E");
//             can28->addPlotData(*this,"2lss_m_ee__nbjets",i,"samp",-1,"E");
//             can29->addPlotData(*this,"2lss_m_emu__nbjets",i,"samp",-1,"E");
//             can30->addPlotData(*this,"2lss_m_mumu__nbjets",i,"samp",-1,"E");
//             can31->addPlotData(*this,"3l_ppp__nbjets",i,"samp",-1,"E");
//             can32->addPlotData(*this,"3l_mmm__nbjets",i,"samp",-1,"E");
//             can33->addPlotData(*this,"3l_mix__nbjets",i,"samp",-1,"E");
//             can34->addPlotData(*this,"3l_mix_sfz__nbjets",i,"samp",-1,"E");
//             can35->addPlotData(*this,"ge4l__nbjets",i,"samp",-1,"E");   
            can1l_mu__nbjets->addPlotData(*this,"1l_mu__nbjets",i,"samp",-1,"E");   
            can1l_e__nbjets->addPlotData(*this,"1l_e__nbjets",i,"samp",-1,"E");   
            
            
            can2los_ee__jetpt->addPlotData(*this,"2los_ee__jetpt",i,"samp",-1,"E");       
            can2los_emu__jetpt->addPlotData(*this,"2los_emu__jetpt",i,"samp",-1,"E");      
            can2los_mumu__jetpt->addPlotData(*this,"2los_mumu__jetpt",i,"samp",-1,"E");     
            can2los_sfz_ee__jetpt->addPlotData(*this,"2los_sfz_ee__jetpt",i,"samp",-1,"E");   
            can2los_sfz_mumu__jetpt->addPlotData(*this,"2los_sfz_mumu__jetpt",i,"samp",-1,"E"); 
//             can2lss_p_ee__jetpt->addPlotData(*this,"2lss_p_ee__jetpt",i,"samp",5,"E");     
//             can2lss_p_emu__jetpt->addPlotData(*this,"2lss_p_emu__jetpt",i,"samp",5,"E");    
//             can2lss_p_mumu__jetpt->addPlotData(*this,"2lss_p_mumu__jetpt",i,"samp",5,"E");   
//             can2lss_m_ee__jetpt->addPlotData(*this,"2lss_m_ee__jetpt",i,"samp",5,"E");     
//             can2lss_m_emu__jetpt->addPlotData(*this,"2lss_m_emu__jetpt",i,"samp",5,"E");    
//             can2lss_m_mumu__jetpt->addPlotData(*this,"2lss_m_mumu__jetpt",i,"samp",5,"E");   
//             can3l_ppp__jetpt->addPlotData(*this,"3l_ppp__jetpt",i,"samp",5,"E");        
//             can3l_mmm__jetpt->addPlotData(*this,"3l_mmm__jetpt",i,"samp",5,"E");        
//             can3l_mix__jetpt->addPlotData(*this,"3l_mix__jetpt",i,"samp",5,"E");        
//             can3l_mix_sfz__jetpt->addPlotData(*this,"3l_mix_sfz__jetpt",i,"samp",5,"E");    
//             cange4l__jetpt->addPlotData(*this,"ge4l__jetpt",i,"samp",5,"E");        
            can1l_mu__jetpt->addPlotData(*this,"1l_mu__jetpt",i,"samp",-1,"E");        
            can1l_e__jetpt->addPlotData(*this,"1l_e__jetpt",i,"samp",-1,"E");        


            can2los_ee__jeteta->addPlotData(*this,"2los_ee__jeteta",i,"samp",-1,"E");      
            can2los_emu__jeteta->addPlotData(*this,"2los_emu__jeteta",i,"samp",-1,"E");     
            can2los_mumu__jeteta->addPlotData(*this,"2los_mumu__jeteta",i,"samp",-1,"E");    
            can2los_sfz_ee__jeteta->addPlotData(*this,"2los_sfz_ee__jeteta",i,"samp",-1,"E");  
            can2los_sfz_mumu__jeteta->addPlotData(*this,"2los_sfz_mumu__jeteta",i,"samp",-1,"E");
//             can2lss_p_ee__jeteta->addPlotData(*this,"2lss_p_ee__jeteta",i,"samp",5,"E");    
//             can2lss_p_emu__jeteta->addPlotData(*this,"2lss_p_emu__jeteta",i,"samp",5,"E");   
//             can2lss_p_mumu__jeteta->addPlotData(*this,"2lss_p_mumu__jeteta",i,"samp",5,"E");  
//             can2lss_m_ee__jeteta->addPlotData(*this,"2lss_m_ee__jeteta",i,"samp",5,"E");    
//             can2lss_m_emu__jeteta->addPlotData(*this,"2lss_m_emu__jeteta",i,"samp",5,"E");   
//             can2lss_m_mumu__jeteta->addPlotData(*this,"2lss_m_mumu__jeteta",i,"samp",5,"E");  
//             can3l_ppp__jeteta->addPlotData(*this,"3l_ppp__jeteta",i,"samp",5,"E");       
//             can3l_mmm__jeteta->addPlotData(*this,"3l_mmm__jeteta",i,"samp",5,"E");       
//             can3l_mix__jeteta->addPlotData(*this,"3l_mix__jeteta",i,"samp",5,"E");       
//             can3l_mix_sfz__jeteta->addPlotData(*this,"3l_mix_sfz__jeteta",i,"samp",5,"E");   
//             cange4l__jeteta->addPlotData(*this,"ge4l__jeteta",i,"samp",5,"E");        
            can1l_mu__jeteta->addPlotData(*this,"1l_mu__jeteta",i,"samp",-1,"E");        
            can1l_e__jeteta->addPlotData(*this,"1l_e__jeteta",i,"samp",-1,"E");        


            can2los_ee__jetcsv->addPlotData(*this,"2los_ee__jetcsv",i,"samp",-1,"E");      
            can2los_emu__jetcsv->addPlotData(*this,"2los_emu__jetcsv",i,"samp",-1,"E");     
            can2los_mumu__jetcsv->addPlotData(*this,"2los_mumu__jetcsv",i,"samp",-1,"E");    
            can2los_sfz_ee__jetcsv->addPlotData(*this,"2los_sfz_ee__jetcsv",i,"samp",-1,"E");  
            can2los_sfz_mumu__jetcsv->addPlotData(*this,"2los_sfz_mumu__jetcsv",i,"samp",-1,"E");
//             can2lss_p_ee__jetcsv->addPlotData(*this,"2lss_p_ee__jetcsv",i,"samp",5,"E");    
//             can2lss_p_emu__jetcsv->addPlotData(*this,"2lss_p_emu__jetcsv",i,"samp",5,"E");   
//             can2lss_p_mumu__jetcsv->addPlotData(*this,"2lss_p_mumu__jetcsv",i,"samp",5,"E");  
//             can2lss_m_ee__jetcsv->addPlotData(*this,"2lss_m_ee__jetcsv",i,"samp",5,"E");    
//             can2lss_m_emu__jetcsv->addPlotData(*this,"2lss_m_emu__jetcsv",i,"samp",5,"E");   
//             can2lss_m_mumu__jetcsv->addPlotData(*this,"2lss_m_mumu__jetcsv",i,"samp",5,"E");  
//             can3l_ppp__jetcsv->addPlotData(*this,"3l_ppp__jetcsv",i,"samp",5,"E");       
//             can3l_mmm__jetcsv->addPlotData(*this,"3l_mmm__jetcsv",i,"samp",5,"E");       
//             can3l_mix__jetcsv->addPlotData(*this,"3l_mix__jetcsv",i,"samp",5,"E");       
//             can3l_mix_sfz__jetcsv->addPlotData(*this,"3l_mix_sfz__jetcsv",i,"samp",5,"E");   
//             cange4l__jetcsv->addPlotData(*this,"ge4l__jetcsv",i,"samp",5,"E");        
            can1l_mu__jetcsv->addPlotData(*this,"1l_mu__jetcsv",i,"samp",-1,"E");        
            can1l_e__jetcsv->addPlotData(*this,"1l_e__jetcsv",i,"samp",-1,"E");        


            can2los_ee__leppt->addPlotData(*this,"2los_ee__leppt",i,"samp",-1,"E");       
            can2los_emu__leppt->addPlotData(*this,"2los_emu__leppt",i,"samp",-1,"E");      
            can2los_mumu__leppt->addPlotData(*this,"2los_mumu__leppt",i,"samp",-1,"E");     
            can2los_sfz_ee__leppt->addPlotData(*this,"2los_sfz_ee__leppt",i,"samp",-1,"E");   
            can2los_sfz_mumu__leppt->addPlotData(*this,"2los_sfz_mumu__leppt",i,"samp",-1,"E"); 
//             can2lss_p_ee__leppt->addPlotData(*this,"2lss_p_ee__leppt",i,"samp",5,"E");     
//             can2lss_p_emu__leppt->addPlotData(*this,"2lss_p_emu__leppt",i,"samp",5,"E");    
//             can2lss_p_mumu__leppt->addPlotData(*this,"2lss_p_mumu__leppt",i,"samp",5,"E");   
//             can2lss_m_ee__leppt->addPlotData(*this,"2lss_m_ee__leppt",i,"samp",5,"E");     
//             can2lss_m_emu__leppt->addPlotData(*this,"2lss_m_emu__leppt",i,"samp",5,"E");    
//             can2lss_m_mumu__leppt->addPlotData(*this,"2lss_m_mumu__leppt",i,"samp",5,"E");   
//             can3l_ppp__leppt->addPlotData(*this,"3l_ppp__leppt",i,"samp",5,"E");        
//             can3l_mmm__leppt->addPlotData(*this,"3l_mmm__leppt",i,"samp",5,"E");        
//             can3l_mix__leppt->addPlotData(*this,"3l_mix__leppt",i,"samp",5,"E");        
//             can3l_mix_sfz__leppt->addPlotData(*this,"3l_mix_sfz__leppt",i,"samp",5,"E");   
//             cange4l__leppt->addPlotData(*this,"ge4l__leppt",i,"samp",5,"E");        
            can1l_mu__leppt->addPlotData(*this,"1l_mu__leppt",i,"samp",-1,"E");        
            can1l_e__leppt->addPlotData(*this,"1l_e__leppt",i,"samp",-1,"E");        


            can2los_ee__lepeta->addPlotData(*this,"2los_ee__lepeta",i,"samp",-1,"E");      
            can2los_emu__lepeta->addPlotData(*this,"2los_emu__lepeta",i,"samp",-1,"E");     
            can2los_mumu__lepeta->addPlotData(*this,"2los_mumu__lepeta",i,"samp",-1,"E");
            can2los_sfz_ee__lepeta->addPlotData(*this,"2los_sfz_ee__lepeta",i,"samp",-1,"E");  
            can2los_sfz_mumu__lepeta->addPlotData(*this,"2los_sfz_mumu__lepeta",i,"samp",-1,"E");
//             can2lss_p_ee__lepeta->addPlotData(*this,"2lss_p_ee__lepeta",i,"samp",5,"E");
//             can2lss_p_emu__lepeta->addPlotData(*this,"2lss_p_emu__lepeta",i,"samp",5,"E");
//             can2lss_p_mumu__lepeta->addPlotData(*this,"2lss_p_mumu__lepeta",i,"samp",5,"E");  
//             can2lss_m_ee__lepeta->addPlotData(*this,"2lss_m_ee__lepeta",i,"samp",5,"E");    
//             can2lss_m_emu__lepeta->addPlotData(*this,"2lss_m_emu__lepeta",i,"samp",5,"E");   
//             can2lss_m_mumu__lepeta->addPlotData(*this,"2lss_m_mumu__lepeta",i,"samp",5,"E");  
//             can3l_ppp__lepeta->addPlotData(*this,"3l_ppp__lepeta",i,"samp",5,"E");       
//             can3l_mmm__lepeta->addPlotData(*this,"3l_mmm__lepeta",i,"samp",5,"E");       
//             can3l_mix__lepeta->addPlotData(*this,"3l_mix__lepeta",i,"samp",5,"E");       
//             can3l_mix_sfz__lepeta->addPlotData(*this,"3l_mix_sfz__lepeta",i,"samp",5,"E");  
//             cange4l__lepeta->addPlotData(*this,"ge4l__lepeta",i,"samp",5,"E");        
            can1l_mu__lepeta->addPlotData(*this,"1l_mu__lepeta",i,"samp",-1,"E");        
            can1l_e__lepeta->addPlotData(*this,"1l_e__lepeta",i,"samp",-1,"E");        



            can2los_ee__met->addPlotData(*this,"2los_ee__met",i,"samp",-1,"E");        
            can2los_emu__met->addPlotData(*this,"2los_emu__met",i,"samp",-1,"E");        
            can2los_mumu__met->addPlotData(*this,"2los_mumu__met",i,"samp",-1,"E");       
            can2los_sfz_ee__met->addPlotData(*this,"2los_sfz_ee__met",i,"samp",-1,"E");     
            can2los_sfz_mumu__met->addPlotData(*this,"2los_sfz_mumu__met",i,"samp",-1,"E");   
//             can2lss_p_ee__met->addPlotData(*this,"2lss_p_ee__met",i,"samp",5,"E");       
//             can2lss_p_emu__met->addPlotData(*this,"2lss_p_emu__met",i,"samp",5,"E");      
//             can2lss_p_mumu__met->addPlotData(*this,"2lss_p_mumu__met",i,"samp",5,"E");     
//             can2lss_m_ee__met->addPlotData(*this,"2lss_m_ee__met",i,"samp",5,"E");       
//             can2lss_m_emu__met->addPlotData(*this,"2lss_m_emu__met",i,"samp",5,"E");      
//             can2lss_m_mumu__met->addPlotData(*this,"2lss_m_mumu__met",i,"samp",5,"E");     
//             can3l_ppp__met->addPlotData(*this,"3l_ppp__met",i,"samp",5,"E");        
//             can3l_mmm__met->addPlotData(*this,"3l_mmm__met",i,"samp",5,"E");        
//             can3l_mix__met->addPlotData(*this,"3l_mix__met",i,"samp",5,"E");        
//             can3l_mix_sfz__met->addPlotData(*this,"3l_mix_sfz__met",i,"samp",5,"E");      
//             cange4l__met->addPlotData(*this,"ge4l__met",i,"samp",5,"E");        
            can1l_mu__met->addPlotData(*this,"1l_mu__met",i,"samp",-1,"E");        
            can1l_e__met->addPlotData(*this,"1l_e__met",i,"samp",-1,"E");        

            can2los_ee__metphi->addPlotData(*this,"2los_ee__metphi",i,"samp",-1,"E");      
            can2los_emu__metphi->addPlotData(*this,"2los_emu__metphi",i,"samp",-1,"E");     
            can2los_mumu__metphi->addPlotData(*this,"2los_mumu__metphi",i,"samp",-1,"E");    
            can2los_sfz_ee__metphi->addPlotData(*this,"2los_sfz_ee__metphi",i,"samp",-1,"E");  
            can2los_sfz_mumu__metphi->addPlotData(*this,"2los_sfz_mumu__metphi",i,"samp",-1,"E");
//             can2lss_p_ee__metphi->addPlotData(*this,"2lss_p_ee__metphi",i,"samp",5,"E");    
//             can2lss_p_emu__metphi->addPlotData(*this,"2lss_p_emu__metphi",i,"samp",5,"E");   
//             can2lss_p_mumu__metphi->addPlotData(*this,"2lss_p_mumu__metphi",i,"samp",5,"E");  
//             can2lss_m_ee__metphi->addPlotData(*this,"2lss_m_ee__metphi",i,"samp",5,"E");    
//             can2lss_m_emu__metphi->addPlotData(*this,"2lss_m_emu__metphi",i,"samp",5,"E");   
//             can2lss_m_mumu__metphi->addPlotData(*this,"2lss_m_mumu__metphi",i,"samp",5,"E");  
//             can3l_ppp__metphi->addPlotData(*this,"3l_ppp__metphi",i,"samp",5,"E");       
//             can3l_mmm__metphi->addPlotData(*this,"3l_mmm__metphi",i,"samp",5,"E");       
//             can3l_mix__metphi->addPlotData(*this,"3l_mix__metphi",i,"samp",5,"E");       
//             can3l_mix_sfz__metphi->addPlotData(*this,"3l_mix_sfz__metphi",i,"samp",5,"E");   
//             cange4l__metphi->addPlotData(*this,"ge4l__metphi",i,"samp",5,"E");
            can1l_mu__metphi->addPlotData(*this,"1l_mu__metphi",i,"samp",-1,"E");
            can1l_e__metphi->addPlotData(*this,"1l_e__metphi",i,"samp",-1,"E");
            
            
            can2los_ee__numPVs->addPlotData(*this,"2los_ee__numPVs",i,"samp",-1,"E");      
            can2los_emu__numPVs->addPlotData(*this,"2los_emu__numPVs",i,"samp",-1,"E");     
            can2los_mumu__numPVs->addPlotData(*this,"2los_mumu__numPVs",i,"samp",-1,"E");    
            can2los_sfz_ee__numPVs->addPlotData(*this,"2los_sfz_ee__numPVs",i,"samp",-1,"E");  
            can2los_sfz_mumu__numPVs->addPlotData(*this,"2los_sfz_mumu__numPVs",i,"samp",-1,"E");
//             can2lss_p_ee__numPVs->addPlotData(*this,"2lss_p_ee__numPVs",i,"samp",5,"E");    
//             can2lss_p_emu__numPVs->addPlotData(*this,"2lss_p_emu__numPVs",i,"samp",5,"E");   
//             can2lss_p_mumu__numPVs->addPlotData(*this,"2lss_p_mumu__numPVs",i,"samp",5,"E");  
//             can2lss_m_ee__numPVs->addPlotData(*this,"2lss_m_ee__numPVs",i,"samp",5,"E");    
//             can2lss_m_emu__numPVs->addPlotData(*this,"2lss_m_emu__numPVs",i,"samp",5,"E");   
//             can2lss_m_mumu__numPVs->addPlotData(*this,"2lss_m_mumu__numPVs",i,"samp",5,"E");  
//             can3l_ppp__numPVs->addPlotData(*this,"3l_ppp__numPVs",i,"samp",5,"E");       
//             can3l_mmm__numPVs->addPlotData(*this,"3l_mmm__numPVs",i,"samp",5,"E");       
//             can3l_mix__numPVs->addPlotData(*this,"3l_mix__numPVs",i,"samp",5,"E");       
//             can3l_mix_sfz__numPVs->addPlotData(*this,"3l_mix_sfz__numPVs",i,"samp",5,"E");   
//             cange4l__numPVs->addPlotData(*this,"ge4l__numPVs",i,"samp",5,"E");
            can1l_mu__numPVs->addPlotData(*this,"1l_mu__numPVs",i,"samp",-1,"E");
            can1l_e__numPVs->addPlotData(*this,"1l_e__numPVs",i,"samp",-1,"E");            
            
            can2los_ee__lep1pt->addPlotData(*this,"2los_ee__lep1pt",i,"samp",-1,"E");      
            can2los_emu__lep1pt->addPlotData(*this,"2los_emu__lep1pt",i,"samp",-1,"E");     
            can2los_mumu__lep1pt->addPlotData(*this,"2los_mumu__lep1pt",i,"samp",-1,"E");    
            can2los_sfz_ee__lep1pt->addPlotData(*this,"2los_sfz_ee__lep1pt",i,"samp",-1,"E");  
            can2los_sfz_mumu__lep1pt->addPlotData(*this,"2los_sfz_mumu__lep1pt",i,"samp",-1,"E");
//             can2lss_p_ee__lep1pt->addPlotData(*this,"2lss_p_ee__lep1pt",i,"samp",5,"E");    
//             can2lss_p_emu__lep1pt->addPlotData(*this,"2lss_p_emu__lep1pt",i,"samp",5,"E");   
//             can2lss_p_mumu__lep1pt->addPlotData(*this,"2lss_p_mumu__lep1pt",i,"samp",5,"E");  
//             can2lss_m_ee__lep1pt->addPlotData(*this,"2lss_m_ee__lep1pt",i,"samp",5,"E");    
//             can2lss_m_emu__lep1pt->addPlotData(*this,"2lss_m_emu__lep1pt",i,"samp",5,"E");   
//             can2lss_m_mumu__lep1pt->addPlotData(*this,"2lss_m_mumu__lep1pt",i,"samp",5,"E");  
//             can3l_ppp__lep1pt->addPlotData(*this,"3l_ppp__lep1pt",i,"samp",5,"E");       
//             can3l_mmm__lep1pt->addPlotData(*this,"3l_mmm__lep1pt",i,"samp",5,"E");       
//             can3l_mix__lep1pt->addPlotData(*this,"3l_mix__lep1pt",i,"samp",5,"E");       
//             can3l_mix_sfz__lep1pt->addPlotData(*this,"3l_mix_sfz__lep1pt",i,"samp",5,"E");   
//             cange4l__lep1pt->addPlotData(*this,"ge4l__lep1pt",i,"samp",5,"E");
            can1l_mu__lep1pt->addPlotData(*this,"1l_mu__lep1pt",i,"samp",-1,"E");
            can1l_e__lep1pt->addPlotData(*this,"1l_e__lep1pt",i,"samp",-1,"E");            
            
            can2los_ee__lep2pt->addPlotData(*this,"2los_ee__lep2pt",i,"samp",-1,"E");      
            can2los_emu__lep2pt->addPlotData(*this,"2los_emu__lep2pt",i,"samp",-1,"E");     
            can2los_mumu__lep2pt->addPlotData(*this,"2los_mumu__lep2pt",i,"samp",-1,"E");    
            can2los_sfz_ee__lep2pt->addPlotData(*this,"2los_sfz_ee__lep2pt",i,"samp",-1,"E");  
            can2los_sfz_mumu__lep2pt->addPlotData(*this,"2los_sfz_mumu__lep2pt",i,"samp",-1,"E");
//             can2lss_p_ee__lep2pt->addPlotData(*this,"2lss_p_ee__lep2pt",i,"samp",5,"E");    
//             can2lss_p_emu__lep2pt->addPlotData(*this,"2lss_p_emu__lep2pt",i,"samp",5,"E");   
//             can2lss_p_mumu__lep2pt->addPlotData(*this,"2lss_p_mumu__lep2pt",i,"samp",5,"E");  
//             can2lss_m_ee__lep2pt->addPlotData(*this,"2lss_m_ee__lep2pt",i,"samp",5,"E");    
//             can2lss_m_emu__lep2pt->addPlotData(*this,"2lss_m_emu__lep2pt",i,"samp",5,"E");   
//             can2lss_m_mumu__lep2pt->addPlotData(*this,"2lss_m_mumu__lep2pt",i,"samp",5,"E");  
//             can3l_ppp__lep2pt->addPlotData(*this,"3l_ppp__lep2pt",i,"samp",5,"E");       
//             can3l_mmm__lep2pt->addPlotData(*this,"3l_mmm__lep2pt",i,"samp",5,"E");       
//             can3l_mix__lep2pt->addPlotData(*this,"3l_mix__lep2pt",i,"samp",5,"E");       
//             can3l_mix_sfz__lep2pt->addPlotData(*this,"3l_mix_sfz__lep2pt",i,"samp",5,"E");   
//             cange4l__lep2pt->addPlotData(*this,"ge4l__lep2pt",i,"samp",5,"E");         
            
            
            can2los_ee__llmass->addPlotData(*this,"2los_ee__llmass",i,"samp",-1,"E");      
            can2los_emu__llmass->addPlotData(*this,"2los_emu__llmass",i,"samp",-1,"E");     
            can2los_mumu__llmass->addPlotData(*this,"2los_mumu__llmass",i,"samp",-1,"E");    
            can2los_sfz_ee__llmass->addPlotData(*this,"2los_sfz_ee__llmass",i,"samp",-1,"E");  
            can2los_sfz_mumu__llmass->addPlotData(*this,"2los_sfz_mumu__llmass",i,"samp",-1,"E");
//             can2lss_p_ee__llmass->addPlotData(*this,"2lss_p_ee__llmass",i,"samp",5,"E");    
//             can2lss_p_emu__llmass->addPlotData(*this,"2lss_p_emu__llmass",i,"samp",5,"E");   
//             can2lss_p_mumu__llmass->addPlotData(*this,"2lss_p_mumu__llmass",i,"samp",5,"E");  
//             can2lss_m_ee__llmass->addPlotData(*this,"2lss_m_ee__llmass",i,"samp",5,"E");    
//             can2lss_m_emu__llmass->addPlotData(*this,"2lss_m_emu__llmass",i,"samp",5,"E");   
//             can2lss_m_mumu__llmass->addPlotData(*this,"2lss_m_mumu__llmass",i,"samp",5,"E");  
          
            
            can2los_ee__MHT->addPlotData(*this,"2los_ee__MHT",i,"samp",-1,"E");      
            can2los_emu__MHT->addPlotData(*this,"2los_emu__MHT",i,"samp",-1,"E");     
            can2los_mumu__MHT->addPlotData(*this,"2los_mumu__MHT",i,"samp",-1,"E");    
            can2los_sfz_ee__MHT->addPlotData(*this,"2los_sfz_ee__MHT",i,"samp",-1,"E");  
            can2los_sfz_mumu__MHT->addPlotData(*this,"2los_sfz_mumu__MHT",i,"samp",-1,"E");
//             can2lss_p_ee__MHT->addPlotData(*this,"2lss_p_ee__MHT",i,"samp",5,"E");    
//             can2lss_p_emu__MHT->addPlotData(*this,"2lss_p_emu__MHT",i,"samp",5,"E");   
//             can2lss_p_mumu__MHT->addPlotData(*this,"2lss_p_mumu__MHT",i,"samp",5,"E");  
//             can2lss_m_ee__MHT->addPlotData(*this,"2lss_m_ee__MHT",i,"samp",5,"E");    
//             can2lss_m_emu__MHT->addPlotData(*this,"2lss_m_emu__MHT",i,"samp",5,"E");   
//             can2lss_m_mumu__MHT->addPlotData(*this,"2lss_m_mumu__MHT",i,"samp",5,"E");  
//             can3l_ppp__MHT->addPlotData(*this,"3l_ppp__MHT",i,"samp",5,"E");       
//             can3l_mmm__MHT->addPlotData(*this,"3l_mmm__MHT",i,"samp",5,"E");       
//             can3l_mix__MHT->addPlotData(*this,"3l_mix__MHT",i,"samp",5,"E");       
//             can3l_mix_sfz__MHT->addPlotData(*this,"3l_mix_sfz__MHT",i,"samp",5,"E");   
//             cange4l__MHT->addPlotData(*this,"ge4l__MHT",i,"samp",5,"E");
            can1l_mu__MHT->addPlotData(*this,"1l_mu__MHT",i,"samp",-1,"E");
            can1l_e__MHT->addPlotData(*this,"1l_e__MHT",i,"samp",-1,"E");            

//             can2los_ee__lepMVA->addPlotData(*this,"2los_ee__lepMVA",i,"samp",-1,"E");      
//             can2los_emu__lepMVA->addPlotData(*this,"2los_emu__lepMVA",i,"samp",-1,"E");     
//             can2los_mumu__lepMVA->addPlotData(*this,"2los_mumu__lepMVA",i,"samp",-1,"E");    
//             can2los_sfz_ee__lepMVA->addPlotData(*this,"2los_sfz_ee__lepMVA",i,"samp",-1,"E");  
//             can2los_sfz_mumu__lepMVA->addPlotData(*this,"2los_sfz_mumu__lepMVA",i,"samp",-1,"E");
// //             can2lss_p_ee__lepMVA->addPlotData(*this,"2lss_p_ee__lepMVA",i,"samp",5,"E");    
// //             can2lss_p_emu__lepMVA->addPlotData(*this,"2lss_p_emu__lepMVA",i,"samp",5,"E");   
// //             can2lss_p_mumu__lepMVA->addPlotData(*this,"2lss_p_mumu__lepMVA",i,"samp",5,"E");  
// //             can2lss_m_ee__lepMVA->addPlotData(*this,"2lss_m_ee__lepMVA",i,"samp",5,"E");    
// //             can2lss_m_emu__lepMVA->addPlotData(*this,"2lss_m_emu__lepMVA",i,"samp",5,"E");   
// //             can2lss_m_mumu__lepMVA->addPlotData(*this,"2lss_m_mumu__lepMVA",i,"samp",5,"E");  
// //             can3l_ppp__lepMVA->addPlotData(*this,"3l_ppp__lepMVA",i,"samp",5,"E");       
// //             can3l_mmm__lepMVA->addPlotData(*this,"3l_mmm__lepMVA",i,"samp",5,"E");       
// //             can3l_mix__lepMVA->addPlotData(*this,"3l_mix__lepMVA",i,"samp",5,"E");       
// //             can3l_mix_sfz__lepMVA->addPlotData(*this,"3l_mix_sfz__lepMVA",i,"samp",5,"E");   
// //             cange4l__lepMVA->addPlotData(*this,"ge4l__lepMVA",i,"samp",5,"E");
//             can1l_mu__lepMVA->addPlotData(*this,"1l_mu__lepMVA",i,"samp",-1,"E");
//             can1l_e__lepMVA->addPlotData(*this,"1l_e__lepMVA",i,"samp",-1,"E");

            can2los_ee__PUMVA->addPlotData(*this,"2los_ee__PUMVA",i,"samp",-1,"E");      
            can2los_emu__PUMVA->addPlotData(*this,"2los_emu__PUMVA",i,"samp",-1,"E");     
            can2los_mumu__PUMVA->addPlotData(*this,"2los_mumu__PUMVA",i,"samp",-1,"E");    
            can2los_sfz_ee__PUMVA->addPlotData(*this,"2los_sfz_ee__PUMVA",i,"samp",-1,"E");  
            can2los_sfz_mumu__PUMVA->addPlotData(*this,"2los_sfz_mumu__PUMVA",i,"samp",-1,"E");
//             can2lss_p_ee__PUMVA->addPlotData(*this,"2lss_p_ee__PUMVA",i,"samp",5,"E");    
//             can2lss_p_emu__PUMVA->addPlotData(*this,"2lss_p_emu__PUMVA",i,"samp",5,"E");   
//             can2lss_p_mumu__PUMVA->addPlotData(*this,"2lss_p_mumu__PUMVA",i,"samp",5,"E");  
//             can2lss_m_ee__PUMVA->addPlotData(*this,"2lss_m_ee__PUMVA",i,"samp",5,"E");    
//             can2lss_m_emu__PUMVA->addPlotData(*this,"2lss_m_emu__PUMVA",i,"samp",5,"E");   
//             can2lss_m_mumu__PUMVA->addPlotData(*this,"2lss_m_mumu__PUMVA",i,"samp",5,"E");  
//             can3l_ppp__PUMVA->addPlotData(*this,"3l_ppp__PUMVA",i,"samp",5,"E");       
//             can3l_mmm__PUMVA->addPlotData(*this,"3l_mmm__PUMVA",i,"samp",5,"E");       
//             can3l_mix__PUMVA->addPlotData(*this,"3l_mix__PUMVA",i,"samp",5,"E");       
//             can3l_mix_sfz__PUMVA->addPlotData(*this,"3l_mix_sfz__PUMVA",i,"samp",5,"E");   
//             cange4l__PUMVA->addPlotData(*this,"ge4l__PUMVA",i,"samp",5,"E");
            can1l_mu__PUMVA->addPlotData(*this,"1l_mu__PUMVA",i,"samp",-1,"E");
            can1l_e__PUMVA->addPlotData(*this,"1l_e__PUMVA",i,"samp",-1,"E");



        
            cout << " " << endl;      
            double eff = ((TH1D*)hist[i].FindObject("single_ele_trigs"))->GetBinContent(2);
            double denom = ((TH1D*)hist[i].FindObject("single_ele_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "single_ele_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("single_mu_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("single_mu_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "single_mu_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("double_mu_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("double_mu_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "double_mu_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("double_ele_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("double_ele_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "double_ele_trigs eff: " << eff << endl;
            
            eff = ((TH1D*)hist[i].FindObject("mu_ele_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("mu_ele_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "mu_ele_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "all_trigs eff: " << eff << endl;
            cout << " " << endl;
            
            eff = ((TH1D*)hist[i].FindObject("2los_ee__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_ee__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_ee__all_trigs eff: " << eff << endl;                     
            
            eff = ((TH1D*)hist[i].FindObject("2los_emu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_emu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_emu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2los_mumu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_mumu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_mumu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2los_sfz_ee__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_sfz_ee__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_sfz_ee__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2los_sfz_mumu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_sfz_mumu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_sfz_mumu__all_trigs eff: " << eff << endl;                      
            
            eff = ((TH1D*)hist[i].FindObject("2lss_p_ee__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_p_ee__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_p_ee__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2lss_p_emu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_p_emu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_p_emu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2lss_p_mumu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_p_mumu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_p_mumu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2lss_m_ee__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_m_ee__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_m_ee__all_trigs eff: " << eff << endl;
                                  
            eff = ((TH1D*)hist[i].FindObject("2lss_m_emu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_m_emu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_m_emu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2lss_m_mumu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_m_mumu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_m_mumu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("3l_ppp__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("3l_ppp__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "3l_ppp__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("3l_mmm__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("3l_mmm__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "3l_mmm__all_trigs eff: " << eff << endl;                      
            
            eff = ((TH1D*)hist[i].FindObject("3l_mix__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("3l_mix__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "3l_mix__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("3l_mix_sfz__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("3l_mix_sfz__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "3l_mix_sfz__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("ge4l__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("ge4l__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "ge4l__all_trigs eff: " << eff << endl;
            cout << " " << endl;



            
                   
            continue;
        }
        
        
        can1->addStackWithSumMC(*this,"category_yields",i,"samp");
        cancategory_yields_njets_nbjets->addStackWithSumMC(*this,"category_yields_njets_nbjets",i,"samp");
        can2->addStackWithSumMC(*this,"2los_ee__njets",i,"samp");
        can3->addStackWithSumMC(*this,"2los_emu__njets",i,"samp");
        can4->addStackWithSumMC(*this,"2los_mumu__njets",i,"samp");
        can5->addStackWithSumMC(*this,"2los_sfz_ee__njets",i,"samp");
        can7->addStackWithSumMC(*this,"2los_sfz_mumu__njets",i,"samp");
//         can8->addStackWithSumMC(*this,"2lss_p_ee__njets",i,"samp");
//         can9->addStackWithSumMC(*this,"2lss_p_emu__njets",i,"samp");
//         can10->addStackWithSumMC(*this,"2lss_p_mumu__njets",i,"samp");
//         can11->addStackWithSumMC(*this,"2lss_m_ee__njets",i,"samp");
//         can12->addStackWithSumMC(*this,"2lss_m_emu__njets",i,"samp");
//         can13->addStackWithSumMC(*this,"2lss_m_mumu__njets",i,"samp");
//         can14->addStackWithSumMC(*this,"3l_ppp__njets",i,"samp");
//         can15->addStackWithSumMC(*this,"3l_mmm__njets",i,"samp");
//         can16->addStackWithSumMC(*this,"3l_mix__njets",i,"samp");
//         can17->addStackWithSumMC(*this,"3l_mix_sfz__njets",i,"samp");
//         can18->addStackWithSumMC(*this,"ge4l__njets",i,"samp");
        can1l_mu__njets->addStackWithSumMC(*this,"1l_mu__njets",i,"samp");
        can1l_e__njets->addStackWithSumMC(*this,"1l_e__njets",i,"samp");

        can19->addStackWithSumMC(*this,"2los_ee__nbjets",i,"samp");
        can20->addStackWithSumMC(*this,"2los_emu__nbjets",i,"samp");
        can21->addStackWithSumMC(*this,"2los_mumu__nbjets",i,"samp");
        can22->addStackWithSumMC(*this,"2los_sfz_ee__nbjets",i,"samp");
        can24->addStackWithSumMC(*this,"2los_sfz_mumu__nbjets",i,"samp");
//         can25->addStackWithSumMC(*this,"2lss_p_ee__nbjets",i,"samp");
//         can26->addStackWithSumMC(*this,"2lss_p_emu__nbjets",i,"samp");
//         can27->addStackWithSumMC(*this,"2lss_p_mumu__nbjets",i,"samp");
//         can28->addStackWithSumMC(*this,"2lss_m_ee__nbjets",i,"samp");
//         can29->addStackWithSumMC(*this,"2lss_m_emu__nbjets",i,"samp");
//         can30->addStackWithSumMC(*this,"2lss_m_mumu__nbjets",i,"samp");
//         can31->addStackWithSumMC(*this,"3l_ppp__nbjets",i,"samp");
//         can32->addStackWithSumMC(*this,"3l_mmm__nbjets",i,"samp");
//         can33->addStackWithSumMC(*this,"3l_mix__nbjets",i,"samp");
//         can34->addStackWithSumMC(*this,"3l_mix_sfz__nbjets",i,"samp");
//         can35->addStackWithSumMC(*this,"ge4l__nbjets",i,"samp");   
        can1l_mu__nbjets->addStackWithSumMC(*this,"1l_mu__nbjets",i,"samp");   
        can1l_e__nbjets->addStackWithSumMC(*this,"1l_e__nbjets",i,"samp");   
        
        can2los_ee__jetpt->addStackWithSumMC(*this,"2los_ee__jetpt",i,"samp",-1);       
        can2los_emu__jetpt->addStackWithSumMC(*this,"2los_emu__jetpt",i,"samp",-1);      
        can2los_mumu__jetpt->addStackWithSumMC(*this,"2los_mumu__jetpt",i,"samp",-1);     
        can2los_sfz_ee__jetpt->addStackWithSumMC(*this,"2los_sfz_ee__jetpt",i,"samp",-1);   
        can2los_sfz_mumu__jetpt->addStackWithSumMC(*this,"2los_sfz_mumu__jetpt",i,"samp",-1); 
//         can2lss_p_ee__jetpt->addStackWithSumMC(*this,"2lss_p_ee__jetpt",i,"samp",5);     
//         can2lss_p_emu__jetpt->addStackWithSumMC(*this,"2lss_p_emu__jetpt",i,"samp",5);    
//         can2lss_p_mumu__jetpt->addStackWithSumMC(*this,"2lss_p_mumu__jetpt",i,"samp",5);   
//         can2lss_m_ee__jetpt->addStackWithSumMC(*this,"2lss_m_ee__jetpt",i,"samp",5);     
//         can2lss_m_emu__jetpt->addStackWithSumMC(*this,"2lss_m_emu__jetpt",i,"samp",5);    
//         can2lss_m_mumu__jetpt->addStackWithSumMC(*this,"2lss_m_mumu__jetpt",i,"samp",5);   
//         can3l_ppp__jetpt->addStackWithSumMC(*this,"3l_ppp__jetpt",i,"samp",5);        
//         can3l_mmm__jetpt->addStackWithSumMC(*this,"3l_mmm__jetpt",i,"samp",5);        
//         can3l_mix__jetpt->addStackWithSumMC(*this,"3l_mix__jetpt",i,"samp",5);        
//         can3l_mix_sfz__jetpt->addStackWithSumMC(*this,"3l_mix_sfz__jetpt",i,"samp",5);    
//         cange4l__jetpt->addStackWithSumMC(*this,"ge4l__jetpt",i,"samp",5);        
        can1l_mu__jetpt->addStackWithSumMC(*this,"1l_mu__jetpt",i,"samp",-1);        
        can1l_e__jetpt->addStackWithSumMC(*this,"1l_e__jetpt",i,"samp",-1);        


        can2los_ee__jeteta->addStackWithSumMC(*this,"2los_ee__jeteta",i,"samp",-1);      
        can2los_emu__jeteta->addStackWithSumMC(*this,"2los_emu__jeteta",i,"samp",-1);     
        can2los_mumu__jeteta->addStackWithSumMC(*this,"2los_mumu__jeteta",i,"samp",-1);    
        can2los_sfz_ee__jeteta->addStackWithSumMC(*this,"2los_sfz_ee__jeteta",i,"samp",-1);  
        can2los_sfz_mumu__jeteta->addStackWithSumMC(*this,"2los_sfz_mumu__jeteta",i,"samp",-1);
//         can2lss_p_ee__jeteta->addStackWithSumMC(*this,"2lss_p_ee__jeteta",i,"samp",5);    
//         can2lss_p_emu__jeteta->addStackWithSumMC(*this,"2lss_p_emu__jeteta",i,"samp",5);   
//         can2lss_p_mumu__jeteta->addStackWithSumMC(*this,"2lss_p_mumu__jeteta",i,"samp",5);  
//         can2lss_m_ee__jeteta->addStackWithSumMC(*this,"2lss_m_ee__jeteta",i,"samp",5);    
//         can2lss_m_emu__jeteta->addStackWithSumMC(*this,"2lss_m_emu__jeteta",i,"samp",5);   
//         can2lss_m_mumu__jeteta->addStackWithSumMC(*this,"2lss_m_mumu__jeteta",i,"samp",5);  
//         can3l_ppp__jeteta->addStackWithSumMC(*this,"3l_ppp__jeteta",i,"samp",5);       
//         can3l_mmm__jeteta->addStackWithSumMC(*this,"3l_mmm__jeteta",i,"samp",5);       
//         can3l_mix__jeteta->addStackWithSumMC(*this,"3l_mix__jeteta",i,"samp",5);       
//         can3l_mix_sfz__jeteta->addStackWithSumMC(*this,"3l_mix_sfz__jeteta",i,"samp",5);   
//         cange4l__jeteta->addStackWithSumMC(*this,"ge4l__jeteta",i,"samp",5);        
        can1l_mu__jeteta->addStackWithSumMC(*this,"1l_mu__jeteta",i,"samp",-1);        
        can1l_e__jeteta->addStackWithSumMC(*this,"1l_e__jeteta",i,"samp",-1);        


        can2los_ee__jetcsv->addStackWithSumMC(*this,"2los_ee__jetcsv",i,"samp",-1);      
        can2los_emu__jetcsv->addStackWithSumMC(*this,"2los_emu__jetcsv",i,"samp",-1);     
        can2los_mumu__jetcsv->addStackWithSumMC(*this,"2los_mumu__jetcsv",i,"samp",-1);    
        can2los_sfz_ee__jetcsv->addStackWithSumMC(*this,"2los_sfz_ee__jetcsv",i,"samp",-1);  
        can2los_sfz_mumu__jetcsv->addStackWithSumMC(*this,"2los_sfz_mumu__jetcsv",i,"samp",-1);
//         can2lss_p_ee__jetcsv->addStackWithSumMC(*this,"2lss_p_ee__jetcsv",i,"samp",5);    
//         can2lss_p_emu__jetcsv->addStackWithSumMC(*this,"2lss_p_emu__jetcsv",i,"samp",5);   
//         can2lss_p_mumu__jetcsv->addStackWithSumMC(*this,"2lss_p_mumu__jetcsv",i,"samp",5);  
//         can2lss_m_ee__jetcsv->addStackWithSumMC(*this,"2lss_m_ee__jetcsv",i,"samp",5);    
//         can2lss_m_emu__jetcsv->addStackWithSumMC(*this,"2lss_m_emu__jetcsv",i,"samp",5);   
//         can2lss_m_mumu__jetcsv->addStackWithSumMC(*this,"2lss_m_mumu__jetcsv",i,"samp",5);  
//         can3l_ppp__jetcsv->addStackWithSumMC(*this,"3l_ppp__jetcsv",i,"samp",5);       
//         can3l_mmm__jetcsv->addStackWithSumMC(*this,"3l_mmm__jetcsv",i,"samp",5);       
//         can3l_mix__jetcsv->addStackWithSumMC(*this,"3l_mix__jetcsv",i,"samp",5);       
//         can3l_mix_sfz__jetcsv->addStackWithSumMC(*this,"3l_mix_sfz__jetcsv",i,"samp",5);   
//         cange4l__jetcsv->addStackWithSumMC(*this,"ge4l__jetcsv",i,"samp",5);        
        can1l_mu__jetcsv->addStackWithSumMC(*this,"1l_mu__jetcsv",i,"samp",-1);        
        can1l_e__jetcsv->addStackWithSumMC(*this,"1l_e__jetcsv",i,"samp",-1);        


        can2los_ee__leppt->addStackWithSumMC(*this,"2los_ee__leppt",i,"samp",-1);       
        can2los_emu__leppt->addStackWithSumMC(*this,"2los_emu__leppt",i,"samp",-1);      
        can2los_mumu__leppt->addStackWithSumMC(*this,"2los_mumu__leppt",i,"samp",-1);     
        can2los_sfz_ee__leppt->addStackWithSumMC(*this,"2los_sfz_ee__leppt",i,"samp",-1);   
        can2los_sfz_mumu__leppt->addStackWithSumMC(*this,"2los_sfz_mumu__leppt",i,"samp",-1); 
//         can2lss_p_ee__leppt->addStackWithSumMC(*this,"2lss_p_ee__leppt",i,"samp",5);     
//         can2lss_p_emu__leppt->addStackWithSumMC(*this,"2lss_p_emu__leppt",i,"samp",5);    
//         can2lss_p_mumu__leppt->addStackWithSumMC(*this,"2lss_p_mumu__leppt",i,"samp",5);   
//         can2lss_m_ee__leppt->addStackWithSumMC(*this,"2lss_m_ee__leppt",i,"samp",5);     
//         can2lss_m_emu__leppt->addStackWithSumMC(*this,"2lss_m_emu__leppt",i,"samp",5);    
//         can2lss_m_mumu__leppt->addStackWithSumMC(*this,"2lss_m_mumu__leppt",i,"samp",5);   
//         can3l_ppp__leppt->addStackWithSumMC(*this,"3l_ppp__leppt",i,"samp",5);        
//         can3l_mmm__leppt->addStackWithSumMC(*this,"3l_mmm__leppt",i,"samp",5);        
//         can3l_mix__leppt->addStackWithSumMC(*this,"3l_mix__leppt",i,"samp",5);        
//         can3l_mix_sfz__leppt->addStackWithSumMC(*this,"3l_mix_sfz__leppt",i,"samp",5);   
//         cange4l__leppt->addStackWithSumMC(*this,"ge4l__leppt",i,"samp",5);        
        can1l_mu__leppt->addStackWithSumMC(*this,"1l_mu__leppt",i,"samp",-1);        
        can1l_e__leppt->addStackWithSumMC(*this,"1l_e__leppt",i,"samp",-1);        


        can2los_ee__lepeta->addStackWithSumMC(*this,"2los_ee__lepeta",i,"samp",-1);      
        can2los_emu__lepeta->addStackWithSumMC(*this,"2los_emu__lepeta",i,"samp",-1);     
        can2los_mumu__lepeta->addStackWithSumMC(*this,"2los_mumu__lepeta",i,"samp",-1);
        can2los_sfz_ee__lepeta->addStackWithSumMC(*this,"2los_sfz_ee__lepeta",i,"samp",-1);  
        can2los_sfz_mumu__lepeta->addStackWithSumMC(*this,"2los_sfz_mumu__lepeta",i,"samp",-1);
//         can2lss_p_ee__lepeta->addStackWithSumMC(*this,"2lss_p_ee__lepeta",i,"samp",5);
//         can2lss_p_emu__lepeta->addStackWithSumMC(*this,"2lss_p_emu__lepeta",i,"samp",5);
//         can2lss_p_mumu__lepeta->addStackWithSumMC(*this,"2lss_p_mumu__lepeta",i,"samp",5);  
//         can2lss_m_ee__lepeta->addStackWithSumMC(*this,"2lss_m_ee__lepeta",i,"samp",5);    
//         can2lss_m_emu__lepeta->addStackWithSumMC(*this,"2lss_m_emu__lepeta",i,"samp",5);   
//         can2lss_m_mumu__lepeta->addStackWithSumMC(*this,"2lss_m_mumu__lepeta",i,"samp",5);  
//         can3l_ppp__lepeta->addStackWithSumMC(*this,"3l_ppp__lepeta",i,"samp",5);       
//         can3l_mmm__lepeta->addStackWithSumMC(*this,"3l_mmm__lepeta",i,"samp",5);       
//         can3l_mix__lepeta->addStackWithSumMC(*this,"3l_mix__lepeta",i,"samp",5);       
//         can3l_mix_sfz__lepeta->addStackWithSumMC(*this,"3l_mix_sfz__lepeta",i,"samp",5);  
//         cange4l__lepeta->addStackWithSumMC(*this,"ge4l__lepeta",i,"samp",5);        
        can1l_mu__lepeta->addStackWithSumMC(*this,"1l_mu__lepeta",i,"samp",-1);        
        can1l_e__lepeta->addStackWithSumMC(*this,"1l_e__lepeta",i,"samp",-1);        



        can2los_ee__met->addStackWithSumMC(*this,"2los_ee__met",i,"samp",-1);        
        can2los_emu__met->addStackWithSumMC(*this,"2los_emu__met",i,"samp",-1);        
        can2los_mumu__met->addStackWithSumMC(*this,"2los_mumu__met",i,"samp",-1);       
        can2los_sfz_ee__met->addStackWithSumMC(*this,"2los_sfz_ee__met",i,"samp",-1);     
        can2los_sfz_mumu__met->addStackWithSumMC(*this,"2los_sfz_mumu__met",i,"samp",-1);   
//         can2lss_p_ee__met->addStackWithSumMC(*this,"2lss_p_ee__met",i,"samp",5);       
//         can2lss_p_emu__met->addStackWithSumMC(*this,"2lss_p_emu__met",i,"samp",5);      
//         can2lss_p_mumu__met->addStackWithSumMC(*this,"2lss_p_mumu__met",i,"samp",5);     
//         can2lss_m_ee__met->addStackWithSumMC(*this,"2lss_m_ee__met",i,"samp",5);       
//         can2lss_m_emu__met->addStackWithSumMC(*this,"2lss_m_emu__met",i,"samp",5);      
//         can2lss_m_mumu__met->addStackWithSumMC(*this,"2lss_m_mumu__met",i,"samp",5);     
//         can3l_ppp__met->addStackWithSumMC(*this,"3l_ppp__met",i,"samp",5);        
//         can3l_mmm__met->addStackWithSumMC(*this,"3l_mmm__met",i,"samp",5);        
//         can3l_mix__met->addStackWithSumMC(*this,"3l_mix__met",i,"samp",5);        
//         can3l_mix_sfz__met->addStackWithSumMC(*this,"3l_mix_sfz__met",i,"samp",5);      
//         cange4l__met->addStackWithSumMC(*this,"ge4l__met",i,"samp",5);        
        can1l_mu__met->addStackWithSumMC(*this,"1l_mu__met",i,"samp",-1);        
        can1l_e__met->addStackWithSumMC(*this,"1l_e__met",i,"samp",-1);        

        can2los_ee__metphi->addStackWithSumMC(*this,"2los_ee__metphi",i,"samp",-1);      
        can2los_emu__metphi->addStackWithSumMC(*this,"2los_emu__metphi",i,"samp",-1);     
        can2los_mumu__metphi->addStackWithSumMC(*this,"2los_mumu__metphi",i,"samp",-1);    
        can2los_sfz_ee__metphi->addStackWithSumMC(*this,"2los_sfz_ee__metphi",i,"samp",-1);  
        can2los_sfz_mumu__metphi->addStackWithSumMC(*this,"2los_sfz_mumu__metphi",i,"samp",-1);
//         can2lss_p_ee__metphi->addStackWithSumMC(*this,"2lss_p_ee__metphi",i,"samp",5);    
//         can2lss_p_emu__metphi->addStackWithSumMC(*this,"2lss_p_emu__metphi",i,"samp",5);   
//         can2lss_p_mumu__metphi->addStackWithSumMC(*this,"2lss_p_mumu__metphi",i,"samp",5);  
//         can2lss_m_ee__metphi->addStackWithSumMC(*this,"2lss_m_ee__metphi",i,"samp",5);    
//         can2lss_m_emu__metphi->addStackWithSumMC(*this,"2lss_m_emu__metphi",i,"samp",5);   
//         can2lss_m_mumu__metphi->addStackWithSumMC(*this,"2lss_m_mumu__metphi",i,"samp",5);  
//         can3l_ppp__metphi->addStackWithSumMC(*this,"3l_ppp__metphi",i,"samp",5);       
//         can3l_mmm__metphi->addStackWithSumMC(*this,"3l_mmm__metphi",i,"samp",5);       
//         can3l_mix__metphi->addStackWithSumMC(*this,"3l_mix__metphi",i,"samp",5);       
//         can3l_mix_sfz__metphi->addStackWithSumMC(*this,"3l_mix_sfz__metphi",i,"samp",5);   
//         cange4l__metphi->addStackWithSumMC(*this,"ge4l__metphi",i,"samp",5);        
        can1l_mu__metphi->addStackWithSumMC(*this,"1l_mu__metphi",i,"samp",-1);
        can1l_e__metphi->addStackWithSumMC(*this,"1l_e__metphi",i,"samp",-1);

        can2los_ee__numPVs->addStackWithSumMC(*this,"2los_ee__numPVs",i,"samp",-1);      
        can2los_emu__numPVs->addStackWithSumMC(*this,"2los_emu__numPVs",i,"samp",-1);     
        can2los_mumu__numPVs->addStackWithSumMC(*this,"2los_mumu__numPVs",i,"samp",-1);    
        can2los_sfz_ee__numPVs->addStackWithSumMC(*this,"2los_sfz_ee__numPVs",i,"samp",-1);  
        can2los_sfz_mumu__numPVs->addStackWithSumMC(*this,"2los_sfz_mumu__numPVs",i,"samp",-1);
//         can2lss_p_ee__numPVs->addStackWithSumMC(*this,"2lss_p_ee__numPVs",i,"samp",5);    
//         can2lss_p_emu__numPVs->addStackWithSumMC(*this,"2lss_p_emu__numPVs",i,"samp",5);   
//         can2lss_p_mumu__numPVs->addStackWithSumMC(*this,"2lss_p_mumu__numPVs",i,"samp",5);  
//         can2lss_m_ee__numPVs->addStackWithSumMC(*this,"2lss_m_ee__numPVs",i,"samp",5);    
//         can2lss_m_emu__numPVs->addStackWithSumMC(*this,"2lss_m_emu__numPVs",i,"samp",5);   
//         can2lss_m_mumu__numPVs->addStackWithSumMC(*this,"2lss_m_mumu__numPVs",i,"samp",5);  
//         can3l_ppp__numPVs->addStackWithSumMC(*this,"3l_ppp__numPVs",i,"samp",5);       
//         can3l_mmm__numPVs->addStackWithSumMC(*this,"3l_mmm__numPVs",i,"samp",5);       
//         can3l_mix__numPVs->addStackWithSumMC(*this,"3l_mix__numPVs",i,"samp",5);       
//         can3l_mix_sfz__numPVs->addStackWithSumMC(*this,"3l_mix_sfz__numPVs",i,"samp",5);   
//         cange4l__numPVs->addStackWithSumMC(*this,"ge4l__numPVs",i,"samp",5);        
        can1l_mu__numPVs->addStackWithSumMC(*this,"1l_mu__numPVs",i,"samp",-1);
        can1l_e__numPVs->addStackWithSumMC(*this,"1l_e__numPVs",i,"samp",-1);
        
        can2los_ee__lep1pt->addStackWithSumMC(*this,"2los_ee__lep1pt",i,"samp",-1);      
        can2los_emu__lep1pt->addStackWithSumMC(*this,"2los_emu__lep1pt",i,"samp",-1);     
        can2los_mumu__lep1pt->addStackWithSumMC(*this,"2los_mumu__lep1pt",i,"samp",-1);    
        can2los_sfz_ee__lep1pt->addStackWithSumMC(*this,"2los_sfz_ee__lep1pt",i,"samp",-1);  
        can2los_sfz_mumu__lep1pt->addStackWithSumMC(*this,"2los_sfz_mumu__lep1pt",i,"samp",-1);
//             can2lss_p_ee__lep1pt->addStackWithSumMC(*this,"2lss_p_ee__lep1pt",i,"samp",5);    
//             can2lss_p_emu__lep1pt->addStackWithSumMC(*this,"2lss_p_emu__lep1pt",i,"samp",5);   
//             can2lss_p_mumu__lep1pt->addStackWithSumMC(*this,"2lss_p_mumu__lep1pt",i,"samp",5);  
//             can2lss_m_ee__lep1pt->addStackWithSumMC(*this,"2lss_m_ee__lep1pt",i,"samp",5);    
//             can2lss_m_emu__lep1pt->addStackWithSumMC(*this,"2lss_m_emu__lep1pt",i,"samp",5);   
//             can2lss_m_mumu__lep1pt->addStackWithSumMC(*this,"2lss_m_mumu__lep1pt",i,"samp",5);  
//             can3l_ppp__lep1pt->addStackWithSumMC(*this,"3l_ppp__lep1pt",i,"samp",5);       
//             can3l_mmm__lep1pt->addStackWithSumMC(*this,"3l_mmm__lep1pt",i,"samp",5);       
//             can3l_mix__lep1pt->addStackWithSumMC(*this,"3l_mix__lep1pt",i,"samp",5);       
//             can3l_mix_sfz__lep1pt->addStackWithSumMC(*this,"3l_mix_sfz__lep1pt",i,"samp",5);   
//             cange4l__lep1pt->addStackWithSumMC(*this,"ge4l__lep1pt",i,"samp",5);
        can1l_mu__lep1pt->addStackWithSumMC(*this,"1l_mu__lep1pt",i,"samp",-1);
        can1l_e__lep1pt->addStackWithSumMC(*this,"1l_e__lep1pt",i,"samp",-1);            
        
        can2los_ee__lep2pt->addStackWithSumMC(*this,"2los_ee__lep2pt",i,"samp",-1);      
        can2los_emu__lep2pt->addStackWithSumMC(*this,"2los_emu__lep2pt",i,"samp",-1);     
        can2los_mumu__lep2pt->addStackWithSumMC(*this,"2los_mumu__lep2pt",i,"samp",-1);    
        can2los_sfz_ee__lep2pt->addStackWithSumMC(*this,"2los_sfz_ee__lep2pt",i,"samp",-1);  
        can2los_sfz_mumu__lep2pt->addStackWithSumMC(*this,"2los_sfz_mumu__lep2pt",i,"samp",-1);
//             can2lss_p_ee__lep2pt->addStackWithSumMC(*this,"2lss_p_ee__lep2pt",i,"samp",5);    
//             can2lss_p_emu__lep2pt->addStackWithSumMC(*this,"2lss_p_emu__lep2pt",i,"samp",5);   
//             can2lss_p_mumu__lep2pt->addStackWithSumMC(*this,"2lss_p_mumu__lep2pt",i,"samp",5);  
//             can2lss_m_ee__lep2pt->addStackWithSumMC(*this,"2lss_m_ee__lep2pt",i,"samp",5);    
//             can2lss_m_emu__lep2pt->addStackWithSumMC(*this,"2lss_m_emu__lep2pt",i,"samp",5);   
//             can2lss_m_mumu__lep2pt->addStackWithSumMC(*this,"2lss_m_mumu__lep2pt",i,"samp",5);  
//             can3l_ppp__lep2pt->addStackWithSumMC(*this,"3l_ppp__lep2pt",i,"samp",5);       
//             can3l_mmm__lep2pt->addStackWithSumMC(*this,"3l_mmm__lep2pt",i,"samp",5);       
//             can3l_mix__lep2pt->addStackWithSumMC(*this,"3l_mix__lep2pt",i,"samp",5);       
//             can3l_mix_sfz__lep2pt->addStackWithSumMC(*this,"3l_mix_sfz__lep2pt",i,"samp",5);   
//             cange4l__lep2pt->addStackWithSumMC(*this,"ge4l__lep2pt",i,"samp",5);         
        
        
        can2los_ee__llmass->addStackWithSumMC(*this,"2los_ee__llmass",i,"samp",-1);      
        can2los_emu__llmass->addStackWithSumMC(*this,"2los_emu__llmass",i,"samp",-1);     
        can2los_mumu__llmass->addStackWithSumMC(*this,"2los_mumu__llmass",i,"samp",-1);    
        can2los_sfz_ee__llmass->addStackWithSumMC(*this,"2los_sfz_ee__llmass",i,"samp",-1);  
        can2los_sfz_mumu__llmass->addStackWithSumMC(*this,"2los_sfz_mumu__llmass",i,"samp",-1);
//             can2lss_p_ee__llmass->addStackWithSumMC(*this,"2lss_p_ee__llmass",i,"samp",5);    
//             can2lss_p_emu__llmass->addStackWithSumMC(*this,"2lss_p_emu__llmass",i,"samp",5);   
//             can2lss_p_mumu__llmass->addStackWithSumMC(*this,"2lss_p_mumu__llmass",i,"samp",5);  
//             can2lss_m_ee__llmass->addStackWithSumMC(*this,"2lss_m_ee__llmass",i,"samp",5);    
//             can2lss_m_emu__llmass->addStackWithSumMC(*this,"2lss_m_emu__llmass",i,"samp",5);   
//             can2lss_m_mumu__llmass->addStackWithSumMC(*this,"2lss_m_mumu__llmass",i,"samp",5);  
      
        
        can2los_ee__MHT->addStackWithSumMC(*this,"2los_ee__MHT",i,"samp",-1);      
        can2los_emu__MHT->addStackWithSumMC(*this,"2los_emu__MHT",i,"samp",-1);     
        can2los_mumu__MHT->addStackWithSumMC(*this,"2los_mumu__MHT",i,"samp",-1);    
        can2los_sfz_ee__MHT->addStackWithSumMC(*this,"2los_sfz_ee__MHT",i,"samp",-1);  
        can2los_sfz_mumu__MHT->addStackWithSumMC(*this,"2los_sfz_mumu__MHT",i,"samp",-1);
//             can2lss_p_ee__MHT->addStackWithSumMC(*this,"2lss_p_ee__MHT",i,"samp",5);    
//             can2lss_p_emu__MHT->addStackWithSumMC(*this,"2lss_p_emu__MHT",i,"samp",5);   
//             can2lss_p_mumu__MHT->addStackWithSumMC(*this,"2lss_p_mumu__MHT",i,"samp",5);  
//             can2lss_m_ee__MHT->addStackWithSumMC(*this,"2lss_m_ee__MHT",i,"samp",5);    
//             can2lss_m_emu__MHT->addStackWithSumMC(*this,"2lss_m_emu__MHT",i,"samp",5);   
//             can2lss_m_mumu__MHT->addStackWithSumMC(*this,"2lss_m_mumu__MHT",i,"samp",5);  
//             can3l_ppp__MHT->addStackWithSumMC(*this,"3l_ppp__MHT",i,"samp",5);       
//             can3l_mmm__MHT->addStackWithSumMC(*this,"3l_mmm__MHT",i,"samp",5);       
//             can3l_mix__MHT->addStackWithSumMC(*this,"3l_mix__MHT",i,"samp",5);       
//             can3l_mix_sfz__MHT->addStackWithSumMC(*this,"3l_mix_sfz__MHT",i,"samp",5);   
//             cange4l__MHT->addStackWithSumMC(*this,"ge4l__MHT",i,"samp",5);
        can1l_mu__MHT->addStackWithSumMC(*this,"1l_mu__MHT",i,"samp",-1);
        can1l_e__MHT->addStackWithSumMC(*this,"1l_e__MHT",i,"samp",-1);            

//         can2los_ee__lepMVA->addStackWithSumMC(*this,"2los_ee__lepMVA",i,"samp",-1);      
//         can2los_emu__lepMVA->addStackWithSumMC(*this,"2los_emu__lepMVA",i,"samp",-1);     
//         can2los_mumu__lepMVA->addStackWithSumMC(*this,"2los_mumu__lepMVA",i,"samp",-1);    
//         can2los_sfz_ee__lepMVA->addStackWithSumMC(*this,"2los_sfz_ee__lepMVA",i,"samp",-1);  
//         can2los_sfz_mumu__lepMVA->addStackWithSumMC(*this,"2los_sfz_mumu__lepMVA",i,"samp",-1);
// //             can2lss_p_ee__lepMVA->addStackWithSumMC(*this,"2lss_p_ee__lepMVA",i,"samp",5);    
// //             can2lss_p_emu__lepMVA->addStackWithSumMC(*this,"2lss_p_emu__lepMVA",i,"samp",5);   
// //             can2lss_p_mumu__lepMVA->addStackWithSumMC(*this,"2lss_p_mumu__lepMVA",i,"samp",5);  
// //             can2lss_m_ee__lepMVA->addStackWithSumMC(*this,"2lss_m_ee__lepMVA",i,"samp",5);    
// //             can2lss_m_emu__lepMVA->addStackWithSumMC(*this,"2lss_m_emu__lepMVA",i,"samp",5);   
// //             can2lss_m_mumu__lepMVA->addStackWithSumMC(*this,"2lss_m_mumu__lepMVA",i,"samp",5);  
// //             can3l_ppp__lepMVA->addStackWithSumMC(*this,"3l_ppp__lepMVA",i,"samp",5);       
// //             can3l_mmm__lepMVA->addStackWithSumMC(*this,"3l_mmm__lepMVA",i,"samp",5);       
// //             can3l_mix__lepMVA->addStackWithSumMC(*this,"3l_mix__lepMVA",i,"samp",5);       
// //             can3l_mix_sfz__lepMVA->addStackWithSumMC(*this,"3l_mix_sfz__lepMVA",i,"samp",5);   
// //             cange4l__lepMVA->addStackWithSumMC(*this,"ge4l__lepMVA",i,"samp",5);
//         can1l_mu__lepMVA->addStackWithSumMC(*this,"1l_mu__lepMVA",i,"samp",-1);
//         can1l_e__lepMVA->addStackWithSumMC(*this,"1l_e__lepMVA",i,"samp",-1);


        can2los_ee__PUMVA->addStackWithSumMC(*this,"2los_ee__PUMVA",i,"samp",-1);      
        can2los_emu__PUMVA->addStackWithSumMC(*this,"2los_emu__PUMVA",i,"samp",-1);     
        can2los_mumu__PUMVA->addStackWithSumMC(*this,"2los_mumu__PUMVA",i,"samp",-1);    
        can2los_sfz_ee__PUMVA->addStackWithSumMC(*this,"2los_sfz_ee__PUMVA",i,"samp",-1);  
        can2los_sfz_mumu__PUMVA->addStackWithSumMC(*this,"2los_sfz_mumu__PUMVA",i,"samp",-1);
//             can2lss_p_ee__PUMVA->addStackWithSumMC(*this,"2lss_p_ee__PUMVA",i,"samp",5);    
//             can2lss_p_emu__PUMVA->addStackWithSumMC(*this,"2lss_p_emu__PUMVA",i,"samp",5);   
//             can2lss_p_mumu__PUMVA->addStackWithSumMC(*this,"2lss_p_mumu__PUMVA",i,"samp",5);  
//             can2lss_m_ee__PUMVA->addStackWithSumMC(*this,"2lss_m_ee__PUMVA",i,"samp",5);    
//             can2lss_m_emu__PUMVA->addStackWithSumMC(*this,"2lss_m_emu__PUMVA",i,"samp",5);   
//             can2lss_m_mumu__PUMVA->addStackWithSumMC(*this,"2lss_m_mumu__PUMVA",i,"samp",5);  
//             can3l_ppp__PUMVA->addStackWithSumMC(*this,"3l_ppp__PUMVA",i,"samp",5);       
//             can3l_mmm__PUMVA->addStackWithSumMC(*this,"3l_mmm__PUMVA",i,"samp",5);       
//             can3l_mix__PUMVA->addStackWithSumMC(*this,"3l_mix__PUMVA",i,"samp",5);       
//             can3l_mix_sfz__PUMVA->addStackWithSumMC(*this,"3l_mix_sfz__PUMVA",i,"samp",5);   
//             cange4l__PUMVA->addStackWithSumMC(*this,"ge4l__PUMVA",i,"samp",5);
        can1l_mu__PUMVA->addStackWithSumMC(*this,"1l_mu__PUMVA",i,"samp",-1);
        can1l_e__PUMVA->addStackWithSumMC(*this,"1l_e__PUMVA",i,"samp",-1);
        
        // when using this function, no need to manually add the plots to the "canvas" object
//         makeAndAdd2DPlot1Sample(*this,i,"2los_ee__nbjets_vs_njets"); 
//         makeAndAdd2DPlot1Sample(*this,i,"2los_emu__nbjets_vs_njets");
//         makeAndAdd2DPlot1Sample(*this,i,"2los_mumu__nbjets_vs_njets");
//         makeAndAdd2DPlot1Sample(*this,i,"2los_sfz_ee__nbjets_vs_njets");  
//         makeAndAdd2DPlot1Sample(*this,i,"2los_sfz_mumu__nbjets_vs_njets");
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_p_ee__nbjets_vs_njets");    
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_p_emu__nbjets_vs_njets");   
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_p_mumu__nbjets_vs_njets");  
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_m_ee__nbjets_vs_njets");    
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_m_emu__nbjets_vs_njets");   
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_m_mumu__nbjets_vs_njets");  
//         makeAndAdd2DPlot1Sample(*this,i,"3l_ppp__nbjets_vs_njets");       
//         makeAndAdd2DPlot1Sample(*this,i,"3l_mmm__nbjets_vs_njets");       
//         makeAndAdd2DPlot1Sample(*this,i,"3l_mix__nbjets_vs_njets");       
//         makeAndAdd2DPlot1Sample(*this,i,"3l_mix_sfz__nbjets_vs_njets");   
//         makeAndAdd2DPlot1Sample(*this,i,"ge4l__nbjets_vs_njets");                 
                
        
        cout << " " << endl;      
        double eff = ((TH1D*)hist[i].FindObject("single_ele_trigs"))->GetBinContent(2);
        double denom = ((TH1D*)hist[i].FindObject("single_ele_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "single_ele_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("single_mu_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("single_mu_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "single_mu_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("double_mu_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("double_mu_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "double_mu_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("double_ele_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("double_ele_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "double_ele_trigs eff: " << eff << endl;
        
        eff = ((TH1D*)hist[i].FindObject("mu_ele_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("mu_ele_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "mu_ele_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "all_trigs eff: " << eff << endl;
        cout << " " << endl;
        
        eff = ((TH1D*)hist[i].FindObject("2los_ee__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_ee__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_ee__all_trigs eff: " << eff << endl;                     
        
        eff = ((TH1D*)hist[i].FindObject("2los_emu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_emu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_emu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2los_mumu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_mumu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_mumu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2los_sfz_ee__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_sfz_ee__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_sfz_ee__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2los_sfz_mumu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_sfz_mumu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_sfz_mumu__all_trigs eff: " << eff << endl;                      
        
        eff = ((TH1D*)hist[i].FindObject("2lss_p_ee__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_p_ee__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_p_ee__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2lss_p_emu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_p_emu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_p_emu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2lss_p_mumu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_p_mumu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_p_mumu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2lss_m_ee__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_m_ee__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_m_ee__all_trigs eff: " << eff << endl;
                              
        eff = ((TH1D*)hist[i].FindObject("2lss_m_emu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_m_emu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_m_emu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2lss_m_mumu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_m_mumu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_m_mumu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("3l_ppp__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("3l_ppp__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "3l_ppp__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("3l_mmm__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("3l_mmm__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "3l_mmm__all_trigs eff: " << eff << endl;                      
        
        eff = ((TH1D*)hist[i].FindObject("3l_mix__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("3l_mix__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "3l_mix__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("3l_mix_sfz__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("3l_mix_sfz__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "3l_mix_sfz__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("4l__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("4l__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "4l__all_trigs eff: " << eff << endl;
        cout << " " << endl;        
        
         
    }
  
    //can1->printStackContents();
    cancategory_yields_njets_nbjets->printStackContents();
        
               
    
    
}
