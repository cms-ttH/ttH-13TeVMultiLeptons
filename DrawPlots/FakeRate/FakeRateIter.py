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
import multiprocessing

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

    FR_keys = config.get('muon pt eta csv categories', {}).keys()
    FR_array = config['muon pt eta csv categories']

    muPt = config['binning']['mu']['pT']
    muEta = config['binning']['mu']['eta']
    muCSV = config['binning']['mu']['jetBTagCSV']
    elePt = config['binning']['ele']['pT']
    eleEta = config['binning']['ele']['eta']
    eleCSV = config['binning']['ele']['jetBTagCSV']

    print 'About to make histograms'
    FR_hist_tight_mu_init = ROOT.TH3F('initial tight mu FR', 'initial tight mu FR', len(muPt)-1, numpy.array(muPt,numpy.dtype(float)), len(muEta)-1, numpy.array(muEta,numpy.dtype(float)), len(muCSV)-1, numpy.array(muCSV,numpy.dtype(float)))
    FR_hist_tight_ele_init = ROOT.TH3F('initial tight ele FR', 'initial tight ele FR', len(elePt)-1, numpy.array(elePt,numpy.dtype(float)), len(eleEta)-1, numpy.array(eleEta,numpy.dtype(float)), len(eleCSV)-1, numpy.array(eleCSV,numpy.dtype(float)))
    FR_hist_tight_mu_final = ROOT.TH3F('final tight mu FR', 'final tight mu FR', len(muPt)-1, numpy.array(muPt,numpy.dtype(float)), len(muEta)-1, numpy.array(muEta,numpy.dtype(float)), len(muCSV)-1, numpy.array(muCSV,numpy.dtype(float)))
    FR_hist_tight_ele_final = ROOT.TH3F('final tight ele FR', 'final tight ele FR', len(elePt)-1, numpy.array(elePt,numpy.dtype(float)), len(eleEta)-1, numpy.array(eleEta,numpy.dtype(float)), len(eleCSV)-1, numpy.array(eleCSV,numpy.dtype(float)))
    print 'Made histogram'

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

    columns_mu_1 = ['iteration']
    columns_mu_2 = ['iteration']
    columns_mu_3 = ['iteration']
    columns_ele_1 = ['iteration']
    columns_ele_2 = ['iteration']
    columns_ele_3 = ['iteration']
    for key in FR_keys:
        if key.startswith('mu') and key.endswith('_1'):
            columns_mu_1.append(key+' (old, new, diff)')
        if key.startswith('mu') and key.endswith('_2'):
            columns_mu_2.append(key+' (old, new, diff)')
        if key.startswith('mu') and key.endswith('_3'):
            columns_mu_3.append(key+' (old, new, diff)')
        if key.startswith('ele') and key.endswith('_1'):
            columns_ele_1.append(key+' (old, new, diff)')
        if key.startswith('ele') and key.endswith('_2'):
            columns_ele_2.append(key+' (old, new, diff)')
        if key.startswith('ele') and key.endswith('_3'):
            columns_ele_3.append(key+' (old, new, diff)')
    iter_table_mu_1 = PrettyTable(columns_mu_1)
    iter_table_mu_2 = PrettyTable(columns_mu_2)
    iter_table_mu_3 = PrettyTable(columns_mu_3)
    iter_table_ele_1 = PrettyTable(columns_ele_1)
    iter_table_ele_2 = PrettyTable(columns_ele_2)
    iter_table_ele_3 = PrettyTable(columns_ele_3)

    #WP = config['lepMVA cuts']['tight']
    WP_presel = config['lepCut cuts']['presel']
    WP_sel = config['lepCut cuts']['tight']
    for iter in range(config.get('iterations')):
        table_entry_mu_1 = [str(iter+1)]
        table_entry_mu_2 = [str(iter+1)]
        table_entry_mu_3 = [str(iter+1)]
        table_entry_ele_1 = [str(iter+1)]
        table_entry_ele_2 = [str(iter+1)]
        table_entry_ele_3 = [str(iter+1)]
        print ''
        print '------- Iteration '+str(iter+1)+' -------'
        for bin in FR_keys:
            num = 0
            denom = 0
            for lep_cat in config.get('lepton categories', {}).keys():
                if lep_cat == 'mu_mu' or lep_cat == 'mu_ele' or lep_cat == 'ele_ele':
                    lepStr = config['leptons']['SS']
                elif lep_cat == '3l':
                    lepStr = config['leptons']['3l']
                for iLep in range(2):
                    if iter == 0:
                        num += compute_num_denom(bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_sel, FR_array, FR_hist_tight_mu_init, FR_hist_tight_ele_init, config)
                        denom += compute_num_denom(bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_presel, FR_array, FR_hist_tight_mu_init, FR_hist_tight_ele_init, config)
                    else:
                        num += compute_num_denom(bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_sel, FR_array, FR_hist_tight_mu_final, FR_hist_tight_ele_final, config)
                        denom += compute_num_denom(bin, lep_cat, iLep, lepStr, base_cuts[lep_cat], WP_sel, WP_presel, FR_array, FR_hist_tight_mu_final, FR_hist_tight_ele_final, config)

            print 'numerator for '+bin+' = '+str(num)
            print 'denominator for '+bin+' = '+str(denom)
            #print '%0.3f, %0.3f, %0.1f' % (FR_array[bin][8], num/denom, 100*((num/denom) - FR_array[bin][8])/FR_array[bin][8])
            if bin.startswith('mu') and bin.endswith('_1'):
                table_entry_mu_1.append('%0.3f, %0.3f +/- %0.3f, %0.1f' % (FR_array[bin][8], num/max(denom,1.0), abs(num/max(denom,1.0))*math.sqrt((1/max(num,1.0))+(1/max(denom,1.0))), 100*((num/max(denom,1.0)) - FR_array[bin][8])/(FR_array[bin][8]+0.0001))+'%')
            if bin.startswith('mu') and bin.endswith('_2'):
                table_entry_mu_2.append('%0.3f, %0.3f +/- %0.3f, %0.1f' % (FR_array[bin][8], num/max(denom,1.0), abs(num/max(denom,1.0))*math.sqrt((1/max(num,1.0))+(1/max(denom,1.0))), 100*((num/max(denom,1.0)) - FR_array[bin][8])/(FR_array[bin][8]+0.0001))+'%')
            if bin.startswith('mu') and bin.endswith('_3'):
                table_entry_mu_3.append('%0.3f, %0.3f +/- %0.3f, %0.1f' % (FR_array[bin][8], num/max(denom,1.0), abs(num/max(denom,1.0))*math.sqrt((1/max(num,1.0))+(1/max(denom,1.0))), 100*((num/max(denom,1.0)) - FR_array[bin][8])/(FR_array[bin][8]+0.0001))+'%')
            if bin.startswith('ele') and bin.endswith('_1'):
                table_entry_ele_1.append('%0.3f, %0.3f +/- %0.3f, %0.1f' % (FR_array[bin][8], num/max(denom,1.0), abs(num/max(denom,1.0))*math.sqrt((1/max(num,1.0))+(1/max(denom,1.0))), 100*((num/max(denom,1.0)) - FR_array[bin][8])/(FR_array[bin][8]+0.0001))+'%')
            if bin.startswith('ele') and bin.endswith('_2'):
                table_entry_ele_2.append('%0.3f, %0.3f +/- %0.3f, %0.1f' % (FR_array[bin][8], num/max(denom,1.0), abs(num/max(denom,1.0))*math.sqrt((1/max(num,1.0))+(1/max(denom,1.0))), 100*((num/max(denom,1.0)) - FR_array[bin][8])/(FR_array[bin][8]+0.0001))+'%')
            if bin.startswith('ele') and bin.endswith('_3'):
                table_entry_ele_3.append('%0.3f, %0.3f +/- %0.3f, %0.1f' % (FR_array[bin][8], num/max(denom,1.0), abs(num/max(denom,1.0))*math.sqrt((1/max(num,1.0))+(1/max(denom,1.0))), 100*((num/max(denom,1.0)) - FR_array[bin][8])/(FR_array[bin][8]+0.0001))+'%')
            #print '-------- old FR = '+str(FR_array[bin][8])+', new FR = '+str(num/denom)+' -------'

            FR_array[bin][8] = num/denom

        iter_table_mu_1.add_row(table_entry_mu_1)
        iter_table_mu_2.add_row(table_entry_mu_2)
        iter_table_mu_3.add_row(table_entry_mu_3)
        iter_table_ele_1.add_row(table_entry_ele_1)
        iter_table_ele_2.add_row(table_entry_ele_2)
        iter_table_ele_3.add_row(table_entry_ele_3)
        print iter_table_mu_1
        print ''
        print iter_table_mu_2
        print ''
        print iter_table_mu_3
        print ''
        print iter_table_ele_1
        print ''
        print iter_table_ele_2
        print ''
        print iter_table_ele_3
        print ''

        for bin in FR_keys:
            if FR_array[bin][0] == 1:
                histBin = FR_hist_tight_mu_final.FindBin( (FR_array[bin][1]+FR_array[bin][2])/2.0, (FR_array[bin][3]+FR_array[bin][4])/2.0, (FR_array[bin][5]+FR_array[bin][6])/2.0 )
                FR_hist_tight_mu_final.SetBinContent(histBin, FR_array[bin][8])
            if FR_array[bin][0] == 0:
                histBin = FR_hist_tight_ele_final.FindBin( (FR_array[bin][1]+FR_array[bin][2])/2.0, (FR_array[bin][3]+FR_array[bin][4])/2.0, (FR_array[bin][5]+FR_array[bin][6])/2.0 )
                FR_hist_tight_ele_final.SetBinContent(histBin, FR_array[bin][8])

