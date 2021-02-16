//
// Start at a TGeoNode, descend the daughter tree.  If any ancestor
// of a given volume is a vacuum volume, then make that volume
// visible.
//

#include "InVacuum.hh"

#include "TGeoNode.h"
#include "TGeoVolume.h"


using namespace std;

InVacuum::InVacuum( TGeoNode * node, bool inVac ):
  _name(node->GetVolume()->GetName()),
  _inVac(inVac){

  if ( node->GetMotherVolume() ) {
    string motherName(node->GetMotherVolume()->GetName());
    if ( motherName.find("Vacuum") != string::npos ){
      _inVac = true;
    }
  }

  if ( _inVac ) {
    node->SetVisibility(kTRUE);
  } else{
    node->SetVisibility(kFALSE);
  }

  // Descend recursively into each daughter TGeoNode.
  int ndau = node->GetNdaughters();
  for ( int i=0; i<ndau; ++i ){
    TGeoNode * dau = node->GetDaughter(i);
    InVacuum( dau, _inVac );
  }

}
