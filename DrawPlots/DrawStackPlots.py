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
                drawStackPlot (lepton_category, jet_tag_category, distribution)

    if args.web:
        print '\nFinished processing.  Plots will be posted to: http://www.nd.edu/~%s/stack_plots/%s/' % (os.environ['USER'], in_out_files['input_file_label'])

def drawStackPlot (lepton_category, jet_tag_category, distribution):
    myStack = THStack("theStack", "")

    legForStack = makeLegend()
    
    infoStrings = makeInfoStrings( lepton_category, jet_tag_category )
    
    SFInfoLatex = infoStrings[5]
    SFInfo = infoStrings[4]
    selectionInfoLatex = infoStrings[3]
    catInfo = infoStrings[2]
    myLumiTex = infoStrings[1]
    myLumiString = infoStrings[0]

    histoStorageList = {}
    MCSum = 0.0
    signalSum = 0.0
    dataSum = 0.0
        
    ## Draw the background sample histograms, put in legend
    for sample in background_samples:
        for systematic in systematics:
            origHist = getHist( distribution, systematic, sample, lepton_category, jet_tag_category )
            histoStorageList[sample+"_"+systematic] = origHist.Clone()

            if (systematic == "nominal"):
                iHist = origHist.Clone("stack")
                MCSum += iHist.Integral()
                sample_info = plot_helper.SampleInformation(sample)
                xsec_frac_error = sample_info.x_section / sample_info.x_section_error
                myStack.Add(iHist, "hist")
                legForStack.AddEntry(iHist, '%s (%0.1f)' % (background_samples[sample][0], iHist.Integral()), 'f')

    ## Draw the signal sample histogram(s), put in legend
    for sample in signal_samples:
        origHist = getHist( distribution, "nominal", sample, lepton_category, jet_tag_category ) 
        histoStorageList[sample+"_"+systematic] = origHist.Clone()

        if ( signal_samples[sample][4] == "line" ):
            iSig = origHist.Clone("signal")
        elif ( signal_samples[sample][4] == "stack" ):
            iSig = origHist.Clone("stack")
        else:
            sys.exit("For signal, must be line or stack")
                
        signalSum = iSig.Integral()

        if ( signalSum > 0 and signal_samples[sample][5] == "norm" ):
            iSig.Scale(MCSum/signalSum)
        elif ( signalSum > 0 ):
            iSig.Scale(signal_samples[sample][5])

        if ( signal_samples[sample][4] == "stack" ):
            myStack.Add(iSig, "hist")

        if (signalSum > 0):
            legForStack.AddEntry(iHist, '%s (%0.1f x %0.1f)' % (signal_samples[sample][2], signalSum, (iSig.Integral()/signalSum)), "l")
        else:
            legForStack.AddEntry(iHist, '%s (0.0x1.0)' % signal_samples[sample][2], 'l')

    ## Draw the data histogram, put in legend
    if not draw_options['blinded']:
        origHist = getHist( distribution, systematic, "data", lepton_category, jet_tag_category )
        histoStorageList['data'] = origHist.Clone()

        iData = origHist.Clone("data")
        dataSum = iData.Integral()
        legForStack.AddEntry(iData, "Data (%.0f) " % dataSum, "lpe")

    lumi_error = lumi_era['lumi_error']     
    trigSF_error = lumi_era['trig_SF_error']        
    lumi_trigSF_error = math.sqrt(math.pow(lumi_error,2)+math.pow(trigSF_error,2))

    try:
        nBins = myStack.GetStack().Last().GetNbinsX()
        xMin = myStack.GetStack().Last().GetXaxis().GetXmin()
        xMax = myStack.GetStack().Last().GetXaxis().GetXmax()
    except: sys.exit("No histograms in stack.  Quitting.")

    # Create a histogram with the error bars for the MC stack
    MCErrHist = TH1F("MCErrHist", "", nBins, xMin, xMax)
    for i in range(1, nBins+1):
        MCErrHist.SetBinContent(i,myStack.GetStack().Last().GetBinContent(i))
        bin_error_squared = math.pow(lumi_trigSF_error*myStack.GetStack().Last().GetBinContent(i),2)
        for sample in background_samples:
            for systematic in systematics:
                bin_error_squared += math.pow(histoStorageList[sample+"_"+systematic].GetBinContent(i) - histoStorageList[sample+"_nominal"].GetBinContent(i),2)
        MCErrHist.SetBinError(i,math.sqrt(bin_error_squared))

    MCErrHist.SetFillStyle(cosmetics['mc_err_fill_style'])
    MCErrHist.SetFillColor(getattr(ROOT,cosmetics['mc_err_fill_color']))

    legForStack.AddEntry(MCErrHist, "Sum MC (%0.1f) " % (MCSum + signalSum), "f")

    plotMax = myStack.GetMaximum()
    if ( iSig ): plotMax = max(plotMax,iSig.GetMaximum())   
    if (not draw_options['blinded']): plotMax = max(plotMax,iData.GetMaximum())

    myStack = configureMyStack(myStack, plotMax)
    myCanvasLin = TCanvas(distribution+"Lin", distribution, cosmetics['canvas_lin_min'], cosmetics['canvas_lin_max'])

    gStyle.SetPadBorderMode(cosmetics['pad_border_mode'])
    gStyle.SetFrameBorderMode(cosmetics['frame_border_mode'])

    myCanvasLin.cd()

    upLin = TPad("upLin", "up", cosmetics['up_lin_x1'], cosmetics['up_lin_y1'], cosmetics['up_lin_x2'], cosmetics['up_lin_y2'])
    downLin =  TPad ("downLin", "down", cosmetics['down_lin_x1'], cosmetics['down_lin_y1'], cosmetics['down_lin_x2'], cosmetics['down_lin_y2'])

    (upLin, downLin) = configureUpDownLin(upLin, downLin)

    upLin.Draw()
    downLin.Draw()

    upLin.cd()
    if (draw_options['log_scale']):
        gPad.SetLogy()

    gPad.SetBottomMargin(cosmetics['pad_bottom_margin'])
