#pragma once

#include <G4UserSteppingAction.hh>

#include <ecs/Detector.hh>

namespace ecs {

class SteppingAction: public G4UserSteppingAction {
public:

	SteppingAction(Detector&);

	void UserSteppingAction(G4Step const*) override;

private:
	Detector& detector;
};

}
