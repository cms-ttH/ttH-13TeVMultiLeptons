void HistMaker::proof_of_concept()
{
    // everything is already set up. You're in the event loop.
    int asdf = 0;
    for (const auto & ele : *raw_electrons_intree)
    {
        th1d["test"]->Fill(ele.obj.Pt());
        //if (asdf%1000==0) cout << ele.obj.Pt() << endl;
        asdf++;
    }
    
}
