#!/usr/bin/env python
import os, sys
import ConfigParser
from argparse import ArgumentParser
import math
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper

parser = ArgumentParser(description='Make stack plots from histogram files.')
parser.add_argument('config_file_name', nargs='?', default='stack_plot_configuration.cfg', help='Configuration file to process.')
parser.add_argument('cosmetics_config_file_name', nargs='?', default='stack_plot_cosmetics.cfg', help='Cosmetics configuration file to process.')
parser.add_argument('-w', '--web', action='store_true', help='post each plot to the user\'s AFS space')
args = parser.parse_args()

## Set up the parser for the .cfg files
## config is mostly options that change the substance of what is displayed
config = ConfigParser()
config.read(args.config_file_name)

## config_cosmetics is mostly options that change the style of the stack plot
config_cosmetics = ConfigParser()
config_cosmetics.read(args.cosmetics_config_file_name)

## In addition to itmes, you can just get the keys or values                                            
#background_samples_keys = config['background_samples'].keys()
#background_samples_values = config['background_samples'].values()

## We create an ordered dictionary of the items under each header.
in_out_files = dict(config['in_out_files'].items())
draw_options = dict(config['draw_options'].items())
lumi_era = dict(config['lumi_era'].items())
background_samples = dict(config['background_samples'].items())
signal_samples = dict(config['signal_samples'].items())
signal_sample_keys = config['signal_samples'].keys()
lepton_categories = dict(config['lepton_categories'].items())
jet_tag_categories = dict(config['jet_tag_categories'].items())
distributions = dict(config['distributions'].items())
systematics = config['systematics'].keys()
cosmetics = dict(config_cosmetics['cosmetics'].items())

def main():
    ## import the root libraries; with this import
    ## you won't need to prefix your root objects with ROOT
    from ROOT import * 
    gROOT.SetBatch()
    
    for lepton_category in lepton_categories:
        print '\n\nStarting lepton category %s...\n' % lepton_category
        for jet_tag_category in jet_tag_categories:
            print 'Starting jet tag category %s...' % jet_tag_category
            for distribution in distributions:
                print 'Drawing distribution: %s with jet selection printing name: %s' %  (distribution, jet_tag_categories[jet_tag_category])
                draw_stack_plot (lepton_category, jet_tag_category, distribution)

    if args.web:
        print '\nFinished processing.  Plots will be posted to: http://www.nd.edu/~%s/stack_plots/%s/' % (os.environ['USER'], in_out_files['input_file_label'])

