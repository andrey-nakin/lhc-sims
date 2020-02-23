#pragma once

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <ecs/DataRecord.hh>
#include <ecs/ParticleInfo.hh>

class G4Run;

namespace ecs {

class RunAction: public G4UserRunAction {

public:
	RunAction(G4String const&, G4String const& passedFileName,
			G4String const& backscatteredFileName);

	G4Run* GenerateRun() override;

	void BeginOfRunAction(G4Run const*) override;
	void EndOfRunAction(G4Run const*) override;

	void addDataRecord(DataRecord const&);
	void registerPassedParticle(G4double initialEnergy,
			G4double remainingEnergy);
	void registerBackScattering(G4double initialEnergy,
			G4double remainingEnergy);

private:
	G4String const fOutputFileSpec, fPassedFileName, fBackscatteredFileName;
	std::vector<DataRecord> fData;
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
