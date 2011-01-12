#include "TestUtilities.h"

#include <algorithm>
#include <functional>

namespace Utilities{
	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		testcase->setReport(reporter);
		if (notify) notify->StartMethod("setup");
		testcase->setup();
		if (notify) notify->StartMethod("test");
		testcase->test();
		if (notify) notify->StartMethod("teardown");
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
