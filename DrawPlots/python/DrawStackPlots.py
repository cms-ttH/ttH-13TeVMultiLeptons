#!/usr/bin/env python
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
from ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper import *
## Set up the parser for the .cfg files
## config is mostly options that change the substance of what is displayed
config = ConfigParser()
config.read('stack_plot_configuration.cfg')

## config_cosmetics is mostly options that change the style of the stack plot
config_cosmetics = ConfigParser()
config_cosmetics.read('stack_plot_cosmetics.cfg')

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


def main ():

    ## Import some potential useful things
	import sys, ConfigParser, os, string, commands, time
	import math
	from optparse import OptionParser
    ## import the root libraries; with this import
    ## you won't need to prefix your root objects with ROOT
	from ROOT import *
	## Done with imports

	myStack = THStack("theStack", "")

	for lepton_category in lepton_categories:
		for jet_tag_category in jet_tag_categories:
			for distribution in distributions:
				print lepton_category+"	 "+jet_tag_category+"  "+distribution
				print lepton_categories[lepton_category]
				print jet_tag_categories[jet_tag_category]
				print distributions[distribution][0]
				print ''
 				drawStackPlot (lepton_category, jet_tag_category, distribution)



def drawStackPlot (lepton_category, jet_tag_category, distribution):

	print "drawing distribution %s with jet selection printing name %s" % (distribution, jet_tag_categories[jet_tag_category])
	myStack = THStack("theStack", "")

	legForStack = makeLegend()

	infoStrings = makeInfoStrings( lepton_category, jet_tag_category )

	SFInfoLatex = infoStrings[5]
	SFInfo = infoStrings[4]
	selectionInfoLatex = infoStrings[3]
	catInfo = infoStrings[2]
	myLumiTex = infoStrings[1]
	myLumiString = infoStrings[0]

	print "myLumiString = "+myLumiString
	print "catInfo = "+catInfo
	print "SFInfo = "+SFInfo

	histoStorageList = {}
	MCSum = 0.0
	totalMCSum = 0.0
	signalSum = 0.0
	dataSum = 0
	
	sys.exit("Done for now.  Quitting.")
	## Draw the background sample histograms, put in legend
	for sample in background_samples:

 		origHist = getHist( distribution, systematic, sample, lepton_category, jet_tag_category, False )

		iHist = origHist.Clone("stack")
		   
		histoStorageList[sample+"_"+systematic] = origHist
		   
		MCSum += iHist.Integral()
		totalMCSum += iHist.Integral()
		xsec_frac_error = background_samples[sample][1]/background_samples[sample][0]

		myStack.Add(iHist, "hist")
		   
		legForStack.AddEntry(iHist, background_samples[sample][2]+" ("+str(round(MCSum,1))+")", "f")


	## Draw the signal sample histogram(s), put in legend
	for sample in signal_samples:

		origHist = getHist( distribution, systematic, sample, lepton_category, jet_tag_category, False ) 

		iSig = origHist.Clone("signal")
		
		signalSum = iSig.Integral()
		signalError = math.pow(iSig.GetBinError(1),2)

		if ( signalSum > 0 and signal_samples[distribution][6] == 'norm' ):
			iSig.Scale(MCSum/signalSum)
		elif ( signalSum > 0 ):
			iSig.Scale(signal_samples[distribution][6])

		histoStorageList[sample+"_"+systematic] = origHist

		if ( signalSum > 0 ):
			legForStack.AddEntry(iHist, signal_samples[sample][2]+" ("+str(round(signalSum,1))+"x"+str(round(iSig.Integral()/signalSum,1))+")", "l")
		else:
			legForStack.AddEntry(iHist, signal_samples[sample][2]+" (0.0x1.0)", "l") 

	## Draw the data histogram, put in legend
	if not draw_options['blinded']:

		origHist = getHist( distribution, systematic, sample, lepton_category, jet_tag_category, False )

		iData = origHist.Clone("data")

		dataSum = iData.Integral()

		legForStack.AddEntry(iData, "Data ("+str(round(dataSum,0))+")", "lpe")

		histoStorageList["data"] = iData.Clone("data_obs_CFMlpANN_%s" % (jet_tag_categories[jet_tag_category])  )


	lumi_error = lumi_era[lumi_error]	
	trigSF_error = lumi_era[trig_SF_error]	
	lumi_trigSF_error = math.sqrt(math.pow(lumi_error,2)+math.pow(trigSF_error,2))

	try:
		nBins = myStack.GetStack().Last().GetNbinsX()
		xMin = myStack.GetStack().Last().GetXmin()
		xMax = myStack.GetStack().Last().GetXmax()
	except: sys.exit("No histograms in stack.  Quitting.")

	# Create a histogram with the error bars for the MC stack
	MCErrHist = TH1F("MCErrHist", "", nBins, xMin, xMax)
	for i in range(1, nBins+1):
		MCErrHist.SetBinContent(i,myStack.GetStack().Last().GetBinContent(i))
		MCErrHist.SetBinError(i,math.sqrt(math.pow(myStack.GetStack().Last().GetBinError(i),2)+math.pow(lumi_trigSF_error*myStack.GetStack().Last().GetBinContent(i),2)))

	MCErrHist.SetFillStyle(cosmetics['mc_err_fill_style'])
	MCErrHist.SetFillColor(cosmetics['mc_err_fill_color'])
	totalMCErr = math.pow(MCErrHist.GetBinError(1),2)

	legForStack.AddEntry(MCErrHist, "Sum MC ("+str(round(totalMCSum,1))+")", "f")

	theDataHisto = iData.Clone()

	plotMax = myStack.GetMaximum()
	if ( iSig ): plotMax = max(plotMax,iSig.GetMaximum())	
	if (not draw_options['blinded']): plotMax = max(plotMax,theDataHisto.GetMaximum())
	
	myStack = configureMyStack(myStack)

	myCanvasLin = TCanvas(dist+"Lin", dist, cosmetics['canvas_lin_min'], cosmetics['canvas_lin_max'])

	gStyle.SetPadBorderMode(cosmetics['pad_border_mode'])
	gStyle.SetFrameBorderMode(cosmetics['frame_border_mode'])

	myCanvasLin.cd()

	upLin = TPad("upLin", "up", cosmetics['up_lin_x1'], cosmetics['up_lin_y1'], cosmetics['up_lin_x2'], cosmetics['up_lin_y2'])
	downLin =  TPad ("downLin", "down", cosmetics['down_lin_x1'], cosmetics['down_lin_y1'], cosmetics['down_lin_x2'], cosmetics['down_lin_y2'])

	downLin = configureUpDownLin( upLin, downLin )[1]
	upLin = configureUpDownLin( upLin, downLin )[0]

	upLin.Draw()
	downLin.Draw()

	if (draw_options['log_scale']):
		upLin.cd()
		gPad.SetLogy()

	upLin.cd()
	gPad.SetBottomMargin(cosmetics['pad_bottom_margin'])
	gPad.Modified()

	myStack.Draw()

	MCErrHist.Draw(cosmetics['MCErrHist_draw_style'])
	
	iSig.Draw(cosmetics['iSig_draw_style'])

    ## asymmetrical poisson errors for data
	ggg = configureDataAsymmetricErrors()

	if (not draw_options['blinded']): ggg.Draw(cosmetics['ggg_draw_style']) 

	## calculate the KS test result, put it somewhere
	if (draw_options['KS_test']):
		ksResult = theDataHisto.KolmogorovTest(MCErrHist)
		myLumiString = myLumiString + " (KS = %0.2f)" % (ksResult)

	if (draw_options['draw_legend']): legForStack.Draw()
	myLumiTex.DrawLatex(cosmetics['lumi_text_first'], cosmetics['lumi_text_second'], myLumiString) 
	if draw_options['selection_info']: selectionInfoLatex.DrawLatex(cosmetics['selection_text_first'], cosmetics['selection_text_second'], catInfo)
	if draw_options['SF_info']:
		if (dist.find("CFMlpANN") != -1):
			SFInfoLatex.DrawLatex(cosmetics['SF_info_min'], cosmetics['SF_info_max'], SFInfo)
	
	downLin.cd()
	gPad.SetTopMargin(cosmetics['pad_top_margin'])
	gPad.SetTickx()
	gPad.Modified()

	ratioHist = makeRatioHist()
	ratioHist = configureRatioHist( ratioHist )

	ratioErrHist = makeRatioErrHist()
	ratioErrHist = configureRatioErrHist( ratioErrHist )
		
	ratioHist.DrawCopy() 
	if (not draw_options['blinded']): ratioErrHist.DrawCopy("e2same")		 
	if (not draw_options['blinded']): ratioHist.Draw("sameaxis") 

    ## asymmetrical poisson errors for data in ratio plot
	gRatio = makeDataRatioAsymmetricErrors ( theDataHisto, myStack, ggg )
	gRatio = configureDataRatioAsymmetricErrors ( gRatio )
	  
	if (not draw_options['blinded']): gRatio.Draw("psame") 
	
	l = TLine()
	l.DrawLine(xMin,1.,xMax,1.)

	if not os.path.exists(in_out_files['output_file_location']):
		os.mkdir(in_out_files['output_file_location'])
	if not os.path.exists(in_out_files['output_file_location']+lepton_category+"_"+jet_tag_category):
		os.mkdir(in_out_files['output_file_location']+lepton_category+"_"+jet_tag_category)

	pdfName = "%s/%s_%s/%s.pdf" % (in_out_files['output_file_location'], lepton_category, jet_tag_category, distribution)
	pngName = "%s/%s_%s/%s.png" % (in_out_files['output_file_location'], lepton_category, jet_tag_category, distribution)

	if (draw_options['save_png']): myCanvasLin.SaveAs(pngName)
	if (draw_options['save_pdf']): myCanvasLin.SaveAs(pdfName)

	gPad.Close()
	upLin.Close()
	downLin.Close()
	myStack.Delete()
	myCanvasLin.Close()

