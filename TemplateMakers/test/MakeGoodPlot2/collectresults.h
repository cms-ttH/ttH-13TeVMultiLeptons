void HistMaker::collectResults()
{
    cout << "Collecting results..." << endl;
    
    objArray = new TObjArray();
    
    int th1eftblah = 0;
    int th1dblah = 0;
    
    for (const std::pair<string,TH1EFT*> & it : th1eft)
    {    
        if (it.first.substr(0,4)=="blah") 
        {
            th1eftblah++;
            continue;
        }
        
        objArray->Add(it.second);
    }
    for (auto it : th1d)
    {        
        //cout << it.second->GetName() << endl;
                
        //if (it.second->GetName()=="2los_mumu_2b") 
        //{
            //cout << "found it.." << endl;
            //cout << it.second->GetEntries() << endl;
        //}
        
        if (it.first.substr(0,4)=="blah") 
        {
            th1dblah++;
            continue;
        }
        
        objArray->Add(it.second);
    }
    for (auto it : th2d)
    {        
        
        if (it.first.substr(0,4)=="blah") 
        {
            continue;
        }
        
        objArray->Add(it.second);
    }    
    
    cout << "th1eftblah: " << th1eftblah << endl;
    cout << "th1dblah: " << th1dblah << endl;

}
