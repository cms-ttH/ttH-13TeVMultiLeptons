// makegoodplot() by Geoff Smith
// resurrected from 8 TeV original version
// flexible code for quick plots/studies directly from trees
// root makegoodplot.C+
//

#include "MakeGoodPlot_src/MakeGoodPlot.cc"
#include "/afs/cern.ch/user/g/gesmith/nicepalette.h"

void makegoodplot()
{
	// declare new instance:
	MakeGoodPlot *newplot = new MakeGoodPlot();
	set_plot_style();
        
        // vector of samples to include in the plot:
	std::vector<int> samples;
	std::vector<int> signal;
	
        signal.push_back(1); // ttH (125)
        
        // uncomment these to add sample to plot:
//	samples.push_back(0); // mu data

	samples.push_back(1); // new ttH (125)	
//	samples.push_back(2); // ttbar_bbbar;
//	samples.push_back(3); // ttbar_b
//	samples.push_back(4); // ttbar_ccbar
	samples.push_back(5); // TTJets
//	samples.push_back(1); // ttH (125)
	samples.push_back(6); // ZJets
	samples.push_back(7); // WJets
	samples.push_back(8); // TTWJets
	samples.push_back(9); // TTZJets

	samples.push_back(10); // diboson (WZ)
        samples.push_back(11); // diboson (ZZ)
        
//        samples.push_back(12); // old ttH
        
        // done with setup..
        
/////////////////////////////////////////////////////////////////////////////////////////

/////// Do whatever you want here (just modify or make new member function in MakeGoodPlot.cc as appropriate). /////////
		
//	newplot->draw_simple_curves_normalized(samples);	// <- draws all samples in vector

//	newplot->draw_nice_stack(samples);			// <- draws all samples in vector
	
//	int signal = 1; // tth
//	newplot->draw_ROC_curves(samples,signal);		// <- draws all samples in vector, with specified sample as signal
	
 //	newplot->make_eff_vs_var_separation_plot(samples);

	//newplot->draw_corr_rand_gauss_2D(samples,true);

//	newplot->draw_something_quick_without_samples();       
        
//	newplot->print_geninfo_table(samples);

//	newplot->print_yields_given_syst(samples);

//	newplot->make_simple_plot_mytrees("0pt5shift",1);
//	newplot->make_simple_plot_mytrees("1pt0shift",0);
//	newplot->make_simple_plot_mytrees("2pt0shift",0);

//        newplot->print_cutflow(samples);

	//newplot->draw_ROC_iso(signal);


        //newplot->draw_several_comparisons(samples);
        
        //std::vector<TString> somefiles;
        //somefiles.push_back("temp_0.root");
        //somefiles.push_back("temp_1.root");
        //newplot->compareplots(samples,somefiles);

        
        newplot->draw_2D_plot(samples);
        


//--------------------------------------------------------------------------


//// leftover from 8 TeV (maybe not useful?)

	// don't use:
//	newplot->visualize_yggdrasil(1); 			// <- only one sample can be drawn here.

/*	
	TH1F *htemp1 = (TH1F*) gPad->GetPrimitive("asdf_0pt5shift");
	TH1F *htemp2 = (TH1F*) gPad->GetPrimitive("asdf_1pt0shift");
	TH1F *htemp3 = (TH1F*) gPad->GetPrimitive("asdf_2pt0shift");
		
	TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);
	
	leg->SetFillColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.035);
		
	leg->AddEntry(htemp1,"0pt5shift","l");
	leg->AddEntry(htemp2,"1pt0shift","l");
	leg->AddEntry(htemp3,"2pt0shift","l");
	
	leg->Draw();
*/	



}
	
	
	
