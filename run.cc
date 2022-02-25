#include "run.hh"

MyRunAction::MyRunAction()
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->CreateH1("edepos", "Energy vs radius", 121, 0., 120.);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
  //create new output file for every run
  G4AnalysisManager *man = G4AnalysisManager::Instance();
 
  G4int runID = run->GetRunID();

  std::stringstream strRunID;
  strRunID << runID;
  
  man->OpenFile("output"+strRunID.str()+".root"); 
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
  //write to histogram
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->Write();
  man->CloseFile();

}
