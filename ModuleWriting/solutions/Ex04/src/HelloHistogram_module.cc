//
//  The HelloHistogram module
//
//  Original author Andy Edmonds
//

#include "Offline/RecoDataProducts/inc/KalSeed.hh"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"

#include "TH1F.h"

#include <iostream>

namespace mu2e {

  class HelloHistogram : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> kalSeedsTag{Name("kalSeedsTag"), Comment("KalSeedsTag")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HelloHistogram(const Parameters& conf);

    void beginJob();
    void analyze(const art::Event& event);

  private:
    art::ProductToken<KalSeedCollection> const _kalSeedsToken;

    TH1F* _hTrackTimes;
  };

  HelloHistogram::HelloHistogram(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _kalSeedsToken{consumes<KalSeedCollection>(conf().kalSeedsTag() )}{
  }

  void HelloHistogram::beginJob() {
    art::ServiceHandle<art::TFileService> tfs;
    constexpr double min_t0   =    0.;
    constexpr double max_t0   = 1700.;
    constexpr double t0_width =   10.;
    constexpr int n_t0_bins = (max_t0 - min_t0) / t0_width;
    _hTrackTimes = tfs->make<TH1F>("hTrackTimes","Track t0;(ns)", n_t0_bins,min_t0,max_t0);
  }

  void HelloHistogram::analyze(const art::Event& event){

    const auto& kalSeeds = event.getProduct( _kalSeedsToken );

    for (const auto& kSeed : kalSeeds ) {
      _hTrackTimes->Fill( kSeed.t0().t0() );
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloHistogram)
