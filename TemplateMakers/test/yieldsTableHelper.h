class YieldsTableHelper
{
private:
  std::ofstream out_; 
  double int_tot, int_ee, int_em, int_mm;
  double err_tot=0.;
  double err_ee=0.;
  double err_em=0.;
  double err_mm=0.;
  
  double ee_bkg=0., ee_bkg_err=0.;
  double em_bkg=0., em_bkg_err=0.;
  double mm_bkg=0., mm_bkg_err=0.;

  double ee_ttz_bkg=0., ee_ttz_bkg_err=0.;
  double em_ttz_bkg=0., em_ttz_bkg_err=0.;
  double mm_ttz_bkg=0., mm_ttz_bkg_err=0.;

  double ee_conv_bkg=0., ee_conv_bkg_err=0.;
  double em_conv_bkg=0., em_conv_bkg_err=0.;
  double mm_conv_bkg=0., mm_conv_bkg_err=0.;

  double ee_rare_bkg=0., ee_rare_bkg_err=0.;
  double em_rare_bkg=0., em_rare_bkg_err=0.;
  double mm_rare_bkg=0., mm_rare_bkg_err=0.;
  
  void addBkgs(double &output_ee, double &output_em, double &output_mm,
	       double &output_err_ee, double &output_err_em, double &output_err_mm,
	       double input_ee, double input_em, double input_mm,
	       double input_err_ee, double input_err_em, double input_err_mm)
  {
    output_err_ee += input_err_ee*input_err_ee;
    output_ee += input_ee;
    output_err_em += input_err_em*input_err_em;
    output_em += input_em;
    output_err_mm += input_err_mm*input_err_mm;
    output_mm += input_mm;
  }

public:
  YieldsTableHelper(void){
    out_.open("yields_2lss.txt");
    out_ << setw(26) << "Process" << 
      setw(12) << "mm" <<
      setw(12) << "ee" <<
      setw(12) << "em" << endl;
  }//default constructor
  
  void fill(PlotObject plot)
  {
    
    int_tot = plot.template_hist->IntegralAndError(1,plot.template_hist->GetNbinsX(),err_tot);
    int_ee = plot.ee_hist->IntegralAndError(1,plot.ee_hist->GetNbinsX(),err_ee);
    int_em = plot.em_hist->IntegralAndError(1,plot.em_hist->GetNbinsX(),err_em);
    int_mm = plot.mm_hist->IntegralAndError(1,plot.mm_hist->GetNbinsX(),err_mm);
    
    if (plot.sample_name != "data" && plot.sample_name != "ttH")
      {
	addBkgs(ee_bkg, em_bkg, mm_bkg,
		ee_bkg_err, em_bkg_err, mm_bkg_err,
		int_ee, int_em, int_mm,
		err_ee, err_em, err_mm);
      }
    if (plot.legend_name == "TTZ")
      {
	addBkgs(ee_ttz_bkg, em_ttz_bkg, mm_ttz_bkg,
		ee_ttz_bkg_err, em_ttz_bkg_err, mm_ttz_bkg_err,
		int_ee, int_em, int_mm,
		err_ee, err_em, err_mm);
      }
    else if (plot.legend_name == "Convs")
      {
	addBkgs(ee_conv_bkg, em_conv_bkg, mm_conv_bkg,
		ee_conv_bkg_err, em_conv_bkg_err, mm_conv_bkg_err,
		int_ee, int_em, int_mm,
		err_ee, err_em, err_mm);
      }
    else if (plot.legend_name == "Rares")
      {
	addBkgs(ee_rare_bkg, em_rare_bkg, mm_rare_bkg,
		ee_rare_bkg_err, em_rare_bkg_err, mm_rare_bkg_err,
		int_ee, int_em, int_mm,
		err_ee, err_em, err_mm);
      }

    // cout << "total 2lss: " << int_tot << " +- " << err_tot << endl;
    // cout << "2lss ee: " << int_ee << " +- " << err_ee << endl;
    // cout << "2lss em: " << int_em << " +- " << err_em << endl;
    // cout << "2lss mm: " << int_mm << " +- " << err_mm << endl;
    
    out_ << setiosflags(ios::fixed) << setprecision(1);
    out_ <<
      setw(26) << plot.sample_name <<
      setw(6) << int_mm << setw(2) << "+-" << setw(4) << err_mm <<
      setw(6) << int_ee << setw(2) << "+-" << setw(4) << err_ee <<
      setw(6) << int_em << setw(2) << "+-" << setw(4) << err_em << endl;
    
  }

  void sumBkgs(void)
  {

    out_ << setiosflags(ios::fixed) << setprecision(1);
    out_ <<
      setw(26) << "TTZ " <<
      setw(6) << mm_ttz_bkg << setw(2) << "+-" << setw(4) << sqrt(mm_ttz_bkg_err) <<
      setw(6) << ee_ttz_bkg << setw(2) << "+-" << setw(4) << sqrt(ee_ttz_bkg_err) <<
      setw(6) << em_ttz_bkg << setw(2) << "+-" << setw(4) << sqrt(em_ttz_bkg_err) << endl;

    out_ << setiosflags(ios::fixed) << setprecision(1);
    out_ <<
      setw(26) << "Convs. " <<
      setw(6) << mm_conv_bkg << setw(2) << "+-" << setw(4) << sqrt(mm_conv_bkg_err) <<
      setw(6) << ee_conv_bkg << setw(2) << "+-" << setw(4) << sqrt(ee_conv_bkg_err) <<
      setw(6) << em_conv_bkg << setw(2) << "+-" << setw(4) << sqrt(em_conv_bkg_err) << endl;

    out_ << setiosflags(ios::fixed) << setprecision(1);
    out_ <<
      setw(26) << "Rare SM bkg. " <<
      setw(6) << mm_rare_bkg << setw(2) << "+-" << setw(4) << sqrt(mm_rare_bkg_err) <<
      setw(6) << ee_rare_bkg << setw(2) << "+-" << setw(4) << sqrt(ee_rare_bkg_err) <<
      setw(6) << em_rare_bkg << setw(2) << "+-" << setw(4) << sqrt(em_rare_bkg_err) << endl;

    out_ << setiosflags(ios::fixed) << setprecision(1);
    out_ <<
      setw(26) << "All backgrounds" <<
      setw(6) << mm_bkg << setw(2) << "+-" << setw(4) << sqrt(mm_bkg_err) <<
      setw(6) << ee_bkg << setw(2) << "+-" << setw(4) << sqrt(ee_bkg_err) <<
      setw(6) << em_bkg << setw(2) << "+-" << setw(4) << sqrt(em_bkg_err) << endl;
  }

  virtual ~YieldsTableHelper(){}
};

