//
//  The HelloKalSeed module
//
//  Original author Andy Edmonds
//

#include "Offline/RecoDataProducts/inc/KalSeed.hh"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include <iostream>

namespace mu2e {

  class HelloKalSeed : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> kalSeedsTag{Name("kalSeedsTag"), Comment("art::InputTag for a KalSeedsCollection")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HelloKalSeed(const Parameters& conf);

    void analyze(const art::Event& event) override;

  private:
    art::ProductToken<KalSeedCollection> const _kalSeedsToken;

  };

  HelloKalSeed::HelloKalSeed(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _kalSeedsToken{consumes<KalSeedCollection>(conf().kalSeedsTag() )}{
    std::cout << "Tag for the KalSeeds is: " << conf().kalSeedsTag() << std::endl;
  }

  void HelloKalSeed::analyze(const art::Event& event){

    const auto& kalSeeds = event.getProduct( _kalSeedsToken );
    for (const auto& kSeed : kalSeeds) {
      std::cout << "t0 = " << kSeed.t0().t0() << " ns" << std::endl;
    }

  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloKalSeed)
