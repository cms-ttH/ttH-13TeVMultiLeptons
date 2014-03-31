#!/usr/bin/env python
import os, sys
import ROOT
import string
from distutils import file_util
import shutil
import glob
import time
import itertools
import numpy
from ttHMultileptonAnalysis.DrawPlots.utilities.ordereddict import DefaultOrderedDict

def append_integral_histo(config):
    if not config['distributions'].has_key('integral_histo'):
        config['distributions']['integral_histo'] = {'axis labels': ['isCleanEvent', 'Events'],
                                                     'expression': 'isCleanEvent',
                                                     'plot type': 'TH1F',
                                                     'binning': [2, 0, 2]}

    return config

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

def make_fresh_directory(directory):
    if os.path.exists(directory):
        try:
            shutil.rmtree(directory)
        except:
            pass
    os.makedirs(directory)

def update_indexes(directory):
    www_base_directory = get_www_base_directory()
    directory = os.path.join(www_base_directory, directory)
    for root, dirs, files in os.walk(directory):
        current_dirs = dirs + ['..']
        current_dirs.sort()
        dir_names = ['<b>%s/</b>' % i for i in current_dirs]
        non_image_items = [file for file in files if 'pdf' not in file and 'png' not in file]
        non_image_items.sort()
        non_image_item_paths = [os.path.join(root, i) for i in non_image_items]
        non_image_item_names = dir_names + non_image_items
        non_image_item_locations = current_dirs + non_image_items
        non_image_mod_times = ['' for i in current_dirs] + [time.ctime(os.path.getmtime(i)) for i in non_image_item_paths]
        png_images = [f for f in files if 'png' in f]
        pdf_images = [f.replace('.png', '.pdf') for f in png_images]
#         png_images.sort()
#         pdf_images.sort()
        snippet = '<tr><td><a href={location}>{name}</a></td><td>{mod_time}</td></tr>'
        files_snippet = '\n'.join([snippet.format(location=location, name=name, mod_time=mod_time) for (location, name, mod_time) in zip(non_image_item_locations, non_image_item_names, non_image_mod_times)])
        snippet = '<div class="pic photo-link smoothbox" id="{png}"><a href="{pdf}" rel="gallery"><img src="{png}" class="pic"/></a></div>'
        image_snippet = '\n'.join([snippet.format(pdf=pdf, png=png) for (pdf, png) in zip(pdf_images, png_images)])
        with open(os.path.join(os.environ['CMSSW_BASE'], 'src/ttHMultileptonAnalysis/DrawPlots/python/utilities/index.html'), 'r') as f:
            index = f.read()
        with open(os.path.join(root, 'index.html'), 'w') as f:
            segment = index[index.find("<body>"):] #Have to do this because all of the javascript looks like python formatting statements
            modified_segment = segment.format(files=files_snippet, images=image_snippet)
            index = index.replace(segment, modified_segment)
            f.write(index)

def setup_www_directory(directory, depth=1, *extra_files_to_post):
    make_fresh_directory(directory)
    head = directory
    for level in range(depth):
        if not os.path.exists(os.path.join(head, '/index.html')):
            file_util.copy_file(os.path.join(os.environ['CMSSW_BASE'], 'src/ttHMultileptonAnalysis/DrawPlots/python/utilities/index.html'), head)
        head, tail = os.path.split(head)

    for file in extra_files_to_post:
        file_util.copy_file(file, directory)

def setup_www_directories(directories, depth=1, *extra_files_to_post):
    for directory in directories:
        setup_www_directory(directory, depth, *extra_files_to_post)

def setup_web_posting(directories, depth=1, *extra_files_to_post):
    www_base_directory = get_www_base_directory()

    www_plot_directories = [os.path.join(www_base_directory, directory) for directory in directories]
    setup_www_directories(www_plot_directories, depth, *extra_files_to_post)

def is_matching_data_sample(lepton_category_data_samples, sample):
    for data_sample in lepton_category_data_samples:
        if data_sample in sample:
            return True
        elif 'inclusive_data' in data_sample and 'inclusive_data' in sample:
            return True
        elif 'DoubleMu' in data_sample and 'DoubleMu' in sample:
            return True
        elif 'DoubleElectron' in data_sample and 'DoubleElectron' in sample:
            return True
        elif 'MuEG' in data_sample and 'MuEG' in sample:
            return True
    return False

