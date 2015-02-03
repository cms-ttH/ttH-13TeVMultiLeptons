# #!/usr/bin/env python
# import re
# import os
# import math
# import copy
from argparse import ArgumentParser
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
# from operator import itemgetter, attrgetter
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper

#########################

import ROOT
import yaml
#from ROOT import gStyle
ROOT.gROOT.SetBatch(True)
#gStyle.SetOptStat(110011)
#gStyle.SetOptStat(000000)
import numpy
import itertools

import warnings
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter for unknown type.*' )

def main():
    parser = ArgumentParser(description='Make trees for match-making BDT.')
    parser.add_argument('config_file_name', nargs='?', default='multilepton.yaml', help='Configuration file to process.')
    parser.add_argument('-l', '--label', help='Add label to end of root file name.')
    args = parser.parse_args()

    with open(args.config_file_name) as config_file:
        config = yaml.load(config_file)

    if args.label: out_label = '_'+args.label
    else: out_label = ''
        
    input_file = ROOT.TFile(config['input file'])
    input_tree = input_file.Get('summaryTree')

    output_file_sig = ROOT.TFile(config['output file'].replace('.root', out_label+'_signal.root'), 'RECREATE')
    output_tree_sig = ROOT.TTree('summaryTree', 'summaryTree')    

    output_file_bkg = ROOT.TFile(config['output file'].replace('.root', out_label+'_background_dummy.root'), 'RECREATE')
    output_tree_bkg = ROOT.TTree('summaryTree', 'summaryTree')    

    distribution_keys = config['distributions'].keys()

    formulas_sig = {}
    formulas_bkg = {}
    branch_vals = {}
    num_bkg_vars = {}

    branch_vals['signal'] = numpy.zeros(1, dtype=int)
    branch_vals['background'] = numpy.zeros(1, dtype=int)
    output_tree_sig.Branch('signal', branch_vals['signal'], 'signal'+'/I')
    output_tree_sig.Branch('background', branch_vals['background'], 'background'+'/I')
    output_tree_bkg.Branch('signal', branch_vals['signal'], 'signal'+'/I')
    output_tree_bkg.Branch('background', branch_vals['background'], 'background'+'/I')

    base_cuts = ROOT.TCut()
    for cut_str in config['common cuts'].values():
        base_cuts += ROOT.TCut(cut_str)
    base_cuts_formula = ROOT.TTreeFormula('base_cuts_formula', str(base_cuts), input_tree)
    
#     input_tree_clone = input_tree.CloneTree(base_cuts)

    for distribution in distribution_keys:
        print 'Creating branches for '+distribution
        branch_vals[distribution] = numpy.zeros(1, dtype=float)
        output_tree_sig.Branch(distribution, branch_vals[distribution], distribution+'/D')
        output_tree_bkg.Branch(distribution, branch_vals[distribution], distribution+'/D')

        formulas_sig[distribution] = ROOT.TTreeFormula('formula_'+distribution, config['distributions'][distribution]['variables'][0], input_tree)
        formulas_bkg[distribution] = {}
        for perm in itertools.permutations([1,2,3,4,5,6], 4):
            draw_string = config['distributions'][distribution]['bkg_tree'][0]
            indices = []
            if 'WW' in draw_string: indices.append(perm[0])
            if 'XX' in draw_string: indices.append(perm[1])
            if 'YY' in draw_string: indices.append(perm[2])
            if 'ZZ' in draw_string: indices.append(perm[3])
            indices.sort()
            used_indices = 0
            if 'WW' in draw_string:
                draw_string = draw_string.replace('WW', str(indices[used_indices]))
                used_indices += 1
            if 'XX' in draw_string:
                draw_string = draw_string.replace('XX', str(indices[used_indices]))
                used_indices += 1
            if 'YY' in draw_string:
                draw_string = draw_string.replace('YY', str(indices[used_indices]))
                used_indices += 1
            if 'ZZ' in draw_string:
                draw_string = draw_string.replace('ZZ', str(indices[used_indices]))
                used_indices += 1
