#ifndef BDSMAGNET_H
#define BDSMAGNET_H

#include "globals.hh"
#include "BDSAcceleratorComponent.hh"
#include "BDSFieldInfo.hh"
#include "BDSMagnetType.hh"

class BDSBeamPipe;
class BDSBeamPipeInfo;
class BDSMagnetOuter;
class BDSMagnetOuterInfo;
class BDSMagnetStrength;

/**
 * @brief Abstract base class that implements features common to all magnets. 
 *
 * This includes the general construction pattern using the magnet 
 * outer geometry factories and the field related objects and attaching 
 * them to the necessary volumes. Each derived class must implement 
 * BuildBPFieldAndStepper() which constructs the field objects that
 * are later attached to the vacuum volume.
 * 
 * @author Laurie Nevay
 */

class BDSMagnet: public BDSAcceleratorComponent
{
public:
  /// Magnet base class constructor that is for basic geometric information rather
  /// magnetic field details, which are handled in the derived classes
  BDSMagnet(BDSMagnetType       type,
	    G4String            name, 
	    G4double            length,
	    BDSBeamPipeInfo*    beamPipeInfo,
	    BDSMagnetOuterInfo* magnetOuterInfo,
	    BDSFieldInfo*       vacuumFieldInfoIn,
	    G4double            angle            = 0,
	    BDSFieldInfo*       outerFieldInfoIn = nullptr);
  
  virtual ~BDSMagnet();
  
  inline const BDSMagnetStrength* MagnetStrength() const {return vacuumFieldInfo->MagnetStrength();}

  /// @ { Delete existing field info and replace.
  void SetOuterField(BDSFieldInfo* outerFieldInfoIn);
  void SetVacuumField(BDSFieldInfo* vacuumFieldInfoIn);
  /// @}

  /// Determine which is the appropriate key to query a BDSMagnetStrength with for
  /// a given type of magnet.
  static G4String DetermineScalingKey(BDSMagnetType typeIn);
  
protected:
  /// Private default constructor to force the use of the supplied one.
  BDSMagnet() = delete;

  /// @{ Assignment and copy constructor not implemented nor used
  BDSMagnet& operator=(const BDSMagnet&) = delete;
  BDSMagnet(BDSMagnet&) = delete;
  /// @}
  
  /// Overridden method of BDSAcceleratorComponent to not only build container, but
  /// first construct field objects. After using BDSAcceleratorComponent::Build() to
  /// build the container, the beam pipe and outer geometry are built.
  virtual void Build();
  
  /// Construct a general straight piece of beampipe. Virtual so it can be overloaded
  /// by derived classes as required - such as RBend.
  virtual void BuildBeampipe();

  /// Construct the field for the vacuum and attach it
  virtual void BuildVacuumField();

  /// Construct the outer magnet geometry beit poled geometry or cylinders. This
  /// function switches on the member variable of BDSMagnetType type, so is contained in
  /// the base class.
  virtual void BuildOuter();
  
  /// Construct the magnetic field for the outer magnet geometry.
  virtual void BuildOuterField();

  /// Necessary to provide this function a la BDSAcceleratorComponent. If there's an
  /// outer geometry, the containerSolid will have been set and build it into a logical
  /// volume. If no outer geometry, use the beam pipe container as this objects container
  /// in which case no need to build any logical volumes. Update extents if necessary. 
  virtual void BuildContainerLogicalVolume();

  /// Place the beam pipe and outer geometry in the overall container. If there's no outer
  /// geometry, then we don't need to place either as the beam pipe becomes the container.
  virtual void PlaceComponents();

  ///@{ normal vector for faces when preparing solids
  G4ThreeVector inputface;
  G4ThreeVector outputface;
  ///@}
  
  /// Magnet type
  BDSMagnetType magnetType;

  /// Model information for the outer volume construction
  BDSMagnetOuterInfo* magnetOuterInfo;

  /// Field information for vacuum field
  BDSFieldInfo* vacuumFieldInfo;

  /// Field information for outer magnetic field (optional)
  BDSFieldInfo* outerFieldInfo;
  
  /// The constructed beampipe
  BDSBeamPipe*    beampipe;

  /// In the case where there's no magnet outer geometry, we just use the beam pipe
  /// and therefore we don't need to place it again. Use this boolean to record that
  /// and decide upon it. Default = true.
  G4bool          placeBeamPipe;

  /// For outer volume construction
  G4double        outerDiameter;

  /// Separate variable for the container radius so it can be changed if
  /// required by specific magnet geometry.
  G4double        containerRadius;
  
  /// Displacement (if required - default 0,0,0) for specific magnet geometry. Allows
  /// derived classes to specify different geometry without having to override placement
  /// which is provided in base class.
  G4ThreeVector magnetOuterOffset;
  
  /// The assembled outer magnet geometry
  BDSMagnetOuter* outer;

  /// Used to pass the placement offset to the field so that it can be offset from the
  /// local coordinates of the solid appropriately.
  G4Transform3D beamPipePlacementTransform;
};

#endif
