#!/usr/bin/env python
import os
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
from ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper import *
from argparse import ArgumentParser
import ROOT

parser = ArgumentParser(description='Make plots from summary trees.')
parser.add_argument('config_file_name', help='Configuration file to process.')
parser.add_argument('-b', '--batch', action='store_true', help='Batch mode: this submits one sample per condor job.')
parser.add_argument('-s', '--sample', action='append', help='Run on a single sample.  Default is to run on all samples listed in the configuration file.')
args = parser.parse_args()

config = ConfigParser()
config.read(args.config_file_name)
project_label = config['run_parameters']['label']
lepton_categories = config['lepton_categories'].keys()
for lepton_category in lepton_categories: #This should be outside the run loop so we don't create race conditions in batch mode
    if not os.path.exists(lepton_category):
        os.makedirs(lepton_category)
        
if args.sample:
    samples = args.sample
else:
    samples = config['samples'].keys()

def run(args, config, samples, project_label):
    lumi = config['run_parameters']['lumi']
    cut_strings = config['cuts'].values() #.values() returns a list of everything after the ':' under the 'cuts' header in the config file
    jet_tag_categories = config['jet_tag_categories'].keys() #.keys() returns a list of everything before the ':' under the 'distributions' header in the config file

    mc_weight_strings = config['mc_weights'].values()
    baseline_systematics = config['baseline_systematics'].keys()
    distributions = config['distributions'].keys()
    plot_parameters = config['distributions'].values()

    for sample in samples:

        sample_info = SampleInformation(sample)
        systematics_info = SystematicsInformation(baseline_systematics)
        systematics_info.edit_systematics_list(sample_info.systematics)
        for systematic in systematics_info.systematics_list:

            systematic_weight_string = systematics_info.dictionary[systematic]['weight_string']
            source_file_label = systematics_info.dictionary[systematic]['source_file_label']
            if source_file_label == '' or source_file_label == 'nominal':
                source_file_name = 'tree_files/summary_trees_%s_%s_all.root' % (sample, project_label)                
            else:
                source_file_name = 'tree_files/summary_trees_%s_%s_%s_all.root' % (sample, project_label, source_file_label)
            source_file = ROOT.TFile(source_file_name)
            tree = source_file.Get('summaryTree')

            for lepton_category in lepton_categories:
                output_file_name = '%s/%s_%s.root' % (lepton_category, sample, project_label)
                output_file = ROOT.TFile(output_file_name, 'RECREATE')

                for jet_tag_category in jet_tag_categories:
                    print 'Beginning loop.  Jet tag category: %-10s  Lepton category: %-10s Systematic: %-10s' % (jet_tag_category, lepton_category, systematic)

                    draw_string_maker = DrawStringMaker()
                    draw_string_maker.append_selection_requirements(cut_strings)
                    draw_string_maker.append_jet_tag_category_requirements(jet_tag_category)
                    draw_string_maker.append_lepton_category_requirements(lepton_category)
                    draw_string_maker.multiply_by_factor(systematic_weight_string)
                    if not sample_info.is_data:
                        draw_string_maker.multiply_by_factors(mc_weight_strings)
                        draw_string_maker.multiply_by_factor('%s * %s / %s' % (sample_info.x_section, lumi, sample_info.num_generated))
                        
                    for (distribution, parameters) in zip(distributions, plot_parameters):
                        plot = Plot(output_file, tree, distribution, parameters, draw_string_maker.draw_string)
                        
                output_file.Close() #end lepton category
            source_file.Close() #end systematic

if not args.batch:
    run(args, config, samples, project_label)    
else:
    if not os.path.exists('batch_logs'):
        os.makedirs('batch_logs')
    condor_header = 'universe = vanilla \nexecutable = make_plots.py \nnotification = Never \ngetenv = True \n+IsExpressJob = True'
    for sample in samples:        
        condor_submit_file = open('make_plots_batch.submit', 'w')
        condor_submit_file.write(condor_header)
        condor_submit_file.write('\narguments = -s %s %s' % (sample, args.config_file_name))
        condor_submit_file.write('\nlog = batch_logs/%s_%s.log' % (project_label, sample))
        condor_submit_file.write('\noutput = batch_logs/%s_%s.stdout' % (project_label, sample))
        condor_submit_file.write('\nerror = batch_logs/%s_%s.stderr' % (project_label, sample))
        condor_submit_file.write('\nqueue 1')
        condor_submit_file.close()

        os.popen('condor_submit make_plots_batch.submit')