#             draw_string = draw_string.replace('WW', str(perm[0]))
#             draw_string = draw_string.replace('XX', str(perm[1]))
#             draw_string = draw_string.replace('YY', str(perm[2]))
#             draw_string = draw_string.replace('ZZ', str(perm[3]))
            formula_name = 'formula_%s_%d_%d_%d_%d' % (distribution, perm[0], perm[1], perm[2], perm[3])
            formulas_bkg[distribution][perm] = ROOT.TTreeFormula(formula_name, draw_string, input_tree)            

            
        if len(config['distributions'][distribution]['num_bkg_vars']) > len(num_bkg_vars):
            num_bkg_vars = config['distributions'][distribution]['num_bkg_vars']

    nEvt = 0
    nEvtK = 0
    for event in input_tree:
        if nEvt < 500000:
        #if nEvt < 5000:
            if nEvt - nEvtK*1000 == 1000:
                nEvtK += 1
                print 'About to call fill_branches for event '+str(nEvt)
            if base_cuts_formula.EvalInstance():
                fill_branches_sig(args, config, event, input_tree, output_tree_sig, formulas_sig, formulas_bkg, branch_vals, distribution_keys, num_bkg_vars)
                #fill_branches_bkg(args, config, event, input_tree, output_tree_bkg, formulas_sig, formulas_bkg, branch_vals, distribution_keys, num_bkg_vars)
            nEvt += 1
        else:
            break

    output_file_sig.Write()
    output_file_bkg.Write()
    del input_tree
    input_file.Close()
    del output_tree_sig
    output_file_sig.Close()
    output_file_bkg.Close()
        

def fill_branches_sig(args, config, event, input_tree, output_tree_sig, formulas_sig, formulas_bkg, branch_vals, distribution_keys, num_bkg_vars):

    # Fill the signal branches
    branch_vals['signal'][0] = 1
    branch_vals['background'][0] = 0
    for distribution in distribution_keys:
        branch_vals[distribution][0] = formulas_sig[distribution].EvalInstance() if abs(formulas_sig[distribution].EvalInstance()) < 9999 else -99
        #branch_vals[distribution][0] = getattr(event, config['distributions'][distribution]['variables'][0])
        #branch_vals[distribution][0] = event.numJets
    output_tree_sig.Fill()
             
def fill_branches_bkg(args, config, event, input_tree, output_tree_bkg, formulas_sig, formulas_bkg, branch_vals, distribution_keys, num_bkg_vars):

    # Fill the background branches
    sig_value = {}
    for distribution in distribution_keys:
        sig_value[distribution] = formulas_sig[distribution].EvalInstance()
    signal_test_dist = ['lepTop_jet_CSV', 'hadTop_jet_CSV', 'W_jet_1_CSV', 'W_jet_2_CSV', 'lepTop_jet_charge', 'hadTop_jet_charge', 'top_mass_lep_B', 'top_MT_met_lep_B']
    #signal_test_dist = ['']
    for perm in itertools.permutations([1,2,3,4,5,6], 4):
        isSignal = 1
        isBackground = 0
        for distribution in distribution_keys:
            bkg_value = formulas_bkg[distribution][perm].EvalInstance()
            branch_vals[distribution][0] = bkg_value if abs(bkg_value) < 9999 else -99
            #branch_vals[distribution][0] = bkg_value

            # Determine whether permutation is matched to signal permutation
            if abs(bkg_value) < 9999 and abs(sig_value[distribution]) < 9999 and distribution in signal_test_dist:
                if bkg_value != 0 and sig_value[distribution] != 0:
                    if abs(1 - (bkg_value / sig_value[distribution])) > 0.01:
                        isSignal = 0
                        isBackground = 1
            if ((abs(bkg_value) > 9999) + (abs(sig_value[distribution]) > 9999)) == 1 and distribution in signal_test_dist:
                isSignal = 0
                isBackground = 1
            if ((bkg_value == 0) + (sig_value[distribution] == 0)) == 1 and distribution in signal_test_dist:
                isSignal = 0
                isBackground = 1

        branch_vals['signal'][0] = isSignal
        branch_vals['background'][0] = isBackground
        output_tree_bkg.Fill()


if __name__ == '__main__':
    main()

