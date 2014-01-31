##########################################################################
##Streamline event removal
##Warning (not an error in this code): CERN has some negative event numbers
###########################################################################

#!/usr/bin/env python
import re
import os
import math
import copy
from argparse import ArgumentParser
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
import ROOT
from ROOT import gStyle
from operator import itemgetter, attrgetter
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper
ROOT.gROOT.SetBatch(True)
gStyle.SetOptStat(110011)

verbose = True

if verbose: print 'Imported'

parser = ArgumentParser(description='Make histograms of events that are different between two trees.')
parser.add_argument('sample_1', help='ND sample')
parser.add_argument('sample_2', help='CERN sample')
parser.add_argument('cuts_file_name', help='File with selection cuts')

args = parser.parse_args()
config = ConfigParser()

if verbose: print 'Parsed'

#tree_file_1 = ROOT.TFile('~abrinke1/CMSSW_5_3_8_patch1/src/ttHMultileptonAnalysis/DrawPlots/tree_files/%s_SS_baseline_Jan13_all.root' % (args.sample_1) )
#tree_file_1 = ROOT.TFile('~abrinke1/CMSSW_5_3_8_patch1/src/ttHMultileptonAnalysis/DrawPlots/tree_files/%s_SS_baseline_Jan20_SS_3l_ge0j_all.root' % (args.sample_1) )
#tree_file_1 = ROOT.TFile('~awoodard/releases/CMSSW_5_3_8_patch1/src/ttHMultileptonAnalysis/DrawPlots/tree_files/%s_ss_v5_all.root' % (args.sample_1) )
#tree_file_1 = ROOT.TFile('~awoodard/releases/CMSSW_5_3_8_patch1/src/ttHMultileptonAnalysis/DrawPlots/tree_files/%s_ss_v6_all.root' % (args.sample_1) )
tree_file_1 = ROOT.TFile('~awoodard/releases/CMSSW_5_3_8_patch1/src/ttHMultileptonAnalysis/DrawPlots/tree_files/%s_ss_v12_all.root' % (args.sample_1) )
tree_1_pass = tree_file_1.Get('summaryTree')
tree_1_fail = tree_file_1.Get('summaryTree')
tree_1_shared = tree_file_1.Get('summaryTree')
tree_file_2 = ROOT.TFile('/afs/crc.nd.edu/user/a/abrinke1/CMSSW_5_3_8_patch1/src/ttHMultileptonAnalysis/TemplateMakers/bin/selection_studies_Jan15/CERN_SS_3l_skimmed_trees/TREES_250513_HADD_gpetrucc_%s.root' % (args.sample_2) )
tree_2_pass = tree_file_2.Get('ttHLepTreeProducerBase')
tree_2_fail = tree_file_2.Get('ttHLepTreeProducerBase')
tree_2_shared = tree_file_2.Get('ttHLepTreeProducerBase')

if verbose: print 'Got trees'

temp_tree_file_1_pass = ROOT.TFile('temp_tree_file_1_pass.root', 'RECREATE')
temp_tree_1_pass = tree_1_pass.CloneTree(0)
temp_tree_file_2_pass = ROOT.TFile('temp_tree_file_2_pass.root', 'RECREATE')
temp_tree_2_pass = tree_2_pass.CloneTree(0)

temp_tree_file_1_fail = ROOT.TFile('temp_tree_file_1_fail.root', 'RECREATE')
temp_tree_1_fail = tree_1_fail.CloneTree(0)
temp_tree_file_2_fail = ROOT.TFile('temp_tree_file_2_fail.root', 'RECREATE')
temp_tree_2_fail = tree_2_fail.CloneTree(0)

temp_tree_file_1_shared = ROOT.TFile('temp_tree_file_1_shared.root', 'RECREATE')
temp_tree_1_shared = tree_1_shared.CloneTree(0)
temp_tree_file_2_shared = ROOT.TFile('temp_tree_file_2_shared.root', 'RECREATE')
temp_tree_2_shared = tree_2_shared.CloneTree(0)

if verbose: print 'Made temp trees'

config.read(args.cuts_file_name)
cuts_1 = config['ND_cuts'].items()
cuts_2 = config['CERN_cuts'].items()
histos = config['histos'].items()

cuts_file_label = args.cuts_file_name.replace('.cfg','')
if not os.path.exists(cuts_file_label):
    os.makedirs(cuts_file_label)
if not os.path.exists(cuts_file_label+'/'+args.sample_1):
    os.makedirs(cuts_file_label+'/'+args.sample_1)

if verbose: print 'Got cuts'

all_cuts_1 = ROOT.TCut()
all_cuts_2 = ROOT.TCut()
for (cut_label, cut_string) in cuts_1:
    if verbose: print 'Adding ND cut_string %s' % (cut_string)
    all_cuts_1 += ROOT.TCut(cut_string)
for (cut_label, cut_string) in cuts_2:
    if verbose: print 'Adding CERN cut_string %s' % (cut_string)
    all_cuts_2 += ROOT.TCut(cut_string)

