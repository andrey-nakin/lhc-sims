#include <G4SystemOfUnits.hh>
#include <ecs/DataRecord.hh>

namespace ecs {

DataRecord::DataRecord(G4Step const* const aStep) :
		fPrePos(aStep->GetPreStepPoint()->GetPosition().z()), fPostPos(
				aStep->GetPostStepPoint()->GetPosition().z()), fEnergyDeposit(
				aStep->GetTotalEnergyDeposit()) {

}

std::ostream& DataRecord::Print(std::ostream& s) const {

	return s << fPrePos / um << '\t' << fPostPos / um << '\t'
			<< fEnergyDeposit / eV;

}

std::ostream& DataRecord::PrintHeader(std::ostream& s) {
	return s << "# Start (um)\tStop (um)\tAbsorption (eV)" << G4endl;
}

}
