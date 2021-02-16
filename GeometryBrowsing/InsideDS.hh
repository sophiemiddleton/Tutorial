#ifndef InsideDS_hh
#define InsideDS_hh

//
// Start at a TGeoNode, descend the daughter tree. 
//
// If a volume inside either the DS2 or DS3 volumes,
// make it visible; otherwise make it invisible.
//
// Special case:
// If the volume is a virtual detector, make it invisible
// even if it is inside the DS2 or DS3.
//

class TGeoNode;
class TGeoVolume;

#include <iostream>
#include <string>
#include <vector>

class InsideDS{

public:

  InsideDS( TGeoNode *, bool inDSVac );
  // Accept compiler written d'tor, copy c'tor and assignment operator.

  std::string const& name() const { return _name; }


private:
  std::string _name;     // Name of this TGeoNode
  bool        _inDSVac;  // Is this node inside he DS vacuum?

};

#endif /* InsideDS_hh */
