#include "TestUtilities.h"

#include "src\MethodNames.h"
#include "src\TestCaseMethodCaller.h"
#include "src\MethodDescription.h"

#include <algorithm>
#include <functional>

namespace Utilities{

	class MethodDescriptionImpl: public gppUnit::MethodDescription{
		std::string title;
		std::string name() const { return title; }
	public:
		explicit MethodDescriptionImpl(const std::string& name):title(name){}
	};

	void TestCaseCaller::callMethod(gppUnit::TestCaseMethodCaller& method){
		MethodDescriptionImpl desc(method.methodName());
		if (notify) notify->StartMethod(desc);
		method.forward();
		if (notify) notify->EndMethod();
	}

	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		gppUnit::SetupCaller setup(*testcase);
		gppUnit::TestCaller test(*testcase);
		gppUnit::TeardownCaller teardown(*testcase);

		testcase->setReport(reporter);

		callMethod(setup);
		callMethod(test);
		callMethod(teardown);
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