def draw_stack_plot (lepton_category, jet_tag_category, distribution):
    stack_plot = THStack("theStack", "")

    stack_plot_legend = make_legend()
    
    (luminosity_info_tex, selection_info_tex, SF_info_tex) = make_info_tex_objects(lepton_category, jet_tag_category)
    
    histoStorageList = {}
    mc_sum = 0.0
    signal_sum = 0.0
    data_sum = 0.0
        
    ## Draw the background sample histograms, put in legend
    for sample in background_samples:
        for systematic in systematics:
            original_histogram = get_histogram(distribution, systematic, sample, lepton_category, jet_tag_category)
            histoStorageList[sample+"_"+systematic] = original_histogram.Clone()

            if systematic == 'nominal':
                histogram = original_histogram.Clone('stack')
                mc_sum += histogram.Integral()
                sample_info = plot_helper.SampleInformation(sample)
                xsec_frac_error = sample_info.x_section / sample_info.x_section_error
                stack_plot.Add(histogram, "hist")
                stack_plot_legend.AddEntry(histogram, '%s (%0.1f)' % (background_samples[sample][0], histogram.Integral()), 'f')

    ## Draw the signal sample histogram(s), put in legend
    for sample in signal_samples:
        original_histogram = get_histogram(distribution, 'nominal', sample, lepton_category, jet_tag_category)
        histoStorageList[sample+"_"+systematic] = original_histogram.Clone()

        if signal_samples[sample][4] == 'line':
            signal_histogram = original_histogram.Clone('signal')
        elif signal_samples[sample][4] == 'stack':
            signal_histogram = original_histogram.Clone('stack')
        else:
            sys.exit('For signal, must be line or stack')
                
        signal_sum = signal_histogram.Integral()

        if (signal_sum > 0 and signal_samples[sample][5] == 'norm'):
            signal_histogram.Scale(mc_sum/signal_sum)
        elif (signal_sum > 0):
            signal_histogram.Scale(signal_samples[sample][5])

        if (signal_samples[sample][4] == 'stack'):
            stack_plot.Add(signal_histogram, 'hist')

        if (signal_sum > 0):
            stack_plot_legend.AddEntry(histogram, '%s (%0.1f x %0.1f)' % (signal_samples[sample][2], signal_sum, (signal_histogram.Integral() / signal_sum)), 'l')
        else:
            stack_plot_legend.AddEntry(histogram, '%s (0.0x1.0)' % signal_samples[sample][2], 'l')

    ## Draw the data histogram, put in legend
    if not draw_options['blinded']:
        original_histogram = get_histogram(distribution, systematic, 'data', lepton_category, jet_tag_category)
        histoStorageList['data'] = original_histogram.Clone()

        data_histogram = original_histogram.Clone('data')
        data_sum = data_histogram.Integral()
        stack_plot_legend.AddEntry(data_histogram, 'Data (%.0f) ' % data_sum, 'lpe')

    lumi_error = lumi_era['lumi_error']     
    trigger_SF_error = lumi_era['trig_SF_error']        
    lumi_trigger_SF_error = math.sqrt(math.pow(lumi_error,2)+math.pow(trigger_SF_error,2))

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
        for sample in background_samples:
            for systematic in systematics:
                bin_error_squared += math.pow(histoStorageList[sample+'_'+systematic].GetBinContent(i) - histoStorageList[sample+'_nominal'].GetBinContent(i), 2)
        mc_error_histogram.SetBinError(i, math.sqrt(bin_error_squared))

    mc_error_histogram.SetFillStyle(cosmetics['mc_err_fill_style'])
    mc_error_histogram.SetFillColor(getattr(ROOT,cosmetics['mc_err_fill_color']))

    stack_plot_legend.AddEntry(mc_error_histogram, 'Sum MC (%0.1f) ' % (mc_sum + signal_sum), 'f')

    plot_max = stack_plot.GetMaximum()
    if (signal_histogram): plot_max = max(plot_max, signal_histogram.GetMaximum())   
    if (not draw_options['blinded']): plot_max = max(plot_max, data_histogram.GetMaximum())

    stack_plot = configure_my_stack(stack_plot, plot_max)
    canvas = TCanvas(distribution+'Lin', distribution, cosmetics['canvas_min'], cosmetics['canvas_max'])

    gStyle.SetPadBorderMode(cosmetics['pad_border_mode'])
    gStyle.SetFrameBorderMode(cosmetics['frame_border_mode'])

    top_canvas = TPad('top_canvas', 'up', cosmetics['top_canvas_x1'], cosmetics['top_canvas_y1'], cosmetics['top_canvas_x2'], cosmetics['top_canvas_y2'])
    bottom_canvas =  TPad ('bottom_canvas', 'down', cosmetics['bottom_canvas_x1'], cosmetics['bottom_canvas_y1'], cosmetics['bottom_canvas_x2'], cosmetics['bottom_canvas_y2'])

    (top_canvas, bottom_canvas) = configure_canvases(top_canvas, bottom_canvas)

    top_canvas.Draw()
    bottom_canvas.Draw()

    top_canvas.cd()
    if (draw_options['log_scale']):
        gPad.SetLogy()

    gPad.SetBottomMargin(cosmetics['pad_bottom_margin'])

    stack_plot.Draw()
    ## For some reason can't be done before Draw()
    stack_plot.GetYaxis().SetTitleSize(cosmetics['stack_y_axis_title_size']) 
    stack_plot.GetYaxis().SetTitleOffset(cosmetics['stack_y_axis_title_offset'])
    mc_error_histogram.Draw(cosmetics['mc_error_histogram_draw_style'])
    signal_histogram.Draw(cosmetics['signal_histogram_draw_style'])
    
    ## asymmetrical poisson errors for data
    ggg = get_configured_data_asymmetric_errors(data_histogram)

    if (not draw_options['blinded']): ggg.Draw(cosmetics['ggg_draw_style']) 

    ## calculate the KS test result, put it somewhere
    if (draw_options['KS_test']):
        ks_result = data_histogram.KolmogorovTest(mc_error_histogram)
        luminosity_info_tex.SetTitle('%s (KS = %0.2f)' % (luminosity_info_tex.GetTitle(), ks_result))

    if draw_options['draw_legend']: stack_plot_legend.Draw()

    luminosity_info_tex.DrawLatex(cosmetics['lumi_text_first'], cosmetics['lumi_text_second'], luminosity_info_tex.GetTitle()) 
    if draw_options['selection_info']: selection_info_tex.DrawLatex(cosmetics['selection_text_first'], cosmetics['selection_text_second'], selection_info_tex.GetTitle())

    if draw_options['SF_info']:
        if (dist.find('CFMlpANN') != -1):
            SF_info_tex.DrawLatex(cosmetics['SF_info_min'], cosmetics['SF_info_max'], SF_info_tex.GetTitle())
        
    bottom_canvas.cd()

    (ratio_histogram, ratio_error_histogram) = make_ratio_histogram(nBins, xMin, xMax, mc_error_histogram, data_histogram, signal_histogram)

    ratio_histogram = configure_ratio_histogram(ratio_histogram, distribution)
    ratio_error_histogram = configure_ratio_error_histogram(ratio_error_histogram)
    ratio_histogram.DrawCopy() 
    if (not draw_options['blinded']):
        ratio_error_histogram.DrawCopy('e2same')
        ratio_histogram.Draw('sameaxis') 

    ## asymmetrical poisson errors for data in ratio plot
    g_ratio = make_data_ratio_asymmetric_errors(nBins, xMin, xMax, ggg, data_histogram, signal_histogram, stack_plot)
    g_ratio = configure_data_ratio_asymmetric_errors (g_ratio)
          
    if (not draw_options['blinded']): g_ratio.Draw('psame') 
        
    l = TLine()
    l.DrawLine(xMin, 1., xMax, 1.)

    if not os.path.exists(in_out_files['output_file_location']+lepton_category+'_'+jet_tag_category):
        os.mkdir(in_out_files['output_file_location']+lepton_category+'_'+jet_tag_category)

    plot_name = '%s_%s/%s' % (lepton_category, jet_tag_category, distribution)

    if (draw_options['save_png']): canvas.SaveAs(in_out_files['output_file_location']+plot_name+'.png')
    if (draw_options['save_pdf']): canvas.SaveAs(in_out_files['output_file_location']+plot_name+'.pdf')

    if args.web:
        try:
            afs_base_directory = in_out_files['afs_base_directory']
        except:
            afs_base_directory = plot_helper.get_afs_base_directory()
            in_out_files['afs_base_directory'] = afs_base_directory

        www_plot_directory = '%s/stack_plots/%s/%s_%s/' % (afs_base_directory, in_out_files['input_file_label'], lepton_category, jet_tag_category)
        plot_helper.setup_www_directory(www_plot_directory, 3)
        plot_helper.copy_to_www_area(in_out_files['output_file_location'], www_plot_directory, plot_name, args.config_file_name, args.cosmetics_config_file_name)

    gPad.Close()
    top_canvas.Close()
    bottom_canvas.Close()
    stack_plot.Delete()
    canvas.Close()
