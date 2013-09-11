#! /usr/bin/env python
import optparse
import os
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
from ttHMultileptonAnalysis.DrawPlots.utilities.ordereddict import *
from ttHMultileptonAnalysis.DrawPlots.utilities.prettytable import *
from argparse import ArgumentParser
import ROOT

parser = ArgumentParser(description='Dump events from summary trees and make a yield table.')
parser.add_argument('cuts_file_name', help='Cuts file to process.')
parser.add_argument('tree_file_name', help='ROOT file with tree to dump.')
parser.add_argument('--no_lists', action='store_true', help='Do not make a list of run:lumi:event:... information for events passing each cut. (Speeds up yield-table making.)')

if not os.path.exists('event_dumps'):
        os.makedirs('event_dumps')
        
args = parser.parse_args()
config = ConfigParser()
config.read(args.cuts_file_name)
tree_file = ROOT.TFile(args.tree_file_name)
labels_and_cut_strings = config['cuts'].items()
yields = OrderedDict()
tree = tree_file.Get('summaryTree')

all_cuts = ROOT.TCut()
for (cut_label, cut_string) in labels_and_cut_strings:
    print "Evaluating yields for cut: %s..." % cut_label
    all_cuts += ROOT.TCut(cut_string)
    tree.Draw(">>event_list_%s" % cut_label, all_cuts.GetTitle())
    event_list = ROOT.gDirectory.Get("event_list_%s" % cut_label)
    yields[cut_label] = int(event_list.GetN())
    output_file_name = "event_dumps/event_list_%s.txt" % cut_label
    tree.SetEventList(event_list)
    if not args.no_lists:
        with open(output_file_name, 'w') as output_file:
            for event in range(event_list.GetN()):
                tree.GetEntry(event_list.GetEntry(event))
                output_line = "%i:%i:%i:%.4f:%.4f:%.4f:%.2f:%i:%.2f:%.2f:%.2f:%.2f:%.2f:%.2f:%.2f\n" % (tree.eventInfo_run, tree.eventInfo_lumi, tree.eventInfo_evt, tree.all_leptons_by_pt_1_lepMVA, tree.all_leptons_by_pt_2_lepMVA, tree.met_ld, tree.met_pt, tree.numJets, tree.jets_by_pt_1_pt, tree.jets_by_pt_2_pt, tree.jets_by_pt_3_pt, tree.jets_by_pt_4_pt, tree.jets_by_pt_4_pt, tree.jets_by_pt_5_pt, tree.jets_by_pt_6_pt)        
                output_line = output_line.replace("-899999982852417519616.00", "-99.00")
                output_file.write(output_line)
            
yield_table = PrettyTable(['cut', 'yield'])
for cut_label, cut_yield in yields.items():
    yield_table.add_row([cut_label, cut_yield])

print yield_table






