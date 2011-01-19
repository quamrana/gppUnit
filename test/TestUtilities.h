#ifndef TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52
#define TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52

#include "AutoRun.h"

#include "src\TestCase.h"
#include "src\Notification.h"
#include "src\TimeReport.h"
#include "src\MethodTimer.h"
#include "src\AutoMethodTimer.h"
#include "src\ReportResult.h"

#include <sstream>

namespace gppUnit{
	class TestCaseMethodCaller;
}

namespace Utilities{
	class DestructableNotification: public gppUnit::Notification{};

	template<int TIME>
	class MockAuto{
		gppUnit::TimeReport& report;
	public:
		explicit MockAuto(gppUnit::TimeReport& report):report(report){}
		~MockAuto(){
			double time=TIME;
			report.reportTime(time/10);
		}
		int timeParameter(){ return TIME; }
	};

	class TestCaseCaller: public Auto::TestCase, gppUnit::ReportResult{
		gppUnit::TestCaseList cases;

		void privateTimeMethod(gppUnit::MethodCaller& method, gppUnit::TimeReport& report);

		template<typename T>
		void reportException(T what){
			std::stringstream strm;
			strm << what;
			notify->Exception(strm.str());
		}
		bool privateProtectMethod(gppUnit::MethodCaller& method, gppUnit::TimeReport& report);
		bool callMethod(gppUnit::TestCaseMethodCaller& method);
		void call(gppUnit::PrototypeTestCase* testcase);

		gppUnit::Notification* notify;
		DestructableNotification emptyNotification;
		gppUnit::MethodTimer* timer;

		gppUnit::AutoMethodTimer<MockAuto<1> > autoTimer;

		void Report(const gppUnit::TestResult&);
		gppUnit::ReportResult* reporter;
	protected:
		void add(gppUnit::PrototypeTestCase& testcase){
			cases.push_back(&testcase);
		}

		void givenNotification(gppUnit::Notification* notified){ notify=notified; }
		void givenTimer(gppUnit::MethodTimer* timed){ timer=timed; }
		void whenCalled();

		TestCaseCaller():cases(),notify(&emptyNotification),timer(&autoTimer){}
	};
	class MockTestCase: public gppUnit::PrototypeTestCase{
		void setReport(gppUnit::ReportResult*report){ reporter=report; }
	protected:
		gppUnit::ReportResult* reporter;
	};
}

#endif // TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52
