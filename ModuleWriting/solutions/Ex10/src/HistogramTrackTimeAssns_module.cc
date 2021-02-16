//
//  The HistogramTrackTimeAssns module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Optional/TFileService.h"

#include "solutions/Ex10/inc/OurAssns.hh"

#include "TH2F.h"

namespace mu2e {

  class HistogramTrackTimeAssns : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HistogramTrackTimeAssns(const Parameters& conf);

    void beginJob();
    void analyze(const art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
    TH2F* _hOurAssns;
  };

  HistogramTrackTimeAssns::HistogramTrackTimeAssns(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()),
      _input(conf().input()){
  }

  void HistogramTrackTimeAssns::beginJob() {
    art::ServiceHandle<art::TFileService> tfs;
    double min_t0 = 0;
    double max_t0 = 1700;
    double t0_width = 10;
    int n_t0_bins = (max_t0 - min_t0) / t0_width;
    int min_nhits = 0;
    int max_nhits = 100;
    int nhits_width = 1;
    int n_nhits_bins = (max_nhits - min_nhits) / nhits_width;
    _hOurAssns = tfs->make<TH2F>("hOurAssns","Track t0 vs N KalSeed hits", n_t0_bins,min_t0,max_t0, n_nhits_bins,min_nhits,max_nhits);
  }

  void HistogramTrackTimeAssns::analyze(const art::Event& event){

    const auto& ourAssnsHandle = event.getValidHandle<mu2e::OurAssns>(_input);
    const auto& ourAssns = *ourAssnsHandle;
    for (const auto& i_entry : ourAssns) {

      const auto& ttimePtr = i_entry.first;
      const auto& kseedPtr = i_entry.second;
      _hOurAssns->Fill(ttimePtr->time(), kseedPtr->hits().size());
    }
  }

} // end namespace mu2e

using mu2e::HistogramTrackTimeAssns;
DEFINE_ART_MODULE(HistogramTrackTimeAssns);
