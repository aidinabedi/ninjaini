/*
The zlib/libpng License

Copyright (c) 2007 Aidin Abedi (http://sourceforge.net/projects/ninjaini)

This software is provided 'as-is', without any express or implied warranty. In no event will
the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following
restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that 
       you wrote the original software. If you use this software in a product, 
       an acknowledgment in the product documentation would be appreciated but is 
       not required.

    2. Altered source versions must be plainly marked as such, and must not be 
       misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/

#include "NinjaContainer.h"

namespace Ninja {


//-----------------------------------------------------------------------------

	void Container::parse(int argc, char *argv[]) {
		for (int i = 0; i < argc; i++)
			parseArgument(argv[i]);
	}


//-----------------------------------------------------------------------------------

	void Container::parseArgument(const char* s) {
		if (*(s++) != '-') return;
		const char* e = strchr(s, '=');

		if (!e) {
			key(s).add(new Value("true"));

		} else if (*e == '=') {
			std::string name(s, e);

			key(name).add(new Value(e + 1));
		}
	}


//-----------------------------------------------------------------------------

	Container::map_type Container::map(void) {
		map_type mapPairArray;

		for (int i = 0; i < size(); ++i)
			mapPairArray.insert(pair_type(operator [](i).getName(), operator [](i).toString()));

		return mapPairArray;
	}


//-----------------------------------------------------------------------------------

	const char* Container::parseParam(const char* s) {
		const char* e = strpbrk(s, "=,)");
		if (!e) return NULL;

		if (*e == '=') {
			std::string name(s, TrimRight(s, e));

			s = e + 1;
			e = strpbrk(s, ",)");
			if (!e) e = s + strlen(s);

			std::string value(TrimLeft(s, e), TrimRight(s, e));
			key(name).add(new Value(value));

			if (!*e) return NULL;
		}

		return e + 1;
	}


//-----------------------------------------------------------------------------------

	void Container::parse(const char* a_sData) {
		const char *s = a_sData;

		s = strchr(s, '(');
		if (!s) return;
		else s++;

		while (*s != '\0') {
			while (*s == ' ') s++;

			s = parseParam(s);
			if (!s) return;
		}
	}

}