def compute_num_denom(bin, lep_cat, iLep, lepStr, base_cut, WP_tag, WP_probe, FR_array, FR_hist_tight_mu, FR_hist_tight_ele, config):

    #print 'Inside compute_num_denom'

    this_base_cut = copy.deepcopy(base_cut)

    this_num_denom = 0.0

    if FR_array[bin][0] == 1 and lep_cat == 'ele_ele':
        return 0.0
    if FR_array[bin][0] == 0 and lep_cat == 'mu_mu':
        return 0.0

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

    these_integrals = {}
    pool = multiprocessing.Pool(processes=10)
    work = []
    
    for sample in config['samples']:

        sample_dict = config['samples'][sample] if config['samples'][sample] else {'systematics':['common'], 'weights':['common']}
        
        tree_sample = sample_dict.get('tree sample', sample)
        additional_cuts = sample_dict.get('additional cuts', [])
        cuts_to_remove = sample_dict.get('cuts to remove', [])
        sample_info = plot_helper.SampleInformation(tree_sample)
        
        if lep_cat == 'mu_mu' or lep_cat == 'mu_ele' or lep_cat == 'ele_ele':
            source_file_name = '%s/%s_%s_all.root' % (config['input_trees_directory'], tree_sample, config['SS label'])
        elif lep_cat == '3l':
            source_file_name = '%s/%s_%s_all.root' % (config['input_trees_directory'], tree_sample, config['3l label'])
        source_file = ROOT.TFile(source_file_name)
        tree = source_file.Get('summaryTree')

        draw_string_maker = plot_helper.DrawStringMaker()

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

        draw_string_maker.remove_selection_requirements(cuts_to_remove)
        draw_string_maker.append_selection_requirements(additional_cuts)

        ## Are the QF weights implemented properly?
        weights = plot_helper.customize_list(config['weights'], sample_dict.get('weights', ['common']))

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

        if sample_info.sample_type not in ['MC', 'data'] and 'sideband' not in sample_info.sample_type:
            sys.exit('Invalid sample_type must be data, sideband, or MC' % (sample_info.sample_type))

        #this_plot_integral = 0.0

        if 'NP_sideband' in sample:
            #print sample
            for isMuon in range(2):
                if isMuon == 1:
                    for ptBin in range(FR_hist_tight_mu.GetNbinsX()):
                        for etaBin in range(FR_hist_tight_mu.GetNbinsY()):
                            for csvBin in range(FR_hist_tight_mu.GetNbinsZ()):
                                tag_lepton_bin_cut = [lepStr+str(abs(iLep-1)+1)+'_isMuon == '+str(isMuon)]
                                tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_pt > '+str(FR_hist_tight_mu.GetXaxis().GetBinLowEdge(ptBin+1)))
                                tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_pt < '+str(FR_hist_tight_mu.GetXaxis().GetBinLowEdge(ptBin+1)+FR_hist_tight_mu.GetXaxis().GetBinWidth(ptBin+1)))
                                tag_lepton_bin_cut[0] += (' && abs('+lepStr+str(abs(iLep-1)+1)+'_eta) > '+str(FR_hist_tight_mu.GetYaxis().GetBinLowEdge(etaBin+1)))
                                tag_lepton_bin_cut[0] += (' && abs('+lepStr+str(abs(iLep-1)+1)+'_eta) < '+str(FR_hist_tight_mu.GetYaxis().GetBinLowEdge(etaBin+1)+FR_hist_tight_mu.GetYaxis().GetBinWidth(etaBin+1)))
                                tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_jetBTagCSV > '+str(FR_hist_tight_mu.GetZaxis().GetBinLowEdge(csvBin+1)))
                                tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_jetBTagCSV < '+str(FR_hist_tight_mu.GetZaxis().GetBinLowEdge(csvBin+1)+FR_hist_tight_mu.GetZaxis().GetBinWidth(csvBin+1)))
                                #print tag_lepton_bin_cut
                                #print FR_hist_tight_mu.GetBinContent(ptBin+1, etaBin+1)
                                draw_string_maker.append_selection_requirements(tag_lepton_bin_cut)
                                these_integrals['%s_%d_%d_%d_%d' % (sample, isMuon, ptBin, etaBin, csvBin)] = -99.0
                                
