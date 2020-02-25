#pragma once

#include <G4String.hh>

namespace lhcs {

namespace string {

class String {

	String();

public:

	static G4String Format(G4String const& fmt, ...);

};

}

}
