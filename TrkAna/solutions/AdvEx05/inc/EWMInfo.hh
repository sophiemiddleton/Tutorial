#ifndef EWMInfo_hh_
#define EWMInfo_hh_

namespace mu2e {

  struct EWMInfo {
    EWMInfo() { reset(); }

    Float_t _tOffset;

    void reset() { _tOffset = 0.0; }
    static std::string leafnames() {
      static std::string leaves;
      leaves = "tOffset/F";
      return leaves;
    }
  };
}

#endif
