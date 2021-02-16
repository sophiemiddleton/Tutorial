//
// Expose the product target and proton absorber assemblies
// inside the PS Vacuum.
//
{
  gEnv->SetValue("Viewer3D.DefaultDrawOption", "ogl");

#include "InPSVacuum.cc+"

  TGeoManager *geom = TGeoManager::Import("mu2e.gdml");
  TBrowser *b       =  new TBrowser();

  InPSVacuum d(geom->GetTopNode(),false);
  
  geom->GetVolume("PSVacuum")->Draw();
}

