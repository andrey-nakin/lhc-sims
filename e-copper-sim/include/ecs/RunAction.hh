#pragma once

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <ecs/DataRecord.hh>
#include <ecs/ParticleInfo.hh>

class G4Run;

namespace ecs {

class RunAction: public G4UserRunAction {

public:
	RunAction(G4String const&);

	G4Run* GenerateRun() override;

	void BeginOfRunAction(G4Run const*) override;
	void EndOfRunAction(G4Run const*) override;

	void addDataRecord(DataRecord const&);
	void registerPassedParticle(G4double remainingEnergy);
	void registerBackScattering(G4double remainingEnergy);

private:
	G4String const fOutputFileSpec;
	std::vector<DataRecord> fData;
	std::vector<ParticleInfo> fPassed;
	std::vector<ParticleInfo> fBackscattered;
};

}
