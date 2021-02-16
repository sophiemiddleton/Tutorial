//
//  The HelloCoolTrackTime module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "solutions/Ex08/inc/TrackTime.hh"

namespace mu2e {

  class HelloCoolTrackTime : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
      fhicl::Atom<float> cut{Name("cut"), Comment("Time Cut [ns]")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloCoolTrackTime(const Parameters& conf);

    void produce(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
    float _cut;
  };

  HelloCoolTrackTime::HelloCoolTrackTime(const Parameters& conf)
    : _conf(conf()),
      _input(conf().input()),
      _cut(conf().cut()){

    produces<TrackTimeCollection>();
  }

  void HelloCoolTrackTime::produce(art::Event& event){

    std::unique_ptr<TrackTimeCollection> outputTrackTimes(new TrackTimeCollection());

    const auto& trackTimeCollectionHandle = event.getValidHandle<TrackTimeCollection>(_input);
    const auto& trackTimeCollection = *trackTimeCollectionHandle;
    for (const auto& i_trackTime : trackTimeCollection) {

      if (i_trackTime.time() > _cut) {
	outputTrackTimes->push_back(i_trackTime);
      }
    }

    event.put(std::move(outputTrackTimes));
  }

} // end namespace mu2e

using mu2e::HelloCoolTrackTime;
DEFINE_ART_MODULE(HelloCoolTrackTime);
