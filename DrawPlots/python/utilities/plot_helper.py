#!/usr/bin/env python
import os, sys
import ROOT

class Plot:
    def __init__(self, output_file, tree, distribution, plot_name, parameters, draw_string):
        (plot_type, title, num_bins, x_min, x_max) = parameters
        self.plot_name = plot_name

        if plot_type == 'TH1F':
            self.plot = ROOT.TH1F(plot_name, title, num_bins, x_min, x_max)
            tree.Project(self.plot_name, distribution, draw_string)
        else:
            print 'ERROR [plot_helper.py]: Method Plot::__init__ currently only supports TH1F histograms.  Please add support for other types if you wish to use them.'
            sys.exit(2)
        #tree.Draw(distribution + '>>' + self.plot_name, draw_string, 'goff')
        self.plot.SetDirectory(output_file)
        output_file.Write('', ROOT.TObject.kOverwrite)

    def save_pdf(self):
        if not os.path.exists('plot_pdfs'):
            os.makedirs('plot_pdfs')
        self.set_style()
        ROOT.gROOT.SetBatch(ROOT.kTRUE)
        canvas = ROOT.TCanvas('canvas', 'canvas', 700, 800)
        self.plot.Draw()
        canvas.Print('plot_pdfs/%s.pdf' % self.plot_name)

    def set_style(self): #later we can add arguments for different style sets if needed
        ROOT.gStyle.SetOptStat(0)
        ROOT.gStyle.SetPadBorderMode(0)
        ROOT.gStyle.SetFrameBorderMode(0)
        ROOT.gStyle.SetLineWidth(2)
        ROOT.gStyle.SetLabelOffset(0.01)
        ROOT.gStyle.SetLabelSize(0.035)
        ROOT.gStyle.SetHistLineWidth(2)
        #self.plot.GetYaxis().SetNoExponent(ROOT.kTRUE)


class DrawStringMaker:
    def __init__(self):
        self.requirements_string = ''
        self.factors_string = ''
        self.draw_string = ''

    def update_draw_string(self):
        self.draw_string = '(' + self.requirements_string + ')' + self.factors_string

    def append_selection_requirement(self, cut_string):
        if (self.requirements_string == ''):
            self.requirements_string += cut_string
        else:
            self.requirements_string += ' && ' + cut_string

        self.update_draw_string()        

    def append_selection_requirements(self, cut_strings): 
        for cut_string in cut_strings:
            self.append_selection_requirement(cut_string)

    def append_jet_tag_category_requirements(self, jet_tag_category):
        if jet_tag_category == 'ge2t':
            jet_tag_string = ' numJets >= 2 && numTaggedJets >= 2'
        elif jet_tag_category == 'eq2jeq2t':
            jet_tag_string = ' numJets == 2 && numTaggedJets == 2'
        elif jet_tag_category == 'eq3jeq2t':
            jet_tag_string = ' numJets == 3 && numTaggedJets == 2'
        elif jet_tag_category == 'ge4jeq2t':
            jet_tag_string = ' numJets >= 4'
        else:
            print 'ERROR [plot_helper.py]: Unrecognized jet tag category. Please update DrawStringMaker::append_jet_tag_category_requirements'
            sys.exit(2)

        self.append_selection_requirement(jet_tag_string)

    def append_lepton_category_requirements(self, lepton_category):
        if lepton_category == 'mu_mu':
            lepton_category_string = '(isDoubleMuTriggerPass == 1)'
        elif lepton_category == 'ele_ele':
            lepton_category_string = '(isDoubleElectronTriggerPass == 1)'
        elif lepton_category == 'mu_ele':
            lepton_category_string = '(isMuEGTriggerPass == 1)'
        else:
            print 'ERROR [plot_helper.py]: Unrecognized lepton category.  Please update DrawStringMaker::append_lepton_category_requirements'
            sys.exit(2)
            
        self.append_selection_requirement(lepton_category_string)
            
    def multiply_by_factor(self, weight):
        weight = str(weight)
        self.factors_string += ' * ' + weight
        self.update_draw_string()

    def multiply_by_factors(self, weights):
        for weight in weights:
            self.multiply_by_factor(weight)

