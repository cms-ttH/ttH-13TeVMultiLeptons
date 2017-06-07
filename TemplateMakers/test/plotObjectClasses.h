#include "cms_spam/CMS_lumi.C"

TH1 *sumStack(THStack* stack)
{
  //cout<<"doing sum  "<<endl;         
  TList * mylist = (TList*)stack->GetHists();
  TIter next(mylist);
  TH1 *hh  = (TH1*) mylist -> First() ->Clone();
  //hh -> SetLineColor(kBlack);
  //hh -> SetFillStyle(0);
  TObject *obj;
  while ((obj = next()))
    {
      // cout<<obj->GetName()<<endl;
      //skip first object since it's used by creating the histogram                               
      if(obj == mylist->First()) continue;
      hh -> Add((TH1*)obj);
    }
  return hh;
}

TH1 *ratioErrorHist(TH1* mc_hist)
{
  TH1 *mc_error_hist = (TH1*)mc_hist->Clone("");
  for (int bin=1; bin<= mc_hist->GetNbinsX(); bin++)
    {
      double mc_value = mc_hist->GetBinContent(bin);
      double mc_error = mc_hist->GetBinError(bin); 
      if (mc_value != 0)
	{
	  double ratio_error_mc = mc_error/mc_value;
	  mc_error_hist->SetBinContent(bin,1);
	  mc_error_hist->SetBinError(bin,ratio_error_mc);
	}
      else
	{
	  mc_error_hist->SetBinContent(bin,1);
	  mc_error_hist->SetBinError(bin,0);
	}
     }
  mc_error_hist->SetFillStyle(1001);
  mc_error_hist->SetFillColor(kCyan);
  
  return mc_error_hist;
}


class PlotObject
{
private:

  int bins;
  double xmin;
  double xmax;
  TString drawCommand;

public:
 PlotObject(TString hist_name_="name", TString hist_title_="hist_title", int bins_=10, double xmin_=0., double xmax_ =100., TString drawCommand_="mcwgt"):
  hist_name(hist_name_),
    hist_title(hist_title_),
    bins(bins_),
    xmin(xmin_),
    xmax(xmax_),
    drawCommand(drawCommand_)      
  {
    
  }//default constructor

  TString hist_name;
  TString hist_title;
  TString legend_name;
  TString sample_name;
  TH1D* template_hist;
  TH1D* ee_hist;
  TH1D* mm_hist;
  TH1D* em_hist;
  TH1D* ee_p_hist;
  TH1D* ee_m_hist;
  TH1D* mm_bt_m_hist;
  TH1D* mm_bt_p_hist;
  TH1D* mm_bl_m_hist;
  TH1D* mm_bl_p_hist;
  TH1D* em_bt_m_hist;
  TH1D* em_bt_p_hist;
  TH1D* em_bl_m_hist;
  TH1D* em_bl_p_hist;


