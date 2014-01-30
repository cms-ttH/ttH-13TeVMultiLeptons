#!/usr/bin/env python
##########################################################################
##Streamline event removal
##Warning (not an error in this code): CERN has some negative event numbers
###########################################################################
import re
import os
import math
import copy
from argparse import ArgumentParser
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
import ROOT
#from ROOT import gStyle
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper
import yaml
import collections
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(110011)

parser = ArgumentParser(description='Make histograms of events that are different between two trees.')
parser.add_argument('sample_1', help='ND sample')
parser.add_argument('sample_2', help='CERN sample')
parser.add_argument('cuts_file_name', help='YAML file with selection cuts')
args = parser.parse_args()

with open(args.cuts_file_name) as config_file:
    config = yaml.load(config_file)
    verbose = config['verbose']

cuts_file_label = args.cuts_file_name.replace('.yaml', '')
if not os.path.exists(cuts_file_label):
    os.makedirs(cuts_file_label)

def main():
    tree_file_1 = ROOT.TFile(os.path.join(config['first tree dir'], '%s_%s_all.root' % (args.sample_1, config['label'])))
    tree_1_pass = tree_file_1.Get('summaryTree')
    tree_1_all = tree_file_1.Get('summaryTree')
    tree_file_2 = ROOT.TFile(os.path.join(config['second tree dir'], 'TREES_250513_HADD_gpetrucc_%s.root' % args.sample_2))
    tree_2_pass = tree_file_2.Get('ttHLepTreeProducerBase')
    tree_2_all = tree_file_2.Get('ttHLepTreeProducerBase')
    if verbose: print 'Got trees'

    cuts_1 = config['ND cuts'].values()
    cuts_2 = config['CERN cuts'].values()
    if verbose: print 'Got cuts'

    all_cuts_1 = ROOT.TCut()
    all_cuts_2 = ROOT.TCut()
    for cut_string in cuts_1:
        if verbose: print 'Adding ND cut_string %s' % cut_string
        all_cuts_1 += ROOT.TCut(cut_string)
    for cut_string in cuts_2:
        if verbose: print 'Adding CERN cut_string %s' % (cut_string)
        all_cuts_2 += ROOT.TCut(cut_string)

    (tree_event_list_pass_1, events_pass_1) = get_lists(tree_1_pass, 'pass_1', 'eventInfo_run:eventInfo_lumi:eventInfo_evt', all_cuts_1.GetTitle())
    (tree_event_list_pass_2, events_pass_2) = get_lists(tree_2_pass, 'pass_2', 'run:lumi:evt', all_cuts_2.GetTitle())
    (tree_event_list_all_1, all_events_1) = get_lists(tree_1_all, 'all_1', 'eventInfo_run:eventInfo_lumi:eventInfo_evt', '')
    (tree_event_list_all_2, all_events_2) = get_lists(tree_2_all, 'all_2', 'run:lumi:evt', '')

    if verbose: print 'ND has '+str(len(events_pass_1))+' selected events.'
    if verbose: print 'CERN has '+str(len(events_pass_2))+' selected events.'

    unique_events_pass_1 = set(events_pass_1)
    unique_events_pass_2 = set(events_pass_2)
    common_events = unique_events_pass_1.intersection(unique_events_pass_2)
    events_pass_1_fail_2 = unique_events_pass_1.difference(unique_events_pass_2)
    events_fail_1_pass_2 = unique_events_pass_2.difference(unique_events_pass_1)

    if verbose: print 'ND has %i unique selected events.' % len(unique_events_pass_1)
    if verbose: print 'CERN has %i unique selected events.' % len(unique_events_pass_2)
    if verbose: print 'ND and CERN have %i common events.' % len(common_events)

