V0.992 - 2017 / 07 / 26
=======================

New Features
------------

* Preparsing for GDML for pygeometry generated geometry - overcomes Geant4's GDML parser
  deficiency of only allowing one GDML file to be loaded in the whole program.
* Visualisation of multiple beam lines.
* Option to use first sampler emittance as assumed emittance throughout lattice in optical
  function calculation.
* Additional materials for LHC tunnel and geometry.
  
Bug Fixes
---------

* Fix uncaught exception in analysis DataLoader class construction depending on optional arguments.
* BDSIM installation no longer dependent on build files - ROOT analysis dictionaries would use
  build headers. Issues #197 and #199.
* Fixed magnitude of B field in rfcavity that resulted in extraordinarily strong B fields.
* Fixed rf E and pill-box fields ignoring phase and being a factor of 2:math:`\pi` too low in frequency.
* Fix for crash when particle was at exactly 0 in a quadrupole.
* Fix compiler warnings for Clang 8.1.
* Fixed all variable shadowing throughout codebase and reintroduced compiler warning if present.
* Fix field transform for tilted and offset magnets. This fixes incorrect tracking for tilted
  magnets when using the "bdsimtwo" integrator set for dipoles.

General
-------

* Separated field and geometry in rf cavity element.
* Revised implementation of rf cavity construction for greater flexibility.
* RF cavity phase now automatically calculated based on location in lattice.
* Removal of old ROOT analysis scripts for very old data format.
* Revised construction to allow construction of multiple beam lines dynamically.

Utilities
---------

* pymadx v0.9
* pybdsim v1.2
* pymad8 v0.7


V0.991 - 2017 / 07 / 04
=======================

Bug Fixes
---------

* Fix simple histogram weighting with boolean expressions in rebdsim.
* Fix comparator always failing.
* Fix loading default event information in analysis.
* Fix executing BDSIM from outside the directory containing the main gmad file.
* Fix charge dependence of thin multipole and dipole fringe integrators.
* Scale dipole fringe and thin multipole by momentum and of particle.
* Fix for loading geometry files prefixed with superfluous './'.
* Fix for duplicate run beam on icon in visualiser for Geant4.10.3 onwards.


General
-------

* Separate Doxygen cmake into own macro.

Utilities
---------

* pymadx v0.9
* pybdsim v1.1
* pymad8 v0.7


V0.99 - 2017 / 06 / 09
======================

New Features
------------

 * Parser will expand values from structures when printing. Issue #167.
 * Optical physics example and test. Issue #156.
 * Improved parser error messages. Issue #170.
 * Support for compressed input coordinate files for beam distributions using tar and gz.
 * Switch entirely to CMake labels instead of naming convention for tests.
 * AWAKE experiment code refactored into module.
 * New *shield* element that is a drift surrounded by rectangle of material.
 * New *placement* element that allows an object with geometry to be placed independent of the beam line.
 * maximumTrackLength option to limit any track in the geometry.
 * Ability to offset beam line w.r.t. world coordinates at start.
 * Check for required Geant4 environment variables.
 * Thin horizontal and vertical (and combined) kickers.
 * Thin multipoles.
 * Compatability with Geant4.10.3.
   
Fields & Integrators
^^^^^^^^^^^^^^^^^^^^
 * Complete refactorisation of field classes and construction.
 * Centralised construction of fields.
 * 1-4D BDSIM format field map loading.
 * 2D Poisson SuperFish SF7 format field map loading.
 * 1-4D nearest neighbour, linear and cubic interpolators for field maps.
 * Support for compressed field maps using tar and gz.
 * Ability to choose integrator sets for all elements via parser.
 * Removal of all individual magnet classes - centralised construction in BDSMagnet.
 * New executable - "bdsinterpolator" - allows loaded and interpolated field to be queried and written out.
 * Rewritten dipole integrator using Geant4's helical stepper.
 * All integrators tested for low energy spiralling particles.
 * Introduction of visualisation commands.

Geometry
^^^^^^^^

 * Rewritten external geometry loading.
 * Ability to overlay externally provided geometry on magnets (except sbend).
 * Automatically generated tight-fitting containers for externally loaded GDML geometry.
 * *circularvacuum* beam pipe geometry that allows no geometry for the beam pipe; only vacuum.
 * Magnet colours tweaked slightly - pybdsim now matches BDSIM colour-wise.
 * Additional curvilinear bridge world to ensure continuous curvilinear coordinates.

   
