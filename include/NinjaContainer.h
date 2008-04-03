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

#ifndef NINJA_CONTAINER_H
#define NINJA_CONTAINER_H

#include "NinjaKey.h"
#include "NinjaArray.h"

#include <map>

namespace Ninja { // tolua_export


//-----------------------------------------------------------------------------

	class Container : // tolua_export
		public Ninja::AssociativeArray<Ninja::Key> // tolua_export
	{ // tolua_export
	protected:

		void parseArgument(const char* s);

		const char* parseParam(const char* s);

	public: // tolua_export

		typedef std::map<std::string, std::string> map_type;
		typedef std::pair<std::string, std::string> pair_type;

		Container(void) {} // tolua_export
		Container(Key& k) { parse(k.toString()); } // tolua_export
		Container(const Value& v) { parse(v.toString()); } // tolua_export
		Container(const char *a_sValue) { parse(a_sValue); } // tolua_export
		Container(int argc, char *argv[]) { parse(argc, argv); }
		~Container() {} // tolua_export

		void parse(const char* a_sData); // tolua_export
		void parse(int argc, char *argv[]);

		Key& key(const char* a) { return operator [](a); } // tolua_export
		Key& key(const std::string& a) { return operator [](a); }
		Key& key(int index) { return operator [](index); } // tolua_export

		map_type map(void);

		// tolua_begin
		std::string str(void) const { std::stringstream ss; ss << *this; return ss.str(); }

		std::string strAsCmdLine(void) const {
			std::string s;

			for (int i = 0; i < size(); ++i)
				s += operator [](i).strAsCmdLine();

			return s;
		}
		// tolua_end

		Container& operator =(const Value &a) { parse(a); return *this; }
		operator Value*() { return new Value(str()); } // tolua_export

		friend std::ostream& operator << (std::ostream &os, const Container &a) {
			if (a.isEmpty()) return os;
			os << "(" << a.first().strAsParameter().c_str();

			for (int i = 1; i < a.size(); ++i)
				os << ", " << a[i].strAsParameter().c_str();

			return os << ")";
		}
	}; // tolua_export

} // namespace Ninja // tolua_export

#endif
