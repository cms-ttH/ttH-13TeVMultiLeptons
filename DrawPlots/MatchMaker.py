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
    parser.add_argument('-l', '--label', help='Add label to end of root file name.')
    args = parser.parse_args()

    with open(args.config_file_name) as config_file:
        config = yaml.load(config_file)

    if args.label: out_label = '_'+args.label
    else: out_label = ''
        
    input_file = ROOT.TFile(config['input file'])
    output_file = ROOT.TFile(config['output file'].replace('.root', out_label+'.root'), 'RECREATE')
    tree = input_file.Get('summaryTree')

    distribution_keys = config['distributions'].keys()

    for distribution in distribution_keys:
        draw_histos(args, config, distribution, tree, output_file)

    for distribution in distribution_keys:
        draw_corrs(args, config, distribution, tree, output_file)
        
    del tree
    input_file.Close()
        

def draw_histos(args, config, distribution, tree, output_file):

    print 'inside draw_histos with '+distribution

    nBins = config['distributions'][distribution]['num bins']
    xMin = config['distributions'][distribution]['min']
    xMax = config['distributions'][distribution]['max']
    vars = config['distributions'][distribution]['variables']
    bkg_vars = config['distributions'][distribution]['bkg_vars']

    base_cuts = config.get('common cuts', {}).values()
    dist_cuts = config['distributions'][distribution].get('cuts', {}).values()
    bkg_cuts = config['distributions'][distribution].get('bkg_cuts', {}).values()

    sel_strings = {}
    bkg_sel_strings = {}
    for var in vars:
        #print var
        sel_strings[var] = plot_helper.DrawStringMaker()
        sel_strings[var].append_selection_requirements(base_cuts, dist_cuts)
        if var in config['special cuts'].keys():
            sel_strings[var].append_selection_requirements(config['special cuts'].get(var, {}).values())
        #print sel_strings[var].draw_string

        bkg_sel_strings[var] = {}
        for bkg_var in bkg_vars:
            #print bkg_var
            bkg_sel_string_temp = plot_helper.DrawStringMaker()
            bkg_sel_string_temp.append_selection_requirements(base_cuts, dist_cuts, bkg_cuts)
            if var in config['special cuts'].keys():
                bkg_sel_string_temp.append_selection_requirements(config['special cuts'].get(var, {}).values())
            if bkg_var in config['special cuts'].keys():
                bkg_sel_string_temp.append_selection_requirements(config['special cuts'].get(bkg_var, {}).values())
            #print bkg_sel_string_temp.draw_string

            for i in range(config['distributions'][distribution]['num_bkg_vars'][0]):
                bkg_var_new = bkg_var.replace('_WW', '_'+str(i+1))
                bkg_sel_string = bkg_sel_string_temp.draw_string.replace('_WW', '_'+str(i+1))
                if len(config['distributions'][distribution]['num_bkg_vars']) == 1:
                    #print str(i+1)+' '+bkg_var_new+': '+bkg_sel_string
                    bkg_sel_strings[var][bkg_var_new] = bkg_sel_string
                else:
                    for j in range(config['distributions'][distribution]['num_bkg_vars'][1]):
                        bkg_var_new = bkg_var.replace('_WW', '_'+str(i+1))
                        bkg_var_new = bkg_var_new.replace('_XX', '_'+str(j+1))
                        bkg_sel_string = bkg_sel_string_temp.draw_string.replace('_WW', '_'+str(i+1))
                        bkg_sel_string = bkg_sel_string.replace('_XX', '_'+str(j+1))
                        if len(config['distributions'][distribution]['num_bkg_vars']) == 2:
                            if i<j:
                                #print str(i+1)+' '+str(j+1)+' '+bkg_var_new+': '+bkg_sel_string
                                bkg_sel_strings[var][bkg_var_new] = bkg_sel_string
                        else:
                            for k in range(config['distributions'][distribution]['num_bkg_vars'][2]):
                                bkg_var_new = bkg_var.replace('_WW', '_'+str(i+1))
                                bkg_var_new = bkg_var_new.replace('_XX', '_'+str(j+1))
                                bkg_var_new = bkg_var_new.replace('_YY', '_'+str(k+1))
                                bkg_sel_string = bkg_sel_string_temp.draw_string.replace('_WW', '_'+str(i+1))
                                bkg_sel_string = bkg_sel_string.replace('_XX', '_'+str(j+1))
                                bkg_sel_string = bkg_sel_string.replace('_YY', '_'+str(k+1))
                                if len(config['distributions'][distribution]['num_bkg_vars']) == 3:
                                    if i<j and j<k:
                                        #print str(i+1)+' '+str(j+1)+' '+str(k+1)+' '+bkg_var_new+': '+bkg_sel_string
                                        bkg_sel_strings[var][bkg_var_new] = bkg_sel_string
                                else:
                                    for l in range(config['distributions'][distribution]['num_bkg_vars'][3]):
                                        if i<j and j<k and k<l:
                                            bkg_var_new = bkg_var.replace('_WW', '_'+str(i+1))
                                            bkg_var_new = bkg_var_new.replace('_XX', '_'+str(j+1))
                                            bkg_var_new = bkg_var_new.replace('_YY', '_'+str(k+1))
                                            bkg_var_new = bkg_var_new.replace('_ZZ', '_'+str(l+1))
                                            bkg_sel_string = bkg_sel_string_temp.draw_string.replace('_WW', '_'+str(i+1))
                                            bkg_sel_string = bkg_sel_string.replace('_XX', '_'+str(j+1))
                                            bkg_sel_string = bkg_sel_string.replace('_YY', '_'+str(k+1))
                                            bkg_sel_string = bkg_sel_string.replace('_ZZ', '_'+str(l+1))
                                            #print str(i+1)+' '+str(j+1)+' '+str(k+1)+' '+bkg_var_new+': '+bkg_sel_string
                                            bkg_sel_strings[var][bkg_var_new] = bkg_sel_string

    ## Draw the signal histograms
    canvas = ROOT.TCanvas('hist '+distribution, 'hist '+distribution)
    hist = ROOT.TH1F('hist_'+distribution, 'hist_'+distribution, nBins, xMin, xMax)

    #print vars[0]+', '+sel_strings[vars[0]].draw_string
    tree.Draw(vars[0]+' >> hist_'+distribution, sel_strings[vars[0]].draw_string, '')
    for var in vars:
        if not var == vars[0]:
            #print var+', '+sel_strings[var].draw_string
            tree.Draw(var+' >>+ hist_'+distribution, sel_strings[var].draw_string, '')



    ## Draw the background histograms
    bkg_vars_new = {}
    for var in vars:
        bkg_vars_new[var] = bkg_sel_strings[var].keys()

    bkg_canvas = ROOT.TCanvas('bkg_hist '+distribution, 'bkg hist '+distribution)
    bkg_hist = ROOT.TH1F('bkg_hist_'+distribution, 'bkg_hist_'+distribution, nBins, xMin, xMax)

    #print bkg_vars_new[vars[0]][0]+', '+bkg_sel_strings[var][bkg_vars_new[vars[0]][0]]
    tree.Draw(bkg_vars_new[vars[0]][0]+' >> bkg_hist_'+distribution, bkg_sel_strings[var][bkg_vars_new[vars[0]][0]], '')
    for var in vars:
        for bkg_var in bkg_vars_new[var]:
            if not (var == vars[0] and bkg_var == bkg_vars_new[var][0]):
                #print bkg_var+', '+bkg_sel_strings[var][bkg_var]
                tree.Draw(bkg_var+' >>+ bkg_hist_'+distribution, bkg_sel_strings[var][bkg_var], '')

    ## Subtract signal hist from background hist?
    #bkg_hist.Add(hist, -1)

    ratio_canvas = ROOT.TCanvas('ratio '+distribution, 'ratio '+distribution)
    ratio_hist = ROOT.TH1F('ratio_'+distribution, 'ratio_'+distribution, nBins, xMin, xMax)

    for i in range(nBins):
        ratio_hist.SetBinContent(i+1, hist.GetBinContent(i+1)/bkg_hist.GetBinContent(i+1))
        
    integral = hist.Integral(1,nBins)
    if config['distributions'][distribution]['underflow']:
        ratio_hist.SetBinContent(1, hist.Integral(0,1)/bkg_hist.Integral(0,1))
        integral = hist.Integral(0,nBins)
    if config['distributions'][distribution]['overflow']:
        ratio_hist.SetBinContent(nBins, hist.Integral(nBins,nBins+1)/bkg_hist.Integral(nBins,nBins+1))
        integral = hist.Integral(1,nBins+1)
        if config['distributions'][distribution]['underflow']:
            integral = hist.Integral(0,nBins+1)

    product = 0
    for i in range(nBins):
        if i+1 == 1 and config['distributions'][distribution]['underflow']:
            product += ratio_hist.GetBinContent(i+1)*hist.Integral(0,i+1)
        elif i+1 == nBins:
            product += ratio_hist.GetBinContent(i+1)*hist.Integral(i+1,nBins+1)
        else:
            product += ratio_hist.GetBinContent(i+1)*hist.GetBinContent(i+1)
    ratio_hist.Scale(integral/product)

    hist.SetDirectory(output_file)
    hist.Write()
    bkg_hist.SetDirectory(output_file)
    bkg_hist.Write()
    ratio_hist.SetDirectory(output_file)
    ratio_hist.Write()
    
    del hist
    del canvas
    del bkg_hist
    del bkg_canvas
    del ratio_hist
    del ratio_canvas

