#General Instructions


## 1. Make the ntuples

The cmsRun config is osTwoLep_cfg.py and is located in Templatemakers/test. This uses the edm plugin OSTwoLepAna. 
Despite the "OSTwoLep" moniker, there is no event selection applied at this stage, except for a loose skim of 2 or more
preselected leptons, which can be disabled by commenting out appropriate lines in Templatemakers/plugins/OSTwoLepAna.cc.

To make a test ntuple, you can simply run an interactive job after editing osTwoLep_cfg.py. To process all the samples,
you can edit the various crab configs to point to your favorite stage-out area, and then in the test directory type:

    source crabscript.csh


## 2. Use the ntuples for studies

Several pieces of code exist or are in development for doing studies with our ntuples:

makesimpleplot.py -- See [this older version](https://github.com/cms-ttH/ttH-13TeVMultiLeptons/blob/ccb950fa684e6ce62224080508a36b0ba2ff7abe/TemplateMakers/test/makesimpleplot.py) 
for a simple example of how to make a plot using the nutuples. The current version is a slightly more complex example.

makegoodplot.C -- A c++ - based tool for doing quick studies. Integers which represent the samples are added to a vector, which is passed to a helper class that runs a given study.
 
MakeGoodPlot.cc -- Class used by makegoodplot.C. Provides some modularity for common tasks (loading samples, initialization of tree variables, etc.) 
Note that some parts of this class are left over from another analysis, and have not yet been updated. To start a new study, just add a new public 
member function and call it from makegoodplot.C. For example, see the "print_cutflow" function. Specify the location of your ntuples in "load_samples."
         
variables.h -- Function templates that can be used to calculate analysis variables (c++)

variables.py -- Functions that can be used to calculate analysis variables (python)


## 3. Make flat trees

The tools to make flat trees are located in Templatemakers/test. These trees are filled with all the variables used in 
the analysis, and are calculated from the ntuple collections. The trees can be used in MVA training, and are also used to 
fill histograms in the next step. To run an interactive job:

    root addvarstotree.C+'("root://eoscms.cern.ch//eos/cms/store/path/to/ntuples/ttH125/*.root","ttH125.root")'

Where you should replace the "root://.../*.root" with the path to the directory containing your ntuples. If you choose to,
at this stage you can apply some additional cuts to reduce the size of the trees, for example if you are only interested in
looking at one analysis category. 
If you are working on lxplus, you can also run batch jobs through ssh (in order to avoid waiting long times in bsub queues):

    ./addvarstotree.sh


## 3. Make histograms

The histogram-making tools are located in DrawPlots. The python executable is make_histo.py, which has various parameters that 
can be controlled by editing the multilepton.yaml config file. For an interactive job with one input file:

    ./make_histos.py -f ttH125.root -s ttH125 multilepton.yaml 

Here, the ttH125.root file contains the flat tree produced in the previous step. The "-s ttH125" tells the script what the sample
is. Currently, the choices are: ttH125, TTZJets, TTWJets, ZJets, WJets, WZJets, and TTJets. This script will apply the event selection
corresponding to the different analysis categories, and store the output histograms in the "histos" directory.
When making the histos starting from trees that already contain some cuts, or when running over small samples, batch jobs are not usually necessary. Typing:

    source launchmakehistos_oneinputpersample_sequence.csh

will create one histo-making process per sample. Alternatively, you can run batch jobs to make the histograms by typing:

    ./launchmakehistos.sh

To collect the histograms in one file (in preparation for running the limits), run this script:

    root collect_disc_results_53x_v27.C+'(-99,27)'


## 4. Make stack plots

A similar python script + yaml config combination exists to make stack plots. Once you have the histograms, edit stack_plot_configuration.yaml to
point to their location. Various other parameters can be configured. Make the plots by typing:

    ./DrawStackPlots.py -w stack_plot_configuration.yaml

where the "-w" flag will automatically post the plots to your CERN web area.


## 5. Run limits with combine

Once the histos have been made, you can run limits. For now, this code is based off the ttH code from 8 TeV. You can follow the instructions to check it out here:

    https://github.com/cms-ttH/ttH-Limits

You will also need the package HiggsAnalysis/CombinedLimit, which isn't part of the central CMSSW anymore so you can't grab it using cms-addpkg. Instead, for now do:

    git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit

Copy the file with the collected histograms over to ttH/Limits/macros/. Then, hack ttH/Limits/scripts/mk_datacard, by adding the following around line 69:

    "multilep_2lss multilep_3l multilep_4l " \ 

Do a scram b, then make the datacard:

    mk_datacard -o card_ml_test4.dat -d "MVA" -c "multilep_2lss multilep_3l multilep_4l" collect_results2.root

And then finally, run the limits:

    combine -M Asymptotic --minosAlgo stepping -S 0 -m 125 -t -1 card_ml_test4.dat 

