// Created by Andrew Wightman

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/EFTLHEReader.h"

EFTLHEReader::EFTLHEReader(const edm::ParameterSet& constructparams)
{
    entire_pset = constructparams;
    parse_params(); // Currently doesn't do anything
    lheInfo_token_ = consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer"));
}

EFTLHEReader::~EFTLHEReader(){}

void EFTLHEReader::beginJob()
{
    edm::Service<TFileService> newfs;
    summaryTree = newfs->make<TTree>("summaryTree","Summary Event Values");
    tree_add_branches();
}

void EFTLHEReader::endJob(){}

void EFTLHEReader::analyze(const edm::Event& event, const edm::EventSetup& evsetup)
{
    eventcount++;

    // set tree vars to default values
    initialize_variables();

    edm::Handle<LHEEventProduct> LHEInfo;
    event.getByToken(lheInfo_token_,LHEInfo);

    originalXWGTUP_intree = LHEInfo->originalXWGTUP();  // original cross-section

    // Add EFT weights
    for (auto wgt_info: LHEInfo->weights())
    {
        auto LHEwgtstr = std::string(wgt_info.id);
        std::size_t foundstr = LHEwgtstr.find("EFTrwgt"); // only save our EFT weights
        if (foundstr!=std::string::npos) {
            eftwgts_intree[wgt_info.id] = wgt_info.wgt;
        }
    }

    eventnum_intree = event.id().event();
    lumiBlock_intree = event.id().luminosityBlock();
    runNumber_intree = event.id().run();

    summaryTree->Fill();
}

void EFTLHEReader::beginRun(edm::Run const& run, edm::EventSetup const& evsetup)
{
    eventcount = 0;
}

void EFTLHEReader::endRun(edm::Run const& run, edm::EventSetup const& evsetup)
{
    std::cout << "total events processed: " << eventcount << std::endl;
}

void EFTLHEReader::beginLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){}
void EFTLHEReader::endLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){}

DEFINE_FWK_MODULE(EFTLHEReader);