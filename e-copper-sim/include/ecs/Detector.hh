#pragma once

#include <G4VUserDetectorConstruction.hh>
#include <G4Material.hh>

namespace ecs {

class Detector: public G4VUserDetectorConstruction {

	G4VPhysicalVolume* CreateWorld();

public:
	Detector();

	G4VPhysicalVolume* Construct() override;

	G4double GetTargetWidth() const {
		return targetWidth;
	}

	G4Material const* GetTargetMaterial() const {
		return fTargetMaterial;
	}

private:

	G4double wordRadius;
	G4double targetWidth;
	G4Material* const fTargetMaterial;

};

}