## end draw_stack_plot

## Gets a single histogram
def get_histogram(distribution, systematic, sample, lepton_category, jet_tag_category):
    histogram = None
    if sample == 'data':
        sample = plot_helper.get_data_sample_name(lepton_category)

    if systematic == 'nominal' or sample == 'data':
        name_plus_cycle = '%s_%s_%s_%s;1' % (sample, lepton_category, jet_tag_category, distribution)
    else:
        name_plus_cycle = '%s_%s_%s_%s_%s;1' % (sample, lepton_category, jet_tag_category, distribution, systematic)

    root_file = TFile('%s%s/%s_%s_%s_%s.root' % (in_out_files['input_file_location'], lepton_category, lepton_category, jet_tag_category, sample, in_out_files['input_file_label']))
    histogram = root_file.Get(name_plus_cycle).Clone()
        
    if not histogram:
        print 'Oops! Error looking for histo %s, exiting...' % (distribution)
        sys.exit()

#    histogram.UseCurrentStyle() ##What does this do?
    histogram.SetDirectory(0) ##Decouples histogram from root file
        
    if (sample == 'MuEG' or sample == 'DoubleMu' or sample == 'DoubleElectron'):           
        histogram.SetLineColor(getattr(ROOT,cosmetics['data_line_color']))
        histogram.SetMarkerColor(getattr(ROOT,cosmetics['data_marker_color']))
        histogram.SetFillColor(getattr(ROOT,cosmetics['data_fill_color']))
        histogram.SetLineWidth(cosmetics['data_line_width'])
        histogram.SetMarkerStyle(cosmetics['data_marker_style'])
        histogram.SetMarkerSize(cosmetics['data_marker_size'])

    elif (sample in background_samples):
        histogram.SetLineColor(getattr(ROOT,background_samples[sample][1]))
        histogram.SetFillColor(getattr(ROOT,background_samples[sample][1]))
        histogram.SetFillStyle(cosmetics['background_fill_style'])
                
    elif (sample in signal_samples):
        if (signal_samples[sample][4] == 'line'):
            histogram.SetLineColor(getattr(ROOT,signal_samples[sample][3]))
            histogram.SetFillColor(getattr(ROOT,signal_samples[sample][3]))
            histogram.SetLineWidth(signal_samples[sample][5])
            
    elif (signal_samples[sample][4] == 'stack'):
        histogram.SetLineColor(getattr(ROOT,signal_samples[sample][3]))
        histogram.SetFillColor(getattr(ROOT,signal_samples[sample][3]))
        histogram.SetFillStyle(cosmetics['background_fill_style'])

    else:
        sys.exit('Error - must select either line or stack for signal_sample '+sample+'.  Quitting.')

    return histogram
