#include <fstream>
#include "G4Run.hh"
#include "G4RunManager.hh"
#include <G4SystemOfUnits.hh>

#include "ecs/RunAction.hh"
#include "ecs/Run.hh"

namespace ecs {

RunAction::RunAction(G4String const& outputFile, G4String const& passedFileName,
		G4String const& backscatteredFileName, Detector& aDetector) :
		G4UserRunAction(), fOutputFileSpec(outputFile), fPassedFileName(
				passedFileName), fBackscatteredFileName(backscatteredFileName), fDetector(
				aDetector) {

	G4RunManager::GetRunManager()->SetPrintProgress(100000);

}

G4Run* RunAction::GenerateRun() {

	return new Run();

}

void RunAction::BeginOfRunAction(G4Run const*) {

	fData.clear();
	fData.resize(
			static_cast<decltype(fData.size())>(fDetector.GetTargetWidth() / um
					+ 0.5));
	fPassed.clear();
	fBackscattered.clear();

}

void RunAction::EndOfRunAction(G4Run const*) {

	Dump(fPassedFileName, fPassed);
	Dump(fBackscatteredFileName, fBackscattered);

	std::ofstream s(fOutputFileSpec);
	s << "# Pos (um)\tEnergy (eV)\n";

	auto x = 0.;
	for (decltype(fData.size()) i = 0; i < fData.size(); i++) {
		x += fDetector.GetTargetWidth() / fData.size();
		s << x / um << '\t' << fData[i] / eV << '\n';
	}

}

void RunAction::addDataRecord(G4double const pos, G4double const energy) {

	auto const i = static_cast<decltype(fData.size())>(pos
			/ fDetector.GetTargetWidth() * fData.size());
	if (i < fData.size()) {
		fData[i] += energy;
	}

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
