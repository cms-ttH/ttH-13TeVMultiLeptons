#!/usr/bin/env python
import os
import sys
import ROOT
from argparse import ArgumentParser

def checkDirs (inDir) :
    if not os.path.exists(inDir):
        os.mkdir(inDir)

def main ():
    parser = ArgumentParser(description='add together trees and move them to the plot making area')
    parser.add_argument('project_label', help='project label')
    parser.add_argument('-s', '--sumData', action='store_true', default=False, help='sum the data files together')
    parser.add_argument('-i', '--makeInclusive', action='store_true', default=False, help='sum all data categories together to make an inclusive data file')
    parser.add_argument('-r', '--removeDuplicates', action='store_true', default=False, help='remove duplicates when making inclusive file')
    parser.add_argument('-c', '--copyFiles', action='store_true', default=False, help='copy files to treeFile directory')
    parser.add_argument('-m', '--moveFiles', action='store_true', default=False, help='move files to treeFile directory')
    parser.add_argument('-n', '--skipHadd', action='store_true', default=False, help ='don\'t hadd stuff, just move/copy it')
    parser.add_argument('-l', '--cleanup', action='store_true', default=False, help='when summing data, remove everything except the summed file')

    args = parser.parse_args()

    ####### Hard-coded ouput directory #####
    baseDir = os.environ['CMSSW_BASE']
    outDir = baseDir +"/src/ttHMultileptonAnalysis/DrawPlots/tree_files/"

    print "Directory label %s" % args.project_label
    print "Running with sumData = %s" % args.sumData

    if not (args.skipHadd):
        print "Hadding everything together"
        for iDir in os.popen("find batch_trees -name '*_%s' -type d" % (args.project_label)  ).readlines():
            dirStrip = iDir.strip()
            print "Directory name is %s" % dirStrip
            lsCommand = "ls %s/*.root | grep -v '_all'" % dirStrip
            listOfFiles = os.popen (lsCommand).readlines()
            #print "List of files is "
            #print listOfFiles
            if len(listOfFiles) < 1:
                print "No root files... skipping %s" % dirStrip
            else:
                oldName = listOfFiles[0].strip()
                newName = oldName[:oldName.find('job')+3]+'.root'
                newName = newName.replace('job', 'all')
                if len(listOfFiles) == 1:
                    haddCommand = "cp %s %s" % ( oldName,  newName)
                else:
                    haddCommand = "hadd -v 0 -f %s " % (newName)
                    for iFile in listOfFiles[0:]:
                        haddCommand = haddCommand + " " + iFile.strip()
                for feedback in os.popen(haddCommand).readlines():
                        print feedback
                print "Created %s" % newName

    dataNames2011 = {"DoubleElectron":['DoubleElectron_Run2011A-05Aug2011-v1',
                                   'DoubleElectron_Run2011A-May10ReReco-v1',
                                   'DoubleElectron_Run2011A-PromptReco-v4',
                                   'DoubleElectron_Run2011A-PromptReco-v6',
                                   'DoubleElectron_Run2011B-PromptReco-v1'],
                 "DoubleMu":['DoubleMu_Run2011A-05Aug2011-v1',
                             'DoubleMu_Run2011A-May10ReReco-v1',
                             'DoubleMu_Run2011A-PromptReco-v4',
                             'DoubleMu_Run2011A-PromptReco-v6',
                             'DoubleMu_Run2011B-PromptReco-v1'],
                 "MuEG":['MuEG_Run2011A-05Aug2011-v1',
                         'MuEG_Run2011A-May10ReReco-v1',
                         'MuEG_Run2011A-PromptReco-v4',
                         'MuEG_Run2011A-PromptReco-v6',
                         'MuEG_Run2011B-PromptReco-v1']
                 }
    dataNames2012_52x = {"DoubleElectron":['DoubleElectron_Run2012A',
                                           'DoubleElectron_Run2012B'],
                         "DoubleMu":['DoubleMu_Run2012A',
                                     'DoubleMu_Run2012B'],
                         "MuEG":['MuEG_Run2012A',
                                 'MuEG_Run2012B']
                 }
    dataNames2012_53x = {"DoubleElectron":['DoubleElectron_Run2012A-13Jul2012-v1',
                                           'DoubleElectron_Run2012A-recover-06Aug2012-v1',
                                           'DoubleElectron_Run2012B-13Jul2012-v1',
                                           'DoubleElectron_Run2012C-PromptReco-v2',
                                           'DoubleElectron_Run2012C-24Aug2012-v1',
                                           'DoubleElectron_Run2012D-PromptReco-v1'],
                         "DoubleMu":['DoubleMu_Run2012A-13Jul2012-v1',
                                     'DoubleMu_Run2012A-recover-06Aug2012-v1',
                                     'DoubleMu_Run2012B-13Jul2012-v4',
                                     'DoubleMu_Run2012C-PromptReco-v2',
                                     'DoubleMu_Run2012C-24Aug2012-v1',
                                     'DoubleMu_Run2012D-PromptReco-v1',
                                     'DoubleMu_Run2012D-16Jan2013-v2'],
                         "MuEG":['MuEG_Run2012A-13Jul2012-v1',
                                 'MuEG_Run2012A-recover-06Aug2012-v1',
                                 'MuEG_Run2012B-13Jul2012-v1',
                                 'MuEG_Run2012C-PromptReco-v2',
                                 'MuEG_Run2012C-24Aug2012-v1',
                                 'MuEG_Run2012D-PromptReco-v1'],
                         "DoubleElectron_NP_sideband":['DoubleElectron_Run2012A-13Jul2012-v1_NP_sideband',
                                                       'DoubleElectron_Run2012A-recover-06Aug2012-v1_NP_sideband',
                                                       'DoubleElectron_Run2012B-13Jul2012-v1_NP_sideband',
                                                       'DoubleElectron_Run2012C-PromptReco-v2_NP_sideband',
                                                       'DoubleElectron_Run2012C-24Aug2012-v1_NP_sideband',
                                                       'DoubleElectron_Run2012D-PromptReco-v1_NP_sideband'],
                         "DoubleMu_NP_sideband":['DoubleMu_Run2012A-13Jul2012-v1_NP_sideband',
                                                 'DoubleMu_Run2012A-recover-06Aug2012-v1_NP_sideband',
                                                 'DoubleMu_Run2012B-13Jul2012-v4_NP_sideband',
                                                 'DoubleMu_Run2012C-PromptReco-v2_NP_sideband',
                                                 'DoubleMu_Run2012C-24Aug2012-v1_NP_sideband',
                                                 'DoubleMu_Run2012D-PromptReco-v1_NP_sideband',
                                                 'DoubleMu_Run2012D-16Jan2013-v2_NP_sideband'],
                         "MuEG_NP_sideband":['MuEG_Run2012A-13Jul2012-v1_NP_sideband',
                                             'MuEG_Run2012A-recover-06Aug2012-v1_NP_sideband',
                                             'MuEG_Run2012B-13Jul2012-v1_NP_sideband',
                                             'MuEG_Run2012C-PromptReco-v2_NP_sideband',
                                             'MuEG_Run2012C-24Aug2012-v1_NP_sideband',
                                             'MuEG_Run2012D-PromptReco-v1_NP_sideband'],
                         "DoubleElectron_QF_sideband":['DoubleElectron_Run2012A-13Jul2012-v1_QF_sideband',
                                                       'DoubleElectron_Run2012A-recover-06Aug2012-v1_QF_sideband',
                                                       'DoubleElectron_Run2012B-13Jul2012-v1_QF_sideband',
                                                       'DoubleElectron_Run2012C-PromptReco-v2_QF_sideband',
                                                       'DoubleElectron_Run2012C-24Aug2012-v1_QF_sideband',
                                                       'DoubleElectron_Run2012D-PromptReco-v1_QF_sideband'],
                         "MuEG_QF_sideband":['MuEG_Run2012A-13Jul2012-v1_QF_sideband',
                                             'MuEG_Run2012A-recover-06Aug2012-v1_QF_sideband',
                                             'MuEG_Run2012B-13Jul2012-v1_QF_sideband',
                                             'MuEG_Run2012C-PromptReco-v2_QF_sideband',
                                             'MuEG_Run2012C-24Aug2012-v1_QF_sideband',
                                             'MuEG_Run2012D-PromptReco-v1_QF_sideband']
                 }

    data_names = dataNames2012_53x

    if (args.sumData):
        print "Summing data Files"
        print "Data names are...", data_names

        for (data_category, datasets) in data_names.items():
            dataset_paths = []
            for dataset in datasets:
                labeled_dataset = '%s_%s' % (dataset, args.project_label)
                path = os.path.join('batch_trees', labeled_dataset, '%s_all.root' % labeled_dataset)
                if os.path.exists(path):
                    dataset_paths.append(path)
                else:
                    print "Could not find requested dataset %s.  It will not be included in the sum %s." % (path, data_category)

            hadd_command = "hadd -v 0 -f %s_%s_all.root %s" % (data_category, args.project_label, " ".join(dataset_paths))
            print ">>>>>>>>>> Running >>>>>>>>>  "
            print "       %s" % hadd_command
            for feedback in os.popen(hadd_command).readlines():
                print feedback
            print "-------Done summing data category %s---------" % data_category

            if args.cleanup:
                rm_command = "rm %s" % " ".join(dataset_paths)
                for feedback in os.popen(rm_command).readlines():
                    print feedback

    if args.makeInclusive:
        inclusive_data = ['%s_%s_all.root' % (f, args.project_label) for f in data_names.keys() if 'sideband' not in f]
        inclusive_data_NP_sideband = ['%s_%s_all.root' % (f, args.project_label) for f in data_names.keys() if 'NP_sideband' in f]
        inclusive_data_QF_sideband = ['%s_%s_all.root' % (f, args.project_label) for f in data_names.keys() if 'QF_sideband' in f]

        merge_trees(inclusive_data, 'inclusive_data_%s_all.root' % args.project_label)
        merge_trees(inclusive_data_NP_sideband, 'inclusive_data_NP_sideband_%s_all.root' % args.project_label)
        merge_trees(inclusive_data_QF_sideband, 'inclusive_data_QF_sideband_%s_all.root' % args.project_label)

        if args.removeDuplicates:
            remove_duplicates('inclusive_data_%s_all.root' % args.project_label)
            remove_duplicates('inclusive_data_NP_sideband_%s_all.root' % args.project_label)
            remove_duplicates('inclusive_data_QF_sideband_%s_all.root' % args.project_label)

    # make sure the destination exists before sending files
    checkDirs(outDir)

    if (args.copyFiles):
        print "Now copying results to tree files!"
        for iLine in os.popen ("find . -wholename '*%s*_all.root' -exec cp {} %s \;" % (args.project_label, outDir)):
            print iLine
        print "Done copying files"
    # end copy files

    if (args.moveFiles):
        print "Now moving results to tree files!"
        for iLine in os.popen("find . -wholename '*%s*_all.root' -exec mv {} %s \;" % (args.project_label, outDir)):
            print iLine
        print "Done moving files"
    # end move files

    print "-----Done------"

    return