tree_1_pass.GetPlayer().SetScanRedirect(ROOT.kTRUE)
tree_1_pass.GetPlayer().SetScanFileName("output_1_pass.txt")
tree_1_pass.SetScanField(0) #Allows scanning of all rows
tree_1_pass.Scan("eventInfo_run:eventInfo_lumi:eventInfo_evt", all_cuts_1.GetTitle(), "colsize=12")
tree_1_pass.Draw(">>root_tree_event_list_pass_1", all_cuts_1.GetTitle())
tree_event_list_pass_1 = ROOT.gDirectory.Get("root_tree_event_list_pass_1")

tree_2_pass.GetPlayer().SetScanRedirect(ROOT.kTRUE)
tree_2_pass.GetPlayer().SetScanFileName("output_2_pass.txt")
tree_2_pass.SetScanField(0) #Allows scanning of all rows
tree_2_pass.Scan("run:lumi:evt", all_cuts_2.GetTitle(), "colsize=12")
tree_2_pass.Draw(">>root_tree_event_list_pass_2", all_cuts_2.GetTitle())
tree_event_list_pass_2 = ROOT.gDirectory.Get("root_tree_event_list_pass_2")

tree_1_fail.GetPlayer().SetScanRedirect(ROOT.kTRUE)
tree_1_fail.GetPlayer().SetScanFileName("output_1_fail.txt")
tree_1_fail.SetScanField(0) #Allows scanning of all rows
tree_1_fail.Scan("eventInfo_run:eventInfo_lumi:eventInfo_evt", "", "colsize=12")
tree_1_fail.Draw(">>root_tree_event_list_fail_1", "")
tree_event_list_fail_1 = ROOT.gDirectory.Get("root_tree_event_list_fail_1")

tree_2_fail.GetPlayer().SetScanRedirect(ROOT.kTRUE)
tree_2_fail.GetPlayer().SetScanFileName("output_2_fail.txt")
tree_2_fail.SetScanField(0) #Allows scanning of all rows
tree_2_fail.Scan("run:lumi:evt", "", "colsize=12")
tree_2_fail.Draw(">>root_tree_event_list_fail_2", "")
tree_event_list_fail_2 = ROOT.gDirectory.Get("root_tree_event_list_fail_2")

events_pass_1 = []
with open('output_1_pass.txt', 'r') as event_list_file:
    for line in event_list_file.readlines():
        match = re.search('\*\s*\d+\s\*\s*(\d+)\s\*\s*(\d+)\s\*\s*(\-*\d+)\s\*', line)
        if match:
            events_pass_1.append(match.groups(0))

events_pass_2 = []
with open('output_2_pass.txt', 'r') as event_list_file:
    for line in event_list_file.readlines():
        match = re.search('\*\s*\d+\s\*\s*(\d+)\s\*\s*(\d+)\s\*\s*(\-*\d+)\s\*', line)
        if match:
            events_pass_2.append(match.groups(0))
if verbose: print 'ND has '+str(len(events_pass_1))+' selected events.'
if verbose: print 'CERN has '+str(len(events_pass_2))+' selected events.'


events_pass_1 = sorted(events_pass_1, key=itemgetter(0,2))
if verbose: print 'Sorted ND selected events'
events_pass_2 =  sorted(events_pass_2, key=itemgetter(0,2))
if verbose: print 'Sorted CERN selected events'

## Duplicate check
duplicates_1 = []
last_event_1 = (0, 0, 0)
for event_1a in events_pass_1:
    if event_1a == last_event_1:
        duplicates_1.append(event_1a)
    last_event_1 = event_1a
for duplicate in duplicates_1:
    events_pass_1.remove(duplicate)
if verbose: print 'Removed '+str(len(duplicates_1))+' duplicates from ND sample'

## Duplicate check
duplicates_2 = []
last_event_2 = (0, 0, 0)
for event_2a in events_pass_2:
    if event_2a == last_event_2:
        duplicates_2.append(event_2a)
    last_event_2 = event_2a
for duplicate in duplicates_2:
    events_pass_2.remove(duplicate)
if verbose: print 'Removed '+str(len(duplicates_2))+' duplicates from CERN sample'

## Make unique lists
unique_events_pass_1 = []
non_unique_events_pass_1 = []
unique_events_pass_2 = []
non_unique_events_pass_2 = []
if verbose: print 'ND has '+str(len(events_pass_1))+' selected duplicate-removed events.'
if verbose: print 'CERN has '+str(len(events_pass_2))+' selected duplicate-removed events.'

i_1 = 0
for event_1 in events_pass_1:
    i_2 = i_1
    if i_2 >= len(events_pass_2): i_2 = len(events_pass_2) - 1
    while events_pass_2[i_2][0] <= event_1[0] and i_2 < len(events_pass_2) - 1:
        if events_pass_2[i_2][0] < event_1[0] or events_pass_2[i_2][2] < event_1[2]:
            i_2 += 1
        else: break
    while events_pass_2[i_2][0] >= event_1[0] and i_2 > 0:
        if events_pass_2[i_2][0] > event_1[0] or events_pass_2[i_2][2] > event_1[2]:
            i_2 -= 1
        else: break
    if ( event_1[0] == events_pass_2[i_2][0] and event_1[1] == events_pass_2[i_2][1] and event_1[2] == events_pass_2[i_2][2] ):
        non_unique_events_pass_1.append(event_1)
    else:
        unique_events_pass_1.append(event_1)
    i_1 += 1

