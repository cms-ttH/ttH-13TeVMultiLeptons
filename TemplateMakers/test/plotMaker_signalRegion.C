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
  //sample_vector.push_back(Sample("flips"));
  //sample_vector.push_back("fakes");  
  // sample_vector.push_back("tttt");
  // sample_vector.push_back("tqZ");
  // sample_vector.push_back("WWqq_rares");
  // sample_vector.push_back("WWds");
  // sample_vector.push_back(WWZ);
  // sample_vector.push_back(WZZ);
  // sample_vector.push_back(ZZZ);
  // sample_vector.push_back(WW);
  // sample_vector.push_back(WZ);
  // sample_vector.push_back(ZZ);
  // sample_vector.push_back(ttGammaStar);
  samples.push_back(Sample("ttZ"));
  samples.push_back(Sample("ttW"));
  samples.push_back(Sample("ttH"));
  //  sample_vector.push_back(Sample("data"));

  
  //////////////////////////
  ///
  /// choose plots
  ///
  //////////////////////////

  std::map<TString, StackObject> stacks;
  std::vector<PlotObject> plots;
  
  //TString drawCommand;
  PlotObject lep1Pt("l1_pt","leading lepton corrected p_{T}",10,0,200,"fakeable_leptons[0].correctedPt");
  StackObject l1Pt_stack("l1_pt","leading lepton corrected p_{T}"); 
  stacks[lep1Pt.hist_name] = l1Pt_stack;
  plots.push_back(lep1Pt);

  for (const auto & sample : samples)
    {
      for (auto & plot : plots)
       	{
       	  plot.fill(sample, outputfile);
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
