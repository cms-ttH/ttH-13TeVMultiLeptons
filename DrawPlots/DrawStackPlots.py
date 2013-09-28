#!/usr/bin/env python
import os, sys
from argparse import ArgumentParser
import math
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper
from ttHMultileptonAnalysis.DrawPlots.utilities.yamlhelpers import ttHMultileptonYAMLLoader
import yaml

parser = ArgumentParser(description='Make stack plots from histogram files.')
parser.add_argument('config_file_name', nargs='?', default='stack_plot_configuration.yaml', help='Configuration file to process.')
parser.add_argument('cosmetics_config_file_name', nargs='?', default='stack_plot_cosmetics.yaml', help='Cosmetics configuration file to process.')
parser.add_argument('-w', '--web', action='store_true', help='post each plot to the user\'s AFS space')
args = parser.parse_args()

## config is mostly options that change the substance of what is displayed
## config_cosmetics is mostly options that change the style of the stack plot
with open(args.config_file_name) as config_file:
    config = yaml.load(config_file, Loader=ttHMultileptonYAMLLoader)

with open(args.cosmetics_config_file_name) as cosmetics_file:
    cosmetics = yaml.load(cosmetics_file)

lepton_categories = config['lepton categories']
jet_tag_categories = config['jet tag categories']
distributions = config['distributions']
signal_samples = config['signal samples']
background_samples = config['background samples']
if config.has_key('background sample groups'):
    background_sample_groups = config['background sample groups']

def main():
    ## import the root libraries; with this import
    ## you won't need to prefix your root objects with ROOT
    from ROOT import * 
    gROOT.SetBatch()

    if args.web:
        www_plot_directories = []
        for lepton_category in lepton_categories:
            for jet_tag_category in jet_tag_categories:
                www_plot_directories.append('stack_plots/%s/%s_%s/' % (config['input file label'], lepton_category, jet_tag_category))

        plot_helper.setup_web_posting(www_plot_directories, 4, args.config_file_name, args.cosmetics_config_file_name)

    for lepton_category in lepton_categories:
        print '\n\nStarting lepton category %s...\n' % lepton_category

        for jet_tag_category in jet_tag_categories:
            print 'Starting jet tag category %s...' % jet_tag_category

            for distribution in distributions:
                print 'Drawing distribution: %s with jet selection printing name: %s' %  (distribution, jet_tag_categories[jet_tag_category])
                draw_stack_plot(lepton_category, jet_tag_category, distribution)

    if args.web:
        print '\nFinished processing.  Plots will be posted to: http://www.nd.edu/~%s/stack_plots/%s/' % (os.environ['USER'], config['input file label'])

