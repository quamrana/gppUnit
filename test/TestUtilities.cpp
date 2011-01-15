#include "src\MethodNames.h"
#include "src\TestCaseMethodCaller.h"
#include "src\MethodDescription.h"
#include "src\ReportResult.h"

#include "TestUtilities.h"

#include <algorithm>
#include <functional>

namespace Utilities{

	class MethodDescriptionImpl: public gppUnit::MethodDescription, 
				public gppUnit::ReportResult,
				public gppUnit::TimeReport{
		std::string title;

		size_t resultCount;
		void Result(const gppUnit::TestResult&){ resultCount+=1; }

		double reportedTime;
		void reportTime(double run_time){ reportedTime=run_time; }

		std::string name() const { return title; }
		size_t results() const { return resultCount; }
		virtual double run_time() const { return reportedTime; }
	public:
		explicit MethodDescriptionImpl(const std::string& name):title(name),
			resultCount(0),
			reportedTime(0){}
	};

	void TestCaseCaller::timeMethod(gppUnit::MethodCaller& method, gppUnit::TimeReport& report){
		method.forward();
		report.reportTime(0.1);
	}

	void TestCaseCaller::callMethod(gppUnit::TestCaseMethodCaller& method){
		MethodDescriptionImpl desc(method.methodName());
		method.setReport(&desc);
		if (notify) notify->StartMethod(desc);

		timer->timeMethod(method,desc);

		if (notify) notify->EndMethod();
	}

	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		gppUnit::SetupCaller setup(*testcase);
		gppUnit::TestCaller test(*testcase);
		gppUnit::TeardownCaller teardown(*testcase);

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
