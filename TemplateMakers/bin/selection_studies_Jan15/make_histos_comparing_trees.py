##################################################
##Make plots with unique events which did NOT pass
##################################################

#!/usr/bin/env python
import re
import os
from argparse import ArgumentParser
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
import ROOT
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper
ROOT.gROOT.SetBatch(True)

verbose = True

if verbose: print 'Imported'

parser = ArgumentParser(description='Make histograms of events that are different between two trees.')
parser.add_argument('sample_1', help='ND sample')
parser.add_argument('sample_2', help='CERN sample')
parser.add_argument('cuts_file_name', help='File with selection cuts')

args = parser.parse_args()
config = ConfigParser()

if verbose: print 'Parsed'

tree_file_1 = ROOT.TFile('/afs/crc.nd.edu/user/a/abrinke1/CMSSW_5_3_8_patch1/src/ttHMultileptonAnalysis/DrawPlots/tree_files/%s_SS_baseline_Jan13_all.root' % (args.sample_1) )
tree_1_pass = tree_file_1.Get('summaryTree')
tree_1_fail = tree_file_1.Get('summaryTree')
tree_file_2 = ROOT.TFile('/afs/crc.nd.edu/user/a/abrinke1/CMSSW_5_3_8_patch1/src/ttHMultileptonAnalysis/TemplateMakers/bin/selection_studies_Jan15/CERN_SS_3l_skimmed_trees/TREES_250513_HADD_gpetrucc_%s.root' % (args.sample_2) )
tree_2_pass = tree_file_2.Get('ttHLepTreeProducerBase')
tree_2_fail = tree_file_2.Get('ttHLepTreeProducerBase')

if verbose: print 'Got trees'

temp_tree_file_1_pass = ROOT.TFile('temp_tree_file_1_pass.root', 'RECREATE')
temp_tree_1_pass = tree_1_pass.CloneTree(0)
temp_tree_file_2_pass = ROOT.TFile('temp_tree_file_2_pass.root', 'RECREATE')
temp_tree_2_pass = tree_2_pass.CloneTree(0)

temp_tree_file_1_fail = ROOT.TFile('temp_tree_file_1_fail.root', 'RECREATE')
temp_tree_1_fail = tree_1_fail.CloneTree(0)
temp_tree_file_2_fail = ROOT.TFile('temp_tree_file_2_fail.root', 'RECREATE')
temp_tree_2_fail = tree_2_fail.CloneTree(0)

if verbose: print 'Made temp trees'

config.read(args.cuts_file_name)
cuts_1 = config['ND_cuts'].items()
cuts_2 = config['CERN_cuts'].items()
histos = config['histos'].items()

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
tree_1_pass.Scan("eventInfo_run:eventInfo_lumi:eventInfo_evt", all_cuts_1.GetTitle(), "colsize=11")
tree_1_pass.Draw(">>root_tree_event_list_pass_1", all_cuts_1.GetTitle())
tree_event_list_pass_1 = ROOT.gDirectory.Get("root_tree_event_list_pass_1")

tree_2_pass.GetPlayer().SetScanRedirect(ROOT.kTRUE)
tree_2_pass.GetPlayer().SetScanFileName("output_2_pass.txt")
tree_2_pass.SetScanField(0) #Allows scanning of all rows
tree_2_pass.Scan("run:lumi:evt", all_cuts_2.GetTitle(), "colsize=11")
tree_2_pass.Draw(">>root_tree_event_list_pass_2", all_cuts_2.GetTitle())
tree_event_list_pass_2 = ROOT.gDirectory.Get("root_tree_event_list_pass_2")

tree_1_fail.GetPlayer().SetScanRedirect(ROOT.kTRUE)
tree_1_fail.GetPlayer().SetScanFileName("output_1_fail.txt")
tree_1_fail.SetScanField(0) #Allows scanning of all rows
tree_1_fail.Scan("eventInfo_run:eventInfo_lumi:eventInfo_evt", "", "colsize=11")
tree_1_fail.Draw(">>root_tree_event_list_fail_1", "")
tree_event_list_fail_1 = ROOT.gDirectory.Get("root_tree_event_list_fail_1")

