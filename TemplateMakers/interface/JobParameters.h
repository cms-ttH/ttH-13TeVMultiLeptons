
#ifndef _JobParameters_h
#define _JobParameters_h


// This is basically a struct to handle
// all of your job parameter parsing

class JobParameters {

public:
  
  JobParameters() :
    outputFileName("NONE"),
    sampleName("NONE"),
    maxEvents(-1),
    jetSyst("NA")
  {};


  vector<string> inputFileNames;
  string outputFileName;

  string sampleName;

  int maxEvents;

  string jetSyst;

  


};


#endif 
