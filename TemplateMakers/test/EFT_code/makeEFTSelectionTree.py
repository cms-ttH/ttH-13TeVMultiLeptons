import subprocess
import sys

infiles = sys.argv[1:]
s = ",".join('"{}"'.format(fn) for fn in infiles)

subprocess.check_call(["root", "-b", "-l", "-q", "makeEFTSelectionTree.C+(\"output.root\", {{{}}})".format(s)])
