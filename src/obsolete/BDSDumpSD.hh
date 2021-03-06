#ifndef BDSDUMPSD_H
#define BDSDUMPSD_H 

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class BDSDumpSD : public G4VSensitiveDetector
{
  
public:
  BDSDumpSD(G4String name, G4String type);
  ~BDSDumpSD();
  
  void SetType(G4String aType);
  
  virtual void Initialize(G4HCofThisEvent*HCE);
  virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
  
private:  
  G4String itsType;
  G4String itsCollectionName;
};

inline void BDSDumpSD::SetType(G4String aType)
{itsType=aType;}

#endif