#    gPad.Modified()

    myStack.Draw()
    ## For some reason can't be done before Draw()
    myStack.GetYaxis().SetTitleSize(cosmetics['stack_y_axis_title_size']) 
    myStack.GetYaxis().SetTitleOffset(cosmetics['stack_y_axis_title_offset'])

    MCErrHist.Draw(cosmetics['MCErrHist_draw_style'])
        
    iSig.Draw(cosmetics['iSig_draw_style'])

    ## asymmetrical poisson errors for data
    ggg = TGraphAsymmErrors(iData); 
    ggg = configureDataAsymmetricErrors(ggg)

    if (not draw_options['blinded']): ggg.Draw(cosmetics['ggg_draw_style']) 

    ## calculate the KS test result, put it somewhere
    if (draw_options['KS_test']):
        ksResult = iData.KolmogorovTest(MCErrHist)
        myLumiString = myLumiString + " (KS = %0.2f)" % (ksResult)

    if (draw_options['draw_legend']): legForStack.Draw()
    myLumiTex.DrawLatex(cosmetics['lumi_text_first'], cosmetics['lumi_text_second'], myLumiString) 
    if draw_options['selection_info']: selectionInfoLatex.DrawLatex(cosmetics['selection_text_first'], cosmetics['selection_text_second'], catInfo)
#     if draw_options['SF_info']:
#         if (dist.find("CFMlpANN") != -1):
#             SFInfoLatex.DrawLatex(cosmetics['SF_info_min'], cosmetics['SF_info_max'], SFInfo)
        
    downLin.cd()
#     gPad.SetTopMargin(cosmetics['pad_top_margin'])
#     gPad.SetTickx()
#     gPad.Modified()

    (ratioHist, ratioErrHist) = makeRatioHist(nBins, xMin, xMax, MCErrHist, iData, iSig)

    ratioHist = configureRatioHist(ratioHist, distribution)
    ratioErrHist = configureRatioErrHist(ratioErrHist)
    
    ratioHist.DrawCopy() 
    if (not draw_options['blinded']):
        ratioErrHist.DrawCopy("e2same")
        ratioHist.Draw("sameaxis") 

    ## asymmetrical poisson errors for data in ratio plot
    gRatio = makeDataRatioAsymmetricErrors (nBins, xMin, xMax, ggg, iData, iSig, myStack)
    gRatio = configureDataRatioAsymmetricErrors (gRatio)
          
    if (not draw_options['blinded']): gRatio.Draw("psame") 
        
    l = TLine()
    l.DrawLine(xMin,1.,xMax,1.)

    if not os.path.exists(in_out_files['output_file_location']+lepton_category+"_"+jet_tag_category):
        os.mkdir(in_out_files['output_file_location']+lepton_category+"_"+jet_tag_category)

    plot_name = '%s_%s/%s' % (lepton_category, jet_tag_category, distribution)

    if (draw_options['save_png']): myCanvasLin.SaveAs(in_out_files['output_file_location']+plot_name+'.png')
    if (draw_options['save_pdf']): myCanvasLin.SaveAs(in_out_files['output_file_location']+plot_name+'.pdf')

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
    upLin.Close()
    downLin.Close()
    myStack.Delete()
    myCanvasLin.Close()
