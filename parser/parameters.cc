#include "parameters.h"

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>

#include "array.h"

using namespace GMAD;

Parameters::Parameters()
{
  // fill setMap, needs to match published member names
  // usually same but some exceptions, those are commented
  setMap["l"]     = false;
  setMap["ks"]    = false;
  setMap["k1"]    = false;
  setMap["k2"]    = false;
  setMap["k3"]    = false;
  setMap["k4"]    = false;
  setMap["angle"] = false;
  setMap["B"]     = false;
  setMap["e1"]    = false;
  setMap["e2"]    = false;
  setMap["fint"]  = false;
  setMap["fintx"] = false;
  setMap["hgap"]  = false;
  setMap["kick"]  = false;
  setMap["hkick"] = false;
  setMap["vkick"] = false;
  setMap["knl"]   = false;
  setMap["ksl"]   = false;
  setMap["gradient"]  = false;
  setMap["E"]         = false;
  setMap["frequency"] = false;
  setMap["phase"]     = false;
  setMap["tOffset"]   = false;
  
  setMap["beampipeThickness"] = false;
  setMap["aper1"] = false;
  setMap["aper2"] = false;
  setMap["aper3"] = false;
  setMap["aper4"] = false;
  setMap["apertureType"] = false;
  setMap["beampipeMaterial"] = false;
  setMap["vacuumMaterial"] = false;
  setMap["magnetGeometryType"] = false;
  setMap["outerMaterial"] = false;
  setMap["outerDiameter"] = false;
  setMap["yokeOnInside"]  = false;
  setMap["tilt"] = false;
  setMap["xsize"] = false;
  setMap["ysize"] = false;
  setMap["xsizeOut"] = false;
  setMap["ysizeOut"] = false;
  setMap["offsetX"] = false;
  setMap["offsetY"] = false;
  setMap["tscint"] = false;
  setMap["twindow"] = false;
  setMap["tmount"] = false;
  setMap["windowScreenGap"] = false;
  setMap["screenXSize"] = false;
  setMap["screenYSize"] = false;
  setMap["screenPSize"] = false;
  setMap["screenEndZ"] = false;
  setMap["poleStartZ"] = false;
  setMap["screenWidth"] = false;
  setMap["awakeMagnetOffsetX"] = false;
  setMap["layerThicknesses"] = false;
  setMap["layerMaterials"] = false;
  setMap["layerIsSampler"] = false;
  setMap["xdir"] = false;
  setMap["ydir"] = false;
  setMap["zdir"] = false; 
  setMap["waveLength"] = false;
  setMap["gradient"] = false;
  setMap["phi"] = false;
  setMap["theta"] = false;
  setMap["psi"] = false;
  setMap["blmLocZ"] = false;  setMap["blmLocTheta"] = false;
  setMap["bias"] = false, setMap["biasMaterial"] = false, setMap["biasVacuum"] = false;
  setMap["samplerName"] = false;
  setMap["samplerType"] = false;
  setMap["samplerRadius"] = false;
  setMap["region"] = false;
  setMap["fieldOuter"]  = false;
  setMap["fieldVacuum"] = false;
  setMap["fieldAll"]    = false;

  setMap["geometry"] = false; // for geometryFile
  setMap["material"] = false;
  setMap["scintmaterial"] = false;
  setMap["windowmaterial"] = false;
  setMap["mountmaterial"] = false;
  setMap["spec"] = false;
  setMap["cavityModel"] = false;

  setMap["numberWedges"] = false;
  setMap["wedgeLength"] = false;
  setMap["degraderHeight"] = false;
  setMap["materialThickness"] = false;
  setMap["degraderOffset"] = false;

  setMap["colour"] = false;
}

void Parameters::flush() {

  Element::flush();

  for (auto& i : setMap)
    {
      i.second = false;
    }
}

void Parameters::inherit_properties(const Element& e)
{
  // copy parameters into temporary buffer params from element e
  // parameters already set in params have priority and are not overridden
  // this is used for the inheritance / newinstance mechanism

  for (auto& i : setMap)
    {
      if(i.second == false)
	{
	  std::string property = i.first;
          // method can in theory throw runtime_error (shouldn't happen), catch and exit gracefully
	  try {
	    Published<Element>::set(this,(Element*)&e,property);
	  }
	  catch(std::runtime_error) {
	    std::cerr << "Error: element> unknown property \"" << property << "\" from element " << e.name  << std::endl;
	    exit(1);
	  }
	  
	  i.second = true;
	}
    }
}

// template specialisation for Array pointers, to be merged into templated function
void Parameters::set_value(std::string property, Array* value)
{
#ifdef BDSDEBUG
  std::cout << "element> Setting value " << std::setw(25) << std::left << property << std::endl;
#endif
  if(property=="knl") 
    {
      value->set_vector(knl);
    } 
  else if(property=="ksl") 
    {
      value->set_vector(ksl);
    }
  else if(property=="blmLocZ") 
    {
      value->set_vector(blmLocZ);
    }
  else if(property=="blmLocTheta") 
    {
      value->set_vector(blmLocTheta);
    }
  else if(property=="layerThicknesses")
    {
      value->set_vector(layerThicknesses);
    }
  else if(property=="layerMaterials")
    {
      value->set_vector(layerMaterials);
    }
  else if(property=="layerIsSampler")
    {
      value->set_vector(layerIsSampler);
    }
  else
    {
      std::cerr << "Error: element> unknown parameter option \"" << property << "\", or doesn't expect vector type" << std::endl;
      // don't exit here, but flag willExit instead
      //exit(1);
      willExit = true;
      return;
    }

  setMap.at(property) = true;
}
