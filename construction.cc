#include "construction.hh"
#include "G4SDManager.hh"


MyDetectorConstruction::MyDetectorConstruction()
{
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

  fMessenger->DeclareProperty("nSpheres", nDetectors, "# spheres");

  nDetectors = 100;
  personRadius = 0.2;

  DefineMaterials();

  xWorld = 0.5*m;
  yWorld = 0.5*m;
  zWorld = 0.5*m;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{ 
  G4NistManager *nist = G4NistManager::Instance();

  SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
  SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
  SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

  H2O = new G4Material("H20", 1*g/cm3, 2);
  H2O->AddElement(nist->FindOrBuildElement("H"), 2);
  H2O->AddElement(nist->FindOrBuildElement("O"), 1);

  C = nist->FindOrBuildElement("C");

  Na = nist->FindOrBuildElement("Na");
  I = nist->FindOrBuildElement("I");
  NaI = new G4Material("NaI", 3.67*g/cm3, 2);
  NaI->AddElement(Na, 1);
  NaI->AddElement(I, 1);

  worldMat = nist->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");
}


void MyDetectorConstruction::ConstructSpheres()
{
  //radius is set as 20cm (little bit on the large size but hey)
  
  //sphere = new sphere(name, inner radius, outer radius, low phi, high phi, low theta, high theta)
  solidRadiator = new G4Sphere("solidRadiator", 0.*m, personRadius*m, 0.0*deg, 360.0*deg, 0.0*deg, 180.0*deg);

  logicRadiator = new G4LogicalVolume(solidRadiator, worldMat, "logicRadiator");

  fScoringVolume = logicRadiator;

  //g4pvplacment (rotation matrix, 3vector translation, current logical, name, mother logical, pMany(meant to overlap), copyNo, surf(check for overlap))
  physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicRadiator, "physRadiator", logicWorld, false, 0, true);

  

  for(G4int r=0; r < nDetectors; r++){
    solidDetector = new G4Sphere("solidDetector", ((personRadius/nDetectors)*r)*m, ((personRadius/nDetectors)*(r+1))*m, 0.0*deg, 360.0*deg, 0.0*deg, 180.0*deg);
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    physDetector = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), logicDetector, "physDetector", logicWorld, false, r+1, true);
  }
}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);

  logicWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");
  
  physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

  ConstructSpheres();
  
  return physWorld;
  
}


void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  logicDetector->SetSensitiveDetector(sensDet);
}
