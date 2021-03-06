#include "BDSTunnelBuilder.hh"

#include "BDSBeamline.hh"
#include "BDSBeamlineElement.hh"
#include "BDSDebug.hh"
#include "BDSGlobalConstants.hh"
#include "BDSTiltOffset.hh"
#include "BDSTunnelFactory.hh"
#include "BDSTunnelInfo.hh"
#include "BDSTunnelSection.hh"
#include "BDSUtilities.hh"  // for isfinite function

#include "globals.hh"

BDSTunnelBuilder::BDSTunnelBuilder()
{
  displacementTolerance = 50 * CLHEP::cm;    // maximum displacemenet of beamline before split
  maxItems              = 50;                // maximum number of items before split
  maxLength             = 50 * CLHEP::m;     // maximum length of tunnel segment
  maxAngle              = 100 * CLHEP::mrad; // maximum angle before split
  minLength             = 4000;              // minimum length
}

BDSTunnelBuilder::~BDSTunnelBuilder()
{
  delete BDSTunnelFactory::Instance();
}

G4bool BDSTunnelBuilder::BreakTunnel(G4double cumulativeLength,
				     G4double cumulativeAngle,
				     G4int    cumulativeNItems,
				     G4double cumulativeDisplacementX,
				     G4double cumulativeDisplacementY)
{
  G4bool result = false;

  G4bool lengthTest = false;
  if (cumulativeLength > maxLength)
    {lengthTest = true;}

  G4bool angleTest = false;
  if (fabs(cumulativeAngle) > maxAngle)
    {angleTest = true;}

  G4bool nItemsTest = false;
  if (cumulativeNItems > maxItems)
    {nItemsTest = true;}

  G4bool dispXTest = false;
  if (cumulativeDisplacementX > displacementTolerance)
    {dispXTest = true;}

  G4bool dispYTest = false;
  if (cumulativeDisplacementY > displacementTolerance)
    {dispYTest = true;}

  result = lengthTest || angleTest || nItemsTest || dispXTest || dispYTest;

  // ensure that it's not too sharp a turn
  G4bool   lengthTestFail      = cumulativeLength < minLength;
  G4bool   angleIsFinite       = BDS::IsFinite(cumulativeAngle);
  
  if (lengthTestFail && result && angleIsFinite)
    {
      // only in the case of bent items
      // result is positive -> split tunnel, but too short - continue to increase length
      result = false;
    }

#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "testing cumulative parameters" << G4endl;
  G4cout << "Cumulative Length (mm):    " << cumulativeLength << " > " << maxLength << " test-> " << lengthTest << G4endl;
  G4cout << "Cumulative Angle (rad):    " << cumulativeAngle  << " > " << maxAngle  << " test-> " << angleTest  << G4endl;
  G4cout << "# of items:                " << cumulativeNItems << " > " << maxItems  << " test-> " << nItemsTest << G4endl;
  G4cout << "Cumulative displacement X: " << cumulativeDisplacementX << " > " << displacementTolerance
	 << " test-> " << dispXTest << G4endl;
  G4cout << "Cumulative displacement Y: " << cumulativeDisplacementY << " > " << displacementTolerance
	 << " test-> " << dispYTest << G4endl;
  G4cout << "Length:                    " << cumulativeLength << " < " << minLength << " test-> " << lengthTestFail << G4endl;
  G4cout << "Result:                    " << result << G4endl;
#endif
  return result;
}

