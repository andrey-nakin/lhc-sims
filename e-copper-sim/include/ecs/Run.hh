#pragma once

#include "G4Event.hh"
#include "G4Run.hh"

namespace ecs {

class Run: public G4Run {

public:
	Run();

	void RecordEvent(G4Event const*) override;
	void Merge(G4Run const*) override;

private:
};

}
