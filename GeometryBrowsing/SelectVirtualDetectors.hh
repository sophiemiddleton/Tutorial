#ifndef SelectVirtualDetectors_hh
#define SelectVirtualDetectors_hh

//
// Start at a TGeoNode, descend the daughter tree.  Make all virtual detectors
// visible, all else invisible.
//
// Contact person Rob Kutschke
//

class TGeoNode;
class TGeoVolume;

#include <iostream>
#include <string>
#include <vector>

class SelectVirtualDetectors{

public:

  SelectVirtualDetectors( TGeoNode *, int depth );
  // Accept compiler written d'tor, copy c'tor and assignment operator.

  std::string const& name() const { return _name; }


private:
  std::string _name;
  int         _depth;

};

#endif /* SelectVirtualDetectors_hh */
