#!/bin/bash

python CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d higgsCombineTest.Asymptotic.mH125.root -m 125 --doInitialFit --robustFit 1 --rMin -6 --rMax 6

#this takes like 30min
python CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d higgsCombineTest.Asymptotic.mH125.root -m 125 --robustFit 1 --doFits --rMin -6 --rMax 6 --parallel 5

python CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d higgsCombineTest.Asymptotic.mH125.root -m 125 --rMin -6 --rMax 6 -o impacts.json
 
python CombineHarvester/CombineTools/scripts/plotImpacts.py -i impacts.json -o impacts_ttH_13TeV