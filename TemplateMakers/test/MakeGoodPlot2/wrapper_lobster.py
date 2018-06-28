#### For use with config_lobster.py ####

import subprocess
import sys

thisamp = sys.argv[1]
#infiles = sys.argv[2:]
thing   = sys.argv[2]
infiles = sys.argv[3:]

print thisamp
print thing
print infiles


with open('files.txt', 'w') as fd:
    for fn in infiles:
        fd.write('{}\n'.format(fn))

#subprocess.check_call(["root", "-b", "-l", "-q", "wrapper_lobster.C+(\""+thisamp+"\", \"files.txt\")"])

if (thing=='nom'):
    print "nom"
    subprocess.check_call(["root", "-b", "-l", "-q", "wrapper_lobster.C+(\""+thisamp+"\", \"files.txt\")"])

else:
    print "not nom!"
    #if (thisamp=='DoubleEG' or thisamp=='DoubleMuon' or thisamp=='MuonEG' or thisamp=='SingleElectron' or thisamp=='SingleMuon'):
    if (thing=='_QFs'):
        print "QFs"
        subprocess.check_call(["root", "-b", "-l", "-q", "wrapper_lobster.C+(\""+thisamp+"\", \"files.txt\", true, false)"])
    elif (thing=='_Fakes'):
        print "Fakes"
        subprocess.check_call(["root", "-b", "-l", "-q", "wrapper_lobster.C+(\""+thisamp+"\", \"files.txt\", false, true)"])
