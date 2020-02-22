#include <globals.hh>
#include <G4Step.hh>
#include <G4SystemOfUnits.hh>

#include <ecs/SteppingAction.hh>

namespace ecs {

SteppingAction::SteppingAction(Detector& aDetector, RunAction& aRunAction) :
		G4UserSteppingAction(), detector(aDetector), runAction(aRunAction) {
}

void SteppingAction::UserSteppingAction(G4Step const* aStep) {
	G4cout << "SteppingAction::UserSteppingAction("
			<< aStep->GetPreStepPoint()->GetPosition().z() / um << ", "
			<< aStep->GetPostStepPoint()->GetPosition().z() / um << ", "
			<< aStep->GetTotalEnergyDeposit() / eV << ")" << G4endl;

	if (aStep->GetTotalEnergyDeposit() > 0.
			&& aStep->GetPreStepPoint()->GetPosition().z() >= 0.
			&& aStep->GetPostStepPoint()->GetPosition().z() > 0.
			&& aStep->GetPostStepPoint()->GetPosition().z()
					< detector.getTargetWidth()) {
		// register energy absorption
		runAction.addDataRecord(DataRecord(aStep));
	}
}

}
