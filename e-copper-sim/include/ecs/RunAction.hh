#pragma once

#include <memory>
#include <G4UserRunAction.hh>
#include <globals.hh>
#include <g4analysis.hh>

#include <ecs/ParticleInfo.hh>
#include <ecs/Detector.hh>

class G4Run;

namespace ecs {

class RunAction: public G4UserRunAction {

public:
	RunAction(G4String const&, G4String const& passedFileName,
			G4String const& backscatteredFileName, Detector& aDetector);

	void BeginOfRunAction(G4Run const*) override;
	void EndOfRunAction(G4Run const*) override;

	void addDataRecord(G4double pos, G4double energy,
			G4double nonIonizationEnergy, G4double stepLen);
	void registerPassedParticle(G4double initialEnergy,
			G4double remainingEnergy);
	void registerBackScattering(G4double initialEnergy,
			G4double remainingEnergy);

private:
	G4String const fHistFileNameTemplate;
	G4String const fOutputFileSpec, fPassedFileName, fBackscatteredFileName;
	Detector& fDetector;
	std::unique_ptr<G4AnalysisManager> const fAnalysisManager;
	G4int const fEnergyLossHisto, fBackscatteredEnergyLossHisto,
			fEnergyPerStepHisto, fNIEnergyPerStepHisto, fStepLengthHisto;
	std::vector<G4double> fData;
	std::vector<ParticleInfo> fPassed;
	std::vector<ParticleInfo> fBackscattered;

	template<typename T>
	void Dump(G4String const& fileName, std::vector<T> const& src) {
		std::ofstream s(fileName);
		T::PrintHeader(s);
		std::for_each(src.begin(), src.end(), [&s](T const& dr) {
			dr.Print(s) << '\n';
		});

	}

};

}
