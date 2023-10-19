//
// Make the following volumes invisible:
//  - anything in the top two levels of the volume heirarchy
//  - anything related to the building, shielding or the CRV
//  - Virtual detectors
//

#include "NoBuildingOrCRV.hh"

#include "TGeoNode.h"
#include "TGeoVolume.h"
#include "Rtypes.h"

#include<string>
#include<vector>

using namespace std;

int NoBuildingOrCRV::maxDepth      = 0;

NoBuildingOrCRV::NoBuildingOrCRV( TGeoNode * node, int depth ):
  _name(node->GetVolume()->GetName()),
  _depth(depth){

  maxDepth = std::max( maxDepth, depth );

  // Volumes will be made invisible if their name contains one
  // of these strings.
  static std::vector<string> substrings  { "CRS", "ExtShield", "Ceiling",
      "backfill", "dirt", "concrete", "VirtualDetector", "CRV", "CRS" };

  // Volumes with these material names will be made invisible.
  static std::vector<string> materials { "MBOverburden", "CONCRETE" };

  if ( _depth < 2 ){
    node->SetVisibility(kFALSE);
  } else{
    bool vis = true;
    for ( auto const& substring : substrings ){
      if ( _name.find(substring) != string::npos ){
	vis = false;
	node->SetVisibility(kFALSE);
	break;
      }
    }
    if ( vis ){
      string material(node->GetVolume()->GetMaterial()->GetName());
      for ( auto const& mat : materials ){
	if ( material.find(mat) != string::npos ){
	  vis = false;
	  node->SetVisibility(kFALSE);
	  break;
	}
      }
    }
  }

  // Descend recursively into each daughter TGeoNode.
  int ndau = node->GetNdaughters();
  for ( int i=0; i<ndau; ++i ){
    TGeoNode * dau = node->GetDaughter(i);
    NoBuildingOrCRV( dau, depth+1);
  }

}
