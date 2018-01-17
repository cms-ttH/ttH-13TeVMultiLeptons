class GoodPlot : public TCanvas
{
    public:
        GoodPlot(TString name, string legopt="none");
        TLegend *theleg;
        THStack *thestack;
        THStack *thebackstack;
        TGraphAsymmErrors *sumMCbandNoStat;
        std::vector<TString> stacksamps;
        std::vector<int> stacksampints;
        int globalfont=42;
        bool exists = false;
        double maxsofar = 0.;
        bool drawleg = false;
        void addTGraphAsErrors(MakeGoodPlot &thisMGP, TString thenumer, TString thedenom, int i, TString ylabel="Efficiency", double ymin=0., double ymax=1.05);
        void addEfficiencyPlot(MakeGoodPlot &thisMGP, TString thenumer, TString thedenom, int i);
        //void addROC(... // To Do
        void addPlot(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", TString drawopt="hist,PLC");
        void addPlotNorm(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", TString drawopt="hist,PLC");
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
    theleg = new TLegend(getleg(legopt));
    thestack = new THStack("stack","");
    thebackstack = new THStack("backstack","");
    if (legopt!="none") drawleg = true;
    //gPad->SetLogy();
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

    clean_neg_bins(*myhist);    
    //myhist->GetYaxis()->SetRangeUser(-50000,50000);
    
    if (maxsofar<myhist->GetMaximum()) maxsofar = myhist->GetMaximum();
    
    if (exists) 
    {
        drawopt=drawopt+",same";
        TIter iter(this->GetListOfPrimitives());
        TH1D *h = (TH1D*)iter.Next();
        h->SetAxisRange(0.,1.1*maxsofar,"Y");
    }
    
    myhist->Draw(drawopt);
    exists = true;
    
    if (drawleg)
    {
        if (legtext=="samp") theleg->AddEntry(myhist,thisMGP.sample_names[thisMGP.samples[i]],"L");
        else theleg->AddEntry(myhist,legtext,"L");
        theleg->Draw();
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
    myhist->Scale(thisMGP.lumi*thisMGP.xsec[thisSamp]/thisMGP.numgen[thisSamp]);
    
    myhist->Draw("COLZ");
}
    
void GoodPlot::addStack(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, int rebin)
{
    this->cd();
    
    bool logplot = false;
    
    auto myhist = (TH1*)thisMGP.hist[i].FindObject(thehist);
    if (rebin>0) myhist->Rebin(rebin);
    clean_neg_bins(*myhist);       
    
    int thisSamp = thisMGP.samples[i];
    int numsamps = thisMGP.numsamples;
    stacksamps.push_back(thisMGP.sample_names[thisSamp]);
    stacksampints.push_back(thisSamp);
    
    myhist->Scale(thisMGP.lumi*thisMGP.xsec[thisSamp]/thisMGP.numgen[thisSamp]);    
    myhist->SetLineColor(thisMGP.color[thisSamp]);
    
    bool isSig = (thisSamp==1 || thisSamp==8 || thisSamp==9) ? true : false;
    if (!isSig) myhist->SetFillColor(thisMGP.color[thisSamp]);
    myhist->SetLineWidth(0);
    if (isSig) myhist->SetLineWidth(2);
    if (logplot) myhist->SetMinimum(0.1);
    thestack->Add(myhist);  
    if (!isSig) thebackstack->Add(myhist);
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
    
    if (logplot && i==(numsamps-1)) this->SetLogy(true); 
}

void GoodPlot::addStackWithSumMC(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext, int rebin)
{    
    // If you get plots with non-translucent error bands, try uncommenting this:
    //gStyle->SetCanvasPreferGL(1);
    this->SetGrid(0,0);
    
    addStack(thisMGP, thehist, i, legtext, rebin); // <- this should already have scaled the hist, cleaned neg bins, rebinned etc.
    auto myhist = (TH1*)thisMGP.hist[i].FindObject(thehist);
    
    auto stackarray = thebackstack->GetStack();    
    auto sumhist = (TH1*)stackarray->Last();
    TGraphAsymmErrors *sumMCband = new TGraphAsymmErrors(sumhist);
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
        double sumerrorup = sqrt(sumMCband->GetErrorYhigh(j)*sumMCband->GetErrorYhigh(j) + sumMCbandNoStat->GetErrorYhigh(j)*sumMCbandNoStat->GetErrorYhigh(j));
        double sumerrordown = sqrt(sumMCband->GetErrorYlow(j)*sumMCband->GetErrorYlow(j) + sumMCbandNoStat->GetErrorYlow(j)*sumMCbandNoStat->GetErrorYlow(j));
        
        sumMCband->SetPointEYhigh(j,sumerrorup);
        sumMCband->SetPointEYlow(j,sumerrordown);
        
    }
    
    cout << "  " << endl;
    cout << "  " << endl;
    double dummyxpoint;
    double dummyypoint;
    int dummyint = sumMCband->GetPoint(sumhist->GetMaximumBin()-1,dummyxpoint,dummyypoint);
    //cout << maxamount << " " << dummyxpoint << "  " << dummyypoint << endl;
    double maxamount = dummyypoint + sumMCband->GetErrorYhigh(sumhist->GetMaximumBin()-1);
    cout << maxamount << endl;
    maxamount = std::max(maxamount,thestack->GetMaximum());    
    cout << maxamount << thestack->GetMaximum() << endl;
    thestack->SetMaximum(1.3*maxamount); // sumhist
    this->Update();
    
    exists = true;    
    
    if (i==(numsamps-1))
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
        sumMCband->Draw("2");    

        if (drawleg)
        {
            theleg->AddEntry(sumMCband,"Sum Bkgd","F");
            theleg->Draw();
        }      
        thisMGP.CMSInfoLatex->Draw();
        thisMGP.canvas.Add(this);
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
}




void makeAndAdd2DPlot1Sample(MakeGoodPlot &thisMGP, int i, TString thehist)
{
    GoodPlot *dummyplot = new GoodPlot(thehist+thisMGP.sample_names_reg[thisMGP.samples[i]]);
    dummyplot->addPlot2D(thisMGP,i,thehist);
    thisMGP.canvas.Add(dummyplot);
}