#pragma once

#include <G4UserSteppingAction.hh>

#include <ecs/Detector.hh>
#include <ecs/RunAction.hh>

namespace ecs {

class SteppingAction: public G4UserSteppingAction {
public:

	SteppingAction(Detector&, RunAction&);

	void UserSteppingAction(G4Step const*) override;

private:
	Detector& fDetector;
	RunAction& fRunAction;
};

}
