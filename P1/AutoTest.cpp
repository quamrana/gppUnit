#include "AutoTest.h"

namespace Prototype1{
	namespace Auto{
		TestCaseList& autoTests(){ 
			static TestCaseList tests;
			return tests; 
		}

		AutoTest::AutoTest(){ autoTests().push_back(this); }

	}
}