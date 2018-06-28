// You should never need to touch this.
void HistMaker::run(TTreeReader & newreader)
{
    cout << "Starting event loop..." << endl;
    int count = 0;
    while (newreader.Next())
    {
        doOneEvent();
        //count++;
        //if (count>50000) break;
    }
}
