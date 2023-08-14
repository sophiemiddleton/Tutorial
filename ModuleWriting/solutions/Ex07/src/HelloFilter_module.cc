//
//  The HelloFilter module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"

#include "TH1F.h"

namespace mu2e {

  class HelloFilter : public art::EDFilter {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDFilter::Table<Config> Parameters;

    explicit HelloFilter(const Parameters& conf);

    bool filter(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
  };

  HelloFilter::HelloFilter(const Parameters& conf)
    : art::EDFilter(conf),
      _conf(conf()),
      _input(conf().input()){

  }

  bool HelloFilter::filter(art::Event& event){

    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;
    if (kalSeedCollection.size()>0) {
      return true;
    }
    else {
      return false;
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloFilter)
