#include "BDSArray4DCoords.hh"
#include "BDSFieldValue.hh"
#include "BDSInterpolator4DNearest.hh"


BDSInterpolator4DNearest::BDSInterpolator4DNearest(BDSArray4DCoords* arrayIn):
  BDSInterpolator4D(arrayIn)
{;}

BDSInterpolator4DNearest::~BDSInterpolator4DNearest()
{;}

BDSFieldValue BDSInterpolator4DNearest::GetInterpolatedValueT(G4double x,
							      G4double y,
							      G4double z,
							      G4double t) const
{
  G4int xind = array->NearestX(x);
  G4int yind = array->NearestY(y);
  G4int zind = array->NearestZ(z);
  G4int tind = array->NearestT(t);
  // here we're constructing a copy on purpose
  BDSFieldValue result = array->GetConst(xind, yind, zind, tind);
  return result;
}
