#include "MethodResult.h"

#include "Notification.h"
#include "TestCaseMethodCaller.h"
#include "TestResult.h"
#include "MethodTimer.h"

namespace gppUnit{

	MethodResult::MethodResult(TestCaseMethodCaller& method, Notification& notify, MethodTimer& timer):method(method),
		notify(notify),
		timer(timer),
		methodData(method.methodName())
	{
		method.setReport(this);
		notify.StartMethod(*this);
	}
	MethodResult::~MethodResult(){ notify.EndMethod(); }

	bool MethodResult::protectMethod(){
		bool result=false;
		try{
			timer.timeMethod(method,*this);
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
		methodData.checkForExceptions(result);
		return result;
	}

	void MethodResult::Report(const TestResult& result){ 
		methodData.accrueResult(result.result);
		notify.Result(result);
	}

	void MethodResult::Exception(const std::string& what){
		notify.Exception(what);
	}

}

