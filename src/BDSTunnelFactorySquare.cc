#include "BDSTunnelFactoryBase.hh"
#include "BDSTunnelFactorySquare.hh"
#include "BDSTunnelFactoryRectangular.hh"

#include "BDSDebug.hh"
#include "BDSTunnelInfo.hh"

#include "globals.hh"                 // geant4 globals / types

BDSTunnelFactorySquare* BDSTunnelFactorySquare::_instance = nullptr;

BDSTunnelFactorySquare* BDSTunnelFactorySquare::Instance()
{
  if (_instance == nullptr)
    {_instance = new BDSTunnelFactorySquare();}
  return _instance;
}

BDSTunnelFactorySquare::BDSTunnelFactorySquare()
{;}

BDSTunnelFactorySquare::~BDSTunnelFactorySquare()
{
  _instance = nullptr;
}

BDSTunnelSection* BDSTunnelFactorySquare::CreateTunnelSection(G4String    name,
							      G4double    length,
							      G4double    tunnelThickness,
							      G4double    tunnelSoilThickness,
							      G4Material* tunnelMaterial,
							      G4Material* tunnelSoilMaterial,
							      G4bool      tunnelFloor,
							      G4double    tunnelFloorOffset,
							      G4double    tunnel1,
							      G4double    /*tunnel2*/,
							      G4bool      visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // test input parameters - set global options as default if not specified
  TestInputParameters(length, tunnelThickness, tunnelSoilThickness, tunnelMaterial,
		      tunnelSoilMaterial, tunnelFloorOffset, tunnel1);
  return BDSTunnelFactoryRectangular::Instance()->CreateTunnelSection(name, length, tunnelThickness,
								      tunnelSoilThickness, tunnelMaterial,
								      tunnelSoilMaterial, tunnelFloor,
								      tunnelFloorOffset, tunnel1, tunnel1, visible);
}


BDSTunnelSection* BDSTunnelFactorySquare::CreateTunnelSectionAngled(G4String      name,
								    G4double      length,
								    G4ThreeVector inputFace,
								    G4ThreeVector outputFace,
								    G4double      tunnelThickness,
								    G4double      tunnelSoilThickness,
								    G4Material*   tunnelMaterial,
								    G4Material*   tunnelSoilMaterial,
								    G4bool        tunnelFloor,
								    G4double      tunnelFloorOffset,
								    G4double      tunnel1,
								    G4double      /*tunnel2*/,
								    G4bool        visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // test input parameters - set global options as default if not specified
  TestInputParameters(length, tunnelThickness, tunnelSoilThickness, tunnelMaterial,
		      tunnelSoilMaterial, tunnelFloorOffset, tunnel1);
  return BDSTunnelFactoryRectangular::Instance()->CreateTunnelSectionAngled(name, length, inputFace, outputFace,
									    tunnelThickness,
									    tunnelSoilThickness, tunnelMaterial,
									    tunnelSoilMaterial, tunnelFloor,
									    tunnelFloorOffset, tunnel1, tunnel1, visible);
}


/// functions below here are private to this particular factory
void BDSTunnelFactorySquare::TestInputParameters(G4double&    length,
						 G4double&    tunnelThickness,
						 G4double&    tunnelSoilThickness,
						 G4Material*& tunnelMaterial,
						 G4Material*& tunnelSoilMaterial,
						 G4double&    tunnelFloorOffset,
						 G4double&    tunnel1)
{
  CommontTestInputParameters(length, tunnelThickness, tunnelSoilThickness, tunnelMaterial, tunnelSoilMaterial);
  
  if (tunnelFloorOffset < 1e-10)
    {tunnelFloorOffset = defaultModel->floorOffset;}
  
  if (tunnel1 < 1e-10)
    {tunnel1 = defaultModel->aper1;}
}
