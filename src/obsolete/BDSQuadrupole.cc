#include "BDSBeamPipeInfo.hh"
#include "BDSDebug.hh"
#include "BDSGlobalConstants.hh" 
#include "BDSMagnetType.hh"
#include "BDSMagnetOuterInfo.hh"
#include "BDSQuadrupole.hh"
#include "BDSQuadMagField.hh"
#include "BDSQuadStepper.hh"

#include "G4Mag_UsualEqRhs.hh"

BDSQuadrupole::BDSQuadrupole(G4String            name,
			     G4double            length,
			     G4double            bGrad,
			     BDSBeamPipeInfo*    beamPipeInfo,
			     BDSMagnetOuterInfo* magnetOuterInfo):
  BDSMagnet(BDSMagnetType::quadrupole, name, length,
	    beamPipeInfo, magnetOuterInfo),
  itsBGrad(bGrad)
{;}

void BDSQuadrupole::Build() 
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  BDSMagnet::Build();
  
  if(BDSGlobalConstants::Instance()->IncludeIronMagFields())
    {
      G4double polePos[4];
      G4double Bfield[3];
      
      //coordinate in GetFieldValue
      polePos[0]=-BDSGlobalConstants::Instance()->MagnetPoleRadius()*sin(CLHEP::pi/4);
      polePos[1]= BDSGlobalConstants::Instance()->MagnetPoleRadius()*cos(CLHEP::pi/4);
      polePos[2]=0.;
      polePos[3]=-999.;//flag to use polePos rather than local track
      
      itsMagField->GetFieldValue(polePos,Bfield);
      G4double BFldIron=
	sqrt(Bfield[0]*Bfield[0]+Bfield[1]*Bfield[1])*
            BDSGlobalConstants::Instance()->MagnetPoleSize()/
	(BDSGlobalConstants::Instance()->ComponentBoxSize()/2-
            BDSGlobalConstants::Instance()->MagnetPoleRadius());
      
      // Magnetic flux from a pole is divided in two directions
      BFldIron/=2.;
      
      BuildOuterFieldManager(4, BFldIron,CLHEP::pi/4);
    }
}

void BDSQuadrupole::BuildBPFieldAndStepper()
{
  // set up the magnetic field and stepper
  itsMagField = new BDSQuadMagField(1*itsBGrad); //L Deacon checking sign of field 4/7/12
  itsEqRhs    = new G4Mag_UsualEqRhs(itsMagField);
  BDSQuadStepper* quadStepper = new BDSQuadStepper(itsEqRhs);
  quadStepper->SetBGrad(itsBGrad);
  itsStepper = quadStepper;
}
