
#############################################
#
# myPlots.py
#
# Think of this as a cmssw config file
#
# You will include it in your file that actually
# draws the plots
# 
# It has one function defined
# that returns a list of plot objects
# that have been properly configured.
# The function name is not important...
# you just need to know how to access
# the list of plots from the drawing script
#
# The plot objects are defined in PlotEnv
# and need a dictionary to intialize them
# 
#
#############################################

# load the usual stuff

from ROOT import *
from PlotEnv import *

def getMyPlotsAndrewNorm (lepselection, year, Zmask, charge, jetselection) :


	skipSystematics = False

	dirStr = lepselection+"/"

	rootStr = "_" + year + "_" + Zmask + "_" + charge + "_" + jetselection + "_" + lepselection +".root"

#	defaultLumi = 5288.0
	#defaultLumi = 12187.0
	defaultLumi = 19450.0
	if lepselection.startswith("ThreeMuon"):
		dataStr = dirStr+'DoubleMu_'+  year + "_" + Zmask + "_" + charge + "_" + jetselection +	 "_ThreeMuon.root"

	elif lepselection.startswith("TwoMuonEle"):
		dataStr = dirStr+'DoubleMu_'+  year + "_" + Zmask + "_" + charge + "_" + jetselection +	 "_TwoMuonEle.root"

	elif lepselection.startswith("TwoEleMuon"):
		dataStr = dirStr+'DoubleElectron_'+	 year + "_" + Zmask + "_" + charge + "_" + jetselection +  "_TwoEleMuon.root"

	elif lepselection.startswith("ThreeEle"):
		dataStr = dirStr+'DoubleElectron_'+	 year + "_" + Zmask + "_" + charge + "_" + jetselection +  "_ThreeEle.root"

	elif lepselection.startswith("TwoMuon"):
		dataStr = dirStr+'DoubleMu_'+ year + "_" + Zmask + "_" + charge + "_" + jetselection + "_TwoMuon.root"

	elif lepselection.startswith("TwoEle"):
		dataStr = dirStr+'DoubleElectron_'+	 year + "_" + Zmask + "_" + charge + "_" + jetselection +  "_TwoEle.root"

	elif lepselection.startswith("MuonEle"):
		dataStr = dirStr+'MuEG_' + year + "_" + Zmask + "_" + charge + "_" + jetselection +	 "_MuonEle.root"

	elif lepselection.startswith("SameLep"):
		dataStr = dirStr+'SameLep'+rootStr
	else:
		dataStr = dirStr+'TwoLep'+rootStr


#	 directoryName = "pdf_2012/"+ Zmask + "/" +lepselection+"_"+year + "_" + Zmask + "_" + jetselection
	directoryName = "pdf_2012_53x/"+lepselection+"_"+year + "_" + Zmask + "_" + charge + "_" + jetselection 
	
	groupName = lepselection+"_"+year + "_" + Zmask + "_" + charge + "_" + jetselection

	sys_arrays = {}
	##sys_array['sample'] = [PU, hfSF, lfSF]
	if jetselection.startswith("ge3t"):
		sys_arrays['tt'] = [0.504,7.15,5.07]
		sys_arrays['ttcc'] = [1.81,10.4,0.511]
		sys_arrays['ttbb'] = [0.497,7.05,0.165]
		sys_arrays['t'] = [2.3,7.58,4.42]
		sys_arrays['ttV'] = [10.5,9.57,2.48]
		sys_arrays['diboson'] = [1.11,8.56,3.12]
		sys_arrays['WJets'] = [0,0,0]
		sys_arrays['ZJets'] = [1.29,8.19,4.77]
		sys_arrays['ttH_120'] = [0.99,6.97,0.56]
	elif jetselection.startswith("eq1t"):
		sys_arrays['tt'] = [1.05,5.13,0.108]
		sys_arrays['ttcc'] = [0.647,6.27,0.084]
		sys_arrays['ttbb'] = [0.726,5.22,0.27]
		sys_arrays['t'] = [0.357,5.33,0.358]
		sys_arrays['ttV'] = [10.2,5.56,0.399]
		sys_arrays['diboson'] = [1.8,5.86,0.855]
		sys_arrays['WJets'] = [0,0,0]
		sys_arrays['ZJets'] = [0.415,5.64,1.54]
		sys_arrays['ttH_120'] = [1.47,5.4,0.259]
	else:	 
		sys_arrays['tt'] = [1.05,5.13,0.108]
		sys_arrays['ttcc'] = [0.647,6.27,0.084]
		sys_arrays['ttbb'] = [0.726,5.22,0.27]
		sys_arrays['t'] = [0.357,5.33,0.358]
		sys_arrays['ttV'] = [10.2,5.56,0.399]
		sys_arrays['diboson'] = [1.8,5.86,0.855]
		sys_arrays['WJets'] = [0,0,0]
		sys_arrays['ZJets'] = [0.415,5.64,1.54]
		sys_arrays['ttH_120'] = [1.47,5.4,0.259]


	# Start with an empty list just to get things going
	plotList = []

	# append on an item to the list
	# you can pass it a dictionary with the pieces
	# that you want to intialize
	# yes, we are aware that it looks like cmssw
	
	##Systematic errors in format [JES, PU, hfSF, lfSf]