## end drawStackPlot


## Gets a single histogram
def getHist(distribution, systematic, sample, lepton_category, jet_tag_category):

	targetHist = None

	if systematic == "nominal" or isData:
		namePlusCycle = "%s;1" % (distribution)
	else:
		namePlusCycle = "%s_%s;1" % (distribution, systematic)

	rootFile = TFile(in_out_files['input_file_location']+lepton_category+"/"+sample+"_"+jet_tag_category+"_"+lepton_category+"_"+in_out_files['input_file_label']+".root")

	targetHist = rootFile.Get(namePlusCycle).Clone()

	if (targetHist == None):
		print "Oops! Error looking for histo %s, exiting..." % (distribution)
		sys.exit()

	targetHist.UseCurrentStyle() ##What does this do?
	
	if ( sample in lepton_categories ):		
		
		targetHist.SetLineColor(cosmetics['data_line_color'])
		targetHist.SetMarkerColor(cosmetics['data_marker_color'])
		targetHist.SetFillColor(cosmetics['data_fill_color'])
		targetHist.SetLineWidth(cosmetics['data_line_width'])
		targetHist.SetMarkerStyle(cosmetics['data_marker_style'])
		targetHist.SetMarkerSize(cosmetics['data_marker_size'])
				
		return targetHist
		
	elif ( sample in background_samples ):
			
		targetHist.SetLineColor(background_samples[sample][3])
		targetHist.SetFillColor(background_samples[sample][3])
		targetHist.SetFillStyle(cosmetics['background_fill_style'])
		
		return targetHist

	elif ( sample in signal_samples ):

		if ( signal_samples[sample][4] == 'line' ):

			targetHist.SetLineColor(signal_samples[sample][3])
			targetHist.SetFillColor(signal_samples[sample][3])
			targetHist.SetLineWidth(signal_samples[sample][5])
			return targetHist
	
		elif ( signal_samples[sample][4] == 'stack' ):

			targetHist.SetLineColor(signal_samples[sample][3])
			targetHist.SetFillColor(signal_samples[sample][3])
			targetHist.SetFillStyle(cosmetics['background_fill_style'])
			return targetHist

		else:
			sys.exit("Error - must select either line or stack for signal_sample "+sample+".  Quitting.")
			
	   		
					
