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

#ifndef NINJA_ARRAY_H
#define NINJA_ARRAY_H

#include "NinjaTools.h"

namespace Ninja { // tolua_export


//-----------------------------------------------------------------------------

	template <class T>
	class Array { // tolua_export
		TEMPLATE_BIND((T, Ninja::Section, Ninja::Key, Ninja::Value)); // tolua_export

	public:

		typedef std::vector<T*> vector_type;
		typedef typename vector_type::iterator iterator;
		typedef typename vector_type::const_iterator const_iterator;
		typedef typename vector_type::reverse_iterator reverse_iterator;
		typedef typename vector_type::const_reverse_iterator const_reverse_iterator;

	protected:

		vector_type m_Array;

	public: // tolua_export

		Array(void) {}
		//Array(const Array<T>& a) { operator =(a); }
		~Array() { clear(); }

		vector_type& getVector(void) { return m_Array; }
		const vector_type& getVector(void) const { return m_Array; }

		iterator begin(void) { return m_Array.begin(); }
		const_iterator begin(void) const { return m_Array.begin(); }

		iterator end(void) { return m_Array.end(); }
		const_iterator end(void) const { return m_Array.end(); }

		reverse_iterator rbegin(void) { return m_Array.rbegin(); }
		const_reverse_iterator rbegin(void) const { return m_Array.rbegin(); }

		reverse_iterator rend(void) { return m_Array.rend(); }
		const_reverse_iterator rend(void) const { return m_Array.rend(); }

		// tolua_begin
		T& first(void) { return *(m_Array.front()); }
		const T& first(void) const { return *(m_Array.front()); }

		T& last(void) { return *(m_Array.back()); }
		const T& last(void) const { return *(m_Array.back()); }

		void add(T* a) { m_Array.push_back(a); }

		void remove(int index) {
			delete m_Array[index];
			m_Array.erase(m_Array.begin() + index);
		}

		int size(void) const { return static_cast<int>(m_Array.size()); }
		bool isEmpty(void) const { return m_Array.empty(); }

		void clear(void) {
			for (int i = 0; i < size(); ++i)
				delete m_Array[i];

			m_Array.clear();
		}
		// tolua_end

		T& operator [](int index) { return *(m_Array[index]); }
		const T& operator [](int index) const { return *(m_Array[index]); }

		/*
		Array<T>& operator =(const Array<T>& a) {
			clear();
			m_Array.resize(a.size());

			for (int i = 0; i < a.size(); ++i)
				*(m_Array[i] = new T) = a[i];

			return *this;
		}
		*/
	}; // tolua_export


//-----------------------------------------------------------------------------

	template <class T>
	class AssociativeArray: public Array<T> { // tolua_export
		TEMPLATE_BIND((T, Ninja::Section, Ninja::Key)); // tolua_export

	public: // tolua_export

		AssociativeArray(void) {}
		//AssociativeArray(const AssociativeArray<T>& a) { operator =(a); }

		// tolua_begin
		T* find(const char *name) {
			for (int i = 0; i < Array<T>::size(); ++i)
				if (strcasecmp(name, operator [](i).getName()) == 0)
					return &operator [](i);

			return NULL;
		}

		const T* find(const char *name) const {
			for (int i = 0; i < Array<T>::size(); ++i)
				if (strcasecmp(name, operator [](i).getName()) == 0)
					return &operator [](i);

			return NULL;
		}

		void remove(const char *name) {
			for (int i = 0; i < Array<T>::size(); ++i)
				if (strcasecmp(name, operator [](i).getName()) == 0)
					Array<T>::remove(i);
		}
		// tolua_end

		T& operator [](const char *name) {
			T* pItem = find(name);
			if (pItem) return *pItem;

			pItem = new T(name);
			add(pItem);
			return *pItem;
		}

		T* find(const std::string& name) { return find(name.c_str()); }
		const T* find(const std::string& name) const { return find(name.c_str()); }
		void remove(const std::string& name) { remove(name.c_str()); }
		T& operator [](const std::string& name) { return operator [](name.c_str()); }

		T& operator [](int index) { return Array<T>::operator [](index); }
		const T& operator [](int index) const { return Array<T>::operator [](index); }

		/*
		AssociativeArray<T>& operator =(const AssociativeArray<T>& a) {
			Array<T>::operator =(a);
			return *this;
		}
		*/
	}; // tolua_export

} // namespace Ninja // tolua_export

#endif
