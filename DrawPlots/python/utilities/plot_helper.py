#!/usr/bin/env python
import os, sys
import ROOT
import string
from distutils import file_util

def get_www_base_directory():
    try:
        www_base_directory = os.environ['HOME']+'/www'
        return www_base_directory
    except:
        print 'Problem accessing your CRC www directory.  Try emailing crcsupport@nd.edu and asking them to create one for you.'
        sys.exit()

def copy_to_www_area(local_plot_directory, www_plot_directory, plot_name):
    file_util.copy_file('%s/%s.png' % (local_plot_directory, plot_name), www_plot_directory)
    file_util.copy_file('%s/%s.pdf' % (local_plot_directory, plot_name), www_plot_directory)

def make_sure_directories_exist(directories):
    for directory in directories:
        if not os.path.exists(directory):
            os.makedirs(directory)

def setup_www_directory(directory, depth=1, *extra_files_to_post):
    directory_parts = directory.split('/')
    for level in range(depth):
        parts_in_current_level = len(directory_parts) - level
        directory_to_setup = string.join(directory_parts[:parts_in_current_level], '/')
        make_sure_directories_exist([directory_to_setup])

        if not os.path.exists(directory_to_setup+'/index.php'):
            file_util.copy_file(os.environ['CMSSW_BASE']+'/src/ttHMultileptonAnalysis/DrawPlots/python/utilities/index.php', directory_to_setup)

    for file in extra_files_to_post:
        file_util.copy_file('%s' % file, directory)

def setup_www_directories(directories, depth=1, *extra_files_to_post):
    for directory in directories:
        setup_www_directory(directory, depth, *extra_files_to_post)

def setup_web_posting(directories, depth=4, *extra_files_to_post):
    www_base_directory = get_www_base_directory()

    www_plot_directories = ['%s/%s' % (www_base_directory, directory) for directory in directories]
    setup_www_directories(www_plot_directories, depth, *extra_files_to_post)

def get_data_sample_name(lepton_category):
    if lepton_category == 'mu_ele':
        return 'MuEG'
    elif lepton_category == 'mu_mu':
        return 'DoubleMu'
    elif lepton_category == 'ele_ele':
        return 'DoubleElectron'