def draw_corrs(args, config, distribution, tree, output_file):

    dependencies = config['distributions'][distribution].get('dependencies', {})
    if len(dependencies) == 0:
        print distribution+' has no dependencies'
        return
    else:
        print distribution+' depends on '+dependencies[0]

    # Parameters for the dependent variable
    nBins = config['distributions'][distribution]['num bins']
    xMin = config['distributions'][distribution]['min']
    xMax = config['distributions'][distribution]['max']
    bin_width = (xMax - xMin) / nBins
    vars = config['distributions'][distribution]['variables']

    # Parameters for the independent variable
    nBins_indep = config['distributions'][dependencies[0]]['num bins']
    xMin_indep = config['distributions'][dependencies[0]]['min']
    xMax_indep = config['distributions'][dependencies[0]]['max']
    vars_indep = config['distributions'][dependencies[0]]['variables']

    base_cuts = config.get('common cuts', {}).values()
    dist_cuts = config['distributions'][distribution].get('cuts', {}).values()

    dist_cuts_indep = config['distributions'][dependencies[0]].get('cuts', {}).values()

    nBins_corr = config['distributions'][distribution]['num corr bins']
    bin_width_corr = (xMax - xMin) / nBins_corr
    corr = ROOT.TH1F('corr_'+distribution+'_'+dependencies[0], 'corr_'+distribution+'_'+dependencies[0], nBins_corr, xMin, xMax)

    ratio_indep = output_file.Get('ratio_'+dependencies[0])
    
    for i in range(nBins_corr):
        avg_ratio_indep = 0
        hist_indep = ROOT.TH1F('hist_indep_'+dependencies[0], 'hist_indep_'+dependencies[0], nBins_indep, xMin_indep, xMax_indep)
        #iVar = 0
        for var_indep in vars_indep:
            sel_string = plot_helper.DrawStringMaker()

            sel_string.append_selection_requirements(base_cuts, dist_cuts)
            if var_indep in config['special cuts'].keys():
                sel_string.append_selection_requirements(config['special cuts'].get(var_indep, {}).values())

            for var in vars:
                sel_string_var = sel_string
                
                if var in config['special cuts'].keys():
                    sel_string_var.append_selection_requirements(config['special cuts'].get(var, {}).values())

                if i == 0:
                    var_bin_cut = '%s < %d' % (var, xMin+(i+1)*bin_width_corr)
                elif i == nBins_corr-1:
                    var_bin_cut = '%s > %d' % (var, xMin+i*bin_width_corr)
                else:
                    var_bin_cut = '%s > %d && %s < %d' % (var, xMin+i*bin_width_corr, var, xMin+(i+1)*bin_width_corr)

                sel_string_var.append_selection_requirement(var_bin_cut)

                #print sel_string_var.draw_string
                if var == vars[0]:
                    tree.Draw(var_indep+' >> hist_indep_'+dependencies[0], sel_string_var.draw_string, '')
                else:
                    tree.Draw(var_indep+' >>+ hist_indep_'+dependencies[0], sel_string_var.draw_string, '')


        for j in range(nBins_indep):
            avg_ratio_indep += hist_indep.GetBinContent(j+1)*ratio_indep.GetBinContent(j+1)
            
        #print hist_indep.Integral()
        if hist_indep.Integral() == 0:
            avg_ratio_indep = 1.0
        else:
            avg_ratio_indep = avg_ratio_indep / hist_indep.Integral()

        corr.SetBinContent(i+1, 1/avg_ratio_indep)
        del hist_indep


    hist = output_file.Get('hist_'+distribution)
    integral = hist.Integral(1,nBins)
    if config['distributions'][distribution]['underflow']:
        integral = hist.Integral(0,nBins)
    if config['distributions'][distribution]['overflow']:
        integral = hist.Integral(1,nBins+1)
        if config['distributions'][distribution]['underflow']:
            integral = hist.Integral(0,nBins+1)

    product = 0
    for i in range(nBins):
        if i+1 == 1 and config['distributions'][distribution]['underflow']:
            product += corr.GetBinContent(corr.GetXaxis().FindBin(xMin+(i+0.5)*bin_width))*hist.Integral(0,i+1)
        elif i+1 == nBins:
            product += corr.GetBinContent(corr.GetXaxis().FindBin(xMin+(i+0.5)*bin_width))*hist.Integral(i+1,nBins+1)
        else:
            product += corr.GetBinContent(corr.GetXaxis().FindBin(xMin+(i+0.5)*bin_width))*hist.GetBinContent(i+1)

    corr.Scale(integral/product)
        
    canvas = ROOT.TCanvas('corr '+distribution+' to '+dependencies[0], 'corr '+distribution+' to '+dependencies[0])
    corr.SetDirectory(output_file)
    corr.Write()

    del hist
    del ratio_indep
    del corr
    del canvas

if __name__ == '__main__':
    main()

