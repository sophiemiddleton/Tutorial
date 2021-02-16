#ifndef InPSVacuum_hh
#define InPSVacuum_hh
//
// Expose the product target and proton absorber assemblies
// inside the PS Vacuum.
//
// Start at a TGeoNode, descend the daughter tree.  Make the following
// volumes invisible:
//   - any volume whose name contains "Shield"
//   - all virtual detectors
//

class TGeoNode;
class TGeoVolume;

#include <iostream>
#include <string>
#include <vector>

class InPSVacuum{

public:

  InPSVacuum( TGeoNode *, bool inVac );
  // Accept compiler written d'tor, copy c'tor and assignment operator.

  std::string const& name() const { return _name; }


private:
  std::string _name;
  bool        _inVac;

};

#endif /* InPSVacuum_hh */
