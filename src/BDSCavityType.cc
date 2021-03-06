#include "BDSCavityType.hh"
#include "BDSDebug.hh"

#include <map>
#include <string>

// dictionary for BDSCavityType
template<>
std::map<BDSCavityType, std::string>* BDSCavityType::dictionary =
  new std::map<BDSCavityType, std::string> ({
  {BDSCavityType::elliptical,  "elliptical"},
  {BDSCavityType::rectangular, "rectangular"},
  {BDSCavityType::pillbox,     "pillbox"}
});

BDSCavityType BDS::DetermineCavityType(G4String cavityType)
{
  std::map<G4String, BDSCavityType> types;
  types["elliptical"]  = BDSCavityType::elliptical;
  types["rectangular"] = BDSCavityType::rectangular;
  types["pillbox"]     = BDSCavityType::pillbox;
  
  cavityType.toLower();

  auto result = types.find(cavityType);
  if (result == types.end())
    {
      // it's not a valid key
      G4cout << __METHOD_NAME__ << "\"" << cavityType << "\" is not a valid cavity type" << G4endl;
      G4cout << "Available cavity types are:" << G4endl;
      for (auto it : types)
	{G4cout << "\"" << it.first << "\"" << G4endl;}
      exit(1);
    }
  
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " determined cavity type to be " << result->second << G4endl;
#endif
  return result->second;
}
