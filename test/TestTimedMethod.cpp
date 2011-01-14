#include "TestUtilities.h"

#include "src\MethodNames.h"
#include "src\MethodDescription.h"

#include <sstream>

namespace {
	class MockTestCase: public Utilities::MockTestCase{
		void test(){ }
	};

	std::string setuptestteardownString(double run_time){
		std::stringstream strm;
		strm << gppUnit::setupMethodName() << '.' << run_time << ".end." <<
			gppUnit::testMethodName() << '.' << run_time << ".end." <<
			gppUnit::teardownMethodName() << '.' << run_time << ".end.";
		return strm.str();
	}

	class TestNumResultsBase: public Utilities::TestCaseCaller, gppUnit::Notification{
		std::stringstream collect;
		MockTestCase testcase;
		const gppUnit::MethodDescription* description;

		void StartMethod(const gppUnit::MethodDescription& desc){
			description=&desc;
			collect << desc.name();
		}
		void EndMethod(){
			collect << '.' << description->run_time() << '.' << "end.";
		}
	protected:
		void givenMockTestCase(){
			add(testcase);
			givenNotification(this);
		}
		void thenEachMethodStartedAndEndedWithRunTime(double run_time){
			confirm.equals(setuptestteardownString(run_time),collect.str(),"Should have called three methods");
		}
		void test(){
			givenMockTestCase();
			whenCalled();
			thenEachMethodStartedAndEndedWithRunTime(1.1);
		}
	}GPPUNIT_INSTANCE;
}
