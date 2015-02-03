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
#import numpy

def main():
    parser = ArgumentParser(description='Make plots from summary trees.')
    parser.add_argument('config_file_name', nargs='?', default='multilepton.yaml', help='Configuration file to process.')
    args = parser.parse_args()

    with open(args.config_file_name) as config_file:
        config = yaml.load(config_file)

    input_file = ROOT.TFile(config['input file'])
    output_file = ROOT.TFile(config['output file'], 'RECREATE')
    tree = input_file.Get('summaryTree')

    distribution_keys = config['distributions'].keys()

    for distribution in distribution_keys:
        draw_histos(args, config, distribution, tree, output_file)

    for distribution in distribution_keys:
        draw_probs(args, config, distribution, output_file)
        
    for distribution in distribution_keys:
        draw_corrs(args, config, distribution, tree, output_file)
        
    del tree
    input_file.Close()
        

def draw_histos(args, config, distribution, tree, output_file):

    print 'inside draw_histos with '+distribution

    nBins = config['num bins']
    xMin = config['distributions'][distribution]['min']
    xMax = config['distributions'][distribution]['max']
    vars = config['distributions'][distribution]['variables']

    base_cuts = config.get('common cuts', {}).values()
    dist_cuts = config['distributions'][distribution].get('cuts', {}).values()
    sel_strings = {}
    for var in vars:
        #print var
        sel_strings[var] = plot_helper.DrawStringMaker()
        if var in config['special cuts'].keys():
            sel_strings[var].append_selection_requirements(base_cuts, dist_cuts, config['special cuts'].get(var, {}).values())
        else:
            sel_strings[var].append_selection_requirements(base_cuts, dist_cuts)
        #print sel_strings[var].draw_string

    #output_file.cd()
    canvas = ROOT.TCanvas('hist '+distribution, 'hist '+distribution)
    hist = ROOT.TH1D('hist_'+distribution, 'hist_'+distribution, nBins, xMin, xMax)

    tree.Draw(vars[0]+' >> hist_'+distribution, sel_strings[vars[0]].draw_string, '')
    for var in vars:
        if not var == vars[0]:
            tree.Draw(var+' >>+ hist_'+distribution, sel_strings[var].draw_string, '')

    hist.SetDirectory(output_file)
    hist.Write()
    #output_file.Write()
    del hist
    del canvas

def draw_probs(args, config, distribution, output_file):

    print 'inside draw_probs with '+distribution

    hist = output_file.Get('hist_'+distribution)
    
    nBins = config['num bins']
    xMin = config['distributions'][distribution]['min']
    xMax = config['distributions'][distribution]['max']
    bin_width = (xMax - xMin) / nBins
    target = config['distributions'][distribution]['target']
    
    prob = ROOT.TH1D('prob_'+distribution, 'prob_'+distribution, nBins, xMin, xMax)

    if target == 'max':
        integral = hist.Integral(0, nBins+1)
        product = 0
        for i in range(nBins):
            if i+1 < nBins:
                prob.SetBinContent(i+1, hist.Integral(0,i+1))
                product += hist.GetBinContent(i+1)*hist.Integral(0,i+1)
            else:
                prob.SetBinContent(i+1, hist.Integral(0,nBins+1))
                product += hist.GetBinContent(i+1)*hist.Integral(0,nBins+1)
        prob.Scale(integral/product)

    elif target == 'min':
        integral = hist.Integral(0, nBins+1)
        product = 0
        for i in range(nBins):
            if i+1 > 1:
                prob.SetBinContent(i+1, hist.Integral(i+1,nBins+1))
                product += hist.GetBinContent(i+1)*hist.Integral(i+1,nBins+1)
            else:
                prob.SetBinContent(i+1, hist.Integral(0,nBins+1))
                product += hist.GetBinContent(i+1)*hist.Integral(0,nBins+1)
        prob.Scale(integral/product)
            
    else:
        bin_down = hist.FindBin(target - 0.5*bin_width)
        bin_up = hist.FindBin(target + 0.5*bin_width)
        integral_down = hist.Integral(0, bin_down)
        integral_up = hist.Integral(bin_up, nBins+1)
        product_down = 0
        product_up = 0
        for i in range(nBins):
            if i+1 <= bin_down:
                prob.SetBinContent(i+1, hist.Integral(0,i+1))
                product_down += hist.GetBinContent(i+1)*hist.Integral(0,i+1)
            else:
                prob.SetBinContent(i+1, hist.Integral(i+1, nBins+1))
                product_up += hist.GetBinContent(i+1)*hist.Integral(i+1, nBins+1)
        #prob.Scale((integral_up+integral_down)/(product_up+product_down))
        #print 'integral_down/product_down = '+str(integral_down/product_down)
        #print 'integral_up/product_up = '+str(integral_up/product_up)
        #print '(integral_up+integral_down)/(product_up+product_down) = '+str((integral_up+integral_down)/(product_up+product_down))

        for i in range(nBins):
            if i+1 <= bin_down:
                prob.SetBinContent(i+1, prob.GetBinContent(i+1)*(integral_down/product_down))
            else:
                prob.SetBinContent(i+1, prob.GetBinContent(i+1)*(integral_up/product_up))

    #output_file.cd()
    canvas = ROOT.TCanvas('prob '+distribution, 'prob '+distribution)
    prob.SetDirectory(output_file)
    prob.Write()
    
    del hist
    del prob
    del canvas


