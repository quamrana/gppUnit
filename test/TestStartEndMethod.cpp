#include "TestUtilities.h"

#include "src\Notification.h"
#include "src\MethodNames.h"
#include "src\MethodDescription.h"

#include <sstream>

namespace TestStartEndMethod{
	class MockTestCaseNoResults: public Utilities::MockTestCase{
		void test(){ } //reporter->Result(); }
	};

	std::string setuptestteardownString(int results){
		std::stringstream strm;
		strm << gppUnit::setupMethodName() << ".0.end." <<
			gppUnit::testMethodName() << '.' << results << ".end." <<
			gppUnit::teardownMethodName() << ".0.end."; 
		return strm.str();
	}

	class TestNumResults: public Utilities::TestCaseCaller, gppUnit::Notification{
		std::stringstream collect;
		const gppUnit::MethodDescription* description;

		void StartMethod(const gppUnit::MethodDescription& desc){
			description=&desc;
			collect << desc.name();
		}
		void EndMethod(){
			collect << '.' << description->results() << '.' << "end.";
		}
	protected:
		void givenMockTestCase(Utilities::MockTestCase& testcase){
			add(testcase);
			givenNotification(this);
		}
		void thenEachMethodStartedAndEndedWithNumResults(int results){
			confirm.equals(setuptestteardownString(results),collect.str(),"Should have called three methods");
		}
	};

	class TestNoResults: public TestNumResults{
		MockTestCaseNoResults testcase;

		void test(){
			givenMockTestCase(testcase);
			whenCalled();
			thenEachMethodStartedAndEndedWithNumResults(0);
		}
	}GPPUNIT_INSTANCE;

	class MockTestCaseOneResult: public Utilities::MockTestCase{
		void test(){ reporter->Result(); }
	};
	class TestOneResult: public TestNumResults{
		MockTestCaseOneResult testcase;

		void test(){
			givenMockTestCase(testcase);
			whenCalled();
			thenEachMethodStartedAndEndedWithNumResults(1);
		}
	}GPPUNIT_INSTANCE;
}
