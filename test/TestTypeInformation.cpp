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
#include "src\TypeInformation.h"

#include "AutoRun.h"

#include <typeinfo>


class ClassInGlobalNamespace {};

namespace {
	class ClassInEmptyNamespace {};
}

namespace TestTypeInformation {
	using gppUnit::equals;

	class ClassInNamespace {};
	class ActualNames: public Auto::TestCase {
		void test() {
			confirm.that(gppUnit::demangleTypeName(typeid(ClassInNamespace).name()), equals("TestTypeInformation::ClassInNamespace"));
			confirm.that(gppUnit::demangleTypeName(typeid(ClassInEmptyNamespace).name()), equals("(anonymous namespace)::ClassInEmptyNamespace"));
			confirm.that(gppUnit::demangleTypeName(typeid(ClassInGlobalNamespace).name()), equals("ClassInGlobalNamespace"));
			confirm.that(gppUnit::demangleTypeName(typeid(int).name()), equals("int"));
		}
	} GPPUNIT_INSTANCE;
	class ArbitraryNames: public Auto::TestCase {
		void test() {
			confirm.that(gppUnit::demangleTypeName("foo"), equals("foo"));
		}
	} GPPUNIT_INSTANCE;
}
