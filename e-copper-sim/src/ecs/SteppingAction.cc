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
			<< aStep->GetTotalEnergyDeposit() / eV << ", "
			<< aStep->IsFirstStepInVolume() << ", "
			<< aStep->GetTrack()->GetTrackID() << ", "
			<< aStep->GetTrack()->GetKineticEnergy() / eV << ", "
			<< aStep->GetTrack()->GetVertexKineticEnergy() / eV << ")"
			<< G4endl;

	if (aStep->GetTrack()->GetTrackID() != 1) {
		return;
	}

	if (aStep->GetPostStepPoint()->GetPosition().z()
			> detector.getTargetWidth()) {
		// particle passed through the target
		if (aStep->IsFirstStepInVolume()) {
			runAction.registerPassedParticle(
					aStep->GetTrack()->GetVertexKineticEnergy(),
					aStep->GetTrack()->GetKineticEnergy());
		}
	} else if (aStep->GetPostStepPoint()->GetPosition().z() < 0.) {
		// back-scattered particle
		if (aStep->IsFirstStepInVolume()) {
			runAction.registerBackScattering(
					aStep->GetTrack()->GetVertexKineticEnergy(),
					aStep->GetTrack()->GetKineticEnergy());
		}
	} else if (aStep->GetTotalEnergyDeposit() > 0.) {
		// register energy absorption
		runAction.addDataRecord(DataRecord(aStep));
	}
}

}
