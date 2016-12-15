/*
Copyright (c) 2011 Andrew Wall

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "TestMatchersHelpers.h"

namespace TestLessThan {
	using Utilities::MatcherHelper;
	using gppUnit::less_than;
	using gppUnit::equal_to;

	class TestIntegers: public MatcherHelper {
		void test() {
			int integer = 1;
			long longint = 2;
			signed char schar = -4;
			std::vector<MatcherHelper*> vec;

			That(longint, !less_than(integer), "not a value less than '1'\n");
			That(integer, !less_than(vec.size()), "not a value less than '0'\n");
			That(longint, !less_than(schar), "not a value less than '-4'\n");
			That(vec.size(), !less_than(schar), "not a value less than '-4'\n");

			That(integer, less_than(longint), "a value less than '2'\n");
			That(vec.size(), less_than(integer), "a value less than '1'\n");
			That(schar, less_than(longint), "a value less than '2'\n");
			That(schar, less_than(vec.size()), "a value less than '0'\n");
		}
	} GPPUNIT_INSTANCE;

	class TestReal: public MatcherHelper {
		void test() {
			float floater = 2;
			double dubble = 3;

			That(dubble, !less_than(dubble), "not a value less than '3'\n");
			That(dubble, !less_than(floater), "not a value less than '2'\n");
			That(floater, !less_than(floater), "not a value less than '2'\n");
			That(floater, less_than(dubble), "a value less than '3'\n");
		}
	} GPPUNIT_INSTANCE;
}
