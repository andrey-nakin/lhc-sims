#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Tubs.hh>
#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4VisAttributes.hh>
#include <G4UserLimits.hh>

#include <ecs/Detector.hh>
#include <lhcs/repository/Colours.hh>

namespace ecs {

Detector::Detector() :
		wordRadius(5. * cm), targetWidth(35. * um) {

}

G4VPhysicalVolume* Detector::CreateWorld() {
	using namespace lhcs::repository;

	auto const nist = G4NistManager::Instance();
	auto const worldSolid = new G4Tubs("WorldSolid", 0. * cm, wordRadius,
			10. * cm, 0. * deg, 360. * deg);
	auto const worldLog = new G4LogicalVolume(worldSolid,
			nist->FindOrBuildMaterial("G4_Galactic"), "World");
	worldLog->SetVisAttributes(G4VisAttributes(true, Colours::Air()));

	auto const targetSolid = new G4Tubs("TargetSolid", 0. * cm, wordRadius,
			targetWidth / 2, 0. * deg, 360. * deg);
	auto const targetLog = new G4LogicalVolume(targetSolid,
			nist->FindOrBuildMaterial("G4_Cu"), "Target");
	targetLog->SetVisAttributes(G4VisAttributes(Colours::Copper()));
	auto const limits = new G4UserLimits;
	limits->SetMaxAllowedStep(targetWidth / 100);
	targetLog->SetUserLimits(limits);
	new G4PVPlacement(nullptr, G4ThreeVector(0., 0., targetWidth / 2),
			targetLog, "TargetPhys", worldLog, false, 0);

	auto const worldPhys = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.),
			worldLog, "WorldPhys", nullptr, false, 0);

	return worldPhys;
}

G4VPhysicalVolume* Detector::Construct() {
	auto const physiworld = CreateWorld();
	return physiworld;
}

}