Output & Analysis
^^^^^^^^^^^^^^^^^

 * Protection against invalid sampler names that would cause ROOT branching errors.
 * 1x 3D histogram in default output that can be placed along the beam line.
 * Support for 3D histograms in rebdsim.
 * All magnet strength components written out to survey.
 * Change of syntax in rebdsim analysis file to specify dimensions of histogram.
 * Stricter parsing of analysisConfig.txt for syntax checking.
 * New executable rebdsimOrbit to extract single orbit from sampler data.


Bug Fixes
---------

 * ASCII seed state can be loaded properly. Issue #163.
 * rfcavity can be created without a cavitymodel instance. Issue #165.
 * Memory leak in comparator event tree comparison fixed. Issue #169.
 * 0 angle bend with finite field can be created. Issue #176.
 * Samplers are compared properly in comparator. Issue #177.
 * Sampler names in Model tree now match exactly those in the Event tree.
 * Missing virtual keyword from destructors fixed through to fix leaks at end of program.
 * GFlash parameterisation is only loaded if specified in physics list.
 * Fixed geometry construction errors that may occur due to dynamic tolerances for physically large models.
 * Fix infinite loop events if the primary vertex starts outside the world volume.
 * Regions and biases set correctly to components in BDSLine class.
 * Circle distribution did not have central value offsets.
 * Fix double registration of pion decay as well as some others for muons when using muon phyiscs list.
 * Particles from physics list are now constructed correctly allowing more particles to be used in the beam definition.
 * Removal of cherenkov radiation from muon phyiscs significantly reducing simulation time.
 * Fix double registration of pion decay with muon phyiscs list.
 * Issue #134 - samplers cause tracking warning.
 * Long running events due to spiralling particles. Issues #178, #132, #187.

General
-------

 * ``Sampler_`` prefix was removed from all samplers in rootevent output.
 * Sampler thickness reduced from 40 nm to 10 pm.
 * Removal of unnecessary step length limit to half the length of an element.
 * Revised region construction allowing arbitrary number to be constructed.
 * Revised bend construction with reduced volume count in some cases.

Utilities
---------

* pymadx v0.8
* pybdsim v1.0
* pymad8 v0.7

V0.95 - 2016 / 11 / 07
======================

New Features
------------

* Comparator program introduced for statistical comparison against reference results.
* rebdsim analysis examples and tests added.
* ROOT examples and tests added for analysis code usage in ROOT.
* Discrete optics only program rebdsimOptics added.
* Update clhep in AFS build to 2.3.1.0 for apple and 2.3.3.0 for RHL6.
* Reduced compilation time.

Bug Fixes
---------

* Fix geometry tolernace issue that would cause Geant4 runtime errors for
  regular geometry for some particularly large spatial size models.
* Fix for linker error with ZLIB and gzstream. Issues #9, #155, #158.
* Fix nan errors in certain circumstances when calculating optical functions.
* Fix shadowing compilation warnings.
* Fix geometry overlaps in rf cavity geometry. Issue #136.
* Coverity fixes for uninitialised variables / small memory leaks. Issues #152, #156.
* Fix potential magnet geometry errors when creating very thin components.
* Fix negative interaction warnings due to biasing. Issue #141.

General
-------

* Deprecate BDSIM Plank scattering, laserwire calorimeter, e bremsstrahlung
  lead particle biasing.

Utilities
---------
* pymadx v0.7
* pybdsim v0.9
* pymad8 v0.6
* robdsim v0.7

V0.94 - 2016 / 09 / 13
======================

New Features
------------

Analysis
^^^^^^^^

* Analysis class have been refactored to allow analysis on any tree in the BDSIM
  ROOT event output format using rebdsim.

Geometry
^^^^^^^^

* Tilted dipoles are now supported.
* The Read Out geometry has been moved to the Geant4 parallel world scheme.
* The parallel sensitive geometry for tunnel hits has been deprecated and the
  functionality now provided by the new parallel read out geometry.
* The read out geometry construction has moved out of BDSAcceleratorComponent
  to its own geometry factory.
* Beam pipes are now constructed with arbitrary 3-vector surface normals rather
  than angled faces described by an angle only in the x-z plane.
* The side of the yoke of a dipole with poled geometry can now be controlled with
  the :code:`yokeOnLeft` option.
