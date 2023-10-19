// Draw the full mu2e world.
//

void world()
{
  gEnv->SetValue("Viewer3D.DefaultDrawOption", "ogl");

  TGeoManager* geom = TGeoManager::Import("mu2e.gdml");
  TBrowser*       b = new TBrowser();
  geom->GetTopVolume()->Draw();
}