## end of getHist


def makeLegend():

	# Make a legend
	legForStack = TLegend(cosmetics['legend_x1'],cosmetics['legend_y1'],cosmetics['legend_x2'],cosmetics['legend_y2'])
	legForStack.SetFillColor(cosmetics['legend_fill_color'])
	legForStack.SetBorderSize(cosmetics['legend_border_size'])
	legForStack.SetNColumns(cosmetics['legend_n_columns'])
	
	return legForStack

## end of makeLegend

def makeInfoStrings( lepton_category, jet_tag_category ):

	myLumiString = lepton_categories[lepton_category]+jet_tag_categories[jet_tag_category]+lumi_era['lumi_era_string']
	print "myLumiString = "+myLumiString

	myLumiTex = TLatex()
	myLumiTex.SetNDC()
	myLumiTex.SetTextFont(cosmetics['lumi_text_font'])
	myLumiTex.SetTextSize(cosmetics['lumi_text_size'])

	catInfo = lepton_categories[lepton_category]+jet_tag_categories[jet_tag_category]
	print "catInfo = "+catInfo
	selectionInfoLatex = TLatex()
	selectionInfoLatex.SetNDC()
	selectionInfoLatex.SetTextFont(cosmetics['selection_text_font'])
	selectionInfoLatex.SetTextSize(cosmetics['selection_text_size'])

	print "ttH125"
	print signal_sample_keys[0]
	print signal_samples[signal_sample_keys[0]]

	SFInfo = signal_samples[signal_sample_keys[0]][1]+" x "+str(signal_samples[signal_sample_keys[0]][6])
	print "SFInfo = "+SFInfo
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

