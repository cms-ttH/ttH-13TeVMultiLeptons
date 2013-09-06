#!/usr/bin/env python
import os, sys
import ROOT

class Plot:
    def __init__(self, output_file, tree, distribution, plot_name, default_num_bins, parameters, draw_string):
        (plot_type, title, num_bins, x_min, x_max) = parameters
        if num_bins == 'default_num_bins':
            num_bins = int(default_num_bins)
        self.plot_name = plot_name

        if plot_type == 'TH1F':
            self.plot = ROOT.TH1F(plot_name, title, num_bins, x_min, x_max)
            tree.Project(self.plot_name, distribution, draw_string)
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

    def post_to_web(self, config_file_name, config, lepton_category):
        self.save_image('png', 'pdf')
        afs_base_directory = self.get_afs_base_directory(config)
        afs_directory = afs_base_directory + '/' + config['run_parameters']['label'] + '/' + lepton_category
        if not os.path.exists(afs_directory):
            os.makedirs(afs_directory)
            
        from distutils import file_util
        file_util.move_file('plot_pdfs/%s.png' % self.plot_name, afs_directory)
        file_util.copy_file('plot_pdfs/%s.pdf' % self.plot_name, afs_directory)
        file_util.copy_file('%s' % config_file_name, afs_directory)
        file_util.copy_file('utilities/index.php', afs_directory)
        file_util.copy_file('utilities/index.php', afs_base_directory + '/' + config['run_parameters']['label'])

    def get_afs_base_directory(self, config):
        try:
            afs_base_directory = config['run_parameters']['afs_base_directory']
        except:
            import subprocess
            print "\n\nDid not find an afs_base_directory defined in the configuration file.  Looking for it now (this can take a minute)..."
            process = subprocess.Popen('ls -d /afs/nd.edu/user*/%s/www' % os.environ['USER'], stdout=subprocess.PIPE, shell=True)
            output, error = process.communicate()
            afs_base_directory = output.strip()
            print "Found it! To skip this step next time, add the following line under the ['run_parameters'] heading in your configuration file: \n afs_base_directory: %s \n\n" % afs_base_directory
            config['run_parameters']['afs_base_directory'] = afs_base_directory

        return afs_base_directory 
            
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

    def append_selection_requirements(self, cut_strings): 
        for cut_string in cut_strings:
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
        elif jet_tag_category == 'inclusive':
            jet_tag_string = ''
        elif jet_tag_category == 'ge4j':
            jet_tag_string = 'numJets>=4'
        else:
            print 'ERROR [plot_helper.py]: Unrecognized jet tag category. Please update DrawStringMaker::append_jet_tag_category_requirements'
            sys.exit(2)

        self.append_selection_requirement(jet_tag_string)

    def append_lepton_category_requirements(self, lepton_category):
        if lepton_category == 'mu_mu':
            lepton_category_string = '(isDoubleMuTriggerPass == 1)'
        elif lepton_category == 'ele_ele':
            lepton_category_string = '(isDoubleEleTriggerPass == 1)'
        elif lepton_category == 'mu_ele':
            lepton_category_string = '(isMuEGTriggerPass == 1)'
        elif lepton_category == 'inclusive':
            lepton_category_string = ''
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

            'ZZ': {'is_data': False,
                   'x_section': 0.0077,#0.00826,
                   'x_section_error': 0.00015,
                   'num_generated':  9755621,
                   'systematics': 'all'},

            'WWW': {'is_data': False,
                    'x_section': 0.00008217,#0.0571,
                    'x_section_error': 0.00008217*0.0015/0.0548,
                    'num_generated': 220040,
                    'systematics': 'all'},
            
            'WWZ': {'is_data': False,
                    'x_section': 0.0000633,#0.0571,
                    'x_section_error': 0.0000633*0.0015/0.0548,
                    'num_generated': 221576,
                    'systematics': 'all'},

            'WZZ': {'is_data': False, 
                    # 		 'x_section': 0.00001922,#0.0571,
                    'x_section': 0.0000001,
                    'x_section_error': 0.00001922*0.0015/0.0548,
                    'num_generated': 219835,
                    'systematics': 'all'},                    

            'ZZZ': {'is_data': False,
                    'x_section': 0.000004587,#0.0571,
                    'x_section_error': 0.000004587*0.0015/0.0548,
                    'num_generated': 224519,
                    'systematics': 'all'},                                        

            'WJets': {'is_data': False,
                      'x_section': 36.257,
                      'x_section_error': 1.558,
                      'num_generated':  57536319,
                      'systematics': 'all'},                                                              

            'ZJets': {'is_data': False,
                      'x_section': 3.5057,
                      'x_section_error': 0.132,
                      'num_generated':	30072710,
                      'systematics': 'all'},
            
            'ZJets_M10-50': {'is_data': False,
                             'x_section': 14.7, #0.860,
                             'x_section_error': 0.132*0.86/3.5057,
                             'num_generated': 37828841,
                             'systematics': 'all'},

            'ttW': {'is_data': False,
                    'x_section': 0.000249, #0.000163*1.5,
                    'x_section_error': 0.2*0.000249,
                    'num_generated':  195396,
                    'systematics': 'all'},                    

            'ttZ': {'is_data': False,
                    'x_section': 0.000208,#0.000136*1.5,
                    'x_section_error': 0.2*0.000208,
                    'num_generated':  209512,
                    'systematics': 'all'},                    

            'ttWW': {'is_data': False,
                     'x_section': 0.000002037,#0.000136*1.5,
                     'x_section_error': 0.2*0.000002037,
                     'num_generated':  216867,
                     'systematics': 'all'},                    

            'tttt': {'is_data': False,
                     'x_section': 0.0000000001,#0.000000716,
                     'x_section_error': 0.2*0.000000716,
                     'num_generated':  99994,
                     'systematics': 'all'},                    

            't_s': {'is_data': False,
                    'x_section': 0.00379,
                    'x_section_error': 0.00006*0.00379/(0.00379+0.00176),
                    'num_generated': 259657,
                    'systematics': 'all'},                    

            'tbar_s': {'is_data': False,
                       'x_section': 0.00176,
                       'x_section_error': 0.00006*0.00176/(0.00379+0.00176),
                       'num_generated': 139835,
                       'systematics': 'all'},                    

            't_t': {'is_data': False,
                    'x_section': 0.0564,
                    'x_section_error': 0.0032*0.0564/(0.0564+0.0307),
                    'num_generated': 3744404,
                    'systematics': 'all'},                    

            'tbar_t': {'is_data': False,
                       'x_section': 0.0307,
                       'x_section_error': 0.0032*0.0307/(0.0564+0.0307),
                       'num_generated': 1933504,
                       'systematics': 'all'},                    

            't_tW': {'is_data': False,
                     'x_section': 0.0111,
                     'x_section_error': 0.0008*0.0111/0.00106,	  #### 0.00106
                     'num_generated': 496918,
                     'systematics': 'all'},                    

            'tbar_tW': {'is_data': False,
                        'x_section': 0.0111,
                        'x_section_error': 0.0008*0.0111/0.00106,	 #### 0.00106
                        'num_generated': 492779,
                        'systematics': 'all'},                    

            'ttbb': {'is_data': False,
                     'x_section': 0.2458, #0.225197,
                     'x_section_error': 0.5*0.2458, #0.225197, #0.3*0.225197,
                     'num_generated':  6912438+1362471,
                     'systematics': 'all'},                    

            'ttcc': {'is_data': False,
                     'x_section': 0.2458, #0.225197,
                     'x_section_error': 0.3*0.2458, #0.225197,
                     'num_generated':  6912438+1362471,
                     'systematics': 'all'},                    

            'tt': {'is_data': False,
                   'x_section': 0.2458, #0.225197,
                   'x_section_error': 0.024,
                   'num_generated':  6912438+1362471,
                   'systematics': 'all'},                    

            'ttH_110': {'is_data': False,
                        'x_section': 0.0001887,
                        'x_section_error': 0.0,
                        'num_generated': 975341,
                        'systematics': 'all'},                    

            'ttH_115': {'is_data': False,
                        'x_section': 0.0001663,
                        'x_section_error': 0.0,
                        'num_generated': 995188,
                        'systematics': 'all'},                    

            'ttH_120': {'is_data': False,
                        'x_section': 0.000147,
                        'x_section_error': 0.0,
                        'num_generated': 996773,
                        'systematics': 'all'},

            'ttH125': {'is_data': False,
                       'x_section': 0.0001302,
                       'x_section_error': 0.0,
                       'num_generated': 992997,
                       'systematics': 'all'},

            'ttH_130': {'is_data': False,
                        'x_section': 0.0001157,
                        'x_section_error': 0.0,
                        'num_generated': 931369,
                        'systematics': 'all'},                    

            'ttH_135': {'is_data': False,
                        'x_section': 0.0001031,
                        'x_section_error': 0.0,
                        'num_generated': 993975,
                        'systematics': 'all'},                    

            'ttH_140': {'is_data': False,
                        'x_section': 0.00009207,
                        'x_section_error': 0.0,
                        'num_generated': 997191,
                        'systematics': 'all'},                    

            'data_2012_53x': {'is_data': True,
                              'x_section': 1,
                              'x_section_error': 0.0,
                              'num_generated': 1,
                              'systematics': 'none'}

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
        if sample_systematics_string == 'none' or sample_systematics_string == 'None':
            self.systematics_list = ['nominal']
        else:
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
