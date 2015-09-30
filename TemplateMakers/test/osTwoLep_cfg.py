import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("Demo")


process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff" )
process.GlobalTag.globaltag = '74X_mcRun2_asymptotic_v2' #MCRUN2_74_V9 #'PHYS14_25_V2' #'PLS170_V7AN1::All'  #'MCRUN2_72_V3A' #'MC_72_v1' ##'PHYS14_25_V1' ###'PLS170_V7AN1::All'  ###'PLS170_V7AN1::All' ##'START61_V11::All' #START61_V8::All #'GR_R_60_V7::All'   # 'GR_R_52_V9::All'
process.prefer("GlobalTag")

#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag as customiseGlobalTag 
#process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'MCRUN2_72_V1A::All') ## maybe try MCRUN2_72_V1? "optimisitic" conditions.
#process.GlobalTag.connect = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'

# PU 40:
#miniaodfiledirPU40 = str("root://xrootd.ba.infn.it//store/mc/Phys14DR/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU40bx25_PHYS14_25_V1-v1/00000/")
# PU 20:
#miniaodfiledirPU20 = str("root://xrootd.ba.infn.it//store/mc/Phys14DR/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v2/")


process.maxEvents = cms.untracked.PSet(
    	input = cms.untracked.int32(-1) # number of events
)

