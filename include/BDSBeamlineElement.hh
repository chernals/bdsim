#ifndef BDSBEAMLINEELEMENT_H
#define BDSBEAMLINEELEMENT_H

#include "BDSAcceleratorComponent.hh"
#include "BDSSamplerType.hh"

#include "globals.hh" // geant4 globals / types
#include "G4ThreeVector.hh"
#include "BDSTiltOffset.hh"

#include <ostream>

namespace HepGeom {
  class Transform3D;
}
typedef HepGeom::Transform3D G4Transform3D;
namespace CLHEP {
  class HepRotation;
}
typedef CLHEP::HepRotation G4RotationMatrix;

/**
 * @brief A class that holds a fully constructed BDSAcceleratorComponent
 * as well as any information relevant to its position within the beamline.
 *
 * For example, position information as curvilinear s position coordinate
 * as these are only defined with respect to the components position in the 
 * beamline / lattice.
 * 
 * Each instance of this class owns the position vectors and rotation matrices
 * BUT NOT the accelerator component - this is owned by the component registry.
 *
 * This also owns an instance of BDSTiltOffset that the instance of this class
 * was prepared with for reference.  This is optional so can be nullptr and
 * therefore should ALWAYS be tested on.
 * 
 * @author Laurie Nevay
 */

class BDSBeamlineElement
{
public:
  BDSBeamlineElement(BDSAcceleratorComponent* componentIn,
		     G4ThreeVector            positionStartIn,
		     G4ThreeVector            positionMiddleIn,
		     G4ThreeVector            positionEndIn,
		     G4RotationMatrix*        rotationStartIn,
		     G4RotationMatrix*        rotationMiddleIn,
		     G4RotationMatrix*        rotationEndIn,
		     G4ThreeVector            referencePositionStartIn,
		     G4ThreeVector            referencePositionMiddleIn,
		     G4ThreeVector            referencePositionEndIn,
		     G4RotationMatrix*        referenceRotationStartIn,
		     G4RotationMatrix*        referenceRotationMiddleIn,
		     G4RotationMatrix*        referenceRotationEndIn,
		     G4double                 sPositionStartIn,
		     G4double                 sPositionMiddleIn,
		     G4double                 sPositionEndIn,
		     BDSTiltOffset*           tiltOffsetIn  = nullptr,
		     BDSSamplerType           samplerTypeIn = BDSSamplerType::none,
		     G4String                 samplerNameIn = "",
		     G4int                    indexIn       = -1);

  ~BDSBeamlineElement();
  
  ///@{ Accessor
  inline BDSAcceleratorComponent* GetAcceleratorComponent() const {return component;}
  inline G4String          GetName()                      const {return component->GetName();}
  inline G4String          GetType()                      const {return component->GetType();}
  inline G4double          GetArcLength()                 const {return component->GetArcLength();}
  inline G4double          GetChordLength()               const {return component->GetChordLength();}
  inline G4double          GetAngle()                     const {return component->GetAngle();}
  inline BDSBeamPipeInfo*  GetBeamPipeInfo()              const {return component->GetBeamPipeInfo();}
  inline G4String          GetPlacementName()             const {return placementName;}
  inline G4int             GetCopyNo()                    const {return copyNumber;}
  inline G4LogicalVolume*  GetContainerLogicalVolume()    const {return component->GetContainerLogicalVolume();}
  inline G4ThreeVector     GetPositionStart()             const {return positionStart;}
  inline G4ThreeVector     GetPositionMiddle()            const {return positionMiddle;}
  inline G4ThreeVector     GetPositionEnd()               const {return positionEnd;}
  inline G4RotationMatrix* GetRotationStart()             const {return rotationStart;}
  inline G4RotationMatrix* GetRotationMiddle()            const {return rotationMiddle;}
  inline G4RotationMatrix* GetRotationEnd()               const {return rotationEnd;}
  inline G4ThreeVector     GetReferencePositionStart()    const {return referencePositionStart;}
  inline G4ThreeVector     GetReferencePositionMiddle()   const {return referencePositionMiddle;}
  inline G4ThreeVector     GetReferencePositionEnd()      const {return referencePositionEnd;}
  inline G4RotationMatrix* GetReferenceRotationStart()    const {return referenceRotationStart;}
  inline G4RotationMatrix* GetReferenceRotationMiddle()   const {return referenceRotationMiddle;}
  inline G4RotationMatrix* GetReferenceRotationEnd()      const {return referenceRotationEnd;}
  inline G4double          GetSPositionStart()            const {return sPositionStart;}
  inline G4double          GetSPositionMiddle()           const {return sPositionMiddle;}
  inline G4double          GetSPositionEnd()              const {return sPositionEnd;}
  inline BDSTiltOffset*    GetTiltOffset()                const {return tiltOffset;}
  inline G4Transform3D*    GetPlacementTransform()        const {return placementTransform;}
  inline G4Transform3D*    GetPlacementTransformCL()      const {return placementTransformCL;}
  inline BDSSamplerType    GetSamplerType()               const {return samplerType;}
  inline G4String          GetSamplerName()               const {return samplerName;}
  inline G4Transform3D*    GetSamplerPlacementTransform() const {return samplerPlacementTransform;}
  inline G4int             GetIndex()                     const {return index;}
  ///@}