def draw_stack_plot (lepton_category, jet_tag_category, distribution):
    stack_plot = THStack("theStack", "")
    stack_plot_legend = make_legend()

    (luminosity_info_tex, selection_info_tex, SF_info_tex) = make_info_tex_objects(lepton_category, jet_tag_category)

    histogram_dictionary = {}
    mc_sum = 0.0
    signal_sum = 0.0
    data_sum = 0.0

    ## Draw the background sample histograms, put in legend
    for sample in background_samples:
        for systematic in config['systematics']:
            original_histogram = get_histogram(distribution, systematic, sample, lepton_category, jet_tag_category)
            histogram_dictionary[sample+'_'+systematic] = original_histogram.Clone()

            if systematic == 'nominal':
                histogram = original_histogram.Clone('stack')
                mc_sum += histogram.Integral()
                sample_info = plot_helper.SampleInformation(sample)
                xsec_frac_error = sample_info.x_section / sample_info.x_section_error #is this being used?
                stack_plot.Add(histogram, "hist")
                stack_plot_legend.AddEntry(histogram, '%s (%0.1f)' % (background_samples[sample]['draw name'], histogram.Integral()), 'f')

    # Sum histograms in each sample group, then add summed histos to stack plot and histogram_dictionary
    samples_and_sample_groups = background_samples.keys()
    if config.has_key('background sample groups'):
        samples_and_sample_groups.extend(background_sample_groups.keys())
        for sample_group in background_sample_groups:
            for systematic in config['systematics']:
                samples_in_group = background_sample_groups[sample_group]['samples']
                for index, sample in enumerate(samples_in_group):
                    sample_histogram = get_histogram(distribution, systematic, sample, lepton_category, jet_tag_category, sample_group)
                    if index == 0:
                        group_histogram = sample_histogram
                    else:
                        group_histogram.Add(sample_histogram)

                histogram_dictionary[sample_group+'_'+systematic] = group_histogram.Clone()
                if systematic == 'nominal':
                    histogram = group_histogram.Clone('stack')
                    mc_sum += group_histogram.Integral()
                    stack_plot.Add(histogram, "hist")
                    stack_plot_legend.AddEntry(histogram, '%s (%0.1f)' % (background_sample_groups[sample_group]['draw name'], group_histogram.Integral()), 'f')

    ## Draw the signal sample histogram(s), put in legend
    for sample in signal_samples:
        original_histogram = get_histogram(distribution, 'nominal', sample, lepton_category, jet_tag_category)
        histogram_dictionary[sample+'_'+systematic] = original_histogram.Clone()

        if signal_samples[sample]['stack or line'] == 'line':
            signal_histogram = original_histogram.Clone('nostack') #should this be 'line'?
        elif signal_samples[sample]['stack or line'] == 'stack':
            signal_histogram = original_histogram.Clone('stack')
        else:
            sys.exit('For signal, must be line or stack')

        signal_sum = signal_histogram.Integral()

        if (signal_sum > 0 and signal_samples[sample]['scale'] == 'norm'):
            signal_histogram.Scale(mc_sum / signal_sum)
        elif (signal_sum > 0):
            signal_histogram.Scale(signal_samples[sample]['scale'])

