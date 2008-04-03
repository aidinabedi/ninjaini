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

#include "NinjaFile.h"

#include <vector>
#include <fstream>

namespace Ninja {


//-----------------------------------------------------------------------------------

	const char* File::parseComment(const char* s) {
		s = strpbrk(s + 1, "\n\r");
		return (s)? s+1 : NULL;
	}


//-----------------------------------------------------------------------------------

	const char* File::parseSection(const char* s, Section **pp) {
		const char *e = strpbrk(s + 1, "]\n\r");
		if (!e) return NULL;

		s++;
		if (*e == ']') {
			std::string name(TrimLeft(s, e), TrimRight(s, e));

			*pp = &sec(name);
		}

		return e + 1;
	}


//-----------------------------------------------------------------------------------

	const char* File::parseKey(const char* s, Section *p) {
		const char *e = strpbrk(s, "=\n\r");
		if (!e) return NULL;

		if (*e == '=') {
			std::string name(s, TrimRight(s, e));

			if (!p) {
				add(new Section());
				p = &last();
			}

			Key* key = &p->key(name);

			s = e + 1;
			e = strpbrk(e + 1, "\n\r");
			if (!e) return NULL;

			s = TrimLeft(s, e);
			std::string value(s, TrimRight(s, e));

			key->add(new Value(value));
		}

		return e + 1;
	}


//-----------------------------------------------------------------------------------

	void File::parse(const char* a_sData) {
		Section *pLastSection = NULL;
		const char *s = a_sData;

		clear();

		for (;;) {
			switch (*s) {
				case '\0':
					return;

				case ' ':
				case '\t':
				case '\r':
				case '\n':
					s++;
					break;

				case '#':
				case ';':
					s = parseComment(s);
					if (s) break;
					else return;

				case '[':
					s = parseSection(s, &pLastSection);
					if (s) break;
					else return;

				default:
					s = parseKey(s, pLastSection);
					if (s) break;
					else return;
			}
		};
	}


//-----------------------------------------------------------------------------------

	bool File::load(const char *a_sFilename) {
		std::ifstream file(a_sFilename, std::ios::in | std::ios::ate | std::ios::binary);
		if (!file.is_open()) return false;

		std::streamsize size = file.tellg();
		std::vector<char> buffer(size + 1);
		buffer.back() = '\0';

		file.seekg(0, std::ios_base::beg);
		file.read(&buffer[0], size);

		parse(&buffer[0]);
		return true;
	}


//-----------------------------------------------------------------------------------

	bool File::save(const char *a_sFilename) const {
		std::ofstream file(a_sFilename, std::ios::out);
		if (!file.is_open()) return false;

		file << *this;
		return true;
	}

}