##	   plotList.append(
##		   PlotInfo(
##		   {'name': 'ttbar',
##			'file': dirStr+'TTJets_TuneZ2_7TeV-madgraph-tauola_'+rootStr,
##			'xsec': 0.1577,
##			'ngen': 52135272,
##			#'fillColor': ROOT.kOrange+10,
##			'fillColor': ROOT.kRed,
##			'fillPattern': 1001,
##			'isNormPerJetBin': 0,}
##		   )
##		   )

	plotList.append(
		PlotInfo(
		{'name': 'WW',
		 'file': dirStr+'ww' +rootStr,
		 'file_JESUp': dirStr+'ww'+rootStr,
		 'file_JESDown': dirStr+'ww'+rootStr,
		 'xsec': 0.0548,#0.0571,
		 'xsec_err': 0.0015,
		 'sys_array': sys_arrays['diboson'],
		 'ngen': 9955089,
#		  'fillColor': ROOT.kCyan+2,
		 'fillColor': ROOT.kAzure+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'WZ',
		 'file': dirStr+'wz' +rootStr,
		 'file_JESUp': dirStr+'wz'+rootStr,
		 'file_JESDown': dirStr+'wz'+rootStr,
		 'xsec': 0.0323,
		 'xsec_err': 0.0007,
		 'sys_array': sys_arrays['diboson'],
		 'ngen':  9931257,
#		  'fillColor': ROOT.kCyan-2,
		 'fillColor': ROOT.kAzure+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ZZ',
		 'file': dirStr+'zz' +rootStr,
		 'file_JESUp': dirStr+'zz'+rootStr,
		 'file_JESDown': dirStr+'zz'+rootStr,
		 'xsec': 0.0077,#0.00826,
		 'xsec_err': 0.00015,
		 'sys_array': sys_arrays['diboson'],
		 'ngen':  9755621,
#		  'fillColor': ROOT.kCyan,
		 'fillColor': ROOT.kAzure+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'skipSystematics':skipSystematics,
		 }
		)
		)

