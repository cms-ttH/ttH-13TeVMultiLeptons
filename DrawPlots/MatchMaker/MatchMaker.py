from argparse import ArgumentParser
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper

#########################

import ROOT
import yaml
ROOT.gROOT.SetBatch(True)

def main():
    parser = ArgumentParser(description='Make plots from summary trees.')
    parser.add_argument('config_file_name', nargs='?', default='multilepton.yaml', help='Configuration file to process.')
    parser.add_argument('-l', '--label', help='Add label to end of root file name.')
    args = parser.parse_args()

    ## match_*.yaml
    with open(args.config_file_name) as config_file:
        config = yaml.load(config_file)

    if args.label: out_label = '_'+args.label
    else: out_label = ''

    ## Input tree file, in tree_files
    input_file = ROOT.TFile(config['input file'])
    ## Output distribution and ratio histograms
    output_file = ROOT.TFile(config['output file'].replace('.root', out_label+'.root'), 'RECREATE')
    tree = input_file.Get('summaryTree')

    ## Names of distributions
    distribution_keys = config['distributions'].keys()

    for distribution in distribution_keys:
        ## Separate into different nJet / nTag categories
        for cat in config['distributions'][distribution].get('categories', ['']):
            ## Draw the distribution and ratio histograms for correct permutation (sig) and all permutations (bkg)
            draw_histos(args, config, distribution, tree, output_file, cat)

    for distribution in distribution_keys:
        for cat in config['distributions'][distribution].get('categories', ['']):
            ## Draw correlation histograms between selected ratio histograms
            draw_corrs(args, config, distribution, tree, output_file, cat)
        
    del tree
    input_file.Close()
        

def draw_histos(args, config, distribution, tree, output_file, cat):

    print 'inside draw_histos with '+distribution+' '+cat

    nBins = config['distributions'][distribution]['num bins']
    xMin = config['distributions'][distribution]['min']
    xMax = config['distributions'][distribution]['max']
    ## Branch names for gen-level correct permutation (sig)
    vars = config['distributions'][distribution]['variables']
    ## Branch names for all permutations (bkg)
    bkg_vars = config['distributions'][distribution]['bkg_vars']

    ## Basic cuts
    base_cuts = config.get('common cuts', {}).values()
    ## Cuts for this distribution
    dist_cuts = config['distributions'][distribution].get('cuts', {}).values()
    ## Cuts for background permutations
    bkg_cuts = config['distributions'][distribution].get('bkg_cuts', {}).values()

    ## If there are categories, divide them up
    if cat == '':
        cat_cut = config['category cuts']['none']
        cat_str = ''
    else:
        cat_cut = config['category cuts'][cat]
        cat_str = '_'+cat

    ## Array of selection strings for the 'Draw' command
    sel_strings = {}
    bkg_sel_strings = {}
    ## Sometimes there are multiple branch names (variables) for each distribution
    for var in vars:
        ## Initialize an empty selection string for signal
        sel_strings[var] = plot_helper.DrawStringMaker()
        ## Add cuts to selection string
        sel_strings[var].append_selection_requirements(base_cuts, dist_cuts, cat_cut)
        ## Add specific cuts for specific variables
        if var in config['special cuts'].keys():
            sel_strings[var].append_selection_requirements(config['special cuts'].get(var, {}).values())

        ## Initialize an empty array for background
        bkg_sel_strings[var] = {}
        for bkg_var in bkg_vars:
             ## Initialize an empty selection string for this signal variable and this background variable
            bkg_sel_string_temp = plot_helper.DrawStringMaker()

