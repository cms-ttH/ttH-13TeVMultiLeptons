//-------- Charlie Mueller 5/12/2017 -------//
#include "selection.h"
#include "loadSamples.h"
#include "treeTools.h"
#include "plotObjectClasses.h"

void plotMaker_signalRegion(void)
{
  TFile *outputfile = new TFile("sr_plots.root", "RECREATE");
  //////////////////////////
  ///
  /// choose samples
  ///
  //////////////////////////
  std::vector<Sample> samples; //push back in order you want stacked
  samples.push_back(Sample("flips"));
  samples.push_back(Sample("fakes"));  
  samples.push_back(Sample("tttt"));
  samples.push_back(Sample("tZq"));

  samples.push_back(Sample("WGToLNuG"));
  samples.push_back(Sample("ZGTo2LG"));

  samples.push_back(Sample("WWqq_rares"));
  samples.push_back(Sample("WW_doublescatering_rares"));
  samples.push_back(Sample("WWW_rares"));
  samples.push_back(Sample("WWZ_rares"));
  samples.push_back(Sample("WZZ_rares"));
  samples.push_back(Sample("ZZZ_rares"));
  //  samples.push_back(Sample("WW_diboson"));
  samples.push_back(Sample("WZ_diboson"));
  samples.push_back(Sample("ZZ_diboson"));
  // samples.push_back(ttGammaStar);
  samples.push_back(Sample("ttZ"));
  samples.push_back(Sample("ttW"));
  samples.push_back(Sample("ttH"));
  samples.push_back(Sample("data"));

  
  //////////////////////////
  ///
  /// choose plots
  ///
  //////////////////////////

  std::map<TString, StackObject> stacks;
  std::vector<PlotObject> plots;
  
  //TString drawCommand;
  PlotObject lep1Pt("l1_pt","leading lepton corrected p_{T} [GeV]",10,0,200,"fakeable_leptons[0].correctedPt");
  StackObject l1Pt_stack("l1_pt","leading lepton corrected p_{T} [GeV]"); 
  stacks[lep1Pt.hist_name] = l1Pt_stack;
  plots.push_back(lep1Pt);

  for (const auto & sample : samples)
    {

      cout << "sample: " << sample.legend_name << endl;
      for (auto & plot : plots)
       	{
       	  plot.fill(sample, outputfile);
	  cout << "total 2lss: " << plot.template_hist->Integral() << endl;
	  cout << "2lss ee: " << plot.ee_hist->Integral() << endl;
	  cout << "2lss em: " << plot.em_hist->Integral() << endl;
	  cout << "2lss mm: " << plot.mm_hist->Integral() << endl;

       	  stacks[plot.hist_name].Add(plot,sample);
       	}
    }

  //draw stacks
  for (auto & it : stacks )
    {
      auto key = it.first;
      auto stack = it.second;
      stack.draw();
    }
  outputfile->Close();  
}
