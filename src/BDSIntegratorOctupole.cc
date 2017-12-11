#include "BDSDebug.hh"
#include "BDSIntegratorOctupole.hh"
#include "BDSMagnetStrength.hh"
#include "BDSStep.hh"

#include "G4Mag_EqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ThreeVector.hh"

#include "CLHEP/Units/SystemOfUnits.h"

#include <cmath>

BDSIntegratorOctupole::BDSIntegratorOctupole(BDSMagnetStrength const* strength,
					     G4double                 brho,
					     G4Mag_EqRhs*             eqOfMIn):
  BDSIntegratorEulerOld(eqOfMIn)
{
  // B''' = d^3By/dx^3 = Brho * (1/Brho d^3By/dx^3) = Brho * k3
  bTriplePrime = brho * (*strength)["k3"] / (CLHEP::m3*CLHEP::m);
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "B''' = " << bTriplePrime << G4endl;
#endif
}

void BDSIntegratorOctupole::AdvanceHelix(const G4double  yIn[],
					 G4double        h,
					 G4double        yOut[])
{
  G4ThreeVector mom = G4ThreeVector(yIn[3], yIn[4], yIn[5]);
  G4double momMag   = mom.mag();
  G4double kappa    = -eqOfM->FCof()*bTriplePrime / momMag;
  
  if(std::abs(kappa) < 1e-20)
    {
      AdvanceDriftMag(yIn, h, yOut);
      SetDistChord(0);
      return;
    }
  
  G4ThreeVector pos          = G4ThreeVector(yIn[0], yIn[1], yIn[2]);
  BDSStep       localPosMom  = ConvertToLocal(pos, mom, h, false);
  G4ThreeVector localPos     = localPosMom.PreStepPoint();
  G4ThreeVector localMom     = localPosMom.PostStepPoint();
  G4ThreeVector localMomUnit = localMom.unit();
  
  G4double x0 = localPos.x();
  G4double y0 = localPos.y();

  // Evaluate field at the approximate midpoint of the step.
  const G4double halfH = 0.5*h;
  x0 = x0 + localMomUnit.x()*halfH;
  y0 = y0 + localMomUnit.y()*halfH;
  
  G4double xp = localMomUnit.x();
  G4double yp = localMomUnit.y();
  G4double zp = localMomUnit.z();
  
  G4double y3fac = y0*(y0*y0 - 3*x0*x0);
  G4double x3fac = x0*(x0*x0 - 3*y0*y0);
  
  // local r'' (for curvature)
  G4ThreeVector localA;
  localA.setX(-zp*x3fac);
  localA.setY(-zp*y3fac);
  localA.setZ( xp*x3fac + yp*y3fac);
  
  localA *= kappa / 6; // 6 is actually a 3! factor.;
  
  AdvanceChord(h,localPos,localMomUnit,localA);
  ConvertToGlobal(localPos, localMomUnit, yOut, momMag);
}