class Plot:
    def __init__(self, sample, output_file, tree, plot_name, parameters, draw_string):
        self.plot_name = plot_name
        title = '%s;%s;%s' % (sample, parameters['axis labels'][0], parameters['axis labels'][1])
        bins = parameters['binning']
        if len(bins) == 2 or len(bins) == 4: #Manual binning for 1D or 2D
            bins[1] = numpy.array(bins[1],numpy.dtype(float))
        if len(bins) == 4: #Manual binning for 2D
            bins[3] = numpy.array(bins[3],numpy.dtype(float))

        if parameters.get('plot type', 'TH1F') == 'TH1F':
            self.plot = ROOT.TH1F(plot_name, title, *bins)
            if parameters.get('can rebin'):
                self.plot.SetBit(ROOT.TH1.kCanRebin)
        elif parameters.get('plot type', 'TH1F') == 'TH2F':
            self.plot = ROOT.TH2F(plot_name, title, *bins)
            if parameters.get('can rebin'):
                self.plot.SetBit(ROOT.TH2.kCanRebin)
        else:
            print 'ERROR [plot_helper.py]: Method Plot::__init__ currently only supports TH1F and TH2F histograms.  Please add support for other types if you wish to use them.'
            sys.exit(2)
        try:
            tree.Project(self.plot_name, parameters['expression'], draw_string)
        except AttributeError:
            raise Exception("Tree is missing!  Exiting...")
        self.plot.SetDirectory(output_file)

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

        www_plot_directory = '%s/plots/%s/%s/%s' % (www_base_directory, config['label'], config['output directory'], lepton_category)
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
        self.draw_string = ''
        self.requirements = []
        self.factors = []

    def update_draw_string(self):
        requirements_string = ' && '.join(self.requirements)
        factors_string = ' * ' + ' * '.join(self.factors)

        self.draw_string = '(' + requirements_string + ')' + factors_string

    def remove_selection_requirements(self, cut_string_list):
        self.requirements = list(set(self.requirements) - set(cut_string_list))
        if cut_string_list == ['all']:
            self.requirements = ['isCleanEvent==1']

        self.update_draw_string()

    def append_selection_requirement(self, cut_string):
        if cut_string != '':
            self.requirements.append(cut_string)

        self.update_draw_string()

    def append_selection_requirements(self, *cut_string_lists):
        cut_string_list = list(itertools.chain(*cut_string_lists))
        for cut_string in cut_string_list:
            self.append_selection_requirement(cut_string)

    def multiply_by_factor(self, weight):
        self.factors.append(str(weight))

        self.update_draw_string()

    def multiply_by_factors(self, *weights):
        weights = list(itertools.chain(*weights))
        for weight in weights:
            self.multiply_by_factor(weight)

    def get_matched_SF(self, lepton_category):
        if 'mu_mu' in lepton_category:
            matched_SF = 'twoMuonTriggerSF'
        elif 'ele_ele' in lepton_category:
            matched_SF = 'twoElectronTriggerSF'
        elif 'mu_ele' in lepton_category:
            matched_SF = 'muonElectronTriggerSF'
        elif 'inclusive' in lepton_category or '3l' in lepton_category or '4l' in lepton_category:
            matched_SF = '1.0'

        return matched_SF

