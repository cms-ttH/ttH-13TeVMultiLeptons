from argparse import ArgumentParser
from ttHMultileptonAnalysis.DrawPlots.utilities.configparser import *
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper
from ttHMultileptonAnalysis.DrawPlots.utilities.prettytable import PrettyTable

import ROOT
ROOT.gROOT.SetBatch(True)
import yaml
import numpy
import copy
import math
import itertools

def main():
    parser = ArgumentParser(description='Calculate fake rates.')
    parser.add_argument('config_file_name', nargs='?', default='fakerate_ttbar_SS_3l.yaml', help='Configuration file to process.')
    args = parser.parse_args()

    with open(args.config_file_name) as config_file:
        config = yaml.load(config_file)

    base_cuts = {}

    base_cuts_SS = config.get('common cuts SS', {}).values()
    base_cuts_3l = config.get('common cuts 3l', {}).values()

    for lep_cat in config.get('lepton categories', {}).keys():
        if lep_cat == 'mu_mu' or lep_cat == 'mu_ele' or lep_cat == 'ele_ele':
            base_cuts[lep_cat] = base_cuts_SS+config['lepton categories'][lep_cat].get('cuts', {}).values()
        elif lep_cat == '3l':
            base_cuts[lep_cat] = base_cuts_3l+config['lepton categories'][lep_cat].get('cuts', {}).values()

    ## pt/eta/CSV bin names
    FR_keys = config.get('muon pt eta csv categories', {}).keys()
    ## Bins [isMuon, pt_min, pt_max, eta_min, eta_max, CSV_min, CSV_max]
    FR_array = config['muon pt eta csv categories']

    muPt = config['binning']['mu']['pT']
    muEta = config['binning']['mu']['eta']
    muCSV = config['binning']['mu']['jetBTagCSV']
    elePt = config['binning']['ele']['pT']
    eleEta = config['binning']['ele']['eta']
    eleCSV = config['binning']['ele']['jetBTagCSV']

    print 'About to make histograms'
    ## Make 3D FR histograms where (x, y, z) = (pt, eta, CSV) 
    FR_hist_tight_mu_init = ROOT.TH3F('initial tight mu FR', 'initial tight mu FR', len(muPt)-1, numpy.array(muPt,numpy.dtype(float)), len(muEta)-1, numpy.array(muEta,numpy.dtype(float)), len(muCSV)-1, numpy.array(muCSV,numpy.dtype(float)))
    FR_hist_tight_ele_init = ROOT.TH3F('initial tight ele FR', 'initial tight ele FR', len(elePt)-1, numpy.array(elePt,numpy.dtype(float)), len(eleEta)-1, numpy.array(eleEta,numpy.dtype(float)), len(eleCSV)-1, numpy.array(eleCSV,numpy.dtype(float)))
    FR_hist_tight_mu_final = ROOT.TH3F('final tight mu FR', 'final tight mu FR', len(muPt)-1, numpy.array(muPt,numpy.dtype(float)), len(muEta)-1, numpy.array(muEta,numpy.dtype(float)), len(muCSV)-1, numpy.array(muCSV,numpy.dtype(float)))
    FR_hist_tight_ele_final = ROOT.TH3F('final tight ele FR', 'final tight ele FR', len(elePt)-1, numpy.array(elePt,numpy.dtype(float)), len(eleEta)-1, numpy.array(eleEta,numpy.dtype(float)), len(eleCSV)-1, numpy.array(eleCSV,numpy.dtype(float)))
    print 'Made histogram'

    ## Append initial and final FR to each bin, and fill initial FR hist with initial FR
    for bin in FR_keys:
        if FR_array[bin][0] == 1:
            FR_array[bin].append(config['initial FR']['tight mu']) #Initial FR
            FR_array[bin].append(config['initial FR']['tight mu']) #Final FR
            histBin = FR_hist_tight_mu_init.FindBin( (FR_array[bin][1]+FR_array[bin][2])/2.0, (FR_array[bin][3]+FR_array[bin][4])/2.0, (FR_array[bin][5]+FR_array[bin][6])/2.0 )
            FR_hist_tight_mu_init.SetBinContent(histBin, config['initial FR']['tight mu'] )
        if FR_array[bin][0] == 0:
            FR_array[bin].append(config['initial FR']['tight ele']) #Initial FR
            FR_array[bin].append(config['initial FR']['tight ele']) #Final FR
            histBin = FR_hist_tight_ele_init.FindBin( (FR_array[bin][1]+FR_array[bin][2])/2.0, (FR_array[bin][3]+FR_array[bin][4])/2.0, (FR_array[bin][5]+FR_array[bin][6])/2.0 )
            FR_hist_tight_ele_init.SetBinContent(histBin, config['initial FR']['tight ele'] )

    ## Establish working points
    #WP = config['lepMVA cuts']['tight']
    WP_presel = config['lepCut cuts']['presel']
    WP_sel = config['lepCut cuts']['tight']

    data_yield = {}
    MC_yield = {}
    QF_yield = {}
    NP_probe_yield = {}
    NP_tag_yield = {}

    for bin in FR_keys:
        data_yield[bin] = {}
        MC_yield[bin] = {}
        QF_yield[bin] = {}
        NP_probe_yield[bin] = {}
        NP_tag_yield[bin] = {}
        for lep_cat in config.get('lepton categories', {}).keys():
            data_yield[bin][lep_cat] = {}
            MC_yield[bin][lep_cat] = {}
            QF_yield[bin][lep_cat] = {}
            NP_tag_yield[bin][lep_cat] = {}
            NP_probe_yield[bin][lep_cat] = {}

            if lep_cat == 'mu_mu' or lep_cat == 'mu_ele' or lep_cat == 'ele_ele':
                lepStr = config['leptons']['SS']
            elif lep_cat == '3l':
                lepStr = config['leptons']['3l']
                
            for iLep in range(2):
                data_yield[bin][lep_cat][iLep] = {}
                MC_yield[bin][lep_cat][iLep] = {}
                QF_yield[bin][lep_cat][iLep] = {}
                NP_tag_yield[bin][lep_cat][iLep] = {}
                NP_probe_yield[bin][lep_cat][iLep] = {}

                data_yield[bin][lep_cat][iLep]['num'] = compute_num_denom('data', bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_sel, FR_array, config, bin)        
                MC_yield[bin][lep_cat][iLep]['num'] = compute_num_denom('MC', bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_sel, FR_array, config, bin)        
                QF_yield[bin][lep_cat][iLep]['num'] = compute_num_denom('QF', bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_sel, FR_array, config, bin)        
                data_yield[bin][lep_cat][iLep]['denom'] = compute_num_denom('data', bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_presel, FR_array, config, bin)        
                MC_yield[bin][lep_cat][iLep]['denom'] = compute_num_denom('MC', bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_presel, FR_array, config, bin)
                QF_yield[bin][lep_cat][iLep]['denom'] = compute_num_denom('QF', bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_presel, FR_array, config, bin)

                NP_tag_yield[bin][lep_cat][iLep]['num'] = {}
                NP_tag_yield[bin][lep_cat][iLep]['denom'] = {}
                for bin_NP in FR_keys:
                    NP_tag_yield[bin][lep_cat][iLep]['num'][bin_NP] = compute_num_denom('NP_tag', bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_sel, FR_array, config, bin_NP)        
                    NP_tag_yield[bin][lep_cat][iLep]['denom'][bin_NP] = compute_num_denom('NP_tag', bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_presel, FR_array, config, bin_NP)        

