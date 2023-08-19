//
//  The HelloTrackTimePtr module
//
//  Original author Andy Edmonds
//

#include "Tutorial/ModuleWriting/solutions/Ex09/inc/TrackTimePtr.hh"
#include "Offline/RecoDataProducts/inc/KalSeed.hh"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include <iostream>

namespace mu2e {

  class HelloTrackTimePtr : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> kalSeedsTag{Name("kalSeedsTag"), Comment("art::InputTag for a KalSeedsCollection")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloTrackTimePtr(const Parameters& conf);

    void produce(art::Event& event) override;

  private:

    art::ProductToken<KalSeedCollection> const _kalSeedsToken;
  };

  HelloTrackTimePtr::HelloTrackTimePtr(const Parameters& conf)
    : art::EDProducer(conf),
      _kalSeedsToken{consumes<KalSeedCollection>(conf().kalSeedsTag() )}{
    produces<TrackTimePtrCollection>();
  }

  void HelloTrackTimePtr::produce(art::Event& event){

    auto outputTrackTimePtrs = std::make_unique<TrackTimePtrCollection>(TrackTimePtrCollection());

    const auto& kalSeedsHandle = event.getValidHandle<KalSeedCollection>(_kalSeedsToken);
    const auto& kalSeeds       = *kalSeedsHandle;

    for (auto i_kalSeed = kalSeeds.begin(); i_kalSeed != kalSeeds.end(); ++i_kalSeed) {

      TrackTimePtr track_time(*i_kalSeed);
      art::Ptr<KalSeed> kseedPtr(kalSeedsHandle, i_kalSeed-kalSeeds.begin());
      track_time.setKalSeedPtr(kseedPtr);

      outputTrackTimePtrs->push_back(track_time);
    }

    if (kalSeeds.size() != outputTrackTimePtrs->size()) {
      throw cet::exception("Tutorial") << "Input KalSeedCollection and output TrackTimePtrCollection are different sizes (" << kalSeeds.size() << " and " << outputTrackTimePtrs->size() << " respectively)";
    }

    event.put(std::move(outputTrackTimePtrs));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloTrackTimePtr)
