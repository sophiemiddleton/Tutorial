//
//  The CondensedKalSeed module
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

  class CondensedKalSeed : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
      fhicl::Atom<float> cut{Name("cut"), Comment("momentum cut [MeV/c]")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit CondensedKalSeed(const Parameters& conf);

    void produce(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
    float _cut;
  };

  CondensedKalSeed::CondensedKalSeed(const Parameters& conf)
    : art::EDProducer(conf),
      _conf(conf()),
      _input(conf().input()),
      _cut(conf().cut()){

    produces<KalSeedCollection>();
  }

  void CondensedKalSeed::produce(art::Event& event){

    std::unique_ptr<KalSeedCollection> outputKalSeeds(new KalSeedCollection());

    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;
    for (const auto& i_kalSeed : kalSeedCollection) {

      if (i_kalSeed.segments().begin()->mom() > _cut) {
	outputKalSeeds->push_back(i_kalSeed);
      }
    }

    event.put(std::move(outputKalSeeds));
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::CondensedKalSeed)
