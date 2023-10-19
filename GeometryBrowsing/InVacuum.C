// Draw only the objects that are inside vacuum volumes.
//
{
  gEnv->SetValue("Viewer3D.DefaultDrawOption", "ogl");

#include "InVacuum.cc+"

  TGeoManager *geom = TGeoManager::Import("mu2e.gdml");
  TBrowser *b       =  new TBrowser();

  TGeoNode *top = geom->GetTopNode();

  // Traverse the geometry tree; make all virtual
  // detectors visible and all others invisible.
  InVacuum d(top,false);

  geom->GetTopVolume()->Draw();
}

