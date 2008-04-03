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

#ifndef NINJA_FILE_H
#define NINJA_FILE_H

#include "NinjaSection.h"

namespace Ninja { // tolua_export


//-----------------------------------------------------------------------------

	class File : // tolua_export
		public Ninja::AssociativeArray<Ninja::Section> // tolua_export
	{ // tolua_export
	private:

		const char* parseComment(const char* s);
		const char* parseSection(const char* s, Section **pp);
		const char* parseKey(const char* s, Section *p);

	public: // tolua_export

		// tolua_begin
		File(void) {}
		File(const File& a) { operator =(a); }
		File(const char* a_sFilename) { load(a_sFilename); }
		~File() {}

		void parse(const char* a_sData);
		bool load(const char* a_sFilename);
		bool save(const char* a_sFilename) const;
		// tolua_end

		Section& sec(const char* a) { return operator [](a); } // tolua_export
		Section& sec(const std::string& a) { return operator [](a); }
		Section& sec(int index) { return operator [](index); } // tolua_export

		std::string str(void) const { std::stringstream ss; ss << *this; return ss.str(); } // tolua_export

		friend std::ostream& operator << (std::ostream &os, const File &a) {
			if (a.isEmpty()) return os;
			os << a.first();

			for (int i = 1; i < a.size(); ++i) os << '\n' << a[i];
			return os;
		}

	}; // tolua_export

} // namespace Ninja // tolua_export

#endif
