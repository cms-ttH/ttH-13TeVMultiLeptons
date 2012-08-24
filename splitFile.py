#! /usr/bin/env python

import optparse
import os, sys

if __name__ == "__main__":

    # Setup options parser
    parser = optparse.OptionParser(
            usage = "usage: %prog [options] file nParts outFilePattern"+
            "\nCall with --help for more info.",
            description = "Takes one file and splits it into nParts separate files.  The argument outFilePattern should contain exactly one %d to indicate where you want the file number placed.  Numbering starts at 1."
            )
    
    parser.add_option("-d","--debug", action="store", type="int", dest="debug",
                      help="Set to >= 1 for debug output.", default=0)
    
    options, args = parser.parse_args()
    
    if len(args) != 3:
            parser.print_usage()
            sys.exit(2)

    #Step 0: Validate the command line input
    inFile = args[0]
    nParts = 0
    try :
        nParts = int(args[1])
    except ValueError:
        print "Entered invalid integer for nParts:",args[1]
        parser.print_usage()
        sys.exit(2)
    outFilePattern = args[2]

    if outFilePattern.count("%d") != 1:
        print "Invalid outFilePattern:",outFilePattern
        print 'Should contain only one "%d"'
        parser.print_usage()
        sys.exit(2)

    #Step 1: Read in the file list
    fileList = []
    with open(inFile, 'r') as f:
        fileList = f.readlines()

    print "Found file list with %d files" % len(fileList)
    print "Dividing the list into %d parts" % nParts

    for part in range(0,nParts):

        with open(outFilePattern % (part+1),'w') as f:
            f.writelines(fileList[part::nParts])
            print 'Wrote %d files to list %s' % (
                len(fileList[part::nParts]),outFilePattern % (part + 1)
                )

    print "\nDone."
