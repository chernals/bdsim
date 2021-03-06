#ifndef BDSCCDCHIP_H
#define BDSCCDCHIP_H 

#include "globals.hh"
#include "BDSCCDPixel.hh"
#include "G4LogicalVolume.hh"

#include "G4VSolid.hh"
#include <vector>
#include "G4TwoVector.hh"
#include "G4ThreeVector.hh"

class BDSCCDChip
{
public:
  BDSCCDChip(G4String aName, G4ThreeVector pixelSize, G4TwoVector nPixels);
  ~BDSCCDChip();
  inline G4LogicalVolume* log(){return _log;}
  inline G4String name(){return _name;}
  inline G4ThreeVector size(){return _size;}

protected:

private:
  void computeDimensions();
  void build();
  void buildMotherVolume();
  void buildPixels();
  
  // Geometrical objects:
  //  G4VPhysicalVolume* _phys;
  G4LogicalVolume* _log;
  G4VSolid* _solid;
  BDSCCDPixel* _pixel;
  
private:
  const G4TwoVector _nPixels;
  G4ThreeVector _size;
  G4String _name;
};

#endif
