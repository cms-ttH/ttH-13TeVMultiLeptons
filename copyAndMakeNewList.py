#!/usr/bin/env python

import os
import sys
from optparse import OptionParser

def main ():



    for iFile in os.popen("ls -1 *.list").readlines():
        iFileClean = iFile.strip()
        print "Trying to open list file named ", iFileClean
        inputList = open(iFileClean)
        outputList = open("../listsForSkims2012_53x_v1_hadoop/%s"%iFileClean, "w")
        for iLine in inputList:
            iLineClean = iLine.strip().replace("file:", "")
            destination = iLineClean.replace("/store/user/abrinke1/", "/hadoop/users/jslaunwh/2012_53x_Skims/")

            #Parse out the directory names that you might want to create
            targetDir = os.path.dirname(destination)
            print "The directory to create is ", targetDir

            # try to make the dir if it isn't there
            if not os.path.exists(targetDir):
                os.popen("mkdir -p %s "% targetDir ).readlines()

            # if it isn't there now, you are in trouble
            if not os.path.exists(targetDir):
                print "Couldn't make dir ", targetDir, ", ...quitting"
                exit(4)
            
            print "Line in list is ", iLineClean
            
            print "New destination file is ", destination

            if not os.path.isfile(destination):
                os.popen('cp -v %s %s' % (iLineClean, destination)).readlines()
            else :
                print "Skipping file ", destination, "because it is already there" 
            
            newFileExists = os.path.isfile(destination)
            if not newFileExists:
                print "First try to copy failed :("
                print "Trying again"
                os.popen('cp -v %s %s' % (iLineClean, destination)).readlines()
                newFileExists = os.path.isfile(destination)
                if not newFileExists:
                    print "Couldn't copy to ", destination, " ... exiting"
                    exit(3)
                # end if not
            # end if not            
            outputList.write("file:%s\n" % destination)
        # end for each file in list
        outputList.close()
        inputList.close()



# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()
