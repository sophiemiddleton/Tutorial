//
//  The HistogramTrackTime module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"

#include "TH1F.h"

#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"

namespace mu2e {

  class HistogramTrackTime : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HistogramTrackTime(const Parameters& conf);

    void beginJob();
    void analyze(const art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
    TH1F* _hTrackTimes;
  };

  HistogramTrackTime::HistogramTrackTime(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()),
      _input(conf().input()){
  }

  void HistogramTrackTime::beginJob() {
    art::ServiceHandle<art::TFileService> tfs;
    double min_t0 = 0;
    double max_t0 = 1700;
    double t0_width = 10;
    int n_t0_bins = (max_t0 - min_t0) / t0_width;
    _hTrackTimes = tfs->make<TH1F>("hTrackTimes","Track t0", n_t0_bins,min_t0,max_t0);
  }

  void HistogramTrackTime::analyze(const art::Event& event){

    const auto& trackTimeCollectionHandle = event.getValidHandle<TrackTimeCollection>(_input);
    const auto& trackTimeCollection = *trackTimeCollectionHandle;
    for (const auto& i_trackTime : trackTimeCollection) {
      _hTrackTimes->Fill(i_trackTime.time());
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HistogramTrackTime)
