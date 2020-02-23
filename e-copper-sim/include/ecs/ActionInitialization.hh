#pragma once

#include <vector>
#include <G4VUserActionInitialization.hh>

#include <ecs/Detector.hh>

namespace ecs {

class ActionInitialization: public G4VUserActionInitialization {
public:
	ActionInitialization(G4String const&, G4String const& passedFileName,
			G4String const& backscatteredFileName, Detector& detector);

	void BuildForMaster() const override;
	void Build() const override;

private:
	G4String const fOutputFileSpec, fPassedFileName, fBackscatteredFileName;
	Detector& fDetector;
};

}

