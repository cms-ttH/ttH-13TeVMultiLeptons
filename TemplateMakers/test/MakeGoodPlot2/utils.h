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
std::string TString2string(TString the_abomination)
{
        std::ostringstream thess;
        thess << the_abomination;
        std::string string_out = thess.str();
        return string_out;
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

string getjettagcategory(string lepcat, int jets, int tags)
{
    
    string jetstr = "";
    string tagstr = "";
    
    if (tags>=2) tagstr = "_2b";
    else if (tags==1) tagstr = "_1b";
    else return "null";
    
    std::size_t foundstr = lepcat.find("2l");
    
    if ( foundstr!=std::string::npos )
    {
        if (jets>=6) jetstr = "_6j";
        else if (jets==5) jetstr = "_5j";
        else if (jets==4) jetstr = "_4j";
        else if (jets==3) jetstr = "_3j";
        else if (jets==2) jetstr = "_2j";
        else return "null";
    }
    
    foundstr = lepcat.find("3l");
    if ( foundstr!=std::string::npos )
    {
        if (jets>=4) jetstr = "_4j";
        else if (jets==3) jetstr = "_3j";
        else if (jets==2) jetstr = "_2j";
        else if (jets==1) jetstr = "_1j";
        else return "null";
    }
    
    foundstr = lepcat.find("4l");
    if ( foundstr!=std::string::npos )
    {
        if (jets>=2) jetstr = "_2j";
        else if (jets==1) jetstr = "_1j";
        else return "null";
    }
    
    foundstr = lepcat.find("5l");
    if ( foundstr!=std::string::npos )
    {
        if (jets>=1) jetstr = "_1j";
        else return "null";
        if (tags>=1) tagstr = "_1b";
        else return "null";
    }
    
    return lepcat+jetstr+tagstr;

}



void clean_neg_bins(TH1 &negBinHist)
{
    // this works for 1D and 2D hists
    int numbinsx = negBinHist.GetNbinsX();
    int numbinsy = negBinHist.GetNbinsY();
    int numbins = numbinsx*numbinsy;
    
    for (int i=1; i<=numbinsx; i++)
    {
        for (int j=1; j<=numbinsy; j++)
        {                  
            int bin = negBinHist.GetBin(i,j);
            double bincont = negBinHist.GetBinContent(bin);

            if (bincont<0.) 
            {
                negBinHist.SetBinContent(bin,0.);
                negBinHist.SetBinError(bin,0.);
            }
        } 
    }
}