class SampleInformation:
    def __init__(self, sample):
        dictionary = {
            'WW': {'is_data' : False,
                   'x_section': 0.0548, #0.0571,
                   'x_section_error': 0.0015,
                   'num_generated': 9955089,
                   'systematics': 'all+TopPtDown'},

            'WZ': {'is_data' : False,
                   'x_section': 0.0323,
                   'x_section_error': 0.0007,
                   'num_generated':  9931257,
                   'systematics': 'all'},

            'ttH125': {'is_data': False,
                       'x_section': 0.0001302,
                       'x_section_error': 0.0,
                       'num_generated': 992997,
                       'systematics': 'all'}                       
            }

        self.sample = sample
        self.is_data = dictionary[sample]['is_data']
        self.x_section = dictionary[sample]['x_section']
        self.x_section_error = dictionary[sample]['x_section_error']
        self.num_generated = dictionary[sample]['num_generated']
        self.systematics = dictionary[sample]['systematics']

"""
This clunky class is an attempt to provide a way to add sample-specific treatment of systematics
"""
class SystematicsInformation:
    def __init__(self, baseline_systematics=[]):
        self.systematics_list = ['nominal'] 
        self.dictionary = {
            'nominal': {'weight_string': '1', 'source_file_label': ''},
            'JESUp': {'weight_string': '1', 'source_file_label': 'JESUp'},
            'PUUp': {'weight_string':'(weight_PUup/weight)', 'source_file_label': ''},
            'CSV_HFUp': {'weight_string': 'CSV_HFUp', 'source_file_label': ''},
            'TopPtDown': {'weight_string': '(1/TopPT_wgt)', 'source_file_label': ''}
            }

        self.add_systematics(baseline_systematics)

    def add_systematics(self, systematics_list):
        self.systematics_list.extend(systematics_list)
        
    def edit_systematics_list(self, sample_systematics_string):
        systematics_set = set(self.systematics_list) #copy into a set for convenient duplicate removal

        import re
        systematics_to_add = []
        first_item = sample_systematics_string.strip() #If there is no '+' or '-', there must only be one term
        first_item_match = re.search('.*?(?=(\+|\-))', sample_systematics_string) #Sorry for the nasty regular expressions.  This gets the first term in sample_systematics_string if it's followed by a '+' or '-'
        if first_item_match: 
            first_item = first_item_match.group(0).strip()
        if first_item != 'all' and first_item != '':
            systematics_to_add.append(first_item)
        systematics_to_add.extend([match.strip() for match in re.findall('\+(.\w*)', sample_systematics_string)]) #This gets a list of all terms that come after a '+' in sample_systematics_string
        systematics_set = systematics_set.union(set(systematics_to_add))

        systematics_to_remove = [match.strip() for match in re.findall('\-(.\w*)', sample_systematics_string)]
        systematics_set = systematics_set.difference(set(systematics_to_remove))

        self.systematics_list = list(systematics_set)

# 		{'name': 'ZZ',
# 		 'xsec': 0.0077,#0.00826,
# 		 'xsec_err': 0.00015,
# 		 'ngen':  9755621,
# 		 'skipSystematics':skipSystematics,
# 		 }
# 		{'name': 'WWW',
# 		 'xsec': 0.00008217,#0.0571,
# 		 'xsec_err': 0.00008217*0.0015/0.0548,
# 		 'ngen': 220040,
# 		 'skipSystematics':skipSystematics,
# 		 }
# 		{'name': 'WWZ',
# 		 'xsec': 0.0000633,#0.0571,
# 		 'xsec_err': 0.0000633*0.0015/0.0548,
# 		 'ngen': 221576,
# 		 'skipSystematics':skipSystematics,
# 		 }
# 		{'name': 'WZZ',
# # 		 'xsec': 0.00001922,#0.0571,
# 		 'xsec': 0.0000001,
# 		 'xsec_err': 0.00001922*0.0015/0.0548,
# 		 'sys_array': sys_arrays['diboson'],
# 		 'ngen': 219835,
# 		{'name': 'ZZZ',
# 		 'xsec': 0.000004587,#0.0571,
# 		 'xsec_err': 0.000004587*0.0015/0.0548,
# 		 'ngen': 224519,

# 		{'name': 'WJets',
# 		 'xsec': 36.257,
# 		 'xsec_err': 1.558,
# 		 'ngen':  57536319,

