#! /usr/bin/env python
import os
import re
from ttHMultileptonAnalysis.DrawPlots.utilities.prettytable import *
from argparse import ArgumentParser
import ROOT

parser = ArgumentParser(description='Dump event information from a summary tree.')
parser.add_argument('tree_file_name', help='ROOT file with tree to dump.')
parser.add_argument('--event_list', action='store', help='Dump only events listed in event list.')
parser.add_argument('--branches', nargs='+')

args = parser.parse_args()
tree_file = ROOT.TFile(args.tree_file_name)
tree = tree_file.Get('summaryTree')
branches = [branch.GetName() for branch in tree.GetListOfBranches()]
if args.branches:
    branches = args.branches
dump_table = PrettyTable(branches)
dump_table.float_format = '4.2'

if args.event_list:
    selected_run_lumi_events = []
    with open(args.event_list) as event_list:
        for line in event_list:
            run_lumi_events = [entry.strip() for entry in re.split('[,:\s]', line)] #can be comma or colon delineated
            selected_run_lumi_events.append([int(entry) for entry in run_lumi_events[:3]]) #in case there are extra columns after run, lumi, event
    
for index, event in enumerate(tree):
    if index % 20000 == 0 and index != 0:
        print '%.0f%% finished...' % (float(index) / tree.GetEntries() * 100)
    if [tree.eventInfo_run, tree.eventInfo_lumi, tree.eventInfo_evt] in selected_run_lumi_events or not args.event_list:
        dump_table.add_row([getattr(tree, branch) for branch in branches])    

print 'Writing dump table...'
output_file_name = '%s_branch_value_dump.txt' % args.tree_file_name.replace('.root', '')
with open(output_file_name, 'w+') as output_file:
    output_file.write(dump_table.get_string())
        






