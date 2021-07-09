//
//  The HelloCoolKalSeed module
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

#include "TH1F.h"

namespace mu2e {

  class HelloCoolKalSeed : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
      fhicl::Atom<float> cut{Name("cut"), Comment("Time Cut [ns]")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit HelloCoolKalSeed(const Parameters& conf);

    void produce(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
    float _cut;
  };

  HelloCoolKalSeed::HelloCoolKalSeed(const Parameters& conf)
    : _conf(conf()),
      _input(conf().input()),
      _cut(conf().cut()){

    produces<KalSeedCollection>();
  }

  void HelloCoolKalSeed::produce(art::Event& event){

    std::unique_ptr<KalSeedCollection> outputKalSeeds(new KalSeedCollection());

    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;
    for (const auto& i_kalSeed : kalSeedCollection) {

      if (i_kalSeed.t0().t0() > _cut) {
	outputKalSeeds->push_back(i_kalSeed);
      }
    }

    event.put(std::move(outputKalSeeds));
  }

} // end namespace mu2e

using mu2e::HelloCoolKalSeed;
DEFINE_ART_MODULE(HelloCoolKalSeed);
