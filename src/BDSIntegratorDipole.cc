#include "BDSDebug.hh"
#include "BDSIntegratorDipole.hh"
#include "BDSGlobalConstants.hh"
#include "BDSMagnetStrength.hh"
#include "BDSStep.hh"

#include <utility>
#include "globals.hh" // geant4 types / globals
#include "G4AffineTransform.hh"
#include "G4Mag_EqRhs.hh"
#include "G4ThreeVector.hh"


BDSIntegratorDipole::BDSIntegratorDipole(BDSMagnetStrength const*  strength,
					 G4double                  /*brho*/,
					 G4Mag_EqRhs*              eqOfMIn):
  BDSIntegratorMag(eqOfMIn, 6),
  angle((*strength)["angle"]),
  length((*strength)["length"]),
  bField((*strength)["field"]),
  minimumRadiusOfCurvature(BDSGlobalConstants::Instance()->MinimumRadiusOfCurvature())
{
  cOverGeV = BDSGlobalConstants::Instance()->COverGeV();

#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "B Field " << bField << G4endl;
#endif
}

void BDSIntegratorDipole::AdvanceHelix(const G4double yIn[],
				       const G4double dydx[],
				       G4double       h,
				       G4double       yOut[],
				       G4double       yErr[])
{
  // In case of zero field or neutral particles do a linear step:
  if(bField == 0 || eqOfM->FCof() == 0)
    {
      AdvanceDriftMag(yIn, h, yOut, yErr);
      SetDistChord(0);
      return;
    }
  
  // Construct variables
  G4ThreeVector pos = G4ThreeVector(yIn[0], yIn[1], yIn[2]);
  G4ThreeVector mom = G4ThreeVector(yIn[3], yIn[4], yIn[5]);
  G4double charge   = (eqOfM->FCof())/CLHEP::c_light;
  G4double momMag   = mom.mag();
  G4double rho = momMag/CLHEP::GeV/(cOverGeV * bField/CLHEP::tesla * charge) * CLHEP::m;

  if (std::abs(rho) < minimumRadiusOfCurvature)
    {
      AdvanceDriftMag(yIn, h, yOut, yErr);
      SetDistChord(0);
      return;
    }

  // global to local
  // false = use the mass world for the transform
  BDSStep       localPosMom         = ConvertToLocal(pos, mom, h, false);
  G4ThreeVector localMom            = localPosMom.PostStepPoint();
  G4ThreeVector localMomUnit        = localMom.unit();

  // check for paraxial approximation:
  if(localMomUnit.z() < 0.9)
    {// use a classical Runge Kutta stepper here
      backupStepper->Stepper(yIn, dydx, h, yOut, yErr);
      SetDistChord(backupStepper->DistChord());
      return;
    }

  G4ThreeVector localPos            = localPosMom.PreStepPoint();
  G4ThreeVector initialLocalPos     = localPos;
  G4ThreeVector intiialLocalMomUnit = localMomUnit;
  
  // advance the orbit
  std::pair<G4ThreeVector,G4ThreeVector> RandRp = UpdatePandR(rho,h,localPos,localMomUnit);
  G4ThreeVector outputLocalPos = RandRp.first;
  G4ThreeVector outputLocalMomUnit = RandRp.second;
  
  G4double CosT_ov_2=cos(h/rho/2.0);
  G4double dc = std::abs(rho)*(1.-CosT_ov_2);
  if (std::isnan(dc))
    {SetDistChord(rho);}
  else
    {SetDistChord(dc);}
  
  // This uses the mass world volume for the transform!
  ConvertToGlobal(outputLocalPos, outputLocalMomUnit, yOut, momMag);
  
  // If the radius of curvature is too small, reduce the momentum by 2%. This will
  // cause artificial spiralling for what must be particles well below the design momenta.
  // Nominally adding a small z increment along the axis of the helix wasn't reliable,
  // as there can be inconsistencies in the field vectors resulting in 0 additional offset,
  // plus Geant4 complained about clearly wrong motion. This way works and produces no
  // errors.  The particle would be lost approximately in the current location anyway.
  if (std::abs(rho) < minimumRadiusOfCurvature)
    {
      G4double momentumReduction = 0.98;
      yOut[3] *= momentumReduction;
      yOut[4] *= momentumReduction;
      yOut[5] *= momentumReduction;
    }
  return;
}

void BDSIntegratorDipole::Stepper(const G4double yIn[],
				  const G4double dydx[],
				  const G4double h,
				  G4double       yOut[],
				  G4double       yErr[])
{
  G4double err = 1e-10 * h; // very small linear increase with distance
  for(G4int i = 0; i < nVariables; i++)
    {yErr[i] = err;}

  AdvanceHelix(yIn, dydx, h, yOut, yErr);
}

std::pair<G4ThreeVector,G4ThreeVector> BDSIntegratorDipole::UpdatePandR(G4double      rho,
									G4double      h,
									G4ThreeVector localPos,
									G4ThreeVector localMomUnit)
{
  G4ThreeVector yhat(0.,1.,0.);
  G4ThreeVector vhat  = localMomUnit;
  G4ThreeVector vnorm = vhat.cross(yhat);
    
  G4double Theta = h/rho;

  G4double CosT_ov_2, SinT_ov_2, CosT, SinT;
  CosT_ov_2 = cos(Theta/2);
  SinT_ov_2 = sin(Theta/2);
  
  CosT = (CosT_ov_2*CosT_ov_2) - (SinT_ov_2*SinT_ov_2);
  SinT = 2*CosT_ov_2*SinT_ov_2;

  G4ThreeVector dPos = rho*(SinT*vhat + (1-CosT)*vnorm); // missing component parallel to B
  G4ThreeVector outputLocalPos     = localPos+dPos;
  G4ThreeVector outputLocalMomUnit = CosT*vhat + SinT*vnorm;
  
  return std::make_pair(outputLocalPos,outputLocalMomUnit);
}
