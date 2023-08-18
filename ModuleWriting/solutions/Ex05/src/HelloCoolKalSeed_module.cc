//
//  The HelloCoolKalSeed module
//
//  Original author Andy Edmonds
//

#include "Offline/RecoDataProducts/inc/KalSeed.hh"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "TH1F.h"

namespace mu2e {

  class HelloCoolKalSeed : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> kalSeedsTag{Name("kalSeedsTag"), Comment("KalSeedsTag")};
      fhicl::Atom<float>         tcut       {Name("tcut"),        Comment("Time Cut [ns]")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloCoolKalSeed(const Parameters& conf);

    void produce(art::Event& event);

  private:

    art::ProductToken<KalSeedCollection> const _kalSeedsToken;
    float _tcut;

  };

  HelloCoolKalSeed::HelloCoolKalSeed(const Parameters& conf)
    : art::EDProducer(conf),
      _kalSeedsToken{consumes<KalSeedCollection>(conf().kalSeedsTag() )},
      _tcut(conf().tcut()){
    produces<KalSeedCollection>();
  }

  void HelloCoolKalSeed::produce(art::Event& event){

    std::unique_ptr<KalSeedCollection> outputKalSeeds(new KalSeedCollection());

    const auto& kalSeeds = event.getProduct( _kalSeedsToken );\
    for ( const auto& kSeed : kalSeeds ) {
      if ( kSeed.t0().t0() > _tcut) {
	outputKalSeeds->push_back(kSeed);
      }
    }

    event.put(std::move(outputKalSeeds));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloCoolKalSeed)
