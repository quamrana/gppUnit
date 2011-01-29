#include "src\MethodDescription.h"
#include "src\ReportResult.h"
#include "src\TestResult.h"
#include "src\AssertException.h"

#include "TestUtilities.h"

#include <stdexcept>
#include <sstream>

namespace TestExceptionCatching{
	using gppUnit::equals;

	class RTEThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw std::runtime_error("rte");
		}
	};
	class StringThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw std::string("string");
		}
	};
	class CharStarThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw "charstar";
		}
	};
	class IntStarThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw 1;
		}
	};
	class SelfThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw this;
		}
	};
	class AssertExceptionThrowingTestCase: public Utilities::MockTestCase{
		void test(){ 
			throw gppUnit::assertException;
		}
	};

	class VariousExceptions: public Utilities::TestCaseCaller, gppUnit::Notification{
		RTEThrowingTestCase testcase1;
		StringThrowingTestCase testcase2;
		CharStarThrowingTestCase testcase3;
		IntStarThrowingTestCase testcase4;
		SelfThrowingTestCase testcase5;

	protected:
		std::stringstream collect;
		bool exceptionReported;
	private:

		const gppUnit::MethodDescription* description;

		double run_time;
		bool runtimeCaptured;

		void StartMethod(const gppUnit::MethodDescription& desc){
			description=&desc;
		}

		void Exception(const std::string& what){
			exceptionReported=true;
			collect << what << '.';
		}
		void EndMethod(){
			if (!runtimeCaptured){
				if (description->name()=="test"){
					run_time=description->run_time();
					runtimeCaptured=true;
				}
			}
			description=0;
		}

		virtual void givenTestCases(){
			add(testcase1);
			add(testcase2);
			add(testcase3);
			add(testcase4);
			add(testcase5);
		}
		void givenTestCase(){
			givenTestCases();
			givenNotification(this);
			exceptionReported=false;
			run_time=-1;
			runtimeCaptured=false;
		}
		virtual void thenExceptionReported(){
			confirm.isTrue(exceptionReported,"thenExceptionReported");
			confirm.that(collect.str(),equals("rte.string.charstar.1.Unknown Exception."),"Various exceptions");
		}
		void thenTimeReported(){
			confirm.that(run_time,equals(0.1),"TestUtilities should supply a standard run_time");
		}
		void test(){
			givenTestCase();
			whenCalled();
			thenExceptionReported();
			thenTimeReported();
		}
	}GPPUNIT_INSTANCE;

	class AssertExceptionTest: public VariousExceptions{
		AssertExceptionThrowingTestCase testcase6;
		virtual void givenTestCases(){
			add(testcase6);
		}
		virtual void thenExceptionReported(){
			confirm.isFalse(exceptionReported,"then_NO_ExceptionReported");
			confirm.that(collect.str(),equals(""),"AssertException not collected");
		}
	}GPPUNIT_INSTANCE;

	class SetupThrowingTestCase: public Utilities::MockTestCase{
		void setup(){ 
			throw std::runtime_error("rte");
		}
		void test(){}
	};
	class ExceptionInSetup: public Utilities::TestCaseCaller, gppUnit::Notification{
		SetupThrowingTestCase testcase1;

		std::stringstream collect;

		void StartMethod(const gppUnit::MethodDescription& desc){
			collect << desc.name() << '.';
		}

		void givenTestCase(){
			add(testcase1);
			givenNotification(this);
		}
		void thenOnlySetupAndTeardownRun(){
			confirm.that(collect.str(),equals("setup.teardown."),"thenOnlySetupAndTeardownRun");
		}
		void test(){
			givenTestCase();
			whenCalled();
			thenOnlySetupAndTeardownRun();
		}
	}GPPUNIT_INSTANCE;

	class SetupFailTestCase: public Utilities::MockTestCase{
		void setup(){ 
			gppUnit::TestResult result;
			result.message="setup fails";
			reporter->Report(result);
		}
		void test(){}
	};
	class FailInSetup: public Utilities::TestCaseCaller, gppUnit::Notification{
		SetupFailTestCase testcase1;

		std::stringstream collect;

		void StartMethod(const gppUnit::MethodDescription& desc){
			collect << desc.name() << '.';
		}

		void givenTestCase(){
			add(testcase1);
			givenNotification(this);
		}
		void thenOnlySetupAndTeardownRun(){
			confirm.that(collect.str(),equals("setup.teardown."),"thenOnlySetupAndTeardownRun");
		}
		void test(){
			givenTestCase();
			whenCalled();
			thenOnlySetupAndTeardownRun();
		}
	}GPPUNIT_INSTANCE;
}
