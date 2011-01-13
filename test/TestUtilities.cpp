#include "TestUtilities.h"

#include "src\MethodNames.h"
#include "src\TestCaseMethodCaller.h"
#include "src\MethodDescription.h"

#include <algorithm>
#include <functional>

namespace Utilities{

	class MethodDescriptionImpl: public gppUnit::MethodDescription, public gppUnit::ReportResult{
		std::string title;
		size_t resultCount;
		std::string name() const { return title; }
		size_t results() const { return resultCount; }
		virtual void Result(){ resultCount=1; }
	public:
		explicit MethodDescriptionImpl(const std::string& name):title(name),resultCount(0){}
	};

	void TestCaseCaller::callMethod(gppUnit::TestCaseMethodCaller& method){
		MethodDescriptionImpl desc(method.methodName());
		method.setReport(&desc);
		if (notify) notify->StartMethod(desc);
		method.forward();
		if (notify) notify->EndMethod();
	}

	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		gppUnit::SetupCaller setup(*testcase);
		gppUnit::TestCaller test(*testcase);
		gppUnit::TeardownCaller teardown(*testcase);

		//testcase->setReport(reporter);

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