#     ## Calculate one iteration of FR given an initial FR
#     for bin in FR_keys:
#         numerator = 0.0
#         denominator = 0.0
#         data_numerator = 0.0
#         data_denominator = 0.0
#         MC_numerator = 0.0
#         MC_denominator = 0.0
#         QF_numerator = 0.0
#         QF_denominator = 0.0
#         NP_numerator = 0.0
#         NP_denominator = 0.0
#         NP_numerator_unsc = 0.0
#         NP_denominator_unsc = 0.0
#         for lep_cat in config.get('lepton categories', {}).keys():
#             for iLep in range(2):
#                 data_numerator += data_yield[bin][lep_cat][iLep]['num']
#                 MC_numerator += MC_yield[bin][lep_cat][iLep]['num']
#                 QF_numerator += QF_yield[bin][lep_cat][iLep]['num']
#                 data_denominator += data_yield[bin][lep_cat][iLep]['denom']
#                 MC_denominator += MC_yield[bin][lep_cat][iLep]['denom']
#                 QF_denominator += QF_yield[bin][lep_cat][iLep]['denom']
#                 for bin_NP in FR_keys:
#                     NP_numerator += NP_tag_yield[bin][lep_cat][iLep]['num'][bin_NP]*FR_array[bin_NP][7]/(1-FR_array[bin_NP][7])
#                     NP_denominator += NP_tag_yield[bin][lep_cat][iLep]['denom'][bin_NP]*FR_array[bin_NP][7]/(1-FR_array[bin_NP][7])
#                     NP_numerator_unsc += NP_tag_yield[bin][lep_cat][iLep]['num'][bin_NP]
#                     NP_denominator_unsc += NP_tag_yield[bin][lep_cat][iLep]['denom'][bin_NP]

