#include "TestUtilities.h"

namespace TestTestResults{
	class MockTestCase: public Utilities::MockTestCase{
		void test(){ reporter->Result(); }
	};
	class TestCaseReportsResult: public Utilities::TestCaseCaller, gppUnit::ReportResult{
		MockTestCase testcase;
		bool result;
		void Result(){ result=true; }
		void givenMockTestCase(){
			add(testcase);
			result=false;
			givenReporter(this);
		}
		void thenTestMethodReportsTestResult(){
			confirm.isTrue(result,"Result should be called");
		}
		void test(){
			givenMockTestCase();
			whenCalled();
			thenTestMethodReportsTestResult();
		}
	}GPPUNIT_INSTANCE;
}
