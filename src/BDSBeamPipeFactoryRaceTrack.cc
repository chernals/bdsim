#include "BDSBeamPipeFactoryRaceTrack.hh"
#include "BDSBeamPipeFactoryPoints.hh"
#include "BDSDebug.hh"

#include "globals.hh"                 // geant4 globals / types
#include "G4TwoVector.hh"

#include <cmath>


BDSBeamPipeFactoryRaceTrack* BDSBeamPipeFactoryRaceTrack::instance = nullptr;

BDSBeamPipeFactoryRaceTrack* BDSBeamPipeFactoryRaceTrack::Instance()
{
  if (instance == nullptr)
    {instance = new BDSBeamPipeFactoryRaceTrack();}
  return instance;
}

BDSBeamPipeFactoryRaceTrack::BDSBeamPipeFactoryRaceTrack()
{;}

BDSBeamPipeFactoryRaceTrack::~BDSBeamPipeFactoryRaceTrack()
{
  instance = nullptr;
}

void BDSBeamPipeFactoryRaceTrack::GenerateRaceTrack(std::vector<G4TwoVector>& vec,
						    G4double x,
						    G4double y,
						    G4double r,
						    G4int    pointsPerTwoPi)
{
  G4int pointsPerCurve = pointsPerTwoPi / 4;
  AppendAngle(vec, 0,             0.5*CLHEP::pi,     r, pointsPerCurve, x, y);
  AppendPoint(vec, x+r, y);
  AppendAngle(vec, 0.5*CLHEP::pi, CLHEP::pi,         r, pointsPerCurve, x, -y);
  AppendPoint(vec, x, -y-r);
  AppendAngle(vec, CLHEP::pi,     (3./2.)*CLHEP::pi, r, pointsPerCurve, -x, -y);
  AppendPoint(vec, -x-r, -y);
  AppendAngle(vec, (3./2)*CLHEP::pi, CLHEP::twopi,   r, pointsPerCurve, -x, y);
  AppendPoint(vec, -x, y+r);
}
						    

void BDSBeamPipeFactoryRaceTrack::GeneratePoints(G4double aper1,
						 G4double aper2,
						 G4double aper3,
						 G4double /*aper4*/,
						 G4double beamPipeThickness,
						 G4int    pointsPerTwoPi)
{
  GenerateRaceTrack(vacuumEdge, aper1, aper2, aper3, pointsPerTwoPi);
  G4double bpInner1 = aper1 + lengthSafety;
  G4double bpInner2 = aper2 + lengthSafety;
  G4double bpInner3 = aper3 + lengthSafety;
  GenerateRaceTrack(beamPipeInnerEdge, bpInner1, bpInner2, bpInner3, pointsPerTwoPi);
  G4double bpOuter1 = aper1 + beamPipeThickness;
  G4double bpOuter2 = aper2 + beamPipeThickness;
  G4double bpOuter3 = aper3 + beamPipeThickness;
  GenerateRaceTrack(beamPipeOuterEdge, bpOuter1, bpOuter2, bpOuter3, pointsPerTwoPi);
  G4double cont1 = bpOuter1 + lengthSafetyLarge;
  G4double cont2 = bpOuter2 + lengthSafetyLarge;
  G4double cont3 = bpOuter3 + lengthSafetyLarge;
  GenerateRaceTrack(containerEdge, cont1, cont2, cont3, pointsPerTwoPi);
  G4double contSub1 = cont1 + lengthSafetyLarge;
  G4double contSub2 = cont2 + lengthSafetyLarge;
  G4double contSub3 = cont3 + lengthSafetyLarge;
  GenerateRaceTrack(containerSubtractionEdge, contSub1, contSub2, contSub3, pointsPerTwoPi);
}

G4double BDSBeamPipeFactoryRaceTrack::CalculateIntersectionRadius(G4double aper1,
								  G4double aper2,
								  G4double aper3,
								  G4double /*aper4*/,
								  G4double beamPipeThickness)
{
  G4double result = std::hypot(aper1,aper2) + aper3 + beamPipeThickness;
  result *= 1.5; // 10% margin is just enough
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "intersection radius: " << result << G4endl;
#endif
  return result;
}