process.source = cms.Source("PoolSource",
    	fileNames = cms.untracked.vstring(
        
        #'/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/04A14FA4-2523-E511-9860-0025905C96A6.root'
        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/088378DB-3D24-E511-8B0E-20CF3027A589.root'
        #'/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/06249DB6-C309-E511-957A-782BCB6A4BB8.root'
        
        
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/06249DB6-C309-E511-957A-782BCB6A4BB8.root', 
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/0E83823D-C408-E511-B52C-001E67A401B3.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/580DE3FC-CA08-E511-B78E-001517F7F510.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/6200A898-F908-E511-B819-842B2B2B0EC5.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/6274B8AF-E909-E511-A805-002590D9D9DA.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/64E2F68A-9C09-E511-A692-90B11C04FE38.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/764E7F91-E909-E511-B98B-782BCB6A52FE.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/7CDB238E-D309-E511-9820-002590D9D8BE.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/94EE41C0-C708-E511-A646-90B11C067ADE.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/A0BD7EDA-C208-E511-B337-0026182FD740.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/ACBE5E42-BE08-E511-8D9D-001E67A3EA89.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/C2C9A27E-CC08-E511-B906-000F53273724.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/C4FA3F9A-E909-E511-939B-0026181D28BB.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/D26A661C-EB09-E511-95EB-984BE1089EB8.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/D4DC2D88-D608-E511-AFCD-001E67397BC5.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/D645A0F8-A009-E511-A2F1-001E6739726F.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/10000/DC8DDCDD-D208-E511-A982-0026181D2933.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/14C295E9-8209-E511-A5B8-001E67398110.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/246D7054-0F09-E511-9573-002590A887F2.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/266D803C-8309-E511-9A34-000F53273750.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/2EC6789A-1709-E511-971C-002590A36FA2.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/304D3306-0909-E511-9837-0025B3E063F0.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/463C4141-8309-E511-B201-842B2B185C51.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/4C32E8AF-FE08-E511-A2A0-002590A83354.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/A6889F3B-8309-E511-9423-000F530E4644.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/EAF04ACB-0A09-E511-BAFB-001E673968BA.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/50000/FE06E5A9-F408-E511-B900-001E67396897.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/047A90E2-3709-E511-98DC-B083FED76520.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/04E02FB8-B208-E511-BE55-AC853D9DAC27.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/08E6BFB0-6009-E511-A07C-782BCB6E0AD0.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/0E28DCCE-6009-E511-9796-782BCB282B5F.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/0EA3C12F-0409-E511-880F-782BCB283ED2.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/2CF212FF-CB08-E511-BFF8-000F532734A4.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/2CFC242D-E108-E511-B1F5-782BCB6E134C.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/306B46DD-450A-E511-A4CC-00074305CEAD.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/30E1E395-B208-E511-A0CB-842B2B18193D.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/3A81860B-4F09-E511-9C3F-002590200AC4.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/3C92EBB4-450A-E511-BAD9-002590200B44.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/3E06BC0A-BF08-E511-96D4-AC853D9DAD0D.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/3EB464D7-BE08-E511-9175-B083FED76C6C.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/5476F7CD-B208-E511-B3DB-000F532734B4.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/649CC191-B208-E511-9B1B-B083FED734F5.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/6C9E6226-0409-E511-AD54-000F532734AC.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/743707DF-450A-E511-A912-842B2B29C638.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/74A46396-B208-E511-9E6C-000F530E46DC.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/8005B405-3509-E511-B7E7-0026B95CE867.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/80290F34-AA09-E511-A780-782BCB7797E2.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/84D1281A-0409-E511-9321-782BCB27C84E.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/8887028E-6009-E511-B136-000F53273734.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/8C3546B7-5509-E511-9ED6-B083FED7593B.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/90BB8BBA-5509-E511-902F-782BCB282C03.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/981616B9-450A-E511-A7A2-B083FED76C6C.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/A254BABE-170A-E511-8AE0-002590200AF4.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/A6D07693-B208-E511-A7AD-AC853D9DACE1.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/B01E8E03-3C09-E511-8B64-842B2B2B0D2E.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/B4218604-BF08-E511-86C4-000F530E4784.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/B6A7C9A4-1F0A-E511-B453-782BCB6E0F56.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/B82CCBB2-B208-E511-AE6C-782BCB27C84E.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/BA7F23B8-7209-E511-8605-001E67398052.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/C0855DDF-450A-E511-9B9D-002590D9D9E4.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/C4CFDB01-3509-E511-9126-842B2B2925F5.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/CE17B402-BF08-E511-BEF3-B083FED76637.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/D8F5AFE5-0B09-E511-BF5E-842B2B29273C.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/E4EEA916-0409-E511-91F7-000F530E479C.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/F81B62A8-5509-E511-AEF1-B083FED76520.root',
#        '/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v3/70000/F88FB131-E108-E511-A69C-000F532734AC.root'
#                                                                                                                                                                                     
                                                                                                                                                                                     
                                                                                                                                                                                                                                                                                                                                                                   
                                                                                                                                                                                     
                                                                                                                                                                                     
        
        
        
        
        #'file:/afs/cern.ch/user/m/muell149/public/ttH_phys14_sync.root'

	# Phys14 ttH
	# PU 40:
	 # miniaodfiledirPU40 + '1034F24B-1A78-E411-9D64-001E67398C1E.root',
	 # miniaodfiledirPU40 + '6856B40F-0C77-E411-893D-D8D385FF7678.root',
	 # miniaodfiledirPU40 + 'A8D5A514-DD77-E411-95AB-002481E14D64.root',
	 # miniaodfiledirPU40 + 'C20B68E7-0277-E411-85E5-001E67396A22.root',
	 # miniaodfiledirPU40 + 'E601D324-FA76-E411-B2A3-0025B3E066A4.root',
	 # miniaodfiledirPU40 + 'EC51B40A-0F77-E411-AB65-002590A831AA.root',
	 # miniaodfiledirPU40 + 'ECF2804E-F476-E411-A097-001E67398110.root',

	# PU 20:
#	miniaodfiledirPU20 + '00000/08B36E8F-5E7F-E411-9D5A-002590200AE4.root',
#	miniaodfiledirPU20 + '00000/FC4E6E16-5C7F-E411-8843-002590200AE4.root',
#	miniaodfiledirPU20 + '10000/629CE4D5-687F-E411-BF71-001E673969FA.root',
#	miniaodfiledirPU20 + '20000/14587980-CB7E-E411-A0F4-001E67397701.root',
#	miniaodfiledirPU20 + '30000/9E314FC0-067F-E411-9500-001E67397B11.root',
#	miniaodfiledirPU20 + '40000/78722DCF-E57E-E411-B437-002590A4FFB8.root',
#	miniaodfiledirPU20 + '40000/F87FB415-E57E-E411-B7CF-002590A4FFB8.root',
	

	)
                            )

