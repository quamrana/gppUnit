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
