import re, sys, os, os.path
from argparse import ArgumentParser
import math
import copy
import yaml
import ttHMultileptonAnalysis.DrawPlots.utilities.plot_helper as plot_helper
from ttHMultileptonAnalysis.DrawPlots.utilities.yamlhelpers import ttHMultileptonYAMLLoader
systs = {}

# parser = OptionParser(usage="%prog [options] mc.txt cuts.txt var bins systs.txt ")
parser = ArgumentParser(description='Arguments are [options] config.yaml var systs.txt ')
parser.add_argument('config_file_name', nargs='?', default='stack_plot_configuration.yaml', help='Configuration file to process.')
parser.add_argument('distribution', nargs='?', default='numJets', help='Variable (distribution) name.')
parser.add_argument('systematics_file_names', nargs='*', default='systsEnv_new.txt', help='File with systematics.')
parser.add_argument('-jt', '--jet_tag', action='store_true', help='Add jet-tag category to end of datacard name.')
parser.add_argument('-l', '--label', help='Add label to end of datacard name.')
parser.add_argument('-s', '--scale_all', help='Scale all samples uniformly.')
parser.add_argument('-db','--data_bkg', action='store_true', help='Replace data with background.')
parser.add_argument('-dsb','--data_sig_bkg', action='store_true', help='Replace data with signal+background.')
parser.add_argument('-st','--stat_uncert', help='Use bin-by-bin statistical uncertainties. Can use "all" or "some" or "ttH".')
args = parser.parse_args()

with open(args.config_file_name) as config_file:
    config = yaml.load(config_file, Loader=ttHMultileptonYAMLLoader)

lepton_categories = config['lepton categories']
jet_tag_categories = config['jet tag categories']
distribution = args.distribution
signal_samples = config['signal samples']
background_samples = config['background samples']
data_samples = config['data samples']
ttH_masses = config['ttH mass points'] ##New code to automate masses

input_file_location = config['input file location']
input_file_label = config['input file label']

def main():

    ## import the root libraries; with this import
    ## you won't need to prefix your root objects with ROOT
    from ROOT import *
    gROOT.SetBatch()

    histograms = {}
    for lepton_category in lepton_categories:
        histograms[lepton_category] = {}
        for jet_tag_category in jet_tag_categories:
            histograms[lepton_category][jet_tag_category] = {}
            make_datacard_one_category(lepton_category, jet_tag_category, histograms)