## end of get_histogram

def make_legend():
    stack_plot_legend = TLegend(cosmetics['legend_x1'],cosmetics['legend_y1'],cosmetics['legend_x2'],cosmetics['legend_y2'])
    stack_plot_legend.SetFillColor(getattr(ROOT,cosmetics['legend_fill_color']))
    stack_plot_legend.SetBorderSize(cosmetics['legend_border_size'])
    stack_plot_legend.SetNColumns(cosmetics['legend_n_columns'])
    
    return stack_plot_legend
## end of make_legend

def make_info_tex_objects(lepton_category, jet_tag_category):
    luminosity_info_tex = TLatex()
    luminosity_info_tex.SetNDC()
    luminosity_info_tex.SetTextFont(cosmetics['lumi_text_font'])
    luminosity_info_tex.SetTextSize(cosmetics['lumi_text_size'])
    luminosity_info_tex.SetTitle(lepton_categories[lepton_category]+jet_tag_categories[jet_tag_category]+lumi_era['lumi_era_string'])

    selection_info_tex = TLatex()
    selection_info_tex.SetNDC()
    selection_info_tex.SetTextFont(cosmetics['selection_text_font'])
    selection_info_tex.SetTextSize(cosmetics['selection_text_size'])
    selection_info_tex.SetTitle(lepton_categories[lepton_category]+jet_tag_categories[jet_tag_category])

    SF_info_tex = TLatex()
    SF_info_tex.SetNDC()
    SF_info_tex.SetTextFont(cosmetics['SF_text_font'])
    SF_info_tex.SetTextSize(cosmetics['SF_text_size'])
    SF_info_tex.SetTitle(str(signal_samples[signal_sample_keys[0]][1])+' x '+str(signal_samples[signal_sample_keys[0]][5]))

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
    title_string = '%s;%s;%s' % ('', '', 'Events')
    stack_plot.SetTitle(title_string)
    stack_plot.SetMinimum(cosmetics['stack_minimum'])
    stack_plot.SetMaximum(max(cosmetics['stack_lowest_maximum'],plot_max*cosmetics['stack_maximum_factor']))
    if (draw_options['log_scale']):
        stack_plot.SetMinimum(cosmetics['stack_minimum_log_scale'])
        stack_plot.SetMaximum(max(cosmetics['stack_lowest_maximum_log_scale'],plot_max*cosmetics['stack_maximum_factor_log_scale'])) 

    return stack_plot
## end configure_my_stack

