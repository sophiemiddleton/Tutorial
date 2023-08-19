//
//  The FilterTrackTime module
//
//  Original author Andy Edmonds
//

#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"

#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include <iostream>

namespace mu2e {

  class FilterTrackTime : public art::EDFilter {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> trackTimesTag{Name("trackTimesTag"), Comment("art::InputTag for a TrackTimeCollection")};
    };
    typedef art::EDFilter::Table<Config> Parameters;

    explicit FilterTrackTime(const Parameters& conf);

    bool filter(art::Event& event) override;

  private:

    art::ProductToken<TrackTimeCollection> const _trackTimesToken;
  };

  FilterTrackTime::FilterTrackTime(const Parameters& conf)
    : art::EDFilter(conf),
      _trackTimesToken{consumes<TrackTimeCollection>(conf().trackTimesTag() )}{
  }

  bool FilterTrackTime::filter(art::Event& event){

    const auto& trackTimes = event.getProduct( _trackTimesToken );
    if (trackTimes.size()>0) {
      return true;
    }
    else {
      return false;
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::FilterTrackTime)
