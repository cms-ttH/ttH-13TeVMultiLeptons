// Created by Geoff Smith, 2017.

class GoodPlot : public TCanvas
{
    private:
        bool checkForCombo(MakeGoodPlot &thisMGP, TH1D *thehist, int sample);
    
    public:
        GoodPlot(TString name, string legopt="none");
        TLegend *theleg;
        TH1D *sumdata=0;
        THStack *thestack;
        THStack *thebackstack;
        THStack *syststack[100];
        int numsysts = 8;
        TString thisSystTStr[12] = {"MCStatUP","MCStatDOWN","LumiUP","LumiDOWN","pdfUP","pdfDOWN","Q2UP","Q2DOWN","JESUP","JESDOWN","BTagUP","BTagDOWN"}; // work in progress
        TGraphAsymmErrors *sumMCband;
        TGraphAsymmErrors *sumMCbandNoStat;
        std::vector<TString> stacksamps;
        std::vector<int> stacksampints;
        std::vector<int> stacksampintscomboaware;
        int globalfont=42;
        bool exists = false;
        double maxsofar = 0.;
        bool drawleg = false;
        bool logplot = false;
        TH1D *sumVjets=0;
        TH1D *sumDiboson=0;
        TH1D *sumTriboson=0;
        TH1D *sumSingleTop=0;
        TH1D *sumSplitTTBar=0;
        void addTGraphAsErrors(MakeGoodPlot &thisMGP, TString thenumer, TString thedenom, int i, TString ylabel="Efficiency", double ymin=0., double ymax=1.05);
        void addEfficiencyPlot(MakeGoodPlot &thisMGP, TString thenumer, TString thedenom, int i);
        //void addROC(... // To Do
        void addPlot(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", int rebin=-1, TString drawopt="hist,PLC");
        void addPlotData(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", int rebin=-1, TString drawopt="E", bool withRatio=true);
        void addPlotNorm(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", int rebin=-1, TString drawopt="hist,PLC");
        void addPlot2D(MakeGoodPlot &thisMGP, int i, TString thehist="same");
        
        //void addComparison( ... // To do: this should be after you already added the things you're going to compare,
                                    // such as stacked mc and data, or two normalized plots, etc. This will 
                                    // do the usual division of the cavas into two pads, plotting the comparison
                                    // on the lower pad (with a given y axis label)
        
        void addStack(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", int rebin=-1);
        void addStackWithSumMC(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", int rebin=-1);
        void printStackContents(); // in progress
        //void addErrorBand(... // To Do;
        void addCMSText(MakeGoodPlot &thisMGP);
};

GoodPlot::GoodPlot(TString name, string legopt) : TCanvas(name,"can",150,10,960,660) 
{
    logplot = false;
    
    theleg = new TLegend(getleg(legopt));
    thestack = new THStack("stack","");
    for (int thisSyst=0; thisSyst<numsysts; thisSyst++) syststack[thisSyst] = new THStack("syststack"+int2ss(thisSyst),"");
    thebackstack = new THStack("backstack","");
    if (legopt!="none") drawleg = true;
    if (logplot) this->SetLogy(true);
}
void GoodPlot::addCMSText(MakeGoodPlot &thisMGP)
{
    thisMGP.CMSInfoLatex->Draw();
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

void GoodPlot::addPlotNorm(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, int rebin, TString drawopt)
{
    this->cd();
    if (thehist=="auto") thehist=this->GetName();
    auto myhist = (TH1*)thisMGP.hist[i].FindObject(thehist);
    if (rebin>0) myhist->Rebin(rebin);
    myhist->SetLineWidth(2);    
    myhist->GetXaxis()->SetTitleFont(globalfont);
    myhist->GetYaxis()->SetTitleFont(globalfont);
    if (strcmp(myhist->GetYaxis()->GetTitle(),"")==0) myhist->GetYaxis()->SetTitle("a. u.");
    
    myhist->SetMarkerStyle(10);
    myhist->SetMarkerColor(thisMGP.color[thisMGP.samples[i]]); // <- not if drawopt contains "PLC" ...
    myhist->SetLineColor(thisMGP.color[thisMGP.samples[i]]); // <- not if drawopt contains "PLC" ...
    
    clean_neg_bins(*myhist);
    myhist->Scale(1./myhist->Integral());
    if (maxsofar<myhist->GetMaximum()) maxsofar = myhist->GetMaximum();
    
    if (exists) 
    {
        drawopt=drawopt+",same";
        TIter iter(this->GetListOfPrimitives());
        TH1D *h = (TH1D*)iter.Next();
        if (logplot) h->SetAxisRange(0.,1000.*maxsofar,"Y");
        else h->SetAxisRange(0.,1.25*maxsofar,"Y");
    }
    
    //myhist->DrawNormalized(drawopt); // never use DrawNormalized with PLC or PMC
    myhist->Draw(drawopt);
    exists = true;
    
    if (drawleg)
    {
        if (legtext=="samp") theleg->AddEntry(myhist,thisMGP.sample_names[thisMGP.samples[i]],"L");
        else theleg->AddEntry(myhist,legtext,"L");
        theleg->Draw();
    }
    if (i==(thisMGP.numsamples-1)) thisMGP.canvas.Add(this);
}
void GoodPlot::addPlot(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, int rebin, TString drawopt)
{
    this->cd();
    auto myhist = (TH1*)thisMGP.hist[i].FindObject(thehist);
    if (rebin>0) myhist->Rebin(rebin);
    myhist->SetLineWidth(2);
    //myhist->SetLineColor(1);
    myhist->GetXaxis()->SetTitleFont(globalfont);
    myhist->GetYaxis()->SetTitleFont(globalfont);     
    if (strcmp(myhist->GetYaxis()->GetTitle(),"")==0) myhist->GetYaxis()->SetTitle("Events");

    clean_neg_bins(*myhist);    
    if (maxsofar<myhist->GetMaximum()) maxsofar = myhist->GetMaximum();
    
    if (exists) 
    {
        drawopt=drawopt+",same";
        TIter iter(this->GetListOfPrimitives());
        TH1D *h = (TH1D*)iter.Next();
        if (logplot) h->SetAxisRange(0.,1000.*maxsofar,"Y");
        else h->SetAxisRange(0.,1.1*maxsofar,"Y");
    }
    
    myhist->Draw(drawopt);
    exists = true;
    
    if (drawleg)
    {
        if (legtext=="samp") theleg->AddEntry(myhist,thisMGP.sample_names[thisMGP.samples[i]],"L");
        else theleg->AddEntry(myhist,legtext,"L");
        theleg->Draw();
    } 
    if (i==(thisMGP.numsamples-1)) thisMGP.canvas.Add(this);
}
void GoodPlot::addPlotData(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, int rebin, TString drawopt, bool withRatio)
{
    this->cd();
    auto myhist = (TH1D*)thisMGP.hist[i].FindObject(thehist);

    if (rebin>0) myhist->Rebin(rebin);
    myhist->SetLineWidth(2);
    myhist->SetLineColor(1); // should already be this but whatever
    myhist->SetMarkerStyle(10);
    myhist->SetMarkerColor(kBlack);
    myhist->GetXaxis()->SetTitleFont(globalfont);
    myhist->GetYaxis()->SetTitleFont(globalfont);     
    if (strcmp(myhist->GetYaxis()->GetTitle(),"")==0) myhist->GetYaxis()->SetTitle("Events");       
    //cout << "asdf" << endl;
    if (sumdata==0) 
    {
        //cout << "asdf0.1" << endl;
        sumdata = (TH1D*)myhist->Clone();
    }
    else sumdata->Add(myhist);
    //cout << "asdf2" << endl;
    if (maxsofar<sumdata->GetMaximum()) maxsofar = sumdata->GetMaximum();
    
    if (exists) 
    {
        drawopt=drawopt+",same";
        //TIter iter(this->GetListOfPrimitives());
        //TH1D *h = (TH1D*)iter.Next();
        //h->SetAxisRange(0.,1.1*maxsofar,"Y");
    }
    
    if (i==(thisMGP.numsamples-1))
    {    
        sumdata->Draw(drawopt);
        exists = true;
    
        if (drawleg)
        {
            if (legtext=="samp") theleg->AddEntry(sumdata,"data","L");
            else theleg->AddEntry(sumdata,legtext,"L");
            theleg->Draw();
        } 
        
        if (withRatio) 
        {
            // divide canvas, cd to new pad
            // divided data is just data hist divided by mc stack hist
            // for mc band, first clone (copy?) sum mc error band tgraph. 
            // iterate through points, setting each one to zero and each error to error/y value.
            
            //auto hopefullyAcopyOfThePlot = this->GetPad(0);
            //TPad *pnew = (TPad*)this->Clone();
            //auto pnew = this->Clone();
            
            //this->Divide(1,2,0,0);
            this->SetCanvasSize(960,900); // really should be (960,943), but due to margins, etc., it's a little different
            this->Divide(1,2,0,0); // first divide this canvas into two sections
            // now move to top pad:
            this->cd(1);
            gPad->SetPad("mainPad","",0.0,0.3,1.0,1.0);
            gPad->SetBorderSize(0);
            gPad->SetFillColor(0);
            gPad->SetGridx(0);
            gPad->SetGridy(0);
            if (logplot) gPad->SetLogy(true);
            // tried these but didn't work:
            //sumdata->Draw();
            //hopefullyAcopyOfThePlot->Draw();
            //pnew->Draw();
            // so, just redraw everything in top pad first (not that hard):
            thestack->Draw("hist"); 
            sumMCband->Draw("2"); // not drawn correctly on log plots for some reason
            if (drawleg) theleg->Draw();  
            thisMGP.CMSInfoLatex->Draw();
            sumdata->Draw(drawopt);
            // move to bottom pad:
            this->cd(2);
            gPad->SetPad("ratioPad","",0.0,0.0,1.0,0.3);
            gPad->SetBorderSize(0);
            gPad->SetFillColor(0);
            gPad->SetLogy(false);
            gPad->SetGridx(0);
            // set up ratio hist and error band:
            auto stackarray = thestack->GetStack();  
            auto sumback = (TH1*)stackarray->Last();
            auto dataMCratio = (TH1*)sumdata->Clone();
            // copy settings from top plot:
            dataMCratio->Divide(sumdata,sumback);
            dataMCratio->GetYaxis()->SetTitle("Data/MC");
            dataMCratio->GetYaxis()->SetRangeUser(0.5,1.5);
            dataMCratio->SetLabelSize(sumback->GetLabelSize());
            //dataMCratio->SetTitleOffset(sumback->GetTitleOffset("Y"), "Y");
            dataMCratio->SetTitleSize(sumback->GetTitleSize("Y")*0.7/0.3, "Y");
            //dataMCratio->SetTitleOffset(sumback->GetTitleOffset("X"), "X");
            dataMCratio->SetTitleSize(sumback->GetTitleSize("X")*0.7/0.3, "X");
            dataMCratio->Draw();
            TGraphAsymmErrors *sumMCbandRatio = new TGraphAsymmErrors(*sumMCband);
            
            for (int j=0; j<dataMCratio->GetNbinsX(); j++)
            {
                double xpoint, ypoint;
                int dummyint = sumMCbandRatio->GetPoint(j,xpoint,ypoint);
                double errorup = sumMCbandRatio->GetErrorYhigh(j)/ypoint;
                double errordown = sumMCbandRatio->GetErrorYlow(j)/ypoint;             
                sumMCbandRatio->SetPoint(j,xpoint,1.);
                sumMCbandRatio->SetPointEYhigh(j,errorup);
                sumMCbandRatio->SetPointEYlow(j,errordown);
            }   
            
            sumMCbandRatio->Draw("2");
        
            TLine lineAt1;
            lineAt1.SetLineColor(2);
            lineAt1.SetLineWidth(2);
            lineAt1.DrawLine(dataMCratio->GetXaxis()->GetBinLowEdge(1),1,dataMCratio->GetXaxis()->GetBinUpEdge(dataMCratio->GetNbinsX()),1);
            dataMCratio->Draw("same");
            auto oldtopmargin = gPad->GetTopMargin();
            //gPad->SetTopMargin(gPad->GetTopMargin()/2.);
            gPad->SetTopMargin(0);
            //gPad->SetBottomMargin(gPad->GetBottomMargin()+(gPad->GetTopMargin()/2.));
            gPad->SetBottomMargin(gPad->GetBottomMargin()+oldtopmargin);
            this->Update();
            
            
        }
        
        thisMGP.canvas.Add(this);
    }
}
void GoodPlot::addPlot2D(MakeGoodPlot &thisMGP, int i, TString thehist)
{        
    this->cd();
    if (thehist=="same")
    {
        thehist=this->GetName();
    }
    auto myhist = (TH2*)thisMGP.hist[i].FindObject(thehist);
    
    myhist->GetXaxis()->SetTitleFont(globalfont);
    myhist->GetYaxis()->SetTitleFont(globalfont);
    
    int thisSamp = thisMGP.samples[i];
    //myhist->Scale(thisMGP.lumi*thisMGP.xsec[thisSamp]/thisMGP.numgen[thisSamp]);
    clean_neg_bins(*myhist);
    
    myhist->Draw("COLZ");
}
    
void GoodPlot::addStack(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, int rebin)
{
    //cout << "inside00" << endl;
    this->cd();
    
    auto myhist = (TH1*)thisMGP.hist[i].FindObject(thehist);
    if (rebin>0) myhist->Rebin(rebin);
    clean_neg_bins(*myhist);       
    
    int thisSamp = thisMGP.samples[i];
    if (thisSamp>99) cout << "Trying to add a data sample to the stack. Fix your code..." << endl;
    int numsamps = thisMGP.numsamples;
    stacksamps.push_back(thisMGP.sample_names[thisSamp]);
    stacksampints.push_back(thisSamp);
    
    myhist->Scale(thisMGP.lumi*thisMGP.xsec[thisSamp]/thisMGP.numgen[thisSamp]);    
    myhist->SetLineColor(thisMGP.color[thisSamp]);
    
    bool isSig = (thisSamp==1 || thisSamp==8 || thisSamp==9 || thisSamp==26 || thisSamp==27 || thisSamp==28 || thisSamp==29) ? true : false;
    if (!isSig) myhist->SetFillColor(thisMGP.color[thisSamp]);
    myhist->SetLineWidth(0);
    if (isSig) myhist->SetLineWidth(2);
    if (logplot) myhist->SetMinimum(0.1);
    
    thestack->Add(myhist);  
    if (!isSig) thebackstack->Add(myhist);
    
    // add the systs:
    // comment this out if not needed and causing problems
    //"MCStatUP","MCStatDOWN","LumiUP","LumiDOWN","pdfUP","pdfDOWN","Q2UP","Q2DOWN"
    
    //TH1 *myhistMCStatUP = myhist->Clone();
    //TH1 *myhistMCStatDOWN = myhist->Clone();
    cout << "hey1" << endl;
    TH1 *myhistLumiUP = (TH1*)myhist->Clone();
    TH1 *myhistLumiDOWN = (TH1*)myhist->Clone();
    TH1 *myhistpdfUP = (TH1*)myhist->Clone();
    TH1 *myhistpdfDOWN = (TH1*)myhist->Clone();
    TH1 *myhistQ2UP = (TH1*)myhist->Clone();
    TH1 *myhistQ2DOWN = (TH1*)myhist->Clone();
    cout << "hey2" << endl;

    myhistLumiUP->Scale((thisMGP.lumiup-thisMGP.lumi)/thisMGP.lumi);
    myhistLumiDOWN->Scale((thisMGP.lumidown-thisMGP.lumi)/thisMGP.lumi);
    myhistpdfUP->Scale(thisMGP.pdfup[thisSamp]/thisMGP.xsec[thisSamp]);
    myhistpdfDOWN->Scale(thisMGP.pdfdown[thisSamp]/thisMGP.xsec[thisSamp]);
    myhistQ2UP->Scale(thisMGP.q2up[thisSamp]/thisMGP.xsec[thisSamp]);
    myhistQ2DOWN->Scale(thisMGP.q2down[thisSamp]/thisMGP.xsec[thisSamp]);
    
    //syststack[0]->Add(myhist);  
    //syststack[1]->Add(myhist);    
    syststack[2]->Add(myhistLumiUP);    
    syststack[3]->Add(myhistLumiDOWN);    
    syststack[4]->Add(myhistpdfUP);    
    syststack[5]->Add(myhistpdfDOWN);    
    syststack[6]->Add(myhistQ2UP);
    syststack[7]->Add(myhistQ2DOWN);
        
    
    if (logplot) thestack->SetMinimum(0.1);
    thestack->Draw("hist");
    
    thestack->GetYaxis()->SetTitle("Events");
    thestack->GetXaxis()->SetTitle(myhist->GetXaxis()->GetTitle());
    thestack->GetXaxis()->SetTitleFont(globalfont);
    thestack->GetYaxis()->SetTitleFont(globalfont);
    
    if (drawleg)
    {
        if (legtext=="samp")
        {
            //if (isSig) theleg->AddEntry(myhist,thisMGP.sample_names[thisSamp],"L");
            theleg->AddEntry(myhist,thisMGP.sample_names[thisSamp],"F");
            //else theleg->AddEntry(myhist,thisMGP.sample_names[thisSamp],"F");
        }
        else theleg->AddEntry(myhist,legtext,"L");
        theleg->Draw();
    }
    
    //if (logplot && i==(numsamps-1)) this->SetLogy(true); 
    if (logplot) gPad->SetLogy(true);
}

void GoodPlot::addStackWithSumMC(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, int rebin)
{    
    // If you get plots with non-translucent error bands, try uncommenting this:
    //gStyle->SetCanvasPreferGL(1);
    this->SetGrid(0,0);
    
    addStack(thisMGP, thehist, i, legtext, rebin); // <- this should already have scaled the hist, cleaned neg bins, rebinned etc.
    auto myhist = (TH1*)thisMGP.hist[i].FindObject(thehist);
    auto stackarray = thebackstack->GetStack();   
    if (stackarray->GetEntries()<1)
    {
        cout << "Empty background stack. Doing nothing..." << endl; 
        return;
    }
    auto sumhist = (TH1*)stackarray->Last();
    if (!exists) sumMCband = new TGraphAsymmErrors(sumhist);
    if (!exists) sumMCbandNoStat = new TGraphAsymmErrors(sumhist);
    
    int thisSamp = thisMGP.samples[i];
    int numsamps = thisMGP.numsamples;
    
    for (int j=0; j<myhist->GetNbinsX(); j++) // <- The numbering system for TGraph points starts at 0.
    {
        if (!exists)
        {
            sumMCbandNoStat->SetPointEYhigh(j,0.); // Removing the stat error here.
            sumMCbandNoStat->SetPointEYlow(j,0.); // Removing the stat error here.
        }
        
        // all the syst uncertainties for this sample (maybe move to separate function when the list gets longer):        
        double thisbincontent = myhist->GetBinContent(j+1);        
        double thisbinerrorup = thisbincontent*sqrt(thisMGP.q2up[thisSamp]*thisMGP.q2up[thisSamp] + thisMGP.pdfup[thisSamp]*thisMGP.pdfup[thisSamp])/thisMGP.xsec[thisSamp];
        double thisbinerrordown = thisbincontent*sqrt(thisMGP.q2down[thisSamp]*thisMGP.q2down[thisSamp] + thisMGP.pdfdown[thisSamp]*thisMGP.pdfdown[thisSamp])/thisMGP.xsec[thisSamp];
                
        // append to syst-only uncertainties from the other samples:
        double currentsystup = sumMCbandNoStat->GetErrorYhigh(j);
        double currentsystdown = sumMCbandNoStat->GetErrorYlow(j);                
        sumMCbandNoStat->SetPointEYhigh(j,sqrt(currentsystup*currentsystup + thisbinerrorup*thisbinerrorup));
        sumMCbandNoStat->SetPointEYlow(j,sqrt(currentsystdown*currentsystdown + thisbinerrordown*thisbinerrordown));
        
        // Now combine with the mc stat error from the stack:
        //double sumerrorup = sqrt(sumMCband->GetErrorYhigh(j)*sumMCband->GetErrorYhigh(j) + sumMCbandNoStat->GetErrorYhigh(j)*sumMCbandNoStat->GetErrorYhigh(j));
        //double sumerrordown = sqrt(sumMCband->GetErrorYlow(j)*sumMCband->GetErrorYlow(j) + sumMCbandNoStat->GetErrorYlow(j)*sumMCbandNoStat->GetErrorYlow(j));
        double sumerrorup = sqrt(sumhist->GetBinError(j+1)*sumhist->GetBinError(j+1) + sumMCbandNoStat->GetErrorYhigh(j)*sumMCbandNoStat->GetErrorYhigh(j));
        double sumerrordown = sqrt(sumhist->GetBinError(j+1)*sumhist->GetBinError(j+1) + sumMCbandNoStat->GetErrorYlow(j)*sumMCbandNoStat->GetErrorYlow(j));

        sumMCband->SetPointEYhigh(j,sumerrorup);
        sumMCband->SetPointEYlow(j,sumerrordown);
        double xpoint;
        double ypoint;
        int dummyint = sumMCband->GetPoint(j,xpoint,ypoint);
        sumMCband->SetPoint(j,xpoint,sumhist->GetBinContent(j+1));
        sumMCbandNoStat->SetPoint(j,xpoint,sumhist->GetBinContent(j+1));
        
    }
    
    //cout << "  " << endl;
    //cout << "  " << endl;
    double dummyxpoint;
    double dummyypoint;
    int dummyint = sumMCband->GetPoint(sumhist->GetMaximumBin()-1,dummyxpoint,dummyypoint);
    //cout << maxamount << " " << dummyxpoint << "  " << dummyypoint << endl;
    double maxamount = dummyypoint + sumMCband->GetErrorYhigh(sumhist->GetMaximumBin()-1);
    //cout << maxamount << endl;
    maxamount = std::max(maxamount,thestack->GetMaximum());    
    //cout << maxamount << thestack->GetMaximum() << endl;
    
    maxsofar = 1.3*maxamount;
    if (logplot) maxsofar = 1000*maxamount;
    thestack->SetMaximum(maxsofar); // sumhist
    
    this->Update();
    
    exists = true;    
    
    if ( (!thisMGP.hasdata && i==(numsamps-1)) || (thisMGP.hasdata && i==(numsamps-(thisMGP.numdatasamples+1))) )
    {
        // at the end, add the overall lumi uncertainty:
        
        for (int j=0; j<sumhist->GetNbinsX(); j++)
        {
            double lumierrorup = sumhist->GetBinContent(j+1)*(thisMGP.lumiup-thisMGP.lumi)/thisMGP.lumi;
            double lumierrordown = sumhist->GetBinContent(j+1)*(thisMGP.lumi-thisMGP.lumidown)/thisMGP.lumi;

            sumMCband->SetPointEYhigh(j,sqrt(sumMCband->GetErrorYhigh(j)*sumMCband->GetErrorYhigh(j) + lumierrorup*lumierrorup));
            sumMCband->SetPointEYlow(j,sqrt(sumMCband->GetErrorYlow(j)*sumMCband->GetErrorYlow(j) + lumierrordown*lumierrordown));        
        }
    
        //sumMCband->SetMarkerStyle(21);
        sumMCband->SetLineColor(kWhite);
        sumMCband->SetFillColorAlpha(kBlack, 0.25); // <- need OpenGL enabled for this to work
        if (!logplot) sumMCband->Draw("2"); // not drawn correctly on log plots for some reason

        if (drawleg)
        {
            theleg->AddEntry(sumMCband,"Sum Bkgd","F");
            theleg->Draw();
        }      
        thisMGP.CMSInfoLatex->Draw();
        if (!thisMGP.hasdata) thisMGP.canvas.Add(this);
    }    
       
}
void GoodPlot::printStackContents()
{
    // prints a latex-formatted table summarizing the stack contents
    
    cout << " " << endl;
    cout << "Printing contents of " << this->GetName() << " stack:" << endl;
    cout << " " << endl;
    
    auto hlist = thestack->GetHists();
    int numhists = hlist->GetEntries();

    if (numhists<1)
    {
        cout << "Empty stack. Skipping the rest of printStackContents..." << endl;
        return;
    }

    TH1D *backsum = (TH1D*)hlist->At(0)->Clone();
    TH1D *sigsum = (TH1D*)hlist->At(0)->Clone();
    backsum->Reset();
    sigsum->Reset();    


    // bin labels -> names of columns in table
    cout << "\\hline \\\\" << endl;
    for (int j=1; j<=backsum->GetNbinsX(); j++)
    {
        if (thestack->GetXaxis()->GetBinLabel(j)!="") cout << " & " << thestack->GetXaxis()->GetBinLabel(j);
        else cout << " & " << j;
    }
    cout << " \\\\" << endl;     
    cout << "\\hline \\\\" << endl;

    for (int i=0; i<numhists; i++)
    {
        cout << stacksamps[i] << "  ";
        for (int j=1; j<=((TH1*)hlist->At(i))->GetNbinsX(); j++)
        {
            cout << std::fixed << std::setprecision(1) << " & " << ((TH1*)hlist->At(i))->GetBinContent(j);
        }
        cout << " \\\\" << endl; // this will actually print two backslashes
        if (stacksampints[i]==1 || stacksampints[i]==8 || stacksampints[i]==9) sigsum->Add((TH1*)hlist->At(i));
        else backsum->Add((TH1*)hlist->At(i));
    }            
    auto stackarray = thestack->GetStack();
    auto sumhist = (TH1*)stackarray->Last();

    cout << "\\hline \\\\" << endl;
    cout << "Sum Background  ";    
    for (int j=1; j<=backsum->GetNbinsX(); j++)
    {
        cout << std::fixed << std::setprecision(1) << " & " << backsum->GetBinContent(j);
    }
    cout << " \\\\" << endl; 

    cout << "\\hline \\\\" << endl;
    cout << "Sum Signal  ";    
    for (int j=1; j<=sigsum->GetNbinsX(); j++)
    {
        cout << std::fixed << std::setprecision(1) << " & " << sigsum->GetBinContent(j);
    }
    cout << " \\\\" << endl; 

    cout << "\\hline \\\\" << endl;
    cout << "S+B  ";    
    for (int j=1; j<=sumhist->GetNbinsX(); j++)
    {
        cout << std::fixed << std::setprecision(1) << " & " << sumhist->GetBinContent(j);
    }
    cout << " \\\\" << endl; 

    cout << "\\hline \\\\" << endl;
    cout << "$S/\\sqrt{B}$  ";    
    for (int j=1; j<=sigsum->GetNbinsX(); j++)
    {
        if (backsum->GetBinContent(j)>0)
        {
            cout << std::fixed << std::setprecision(1) << " & " << (sigsum->GetBinContent(j)/sqrt(backsum->GetBinContent(j)));
        }
        else cout << " & " << "(inf)";
    }
    cout << " \\\\" << endl;     
    cout << "\\hline \\\\" << endl;


    cout << " " << endl;
    cout << " " << endl;
    
    
    for (int thisSyst=0; thisSyst<numsysts; thisSyst++)
    {        
        if (thisSyst<2)
        {
            for (int i=0; i<numhists; i++)
            {
                cout << stacksamps[i]+" "+thisSystTStr[thisSyst] << "  ";
                for (int j=1; j<=((TH1*)hlist->At(i))->GetNbinsX(); j++)
                {
                    if (thisSyst==0) cout << std::fixed << std::setprecision(1) << " & " << ((TH1*)hlist->At(i))->GetBinContent(j) + ((TH1*)hlist->At(i))->GetBinError(j);
                    else if (thisSyst==1) cout << std::fixed << std::setprecision(1) << " & " << ((TH1*)hlist->At(i))->GetBinContent(j) - ((TH1*)hlist->At(i))->GetBinError(j);
                }
                cout << " \\\\" << endl; // this will actually print two backslashes
            }
            continue;
        }
        
        auto hlistSyst = syststack[thisSyst]->GetHists();
        numhists = hlistSyst->GetEntries();
    
        TH1D *backsumSyst = (TH1D*)hlistSyst->At(0)->Clone();
        TH1D *sigsumSyst = (TH1D*)hlistSyst->At(0)->Clone();
        backsumSyst->Reset();
        sigsumSyst->Reset();    

        // bin labels -> names of columns in table
        // cout << "\\hline \\\\" << endl;
//         for (int j=1; j<=backsumSyst->GetNbinsX(); j++)
//         {
//             if (syststack[thisSyst]->GetXaxis()->GetBinLabel(j)!="") cout << " & " << syststack[thisSyst]->GetXaxis()->GetBinLabel(j);
//             else cout << " & " << j;
//         }
//         cout << " \\\\" << endl;     
//         cout << "\\hline \\\\" << endl;

        for (int i=0; i<numhists; i++)
        {
            cout << stacksamps[i]+" "+thisSystTStr[thisSyst] << "  ";
            for (int j=1; j<=((TH1*)hlistSyst->At(i))->GetNbinsX(); j++)
            {
                cout << std::fixed << std::setprecision(1) << " & " << ((TH1*)hlistSyst->At(i))->GetBinContent(j);
            }
            cout << " \\\\" << endl; // this will actually print two backslashes
            
            //if (stacksampints[i]==1 || stacksampints[i]==8 || stacksampints[i]==9) sigsumSyst->Add((TH1*)hlistSyst->At(i));
            //else backsumSyst->Add((TH1*)hlistSyst->At(i));
        }            
//         auto stackarraySyst = syststack[thisSyst]->GetStack();
//         auto sumhistSyst = (TH1*)stackarraySyst->Last();
//     
//         cout << "\\hline \\\\" << endl;
//         cout << "Sum Background  ";    
//         for (int j=1; j<=backsumSyst->GetNbinsX(); j++)
//         {
//             cout << std::fixed << std::setprecision(1) << " & " << backsumSyst->GetBinContent(j);
//         }
//         cout << " \\\\" << endl; 
//     
//         cout << "\\hline \\\\" << endl;
//         cout << "Sum Signal  ";    
//         for (int j=1; j<=sigsumSyst->GetNbinsX(); j++)
//         {
//             cout << std::fixed << std::setprecision(1) << " & " << sigsumSyst->GetBinContent(j);
//         }
//         cout << " \\\\" << endl; 
//     
//         cout << "\\hline \\\\" << endl;
//         cout << "S+B  ";    
//         for (int j=1; j<=sumhistSyst->GetNbinsX(); j++)
//         {
//             cout << std::fixed << std::setprecision(1) << " & " << sumhistSyst->GetBinContent(j);
//         }
//         cout << " \\\\" << endl; 
//     
//         cout << "\\hline \\\\" << endl;
//         cout << "$S/\\sqrt{B}$  ";    
//         for (int j=1; j<=sigsumSyst->GetNbinsX(); j++)
//         {
//             if (backsumSyst->GetBinContent(j)>0)
//             {
//                 cout << std::fixed << std::setprecision(1) << " & " << (sigsumSyst->GetBinContent(j)/sqrt(backsumSyst->GetBinContent(j)));
//             }
//             else cout << " & " << "(inf)";
//         }
//         cout << " \\\\" << endl;     
//         cout << "\\hline \\\\" << endl;
    
    
        cout << " " << endl;
        cout << " " << endl;
    }
}
bool GoodPlot::checkForCombo(MakeGoodPlot &thisMGP, TH1D *thehist, int sample)
{
    if (thisMGP.groupsamples)
    {
        //Vjets
        if (sample==6 || sample==16 || sample==7)
        {
            if (sumVjets==0) sumVjets = (TH1D*)thehist->Clone();
            else sumVjets->Add(thehist);
            return true;
        }
        //Diboson 
        if (sample==10 || sample==11 || sample==12)
        {
            if (sumDiboson==0) sumDiboson = (TH1D*)thehist->Clone();
            else sumDiboson->Add(thehist);
            return true;
        }        
        //Triboson
        if (sample==22 || sample==23 || sample==24 || sample==25)
        {
            if (sumTriboson==0) sumTriboson = (TH1D*)thehist->Clone();
            else sumTriboson->Add(thehist);
            return true;
        }        
        //SingleTop 
        if (sample==17 || sample==18 || sample==19 || sample==20 || sample==21)
        {
            if (sumSingleTop==0) sumSingleTop = (TH1D*)thehist->Clone();
            else sumSingleTop->Add(thehist);
            return true;
        }        
        //SplitTTBar
        if (sample==13 || sample==14 || sample==15)
        {
            if (sumSplitTTBar==0) sumSplitTTBar = (TH1D*)thehist->Clone();
            else sumSplitTTBar->Add(thehist);
            return true;
        }
    }
    return false;
}

void makeAndAdd2DPlot1Sample(MakeGoodPlot &thisMGP, int i, TString thehist)
{
    GoodPlot *dummyplot = new GoodPlot(thehist+thisMGP.sample_names_reg[thisMGP.samples[i]]);
    dummyplot->addPlot2D(thisMGP,i,thehist);
    thisMGP.canvas.Add(dummyplot);
}
