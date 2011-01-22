#include "src\ProjectRunner.h"
#include "src\TestResult.h"
#include "src\ReportResult.h"
#include "src\TimeReport.h"

#include "TestUtilities.h"

namespace Utilities{

	void reportTimeDividedByTen(gppUnit::TimeReport& report, int Time){
		double time=Time;
		report.reportTime(time/10);
	}

	void TestCaseCaller::whenCalled(){
		gppUnit::ProjectRunner runner("TestCaseCaller",*notify,*timer,cases);
		projectReturn=runner.run();
	}
	void ReportingMockTestCase::test(){
		gppUnit::TestResult result;
		reporter->Report(result);
	}

	gppUnit::TestCaseList dummyTestCaseList;
}
