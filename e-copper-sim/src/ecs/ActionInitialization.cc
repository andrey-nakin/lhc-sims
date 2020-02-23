#include "globals.hh"

#include "ecs/ActionInitialization.hh"
#include "ecs/RunAction.hh"
#include "ecs/PrimaryGeneratorAction.hh"
#include "ecs/SteppingAction.hh"

namespace ecs {

ActionInitialization::ActionInitialization(G4String const& outputFile,
		Detector& aDetector) :
		G4VUserActionInitialization(), fOutputFileSpec(outputFile), fDetector(
				aDetector) {
}

void ActionInitialization::BuildForMaster() const {

	SetUserAction(new RunAction(fOutputFileSpec));

}

void ActionInitialization::Build() const {

	auto const runAction = new RunAction(fOutputFileSpec);
	SetUserAction(runAction);
	SetUserAction(new PrimaryGeneratorAction);
	SetUserAction(new SteppingAction(fDetector, *runAction));

}

}
