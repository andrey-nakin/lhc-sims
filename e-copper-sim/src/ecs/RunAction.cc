#include <fstream>
#include "G4Run.hh"
#include "G4RunManager.hh"
#include <G4SystemOfUnits.hh>

#include "ecs/RunAction.hh"
#include "lhcs/string/String.hh"

namespace ecs {

RunAction::RunAction(G4String const& outputFile, G4String const& passedFileName,
		G4String const& backscatteredFileName, Detector& aDetector) :
		G4UserRunAction(), fHistFileNameTemplate("run-%03d"), fOutputFileSpec(
				outputFile), fPassedFileName(passedFileName), fBackscatteredFileName(
				backscatteredFileName), fDetector(aDetector), fAnalysisManager(
				std::unique_ptr < G4AnalysisManager
						> (G4Analysis::ManagerInstance("root"))), fEnergyLossHisto(
				fAnalysisManager->CreateH1("energy-loss",
						"Energy loss of passed particles", 1000, 0.,
						1000. * keV, "keV")), fBackscatteredEnergyLossHisto(
				fAnalysisManager->CreateH1("backscattered-energy-loss",
						"Energy loss of backscattered particles", 1000, 0.,
						1000. * keV, "keV")), fEnergyPerStepHisto(
				fAnalysisManager->CreateH1("energy-absorption-per-step",
						"Energy absorption per MC step", 1000, 0., 10000. * eV,
						"eV")), fNIEnergyPerStepHisto(
				fAnalysisManager->CreateH1("ni-energy-absorption-per-step",
						"Non-ionization energy absorption per MC step", 1000,
						0., 1000. * eV, "eV")), fStepLengthHisto(
				fAnalysisManager->CreateH1("mc-step-length",
						"Monte-Carlo step length within target", 1000, 0.,
						10. * um, "um")) {

	G4RunManager::GetRunManager()->SetPrintProgress(100);

}

void RunAction::BeginOfRunAction(G4Run const* run) {

	using namespace lhcs::string;

	fData.clear();
	fData.resize(
			static_cast<decltype(fData.size())>(fDetector.GetTargetWidth() / um
					+ 0.5));
	fPassed.clear();
	fBackscattered.clear();

	fAnalysisManager->OpenFile(
			String::Format(fHistFileNameTemplate, run->GetRunID()));

}

void RunAction::EndOfRunAction(G4Run const* run) {

	using namespace lhcs::string;

	Dump(String::Format(fPassedFileName, run->GetRunID()), fPassed);
	Dump(String::Format(fBackscatteredFileName, run->GetRunID()),
			fBackscattered);

	std::ofstream s(String::Format(fOutputFileSpec, run->GetRunID()));
	s << "# Pos (um)\tEnergy (eV)\n";

	auto x = 0.;
	for (decltype(fData.size()) i = 0; i < fData.size(); i++) {
		x += fDetector.GetTargetWidth() / fData.size();
		s << x / um << '\t' << fData[i] / eV << '\n';
	}

	fAnalysisManager->Write();
	fAnalysisManager->CloseFile();

}

void RunAction::addDataRecord(G4double const pos, G4double const energy,
		G4double const nonIonizationEnergy, G4double const stepLen) {

	auto const i = static_cast<decltype(fData.size())>(pos
			/ fDetector.GetTargetWidth() * fData.size());
	if (i < fData.size()) {
		fData[i] += energy;
	}

	if (energy > 0.) {
		fAnalysisManager->FillH1(fEnergyPerStepHisto, energy);
	}
	if (nonIonizationEnergy > 0.) {
		fAnalysisManager->FillH1(fNIEnergyPerStepHisto, nonIonizationEnergy);
	}
	fAnalysisManager->FillH1(fStepLengthHisto, stepLen);

}

void RunAction::registerPassedParticle(G4double const initialEnergy,
		G4double const remainingEnergy) {

	fPassed.push_back(ParticleInfo(initialEnergy, remainingEnergy));
	fAnalysisManager->FillH1(fEnergyLossHisto, initialEnergy - remainingEnergy);

}

void RunAction::registerBackScattering(G4double const initialEnergy,
		G4double const remainingEnergy) {

	fBackscattered.push_back(ParticleInfo(initialEnergy, remainingEnergy));
	fAnalysisManager->FillH1(fBackscatteredEnergyLossHisto,
			initialEnergy - remainingEnergy);

}

}