tree_2_fail.GetPlayer().SetScanRedirect(ROOT.kTRUE)
tree_2_fail.GetPlayer().SetScanFileName("output_2_fail.txt")
tree_2_fail.SetScanField(0) #Allows scanning of all rows
tree_2_fail.Scan("run:lumi:evt", "", "colsize=11")
tree_2_fail.Draw(">>root_tree_event_list_fail_2", "")
tree_event_list_fail_2 = ROOT.gDirectory.Get("root_tree_event_list_fail_2")

events_pass_1 = []
with open('output_1_pass.txt', 'r') as event_list_file:
	for line in event_list_file.readlines():
		match = re.search('\*\s*\d+\s\*\s*(\d+)\s\*\s*(\d+)\s\*\s*(\d+)\s\*', line)
		if match:
			events_pass_1.append(match.groups(0))

events_pass_2 = []
with open('output_2_pass.txt', 'r') as event_list_file:
	for line in event_list_file.readlines():
		match = re.search('\*\s*\d+\s\*\s*(\d+)\s\*\s*(\d+)\s\*\s*(\d+)\s\*', line)
		if match:
			events_pass_2.append(match.groups(0))

## Duplicate check
duplicates_1 = []
for event_1a in events_pass_1:
	num_duplicates = -1
	for event_1b in events_pass_1:
		if ( event_1a[0] == event_1b[0] and event_1a[1] == event_1b[1] and event_1a[2] == event_1b[2] ):
			num_duplicates += 1
			if (num_duplicates == 1 and not event_1b in duplicates_1) or num_duplicates > 1:
				if verbose: print "DUPLICATE ALERT! Event"
				if verbose: print str(event_1a[0])+', '+str(event_1a[1])+', '+str(event_1a[2])
				if verbose: print 'in ND sample has a duplicate.  Removing.'
				duplicates_1.append(event_1b)
for duplicate in duplicates_1:
	events_pass_1.remove(duplicate)

duplicates_2 = []
for event_2a in events_pass_2:
	num_duplicates = -1
	for event_2b in events_pass_2:
		if ( event_2a[0] == event_2b[0] and event_2a[1] == event_2b[1] and event_2a[2] == event_2b[2] ):
			num_duplicates += 1
			if (num_duplicates == 1 and not event_2b in duplicates_2) or num_duplicates > 1:
				if verbose: print "DUPLICATE ALERT! Event"
				if verbose: print str(event_2a[0])+', '+str(event_2a[1])+', '+str(event_2a[2])
				if verbose: print 'in CERN sample has a duplicate.  Removing.'
				duplicates_2.append(event_2b)
for duplicate in duplicates_2:
	events_pass_2.remove(duplicate)
		
## Make unique lists
unique_events_pass_1 = []
non_unique_events_pass_1 = []
if verbose: print 'ND has '+str(len(events_pass_1))+' selected events.'
if verbose: print 'CERN has '+str(len(events_pass_2))+' selected events.'
for event_1 in events_pass_1:
	is_unique = True
	for event_2 in events_pass_2:
		if ( event_1[0] == event_2[0] and event_1[1] == event_2[1] and event_1[2] == event_2[2] ):
			is_unique = False
			non_unique_events_pass_1.append(event_1)
			#break
	if is_unique:
		unique_events_pass_1.append(event_1)
	
unique_events_pass_2 = []
non_unique_events_pass_2 = []
for event_2 in events_pass_2:
	is_unique = True
	for event_1 in events_pass_1:
		if ( event_1[0] == event_2[0] and event_1[1] == event_2[1] and event_1[2] == event_2[2] ):
			is_unique = False
			non_unique_events_pass_2.append(event_2)
			#break
	if is_unique:
		unique_events_pass_2.append(event_2)