#     for events, unique_events, label in zip([events_pass_1, events_pass_2, events_fail_1, events_fail_2],
#                                             [unique_events_pass_1, unique_events_pass_2, set(events_fail_1), set(events_fail_2)],
#                                             ['ND selected', 'CERN selected', 'ND failed', 'CERN failed']):
    for events, unique_events, label in zip([events_pass_1, events_pass_2], [unique_events_pass_1, unique_events_pass_2], ['ND selected', 'CERN selected']):
        if len(events) != len(unique_events):
            print 'Duplicate alert!  The following %s events are repeated:' % label
            for duplicate, frequency in set([(x, events.count(x)) for x in events if events.count(x) > 1]):
                print '%s (%i times)' % (duplicate, frequency)

    tree_1_pass.SetEventList(tree_event_list_pass_1)
    tree_2_pass.SetEventList(tree_event_list_pass_2)

    histos = {}
    difference_histos = {}
    formulas = {}
    for name, options in config['histos'].items():
        formulas['%s_1' % name] = ROOT.TTreeFormula('%s_1' % name, options['first tree expression'], tree_1_all)
        formulas['%s_2' % name] = ROOT.TTreeFormula('%s_2' % name, options['second tree expression'], tree_2_all)
        title = ';%s;%s' % tuple(options['axis labels'])

        if isinstance(options['overlay plot bins'], list):
            (num_bins, x_min, x_max) = options['overlay plot bins']
        else:
            (num_bins, x_min, x_max) = (options['overlay plot bins'], -0.000001, 0.000001)
        for key in ['%s_1_pass' % name, '%s_1_fail' % name, '%s_2_pass' % name, '%s_2_fail' % name]:
            histos[key] = ROOT.TH1F(key, title, num_bins, x_min, x_max)
            if not isinstance(options['overlay plot bins'], list):
                histos[key].SetBit(ROOT.TH1.kCanRebin)

        if isinstance(options['difference plot bins'], list):
            (num_bins, x_min, x_max) = options['difference plot bins']
        else:
            (num_bins, x_min, x_max) = (options['difference plot bins'], -0.000001, 0.000001)
        difference_histos['%s_difference' % name] = ROOT.TH1F('%s_difference' % name, title, num_bins, x_min, x_max)
        if not isinstance(options['difference plot bins'], list):
            difference_histos['%s_difference' % name].SetBit(ROOT.TH1.kCanRebin)

    with open(cuts_file_label+'/pass_ND_fail_CERN.txt', 'w+') as pass_ND_fail_CERN:
        tree_1_shared_entries_by_run_lumi_event = {}
        filled = dict.fromkeys(all_events_1, False)
        filled_common = dict.fromkeys(all_events_1, False)
        for event in range(tree_event_list_all_1.GetN()):
            tree_1_all.GetEntry(tree_event_list_all_1.GetEntry(event))
            event_tuple = (str(tree_1_all.eventInfo_run), str(tree_1_all.eventInfo_lumi), str(tree_1_all.eventInfo_evt))
            if event_tuple in common_events:
                tree_1_shared_entries_by_run_lumi_event[event_tuple] = tree_event_list_all_1.GetEntry(event)
            if event_tuple in events_pass_1_fail_2 and not filled[event_tuple]:
                pass_ND_fail_CERN.write('%s:%s:%s\n' % event_tuple)
                for k in config['histos'].keys():
                    histos['%s_1_pass' % k].Fill(formulas['%s_1' % k].EvalInstance())
            if event_tuple in events_fail_1_pass_2 and not filled[event_tuple]:
                for k in config['histos'].keys():
                    print '%s_1_fail' % k, formulas['%s_1' % k].EvalInstance()
                    histos['%s_1_fail' % k].Fill(formulas['%s_1' % k].EvalInstance())
            filled[event_tuple] = True


    with open(cuts_file_label+'/fail_ND_pass_CERN.txt', 'w+') as fail_ND_pass_CERN:
        filled = dict.fromkeys(all_events_2, False)
        filled_common = dict.fromkeys(common_events, False)
        for event in range(tree_event_list_all_2.GetN()):
            tree_2_all.GetEntry(tree_event_list_all_2.GetEntry(event))
            event_tuple = (str(tree_2_pass.run), str(tree_2_pass.lumi), str(tree_2_pass.evt))
            if event_tuple in events_fail_1_pass_2 and not filled[event_tuple]:
                fail_ND_pass_CERN.write('%s:%s:%s\n' % event_tuple)
                for k in config['histos'].keys():
                    histos['%s_2_pass' % k].Fill(formulas['%s_2' % k].EvalInstance())
            if event_tuple in events_pass_1_fail_2 and not filled[event_tuple]:
                for k in config['histos'].keys():
                    histos['%s_2_fail' % k].Fill(formulas['%s_2' % k].EvalInstance())
            filled[event_tuple] = True
            if event_tuple in common_events and not filled_common[event_tuple]:
                filled_common[event_tuple] = True
                tree_1_all.GetEntry(tree_1_shared_entries_by_run_lumi_event[event_tuple])
                for k in config['histos'].keys():
                    value_1 = formulas['%s_1' % k].EvalInstance()
                    value_2 = formulas['%s_2' % k].EvalInstance()
#                    print '%s: [ND]: %f [CERN]: %f [ND-CERN]: %f' % (k, formulas['%s_1' % k].EvalInstance(), formulas['%s_2' % k].EvalInstance(), formulas['%s_1' % k].EvalInstance() - formulas['%s_2' % k].EvalInstance())
                    if ((value_1 > -99) and (value_2 > -99)):
                        difference_histos['%s_difference' % k].Fill(value_1 - value_2)

    www_directories = []
    www_base_directory = plot_helper.get_www_base_directory()
    for directory in ['CERN_ND_unique_pass', 'ND_pass_CERN_fail', 'CERN_ND_shared', 'CERN_pass_ND_fail']:
        www_directories.append(os.path.join(www_base_directory, 'CERN_ND_comparison', cuts_file_label, directory))
        if not os.path.exists(os.path.join(cuts_file_label, directory)):
            os.makedirs(os.path.join(cuts_file_label, directory))
    plot_helper.setup_www_directories(www_directories, 1, args.cuts_file_name)

    for k in config['histos'].keys():
        overlay_histos(histos['%s_1_pass' % k], 'ND pass', histos['%s_2_pass' % k], 'CERN pass', 'CERN_ND_unique_pass', k)
        overlay_histos(histos['%s_1_pass' % k], 'ND pass', histos['%s_2_fail' % k], 'CERN fail', 'ND_pass_CERN_fail', k)
        overlay_histos(histos['%s_1_fail' % k], 'ND fail', histos['%s_2_pass' % k], 'CERN pass', 'CERN_pass_ND_fail', k)

        canvas = ROOT.TCanvas()
        canvas.cd()
        difference_histo = difference_histos['%s_difference' % k]
        difference_histo.SetLineColor(ROOT.kViolet)
        difference_histo.SetLineWidth(4)
        difference_histo.SetMaximum(1.5 * difference_histo.GetMaximum())
        difference_histo.SetStats(True)
        difference_histo.Draw()
        legend_shared = ROOT.TLegend(0.2, 0.70, 0.70, 0.85)
        legend_shared.SetFillColor(ROOT.kWhite)
        legend_shared.SetBorderSize(0)
        legend_shared.SetNColumns(1)
