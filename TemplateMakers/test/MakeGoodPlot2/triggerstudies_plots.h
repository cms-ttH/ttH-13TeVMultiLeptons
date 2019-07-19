void MakeGoodPlot::triggerstudies_plots()
{

    GoodPlot *SSeePt_lep1_eff = new GoodPlot("SSeePt_lep1_eff","br");
    GoodPlot *SSeuPt_lep1_eff = new GoodPlot("SSeuPt_lep1_eff","br");
    GoodPlot *SSuePt_lep1_eff = new GoodPlot("SSuePt_lep1_eff","br"); 
    GoodPlot *SSuuPt_lep1_eff = new GoodPlot("SSuuPt_lep1_eff","br"); 
    GoodPlot *SS3lPt_lep1_eff = new GoodPlot("SS3lPt_lep1_eff","br"); 

    GoodPlot *SSeePt_lep2_eff = new GoodPlot("SSeePt_lep2_eff","br");
    GoodPlot *SSeuPt_lep2_eff = new GoodPlot("SSeuPt_lep2_eff","br"); 
    GoodPlot *SSuePt_lep2_eff = new GoodPlot("SSuePt_lep2_eff","br");
    GoodPlot *SSuuPt_lep2_eff = new GoodPlot("SSuuPt_lep2_eff","br"); 
    GoodPlot *SS3lPt_lep2_eff = new GoodPlot("SS3lPt_lep2_eff","br"); 

    GoodPlot *SSeeEta_lep1_eff = new GoodPlot("SSeeEta_lep1_eff","br");
    GoodPlot *SSeuEta_lep1_eff = new GoodPlot("SSeuEta_lep1_eff","br");
    GoodPlot *SSueEta_lep1_eff = new GoodPlot("SSueEta_lep1_eff","br");
    GoodPlot *SSuuEta_lep1_eff = new GoodPlot("SSuuEta_lep1_eff","br");
    GoodPlot *SS3lEta_lep1_eff = new GoodPlot("SS3lEta_lep1_eff","br");
    GoodPlot *SSeeEta_lep2_eff = new GoodPlot("SSeeEta_lep2_eff","br");
    GoodPlot *SSeuEta_lep2_eff = new GoodPlot("SSeuEta_lep2_eff","br");
    GoodPlot *SSueEta_lep2_eff = new GoodPlot("SSueEta_lep2_eff","br");
    GoodPlot *SSuuEta_lep2_eff = new GoodPlot("SSuuEta_lep2_eff","br");
    GoodPlot *SS3lEta_lep2_eff = new GoodPlot("SS3lEta_lep2_eff","br");
    GoodPlot *SS3l_total_eff = new GoodPlot("SS3l_total_eff","br");
    GoodPlot *SSuu_total_eff = new GoodPlot("SSuu_total_eff","br");
    GoodPlot *SSeu_total_eff = new GoodPlot("SSeu_total_eff","br");
    GoodPlot *SSee_total_eff = new GoodPlot("SSee_total_eff","br"); 
    

    for (int i=0; i<numsamples; i++)
    {
    
        SSeePt_lep1_eff->addEfficiencyPlot(*this,"SSeePt_lep1_numer","SSeePt_lep1_denom",i);
        
        SSeuPt_lep1_eff->addEfficiencyPlot(*this,"SSeuPt_lep1_numer","SSeuPt_lep1_denom",i);
        SSuePt_lep1_eff->addEfficiencyPlot(*this,"SSuePt_lep1_numer","SSuePt_lep1_denom",i);
        SSuuPt_lep1_eff->addEfficiencyPlot(*this,"SSuuPt_lep1_numer","SSuuPt_lep1_denom",i);
        SS3lPt_lep1_eff->addEfficiencyPlot(*this,"SS3lPt_lep1_numer","SS3lPt_lep1_denom",i);

        SSeePt_lep2_eff->addEfficiencyPlot(*this,"SSeePt_lep2_numer","SSeePt_lep2_denom",i);
        SSeuPt_lep2_eff->addEfficiencyPlot(*this,"SSeuPt_lep2_numer","SSeuPt_lep2_denom",i);
        SSuePt_lep2_eff->addEfficiencyPlot(*this,"SSuePt_lep2_numer","SSuePt_lep2_denom",i);
        SSuuPt_lep2_eff->addEfficiencyPlot(*this,"SSuuPt_lep2_numer","SSuuPt_lep2_denom",i);
        SS3lPt_lep2_eff->addEfficiencyPlot(*this,"SS3lPt_lep2_numer","SS3lPt_lep2_denom",i);

        SSeeEta_lep1_eff->addEfficiencyPlot(*this,"SSeeEta_lep1_numer","SSeeEta_lep1_denom",i);
        SSeuEta_lep1_eff->addEfficiencyPlot(*this,"SSeuEta_lep1_numer","SSeuEta_lep1_denom",i);
        SSueEta_lep1_eff->addEfficiencyPlot(*this,"SSueEta_lep1_numer","SSueEta_lep1_denom",i);
        SSuuEta_lep1_eff->addEfficiencyPlot(*this,"SSuuEta_lep1_numer","SSuuEta_lep1_denom",i);
        SS3lEta_lep1_eff->addEfficiencyPlot(*this,"SS3lEta_lep1_numer","SS3lEta_lep1_denom",i);
        SSeeEta_lep2_eff->addEfficiencyPlot(*this,"SSeeEta_lep2_numer","SSeeEta_lep2_denom",i);
        SSeuEta_lep2_eff->addEfficiencyPlot(*this,"SSeuEta_lep2_numer","SSeuEta_lep2_denom",i);
        SSueEta_lep2_eff->addEfficiencyPlot(*this,"SSueEta_lep2_numer","SSueEta_lep2_denom",i);
        SSuuEta_lep2_eff->addEfficiencyPlot(*this,"SSuuEta_lep2_numer","SSuuEta_lep2_denom",i);
        SS3lEta_lep2_eff->addEfficiencyPlot(*this,"SS3lEta_lep2_numer","SS3lEta_lep2_denom",i);
        SS3l_total_eff->addEfficiencyPlot(*this,"SS3l_total_numer","SS3l_total_denom",i);
        SSuu_total_eff->addEfficiencyPlot(*this,"SSuu_total_numer","SSuu_total_denom",i);
        SSeu_total_eff->addEfficiencyPlot(*this,"SSeu_total_numer","SSeu_total_denom",i);
        SSee_total_eff->addEfficiencyPlot(*this,"SSee_total_numer","SSee_total_denom",i);  
    
   
        
        //can1->cd(), etc.
        // could try: can1->BuildLegend(); (prob won't have desired result tho)
        // can try new PLC PMC draw options
        
        
    }
    
    // cans should have been drawn

    canvas.Add(SSeePt_lep1_eff);
    canvas.Add(SSeuPt_lep1_eff);
    //canvas.Add(SSuePt_lep1_eff);
    canvas.Add(SSuuPt_lep1_eff);
    canvas.Add(SS3lPt_lep1_eff);
    
    canvas.Add(SSeePt_lep2_eff);
    canvas.Add(SSeuPt_lep2_eff);
    //canvas.Add(SSuePt_lep2_eff);
    canvas.Add(SSuuPt_lep2_eff);
    canvas.Add(SS3lPt_lep2_eff);
    
    canvas.Add(SSeeEta_lep1_eff);
    canvas.Add(SSeuEta_lep1_eff);
    //canvas.Add(SSueEta_lep1_eff);
    canvas.Add(SSuuEta_lep1_eff);
    canvas.Add(SS3lEta_lep1_eff);
    canvas.Add(SSeeEta_lep2_eff);
    canvas.Add(SSeuEta_lep2_eff);
    //canvas.Add(SSueEta_lep2_eff);
    canvas.Add(SSuuEta_lep2_eff);
    canvas.Add(SS3lEta_lep2_eff);
    canvas.Add(SS3l_total_eff);
    canvas.Add(SSuu_total_eff);
    canvas.Add(SSeu_total_eff);
    canvas.Add(SSee_total_eff);


    // that's it!
    
}