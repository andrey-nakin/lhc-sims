#include <ecs/DataRecord.hh>

namespace ecs {

DataRecord::DataRecord(G4Step const* const aStep) :
		prePos(aStep->GetPreStepPoint()->GetPosition().z()), postPos(
				aStep->GetPostStepPoint()->GetPosition().z()), energyDeposit(
				aStep->GetTotalEnergyDeposit()) {

}

}
