cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(LhcSims LANGUAGES CXX DESCRIPTION "Geant4-based simulations for LHC research")
add_subdirectory(lhc-sim-lib)
add_subdirectory(e-copper-sim)