# 		{'name': 'ZJets',
# 		 'xsec': 3.5057,
# 		 'xsec_err': 0.132,
# 		 'ngen':	30072710,

# 		{'name': 'ZJets_M10-50',
# 		 'xsec': 14.7, #0.860,
# 		 'xsec_err': 0.132*0.86/3.5057,
# 		 'ngen': 37828841,

# 		{'name': 'ttW',
# 		 'xsec': 0.000249, #0.000163*1.5,
# 		 'xsec_err': 0.2*0.000249,
# 		 'ngen':  195396,

# 		{'name': 'ttZ',
# 		 'xsec': 0.000208,#0.000136*1.5,
# 		 'xsec_err': 0.2*0.000208,
# 		 'ngen':  209512,

# 		{'name': 'ttWW',
# 		 'xsec': 0.000002037,#0.000136*1.5,
# 		 'xsec_err': 0.2*0.000002037,
# 		 'ngen':  216867,

# 		{'name': 'tttt',
# 		 'xsec': 0.0000000001,#0.000000716,
# 		 'xsec_err': 0.2*0.000000716,
# 		 'ngen':  99994,

# 		{'name': 't_s',
# 		 'xsec': 0.00379,
# 		 'xsec_err': 0.00006*0.00379/(0.00379+0.00176),
# 		 'ngen': 259657,

# 		{'name': 'tbar_s',
# 		 'xsec': 0.00176,
# 		 'xsec_err': 0.00006*0.00176/(0.00379+0.00176),
# 		 'ngen': 139835,

# 		{'name': 't_t',
# 		 'xsec': 0.0564,
# 		 'xsec_err': 0.0032*0.0564/(0.0564+0.0307),
# 		 'ngen': 3744404,

# 		{'name': 'tbar_t',
# 		 'xsec': 0.0307,
# 		 'xsec_err': 0.0032*0.0307/(0.0564+0.0307),
# 		 'ngen': 1933504,

# 		{'name': 't_tW',
# 		 'xsec': 0.0111,
# 		 'xsec_err': 0.0008*0.0111/0.00106,	  #### 0.00106
# 		 'ngen': 496918,

# 		{'name': 'tbar_tW',
# 		 'xsec': 0.0111,
# 		 'xsec_err': 0.0008*0.0111/0.00106,	 #### 0.00106
# 		 'ngen': 492779,

# 		{'name': 'ttbb',
# 		 'xsec': 0.2458, #0.225197,
# 		 'xsec_err': 0.5*0.2458, #0.225197, #0.3*0.225197,
# 		 'ngen':  6912438+1362471,

# 		{'name': 'ttcc',
# 		 'xsec': 0.2458, #0.225197,
# 		 'xsec_err': 0.3*0.2458, #0.225197,
# 		 'ngen':  6912438+1362471, 

# 		{'name': 'tt',
# 		 'xsec': 0.2458, #0.225197,
# 		 'xsec_err': 0.024,
# 		 'ngen':  6912438+1362471, 

# 		{'name': 'ttH_110',
# 		 'xsec': 0.0001887,
# 		 'xsec_err': 0.0,
# 		 'ngen': 975341, 

# 		{'name': 'ttH_115',
# 		 'xsec': 0.0001663,
# 		 'xsec_err': 0.0,
# 		 'ngen': 995188, 

# 		{'name': 'ttH_120',
# 		 'xsec': 0.000147,
# 		 'xsec_err': 0.0,
# 		 'ngen': 996773,

# 		{'name': 'ttH_130',
# 		 'xsec': 0.0001157,
# 		 'xsec_err': 0.0,
# 		 'ngen': 931369,

# 		{'name': 'ttH_135',
# 		 'xsec': 0.0001031,
# 		 'xsec_err': 0.0,
# 		 'ngen': 993975,

# 		{'name': 'ttH_140',
# 		 'xsec': 0.00009207,
# 		 'xsec_err': 0.0,
# 		 'ngen': 997191,

# 		{'name': 'data_2012_53x',
# 		 'xsec': 1,
# 		 'xsec_err': 0.0,
# 		 'sys_array': [0,0,0,0],
# 		 'ngen': 1,

