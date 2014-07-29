import os

def main ():

    #print "About to enter loop"
	#find batch_trees/*/*ttV_lepCuts_v1*.root -size -2k -print
    for errFile in os.popen("find batch_trees/condor_logs/*ttV_lepCuts_v1*.stderr -size +0k -print"):
        #print 'Inside loop, file ' + errFile
        sampleNameLine = open(errFile.split('.',1)[0] + '.stdout').read().splitlines()[2]
        sampleName = sampleNameLine.split('sample name =  ',1)[1]
        #if 'lowmll' in sampleName:
            #continue
        #print sampleName
        fileNameLine = open(errFile.split('.',1)[0] + '.stdout').read().splitlines()[3]
        fileName = fileNameLine.split('file:',1)[1]
        #print fileName
        jobNumber_1 = errFile.split('ttV_lepCuts_v1_',1)[1]
        jobNumber = jobNumber_1.split('.std',1)[0]
        #print jobNumber

        rm_command = "rm %s.std*" % ( errFile.split('.',1)[0] )
        print rm_command
        if "ttV_lepCuts_v1" in errFile:
            command = "lepMVAStudies ssCondor.py %s ttV_lepCuts_v1 %s 1 %s !>& lepMVAStudies_%s_%s.log &" % ( sampleName, jobNumber, fileName, sampleName, jobNumber )
            print command
        if "ttV_lepCuts_v1" in errFile:
            command = "ttV ssCondor.py %s ttV_lepCuts_v1 %s 1 %s !>& lepMVAStudies_%s_%s.log &" % ( sampleName, jobNumber, fileName, sampleName, jobNumber )
            print command
        

if __name__ == '__main__':
        main()
        

# def main ():

#     #print "About to enter loop"
#     for errFile in os.popen("find ~awoodard/multileptons/TemplateMakers/test/batch_trees/condor_logs/*ttV_lepCuts_v1*.stderr -size +0k -print"):
#         #print 'Inside loop, file ' + errFile
#         sampleNameLine = open(errFile.rpartition('.')[0] + '.stdout').read().splitlines()[2]
#         sampleName = sampleNameLine.split('sample name =  ',1)[1]
#         #print sampleName
#         fileNameLine = open(errFile.rpartition('.')[0] + '.stdout').read().splitlines()[3]
#         fileName = fileNameLine.split('file:',1)[1]
#         #print fileName
#         jobNumber_1 = errFile.split('ttV_lepCuts_v1_',1)[1]
#         jobNumber = jobNumber_1.split('.std',1)[0]
#         #print jobNumber

#         rm_command = "rm %s.std*" % ( errFile.rpartition('.')[0] )
#         print rm_command
#         if "ttV_lepCuts_v1" in errFile:
#             command = "lepMVAStudies ssCondor.py %s ttV_lepCuts_v1 %s 1 %s !>& lepMVAStudies_%s_%s.log &" % ( sampleName, jobNumber, fileName, sampleName, jobNumber )
#             print command
#         if "ttV_lepCuts_v1" in errFile:
#             command = "ttV ssCondor.py %s ttV_lepCuts_v1 %s 1 %s !>& lepMVAStudies_%s_%s.log &" % ( sampleName, jobNumber, fileName, sampleName, jobNumber )
#             print command
        

# if __name__ == '__main__':
#         main()
