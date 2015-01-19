#!/usr/bin/env python
import os, sys
import re
from ttH-13TeVMultiLeptons.DrawPlots.utilities.configparser import *
from ttH-13TeVMultiLeptons.DrawPlots.utilities.ordereddict import *
from argparse import ArgumentParser
from collections import defaultdict

parser = ArgumentParser(description='Compare two event lists.')
parser.add_argument('first_file', help='First text file. Events should be in this order: run:lumi:event:anything:else:here:is:ok.  Events can also be comma delimited (run, lumi, event, anything, else) or space delimited (run lumi event anything else).')
parser.add_argument('second_file', help='Second text file.')
parser.add_argument('--cuts_file', help='Cuts file (must first run make_yields_from_tree.py)')
parser.add_argument('--nolist', action='store_true', help='Do not print lists for event overlap.')
args = parser.parse_args()

def get_events(text_file_name):
    events = {}
    with open(text_file_name, 'r') as event_list:
        lines_with_numbers = [line for line in event_list.readlines() if re.search('\d', line)]        
        for line in lines_with_numbers:
            if ',' in line or ':' in line:
                run_lumi_events = [entry.strip() for entry in re.split('[,:]', line.strip())] #can be comma or colon delimited
            else:
                run_lumi_events = [entry.strip() for entry in re.split('\w', line)]
            events[tuple(run_lumi_events[:3])] = line

    return events

def find_event_in_file(event_file_text, event):
    for line in event_file_text:
        if event in line:
            return True
    return False

event_dictionary_first_file = get_events(args.first_file)
event_dictionary_second_file = get_events(args.second_file)

event_set_first_file = set(event_dictionary_first_file.keys())
event_set_second_file = set(event_dictionary_second_file.keys())
event_set_both_files = event_set_first_file & event_set_second_file

events_in_first_missing_in_second = sorted(list(event_set_first_file - event_set_second_file))
events_in_second_missing_in_first = sorted(list(event_set_second_file - event_set_first_file))
events_in_both_files = sorted(list(event_set_both_files))

if not args.nolist:
    print '\nEvents in %s but missing in %s:' % (args.first_file, args.second_file)
    for event in events_in_first_missing_in_second:
        print event_dictionary_first_file[event]

    print '\nEvents in %s but missing in %s:' % (args.second_file, args.first_file)
    for event in events_in_second_missing_in_first:
        print event_dictionary_second_file[event]

print '\n\nNumber of unique events in file %s: %i' % (args.first_file, len(event_set_first_file))
print 'Number of unique events in file %s: %i' % (args.second_file, len(event_set_second_file))
print '\n\nNumber of events in both files: %i \nNumber of events in %s but missing in %s: %i \nNumber of events in %s but missing in %s: %i' % (len(events_in_both_files), args.first_file, args.second_file, len(events_in_first_missing_in_second), args.second_file, args.first_file, len(events_in_second_missing_in_first))

if args.cuts_file:
    cuts = ConfigParser()
    cuts.read(args.cuts_file)
    cut_labels = cuts['cuts'].keys()

    events_killed_by_cuts = defaultdict(list)
    index = 0
    event_dump_text = {}
    for cut_label in cut_labels:
        dump_file_name = 'event_dumps/event_list_%s.txt' % cut_label
        dump_file = open(dump_file_name, 'r')
        event_dump_text[cut_label] = dump_file.readlines()

    for (run, lumi, event) in events_in_first_missing_in_second:
        killing_cut = ''
        for cut_label in cut_labels:
            found = find_event_in_file(event_dump_text[cut_label], event)
            if not found:
                killing_cut = cut_label
                break

        events_killed_by_cuts[killing_cut].append((run, lumi, event))

    total = 0
    print '\nFor events in %s but missing in %s, events were lost at the following cuts:' % (args.first_file, args.second_file)
    for cut_label in cut_labels:
        total += len(events_killed_by_cuts[cut_label])
        print '\nMissing after %s:' % cut_label
        if len(events_killed_by_cuts[cut_label]) > 0:
            with open('missing_after_%s.txt' % cut_label, 'w+') as output_file:
                for (run, lumi, event) in events_killed_by_cuts[cut_label]:
                    print event_dictionary_first_file[(run, lumi, event)]
                    output_file.write(event_dictionary_first_file[(run, lumi, event)]+'\n')

    print '\nTotal missing events accounted for: ', total
