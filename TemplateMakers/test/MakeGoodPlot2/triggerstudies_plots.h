void MakeGoodPlot::triggerstudies_plots()
{

    TCanvas *SSeuPt_lep1_eff = new TCanvas("SSeuPt_lep1_eff","can",150,10,960,660);
    TCanvas *SSuePt_lep1_eff = new TCanvas("SSuePt_lep1_eff","can",150,10,960,660);    
    TCanvas *SSuuPt_lep1_eff = new TCanvas("SSuuPt_lep1_eff","can",150,10,960,660);    
    TCanvas *SS3lPt_lep1_eff = new TCanvas("SS3lPt_lep1_eff","can",150,10,960,660);    
    TCanvas *SSeePt_lep2_eff = new TCanvas("SSeePt_lep2_eff","can",150,10,960,660);    
    TCanvas *SSeuPt_lep2_eff = new TCanvas("SSeuPt_lep2_eff","can",150,10,960,660);    
    TCanvas *SSuePt_lep2_eff = new TCanvas("SSuePt_lep2_eff","can",150,10,960,660);    
    TCanvas *SSuuPt_lep2_eff = new TCanvas("SSuuPt_lep2_eff","can",150,10,960,660);    
    TCanvas *SS3lPt_lep2_eff = new TCanvas("SS3lPt_lep2_eff","can",150,10,960,660);    
    TCanvas *SSeeEta_lep1_eff = new TCanvas("SSeeEta_lep1_eff","can",150,10,960,660);    
    TCanvas *SSeuEta_lep1_eff = new TCanvas("SSeuEta_lep1_eff","can",150,10,960,660);    
    TCanvas *SSueEta_lep1_eff = new TCanvas("SSueEta_lep1_eff","can",150,10,960,660);    
    TCanvas *SSuuEta_lep1_eff = new TCanvas("SSuuEta_lep1_eff","can",150,10,960,660);    
    TCanvas *SS3lEta_lep1_eff = new TCanvas("SS3lEta_lep1_eff","can",150,10,960,660);    
    TCanvas *SSeeEta_lep2_eff = new TCanvas("SSeeEta_lep2_eff","can",150,10,960,660);    
    TCanvas *SSeuEta_lep2_eff = new TCanvas("SSeuEta_lep2_eff","can",150,10,960,660);    
    TCanvas *SSueEta_lep2_eff = new TCanvas("SSueEta_lep2_eff","can",150,10,960,660);    
    TCanvas *SSuuEta_lep2_eff = new TCanvas("SSuuEta_lep2_eff","can",150,10,960,660);    
    TCanvas *SS3lEta_lep2_eff = new TCanvas("SS3lEta_lep2_eff","can",150,10,960,660);    
    TCanvas *SS3l_total_eff = new TCanvas("SS3l_total_eff","can",150,10,960,660); 
    TCanvas *SSuu_total_eff = new TCanvas("SSuu_total_eff","can",150,10,960,660); 
    TCanvas *SSeu_total_eff = new TCanvas("SSeu_total_eff","can",150,10,960,660); 
    TCanvas *SSee_total_eff = new TCanvas("SSee_total_eff","can",150,10,960,660); 
    

    for (int i=0; i<numsamples; i++)
    {
    
        auto SSeePt_lep1_denom = (TH1D*)hist[i].FindObject("SSeePt_lep1_denom");
        auto SSeePt_lep1_numer = (TH1D*)hist[i].FindObject("SSeePt_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSeuPt_lep1_denom = (TH1D*)hist[i].FindObject("SSeuPt_lep1_denom");
        auto SSeuPt_lep1_numer = (TH1D*)hist[i].FindObject("SSeuPt_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSuePt_lep1_denom = (TH1D*)hist[i].FindObject("SSuePt_lep1_denom");
        auto SSuePt_lep1_numer = (TH1D*)hist[i].FindObject("SSuePt_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSuuPt_lep1_denom = (TH1D*)hist[i].FindObject("SSuuPt_lep1_denom");
        auto SSuuPt_lep1_numer = (TH1D*)hist[i].FindObject("SSuuPt_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SS3lPt_lep1_denom = (TH1D*)hist[i].FindObject("SS3lPt_lep1_denom");
        auto SS3lPt_lep1_numer = (TH1D*)hist[i].FindObject("SS3lPt_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);

        auto SSeePt_lep2_denom = (TH1D*)hist[i].FindObject("SSeePt_lep2_denom");
        auto SSeePt_lep2_numer = (TH1D*)hist[i].FindObject("SSeePt_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSeuPt_lep2_denom = (TH1D*)hist[i].FindObject("SSeuPt_lep2_denom");
        auto SSeuPt_lep2_numer = (TH1D*)hist[i].FindObject("SSeuPt_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSuePt_lep2_denom = (TH1D*)hist[i].FindObject("SSuePt_lep2_denom");
        auto SSuePt_lep2_numer = (TH1D*)hist[i].FindObject("SSuePt_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSuuPt_lep2_denom = (TH1D*)hist[i].FindObject("SSuuPt_lep2_denom");
        auto SSuuPt_lep2_numer = (TH1D*)hist[i].FindObject("SSuuPt_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SS3lPt_lep2_denom = (TH1D*)hist[i].FindObject("SS3lPt_lep2_denom");
        auto SS3lPt_lep2_numer = (TH1D*)hist[i].FindObject("SS3lPt_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);

        auto SSeeEta_lep1_denom = (TH1D*)hist[i].FindObject("SSeeEta_lep1_denom");
        auto SSeeEta_lep1_numer = (TH1D*)hist[i].FindObject("SSeeEta_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSeuEta_lep1_denom = (TH1D*)hist[i].FindObject("SSeuEta_lep1_denom");
        auto SSeuEta_lep1_numer = (TH1D*)hist[i].FindObject("SSeuEta_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSueEta_lep1_denom = (TH1D*)hist[i].FindObject("SSueEta_lep1_denom");
        auto SSueEta_lep1_numer = (TH1D*)hist[i].FindObject("SSueEta_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSuuEta_lep1_denom = (TH1D*)hist[i].FindObject("SSuuEta_lep1_denom");
        auto SSuuEta_lep1_numer = (TH1D*)hist[i].FindObject("SSuuEta_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SS3lEta_lep1_denom = (TH1D*)hist[i].FindObject("SS3lEta_lep1_denom");
        auto SS3lEta_lep1_numer = (TH1D*)hist[i].FindObject("SS3lEta_lep1_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);

        auto SSeeEta_lep2_denom = (TH1D*)hist[i].FindObject("SSeeEta_lep2_denom");
        auto SSeeEta_lep2_numer = (TH1D*)hist[i].FindObject("SSeeEta_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSeuEta_lep2_denom = (TH1D*)hist[i].FindObject("SSeuEta_lep2_denom");
        auto SSeuEta_lep2_numer = (TH1D*)hist[i].FindObject("SSeuEta_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSueEta_lep2_denom = (TH1D*)hist[i].FindObject("SSueEta_lep2_denom");
        auto SSueEta_lep2_numer = (TH1D*)hist[i].FindObject("SSueEta_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SSuuEta_lep2_denom = (TH1D*)hist[i].FindObject("SSuuEta_lep2_denom");
        auto SSuuEta_lep2_numer = (TH1D*)hist[i].FindObject("SSuuEta_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);
        auto SS3lEta_lep2_denom = (TH1D*)hist[i].FindObject("SS3lEta_lep2_denom");
        auto SS3lEta_lep2_numer = (TH1D*)hist[i].FindObject("SS3lEta_lep2_numer");
        TGraphAsymmErrors * = new TGraphAsymmErrors(,);


        auto SS3l_total_denom = (TH1D*)hist[i].FindObject("SS3l_total_denom");
        auto SS3l_total_numer = (TH1D*)hist[i].FindObject("SS3l_total_numer");
        TGraphAsymmErrors *SS3l_total = new TGraphAsymmErrors(SS3l_total_numer,SS3l_total_denom);
        auto SSuu_total_denom = (TH1D*)hist[i].FindObject("SSuu_total_denom");
        auto SSuu_total_numer = (TH1D*)hist[i].FindObject("SSuu_total_numer");
        TGraphAsymmErrors *SSuu_total = new TGraphAsymmErrors(SSuu_total_numer,SSuu_total_denom);
        auto SSeu_total_denom = (TH1D*)hist[i].FindObject("SSeu_total_denom");
        auto SSeu_total_numer = (TH1D*)hist[i].FindObject("SSeu_total_numer");
        TGraphAsymmErrors *SSeu_total = new TGraphAsymmErrors(SSeu_total_numer,SSeu_total_denom);
        auto SSee_total_denom = (TH1D*)hist[i].FindObject("SSee_total_denom");
        auto SSee_total_numer = (TH1D*)hist[i].FindObject("SSee_total_numer");       
        TGraphAsymmErrors *SSee_total = new TGraphAsymmErrors(SSee_total_numer,SSee_total_denom);
    
        
        
        
        
        
        //can1->cd(), etc.
        // could try: can1->BuildLegend(); (prob won't have desired result tho)
        // can try new PLC PMC draw options
        
        
    }
    
    // cans should have been drawn

    canvas.Add(SSeuPt_lep1_eff);
    canvas.Add(SSuePt_lep1_eff);
    canvas.Add(SSuuPt_lep1_eff);
    canvas.Add(SS3lPt_lep1_eff);
    canvas.Add(SSeePt_lep2_eff);
    canvas.Add(SSeuPt_lep2_eff);
    canvas.Add(SSuePt_lep2_eff);
    canvas.Add(SSuuPt_lep2_eff);
    canvas.Add(SS3lPt_lep2_eff);
    canvas.Add(SSeeEta_lep1_eff);
    canvas.Add(SSeuEta_lep1_eff);
    canvas.Add(SSueEta_lep1_eff);
    canvas.Add(SSuuEta_lep1_eff);
    canvas.Add(SS3lEta_lep1_eff);
    canvas.Add(SSeeEta_lep2_eff);
    canvas.Add(SSeuEta_lep2_eff);
    canvas.Add(SSueEta_lep2_eff);
    canvas.Add(SSuuEta_lep2_eff);
    canvas.Add(SS3lEta_lep2_eff);
    canvas.Add(SS3l_total_eff);
    canvas.Add(SSuu_total_eff);
    canvas.Add(SSeu_total_eff);
    canvas.Add(SSee_total_eff);


    // that's it!
    
}
