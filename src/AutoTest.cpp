#include "AutoTest.h"

namespace gppUnit {

	// globalTestCaseList is the 'magic' list.
	TestCaseList& globalTestCaseList() {
		static TestCaseList tests;
		return tests;
	}

	// AutoList initialises itself from the single instance of TestCastList at globalTestCaseList()
	AutoList::AutoList(): current(&globalTestCaseList()) {}

	// globalAutoList maintains a single AutoList
	AutoList& globalAutoList() {
		static AutoList autoList;
		return autoList;
	}

	// AutoTests gets its list from the single instance of AutoList at globalAutoList
	TestCaseList& autoTests() {
		return globalAutoList().autoTests();
	}

	// AutoTest registers itself with autoTests()
	AutoTest::AutoTest() { autoTests().push_back(this); }

}
