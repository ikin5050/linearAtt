#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
  fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  //Define Track
  G4Track *track = step->GetTrack();

  //Get Touchable

  auto *Vol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  int copyNo = Vol->GetCopyNo();
  int radius = copyNo - 1;  
  
  //Get volume containing particle
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  //Get scoring volume
  const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());  
  G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();

  //Compare volume with particle and volume of interest
  if(volume == fScoringVolume){
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep, radius);
  }

}
