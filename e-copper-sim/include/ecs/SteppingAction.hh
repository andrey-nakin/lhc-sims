#pragma once

#include <G4UserSteppingAction.hh>

namespace ecs {

class SteppingAction: public G4UserSteppingAction {
public:

	SteppingAction();

	void UserSteppingAction(G4Step const*) override;

};

}
