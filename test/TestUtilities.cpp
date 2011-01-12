#include "TestUtilities.h"

#include <algorithm>
#include <functional>

namespace Utilities{
	std::string setupString(){ return "setup"; }
	std::string testString(){ return "test"; }
	std::string teardownString(){ return "teardown"; }

	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		testcase->setReport(reporter);

		if (notify) notify->StartMethod(setupString());
		testcase->setup();
		if (notify) notify->EndMethod();

		if (notify) notify->StartMethod(testString());
		testcase->test();
		if (notify) notify->EndMethod();

		if (notify) notify->StartMethod(teardownString());
		testcase->teardown();
		if (notify) notify->EndMethod();
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