#still see signal after commenting these lines?!
#         if (signal_samples[sample]['stack or line'] == 'stack'):
#             stack_plot.Add(signal_histogram, "hist")

        if (signal_sum > 0):
            stack_plot_legend.AddEntry(signal_histogram, '%s (%0.1f x %0.1f)' % (signal_samples[sample]['draw name'], signal_sum, (signal_histogram.Integral() / signal_sum)), 'l')
        else:
            stack_plot_legend.AddEntry(signal_histogram, '%s (0.0x1.0)' % signal_samples[sample]['draw name'], 'l')

    ## Draw the data histogram, put in legend
    if not config['blinded']:
        original_histogram = get_histogram(distribution, systematic, 'data', lepton_category, jet_tag_category)
        histogram_dictionary['data'] = original_histogram.Clone()

        data_histogram = original_histogram.Clone('data')
        data_sum = data_histogram.Integral()
        stack_plot_legend.AddEntry(data_histogram, 'Data (%.0f) ' % data_sum, 'lpe')

    lumi_error = config['luminosity error']
    trigger_SF_error = config['trigger SF error']
    lumi_trigger_SF_error = math.sqrt(math.pow(lumi_error, 2) + math.pow(trigger_SF_error, 2))

    try:
        nBins = stack_plot.GetStack().Last().GetNbinsX()
        xMin = stack_plot.GetStack().Last().GetXaxis().GetXmin()
        xMax = stack_plot.GetStack().Last().GetXaxis().GetXmax()
    except: sys.exit('No histograms in stack.  Quitting.')

    # Create a histogram with the error bars for the MC stack
    mc_error_histogram = TH1F('mc_error_histogram', '', nBins, xMin, xMax)
    for i in range(1, nBins+1):
        mc_error_histogram.SetBinContent(i,stack_plot.GetStack().Last().GetBinContent(i))
        bin_error_squared = math.pow(lumi_trigger_SF_error * stack_plot.GetStack().Last().GetBinContent(i), 2)
        for sample in samples_and_sample_groups:
            for systematic in config['systematics']:
                bin_error_squared += math.pow(histogram_dictionary[sample+'_'+systematic].GetBinContent(i) - histogram_dictionary[sample+'_nominal'].GetBinContent(i), 2)

        mc_error_histogram.SetBinError(i, math.sqrt(bin_error_squared))

    mc_error_histogram.SetFillStyle(cosmetics['mc error fill style'])
    mc_error_histogram.SetFillColor(getattr(ROOT,cosmetics['mc error fill color']))

    stack_plot_legend.AddEntry(mc_error_histogram, 'Sum MC (%0.1f) ' % (mc_sum + signal_sum), 'f')

    plot_max = stack_plot.GetMaximum()
    if (signal_histogram): plot_max = max(plot_max, signal_histogram.GetMaximum())
    if (not config['blinded']): plot_max = max(plot_max, data_histogram.GetMaximum())

    stack_plot = configure_my_stack(stack_plot, plot_max)
    canvas = TCanvas(distribution+'Lin', distribution, cosmetics['canvas min'], cosmetics['canvas max'])

    gStyle.SetPadBorderMode(cosmetics['pad border mode'])
    gStyle.SetFrameBorderMode(cosmetics['frame border mode'])

    top_canvas = TPad('top_canvas', 'up', cosmetics['top canvas x1'], cosmetics['top canvas y1'], cosmetics['top canvas x2'], cosmetics['top canvas y2'])
    bottom_canvas =  TPad ('bottom_canvas', 'down', cosmetics['bottom canvas x1'], cosmetics['bottom canvas y1'], cosmetics['bottom canvas x2'], cosmetics['bottom canvas y2'])

    (top_canvas, bottom_canvas) = configure_canvases(top_canvas, bottom_canvas)

    top_canvas.Draw()
    bottom_canvas.Draw()

    top_canvas.cd()
    if (config['log scale']):
        gPad.SetLogy()

    gPad.SetBottomMargin(cosmetics['pad bottom margin'])

    stack_plot.Draw()
    ## For some reason can't be done before Draw()
    stack_plot.GetYaxis().SetTitleSize(cosmetics['stack y axis title size'])
    stack_plot.GetYaxis().SetTitleOffset(cosmetics['stack y axis title offset'])
    mc_error_histogram.Draw(cosmetics['mc error histogram draw style'])
    signal_histogram.Draw(cosmetics['signal histogram draw style'])

    ## asymmetrical poisson errors for data
    ggg = get_configured_data_asymmetric_errors(data_histogram)

    if (not config['blinded']): ggg.Draw(cosmetics['ggg draw style'])

    ## calculate the KS test result, put it somewhere
    if (config['KS test']):
        ks_result = data_histogram.KolmogorovTest(mc_error_histogram)
        luminosity_info_tex.SetTitle('%s (KS = %0.2f)' % (luminosity_info_tex.GetTitle(), ks_result))

    if config['draw legend']: stack_plot_legend.Draw()

    luminosity_info_tex.DrawLatex(cosmetics['lumi text first'], cosmetics['lumi text second'], luminosity_info_tex.GetTitle())
    if config['selection info']: selection_info_tex.DrawLatex(cosmetics['selection text first'], cosmetics['selection text second'], selection_info_tex.GetTitle())

    if config['SF info']:
        if (dist.find('CFMlpANN') != -1):
            SF_info_tex.DrawLatex(cosmetics['SF info min'], cosmetics['SF info max'], SF_info_tex.GetTitle())

    bottom_canvas.cd()

    (ratio_histogram, ratio_error_histogram) = make_ratio_histogram(nBins, xMin, xMax, mc_error_histogram, data_histogram, signal_histogram)

    ratio_histogram = configure_ratio_histogram(ratio_histogram, distribution)
    ratio_error_histogram = configure_ratio_error_histogram(ratio_error_histogram)
    ratio_histogram.DrawCopy()
    if (not config['blinded']):
        ratio_error_histogram.DrawCopy('e2same')
        ratio_histogram.Draw('sameaxis')

    ## asymmetrical poisson errors for data in ratio plot
    g_ratio = make_data_ratio_asymmetric_errors(nBins, xMin, xMax, ggg, data_histogram, signal_histogram, stack_plot)
    g_ratio = configure_data_ratio_asymmetric_errors (g_ratio)

    if (not config['blinded']): g_ratio.Draw('psame')

    l = TLine()
    l.DrawLine(xMin, 1., xMax, 1.)

    if not os.path.exists(config['output file location']+lepton_category+'_'+jet_tag_category):
        os.mkdir(config['output file location']+lepton_category+'_'+jet_tag_category)

    plot_name = '%s_%s/%s' % (lepton_category, jet_tag_category, distribution)

    if (config['save png']): canvas.SaveAs(config['output file location']+plot_name+'.png')
    if (config['save pdf']): canvas.SaveAs(config['output file location']+plot_name+'.pdf')

    if args.web:
        try:
            afs_base_directory = config['afs base directory']
        except:
            afs_base_directory = plot_helper.get_afs_base_directory()
            config['afs base directory'] = afs_base_directory

        www_plot_directory = '%s/stack_plots/%s/%s_%s/' % (afs_base_directory, config['input file label'], lepton_category, jet_tag_category)
        plot_helper.copy_to_www_area(config['output file location'], www_plot_directory, plot_name)

    gPad.Close()
    top_canvas.Close()
    bottom_canvas.Close()
    stack_plot.Delete()
    canvas.Close()
