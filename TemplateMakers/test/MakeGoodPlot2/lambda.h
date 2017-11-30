#include "PlotHelper.h"


auto workItem = [](TTreeReader & reader) // load the TChain outside of this
{
    //TTreeReaderValue<Float_t> randomRV(reader, "r");
      
    //instantiate class here!
    PlotHelper *plothelper = new PlotHelper();   
    plothelper->setBranchAddresses(reader);

//           inside book histos
//       auto anarray = new TObjArray(); <-- make this (public) array part of the class!!!
//       anarray->Add(partialHisto);
//       anarray->Add(partialHisto2);
//       return partialHisto;

    plothelper->bookHistos();
    plothelper->run(); // contains the while loop
      
    // book histos
    //auto partialHisto = new TH1F("outHistoMP", "Random Numbers", 128, -4, 4);
    //auto partialHisto2 = new TH1F("outHistoMP2", "Random Numbers2", 256, -4, 4);

    
//       run
//       while (reader.Next()) {
//          partialHisto->Fill(*randomRV);
//          partialHisto2->Fill(*randomRV);
//       }
           

      return plothelper->objArray;
      // done son

};
