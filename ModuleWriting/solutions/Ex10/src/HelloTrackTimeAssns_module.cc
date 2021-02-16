//
//  The HelloTrackTimeAssns module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "RecoDataProducts/inc/KalSeed.hh"
#include "solutions/Ex08/inc/TrackTime.hh"
#include "solutions/Ex10/inc/OurAssns.hh"


namespace mu2e {

  class HelloTrackTimeAssns : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloTrackTimeAssns(const Parameters& conf);

    void produce(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
  };

  HelloTrackTimeAssns::HelloTrackTimeAssns(const Parameters& conf)
    : _conf(conf()),
      _input(conf().input()){

    produces<TrackTimeCollection>();
    produces<OurAssns>();
  }

  void HelloTrackTimeAssns::produce(art::Event& event){

    std::unique_ptr<TrackTimeCollection> outputTrackTimes(new TrackTimeCollection());
    std::unique_ptr<OurAssns> outputAssns(new OurAssns());

    auto TrackTimeProdID = getProductID<TrackTimeCollection>();
    auto TrackTimeGetter = event.productGetter(TrackTimeProdID);

    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;
    for (auto i_kalSeed = kalSeedCollection.begin(); i_kalSeed != kalSeedCollection.end(); ++i_kalSeed) {

      TrackTime track_time(*i_kalSeed);
      outputTrackTimes->push_back(track_time);

      art::Ptr<KalSeed> kseedPtr(kalSeedCollectionHandle, i_kalSeed-kalSeedCollection.begin());
      art::Ptr<TrackTime> trackTimePtr(TrackTimeProdID, outputTrackTimes->size()-1, TrackTimeGetter);
      outputAssns->addSingle(trackTimePtr, kseedPtr);
    }

    if (kalSeedCollection.size() != outputTrackTimes->size()) {
      throw cet::exception("Tutorial") << "Input KalSeedCollection and output TrackTimeCollection are different sizes (" << kalSeedCollection.size() << " and " << outputTrackTimes->size() << " respectively)";
    }

    event.put(std::move(outputTrackTimes));
    event.put(std::move(outputAssns));
  }

} // end namespace mu2e

using mu2e::HelloTrackTimeAssns;
DEFINE_ART_MODULE(HelloTrackTimeAssns);
