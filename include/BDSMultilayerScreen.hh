#ifndef BDSMULTILAYERSCREEN_H
#define BDSMULTILAYERSCREEN_H 

#include <map>
#include <vector>

#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4TwoVector.hh"
#include "G4ThreeVector.hh"

class G4LogicalVolume;
class G4PVPlacement;
class G4VSolid;

class BDSColourWheel;
class BDSScreenLayer;

/** 
 * @brief An accelerator component for diagnostics screens e.g. OTR. Screen inside beam pipe.
 *
 * @author Lawrence Deacon
 */

class BDSMultilayerScreen 
{
public:
  BDSMultilayerScreen(G4TwoVector xysize,
		      G4String    name);
  virtual ~BDSMultilayerScreen();

  /// Construct and add a screen layer.
  void AddScreenLayer(G4double thickness,
		      G4String material,
		      G4String name,
		      G4int    isSampler = 0,
		      G4double grooveWidth = 0,
		      G4double grooveSpatialFrequency = 0);
  /// Add a premade screen layer - retains ownership of layer.
  void AddScreenLayer(BDSScreenLayer* layer, G4int isSampler=0);

  /// Full size of screen in x,y,z.
  inline const G4ThreeVector& GetSize() const {return size;}
  /// Get a particular screen layer by index.
  inline BDSScreenLayer* ScreenLayer(G4int layer) {return screenLayers[layer];}
  /// Get a particular screen layer by name.
  BDSScreenLayer* ScreenLayer(G4String layerName);
  /// Get the last layer of the screen.
  BDSScreenLayer* LastLayer() const {return screenLayers.back();}
  /// Size of the screen.
  inline G4int NLayers() const {return (G4int)screenLayers.size();}

  /// Set a physical placement to member variable.
  inline void SetPhys(G4PVPlacement* physIn) {phys = physIn;}

  /// Construct container, compute dimensions then place layers.
  void Build();

  /// Place the member logical volume 'log' with a given transform in a given mother volume.
  virtual void Place(G4RotationMatrix* rot, G4ThreeVector pos, G4LogicalVolume* motherVol);

  /// Construct a reflective surface between two layers.
  void ReflectiveSurface(G4int layer1, G4int layer2);
  /// Construct a rough surface between two layers.
  void RoughSurface(G4int layer1, G4int layer2);

private:
  ///@{ Private default constructor to force use of provided one.
  BDSMultilayerScreen() = delete;
  BDSMultilayerScreen(const BDSMultilayerScreen&) = delete;
  BDSMultilayerScreen& operator=(const BDSMultilayerScreen&) = delete;
  ///@}
  /// Calculate the extent of the multilayer screen given all the layers.
  void ComputeDimensions();

  /// Build a container volume
  void BuildMotherVolume();

  /// Place each layer in order in the container volume.
  void PlaceLayers();
  
  G4TwoVector   xysize; ///< X,Y size of multilayer screen.
  G4String      name;   ///< Name of multilayer screen.
  G4ThreeVector size;   ///< Extent.

  /// @{ Geometrical objects:
  G4LogicalVolume* log;
  G4PVPlacement*   phys;
  G4VSolid*        solid;
  /// @}
  std::vector<BDSScreenLayer*>        screenLayers;     ///< Main storage of all layers.
  std::map<G4String, BDSScreenLayer*> screenLayerNames; ///< Map of names for looking up.
  std::vector<G4double> screenLayerZPos;///< Cache of calculated z locations for layers.

  /// Colour wheel that iterately supplies different colours - allows each layer to be
  /// clearly visualised.
  BDSColourWheel* colourWheel;
};

#endif