#         numerator = data_numerator - MC_numerator - QF_numerator - NP_numerator
#         denominator = data_denominator - MC_denominator - QF_denominator - NP_denominator
#         print bin+' data num = '+str(data_numerator)+', denom = '+str(data_denominator)
#         print bin+' MC num = '+str(MC_numerator)+', denom = '+str(MC_denominator)
#         print bin+' QF num = '+str(QF_numerator)+', denom = '+str(QF_denominator)
#         print bin+' NP num = '+str(NP_numerator)+', denom = '+str(NP_denominator)
#         print bin+' NP num unsc = '+str(NP_numerator_unsc)+', denom = '+str(NP_denominator_unsc)
#         print bin+' final num = '+str(numerator)+', denom = '+str(denominator)
#         print 'FR for bin '+bin+' = '+str(numerator/denominator)

    FR_combos = numpy.arange(0, 0.5, 0.01)
    FR_final = {}
    chi2_init = 10000

    for FR_set in itertools.product(FR_combos, repeat=len(FR_keys)):
        print '--------- NEW FR SET -----------'
        print FR_set

        ## Set initial fake rates to this combination
        for bin_index in range(len(FR_keys)):
            FR_array[FR_keys[bin_index]][7] = FR_set[bin_index]

        ## Calculate chi2
        this_chi2 = 0.0
        for bin in FR_keys:
            numerator = 0.0
            denominator = 0.0
            num_err2 = 0.0
            denom_err2 = 0.0
            for lep_cat in config.get('lepton categories', {}).keys():
                for iLep in range(2):
                    numerator += (data_yield[bin][lep_cat][iLep]['num'] - MC_yield[bin][lep_cat][iLep]['num'] - QF_yield[bin][lep_cat][iLep]['num'])
                    num_err2 += data_yield[bin][lep_cat][iLep]['num'] + MC_yield[bin][lep_cat][iLep]['num'] + QF_yield[bin][lep_cat][iLep]['num']
                    denominator += (data_yield[bin][lep_cat][iLep]['denom'] - MC_yield[bin][lep_cat][iLep]['denom'] - QF_yield[bin][lep_cat][iLep]['denom'])
                    denom_err2 += data_yield[bin][lep_cat][iLep]['denom'] + MC_yield[bin][lep_cat][iLep]['denom'] + QF_yield[bin][lep_cat][iLep]['denom']
                    for bin_NP in FR_keys:
                        numerator -= NP_tag_yield[bin][lep_cat][iLep]['num'][bin_NP]*FR_array[bin_NP][7]/(1-FR_array[bin_NP][7])
                        num_err2 += NP_tag_yield[bin][lep_cat][iLep]['num'][bin_NP]*FR_array[bin_NP][7]/(1-FR_array[bin_NP][7])
                        denominator -= NP_tag_yield[bin][lep_cat][iLep]['denom'][bin_NP]*FR_array[bin_NP][7]/(1-FR_array[bin_NP][7])
                        denom_err2 += NP_tag_yield[bin][lep_cat][iLep]['denom'][bin_NP]*FR_array[bin_NP][7]/(1-FR_array[bin_NP][7])
                    #print 'bin %s, lep_cat %s, iLep %d, num = %d, denom = %d, FR = %0.3f' % (bin, lep_cat, iLep, numerator, denominator, FR_array[bin][7])
                #print 'TOTAL bin %s, num = %d, denom = %d, FR = %0.3f' % (bin, numerator, denominator, FR_array[bin][7])
            #numerator = max(numerator, 1.0)
            #denominator = max(denominator, 1.0)
            this_chi2 += pow( ( (numerator/denominator) - FR_array[bin][7] ) / (math.sqrt(num_err2/pow(numerator,2) + denom_err2/pow(denominator,2))*numerator/denominator) , 2)
            if denominator < 0:
                this_chi2 += 1000
            print 'bin %s this_chi2 = %0.3f' % (bin, this_chi2)

        if this_chi2 < chi2_init:
            chi2_init = this_chi2
            FR_final = FR_set
            for bin in FR_keys:
                FR_array[bin][8] = FR_array[bin][7]

    print 'Minimum chi2 = %0.3f' % (chi2_init)
    print FR_final
    print FR_array

                    


        #FR_array[bin][8] = num/denom
    #print 'DATA YIELD'
    #print data_yield
    #print 'MC YIELD'
    #print MC_yield
    #print 'QF YIELD'
    #print QF_yield
    #print 'NP_TAG YIELD'
    #print NP_tag_yield

