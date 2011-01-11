#ifndef TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52
#define TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52

#include "AutoRun.h"

#include "src\TestCase.h"

namespace Utilities{
	class TestCaseCaller: public Auto::TestCase{
		gppUnit::TestCaseList cases;
		void call(gppUnit::PrototypeTestCase* testcase);
		gppUnit::ReportResult* reporter;
	protected:
		void add(gppUnit::PrototypeTestCase& testcase){
			cases.push_back(&testcase);
		}
		void givenReporter(gppUnit::ReportResult* report){ reporter=report; }
		void whenCalled();
		TestCaseCaller():reporter(0){}
	};
	class MockTestCase: public gppUnit::PrototypeTestCase{
		void setReport(gppUnit::ReportResult*report){ reporter=report; }
	protected:
		gppUnit::ReportResult* reporter;
	};
}

#endif // TESTUTILITIES_H_B22D7F0E_4A0D_4EFB_9092_AE3C8B950C52
