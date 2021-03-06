#include "BDSFieldMag.hh"

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

BDSFieldMag::BDSFieldMag():
  transform(G4Transform3D::Identity),
  inverseTransform(G4Transform3D::Identity)
{;}

BDSFieldMag::BDSFieldMag(G4Transform3D transformIn):
  transform(transformIn),
  inverseTransform(transformIn.inverse())
{;}

G4ThreeVector BDSFieldMag::GetFieldTransformed(const G4ThreeVector& position,
					       const G4double       t) const
{
  if (transform != G4Transform3D::Identity)
    {
      G4ThreeVector transformedPosition = inverseTransform * (HepGeom::Point3D<G4double>)position;
      G4ThreeVector field = GetField(transformedPosition, t);
      G4ThreeVector transformedField = transform * (HepGeom::Vector3D<G4double>)field;
      return transformedField;
    }
  else
    {return GetField(position, t);}
}

void BDSFieldMag::GetFieldValue(const G4double point[4],
				G4double* field) const
{
  G4ThreeVector fieldValue = GetFieldTransformed(G4ThreeVector(point[0], point[1],
							       point[2]), point[3]);
  field[0] = fieldValue[0]; // B_x
  field[1] = fieldValue[1]; // B_y
  field[2] = fieldValue[2]; // B_z
  field[3] = 0;             // E_x
  field[4] = 0;             // E_y
  field[5] = 0;             // E_z
}
