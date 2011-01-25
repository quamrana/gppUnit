#include "src\ReportResult.h"
#include "src\TestResult.h"
#include "src\TestCase.h"
#include "src\AssertException.h"

#include "AutoRun.h"

namespace gppUnit{
	class Confirm: public gppUnit::ResultSetter{
		ReportResult* report;
		void setReport(ReportResult* reporter){ report=reporter; }
	public:
		virtual void fail(const char* message="fail"){
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
	class Expect: public Confirm{
	public:
		virtual void fail(const char* message="fail"){
			Confirm::fail(message);
			throw gppUnit::assertException;
		}
	};
}

namespace TestAsserts{
	class Base: public Auto::TestCase, gppUnit::ReportResult{ 
		gppUnit::TestResult testResult;
		virtual void Report(const gppUnit::TestResult& result){
			testResult=result;
		}
	protected:
		void setReport(gppUnit::ResultSetter& setter){
			setter.setReport(this);
		}
		void thenResultIsFail(){
			confirm.isFalse(testResult.result,"thenResultIsFail");
			confirm.equals("fail",testResult.message,"message is fail");
		}
		void thenResultIsPass(){
			confirm.isTrue(testResult.result,"thenResultIsPass");
			confirm.equals("pass",testResult.message,"message is pass");
		}
	};
	class ConfirmPassAndFail: public Base{
		gppUnit::Confirm conf;
		void givenConfirm(){
			setReport(conf);
		}
		void whenFailCalled(){
			conf.fail("fail");
		}
		void whenPassCalled(){
			conf.pass("pass");
		}
		void test(){
			givenConfirm();
			whenFailCalled();
			thenResultIsFail();
			whenPassCalled();
			thenResultIsPass();
		}
	}GPPUNIT_INSTANCE;
	class CatchExceptionsFromExpect: public Base{
		gppUnit::Expect exp;
		bool caughtException;
		void givenExpect(){
			setReport(exp);
			caughtException=false;
		}
		void whenFailCalled(){
			try{
				exp.fail("fail");
			} catch (gppUnit::AssertException e){
				caughtException=true;
			}
		}
		void thenExceptionCaught(){
			confirm.isTrue(caughtException,"thenExceptionCaught");
		}
		void whenPassCalled(){
			exp.pass("pass");
		}
		void test(){
			givenExpect();
			whenFailCalled();
			thenResultIsFail();
			thenExceptionCaught();
			whenPassCalled();
			thenResultIsPass();
		}
	}GPPUNIT_INSTANCE;
}
