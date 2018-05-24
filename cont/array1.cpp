/* The following code example is taken from the book
 * "The C++ Standard Library - A Tutorial and Reference, 2nd Edition"
 * by Nicolai M. Josuttis, Addison-Wesley, 2012
 *
 * (C) Copyright Nicolai M. Josuttis 2012.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */
#include <array>
#include <algorithm>
#include <functional>
#include <numeric>
#include "print.hpp"
using namespace std;

#include <vector>
void initialization()
{
	std::array<int, 4> x;           // oops: elements of x have undefined value.
	std::array<int, 4> x1 = {};      // all elements of x have value 0 (int()).

	std::array<int, 5> coll = {1, 2, 3, 4, 5};    // before C++, use initializer list to initialize.

	std::array<int, 10> c2 = {42};    // 42, 0, 0, 0, ..., 0

//    std::array<int, 5> c3 = {1, 2, 3, 4, 5, 6};   // Error: too many values.

//    std::array<int, 5> a({1, 2, 3, 4, 5});    // Error: no such ctor.
    std::vector<int> v({1, 2, 3, 4, 5});      // OK? error: expected expression

	PRINT_ELEMENTS(x, "x with undefined values: ");
}

void move()
{
	std::array<int, 2> x = {1, 2};
	std::array<int, 2> y = {3, 4};

	x[1] = x[1]+1;
	y[1] = y[1]+1;

	x = std::move(y);

	PRINT_ELEMENTS(x, "x: ");
	PRINT_ELEMENTS(y, "y: ");
}

void size()
{
	std::array<int, 0> zero;				// array with no elements
	
	std::sort(zero.begin(), zero.end());	// OK. No effect.

	// runtime errors.
	zero[5] = 100;
	std::cout << zero.front() << std::endl;
}

void cstylearray()
{
	std::array<char, 50> str;
	strcpy(str.data(), "hello, world!");
	printf("%s\n", str.data());
}

void Tuple()
{
	typedef std::array<std::string, 3> ThreeStrings;

	ThreeStrings a = { "hello", "the", "world" };

	std::cout << std::tuple_size<ThreeStrings>::value << std::endl;	// 3
	std::tuple_element<1, ThreeStrings>::type str;					// string type.
	std::cout << std::get<1>(a) << std::endl;						// "the"
}

int main()
{
	initialization();
	move();
	size();
	cstylearray();
	Tuple();

	cout << "----" << endl;

	// create array with 10 ints
	array<int, 10> a = { 11, 22, 33, 44 };

	PRINT_ELEMENTS(a);

	// modify last two elements
	a.back() = 9999999;
	a[a.size()-2] = 42;
	PRINT_ELEMENTS(a);

	// process sum of all elements
	cout << "sum: " 
		 << accumulate(a.begin(), a.end(), 0)
		 << endl;

	// negate all elements
	transform(a.begin(), a.end(),    // source
			  a.begin(),            // destination
			  negate<int>());       // operation
	PRINT_ELEMENTS(a);
}

