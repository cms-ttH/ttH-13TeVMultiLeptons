import datetime
from glob import glob
from lobster import cmssw
from lobster.core import AdvancedOptions, Category, Config, Dataset, StorageConfiguration, Workflow

version = datetime.datetime.now().strftime('%Y%m%d_%H%M')

#thisround = "lobster_trees__EFT_test_14_4_18/" # old Fall17 MINIAOD
#thisround = "lobster_trees__EFT_test_28_4_18/" # available new MINIAOD 
#thisround = "lobster_trees__EFT_SingleMu_only_test_10_5_18/" #SingleMu data and ttjets only
#thisround = "lobster_trees__EFT_noSkim_test_10_5_18/" #ttjets only
#thisround = "lobster_trees__EFT_for_trigSFs_15_5_18/"


## current ##
isdata = False
#############

ddbr_or_nom = ['nom']
#thisround = "lobster_trees__lobster_trees__EFT_test_25_5_18/" # mc
#thisround = "lobster_trees__lobster_trees__EFT_test_14_6_18/" # EFT mc
#thisround = "/" # MD EFT mc

if isdata:
    #thisround = "lobster_trees__lobster_trees__EFT_test_20_5_18/" # data
    ddbr_or_nom=['nom','_Fakes','_QFs']
    #ddbr_or_nom=['_Fakes']
    #ddbr_or_nom=['_Fakes','_QFs']
    #ddbr_or_nom = ['nom']
    
#/store/user/$USER
storage = StorageConfiguration(
    input=[
        #"hdfs://eddie.crc.nd.edu:19000/store/user/gesmith/crab/EFT_test_6_12_17/",
        #"root://deepthought.crc.nd.edu//store/user/gesmith/crab/EFT_test_6_12_17/"
        #"hdfs://eddie.crc.nd.edu:19000/store/user/gesmith/crab/"+thisround,
        #"root://deepthought.crc.nd.edu//store/user/gesmith/crab/"+thisround
        "file:///hadoop/store/user/gesmith/",
        "hdfs://eddie.crc.nd.edu:19000/store/user/gesmith/", #+thisround,
        "root://deepthought.crc.nd.edu//store/user/gesmith/", #+thisround
        "gsiftp://T3_US_NotreDame/store/user/gesmith/",
    ],
    output=[
        #"hdfs://eddie.crc.nd.edu:19000/store/user/gesmith/lobster_test_" + version,
        "file:///hadoop/store/user/gesmith/lobster_test_" + version,
        # ND is not in the XrootD redirector, thus hardcode server.
        # Note the double-slash after the hostname!
        "root://deepthought.crc.nd.edu//store/user/gesmith/lobster_test_" + version,
        #"chirp://eddie.crc.nd.edu:9094/store/user/gesmith/lobster_test_" + version,
        "gsiftp://T3_US_NotreDame/store/user/gesmith/lobster_test_" + version,
        "srm://T3_US_NotreDame/store/user/gesmith/lobster_test_" + version
    ]
)

processing = Category(
    name='processing',
    cores=1,
    #runtime=2 * 60,  # Time in seconds (for one job)
    memory=6000
)


mysamples = []
if (not isdata):
    ## Add the MC...
#    mysamples.append('DYJets_M50')
#    mysamples.append('SingleTop_schan')

  # mysamples.append('SingleTop_tWchan_antitop')
  # mysamples.append('SingleTop_tWchan_top')
  # mysamples.append('SingleTop_tchan_antitop')
  # mysamples.append('SingleTop_tchan_top')
    
#     mysamples.append('WW')                                
#     mysamples.append('WZ')  
#     mysamples.append('ZZ')
#     mysamples.append('WWW')
#     mysamples.append('WWZ')
#     mysamples.append('WZZ')
#     mysamples.append('ZZZ')
#     mysamples.append('ttGJets')
    
    # mysamples.append('ttJets')                              #<-- new in latest round
    ## #mysamples.append('ttJets_Dilept')                      #<-- not in latest round
    ## #mysamples.append('ttJets_SingleLeptFromT')             #<-- not in latest round
    ## #mysamples.append('ttJets_SingleLeptFromTbar')          #<-- not in latest round

#     mysamples.append('ttH')
#     mysamples.append('ttW')
#     mysamples.append('ttZ')
#    mysamples.append('tZq')
#     mysamples.append('tHq')

#   #  ## mysamples.append('ttWW')
#   #  ## mysamples.append('ttWZ')
# # #   mysamples.append('DYJets_M10to50')                    
# # #   mysamples.append('WJets')                             


    # EFT samps
    ##mysamples.append('ttH_cbW')
#     mysamples.append('ttH_cpQ3') 
#     mysamples.append('ttH_cpQM') 
#     mysamples.append('ttH_cptb') 
#     mysamples.append('ttH_cpt')
#     mysamples.append('ttH_cQe1') 
#     mysamples.append('ttH_ctG')
#     mysamples.append('ttH_ctl1') 
#     mysamples.append('ttH_ctp')
#     mysamples.append('ttH_ctW')
#     mysamples.append('ttH_ctZ')
#     mysamples.append('tllq_cpQ3')
#     mysamples.append('tllq_cpQM')
#     mysamples.append('tllq_cptb')
#     mysamples.append('tllq_cpt') 
#     mysamples.append('tllq_cQe1')
#     mysamples.append('tllq_ctG') 
#     mysamples.append('tllq_ctl1')
#     mysamples.append('tllq_ctp') 
#     mysamples.append('tllq_ctW') 
#     mysamples.append('tllq_ctZ') 
#     ##mysamples.append('ttll_cbW') 
#     mysamples.append('ttll_cpQ3')
#     mysamples.append('ttll_cpQM')
#     mysamples.append('ttll_cptb')
#     mysamples.append('ttll_cpt') 
#     mysamples.append('ttll_cQe1')
#     mysamples.append('ttll_ctG') 
#     mysamples.append('ttll_ctl1')
#     mysamples.append('ttll_ctp') 
#     mysamples.append('ttll_ctW') 
#     mysamples.append('ttll_ctZ') 
#     ##mysamples.append('ttlnu_cbW')
#     mysamples.append('ttlnu_cpQ3')
#     mysamples.append('ttlnu_cpQM')
#     mysamples.append('ttlnu_cptb')
#     mysamples.append('ttlnu_cpt')
#     mysamples.append('ttlnu_cQe1')
#     mysamples.append('ttlnu_ctG')
#     mysamples.append('ttlnu_ctl1')
#     mysamples.append('ttlnu_ctp')
#     mysamples.append('ttlnu_ctW')
#     mysamples.append('ttlnu_ctZ')
    
