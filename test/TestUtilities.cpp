#include "src\MethodNames.h"
#include "src\TestCaseMethodCaller.h"
#include "src\MethodDescription.h"
#include "src\ReportResult.h"
#include "src\TestResult.h"
#include "src\TypeInformation.h"
#include "src\ClassDescription.h"
#include "src\MethodResult.h"

#include "TestUtilities.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <typeinfo>

namespace Utilities{

	template<typename T>
	struct Results{
		size_t operator()(size_t init, const T& description){
			return init+description.resultCount;
		}
	};
	template<typename T>
	struct RunTime{
		double operator()(double init, const T& description){
			return init+description.reportedTime;
		}
	};

	class ClassRunner: public gppUnit::ClassDescription, public gppUnit::Runner{
		gppUnit::Notification& notify;
		gppUnit::PrototypeTestCase& testcase;
		gppUnit::MethodTimer& timer;
		gppUnit::SetupCaller setup;
		gppUnit::TestCaller test;
		gppUnit::TeardownCaller teardown;

		std::string title;
		std::vector<gppUnit::MethodData> methodData;

		std::string name() const { return title; }
		size_t methods() const { return methodData.size(); }
		size_t results() const { 
			return std::accumulate(methodData.begin(),methodData.end(),long(),Results<gppUnit::MethodData>());
		}
		double run_time() const { 
			return std::accumulate(methodData.begin(),methodData.end(),double(),RunTime<gppUnit::MethodData>());
		}

		gppUnit::MethodData callMethod(gppUnit::TestCaseMethodCaller& method){
			gppUnit::MethodResult desc(method,notify,timer);

			desc.protectMethod();

			return desc.methodSummary();
		}
		bool add(const gppUnit::MethodData& data){ methodData.push_back(data); return data.goodReport; }
	public:
		ClassRunner(gppUnit::Notification& notify, 
			gppUnit::PrototypeTestCase& testcase,
			gppUnit::MethodTimer& timer):notify(notify),
			testcase(testcase),
			timer(timer),
			setup(testcase,*this),
			test(testcase,*this),
			teardown(testcase,*this),
			title(gppUnit::demangleTypeName(typeid(testcase).name()))
		{
			notify.StartClass(*this);
		}
		~ClassRunner(){ notify.EndClass(); }
		bool run(gppUnit::TestCaseMethodCaller* method){
			return add(callMethod(*method));
		}
		void run(){
			if (setup())
			{
				test();
			}
			teardown();
		}
	};

	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		ClassRunner runner(*notify,*testcase,*timer);

		runner.run();
	}
	// TODO: Turn whenCalled inside out.
	// Make a ClassRunner first, then hand it a testcase in each iteration.
	void TestCaseCaller::whenCalled(){
		std::for_each(cases.begin(),cases.end(),
			std::bind1st(
				std::mem_fun(&TestCaseCaller::call),
				this
			)
		);
	}
}
