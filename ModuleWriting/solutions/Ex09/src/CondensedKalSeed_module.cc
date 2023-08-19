//
//  The CondensedKalSeed module
//
//  Original author Andy Edmonds
//

#include "Offline/RecoDataProducts/inc/KalSeed.hh"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "TH1F.h"

#include <iostream>

namespace mu2e {

  class CondensedKalSeed : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> kalSeedsTag{Name("kalSeedsTag"), Comment("art::InputTag for a KalSeedsCollection")};
      fhicl::Atom<float> pcut{Name("pcut"), Comment("Momentum cut [MeV/c]")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit CondensedKalSeed(const Parameters& conf);

    void produce(art::Event& event) override;

  private:

    art::ProductToken<KalSeedCollection> const _kalSeedsToken;
    float _pcut;
  };

  CondensedKalSeed::CondensedKalSeed(const Parameters& conf)
    : art::EDProducer(conf),
      _kalSeedsToken{consumes<KalSeedCollection>(conf().kalSeedsTag() )},
      _pcut(conf().pcut()){
    produces<KalSeedCollection>();
  }

  void CondensedKalSeed::produce(art::Event& event){

    auto outputKalSeeds = std::make_unique<KalSeedCollection>( KalSeedCollection() );

    const auto& kalSeeds = event.getProduct( _kalSeedsToken );
    for (const auto& kalSeed : kalSeeds ) {

      if ( kalSeed.segments().begin()->mom() > _pcut) {
	outputKalSeeds->push_back(kalSeed);
      }
    }

    event.put(std::move(outputKalSeeds));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::CondensedKalSeed)
