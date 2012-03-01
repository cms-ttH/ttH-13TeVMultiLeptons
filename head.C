{
gROOT->Reset();

gSystem->Load("libFWCoreFWLite.so");
AutoLibraryLoader::enable();
gSystem->Load("libDataFormatsFWLite.so");

gROOT->SetStyle("Plain");
gROOT->ForceStyle();

gStyle->SetPalette(1);
}
