#ifndef BDSVISMANAGER_H
#define BDSVISMANAGER_H 

#include "G4Types.hh"

/**
 * @brief The BDS Visualisation Manager
 * 
 * This class manages the visualisation.
 * Chosen not to inherit from G4Manager, but instead a wrapper around it.
 */

class BDSVisManager
{
public:
  BDSVisManager();

  /// start interactive mode
  void StartSession(G4int argc, char** argv);
};

#endif

