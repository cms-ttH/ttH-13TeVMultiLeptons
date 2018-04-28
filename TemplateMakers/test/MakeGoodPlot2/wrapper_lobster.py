#### For use with config_lobster.py ####

import subprocess
import sys

thisamp = sys.argv[1]
infiles = sys.argv[2:]
#print thisamp
#print infiles

with open('files.txt', 'w') as fd:
    for fn in infiles:
        fd.write('{}\n'.format(fn))

subprocess.check_call(["root", "-b", "-l", "-q", "wrapper_lobster.C+(\""+thisamp+"\", \"files.txt\")"])
#subprocess.check_call(["root", "-b", "-l", "-q", "makeEFTSelectionTree.C+(\"output.root\", \"files.txt\")"])