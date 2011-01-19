#include "src\MethodNames.h"
#include "src\TestCaseMethodCaller.h"
#include "src\MethodDescription.h"
#include "src\ReportResult.h"
#include "src\TestResult.h"

#include "TestUtilities.h"

#include <algorithm>
#include <functional>

namespace Utilities{
	struct MethodData{
		std::string title;
		size_t resultCount;
		bool goodReport;
		double reportedTime;

		void accrueResult(const gppUnit::TestResult& result){
			resultCount+=1;
			goodReport&=result.result;
		}
		void checkForExceptions(bool noExceptions){
			goodReport&=noExceptions;
		}
		explicit MethodData(const std::string& name):title(name),
			resultCount(0),
			goodReport(true),
			reportedTime(0){}
	};
	class MethodResultCounter: public gppUnit::MethodDescription, 
				public gppUnit::ReportResult,
				public gppUnit::TimeReport{

		MethodData methodData;
		gppUnit::Notification& notify;

		void Report(const gppUnit::TestResult& result){ 
			methodData.accrueResult(result);
			notify.Result(result);
		}
		void reportTime(double run_time){ methodData.reportedTime=run_time; }

		std::string name() const { return methodData.title; }
		size_t results() const { return methodData.resultCount; }
		virtual double run_time() const { return methodData.reportedTime; }
	public:
		MethodResultCounter(const std::string& name, gppUnit::Notification& notify):methodData(name),
			notify(notify){}
		void checkForExceptions(bool noExceptions){
			methodData.checkForExceptions(noExceptions);
		}
		bool methodSummary() const { return methodData.goodReport; }
	};

	void TestCaseCaller::privateTimeMethod(gppUnit::MethodCaller& method, gppUnit::TimeReport& report){
		timer->timeMethod(method,report);
	}

	bool TestCaseCaller::privateProtectMethod(gppUnit::MethodCaller& method, gppUnit::TimeReport& report){
		bool result=false;
		try{
			privateTimeMethod(method,report);
			result=true;
		} catch(std::exception& e){
			reportException(e.what());
		} catch (std::string& e) {
			reportException(e);
		} catch (const char* e) {
			reportException(e);
		} catch (int e) {
			reportException(e);
		} catch (...) {
			reportException("Unknown Exception");
		}
		return result;
	}

	bool TestCaseCaller::callMethod(gppUnit::TestCaseMethodCaller& method){
		MethodResultCounter desc(method.methodName(),*notify);
		method.setReport(&desc);
		if (notify) notify->StartMethod(desc);

		bool result=privateProtectMethod(method,desc);
		desc.checkForExceptions(result);

		if (notify) notify->EndMethod();

		return desc.methodSummary();
	}

	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		gppUnit::SetupCaller setup(*testcase);
		gppUnit::TestCaller test(*testcase);
		gppUnit::TeardownCaller teardown(*testcase);

		if (callMethod(setup))
		{
			callMethod(test);
		}

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
