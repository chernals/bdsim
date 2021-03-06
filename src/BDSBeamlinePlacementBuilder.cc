#include "BDSBeamline.hh"
#include "BDSBeamlineElement.hh"
#include "BDSBeamlinePlacementBuilder.hh"
#include "BDSDetectorConstruction.hh"
#include "BDSExtent.hh"
#include "BDSGeometryExternal.hh"
#include "BDSGeometryFactory.hh"
#include "BDSSimpleComponent.hh"
#include "BDSUtilities.hh"

#include "parser/placement.h"

#include "CLHEP/Units/SystemOfUnits.h"

#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"

#include <vector>


BDSBeamline* BDS::BuildPlacementGeometry(const std::vector<GMAD::Placement>& placements)
{
  if (placements.empty())
    {return nullptr;} // don't do anything - no placements
  
  BDSBeamline* placementBL = new BDSBeamline();

  for (const auto& placement : placements)
    {
      // if a sequence is specified, it's a beam line and will be constructed
      // elsewhere - skip it!
      if (!placement.sequence.empty())
	{continue;}
	
      auto geom = BDSGeometryFactory::Instance()->BuildGeometry(placement.name,
								placement.geometryFile,
								nullptr,
								0, 0,
								placement.sensitive);

      G4double length = geom->GetExtent().DZ();
      BDSSimpleComponent* comp = new BDSSimpleComponent(geom->GetName(),
							geom,
							length);

      G4Transform3D transform = BDSDetectorConstruction::CreatePlacementTransform(placement);
      
      /// Here we're assuming the length is along z which may not be true, but
      /// close enough for this purpose as we rely only on the centre position.
      G4ThreeVector halfLengthBeg = G4ThreeVector(0,0,-length*0.5);
      G4ThreeVector halfLengthEnd = G4ThreeVector(0,0, length*0.5);
      G4ThreeVector midPos        = transform.getTranslation();
      G4ThreeVector startPos = midPos + transform * (HepGeom::Point3D<G4double>)halfLengthBeg;
      G4ThreeVector endPos   = midPos + transform * (HepGeom::Point3D<G4double>)halfLengthEnd;
      G4RotationMatrix* rm   = new G4RotationMatrix(transform.getRotation());
      
      BDSBeamlineElement* el = new BDSBeamlineElement(comp,
						      startPos,
						      midPos,
						      endPos,
						      rm,
						      new G4RotationMatrix(*rm),
						      new G4RotationMatrix(*rm),
						      startPos,
						      midPos,
						      endPos,
						      new G4RotationMatrix(*rm),
						      new G4RotationMatrix(*rm),
						      new G4RotationMatrix(*rm),
						      -1,-1,-1);

      placementBL->AddBeamlineElement(el);
    }

  return placementBL;
}
