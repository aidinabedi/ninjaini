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

#include "NinjaValue.h"

#include <cstdlib>

namespace Ninja {


//-----------------------------------------------------------------------------

	void Value::removeQuotes(void) {
		if (m_strValue.empty()) return;

		std::string::iterator s = m_strValue.begin();
		if (strchr("\"“”", *s) == NULL) return;
		++s;

		std::string::iterator e = m_strValue.end();
		if (strchr("\"“”", *(--e)) == NULL) ++e;

		m_strValue.assign(s, e);
	}


//-----------------------------------------------------------------------------

	bool Value::needQuotes(void) const {
		if (m_strValue.empty()) return false;

		std::string::const_iterator s = m_strValue.begin();
		if (*s == ' ') return true;

		std::string::const_iterator e = m_strValue.end();
		if (*(--e) == ' ') return true;

		return false;
	}


//-----------------------------------------------------------------------------

	void Value::set(int a) {
		std::stringstream ss;

		ss << a;
		set(ss.str());
	}


//-----------------------------------------------------------------------------

	void Value::set(double a) {
		std::stringstream ss;

		ss << a;
		set(ss.str());
	}


//-----------------------------------------------------------------------------
		
	bool Value::parse(int &a) const {
		if (m_strValue.empty()) return false;

		const char* s = m_strValue.c_str();
		const char* e1 = s + m_strValue.length();
		char* e2;

		a = strtol(s, &e2, 0);
		return (e1 == e2);
	}


//-----------------------------------------------------------------------------

	bool Value::parse(bool &a) const {
		const char* s = m_strValue.c_str();

		if (strcmp(s, "1") == 0 || strcasecmp(s, "true") == 0) {
			a = true;
			return true;

		} else if (strcmp(s, "0") == 0 || strcasecmp(s, "false") == 0) {
			a = false;
			return true;

		} else {
			return false;
		}
	}


//-----------------------------------------------------------------------------

	bool Value::parse(double &a) const {
		if (m_strValue.empty()) return false;

		const char* s = m_strValue.c_str();
		const char* e1 = s + m_strValue.length();
		char* e2;

		a = strtod(s, &e2);
		return (e1 == e2);
	}

} // namespace Ninja
