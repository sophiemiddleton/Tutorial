//
// Start at a TGeoNode, descend the daughter tree. 
//
// If a volume is inside either the DS2 or DS3 volumes,
// make it visible; otherwise make it invisible.
//
// Special case:
// If the volume is a virtual detector, make it invisible
// even if it is inside the DS2 or DS3.
//

#include "InsideDS.hh"

#include "TGeoNode.h"
#include "TGeoVolume.h"


using namespace std;

InsideDS::InsideDS( TGeoNode * node, bool inDSVac ):
  _name(node->GetVolume()->GetName()),
  _inDSVac(inDSVac){

  // Is this volume's mother inside the DS vacuum; if so 
  // remember it so that it's descendants know too.
  if ( node->GetMotherVolume() ) {
    string motherName(node->GetMotherVolume()->GetName());
    if ( motherName == "DS2Vacuum" || motherName == "DS3Vacuum" ){
      _inDSVac = true;
    }
  }

  if ( _inDSVac && _name.find("Virtual") != 0 ) {
    node->SetVisibility(kTRUE);
  } else{
    node->SetVisibility(kFALSE);
  }

  // Descend into each daughter TGeoNode.
  int ndau = node->GetNdaughters();
  for ( int i=0; i<ndau; ++i ){
    TGeoNode * dau = node->GetDaughter(i);
    InsideDS( dau, _inDSVac );
  }

}