##	plotList.append(
##		PlotInfo(
##		{'name': 'WWW',
##		 'file': dirStr+'www' +rootStr,
##		 'file_JESUp': dirStr+'www'+rootStr,
##		 'file_JESDown': dirStr+'www'+rootStr,
##		 'xsec': 0.00008217,#0.0571,
##		 'xsec_err': 0.00008217*0.0015/0.0548,
##		 'sys_array': sys_arrays['diboson'],
##		 'ngen': 220040,
###		  'fillColor': ROOT.kCyan+2,
##		 'fillColor': ROOT.kAzure+1,
##		 'fillPattern': 1001,
##		 'isNormPerJetBin': 0,
##		 'skipSystematics':skipSystematics,
##		 }
##		)
##		)
##
##	plotList.append(
##		PlotInfo(
##		{'name': 'WWZ',
##		 'file': dirStr+'wwz' +rootStr,
##		 'file_JESUp': dirStr+'wwz'+rootStr,
##		 'file_JESDown': dirStr+'wwz'+rootStr,
##		 'xsec': 0.0000633,#0.0571,
##		 'xsec_err': 0.0000633*0.0015/0.0548,
##		 'sys_array': sys_arrays['diboson'],
##		 'ngen': 221576,
###		  'fillColor': ROOT.kCyan+2,
##		 'fillColor': ROOT.kAzure+1,
##		 'fillPattern': 1001,
##		 'isNormPerJetBin': 0,
##		 'skipSystematics':skipSystematics,
##		 }
##		)
##		)
##
##	plotList.append(
##		PlotInfo(
##		{'name': 'WZZ',
##		 'file': dirStr+'wzz' +rootStr,
##		 'file_JESUp': dirStr+'wzz'+rootStr,
##		 'file_JESDown': dirStr+'wzz'+rootStr,
##		 'xsec': 0.00001922,#0.0571,
##		 'xsec_err': 0.00001922*0.0015/0.0548,
##		 'sys_array': sys_arrays['diboson'],
##		 'ngen': 219835,
###		  'fillColor': ROOT.kCyan+2,
##		 'fillColor': ROOT.kAzure+1,
##		 'fillPattern': 1001,
##		 'isNormPerJetBin': 0,
##		 'skipSystematics':skipSystematics,
##		 }
##		)
##		)
##
##	plotList.append(
##		PlotInfo(
##		{'name': 'ZZZ',
##		 'file': dirStr+'zzz' +rootStr,
##		 'file_JESUp': dirStr+'zzz'+rootStr,
##		 'file_JESDown': dirStr+'zzz'+rootStr,
##		 'xsec': 0.000004587,#0.0571,
##		 'xsec_err': 0.000004587*0.0015/0.0548,
##		 'sys_array': sys_arrays['diboson'],
##		 'ngen': 224519,
###		  'fillColor': ROOT.kCyan+2,
##		 'fillColor': ROOT.kAzure+1,
##		 'fillPattern': 1001,
##		 'isNormPerJetBin': 0,
##		 'skipSystematics':skipSystematics,
##		 }
##		)
##		)

	plotList.append(
		PlotInfo(
		{'name': 'WJets',
		 'file': dirStr+'wjets' +rootStr,
		 'file_JESUp': dirStr+'wjets'+rootStr,
		 'file_JESDown': dirStr+'wjets'+rootStr,
		 'xsec': 36.257,
		 'xsec_err': 1.558,
		 'sys_array': sys_arrays['WJets'],
		 'ngen':  57536319,
#		  'fillColor': ROOT.kAzure-1,
		 'fillColor': ROOT.kAzure+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'wjets',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ZJets',
		 'file': dirStr+'zjets' +rootStr,
		 'file_JESUp': dirStr+'zjets'+rootStr,
		 'file_JESDown': dirStr+'zjets'+rootStr,
		 'xsec': 3.5057,
		 'xsec_err': 0.132,
		 'sys_array': sys_arrays['ZJets'],
		 'ngen':	30072710,
		 'fillColor': ROOT.kAzure+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'zjets_h',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ZJets_M10-50',
		 'file': dirStr+'zjets_lowmass' +rootStr,
		 'file_JESUp': dirStr+'zjets_lowmass'+rootStr,
		 'file_JESDown': dirStr+'zjets_lowmass'+rootStr,
		 'xsec': 14.7, #0.860,
		 'xsec_err': 0.132*0.86/3.5057,
		 'sys_array': sys_arrays['ZJets'],
		 'ngen': 37828841,
		 'fillColor': ROOT.kAzure+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'zjets_lowmass',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ttW',
		 'file': dirStr+'ttbarW' +rootStr,
		 'file_JESUp': dirStr+'ttbarW'+rootStr,
		 'file_JESDown': dirStr+'ttbarW'+rootStr,
		 'xsec': 0.000249, #0.000163*1.5,
		 'xsec_err': 0.2*0.000249,
		 'sys_array': sys_arrays['ttV'],
		 'ngen':  195396,
		 'fillColor': ROOT.kBlue-10,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttbarW',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ttZ',
		 'file': dirStr+'ttbarZ' +rootStr,
		 'file_JESUp': dirStr+'ttbarZ'+rootStr,
		 'file_JESDown': dirStr+'ttbarZ'+rootStr,
		 'xsec': 0.000208,#0.000136*1.5,
		 'xsec_err': 0.2*0.000208,
		 'sys_array': sys_arrays['ttV'],
		 'ngen':  209512,
		 'fillColor': ROOT.kBlue-10,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttbarZ',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

##	plotList.append(
##		PlotInfo(
##		{'name': 'ttWW',
##		 'file': dirStr+'ttbarWW' +rootStr,
##		 'file_JESUp': dirStr+'ttbarWW'+rootStr,
##		 'file_JESDown': dirStr+'ttbarWW'+rootStr,
##		 'xsec': 0.000002037,#0.000136*1.5,
##		 'xsec_err': 0.2*0.000002037,
##		 'sys_array': sys_arrays['ttV'],
##		 'ngen':  216867,
##		 'fillColor': ROOT.kBlue-9,
##		 'fillPattern': 1001,
##		 'isNormPerJetBin': 0,
##		 'limitPlotName':'ttbarWW',
##		 'skipSystematics':skipSystematics,
##		 }
##		)
##		)
##
##	plotList.append(
##		PlotInfo(
##		{'name': 'tttt',
##		 'file': dirStr+'ttbarttbar' +rootStr,
##		 'file_JESUp': dirStr+'ttbarttbar'+rootStr,
##		 'file_JESDown': dirStr+'ttbarttbar'+rootStr,
##		 'xsec': 0.0000000001,#0.000000716,
##		 'xsec_err': 0.2*0.000000716,
##		 'sys_array': sys_arrays['ttV'],
##		 'ngen':  99994,
##		 'fillColor': ROOT.kBlue-9,
##		 'fillPattern': 1001,
##		 'isNormPerJetBin': 0,
##		 'limitPlotName':'ttbarttbar',
##		 'skipSystematics':skipSystematics,
##		 }
##		)
##		)

	plotList.append(
		PlotInfo(
		{'name': 't_s',
		 'file': dirStr+'singlet_s' +rootStr,
		 'file_JESUp': dirStr+'singlet_s'+rootStr,
		 'file_JESDown': dirStr+'singlet_s'+rootStr,
		 'xsec': 0.00379,
		 'xsec_err': 0.00006*0.00379/(0.00379+0.00176),
		 'sys_array': sys_arrays['t'],
		 'ngen': 259657,
		 'fillColor': ROOT.kMagenta,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'singlet_s',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'tbar_s',
		 'file': dirStr+'singletbar_s' +rootStr,
		 'file_JESUp': dirStr+'singletbar_s'+rootStr,
		 'file_JESDown': dirStr+'singletbar_s'+rootStr,
		 'xsec': 0.00176,
		 'xsec_err': 0.00006*0.00176/(0.00379+0.00176),
		 'sys_array': sys_arrays['t'],
		 'ngen': 139835,
		 'fillColor': ROOT.kMagenta,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'singletbar_s',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 't_t',
		 'file': dirStr+'singlet_t' +rootStr,
		 'file_JESUp': dirStr+'singlet_t'+rootStr,
		 'file_JESDown': dirStr+'singlet_t'+rootStr,
		 'xsec': 0.0564,
		 'xsec_err': 0.0032*0.0564/(0.0564+0.0307),
		 'sys_array': sys_arrays['t'],
		 'ngen': 3744404,
		 'fillColor': ROOT.kMagenta,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'singlet_t',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'tbar_t',
		 'file': dirStr+'singletbar_t' +rootStr,
		 'file_JESUp': dirStr+'singletbar_t'+rootStr,
		 'file_JESDown': dirStr+'singletbar_t'+rootStr,
		 'xsec': 0.0307,
		 'xsec_err': 0.0032*0.0307/(0.0564+0.0307),
		 'sys_array': sys_arrays['t'],
		 'ngen': 1933504,
		 'fillColor': ROOT.kMagenta,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'singletbar_t',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 't_tW',
		 'file': dirStr+'singlet_tW' +rootStr,
		 'file_JESUp': dirStr+'singlet_tW'+rootStr,
		 'file_JESDown': dirStr+'singlet_tW'+rootStr,
		 'xsec': 0.0111,
		 'xsec_err': 0.0008*0.0111/0.00106,	  #### 0.00106
		 'sys_array': sys_arrays['t'],
		 'ngen': 496918,
		 'fillColor': ROOT.kMagenta,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'singlet_tW',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'tbar_tW',
		 'file': dirStr+'singletbar_tW' +rootStr,
		 'file_JESUp': dirStr+'singletbar_tW'+rootStr,
		 'file_JESDown': dirStr+'singletbar_tW'+rootStr,
		 'xsec': 0.0111,
		 'xsec_err': 0.0008*0.0111/0.00106,	 #### 0.00106
		 'sys_array': sys_arrays['t'],
		 'ngen': 492779,
		 'fillColor': ROOT.kMagenta,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'singletbar_tW',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ttbb',
		 'file': dirStr+'ttbar_bb' +rootStr,
		 'file_JESUp': dirStr+'ttbar_bb'+rootStr,
		 'file_JESDown': dirStr+'ttbar_bb'+rootStr,
		 'xsec': 0.2458, #0.225197,
		 'xsec_err': 0.5*0.2458, #0.225197, #0.3*0.225197,
		 'sys_array': sys_arrays['ttbb'],
		 'ngen':  6912438+1362471,
		 'fillColor': ROOT.kRed+3,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttbarPlusBBbar',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ttb',
		 'file': dirStr+'ttbar_b' +rootStr,
		 'file_JESUp': dirStr+'ttbar_b'+rootStr,
		 'file_JESDown': dirStr+'ttbar_b'+rootStr,
		 'xsec': 0.2458, #0.225197,
		 'xsec_err': 0.5*0.2458, #0.225197, #0.3*0.225197,
		 'sys_array': sys_arrays['ttbb'],
		 'ngen':  6912438+1362471,
		 'fillColor': ROOT.kRed-2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttbarPlusB',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ttcc',
		 'file': dirStr+'ttbar_cc' +rootStr,
		 'file_JESUp': dirStr+'ttbar_cc'+rootStr,
		 'file_JESDown': dirStr+'ttbar_cc'+rootStr,
		 'xsec': 0.2458, #0.225197,
		 'xsec_err': 0.5*0.2458, #0.225197,
		 'sys_array': sys_arrays['ttcc'],
		 'ngen':  6912438+1362471, 
		 'fillColor': ROOT.kRed+1,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttbarPlusCCbar',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'tt',
		 'file': dirStr+'ttbar' +rootStr,
		 'file_JESUp': dirStr+'ttbar'+rootStr,
		 'file_JESDown': dirStr+'ttbar'+rootStr,
		 'xsec': 0.2458, #0.225197,
		 'xsec_err': 0.023,
		 'sys_array': sys_arrays['tt'],
		 'ngen':  6912438+1362471, 
		 'fillColor': ROOT.kRed-7,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttbar',
		 'skipSystematics':skipSystematics,
		 }
		)
		)


	plotList.append(
		PlotInfo(
		{'name': 'ttH_110',
		 'file': dirStr+'ttH110' +rootStr,
		 'file_JESUp': dirStr+'ttH110'+rootStr,
		 'file_JESDown': dirStr+'ttH110'+rootStr,
		 'xsec': 0.0001887,
		 'xsec_err': 0.0,
		 'sys_array': sys_arrays['ttH_120'],
		 'ngen': 975341, 
		 'fillColor': ROOT.kBlue+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttH110',
		 'skipSystematics':skipSystematics,
		 }
		)
		)


	plotList.append(
		PlotInfo(
		{'name': 'ttH_115',
		 'file': dirStr+'ttH115' +rootStr,
		 'file_JESUp': dirStr+'ttH115'+rootStr,
		 'file_JESDown': dirStr+'ttH115'+rootStr,
		 'xsec': 0.0001663,
		 'xsec_err': 0.0,
		 'sys_array': sys_arrays['ttH_120'],
		 'ngen': 995188, 
		 'fillColor': ROOT.kBlue+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttH115',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	#print "WARNING: using hacked xsec for PU reweighting"
	plotList.append(
		PlotInfo(
		{'name': 'ttH_120',
		 'file': dirStr+'ttH120' +rootStr,
		 'file_JESUp': dirStr+'ttH120'+rootStr,
		 'file_JESDown': dirStr+'ttH120'+rootStr,
		 'xsec': 0.000147,
		 'xsec_err': 0.0,
		 'sys_array': sys_arrays['ttH_120'],
		 'ngen': 996773,
		 'fillColor': ROOT.kBlue+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttH120',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ttH_125',
		 'file': dirStr+'ttH125' +rootStr,
		 'file_JESUp': dirStr+'ttH125'+rootStr,
		 'file_JESDown': dirStr+'ttH125'+rootStr,
		 'xsec': 0.0001302 ,
		 'xsec_err': 0.0,
		 'sys_array': sys_arrays['ttH_120'],
		 'ngen':  992997,
		 'fillColor': ROOT.kBlue+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttH125',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ttH_130',
		 'file': dirStr+'ttH130' +rootStr,
		 'file_JESUp': dirStr+'ttH130'+rootStr,
		 'file_JESDown': dirStr+'ttH130'+rootStr,
		 'xsec': 0.0001157,
		 'xsec_err': 0.0,
		 'sys_array': sys_arrays['ttH_120'],
		 'ngen': 931369,
		 'fillColor': ROOT.kBlue+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttH130',
		 'skipSystematics':skipSystematics,
		 }
		)
		)
	plotList.append(
		PlotInfo(
		{'name': 'ttH_135',
		 'file': dirStr+'ttH135' +rootStr,
		 'file_JESUp': dirStr+'ttH135'+rootStr,
		 'file_JESDown': dirStr+'ttH135'+rootStr,
		 'xsec': 0.0001031,
		 'xsec_err': 0.0,
		 'sys_array': sys_arrays['ttH_120'],
		 'ngen': 993975,
		 'fillColor': ROOT.kBlue+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttH135',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	plotList.append(
		PlotInfo(
		{'name': 'ttH_140',
		 'file': dirStr+'ttH140' +rootStr,
		 'file_JESUp': dirStr+'ttH140'+rootStr,
		 'file_JESDown': dirStr+'ttH140'+rootStr,
		 'xsec': 0.00009207,
		 'xsec_err': 0.0,
		 'sys_array': sys_arrays['ttH_120'],
		 'ngen': 997191,
		 'fillColor': ROOT.kBlue+2,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'ttH140',
		 'skipSystematics':skipSystematics,
		 }
		)
		)

	
	plotList.append(
		PlotInfo(
		{'name': 'data_2012_53x',
		 'file': dataStr,
		 'file_JESUp': dataStr,
		 'file_JESDown': dataStr,
		 'xsec': 1,
		 'xsec_err': 0.0,
		 'sys_array': [0,0,0,0],
		 'ngen': 1,
		 'fillColor': ROOT.kBlack,
		 'fillPattern': 1001,
		 'isNormPerJetBin': 0,
		 'limitPlotName':'data_obs'
		 }
		)
		)


##	   plotList.append(
##		   PlotInfo(
##			   {'name': 'data_2012',
##				#'file': 
##				'xsec': 1,
##				'ngen': 1,
##				'fillColor': ROOT.kRed,
##				'fillPattern': 1001,
##				'isNormPerJetBin': 0
##				}
##			   )
##		   )

	myPlotGroup = PlotGroup (plotList, defaultLumi, groupName, directoryName, skipSystematics)
	myPlotGroup.jetSelection = jetselection
	myPlotGroup.charge = charge

	return myPlotGroup


