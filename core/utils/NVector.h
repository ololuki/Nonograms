/**********************************************************************
 * Copyright (C) 2017 - 2021 Ololuki
 * https://ololuki.pl
 * 
 * This file is part of Nonograms
 * https://github.com/ololuki/nonograms
 * 
 * Nonograms is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Nonograms is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nonograms.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************/
#ifndef NVECTOR_H
#define NVECTOR_H

#include <vector>


///////////////////////////////////////////////////////////////////////
/// std::vector uses size_t which leads to warnings in comparision with
/// int used by Qt. QVector uses int, but types inside vector needs to
/// has defined default constructors, so I write my own vector wrapper
/// which takes indexes as int and do not need default constructors
/// of kept classes
///////////////////////////////////////////////////////////////////////
template <class T>
class NVector
{
public:
	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;
	typedef typename std::vector<T>::reverse_iterator reverse_iterator;
	typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;

	NVector() {}
	NVector(int count, const T& element = T())
		: vect(count, element) {}
	NVector(std::initializer_list<T> list)
		: vect(list) {}
	
	void operator=(const std::vector<T>& right) {
		vect = right;
	}
	
	int size() const {return static_cast<int>(vect.size());}
	
	T& operator[](int index) {return vect.operator[](index);}
	const T& operator[](int index) const {return vect.operator[](index);}
	
	T& at(int index) {return vect.at(index);}
	const T& at(int index) const {return vect.at(index);}
	
	T& front() {return vect.front();}
	const T& front() const {return vect.front();}

	T& back() {return vect.back();}
	const T& back() const {return vect.back();}

	iterator begin() {return vect.begin();}
	const_iterator begin() const {return vect.begin();}
	const_iterator cbegin() const {return vect.cbegin();}

	iterator end() {return vect.end();}
	const_iterator end() const {return vect.end();}
	const_iterator cend() const {return vect.cend();}

	reverse_iterator rbegin() {return vect.rbegin();}
	const_reverse_iterator rbegin() const {return vect.rbegin();}
	const_reverse_iterator crbegin() const {return vect.crbegin();}

	reverse_iterator rend() {return vect.rend();}
	const_reverse_iterator rend() const {return vect.rend();}
	const_reverse_iterator crend() const {return vect.crend();}

	void push_back(T object) {vect.push_back(object);}
	
	void pop_back() {vect.pop_back();}

private:
	std::vector<T> vect;
};

#endif // NVECTOR_H
