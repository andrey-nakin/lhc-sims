#pragma once

#include <G4VUserDetectorConstruction.hh>
#include <G4Colour.hh>

namespace ecs {

class Detector: public G4VUserDetectorConstruction {

	G4double wordRadius;
	G4double targetWidth;

	G4VPhysicalVolume* CreateWorld();
	static G4Colour FromRGB(short red, short green, short blue);
	static G4Colour FromRGBA(short red, short green, short blue, short alpha);

public:
	Detector();

	G4VPhysicalVolume* Construct() override;
};

}