## end drawStackPlot

## Gets a single histogram
def getHist( distribution, systematic, sample, lepton_category, jet_tag_category ):
    targetHist = None
    if sample == 'data':
        sample = plot_helper.get_data_sample_name(lepton_category)

    if systematic == "nominal" or sample == 'data':
        namePlusCycle = "%s;1" % (sample+"_"+lepton_category+"_"+jet_tag_category+"_"+distribution)
    else:
        namePlusCycle = "%s_%s;1" % (sample+"_"+lepton_category+"_"+jet_tag_category+"_"+distribution, systematic)

    rootFile = TFile(in_out_files['input_file_location']+lepton_category+"/"+lepton_category+"_"+jet_tag_category+"_"+sample+"_"+in_out_files['input_file_label']+".root")

    targetHist = rootFile.Get(namePlusCycle).Clone()
        
    if (targetHist == None):
        print "Oops! Error looking for histo %s, exiting..." % (distribution)
        sys.exit()

    targetHist.UseCurrentStyle() ##What does this do?
    targetHist.SetDirectory(0) ##Decouples histogram from root file
        
    if ( sample == "MuEG" or sample == "DoubleMu" or sample == "DoubleElectron"):           
        targetHist.SetLineColor(getattr(ROOT,cosmetics['data_line_color']))
        targetHist.SetMarkerColor(getattr(ROOT,cosmetics['data_marker_color']))
        targetHist.SetFillColor(getattr(ROOT,cosmetics['data_fill_color']))
        targetHist.SetLineWidth(cosmetics['data_line_width'])
        targetHist.SetMarkerStyle(cosmetics['data_marker_style'])
        targetHist.SetMarkerSize(cosmetics['data_marker_size'])

    elif ( sample in background_samples ):
        targetHist.SetLineColor(getattr(ROOT,background_samples[sample][1]))
        targetHist.SetFillColor(getattr(ROOT,background_samples[sample][1]))
        targetHist.SetFillStyle(cosmetics['background_fill_style'])
                
    elif ( sample in signal_samples ):
        if ( signal_samples[sample][4] == "line" ):
            targetHist.SetLineColor(getattr(ROOT,signal_samples[sample][3]))
            targetHist.SetFillColor(getattr(ROOT,signal_samples[sample][3]))
            targetHist.SetLineWidth(signal_samples[sample][5])
            
    elif ( signal_samples[sample][4] == "stack" ):
        targetHist.SetLineColor(getattr(ROOT,signal_samples[sample][3]))
        targetHist.SetFillColor(getattr(ROOT,signal_samples[sample][3]))
        targetHist.SetFillStyle(cosmetics['background_fill_style'])

    else:
        sys.exit("Error - must select either line or stack for signal_sample "+sample+".  Quitting.")

    return targetHist
## end of getHist

def makeLegend():
    legForStack = TLegend(cosmetics['legend_x1'],cosmetics['legend_y1'],cosmetics['legend_x2'],cosmetics['legend_y2'])
    legForStack.SetFillColor(getattr(ROOT,cosmetics['legend_fill_color']))
    legForStack.SetBorderSize(cosmetics['legend_border_size'])
    legForStack.SetNColumns(cosmetics['legend_n_columns'])
    
    return legForStack
## end of makeLegend

def makeInfoStrings( lepton_category, jet_tag_category ):
    myLumiString = lepton_categories[lepton_category]+jet_tag_categories[jet_tag_category]+lumi_era['lumi_era_string']
    
    myLumiTex = TLatex()
    myLumiTex.SetNDC()
    myLumiTex.SetTextFont(cosmetics['lumi_text_font'])
    myLumiTex.SetTextSize(cosmetics['lumi_text_size'])

    catInfo = lepton_categories[lepton_category]+jet_tag_categories[jet_tag_category]
    selectionInfoLatex = TLatex()
    selectionInfoLatex.SetNDC()
    selectionInfoLatex.SetTextFont(cosmetics['selection_text_font'])
    selectionInfoLatex.SetTextSize(cosmetics['selection_text_size'])

    SFInfo = str(signal_samples[signal_sample_keys[0]][1])+" x "+str(signal_samples[signal_sample_keys[0]][5])
    SFInfoLatex = TLatex()
    SFInfoLatex.SetNDC()
    SFInfoLatex.SetTextFont(cosmetics['SF_text_font'])
    SFInfoLatex.SetTextSize(cosmetics['SF_text_size'])

    return myLumiString, myLumiTex, catInfo, selectionInfoLatex, SFInfo, SFInfoLatex
