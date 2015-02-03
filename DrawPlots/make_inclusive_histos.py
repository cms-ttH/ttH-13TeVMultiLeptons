#! /usr/bin/env python
import os
from argparse import ArgumentParser
import glob
import ROOT

parser = ArgumentParser(description=('Combine lepton categories to make an inclusive category.\n',
                                     'WARNING: there is currently no intelligent matching-- you must\n',
                                     'have exactly the same samples and jet tag categories in each lepton catgory!'))
parser.add_argument('directory', help='Histo directory to make inclusive category for.')
args = parser.parse_args()

lepton_categories = [x for x in glob.glob(os.path.join(args.directory, '*')) if 'inclusive' not in x]
file_dict = dict((lep_cat, sorted(glob.glob('%s/*.root' % lep_cat))) for lep_cat in lepton_categories)

if not os.path.exists(os.path.join(args.directory, 'inclusive')):
    os.makedirs(os.path.join(args.directory, 'inclusive'))

for files in zip(*file_dict.values()):
    head, file = os.path.split(files[0])
    base, category = os.path.split(head)
    output = os.path.join(base, 'inclusive', file.replace(category, 'inclusive'))

    command = 'hadd -f %s ' % output + ' '.join(files)
    for feedback in os.popen(command).readlines():
        print feedback


