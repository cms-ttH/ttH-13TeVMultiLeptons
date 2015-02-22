#Interative mode

## 1. Make trees

To make trees:

   	cd ttH-13TeVMultiLeptons/TemplateMakers/test/
        cmsRun osTwoLep_cfg.py

The output tree file will be called multileptree.root

## 2. Make histograms

To make histograms from trees:

   	python make_histos.py -f multileptree.root -s <sample> multilepton.yaml 

Where <sample> options:

      ttH125 TTZJets TTWJets ZJets WJets WZJets TTJets

## 3. Make stack plots

To make stack plots from histograms:

   	./DrawStackPlots.py -w stack_plot_configuration.yaml

## 4. Run limits with combine