class Plot:
    def __init__(self, sample, output_file, tree, plot_name, parameters, draw_string):
        self.plot_name = plot_name
        (num_bins, x_min, x_max) = parameters['binning']

        if parameters['plot type'] == 'TH1F':
            title = '%s;%s;%s' % (sample, parameters['axis labels'][0], parameters['axis labels'][1])
            self.plot = ROOT.TH1F(plot_name, title, num_bins, x_min, x_max)
            tree.Project(self.plot_name, parameters['expression'], draw_string)
        else:
            print 'ERROR [plot_helper.py]: Method Plot::__init__ currently only supports TH1F histograms.  Please add support for other types if you wish to use them.'
            sys.exit(2)
        self.plot.SetDirectory(output_file)
        output_file.Write('', ROOT.TObject.kOverwrite)

    def save_image(self, *image_types): #I am choosing for now not to add the option in make_plots to save pngs (though it can be called here), since pdfs look nicer
        if not os.path.exists('plot_pdfs'):
            os.makedirs('plot_pdfs')
        self.set_style()
        ROOT.gROOT.SetBatch(ROOT.kTRUE)
        canvas = ROOT.TCanvas('canvas', 'canvas', 700, 800)
        self.plot.Draw()
        for type in image_types:
            canvas.Print('plot_pdfs/%s.%s' % (self.plot_name, type))

    def post_to_web(self, config, lepton_category):
        www_base_directory = get_www_base_directory()

        self.save_image('png', 'pdf')

        www_plot_directory = '%s/plots/%s/%s' % (www_base_directory, config['label'], lepton_category)
        copy_to_www_area('plot_pdfs', www_plot_directory, self.plot_name)

    def set_style(self): #later we can add arguments for different style sets if needed
        #ROOT.gStyle.SetOptStat(0)
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

    def append_selection_requirements(self, *cut_string_lists):
        for cut_string_list in cut_string_lists:
            for cut_string in cut_string_list:
                self.append_selection_requirement(cut_string)

    def append_jet_tag_category_requirements(self, jet_tag_category):
        if jet_tag_category == 'ge2t':
            jet_tag_string = ' numJets >= 2 && numMediumBJets >= 2'
        elif jet_tag_category == 'eq2jeq2t':
            jet_tag_string = ' numJets == 2 && numMediumBJets == 2'
        elif jet_tag_category == 'eq3jeq2t':
            jet_tag_string = ' numJets == 3 && numMediumBJets == 2'
        elif jet_tag_category == 'ge4jeq2t':
            jet_tag_string = ' numJets >= 4 && numMediumBJets == 2'
        elif jet_tag_category == 'ge3t':
            jet_tag_string = ' numJets >= 3 && numMediumBJets >= 3'
        elif jet_tag_category == 'eq3jeq3t':
            jet_tag_string = ' numJets == 3 && numMediumBJets ==3'
        elif jet_tag_category == 'ge4jeq3t':
            jet_tag_string = ' numJets >= 4 && numMediumBJets == 3'
        elif jet_tag_category == 'ge4jge3t':
            jet_tag_string = ' numJets >= 4 && numMediumBJets >= 3'
        elif jet_tag_category == 'ge4t':
            jet_tag_string = ' numJets >= 4 && numMediumBJets >= 4'
        elif jet_tag_category == 'eq0j':
            jet_tag_string = ' numJets == 0 && numMediumBJets == 0'
        elif jet_tag_category == 'eq1jeq0t':
            jet_tag_string = ' numJets == 1 && numMediumBJets == 0'
        elif jet_tag_category == 'eq1jeq1t':
            jet_tag_string = ' numJets == 1 && numMediumBJets == 1'
        elif jet_tag_category == 'eq2jge0t':
            jet_tag_string = ' numJets == 2 && numMediumBJets >= 0'
        elif jet_tag_category == 'eq2jeq0t':
            jet_tag_string = ' numJets == 2 && numMediumBJets == 0'
        elif jet_tag_category == 'eq2jge1t':
            jet_tag_string = ' numJets == 2 && numMediumBJets >= 1'
        elif jet_tag_category == 'eq2jeq1t':
            jet_tag_string = ' numJets == 2 && numMediumBJets == 1'
        elif jet_tag_category == 'eq3jeq0t':
            jet_tag_string = ' numJets == 3 && numMediumBJets == 0'
        elif jet_tag_category == 'eq3jge1t':
            jet_tag_string = ' numJets == 3 && numMediumBJets >= 1'
        elif jet_tag_category == 'eq3jeq1t':
            jet_tag_string = ' numJets == 3 && numMediumBJets == 1'
        elif jet_tag_category == 'eq3jge2t':
            jet_tag_string = 'numJets == 3 && numMediumBJets >= 2'
        elif jet_tag_category == 'ge4jeq1t':
            jet_tag_string = 'numJets >= 4 && numMediumBJets == 1'
        elif jet_tag_category == 'ge4jge2t':
            jet_tag_string = 'numJets >= 4 && numMediumBJets >= 2'
        elif jet_tag_category == 'ge4j':
            jet_tag_string = 'numJets>=4'
        elif jet_tag_category == 'inclusive':
            pass
        else:
            print 'ERROR [plot_helper.py]: Unrecognized jet tag category. Please update DrawStringMaker::append_jet_tag_category_requirements'
            sys.exit(2)

        if jet_tag_category != 'inclusive':
            self.append_selection_requirement(jet_tag_string)

    def multiply_by_factor(self, weight):
        weight = str(weight)
        self.factors_string += ' * ' + weight
        self.update_draw_string()

    def multiply_by_factors(self, weights):
        for weight in weights:
            self.multiply_by_factor(weight)

    def get_matched_SF(self, lepton_category):
        if lepton_category == 'mu_mu':
            matched_SF = 'twoMuonTriggerSF'
        elif lepton_category == 'ele_ele':
            matched_SF = 'twoElectronTriggerSF'
        elif lepton_category == 'mu_ele':
            matched_SF = 'muonElectronTriggerSF'

        return matched_SF

