#! /usr/bin/env python
import optparse
import os
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
from ttHMultileptonAnalysis.DrawPlots.utilities.ordereddict import *
from ttHMultileptonAnalysis.DrawPlots.utilities.prettytable import *
from argparse import ArgumentParser
import ROOT

parser = ArgumentParser(description='Dump events from summary trees and make a yield table.')
parser.add_argument('config_file_name', help='Configuration file to process.')
parser.add_argument('tree_file_name', help='ROOT file with tree to dump.')

if not os.path.exists('event_dumps'):
        os.makedirs('event_dumps')
        
args = parser.parse_args()
config = ConfigParser()
config.read(args.config_file_name)
tree_file = ROOT.TFile(args.tree_file_name)
labels_and_cut_strings = config['cuts'].items()
yields = OrderedDict()

tree = tree_file.Get("summaryTree")

all_cuts = ROOT.TCut()
index = 0
for (cut_label, cut_string) in labels_and_cut_strings:
    print "Evaluating yields for cut: %s..." % cut_label
    index += 1
    cut = ROOT.TCut(cut_string)
    all_cuts += cut
    tree.Draw(">>event_list_%s" % cut_label, all_cuts.GetTitle())
    list = ROOT.gDirectory.Get("event_list_%s" % cut_label)
    yields[cut_label] = int(list.GetN())
    output_file_name = "event_dumps/event_list_%s.txt" % cut_label
    output_file = open(output_file_name, 'w')

    for event in range(list.GetN()):
        tree.GetEntry(list.GetEntry(event))
        output_line = "%i:%i:%i:%.4f:%.4f:%.4f:%.2f:%i:%.2f:%.2f:%.2f:%.2f:%.2f:%.2f:%.2f\n" % (tree.eventInfo_run, tree.eventInfo_lumi, tree.eventInfo_evt, tree.preselected_leptons_by_pt_1_lepMVA, tree.preselected_leptons_by_pt_2_lepMVA, tree.met_ld, tree.met_pt, tree.numJets, tree.jets_by_pt_1_pt, tree.jets_by_pt_2_pt, tree.jets_by_pt_3_pt, tree.jets_by_pt_4_pt, tree.jets_by_pt_4_pt, tree.jets_by_pt_5_pt, tree.jets_by_pt_6_pt)
        output_line = output_line.replace("-899999982852417519616.00", "-99.00")
        output_file.write(output_line)

    output_file.close()

yield_table = PrettyTable(['cut', 'yield'])
for cut_label, cut_yield in yields.items():
    yield_table.add_row([cut_label, cut_yield])

print yield_table






