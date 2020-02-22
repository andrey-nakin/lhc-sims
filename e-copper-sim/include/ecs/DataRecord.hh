#pragma once

#include <G4Step.hh>

namespace ecs {

class DataRecord {
public:

	DataRecord(G4Step const* aStep);

private:
	G4double prePos, postPos;
	G4double energyDeposit;

};

}
