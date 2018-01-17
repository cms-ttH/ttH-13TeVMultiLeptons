TString int2ss(int theint)
{
	std::ostringstream thess;
	thess << theint;
	TString string_out = thess.str();
	return string_out;
}
string d2ss(double dbl,int prec=-1)
{
    std::ostringstream thess;
    if (prec>0) thess << fixed << setprecision(prec) << dbl;
    else thess << dbl;
    std::string thestr = thess.str();
    return thestr;
}
TLegend getleg(string format)
{
    if (format=="bl") 
    {                       
        TLegend leg(0.12,0.12,0.3,0.4);
        leg.SetLineColor(kWhite);
        leg.SetShadowColor(kWhite);            
        leg.SetTextFont(42);                        
        return leg;
    }
    else if (format=="ul" || format=="tl")
    {        
        TLegend leg(0.3,0.77,0.7,0.88); // not sure about this one..
        leg.SetLineColor(kWhite);
        leg.SetShadowColor(kWhite);            
        leg.SetTextFont(42);                        
        return leg;      
    }
    else if (format=="br")     
    {
        TLegend leg(0.55,0.12,0.89,0.4);
        leg.SetLineColor(kWhite);
        leg.SetShadowColor(kWhite);            
        leg.SetTextFont(42);
        return leg;
    }          
    else if (format=="ur" || format=="tr")
    {     
        TLegend leg(0.55,0.7,0.89,0.89);
        leg.SetLineColor(kWhite);
        leg.SetShadowColor(kWhite);            
        leg.SetTextFont(42);                        
        return leg;        
    }   
    else if (format=="above")
    {
        TLegend leg(0.11,0.91,0.89,0.99);
        leg.SetLineColor(kWhite);
        leg.SetShadowColor(kWhite);            
        leg.SetTextFont(42);
        leg.SetNColumns(3);
        return leg;
    }  
    else if (format=="darren")
    {        
        TLegend leg(0.14,0.75,0.89,0.89);
        leg.SetLineColor(kWhite);
        leg.SetShadowColor(kWhite);            
        leg.SetTextFont(42);
        leg.SetNColumns(5);
        return leg;
    }  
    else
    {    
        TLegend leg(0.55,0.7,0.9,0.9);
        leg.SetLineColor(kWhite);
        leg.SetShadowColor(kWhite);            
        leg.SetTextFont(42);                        
        return leg;
    }
}

void clean_neg_bins(TH1 &negBinHist)
{
    int numbins = negBinHist.GetNbinsX();
    for (int i=1; i<=numbins; i++)
    {
        double bincont = negBinHist.GetBinContent(i);
        if (bincont<0.) 
        {
            negBinHist.SetBinContent(i,0.);
            negBinHist.SetBinError(i,0.);
        }
        
    }
}

