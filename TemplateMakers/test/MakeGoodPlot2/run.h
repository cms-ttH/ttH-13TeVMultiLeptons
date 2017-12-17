// You should never need to touch this.
void HistMaker::run(TTreeReader & newreader)
{
    //cout << "Starting event loop..." << endl;
    while (newreader.Next()) doOneEvent();
}
