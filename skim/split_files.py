#! /usr/bin/env python
import os
import glob
import re
from argparse import ArgumentParser

parser = ArgumentParser(description='Split up files')
parser.add_argument('files', help='What to split up: if a directory is given, all files in the directory will be split up.  If a file is given, it will be split up.')
parser.add_argument('max_events', type=int, help='Maximum number of events a file can have, otherwise it will be split up')
args = parser.parse_args()

cfg_text = """
import FWCore.ParameterSet.Config as cms

process = cms.Process('Split')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.source = cms.Source('PoolSource',
                            skipEvents = cms.untracked.uint32({skip_events}),
                            fileNames = cms.untracked.vstring('file:{file_names}'))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32({max_events}))
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('{output_name}'),
                               outputCommands = cms.untracked.vstring('keep *')
                               )
process.outpath = cms.EndPath(process.out)
"""

if os.path.isdir(args.files):
    files = glob.glob(os.path.join(args.files, '*'))
else:
    files = [args.files]

regex = re.compile(".* (\d+) events.*")
for file in files:
    with os.popen('edmFileUtil %s' % file) as edm_output:
        r = regex.search(edm_output.read())
        events_in_file = int(r.groups()[0])
    if events_in_file > args.max_events:
        skip_events = 0
        index = 0
        print 'File %s has %s events; splitting it up...' % (file, events_in_file)
        while skip_events < events_in_file:
            index += 1
            output_name = os.path.basename(file).replace('.root', '_%s.root' % index)
            with open('cfg.py', 'w') as c:
                c.write(cfg_text.format(skip_events=skip_events, file_names=file, max_events=args.max_events, output_name=output_name))
            with os.popen('cmsRun cfg.py') as handle:
                print handle.read()
            skip_events += args.max_events
            os.remove('cfg.py')

        print 'File %s has been split into % files with no more than % events each. To remove the original file, use: \nrm %s' % (file, index, max_events, file)

