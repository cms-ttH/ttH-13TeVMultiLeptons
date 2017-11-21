void PlotHelper::collectResults()
{
    cout << "Collecting results..." << endl;
    
    objArray = new TObjArray();
    
    for (auto it : th1d)
    {        
        objArray->Add(it.second);
    }
    for (auto it : th2d)
    {        
        objArray->Add(it.second);
    }    

}