i_2 = 0
for event_2 in events_pass_2:
    i_1 = i_2
    if i_1 >= len(events_pass_1): i_1 = len(events_pass_1) - 1
    while events_pass_1[i_1][0] <= event_2[0] and i_1 < len(events_pass_1) - 1:
        if events_pass_1[i_1][0] < event_2[0] or events_pass_1[i_1][2] < event_2[2]:
            i_1 += 1
        else: break
    while events_pass_1[i_1][0] >= event_2[0] and i_1 > 0:
        if events_pass_1[i_1][0] > event_2[0] or events_pass_1[i_1][2] > event_2[2]:
            i_1 -= 1
        else: break
    if ( event_2[0] == events_pass_1[i_1][0] and event_2[1] == events_pass_1[i_1][1] and event_2[2] == events_pass_1[i_1][2] ):
        non_unique_events_pass_2.append(event_2)
    else:
        unique_events_pass_2.append(event_2)
    i_2 += 1

if verbose: print 'ND has '+str(len(unique_events_pass_1))+' unique events.'
if verbose: print 'CERN has '+str(len(unique_events_pass_2))+' unique events.'
if verbose: print 'ND has '+str(len(non_unique_events_pass_1))+' non-unique events.'
if verbose: print 'CERN has '+str(len(non_unique_events_pass_2))+' non-unique events.'

tree_1_pass.SetEventList(tree_event_list_pass_1)
tree_2_pass.SetEventList(tree_event_list_pass_2)

tree_1_fail.SetEventList(tree_event_list_fail_1)
tree_2_fail.SetEventList(tree_event_list_fail_2)

temp_1a = copy.deepcopy(unique_events_pass_1) #For duplicate removal
temp_1b = copy.deepcopy(non_unique_events_pass_1) #For duplicate removal
for event in range(tree_event_list_pass_1.GetN()):
    tree_1_pass.GetEntry(tree_event_list_pass_1.GetEntry(event))
    if ( (str(tree_1_pass.eventInfo_run), str(tree_1_pass.eventInfo_lumi), str(tree_1_pass.eventInfo_evt)) in temp_1a ):
        temp_tree_1_pass.Fill()
        temp_1a.remove( (str(tree_1_pass.eventInfo_run), str(tree_1_pass.eventInfo_lumi), str(tree_1_pass.eventInfo_evt)) )
    if ( (str(tree_1_pass.eventInfo_run), str(tree_1_pass.eventInfo_lumi), str(tree_1_pass.eventInfo_evt)) in temp_1b ):
        temp_tree_1_shared.Fill()
        temp_1b.remove( (str(tree_1_pass.eventInfo_run), str(tree_1_pass.eventInfo_lumi), str(tree_1_pass.eventInfo_evt)) )

if verbose: print 'Filled tree_1 pass and shared'

temp_2a = copy.deepcopy(unique_events_pass_2) #For duplicate removal
temp_2b = copy.deepcopy(non_unique_events_pass_2) #For duplicate removal
for event in range(tree_event_list_pass_2.GetN()):
    tree_2_pass.GetEntry(tree_event_list_pass_2.GetEntry(event))
    if ( (str(tree_2_pass.run), str(tree_2_pass.lumi), str(tree_2_pass.evt)) in temp_2a ):
        temp_tree_2_pass.Fill()
        temp_2a.remove( (str(tree_2_pass.run), str(tree_2_pass.lumi), str(tree_2_pass.evt)) )
    if ( (str(tree_2_pass.run), str(tree_2_pass.lumi), str(tree_2_pass.evt)) in temp_2b ):
        temp_tree_2_shared.Fill()
        temp_2b.remove( (str(tree_2_pass.run), str(tree_2_pass.lumi), str(tree_2_pass.evt)) )

temp_tree_1_shared.BuildIndex('eventInfo_run', 'eventInfo_evt')
temp_tree_2_shared.SetAlias('eventInfo_run', 'run')
temp_tree_2_shared.SetAlias('eventInfo_evt', 'evt')
temp_tree_2_shared.BuildIndex('eventInfo_run', 'eventInfo_evt')
temp_tree_file_2_shared.Write()
temp_tree_1_shared.AddFriend('ttHLepTreeProducerBase', 'temp_tree_file_2_shared.root')

if verbose: print 'Filled tree_2 pass and shared'

ND_not_missing = open(cuts_file_label+'/'+args.sample_1+'/ND_not_missing.txt', 'w+')
tree_1_fail.BuildIndex('eventInfo_run', 'eventInfo_evt')
temp_2b = copy.deepcopy(unique_events_pass_2) #For duplicate removal
for event in unique_events_pass_2:
    tree_1_fail.GetEntryWithIndex(int(event[0]), int(event[2]))
    if tree_1_fail.eventInfo_run == int(event[0]) and tree_1_fail.eventInfo_evt == int(event[2]):
        temp_tree_1_fail.Fill()
        ND_not_missing.write('%s:%s:%s\n' % (event[0], event[1], event[2]) )
        temp_2b.remove( (event[0], event[1], event[2]) )
ND_missing = open(cuts_file_label+'/'+args.sample_1+'/ND_missing.txt', 'w+')
for event in temp_2b:
    ND_missing.write('%s:%s:%s\n' % (event[0],event[1],event[2]) )

if verbose: print 'Filled tree_1 fail'

