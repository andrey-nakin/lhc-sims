#include <fstream>
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

	fData.clear();
	fPassed.clear();
	fBackscattered.clear();

}

void RunAction::EndOfRunAction(G4Run const* aRun) {

	std::ofstream s(fOutputFileSpec);
	DataRecord::PrintHeader(s);
	std::for_each(fData.begin(), fData.end(), [&s](DataRecord const& dr) {
		dr.Print(s) << '\n';
	});

	// TODO const Run* theRun = dynamic_cast<const Run*>(aRun);
	// TODO assert(0 != theRun);

	// TODO theRun->DumpData(fOutputFileSpec);
}

void RunAction::addDataRecord(DataRecord const& aDr) {

	fData.push_back(aDr);

}

void RunAction::registerPassedParticle(G4double const initialEnergy,
		G4double const remainingEnergy) {

	fPassed.push_back(ParticleInfo(initialEnergy, remainingEnergy));

}

void RunAction::registerBackScattering(G4double const initialEnergy,
		G4double const remainingEnergy) {

	fBackscattered.push_back(ParticleInfo(initialEnergy, remainingEnergy));

}

}