BDSBeamline* BDSTunnelBuilder::BuildTunnelSections(const BDSBeamline* flatBeamline)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  
  BDSTunnelInfo* defaultModel = BDSGlobalConstants::Instance()->TunnelInfo();
  G4double       offsetX      = BDSGlobalConstants::Instance()->TunnelOffsetX();
  G4double       offsetY      = BDSGlobalConstants::Instance()->TunnelOffsetY();
  
  BDSBeamline* tunnelLine   = new BDSBeamline();

  // temporary variables to use as we go along
  G4int    nTunnelSections            = 0;
  G4double cumulativeLength           = 0; // integrated length since last tunnel break
  G4double cumulativeAngle            = 0; // integrated angle since last tunnel break
  G4int    cumulativeNItems           = 0; // integrated number of accelerator components since last tunnel break
  G4double cumulativeDisplacementX    = 0; // integrated offset from initial point - horizontal
  G4double cumulativeDisplacementY    = 0; // integrated offset from initial point - vertical
  BDSTunnelSection* tunnelSection     = nullptr;
  BDSTunnelFactory*     tf            = BDSTunnelFactory::Instance(); // shortcut

  // iterator to the BDSBeamlineElement where the previous tunnel section finished
  BDSBeamline::const_iterator previousEndElement = flatBeamline->begin();

  // iterator to the BDSBeamlineElement where the current tunnel section will begin
  BDSBeamline::const_iterator startElement       = flatBeamline->begin();

  // iterator to the BDSBeamlineElement where the current tunnel section will end
  BDSBeamline::const_iterator endElement         = flatBeamline->begin();

  // if a straight tunnel, just build one long segment, add it to beam line and return
  if (BDSGlobalConstants::Instance()->BuildTunnelStraight())
    {
      BDSBeamlineElement* lastElement = flatBeamline->back();
      G4double segmentLength = lastElement->GetReferencePositionEnd().z();
      tunnelSection = tf->CreateTunnelSection(defaultModel->type,          // type
					      "tunnel",                    // name
					      segmentLength,               // length
					      defaultModel->thickness,     // thickness
					      defaultModel->soilThickness, // soil thickness
					      defaultModel->material,      // material
					      defaultModel->soilMaterial,  // soil material
					      defaultModel->buildFloor,    // build floor?
					      defaultModel->floorOffset,   // floor offset
					      defaultModel->aper1,         // 1st aperture param
					      defaultModel->aper2,         // 2nd aperture param
					      defaultModel->visible);      // is it visible
      BDSTiltOffset* tos = new BDSTiltOffset(offsetX,offsetY,0);
      tunnelLine->AddComponent(tunnelSection,tos);
      return tunnelLine;
    } 

  BDSBeamline::const_iterator it = flatBeamline->begin();
  
  // iterate over beam line and build tunnel segments
  for (; it != flatBeamline->end(); ++it)
    {
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << "iterator at:       " << (*it)->GetPlacementName()           << G4endl;
      G4cout << __METHOD_NAME__ << "start iterator at: " << (*startElement)->GetPlacementName() << G4endl;
      G4cout << __METHOD_NAME__ << "end iterator at:   " << (*endElement)->GetPlacementName()   << G4endl;
#endif
      G4bool breakIt = BreakTunnel(cumulativeLength,
				   cumulativeAngle,
				   cumulativeNItems,
				   cumulativeDisplacementX,
				   cumulativeDisplacementY);
      G4bool isEnd     = (it == (flatBeamline->end() - 1));
      // remember end points to just after the last element, not the last element itself

      if (isEnd)
	{
	  endElement = it;
#ifdef BDSDEBUG
	  G4cout << "End of beam line - forcing break in tunnel" << G4endl;
	  G4cout << "End element for tunnel set to: " << (*endElement)->GetPlacementName()   << G4endl;
	  G4cout << "Start element is:              " << (*startElement)->GetPlacementName() << G4endl;
#endif
	}
      
      // it if matches any of the conditions, break the tunnel here (BEFORE) the item
      // pointed to by (*it)
      if (breakIt || isEnd)
	{
	  // work out tunnel parameters
	  std::string name = "tunnel_" + std::to_string(nTunnelSections);

	  // calculate start central point of tunnel
	  G4ThreeVector startPoint         = (*startElement)->GetReferencePositionStart();
	  G4ThreeVector startOffsetLocal   = G4ThreeVector(offsetX, offsetY, 0);
	  // create a copy of the rotation matrix for this object
	  G4RotationMatrix* startRot       = new G4RotationMatrix(*(*startElement)->GetReferenceRotationStart());
	  G4ThreeVector startOffsetGlobal  = startOffsetLocal.transform(*startRot);
	  startPoint                      += startOffsetGlobal;
#ifdef BDSDEBUG
	  BDS::PrintRotationMatrix(startRot, "rotation at beginning of starting element");
#endif

	  // calculate end central point of tunnel
	  G4ThreeVector endPoint           = (*endElement)->GetReferencePositionEnd();
	  G4ThreeVector endOffsetLocal     = G4ThreeVector(offsetX, offsetY, 0);
	  G4RotationMatrix* endRot         = new G4RotationMatrix(*(*endElement)->GetReferenceRotationEnd());
	  G4ThreeVector endOffsetGlobal    = endOffsetLocal.transform(*endRot);
	  endPoint                        += endOffsetGlobal;

	  G4double sStart = (*startElement)->GetSPositionStart();
	  G4double sEnd   = (*endElement)->GetSPositionEnd();
	  G4double sMid   = 0.5*(sStart + sEnd);

	  // calculate mid point of the tunnel - placement position in global coords
	  // midPoint = startPoint + (endPoint - startPoint)*0.5 // reducing this becomes
	  G4ThreeVector midPoint = 0.5*(startPoint + endPoint);
	  
	  // calculate mid point rotation
	  // mid point is calculated in 3d from vector points at either end. The faces
	  // are also picked up from the elements. To get the rotation, calculate the
	  // unit vectors at the mid point, which can be used to construct a rotation matrix.
	  // This starts from the unit vectors at the start of the starting element.
	  G4ThreeVector delta         = midPoint - startPoint;
	  G4ThreeVector newUnitZ      = delta.unit();
	  // get unit y by calculating x unit (starting element) cross direction of mid point (unit)
	  G4ThreeVector unitXPrevious = G4ThreeVector(1,0,0).transform(*startRot);
	  G4ThreeVector newUnitY      = newUnitZ.cross(unitXPrevious).unit();
	  // get unit x by calculating y unit (starting element) cross direction of mid point (unit)
	  G4ThreeVector unitYPrevious = G4ThreeVector(0,1,0).transform(*startRot);
	  G4ThreeVector newUnitX      = unitYPrevious.cross(newUnitZ).unit();
	  
	  // create mid point rotation matrix from unit vectors at mid point
	  G4RotationMatrix* rotationMiddle = new G4RotationMatrix(newUnitX, newUnitY, newUnitZ);
	  
	  // calculate length
	  G4double segmentLength = (endPoint - startPoint).mag() - 1*CLHEP::um; // -1um purely for safety purposes

	  // test if angled by comparing unit z vector at beginning and end
	  // this works in 3d.
	  G4ThreeVector unitZStart = G4ThreeVector(0,0,1).transform(*startRot);
	  G4ThreeVector unitZEnd   = G4ThreeVector(0,0,1).transform(*endRot);
	  // TBC - this could be done with the cross product in future.
	  G4ThreeVector unitZDiff  = unitZEnd - unitZStart;
	  G4bool isAngled          = unitZDiff.mag() > 1e-30;
	  
#ifdef BDSDEBUG
	  G4cout << __METHOD_NAME__ << "determined tunnel segment to have the following parameters:" << G4endl;
	  G4cout << "Start element name:      " << (*startElement)->GetPlacementName() << G4endl;
	  G4cout << "End element name:        " << (*endElement)->GetPlacementName()   << G4endl;
	  G4cout << "Start point (global):    " << startPoint                          << G4endl;
	  G4cout << "End point (global):      " << endPoint                            << G4endl;
	  G4cout << "Input and output unit Z: " << unitZStart << " " << unitZEnd << G4endl;
	  G4cout << "Has a finite angle:      " << isAngled                            << G4endl;
	  G4cout << "Section length:          " << segmentLength                       << G4endl;
	  G4cout << "Total angle:             " << cumulativeAngle                     << G4endl;
	  G4cout << "Rotation start:          " << *startRot                           << G4endl;
	  G4cout << "Rotation middle:         " << *rotationMiddle                     << G4endl;
	  G4cout << "Rotation end:            " << *endRot                             << G4endl;
#endif
	  
	  // create tunnel segment
	  if (isAngled)
	    { // use the angled faces
	      // make unit vectors for each face of the angled solid if required
	      // We need the rotation matrix for the input face in the frame of the tunnel
	      // segment. This really the difference between the incoming rotation matrix
	      // and the rotation matrix of the tunnel segment (middle). To get the difference
	      // we multiply the incoming by the inverse of the middle.
	      // We can then use this rotation matrix to transform a -ve z unit vector for the
	      // input face and a +ve z unit vector for the output face.
	      // The benefit is that this works in 3D and does not rely on the (cumulative)
	      // angle being averaged between the two faces - so each face can have a totally different
	      // angle as required by the tunnel builder.
	      G4RotationMatrix* middleInverse = new G4RotationMatrix(*rotationMiddle);
	      middleInverse->invert(); // now it's the inverse
	      G4RotationMatrix* inputFaceRotation  = new G4RotationMatrix((*startRot) * (*middleInverse));
	      G4ThreeVector inputFace  = G4ThreeVector(0,0,-1).transform(*inputFaceRotation);
	      G4RotationMatrix* outputFaceRotation = new G4RotationMatrix((*endRot) * (*middleInverse));
	      G4ThreeVector outputFace = G4ThreeVector(0,0,1).transform(*outputFaceRotation);

#ifdef BDSDEBUG
	      BDS::PrintRotationMatrix(middleInverse,"middle inverse");
	      BDS::PrintRotationMatrix(inputFaceRotation, "result");
	      BDS::PrintRotationMatrix(outputFaceRotation, "result end ");
	      G4cout << "tunnel segment input face normal determined to be:  " << inputFace  << G4endl;
	      G4cout << "tunnel segment output face normal determined to be: " << outputFace << G4endl;
#endif
	      
	      tunnelSection = tf->CreateTunnelSectionAngled(defaultModel->type,          // type
							    name,                        // name
							    segmentLength,               // length
							    inputFace,                   // input face normal
							    outputFace,                  // output face normal
							    defaultModel->thickness,     // thickness
							    defaultModel->soilThickness, // soil thickness
							    defaultModel->material,      // material
							    defaultModel->soilMaterial,  // soil material
							    defaultModel->buildFloor,    // build floor?
							    defaultModel->floorOffset,   // floor offset
							    defaultModel->aper1,         // 1st aperture param
							    defaultModel->aper2,         // 2nd aperture param
							    defaultModel->visible);      // is it visible
	      delete middleInverse;
	    }
	  else
	    { // straight section
	      tunnelSection = tf->CreateTunnelSection(defaultModel->type,          // type
						      name,                        // name
						      segmentLength,               // length
						      defaultModel->thickness,     // thickness
						      defaultModel->soilThickness, // soil thickness
						      defaultModel->material,      // material
						      defaultModel->soilMaterial,  // soil material
						      defaultModel->buildFloor,    // build floor?
						      defaultModel->floorOffset,   // floor offset
						      defaultModel->aper1,         // 1st aperture param
						      defaultModel->aper2,         // 2nd aperture param
						      defaultModel->visible);      // is it visible
	    }
	  
	  // bake the tunnel segment into a BDSBeamline element with position information
	  // create copies of rotation matrices (wasteful I know) as they're independently deleted
	  // by BDSBeamlineElement and can't double delete
	  G4RotationMatrix* startRot2 = new G4RotationMatrix(*startRot);
	  G4RotationMatrix* midRot2   = new G4RotationMatrix(*rotationMiddle);
	  G4RotationMatrix* endRot2   = new G4RotationMatrix(*endRot);
	  BDSBeamlineElement* tunnelElement = new BDSBeamlineElement(tunnelSection,  // accelerator component
								     startPoint,     // positionStart
								     midPoint,       // positionMiddle
								     endPoint,       // positionEnd
								     startRot,       // rotationStart
								     rotationMiddle, // rotationMiddle
								     endRot,         // rotationEnd
								     startPoint,     // referencePositionStart
								     midPoint,       // referencePositionMiddle
								     endPoint,       // referencePositionEnd
								     startRot2,      // referenceRotationStart
								     midRot2,        // referenceRotationMiddle
								     endRot2,        // referenceRotationEnd
								     sStart,         // sPositionStart
								     sMid,           // sPositionMiddle
								     sEnd);          // sPositionEnd

	  // store segment in tunnel beam line
	  tunnelLine->AddBeamlineElement(tunnelElement);
								     
	  // update / reset counters & iterators
	  nTunnelSections   += 1;
	  cumulativeLength   = 0;
	  cumulativeAngle    = 0;
	  cumulativeNItems   = 0;
	  cumulativeDisplacementX = 0;
	  cumulativeDisplacementY = 0;
	  if (!isEnd)
	    {
#ifdef BDSDEBUG
	      G4cout << __METHOD_NAME__ << "previous tunnel start element: " << (*startElement)->GetPlacementName() << G4endl;
	      G4cout << __METHOD_NAME__ << "previous tunnel end element:   " << (*endElement)->GetPlacementName()   << G4endl;
#endif
	      previousEndElement = endElement;   // (copy endElement) mark the end of this element as the prevous end
	      startElement       = endElement;   // copy end element iterator
	      ++startElement;                    // next segment will begin where this one finishes
#ifdef BDSDEBUG
	      G4cout << __METHOD_NAME__ << "new start element: " << (*startElement)->GetPlacementName() << G4endl;
	      G4cout << __METHOD_NAME__ << "new tunnel start element: " << (*startElement)->GetPlacementName() << G4endl;
	      G4cout << __METHOD_NAME__ << "new tunnel previous end element: " << (*previousEndElement)->GetPlacementName() << G4endl;
#endif
	    }
	} // end of scope of if (break section)
      else
	{
	  // else: don't break the tunnel here, move on to next element
#ifdef BDSDEBUG
	  G4cout << __METHOD_NAME__ << "moving to next item in beamline" << G4endl;
#endif
	  ++endElement; // advance the potential end element iterator
	}
      
      // accumulate angle and position
      G4double length   = (*startElement)->GetAcceleratorComponent()->GetChordLength();
      G4double angle    = (*startElement)->GetAcceleratorComponent()->GetAngle();
      cumulativeLength += length;
      cumulativeAngle  += angle;
      cumulativeDisplacementX += sin(angle) * length;
      //cumulativeDisplacementY += 0; // currently ignore possibility of vertical bend
      //would still use angle, but would need to involve tilt and rotation axes
      cumulativeNItems += 1;
#ifdef BDSDEBUG
      G4cout << "cumulative length:       " << cumulativeLength        << G4endl;
      G4cout << "cumulative angle:        " << cumulativeAngle         << G4endl;
      G4cout << "cumulative displacement: " << cumulativeDisplacementX << G4endl;
      G4cout << "cumulative # items       " << cumulativeNItems        << G4endl;
#endif
    } // for loop scope end
  return tunnelLine;
}