def configureMyStack(myStack):

	titleString = "%s;%s;%s" % ("", "", "Events")
	
	myStack.SetTitle(titleString)
	myStack.SetMinimum(cosmetics['stack_minimum'])
	myStack.SetMaximum(max(cosmetics['stack_lowest_maximum'],plotMax*cosmetics['stack_maximum_factor']))
	if (draw_options['log_scale']):
		myStack.SetMinimum(cosmetics['stack_minimum_log_scale'])
		myStack.SetMaximum(max(cosmetics['stack_lowest_maximum_log_scale'],plotMax*cosmetics['stack_maximum_factor_log_scale'])) 

	myStack.GetYaxis().SetTitleSize(cosmetics['stack_y_axis_title_size']) 
	myStack.GetYaxis().SetTitleOffset(cosmetics['stack_y_axis_title_offset'])

	return myStack

## end configureMyStack

def configureUpDownLin( upLin, downLin ):

	upLin.SetLeftMargin(cosmetics['up_lin_left_margin'])
	downLin.SetLeftMargin(cosmetics['down_lin_left_margin'])

	upLin.SetRightMargin(cosmetics['up_lin_right_margin'])
	downLin.SetRightMargin(cosmetics['down_lin_right_margin'])

	upLin.SetTopMargin(cosmetics['up_lin_top_margin'])	
	downLin.SetBottomMargin(cosmetics['down_lin_bottom_margin'])

	upLin.Modified()
	downLin.Modified()
		
	return upLin, downLin

## end configureUpDownLin

def configureDataAsymmetricErrors():

	alpha = 1 - 0.6827
	ggg = TGraphAsymmErrors(theDataHisto);
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

	ggg.SetLineColor(cosmetics['ggg_line_color'])
	ggg.SetMarkerStyle(cosmetics['ggg_marker_style'])
	ggg.SetLineWidth(cosmetics['ggg_line_width'])
	ggg.SetMarkerSize(cosmetics['ggg_marker_size'])

	return ggg
	
## end configureRatioHist

