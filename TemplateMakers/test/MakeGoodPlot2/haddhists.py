from config_lobster import mysamples
import subprocess
import sys

# directory containing lobster-produced hists to be hadded:
#histdir = "/hadoop/store/user/gesmith/lobster_test_20190110_1303/"
#outdir = "/tmpscratch/users/gsmith15/hhadded_hists/standardhists_SRs_othogbtags_group1_19_1_11/"
####outdir = "/tmpscratch/users/gsmith15/hhadded_hists/mcvalidation_multidim_18_7_18/"

#print sys.argv[1]
#print sys.argv[2]

histdir = sys.argv[1]
outdir = sys.argv[2]

### print statements from config_lobster.py can be ignored:
print " "
print "Ignore the stuff that was just printed above (it's because you imported"
print "the lobster config to get the list of samples; it's not actually starting"
print "a new lobster process)."
print " "
print "hadding samples from directory: ",histdir

subprocess.Popen("mkdir -p "+outdir,shell=True).communicate()

for samp in mysamples:
    thesefiles = histdir+samp+"/output_*.root"
    if (samp=='tllq_multidim' or samp=='tHq_multidim' or samp=='ttH_multidim' or samp=='ttll_multidim' or samp=='ttlnu_multidim'):
        commandstr = "hadd -f -k -j 8 -d /tmp/gsmith15/ "+outdir+"temp_"+samp+".root "+thesefiles
        subprocess.Popen(commandstr,shell=True).communicate()
    elif (samp=='DoubleEG' or samp=='DoubleMuon' or samp=='MuonEG' or samp=='SingleElectron' or samp=='SingleMuon'):
        commandstr = "hadd -f -k "+outdir+"temp_"+samp+".root "+thesefiles
        subprocess.Popen(commandstr,shell=True).communicate() #
        commandstr = "hadd -a -k "+outdir+"temp_data.root "+outdir+"temp_"+samp+".root"
        subprocess.Popen(commandstr,shell=True).communicate() #
        samp2=samp+"_QFs"
        thesefiles = histdir+samp2+"/output_*.root"
        commandstr = "hadd -a -k "+outdir+"temp_QFs.root "+thesefiles
        subprocess.Popen(commandstr,shell=True).communicate()        
        samp2=samp+"_Fakes"
        thesefiles = histdir+samp2+"/output_*.root"
        commandstr = "hadd -a -k "+outdir+"temp_Fakes.root "+thesefiles
        subprocess.Popen(commandstr,shell=True).communicate()
    else:
        commandstr = "hadd -f -k "+outdir+"temp_"+samp+".root "+thesefiles
        subprocess.Popen(commandstr,shell=True).communicate()
        
    if (samp=='ttlq_multidim'):
        commandstr = "mv "+outdir+"temp_"+samp+".root "+outdir+"temp_tllq_multidim.root"
        subprocess.Popen(commandstr,shell=True).communicate()
