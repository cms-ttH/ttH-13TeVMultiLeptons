from config_lobster import mysamples
import subprocess

# directory containing lobster-produced hists to be hadded:
histdir = "/hadoop/store/user/gesmith/lobster_test_20180427_0606/"

# print statements from config_lobster.py can be ignored:
print " "
print "Ignore the stuff that was just printed above (it's because you imported"
print "the lobster config to get the list of samples; it's not actually starting"
print "a new lobster process)."
print " "
print "hadding samples from directory: ",histdir


for samp in mysamples:
    thesefiles = histdir+samp+"/*.root"
    commandstr = "hadd -f temp_"+samp+".root "+thesefiles
    subprocess.Popen(commandstr,shell=True).communicate()