class SampleInformation:
    def __init__(self, sample):
        dictionary = {
            #ND uses WW_TuneZ2Star, CERN uses WWJetsTo2L2Nu_TuneZ2star with x_section 5.995
            'ww': {'sample_type': 'MC',
                   'is_signal': False,
                   'x_section': 54.8, #ND x_sec
                   'x_section_error': 54.8*0.035, #ND x_sec error
                   'num_generated': 9955089}, #ND number processed

            #ND uses WZ_TuneZ2star
            'wz': {'sample_type': 'MC',
                   'is_signal': False,
                   'x_section': 32.3, #ND x_sec
                   'x_section_error': 54.8*0.035, #ND x_sec error
                   'num_generated': 9931257}, #ND number processed

            #CERN uses WZJetsTo3LNu_TuneZ2
            'wz_lll': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 1.057*1.10, #CERN x_sec; equals (32.3*0.324*0.101) * 1.10
                       'x_section_error': 1.057*1.10*0.2, #CERN x_sec error
                       'num_generated': 1987010}, #ND number processed

            #ND uses ZZ_TuneZ2star
            'zz': {'sample_type': 'MC',
                   'is_signal': False,
                   'x_section': 7.7, #ND x_sec
                   'x_section_error': 7.7*0.035, #ND x_sec error
                   'num_generated': 9755621}, #ND number processed

            #ND uses ZZ_TuneZ2star
            'zz_llll': {'sample_type': 'MC',
                        'is_signal': False,
                        'x_section': 0.157*1.21, #CERN x_sec; why is it not (7.7*0.101*0.101) * 1.21
                        'x_section_error': 0.157*1.21*0.2, #CERN x_sec error
                        'num_generated': 4804217}, #ND number processed

            'www': {'sample_type': 'MC',
                    'is_signal': False,
                    'x_section': 0.08217, #CERN and ND x_sec
                    'x_section_error': 0.08217*0.5, #CERN x_sec error
                    'num_generated': 220040}, #ND number processed

            'wwz': {'sample_type': 'MC',
                    'is_signal': False,
                    'x_section': 0.0633, #CERN and ND x_sec
                    'x_section_error': 0.0633*0.5, #CERN x_sec error
                    'num_generated': 221576}, #ND number processed

            #CERN does not use any wzz sample
            'wzz': {'sample_type': 'MC',
                    'is_signal': False,
                    'x_section': 0.01922, #ND x_sec, straight from PREP
                    'x_section_error': 0.01922*0.5, #Would be CERN x_sec error
                    'num_generated': 219317}, #ND number processed 

            #CERN does not use any zzz sample
            'zzz': {'sample_type': 'MC',
                    'is_signal': False,
                    'x_section': 0.004587, #ND x_sec, straight from PREP
                    'x_section_error': 0.004587*0.5, #Would be CERN x_sec error
                    'num_generated': 224519}, #ND number processed

            'WpWpqq': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.2482, #CERN x_sec, straight from PREP
                       'x_section_error': 0.2482*0.5, #Just an unmotivated guess
                       'num_generated': 99700},

            'WmWmqq': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.0889, #CERN x_sec, straight from PREP
                       'x_section_error': 0.0889*0.5, #Just an unmotivated guess
                       'num_generated': 1}, #Not yet processed

            'WWDPI': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 0.5879, #CERN x_sec, straight from PREP
                      'x_section_error': 0.5879*0.5, #Just an unmotivated guess
                      'num_generated': 833755}, 

            ##All wjets, zjets, and ttbar_* samples use ND x_sec, x_sec error, and number processed
            'wjets': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 36257,
                      'x_section_error': 36257*0.013,
                      'num_generated': 57536319},

            'wjets_0p': {'sample_type': 'MC',
                         'is_signal': False,
                         'x_section': 36257,
                         'x_section_error': 36257*0.013,
                         'num_generated': 57536319},

            'wjets_1p': {'sample_type': 'MC',
                         'is_signal': False,
                         'x_section': 6440.4,
                         'x_section_error': 6440.4*0.013,
                         'num_generated': 23134881},

            'wjets_2p': {'sample_type': 'MC',
                         'is_signal': False,
                         'x_section': 2087.2,
                         'x_section_error': 2087.2*0.013,
                         'num_generated': 33933328},

            'wjets_3p': {'sample_type': 'MC',
                         'is_signal': False,
                         'x_section': 619.0, 
                         'x_section_error': 619.0*0.013, 
                         'num_generated': 15463420},

            'wjets_4p': {'sample_type': 'MC',
                         'is_signal': False,
                         'x_section': 255.2, 
                         'x_section_error': 255.2*0.013, 
                         'num_generated': 13365439},

            'zjets': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 3505.7, 
                      'x_section_error': 3505.7*0.012, 
                      'num_generated': 30072710}, 

            'zjets_0p': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 3505.7,
                      'x_section_error': 3505.7*0.012,
                      'num_generated': 30072710},

            'zjets_1p': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 666.7,
                      'x_section_error': 666.7*0.012,
                      'num_generated': 24032562},

            'zjets_2p': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 215.1,
                      'x_section_error': 215.1*0.012,
                      'num_generated': 2350806},

            'zjets_3p': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 66.07,
                      'x_section_error': 66.07*0.012,
                      'num_generated': 10753491},

            'zjets_4p': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 27.38,
                      'x_section_error': 27.38*0.012,
                      'num_generated': 6370630},

            'zjets_lowmass': {'sample_type': 'MC',
                              'is_signal': False,
                              'x_section': 14702, #Questionable value ... could be 12460. See email chain with Rachel Yohay, Oct. 24 2013
                              'x_section_error': 14702*0.012,
                              'num_generated': 37828841},

            'ttbar': {'sample_type': 'MC',
                      'is_signal': False,
                      'x_section': 245.8, 
                      'x_section_error': 245.8*0.03,
                      'num_generated': 6912438+1362471},

            'ttbar_cc': {'sample_type': 'MC',
                     'is_signal': False,
                     'x_section': 245.8, 
                     'x_section_error': 245.8*0.03, 
                     'num_generated': 6912438+1362471},

            'ttbar_b': {'sample_type': 'MC',
                     'is_signal': False,
                     'x_section': 245.8, 
                     'x_section_error': 245.8*0.03,
                     'num_generated': 6912438+1362471},

            'ttbar_bb': {'sample_type': 'MC',
                     'is_signal': False,
                     'x_section': 245.8, 
                     'x_section_error': 245.8*0.03,
                     'num_generated': 6912438+1362471},

            'ttbar_jj': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.457*245.8, 
                       'x_section_error': 0.457*245.8*0.03,
                       'num_generated': 31111456},

            'ttbar_cc_jj': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.457*245.8, 
                       'x_section_error': 0.457*245.8*0.03,
                       'num_generated': 31111456},

            'ttbar_b_jj': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.457*245.8, 
                       'x_section_error': 0.457*245.8*0.03,
                       'num_generated': 31111456},

            'ttbar_bb_jj': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.457*245.8, 
                       'x_section_error': 0.457*245.8*0.03,
                       'num_generated': 31111456},

            'ttbar_lj': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.438*245.8, 
                       'x_section_error': 0.438*245.8*0.03,
                       'num_generated': 25327478},

            'ttbar_cc_lj': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.438*245.8, 
                       'x_section_error': 0.438*245.8*0.03,
                       'num_generated': 25327478},

            'ttbar_b_lj': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.438*245.8, 
                       'x_section_error': 0.438*245.8*0.03,
                       'num_generated': 25327478},

            'ttbar_bb_lj': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.438*245.8, 
                       'x_section_error': 0.438*245.8*0.03,
                       'num_generated': 25327478},

            'ttbar_ll': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.105*245.8, 
                       'x_section_error': 0.105*245.8*0.03,
                       'num_generated': 12100452},

            'ttbar_cc_ll': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.105*245.8, 
                       'x_section_error': 0.105*245.8*0.03,
                       'num_generated': 12100452},

            'ttbar_b_ll': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.105*245.8, 
                       'x_section_error': 0.105*245.8*0.03,
                       'num_generated': 12100452},

            'ttbar_bb_ll': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.105*245.8, 
                       'x_section_error': 0.105*245.8*0.03,
                       'num_generated': 12100452},

            'ttbarW': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.208, #New NLO result; old number was 0.249 - AWB Feb 12, 2014
                       'x_section_error': 0.208*0.2, #CERN x_sec error; ND x_sec error = 0.208*0.1
                       'num_generated': 195396}, #ND number processed

            'ttbarZ': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 0.206, #CERN x_sec; ND x_sec error = 0.208
                       'x_section_error': 0.206*0.2, #CERN x_sec error; ND x_sec error = 0.208*0.11
                       'num_generated': 209512},

            'ttbarG': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 1.444*1.8, #CERN x_sec; PREP = 1.444
                       'x_section_error': 1.444*1.8*0.2, #CERN x_sec error? just a guess.
                       'num_generated': 71405}, #ND number processed

            'ttbarGStar_ee': {'sample_type': 'MC',
                              'is_signal': False,
                              'x_section': 1.5*0.02724*0.104, #CERN x_sec
                              'x_section_error': 1.5*0.02724*0.104*0.5, #CERN x_sec error
                              'num_generated': 13517},

            'ttbarGStar_mm': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 1.5*0.01233*0.141, #CERN x_sec
                       'x_section_error': 1.5*0.01233*0.141*0.5, #CERN x_sec error
                       'num_generated': 8019},

            'ttbarGStar_tt': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 1.5*0.00133*0.038, #CERN x_sec
                       'x_section_error': 1.5*0.00133*0.038*0.5, #CERN x_sec error
                       'num_generated': 17289},

            'ttbarWW': {'sample_type': 'MC',
                        'is_signal': False,
                        'x_section': 0.002037, #CERN x_sec
                        'x_section_error': 0.002037*0.2, #CERN x_sec error
                        'num_generated': 216867}, #ND number processed

            'tttt': {'sample_type': 'MC',
                     'is_signal': False,
                     'x_section': 0.000716, #ND x_sec, straight from PREP
                     'x_section_error': 0.000716*0.5, #Just an unmotivated guess
                     'num_generated': 99994}, #ND number processed 

            'tbZ_ll': {'sample_type': 'MC',
                     'is_signal': False,
                     'x_section': 0.0114, #CERN x_sec; PREP x_sec = 0.0217
                     'x_section_error': 0.0114*0.5, #Just an unmotivated guess
                     'num_generated': 148158}, #ND number processed 

            'VH_WW': {'sample_type': 'MC',
                      'is_signal': False,
                      #'x_section': 0.7046*0.215, #WH
                      #'x_section': 0.4153*0.215, #ZH
                      #'x_section': 0.1293*0.215, #ttH125
                      'x_section': (0.7046+0.4153+0.1293)*0.215, #Approx inclusive
                      'x_section_error': 0.0,
                      #'num_generated': 115855}, #WH
                      #'num_generated': 62466}, #ZH
                      #'num_generated': 21813}, #ttH125
                      'num_generated': (115855+62466+21813)}, #Approx inclusive
            
            'VH_tautau': {'sample_type': 'MC',
                          'is_signal': False,
                          #'x_section': 0.7046*0.0632, #WH
                          #'x_section': 0.4153*0.0632, #ZH
                          #'x_section': 0.1293*0.0632, #ttH125
                          'x_section': (0.7046+0.4153+0.1293)*0.0632, #Approx inclusive
                          'x_section_error': 0.0,
                          #'num_generated': 104098}, #WH
                          #'num_generated': 56222}, #ZH
                          #'num_generated': 19580}, #ttH125
                          'num_generated': (104098+56222+19580)}, #Approx inclusive
            
            'VH_ZZ': {'sample_type': 'MC',
                      'is_signal': False,
                      #'x_section': 0.7046*0.0264, #WH
                      #'x_section': 0.4153*0.0264, #ZH
                      #'x_section': 0.1293*0.0264, #ttH125
                      'x_section': (0.7046+0.4153+0.1293)*0.0264, #Approx inclusive
                      'x_section_error': 0.0,
                      #'num_generated': 133079}, #WH
                      #'num_generated': 276205}, #ZH
                      #'num_generated': 50505}, #ttH125
                      'num_generated': (133079+276205+50505)}, #Approx inclusive
            
            'VH_TauMu': {'sample_type': 'MC',
                          'is_signal': False,
                          #'x_section': 0.7046*0.0632, #WH
                          #'x_section': 0.4153*0.0632, #ZH
                          'x_section': (0.7046+0.4153)*0.0632, #Approx inclusive
                          'x_section_error': 0.0,
                          'num_generated': 59000}, #Inclusive
            
            #All single top samples use ND x_sec, x_sec error, and number processed
            'singlet_s': {'sample_type': 'MC',
                    'is_signal': False,
                    'x_section': 3.79,
                    'x_section_error': 3.79*0.02,
                    'num_generated': 259657},

            'singletbar_s': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 1.76,
                       'x_section_error': 1.76*0.02,
                       'num_generated': 139835},

            'singlet_t': {'sample_type': 'MC',
                    'is_signal': False,
                    'x_section': 56.4,
                    'x_section_error': 56.4*0.02,
                    'num_generated': 3744404},

            'singletbar_t': {'sample_type': 'MC',
                       'is_signal': False,
                       'x_section': 30.7,
                       'x_section_error': 30.7*0.02,
                       'num_generated': 1933504},

            'singlet_tW': {'sample_type': 'MC',
                     'is_signal': False,
                     'x_section': 11.1,
                     'x_section_error': 11.1*0.02,
                     'num_generated': 496918},

            'singletbar_tW': {'sample_type': 'MC',
                        'is_signal': False,
                        'x_section': 7.87,
                        'x_section_error': 7.87*0.02,
                        'num_generated': 492779},

            'ttH110': {'sample_type': 'MC',
                       'is_signal': True,
                       'x_section': 0.1887,
                       'x_section_error': 0.0,
                       'num_generated': 975341},

            'ttH115': {'sample_type': 'MC',
                       'is_signal': True,
                       'x_section': 0.1663,
                       'x_section_error': 0.0,
                       'num_generated': 995188},

            'ttH120': {'sample_type': 'MC',
                       'is_signal': True,
                       'x_section': 0.147,
                       'x_section_error': 0.0,
                       'num_generated': 996773},

            'ttH125': {'sample_type': 'MC',
                       'is_signal': True,
                       'x_section': 0.1302,
                       'x_section_error': 0.0,
                       'num_generated': 992997},

            'ttH130': {'sample_type': 'MC',
                       'is_signal': True,
                       'x_section': 0.1157,
                       'x_section_error': 0.0,
                       'num_generated': 931369},

            'ttH135': {'sample_type': 'MC',
                       'is_signal': True,
                       'x_section': 0.1031,
                       'x_section_error': 0.0,
                       'num_generated': 993975},

            'ttH140': {'sample_type': 'MC',
                       'is_signal': True,
                       'x_section': 0.09207,
                       'x_section_error': 0.0,
                       'num_generated': 997191},

            'MuEG': {'sample_type': 'data',
                     'is_signal': False,
                     'x_section': 1,
                     'x_section_error': 0.0,
                     'num_generated': 1},

            'DoubleMu': {'sample_type': 'data',
                         'is_signal': False,
                         'x_section': 1,
                         'x_section_error': 0.0,
                         'num_generated': 1},

            'DoubleElectron': {'sample_type': 'data',
                               'is_signal': False,
                               'x_section': 1,
                               'x_section_error': 0.0,
                               'num_generated': 1},

            'inclusive_data': {'sample_type': 'data',
                               'is_signal': False,
                               'x_section': 1,
                               'x_section_error': 0.0,
                               'num_generated': 1},

            'MuEG_NP_sideband': {'sample_type': 'NP_sideband',
                     'is_signal': False,
                     'x_section': 1,
                     'x_section_error': 0.0,
                     'num_generated': 1},

            'DoubleMu_NP_sideband': {'sample_type': 'NP_sideband',
                         'is_signal': False,
                         'x_section': 1,
                         'x_section_error': 0.0,
                         'num_generated': 1},

            'DoubleElectron_NP_sideband': {'sample_type': 'NP_sideband',
                                           'is_signal': False,
                                           'x_section': 1,
                                           'x_section_error': 0.0,
                                           'num_generated': 1},

            'inclusive_data_NP_sideband': {'sample_type': 'NP_sideband',
                                           'is_signal':False,
                                           'x_section': 1,
                                           'x_section_error': 0.0,
                                           'num_generated': 1},

            'MuEG_QF_sideband': {'sample_type': 'QF_sideband',
                                 'is_signal': False,
                                 'x_section': 1,
                                 'x_section_error': 0.0,
                                 'num_generated': 1},

            'DoubleElectron_QF_sideband': {'sample_type': 'QF_sideband',
                                           'is_signal': False,
                                           'x_section': 1,
                                           'x_section_error': 0.0,
                                           'num_generated': 1},

            'inclusive_data_QF_sideband': {'sample_type': 'QF_sideband',
                                           'is_signal':False,
                                           'x_section': 1,
                                           'x_section_error': 0.0,
                                           'num_generated': 1}
            }

        self.sample = sample
        self.sample_type = dictionary[sample]['sample_type']
        self.is_signal = dictionary[sample]['is_signal']
        self.x_section = dictionary[sample]['x_section']
        self.x_section_error = dictionary[sample]['x_section_error']
        self.num_generated = dictionary[sample]['num_generated']

