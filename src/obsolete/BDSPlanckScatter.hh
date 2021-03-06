#ifndef BDSPLANCKSCATTER_H
#define BDSPLANCKSCATTER_H

#include "G4ios.hh" 
#include "globals.hh"
#include "G4VEnergyLossProcess.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "BDSComptonEngine.hh"
#include "BDSPlanckEngine.hh"
 
class BDSPlanckScatter : public G4VEnergyLossProcess
{ 
  public:
 
     BDSPlanckScatter();
 
     ~BDSPlanckScatter();
     virtual void InitialiseEnergyLossProcess(const G4ParticleDefinition*, const G4ParticleDefinition*);
     virtual void PrintInfo();

     G4bool IsApplicable(const G4ParticleDefinition&);
     
     G4double GetMeanFreePath(const G4Track& track,
                              G4double previousStepSize,
                              G4ForceCondition* condition );
 
     G4VParticleChange *PostStepDoIt(const G4Track& track,         
                                     const G4Step&  step);                 

     inline void SetTemperature(G4double aTemperature);
     inline G4double GetTemperature();

  protected:

  //     virtual G4double SecondaryEnergyThreshold(size_t index);

  private:

  // assignment and copy constructor not implemented nor used
  BDSPlanckScatter & operator=(const BDSPlanckScatter &right);
  BDSPlanckScatter(const BDSPlanckScatter&);

  //     const std::vector<G4double>* secondaryEnergyCuts;

private:
    G4double itsTemperature;
    BDSComptonEngine* itsComptonEngine;
    BDSPlanckEngine* itsPlanckEngine;
    G4double itsPlanckMeanFreePath;     
};
inline G4bool BDSPlanckScatter::IsApplicable(
                            const G4ParticleDefinition& part)
{
   return(  (&part == G4Electron::Electron())
          ||(&part == G4Positron::Positron()) );
}
inline G4double BDSPlanckScatter::GetMeanFreePath(const G4Track&,
                                           G4double,
                                           G4ForceCondition* ForceCondition)
{  
*ForceCondition= NotForced ;
return itsPlanckMeanFreePath;
}
  

inline void BDSPlanckScatter::SetTemperature(G4double aTemperature)
{itsTemperature=aTemperature;}
inline G4double BDSPlanckScatter::GetTemperature()
{return itsTemperature;}

// inline G4double BDSPlanckScatter::SecondaryEnergyThreshold(size_t index)
// {
//   return (*secondaryEnergyCuts)[index];
// }

#endif
