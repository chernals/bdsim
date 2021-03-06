#ifndef BDSTUNNELBUILDER_H
#define BDSTUNNELBUILDER_H

#include "globals.hh" // geant4 types / globals

#include "BDSBeamline.hh"

/**
 * @brief A class that constructs tunnel segments around a beamline. 
 *
 * It uses a beam line instance - the flat beam line
 * and creates a new beam line of tunnel segments that can then be placed.
 * 
 * @author Laurie Nevay
 */

class BDSTunnelBuilder
{
public:
  BDSTunnelBuilder();
  ~BDSTunnelBuilder();

  /// Main function of class - use tunnel factories and builds sections
  /// of tunnel around the flat beamline (of accelerator components).
  /// Tunnel segments are placed in order in a new beamline instance,
  /// which is returned.
  BDSBeamline* BuildTunnelSections(const BDSBeamline* flatBeamLine);

private:
  /// Decide whether this is a good point to break the tunnel based on various cumulative
  /// parameters.
  G4bool BreakTunnel(G4double cumulativeLength,
		     G4double cumulativeAngle,
		     G4int    cumulativeNItems,
		     G4double cumulativeOffsetX,
		     G4double cumulativeOffsetY);

  /// Maximum distance tolerable that the beamline can deviate from the previous
  /// tunnel break point before another tunnel break point is made.
  G4double displacementTolerance;

  /// Maximum number of items before split.
  G4double maxItems;

  /// Maximum length before split.
  G4double maxLength;

  /// Maximum angle before split.
  G4double maxAngle;

  /// Minimum length to angle ratio to allow a split.
  G4double minLength;
};


#endif
