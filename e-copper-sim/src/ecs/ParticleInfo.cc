#include <G4SystemOfUnits.hh>
#include <ecs/ParticleInfo.hh>

namespace ecs {

ParticleInfo::ParticleInfo(G4double const initialEnergy,
		G4double const remainingEnergy) :
		fInitialEnergy(initialEnergy), fRemainingEnergy(remainingEnergy) {

}

std::ostream& ParticleInfo::Print(std::ostream& s) const {

	return s << fInitialEnergy / eV << '\t' << fRemainingEnergy / eV;

}

std::ostream& ParticleInfo::PrintHeader(std::ostream& s) {

	return s << "Initial (eV)\tRemaining (eV)\n";

}

}
