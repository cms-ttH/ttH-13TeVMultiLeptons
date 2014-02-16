#!/usr/bin/env python
import sys
import os
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper
from argparse import ArgumentParser
import ROOT
import yaml

def main():
    parser = ArgumentParser(description='Make plots from summary trees.')
    parser.add_argument('config_file_name', nargs='?', default='multilepton.yaml', help='Configuration file to process.')
    parser.add_argument('-b', '--batch', action='store_true', help='Batch mode: this submits one sample per condor job.')
    parser.add_argument('-p', '--pdf', action='store_true', help='Save a PDF of each plot. Default is not to save a PDF.')
    parser.add_argument('-w', '--web', action='store_true', help='Post each plot to the user\'s AFS space.')
    parser.add_argument('-l', '--lepton_category', help='Run on a single lepton category.  Default is to run on all lepton categories listed in the configuration file.')
    parser.add_argument('-n', '--no_weights', action='store_true', help='Don\'t apply any normalization or weights.')
    parser.add_argument('-f', '--file', help='Run on a single file.  (Must also specify which sample it is with --sample.)')
    parser.add_argument('-s', '--sample', help='Run on a single sample.  Default is to run on all samples listed in the configuration file.')
    parser.add_argument('--label', help='Override the label set in the configuration file with LABEL')
    args = parser.parse_args()

    with open(args.config_file_name) as config_file:
        config = yaml.load(config_file)

    if args.label:
        config['label'] = args.label

    #use common systematics and weight as default for all samples
    config['samples'] = dict((k, v if v else {'systematics':'common', 'weights':'common'}) for k, v in config['samples'].items())
    if args.sample:
        config['samples'] = dict(((k, v) for k, v in config['samples'].items() if k == args.sample))

    lepton_categories = config['lepton categories']
    if args.lepton_category:
        lepton_categories = {args.lepton_category: lepton_categories[args.lepton_category]}

    plot_helper.make_sure_directories_exist([os.path.join(config['output directory'], category) for category in lepton_categories])
    if args.web:
        www_plot_directories = [os.path.join('plots', config['label'], config['output directory'], lepton_category) for lepton_category in lepton_categories]
        plot_helper.setup_web_posting(www_plot_directories, 4, args.config_file_name)

    if args.batch:
        submit_batch_jobs(config, config['samples'], lepton_categories)
    else:
        make_histos(args, config, config['samples'], lepton_categories)

    if args.web:
        if args.batch:
            print '\nFinished submitting jobs.  After they complete, plots will be posted to: http://www.crc.nd.edu/~%s/plots/%s/' % (os.environ['USER'], config['label'])
        else:
            plot_helper.update_indexes(config['output directory'])
            print '\nFinished processing.  Plots will be posted to: http://www.crc.nd.edu/~%s/plots/%s/' % (os.environ['USER'], config['label'])

