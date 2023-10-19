// 
// Draw the Mu2e world but make the following volumes invisible:
//  - anything in the top two levels of the volume heirarchy
//  - anything related to the building, shielding or the CRV
//  - Virtual detectors
//
{
  gEnv->SetValue("Viewer3D.DefaultDrawOption", "ogl");

#include "NoBuildingOrCRV.cc+"

  TGeoManager *geom = TGeoManager::Import("mu2e.gdml");
  TBrowser *b       = new TBrowser();

  TGeoNode *top = geom->GetTopNode();
  NoBuildingOrCRV d(top,0);

  geom->GetVolume("HallAir")->Draw();
}

