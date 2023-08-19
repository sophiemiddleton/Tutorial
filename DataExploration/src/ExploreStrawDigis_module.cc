//
//  ExploreStrawDigis module.  Examine features of StrawDigi
//

#include "Offline/RecoDataProducts/inc/StrawDigi.hh"
#include "Offline/RecoDataProducts/inc/ComboHit.hh"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"

#include "TH1F.h"

#include <iostream>

namespace mu2e {

  class ExploreStrawDigis : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;
      fhicl::Atom<art::InputTag> SDCTag{Name("StrawDigisTag"), Comment("Input tag for a StrawDigiCollection")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit ExploreStrawDigis(const Parameters& conf);

    void beginJob( ) override;
    void analyze(const art::Event& event) override;

  private:
    art::ProductToken<StrawDigiCollection> const _strawDigisToken;

    TH1F* _nstrawdigi = nullptr;
    TH1F* _tdc        = nullptr;
    TH1F* _adc        = nullptr;
    TH1F* _tot        = nullptr;
    TH1F* _deltatdc   = nullptr;

  };

  ExploreStrawDigis::ExploreStrawDigis(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _strawDigisToken{consumes<StrawDigiCollection>(conf().SDCTag())}
  {
  }

  void ExploreStrawDigis::beginJob( ){
    art::ServiceHandle<art::TFileService> tfs;
    _nstrawdigi = tfs->make<TH1F>("NStrawDigis", "N StrawDigis",        250,    0.,  5000.);
    _tdc        = tfs->make<TH1F>("tdc",         "StrawDigis TDC",      100,    0.,100000.);
    _deltatdc   = tfs->make<TH1F>("deltatdc",    "StrawDigis deltatdc", 100, -100.,  1000.);
    _tot        = tfs->make<TH1F>("tot",         "StrawDigis TOT",      100,    0.,   100.);
    _adc        = tfs->make<TH1F>("adc",         "StrawDigis ADC",      100,    0.,  5000.);
  }

  void ExploreStrawDigis::analyze(const art::Event& event){

    // Get the requestedd StrawDigiCollection
    auto const& sdc = event.getProduct( _strawDigisToken );

    _nstrawdigi->Fill(sdc.size());

    // loop over strawdigis
    for(auto const& sd : sdc) {
      _tdc->Fill(sd.TDC(StrawEnd::cal));
      _deltatdc->Fill(sd.TDC(StrawEnd::cal)-sd.TDC(StrawEnd::hv));
      _tot->Fill(sd.TOT(StrawEnd::cal));
      _adc->Fill(sd.PMP());
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::ExploreStrawDigis)
