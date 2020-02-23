#include "globals.hh"

#include "ecs/ActionInitialization.hh"
#include "ecs/RunAction.hh"
#include "ecs/PrimaryGeneratorAction.hh"
#include "ecs/SteppingAction.hh"

namespace ecs {

ActionInitialization::ActionInitialization(G4String const& outputFile,
		G4String const& passedFileName, G4String const& backscatteredFileName,
		Detector& aDetector) :
		G4VUserActionInitialization(), fOutputFileSpec(outputFile), fPassedFileName(
				passedFileName), fBackscatteredFileName(backscatteredFileName), fDetector(
				aDetector) {
}

void ActionInitialization::BuildForMaster() const {

	SetUserAction(
			new RunAction(fOutputFileSpec, fPassedFileName,
					fBackscatteredFileName));

}

void ActionInitialization::Build() const {

	auto const runAction = new RunAction(fOutputFileSpec, fPassedFileName,
			fBackscatteredFileName);
	SetUserAction(runAction);
	SetUserAction(new PrimaryGeneratorAction);
	SetUserAction(new SteppingAction(fDetector, *runAction));

}

}