## end of makeInfoStrings

def moveExtraIntoHist (hist):
    """Move over/underflow bins into the histogram"""
        
    numBins = hist.GetNbinsX()
    hist.SetBinContent(1, hist.GetBinContent(0) + hist.GetBinContent(1))
    hist.SetBinContent(0,0)
    hist.SetBinContent(numBins, hist.GetBinContent(numBins) + hist.GetBinContent(numBins+1))
    hist.SetBinContent(numBins+1, 0)
        
    return hist
## end moveExtraIntoHist()

def configureMyStack(myStack, plotMax):
    titleString = "%s;%s;%s" % ("", "", "Events")
        
    myStack.SetTitle(titleString)
    myStack.SetMinimum(cosmetics['stack_minimum'])
    myStack.SetMaximum(max(cosmetics['stack_lowest_maximum'],plotMax*cosmetics['stack_maximum_factor']))
    if (draw_options['log_scale']):
        myStack.SetMinimum(cosmetics['stack_minimum_log_scale'])
        myStack.SetMaximum(max(cosmetics['stack_lowest_maximum_log_scale'],plotMax*cosmetics['stack_maximum_factor_log_scale'])) 

    return myStack
## end configureMyStack

def configureUpDownLin( upLin, downLin ):
    upLin.SetLeftMargin(cosmetics['up_lin_left_margin'])
    downLin.SetLeftMargin(cosmetics['down_lin_left_margin'])
    
    upLin.SetRightMargin(cosmetics['up_lin_right_margin'])
    downLin.SetRightMargin(cosmetics['down_lin_right_margin'])

    upLin.SetTopMargin(cosmetics['up_lin_top_margin'])      
    downLin.SetBottomMargin(cosmetics['down_lin_bottom_margin'])
    downLin.SetTickx()

    upLin.Modified()
    downLin.Modified()
                
    return upLin, downLin
## end configureUpDownLin

def configureDataAsymmetricErrors( ggg ):
    alpha = 1 - 0.6827
    NBin = ggg.GetN()
    for iBin in range(0, NBin):
        NN = ggg.GetY()[iBin]
        if (NN==0):
            LOW = 0
        else: 
            LOW =  Math.gamma_quantile(alpha/2,NN,1.)
        UP =  Math.gamma_quantile_c(alpha/2,NN+1,1)
        ggg.SetPointEYlow(iBin, NN-LOW)
        ggg.SetPointEYhigh(iBin, UP-NN)

    ggg.SetLineColor(getattr(ROOT,cosmetics['ggg_line_color']))
    ggg.SetMarkerStyle(cosmetics['ggg_marker_style'])
    ggg.SetLineWidth(cosmetics['ggg_line_width'])
    ggg.SetMarkerSize(cosmetics['ggg_marker_size'])

    return ggg
## end configureRatioHist

def makeRatioHist( nBins, xMin, xMax, MCErrHist, iData, iSig ):
        ratioHist = TH1F("ratioHist", "", nBins, xMin, xMax)
        ratioErrHist = TH1F("ratioErrHist", "", nBins, xMin, xMax)

        for i in range(1, nBins+1):
                MCVal = MCErrHist.GetBinContent(i)
                if (not draw_options['blinded']): DataVal = iData.GetBinContent(i) 
                if (draw_options['blinded']): DataVal = iSig.GetBinContent(i) 
                MCErr = MCErrHist.GetBinError(i)
                if (not draw_options['blinded']): DataErr = iData.GetBinError(i) 
                if (draw_options['blinded']): DataErr = iSig.GetBinError(i) 

                if (MCVal !=0 and DataVal !=0):
                        ratioVal = DataVal/MCVal
                        ratErr = ratioVal*DataErr/DataVal
                        ratErrMC = MCErr/MCVal
                        if ratioVal > 2:
                                ratioVal = 2
                elif (MCVal == 0 and DataVal != 0):
                        ratioVal = 2
                        ratErr = 2
                elif (MCVal != 0 and DataVal == 0):
                        ratErrMC = MCErr/MCVal
                if (DataVal != 0):
                        ratioHist.SetBinContent(i,ratioVal)
                        ratioHist.SetBinError(i,ratErr)
                if (MCVal != 0):
                        ratioErrHist.SetBinContent(i,1)
                        ratioErrHist.SetBinError(i,ratErrMC)

        return ratioHist, ratioErrHist
