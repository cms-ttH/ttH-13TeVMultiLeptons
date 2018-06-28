void HistMaker::collectResults()
{
    cout << "Collecting results..." << endl;
    
    objArray = new TObjArray();
    
    for (const std::pair<string,TH1EFT*> & it : th1eft)
    {    
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
        
        objArray->Add(it.second);
    }
    for (auto it : th2d)
    {        
        objArray->Add(it.second);
    }    

}
