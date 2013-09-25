#!/usr/bin/env python
import sys
import os
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper
from argparse import ArgumentParser
import ROOT

def main():
    parser = ArgumentParser(description='Make plots from summary trees.')
    parser.add_argument('config_file_name', help='Configuration file to process.')
    parser.add_argument('-b', '--batch', action='store_true', help='Batch mode: this submits one sample per condor job.')
    parser.add_argument('-p', '--pdf', action='store_true', help='Save a PDF of each plot. Default is not to save a PDF.')
    parser.add_argument('-w', '--web', action='store_true', help='Post each plot to the user\'s AFS space.')
    parser.add_argument('-s', '--sample', action='append', help='Run on a single sample.  Default is to run on all samples listed in the configuration file.')
    parser.add_argument('-n', '--no_weights', action='store_true', help='Don\'t apply any normalization or weights.')
    parser.add_argument('-f', '--file', help='Run on a single file.  (Must also specify which sample it is with --sample.)')
    args = parser.parse_args()

    config = ConfigParser()
    config.read(args.config_file_name)

    if args.sample:
        samples = args.sample
    else:
        samples = config['samples'].keys()

    lepton_categories = config['lepton_categories'].keys()
    for lepton_category in lepton_categories: #This should be outside the run loop so we don't create race conditions in batch mode
        if not os.path.exists(lepton_category):
            os.makedirs(lepton_category)
            
    project_label = config['run_parameters']['label']
    if args.batch:
        submit_batch_jobs(samples, lepton_categories, project_label)
    else:
        make_plots(args, config, samples, lepton_categories, project_label)

    if args.web:
        print '\nFinished processing.  Plots will be posted to: http://www.nd.edu/~%s/%s/' % (os.environ['USER'], config['run_parameters']['label'])

def make_plots(args, config, samples, lepton_categories, project_label):
    lumi = config['run_parameters']['lumi']
    default_num_bins = config['run_parameters']['default_num_bins']
    input_trees_directory = config['run_parameters']['input_trees_directory']
    cut_strings = config['common cuts'].values() #.values() returns a list of everything after the ':' under the 'cuts' header in the config file
    jet_tag_categories = config['jet_tag_categories'].keys() #.keys() returns a list of everything before the ':' under the 'distributions' header in the config file
    mc_weight_strings = config['mc_weights'].values()
    baseline_systematics = config['baseline_systematics'].keys()
    distributions = config['distributions'].keys()
    plot_parameters = config['distributions'].values()

    for sample in samples:
        sample_info = plot_helper.SampleInformation(sample)

        for lepton_category in lepton_categories:
            if sample_info.is_data and not plot_helper.get_data_sample_name(lepton_category) == sample:
                    continue
            lepton_category_cut_strings = config['%s cuts' % lepton_category].values()

            for jet_tag_category in jet_tag_categories:
                output_file_name = '%s/%s_%s_%s_%s.root' % (lepton_category, lepton_category, jet_tag_category, sample, project_label)
                output_file = ROOT.TFile(output_file_name, 'RECREATE')

                systematics_info = plot_helper.SystematicsInformation(baseline_systematics)
                systematics_info.edit_systematics_list(sample_info.systematics)
                for systematic in systematics_info.systematics_list:
                    print 'Beginning next loop iteration. Sample: %10s Jet tag category: %-10s  Lepton category: %-10s Systematic: %-10s' % (sample, jet_tag_category, lepton_category, systematic)
                    
                    systematic_weight_string = systematics_info.dictionary[systematic]['weight_string']
                    source_file_label = systematics_info.dictionary[systematic]['source_file_label']
                    if source_file_label != '':
                        source_file_label = '_' + source_file_label
                    source_file_name = '%s/%s_%s%s_all.root' % (input_trees_directory, sample, project_label, source_file_label)
                    if args.file:
                        source_file_name = args.file
                    source_file = ROOT.TFile(source_file_name)
                    tree = source_file.Get('summaryTree')

                    draw_string_maker = plot_helper.DrawStringMaker()
                    draw_string_maker.append_selection_requirements(cut_strings)
                    draw_string_maker.append_selection_requirements(lepton_category_cut_strings)                    
                    draw_string_maker.append_jet_tag_category_requirements(jet_tag_category)

                    if not sample_info.is_data and not args.no_weights:
                        draw_string_maker.multiply_by_factor(systematic_weight_string)                        
                        draw_string_maker.multiply_by_factors(mc_weight_strings)

                    for (distribution, parameters) in zip(distributions, plot_parameters):
                        plot_name = '%s_%s_%s_%s%s' % (sample, lepton_category, jet_tag_category, distribution, source_file_label)
                        plot = plot_helper.Plot(output_file, tree, distribution, plot_name, default_num_bins, parameters, draw_string_maker.draw_string)
                        if not sample_info.is_data:
                            plot.plot.Scale(sample_info.x_section * lumi * plot.plot.GetEntries() / sample_info.num_generated)
                        if args.pdf:
                            plot.save_image('pdf')
                        if args.web:
                            plot.post_to_web(args.config_file_name, config, lepton_category)

                    source_file.Close() #end systematic
                output_file.Close() #end jet tag category

def submit_batch_jobs(samples, lepton_categories, project_label):
    if not os.path.exists('batch_logs'):
        os.makedirs('batch_logs')

    argument_string = ''
    for argument in sys.argv[1:]:
        if argument != '-b' and argument != '-batch':
            argument_string += argument + ' '
                
    condor_header = 'universe = vanilla \nexecutable = make_plots.py \nnotification = Never \ngetenv = True \n+IsExpressJob = True'
    for sample in samples:        
        condor_submit_file = open('make_plots_batch.submit', 'w')
        condor_submit_file.write(condor_header)
        condor_submit_file.write('\narguments = -s %s %s' % (sample, argument_string))
        condor_submit_file.write('\nlog = batch_logs/%s_%s.log' % (project_label, sample))
        condor_submit_file.write('\noutput = batch_logs/%s_%s.stdout' % (project_label, sample))
        condor_submit_file.write('\nerror = batch_logs/%s_%s.stderr' % (project_label, sample))
        condor_submit_file.write('\nqueue 1')
        condor_submit_file.close()

        os.popen('condor_submit make_plots_batch.submit')
        print '\nSubmitting batch jobs for sample: %s... ' % sample

if __name__ == '__main__':
    main()