if verbose: print 'ND has '+str(len(unique_events_pass_1))+' unique events.'
if verbose: print 'CERN has '+str(len(unique_events_pass_2))+' unique events.'
if verbose: print 'ND has '+str(len(non_unique_events_pass_1))+' non-unique events.'
if verbose: print 'CERN has '+str(len(non_unique_events_pass_2))+' non-unique events.'

tree_1_pass.SetEventList(tree_event_list_pass_1)
tree_2_pass.SetEventList(tree_event_list_pass_2)

tree_1_fail.SetEventList(tree_event_list_fail_1)
tree_2_fail.SetEventList(tree_event_list_fail_2)

for event in range(tree_event_list_pass_1.GetN()):
	tree_1_pass.GetEntry(tree_event_list_pass_1.GetEntry(event))
	if ( (str(tree_1_pass.eventInfo_run), str(tree_1_pass.eventInfo_lumi), str(tree_1_pass.eventInfo_evt)) in unique_events_pass_1 ):
		temp_tree_1_pass.Fill()

if verbose: temp_tree_1_pass.Scan("eventInfo_run:eventInfo_lumi:eventInfo_evt","","")

for event in range(tree_event_list_pass_2.GetN()):
	tree_2_pass.GetEntry(tree_event_list_pass_2.GetEntry(event))
	if ( (str(tree_2_pass.run), str(tree_2_pass.lumi), str(tree_2_pass.evt)) in unique_events_pass_2 ):
		temp_tree_2_pass.Fill()

if verbose: temp_tree_2_pass.Scan("run:lumi:evt","","")

for event in range(tree_event_list_fail_1.GetN()):
	tree_1_fail.GetEntry(tree_event_list_fail_1.GetEntry(event))
	if ( (str(tree_1_fail.eventInfo_run), str(tree_1_fail.eventInfo_lumi), str(tree_1_fail.eventInfo_evt)) in unique_events_pass_2 ):
		temp_tree_1_fail.Fill()

if verbose: temp_tree_1_fail.Scan("eventInfo_run:eventInfo_lumi:eventInfo_evt","","")

for event in range(tree_event_list_fail_2.GetN()):
	tree_2_fail.GetEntry(tree_event_list_fail_2.GetEntry(event))
	if ( (str(tree_2_fail.run), str(tree_2_fail.lumi), str(tree_2_fail.evt)) in unique_events_pass_1 ):
		temp_tree_2_fail.Fill()

if verbose: temp_tree_2_fail.Scan("run:lumi:evt","","")

www_base_directory = plot_helper.get_www_base_directory()
www_directories = [os.path.join(www_base_directory, 'CERN_ND_comparison', dirName)
				   for dirName in ['CERN_ND_unique_pass','ND_pass_CERN_fail','CERN_pass_ND_fail'] ] 
plot_helper.setup_www_directories(www_directories, 1)

if not os.path.exists('plots_CERN_ND_unique_pass'):
	os.makedirs('plots_CERN_ND_unique_pass')
if not os.path.exists('plots_ND_pass_CERN_fail'):
	os.makedirs('plots_ND_pass_CERN_fail')
if not os.path.exists('plots_CERN_pass_ND_fail'):
	os.makedirs('plots_CERN_pass_ND_fail')
			
