//-------- Charlie Mueller 5/12/2017 -------//
#include "selection.h"
#include "loadSamples.h"
#include "treeTools.h"
#include "plotObjectClasses.h"

void plotMaker_signalExtraction(void)
{
  TFile *outputfile_cards = new TFile("card_hists.root", "RECREATE");
  TFile *outputfile = new TFile("extraction_plots.root", "RECREATE");
  //////////////////////////
  ///
  /// choose samples
  ///
  //////////////////////////
  std::vector<Sample> samples; //push back in order you want stacked
  samples.push_back(Sample("flips"));
  samples.push_back(Sample("fakes"));  
  samples.push_back(Sample("tttt"));
  samples.push_back(Sample("tWll"));
  samples.push_back(Sample("tZq"));
  samples.push_back(Sample("WGToLNuG"));
  samples.push_back(Sample("ZGTo2LG"));
  samples.push_back(Sample("TTGJets"));
  samples.push_back(Sample("TGJets"));
  samples.push_back(Sample("Wjets"));
  samples.push_back(Sample("WWqq_rares"));
  samples.push_back(Sample("WW_doublescatering_rares"));
  samples.push_back(Sample("WWW_rares"));
  samples.push_back(Sample("WWZ_rares"));
  samples.push_back(Sample("WZZ_rares"));
  samples.push_back(Sample("ZZZ_rares"));
  samples.push_back(Sample("WW_2l2nu"));
  samples.push_back(Sample("WZ_to3lnu"));
  samples.push_back(Sample("ZZ_to4l"));
  samples.push_back(Sample("ttZ"));
  samples.push_back(Sample("ttZ_M1to10"));
  samples.push_back(Sample("ttjets_semilep"));
  samples.push_back(Sample("ttjets_dilep"));
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

  PlotObject finalShape("final_shape_","BDT (ttH,tt/ttV) bin",8,0.5,8.5,"final_shape");
  StackObject finalShape_stack("final_shape_","BDT (ttH,tt/ttV) bin"); 
  stacks[finalShape.hist_name] = finalShape_stack;
  plots.push_back(finalShape);

  PlotObject finalShape_cards("final_shape","BDT (ttH,tt/ttV) bin",8,0.5,8.5,"final_shape");


  for (const auto & sample : samples)
    {
      finalShape_cards.fill(sample,outputfile_cards);
      //cout << "sample: " << sample.legend_name << endl;
      for (auto & plot : plots)
       	{
       	  plot.fill(sample, outputfile);
	  // cout << "total 2lss: " << plot.template_hist->Integral() << endl;
	  // cout << "2lss ee: " << plot.ee_hist->Integral() << endl;
	  // cout << "2lss em: " << plot.em_hist->Integral() << endl;
	  // cout << "2lss mm: " << plot.mm_hist->Integral() << endl;
       	  stacks[plot.hist_name].Add(plot);
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
  outputfile_cards->Close();  

}
