//
//  The HelloTutorial plugin; the first example of a module.
//
//  Original author Rob Kutschke
//  Updated by Andy Edmonds (May 2019)
//

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include <iostream>

namespace mu2e {

  class HelloTutorial : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HelloTutorial(const Parameters& conf);

    void analyze(const art::Event& event) override;

  private:
    Config _conf;
  };

  HelloTutorial::HelloTutorial(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()) {
  }

  void HelloTutorial::analyze(const art::Event& event){
    std::cout << "Hello, world.  From analyze: "
	      << event.id()
	      << std::endl;
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloTutorial)