def make_histos(args, config, samples, lepton_categories):
    for sample, sample_dict in samples.items():
        tree_sample = sample_dict.get('tree sample', sample)
        additional_cuts = sample_dict.get('additional cuts', [])
        sample_info = plot_helper.SampleInformation(tree_sample)

        for lepton_category, lepton_dict in lepton_categories.items():
            lepton_category_cut_strings = lepton_dict.get('cuts', {}).values()
            if sample_info.sample_type == 'data' or 'sideband' in sample_info.sample_type:
                if not plot_helper.is_matching_data_sample(lepton_dict['data samples'], sample):
                    continue

            for jet_tag_category in config['jet tag categories']:
                output_file_name = '%s/%s/%s_%s_%s_%s.root' % (config['output directory'], lepton_category, lepton_category, jet_tag_category, sample, config['label'])
                output_file = ROOT.TFile(output_file_name, 'RECREATE')

                systematics_list = plot_helper.customize_systematics(config['systematics'], sample_dict.get('systematics', 'common'))
                if config['skip systematics']:
                    systematics_list = ['nominal']
                for systematic in systematics_list:
                    print 'Beginning next loop iteration. Sample: %10s Jet tag category: %-10s  Lepton category: %-10s Systematic: %-10s' % (sample, jet_tag_category, lepton_category, systematic)

                    systematic_weight_string, systematic_label = plot_helper.get_systematic_info(systematic)
                    source_file_name = '%s/%s_%s_all.root' % (config['input_trees_directory'], tree_sample, config['label'])
                    if args.file:
                        source_file_name = args.file
                    source_file = ROOT.TFile(source_file_name)
                    tree = source_file.Get('summaryTree')

                    draw_string_maker = plot_helper.DrawStringMaker()
                    draw_string_maker.append_selection_requirements(config['common cuts'].values(),
                                                                    lepton_category_cut_strings,
                                                                    [config['jet tag categories'][jet_tag_category]],
                                                                    additional_cuts) #additional_cuts is empty by default
                    if sample_info.sample_type == 'NP_sideband':
                        draw_string_maker.append_selection_requirements(config.get('NP sideband cuts', {}).values())
                    elif sample_info.sample_type == 'QF_sideband':
                        draw_string_maker.append_selection_requirements(config.get('QF sideband cuts', {}).values())
                    else:
                        draw_string_maker.append_selection_requirements(config.get('regular selection cuts', {}).values())

                    if not args.no_weights:
                        if sample_info.sample_type == 'MC' and 'triggerSF' in config['weights']:
                            matched_SF = draw_string_maker.get_matched_SF(lepton_category)
                            config['weights'] = [matched_SF if x=='triggerSF' else x for x in config['weights']]
                        weights = plot_helper.customize_list(config['weights'], sample_dict.get('weights', 'common'))
                        draw_string_maker.multiply_by_factors(weights, systematic_weight_string)

                    if sample_info.sample_type not in ['MC', 'data'] and 'sideband' not in sample_info.sample_type:
                        sys.exit('Invalid sample_type must be data, sideband, or MC' % (sample_info.sample_type))

                    config = plot_helper.append_integral_histo(config)
                    for distribution in config['distributions'].keys():
                        plot_name = '%s_%s_%s_%s%s' % (sample, lepton_category, jet_tag_category, distribution, systematic_label)
                        plot = plot_helper.Plot(sample, output_file, tree, plot_name, config['distributions'][distribution], draw_string_maker.draw_string)
                        if sample_info.sample_type == 'MC':
                            plot.plot.Scale(sample_info.x_section * config['luminosity'] / sample_info.num_generated)
                        output_file.Write()
                        if args.pdf:
                            plot.save_image('pdf')
                        if args.web:
                            plot.post_to_web(config, lepton_category)

                    source_file.Close() #end systematic
                output_file.Close() #end jet tag category

def submit_batch_jobs(config, samples, lepton_categories):
    plot_helper.make_sure_directories_exist(['batch_logs/%s' % config['label']])

    argument_string = ''
    for argument in sys.argv[1:]:
        if argument != '-b' and argument != '-batch':
            argument_string += argument + ' '

    condor_header = 'universe = vanilla \nexecutable = make_histos.py \nnotification = Never \ngetenv = True \n+IsExpressJob = True'
    for sample in samples:
        for lepton_category in lepton_categories:
            condor_submit_file = open('make_histos_batch.submit', 'w')
            condor_submit_file.write(condor_header)
            condor_submit_file.write('\narguments = -s %s -l %s %s' % (sample, lepton_category, argument_string))
            condor_submit_file.write('\nlog = batch_logs/%s/%s_%s_%s.log' % (config['label'], config['label'], sample, lepton_category))
            condor_submit_file.write('\noutput = batch_logs/%s/%s_%s_%s.stdout' % (config['label'], config['label'], sample, lepton_category))
            condor_submit_file.write('\nerror = batch_logs/%s/%s_%s_%s.stderr' % (config['label'], config['label'], sample, lepton_category))
            condor_submit_file.write('\nqueue 1')
            condor_submit_file.close()

            os.popen('condor_submit make_histos_batch.submit')
            print '\nSubmitting batch jobs for sample %s, lepton category %s... ' % (sample, lepton_category)

if __name__ == '__main__':
    main()
