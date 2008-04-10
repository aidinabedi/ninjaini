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

#ifndef NINJA_MAIN_H
#define NINJA_MAIN_H

#include "NinjaContainer.h"

namespace Ninja { // tolua_export


//-----------------------------------------------------------------------------

	class Main : // tolua_export
		public Ninja::Container // tolua_export
	{ // tolua_export
	protected:

		void parseArgument(const char* s);

	public: // tolua_export

		Main(void) {} // tolua_export
		Main(int argc, char *argv[]) { parse(argc, argv); }
		~Main() {} // tolua_export

		void parse(int argc, char *argv[]);

		map_type map(void);

		// tolua_begin
		std::string str(void) const {
			std::string s;

			for (int i = 0; i < size(); ++i)
				s += operator [](i).strAsCmdLine();

			return s;
		}
		// tolua_end

		operator Value*() { return new Value(str()); } // tolua_export

		friend std::ostream& operator << (std::ostream &os, const Main &a) {
			if (a.isEmpty()) return os;
			os << a.first().strAsCmdLine().c_str();

			for (int i = 1; i < a.size(); ++i)
				os << " " << a[i].strAsCmdLine().c_str();

			return os;
		}
	}; // tolua_export

} // namespace Ninja // tolua_export

#endif