  /// @{ Return face normal accounting for placement tilt of this component.
  G4ThreeVector InputFaceNormal()  const;
  G4ThreeVector OutputFaceNormal() const;
  /// @}

  /// @{ Whether the face normal is angled at all w.r.t. the incoming / outgoing reference trajectory.
  G4bool AngledInputFace()  const {return component->AngledInputFace();}
  G4bool AngledOutputFace() const {return component->AngledOutputFace();}
  /// @}
  
  /// Convenience accessor.
  inline G4double          GetTilt() const {return tiltOffset ? tiltOffset->GetTilt() : 0.0;}
  
  ///@{ Reassign the end variable as required when applying a transform
  inline void SetReferencePositionEnd(G4ThreeVector     newReferencePositionEnd);
  inline void SetReferenceRotationEnd(G4RotationMatrix* newReferenceRotatonEnd);
  ///@}

  /// output stream
  friend std::ostream& operator<< (std::ostream& out, BDSBeamlineElement const &element);
  
private:
  /// Private default constructor to force use of provided constructor
  BDSBeamlineElement() = delete;
  BDSBeamlineElement(const BDSBeamlineElement&) = delete;
  BDSBeamlineElement& operator=(const BDSBeamlineElement&) = delete;

  /// The accelerator component
  BDSAcceleratorComponent* component;

  /// A unique name for placement with "_pv" suffix created for each element
  /// when added to the beamline which is made by interrogating how many times
  /// the BDSAcceleratorComponent has been placed (increments the accelerator
  /// component placement counter).
  G4String          placementName;
  
  /// identification number of AcceleratorComponent (0 for first volume of given type)
  G4int             copyNumber;
  
  ///@{ Global coordinates for the start, middle and end of this beamline element
  G4ThreeVector     positionStart;
  G4ThreeVector     positionMiddle;
  G4ThreeVector     positionEnd;
  ///@}
  
  ///@{ Global rotation matrices for the start, middle and end of this beamline element
  G4RotationMatrix* rotationStart;
  G4RotationMatrix* rotationMiddle;
  G4RotationMatrix* rotationEnd;
  ///@}

  ///@{ Global coordinates for the start, middle and end of this beamline element
  /// along the reference trajectory without any component offsets / displacements
  G4ThreeVector     referencePositionStart;
  G4ThreeVector     referencePositionMiddle;
  G4ThreeVector     referencePositionEnd;
  ///@}
  
  ///@{ Global rotation matrices for the start, middle and end of this beamline element
  /// along the reference trajectory without any tilt or rotation from the component
  G4RotationMatrix* referenceRotationStart;
  G4RotationMatrix* referenceRotationMiddle;
  G4RotationMatrix* referenceRotationEnd;
  ///@}

  ///@{ S Positions for the start, middle and end of this beamline element
  G4double          sPositionStart;
  G4double          sPositionMiddle;
  G4double          sPositionEnd;
  ///@}

  /// The tilt and offset this element was constructed with. Default is nullptr.
  BDSTiltOffset*    tiltOffset;

  /// Transform made from positionMiddle and rotationMiddle. By using them as
  /// a transform, the rotation matrix is the correct way around (inversion).
  G4Transform3D*    placementTransform;

  /// Transform made from the referencePositionMiddle and referenceRottationMiddle.
  /// The read out (curvilinear) geometry should always align with the reference
  /// trajectory and not the possibly offset position of the mass geometry, hence
  /// have a separate transform for it.
  G4Transform3D*    placementTransformCL;

  /// The type of sampler to attach to this element - could be none as well.
  const BDSSamplerType samplerType;

  const G4String samplerName;

  /// The transform for where the sampler 'attached' to this element should be placed.
  /// Note this would normally overlap in the real 'mass' world, but this will be used
  /// in the sampler parallel world, so a transform to coordinates that lie within the
  /// accelerator component are valid. This transform places the sampler just at the
  /// end of the element overlapping with the outgoing boundary as defined by the
  /// reference position at the end and the reference rotation at the end.
  G4Transform3D*    samplerPlacementTransform;

  /// Index of this item in the beamline - saves keeping track of iterators and conversion.
  G4int index;
};

#endif
