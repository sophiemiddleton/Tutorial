//
//  The HelloKalSeed module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "RecoDataProducts/inc/KalSeed.hh"

namespace mu2e {

  class HelloKalSeed : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HelloKalSeed(const Parameters& conf);

    void analyze(const art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
  };

  HelloKalSeed::HelloKalSeed(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()),
      _input(conf().input()){

    std::cout << "The input tag is " << _input << std::endl;
  }

  void HelloKalSeed::analyze(const art::Event& event){
    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;
    for (const auto& i_kalSeed : kalSeedCollection) {
      std::cout << "t0 = " << i_kalSeed.t0().t0() << " ns" << std::endl;
    }
  }

} // end namespace mu2e

using mu2e::HelloKalSeed;
DEFINE_ART_MODULE(HelloKalSeed);
