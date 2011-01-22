#ifndef TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52
#define TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52

#include "AutoRun.h"

#include "src\Notification.h"
#include "src\AutoMethodTimer.h"
#include "src\TestCase.h"

#include <sstream>

namespace gppUnit{
	class TestCaseMethodCaller;
	class TimeReport;
	class MethodTimer;
}

namespace Utilities{
	class DestructableNotification: public gppUnit::Notification{};

	void reportTimeDividedByTen(gppUnit::TimeReport& report, int Time);

	template<int TIME>
	class MockAuto{
		gppUnit::TimeReport& report;
	public:
		explicit MockAuto(gppUnit::TimeReport& report):report(report){}
		~MockAuto(){
			reportTimeDividedByTen(report, TIME);
		}
		//int timeParameter(){ return TIME; }
	};

	class TestCaseCaller: public Auto::TestCase{
		gppUnit::TestCaseList cases;

		void privateTimeMethod(gppUnit::MethodCaller& method, gppUnit::TimeReport& report);

		gppUnit::Notification* notify;
		DestructableNotification emptyNotification;
		gppUnit::MethodTimer* timer;

		gppUnit::AutoMethodTimer<MockAuto<1> > autoTimer;

		bool projectReturn;
	protected:
		void add(gppUnit::PrototypeTestCase& testcase){
			cases.push_back(&testcase);
		}

		void givenNotification(gppUnit::Notification* notified){ notify=notified; }
		void givenTimer(gppUnit::MethodTimer* timed){ timer=timed; }
		void whenCalled();
		bool projectSummary(){ return projectReturn; }

		TestCaseCaller():cases(),notify(&emptyNotification),timer(&autoTimer){}
	};
	class MockTestCase: public virtual gppUnit::PrototypeTestCase{
		void setReport(gppUnit::ReportResult*report){ reporter=report; }
	protected:
		gppUnit::ReportResult* reporter;
	};
	class ReportingMockTestCase: public MockTestCase{
		void test();
	};

	extern gppUnit::TestCaseList dummyTestCaseList;
}

#endif // TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52
