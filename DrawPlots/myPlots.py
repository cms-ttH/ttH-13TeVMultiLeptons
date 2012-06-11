
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

def getMyPlotsAndrewNorm (lepselection, jetselection) :
    dirStr = "root"+lepselection+"/"
    #dirStr = "../../BEAN/root"+lepselection+"/"
    rootStr = "_"+jetselection+"_.root"

    defaultLumi = 4982.0
    if dirStr.startswith("rootDiMuon"):
        #dataStr = dirStr+'data_DiMuon'+rootStr
        dataStr = dirStr+'DoubleMu_Run2011-v1_'+rootStr
        directoryName = "pdf/"+lepselection+"_"+jetselection
    elif dirStr.startswith("rootDiEle"):
        #dataStr= dirStr+'data_DiEle'+rootStr
        dataStr = dirStr+'DoubleElectron_Run2011-v1_'+rootStr
        directoryName = "pdf/"+lepselection+"_"+jetselection
    elif dirStr.startswith("rootMuEG"):
        #dataStr= dirStr+'data_MuEG'+rootStr
        dataStr = dirStr+'MuEG_Run2011-v1_'+rootStr
        directoryName = "pdf/"+lepselection+"_"+jetselection
    else:
        dataStr = dirStr+'data_ALL'+rootStr
        directoryName = "pdf/"+lepselection+"_"+jetselection

    groupName = lepselection+"_"+jetselection

    sys_arrays = {}
    if jetselection.startswith("ge3t"):
        sys_arrays['tt'] = [4.9,0.504,7.15,5.07]
        sys_arrays['ttcc'] = [3.05,1.81,10.4,0.511]
        sys_arrays['ttbb'] = [3.28,0.497,7.05,0.165]
        sys_arrays['t'] = [2.37,2.3,7.58,4.42]
        sys_arrays['ttV'] = [3.27,10.5,9.57,2.48]
        sys_arrays['diboson'] = [8.03,1.11,8.56,3.12]
        sys_arrays['WJets'] = [0,0,0,0]
        sys_arrays['ZJets'] = [6.06,1.29,8.19,4.77]
        sys_arrays['ttH_120'] = [2.62,0.99,6.97,0.56]
    elif jetselection.startswith("eq1t"):
        sys_arrays['tt'] = [0.261,1.05,5.13,0.108]
        sys_arrays['ttcc'] = [3.41,0.647,6.27,0.084]
        sys_arrays['ttbb'] = [4.92,0.726,5.22,0.27]
        sys_arrays['t'] = [0.44,0.357,5.33,0.358]
        sys_arrays['ttV'] = [3.71,10.2,5.56,0.399]
        sys_arrays['diboson'] = [4.13,1.8,5.86,0.855]
        sys_arrays['WJets'] = [0,0,0,0]
        sys_arrays['ZJets'] = [4.96,0.415,5.64,1.54]
        sys_arrays['ttH_120'] = [5.11,1.47,5.4,0.259]
    else:    
        sys_arrays['tt'] = [0.261,1.05,5.13,0.108]
        sys_arrays['ttcc'] = [3.41,0.647,6.27,0.084]
        sys_arrays['ttbb'] = [4.92,0.726,5.22,0.27]
        sys_arrays['t'] = [0.44,0.357,5.33,0.358]
        sys_arrays['ttV'] = [3.71,10.2,5.56,0.399]
        sys_arrays['diboson'] = [4.13,1.8,5.86,0.855]
        sys_arrays['WJets'] = [0,0,0,0]
        sys_arrays['ZJets'] = [4.96,0.415,5.64,1.54]
        sys_arrays['ttH_120'] = [5.11,1.47,5.4,0.259]
                
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
        {'name': 'tt',
         'file': dirStr+'tt'+rootStr,
         #'file': dirStr+'ttbar'+rootStr,
         'xsec': 0.1577,
         'xsec_err': 0.023,
         'sys_array': sys_arrays['tt'],
         'ngen': 52135272,
         'fillColor': ROOT.kRed,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttcc',
         #'file': dirStr+'ttbar_cc'+rootStr,
         'file': dirStr+'ttcc'+rootStr,
         'xsec': 0.1577,
         'xsec_err': 0.3*0.1577,
         'sys_array': sys_arrays['ttcc'],
         'ngen': 52135272,
         'fillColor': ROOT.kGreen-3,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttbb',
         #'file': dirStr+'ttbar_bb'+rootStr,
         'file': dirStr+'ttbb'+rootStr,
         'xsec': 0.1577,
         'xsec_err': 0.3*0.1577,
         'sys_array': sys_arrays['ttbb'],
         'ngen': 52135272,
         'fillColor': ROOT.kMagenta+2,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 't_s',
         #'file': dirStr+'singlet_s'+rootStr,
         'file': dirStr+'T_TuneZ2_s-channel_7TeV-powheg-tauola_PUTAG'+rootStr,
         'xsec': 0.00317,
         'xsec_err': 0.00006*0.00317/(0.00317+0.00144),
         'sys_array': sys_arrays['t'],
         'ngen': 259595,
         'fillColor': ROOT.kOrange+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'tbar_s',
         #'file': dirStr+'singletbar_s'+rootStr,
         'file': dirStr+'Tbar_TuneZ2_s-channel_7TeV-powheg-tauola_PUTAG'+rootStr,
         'xsec': 0.00144,
         'xsec_err': 0.00006*0.00144/(0.00317+0.00144),
         'sys_array': sys_arrays['t'],
         'ngen': 137662,
         'fillColor': ROOT.kOrange+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 't_t',
         #'file': dirStr+'singlet_t'+rootStr,
         'file': dirStr+'T_TuneZ2_t-channel_7TeV-powheg-tauola_PUTAG'+rootStr,
         'xsec': 0.04192,
         'xsec_err': 0.0032*0.04192/(0.04192+0.02265),
         'sys_array': sys_arrays['t'],
         'ngen': 3891841 ,
         'fillColor': ROOT.kOrange+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'tbar_t',
         #'file': dirStr+'singletbar_t'+rootStr,
         'file': dirStr+'Tbar_TuneZ2_t-channel_7TeV-powheg-tauola_PUTAG'+rootStr,
         'xsec': 0.02265,
         'xsec_err': 0.0032*0.02265/(0.04192+0.02265),
         'sys_array': sys_arrays['t'],
         'ngen': 1939703,
         'fillColor': ROOT.kOrange+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 't_tW',
         #'file': dirStr+'singlet_tW'+rootStr,
         'file': dirStr+'T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_PUTAG'+rootStr,
         'xsec': 0.00787,
         'xsec_err': 0.0008*0.00787/0.00106,
         'sys_array': sys_arrays['t'],
         'ngen': 812600,
         'fillColor': ROOT.kOrange+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'tbar_tW',
         #'file': dirStr+'singletbar_tW'+rootStr,
         'file': dirStr+'Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_PUTAG'+rootStr,
         'xsec': 0.00787,
         'xsec_err': 0.0008*0.00787/0.00106,
         'sys_array': sys_arrays['t'],
         'ngen': 808200,
         'fillColor': ROOT.kOrange+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ttW',
         #'file': dirStr+'ttbarW'+rootStr,
         'file': dirStr+'TTW_TuneZ2_7TeV-madgraph_PUTAG'+rootStr,
         'xsec': 0.000163,
         'xsec_err': 0.2*0.000163,
         'sys_array': sys_arrays['ttV'],
         'ngen': 1085456,
         'fillColor': ROOT.kBlue-9,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )
    plotList.append(
        PlotInfo(
        {'name': 'ttZ',
         #'file': dirStr+'ttbarZ'+rootStr,
         'file': dirStr+'TTZ_TuneZ2_7TeV-madgraph_PUTAG'+rootStr,
         'xsec': 0.000136,
         'xsec_err': 0.2*0.000136,
         'sys_array': sys_arrays['ttV'],
         'ngen': 1458573,
         'fillColor': ROOT.kBlue-9,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'WW',
         #'file': dirStr+'WW'+rootStr,
         'file': dirStr+'WW_TuneZ2_7TeV_pythia6_tauola_'+rootStr,
         'xsec': 0.043,
         'xsec_err': 0.0015,
         'sys_array': sys_arrays['diboson'],
         'ngen': 4225916,
         'fillColor': ROOT.kCyan,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'WZ',
         #'file': dirStr+'WZ'+rootStr,
         'file': dirStr+'WZ_TuneZ2_7TeV_pythia6_tauola_'+rootStr,
         'xsec': 0.0182,
         'xsec_err': 0.0007,
         'sys_array': sys_arrays['diboson'],
         'ngen': 4265241,
         'fillColor': ROOT.kCyan,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )
    

    plotList.append(
        PlotInfo(
        {'name': 'ZZ',
         #'file': dirStr+'ZZ'+rootStr,
         'file': dirStr+'ZZ_TuneZ2_7TeV_pythia6_tauola_'+rootStr,
         'xsec': 0.0059,
         'xsec_err': 0.00015,
         'sys_array': sys_arrays['diboson'],
         'ngen': 4191045,
         'fillColor': ROOT.kCyan,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )
    
    plotList.append(
        PlotInfo(
        {'name': 'WJets',
         #'file': dirStr+'wjets'+rootStr,
         'file': dirStr+'WJets'+rootStr,
         'xsec': 31.314,
         'xsec_err': 1.558,
         'sys_array': sys_arrays['WJets'],
         'ngen': 81011945,
         'fillColor': ROOT.kAzure-1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )
    

    plotList.append(
        PlotInfo(
        {'name': 'ZJets',
         #'file': dirStr+'zjets'+rootStr,
         'file': dirStr+'DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_'+rootStr,
         'xsec': 3.048,
         'xsec_err': 0.132,
         'sys_array': sys_arrays['ZJets'],
         'ngen': 35891264,
         'fillColor': ROOT.kAzure+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    plotList.append(
        PlotInfo(
        {'name': 'ZJets_M10-50',
         'file': dirStr+'DYJetsToLL_M-10To50_TuneZ2_7TeV-madgraph_v1_PUTAG'+rootStr,
         'xsec': 12.7826,
         'xsec_err': 0.132*12.7826/3.048,
         'sys_array': sys_arrays['ZJets'],
         'ngen': 31480628,
         'fillColor': ROOT.kAzure+1,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )


    plotList.append(
        PlotInfo(
        {'name': 'ttH_120',
         #'file': dirStr+'TTH_HtoAll_M_120_7TeV_pythia6_'+rootStr,
         #'file': dirStr+'ttH120'+rootStr,
         'file': dirStr+'ttH_m120_PUTAG'+rootStr,
         'xsec': 0.000098,
         'xsec_err': 0.0,
         'sys_array': sys_arrays['ttH_120'],
         'ngen': 998833,
         'fillColor': ROOT.kMagenta,
         'fillPattern': 1001,
         'isNormPerJetBin': 0,}
        )
        )

    
    plotList.append(
        PlotInfo(
        {'name': 'data_2011',
         'file': dataStr,
         'xsec': 1,
         'xsec_err': 0.0,
         'sys_array': [0,0,0,0],
         'ngen': 1,
         'fillColor': ROOT.kBlack,
         'fillPattern': 1001,
         'isNormPerJetBin': 0
         }
        )
        )


##     plotList.append(
##         PlotInfo(
##             {'name': 'data_2012',
##              #'file': dirStr+'BEAN_V05_CV02_toND_v4_DoubleMu_Run2011-v1_'+rootStr,
##              #'file': dirStr+'doubleMu2012_testTree_job_1_'+rootStr,
##              'file': 'DiEleAll_jet_tag/doubleEle2012_week02_52Xonly_testTree_'+jetselection+'_.root',
##              'xsec': 1,
##              'ngen': 1,
##              'fillColor': ROOT.kRed,
##              'fillPattern': 1001,
##              'isNormPerJetBin': 0
##              }
##             )
##         )

    myPlotGroup = PlotGroup (plotList, defaultLumi, groupName, directoryName)

    return myPlotGroup

         
        