  void fill(Sample sample, TFile* fout=0)
  {
    sample_name = sample.sample_name;
    legend_name = sample.legend_name;

    TString hist_save_name = sample_name;
    if (sample_name == "data") hist_save_name = "data_obs";

    TString template_name = hist_name+"_"+hist_save_name;
    template_hist = new TH1D(template_name,hist_title,bins,xmin,xmax);
    template_hist->Sumw2();
    template_hist->SetLineColor(1);
    template_hist->SetMarkerColor(sample.fill_color);

    
    if (sample_name != "data")
      {
	template_hist->SetFillColor(sample.fill_color);
	template_hist->SetFillStyle(sample.fill_style);
      }
    else
      {
    	template_hist->SetMarkerStyle(20);
    	//template_hist->SetMarkerSize(markerSize);
      }


    TString ee_name = template_name+"_ee";
    TString em_name = template_name+"_em";
    TString mm_name = template_name+"_mm";
    TString ee_p_name = template_name+"_ee_p";
    TString ee_m_name = template_name+"_ee_m";
    TString em_bt_p_name = template_name+"_em_bt_p";
    TString em_bt_m_name = template_name+"_em_bt_m";
    TString em_bl_p_name = template_name+"_em_bl_p";
    TString em_bl_m_name = template_name+"_em_bl_m";
    TString mm_bt_p_name = template_name+"_mm_bt_p";
    TString mm_bt_m_name = template_name+"_mm_bt_m";
    TString mm_bl_p_name = template_name+"_mm_bl_p";
    TString mm_bl_m_name = template_name+"_mm_bl_m";

    ee_hist = (TH1D*)template_hist->Clone(ee_name); ee_hist->Sumw2();   
    em_hist = (TH1D*)template_hist->Clone(em_name); em_hist->Sumw2();   
    mm_hist = (TH1D*)template_hist->Clone(mm_name); mm_hist->Sumw2();       
    ee_p_hist = (TH1D*)template_hist->Clone(ee_p_name); ee_p_hist->Sumw2();   
    ee_m_hist = (TH1D*)template_hist->Clone(ee_m_name); ee_m_hist->Sumw2();
    em_bt_p_hist = (TH1D*)template_hist->Clone(em_bt_p_name); em_bt_p_hist->Sumw2();   
    em_bt_m_hist = (TH1D*)template_hist->Clone(em_bt_m_name); em_bt_m_hist->Sumw2();
    em_bl_p_hist = (TH1D*)template_hist->Clone(em_bl_p_name); em_bl_p_hist->Sumw2();  
    em_bl_m_hist = (TH1D*)template_hist->Clone(em_bl_m_name); em_bl_m_hist->Sumw2();
    mm_bt_p_hist = (TH1D*)template_hist->Clone(mm_bt_p_name); mm_bt_p_hist->Sumw2();       
    mm_bt_m_hist = (TH1D*)template_hist->Clone(mm_bt_m_name); mm_bt_m_hist->Sumw2();       
    mm_bl_p_hist = (TH1D*)template_hist->Clone(mm_bl_p_name); mm_bl_p_hist->Sumw2();       
    mm_bl_m_hist = (TH1D*)template_hist->Clone(mm_bl_m_name); mm_bl_m_hist->Sumw2();       

    TString drawCommand_template = drawCommand + " >> "+template_name;
    TString drawCommand_ee = drawCommand + " >> "+ee_name;
    TString drawCommand_em = drawCommand + " >> "+em_name;
    TString drawCommand_mm = drawCommand + " >> "+mm_name;
    TString drawCommand_ee_p = drawCommand + " >> "+ee_p_name;
    TString drawCommand_ee_m = drawCommand + " >> "+ee_m_name;
    TString drawCommand_em_bt_p = drawCommand + " >> "+em_bt_p_name;
    TString drawCommand_em_bt_m = drawCommand + " >> "+em_bt_m_name;
    TString drawCommand_em_bl_p = drawCommand + " >> "+em_bl_p_name;
    TString drawCommand_em_bl_m = drawCommand + " >> "+em_bl_m_name;
    TString drawCommand_mm_bt_p = drawCommand + " >> "+mm_bt_p_name;
    TString drawCommand_mm_bt_m = drawCommand + " >> "+mm_bt_m_name;
    TString drawCommand_mm_bl_p = drawCommand + " >> "+mm_bl_p_name;
    TString drawCommand_mm_bl_m = drawCommand + " >> "+mm_bl_m_name;

    TCut weight = "";
    TCut sim_weight = "mcwgt*btag_weight*trigger_SF*lepton_SF";
    TCut prompt = "((tight_leptons[0].isPromptFinalState || tight_leptons[0].isDirectPromptTauDecayProductFinalState) && (tight_leptons[1].isPromptFinalState || tight_leptons[1].isDirectPromptTauDecayProductFinalState))";
    TCut matchRightCharge = "tight_leptons[0].pdgID == tight_leptons[0].genPdgID && tight_leptons[1].pdgID == tight_leptons[1].genPdgID";
    if (sample_name != "data" && sample_name != "fakes" && sample_name != "flips" )
      {
	weight= sim_weight*prompt*matchRightCharge;
      }
    else if (sample_name == "fakes" || sample_name == "flips")
      {
	weight= "mcwgt";
      }
    if (legend_name == "Convs")//sample_name == "TTGJets" || sample_name == "TGJets")
      {
    	TCut conv_cut = "(tight_leptons[0].genMotherPdgID == 22 || tight_leptons[1].genMotherPdgID == 22)";
    	weight = conv_cut*sim_weight*matchRightCharge;
      }

    TCut weight_ee = "(flavor_category==\"ee\")"*weight;
    TCut weight_em = "(flavor_category==\"em\")"*weight;
    TCut weight_mm = "(flavor_category==\"mm\")"*weight;
    TCut weight_ee_p = "(flavor_category==\"ee\" && plus_category == 1)"*weight;
    TCut weight_ee_m = "(flavor_category==\"ee\" && plus_category == 0)"*weight;
    TCut weight_em_bt_p = "(flavor_category==\"em\" && plus_category == 1 && bTight_category ==1)"*weight;
    TCut weight_em_bt_m = "(flavor_category==\"em\" && plus_category == 0 && bTight_category ==1)"*weight;
    TCut weight_em_bl_p = "(flavor_category==\"em\" && plus_category == 1 && bTight_category ==0)"*weight;
    TCut weight_em_bl_m = "(flavor_category==\"em\" && plus_category == 0 && bTight_category ==0)"*weight;
    TCut weight_mm_bt_p = "(flavor_category==\"mm\" && plus_category == 1 && bTight_category ==1)"*weight;
    TCut weight_mm_bt_m = "(flavor_category==\"mm\" && plus_category == 0 && bTight_category ==1)"*weight;
    TCut weight_mm_bl_p = "(flavor_category==\"mm\" && plus_category == 1 && bTight_category ==0)"*weight;
    TCut weight_mm_bl_m = "(flavor_category==\"mm\" && plus_category == 0 && bTight_category ==0)"*weight;

    
    auto tree = sample.tree;
    template_hist->SetDirectory(gDirectory);
    ee_hist->SetDirectory(gDirectory);
    em_hist->SetDirectory(gDirectory);
    mm_hist->SetDirectory(gDirectory);
    ee_p_hist->SetDirectory(gDirectory);
    ee_m_hist->SetDirectory(gDirectory);
    em_bt_p_hist->SetDirectory(gDirectory);
    em_bt_m_hist->SetDirectory(gDirectory);
    em_bl_p_hist->SetDirectory(gDirectory);
    em_bl_m_hist->SetDirectory(gDirectory);
    mm_bt_p_hist->SetDirectory(gDirectory);
    mm_bt_m_hist->SetDirectory(gDirectory);
    mm_bl_p_hist->SetDirectory(gDirectory);
    mm_bl_m_hist->SetDirectory(gDirectory);
    
    TString drawOption = "goff";

    tree->Draw(drawCommand_template,weight,drawOption);
    tree->Draw(drawCommand_ee,weight_ee,drawOption);
    tree->Draw(drawCommand_em,weight_em,drawOption);
    tree->Draw(drawCommand_mm,weight_mm,drawOption);
    tree->Draw(drawCommand_ee_p,weight_ee_p,drawOption);
    tree->Draw(drawCommand_ee_m,weight_ee_m,drawOption);
    tree->Draw(drawCommand_em_bt_p,weight_em_bt_p,drawOption);
    tree->Draw(drawCommand_em_bt_m,weight_em_bt_m,drawOption);
    tree->Draw(drawCommand_em_bl_p,weight_em_bl_p,drawOption);
    tree->Draw(drawCommand_em_bl_m,weight_em_bl_m,drawOption);
    tree->Draw(drawCommand_mm_bt_p,weight_mm_bt_p,drawOption);
    tree->Draw(drawCommand_mm_bt_m,weight_mm_bt_m,drawOption);
    tree->Draw(drawCommand_mm_bl_p,weight_mm_bl_p,drawOption);
    tree->Draw(drawCommand_mm_bl_m,weight_mm_bl_m,drawOption);
    
    template_hist->Scale( sample.xsec );
    ee_hist->Scale( sample.xsec );
    em_hist->Scale( sample.xsec );
    mm_hist->Scale( sample.xsec );
    ee_p_hist->Scale( sample.xsec );
    ee_m_hist->Scale( sample.xsec );
    em_bt_p_hist->Scale( sample.xsec );
    em_bt_m_hist->Scale( sample.xsec );
    em_bl_p_hist->Scale( sample.xsec );
    em_bl_m_hist->Scale( sample.xsec );
    mm_bt_p_hist->Scale( sample.xsec );
    mm_bt_m_hist->Scale( sample.xsec );
    mm_bl_p_hist->Scale( sample.xsec );
    mm_bl_m_hist->Scale( sample.xsec );
    
    if (fout)
      {
	fout->cd();
	template_hist->Write();
	ee_hist->Write();
	em_hist->Write();
	mm_hist->Write();
	ee_p_hist->Write();
	ee_m_hist->Write();
	em_bt_p_hist->Write();
	em_bt_m_hist->Write();
	em_bl_p_hist->Write();
	em_bl_m_hist->Write();
	mm_bt_p_hist->Write();
	mm_bt_m_hist->Write();
	mm_bl_p_hist->Write();
	mm_bl_m_hist->Write();
      }

  }
  
