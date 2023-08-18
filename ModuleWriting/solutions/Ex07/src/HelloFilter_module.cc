a//
//  The HelloFilter module
//
//  Original author Andy Edmonds
//

#include "Offline/RecoDataProducts/inc/KalSeed.hh"

#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "TH1F.h"

#include <iostream>

namespace mu2e {

  class HelloFilter : public art::EDFilter {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> kalSeedsTag{Name("kalSeedsTag"), Comment("art::InputTag for a KalSeedsCollection")};
    };
    typedef art::EDFilter::Table<Config> Parameters;

    explicit HelloFilter(const Parameters& conf);

    bool filter(art::Event& event) override;

  private:

    art::ProductToken<KalSeedCollection> const _kalSeedsToken;

  };

  HelloFilter::HelloFilter(const Parameters& conf)
    : art::EDFilter(conf),
      _kalSeedsToken{consumes<KalSeedCollection>(conf().kalSeedsTag() )}{
  }

  bool HelloFilter::filter(art::Event& event){

    const auto& kalSeeds = event.getProduct( _kalSeedsToken );

    if (kalSeeds.size()>0) {
      return true;
    }
    else {
      return false;
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloFilter)
