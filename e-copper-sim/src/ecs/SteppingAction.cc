#include <globals.hh>
#include <G4Step.hh>
#include <G4SystemOfUnits.hh>

#include <ecs/SteppingAction.hh>

namespace ecs {

SteppingAction::SteppingAction(Detector& aDetector, RunAction& aRunAction) :
		G4UserSteppingAction(), fDetector(aDetector), fRunAction(aRunAction) {
}

void SteppingAction::UserSteppingAction(G4Step const* const aStep) {
	auto const track = aStep->GetTrack();

	if (track->GetTrackID() != 1) {
		return;
	}

	if (aStep->GetPostStepPoint()->GetPosition().z()
			> fDetector.GetTargetWidth()) {
		// particle passed through the target
		if (aStep->IsFirstStepInVolume()) {
			fRunAction.registerPassedParticle(track->GetVertexKineticEnergy(),
					track->GetKineticEnergy());
		}
		track->SetTrackStatus(fStopAndKill);
		return;
	} else if (aStep->GetPostStepPoint()->GetPosition().z() < 0.) {
		// back-scattered particle
		if (aStep->IsFirstStepInVolume()) {
			fRunAction.registerBackScattering(track->GetVertexKineticEnergy(),
					track->GetKineticEnergy());
		}
		track->SetTrackStatus(fStopAndKill);
		return;
	} else if (aStep->GetTotalEnergyDeposit() > 0.) {
		// register energy absorption
		fRunAction.addDataRecord(aStep->GetPostStepPoint()->GetPosition().z(),
				aStep->GetTotalEnergyDeposit(),
				aStep->GetNonIonizingEnergyDeposit(), aStep->GetStepLength());
	}
}

}
