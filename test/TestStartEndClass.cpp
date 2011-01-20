#include "src\TestCase.h"
#include "src\ClassDescription.h"
#include "src\TestResult.h"

#include "TestUtilities.h"

namespace TestStartEndClass{
	class MockTestCase: public Utilities::MockTestCase{
		void test(){
			gppUnit::TestResult result;
			reporter->Report(result);
		}
	};
	class TestOneClass: public Utilities::TestCaseCaller, gppUnit::Notification{
		MockTestCase testcase;

		const gppUnit::ClassDescription* classDesc;
		size_t methods;
		size_t results;
		double run_time;
	protected:
		std::stringstream collect;
		virtual void StartClass(const gppUnit::ClassDescription& desc){
			collect << desc.name() << '.';
			classDesc=&desc;
		}
		virtual void EndClass(){
			collect << "end.";
			methods=classDesc->methods();
			results=classDesc->results();
			run_time=classDesc->run_time();
			classDesc=0;
		}
	private:
		void givenTestCase(){
			add(testcase);
			givenNotification(this);
			methods=0;
			results=0;
			run_time=-1;
		}
		void thenEachClassStartedAndEnded(){
			confirm.equals("TestStartEndClass::MockTestCase.end.",collect.str(),"Should have recorded test");
		}
		void thenThreeMethodsCalled(){
			confirm.equals(3,methods,"thenThreeMethodsCalled");
		}
		void thenOneTestResult(){
			confirm.equals(1,results,"thenOneTestResult");
		}
		void thenRunTimeIsThreeTimesStandard(){
			double expected=0.3;
			bool result=
				(expected-0.001<run_time) &&
				(run_time<expected+0.001);
			confirm.isTrue(result,"thenRunTimeIsThreeTimesStandard");
		}
		void test(){
			givenTestCase();
			whenCalled();
			thenEachClassStartedAndEnded();
			thenThreeMethodsCalled();
			thenOneTestResult();
			thenRunTimeIsThreeTimesStandard();
		}
	}GPPUNIT_INSTANCE;
}