CERN_not_missing = open(cuts_file_label+'/'+args.sample_1+'/CERN_not_missing.txt', 'w+')
tree_2_fail.BuildIndex('run', 'evt')
temp_1b = copy.deepcopy(unique_events_pass_1) #For duplicate removal
for event in unique_events_pass_1:
    tree_2_fail.GetEntryWithIndex(int(event[0]), int(event[2]))
    if tree_2_fail.run == int(event[0]) and tree_2_fail.evt == int(event[2]):
        temp_tree_2_fail.Fill()
        CERN_not_missing.write('%s:%s:%s\n' % (event[0], event[1], event[2]) )
        temp_1b.remove( (event[0], event[1], event[2]) )
CERN_missing = open(cuts_file_label+'/'+args.sample_1+'/CERN_missing.txt', 'w+')
for event in temp_1b:
    CERN_missing.write('%s:%s:%s\n' % (event[0],event[1],event[2]) )

if verbose: print 'Filled tree_2 fail'

www_base_directory = plot_helper.get_www_base_directory()
www_directories = [os.path.join(www_base_directory, 'CERN_ND_comparison', cuts_file_label, args.sample_1, dirName)
                   for dirName in ['CERN_ND_unique_pass','ND_pass_CERN_fail','CERN_pass_ND_fail','CERN_ND_shared_overlay','CERN_ND_shared'] ] 
plot_helper.setup_www_directories(www_directories, 1, args.cuts_file_name)

