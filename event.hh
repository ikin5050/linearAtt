#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"

#include "construction.hh"
#include "g4root.hh"
#include "run.hh"

class MyEventAction : public G4UserEventAction
{
public:
  MyEventAction(MyRunAction*);
  ~MyEventAction();

  std::array<double, 100> array = {0.};
  int x, y;

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

  void AddEdep(G4double edep, G4int r);

private:
};

#endif