def get_systematic_info(systematic):
    dictionary = {
        'nominal': {'weight_string': '1', 'systematic_label': ''},
        'JESUp': {'weight_string': '1', 'systematic_label': '_JESUp'},
        'JESDown': {'weight_string': '1', 'systematic_label': '_JESDown'},
        'weight_PUUp': {'weight_string': '(weight_PUUp/weight_PU)', 'systematic_label': '_weight_PUUp'},
        'weight_PUDown': {'weight_string': '(weight_PUDown/weight_PU)', 'systematic_label': '_weight_PUDown'},
        'csvWeightHFUp': {'weight_string': 'csvWeightHFUp', 'systematic_label': '_csvWeightHFUp'},
        'csvWeightHFDown': {'weight_string': 'csvWeightHFDown', 'systematic_label': '_csvWeightHFDown'},
        'csvWeightLFUp': {'weight_string': 'csvWeightLFUp', 'systematic_label': '_csvWeightLFUp'},
        'csvWeightLFDown': {'weight_string': 'csvWeightLFDown', 'systematic_label': '_csvWeightLFDown'},
        'CSV_HFUp': {'weight_string': 'CSV_HFUp', 'systematic_label': '_CSV_HFUp'},
        'topPtWgtDown': {'weight_string': '(1/topPtWgt)', 'systematic_label': '_topPtWgtDown'},
        'topPtWgtUp': {'weight_string': '(topPtWgtUp/topPtWgt)', 'systematic_label': '_topPtWgtUp'},
        '40PercentRateUp': {'weight_string': '(1.40)', 'systematic_label': '_40PercentRateUp'},
        '40PercentRateDown': {'weight_string': '(0.60)', 'systematic_label': '_40PercentRateDown'},
        'RecoIDIsoSIPSFDown_3lep': {'weight_string': '(RecoIDIsoSIPSFDown_3lep/RecoIDIsoSIPSF_3lep)', 'systematic_label': '_RecoIDIsoSIPSFDown_3lep'},
        'RecoIDIsoSIPSFUp_3lep': {'weight_string': '(RecoIDIsoSIPSFUp_3lep/RecoIDIsoSIPSF_3lep)', 'systematic_label': '_RecoIDIsoSIPSFUp_3lep'}
        }

    return (dictionary[systematic]['weight_string'], dictionary[systematic]['systematic_label'])

def customize_systematics(systematics, customization_string):
    customized_systematics = customize_list(systematics, customization_string)

    if 'nominal' not in customized_systematics:
        customized_systematics.append('nominal')

    return customized_systematics

def customize_list(common_list, customization_list):
    if customization_list == 'common':
        customized_list = common_list
    elif customization_list == 'none':
        customized_list = []
    elif 'common' in customization_list:
        customization_list.remove('common')
        customized_list = list(set(common_list+customization_list))
    elif isinstance(customization_list, str):
        customized_list = [customization_list]
    else:
        customized_list = customization_list

    return customized_list

class Yields:
    def __init__(self, jet_tag_categories, samples):
        for jet_category in jet_tag_categories:
            self.__dict__[jet_category] = DefaultOrderedDict(dict)
            for sample in samples:
                self.__dict__[jet_category][sample] = {}

    def __getitem__(self, item):
        return self.__dict__[item]

    def items(self):
        return [(jet_category, self.__dict__[jet_category]) for jet_category in self.__dict__.keys()]

