#ifndef BDSGEOMETRYWRITER_H
#define BDSGEOMETRYWRITER_H

#include "globals.hh" // geant4 types / globals

class G4VPhysicalVolume;

/**
 * @brief A class for writing fully constructed geometry from BDSIM
 * out to other formats.
 * 
 * @author Laurie Nevay
 */

class BDSGeometryWriter
{
public:
  BDSGeometryWriter();
  ~BDSGeometryWriter();

  /// Dispatch function that matchest the geometry type and uses the appropraite
  /// member function to write out the geometry
  void ExportGeometry(G4String geometryType,
		      G4String geometryFileName);

private:

#ifdef USE_GDML
  /// Write the geometry to specified output filename. The filename should
  /// be the filename ending in .gdml. If the supplied volume is nullptr (default),
  /// the world volume will be written out.
  void WriteToGDML(G4String outputFileName, G4VPhysicalVolume* volume = nullptr);
#endif
};

#endif