* New interfaces to the auxiliary navigator have been written that use the mid-point
  of a step to much more robustly locate the required volume in the parallel
  curvilinear geometry.
* Overlap checking between adjacent dipoles with pole face rotations (and even tilts)
  prevents overlaps in geometry.

Output
^^^^^^

* Tunnel hits are now of the same type as general energy loss hits.
* The track ID can now be optionally written out to energy deposition hits.

Parser
^^^^^^

* The option :code:`modularPhysicsListsOn` has been deprecated.
* New per element parameter :code:`yokeOnLeft`.
  
Physics
^^^^^^^

* The modular physics lists are now compulsory and the old physics construction has
  been deprecated.
* The existing BDSIM laserwire compton scattering process construction was moved to
  the modular physics list scheme.


Bug Fixes
---------

Geometry
^^^^^^^^

* Extent inheritance with BDSGeoemetryComponent was fixed resolving rare overlaps.
* Poled geometry variable clean up fixed to ensure components from factories aren't
  related to each other - could cause rare crash on exit.
* Fixed extents and possible overlaps in tunnel 'rectaboveground' geometry.

Output
^^^^^^

* Energy deposition coordinates are randomly chosen along the step of the deposition. The
  x,y,z coordinates now match the random point where as they were the post step point previously.

Physics
^^^^^^^

* Fixed an issue that would cause infinite loops with strong process biasing.

General
^^^^^^^

* Initialisation of variables fixed throughout.
* Includes reduced to significantly improve compilation speed.
* Removed executable permission on all source files.

Utilities
---------
* pymadx v0.6
* pybdsim v0.8
* pymad8 v0.5
* robdsim v0.7
  

V0.93 - 2016 / 08 / 24
======================

New Features
------------

Analysis
^^^^^^^^

* New analysis tool 'rebdsim' replaces robdsim.
* Analysis directory with event, model, event info, options analysis.
* Histogram merging with correct statistical uncertainties.
* Deprecated root utilities to :code:`analysis/old/`.
* Rewritten optical function calculation with validated calculation.

Build
^^^^^

* Require CMake 2.8.12 or higher.
* Require Geant4 compiled with external CLHEP - ensures strong reproducibility.
* Start of bootstrapping scripts in :code:`depend/`.
* Factorisation of BDSIM's cmake package finding into :code:`cmake/`.


Geometry
^^^^^^^^

* Coil geometry introduced to generic library magnets.
* Overlap checking between magnets with pole face rotations.
* Collimator colour can now be controlled.
* End pieces for coils also introduced
* Default poled dipole geometry is now a C shaped magnet with yoke on inside of bend.

Output
^^^^^^

* Switched to rootevent as default and **recommended** format.
* Include full set of options used in simulation in output.
* Include software version in output.
* Store seed state per event.
* Store histograms per event.
* Run and event durations stored in output.
* Output written in event of a crash.
* Refactor of trajectory information.
* Write out primary trajectory points.

Parser
^^^^^^

* Factorised options into optionsBase that is simple struct for easy saving.

Physics
^^^^^^^

* "Modular physics" list is now the default.
* Use geant4 helper class for physics lists construction to ensure correct order.
* Ability to provide a default bias to all types of volumes (vacuum, accelerator, all).
* Attribute energy deposition (uniformly) randomly along the step it happened for more correct energy deposition - currently only s, not x,y,z - they represent before, after.
* 'solid' air materials for cross-section validation.
* Seed states are saved and restored in the primary generator action rather than event action.

Tracking
^^^^^^^^

* Geant4 Runge kutta stepper for quadrupole and sextupole for increased robustness.


General
^^^^^^^

