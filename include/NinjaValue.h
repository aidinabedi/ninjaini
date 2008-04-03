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

#ifndef NINJA_VALUE_H
#define NINJA_VALUE_H

#include "NinjaTools.h"

namespace Ninja { // tolua_export


//-----------------------------------------------------------------------------

	class Value { // tolua_export
	protected:

		std::string m_strValue;

		void removeQuotes(void);

		bool parse(int &a) const;
		bool parse(bool &a) const;
		bool parse(double &a) const;

	public:

		Value(void) {} // tolua_export
		Value(const char* value): m_strValue(value) { removeQuotes(); } // tolua_export
		Value(const std::string& value): m_strValue(value) { removeQuotes(); }
		~Value() {} // tolua_export

		// tolua_begin
		bool isDefined(void) const { return !m_strValue.empty(); }
		bool needQuotes(void) const;

		void set(int a);
		void set(bool a) { m_strValue = (a)? "true" : "false"; }
		void set(double a);
		void set(const char* a) { m_strValue = a; removeQuotes(); }
		void set(const std::string& a) { m_strValue = a; removeQuotes(); }

		int toInt(int a_default = 0) const { int x; return parse(x)? x : a_default; }
		bool toBool(bool a_default = false) const { bool x; return parse(x)? x : a_default; }
		double toDouble(double a_default = 0) const { double x; return parse(x)? x : a_default; }
		const char* toString(const char *a_default = "") const { return isDefined()? m_strValue.c_str() : a_default; }
		// tolua_end

		Value& operator =(int a) { set(a); return *this; }
		Value& operator =(bool a) { set(a); return *this; }
		Value& operator =(double a) { set(a); return *this; }
		Value& operator =(const char* a) { set(a); return *this; }
		Value& operator =(const std::string& a) { set(a); return *this; }

		operator int() const { return toInt(); }
		operator bool() const { return toBool(); }
		operator double() const { return toDouble(); }
		operator const char*() const { return toString(); }
		operator std::string() const { return m_strValue; }

		std::string str(void) const { std::stringstream ss; ss << *this; return ss.str(); } // tolua_export

		friend std::ostream& operator << (std::ostream &os, const Value &a) {
			if (a.needQuotes()) return os << '\"' << a.toString() << '\"';
			else return os << a.toString();
		}
	}; // tolua_export

} // namespace Ninja // tolua_export

#endif