## end draw_stack_plot

## Gets a single histogram
def get_histogram(distribution, systematic, sample, lepton_category, jet_tag_category, sample_group=''):
    histogram = None
    if sample == 'data':
        sample = plot_helper.get_data_sample_name(lepton_category)

    if systematic == 'nominal' or sample == plot_helper.get_data_sample_name(lepton_category):
        name_plus_cycle = '%s_%s_%s_%s;1' % (sample, lepton_category, jet_tag_category, distribution)
    else:
        name_plus_cycle = '%s_%s_%s_%s_%s;1' % (sample, lepton_category, jet_tag_category, distribution, systematic)

    root_file = TFile('%s%s/%s_%s_%s_%s.root' % (config['input file location'], lepton_category, lepton_category, jet_tag_category, sample, config['input file label']))
    histogram = root_file.Get(name_plus_cycle).Clone()

    if not histogram:
        print 'Oops! Error looking for histo %s, exiting...' % (distribution)
        sys.exit()

    histogram.SetDirectory(0) ##Decouples histogram from root file

    if (sample == 'MuEG' or sample == 'DoubleMu' or sample == 'DoubleElectron'):
        histogram.SetLineColor(getattr(ROOT,cosmetics['data line color']))
        histogram.SetMarkerColor(getattr(ROOT,cosmetics['data marker color']))
        histogram.SetFillColor(getattr(ROOT,cosmetics['data fill color']))
        histogram.SetLineWidth(cosmetics['data line width'])
        histogram.SetMarkerStyle(cosmetics['data marker style'])
        histogram.SetMarkerSize(cosmetics['data marker size'])

    elif config.has_key('background sample groups') and sample_group in background_sample_groups:
        histogram.SetLineColor(getattr(ROOT, background_sample_groups[sample_group]['color']))
        histogram.SetFillColor(getattr(ROOT, background_sample_groups[sample_group]['color']))
        histogram.SetFillStyle(cosmetics['background fill style'])

    elif sample in background_samples:
        histogram.SetLineColor(getattr(ROOT, background_samples[sample]['color']))
        histogram.SetFillColor(getattr(ROOT, background_samples[sample]['color']))
        histogram.SetFillStyle(cosmetics['background fill style'])

    elif sample in signal_samples:
        histogram.SetLineColor(getattr(ROOT,signal_samples[sample]['color']))
        histogram.SetFillColor(getattr(ROOT,signal_samples[sample]['color']))

        if (signal_samples[sample]['stack or line'] == 'line'):
            histogram.SetLineWidth(signal_samples[sample]['line width'])
        elif (signal_samples[sample]['stack or line'] == 'stack'):
            histogram.SetFillStyle(cosmetics['background fill style'])
        else:
            sys.exit('Error - must select either line or stack for signal_sample '+sample+'.  Quitting.')

    return histogram
