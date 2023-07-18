//
//  ExploreStrawDigis module.  Examine features of StrawDigi
//

// C++ includes.
#include <iostream>

// Framework includes
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"
// Root includes
#include "TH1F.h"
// Mu2e Data Products
#include "Offline/RecoDataProducts/inc/StrawDigi.hh"
#include "Offline/RecoDataProducts/inc/ComboHit.hh"

namespace mu2e {

  class ExploreStrawDigis : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;
      fhicl::Atom<art::InputTag> SDCTag{Name("StrawDigis"), Comment("StrawDigiCollection"), art::InputTag()};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit ExploreStrawDigis(const Parameters& conf);

    void analyze(const art::Event& event);
    void beginJob( );

  private:
    Config _conf;
    TH1F *_nstrawdigi, *_tdc, *_adc, *_tot, *_deltatdc;

  };

  ExploreStrawDigis::ExploreStrawDigis(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()) {
    consumes<StrawDigiCollection>(_conf.SDCTag());
  }

  void ExploreStrawDigis::beginJob( ){
    art::ServiceHandle<art::TFileService> tfs;
      _nstrawdigi = tfs->make<TH1F>("NStrawDigis","N StrawDigis",250,0,5000);
      _tdc = tfs->make<TH1F>("tdc","StrawDigis TDC",100,0,100000); 
      _deltatdc = tfs->make<TH1F>("deltatdc","StrawDigis deltatdc",100,-100,1000);
      _tot = tfs->make<TH1F>("tot","StrawDigis TOT",100,0,100);
      _adc = tfs->make<TH1F>("adc","StrawDigis ADC",100,0,5000);

  }

  void ExploreStrawDigis::analyze(const art::Event& event){
  // find the StrawDigi collection in the event
    auto sdcH = event.getValidHandle<StrawDigiCollection>(_conf.SDCTag());
    auto const& sdc = *sdcH;
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

using mu2e::ExploreStrawDigis;
DEFINE_ART_MODULE(ExploreStrawDigis)