#                                 output_file = ROOT.TFile('temp_'+str(FR_hist_tight_mu.GetNbinsX())+'_'+str(FR_hist_tight_mu.GetNbinsY())+'_'+str(FR_hist_tight_mu.GetNbinsZ())+'.root', 'RECREATE')
#                                 plot = plot_helper.Plot(sample, output_file, tree, 'distribution', config['distribution'], draw_string_maker.draw_string)
#                                 #print draw_string_maker.draw_string
#                                 #print plot.plot.Integral()
#                                 this_plot_integral += plot.plot.Integral()*FR_hist_tight_mu.GetBinContent(ptBin+1, etaBin+1, csvBin+1)

                                thread_index = FR_hist_tight_mu.GetNbinsX()*100 + FR_hist_tight_mu.GetNbinsY()*10 + FR_hist_tight_mu.GetNbinsZ()
                                scale = FR_hist_tight_mu.GetBinContent(ptBin+1, etaBin+1, csvBin+1)
                                #these_integrals['%s_%d_%d_%d_%d' % (sample, isMuon, ptBin, etaBin, csvBin)] = get_one_integral(thread_index, sample, tree, config['distribution'], draw_string_maker.draw_string, scale)
                                work.append( ('%s_%d_%d_%d_%d' % (sample, isMuon, ptBin, etaBin, csvBin), pool.apply_async(get_one_integral, [thread_index, sample, config['distribution'], draw_string_maker.draw_string, scale, source_file_name]) ) )
                                
                                draw_string_maker.remove_selection_requirements(tag_lepton_bin_cut)
                                
