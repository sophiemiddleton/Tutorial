//
//  The FilterTrackTime module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"

namespace mu2e {

  class FilterTrackTime : public art::EDFilter {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDFilter::Table<Config> Parameters;

    explicit FilterTrackTime(const Parameters& conf);

    bool filter(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
  };

  FilterTrackTime::FilterTrackTime(const Parameters& conf)
    : art::EDFilter(conf),
      _conf(conf()),
      _input(conf().input()){

  }

  bool FilterTrackTime::filter(art::Event& event){

    const auto& trackTimeCollectionHandle = event.getValidHandle<TrackTimeCollection>(_input);
    const auto& trackTimeCollection = *trackTimeCollectionHandle;
    if (trackTimeCollection.size()>0) {
      return true;
    }
    else {
      return false;
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::FilterTrackTime)
