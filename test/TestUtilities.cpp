#include "src\MethodNames.h"
#include "src\TestCaseMethodCaller.h"
#include "src\MethodDescription.h"
#include "src\ReportResult.h"
#include "src\TestResult.h"
#include "src\TypeInformation.h"
#include "src\ClassDescription.h"

#include "TestUtilities.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <typeinfo>

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
		MethodData methodSummary() const { return methodData; }
	};

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

	class ClassRunner: public gppUnit::ClassDescription{
		gppUnit::Notification& notify;
		gppUnit::PrototypeTestCase& testcase;
		std::string title;
		std::vector<MethodData> methodData;

		std::string name() const { return title; }
		size_t methods() const { return methodData.size(); }
		size_t results() const { 
			return std::accumulate(methodData.begin(),methodData.end(),long(),Results<MethodData>());
		}
		double run_time() const { 
			return std::accumulate(methodData.begin(),methodData.end(),double(),RunTime<MethodData>());
		}
	public:
		ClassRunner(gppUnit::Notification& notify, 
			gppUnit::PrototypeTestCase& testcase):notify(notify),
			testcase(testcase),
			title(gppUnit::demangleTypeName(typeid(testcase).name()))
		{
			notify.StartClass(*this);
		}
		~ClassRunner(){ notify.EndClass(); }
		bool add(const MethodData& data){ methodData.push_back(data); return data.goodReport; }
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

	// TODO: most of this could be refactored into MethodResultCounter?
	// just needs timer?
	MethodData TestCaseCaller::callMethod(gppUnit::TestCaseMethodCaller& method){
		MethodResultCounter desc(method.methodName(),*notify);
		method.setReport(&desc);
		notify->StartMethod(desc);

		bool result=privateProtectMethod(method,desc);
		desc.checkForExceptions(result);

		notify->EndMethod();

		return desc.methodSummary();
	}

	// TODO: most of this could be refactored into ClassRunner?
	void TestCaseCaller::call(gppUnit::PrototypeTestCase* testcase){
		ClassRunner runner(*notify,*testcase);

		gppUnit::SetupCaller setup(*testcase);
		gppUnit::TestCaller test(*testcase);
		gppUnit::TeardownCaller teardown(*testcase);

		if (runner.add(callMethod(setup)))
		{
			runner.add(callMethod(test));
		}

		runner.add(callMethod(teardown));
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
