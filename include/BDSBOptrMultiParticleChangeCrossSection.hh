#ifndef BDSBOPTRMULTIPARTICLECHANGECROSSSECTION_H
#define BDSBOPTRMULTIPARTICLECHANGECROSSSECTION_H

#include "G4Version.hh"
#if G4VERSION_NUMBER > 1009

#include "G4VBiasingOperator.hh"
class BDSBOptrChangeCrossSection;
class G4ParticleDefinition; 

#include <map>

/**
 * @brief Multi-particle cross-section changer.
 *
 * This class uses classes from Geant4 10.0 and is dependent on 
 * BDSBOptChangeCrossSection which needs 10.1.
 *
 * Largely based on the Geant4 example of this feature.
 *
 * @author Stewar Boogert
 */

class BDSBOptrMultiParticleChangeCrossSection: public G4VBiasingOperator
{
public:
  BDSBOptrMultiParticleChangeCrossSection();
  virtual ~BDSBOptrMultiParticleChangeCrossSection();
  
  void AddParticle(G4String particleName);
  void SetBias(G4String particleName, G4String process, G4double dBias, G4int iPrimary);
  void StartTracking( const G4Track* track ) override;

private: 
  virtual G4VBiasingOperation* ProposeOccurenceBiasingOperation(const G4Track*                   track,
								const G4BiasingProcessInterface* callingProcess) override;
  // -- Methods not used:
  virtual G4VBiasingOperation* ProposeFinalStateBiasingOperation(const G4Track*, const G4BiasingProcessInterface*) override
  {return 0;}
  virtual G4VBiasingOperation* ProposeNonPhysicsBiasingOperation(const G4Track*, const G4BiasingProcessInterface*) override
  {return 0;}
  virtual void OperationApplied(const G4BiasingProcessInterface* callingProcess,
				G4BiasingAppliedCase             biasingCase,
 				G4VBiasingOperation*             occurenceOperationApplied,
				G4double                         weightForOccurenceInteraction,
				G4VBiasingOperation*             finalStateOperationApplied, 
				const G4VParticleChange*         particleChangeProduced) override;
  // prevent compiler warning (since second G4VBiasingOperator::OperationApplied is hidden)
  using G4VBiasingOperator::OperationApplied;
  std::map<const G4ParticleDefinition*, BDSBOptrChangeCrossSection*> fBOptrForParticle;
  std::vector<const G4ParticleDefinition*>                           fParticlesToBias;
  BDSBOptrChangeCrossSection*                                        fCurrentOperator;

  // -- count number of biased interations for current track:
  G4int fnInteractions = 0;  

  G4bool debug;
};

#endif

#endif
