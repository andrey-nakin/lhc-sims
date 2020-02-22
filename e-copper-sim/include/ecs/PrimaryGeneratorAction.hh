#pragma once

#include <memory>
#include "G4VUserPrimaryGeneratorAction.hh"
#include <G4GeneralParticleSource.hh>

namespace ecs {

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction {
public:
	PrimaryGeneratorAction();

	void GeneratePrimaries(G4Event*) override;

private:
	std::unique_ptr<G4GeneralParticleSource> const fParticleGun;
};

}