#                                 output_file.Close()

                else:
                    for ptBin in range(FR_hist_tight_ele.GetNbinsX()):
                        for etaBin in range(FR_hist_tight_ele.GetNbinsY()):
                            for csvBin in range(FR_hist_tight_ele.GetNbinsZ()):
                                tag_lepton_bin_cut = [lepStr+str(abs(iLep-1)+1)+'_isMuon == '+str(isMuon)]
                                tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_pt > '+str(FR_hist_tight_ele.GetXaxis().GetBinLowEdge(ptBin+1)))
                                tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_pt < '+str(FR_hist_tight_ele.GetXaxis().GetBinLowEdge(ptBin+1)+FR_hist_tight_ele.GetXaxis().GetBinWidth(ptBin+1)))
                                tag_lepton_bin_cut[0] += (' && abs('+lepStr+str(abs(iLep-1)+1)+'_eta) > '+str(FR_hist_tight_ele.GetYaxis().GetBinLowEdge(etaBin+1)))
                                tag_lepton_bin_cut[0] += (' && abs('+lepStr+str(abs(iLep-1)+1)+'_eta) < '+str(FR_hist_tight_ele.GetYaxis().GetBinLowEdge(etaBin+1)+FR_hist_tight_ele.GetYaxis().GetBinWidth(etaBin+1)))
                                tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_jetBTagCSV > '+str(FR_hist_tight_ele.GetZaxis().GetBinLowEdge(csvBin+1)))
                                tag_lepton_bin_cut[0] += (' && '+lepStr+str(abs(iLep-1)+1)+'_jetBTagCSV < '+str(FR_hist_tight_ele.GetZaxis().GetBinLowEdge(csvBin+1)+FR_hist_tight_ele.GetZaxis().GetBinWidth(csvBin+1)))
                                #print tag_lepton_bin_cut
                                #print FR_hist_tight_ele.GetBinContent(ptBin+1, etaBin+1)
                                draw_string_maker.append_selection_requirements(tag_lepton_bin_cut)
                                these_integrals['%s_%d_%d_%d_%d' % (sample, isMuon, ptBin, etaBin, csvBin)] = -99.0