nBins = 30
for (ND_hist, CERN_hist) in histos:
	if verbose: print ND_hist

	xMin_pass_pass = min(temp_tree_1_pass.GetMinimum('%s' % ND_hist),temp_tree_2_pass.GetMinimum('%s' % CERN_hist))
	xMax_pass_pass = max(temp_tree_1_pass.GetMaximum('%s' % ND_hist),temp_tree_2_pass.GetMaximum('%s' % CERN_hist))
	xMin_pass_pass -= max( 0.1*(xMax_pass_pass - xMin_pass_pass), 0.1*abs(xMin_pass_pass) )
	xMax_pass_pass += max( 0.1*(xMax_pass_pass - xMin_pass_pass), 0.1*abs(xMax_pass_pass) )
	if xMin_pass_pass == 0 and xMax_pass_pass == 0:
		xMin_pass_pass = -1
		xMax_pass_pass = 1
	
	xMin_pass_fail = min(temp_tree_1_pass.GetMinimum('%s' % ND_hist),temp_tree_2_fail.GetMinimum('%s' % CERN_hist))
	xMax_pass_fail = max(temp_tree_1_pass.GetMaximum('%s' % ND_hist),temp_tree_2_fail.GetMaximum('%s' % CERN_hist))
	xMin_pass_fail -= max( 0.1*(xMax_pass_fail - xMin_pass_fail), 0.1*abs(xMin_pass_fail) )
	xMax_pass_fail += max( 0.1*(xMax_pass_fail - xMin_pass_fail), 0.1*abs(xMax_pass_fail) )
	if xMin_pass_fail == 0 and xMax_pass_fail == 0:
		xMin_pass_fail = -1
		xMax_pass_fail = 1
	
	xMin_fail_pass = min(temp_tree_1_fail.GetMinimum('%s' % ND_hist),temp_tree_2_pass.GetMinimum('%s' % CERN_hist))
	xMax_fail_pass = max(temp_tree_1_fail.GetMaximum('%s' % ND_hist),temp_tree_2_pass.GetMaximum('%s' % CERN_hist))
	xMin_fail_pass -= max( 0.1*(xMax_fail_pass - xMin_fail_pass), 0.1*abs(xMin_fail_pass) )
	xMax_fail_pass += max( 0.1*(xMax_fail_pass - xMin_fail_pass), 0.1*abs(xMax_fail_pass) )
	if xMin_fail_pass == 0 and xMax_fail_pass == 0:
		xMin_fail_pass = -1
		xMax_fail_pass = 1
	
	canvas_pass_pass = ROOT.TCanvas()
	canvas_pass_pass.cd()
	hist_1_pass_pass = ROOT.TH1F("hist_1_pass_pass", ND_hist, nBins, xMin_pass_pass, xMax_pass_pass)
	hist_2_pass_pass = ROOT.TH1F("hist_2_pass_pass", CERN_hist, nBins, xMin_pass_pass, xMax_pass_pass)
	hist_1_pass_pass.SetLineColor(ROOT.kGreen)
	hist_2_pass_pass.SetLineColor(ROOT.kBlue)
	hist_1_pass_pass.SetLineWidth(4)
	hist_2_pass_pass.SetLineWidth(2)
	temp_tree_1_pass.Draw('%s >> hist_1_pass_pass' % (ND_hist), "", "goff")
	temp_tree_2_pass.Draw('%s >> hist_2_pass_pass' % (CERN_hist), "", "goff")
	hist_1_pass_pass.SetMaximum(1.5*max(hist_1_pass_pass.GetMaximum(),hist_2_pass_pass.GetMaximum()))
	hist_1_pass_pass.Draw()
	hist_2_pass_pass.Draw("same")	
	canvas_pass_pass.SaveAs('plots_CERN_ND_unique_pass/%s.png' % (ND_hist))
	canvas_pass_pass.SaveAs('plots_CERN_ND_unique_pass/%s.pdf' % (ND_hist))
	hist_1_pass_pass.Delete()
	hist_2_pass_pass.Delete()

	canvas_pass_fail = ROOT.TCanvas()
	canvas_pass_fail.cd()
	hist_1_pass_fail = ROOT.TH1F("hist_1_pass_fail", ND_hist, nBins, xMin_pass_fail, xMax_pass_fail)
	hist_2_pass_fail = ROOT.TH1F("hist_2_pass_fail", CERN_hist, nBins, xMin_pass_fail, xMax_pass_fail)
	hist_1_pass_fail.SetLineColor(ROOT.kGreen)
	hist_2_pass_fail.SetLineColor(ROOT.kRed)
	hist_1_pass_fail.SetLineWidth(4)
	hist_2_pass_fail.SetLineWidth(2)
	temp_tree_1_pass.Draw('%s >> hist_1_pass_fail' % (ND_hist), "", "goff")
	temp_tree_2_fail.Draw('%s >> hist_2_pass_fail' % (CERN_hist), "", "goff")
	hist_1_pass_fail.SetMaximum(1.5*max(hist_1_pass_fail.GetMaximum(),hist_2_pass_fail.GetMaximum()))
	hist_1_pass_fail.Draw()
	hist_2_pass_fail.Draw("same")	
	canvas_pass_fail.SaveAs('plots_ND_pass_CERN_fail/%s.png' % (ND_hist))
	canvas_pass_fail.SaveAs('plots_ND_pass_CERN_fail/%s.pdf' % (ND_hist))
	hist_1_pass_fail.Delete()
	hist_2_pass_fail.Delete()

	canvas_fail_pass = ROOT.TCanvas()
	canvas_fail_pass.cd()
	hist_1_fail_pass = ROOT.TH1F("hist_1_fail_pass", ND_hist, nBins, xMin_fail_pass, xMax_fail_pass)
	hist_2_fail_pass = ROOT.TH1F("hist_2_fail_pass", CERN_hist, nBins, xMin_fail_pass, xMax_fail_pass)
	hist_1_fail_pass.SetLineColor(ROOT.kRed)
	hist_2_fail_pass.SetLineColor(ROOT.kBlue)
	hist_1_fail_pass.SetLineWidth(4)
	hist_2_fail_pass.SetLineWidth(2)
	temp_tree_1_fail.Draw('%s >> hist_1_fail_pass' % (ND_hist), "", "goff")
	temp_tree_2_pass.Draw('%s >> hist_2_fail_pass' % (CERN_hist), "", "goff")
	hist_1_fail_pass.SetMaximum(1.5*max(hist_1_fail_pass.GetMaximum(),hist_2_fail_pass.GetMaximum()))
	hist_1_fail_pass.Draw()
	hist_2_fail_pass.Draw("same")	
	canvas_fail_pass.SaveAs('plots_CERN_pass_ND_fail/%s.png' % (ND_hist))
	canvas_fail_pass.SaveAs('plots_CERN_pass_ND_fail/%s.pdf' % (ND_hist))
	hist_1_fail_pass.Delete()
	hist_2_fail_pass.Delete()

	plot_helper.copy_to_www_area('plots_CERN_ND_unique_pass', os.path.join(www_base_directory, 'CERN_ND_comparison', 'CERN_ND_unique_pass'), ND_hist)
	plot_helper.copy_to_www_area('plots_ND_pass_CERN_fail', os.path.join(www_base_directory, 'CERN_ND_comparison', 'ND_pass_CERN_fail'), ND_hist)
	plot_helper.copy_to_www_area('plots_CERN_pass_ND_fail', os.path.join(www_base_directory, 'CERN_ND_comparison', 'CERN_pass_ND_fail'), ND_hist)

plot_helper.update_indexes('.')

tree_file_1.Close()
tree_file_2.Close()
temp_tree_file_1_pass.Close()
temp_tree_file_2_pass.Close()
temp_tree_file_1_fail.Close()
temp_tree_file_2_fail.Close()
os.remove('output_1_pass.txt')
os.remove('output_2_pass.txt')
os.remove('output_1_fail.txt')
os.remove('output_2_fail.txt')
os.remove('temp_tree_file_1_pass.root')
os.remove('temp_tree_file_2_pass.root')
os.remove('temp_tree_file_1_fail.root')
os.remove('temp_tree_file_2_fail.root')



