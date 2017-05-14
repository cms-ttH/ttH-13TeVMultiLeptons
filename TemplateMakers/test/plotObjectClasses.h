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

  TH1D* template_hist;
  TH1D* ee_hist;
  TH1D* mm_hist;
  TH1D* em_hist;

  void fill(Sample sample, TFile* fout=0)
  {
   
    TString template_name = hist_name+"_"+sample.legend_name;
    template_hist = new TH1D(template_name,hist_title,bins,xmin,xmax);
    template_hist->SetFillColor(sample.fill_color);
    template_hist->SetFillStyle(sample.fill_style);
    template_hist->SetLineColor(1);
    template_hist->SetMarkerColor(sample.fill_color);

    TString ee_name = template_name+"_ee";
    TString em_name = template_name+"_em";
    TString mm_name = template_name+"_mm";

    ee_hist = (TH1D*)template_hist->Clone(ee_name);    
    em_hist = (TH1D*)template_hist->Clone(em_name);    
    mm_hist = (TH1D*)template_hist->Clone(mm_name);    
    
    TString drawCommand_template = drawCommand + " >> "+template_name;
    TString drawCommand_ee = drawCommand + " >> "+ee_name;
    TString drawCommand_em = drawCommand + " >> "+em_name;
    TString drawCommand_mm = drawCommand + " >> "+mm_name;

    TCut weight = "";
    if (sample.legend_name != "data" && sample.legend_name != "fakes" && sample.legend_name != "flips" )
      {
	weight = "(mcwgt/mcwgt)*btag_weight*trigger_SF*lepton_SF";
      }
    else if (sample.legend_name == "fakes" || sample.legend_name == "flips")
      {
	weight = "mcwgt";
      }
    TCut weight_ee = "(flavor_category==\"ee\")"*weight;
    TCut weight_em = "(flavor_category==\"em\")"*weight;
    TCut weight_mm = "(flavor_category==\"mm\")"*weight;
    
    auto tree = sample.tree;
    template_hist->SetDirectory(gDirectory);
    ee_hist->SetDirectory(gDirectory);
    em_hist->SetDirectory(gDirectory);
    mm_hist->SetDirectory(gDirectory);

    tree->Draw(drawCommand_template,weight,"goff");
    tree->Draw(drawCommand_ee,weight_ee,"goff");
    tree->Draw(drawCommand_em,weight_em,"goff");
    tree->Draw(drawCommand_mm,weight_mm,"goff");
    
    template_hist->Scale( sample.xsec );
    ee_hist->Scale( sample.xsec );
    em_hist->Scale( sample.xsec );
    mm_hist->Scale( sample.xsec );
    
    if (fout)
      {
	fout->cd();
	template_hist->Write();
	ee_hist->Write();
	em_hist->Write();
	mm_hist->Write();
      }

  }
  
  virtual ~PlotObject(){}
};

class StackObject
{
private:
  TString stack_name;
  TString stack_title;
  
  void drawSingle(THStack* stack)
  {
    TString stack_name = stack->GetName();
    TString can_name = stack_name + "_can";
    TString save_name = stack_name + ".root";
    TCanvas* can = new TCanvas(can_name, can_name,10,32,530,580);
    
    stack->Draw("hist");
    //stack->SetMaximum(179);//125
    stack->GetXaxis()->SetTitle("test_stack");
    stack->Draw("hist");
    //gPad->BuildLegend(0.4410646,0.7296544,0.8536122,0.8690078);
    //gPad->SetTicky();
    can->SaveAs(save_name);
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
  
  void Add(PlotObject plot, Sample sample)
  {
    template_stack->Add(plot.template_hist);
    ee_stack->Add(plot.ee_hist);
    em_stack->Add(plot.em_hist);
    mm_stack->Add(plot.mm_hist);
  }

  void draw(void)
  {
    drawSingle(template_stack);
    drawSingle(ee_stack);
    drawSingle(em_stack);
    drawSingle(mm_stack);
  }
  virtual ~StackObject(){}
};
