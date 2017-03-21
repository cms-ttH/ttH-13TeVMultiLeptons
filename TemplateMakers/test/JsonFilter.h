#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>  

class JsonFilter
{
 private:
  std::map<int,vector<int>> dict_;  
  
  void read(void)
  {
    std::ifstream inputFile("../data/JSON/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_text.txt");
    std::string line;
    while(getline(inputFile, line)) {
      if (!line.length() || line[0] == '#')
	continue;
      
      char *linechar = new char[line.length() +1];
      std::strcpy(linechar,line.c_str());
      
      char * split;
      split = strtok(linechar,":,");
      
      vector<int> lumis;
      int key=0;
      int count = 0;
      while (split != NULL)
	{
	  if (count == 0) key = atoi(split);
	  else	    lumis.push_back(atoi(split));
	  split = strtok(NULL,":,");
	  count ++;
	}
      
      dict_[key] = lumis;
      //cout << key << " : " << lumis.size() << endl; 
      
    }
  }
  
 public:
  JsonFilter(){
    read();
  };//default constructor
  
  bool isValid(int run_num, int lumi)
  {
    auto json_lumis = dict_[run_num];
    for (unsigned int i=1;i<=json_lumis.size();i+=2)
      {
	int lower = json_lumis[i-1];
	int upper = json_lumis[i];

	if (lumi < lower) return false; //if below range
	else if (lumi <= upper) return true; // if in range
      }
    return false; 
  }
  
  virtual ~JsonFilter(){};
  
};
