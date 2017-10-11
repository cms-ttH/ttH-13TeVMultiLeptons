// makegoodplot() by Geoff Smith
// resurrected from 8 TeV original version
// flexible code for quick plots/studies directly from trees
// root makegoodplot.C+
//

#include "MakeGoodPlot_src/MakeGoodPlot.cc"
#include "MakeGoodPlot_src/nicepalette.h"

void makegoodplot()
{
        // declare new instance:
        MakeGoodPlot *newplot = new MakeGoodPlot();
        set_plot_style();
  
        // vector of samples to include in the plot:
	std::vector<int> samples;
        
        // Uncomment these to add sample to plot. Edit loadsamples() to change how samples are loaded.
        
//	samples.push_back(0);           // data

	samples.push_back(1);           // ttH
//	samples.push_back(2);           // (unused)
//	samples.push_back(3);           // (unused)                    
//	samples.push_back(4);           // (unused)                    
//	samples.push_back(5);           // TTJets                      
//	samples.push_back(6);           // ZJets                       
//	samples.push_back(7);           // WJets                       
//	samples.push_back(8);           // TTWJets                     
//      samples.push_back(9);           // TTZJets                     
//	samples.push_back(10);          // diboson (WZ)                
//      samples.push_back(11);          // diboson (ZZ)                
//      samples.push_back(12);          // (unused)                    
//      samples.push_back(13);          // TTbar: Dilepton                   
//      samples.push_back(14);          // TTbar: 1l from top        
//      samples.push_back(15);          // TTbar: 1l from anti-top
//      samples.push_back(16);          // (unused)      
//      samples.push_back(17);          // (unused)
//      samples.push_back(18);          // (unused)      
//      samples.push_back(19);          // (unused)     
  
  
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Do whatever you want here (just modify or make new member function in MakeGoodPlot as appropriate). /////////
		
	//newplot->draw_simple_curves_normalized(samples);	// <- draws all samples in vector
//	newplot->draw_nice_stack(samples);			// <- draws all samples in vector	
//	newplot->draw_ROC_curves(samples,1);		        // <- draws all samples in vector, with specified sample as signal
        //newplot->draw_ROC_iso(signal);	


        //newplot->print_cutflow(samples);


        newplot->draw_eff_curves(samples);


        //newplot->draw_several_comparisons(samples);
        
        //std::vector<TString> somefiles;
        //somefiles.push_back("temp_0.root");
        //somefiles.push_back("temp_1.root");
        //newplot->compareplots(samples,somefiles);

        
        //newplot->draw_2D_plot(samples);
        
        
        //newplot->trigger_studies(samples);
        
        //newplot->lepstudies(samples);
        //newplot->fourlstudies(samples);
	//newplot->threelstudies(samples);
	//newplot->MatchTester_ttW_SS(samples);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
