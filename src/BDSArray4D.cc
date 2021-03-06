#include "BDSArray4D.hh"
#include "BDSFieldValue.hh"

#include "globals.hh" // geant4 types / globals

#include <ostream>
#include <vector>


BDSArray4D::BDSArray4D(G4int nXIn, G4int nYIn, G4int nZIn, G4int nTIn):
  nX(nXIn), nY(nYIn), nZ(nZIn), nT(nTIn),
  defaultValue(BDSFieldValue()),
  data(std::vector<BDSFieldValue>(nTIn*nZIn*nYIn*nXIn))
{;}

BDSFieldValue& BDSArray4D::operator()(const G4int x,
				      const G4int y,
				      const G4int z,
				      const G4int t)
{
  OutsideWarn(x,y,z,t); // keep as a warning as can't assign to invalid index
  return data[t*nZ*nY*nX + z*nY*nX + y*nX + x];
}

const BDSFieldValue& BDSArray4D::GetConst(const G4int x,
					  const G4int y,
					  const G4int z,
					  const G4int t) const
{
  if (Outside(x,y,z,t))
    {return defaultValue;}
  return data[t*nZ*nY*nX + z*nY*nX + y*nX + x];
}
  
const BDSFieldValue& BDSArray4D::operator()(const G4int x,
					    const G4int y,
					    const G4int z,
					    const G4int t) const
{
  return GetConst(x,y,z,t);
}

G4bool BDSArray4D::Outside(const G4int x,
			   const G4int y,
			   const G4int z,
			   const G4int t) const
{
  G4bool rx = x < 0 || x > nX-1;
  G4bool ry = y < 0 || y > nY-1;
  G4bool rz = z < 0 || z > nZ-1;
  G4bool rt = t < 0 || t > nT-1;
  return rx || ry || rz || rt;
}

void BDSArray4D::OutsideWarn(const G4int x,
			     const G4int y,
			     const G4int z,
			     const G4int t) const
{
  if (Outside(x,y,z,t))
    {
      G4cerr << "(" << x << ", " << y << ", " << z << ", " << t
	     << ") is outside array" << G4endl;
      exit(1);
    }
}

std::ostream& BDSArray4D::Print(std::ostream& out) const
{
  out << "#x = " << nX << ", ";
  out << "#y = " << nY << ", ";
  out << "#z = " << nZ << ", ";
  out << "#t = " << nT << G4endl;
  
  for (G4int t = 0; t < nT; t++)
    {
      for (G4int z = 0; z < nZ; z++)
	{
	  for (G4int y = 0; y < nY; y++)
	    {
	      for (G4int x = 0; x < nX; x++)
		{out << BDSArray4D::GetConst(x,y,z,t) << G4endl;}
	    }
	}
    }
  return out;
}

std::ostream& operator<< (std::ostream& out, BDSArray4D const &a)
{
  return a.Print(out);
}
