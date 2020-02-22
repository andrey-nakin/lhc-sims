#include "ecs/PrimaryGeneratorAction.hh"

namespace ecs {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
		G4VUserPrimaryGeneratorAction(), fParticleGun(
				std::make_unique<G4GeneralParticleSource>()) {
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* const anEvent) {
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

}