#             ## Apply dist_cuts ('cuts') and bkg_cuts to bkg
#             bkg_sel_string_temp.append_selection_requirements(base_cuts, dist_cuts, cat_cut, bkg_cuts)
#             if var in config['special cuts'].keys():
#                 bkg_sel_string_temp.append_selection_requirements(config['special cuts'].get(var, {}).values())
#             if bkg_var in config['special cuts'].keys():
#                 bkg_sel_string_temp.append_selection_requirements(config['special cuts'].get(bkg_var, {}).values())

            ## Don't apply dist_cuts ('cuts') to bkg - only bkg_cuts
            bkg_sel_string_temp.append_selection_requirements(base_cuts, cat_cut, bkg_cuts)            
            if bkg_var in config['special cuts'].keys():
                bkg_sel_string_temp.append_selection_requirements(config['special cuts'].get(bkg_var, {}).values())

            ## Replace place-holders in background variable names with numbers
            for i in range(config['distributions'][distribution]['num_bkg_vars'][0]):
                bkg_var_new = bkg_var.replace('_WW', '_'+str(i+1))
                bkg_sel_string = bkg_sel_string_temp.draw_string.replace('_WW', '_'+str(i+1))
                ## One place-holder ('WW')
                if len(config['distributions'][distribution]['num_bkg_vars']) == 1:
                    ## Fill selection string for this signal variable and this background variable
                    bkg_sel_strings[var][bkg_var_new] = bkg_sel_string
                ## Two or more place-holders ('WW','XX')
                else:
                    for j in range(config['distributions'][distribution]['num_bkg_vars'][1]):
                        bkg_var_new = bkg_var.replace('_WW', '_'+str(i+1))
                        bkg_var_new = bkg_var_new.replace('_XX', '_'+str(j+1))
                        bkg_sel_string = bkg_sel_string_temp.draw_string.replace('_WW', '_'+str(i+1))
                        bkg_sel_string = bkg_sel_string.replace('_XX', '_'+str(j+1))
                        ## Two place-holders
                        if len(config['distributions'][distribution]['num_bkg_vars']) == 2:
                            ## Indices always in ascending order
                            if i<j:
                                bkg_sel_strings[var][bkg_var_new] = bkg_sel_string
                        ## Three or more place-holders ('WW','XX',YY')
                        else:
                            for k in range(config['distributions'][distribution]['num_bkg_vars'][2]):
                                bkg_var_new = bkg_var.replace('_WW', '_'+str(i+1))
                                bkg_var_new = bkg_var_new.replace('_XX', '_'+str(j+1))
                                bkg_var_new = bkg_var_new.replace('_YY', '_'+str(k+1))
                                bkg_sel_string = bkg_sel_string_temp.draw_string.replace('_WW', '_'+str(i+1))
                                bkg_sel_string = bkg_sel_string.replace('_XX', '_'+str(j+1))
                                bkg_sel_string = bkg_sel_string.replace('_YY', '_'+str(k+1))
                                ## Three place-holders
                                if len(config['distributions'][distribution]['num_bkg_vars']) == 3:
                                    if i<j and j<k:
                                        bkg_sel_strings[var][bkg_var_new] = bkg_sel_string
                                ## Four place-holders ('WW','XX','YY','ZZ')
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
                                            bkg_sel_strings[var][bkg_var_new] = bkg_sel_string

    ## Draw the signal histograms
    canvas = ROOT.TCanvas('hist '+distribution+cat_str, 'hist '+distribution+cat_str)
    hist = ROOT.TH1D('hist_'+distribution+cat_str, 'hist_'+distribution+cat_str, nBins, xMin, xMax)

    ## Draw first variable
    tree.Draw(vars[0]+' >> hist_'+distribution+cat_str, sel_strings[vars[0]].draw_string, '')
    for var in vars:
        ## Draw additional variables if they exist
        if not var == vars[0]:
            tree.Draw(var+' >>+ hist_'+distribution+cat_str, sel_strings[var].draw_string, '')

    ## Draw the background histograms
    bkg_vars_new = {}
    ## Fill array of background variable names place-holders replaced with numbers
    for var in vars:
        bkg_vars_new[var] = bkg_sel_strings[var].keys()

    bkg_canvas = ROOT.TCanvas('bkg_hist '+distribution+cat_str, 'bkg hist '+distribution+cat_str)
    bkg_hist = ROOT.TH1D('bkg_hist_'+distribution+cat_str, 'bkg_hist_'+distribution+cat_str, nBins, xMin, xMax)

    ## Draw for first signal variable and first background variable
    tree.Draw(bkg_vars_new[vars[0]][0]+' >> bkg_hist_'+distribution+cat_str, bkg_sel_strings[var][bkg_vars_new[vars[0]][0]], '')
    for var in vars:
        for bkg_var in bkg_vars_new[var]:
            ## Draw for other signal variables and other background variables (why both?) 
            if not (var == vars[0] and bkg_var == bkg_vars_new[var][0]):
                tree.Draw(bkg_var+' >>+ bkg_hist_'+distribution+cat_str, bkg_sel_strings[var][bkg_var], '')

