import subprocess
import sys

infiles = sys.argv[1:]

with open('files.txt', 'w') as fd:
    for fn in infiles:
        fd.write('{}\n'.format(fn))

subprocess.check_call(["root", "-b", "-l", "-q", "makeEFTSelectionTree.C+(\"output.root\", \"files.txt\")"])
