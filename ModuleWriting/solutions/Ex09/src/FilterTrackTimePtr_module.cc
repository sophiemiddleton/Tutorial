//
//  The FilterTrackTimePtr module
//
//  Original author Andy Edmonds
//

#include "Tutorial/ModuleWriting/solutions/Ex09/inc/TrackTimePtr.hh"

#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include <iostream>

namespace mu2e {

  class FilterTrackTimePtr : public art::EDFilter {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> trackTimePtrsTag{Name("trackTimePtrsTag"), Comment("art::InputTag for a TrackTimePtrCollection")};
    };
    typedef art::EDFilter::Table<Config> Parameters;

    explicit FilterTrackTimePtr(const Parameters& conf);

    bool filter(art::Event& event) override;

  private:
    art::ProductToken<TrackTimePtrCollection> const _trackTimePtrsToken;
  };

  FilterTrackTimePtr::FilterTrackTimePtr(const Parameters& conf)
    : art::EDFilter(conf),
      _trackTimePtrsToken{consumes<TrackTimePtrCollection>(conf().trackTimePtrsTag() )}{
  }

  bool FilterTrackTimePtr::filter(art::Event& event){

    const auto& trackTimePtrs = event.getProduct(_trackTimePtrsToken);
    return (trackTimePtrs.size()>0) ? true: false;

  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::FilterTrackTimePtr)
