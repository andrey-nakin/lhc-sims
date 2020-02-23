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
	G4double prePos, postPos;
	G4double energyDeposit;

};

}