#     ## Subtract signal hist from background hist (best not to do this - divide by 0 errors)
#     bkg_hist.Add(hist, -1)

    ## Draw the ratio histogram
    ratio_canvas = ROOT.TCanvas('ratio '+distribution+cat_str, 'ratio '+distribution+cat_str)
    ratio_hist = ROOT.TH1D('ratio_'+distribution+cat_str, 'ratio_'+distribution+cat_str, nBins, xMin, xMax)

    ## Fill each bin with sig / bkg
    for i in range(nBins):
        ratio_hist.SetBinContent(i+1, hist.GetBinContent(i+1)/bkg_hist.GetBinContent(i+1))

    ## Get the integral of the signal histogram
    integral = hist.Integral(1,nBins)
    if config['distributions'][distribution]['underflow']:
        ratio_hist.SetBinContent(1, hist.Integral(0,1)/bkg_hist.Integral(0,1))
        integral = hist.Integral(0,nBins)
    if config['distributions'][distribution]['overflow']:
        ratio_hist.SetBinContent(nBins, hist.Integral(nBins,nBins+1)/bkg_hist.Integral(nBins,nBins+1))
        integral = hist.Integral(1,nBins+1)
        if config['distributions'][distribution]['underflow']:
            integral = hist.Integral(0,nBins+1)

    ## Get the integral weighted by the ratio value for each bin
    weighted_integral = 0
    for i in range(nBins):
        if i+1 == 1 and config['distributions'][distribution]['underflow']:
            weighted_integral += ratio_hist.GetBinContent(i+1)*hist.Integral(0,i+1)
        elif i+1 == nBins and config['distributions'][distribution]['overflow']:
            weighted_integral += ratio_hist.GetBinContent(i+1)*hist.Integral(i+1,nBins+1)
        else:
            weighted_integral += ratio_hist.GetBinContent(i+1)*hist.GetBinContent(i+1)
    ## Scale the ratio histogram by the weighted_integral for signal,
    ## so the average ratio value for a correct permutation (signal) is 1
    ratio_hist.Scale(integral/weighted_integral)

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