* Strong recreation for an event by setting seed state issue (#118, #139).
* A BDSAcceleratorComponent can own an associated end piece(s) (before and after).
* A BDSAcceleratorComponent can have a input and output angled face.
* Halo bunch distribution developed significantly.
* Revised executable options for recreation / using a seed state.
* Signal handling improved.
* Templated user bunch file - can now use gzip compressed files.
* Improved default options for more realistic geometry.


Bug Fixes
---------

Geometry
^^^^^^^^

* Fix for multiple gdml file loading having conflicting 'world' volumes.
* Reimplementation of pole geometry fixes gaps in poles (issue #110).

Parser
^^^^^^

* Fixed issue of parser python interface (issue #133).

Physics
^^^^^^^

* Modular physics lists are truly modular - fixes segfaults (issue #130).

Tracking
^^^^^^^^

* Fixes for cavity field values (issue #124).
* Fix field value transform in sextupoles and above for global / local coordinates.
* Auxiliary navigator used for transforms more routinely with optional caching.

General
^^^^^^^

* Issues #115, #127, #129, #131

  
Utilities
---------
* pymadx v0.6
* pybdsim v0.7
* pymad8 v0.41
* robdsim v0.7


V0.92 - 2016 / 03 / 29
======================

New Features
------------

* Samplers are attached at the *exit* instead of the *entrance* of an element.
* Poleface rotations for bends are implemented (issue #100).
* Geant4 9.6.x versions support has been dropped (issue #111).
* DUMP element removed (issue #116).

Geometry
^^^^^^^^

* Samplers are no longer placed in the physical world but in a parallel sampler world.
* Above ground 'tunnel' geometry implemented.
* Introduced new RF cavity geometry and fields (still in development).

Output
^^^^^^

* ROOT version 6 support (issue #114).
* Option to fill ROOT with double or float precision.
  
Parser
^^^^^^

* Support for string variable (issue #126).

Physics
^^^^^^^

* Modular physics lists are default (issue #121).
* Use Geant4 provided synchrotron radiation instead of BDSIM one.

Bug fixes
---------

Geometry
^^^^^^^^

* Tunnel geometry fixes (issues #88 and #89).

Parser
^^^^^^

* Fix fast list insertion (issue #113).
* Support for tildes in path names (issue #119).

Physics
^^^^^^^

* Old physics code cleanup (issue #123).
* Physics biasing properly initialised (issue #84).
  
General
^^^^^^^

* PDF Manual builds on Ubuntu (issue #85).
* 1D Histogram class significantly faster for uneven bin width histograms.

Utilities
---------
* pymadx v0.4
* pybdsim v0.5
* pymad8 v0.3
* robdsim v0.5

V0.91 - 2015 / 12 / 17
======================

New Features
------------

* New tests for file IO, coordinate transforms, aperture models, extra optical lattice patterns and general ring example.

Geometry
^^^^^^^^

* Race track and octagonal aperture models introduced.
* New wedged energy degrader component introduced.

Output
^^^^^^

* Optional reduced number of variables in ROOT output - formats now "root" and "rootdetailed" (issue #107)
* Forced dependency on ROOT

Parser
^^^^^^

* Parser warns for redefined variable, and exits for usage of undeclared variables (issue #98)
* Parser reorganised to C++ class structure (issue #77)
* Command line options more flexible (issue #105)
* Ability to define Geant4 regions as objects in parser.
* Can attach samplers to all elements of one type, ie collimators.

Physics
^^^^^^^

* Can attach biasing to any part of any element from parser.

Tracking
^^^^^^^^

* Ability to start bunch from any S position along accelerator rather than just at beginning.
  
Bug fixes
---------

Geometry
^^^^^^^^

* Fix for LHC detailed geometry when beam shield is rotated.
* Consoldation and improvement of aperture parameter validity testing.
* Fix for femtometre occasional overlaps in magnet outer geometry.
* Fixed placement overlaps in rbend.
* Fixed seg-fault with RfCavity at end of run.
* Fixed crashes with zero angle sector bends.
  
Parser
^^^^^^

* Multiple command line arguments without space will now be recognised and highlited.

Physics
^^^^^^^

* Made required version of Geant4 consistent across biasing code.
  
Tracking
^^^^^^^^

* Fields only constructed if non-zero strength used - avoids tracking errors for zero strength components.
* Fixed several issues with vertical and horizontal kicker construction and tracking.
* Broken external magnet fields disabled by default.
* Circular turn counting bugs fixed
* Particles no longer killed with circular flag on if starting slightly behind starting mid point.
* Particles no longer stepped by teleporter at beginning of 1st turn if starting behind starting mid point.
* Fix teleporter tracking for backwards travelling particles that would get stuck in a loop.
  
General
^^^^^^^

* Add CMake protection against Geant4 built with multithreading on (issue #103)

Utilities
---------
* pymadx v0.3
* pybdsim v0.4
* pymad8 v0.2
* robdsim v0.4

V0.9 - 2015 / 11 / 10
=====================

New Features
------------

* Physics biasing with ability to change cross-section for individual particles
  and processes as well as attach to a variety of objects
* Decapole magnet
* Robdsim analysis package as separate executable for testing
* Tracking tester
* Improved C++11 use and iterator implementation across containers
* Fill histogram with energy hit over a range covering several bins
* Introduced a separate auxiliary G4Navigator to avoid accidentally moving
  the particle during tracking when querying global to local transforms
* Transform for curvilinear coordinates to global coordinates
  so primaries in those coordinates can be injected from anywhere (issue #63)
* Parser put in GMAD namespace
* New executable options for writing out geometry coordinates as built by BDSIM
* Magnets now have tightly fitting invisible container volumes as opposed to
  large boxes before
* Changed return type of magnet outer geometry factories to new BDSMagnetOuter
  class. This is because the container contruction is now delegated to the
  magnet outer factory for tight fitting container volumes.
* Extended examples and tests
* Move entirely to Geant4 visualisation manager supporting all available visualisers
  available with the local Geant4 installation

Bug fixes
---------

Geometry
^^^^^^^^

* Fixed bug where the read out coordinates would also be offset by the offset
  of the element
* Fixed overlaps in read out geometry
* Reduced dupliation in magnet outer factories
* Fixed overlaps in rbend geometry (issue #64)
* Increase tolerance for sector bends (issue #73)
* Protect against zero angle sector bends (issue #74)
* Fixed overlaps in GDML geometry (issue #81)
* Geometry fixes (issues #76, 94, 95)
  
Physics
^^^^^^^

Parser
^^^^^^

* Occasional material parser segfault fixed (issue #25)
* Improved syntax checking and not ignore unknown keywords (issue #71)
* Element extension fixed (issue #87)

Tracking
^^^^^^^^

* Dipole uses local coordinates and can bend in any direction (issue #78)
  
General
^^^^^^^

* Samplers can be attached to occurrence of a duplicated element (issue #47)
* Output survey updated and fixed (issue #60)
* Check for Geant4 environment variables (issue #62)
* Consistent policy for overwriting output files (issue #65)
* Improve memory and cpu for output writing (issue #86)

Utilities
---------
* pymadx v0.2
* pybdsim v0.3
* pymad8 v0.2
* robdsim v0.3

V0.8 - 2015 / 08 / 10
=====================

New Features
------------

* Tunnel geometry and flexible tunnel factories for different styles
* Tunnel read out geometry introduced for coordinates along tunnel axis
* C++11 adopted (required)
* `stopSecondaries` option
* Remove dependency on boost (issue #57)
* Restructured examples directory - top level contains only full machines
  and subdirectories contain features.
* Example documentation in manual and in place beside each example with
  example screenshots
* Updated python utilities *pybdsim v0.1*, *pymadx v0.1*, *pymad8 v0.1* and *robdsim v0.2*
* Repeated components are not duplicated in memory - previously, they would
  be repeatedly constructed. Reduced memory footprint
* Component information comes from Physical Volumes instead of Logical Volumes
* Improved manual documentation
* Improved Doxygen documentation
* Rubbish collection for all objects rather than relying on only one run and
  Geant4 (partial) rubbish collection.
* String representation of enum types leading to more readable output
* Introduce ability to switch to new modular physics lists with flexible
  construction and addition of physics lists without hard-coded names for each
  combination - the user must turn this on explicitly

Bug fixes
---------

Geometry
^^^^^^^^
* Geometry overlaps (issues #55 and #58)
* Transform3d fix (issue #54)
* Fixed placement of objects outside x,z global plane - rotation bug, similarly
  for read out geometry placement
* Fix broken circular control - bug was introduced in v0.7 - (issue #51)
* Strict checking of read out geometry construction to avoid invalid solids that
  would cause Geant4 to exit and BDSIM to crash
* Strict checking on teleporter volume construction for circular machines that
  would cause Geant4 to exit and BDSIM to crash
* Fix for calculation of length of sector bend magnet that would cause it to be
  slightly short - introduced in v0.7
* Removed stored axes of rotation due to better implementation in BDSBeamline
  avoiding duplication of information
* Fixed issue of zero angle rbends causing a crash (issue #44)
* Event number print out is now dynamic and based on the number of events to be
  generated and is also controllable with `printModuloFraction` option
* Protect against bad user specified values of `lengthSafety` to avoid
  geometry overlaps
* Improved parser speed

Physics
^^^^^^^
* SR radiation fix in dipole (issue #53)
* Removed continuous synchrotron radiation as traps particles in low step size
  infinite loop
* Removal of poorly set deltaIntersection, chordStepMinimum and lengthSafety
  variables from examples - these should be left unset unless the user knows
  their purpose.

Output
^^^^^^
* Change all transverse output units to **metres** - manual updated accordingly
* Change `z` in ASCII output to **global Z** instead of local z.
* Recorded energy in output is now unweighted but energy recorded in convenience
  energy loss histogram is. Could have lead to double weighting previously
* Fix for global coordinates being written out as local coordinates in ROOT
  output
* Random number generator seed state not written out when no output is specified

Parser
^^^^^^
* Return error if superfluous arguments are present (issue #56)
* Make parser more robust against duplicate element names (issue #43)
* Fixed warnings about compiling c as c++ being deprecated behaviour
  
General
^^^^^^^
* Fix for wrong print out warning due to logic error (issue #51)
* Fix for boundary effects of energy deposition (issue #52)
* Fix large memory leak for events with large number of particles - was due to
  accumulation of BDSTrajectory objects


V0.702 2015 / 07 / 28 - Hotfix
==============================

* Fix for physics production range cuts were not obeyed in simulation
  
V0.701 2015 / 07 / 02 - Hotfix
==============================

* Fix for global X coordinate not written to output for energy deposition

V0.7 - 2015 / 06 / 30
=====================

New Features
------------

* Ability to write no output
* New magnet geometry factories introduced with 7 possible magnet types.
* Introduction of --vis_debug flag to see container volumes without debug build.
* Revised magnet colours (same base colour, just prettier variant).
* New manual using sphinx documentation system.
* Default visualiser provided - no requirement for a vis.mac by the user.
* Nicer visualisation GUI by default.
* Improved visualisation for GDML geometry.
* Support for all Geant4 visualisers introduced (issue #11).

Bug fixes
---------

* Fixes to overlapping volumes and tracking errors in beam pipes.
* Fix for wrong transverse coordinates for geometry other than cylindrical magnets (issue #30).
* Histograms now written to disk in case of crash or kill signal (issue #38).
* Fix for uncontrolled memory consumption for synchrotron radiation (issue #36).
* Fix syntax error in parser on windows end of line character (issue #40).
* Follow user paths properly (issue #24).
* Parser can end on commented line (issue #41).
* Introduction of more flexible and weighted halo bunch distribution.
* Significant tidy of BDSAcceleratorComponent base class and derived classes.
* Fix LHC magnet geometry overlaps and improve efficiency as well as more flexible with different beam pipes.
* New BDSBeamline class used for component placement consistently in code.

V0.65 - 2015 / 04 / 10
======================

* New base class for any geometrical object BDSGeometryComponent.
* New interchangeable beam pipes with 6 possible beam pipe shapes.
* New sensitive detector manager to hold single instance of sd classes.
* Introduction of G4Galactic material for 'empty' volumes rather than beam pipe vacuum.
* Possibility to write to multiple output formats at once.
* Extensive removal of unnecessary headers throughout.
* Updated python utilities.
* Fix for muon spoiler magnetic field (thanks to B. Pilicer).
* Fix for invisible cylinder of iron surrounding drifts previously.


V0.64 - 2015 / 02 / 16
======================

* New histogram manager and factorisation of histograms from outputs.
* Extra per element histograms.
* Basic implementation of valid solenoid.

V0.63 - 2015 / 02 / 06
======================

* Large angle sbends split into multiple sbends - based on aperture error tolerance - currently 1mm.
* New geometry construction and placement for sbends and rbends - no overlapping volumes and
  simpler / increased performance.
* Proper building under c++11 if available.
* Introduction of composite bunch distribution.
* Drop support for Geant4 versions 9.5 and older
  
V0.62 - 2014 / 08 / 07
======================

V0.61 - 2014 / 08 / 05
======================

* Geant4 version 10 support

v0.6 - 2013 / 12 / 02
=====================


v0.5 - 2008 / 11 / 08
=====================


v0.4 - 2008 / 02 / 26
=====================


v0.3 - 2007 / 01 / 26
=====================


v0.2 - 2006 / 05 / 18
=====================


v0.1 - 2006 / 02 / 22
=====================


beta - 2005 / 05 / 01
=====================
