#!/usr/bin/env python
import os
import collections
import matplotlib.pyplot as plt
import plot_helper
#from ttHMultileptonAnalysis.DrawPlots.utilities.prettytable import PrettyTable
import importlib
PrettyTablemod = importlib.import_module('ttH-13TeVMultiLeptons.DrawPlots.utilities.prettytable', None)
PrettyTable = getattr(PrettyTablemod, 'PrettyTable')


def make_yield_pie_charts(yields_object, dir, signals, jet_tag_categories):
    colors = ['#490A3D', '#BD1550', '#E97F02', '#F8CA00', '#8A9B0F', '#FEB89F', '#E23D75', '#5F0D3B', '#742365', '#909A92', '#744F78', '#30091E']
    www_plot_directory = os.path.join(plot_helper.get_www_base_directory(), dir, 'pies')
    plot_helper.make_fresh_directory(www_plot_directory)

    yields_dict = collections.defaultdict(list)
    labels_dict = collections.defaultdict(list)
    for jet_tag_category, jet_cat_dict in yields_object.items():
        for sample, sample_dict in jet_cat_dict.items():
            if sample not in ['data', 'all backgrounds', 'all signals']:
                for lepton_category, entries in sample_dict.items():
                    yields_dict[jet_tag_categories[jet_tag_category]+' ('+lepton_category+')'].append(entries)
                    labels_dict[jet_tag_categories[jet_tag_category]+' ('+lepton_category+')'].append(sample)

    headers = ['category', 'bg yield'] + [x.replace('t#bar{t}H125', '')+' yield' for x in signals] + ['s/b '+ x.replace('t#bar{t}H125', '') for x in signals]
    table = PrettyTable(headers)
    table.align = 'l'
    for (category, labels), yields in zip(labels_dict.items(), yields_dict.values()):
        if sum(yields) == 0 or 'inclusive' not in category:
            continue
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.set_position([0.1, 0.1, 0.5, 0.8])

        fracs = [x/sum(yields) for x in yields]
        patches, texts = plt.pie(fracs, colors=colors)
        leg = plt.legend(patches, labels, bbox_to_anchor=(1.05, 0.9), loc=2)
        leg.get_frame().set_alpha(0)
        plt.axis('equal')

        name = filter(str.isalnum, category)
        plt.title(category)
        plt.savefig(os.path.join(www_plot_directory, name+'.png'))
        plt.savefig(os.path.join(www_plot_directory, name+'.pdf'))
        plt.close()

        background_yields = [x for x, y in zip(yields, labels) if y not in signals]
        signal_yields = [x for x, y in zip(yields, labels) if y in signals]
        bg_sum = sum(background_yields)
        table.add_row([category, format(bg_sum, '.2f')] + [format(x, '.2f') for x in signal_yields] + [format(x/bg_sum, '.3f') for x in signal_yields])

    print table.get_string(sortby=headers[-1])

    plot_helper.update_indexes(www_plot_directory)
