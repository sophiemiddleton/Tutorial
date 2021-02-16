//
// View inside the TrackerMother volume,
//
{
  gEnv->SetValue("Viewer3D.DefaultDrawOption", "ogl");

  TGeoManager *geom = TGeoManager::Import("mu2e.gdml");
  TBrowser *b       =  new TBrowser();
  geom->GetVolume("TrackerMother")->Draw();
}