  virtual ~PlotObject(){}
};


class StackObject
{
 private:
  TString stack_name;
  TString stack_title;
  TLegend *leg = new TLegend(0.5864486,0.5007465,0.8364486,0.8483576);
  vector<TString> legend_list;
  
  void drawSingle(THStack* stack, TH1* data_hist)
  {
    TString stack_name = stack->GetName();
    TString can_name = stack_name + "_can";
    //TString save_name = stack_name + ".root";

    TString title = stack->GetTitle();
    stack->SetTitle("");
    data_hist->SetTitle("");

    TCanvas* can = new TCanvas(can_name, can_name,10,32,430,590);

    TPad* pad1 = new TPad("pad1","pad1",0,0.24,1,1);//
    pad1->SetBottomMargin(0);
    pad1->SetTicks();
    pad1->Draw();
    pad1->cd();

    stack->Draw("hist");
    stack->SetMaximum(data_hist->GetMaximum()*1.5);
    stack->GetYaxis()->SetTitle("Events");
    stack->Draw("hist");

    auto prediction = sumStack(stack);
    prediction->SetFillStyle(3344);
    prediction->Draw("e2same");

    if (std::find(legend_list.begin(),legend_list.end(), "Unc.") == legend_list.end())
      {
	leg->AddEntry(prediction,"Unc.","f");
	legend_list.push_back("Unc.");
      }

    
    data_hist->SetMarkerStyle(20);
    data_hist->Draw("epsame");
    
    leg->SetBorderSize(0);
    leg->Draw();

    CMS_lumi( pad1, 4, 0 );
    pad1->Update();

    can->cd();

    double x_min = data_hist->GetXaxis()->GetXmin();
    double x_max = data_hist->GetXaxis()->GetXmax();

    TPad* pad2 = new TPad("pad2","pad2",0,0,1,0.24);
    pad2->SetTicks();
    TLine *line = new TLine(x_min, 1., x_max, 1.);
    
    auto hist_ratio = (TH1D*)data_hist->Clone();
    auto ratio_error = ratioErrorHist(prediction);
    prediction->SetStats(0);
    hist_ratio->SetStats(0);

    hist_ratio->SetLineWidth(1);
    hist_ratio->Divide(prediction);
    
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.4);
    //pad2->SetGridy();
    pad2->Draw();
    pad2->cd();

