
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

def getMyPlotsAndrewNorm (lepselection, year, Zmask, jetselection) :

    dirStr =  lepselection+"/"
    #dirStr = "root"+lepselection+"/"
    rootStr = "_" + year + "_" + Zmask + "_" + jetselection + "_" + lepselection +".root"    

    defaultLumi = 4982.0
    if lepselection.startswith("TwoMuon"):
        dataStr = dirStr+'DoubleMu_'+ year + "_" + Zmask + "_" + jetselection + "_TwoMuon.root"

    elif lepselection.startswith("TwoEle"):
        dataStr = dirStr+'DoubleElectron_'+  year + "_" + Zmask + "_" + jetselection +  "_TwoEle.root"

    elif lepselection.startswith("MuonEle"):
        dataStr = dirStr+'MuEG_' + year + "_" + Zmask + "_" + jetselection +  "_MuonEle.root"

    elif lepselection.startswith("SameLep"):
        dataStr = dirStr+'SameLep'+rootStr
    else:
        dataStr = dirStr+'TwoLep'+rootStr


#    directoryName = "pdf/"+ Zmask + "/" +lepselection+"_"+year + "_" + Zmask + "_" + jetselection
    directoryName = "pdf/"+lepselection+"_"+year + "_" + Zmask + "_" + jetselection   
    
    groupName = lepselection+"_"+year + "_" + Zmask + "_" + jetselection

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

