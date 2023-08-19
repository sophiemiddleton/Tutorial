//
//  The HelloCoolTrackTimePtr module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "Tutorial/ModuleWriting/solutions/Ex09/inc/TrackTimePtr.hh"

namespace mu2e {

  class HelloCoolTrackTimePtr : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> trackTimePtrsTag{Name("trackTimePtrsTag"), Comment("art::InputTag for a TrackTimePtrCollection")};
      fhicl::Atom<float> tcut{Name("tcut"), Comment("Time Cut [ns]")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloCoolTrackTimePtr(const Parameters& conf);

    void produce(art::Event& event) override;

  private:

    art::ProductToken<TrackTimePtrCollection> const _trackTimePtrsToken;
    float _tcut;
  };

  HelloCoolTrackTimePtr::HelloCoolTrackTimePtr(const Parameters& conf)
    : art::EDProducer(conf),
      _trackTimePtrsToken{consumes<TrackTimePtrCollection>(conf().trackTimePtrsTag() )},
      _tcut(conf().tcut()){

    produces<TrackTimePtrCollection>();
  }

  void HelloCoolTrackTimePtr::produce(art::Event& event){

    auto outputTrackTimePtrs = std::make_unique<TrackTimePtrCollection>(TrackTimePtrCollection());

    const auto& trackTimePtrs = event.getProduct(_trackTimePtrsToken);
    for (const auto& trackTimePtr : trackTimePtrs ) {

      if (trackTimePtr.time() > _tcut) {
	outputTrackTimePtrs->push_back(trackTimePtr);
      }
    }

    event.put(std::move(outputTrackTimePtrs));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloCoolTrackTimePtr)
