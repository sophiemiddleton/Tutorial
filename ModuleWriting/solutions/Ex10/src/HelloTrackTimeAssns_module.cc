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

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"
#include "Tutorial/ModuleWriting/solutions/Ex10/inc/OurAssns.hh"

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
    : art::EDProducer(conf),
      _conf(conf()),
      _input(conf().input()){

    produces<TrackTimeCollection>();
    produces<OurAssns>();
  }

  void HelloTrackTimeAssns::produce(art::Event& event){

    std::unique_ptr<TrackTimeCollection> outputTrackTimes(new TrackTimeCollection());
    std::unique_ptr<OurAssns> outputAssns(new OurAssns());

    // Helper struct to transiently save the information needed to make the Assns.
    struct indexPair{
      indexPair( size_t ks, size_t tt):kalSeed(ks),trackTime(tt){}
      size_t kalSeed;
      size_t trackTime;
    };
    std::vector<indexPair> indices;

    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;

    for (auto i_kalSeed = kalSeedCollection.begin(); i_kalSeed != kalSeedCollection.end(); ++i_kalSeed) {

      TrackTime track_time(*i_kalSeed);
      outputTrackTimes->push_back(track_time);

      indices.emplace_back( i_kalSeed-kalSeedCollection.begin(), outputTrackTimes->size()-1 );

    }

    art::PutHandle<TrackTimeCollection> timesH =  event.put(std::move(outputTrackTimes));

    // Create the Assns and put it in the event.
    for ( auto const& i : indices ){
      outputAssns->addSingle( art::Ptr{ timesH, i.trackTime}, art::Ptr{ kalSeedCollectionHandle, i.kalSeed} );
    }
    event.put(std::move(outputAssns));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloTrackTimeAssns)
