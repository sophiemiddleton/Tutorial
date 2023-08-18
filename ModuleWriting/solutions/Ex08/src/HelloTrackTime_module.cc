//
//  The HelloTrackTime module
//
//  Original author Andy Edmonds
//

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include <iostream>

namespace mu2e {

  class HelloTrackTime : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> kalSeedsTag{Name("kalSeedsTag"), Comment("art::InputTag for a KalSeedsCollection")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloTrackTime(const Parameters& conf);

    void produce(art::Event& event) override;

  private:

    art::ProductToken<KalSeedCollection> const _kalSeedsToken;
  };

  HelloTrackTime::HelloTrackTime(const Parameters& conf)
    : art::EDProducer(conf),
      _kalSeedsToken{consumes<KalSeedCollection>(conf().kalSeedsTag() )}{
    produces<TrackTimeCollection>();
  }

  void HelloTrackTime::produce(art::Event& event){

    auto outputTrackTimes = std::make_unique<TrackTimeCollection>( TrackTimeCollection() );

    const auto& kalSeeds = event.getProduct( _kalSeedsToken );

    outputTrackTimes->reserve( kalSeeds.size() );
    for (const auto& kalSeed : kalSeeds) {
      outputTrackTimes->emplace_back(kalSeed);
    }

    if (kalSeeds.size() != outputTrackTimes->size()) {
      throw cet::exception("Tutorial")
        << "Input KalSeedCollection and output TrackTimeCollection are different sizes ("
        << kalSeeds.size() << " and "
        << outputTrackTimes->size() << " respectively)";
    }

    event.put(std::move(outputTrackTimes));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloTrackTime)
