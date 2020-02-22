#include <globals.hh>
#include <G4Step.hh>
#include <G4SystemOfUnits.hh>

#include <ecs/SteppingAction.hh>

namespace ecs {

SteppingAction::SteppingAction() :
		G4UserSteppingAction() {
}

void SteppingAction::UserSteppingAction(G4Step const* aStep) {
	G4cout << "SteppingAction::UserSteppingAction("
			<< aStep->GetPreStepPoint()->GetPosition().z() / um << ", "
			<< aStep->GetPostStepPoint()->GetPosition().z() / um << ", "
			<< aStep->GetTotalEnergyDeposit() / eV << ")" << G4endl;
}

}
