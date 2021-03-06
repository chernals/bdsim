#include "BDSScreenLayer.hh"

#include "BDSDebug.hh"
#include "BDSGlobalConstants.hh" 
#include "BDSMaterials.hh"
#include "BDSSamplerRegistry.hh"
#include "BDSSamplerSD.hh"
#include "BDSSDManager.hh"
#include "BDSUtilities.hh"

#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4VSolid.hh"

BDSScreenLayer::BDSScreenLayer()
{}

BDSScreenLayer::BDSScreenLayer(G4ThreeVector sizeIn,
			       G4String nameIn,
			       G4String materialIn, 
			       G4double grooveWidthIn,
			       G4double grooveSpatialFrequencyIn):
  size(sizeIn),
  name(nameIn),
  material(materialIn),
  grooveWidth(grooveWidthIn),
  grooveSpatialFrequency(grooveSpatialFrequencyIn)
{
  if (!BDS::IsFinite(size.z()))
    {G4cerr << __METHOD_NAME__ << "Insufficent length for screen layer \"" << name << "\"" << G4endl; exit(1);}
  colour=G4Colour(0.1,0.8,0.1,0.3);
  Build();
}

void BDSScreenLayer::Build()
{
  BuildGroove();
  BuildScreen();
  SetVisAttributes();
}

void BDSScreenLayer::BuildGroove()
{
  //There may or may not be grooves in the screen layer.
  if (!BDS::IsFinite(grooveWidth))
    {return;}
    
  grooveSolid = new G4Box((name+"_grooveSolid").c_str(),
			  grooveWidth/2.0,
			  size.y()/2.0,
			  size.z()/2.0);
  grooveLog = new G4LogicalVolume(grooveSolid,
				  BDSMaterials::Instance()->GetMaterial("air"),
				  (name+"_grooveLog").c_str());
}

void BDSScreenLayer::BuildScreen()
{
  //A small safety length to separate the screen layers.
  G4double tinyLenSaf = 1e-3*CLHEP::nm;
  solid  = new G4Box((name+"_solid").c_str(),
		     size.x()/2.0,
		     size.y()/2.0,
		     size.z()/2.0-tinyLenSaf);
  log = new G4LogicalVolume(solid,
			    BDSMaterials::Instance()->GetMaterial(material),
			    (name+"_log").c_str());
  CutGrooves();
    
  log->SetUserLimits(BDSGlobalConstants::Instance()->GetDefaultUserLimits());
}

void BDSScreenLayer::CutGrooves()
{
  if(grooveWidth>0)
    {
      for(G4double xPosition=-size.x()/2.0+grooveWidth/2.0;
	  xPosition<((size.x()/2.0)-grooveWidth/2.0);
	  xPosition+=grooveSpatialFrequency)
	{ CutGroove(xPosition);}
    }
}

void BDSScreenLayer::CutGroove(G4double xPosition)
{
  if (!grooveLog)
    {return;}
  G4ThreeVector pos(xPosition, 0, 0);
  
  //Create a new physical volume placement for each groove in the screen.
  new G4PVPlacement(nullptr,
		    pos,
		    grooveLog,
		    (G4String)(name+"_groove"),
		    log,
		    true,
		    nGrooves,
		    false);
  
  nGrooves++; //Increment the counter for the number of grooves in the screen.
}

void BDSScreenLayer::SetVisAttributes()
{
  G4VisAttributes* visAtt=new G4VisAttributes(colour);
  visAtt->SetForceSolid(true);
  G4VisAttributes* visAttGroove=new G4VisAttributes(G4Colour(0.0,0.0,0.0));
  visAttGroove->SetForceSolid(true);
  log->SetVisAttributes(visAtt);
  if(grooveLog)
    {grooveLog->SetVisAttributes(visAttGroove);}
}

void BDSScreenLayer::SetPhys(G4PVPlacement* physIn)
{
  if(physIn->GetLogicalVolume() != GetLog())
    {
      G4cerr << "BDSScreenLayer - error: physical volume placement does not match logical volume. Exiting." << G4endl;
      exit(1);
    }
  phys=physIn;
}

void BDSScreenLayer::SetColour(G4Colour col)
{
  colour=col;
  SetVisAttributes();
}


void BDSScreenLayer::AssignSampler()
{
  G4String samplerName = name;
  log->SetSensitiveDetector(BDSSDManager::Instance()->GetSamplerPlaneSD());
  samplerID=BDSSamplerRegistry::Instance()->RegisterSampler(samplerName,nullptr);
  log->SetUserLimits(BDSGlobalConstants::Instance()->GetDefaultUserLimits());
}

/*
void BDSScreenLayer::backInternalMirror()
{
  internalMirror = new InternalMirror(InternalMirror::BACK, size,material,log,phys);
}

void BDSScreenLayer::frontInternalMirror()
{
  internalMirror = new InternalMirror(InternalMirror::FRONT,size,material,log,phys);
}

BDSScreenLayer::InternalMirror::~InternalMirror()
{;}

BDSScreenLayer::InternalMirror::InternalMirror(G4int varsideIn,
					       G4ThreeVector sizeIn,
					       G4String materialIn,
					       G4LogicalVolume* motherLogIn,
					       G4PVPlacement* motherPhysIn):
  side(varsideIn),
  motherSize(sizeIn),
  motherMaterial(materialIn),
  motherLog(motherLogIn),
  motherPhys(motherPhysIn)
{
  thickness=1e-9*CLHEP::m; 
  compute();
  geom();
  place();
  optical();
}

void BDSScreenLayer::InternalMirror::geom()
{
	G4double tinyLenSaf = 1e-6*CLHEP::nm;
  solid = new G4Box("internalMirrorSolid",
		    motherSize.x()/2.0,
		    motherSize.y()/2.0,
		    thickness - tinyLenSaf);
  log = new G4LogicalVolume(solid,
			    BDSMaterials::Instance()->GetMaterial("titanium"),
			    "internalMirrorLog");
}

void BDSScreenLayer::InternalMirror::place()
{
  phys=new G4PVPlacement(nullptr,  //Create a new physical volume placement for each groove in the screen.
			 G4ThreeVector(0,0,pos),
			 log,
			 "internalMirrorPhys",
			 motherLog,
			 false,
			 0,
			 true);
}

void BDSScreenLayer::InternalMirror::optical()
{
  G4OpticalSurface* OpSurface=new G4OpticalSurface("OpSurface");
  //G4LogicalBorderSurface* LogSurface = 
  new G4LogicalBorderSurface("LogSurface", motherPhys, phys, OpSurface);
  //  G4LogicalSkinSurface* LogSurface  = new G4LogicalSkinSurface("LogSurface",screenLayer(1)->log(),OpSurface);
  OpSurface->SetType(dielectric_metal);
  OpSurface->SetModel(unified);
  OpSurface->SetFinish(polished);
  G4MaterialPropertiesTable* SMPT = new G4MaterialPropertiesTable();
  SMPT->AddConstProperty("REFLECTIVITY",0.8);
  //  SMPT->AddConstProperty("RINDEX",1.5750);
  OpSurface->SetMaterialPropertiesTable(SMPT);
}

void BDSScreenLayer::InternalMirror::compute()
{
  G4double sign=0;
  try{
    if(side==BACK){
      sign = 1;
    }else if(side==FRONT){
      sign = -1;
    }else{
      throw 1;
    }
  }catch(int e){
    G4cerr<< "BDSScreenLayer::computInternalMirror - exception number " << e << " occurred. Exiting." << G4endl;
    exit(e);
  }
  
  pos = sign*(motherSize.z()/2.0-thickness/2.0);
}
*/