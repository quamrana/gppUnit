#include "src\ReportResult.h"
#include "src\TestResult.h"
#include "src\TestCase.h"

#include "AutoRun.h"

namespace gppUnit{
	class Confirm: public gppUnit::ResultSetter{
		ReportResult* report;
		void setReport(ReportResult* reporter){ report=reporter; }
	public:
		void fail(const char* message="fail"){
			TestResult result;
			result.message=message;
			report->Report(result);
		}
		void pass(const char* message="pass"){
			TestResult result;
			result.result=true;
			result.message=message;
			report->Report(result);
		}
	};
}

namespace TestAsserts{
	class ConfirmPassAndFail: public Auto::TestCase, gppUnit::ReportResult{
		gppUnit::Confirm conf;
		gppUnit::TestResult testResult;
		virtual void Report(const gppUnit::TestResult& result){
			testResult=result;
		}
		void givenConfirm(){
			gppUnit::ResultSetter* s=&conf;
			s->setReport(this);
		}
		void whenFailCalled(){
			conf.fail("fail");
		}
		void whenPassCalled(){
			conf.pass("pass");
		}
		void thenResultIsFail(){
			confirm.isFalse(testResult.result,"thenResultIsFail");
			confirm.equals("fail",testResult.message,"message is fail");
		}
		void thenResultIsPass(){
			confirm.isTrue(testResult.result,"thenResultIsPass");
			confirm.equals("pass",testResult.message,"message is pass");
		}
		void test(){
			givenConfirm();
			whenFailCalled();
			thenResultIsFail();
			whenPassCalled();
			thenResultIsPass();
		}
	}GPPUNIT_INSTANCE;
}
