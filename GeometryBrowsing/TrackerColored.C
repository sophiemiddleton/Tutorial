//
// View inside the TrackerMother volume.
// Modify the colors of selected volumes.
//

{

  gEnv->SetValue("Viewer3D.DefaultDrawOption", "ogl");

  TGeoManager *geom = TGeoManager::Import("mu2e.gdml");
  TBrowser *b       =  new TBrowser();

  // The v5* geometry has names that start with TTracker but the v7* geometry
  // has names that start with Tracker (no leading T).
  auto whichTracker =  geom->GetVolume("TTrackerEndRingUpstream");

  // The v7 version
  if ( whichTracker == 0 ){
    geom->GetVolume("TrackerEndRingUpstream")->SetLineColor(kBlack);

    geom->GetVolume("ThinSupportRing_0")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_1")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_2")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_3")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_4")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_5")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_6")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_7")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_8")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_9")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_10")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_11")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_12")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_13")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_14")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_15")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_16")->SetLineColor(kRed);

    geom->GetVolume("TrackerSupportBeam_10")->SetLineColor(kGreen);
    geom->GetVolume("TrackerSupportBeam_11")->SetLineColor(kGreen);
    geom->GetVolume("TrackerSupportBeam_12")->SetLineColor(kGreen);
    geom->GetVolume("TrackerSupportBeam_20")->SetLineColor(kGreen);
    geom->GetVolume("TrackerSupportBeam_21")->SetLineColor(kGreen);
    geom->GetVolume("TrackerSupportBeam_22")->SetLineColor(kGreen);
  } 
  // The v5 version.
  else {
    geom->GetVolume("TTrackerEndRingUpstream")->SetLineColor(kRed);

    geom->GetVolume("ThinSupportRing_0")->SetLineColor(kRed);
    geom->GetVolume("ThinSupportRing_1")->SetLineColor(kRed);

    geom->GetVolume("TTrackerSupportBeam_00")->SetLineColor(kGreen);
    geom->GetVolume("TTrackerSupportBeam_10")->SetLineColor(kGreen);
    geom->GetVolume("TTrackerSupportBeam_11")->SetLineColor(kGreen);
    geom->GetVolume("TTrackerSupportBeam_12")->SetLineColor(kGreen);
    geom->GetVolume("TTrackerSupportBeam_20")->SetLineColor(kGreen);
    geom->GetVolume("TTrackerSupportBeam_21")->SetLineColor(kGreen);
    geom->GetVolume("TTrackerSupportBeam_22")->SetLineColor(kGreen);
  }
  geom->GetVolume("VirtualDetector_TT_Mid")->SetLineColor(kBlue);

  geom->GetVolume("TrackerMother")->Draw();
}
