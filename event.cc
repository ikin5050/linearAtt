#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
}

MyEventAction::~MyEventAction()
{}

//add edep to index x,y in array

void MyEventAction::AddEdep(const G4double edep, G4int r)
{
  array[r] += edep;
}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
  for(int i = 0; i < 100; i++){
    array[i] = 0;
  }
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  for(int i=0; i<100; i++){
    man->FillH1(0, i, array[i]);
  }
}
