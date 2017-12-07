TString int2ss(int theint)
{
	std::ostringstream thess;
	thess << theint;
	TString string_out = thess.str();
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
        leg.SetNColumns(5);
        return leg;
    }  
    else if (format=="darren")
    {        
        TLegend leg(0.14,0.75,0.94,0.89);
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