class SampleInformation:
    def __init__(self, sample):
        dictionary = {
            'ww': {'is_data': False,
                   'is_signal': False,
                   'x_section': 54.8, #0.0571,
                   'x_section_error': 0.0015,
                   'num_generated': 9955089,
                   'systematics': 'all'},

            'wz': {'is_data' : False,
                   'is_signal': False,
                   'x_section': 32.3,
                   'x_section_error': 0.0007,
                   'num_generated':  9931257,
                   'systematics': 'all'},

            'zz': {'is_data': False,
                   'is_signal': False,
                   'x_section': 7.7,#0.00826,
                   'x_section_error': 0.00015,
                   'num_generated':  9755621,
                   'systematics': 'all'},

            'www': {'is_data': False,
                    'is_signal': False,
                    'x_section': 0.08217,#0.0571,
                    'x_section_error': 0.00008217*0.0015/0.0548,
                    'num_generated': 220040,
                    'systematics': 'all'},

            'wwz': {'is_data': False,
                    'is_signal': False,
                    'x_section': 0.0633,#0.0571,
                    'x_section_error': 0.0000633*0.0015/0.0548,
                    'num_generated': 221576,
                    'systematics': 'all'},

            'wzz': {'is_data': False,
                    'is_signal': False,
                    # 		 'x_section': 0.00001922,#0.0571,
                    'x_section': 0.0001,
                    'x_section_error': 0.00001922*0.0015/0.0548,
                    'num_generated': 219835,
                    'systematics': 'all'},

            'zzz': {'is_data': False,
                    'is_signal': False,
                    'x_section': 0.004587,#0.0571,
                    'x_section_error': 0.000004587*0.0015/0.0548,
                    'num_generated': 224519,
                    'systematics': 'all'},

            'wjets': {'is_data': False,
                      'is_signal': False,
                      'x_section': 36257,
                      'x_section_error': 1.558,
                      'num_generated':  57536319,
                      'systematics': 'all'},

            'zjets': {'is_data': False,
                      'is_signal': False,
                      'x_section': 3505.7,
                      'x_section_error': 0.132,
                      'num_generated':	30072710,
                      'systematics': 'all'},

            'zjets_lowmass': {'is_data': False,
                              'is_signal': False,
                              'x_section': 14702, #0.860,
                              'x_section_error': 0.132*0.86/3.5057,
                              'num_generated': 37828841,
                              'systematics': 'all'},

            'ttbarW': {'is_data': False,
                       'is_signal': False,
                       'x_section': 0.232, #0.000163*1.5,
                       'x_section_error': 0.2*0.000249,
                       'num_generated':  195196,
                       'systematics': 'all'},

            'ttbarZ': {'is_data': False,
                       'is_signal': False,
                       'x_section': 0.208,#0.000136*1.5,
                       'x_section_error': 0.2*0.000208,
                       'num_generated':  209512,
                       'systematics': 'all'},

            'ttbarWW': {'is_data': False,
                        'is_signal': False,
                        'x_section': 0.002037,#0.000136*1.5,
                        'x_section_error': 0.2*0.000002037,
                        'num_generated':  216867,
                        'systematics': 'all'},

            'tttt': {'is_data': False,
                     'is_signal': False,
                     'x_section': 0.0000001,#0.000000716,
                     'x_section_error': 0.2*0.000000716,
                     'num_generated':  99994,
                     'systematics': 'all'},

            't_s': {'is_data': False,
                    'is_signal': False,
                    'x_section': 3.79,
                    'x_section_error': 0.00006*0.00379/(0.00379+0.00176),
                    'num_generated': 259657,
                    'systematics': 'all'},

            'tbar_s': {'is_data': False,
                       'is_signal': False,
                       'x_section': 1.76,
                       'x_section_error': 0.00006*0.00176/(0.00379+0.00176),
                       'num_generated': 139835,
                       'systematics': 'all'},

            't_t': {'is_data': False,
                    'is_signal': False,
                    'x_section': 56.4,
                    'x_section_error': 0.0032*0.0564/(0.0564+0.0307),
                    'num_generated': 3744404,
                    'systematics': 'all'},

            'tbar_t': {'is_data': False,
                       'is_signal': False,
                       'x_section': 30.7,
                       'x_section_error': 0.0032*0.0307/(0.0564+0.0307),
                       'num_generated': 1933504,
                       'systematics': 'all'},

            't_tW': {'is_data': False,
                     'is_signal': False,
                     'x_section': 11.1,
                     'x_section_error': 0.0008*0.0111/0.00106,	  #### 0.00106
                     'num_generated': 496918,
                     'systematics': 'all'},                    

            'tbar_tW': {'is_data': False,
                        'is_signal': False,
                        'x_section': 11.1,
                        'x_section_error': 0.0008*0.0111/0.00106,	 #### 0.00106
                        'num_generated': 492779,
                        'systematics': 'all'},                    

            'ttbb': {'is_data': False,
                     'is_signal': False,
                     'x_section': 245.8, #0.225197,
                     'x_section_error': 0.5*0.2458, #0.225197, #0.3*0.225197,
                     'num_generated':  6912438+1362471,
                     'systematics': 'all'},                    

            'ttcc': {'is_data': False,
                     'is_signal': False,
                     'x_section': 245.8, #0.225197,
                     'x_section_error': 0.3*0.2458, #0.225197,
                     'num_generated':  6912438+1362471,
                     'systematics': 'all'},                    

            'ttbar': {'is_data': False,
                      'is_signal': False,
                      'x_section': 245.8, #0.225197,
                      'x_section_error': 0.024,
                      'num_generated':  6912438+1362471,
                      'systematics': 'all'},                    

            'ttH110': {'is_data': False,
                       'is_signal': True,
                       'x_section': 0.1887,
                       'x_section_error': 0.0,
                       'num_generated': 975341,
                       'systematics': 'all'},                    

            'ttH115': {'is_data': False,
                       'is_signal': True,
                       'x_section': 0.1663,
                       'x_section_error': 0.0,
                       'num_generated': 995188,
                       'systematics': 'all'},                    

            'ttH120': {'is_data': False,
                       'is_signal': True,
                       'x_section': 0.147,
                       'x_section_error': 0.0,
                       'num_generated': 996773,
                       'systematics': 'all'},

            'ttH125': {'is_data': False,
                       'is_signal': True,
                       'x_section': 0.1302,
                       'x_section_error': 0.0,
                       'num_generated': 992997,
                       'systematics': 'all'},

            'ttH130': {'is_data': False,
                       'is_signal': True,
                       'x_section': 0.1157,
                       'x_section_error': 0.0,
                       'num_generated': 931369,
                       'systematics': 'all'},

            'ttH135': {'is_data': False,
                       'is_signal': True,
                       'x_section': 0.1031,
                       'x_section_error': 0.0,
                       'num_generated': 993975,
                       'systematics': 'all'},

            'ttH140': {'is_data': False,
                       'is_signal': True,
                       'x_section': 0.09207,
                       'x_section_error': 0.0,
                       'num_generated': 997191,
                       'systematics': 'all'},

            'MuEG': {'is_data': True,
                     'is_signal': False,
                     'x_section': 1,
                     'x_section_error': 0.0,
                     'num_generated': 1,
                     'systematics': 'none'},

            'DoubleMu': {'is_data': True,
                         'is_signal': False,
                         'x_section': 1,
                         'x_section_error': 0.0,
                         'num_generated': 1,
                         'systematics': 'none'},

            'DoubleElectron': {'is_data': True,
                               'is_signal': False,
                               'x_section': 1,
                               'x_section_error': 0.0,
                               'num_generated': 1,
                               'systematics': 'none'}

            }

        self.sample = sample
        self.is_data = dictionary[sample]['is_data']
        self.is_signal = dictionary[sample]['is_signal']
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
            'nominal': {'weight_string': '1', 'systematic_label': ''},
            'JESUp': {'weight_string': '1', 'systematic_label': '_JESUp'},
            'weight_PUup': {'weight_string':'(weight_PUup/weight_PU)', 'systematic_label': '_weight_PUup'},
            'weight_PUdown': {'weight_string':'(weight_PUdown/weight_PU)', 'systematic_label': '_weight_PUdown'},            
            'CSV_HFUp': {'weight_string': 'CSV_HFUp', 'systematic_label': '_CSV_HFUp'},
            'topPtWgtDown': {'weight_string': '(1/topPtWgt)', 'systematic_label': '_topPtWgtDown'},
            'topPtWgtUp': {'weight_string': '(topPtWgtUp/topPtWgt)', 'systematic_label': '_topPtWgtUp'}            
            }

        self.add_systematics(baseline_systematics)

    def add_systematics(self, systematics_list):
        self.systematics_list.extend(systematics_list)
        
    def edit_systematics_list(self, sample_systematics_string):
        if sample_systematics_string == 'none' or sample_systematics_string == 'None':
            self.systematics_list = ['nominal']
        else:
            systematics_set = set(self.systematics_list) #copy into a set for duplicate removal

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
