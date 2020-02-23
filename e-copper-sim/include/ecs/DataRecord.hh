#pragma once

#include <iostream>
#include <G4Step.hh>

namespace ecs {

class DataRecord {
public:

	DataRecord(G4Step const* aStep);

	std::ostream& Print(std::ostream&) const;
	static std::ostream& PrintHeader(std::ostream&);

private:
	const G4double fPrePos, fPostPos;
	const G4double fEnergyDeposit;

};

}
