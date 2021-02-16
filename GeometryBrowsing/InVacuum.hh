#ifndef InVacuum_hh
#define InVacuum_hh

//
// Start at a TGeoNode, descend the daughter tree.  If any ancestor
// of a given volume is a vacuum volume, then make that volume
// visible.
//

class TGeoNode;
class TGeoVolume;

#include <iostream>
#include <string>
#include <vector>

class InVacuum{

public:

  InVacuum( TGeoNode *, bool inVac );
  // Accept compiler written d'tor, copy c'tor and assignment operator.

  std::string const& name() const { return _name; }


private:
  std::string _name;
  bool        _inVac;

};

#endif /* InVacuum_hh */