#         if difference_histo.GetMean() == 0: legend_shared.AddEntry(difference_histo, 'Mean = 0')
#         else: legend_shared.AddEntry(difference_histo,
#                                      'Mean = %0.2fe%d' % ( difference_histo.GetMean()*pow(10,-1*math.floor(math.log10(abs(difference_histo.GetMean())))),
#                                                            int(math.floor(math.log10(abs(difference_histo.GetMean())))) )  )
#         if difference_histo.GetRMS() == 0: legend_shared.AddEntry(difference_histo, 'RMS = 0')
#         else: legend_shared.AddEntry(difference_histo,
#                                      'RMS = %0.2fe%d' % ( difference_histo.GetRMS()*pow(10,-1*math.floor(math.log10(difference_histo.GetRMS()))),
#                                                           int(math.floor(math.log10(difference_histo.GetRMS()))) )  )
        legend_shared.AddEntry(difference_histo, 'RMS = %0.3f' % difference_histo.GetRMS(), 'f')
        legend_shared.AddEntry(difference_histo, 'mean = %0.3f' % difference_histo.GetMean(), 'f')
        if difference_histo.GetMean() != 0:
            legend_shared.AddEntry(difference_histo, 'RMS/mean = %0.2f' % (difference_histo.GetRMS()/difference_histo.GetMean()), 'f')
        legend_shared.Draw('same')
        canvas.SaveAs(cuts_file_label+'/CERN_ND_shared/%s.png' % k)
        canvas.SaveAs(cuts_file_label+'/CERN_ND_shared/%s.pdf' % k)
        del canvas, difference_histo, legend_shared

        for directory in ['CERN_ND_unique_pass', 'ND_pass_CERN_fail', 'CERN_pass_ND_fail', 'CERN_pass_ND_fail', 'CERN_ND_shared']:
            plot_helper.copy_to_www_area(os.path.join(cuts_file_label, directory), os.path.join(www_base_directory, 'CERN_ND_comparison', cuts_file_label, directory), k)

    plot_helper.update_indexes('.')

    tree_file_1.Close()
    tree_file_2.Close()

def get_lists(tree, label, scan_string, cuts):
    tree.GetPlayer().SetScanRedirect(ROOT.kTRUE)
    tree.GetPlayer().SetScanFileName('%s.txt' % label)
    tree.SetScanField(0) #Allows scanning of all rows
    tree.Scan(scan_string, cuts, 'colsize=12')
    tree.Draw('>> event_list_%s' % label, cuts)
    tree_event_list = ROOT.gDirectory.Get('event_list_%s' % label)

    events = []
    with open('%s.txt' % label, 'r') as event_list_file:
        for line in event_list_file.readlines():
            match = re.search('\*\s*\d+\s\*\s*(\d+)\s\*\s*(\d+)\s\*\s*(\-*\d+)\s\*', line)
            if match:
                events.append(match.groups(0))

    return (tree_event_list, events)

def overlay_histos(hist_1, label_1, hist_2, label_2, directory, hist_name):
    hist_1.SetLineColor(ROOT.kGreen)
    hist_2.SetLineColor(ROOT.kBlue)
    hist_1.SetLineWidth(4)
    hist_2.SetLineWidth(2)

    canvas = ROOT.TCanvas()
    canvas.cd()
    hist_1.SetMaximum(1.5*max(hist_1.GetMaximum(), hist_2.GetMaximum()))
    hist_1.SetStats(False)
    hist_1.Draw()
    hist_2.Draw('same')
    legend = ROOT.TLegend(0.2, 0.7, 0.85, 0.85)
    legend.SetFillColor(ROOT.kWhite)
    legend.SetBorderSize(0)
    legend.SetNColumns(1)
    legend.AddEntry(hist_1, '%s = %0.1f' % (label_1, hist_1.Integral()), 'l')
    legend.AddEntry(hist_2, '%s = %0.1f' % (label_2, hist_2.Integral()), 'l')
    legend.Draw('same')
    canvas.SaveAs(cuts_file_label+'/%s/%s.png' % (directory, hist_name))
    canvas.SaveAs(cuts_file_label+'/%s/%s.pdf' % (directory, hist_name))
    del canvas, hist_1, hist_2, legend

if __name__ == '__main__':
    main()