## end makeRatioHist

def configureRatioHist( ratioHist , distribution ):
    ratioHist.SetMinimum(cosmetics['ratio_hist_min'])
    ratioHist.SetMaximum(cosmetics['ratio_hist_max'])
    ratiotitleString = "%s;%s;%s" % ("", distributions[distribution][0], "Data/MC") 
    ratioHist.SetTitle(ratiotitleString) 
    ratioHist.GetYaxis().SetTitleSize(cosmetics['ratio_hist_y_axis_title_size'])
    ratioHist.GetYaxis().SetTitleOffset(cosmetics['ratio_hist_y_axis_title_offset'])
    ratioHist.GetYaxis().CenterTitle()
    ratioHist.GetYaxis().SetLabelSize(cosmetics['ratio_hist_y_axis_label_size'])
    ratioHist.GetYaxis().SetNdivisions(cosmetics['ratio_hist_y_axis_Ndivisions'])
        
    ratioHist.GetXaxis().SetLabelSize(cosmetics['ratio_hist_x_axis_label_size']) 
    ratioHist.GetXaxis().SetLabelOffset(cosmetics['ratio_hist_x_axis_label_offset']) 
    ratioHist.GetXaxis().SetTitleOffset(cosmetics['ratio_hist_x_axis_title_offset'])
    ratioHist.GetXaxis().SetTitleSize(cosmetics['ratio_hist_x_axis_title_size']) 

    ratioHist.SetLineColor(getattr(ROOT,cosmetics['ratio_hist_line_color']))
    ratioHist.SetMarkerColor(getattr(ROOT,cosmetics['ratio_hist_marker_color']))     

    if (draw_options['blinded']):
        ratioHist.SetLineColor(getattr(ROOT,cosmetics['ratio_hist_line_color_blind']))     
        ratioHist.SetMarkerColor(getattr(ROOT,cosmetics['ratio_hist_marker_color_blind']))

    return ratioHist
## end configureRatioHist

def configureRatioErrHist( ratioErrHist ):
    ratioErrHist.SetMarkerColor(getattr(ROOT,cosmetics['ratio_err_hist_marker_color']))
    ratioErrHist.SetFillColor(getattr(ROOT,cosmetics['ratio_err_hist_fill_color']))

    return ratioErrHist
## end configureRatioErrHist
        
def makeDataRatioAsymmetricErrors ( nBins, xMin, xMax, ggg, iData, iSig , myStack ):
    ratioMax = 2.3
    gRatio = TGraphAsymmErrors(ggg.GetN())
    for jBin in range(0, gRatio.GetN()):
        xPoint = iData.GetBinCenter(jBin+1)
        xWidth = 0.5*iData.GetBinWidth(jBin+1)
        yG = ggg.GetY()[jBin]
        yG_low  = ggg.GetEYlow()[jBin]
        yG_high = ggg.GetEYhigh()[jBin]
        if not draw_options['blinded']:
            yData = iData.GetBinContent(jBin+1)
        else:
            yData = iSig.GetBinContent(jBin+1)
                
        yBkg = myStack.GetStack().Last().GetBinContent(jBin+1)
                
        if (yBkg>0.):
            yG_ratio = yG/yBkg
            yG_ratio_low = yG_low/yBkg
            yG_ratio_high = yG_high/yBkg
        else:
            yG_ratio = 0.
            yG_ratio_low = 0.
            yG_ratio_high = 0.
                        
        if (yData>0):
            gRatio.SetPoint(jBin, xPoint, yG_ratio )
            gRatio.SetPointEYlow(jBin, yG_ratio_low)
            gRatio.SetPointEYhigh(jBin, yG_ratio_high)                        
            gRatio.SetPointEXlow(jBin, xWidth)
            gRatio.SetPointEXhigh(jBin, xWidth)

            if (yG_ratio>ratioMax and (yG_ratio - yG_ratio_low) < ratioMax):
                minner = yG_ratio_low - (yG_ratio - ratioMax-0.0001)
                gRatio.SetPoint(jBin, xPoint, ratioMax-0.0001 )
                gRatio.SetPointEYlow(jBin, minner)

    return gRatio
## end makeDataRatioAsymmetricErrors

def configureDataRatioAsymmetricErrors ( gRatio ):
    gRatio.SetLineColor(getattr(ROOT,cosmetics['gRatio_line_color']))
    gRatio.SetLineWidth(cosmetics['gRatio_line_width'])

    return gRatio
## end configureDataRatioAsymmetricErrors
        
if __name__ == '__main__':
        main()
        
