#pragma once

#include <G4Colour.hh>

namespace lhcs {

namespace repository {

/**
 * Collections of standard colors
 */
class Colours final {
public:

	Colours() = delete;

	static G4Colour Lead();
	static G4Colour Brass();
	static G4Colour Bronze();
	static G4Colour Steel();
	static G4Colour Aluminium();
	static G4Colour Copper();
	static G4Colour Concrete();
	static G4Colour Air();
	static G4Colour Water();

private:

	static G4Colour FromRGB(short red, short green, short blue);
	static G4Colour FromRGBA(short red, short green, short blue, short alpha);

};

}

}