def make_datacard_one_category(lepton_category, jet_tag_category, histograms):

    root_files = {}
    ## Name the output root file and datacard
    category_name = lepton_categories[lepton_category]['category name']
    if args.jet_tag:
        category_name += '_'+jet_tag_category
    else:
        if '_pos' in jet_tag_category:
            category_name += '_pos'
        if '_neg' in jet_tag_category:
            category_name += '_neg'

    ## Create lists of sample names
    signal_keys = signal_samples.keys()
    signal_keys_masses = []
    for key in signal_keys:
        if 'ttH' in key:
            for mass in ttH_masses:
                signal_keys_masses.append(key.replace('ttH','ttH'+mass))
        else:
            signal_keys_masses.append(key)
    background_keys = background_samples.keys()
    data_keys = data_samples.keys()
    signal_background_keys = signal_samples.keys()+background_samples.keys()
    all_keys = signal_samples.keys()+background_samples.keys()+data_samples.keys()
    signal_background_keys_masses = signal_keys_masses+background_samples.keys()
    all_keys_masses = signal_keys_masses+background_samples.keys()+data_samples.keys()

    ## Associate a process number with each sample name
    process_number = {}
    i = 1
    for key in all_keys:
        process_number[key] = i - len(signal_keys)
        i += 1

    if args.data_bkg or args.data_sig_bkg:
        for data_key in data_keys:
            data_samples[data_key]['samples'] = []
            for background_key in background_keys:
                for sample in background_samples[background_key]['samples']:
                    if not sample in lepton_categories[lepton_category]['excluded samples']:
                        data_samples[data_key]['samples'].append(sample)
                    
    if args.data_sig_bkg:
        for data_key in data_keys:
            for signal_key in signal_keys:
                for sample in signal_samples[signal_key]['samples']:
                    if not sample in lepton_categories[lepton_category]['excluded samples']:
                        data_samples[data_key]['samples'].append(sample)

    ## config information (datacard name, systematics, sub-samples)
    cfg_data_sig_bkg = copy.copy(data_samples)
    cfg_data_sig_bkg.update(signal_samples)
    cfg_data_sig_bkg.update(background_samples)

    for sample in all_keys_masses:
        if 'ttH' in sample:
            sample_no_mass = ''.join([i for i in sample if not (i.isdigit() or i=='.')])
            mass = ''.join([i for i in sample if (i.isdigit() or i=='.' )])
        else:
            sample_no_mass = sample
        
        ## Save the sample name as it will appear in the datacard
        sample_d = cfg_data_sig_bkg[sample_no_mass]['datacard name']
        if 'ttH' in sample:
            sample_d += mass

        ## If a data sample is not included in a lepton category, remove it
        if sample in data_keys and not lepton_categories[lepton_category]['data sample'] in sample:
            data_keys.remove(sample)
            continue

        ## If a data sideband (FR or QF) sample is not included in a lepton category, remove it
        if sample in background_keys:
            if 'sideband' in sample and not lepton_categories[lepton_category]['data sample'] in sample:
                background_keys.remove(sample)
                signal_background_keys.remove(sample)
                signal_background_keys_masses.remove(sample)
                continue

        ## If a sample is being excluded, remove it (but it remains in process_number)
        if sample in lepton_categories[lepton_category]['excluded samples']:
            if sample in signal_keys: signal_keys.remove(sample)
            if sample in signal_keys_masses: signal_keys_masses.remove(sample)
            if sample in background_keys: background_keys.remove(sample)
            if sample in data_keys: data_keys.remove(sample)
            if sample in signal_background_keys: signal_background_keys.remove(sample)
            if sample in signal_background_keys_masses: signal_background_keys_masses.remove(sample)
            continue

        ## Create histogram for the sample (may include several sub-samples)
        group_histogram = None
        group_histogram_Up = {}
        group_histogram_Down = {}
        if sample in signal_background_keys_masses:
            ## Create systematic up and down histograms
            systematics = plot_helper.customize_systematics(config['systematics'], cfg_data_sig_bkg[sample_no_mass]['systematics'])
            for systematic in systematics:
                group_histogram_Up[systematic] = None
                group_histogram_Down[systematic] = None

        for sample_part in cfg_data_sig_bkg[sample_no_mass]['samples']:
            if args.scale_all:
                scale = float(args.scale_all)
            else:
                scale = 1.0
            scale *= (cfg_data_sig_bkg[sample_no_mass]['scale'] if 'scale' in cfg_data_sig_bkg[sample_no_mass].keys() else 1.0)				
            
            if 'ttH' in sample:
                sample_part = sample_part.replace('ttH','ttH'+mass)

            ## Specificaly for 6-bin pos / 4-bin neg distributions; kind of a hack
            if '_pos' in jet_tag_category and distribution == 'FinalBDT':
                name_plus_cycle_nominal = distribution+'_pos'
            elif '_neg' in jet_tag_category and distribution == 'FinalBDT':
                name_plus_cycle_nominal = distribution+'_neg'
            else:
                name_plus_cycle_nominal = distribution
        
            root_file_name = '%s/%s/%s_%s_%s_%s.root' % (input_file_location, lepton_category, lepton_category, jet_tag_category, sample_part, input_file_label)
            #print root_file_name
            root_files[sample_part] = TFile(root_file_name)

            ## Create or add to group_histogram
            if not group_histogram:
                #print sample_part
                #print name_plus_cycle_nominal
                #print 'x_%s' % (sample_d)
                group_histogram = root_files[sample_part].Get(name_plus_cycle_nominal).Clone("x_%s" % (sample_d))
            else:
                group_histogram.Add(root_files[sample_part].Get(name_plus_cycle_nominal))

            if sample in signal_background_keys_masses:
                #print sample				
                for systematic in systematics:
                    #print systematic
                    if systematic != 'nominal':
                        if not group_histogram_Up[systematic]:
                            group_histogram_Up[systematic] = root_files[sample_part].Get("%s_%sUp" % (name_plus_cycle_nominal, systematic)).Clone("x_%s_%sUp" % (sample_d, systematic))
                        else:
                            group_histogram_Up[systematic].Add(root_files[sample_part].Get("%s_%sUp" % (name_plus_cycle_nominal, systematic)))
                        if not group_histogram_Down[systematic]:
                            group_histogram_Down[systematic] = root_files[sample_part].Get("%s_%sDown" % (name_plus_cycle_nominal, systematic)).Clone("x_%s_%sDown" % (sample_d, systematic))
                        else:
                            group_histogram_Down[systematic].Add(root_files[sample_part].Get("%s_%sDown" % (name_plus_cycle_nominal, systematic)))
            for systematic in systematics:
                if not group_histogram or not systematic in group_histogram_Up.keys() or not systematic in group_histogram_Down.keys():
                    continue
                if not group_histogram_Up[systematic] or not group_histogram_Down[systematic]:
                    continue
                if (group_histogram_Down[systematic].Integral() - group_histogram.Integral())*(group_histogram_Up[systematic].Integral() - group_histogram.Integral()) > 0.01:
                    print 'Error in sample %s, systematic %s: down = %0.2f, nominal = %0.2f, up = %0.2f' % (sample, systematic, group_histogram_Down[systematic].Integral(), group_histogram.Integral(), group_histogram_Up[systematic].Integral())
                                                  

        #End "for sample_part in cfg_data_sig_bkg[sample]['samples']" loop

        ## Save histograms by lepton category, jet-tag category, and datacard sample name
        histograms[lepton_category][jet_tag_category][sample_d] = group_histogram
        histograms[lepton_category][jet_tag_category][sample_d].Scale(scale)
        histograms[lepton_category][jet_tag_category][sample_d].SetDirectory(0) ##Decouples histogram from root file
        if sample in signal_background_keys_masses:
            for systematic in systematics:
                if systematic != 'nominal':
                    if group_histogram_Up[systematic]:
                        histograms[lepton_category][jet_tag_category]["%s_%s0Up" % (sample_d, systematic)] = group_histogram_Up[systematic]
                        histograms[lepton_category][jet_tag_category]["%s_%s0Up" % (sample_d, systematic)].Scale(scale)
                        histograms[lepton_category][jet_tag_category]["%s_%s0Up" % (sample_d, systematic)].SetDirectory(0)
                    if group_histogram_Down[systematic]:
                        histograms[lepton_category][jet_tag_category]["%s_%s0Down" % (sample_d, systematic)] = group_histogram_Down[systematic]
                        histograms[lepton_category][jet_tag_category]["%s_%s0Down" % (sample_d, systematic)].Scale(scale)
                        histograms[lepton_category][jet_tag_category]["%s_%s0Down" % (sample_d, systematic)].SetDirectory(0)
                        
    #End "for sample in all_keys" loop
    histograms_local = histograms[lepton_category][jet_tag_category]
                