def draw_corrs(args, config, distribution, tree, output_file):

    dependencies = config['distributions'][distribution].get('dependencies', {})
    if len(dependencies) == 0:
        print distribution+' has no dependencies'
        return
    else:
        print distribution+' depends on '+dependencies[0]


    nBins = config['num bins']
    xMin = config['distributions'][distribution]['min']
    xMax = config['distributions'][distribution]['max']
    vars = config['distributions'][distribution]['variables']

    xMin_dep = config['distributions'][dependencies[0]]['min']
    xMax_dep = config['distributions'][dependencies[0]]['max']
    vars_dep = config['distributions'][dependencies[0]]['variables']

    base_cuts = config.get('common cuts', {}).values()
    dist_cuts = config['distributions'][distribution].get('cuts', {}).values()

    dist_cuts_dep = config['distributions'][dependencies[0]].get('cuts', {}).values()

    nBins_corr = config['num corr bins']
    bin_width_corr = (xMax - xMin) / nBins_corr
    corr = ROOT.TH1D('corr_'+distribution+'_'+dependencies[0], 'corr_'+distribution+'_'+dependencies[0], nBins_corr, xMin, xMax)

    prob_dep = output_file.Get('prob_'+dependencies[0])
    
    for i in range(nBins_corr):
        avg_prob_dep = 0
        hist_dep = ROOT.TH1D('hist_dep_'+dependencies[0], 'hist_dep_'+dependencies[0], nBins, xMin_dep, xMax_dep)
        iVar = 0
        for var_dep in vars_dep:
            sel_string = plot_helper.DrawStringMaker()

            if var_dep in config['special cuts'].keys():
                sel_string.append_selection_requirements(base_cuts, dist_cuts, config['special cuts'].get(var_dep, {}).values())
            else:
                sel_string.append_selection_requirements(base_cuts, dist_cuts)

            if vars[iVar] in config['special cuts'].keys():
                sel_string.append_selection_requirements(config['special cuts'].get(vars[iVar], {}).values())

            if i == 0:
                var_bin_cut = '%s < %d' % (vars[iVar], xMin+(i+1)*bin_width_corr)
            elif i == nBins-1:
                var_bin_cut = '%s > %d' % (vars[iVar], xMin+i*bin_width_corr)
            else:
                var_bin_cut = '%s > %d && %s < %d' % (vars[iVar], xMin+i*bin_width_corr, vars[iVar], xMin+(i+1)*bin_width_corr)

            sel_string.append_selection_requirement(var_bin_cut)

            #print sel_string.draw_string
            if iVar == 0:
                tree.Draw(var_dep+' >> hist_dep_'+dependencies[0], sel_string.draw_string, '')
            else:
                tree.Draw(var_dep+' >>+ hist_dep_'+dependencies[0], sel_string.draw_string, '')
                
            if len(vars) > 1:
                iVar += 1

        for j in range(nBins):
            avg_prob_dep += hist_dep.GetBinContent(j+1)*prob_dep.GetBinContent(j+1)
            
        #print hist_dep.Integral()
        if hist_dep.Integral() == 0:
            avg_prob_dep = 1.0
        else:
            avg_prob_dep = avg_prob_dep / hist_dep.Integral()

        corr.SetBinContent(i+1, avg_prob_dep)
        del hist_dep

        
    canvas = ROOT.TCanvas('corr '+distribution+' to '+dependencies[0], 'corr '+distribution+' to '+dependencies[0])
    corr.SetDirectory(output_file)
    corr.Write()
    
    del prob_dep
    del corr
    del canvas

    

    
if __name__ == '__main__':
    main()

