#!/usr/bin/env python

import os
import sys

import ROOT

ROOT.gROOT.SetBatch()


def mergeDESYEffFiles () :

    print "Merging histograms into a single file"

    # inputs is a list of tuples
    #   1. Histo File name
    #   2. Input histo name
    #   3. Output histo name 

    baseFile = ROOT.TFile('lepton_SF_8TeV_53x_baseline.root', 'UPDATE')
    
    
    fileNamesAndHistoNames = [('./trigger_SF_ee.root', 'eta2d_scalefactor_with_syst', 'TwoEleTriggerSF' ),
                              ('./trigger_SF_mumu.root', 'eta2d_scalefactor_with_syst', 'TwoMuonTriggerSF'),
                              ('./trigger_SF_emu.root', 'eta2d_scalefactor_with_syst', 'MuonEleTriggerSF'),
                              ('./LooseEle_chargeFlipSF.root', 'ChargeFlipSF', 'LooseEleChargeSafeSF'),
                              ('./LooseEle_IdIsoSF.root', 'IsoIdSF', 'LooseEleIdIsoSF'),
                              ('./LooseMuo_IdIsoSF.root', 'IsoIdSF', 'LooseMuonIdIsoSF'),
                              ('./LooseMuo_TriggerSF.root', 'TriggerSF', 'LooseMuonTriggerSF'),
                              ('./TightEle_IdIsoSF.root', 'IsoIdSF', 'TightEleIdIsoSF'),
                              ('./TightEle_TriggerSF.root', 'TriggerSF', 'TightEleTriggerSF'),
                              ('./TightEle_chargeFlipSF.root', 'ChargeFlipSF', 'TightEleChargeSafeSF')
                              ]

    for (iFileName, iInputName, iOutputName) in fileNamesAndHistoNames:
        print "Considering file {f} looking for histo {h}".format( f=iFileName, h=iInputName)
        inputFile = ROOT.TFile(iFileName) #open for reading
        sfHisto = inputFile.Get(iInputName).Clone(iOutputName)
        if sfHisto is None:
            print "Oops, could not find {h}. Quitting".format(h=iInputName)
            exit (4)
        print "-----> Writing out {o}".format(o=sfHisto.GetName())
        sfHisto.SetDirectory(baseFile)
        baseFile.cd()
        sfHisto.Write(sfHisto.GetName(), ROOT.TObject.kOverwrite)
        inputFile.Close()
        


if __name__ == '__main__':
    mergeDESYEffFiles()