## end of get_histogram

def make_legend():
    stack_plot_legend = TLegend(cosmetics['legend x1'], cosmetics['legend y1'], cosmetics['legend x2'], cosmetics['legend y2'])
    stack_plot_legend.SetFillColor(getattr(ROOT, cosmetics['legend fill color']))
    stack_plot_legend.SetBorderSize(cosmetics['legend border size'])
    stack_plot_legend.SetNColumns(cosmetics['legend n columns'])

    return stack_plot_legend
## end of make_legend

def make_info_tex_objects(lepton_category, jet_tag_category):
    luminosity_info_tex = TLatex()
    luminosity_info_tex.SetNDC()
    luminosity_info_tex.SetTextFont(cosmetics['lumi text font'])
    luminosity_info_tex.SetTextSize(cosmetics['lumi text size'])
    luminosity_info_tex.SetTitle(lepton_categories[lepton_category]+jet_tag_categories[jet_tag_category]+config['lumi era string'])

    selection_info_tex = TLatex()
    selection_info_tex.SetNDC()
    selection_info_tex.SetTextFont(cosmetics['selection text font'])
    selection_info_tex.SetTextSize(cosmetics['selection text size'])
    selection_info_tex.SetTitle(lepton_categories[lepton_category]+jet_tag_categories[jet_tag_category])

    SF_info_tex = TLatex()
    SF_info_tex.SetNDC()
    SF_info_tex.SetTextFont(cosmetics['SF text font'])
    SF_info_tex.SetTextSize(cosmetics['SF text size'])
    SF_strings = ['%s x %s' % (signal_samples[sample]['draw name'], signal_samples[sample]['scale']) for sample in signal_samples]
    SF_info_tex.SetTitle(', '.join(SF_strings))

    return luminosity_info_tex, selection_info_tex, SF_info_tex
## end of make_info_tex_objects

def move_extra_into_hist (histogram):
    '''Move over/underflow bins into the histogram'''

    numBins = histogram.GetNbinsX()
    histogram.SetBinContent(1, histogram.GetBinContent(0) + histogram.GetBinContent(1))
    histogram.SetBinContent(0,0)
    histogram.SetBinContent(numBins, histogram.GetBinContent(numBins) + histogram.GetBinContent(numBins+1))
    histogram.SetBinContent(numBins+1, 0)

    return histogram
## end move_extra_into_histogram()

def configure_my_stack(stack_plot, plot_max):
    title_string = ';;%s' % 'Events'
    stack_plot.SetTitle(title_string)
    stack_plot.SetMinimum(cosmetics['stack minimum'])
    stack_plot.SetMaximum(max(cosmetics['stack lowest maximum'], plot_max * cosmetics['stack maximum factor']))
    if (config['log scale']):
        stack_plot.SetMinimum(cosmetics['stack minimum log scale'])
        stack_plot.SetMaximum(max(cosmetics['stack lowest maximum log scale'], plot_max * cosmetics['stack maximum factor log scale']))

    return stack_plot
## end configure_my_stack

