#include "G4Run.hh"
#include "G4RunManager.hh"
#include <assert.h>

#include "ecs/RunAction.hh"
#include "ecs/Run.hh"

namespace ecs {

RunAction::RunAction(G4String const& outputFile) :
		G4UserRunAction(), fOutputFileSpec(outputFile) {
	G4RunManager::GetRunManager()->SetPrintProgress(100000);
}

G4Run* RunAction::GenerateRun() {
	return new Run();
}

void RunAction::BeginOfRunAction(G4Run const*) {
	data.clear();
}

void RunAction::EndOfRunAction(G4Run const* aRun) {

	G4cout << "Number of Events Processed:" << aRun->GetNumberOfEvent()
			<< G4endl;

	// TODO const Run* theRun = dynamic_cast<const Run*>(aRun);
	// TODO assert(0 != theRun);

	// TODO theRun->DumpData(fOutputFileSpec);
}

}