def merge_trees(files, output):
    hadd_command = "hadd -v 0 -f %s %s" % (output, ' '.join(files))
    print ">>>>>>>>>> Running >>>>>>>>>  "
    print "       %s" % hadd_command
    for feedback in os.popen(hadd_command).readlines():
        print feedback
    print "-------Done making inclusive files---------"

def remove_duplicates(file):
    deduplicated_events = []
    output = file.replace('.root', '_without_duplicates_all.root')
    deduplicated_tree_file = ROOT.TFile(output, 'RECREATE')

    print 'Removing duplicates...'
    tree_file = ROOT.TFile(file)
    tree = tree_file.Get('summaryTree')
    deduplicated_tree = tree.CloneTree(0)
    deduplicated_tree.SetDirectory(deduplicated_tree_file)
    for entry in tree:
        event = (entry.eventInfo_evt, entry.eventInfo_lumi, entry.eventInfo_run)
        if not event in deduplicated_events:
            deduplicated_events.append(event)
            deduplicated_tree.Fill()

    deduplicated_tree_file.Write()
    deduplicated_tree_file.Close()
    tree_file.Close()

    print 'Done deduplicating, tree is written to %s\n' % output

# This allows you to run at the command line
# tells you to call the main function defined above
if __name__ == '__main__':
    main()
