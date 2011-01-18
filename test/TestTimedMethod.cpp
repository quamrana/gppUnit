#include "src\MethodNames.h"
#include "src\MethodDescription.h"
#include "src\TestCaseMethodCaller.h"

#include "TestUtilities.h"

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

	class TestRunTime: public Utilities::TestCaseCaller, gppUnit::Notification{
		std::stringstream collect;
		MockTestCase testcase;
		gppUnit::AutoMethodTimer<Utilities::MockAuto<11> > autoTimer;
		const gppUnit::MethodDescription* description;

		void StartMethod(const gppUnit::MethodDescription& desc){
			description=&desc;
			collect << desc.name();
		}
		void EndMethod(){
			collect << '.' << description->run_time() << '.' << "end.";
		}
		double timeToReport;
		void timeMethod(gppUnit::MethodCaller& method, gppUnit::TimeReport& report){
			method.forward();
			report.reportTime(timeToReport);
		}

		void givenMockTestCase(){
			add(testcase);
			givenNotification(this);
		}
		void givenTimeToReport(double run_time){
			timeToReport=run_time;
			expect.isTrue(timeToReport!=0.1,"Sample time used by test is not 0.1");
		}
		void thenEachMethodStartedAndEndedWithRunTime(){
			confirm.equals(setuptestteardownString(timeToReport),collect.str(),"Should have called three methods");
		}
		void test(){
			givenMockTestCase();
			givenTimeToReport(1.1);
			givenTimer(&autoTimer);
			whenCalled();
			thenEachMethodStartedAndEndedWithRunTime();
		}
	}GPPUNIT_INSTANCE;
}