##################################
## Around here, turn into a function, and loop over categories to call it
##################################

    #Rename keys to datacard names
    signal_keys_d = []
    signal_keys_masses_d = []
    background_keys_d = []
    data_keys_d = []
    for key in signal_keys:
        signal_keys_d.append(cfg_data_sig_bkg[key]['datacard name'])
        if 'ttH' in key:
            for mass in ttH_masses:
                signal_keys_masses_d.append(cfg_data_sig_bkg[key]['datacard name']+mass)
        else:
            signal_keys_masses_d.append(cfg_data_sig_bkg[key]['datacard name'])
    for key in background_keys:
        background_keys_d.append(cfg_data_sig_bkg[key]['datacard name']) 
    for key in data_keys:
        data_keys_d.append(cfg_data_sig_bkg[key]['datacard name'])

    #Redefine all_keys, having deleted some
    signal_background_keys = signal_keys+background_keys
    signal_background_keys_d = signal_keys_d+background_keys_d
    all_keys = signal_keys+background_keys+data_keys
    all_keys_d = signal_keys_d+background_keys_d+data_keys_d

    signal_background_keys_masses = signal_keys_masses+background_keys
    signal_background_keys_masses_d = signal_keys_masses_d+background_keys_d
    all_keys_masses = signal_keys_masses+background_keys+data_keys
    all_keys_masses_d = signal_keys_masses_d+background_keys_d+data_keys_d

    ## Find background bins with large statistical uncertainty
    for key in signal_keys_masses_d:
        if not 'Signal' in histograms_local.keys():
            histograms_local['Signal'] = histograms_local[key].Clone('x_Signal')
        else:
            histograms_local['Signal'].Add(histograms_local[key])
    for key in background_keys_d:
        if not 'Background' in histograms_local.keys():
            histograms_local['Background'] = histograms_local[key].Clone('x_Background')
        else:
            histograms_local['Background'].Add(histograms_local[key])
    histograms_local['Signal_Background'] = histograms_local['Signal'].Clone('x_Signal_Background')
    histograms_local['Signal_Background'].Add(histograms_local['Background'])

    bin_syst_names = []
    for key in signal_background_keys_masses_d:
        #print 'Looking at sample %s' % key
        for bin in range(1, histograms_local[key].GetNbinsX()+1):
            data_yield = histograms_local['Signal_Background'].GetBinContent(bin)
            data_error = sqrt(data_yield)
            signal_yield = histograms_local['Signal'].GetBinContent(bin)
            signal_error = histograms_local['Signal'].GetBinError(bin)
            background_yield = histograms_local['Background'].GetBinContent(bin)
            background_error = histograms_local['Background'].GetBinError(bin)
            this_yield = histograms_local[key].GetBinContent(bin)
            this_error = histograms_local[key].GetBinError(bin)
            other_yield = signal_yield + background_yield - this_yield
            other_error = sqrt( pow(signal_error,2) + pow(background_error,2) - pow(this_error,2) )

            do_stat_uncert = False
            if not args.stat_uncert:
                do_stat_uncert = False
            elif 'all' in args.stat_uncert:
                if this_yield > 0.01:
                    do_stat_uncert = True	
            elif 'some' in args.stat_uncert:
                if this_yield > 0.01 and this_yield/background_yield > 0.2 and signal_yield/background_yield > 0.1:
                    do_stat_uncert = True
            elif 'ttH' in args.stat_uncert:
                #### Statistical uncertainty bins from OS ttH analysis
                ### https://github.com/cms-ttH/ttH-Limits/blob/master/python/datacard.py#L93
                if this_yield > 0.01 and background_error > (data_error/5.) and other_error/background_error < 0.95 and signal_yield/background_yield > 0.01:
                    do_stat_uncert = True

            if do_stat_uncert:
#                 print '------- %s bin %d -------' % (key, bin)
#                 print 'This yield: %0.3f' % this_yield
#                 print 'This error: %0.3f' % this_error
#                 print 'Infer %0.1f base events, yield/raw = %0.3f' % ( pow(this_yield/this_error,2), pow(this_error,2)/this_yield )
#                 print 'Signal yield: %0.3f' % signal_yield
#                 print 'Signal error: %0.3f' % signal_error
#                 print 'Other yield: %0.3f' % other_yield
#                 print 'Other error: %0.3f' % other_error
#                 print 'Significance of bin is %0.2f' % (signal_yield/sqrt(background_yield))

                bin_syst_name = '%s_%s_Bin%d' % (key, category_name, bin)
                bin_syst_names.append(bin_syst_name)
                
                histograms_local['%s_%s0Up' % (key, bin_syst_name)] = histograms_local[key].Clone('x_%s_%sUp' % (key, bin_syst_name))  
                histograms_local['%s_%s0Up' % (key, bin_syst_name)].SetBinContent(bin, this_yield + this_error)
                histograms_local['%s_%s0Up' % (key, bin_syst_name)].SetDirectory(0)
                
                histograms_local['%s_%s0Down' % (key, bin_syst_name)] = histograms_local[key].Clone('x_%s_%sDown' % (key, bin_syst_name))
                histograms_local['%s_%s0Down' % (key, bin_syst_name)].SetBinContent(bin, max(0.01, this_yield - this_error))
                histograms_local['%s_%s0Down' % (key, bin_syst_name)].SetDirectory(0)

    print 'Total of %d bins need extra statistical uncertainty' % len(bin_syst_names)
                
    rate_systematics = {}
    shape_systematics = {}

    ## Append the bin-by-bin statistcal uncertainties as template shape uncertainties
    for bin_syst_name in bin_syst_names:
        sample_wildcard = bin_syst_name.split('_%s' % category_name)[0]
        shape_systematics[bin_syst_name] = [(sample_wildcard,bin_syst_name,'templates')]

    with open('all_systematics.txt', 'w') as outfile:
        for fname in args.systematics_file_names:
            with open(fname) as infile:
                outfile.write(infile.read())
    
    #    for sysfile in args[4:]: # e.g. systsEnv.txt and  ../../macros/systematics/btagSyst.txt
    sysfile = 'all_systematics.txt' # e.g. systsEnv.txt and    ../../macros/systematics/btagSyst.txt
    for line in open(sysfile, 'r'):
        if re.match("\s*#.*", line): continue
        line = re.sub("#.*","",line).strip()
        if len(line) == 0: continue
        field = [f.strip() for f in line.split(':')]
        if len(field) < 4:
            raise RuntimeError, "Malformed line %s in file %s"%(line.strip(),sysfile)
        elif len(field) == 4 or field[4] == "lnN": # field[4] is the type of the systematic
            (systematic_name, sample_wildcard, category_wildcard, amount) = field[:4] # systematic name, sample name, lep/jet/tag category, systematic size
            if re.match(category_wildcard,category_name) == None: continue
            if systematic_name not in rate_systematics: rate_systematics[systematic_name] = []
            ## I don't know what re.compile(sample_wildcard) returns ... sample_wildcard seems to work just as well - AWB
            #rate_systematics[systematic_name].append((re.compile(sample_wildcard),amount)) # rate_systematics is only the lnN (or blank?) systematics
            rate_systematics[systematic_name].append((sample_wildcard,amount))
        elif field[4] in ["envelope","shapeOnly","templates","alternateShapeOnly"]:
            (systematic_name, sample_wildcard, category_wildcard, amount) = field[:4]
            if re.match(category_wildcard,category_name) == None: continue
            if systematic_name not in shape_systematics: shape_systematics[systematic_name] = []
            ## I don't know what re.compile(sample_wildcard) returns ... sample_wildcard seems to work just as well - AWB
            #shape_systematics[systematic_name].append((re.compile(sample_wildcard),amount,field[4])) #shape_systematics is the rest
            shape_systematics[systematic_name].append((sample_wildcard,amount,field[4]))
        else:
            raise RuntimeError, "Unknown systematic type %s" % field[4]

    for rate_systematic_name in rate_systematics.keys():
        effect_map = {}
        null_effect = True
        for sample in signal_background_keys_masses_d:
            effect = "-"
            for (sample_wildcard,amount) in rate_systematics[rate_systematic_name]:
                if re.match(sample_wildcard, sample):
                    null_effect = False
                    effect = amount

            effect_map[sample] = effect # effect_map maps effects (floats, or sometimes strings) onto sample key names

        if null_effect:
            del rate_systematics[rate_systematic_name]
        else:
            rate_systematics[rate_systematic_name] = effect_map # syst[systematic name][sample name][amount]

    for shape_systematic_name in shape_systematics.keys():
        effect_map_0  = {} # list with keys of sample names
        effect_map_12 = {}
        null_effect = True
        for sample in signal_background_keys_masses_d:
            effect = "-"
            effect_0  = "-"
            effect_12 = "-"
            for (sample_wildcard,amount,systematic_type) in shape_systematics[shape_systematic_name]: 
                if re.match(sample_wildcard, sample):
                    null_effect = False
                    if systematic_type not in ["templates","alternateShape", "alternateShapeOnly"]:
                        effect = float(amount)
                    else:
                        effect = amount
            nominal = histograms_local[sample] # nominal histogram, by sample name
            if effect == "-" or effect == "0" or nominal.Integral() == 0: 
                effect_map_0[sample]  = "-" 
                effect_map_12[sample] = "-" 
                continue
            if systematic_type in ["envelope","shapeOnly"]:
                hist_0_up = nominal.Clone(nominal.GetName()+"_"+shape_systematic_name+"0Up")
                hist_0_up.Scale(effect) 
                hist_0_down = nominal.Clone(nominal.GetName()+"_"+shape_systematic_name+"0Down")
                hist_0_down.Scale(1.0/effect)
                hist_1_up = nominal.Clone(nominal.GetName()+"_"+shape_systematic_name+"1Up")
                hist_1_down = nominal.Clone(nominal.GetName()+"_"+shape_systematic_name+"1Down")
                hist_2_up = nominal.Clone(nominal.GetName()+"_"+shape_systematic_name+"2Up")
                hist_2_down = nominal.Clone(nominal.GetName()+"_"+shape_systematic_name+"2Down")
                nbin = nominal.GetNbinsX()
                xmin = nominal.GetBinCenter(1)
                xmax = nominal.GetBinCenter(nbin)
                for b in xrange(1,nbin+1):
                    if nbin == 1:
                        continue
                    x = (nominal.GetBinCenter(b)-xmin)/(xmax-xmin)
                    c1 = 2*(x-0.5)           # straight line from (0,-1) to (1,+1)
                    c2 = 1 - 8*(x-0.5)**2  # parabola through (0,-1), (0.5,~1), (1,-1)
                    hist_1_up.SetBinContent(b, hist_1_up.GetBinContent(b) * pow(effect,+c1))
                    hist_1_down.SetBinContent(b, hist_1_down.GetBinContent(b) * pow(effect,-c1))
                    hist_2_up.SetBinContent(b, hist_2_up.GetBinContent(b) * pow(effect,+c2))
                    hist_2_down.SetBinContent(b, hist_2_down.GetBinContent(b) * pow(effect,-c2))
                if systematic_type != "shapeOnly":
                    histograms_local[sample+"_"+shape_systematic_name+"0Up"]   = hist_0_up
                    histograms_local[sample+"_"+shape_systematic_name+"0Down"] = hist_0_down
                    effect_0 = "1"
                histograms_local[sample+"_"+shape_systematic_name+"1Up"]   = hist_1_up
                histograms_local[sample+"_"+shape_systematic_name+"1Down"] = hist_1_down
                histograms_local[sample+"_"+shape_systematic_name+"2Up"]   = hist_2_up
                histograms_local[sample+"_"+shape_systematic_name+"2Down"] = hist_2_down
                effect_12 = "1"
                # useful for plotting
                for hist in hist_0_up, hist_0_down, hist_1_up, hist_1_down, hist_2_up, hist_2_down: 
                    hist.SetFillStyle(0)
                    hist.SetLineWidth(2)
                for hist in hist_1_up, hist_1_down:
                    hist.SetLineColor(4)
                for hist in hist_2_up, hist_2_down:
                    hist.SetLineColor(2)
            elif systematic_type in ["templates"]:
                hist_0_up = histograms_local["%s_%s0Up" % (sample, amount)] 
                hist_0_down = histograms_local["%s_%s0Down" % (sample, amount)]
                if not hist_0_up or not hist_0_down: 
                    raise RuntimeError, "Missing templates %s_%s_(Up,Dn) for %s" % (sample,effect,amount)
                hist_0_up.SetName("%s_%sUp"      % (nominal.GetName(),shape_systematic_name))
                hist_0_down.SetName("%s_%sDown" % (nominal.GetName(),shape_systematic_name))
                histograms_local[hist_0_up.GetName()] = hist_0_up
                histograms_local[hist_0_down.GetName()] = hist_0_down
                effect_0  = "1"
                effect_12 = "-"
            elif systematic_type in ["alternateShape", "alternateShapeOnly"]:
                alternate = histograms_local["%s_%s0Up" % (sample, amount)]
                alternate.SetName("%s_%s0Up" % (nominal.GetName(),shape_systematic_name))
                mirror = nominal.Clone("%s_%s0Down" % (nominal.GetName(),shape_systematic_name))
                if systematic_type == "alternateShapeOnly":
                    alternate.Scale(nominal.Integral()/alternate.Integral())
                for bin in xrange(1,nominal.GetNbinsX()+1):
                    y0 = nominal.GetBinContent(bin)
                    yA = alternate.GetBinContent(bin)
                    yM = y0
                    if (y0 > 0 and yA > 0):
                        yM = y0*y0/yA
                    elif yA == 0:
                        yM = 2*y0
                    mirror.SetBinContent(bin, yM)
                if systematic_type == "alternateShapeOnly":
                    # keep same normalization
                    mirror.Scale(nominal.Integral()/mirror.Integral())
                else:
                    # mirror normalization
                    mnorm = (nominal.Integral()**2)/alternate.Integral()
                    mirror.Scale(mnorm/alternate.Integral())
                histograms_local[alternate.GetName()] = alternate
                histograms_local[mirror.GetName()] = mirror
                effect_0  = "1"
                effect_12 = "-"
            effect_map_0[sample]  = effect_0
            effect_map_12[sample] = effect_12
            #End of loop over samples

        if null_effect:
            del shape_systematics[shape_systematic_name]
        else:
            shape_systematics[shape_systematic_name] = (effect_map_0,effect_map_12,systematic_type)


    signal_background_keys_one_mass_d = []
    for sample in signal_background_keys_masses_d:
        if 'ttH' in sample and not sample.endswith(ttH_masses[0]):
            if sample in effect_map:
                del effect_map[sample]
            if sample in effect_map_0: del effect_map_0[sample]
            if sample in effect_map_12: del effect_map_12[sample]
        else:
            signal_background_keys_one_mass_d.append(sample)

    ## Make the datacard for this category
    outdir = "ND_cards/"
    subdirRoot = "common/"
    ## Version with proper spacing
    if args.label: out_label = '_'+args.label
    else: out_label = ''
    datacard = open(outdir+category_name+out_label+".card.txt", "w")
