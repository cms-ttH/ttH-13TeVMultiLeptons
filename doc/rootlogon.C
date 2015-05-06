{
  // Set up FW Lite for automatic loading of CMS libraries
  // and data formats.   As you may have other user-defined setup
  // in your rootlogon.C, the CMS setup is executed only if the CMS
  // environment is set up.
  //
  
// TString cmsswbase = getenv("CMSSW_BASE");

//   if (cmsswbase.Length() > 0)
//     {
//       //
//       // The CMSSW environment is defined (this is true even for FW Lite)
//       // so set up the rest.
//       //
       
       

//     }


TString cmsswbase = getenv("CMSSW_BASE");

if (cmsswbase.Length() > 0)
{
//
// The CMSSW environment is defined (this is true even for FW Lite)
// so set up the rest.
//
  TString makeshared(gSystem->GetMakeSharedLib());
  TString dummy = makeshared.ReplaceAll("-W ", "");
  gSystem->SetMakeSharedLib(makeshared);
  //TString dummy = makeshared.ReplaceAll("-Wshadow ", "");
  TString dummy = makeshared.ReplaceAll("-Wshadow ", "-std=c++11 "); //-std=c++11 // -std=c++0x
  gSystem->SetMakeSharedLib(makeshared);
  
 
  cout << "Loading FW Lite setup." << endl;
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");
  

  gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");

}	
   	
#include <iostream.h>
//#include <iomanip.h>
#include <time.h>
//#include "nicepalette.h"

gROOT->SetStyle("Plain");
//   	gStyle->SetPalette(1,0);

// See http://root.cern.ch/root/roottalk/roottalk00/1067.html
// Objects like the title box and the statistics box are generated on the fly
// when the histogram or graph is being drawn.
// Use the TStyle control object to set your own defaults:
//
gStyle->SetTitleX(0.1);		//Title box x position (top left-hand corner)	
gStyle->SetTitleY(0.995); 	//Title box y position (default value)		
gStyle->SetTitleW(0.8);		//Title box width as fraction of pad size
gStyle->SetTitleH(0.08);	//Title box height as fraction of pad size	
gStyle->SetTitleColor(1);	//Title box fill color
//gStyle->SetTitleTextColor(4);	//Title box text color
gStyle->SetTitleTextColor(1);	//Title box text color
gStyle->SetTitleStyle(1001);	//Title box fill style!
//TitleFont = 10*fontid + 2 (12 is normal, 22 bold 32 italic)
gStyle->SetTitleFont(32);  	//Title box font (32=italic times bold)
gStyle->SetTitleBorderSize(2);	//Title box border thickness
gStyle->SetTitleOffset(0.9,"x");	//X-axis title offset from axis
gStyle->SetTitleSize(0.05,"x");		//X-axis title size
gStyle->SetTitleSize(0.05,"y");
gStyle->SetTitleSize(0.05,"z");


gStyle->SetStatX(0.995);		//Stat box x position (top right hand corner)	
gStyle->SetStatY(0.995); 		//Stat box y position 		
gStyle->SetStatW(0.15);	 		//Stat box width as fraction of pad size	
gStyle->SetStatH(0.15);	 		//Size of each line in stat box	
gStyle->SetStatColor(0);		//Stat box fill color
gStyle->SetStatTextColor(1);		//Stat box text color
gStyle->SetStatStyle(1001);		//Stat box fill style!
//StatFont = 10*fontid + 2 (12 is normal, 22 bold 32 italic)
gStyle->SetStatFont(62);  		//Stat box font
gStyle->SetStatBorderSize(2);		//Stat box border thickness
//gStyle->SetStatFormat("6.4g");

//Statistic box options 		(from left to right)
//gStyle->SetOptStat(0); //Integral, Overflow, Underflow, RMS, Mean, Nent, Name
gStyle->SetOptStat(11111111); //Integral, Overflow, Underflow, RMS, Mean, Nent, Name
gStyle->SetOptFit(1111);     //probability, Chi2, errors, name/values of parameters

//Go to view menu on canvas, select markers to view possible values
gStyle->SetMarkerStyle(20);		//Marker is a circle
gStyle->SetMarkerSize(1);  		//Reasonable marker size
//
//to modify a given histogram already in a pad use this?
//TPaveText *title = (TPavbeText*)gPad->GetPrimitive("title");
//title->SetX2NDC(0.6);
//gPad->Modified();

//	gStyle->SetPalette(1,0);

gStyle->SetPaintTextFormat("5.2f");

//set_plot_style();

system("pwd");
}