def configure_canvases(top_canvas, bottom_canvas):
    top_canvas.SetLeftMargin(cosmetics['top canvas left margin'])
    bottom_canvas.SetLeftMargin(cosmetics['bottom canvas left margin'])

    top_canvas.SetRightMargin(cosmetics['top canvas right margin'])
    bottom_canvas.SetRightMargin(cosmetics['bottom canvas right margin'])

    top_canvas.SetTopMargin(cosmetics['top canvas top margin'])
    bottom_canvas.SetBottomMargin(cosmetics['bottom canvas bottom margin'])
    bottom_canvas.SetTickx()

    top_canvas.Modified()
    bottom_canvas.Modified()

    return top_canvas, bottom_canvas
## end configure_canvases

def get_configured_data_asymmetric_errors(data_histogram):
    ggg = TGraphAsymmErrors(data_histogram)
        
    alpha = 1 - 0.6827
    num_bins = ggg.GetN()
    for bin in range(0, num_bins):
        NN = ggg.GetY()[bin]
        if NN == 0:
            LOW = 0
        else: 
            LOW =  Math.gamma_quantile(alpha/2, NN, 1.)
        UP =  Math.gamma_quantile_c(alpha/2, NN+1, 1)
        ggg.SetPointEYlow(bin, NN-LOW)
        ggg.SetPointEYhigh(bin, UP-NN)

    ggg.SetLineColor(getattr(ROOT,cosmetics['ggg line color']))
    ggg.SetMarkerStyle(cosmetics['ggg marker style'])
    ggg.SetLineWidth(cosmetics['ggg line width'])
    ggg.SetMarkerSize(cosmetics['ggg marker size'])

    return ggg
## end configure_ratio_histogram

def make_ratio_histogram(nBins, xMin, xMax, mc_error_histogram, data_histogram, signal_histogram):
        ratio_histogram = TH1F('ratio_histogram', '', nBins, xMin, xMax)
        ratio_error_histogram = TH1F('ratio_error_histogram', '', nBins, xMin, xMax)

        for i in range(1, nBins+1):
                mc_value = mc_error_histogram.GetBinContent(i)
                if (not config['blinded']): data_value = data_histogram.GetBinContent(i) 
                if (config['blinded']): data_value = signal_histogram.GetBinContent(i) 
                mc_error = mc_error_histogram.GetBinError(i)
                if (not config['blinded']): data_error = data_histogram.GetBinError(i) 
                if (config['blinded']): data_error = signal_histogram.GetBinError(i) 

                if (mc_value !=0 and data_value != 0):
                        ratio_value = data_value / mc_value
                        ratio_error = ratio_value * data_error / data_value
                        ratio_error_mc = mc_error / mc_value
                        if ratio_value > 2:
                                ratio_value = 2
                elif (mc_value == 0 and data_value != 0):
                        ratio_value = 2
                        ratio_error = 2
                elif (mc_value != 0 and data_value == 0):
                        ratio_error_mc = mc_error / mc_value
                if data_value != 0:
                        ratio_histogram.SetBinContent(i, ratio_value)
                        ratio_histogram.SetBinError(i, ratio_error)
                if mc_value != 0:
                        ratio_error_histogram.SetBinContent(i, 1)
                        ratio_error_histogram.SetBinError(i, ratio_error_mc)

        return ratio_histogram, ratio_error_histogram
## end make_ratio_histogram