    hist_ratio->GetYaxis()->SetTitle("Data/pred.");
    double offset_fraction = 1.6;//1.6;
    double hist_max = hist_ratio->GetMaximum();
    double hist_min = hist_ratio->GetMinimum();
    double y_max = 1 + offset_fraction*max(abs(hist_max - 1), abs(hist_min - 1 ));
    double y_min = 1 - offset_fraction*max(abs(hist_max - 1), abs(hist_min - 1 )); 
    //hist_ratio->GetYaxis()->SetRangeUser( y_min, y_max );
    //hist_ratio->GetYaxis()->SetRangeUser(-0.5,2.5);
    hist_ratio->GetYaxis()->SetRangeUser(0,2);
    hist_ratio->SetLineColor(1);
    hist_ratio->SetMarkerColor(1);
    hist_ratio->GetYaxis()->SetLabelSize(.08);
    hist_ratio->GetXaxis()->SetLabelSize(.12);
    hist_ratio->GetXaxis()->SetTitle( title );
    hist_ratio->GetXaxis()->SetTitleSize(0.17);
    hist_ratio->GetYaxis()->SetNdivisions(5,8,0);
    hist_ratio->GetXaxis()->SetTitleFont(42);
    hist_ratio->GetYaxis()->SetTitleOffset(.4);
    hist_ratio->GetYaxis()->SetTitleSize(.10);
    hist_ratio->GetYaxis()->CenterTitle();