def draw_corrs(args, config, distribution, tree, output_file, cat):

    ## Which distributions are dependent on which
    ## Only set up for single dependencies (dependencies[0]) right now
    dependencies = config['distributions'][distribution].get('dependencies', {})
    if len(dependencies) == 0:
        print distribution+' '+cat+' has no dependencies'
        return
    else:
        print distribution+' '+cat+' depends on '+dependencies[0]+' '+cat

    ## Parameters for the dependent variable
    nBins = config['distributions'][distribution]['num bins']
    xMin = config['distributions'][distribution]['min']
    xMax = config['distributions'][distribution]['max']
    bin_width = (xMax - xMin) / nBins
    vars = config['distributions'][distribution]['variables']

    ## Parameters for the independent variable
    nBins_indep = config['distributions'][dependencies[0]]['num bins']
    xMin_indep = config['distributions'][dependencies[0]]['min']
    xMax_indep = config['distributions'][dependencies[0]]['max']
    vars_indep = config['distributions'][dependencies[0]]['variables']

    base_cuts = config.get('common cuts', {}).values()
    dist_cuts = config['distributions'][distribution].get('cuts', {}).values()

    if cat == '':
        cat_cut = config['category cuts']['none']
        cat_str = ''
    else:
        cat_cut = config['category cuts'][cat]
        cat_str = '_'+cat

    ## Number of bins for the correlation histogram
    nBins_corr = config['distributions'][distribution]['num corr bins']
    bin_width_corr = (xMax - xMin) / nBins_corr
    corr = ROOT.TH1D('corr_'+distribution+'_'+dependencies[0]+cat_str, 'corr_'+distribution+'_'+dependencies[0]+cat_str, nBins_corr, xMin, xMax)

    ## Get the ratio histograms for the dependent and independent distributions
    ratio_dist = output_file.Get('ratio_'+distribution+cat_str)
    ratio_indep = output_file.Get('ratio_'+dependencies[0]+cat_str)
    
    for i in range(nBins_corr):
        ## Initialize average ratio values to 0
        avg_ratio_dist = 0
        avg_ratio_indep = 0
        ## Make temporary histograms for this correlation bin
        hist_indep = ROOT.TH1D('hist_indep_'+dependencies[0]+cat_str, 'hist_indep_'+dependencies[0]+cat_str, nBins_indep, xMin_indep, xMax_indep)
        hist_dist = ROOT.TH1D('hist_dist_'+dependencies[0]+cat_str, 'hist_dist_'+dependencies[0]+cat_str, nBins, xMin, xMax)
        ## Loop over variables for independent distribution
        for var_indep in vars_indep:
            sel_string = plot_helper.DrawStringMaker()

            sel_string.append_selection_requirements(base_cuts, dist_cuts, cat_cut)
            if var_indep in config['special cuts'].keys():
                sel_string.append_selection_requirements(config['special cuts'].get(var_indep, {}).values())

            ## Loop over variables for dependent distribution
            for var in vars:
                ## Single selection string for both independent and dependent distributions
                sel_string_var = sel_string
                
                if var in config['special cuts'].keys():
                    sel_string_var.append_selection_requirements(config['special cuts'].get(var, {}).values())

                ## Specify this correlation bin in the cuts
                if i == 0:
                    var_bin_cut = '%s < %d' % (var, xMin+(i+1)*bin_width_corr)
                elif i == nBins_corr-1:
                    var_bin_cut = '%s > %d' % (var, xMin+i*bin_width_corr)
                else:
                    var_bin_cut = '%s > %d && %s < %d' % (var, xMin+i*bin_width_corr, var, xMin+(i+1)*bin_width_corr)

                sel_string_var.append_selection_requirement(var_bin_cut)

                ## Draw independent and dependent histograms for this correlation bin
                if var == vars[0]:
                    tree.Draw(var_indep+' >> hist_indep_'+dependencies[0]+cat_str, sel_string_var.draw_string, '')
                    tree.Draw(var+' >> hist_dist_'+dependencies[0]+cat_str, sel_string_var.draw_string, '')
                else:
                    tree.Draw(var_indep+' >>+ hist_indep_'+dependencies[0]+cat_str, sel_string_var.draw_string, '')
                    tree.Draw(var+' >>+ hist_dist_'+dependencies[0]+cat_str, sel_string_var.draw_string, '')

        ## Get average ratio for independent and dependent distributions in this correlation bin
        for j in range(nBins_indep):
            avg_ratio_indep += hist_indep.GetBinContent(j+1)*ratio_indep.GetBinContent(j+1)
        for j in range(nBins):
            avg_ratio_dist += hist_dist.GetBinContent(j+1)*ratio_dist.GetBinContent(j+1) 
            
        if hist_indep.Integral() == 0:
            avg_ratio_indep = 1.0
        else:
            avg_ratio_indep = avg_ratio_indep / hist_indep.Integral()

        if hist_dist.Integral() == 0:
            avg_ratio_dist = 1.0
        else:
            avg_ratio_dist = avg_ratio_dist / hist_dist.Integral()

        ## Set correlation value for this bin to 1/(average ratio for independent distribution in this correlation bin)
        corr.SetBinContent(i+1, 1/avg_ratio_indep)
        ## If dependent variable is 'over-correlated', set correlation to 1
        if abs(1 - avg_ratio_indep) > abs(1 - avg_ratio_dist):
            print 'In bin %d, ratio_indep = %f and ratio_dist = %f' % (i+1, avg_ratio_indep, avg_ratio_dist)
            corr.SetBinContent(i+1, 1.0)
        del hist_indep
        del hist_dist


    ## Get integral of the dependent distribution
    hist = output_file.Get('hist_'+distribution+cat_str)
    integral = hist.Integral(1,nBins)
    if config['distributions'][distribution]['underflow']:
        integral = hist.Integral(0,nBins)
    if config['distributions'][distribution]['overflow']:
        integral = hist.Integral(1,nBins+1)
        if config['distributions'][distribution]['underflow']:
            integral = hist.Integral(0,nBins+1)

    ## Get integral of the dependent distribution weighted by the correlation value
    weighted_integral = 0
    for i in range(nBins):
        if i+1 == 1 and config['distributions'][distribution]['underflow']:
            weighted_integral += corr.GetBinContent(corr.GetXaxis().FindBin(xMin+(i+0.5)*bin_width))*hist.Integral(0,i+1)
        elif i+1 == nBins:
            weighted_integral += corr.GetBinContent(corr.GetXaxis().FindBin(xMin+(i+0.5)*bin_width))*hist.Integral(i+1,nBins+1)
        else:
            weighted_integral += corr.GetBinContent(corr.GetXaxis().FindBin(xMin+(i+0.5)*bin_width))*hist.GetBinContent(i+1)

    ## Scale the correlation histogram so that the average correlation value is 1
    corr.Scale(integral/weighted_integral)
                
    canvas = ROOT.TCanvas('corr '+distribution+' to '+dependencies[0]+cat_str, 'corr '+distribution+' to '+dependencies[0]+cat_str)
    corr.SetDirectory(output_file)
    corr.Write()

    del hist
    del ratio_indep
    del corr
    del canvas

if __name__ == '__main__':
    main()

