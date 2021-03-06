#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MyDetectorConstruction();
  ~MyDetectorConstruction();

  G4LogicalVolume *GetScoringVolume() const { return fScoringVolume;}

  virtual G4VPhysicalVolume *Construct();

private:
  virtual void ConstructSDandField();

  G4int nDetectors;
  G4double xWorld, yWorld, zWorld, personRadius;

  G4Box *solidWorld;
  G4Sphere *solidRadiator, *solidDetector;
  G4LogicalVolume *logicWorld, *logicRadiator, *logicDetector;
  G4VPhysicalVolume *physWorld, *physRadiator, *physDetector;

  G4GenericMessenger *fMessenger;

  G4Material *SiO2, *H2O, *Aerogel, *worldMat, *NaI;
  G4Element *C, *Na, *I;

  G4LogicalVolume *fScoringVolume;


  void DefineMaterials();
  void ConstructSpheres();
};

#endif
