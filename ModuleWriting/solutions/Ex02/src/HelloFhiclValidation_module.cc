//
//  The HelloFhiclValidation plugin; the first example of a module.
//
//  Original author Andy Edmonds (May 2019)
//

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "fhiclcpp/types/OptionalAtom.h"

#include <iostream>

namespace mu2e {

  class HelloFhiclValidation : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<int> number{Name("number"), Comment("This module will print this number")};
      fhicl::Atom<int> defaultNumber{Name("defaultNumber"), Comment("This module will print this number and it has a default"), 100};
      fhicl::OptionalAtom<int> optionalNumber{Name("optionalNumber"), Comment("This module will print this number but it is optional")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HelloFhiclValidation(const Parameters& conf);

    void analyze(const art::Event& event);

  private:
    Config _conf;

    int _number;
    int _defaultNumber;
    int _optionalNumber;
  };

  HelloFhiclValidation::HelloFhiclValidation(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()),
      _number(conf().number()),
      _defaultNumber(conf().defaultNumber()){
  }

  void HelloFhiclValidation::analyze(const art::Event& event){
    std::cout << "My _number is..." << _number << std::endl;
    std::cout << "My _defaultNumber is..." << _defaultNumber << std::endl;

    if (_conf.optionalNumber(_optionalNumber)) {
      std::cout << "My _optionalNumber is..." << _optionalNumber << std::endl;
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloFhiclValidation)
