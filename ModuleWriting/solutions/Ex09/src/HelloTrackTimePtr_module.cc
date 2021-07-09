//
//  The HelloTrackTimePtr module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "solutions/Ex09/inc/TrackTimePtr.hh"


namespace mu2e {

  class HelloTrackTimePtr : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloTrackTimePtr(const Parameters& conf);

    void produce(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
  };

  HelloTrackTimePtr::HelloTrackTimePtr(const Parameters& conf)
    : _conf(conf()),
      _input(conf().input()){

    produces<TrackTimePtrCollection>();
  }

  void HelloTrackTimePtr::produce(art::Event& event){

    std::unique_ptr<TrackTimePtrCollection> outputTrackTimePtrs(new TrackTimePtrCollection());

    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;
    for (auto i_kalSeed = kalSeedCollection.begin(); i_kalSeed != kalSeedCollection.end(); ++i_kalSeed) {

      TrackTimePtr track_time(*i_kalSeed);
      art::Ptr<KalSeed> kseedPtr(kalSeedCollectionHandle, i_kalSeed-kalSeedCollection.begin());
      track_time.setKalSeedPtr(kseedPtr);

      outputTrackTimePtrs->push_back(track_time);
    }

    if (kalSeedCollection.size() != outputTrackTimePtrs->size()) {
      throw cet::exception("Tutorial") << "Input KalSeedCollection and output TrackTimePtrCollection are different sizes (" << kalSeedCollection.size() << " and " << outputTrackTimePtrs->size() << " respectively)";
    }

    event.put(std::move(outputTrackTimePtrs));
  }

} // end namespace mu2e

using mu2e::HelloTrackTimePtr;
DEFINE_ART_MODULE(HelloTrackTimePtr);