if not os.path.exists(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_unique_pass'):
    os.makedirs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_unique_pass')
if not os.path.exists(cuts_file_label+'/'+args.sample_1+'/plots_ND_pass_CERN_fail'):
    os.makedirs(cuts_file_label+'/'+args.sample_1+'/plots_ND_pass_CERN_fail')
if not os.path.exists(cuts_file_label+'/'+args.sample_1+'/plots_CERN_pass_ND_fail'):
    os.makedirs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_pass_ND_fail')
if not os.path.exists(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared_overlay'):
    os.makedirs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared_overlay')
if not os.path.exists(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared'):
    os.makedirs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared')

for (ND_hist, CERN_hist) in histos:

    ND_hist_name = ND_hist
    ND_hist_name = ND_hist_name.replace('(','_')
    ND_hist_name = ND_hist_name.replace(')','_')
    ND_hist_name = ND_hist_name.replace(',','_')

    nPlus = ND_hist.count('+')
    ND_hist_sub = ND_hist.split('+')
    CERN_hist_sub = CERN_hist.split('+')

    xMin_pass_pass = 0
    xMax_pass_pass = 0
    xMin_pass_fail = 0
    xMax_pass_fail = 0
    xMin_fail_pass = 0
    xMax_fail_pass = 0
    xMin_shared_overlay = 0
    xMax_shared_overlay = 0

    for i in range (nPlus+1):
        xMin_pass_pass += min(temp_tree_1_pass.GetMinimum('%s' % ND_hist_sub[i]),temp_tree_2_pass.GetMinimum('%s' % CERN_hist_sub[i]))
        xMax_pass_pass += max(temp_tree_1_pass.GetMaximum('%s' % ND_hist_sub[i]),temp_tree_2_pass.GetMaximum('%s' % CERN_hist_sub[i]))    
    if xMax_pass_pass - xMin_pass_pass == 0:
        xMin_pass_pass -= 1
        xMax_pass_pass += 1
    if xMin_pass_pass < -97:
        xMin_pass_pass = -5
    if xMax_pass_pass < -97:
        xMax_pass_pass = 5
    if xMax_pass_pass < xMin_pass_pass:
        xMin_pass_pass = xMax_pass_pass - 2*abs(xMax_pass_pass)
    mag_pass_pass = int(math.floor(math.log10(xMax_pass_pass-xMin_pass_pass)))
    if xMax_pass_pass < round(xMax_pass_pass, -mag_pass_pass): xMax_pass_pass = round(xMax_pass_pass, -mag_pass_pass)
    else: xMax_pass_pass = round(xMax_pass_pass, -mag_pass_pass)+pow(10,mag_pass_pass)
    if xMin_pass_pass > round(xMin_pass_pass, -mag_pass_pass): xMin_pass_pass = round(xMin_pass_pass, -mag_pass_pass)
    else: xMin_pass_pass = round(xMin_pass_pass, -mag_pass_pass)-pow(10,mag_pass_pass)
    #xMax_pass_pass += (xMax_pass_pass-xMin_pass_pass)/10
    #xMin_pass_pass -= (xMax_pass_pass-xMin_pass_pass)/11
    nBins_pass_pass = int(round((xMax_pass_pass-xMin_pass_pass)*pow(10,1-mag_pass_pass),-1))
    
    for i in range (nPlus+1):
        xMin_pass_fail += min(temp_tree_1_pass.GetMinimum('%s' % ND_hist_sub[i]),temp_tree_2_fail.GetMinimum('%s' % CERN_hist_sub[i]))
        xMax_pass_fail += max(temp_tree_1_pass.GetMaximum('%s' % ND_hist_sub[i]),temp_tree_2_fail.GetMaximum('%s' % CERN_hist_sub[i]))
    if xMax_pass_fail > 4*temp_tree_1_pass.GetMaximum('%s' % ND_hist_sub[i]) and 4*temp_tree_1_pass.GetMaximum('%s' % ND_hist_sub[i]) > xMin_pass_fail:
        if temp_tree_1_pass.GetMaximum('%s' % ND_hist_sub[i]) > 0:
            xMax_pass_fail = 4*temp_tree_1_pass.GetMaximum('%s' % ND_hist_sub[i])
    if xMax_pass_fail - xMin_pass_fail == 0:
        xMin_pass_fail -= 1
        xMax_pass_fail += 1
    if xMin_pass_fail < -97:
        xMin_pass_fail = -5
    if xMax_pass_fail < -97:
        xMax_pass_fail = 5
    if xMax_pass_fail < xMin_pass_fail:
        xMin_pass_fail = xMax_pass_fail - 2*abs(xMax_pass_fail)
    mag_pass_fail = int(math.floor(math.log10(xMax_pass_fail-xMin_pass_fail)))
    if xMax_pass_fail < round(xMax_pass_fail, -mag_pass_fail): xMax_pass_fail = round(xMax_pass_fail, -mag_pass_fail)
    else: xMax_pass_fail = round(xMax_pass_fail, -mag_pass_fail)+pow(10,mag_pass_fail)
    if xMin_pass_fail > round(xMin_pass_fail, -mag_pass_fail): xMin_pass_fail = round(xMin_pass_fail, -mag_pass_fail)
    else: xMin_pass_fail = round(xMin_pass_fail, -mag_pass_fail)-pow(10,mag_pass_fail)
    #xMax_pass_fail += (xMax_pass_fail-xMin_pass_fail)/10
    #xMin_pass_fail -= (xMax_pass_fail-xMin_pass_fail)/11
    nBins_pass_fail = int(round((xMax_pass_fail-xMin_pass_fail)*pow(10,1-mag_pass_fail),-1))
    
    for i in range (nPlus+1):
        xMin_fail_pass += min(temp_tree_1_fail.GetMinimum('%s' % ND_hist_sub[i]),temp_tree_2_pass.GetMinimum('%s' % CERN_hist_sub[i]))
        xMax_fail_pass += max(temp_tree_1_fail.GetMaximum('%s' % ND_hist_sub[i]),temp_tree_2_pass.GetMaximum('%s' % CERN_hist_sub[i]))
    if xMax_fail_pass > 4*temp_tree_2_pass.GetMaximum('%s' % CERN_hist_sub[i]) and 4*temp_tree_2_pass.GetMaximum('%s' % CERN_hist_sub[i]) > xMin_fail_pass:
        if temp_tree_2_pass.GetMaximum('%s' % CERN_hist_sub[i]) > 0:
            xMax_fail_pass = 4*temp_tree_2_pass.GetMaximum('%s' % CERN_hist_sub[i])
    if xMax_fail_pass - xMin_fail_pass == 0:
        xMin_fail_pass -= 1
        xMax_fail_pass += 1
    if xMin_fail_pass < -97:
        xMin_fail_pass = -5
    if xMax_fail_pass < -97:
        xMax_fail_pass = 5
    if xMax_fail_pass < xMin_fail_pass:
        xMin_fail_pass = xMax_fail_pass - 2*abs(xMax_fail_pass)
    mag_fail_pass = int(math.floor(math.log10(xMax_fail_pass-xMin_fail_pass)))
    if xMax_fail_pass < round(xMax_fail_pass, -mag_fail_pass): xMax_fail_pass = round(xMax_fail_pass, -mag_fail_pass)
    else: xMax_fail_pass = round(xMax_fail_pass, -mag_fail_pass)+pow(10,mag_fail_pass)
    if xMin_fail_pass > round(xMin_fail_pass, -mag_fail_pass): xMin_fail_pass = round(xMin_fail_pass, -mag_fail_pass)
    else: xMin_fail_pass = round(xMin_fail_pass, -mag_fail_pass)-pow(10,mag_fail_pass)
    #xMax_fail_pass += (xMax_fail_pass-xMin_fail_pass)/10
    #xMin_fail_pass -= (xMax_fail_pass-xMin_fail_pass)/11
    nBins_fail_pass = int(round((xMax_fail_pass-xMin_fail_pass)*pow(10,1-mag_fail_pass),-1))

    for i in range (nPlus+1):
        xMin_shared_overlay += min(temp_tree_1_pass.GetMinimum('%s' % ND_hist_sub[i]),temp_tree_2_pass.GetMinimum('%s' % CERN_hist_sub[i]))
        xMax_shared_overlay += max(temp_tree_1_pass.GetMaximum('%s' % ND_hist_sub[i]),temp_tree_2_pass.GetMaximum('%s' % CERN_hist_sub[i]))    
    if xMax_shared_overlay - xMin_shared_overlay == 0:
        xMin_shared_overlay -= 1
        xMax_shared_overlay += 1
    if xMin_shared_overlay < -97:
        xMin_shared_overlay = -5
    if xMax_shared_overlay < -97:
        xMax_shared_overlay = 5
    if xMax_shared_overlay < xMin_shared_overlay:
        xMin_shared_overlay = xMax_shared_overlay - 2*abs(xMax_shared_overlay)
    mag_shared_overlay = int(math.floor(math.log10(xMax_shared_overlay-xMin_shared_overlay)))
    if xMax_shared_overlay < round(xMax_shared_overlay, -mag_shared_overlay): xMax_shared_overlay = round(xMax_shared_overlay, -mag_shared_overlay)
    else: xMax_shared_overlay = round(xMax_shared_overlay, -mag_shared_overlay)+pow(10,mag_shared_overlay)
    if xMin_shared_overlay > round(xMin_shared_overlay, -mag_shared_overlay): xMin_shared_overlay = round(xMin_shared_overlay, -mag_shared_overlay)
    else: xMin_shared_overlay = round(xMin_shared_overlay, -mag_shared_overlay)-pow(10,mag_shared_overlay)
    #xMax_shared_overlay += (xMax_shared_overlay-xMin_shared_overlay)/10
    #xMin_shared_overlay -= (xMax_shared_overlay-xMin_shared_overlay)/11
    nBins_shared_overlay = int(round((xMax_shared_overlay-xMin_shared_overlay)*pow(10,1-mag_shared_overlay),-1))
    
    shared_var_name = ''
    shared_ND_name = ''
    shared_CERN_name = ''
    for i in range (nPlus+1):
        if i == 0:
            shared_var_name += '%s - %s' % (ND_hist_sub[i], CERN_hist_sub[i])
            shared_CERN_name += '%s' % (CERN_hist_sub[i])

            shared_ND_name += '%s' % (ND_hist_sub[i])
        else:
            shared_var_name += ' + %s - %s' % (ND_hist_sub[i], CERN_hist_sub[i])
            shared_CERN_name += ' + %s' % (CERN_hist_sub[i])

            shared_ND_name += ' + %s' % (ND_hist_sub[i])
    canvas_shared_temp = ROOT.TCanvas()
    canvas_shared_temp.cd()
    hist_1_shared_temp = ROOT.TH1F("hist_1_shared_temp", ND_hist, 100, -100, 100)
    temp_tree_1_shared.Draw('%s >> hist_1_shared_temp' % (shared_var_name), "%s > -97 && %s > -97" % (shared_ND_name, shared_CERN_name), "goff")
    nBins_shared = 51
    xMin_shared = hist_1_shared_temp.GetMean() - 3*hist_1_shared_temp.GetRMS()
    xMax_shared = hist_1_shared_temp.GetMean() + 3*hist_1_shared_temp.GetRMS()
    if xMin_shared == xMax_shared:
        xMin_shared -= 1.0
        xMax_shared += 1.0
    hist_1_shared_temp.Delete()
    canvas_shared_temp.Close()    


    
    canvas_pass_pass = ROOT.TCanvas()
    canvas_pass_pass.cd()
    hist_1_pass_pass = ROOT.TH1F("hist_1_pass_pass", ND_hist, nBins_pass_pass, xMin_pass_pass, xMax_pass_pass)
    hist_2_pass_pass = ROOT.TH1F("hist_2_pass_pass", CERN_hist, nBins_pass_pass, xMin_pass_pass, xMax_pass_pass)
    hist_1_pass_pass.SetLineColor(ROOT.kGreen)
    hist_2_pass_pass.SetLineColor(ROOT.kBlue)
    hist_1_pass_pass.SetLineWidth(4)
    hist_2_pass_pass.SetLineWidth(2)
    temp_tree_1_pass.Draw('%s >> hist_1_pass_pass' % (ND_hist), "", "goff")
    temp_tree_2_pass.Draw('%s >> hist_2_pass_pass' % (CERN_hist), "", "goff")
    hist_1_pass_pass.SetMaximum(1.5*max(hist_1_pass_pass.GetMaximum(),hist_2_pass_pass.GetMaximum()))
    hist_1_pass_pass.SetStats(False)
    hist_1_pass_pass.Draw()
    hist_2_pass_pass.Draw("same")    
    legend_pass_pass = ROOT.TLegend(0.15,0.7,0.85,0.85)
    legend_pass_pass.SetFillColor(ROOT.kWhite)
    legend_pass_pass.SetBorderSize(0)
    legend_pass_pass.SetNColumns(1)
    legend_pass_pass.AddEntry(hist_1_pass_pass, '%s = %0.1f' % (ND_hist,hist_1_pass_pass.Integral()), 'f')
    legend_pass_pass.AddEntry(hist_2_pass_pass, '%s = %0.1f' % (CERN_hist,hist_2_pass_pass.Integral()), 'f')
    legend_pass_pass.Draw("same")
    canvas_pass_pass.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_unique_pass/%s.png' % (ND_hist_name))
    canvas_pass_pass.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_unique_pass/%s.pdf' % (ND_hist_name))
    hist_1_pass_pass.Delete()
    hist_2_pass_pass.Delete()
    legend_pass_pass.Delete()
    canvas_pass_pass.Close()

    canvas_pass_fail = ROOT.TCanvas()
    canvas_pass_fail.cd()
    hist_1_pass_fail = ROOT.TH1F("hist_1_pass_fail", ND_hist, nBins_pass_fail, xMin_pass_fail, xMax_pass_fail)
    hist_2_pass_fail = ROOT.TH1F("hist_2_pass_fail", CERN_hist, nBins_pass_fail, xMin_pass_fail, xMax_pass_fail)
    hist_1_pass_fail.SetLineColor(ROOT.kGreen)
    hist_2_pass_fail.SetLineColor(ROOT.kRed)
    hist_1_pass_fail.SetLineWidth(4)
    hist_2_pass_fail.SetLineWidth(2)
    temp_tree_1_pass.Draw('%s >> hist_1_pass_fail' % (ND_hist), "", "goff")
    temp_tree_2_fail.Draw('%s >> hist_2_pass_fail' % (CERN_hist), "", "goff")
    hist_1_pass_fail.SetMaximum(1.5*max(hist_1_pass_fail.GetMaximum(),hist_2_pass_fail.GetMaximum()))
    hist_1_pass_fail.SetStats(False)
    hist_1_pass_fail.Draw()
    hist_2_pass_fail.Draw("same")    
    legend_pass_fail = ROOT.TLegend(0.15,0.7,0.85,0.85)
    legend_pass_fail.SetFillColor(ROOT.kWhite)
    legend_pass_fail.SetBorderSize(0)
    legend_pass_fail.SetNColumns(1)
    legend_pass_fail.AddEntry(hist_1_pass_fail, '%s = %0.1f' % (ND_hist,hist_1_pass_fail.Integral()), 'f')
    legend_pass_fail.AddEntry(hist_2_pass_fail, '%s = %0.1f' % (CERN_hist,hist_2_pass_fail.Integral()), 'f')
    legend_pass_fail.Draw("same")
    canvas_pass_fail.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_ND_pass_CERN_fail/%s.png' % (ND_hist_name))
    canvas_pass_fail.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_ND_pass_CERN_fail/%s.pdf' % (ND_hist_name))
    hist_1_pass_fail.Delete()
    hist_2_pass_fail.Delete()
    legend_pass_fail.Delete()
    canvas_pass_fail.Close()

    canvas_fail_pass = ROOT.TCanvas()
    canvas_fail_pass.cd()
    hist_1_fail_pass = ROOT.TH1F("hist_1_fail_pass", ND_hist, nBins_fail_pass, xMin_fail_pass, xMax_fail_pass)
    hist_2_fail_pass = ROOT.TH1F("hist_2_fail_pass", CERN_hist, nBins_fail_pass, xMin_fail_pass, xMax_fail_pass)
    hist_1_fail_pass.SetLineColor(ROOT.kRed)
    hist_2_fail_pass.SetLineColor(ROOT.kBlue)
    hist_1_fail_pass.SetLineWidth(4)
    hist_2_fail_pass.SetLineWidth(2)
    temp_tree_1_fail.Draw('%s >> hist_1_fail_pass' % (ND_hist), "", "goff")
    temp_tree_2_pass.Draw('%s >> hist_2_fail_pass' % (CERN_hist), "", "goff")
    hist_1_fail_pass.SetMaximum(1.5*max(hist_1_fail_pass.GetMaximum(),hist_2_fail_pass.GetMaximum()))
    hist_1_fail_pass.SetStats(False)
    hist_1_fail_pass.Draw()
    hist_2_fail_pass.Draw("same")    
    legend_fail_pass = ROOT.TLegend(0.15,0.7,0.85,0.85)
    legend_fail_pass.SetFillColor(ROOT.kWhite)
    legend_fail_pass.SetBorderSize(0)
    legend_fail_pass.SetNColumns(1)
    legend_fail_pass.AddEntry(hist_1_fail_pass, '%s = %0.1f' % (ND_hist,hist_1_fail_pass.Integral()), 'f')
    legend_fail_pass.AddEntry(hist_2_fail_pass, '%s = %0.1f' % (CERN_hist,hist_2_fail_pass.Integral()), 'f')
    legend_fail_pass.Draw("same")
    canvas_fail_pass.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_pass_ND_fail/%s.png' % (ND_hist_name))
    canvas_fail_pass.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_pass_ND_fail/%s.pdf' % (ND_hist_name))
    hist_1_fail_pass.Delete()
    hist_2_fail_pass.Delete()
    legend_fail_pass.Delete()
    canvas_fail_pass.Close()

    canvas_shared_overlay = ROOT.TCanvas()
    canvas_shared_overlay.cd()
    hist_1_shared_overlay = ROOT.TH1F("hist_1_shared_overlay", ND_hist, nBins_shared_overlay, xMin_shared_overlay, xMax_shared_overlay)
    hist_2_shared_overlay = ROOT.TH1F("hist_2_shared_overlay", CERN_hist, nBins_shared_overlay, xMin_shared_overlay, xMax_shared_overlay)
    hist_1_shared_overlay.SetLineColor(ROOT.kGreen)
    hist_2_shared_overlay.SetLineColor(ROOT.kBlue)
    hist_1_shared_overlay.SetLineWidth(4)
    hist_2_shared_overlay.SetLineWidth(2)
    temp_tree_1_shared.Draw('%s >> hist_1_shared_overlay' % (ND_hist), "", "goff")
    temp_tree_2_shared.Draw('%s >> hist_2_shared_overlay' % (CERN_hist), "", "goff")
    hist_1_shared_overlay.SetMaximum(1.5*max(hist_1_shared_overlay.GetMaximum(),hist_2_shared_overlay.GetMaximum()))
    hist_1_shared_overlay.SetStats(False)
    hist_1_shared_overlay.Draw()
    hist_2_shared_overlay.Draw("same")    
    legend_shared_overlay = ROOT.TLegend(0.15,0.7,0.85,0.85)
    legend_shared_overlay.SetFillColor(ROOT.kWhite)
    legend_shared_overlay.SetBorderSize(0)
    legend_shared_overlay.SetNColumns(1)
    legend_shared_overlay.AddEntry(hist_1_shared_overlay, '%s = %0.1f' % (ND_hist,hist_1_shared_overlay.Integral()), 'f')
    legend_shared_overlay.AddEntry(hist_2_shared_overlay, '%s = %0.1f' % (CERN_hist,hist_2_shared_overlay.Integral()), 'f')
    legend_shared_overlay.Draw("same")
    canvas_shared_overlay.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared_overlay/%s.png' % (ND_hist_name))
    canvas_shared_overlay.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared_overlay/%s.pdf' % (ND_hist_name))
    hist_1_shared_overlay.Delete()
    hist_2_shared_overlay.Delete()
    legend_shared_overlay.Delete()
    canvas_shared_overlay.Close()

    canvas_shared = ROOT.TCanvas()
    canvas_shared.cd()
    hist_1_shared = ROOT.TH1F("hist_1_shared", ND_hist, nBins_shared, xMin_shared, xMax_shared)
    hist_1_shared.SetLineColor(ROOT.kViolet)
    hist_1_shared.SetLineWidth(2)
    temp_tree_1_shared.Draw('%s >> hist_1_shared' % (shared_var_name), "", "goff")
    hist_1_shared.SetMaximum(1.5*hist_1_shared.GetMaximum())
    hist_1_shared.SetStats(True)
    hist_1_shared.Draw()
    legend_shared = ROOT.TLegend(0.15,0.70,0.70,0.85)
    legend_shared.SetFillColor(ROOT.kWhite)
    legend_shared.SetBorderSize(0)
    legend_shared.SetNColumns(1)
    if hist_1_shared.GetMean() == 0: legend_shared.AddEntry(hist_1_shared, 'Mean = 0')
    else: legend_shared.AddEntry(hist_1_shared,
                                 'Mean = %0.2fe%d' % ( hist_1_shared.GetMean()*pow(10,-1*math.floor(math.log10(abs(hist_1_shared.GetMean())))),
                                                       int(math.floor(math.log10(abs(hist_1_shared.GetMean())))) )  )
    if hist_1_shared.GetRMS() == 0: legend_shared.AddEntry(hist_1_shared, 'RMS = 0')
    else: legend_shared.AddEntry(hist_1_shared,
                                 'RMS = %0.2fe%d' % ( hist_1_shared.GetRMS()*pow(10,-1*math.floor(math.log10(hist_1_shared.GetRMS()))),
                                                      int(math.floor(math.log10(hist_1_shared.GetRMS()))) )  )
    #legend_shared.AddEntry(hist_1_shared, 'RMS = %0.5f' % (hist_1_shared.GetRMS()), 'f')
    legend_shared.Draw("same")
    canvas_shared.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared/%s.png' % (ND_hist_name))
    canvas_shared.SaveAs(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared/%s.pdf' % (ND_hist_name))
    hist_1_shared.Delete()
    legend_shared.Delete()
    canvas_shared.Close()

    plot_helper.copy_to_www_area(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_unique_pass', os.path.join(www_base_directory, 'CERN_ND_comparison', cuts_file_label, args.sample_1, 'CERN_ND_unique_pass'), ND_hist_name)
    plot_helper.copy_to_www_area(cuts_file_label+'/'+args.sample_1+'/plots_ND_pass_CERN_fail', os.path.join(www_base_directory, 'CERN_ND_comparison', cuts_file_label, args.sample_1, 'ND_pass_CERN_fail'), ND_hist_name)
    plot_helper.copy_to_www_area(cuts_file_label+'/'+args.sample_1+'/plots_CERN_pass_ND_fail', os.path.join(www_base_directory, 'CERN_ND_comparison', cuts_file_label, args.sample_1, 'CERN_pass_ND_fail'), ND_hist_name)
    plot_helper.copy_to_www_area(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared_overlay', os.path.join(www_base_directory, 'CERN_ND_comparison', cuts_file_label, args.sample_1, 'CERN_ND_shared_overlay'), ND_hist_name)
    plot_helper.copy_to_www_area(cuts_file_label+'/'+args.sample_1+'/plots_CERN_ND_shared', os.path.join(www_base_directory, 'CERN_ND_comparison', cuts_file_label, args.sample_1, 'CERN_ND_shared'), ND_hist_name)

plot_helper.update_indexes('.')

tree_file_1.Close()
tree_file_2.Close()
temp_tree_file_1_pass.Close()
temp_tree_file_2_pass.Close()
temp_tree_file_1_fail.Close()
temp_tree_file_2_fail.Close()
temp_tree_file_1_shared.Close()
temp_tree_file_2_shared.Close()
os.remove('output_1_pass.txt')
os.remove('output_2_pass.txt')
os.remove('output_1_fail.txt')
os.remove('output_2_fail.txt')
os.remove('temp_tree_file_1_pass.root')
os.remove('temp_tree_file_2_pass.root')
os.remove('temp_tree_file_1_fail.root')
os.remove('temp_tree_file_2_fail.root')
os.remove('temp_tree_file_1_shared.root')
os.remove('temp_tree_file_2_shared.root')


