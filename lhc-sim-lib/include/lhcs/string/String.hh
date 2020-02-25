#pragma once

#include <G4String.hh>

namespace lhcs {

namespace string {

class String final {

	String() = delete;

public:

	static G4String Format(G4String const& fmt, ...);

};

}

}
