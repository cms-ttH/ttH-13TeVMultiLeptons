class MakeGoodPlot
{
    public:
    
        int numsamples = 1;
        int numtotalhists = 0;
        std::vector<int> samples;
        vector<TFile*> files;
        TString sample_names[20];
        TString sample_names_reg[20];
        string sample_names_std[20];
        Color_t color[20];
        double numgen[20];		

        // CMS info stuff
        std::string cmsinfo;
        TLatex *CMSInfoLatex;
        TPaveText *pt[50];
        TPaveText *pt0;
        TPaveText *pt1; 
        double lumi = 90000.; // fb^-1
        //double scale[20];
        
        std::vector<TObjArray> hist;
        TObjArray canvas;
        
        double xsec[20];
        double q2up[20];
        double q2down[20];
        double pdfup[20];
        double pdfdown[20]; 
        
        void get_rate_info();        
        void setup();        
        void lepeff_plots();
        void jetcleaning_plots();
        void standard_plots();

        MakeGoodPlot(std::vector<int> thesamps);
        MakeGoodPlot(std::vector<int> thesamps, std::vector<TObjArray> exthists);
        
        void drawAll();
        void drawAllToScreen() { drawAll(); }
        void drawAllToFile(string plotfile, string plotoption="pdf");
        void drawAllToWebArea(string plotfile, string plotoption="pdf");
    
};


MakeGoodPlot::MakeGoodPlot(std::vector<int> thesamps)
{    
    numsamples = thesamps.size();
    samples = thesamps;
    
    cout << "hey1" << endl;
    
    for (int i=0; i<numsamples; i++)
    {
        // load the saved hists from file(s):
        
        files.push_back( new TFile("temp_"+int2ss(samples[i])+".root") ); 
        TIter next(files[i]->GetListOfKeys());
        TKey *key;
        TObjArray dummyArray;
        
        while ((key=(TKey*)next()))
        {
            //printf("key: %s points to an object of class: %s",
            //key->GetName(),
            //key->GetClassName());
            dummyArray.Add(files[i]->Get(key->GetName()));
        }
        
        numtotalhists = dummyArray.GetEntriesFast();
        hist.push_back(dummyArray);
    }
    
    
    cout << "hey2" << endl; 
       
    //auto thing = hist[0].FindObject("lepMVA sig1 endcap"); // will be a pointer
    //thing->Draw();
    
    setup();    
}

MakeGoodPlot::MakeGoodPlot(std::vector<int> thesamps, std::vector<TObjArray> exthists)
{
    numsamples = thesamps.size();
    samples = thesamps;    
    
    // pass the hists directly to MakeGoodPlot without saving:    
    hist = exthists;
    
    //auto thing = hist[0].FindObject("lepMVA sig1 endcap"); // will be a pointer
    //thing->Draw();
    
    setup();
}