def configure_canvases(top_canvas, bottom_canvas):
    top_canvas.SetLeftMargin(cosmetics['top_canvas_left_margin'])
    bottom_canvas.SetLeftMargin(cosmetics['bottom_canvas_left_margin'])
    
    top_canvas.SetRightMargin(cosmetics['top_canvas_right_margin'])
    bottom_canvas.SetRightMargin(cosmetics['bottom_canvas_right_margin'])

    top_canvas.SetTopMargin(cosmetics['top_canvas_top_margin'])      
    bottom_canvas.SetBottomMargin(cosmetics['bottom_canvas_bottom_margin'])
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

    ggg.SetLineColor(getattr(ROOT,cosmetics['ggg_line_color']))
    ggg.SetMarkerStyle(cosmetics['ggg_marker_style'])
    ggg.SetLineWidth(cosmetics['ggg_line_width'])
    ggg.SetMarkerSize(cosmetics['ggg_marker_size'])

    return ggg
## end configure_ratio_histogram

def make_ratio_histogram(nBins, xMin, xMax, mc_error_histogram, data_histogram, signal_histogram):
        ratio_histogram = TH1F('ratio_histogram', '', nBins, xMin, xMax)
        ratio_error_histogram = TH1F('ratio_error_histogram', '', nBins, xMin, xMax)

        for i in range(1, nBins+1):
                mc_value = mc_error_histogram.GetBinContent(i)
                if (not draw_options['blinded']): data_value = data_histogram.GetBinContent(i) 
                if (draw_options['blinded']): data_value = signal_histogram.GetBinContent(i) 
                mc_error = mc_error_histogram.GetBinError(i)
                if (not draw_options['blinded']): data_error = data_histogram.GetBinError(i) 
                if (draw_options['blinded']): data_error = signal_histogram.GetBinError(i) 

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
    ratio_histogram.SetMinimum(cosmetics['ratio_hist_min'])
    ratio_histogram.SetMaximum(cosmetics['ratio_hist_max'])
    ratio_title_string = '%s;%s;%s' % ('', distributions[distribution][0], 'Data/MC') 
    ratio_histogram.SetTitle(ratio_title_string) 
    ratio_histogram.GetYaxis().SetTitleSize(cosmetics['ratio_hist_y_axis_title_size'])
    ratio_histogram.GetYaxis().SetTitleOffset(cosmetics['ratio_hist_y_axis_title_offset'])
    ratio_histogram.GetYaxis().CenterTitle()
    ratio_histogram.GetYaxis().SetLabelSize(cosmetics['ratio_hist_y_axis_label_size'])
    ratio_histogram.GetYaxis().SetNdivisions(cosmetics['ratio_hist_y_axis_Ndivisions'])
        
    ratio_histogram.GetXaxis().SetLabelSize(cosmetics['ratio_hist_x_axis_label_size']) 
    ratio_histogram.GetXaxis().SetLabelOffset(cosmetics['ratio_hist_x_axis_label_offset']) 
    ratio_histogram.GetXaxis().SetTitleOffset(cosmetics['ratio_hist_x_axis_title_offset'])
    ratio_histogram.GetXaxis().SetTitleSize(cosmetics['ratio_hist_x_axis_title_size']) 

    ratio_histogram.SetLineColor(getattr(ROOT,cosmetics['ratio_hist_line_color']))
    ratio_histogram.SetMarkerColor(getattr(ROOT,cosmetics['ratio_hist_marker_color']))     

    if (draw_options['blinded']):
        ratio_histogram.SetLineColor(getattr(ROOT,cosmetics['ratio_hist_line_color_blind']))     
        ratio_histogram.SetMarkerColor(getattr(ROOT,cosmetics['ratio_hist_marker_color_blind']))

    return ratio_histogram
## end configure_ratio_histogram

def configure_ratio_error_histogram(ratio_error_histogram):
    ratio_error_histogram.SetMarkerColor(getattr(ROOT,cosmetics['ratio_err_hist_marker_color']))
    ratio_error_histogram.SetFillColor(getattr(ROOT,cosmetics['ratio_err_hist_fill_color']))

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
        if not draw_options['blinded']:
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
    g_ratio.SetLineColor(getattr(ROOT,cosmetics['g_ratio_line_color']))
    g_ratio.SetLineWidth(cosmetics['g_ratio_line_width'])

    return g_ratio
## end configure_data_ratio_asymmetric_errors
        
if __name__ == '__main__':
        main()
        
