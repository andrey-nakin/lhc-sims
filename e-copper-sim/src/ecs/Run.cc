#include "ecs/Run.hh"

namespace ecs {

Run::Run() :
		G4Run() {
}

void Run::RecordEvent(G4Event const* const anEvent) {
	// according to Geant4 documentation, at the end of the implementation,
	// G4Run base-class method for must be invoked for recording data members in the base class.
	G4Run::RecordEvent(anEvent);
}

void Run::Merge(const G4Run* const aRun) {
	// according to Geant4 documentation, at the end of the implementation,
	// G4Run base-class method for must be invoked for merging data	members in the base class.
	G4Run::Merge(aRun);
}

}