##     plotList.append(
##         PlotInfo(
##         {'name': 'ttbar',
##          'file': dirStr+'TTJets_TuneZ2_7TeV-madgraph-tauola_'+rootStr,
##          'xsec': 0.1577,
##          'ngen': 52135272,
##          #'fillColor': ROOT.kOrange+10,
##          'fillColor': ROOT.kRed,
##          'fillPattern': 1001,
##          'isNormPerJetBin': 0,}
##         )
##         )

    plotList.append(
        PlotInfo(
        {'name': 'WW',
         'file': dirStr+'ww' +rootStr,
         'file_JESUp': dirStr+'ww'+rootStr,
         'file_JESDown': dirStr+'ww'+rootStr,
         'xsec': 0.043,
         'xsec_err': 0.0015,
         'sys_array': sys_arrays['diboson'],
         'ngen': 4225916,
#         'fillColor': ROOT.kCyan,
         'fillColor': ROOT.kAzure+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'WZ',
         'file': dirStr+'wz' +rootStr,
         'file_JESUp': dirStr+'wz'+rootStr,
         'file_JESDown': dirStr+'wz'+rootStr,
         'xsec': 0.0182,
         'xsec_err': 0.0007,
         'sys_array': sys_arrays['diboson'],
         'ngen': 4265241,
#         'fillColor': ROOT.kCyan,
         'fillColor': ROOT.kAzure+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'ZZ',
         'file': dirStr+'zz' +rootStr,
         'file_JESUp': dirStr+'zz'+rootStr,
         'file_JESDown': dirStr+'zz'+rootStr,
         'xsec': 0.0059,
         'xsec_err': 0.00015,
         'sys_array': sys_arrays['diboson'],
         'ngen': 4191045,
#         'fillColor': ROOT.kCyan,
         'fillColor': ROOT.kAzure+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'WJets',
         'file': dirStr+'wjets' +rootStr,
         'file_JESUp': dirStr+'wjets'+rootStr,
         'file_JESDown': dirStr+'wjets'+rootStr,
         'xsec': 31.314,
         'xsec_err': 1.558,
         'sys_array': sys_arrays['WJets'],
         'ngen': 81011945,
#         'fillColor': ROOT.kAzure-1,
         'fillColor': ROOT.kAzure+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'wjets'}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'ZJets',
         'file': dirStr+'zjets' +rootStr,
         'file_JESUp': dirStr+'zjets'+rootStr,
         'file_JESDown': dirStr+'zjets'+rootStr,
         'xsec': 3.048,
         'xsec_err': 0.132,
         'sys_array': sys_arrays['ZJets'],
         'ngen': 35891264,
         'fillColor': ROOT.kAzure+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'zjets_h'}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'ZJets_M10-50',
         'file': dirStr+'zjets_lowmass' +rootStr,
         'file_JESUp': dirStr+'zjets_lowmass'+rootStr,
         'file_JESDown': dirStr+'zjets_lowmass'+rootStr,
         'xsec': 12.7826,
         'xsec_err': 0.132*12.7826/3.048,
         'sys_array': sys_arrays['ZJets'],
         'ngen': 31480628, ## 31479522
         'fillColor': ROOT.kAzure+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'zjets_lowmass'}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'ttW',
         'file': dirStr+'ttbarW' +rootStr,
         'file_JESUp': dirStr+'ttbarW'+rootStr,
         'file_JESDown': dirStr+'ttbarW'+rootStr,
         'xsec': 0.000163,
         'xsec_err': 0.2*0.000163,
         'sys_array': sys_arrays['ttV'],
         'ngen': 1085456,
         'fillColor': ROOT.kBlue-9,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttbarW'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttZ',
         'file': dirStr+'ttbarZ' +rootStr,
         'file_JESUp': dirStr+'ttbarZ'+rootStr,
         'file_JESDown': dirStr+'ttbarZ'+rootStr,
         'xsec': 0.000136,
         'xsec_err': 0.2*0.000136,
         'sys_array': sys_arrays['ttV'],
         'ngen': 1458573,
         'fillColor': ROOT.kBlue-9,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttbarZ'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 't_s',
         'file': dirStr+'singlet_s' +rootStr,
         'file_JESUp': dirStr+'singlet_s'+rootStr,
         'file_JESDown': dirStr+'singlet_s'+rootStr,
         'xsec': 0.00317,
         'xsec_err': 0.00006*0.00317/(0.00317+0.00144),
         'sys_array': sys_arrays['t'],
         'ngen': 259595,
         'fillColor': ROOT.kOrange+7,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'singlet_s'}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'tbar_s',
         'file': dirStr+'singletbar_s' +rootStr,
         'file_JESUp': dirStr+'singletbar_s'+rootStr,
         'file_JESDown': dirStr+'singletbar_s'+rootStr,
         'xsec': 0.00144,
         'xsec_err': 0.00006*0.00144/(0.00317+0.00144),
         'sys_array': sys_arrays['t'],
         'ngen': 137662,
         'fillColor': ROOT.kOrange+7,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'singletbar_s'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 't_t',
         'file': dirStr+'singlet_t' +rootStr,
         'file_JESUp': dirStr+'singlet_t'+rootStr,
         'file_JESDown': dirStr+'singlet_t'+rootStr,
         'xsec': 0.04192,
         'xsec_err': 0.0032*0.04192/(0.04192+0.02265),
         'sys_array': sys_arrays['t'],
         'ngen': 3891841 ,
         'fillColor': ROOT.kOrange+7,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'singlet_t'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'tbar_t',
         'file': dirStr+'singletbar_t' +rootStr,
         'file_JESUp': dirStr+'singletbar_t'+rootStr,
         'file_JESDown': dirStr+'singletbar_t'+rootStr,
         'xsec': 0.02265,
         'xsec_err': 0.0032*0.02265/(0.04192+0.02265),
         'sys_array': sys_arrays['t'],
         'ngen': 1939703,
         'fillColor': ROOT.kOrange+7,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'singletbar_t',}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 't_tW',
         'file': dirStr+'singlet_tW' +rootStr,
         'file_JESUp': dirStr+'singlet_tW'+rootStr,
         'file_JESDown': dirStr+'singlet_tW'+rootStr,
         'xsec': 0.00787,
         'xsec_err': 0.0008*0.00787/0.00106,
         'sys_array': sys_arrays['t'],
         'ngen': 812600,
         'fillColor': ROOT.kOrange+7,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'singlet_tW'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'tbar_tW',
         'file': dirStr+'singletbar_tW' +rootStr,
         'file_JESUp': dirStr+'singletbar_tW'+rootStr,
         'file_JESDown': dirStr+'singletbar_tW'+rootStr,
         'xsec': 0.00787,
         'xsec_err': 0.0008*0.00787/0.00106,
         'sys_array': sys_arrays['t'],
         'ngen': 808200,
         'fillColor': ROOT.kOrange+7,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'singletbar_tW'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttbb',
         'file': dirStr+'ttbar_bb' +rootStr,
         'file_JESUp': dirStr+'ttbar_bb'+rootStr,
         'file_JESDown': dirStr+'ttbar_bb'+rootStr,
         'xsec': 0.1577,
         'xsec_err': 0.5*0.1577, ##0.3*0.1577,
         'sys_array': sys_arrays['ttbb'],
         'ngen': 52641551, ##52135272,
         'fillColor': ROOT.kMagenta+2,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttbarPlusBBbar'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttcc',
         'file': dirStr+'ttbar_cc' +rootStr,
         'file_JESUp': dirStr+'ttbar_cc'+rootStr,
         'file_JESDown': dirStr+'ttbar_cc'+rootStr,
         'xsec': 0.1577,
         'xsec_err': 0.3*0.1577,
         'sys_array': sys_arrays['ttcc'],
         'ngen': 52641551, ##52135272,
         'fillColor': ROOT.kOrange-7,  ##color
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttbarPlusCCbar'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'tt',
         'file': dirStr+'ttbar' +rootStr,
         'file_JESUp': dirStr+'ttbar'+rootStr,
         'file_JESDown': dirStr+'ttbar'+rootStr,
         'xsec': 0.1577,
         'xsec_err': 0.023,
         'sys_array': sys_arrays['tt'],
         'ngen': 52641551, ##52135272,
         'fillColor': ROOT.kRed,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttbar'}
        )
        )


    plotList.append(
        PlotInfo(
        {'name': 'ttH_110',
         'file': dirStr+'ttH110' +rootStr,
         'file_JESUp': dirStr+'ttH110'+rootStr,
         'file_JESDown': dirStr+'ttH110'+rootStr,
         'xsec': 0.0001257,
         'xsec_err': 0.0,
         'sys_array': sys_arrays['ttH_120'],
         'ngen':  1059331,#99880,
         'fillColor': ROOT.kMagenta,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttH110'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttH_115',
         'file': dirStr+'ttH115' +rootStr,
         'file_JESUp': dirStr+'ttH115'+rootStr,
         'file_JESDown': dirStr+'ttH115'+rootStr,
         'xsec': 0.0001106,
         'xsec_err': 0.0,
         'sys_array': sys_arrays['ttH_120'],
         'ngen': 1083388,#99915,
         'fillColor': ROOT.kMagenta,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttH115'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttH_120',
         'file': dirStr+'ttH120' +rootStr,
         'file_JESUp': dirStr+'ttH120'+rootStr,
         'file_JESDown': dirStr+'ttH120'+rootStr,
         'xsec': 0.00009756,
         'xsec_err': 0.0,
         'sys_array': sys_arrays['ttH_120'],
         'ngen': 998833,
         'fillColor': ROOT.kMagenta,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttH120'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttH_125',
         'file': dirStr+'ttH125' +rootStr,
         'file_JESUp': dirStr+'ttH125'+rootStr,
         'file_JESDown': dirStr+'ttH125'+rootStr,
         'xsec': 0.00008634, 
         'xsec_err': 0.0,
         'sys_array': sys_arrays['ttH_120'],
         'ngen': 1093285,#99896,
         'fillColor': ROOT.kMagenta,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttH125'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttH_130',
         'file': dirStr+'ttH130' +rootStr,
         'file_JESUp': dirStr+'ttH130'+rootStr,
         'file_JESDown': dirStr+'ttH130'+rootStr,
         'xsec': 0.00007658,
         'xsec_err': 0.0,
         'sys_array': sys_arrays['ttH_120'],
         'ngen': 947576,#99915,
         'fillColor': ROOT.kMagenta,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttH130'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttH_135',
         'file': dirStr+'ttH135' +rootStr,
         'file_JESUp': dirStr+'ttH135'+rootStr,
         'file_JESDown': dirStr+'ttH135'+rootStr,
         'xsec': 0.00006810,
         'xsec_err': 0.0,
         'sys_array': sys_arrays['ttH_120'],
         'ngen':  968457,#99898,
         'fillColor': ROOT.kMagenta,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttH135'}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttH_140',
         'file': dirStr+'ttH140' +rootStr,
         'file_JESUp': dirStr+'ttH140'+rootStr,
         'file_JESDown': dirStr+'ttH140'+rootStr,
         'xsec': 0.00006072,
         'xsec_err': 0.0,
         'sys_array': sys_arrays['ttH_120'],
         'ngen': 1042904,#99909,
         'fillColor': ROOT.kMagenta,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,
         'limitPlotName':'ttH140'}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'data_2011',
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


##     plotList.append(
##         PlotInfo(
##             {'name': 'data_2012',
##              #'file': 
##              'xsec': 1,
##              'ngen': 1,
##              'fillColor': ROOT.kRed,
##              'fillPattern': 1001,
##              'isNormPerJetBin': 0
##              }
##             )
##         )

    myPlotGroup = PlotGroup (plotList, defaultLumi, groupName, directoryName)
    myPlotGroup.jetSelection = jetselection

    return myPlotGroup