#    datacard.write("## Datacard for cut file %s\n"%args[1]) ## What arguments did this take? AWB 03-06-14
    datacard.write("## Datacard for cut file %s (all massess, taking signal normalization from templates)\n")
    datacard.write("shapes *        * %s%s.input.root x_$PROCESS x_$PROCESS_$SYSTEMATIC\n" % (subdirRoot, category_name+out_label))
    for sample in reversed(signal_keys_d):
        if 'ttH' in sample: datacard.write("shapes %s  * %s%s.input.root x_$PROCESS$MASS x_$PROCESS$MASS_$SYSTEMATIC\n" % (sample, subdirRoot, category_name+out_label))
#     datacard.write("shapes data_obs * %s.input.root x_data       \n" % category_name) ##Should this be in? AWB 03-06-14
    datacard.write('##----------------------------------\n')
    datacard.write('bin         %s\n' % category_name)
    for sample in data_keys_d:
        datacard.write('observation %s\n' % histograms_local[sample].Integral())
    datacard.write('##----------------------------------\n')
    klen = max([7, len(category_name)]+[len(sample) for sample in signal_background_keys_d])
    kpatt = " %%%ds "  % klen
    fpatt = " %%%d.%df " % (klen,3)
    datacard.write('##----------------------------------\n')
    datacard.write('bin                                                '+(" ".join([kpatt % category_name    for sample in signal_background_keys_d]))+"\n")
    datacard.write('process                                            '+(" ".join([kpatt % sample           for sample in signal_background_keys_d]))+"\n")
    datacard.write('process                                            '+(" ".join([kpatt % process_number[sample] for sample in signal_background_keys]))+"\n")
    datacard.write('rate                                               '+(" ".join([fpatt % (-1.0*('ttH' in sample and len(ttH_masses) > 1) + (not 'ttH' in sample or len(ttH_masses) < 2)*histograms_local[sample].Integral()) for sample in signal_background_keys_one_mass_d]))+"\n")
    datacard.write('##----------------------------------\n')
    for rate_systematic_name,effect_map in rate_systematics.iteritems(): #Uses a different order than signal_background_keys_d
        datacard.write(('%-47s lnN' % rate_systematic_name) + " ".join([kpatt % effect_map[sample] for sample in signal_background_keys_one_mass_d]) +"\n") #12s
    for shape_systematic_name,(effect_map_0,effect_map_12,systematic_type) in shape_systematics.iteritems():
        if systematic_type == "templates":
            datacard.write(('%-45s shape' % shape_systematic_name) + " ".join([kpatt % effect_map_0[sample]     for sample in signal_background_keys_one_mass_d]) +"\n") #10s
        if systematic_type in ["envelope", "alternateShapeOnly"]:
            datacard.write(('%-45s shape' % (shape_systematic_name+"0")) + " ".join([kpatt % effect_map_0[sample]  for sample in signal_background_keys_one_mass_d]) +"\n") #10s
        if systematic_type in ["envelope", "shapeOnly"]:
            datacard.write(('%-45s shape' % (shape_systematic_name+"1")) + " ".join([kpatt % effect_map_12[sample] for sample in signal_background_keys_one_mass_d]) +"\n") #10s
            datacard.write(('%-45s shape' % (shape_systematic_name+"2")) + " ".join([kpatt % effect_map_12[sample] for sample in signal_background_keys_one_mass_d]) +"\n") #10s

    datacard.close()
    print "Wrote to ",outdir+category_name+out_label+".card.txt"

    datacard_nospaces = open(outdir+"nospaces/"+category_name+out_label+".card.nospaces.txt", "w")
    for line in open(outdir+category_name+out_label+".card.txt", 'r'):
        while '  ' in line:
            line = line.replace('  ', ' ')
        datacard_nospaces.write(line)
    datacard_nospaces.close()
    print "Wrote to ",outdir+"nospaces/"+category_name+out_label+".card.nospaces.txt"

    workspace = TFile.Open(outdir+subdirRoot+category_name+out_label+".input.root", "RECREATE")
    for n,h in histograms_local.iteritems():
        workspace.WriteTObject(h,h.GetName())
    workspace.Close()

    print "Wrote to ",outdir+subdirRoot+category_name+out_label+".input.root"

# end make_datacard_one_category

if __name__ == '__main__':
        main()
        
