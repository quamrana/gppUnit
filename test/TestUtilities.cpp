#include "TestUtilities.h"

#include <algorithm>
#include <functional>

namespace Utilities{
	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		testcase->setReport(reporter);
		testcase->setup();
		testcase->test();
		testcase->teardown();
	}
	void TestCaseCaller::whenCalled(){
		std::for_each(cases.begin(),cases.end(),
			std::bind1st(
				std::mem_fun(&TestCaseCaller::call),
				this
			)
		);
	}
}