#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#    '199812:70-199812:80'
#)

######################################
#JEC

from RecoJets.Configuration.RecoJets_cff import *
from RecoJets.Configuration.RecoPFJets_cff import *
from JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff import *
from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *

process.ak4PFCHSL1Fastjet = cms.ESProducer(
    'L1FastjetCorrectionESProducer',
    level       = cms.string('L1FastJet'),
    algorithm   = cms.string('AK4PFchs'),
    srcRho      = cms.InputTag( 'fixedGridRhoFastjetAll' ),
    useCondDB = cms.untracked.bool(True)
    )

process.ak4PFchsL2Relative   =  ak5PFL2Relative.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL3Absolute   =  ak5PFL3Absolute.clone( algorithm = 'AK4PFchs' )

process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
     correctors = cms.vstring(
        'ak4PFCHSL1Fastjet', 
        'ak4PFchsL2Relative', 
        'ak4PFchsL3Absolute'),
     useCondDB = cms.untracked.bool(True)                                        
)
######################################

## Here, load the analysis:
process.load("ttH.LeptonID.ttHLeptons_cfi")
process.load("ttH-13TeVMultiLeptons.TemplateMakers.OSTwoLepAna_cfi")

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile)

process.OSTwoLepAna.electrons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.muons = cms.InputTag("ttHLeptons")

### new choices for btagging: ###
# combinedSecondaryVertexBJetTags
# pfJetBProbabilityBJetTags
# pfJetProbabilityBJetTags  
# pfTrackCountingHighPurBJetTags 
# pfTrackCountingHighEffBJetTags 
# pfSimpleSecondaryVertexHighEffBJetTags  
# pfSimpleSecondaryVertexHighPurBJetTags  
# pfCombinedSecondaryVertexV2BJetTags 
# pfCombinedInclusiveSecondaryVertexV2BJetTags 
# pfCombinedSecondaryVertexSoftLeptonBJetTags
# pfCombinedMVABJetTags

process.OSTwoLepAna.btags.btagdisc = "pfCombinedInclusiveSecondaryVertexV2BJetTags"  # "combinedInclusiveSecondaryVertexV2BJetTags" #"combinedMVABJetTags" ##"combinedSecondaryVertexMVABJetTags"
process.OSTwoLepAna.triggers.hltlabel = "HLT" #"reHLT" #"HLT" # HLT = centrally produced samples
process.OSTwoLepAna.triggers.trigger_vstring = ( "HLT_Mu17_Mu8_v1",
			"HLT_Mu30_TkMu11_v1", #"HLT_Mu17_TkMu8_v1",
			"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1",
			"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1",
			"HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1", #now is HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1
			"HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1",
			"HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1",
			"HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1",
			"HLT_Ele17_Ele12_Ele10_CaloId_TrackId_v1",
			#"HLT_Ele27_eta2p1_WP85_Gsf_v1" #not in 1.4 menu
			"HLT_Ele32_eta2p1_WP85_Gsf_v1" #single ele test
			#"HLT_IsoMu24_IterTrk02_v1" #single mu test
			)

### example of trivially changing muon isolation:
#looseMuonRelIso = 0.3
##looseMuonRelIso = sys.argv[2] #or take command line argument -> just run however many cmsRun jobs for isolation study!
#process.OSTwoLepAna.muons.looseRelativeIso = looseMuonRelIso

######################################
	
## uncomment this for use with crab script ###
process.TFileService = cms.Service("TFileService",
				   fileName = cms.string("multilep_tree.root")
                                   )


process.p = cms.Path(process.ttHLeptons * process.OSTwoLepAna)

# summary
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )

## comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
outfile = open('dumped_config.py','w')
print >> outfile,process.dumpPython()
outfile.close()
