#ifndef BDSMAGNETOUTER_H
#define BDSMAGNETOUTER_H

#include "BDSGeometryComponent.hh"

#include "globals.hh"
#include "G4ThreeVector.hh"

class BDSGeometryExternal;
class BDSSimpleComponent;
class G4LogicalVolume;
class G4VSolid;

/**
 * @brief An object for both the returned magnet outer body but also a
 * tight fitting container for the whole magnet.
 * 
 * Mostly BDSGeometryComponent but with the 
 * addition of a suggested container volume for the whole magnet body
 * as the magnet outer section is typically the outside of the magnet
 * and only the magnet factory knows its true shape and can make a well
 * fitting container.
 * 
 * @author Laurie Nevay
 */

class BDSMagnetOuter: public BDSGeometryComponent
{
public:
  BDSMagnetOuter(G4VSolid*             containerSolidIn,
		 G4LogicalVolume*      containerLVIn,
		 BDSExtent             extent,
		 BDSGeometryComponent* magnetContainerIn,
		 G4ThreeVector         placementOffset    = G4ThreeVector(0,0,0),
		 BDSSimpleComponent*   endPieceBeforeIn   = nullptr,
		 BDSSimpleComponent*   endPieceAfterIn    = nullptr,
		 G4ThreeVector         inputFaceNormalIn  = G4ThreeVector(0,0,-1),
		 G4ThreeVector         outputFaceNormalIn = G4ThreeVector(0,0, 1));
  BDSMagnetOuter(BDSGeometryComponent* component,
		 BDSGeometryComponent* magnetContainerIn,
		 BDSSimpleComponent*   endPieceBeforeIn   = nullptr,
		 BDSSimpleComponent*   endPieceAfterIn    = nullptr,
		 G4ThreeVector         inputFaceNormalIn  = G4ThreeVector(0,0,-1),
		 G4ThreeVector         outputFaceNormalIn = G4ThreeVector(0,0, 1));
  BDSMagnetOuter(BDSGeometryExternal*  external,
		 BDSGeometryComponent* magnetContainerIn);
  virtual ~BDSMagnetOuter();

  /// Access the magnet container - a BDSGeometryComponent instance that has a suggested
  /// container solid (null pointer LV! - constructed from solid in BDSMagnet and saves doing it
  /// repeatedly in factories) that would contain both the magnet outer section and the
  /// beam pipe - so a solid container. Use as a way to pass solid + extents
  BDSGeometryComponent* GetMagnetContainer() const {return magnetContainer;}

  /// @{ Access the end piece.
  BDSSimpleComponent* EndPieceBefore() const {return endPieceBefore;}
  BDSSimpleComponent* EndPieceAfter()  const {return endPieceAfter;}
  /// @}

  void SetEndPieceBefore(BDSSimpleComponent* endPieceIn) {endPieceBefore = endPieceIn;}
  void SetEndPieceAfter(BDSSimpleComponent* endPieceIn)  {endPieceAfter = endPieceIn;}
  
  /// Clear the memory of the now uneeded magnet container object.
  void ClearMagnetContainer();

  /// Clear the memory of the possibly uneeded end piece objects.
  void ClearEndPieces();

  /// @{ Accessor.
  inline G4ThreeVector InputFaceNormal()  const {return inputFaceNormal;}
  inline G4ThreeVector OutputFaceNormal() const {return outputFaceNormal;}
  /// @}

  /// @{ Setter for face normals.
  inline void SetInputFaceNormal(const G4ThreeVector input)   {inputFaceNormal = input;}
  inline void SetOutputFaceNormal(const G4ThreeVector output) {outputFaceNormal = output;}
  /// @}
  
protected:
  BDSGeometryComponent* magnetContainer;
  BDSSimpleComponent* endPieceBefore;
  BDSSimpleComponent* endPieceAfter;

  G4ThreeVector    inputFaceNormal;
  G4ThreeVector    outputFaceNormal;
};

#endif