def makeRatioHist():

	ratioHist = None
	## AWB - origHist is nominal, sys_hist_array is array of systematically shifted histograms
	if not draw_options['skip_systematics']:
		ratioHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, 1.0, 0.0)
	else :
		ratioHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, 1.0, 0.0, "off")

	for i in range(1, nBins+1):
		MCVal = myStack.GetStack().Last().GetBinContent(i)
		if (not draw_options['blinded']): DataVal = theDataHisto.GetBinContent(i) 
		if (draw_options['blinded']): DataVal = iSig.GetBinContent(i) 
		MCErr = math.sqrt(math.pow(myStack.GetStack().Last().GetBinError(i),2)+math.pow(lumi_trigSF_error*myStack.GetStack().Last().GetBinContent(i),2))
		if (not draw_options['blinded']): DataErr = theDataHisto.GetBinError(i) 
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

	return ratioHist

## end makeRatioHist

def configureRatioHist( ratioHist ):
		
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

	ratioHist.SetLineColor(cosmetics['ratio_hist_line_color'])	 
	ratioHist.SetMarkerColor(cosmetics['ratio_hist_marker_color'])	 

	if (draw_options['binded']):
		ratioHist.SetLineColor(cosmetics['ratio_hist_line_color_blind'])	   
		ratioHist.SetMarkerColor(cosmetics['ratio_hist_marker_color_blind'])

	return ratioHist

## end configureRatioHist

def makeRatioErrHist():

	ratioErrHist = None
	
	if not draw_options['skip_systematics']:
		ratioErrHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, 1.0, 0.0)
	else :
		ratioErrHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, 1.0, 0.0, "off")

	return ratioErrHist

## end makeRatioErrHist

def configureRatioErrHist( ratioErrHist ):
		
	ratioErrHist.SetMarkerColor(cosmetics['ratio_err_hist_marker_color'])
	ratioErrHist.SetFillColor(cosmetics['ratio_err_hist_fill_color'])

	return ratioErrHist

## end configureRatioErrHist
	
def makeDataRatioAsymmetricErrors ( theDataHisto, myStack, ggg ):

	ratioMax = 2.3
	gRatio = TGraphAsymmErrors(ggg.GetN())
	for	 jBin in range(0, gRatio.GetN()):
		xPoint = theDataHisto.GetBinCenter(jBin+1); 
		xWidth = 0.5*theDataHisto.GetBinWidth(jBin+1);	
		
		yG = ggg.GetY()[jBin];
		yG_low	= ggg.GetEYlow()[jBin];
		yG_high = ggg.GetEYhigh()[jBin];
		yData = theDataHisto.GetBinContent(jBin+1); 
		
		yBkg = myStack.GetStack().Last().GetBinContent(jBin+1);
		
		if (yBkg>0.) :
			
			yG_ratio = yG/yBkg
			yG_ratio_low = yG_low/yBkg
			yG_ratio_high = yG_high/yBkg
		else:
			yG_ratio = 0.
			yG_ratio_low = 0.
			yG_ratio_high = 0.
			
		if (yData>0) :
			gRatio.SetPoint(jBin, xPoint, yG_ratio )
			gRatio.SetPointEYlow(jBin, yG_ratio_low)
			gRatio.SetPointEYhigh(jBin, yG_ratio_high)			  
			gRatio.SetPointEXlow(jBin, xWidth)
			gRatio.SetPointEXhigh(jBin, xWidth)

			if ( yG_ratio>ratioMax and (yG_ratio - yG_ratio_low)<ratioMax ):
				minner = yG_ratio_low - (yG_ratio - ratioMax-0.0001)
				gRatio.SetPoint(jBin, xPoint, ratioMax-0.0001 )
				gRatio.SetPointEYlow(jBin, minner)

	return gRatio
				
## end makeDataRatioAsymmetricErrors

def configureDataRatioAsymmetricErrors ( gRatio ):

	gRatio.SetLineColor(cosmetics['gRatio_line_color'])
	gRatio.SetLineWidth(cosmetics['gRatio_line_width'])

	return gRatio

## end configureDataRatioAsymmetricErrors
	
	

if __name__ == '__main__':
	main()
