//
//  The HelloCoolTrackTime module
//
//  Original author Andy Edmonds
//

#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include <iostream>

namespace mu2e {

  class HelloCoolTrackTime : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> trackTimesTag{Name("trackTimesTag"), Comment("art::InputTag for a TrackTimeCollection")};
      fhicl::Atom<float> tcut{Name("tcut"), Comment("Time Cut [ns]")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloCoolTrackTime(const Parameters& conf);

    void produce(art::Event& event) override;

  private:

    art::ProductToken<TrackTimeCollection> const _trackTimesToken;
    float _tcut;

  };

  HelloCoolTrackTime::HelloCoolTrackTime(const Parameters& conf)
    : art::EDProducer(conf),
      _trackTimesToken{consumes<TrackTimeCollection>(conf().trackTimesTag() )},
    _tcut{conf().tcut()}{
      produces<TrackTimeCollection>();
    }

  void HelloCoolTrackTime::produce(art::Event& event){

    auto outputTrackTimes = std::make_unique<TrackTimeCollection>( TrackTimeCollection() );

    const auto& trackTimes = event.getProduct( _trackTimesToken );
    for (const auto& trackTime : trackTimes ) {

      if ( trackTime.time() > _tcut) {
	outputTrackTimes->push_back(trackTime);
      }
    }

    event.put(std::move(outputTrackTimes));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloCoolTrackTime)
