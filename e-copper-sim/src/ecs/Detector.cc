#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Tubs.hh>
#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4VisAttributes.hh>

#include <ecs/Detector.hh>

namespace ecs {

Detector::Detector() :
		wordRadius(5. * cm), targetWidth(35. * um) {

}

G4VPhysicalVolume* Detector::CreateWorld() {
	auto const nist = G4NistManager::Instance();
	auto const worldSolid = new G4Tubs("WorldSolid", 0. * cm, wordRadius,
			10. * cm, 0. * deg, 360. * deg);
	auto const worldLog = new G4LogicalVolume(worldSolid,
			nist->FindOrBuildMaterial("G4_Galactic"), "World");
	worldLog->SetVisAttributes(
			G4VisAttributes(true, FromRGBA(116, 231, 238, 32)));

	auto const targetSolid = new G4Tubs("TargetSolid", 0. * cm, wordRadius,
			targetWidth / 2, 0. * deg, 360. * deg);
	auto const targetLog = new G4LogicalVolume(targetSolid,
			nist->FindOrBuildMaterial("G4_Cu"), "Target");
	targetLog->SetVisAttributes(G4VisAttributes(FromRGB(184, 115, 51)));
	new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), targetLog,
			"TargetPhys", worldLog, false, 0);

	auto const worldPhys = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.),
			worldLog, "WorldPhys", 0, false, 0);

	return worldPhys;
}

G4Colour Detector::FromRGB(short const red, short const green,
		short const blue) {
	const G4double m = 1.0 / 255.0;
	return G4Colour(m * red, m * green, m * blue);
}

G4Colour Detector::FromRGBA(short const red, short const green,
		short const blue, short const alpha) {
	const G4double m = 1.0 / 255.0;
	return G4Colour(m * red, m * green, m * blue, m * alpha);
}

G4VPhysicalVolume* Detector::Construct() {
	auto const physiworld = CreateWorld();
	return physiworld;
}

}

