import datetime
from glob import glob
from lobster import cmssw
from lobster.core import AdvancedOptions, Category, Config, Dataset, StorageConfiguration, Workflow

version = datetime.datetime.now().strftime('%Y%m%d_%H%M')

thisround = "lobster_trees__EFT_test_14_4_18/"



#/store/user/$USER
storage = StorageConfiguration(
    input=[
        #"hdfs://eddie.crc.nd.edu:19000/store/user/gesmith/crab/EFT_test_6_12_17/",
        #"root://deepthought.crc.nd.edu//store/user/gesmith/crab/EFT_test_6_12_17/"
        #"hdfs://eddie.crc.nd.edu:19000/store/user/gesmith/crab/"+thisround,
        #"root://deepthought.crc.nd.edu//store/user/gesmith/crab/"+thisround
        #"hdfs://eddie.crc.nd.edu:19000/store/user/gesmith/"+thisround,
        "root://deepthought.crc.nd.edu//store/user/gesmith/"+thisround
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
    memory=1000
)


mysamples = []
## Add the MC...
mysamples.append('DYJets_M10to50')
mysamples.append('DYJets_M50')
mysamples.append('SingleTop_schan')
mysamples.append('SingleTop_tWchan_antitop')
mysamples.append('SingleTop_tWchan_top')
mysamples.append('SingleTop_tchan_antitop')
mysamples.append('SingleTop_tchan_top')
mysamples.append('WJets')
mysamples.append('WW')
mysamples.append('WZ')
mysamples.append('ZZ')
mysamples.append('WWW')
mysamples.append('WWZ')
mysamples.append('WZZ')
mysamples.append('ZZZ')
mysamples.append('ttJets_Dilept')
mysamples.append('ttJets_SingleLeptFromT')
mysamples.append('ttJets_SingleLeptFromTbar')
mysamples.append('ttH')
mysamples.append('ttW')
mysamples.append('ttZ')
mysamples.append('tZq')
mysamples.append('tttt')
mysamples.append('ttWW')
mysamples.append('ttWZ')
# ## Add the data...
mysamples.append('DoubleEG')
mysamples.append('DoubleMuon')
mysamples.append('MuonEG')
mysamples.append('SingleElectron')
mysamples.append('SingleMuon')
## ToDo: just update sample_names_reg to be the above.


data = [] # <- n.b. this is probably going to end up being huge
for samp in mysamples:
    # this only works if you already made the file lists using loadsample first
    sampfile = open("inputfiles__"+samp+".txt")
    file_list =  sampfile.read().splitlines()
    #file_list = [x.replace("/hadoop/store/user/gesmith/crab/"+thisround,"") for x in file_list]
    file_list = [x.replace("/hadoop/store/user/gesmith/"+thisround,"") for x in file_list]
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
headerfiles = glob("*.h")
extra_inputs.extend(headerfiles)
extra_inputs.append('wrapper_lobster.C')
extra_inputs.append('wrapper_lobster.py')
print " "
print "included files: ",extra_inputs
print " "

workflows = []
for label, dirs in data:
    ttH = Workflow(
        label=label,
        # maybe update this part:
        dataset=Dataset(
            files=dirs,
            files_per_task=1, # eventually change to 5-10
            patterns=["*.root"]
        ),
        category=processing,
        command='python wrapper_lobster.py '+label+' @inputfiles',
        #extra_inputs=[
        #    #'wrapper_lobster_C.so',
        #    #'wrapper_lobster_C_ACLiC_dict_rdict.pcm',
        #    #'wrapper_lobster_C.d',
        #    'wrapper_lobster.C',
        #    'wrapper.py',
        #],
        extra_inputs=extra_inputs,
        publish_label='test',
        merge_command='hadd @outputfiles @inputfiles',
        merge_size='0.001K',
        outputs=['output.root'],
        sandbox=sandbox
    )

    workflows.append(ttH)
    print "added workflow ",label

config = Config(
    workdir='/tmpscratch/users/$USER/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(
        bad_exit_codes=[127, 160],
        log_level=1
    )
)
