#include <G4SystemOfUnits.hh>
#include <ecs/DataRecord.hh>

namespace ecs {

DataRecord::DataRecord(G4Step const* const aStep) :
		prePos(aStep->GetPreStepPoint()->GetPosition().z()), postPos(
				aStep->GetPostStepPoint()->GetPosition().z()), energyDeposit(
				aStep->GetTotalEnergyDeposit()) {

}

std::ostream& DataRecord::Print(std::ostream& s) const {

	return s << prePos / um << '\t' << postPos / um << '\t'
			<< energyDeposit / eV;

}

std::ostream& DataRecord::PrintHeader(std::ostream& s) {
	return s << "# Start (um)\tStop (um)\tAbsorption (eV)" << G4endl;
}

}
