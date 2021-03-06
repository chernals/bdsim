cmake_minimum_required(VERSION 2.8.12)

project(bdsim)

# project version
set( BDSIM_MAJOR_VERSION 0 )
set( BDSIM_MINOR_VERSION 9 )
set( BDSIM_PATCH_LEVEL 2)
set( BDSIM_VERSION ${BDSIM_MAJOR_VERSION}.${BDSIM_MINOR_VERSION}.${BDSIM_PATCH_LEVEL})

message(STATUS "Configuring BDSIM ${BDSIM_VERSION}")

# add source dir as a place for CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

# include BDSIM macros
include(bdsim_macros)

# With this true we automatically include current src/binary directory
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# Default build type (defines different sets of compiler flags)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
       "Choose the type of build, options are: None Debug DebugOutput Release RelWithDebInfo MinSizeRel DebugProf DebugCoverage."
       FORCE)
endif()

message(STATUS "Build Type ${CMAKE_BUILD_TYPE}")

# Add compiler flags based on build type
include(cmake/CompilerBuildFlags.cmake)

# Check if compiler is compatible
include(cmake/CompilerCheck.cmake)

# Check AFS and OS
include(cmake/SystemCheck.cmake)

#################  
# Find Packages #
#################

# GIT - optional - for software version in output & copying only example source files
# minimum version 1.8.2.1 for git ls-files for example copying
find_package(Git 1.8.2.1 QUIET)
# turn off git support if there's no .git folder - ie it's a copy of the source
# but not a repository
if (NOT EXISTS ${CMAKE_SOURCE_DIR}/.git)
  set(GIT_FOUND FALSE)
endif()

# CLHEP
include(cmake/CLHEP.cmake)

# ROOT
include(cmake/ROOT.cmake)

# GDML (on by default)
option( USE_GDML "Include GDML support."  ON )
if(USE_GDML)
    add_definitions("-DUSE_GDML")
    message(STATUS "GDML support ON")
endif()

# Field double precision (off by default)
option( FIELDDOUBLEPRECISION "Field values in double precision."  OFF )
if(FIELDDOUBLEPRECISION)
    add_definitions("-DFIELDDOUBLE")
    message(STATUS "Field double precision ON")
endif()

# Find GEANT4
include(cmake/Geant4.cmake)

## set compiler flags
include(cmake/CompilerFlags.cmake)

# add a target to generate API documentation with Doxygen
include (cmake/Doxygen.cmake)

# enable Testing with ctest
enable_testing()
include(CTest)
include(bdsim_test_macros)
include(comparator_test_macros)
include(interpolator_test_macros)
include(rebdsim_test_macros)
include(root_test_macros)

# This module sets up installation:
include(bdsim_install)

# Source files
string(TIMESTAMP CURRENT_YEAR %Y)
configure_file(${CMAKE_SOURCE_DIR}/bdsim.cc ${CMAKE_BINARY_DIR}/bdsim.cc @ONLY)

BDSIM_COLLATE_APPLICATION_SOURCES(bdsim_sources)
if(NOT USE_GDML)
  list(REMOVE_ITEM bdsim_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/BDSGeometryGDML.cc)
endif()

# Add Modules
option(USE_AWAKE "Use AWAKE Module" OFF)
if (USE_AWAKE)
  add_definitions("-DUSE_AWAKE")
  message(STATUS "AWAKE module ON")
  add_subdirectory(modules/AWAKE)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules/AWAKE/include)
endif()

if($ENV{VERBOSE})
  message(STATUS "ROOT dictionaries ${root_dicts}")
  message(STATUS "BDSIM sources ${bdsim_sources}")
endif()

# Configuration information
add_subdirectory(configuration)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/configuration)

# Parser
add_subdirectory(parser)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/parser)
# include current directory for parser includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# external sources
add_subdirectory(src-external)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src-external)

# add label to original BDSIM files
set_source_files_properties(${bdsim_sources} ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh PROPERTIES LABELS "BDSIM")

# BDSIM library and binaries
add_library(bdsim ${root_dicts} ${bdsim_sources} )

