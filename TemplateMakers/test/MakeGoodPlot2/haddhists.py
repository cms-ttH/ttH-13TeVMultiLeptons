from config_lobster import mysamples
import subprocess

# directory containing lobster-produced hists to be hadded:
histdir = "/hadoop/store/user/gesmith/lobster_test_20180628_0908/"
outdir = "/tmpscratch/users/gsmith15/hhadded_hists/standardhists_2lss2or3JetsGeq1Btags_1l3orMoreJets1orMoreBtag_noReqOnPSleps_geqFakeableSel_FRbugfix2__withPUSF_DeepCSVSFsAllJets_MuSFs_partialEleSFs2_1pslepskimallsamps_lowerpts_18_6_28b/"


# print statements from config_lobster.py can be ignored:
print " "
print "Ignore the stuff that was just printed above (it's because you imported"
print "the lobster config to get the list of samples; it's not actually starting"
print "a new lobster process)."
print " "
print "hadding samples from directory: ",histdir

subprocess.Popen("mkdir -p "+outdir,shell=True).communicate()

for samp in mysamples:
    thesefiles = histdir+samp+"/output_*.root"
    commandstr = "hadd -f -k "+outdir+"temp_"+samp+".root "+thesefiles
    subprocess.Popen(commandstr,shell=True).communicate()
    if (samp=='DoubleEG' or samp=='DoubleMuon' or samp=='MuonEG' or samp=='SingleElectron' or samp=='SingleMuon'):
        commandstr = "hadd -a -k "+outdir+"temp_data.root "+outdir+"temp_"+samp+".root"
        subprocess.Popen(commandstr,shell=True).communicate()
        samp2=samp+"_QFs"
        thesefiles = histdir+samp2+"/output_*.root"
        commandstr = "hadd -a -k "+outdir+"temp_QFs.root "+thesefiles
        subprocess.Popen(commandstr,shell=True).communicate()        
        samp2=samp+"_Fakes"
        thesefiles = histdir+samp2+"/output_*.root"
        commandstr = "hadd -a -k "+outdir+"temp_Fakes.root "+thesefiles
        subprocess.Popen(commandstr,shell=True).communicate()
