class GoodPlot : public TCanvas
{
    public:
        GoodPlot(TString name, string legopt="none");
        TLegend *theleg;
        THStack *thestack;
        int globalfont=42;
        bool exists = false;
        bool drawleg = false;
        void addTGraphAsErrors(MakeGoodPlot &thisMGP, TString thenumer, TString thedenom, int i, TString ylabel="Efficiency", double ymin=0., double ymax=1.05);
        void addEfficiencyPlot(MakeGoodPlot &thisMGP, TString thenumer, TString thedenom, int i);
        //void addROC(... // To Do
        void addPlot(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", TString drawopt="PLC");
        void addPlotNorm(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", TString drawopt="hist,PLC");
        void add2DPlot(MakeGoodPlot &thisMGP, TString thehist, TString xtitle="none", TString ytitle="none"); // To Do
        //void addComparison( ... // To do: this should be after you already added the things you're going to compare,
                                    // such as stacked mc and data, or two normalized plots, etc. This will 
                                    // do the usual division of the cavas into two pads, plotting the comparison
                                    // on the lower pad (with a given y axis label)
        
        //void addStack(... // To Do; 
        //void addErrorBand(... // To Do;
        //void addCMSText
};

GoodPlot::GoodPlot(TString name, string legopt) : TCanvas(name,"can",150,10,960,660) 
{
    theleg = new TLegend(getleg(legopt));
    if (legopt!="none") drawleg = true;
}

void GoodPlot::addTGraphAsErrors(MakeGoodPlot &thisMGP, TString thenumer, TString thedenom, int i, TString ylabel, double ymin, double ymax)
{
    this->cd();
    auto hist_numer = (TH1D*)thisMGP.hist[i].FindObject(thenumer);
    auto hist_denom = (TH1D*)thisMGP.hist[i].FindObject(thedenom);
    
    TGraphAsymmErrors *theTGAE = new TGraphAsymmErrors(hist_numer,hist_denom);

    theTGAE->GetYaxis()->SetRangeUser(ymin,ymax);
    theTGAE->GetYaxis()->SetTitle(ylabel);
    theTGAE->SetLineWidth(2);
    theTGAE->GetXaxis()->SetTitleFont(globalfont);
    theTGAE->GetYaxis()->SetTitleFont(globalfont);  

    if (i==0)
    {
        hist_denom->Scale(1000);
        hist_denom->GetYaxis()->SetRangeUser(ymin,ymax);
        hist_denom->GetYaxis()->SetTitle(ylabel);
        hist_denom->SetLineWidth(2);
        hist_denom->GetXaxis()->SetTitleFont(globalfont);
        hist_denom->GetYaxis()->SetTitleFont(globalfont);  
        hist_denom->Draw();                        
    }
    theTGAE->Draw("P,PLC");
    theleg->AddEntry(theTGAE,thisMGP.sample_names[thisMGP.samples[i]],"L");
    if (i==(thisMGP.numsamples-1)) theleg->Draw();
}

void GoodPlot::addEfficiencyPlot(MakeGoodPlot &thisMGP, TString thenumer, TString thedenom, int i)
{
    addTGraphAsErrors(thisMGP, thenumer, thedenom, i);
}

void GoodPlot::addPlotNorm(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, TString drawopt)
{
    this->cd();
    auto myhist = (TH1*)thisMGP.hist[i].FindObject(thehist);
    myhist->SetLineWidth(2);    
    myhist->GetXaxis()->SetTitleFont(globalfont);
    myhist->GetYaxis()->SetTitleFont(globalfont);
    
    if (strcmp(myhist->GetYaxis()->GetTitle(),"")==0) myhist->GetYaxis()->SetTitle("a. u.");
    myhist->Scale(1./myhist->Integral());
        
    if (exists) drawopt=drawopt+",same";
    
    //myhist->DrawNormalized(drawopt); // never use DrawNormalized with PLC or PMC
    myhist->Draw(drawopt);
    exists = true;
    
    if (drawleg)
    {
        if (legtext=="samp") theleg->AddEntry(myhist,thisMGP.sample_names[thisMGP.samples[i]],"L");
        else theleg->AddEntry(myhist,legtext,"L");
        theleg->Draw();
    }    
}
void GoodPlot::addPlot(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, TString drawopt)
{
    this->cd();
    auto myhist = (TH1*)thisMGP.hist[i].FindObject(thehist);
    myhist->SetLineWidth(2);   
    myhist->GetXaxis()->SetTitleFont(globalfont);
    myhist->GetYaxis()->SetTitleFont(globalfont);     
    if (strcmp(myhist->GetYaxis()->GetTitle(),"")==0) myhist->GetYaxis()->SetTitle("Events");
    
    if (exists) drawopt=drawopt+",same";
    myhist->Draw(drawopt);
    exists = true;
    
    if (drawleg)
    {
        if (legtext=="samp") theleg->AddEntry(myhist,thisMGP.sample_names[thisMGP.samples[i]],"L");
        else theleg->AddEntry(myhist,legtext,"L");
        theleg->Draw();
    }    
}
