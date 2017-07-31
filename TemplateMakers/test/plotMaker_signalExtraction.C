//-------- Charlie Mueller 5/12/2017 -------//
#include "selection.h"
#include "loadSamples.h"
#include "treeTools.h"
#include "plotObjectClasses.h"
#include "systematics.h"
#include "yieldsTableHelper.h"

void plotMaker_signalExtraction(void)
{
  TFile *outputfile_cards = new TFile("card_hists_test.root", "RECREATE");
  TFile *outputfile = new TFile("extraction_plots_test.root", "RECREATE");
  //////////////////////////
  ///
  /// choose samples
  ///
  //////////////////////////
  std::vector<Sample> samples; //push back in order you want stacked

  //reducible
  samples.push_back(Sample("flips"));
  samples.push_back(Sample("fakes"));  
  //convs
  samples.push_back(Sample("ZGTo2LG"));
  samples.push_back(Sample("WGToLNuG"));
  samples.push_back(Sample("TTGJets"));
  samples.push_back(Sample("TGJets"));
  //WWss
  samples.push_back(Sample("WWqq_rares"));
  //rares
  //samples.push_back(Sample("WW_2l2nu")); //zero events
  samples.push_back(Sample("WW_doublescatering_rares"));
  //  samples.push_back(Sample("WWW_rares"));
  samples.push_back(Sample("ZZZ_rares"));
  samples.push_back(Sample("WWZ_rares"));
  samples.push_back(Sample("WZZ_rares"));
  samples.push_back(Sample("ZZ_to4l"));
  samples.push_back(Sample("tttt"));
  samples.push_back(Sample("tZq"));
  samples.push_back(Sample("tWll"));
  //WZ
  samples.push_back(Sample("Wjets")); //zero events
  samples.push_back(Sample("WZ_to3lnu"));
  //ttZ
  samples.push_back(Sample("ttZ_M10"));
  samples.push_back(Sample("ttZ_M1to10"));
  samples.push_back(Sample("ttjets_semilep"));
  samples.push_back(Sample("ttjets_dilep"));
  //ttW
  samples.push_back(Sample("ttW"));
  //signal
  samples.push_back(Sample("ttH"));
  //data
  samples.push_back(Sample("data")); //must have data or it won't work.

  //////////////////////////
  ///
  /// choose plots
  ///
  //////////////////////////

  std::map<TString, StackObject> stacks;
  std::vector<PlotObject> plots;
  
  //TString drawCommand;
  PlotObject ttBDT("tt_BDT","BDT(ttH,tt)",10,-1,1,"vs_ttbar_score");
  StackObject ttBDT_stack("tt_BDT","BDT(ttH,tt)"); 
  stacks[ttBDT.hist_name] = ttBDT_stack;
  plots.push_back(ttBDT);

  PlotObject ttBDT_BDTv8("tt_BDT_BDTv8","BDT(ttH,tt)",10,-1,1,"vs_ttbar_withRecoBdt_score");
  StackObject ttBDT_BDTv8_stack("tt_BDT_BDTv8","BDT(ttH,tt)"); 
  stacks[ttBDT_BDTv8.hist_name] = ttBDT_BDTv8_stack;
  plots.push_back(ttBDT_BDTv8);

  PlotObject ttVBDT("ttV_BDT","BDT(ttH,ttV)",10,-1,1,"vs_ttv_score");
  StackObject ttVBDT_stack("ttV_BDT","BDT(ttH,ttV)"); 
  stacks[ttVBDT.hist_name] = ttVBDT_stack;
  plots.push_back(ttVBDT);

  PlotObject finalShape_bdtv8("final_shape_bdtv8_","BDT (ttH,tt/ttV) bin",8,0.5,8.5,"final_shape_BDTv8");
  StackObject finalShape_bdtv8_stack("final_shape_bdtv8_","BDT (ttH,tt/ttV) bin"); 
  stacks[finalShape_bdtv8.hist_name] = finalShape_bdtv8_stack;
  plots.push_back(finalShape_bdtv8);

  PlotObject finalShape("final_shape_","BDT (ttH,tt/ttV) bin",8,0.5,8.5,"final_shape");
  StackObject finalShape_stack("final_shape_","BDT (ttH,tt/ttV) bin"); 
  stacks[finalShape.hist_name] = finalShape_stack;
  plots.push_back(finalShape);
  
  PlotObject finalShape_cards("final_shape","BDT (ttH,tt/ttV) bin",8,0.5,8.5,"final_shape_BDTv8");
  //  PlotObject finalShape_cards("final_shape","BDT (ttH,tt/ttV) bin",8,0.5,8.5,"final_shape");

  auto mcSysts = getMcSystShapes(finalShape_cards);
  auto frSysts = getFrSystShapes(finalShape_cards);
  //auto statSysts = getTemplateStatSystShapes(finalShape_cards);

  YieldsTableHelper yieldsTable;

  for (const auto & sample : samples)
    {
      finalShape_cards.fill(sample,outputfile_cards);
      cout << "processing sample: " << sample.legend_name << endl;
      if (sample.sample_name != "data" and sample.sample_name != "fakes" and sample.sample_name != "flips")
	{
	  for (auto & plot : mcSysts) plot.fill(sample, outputfile_cards);
	  //for (auto & plot : statSysts) plot.fill(sample, outputfile_cards);
	}
      else if (sample.sample_name == "fakes")
	{
	  for (auto & plot : frSysts) plot.fill(sample, outputfile_cards);
	  //for (auto & plot : statSysts) plot.fill(sample, outputfile_cards);
	}

      bool first_plot = true;
      for (auto & plot : plots)
       	{
       	  plot.fill(sample, outputfile);
	  if (first_plot) yieldsTable.fill(plot);
       	  stacks[plot.hist_name].Add(plot);
	  first_plot = false;
       	}
    }
  
  yieldsTable.sumBkgs();

  //draw stacks
  for (auto & it : stacks )
    {
      auto key = it.first;
      auto stack = it.second;
      stack.draw();
    }
  outputfile->Close();  
  outputfile_cards->Close();  

}
