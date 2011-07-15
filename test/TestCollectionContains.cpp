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
#include "Matchers\SubStringMatchers.h"

namespace TestCollectionContains{
	using Utilities::MatcherHelper;
	using gppUnit::contains;

	class VectorContains: public MatcherHelper{
		void test(){
			std::vector<int> v;
			That(v,!contains(0),"not a container that contains '0'\nan empty container\n");

			v.push_back(1);
			That(v,contains(1),"a container that contains '1'\n[1]\n");
			That(v,!contains(2),"not a container that contains '2'\n[1]\n");

			v.push_back(2);
			v.push_back(3);
			That(v,contains(2),"a container that contains '2'\n[1 2 3]\n");
		}
	}GPPUNIT_INSTANCE;
}