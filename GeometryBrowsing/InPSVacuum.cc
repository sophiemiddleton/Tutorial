//
// Expose the product target and proton absorber assemblies
// inside the PS Vacuum.
//
// Start at a TGeoNode, descend the daughter tree.  Make the following
// volumes invisible:
//   - any volume whose name contains "Shield"
//   - all virtual detectors
//

#include "InPSVacuum.hh"

#include "TGeoNode.h"
#include "TGeoVolume.h"

using namespace std;

InPSVacuum::InPSVacuum( TGeoNode * node, bool inVac ):
  _name(node->GetVolume()->GetName()),
  _inVac(inVac){

  if ( node->GetMotherVolume() ) {
    string motherName(node->GetMotherVolume()->GetName());
    if ( motherName.find("PSVacuum") != string::npos ){
      _inVac = true;
    }
  }

  if ( _inVac ) {
    if ( _name.find("PSShieldShell") == 0 ){
      node->SetVisibility(kFALSE);
    } else if ( _name.find("VirtualDetector") == 0){
      node->SetVisibility(kFALSE);
    } else if ( _name == "PbarAbsTS1InRecord" ){
      node->SetVisibility(kFALSE);
    } else {
      node->SetVisibility(kTRUE);
    }
  } else{
    node->SetVisibility(kFALSE);
  }

  // Descend recursively into each daughter TGeoNode.
  int ndau = node->GetNdaughters();
  for ( int i=0; i<ndau; ++i ){
    TGeoNode * dau = node->GetDaughter(i);
    InPSVacuum( dau, _inVac );
  }

}
