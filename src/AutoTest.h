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
#ifndef AUTOTEST_H_35289BA3_33DB_4246_A1C0_B2C6614F0C8D
#define AUTOTEST_H_35289BA3_33DB_4246_A1C0_B2C6614F0C8D

#include "TestCase.h"

namespace gppUnit {

	class AutoList {
		TestCaseList* current;
	public:
		AutoList();
		TestCaseList& autoTests() { return *current; }
		TestCaseList& autoTests(TestCaseList& cases) { current = &cases; return cases; }
	};

	AutoList& globalAutoList();

	TestCaseList& autoTests();

	class AutoTest: public virtual PrototypeTestCase {
	public:
		AutoTest();
	};
}
#endif // AUTOTEST_H_35289BA3_33DB_4246_A1C0_B2C6614F0C8D