    hist_ratio->DrawCopy();
    ratio_error->DrawCopy("e2same");
    hist_ratio->DrawCopy("epsame");
    line->Draw("same");

    can->cd();

    //can->SaveAs(stack_name+".root");
    can->Print(stack_name+"_stackPlot_SR.pdf",".pdf");
  }

public:
 StackObject(TString stack_name_="name", TString stack_title_="stack_title"):
  stack_name(stack_name_),
    stack_title(stack_title_)
    {  
      
      template_stack = new THStack(stack_name,stack_title);
      ee_stack = new THStack(stack_name,stack_title);
      em_stack = new THStack(stack_name,stack_title);
      mm_stack = new THStack(stack_name,stack_title);

    }//default constructor
  
  THStack* template_stack;
  THStack* ee_stack;
  THStack* mm_stack;
  THStack* em_stack;
  /* THStack* ee_p_stack; */
  /* THStack* ee_m_stack; */
  /* THStack* mm_bt_p_stack; */
  /* THStack* mm_bt_m_stack; */
  /* THStack* mm_bl_p_stack; */
  /* THStack* mm_bl_m_stack; */
  /* THStack* em_bt_p_stack; */
  /* THStack* em_bt_m_stack; */
  /* THStack* em_bl_p_stack; */
  /* THStack* em_bl_m_stack; */
 
  TH1D* template_hist_data = NULL;
  TH1D* ee_hist_data = NULL;
  TH1D* mm_hist_data = NULL;
  TH1D* em_hist_data = NULL;
  /* TH1D* ee_p_hist_data = NULL; */
  /* TH1D* ee_m_hist_data = NULL; */
  /* TH1D* mm_bt_p_hist_data = NULL; */
  /* TH1D* mm_bt_m_hist_data = NULL; */
  /* TH1D* mm_bl_p_hist_data = NULL; */
  /* TH1D* mm_bl_m_hist_data = NULL; */
  /* TH1D* em_bt_p_hist_data = NULL; */
  /* TH1D* em_bt_m_hist_data = NULL; */
  /* TH1D* em_bl_p_hist_data = NULL; */
  /* TH1D* em_bl_m_hist_data = NULL; */
 
  void Add(PlotObject plot)
  {
    
    if (plot.legend_name == "Data")
      {
	if (std::find(legend_list.begin(),legend_list.end(), plot.legend_name) == legend_list.end())
	  {
	    leg->AddEntry(plot.template_hist,plot.legend_name,"lpe");
	    legend_list.push_back(plot.legend_name);
	  }
    	template_hist_data = (TH1D*)plot.template_hist->Clone();
    	ee_hist_data = (TH1D*)plot.ee_hist->Clone();
    	mm_hist_data = (TH1D*)plot.mm_hist->Clone();
    	em_hist_data = (TH1D*)plot.em_hist->Clone();
   	/* ee_p_hist_data = (TH1D*)plot.ee_p_hist->Clone(); */
   	/* ee_m_hist_data = (TH1D*)plot.ee_m_hist->Clone(); */
    	/* mm_bt_p_hist_data = (TH1D*)plot.mm_bt_p_hist->Clone(); */
    	/* mm_bt_m_hist_data = (TH1D*)plot.mm_bt_m_hist->Clone(); */
    	/* mm_bl_p_hist_data = (TH1D*)plot.mm_bl_p_hist->Clone(); */
    	/* mm_bl_m_hist_data = (TH1D*)plot.mm_bl_m_hist->Clone(); */
    	/* em_bt_p_hist_data = (TH1D*)plot.em_bt_p_hist->Clone(); */
    	/* em_bt_m_hist_data = (TH1D*)plot.em_bt_m_hist->Clone(); */
    	/* em_bl_p_hist_data = (TH1D*)plot.em_bl_p_hist->Clone(); */
    	/* em_bl_m_hist_data = (TH1D*)plot.em_bl_m_hist->Clone(); */
      }
    else
      {
	if (std::find(legend_list.begin(),legend_list.end(), plot.legend_name) == legend_list.end())
	  {
	    leg->AddEntry(plot.template_hist,plot.legend_name,"f");
	    legend_list.push_back(plot.legend_name);
	  }
	template_stack->Add(plot.template_hist);
	template_stack->SetName(plot.template_hist->GetName());
	ee_stack->Add(plot.ee_hist);
	ee_stack->SetName(plot.ee_hist->GetName());
	em_stack->Add(plot.em_hist);
	em_stack->SetName(plot.em_hist->GetName());
	mm_stack->Add(plot.mm_hist);
	mm_stack->SetName(plot.mm_hist->GetName());
	/* cout << __LINE__ << endl; */
	/* ee_p_stack->Add(plot.ee_p_hist); */
	/* cout << __LINE__ << endl; */
	/* ee_p_stack->SetName(plot.ee_p_hist->GetName()); */
	/* cout << __LINE__ << endl; */
	/* ee_m_stack->Add(plot.ee_m_hist); */
	/* ee_m_stack->SetName(plot.ee_m_hist->GetName()); */
	/* cout << __LINE__ << endl; */
	/* em_bt_p_stack->Add(plot.em_bt_p_hist); */
	/* em_bt_p_stack->SetName(plot.em_bt_p_hist->GetName()); */
	/* em_bt_m_stack->Add(plot.em_bt_m_hist); */
	/* em_bt_m_stack->SetName(plot.em_bt_m_hist->GetName()); */
	/* em_bl_p_stack->Add(plot.em_bl_p_hist); */
	/* em_bl_p_stack->SetName(plot.em_bl_p_hist->GetName()); */
	/* em_bl_m_stack->Add(plot.em_bl_m_hist); */
	/* em_bl_m_stack->SetName(plot.em_bl_m_hist->GetName()); */
	/* cout << __LINE__ << endl; */
	/* mm_bt_p_stack->Add(plot.mm_bt_p_hist); */
	/* mm_bt_p_stack->SetName(plot.mm_bt_p_hist->GetName()); */
	/* mm_bt_m_stack->Add(plot.mm_bt_m_hist); */
	/* mm_bt_m_stack->SetName(plot.mm_bt_m_hist->GetName()); */
	/* mm_bl_p_stack->Add(plot.mm_bl_p_hist); */
	/* mm_bl_p_stack->SetName(plot.mm_bl_p_hist->GetName()); */
	/* mm_bl_m_stack->Add(plot.mm_bl_m_hist);	 */
	/* mm_bl_m_stack->SetName(plot.mm_bl_m_hist->GetName()); */
	/* cout << __LINE__ << endl; */
      }

  }
  
  void draw(void)
  {
    drawSingle(template_stack, template_hist_data);
    drawSingle(ee_stack, ee_hist_data);
    drawSingle(em_stack, em_hist_data);
    drawSingle(mm_stack, mm_hist_data);
    //don't bother drawing all the specific category stacks for now. 
  }
  virtual ~StackObject(){}
};