#     mysamples.append('ttH_multidim')
#     mysamples.append('ttlnu_multidim')
     mysamples.append('ttll_multidim')
#     mysamples.append('tllq_multidim')
#     mysamples.append('tHq_multidim')
    
    
    #mysamples.append('ttlnu_no_rewgt_1Jet')
    #mysamples.append('ttlnu_no_rewgt_0Jet')
    
    

if isdata:
# ## Add the data...
    mysamples.append('DoubleEG')
    mysamples.append('DoubleMuon')
    mysamples.append('MuonEG')
    mysamples.append('SingleElectron')
    mysamples.append('SingleMuon')


## for trigger studies only:
#mysamples.append('MET')

### moving these here temporarily
## lobster_trees__EFT_test_14_4_18 samps
# mysamples.append('DYJets_M10to50')                     #<-- not in latest round
# mysamples.append('WJets')                              #<-- not in latest round
# mysamples.append('WW')                                 #<-- not in latest round
# mysamples.append('WZ')                                 #<-- not in latest round
# mysamples.append('tttt')                               #<-- not in latest round

#mysamples.append('ttJets_noSkim')

## ToDo: just update sample_names_reg to be the above.


data = [] # <- n.b. this is probably going to end up being huge
for samp in mysamples:
    # this only works if you already made the file lists using loadsample first
    sampfile = open("inputfiles__"+samp+".txt")
    file_list =  sampfile.read().splitlines()
    #file_list = [x.replace("/hadoop/store/user/gesmith/"+thisround,"") for x in file_list]
    file_list = [x.replace("/hadoop/store/user/gesmith/","") for x in file_list]
    file_list = [x.rsplit("/",1)[0] for x in file_list] #removes trailing "/whatever.root"    
    file_list = [x+"/" for x in file_list] # add back trailing /
    file_list = set(file_list)
    file_list = list(file_list) # This gives us a unique list of sub-dirs, starting from 
                                # the storage.input dir. We add the final trailing "*.root" 
                                # when setting up the Workflow below.
    data.append( (samp, file_list) )
    sampfile.close()
    print " "
    print samp,": ",file_list


# This doesn't do what you would think:
#sandbox = cmssw.Sandbox(include=['ttH-13TeVMultiLeptons/TemplateMakers/test/MakeGoodPlot2'])
sandbox = cmssw.Sandbox(include=['ttH-13TeVMultiLeptons/TemplateMakers/src','ttH-13TeVMultiLeptons/TemplateMakers/data'])
# Most stuff has to be added "by hand":
extra_inputs=[]
extra_inputs.append('../variables.h')
extra_inputs.append('../functionsTTH.cc')
extra_inputs.append('../csvSF_treeReader_13TeV.C')
extra_inputs.append('../EFT_code/helperToolsEFT.h')
headerfiles = glob("*.h")
extra_inputs.extend(headerfiles)
extra_inputs.append('wrapper_lobster.C')
extra_inputs.append('wrapper_lobster.py')

print " "
print "included files: ",extra_inputs
print " "

workflows = []
for thing in ddbr_or_nom:
    extlabel=''
    if (thing!='nom'):
        extlabel=thing
    for label, dirs in data:
        fpt=10
        #if (label=='tZq' or label=='ttW' or label=='ttZ' or label[:3]=='ttH' or label[:5]=='ttlnu' or label[:4]=='tllq' or label[:4]=='ttll'):
        if (label=='tZq' or label=='ttW' or label=='ttZ' or label=='ttH_multidim' or label=='ttlnu_multidim' or label=='ttlq_multidim' or label=='ttll_multidim' or label=='tHq_multidim'):
            fpt=1
        if (label=='ttJets'):
            fpt=5
        if (label=='DoubleEG' or label=='DoubleMuon' or label=='MuonEG' or label=='SingleElectron' or label=='SingleMuon'):
            fpt=50
        ttH = Workflow(
            label=label+extlabel,
            dataset=Dataset(
                files=dirs,
                files_per_task=fpt,
                patterns=["*.root"]
            ),
            category=processing,
            command='python wrapper_lobster.py '+label+' '+thing+' @inputfiles',
            extra_inputs=extra_inputs,
            publish_label='test',
            merge_command='hadd @outputfiles @inputfiles',
            #merge_size='0.001K',
            #merge_size='1G',
            #merge_size = -1,
            #merge_size='10M',
            merge_size='50G',
            outputs=['output.root'],
            sandbox=sandbox
        )

        workflows.append(ttH)
        print "added workflow ",label+extlabel


config = Config(
    workdir='/tmpscratch/users/$USER/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    label=version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(
        bad_exit_codes=[127, 160],
        log_level=1
    )
)
