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

#ifndef NINJA_KEY_H
#define NINJA_KEY_H

#include "NinjaValue.h"
#include "NinjaName.h"
#include "NinjaArray.h"
#include "NinjaUndefined.h"

namespace Ninja { // tolua_export


//-----------------------------------------------------------------------------

	class Key : // tolua_export
		public Ninja::Array<Ninja::Value> // tolua_export
		, public Name
	{ // tolua_export
	public: // tolua_export

		Key(void) {} // tolua_export
		Key(const char* name): Name(name) {} // tolua_export
		Key(const std::string& name): Name(name) {}
		~Key() {} // tolua_export

		// tolua_begin	
		bool isDefined(void) const { return !isEmpty() && first().isDefined(); }

		Value& val(void) { if (isEmpty()) add(new Value()); return first(); }
		Value& val(int index) { return operator [](index); }

		void set(int a) { val().set(a); }
		void set(bool a) { val().set(a); }
		void set(double a) { val().set(a); }
		void set(const char* a) { val().set(a); }
		void set(const std::string& a) { val().set(a); }

		int toInt(void) { if (isEmpty()) throw Undefined(getName(), __FUNCTION__); else return val().toInt(); }
		bool toBool(void) { if (isEmpty()) throw Undefined(getName(), __FUNCTION__); else return val().toBool(); }
		double toDouble(void) { if (isEmpty()) throw Undefined(getName(), __FUNCTION__); else return val().toDouble(); }
		const char* toString(void) { if (isEmpty()) throw Undefined(getName(), __FUNCTION__); else return val().toString(); }

		int toInt(int a_default) { return val().toInt(a_default); }
		bool toBool(bool a_default) { return val().toBool(a_default); }
		double toDouble(double a_default) { return val().toDouble(a_default); }
		const char* toString(const char *a_default) { return val().toString(a_default); }
		// tolua_end

		Value& operator =(int a) { return val().operator =(a); }
		Value& operator =(bool a) { return val().operator =(a); }
		Value& operator =(double a) { return val().operator =(a); }
		Value& operator =(const char* a) { return val().operator =(a); }
		Value& operator =(const std::string& a) { return val().operator =(a); }

		operator int() { return val().operator int(); }
		operator bool() { return val().operator bool(); }
		operator double() { return val().operator double(); }
		operator const char*() { return val().operator const char*(); }
		operator std::string() { return val().operator std::string(); }

		// tolua_begin
		std::string str(void) const { std::stringstream ss; ss << *this; return ss.str(); }
		
		std::string strAsCmdLine(void) const {
			std::stringstream ss;
			
			for (int i = 0; i < size(); ++i)
				if (operator [](i).isDefined())
					ss << '-' << getName() << '=' << operator [](i) << ' ';
				
			return ss.str();
		}
				
		std::string strAsParameter(void) const {
			if (isEmpty()) return "";
			std::stringstream ss;
			ss << getName() << '=' << first();
			
			for (int i = 1; i < size(); ++i)
				ss << ", " << getName() << '=' << operator [](i);
				
			return ss.str();
		}
		// tolua_end

		friend std::ostream& operator << (std::ostream &os, const Key &a) {
			for (int i = 0; i < a.size(); ++i)
				if (a[i].isDefined()) os << a.getName() << '=' << a[i] << '\n';

			return os;
		}

		// tolua_begin
		const char* getName(void) const { return Name::getName(); }
		void setName(const char* name) { Name::setName(name); }
		// tolua_end

	}; // tolua_export

} // namespace Ninja // tolua_export

#endif
