#!/usr/bin/env python
import re
from argparse import ArgumentParser
import ROOT

parser = ArgumentParser(description='Make a new tree from the tree in tree_file, which contains only those events specified in the event_list_file.')
parser.add_argument('tree_file_name', help='File with tree. Tree name is currently hardcoded as summaryTree.')
parser.add_argument('event_list_file_name', help='File with event list, in run:lumi:event format.')
args = parser.parse_args()

def get_base(string):
    if '.' in string:
        string = string[:string.rfind('.')]
    if '/' in string:
        string = string[string.find('/')+1:]
    return string

tree_file = ROOT.TFile(args.tree_file_name)
tree = tree_file.Get('summaryTree')
sub_tree_file_name = '%s_%s.root' % (get_base(args.tree_file_name), get_base(args.event_list_file_name))
sub_tree_file = ROOT.TFile(sub_tree_file_name, 'RECREATE')
sub_tree = tree.CloneTree(0)
events = []

with open(args.event_list_file_name, 'r') as event_list_file:
    for line in event_list_file.readlines():
        match = re.search('(\d*):(\d*):(\d*).*', line)
        if match:
            events.append(match.groups(0))    

for event in tree:
    if (str(event.eventInfo_run), str(event.eventInfo_lumi), str(event.eventInfo_evt)) in events:
        print 'Putting event %s into %s' % (event.eventInfo_evt, sub_tree.GetName())
        sub_tree.Fill()

sub_tree_file.Write()
sub_tree_file.Close()
