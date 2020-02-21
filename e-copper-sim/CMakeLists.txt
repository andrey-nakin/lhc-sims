#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(ECopperSim VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Geant4-based simulation of electron-induced copper films")

#include(GNUInstallDirs)
set (CMAKE_CXX_STANDARD 14)

#----------------------------------------------------------------------------
# Find Geant4 package
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
  add_definitions(-DGNEISGEANT4LIB_NO_VIS)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
#include(GNUInstallDirs)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add and configure the library
#
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME e-copper-sim)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