add_executable(bdsimexec ${CMAKE_BINARY_DIR}/bdsim.cc)

set_target_properties(bdsimexec PROPERTIES OUTPUT_NAME "bdsim" VERSION ${BDSIM_VERSION})
target_link_libraries(bdsimexec bdsim gmad)
target_link_libraries(bdsim ${CLHEP_LIBRARIES})
target_link_libraries(bdsim ${Geant4_LIBRARIES})
if (USE_GZSTREAM)
  #preprocessor flag
  add_definitions("-DUSE_GZSTREAM")
  target_link_libraries(bdsim gzstream)
endif()

# link against ROOT
target_link_libraries(bdsim ${ROOT_LIBRARIES})

if(${CMAKE_BUILD_TYPE} STREQUAL "DebugCoverage")
    target_link_libraries(bdsim gcov)
endif()

# set binary name for testing usage
get_target_property(binaryname bdsimexec OUTPUT_NAME)
set(bdsimBinary ${CMAKE_CURRENT_BINARY_DIR}/${binaryname})

# ROOT Event Library
set(bdsimRootEventSources ${root_dicts} ${root_files})

# Add parser options
list(APPEND bdsimRootEventSources ${CMAKE_CURRENT_SOURCE_DIR}/parser/optionsBase.cc)
if($ENV{VERBOSE})
  message(STATUS "bdsimRootEventSources ${bdsimRootEventSources}")
endif()

add_library(bdsimRootEvent SHARED ${bdsimRootEventSources})
target_compile_definitions(bdsimRootEvent PRIVATE "-D__ROOTBUILD__")
# link against ROOT
target_link_libraries(bdsimRootEvent ${ROOT_LIBRARIES})
# Add dependency to make sure bdsimRootEvent is done first
# This is done because the ROOT dictionary generation needs to be done separately for each of them
# And even if the dictionaries are the same compiling with multiple threads will result in building them simultaneously
add_dependencies(bdsim bdsimRootEvent)

# Install the targets:
set(executables bdsimexec)
if (${ROOT_MAJOR_VERSION} STREQUAL "6")
  set(libraries bdsim bdsimRootEvent)
else()
  set(libraries bdsim)
endif()
set_target_properties(${executables} ${libraries} PROPERTIES VERSION ${BDSIM_VERSION})
bdsim_install_targets(${executables} ${libraries})
bdsim_install_libs(${root_pcms})
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)
bdsim_install_headers(${headers} ${root_dicts_headers})

include(CPack)

option(BUILD_MACOSX_APP "Build Mac OSX application" OFF)

if (BUILD_MACOSX_APP AND APPLE)
    # building a macos executablemaking a bundle of 
    add_executable(bdsimapp MACOSX_BUNDLE ${CMAKE_BINARY_DIR}/bdsim.cc)
    set_target_properties(bdsimapp PROPERTIES OUTPUT_NAME "bdsim" VERSION ${BDSIM_VERSION})
    target_link_libraries(bdsimapp bdsim gmad)
    bdsim_install_bundle(bdsim)
endif()

# package source
# uses git but only for developers
add_custom_target(dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# copy dependent libraries in deps directory
add_custom_target(copy-deps
  COMMAND ${CMAKE_SOURCE_DIR}/cmake/copyldd.sh bdsim ${CMAKE_BINARY_DIR}/deps
)

## Add subdirectories
# Visualisation directory
add_subdirectory(vis)

# For testing
add_subdirectory(examples)
# copy examples to build directory - macro defined in bdsim_macros.cmake
if (GIT_FOUND)
  copy_examples()
else()
  copy_examples_no_git()
endif()
  
# Include directory for tests
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(test)

# Include directory for analysis
add_subdirectory(analysis)

# Include directory for comparator
add_subdirectory(comparator)

# Include directory for interpolator
add_subdirectory(interpolator)

# Manual
add_subdirectory(manual)

# Mark some variables as advanced to clean up GUI
if(APPLE)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
  mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
  mark_as_advanced(CMAKE_OSX_SYSROOT)
endif()
