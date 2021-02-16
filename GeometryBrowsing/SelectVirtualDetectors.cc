//
// Start at a TGeoNode, descend the daughter tree.  Make all virtual detectors
// visible, all else invisible.
//

#include "SelectVirtualDetectors.hh"

#include "TGeoNode.h"
#include "TGeoVolume.h"


using namespace std;

SelectVirtualDetectors::SelectVirtualDetectors( TGeoNode * node, int depth ):
  _name(node->GetVolume()->GetName()),
  _depth(depth){

  // Volumes will be made invisible if their name starts with "Virtual"
  if ( _name.find("Virtual") == 0 ){
    node->SetVisibility(kTRUE);
  } else {
    node->SetVisibility(kFALSE);
  }

  // Give colors to the virtual detectors related to the tracker.
  if ( _name.find("VirtualDetector_TT") != string::npos ) {
    if ( _name == "VirtualDetector_TT_Mid" ){
      node->GetVolume()->SetLineColor(kBlue);
    } else if ( _name == "VirtualDetector_TT_MidInner") {
      node->GetVolume()->SetLineColor(kRed);
    } else if ( _name ==  "VirtualDetector_TT_OutSurf" ){
      node->GetVolume()->SetLineColor(kYellow);
    } else if ( _name == "VirtualDetector_TT_FrontHollow" ){
      node->GetVolume()->SetLineColor(kGreen);
    } else if ( _name == "VirtualDetector_TT_Back" ){
      node->GetVolume()->SetLineColor(kGreen);
    } else if ( _name ==  "VirtualDetector_TT_InSurf" ){
      node->GetVolume()->SetLineColor(kCyan);
    }
  }

  // Descend recursively into each daughter TGeoNode.
  int ndau = node->GetNdaughters();
  for ( int i=0; i<ndau; ++i ){
    TGeoNode * dau = node->GetDaughter(i);
    SelectVirtualDetectors( dau, depth+1);
  }

}
