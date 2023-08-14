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

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
      fhicl::Atom<float> cut{Name("cut"), Comment("Time Cut [ns]")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloCoolTrackTimePtr(const Parameters& conf);

    void produce(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
    float _cut;
  };

  HelloCoolTrackTimePtr::HelloCoolTrackTimePtr(const Parameters& conf)
    : art::EDProducer(conf),
      _conf(conf()),
      _input(conf().input()),
      _cut(conf().cut()){

    produces<TrackTimePtrCollection>();
  }

  void HelloCoolTrackTimePtr::produce(art::Event& event){

    std::unique_ptr<TrackTimePtrCollection> outputTrackTimePtrs(new TrackTimePtrCollection());

    const auto& trackTimeCollectionHandle = event.getValidHandle<TrackTimePtrCollection>(_input);
    const auto& trackTimeCollection = *trackTimeCollectionHandle;
    for (const auto& i_trackTime : trackTimeCollection) {

      if (i_trackTime.time() > _cut) {
	outputTrackTimePtrs->push_back(i_trackTime);
      }
    }

    event.put(std::move(outputTrackTimePtrs));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloCoolTrackTimePtr)
