#pragma once

#include <G4VUserDetectorConstruction.hh>

namespace ecs {

class Detector: public G4VUserDetectorConstruction {

	G4double wordRadius;
	G4double targetWidth;

	G4VPhysicalVolume* CreateWorld();

public:
	Detector();

	G4VPhysicalVolume* Construct() override;
};

}
