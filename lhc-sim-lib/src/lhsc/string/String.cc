#include <cstdio>
#include <cstdarg>
#include <lhcs/string/String.hh>

namespace lhcs {

namespace string {

G4String String::Format(G4String const& fmt, ...) {

	char buffer[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	return G4String(buffer);

}

}

}