#                                 output_file = ROOT.TFile('temp_'+str(FR_hist_tight_mu.GetNbinsX())+'_'+str(FR_hist_tight_mu.GetNbinsY())+'_'+str(FR_hist_tight_mu.GetNbinsZ())+'.root', 'RECREATE')
#                                 plot = plot_helper.Plot(sample, output_file, tree, 'distribution', config['distribution'], draw_string_maker.draw_string)
#                                 #print draw_string_maker.draw_string
#                                 #print plot.plot.Integral()
#                                 this_plot_integral += plot.plot.Integral()*FR_hist_tight_ele.GetBinContent(ptBin+1, etaBin+1, csvBin+1)

                                thread_index = FR_hist_tight_ele.GetNbinsX()*100 + FR_hist_tight_ele.GetNbinsY()*10 + FR_hist_tight_ele.GetNbinsZ()
                                scale = FR_hist_tight_ele.GetBinContent(ptBin+1, etaBin+1, csvBin+1)
                                #these_integrals['%s_%d_%d_%d_%d' % (sample, isMuon, ptBin, etaBin, csvBin)] = get_one_integral(thread_index, sample, tree, config['distribution'], draw_string_maker.draw_string, scale)
                                work.append( ('%s_%d_%d_%d_%d' % (sample, isMuon, ptBin, etaBin, csvBin), pool.apply_async(get_one_integral, [thread_index, sample, config['distribution'], draw_string_maker.draw_string, scale, source_file_name]) ) )
                                
                                draw_string_maker.remove_selection_requirements(tag_lepton_bin_cut)
                                
#                                 output_file.Close()
                            
        else:

            these_integrals[sample] = -99.0
            
#             output_file = ROOT.TFile('temp_'+str(FR_hist_tight_mu.GetNbinsX())+'_'+str(FR_hist_tight_mu.GetNbinsY())+'_'+str(FR_hist_tight_mu.GetNbinsZ())+'.root', 'RECREATE')
#             plot = plot_helper.Plot(sample, output_file, tree, 'distribution', config['distribution'], draw_string_maker.draw_string)
#             #if sample in config['lepton categories'][lep_cat]['data samples'] and plot.plot.Integral() == 0:
#                 #print draw_string_maker.draw_string
#             #print draw_string_maker.draw_string
#             if sample_info.sample_type == 'MC':
#                 plot.plot.Scale(sample_info.x_section * config['luminosity'] / sample_info.num_generated)
#             this_plot_integral = plot.plot.Integral()

            thread_index = FR_hist_tight_mu.GetNbinsX()*100 + FR_hist_tight_mu.GetNbinsY()*10 + FR_hist_tight_mu.GetNbinsZ()
            scale = 1.0
            if sample_info.sample_type == 'MC':
                scale = sample_info.x_section * config['luminosity'] / sample_info.num_generated
            #these_integrals[sample] = get_one_integral(thread_index, sample, tree, config['distribution'], draw_string_maker.draw_string, scale)
            work.append( (sample, pool.apply_async(get_one_integral, [thread_index, sample, config['distribution'], draw_string_maker.draw_string, scale, source_file_name]) ) )
            #for (id, res) in work:
                #these_integrals[id] = res.get()
                #print 'id %s in work yields %f' % (id, these_integrals[id])

#             output_file.Close()

        #print sample+' integral for '+lep_cat+', '+bin+', lepton '+str(iLep+1)+' = '+str(this_plot_integral)

#         if sample in config['lepton categories'][lep_cat]['data samples']:
#             this_num_denom += this_plot_integral
#         else:
#             this_num_denom -= this_plot_integral

    for (id, res) in work:
        these_integrals[id] = res.get()

    #pool.join()
    #pool.close()
    
    for sample in these_integrals:
        #print '%s integral is %f' % (sample, these_integrals[sample])
        if sample in config['lepton categories'][lep_cat]['data samples']:
            this_num_denom += these_integrals[sample]
        else:
            this_num_denom -= these_integrals[sample]

    print 'num_denom for '+lep_cat+', WP_probe '+str(WP_probe)+', '+bin+', lepton '+str(iLep+1)+' = '+str(this_num_denom)
    return this_num_denom


def get_one_integral(thread_index, sample, parameters, draw_string, scale, source_file_name):

    #print 'Calling get_one_integral with index %s, sample %s' % (thread_index, sample)

    source_file = ROOT.TFile(source_file_name)
    tree = source_file.Get('summaryTree')
    #print thread_index
    #print sample
    #print draw_string
    #print scale

    #output_file = ROOT.TFile('temp_'+str(thread_index)+'.root', 'RECREATE')
    output_file = 0
    
    plot = plot_helper.Plot(sample, output_file, tree, 'distribution', parameters, draw_string)
    this_plot_integral = plot.plot.Integral()*scale
    #output_file.Close()

    #print 'this_plot_integral = %f' % (this_plot_integral)

    return this_plot_integral
    
if __name__ == '__main__':
    main()

                                                                                                                                                   