#     ## Fill final FR hist with final FR
#     for bin in FR_keys:
#         if FR_array[bin][0] == 1:
#             histBin = FR_hist_tight_mu_final.FindBin( (FR_array[bin][1]+FR_array[bin][2])/2.0, (FR_array[bin][3]+FR_array[bin][4])/2.0, (FR_array[bin][5]+FR_array[bin][6])/2.0 )
#             FR_hist_tight_mu_final.SetBinContent(histBin, FR_array[bin][8])
#         if FR_array[bin][0] == 0:
#             histBin = FR_hist_tight_ele_final.FindBin( (FR_array[bin][1]+FR_array[bin][2])/2.0, (FR_array[bin][3]+FR_array[bin][4])/2.0, (FR_array[bin][5]+FR_array[bin][6])/2.0 )
#             FR_hist_tight_ele_final.SetBinContent(histBin, FR_array[bin][8])

def compute_num_denom(type, bin, lep_cat, iLep, lepStr, base_cut, WP_tag, WP_probe, FR_array, config, bin_NP):

    #print 'Inside compute_num_denom'

    this_base_cut = copy.deepcopy(base_cut)

    this_num_denom = 0.0

    if FR_array[bin][0] == 1 and lep_cat == 'ele_ele':
        return 0.0
    if FR_array[bin][0] == 0 and lep_cat == 'mu_mu':
        return 0.0

    ## Apply cuts for this bin, probe lepton
    #this_base_cut.append(lepStr+str(iLep+1)+'_lepMVA > '+str(WP_probe))
    this_base_cut.append(lepStr+str(iLep+1)+'_lepCut >= '+str(WP_probe))
    this_base_cut.append(lepStr+str(iLep+1)+'_isMuon == '+str(FR_array[bin][0]))
    this_base_cut.append(lepStr+str(iLep+1)+'_pt > '+str(FR_array[bin][1]))
    this_base_cut.append(lepStr+str(iLep+1)+'_pt < '+str(FR_array[bin][2]))
    this_base_cut.append('abs('+lepStr+str(iLep+1)+'_eta) > '+str(FR_array[bin][3]))
    this_base_cut.append('abs('+lepStr+str(iLep+1)+'_eta) < '+str(FR_array[bin][4]))
    this_base_cut.append(lepStr+str(iLep+1)+'_jetBTagCSV > '+str(FR_array[bin][5]))
    this_base_cut.append(lepStr+str(iLep+1)+'_jetBTagCSV < '+str(FR_array[bin][6]))

    #data_cut = [lepStr+str(abs(iLep-1)+1)+'_lepMVA > '+str(WP_tag)]
    #MC_cut = [lepStr+str(abs(iLep-1)+1)+'_lepMVA > '+str(WP_tag)]
    #QF_cut = [lepStr+str(abs(iLep-1)+1)+'_lepMVA > '+str(WP_tag)]
    #NP_cut = [lepStr+str(abs(iLep-1)+1)+'_lepMVA < '+str(WP_tag)]
    data_cut = [lepStr+str(abs(iLep-1)+1)+'_lepCut >= '+str(WP_tag)]
    MC_cut = [lepStr+str(abs(iLep-1)+1)+'_lepCut >= '+str(WP_tag)]
    QF_cut = [lepStr+str(abs(iLep-1)+1)+'_lepCut >= '+str(WP_tag)]
    NP_cut = [lepStr+str(abs(iLep-1)+1)+'_lepCut < '+str(WP_tag)]

    ## Apply cuts for this bin, tag lepton
    if type == 'NP_tag':
        tag_lepton_bin_cut = [lepStr+str(abs(iLep-1)+1)+'_isMuon == '+str(FR_array[bin_NP][0])]
        tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_pt > '+str(FR_array[bin_NP][1]))
        tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_pt < '+str(FR_array[bin_NP][2]))
        tag_lepton_bin_cut[0] += (' && abs('+lepStr+str(abs(iLep-1)+1)+'_eta) > '+str(FR_array[bin_NP][3]))
        tag_lepton_bin_cut[0] += (' && abs('+lepStr+str(abs(iLep-1)+1)+'_eta) < '+str(FR_array[bin_NP][4]))
        tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_jetBTagCSV > '+str(FR_array[bin_NP][5]))
        tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_jetBTagCSV < '+str(FR_array[bin_NP][6]))

    for sample in config['samples']:

        sample_dict = config['samples'][sample] if config['samples'][sample] else {'systematics':['common'], 'weights':['common']}

        ## Get basic sample information
        tree_sample = sample_dict.get('tree sample', sample)
        additional_cuts = sample_dict.get('additional cuts', [])
        cuts_to_remove = sample_dict.get('cuts to remove', [])
        sample_info = plot_helper.SampleInformation(tree_sample)

        ## Only compute relevant samples
        #print 'sample '+sample+', type '+type+', sample_type '+sample_info.sample_type
        if type == 'data' and ((not sample_info.sample_type == 'data') or ('sideband' in sample)):
            continue
        if type == 'MC' and not sample_info.sample_type == 'MC':
            continue
        if type == 'QF' and not 'QF' in sample:
            continue
        if 'NP' in type and not 'NP' in sample:
            continue
        #print 'Proceeding with calculation'
        
        ## Get tree file and summaryTree
        if lep_cat == 'mu_mu' or lep_cat == 'mu_ele' or lep_cat == 'ele_ele':
            source_file_name = '%s/%s_%s_all.root' % (config['input_trees_directory'], tree_sample, config['SS label'])
        elif lep_cat == '3l':
            source_file_name = '%s/%s_%s_all.root' % (config['input_trees_directory'], tree_sample, config['3l label'])
        source_file = ROOT.TFile(source_file_name)
        tree = source_file.Get('summaryTree')

        draw_string_maker = plot_helper.DrawStringMaker()

        ## Apply proper selection criteria
        if sample in config['lepton categories'][lep_cat]['data samples']:
            draw_string_maker.append_selection_requirements(this_base_cut, data_cut)
        elif sample_info.sample_type == 'MC':
            draw_string_maker.append_selection_requirements(this_base_cut, MC_cut)
        elif 'QF_sideband' in sample and sample.replace('_QF_sideband','') in config['lepton categories'][lep_cat]['data samples']:
            draw_string_maker.append_selection_requirements(this_base_cut, QF_cut)
        elif 'NP_sideband' in sample and sample.replace('_NP_sideband','') in config['lepton categories'][lep_cat]['data samples']:
            draw_string_maker.append_selection_requirements(this_base_cut, NP_cut)
        else:
            #print sample+' not included in '+lep_cat+' num_denom'
            continue
        if type == 'NP_tag':
            draw_string_maker.append_selection_requirements(tag_lepton_bin_cut)

        draw_string_maker.remove_selection_requirements(cuts_to_remove)
        draw_string_maker.append_selection_requirements(additional_cuts)

        ## Are the QF weights implemented properly?
        weights = plot_helper.customize_list(config['weights'], sample_dict.get('weights', ['common']))

        ## Apply MC weights
        weights_cat = ['1.0']
        if (lep_cat == 'mu_mu' or lep_cat == 'mu_ele' or lep_cat == 'ele_ele') and sample_info.sample_type == 'MC':
            weights_cat = config['weights SS']
        elif lep_cat == '3l' and sample_info.sample_type == 'MC':
            weights_cat = config['weights 3l']

        if sample_info.sample_type == 'MC' and 'triggerSF' in weights:
            matched_SF = draw_string_maker.get_matched_SF(lep_cat)
            weights = [matched_SF if x=='triggerSF' else x for x in weights]
        #draw_string_maker.multiply_by_factors(weights, [systematic_weight_string])
        draw_string_maker.multiply_by_factors(weights, weights_cat)

        ########################################
        ## ADD IN EFF and (1/EFF) WEIGHTS FOR MC
        ########################################

        if sample_info.sample_type not in ['MC', 'data'] and 'sideband' not in sample_info.sample_type:
            sys.exit('Invalid sample_type must be data, sideband, or MC' % (sample_info.sample_type))

        this_plot_integral = 0.0

        plot = plot_helper.Plot(sample, 0, tree, 'distribution', config['distribution'], draw_string_maker.draw_string)
        #if sample in config['lepton categories'][lep_cat]['data samples'] and plot.plot.Integral() == 0:
            #print draw_string_maker.draw_string
        #print draw_string_maker.draw_string

        if sample_info.sample_type == 'MC':
            plot.plot.Scale(sample_info.x_section * config['luminosity'] / sample_info.num_generated)

        this_plot_integral = plot.plot.Integral()

        #this_plot_integral += plot.plot.Integral()*FR_hist_tight_mu.GetBinContent(ptBin+1, etaBin+1, csvBin+1)
        #this_plot_integral += plot.plot.Integral()*FR_hist_tight_ele.GetBinContent(ptBin+1, etaBin+1, csvBin+1)

        #print sample+' integral for '+lep_cat+', '+bin+', '+bin_NP+', lepton '+str(iLep+1)+', WP('+str(WP_probe)+','+str(WP_tag)+') = '+str(this_plot_integral)

        this_num_denom += this_plot_integral
        ## End loop over samples

    print 'num_denom for '+type+', '+lep_cat+', WP_probe '+str(WP_probe)+', '+bin+', '+bin_NP+', lepton '+str(iLep+1)+' = '+str(this_num_denom)
    return this_num_denom

    
if __name__ == '__main__':
    main()

                                                                                                                                                   
