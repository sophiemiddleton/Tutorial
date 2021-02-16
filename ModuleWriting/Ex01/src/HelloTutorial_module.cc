//
//  The HelloTutorial plugin; the first example of a module.
//
//  $Id: HelloTutorial_module.cc,v 1.5 2013/10/21 21:01:23 kutschke Exp $
//  $Author: kutschke $
//  $Date: 2013/10/21 21:01:23 $
//
//  Original author Rob Kutschke
//  Updated by Andy Edmonds (May 2019)
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

namespace mu2e {

  class HelloTutorial : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HelloTutorial(const Parameters& conf);

    void analyze(const art::Event& event);

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

using mu2e::HelloTutorial;
DEFINE_ART_MODULE(HelloTutorial);
