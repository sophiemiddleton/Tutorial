//
//  The FilterTrackTimePtr module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "solutions/Ex09/inc/TrackTimePtr.hh"

namespace mu2e {

  class FilterTrackTimePtr : public art::EDFilter {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDFilter::Table<Config> Parameters;

    explicit FilterTrackTimePtr(const Parameters& conf);

    bool filter(art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
  };

  FilterTrackTimePtr::FilterTrackTimePtr(const Parameters& conf)
    : _conf(conf()),
      _input(conf().input()){

  }

  bool FilterTrackTimePtr::filter(art::Event& event){

    const auto& trackTimeCollectionHandle = event.getValidHandle<TrackTimePtrCollection>(_input);
    const auto& trackTimeCollection = *trackTimeCollectionHandle;
    if (trackTimeCollection.size()>0) {
      return true;
    }
    else {
      return false;
    }
  }

} // end namespace mu2e

using mu2e::FilterTrackTimePtr;
DEFINE_ART_MODULE(FilterTrackTimePtr);
