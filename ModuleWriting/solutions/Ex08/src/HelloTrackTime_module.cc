//
//  The HelloTrackTime module
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
#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"


namespace mu2e {

  class HelloTrackTime : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloTrackTime(const Parameters& conf);

    void produce(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
  };

  HelloTrackTime::HelloTrackTime(const Parameters& conf)
    : art::EDProducer(conf),
      _conf(conf()),
      _input(conf().input()){

    produces<TrackTimeCollection>();
  }

  void HelloTrackTime::produce(art::Event& event){

    std::unique_ptr<TrackTimeCollection> outputTrackTimes(new TrackTimeCollection());

    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;
    for (const auto& i_kalSeed : kalSeedCollection) {

      TrackTime track_time(i_kalSeed);
      outputTrackTimes->push_back(track_time);
    }

    if (kalSeedCollection.size() != outputTrackTimes->size()) {
      throw cet::exception("Tutorial") << "Input KalSeedCollection and output TrackTimeCollection are different sizes (" << kalSeedCollection.size() << " and " << outputTrackTimes->size() << " respectively)";
    }

    event.put(std::move(outputTrackTimes));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloTrackTime)
