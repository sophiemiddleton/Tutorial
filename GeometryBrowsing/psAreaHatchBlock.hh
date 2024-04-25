#ifndef psAreaHatchBlock_hh
#define psAreaHatchBlock_hh
//
// Make the following volumes invisible:
//  - anything in the top two levels of the volume heirarchy
//  - anything related to the building, shielding or the CRV
//  - Virtual detectors
// Except:
//  - Keep the floors on the bottom level
//  - Keep the psAreaHatchBlock

class TGeoNode;
class TGeoVolume;

#include <iostream>
#include <string>
#include <vector>

class psAreaHatchBlock{

public:

  psAreaHatchBlock( TGeoNode *, int depth );

  // Accept compiler written d'tor, copy c'tor and assignment operator.

  std::string const& name() const { return _name; }

  static int maxDepth;

private:
  std::string _name;
  int         _depth;

};

#endif /* psAreaHatchBlock_hh */
