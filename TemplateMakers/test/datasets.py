# first do: setenv PYTHONPATH ${PYTHONPATH}:/cvmfs/cms.cern.ch/crab/CRAB_2_11_1_patch1/external/dbs3client
# usage: python datasets.py > sampleLists.sh

import datetime
from dbs.apis.dbsClient import DbsApi
dbs = DbsApi('https://cmsweb.cern.ch/dbs/prod/global/DBSReader')

### discover datasets:
#thing = dbs.listDatasets(dataset = '/tt*H*ToNonbb*/*/MINIAODSIM')   
#thing = dbs.listDatasets(dataset = '/TTJets*/*/MINIAODSIM',detail=True)
#thing2 = dbs.listBlockSummaries_doc(dataset = '/TTJets*/*/MINIAODSIM',detail=True)
#thing = dbs.listDatasets(dataset = '/*T*T*Bar*/*/MINIAODSIM',detail=True)
#thing = dbs.listDatasets(dataset = '/TTZ*/*/MINIAODSIM',detail=True)
#thing = dbs.listDatasets(dataset = '/ST_s*/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV*/MINIAODSIM',detail=True)
#thing = dbs.listDatasets(dataset = '/WJetsToLNu*/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV*/MINIAODSIM',detail=True)
#thing = dbs.listDatasets(dataset = '/DYJetsToLL_M*/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV*/MINIAODSIM',detail=True)
thing = dbs.listDatasets(dataset = '/ZZ*/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV*/MINIAODSIM',detail=True)

for item in sorted(thing,key=lambda date: date['creation_date']): # last_modification_date
    #print item
    print datetime.datetime.fromtimestamp(int(item['creation_date'])).strftime('%Y-%m-%d %H:%M:%S'),item['dataset']



    
#### specify datasets ####

### format is ['some label you want to give','string of dataset in DAS']
#dataset_list = []
##dataset_list.append(['ttH125','/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
#dataset_list.append(['ttH125','/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
##dataset_list.append(['ttbar','.....'])
##etc...
#
#
#
##### dump bash-formatted arrays: ####
#
##xrdpfx='root://cms-xrd-global.cern.ch/'
#xrdpfx=''
#
#for idataset in dataset_list:
#    #print idataset
#    filelist = [xrdpfx+blah['logical_file_name'] for blah in dbs.listFiles( dataset=idataset[1] )]
#    print 'declare -a '+idataset[0]+'=( \\'
#    for i_file in filelist:
#        print i_file+' \\'
#    print ')'
#    print ' '
