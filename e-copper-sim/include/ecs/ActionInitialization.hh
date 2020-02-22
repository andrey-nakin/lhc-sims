#pragma once

#include <vector>
#include <G4VUserActionInitialization.hh>

#include <ecs/Detector.hh>

namespace ecs {

class ActionInitialization: public G4VUserActionInitialization {
public:
	ActionInitialization(const G4String&, Detector& detector);

	void BuildForMaster() const override;
	void Build() const override;

private:
	G4String const fOutputFileSpec;
	Detector& detector;
};

}

