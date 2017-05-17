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
  PlotObject lep1Pt("l1_pt","Leading lepton corrected p_{T} [GeV]",10,0,200,"min(fakeable_leptons[0].correctedPt,199)");
  StackObject l1Pt_stack("l1_pt","leading lepton corrected p_{T} [GeV]"); 
  stacks[lep1Pt.hist_name] = l1Pt_stack;
  plots.push_back(lep1Pt);

  PlotObject lep2Pt("l2_pt","Subleading lepton corrected p_{T} [GeV]",10,0,100,"min(fakeable_leptons[1].correctedPt,99)");
  StackObject l2Pt_stack("l2_pt","Subleading lepton corrected p_{T} [GeV]"); 
  stacks[lep2Pt.hist_name] = l2Pt_stack;
  plots.push_back(lep2Pt);

  PlotObject mll("mll","m(ll) [GeV]",10,0,400,"min(mll,399)");
  StackObject mll_stack("mll","m(ll) [GeV]"); 
  stacks[mll.hist_name] = mll_stack;
  plots.push_back(mll);

  PlotObject qSum("qSum","q(l_{1})",2,-2,2,"fakeable_leptons[1].charge");
  StackObject qSum_stack("qSum","q(l_{1})"); 
  stacks[qSum.hist_name] = qSum_stack;
  plots.push_back(qSum);

  PlotObject nJets("nJets","N(jet, p_{T} > 25 GeV)",4,4,8,"min(@preselected_jets.size(),7.9)");
  StackObject nJets_stack("nJets","N(jet, p_{T} > 25 GeV)"); 
  stacks[nJets.hist_name] = nJets_stack;
  plots.push_back(nJets);
  

  for (const auto & sample : samples)
    {

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
}