def configure_ratio_histogram(ratio_histogram , distribution):
    ratio_histogram.SetStats(kFALSE)
    ratio_histogram.SetMinimum(cosmetics['ratio hist min'])
    ratio_histogram.SetMaximum(cosmetics['ratio hist max'])
    ratio_title_string = ';%s;%s' % (distributions[distribution][0], 'Data/MC')
    ratio_histogram.SetTitle(ratio_title_string)
    ratio_histogram.GetYaxis().SetTitleSize(cosmetics['ratio hist y axis title size'])
    ratio_histogram.GetYaxis().SetTitleOffset(cosmetics['ratio hist y axis title offset'])
    ratio_histogram.GetYaxis().CenterTitle()
    ratio_histogram.GetYaxis().SetLabelSize(cosmetics['ratio hist y axis label size'])
    ratio_histogram.GetYaxis().SetNdivisions(cosmetics['ratio hist y axis Ndivisions'])
    ratio_histogram.GetXaxis().SetLabelSize(cosmetics['ratio hist x axis label size'])
    ratio_histogram.GetXaxis().SetLabelOffset(cosmetics['ratio hist x axis label offset'])
    ratio_histogram.GetXaxis().SetTitleOffset(cosmetics['ratio hist x axis title offset'])
    ratio_histogram.GetXaxis().SetTitleSize(cosmetics['ratio hist x axis title size'])

    ratio_histogram.SetLineColor(getattr(ROOT,cosmetics['ratio hist line color']))
    ratio_histogram.SetMarkerColor(getattr(ROOT,cosmetics['ratio hist marker color']))

    if (config['blinded']):
        ratio_histogram.SetLineColor(getattr(ROOT,cosmetics['ratio hist line color blind']))
        ratio_histogram.SetMarkerColor(getattr(ROOT,cosmetics['ratio hist marker color blind']))

    return ratio_histogram
## end configure_ratio_histogram

def configure_ratio_error_histogram(ratio_error_histogram):
    ratio_error_histogram.SetMarkerColor(getattr(ROOT,cosmetics['ratio err hist marker color']))
    ratio_error_histogram.SetFillColor(getattr(ROOT,cosmetics['ratio err hist fill color']))

    return ratio_error_histogram
## end configure_ratio_error_histogram

def make_data_ratio_asymmetric_errors (nBins, xMin, xMax, ggg, data_histogram, signal_histogram , stack_plot):
    ratio_max = 2.3
    g_ratio = TGraphAsymmErrors(ggg.GetN())
    for bin in range(0, g_ratio.GetN()):
        x_point = data_histogram.GetBinCenter(bin+1)
        x_width = 0.5*data_histogram.GetBinWidth(bin+1)
        yG = ggg.GetY()[bin]
        yG_low  = ggg.GetEYlow()[bin]
        yG_high = ggg.GetEYhigh()[bin]
        if not config['blinded']:
            y_data = data_histogram.GetBinContent(bin+1)
        else:
            y_data = signal_histogram.GetBinContent(bin+1)

        yBkg = stack_plot.GetStack().Last().GetBinContent(bin+1)

        if yBkg > 0.0:
            yG_ratio = yG/yBkg
            yG_ratio_low = yG_low/yBkg
            yG_ratio_high = yG_high/yBkg
        else:
            yG_ratio = 0.0
            yG_ratio_low = 0.0
            yG_ratio_high = 0.0
                        
        if y_data > 0:
            g_ratio.SetPoint(bin, x_point, yG_ratio)
            g_ratio.SetPointEYlow(bin, yG_ratio_low)
            g_ratio.SetPointEYhigh(bin, yG_ratio_high)                        
            g_ratio.SetPointEXlow(bin, x_width)
            g_ratio.SetPointEXhigh(bin, x_width)

            if (yG_ratio > ratio_max and (yG_ratio - yG_ratio_low) < ratio_max):
                minner = yG_ratio_low - (yG_ratio - ratio_max - 0.0001)
                g_ratio.SetPoint(bin, x_point, ratio_max - 0.0001)
                g_ratio.SetPointEYlow(bin, minner)

    return g_ratio
## end make_data_ratio_asymmetric_errors

def configure_data_ratio_asymmetric_errors(g_ratio):
    g_ratio.SetLineColor(getattr(ROOT,cosmetics['g ratio line color']))
    g_ratio.SetLineWidth(cosmetics['g ratio line width'])

    return g_ratio
## end configure_data_ratio_asymmetric_errors

if __name__ == '__main__':
        main()
