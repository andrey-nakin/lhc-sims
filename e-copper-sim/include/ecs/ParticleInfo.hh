#pragma once

#include <iostream>
#include <globals.hh>

namespace ecs {

class ParticleInfo {
public:

	ParticleInfo(G4double initialEnergy, G4double remainingEnergy);

	std::ostream& Print(std::ostream&) const;
	static std::ostream& PrintHeader(std::ostream&);

private:
	G4double fInitialEnergy, fRemainingEnergy;
};

}
