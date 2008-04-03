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

#ifndef NINJA_SECTION_H
#define NINJA_SECTION_H

#include "NinjaName.h"
#include "NinjaContainer.h"

namespace Ninja { // tolua_export


//-----------------------------------------------------------------------------

	class Section : // tolua_export
		public Ninja::Container // tolua_export
		, public Name
	{ // tolua_export	
	public: // tolua_export

		Section(void) {} // tolua_export
		Section(const char* name): Name(name) {} // tolua_export
		Section(const std::string& name): Name(name) {}
		~Section() {} // tolua_export

		std::string str(void) const { std::stringstream ss; ss << *this; return ss.str(); } // tolua_export

		friend std::ostream& operator << (std::ostream &os, const Section &a) {
			if (*a.getName() != '\0') os << '[' << a.getName() << "]\n";
			for (int i = 0; i < a.size(); ++i) os << a[i];

			return os;
		}

		// tolua_begin
		const char* getName(void) const { return Name::getName(); }
		void setName(const char* name) { Name::setName(name); }
		// tolua_end

	}; // tolua_export

} // namespace Ninja // tolua_export

#endif
