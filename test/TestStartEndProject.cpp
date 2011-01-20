#include "src\TestCase.h"
#include "src\ProjectDescription.h"
#include "src\TestResult.h"

#include "TestUtilities.h"

namespace TestStartEndProject{
	class MockTestCase: public Utilities::MockTestCase{
		void test(){
			gppUnit::TestResult result;
			reporter->Report(result);
		}
	};
	class TestOneClass: public Utilities::TestCaseCaller, gppUnit::Notification{
		MockTestCase testcase;

		const gppUnit::ProjectDescription* projectDesc;
		size_t classes;
		size_t results;
		double run_time;
	protected:
		std::stringstream collect;
		virtual void StartProject(const gppUnit::ProjectDescription& desc){
			collect << desc.name() << '.';
			projectDesc=&desc;
		}
		virtual void EndProject(){
			collect << "end.";
			classes=projectDesc->classes();
			results=projectDesc->results();
			run_time=projectDesc->run_time();
			projectDesc=0;
		}
	private:
		void givenTestCase(){
			add(testcase);
			givenNotification(this);
			projectDesc=0;
			classes=0;
			results=0;
			run_time=-1;
		}
		void thenEachClassStartedAndEnded(){
			confirm.equals("TestCaseCaller.end.",collect.str(),"Should have recorded test");
		}
		void thenOneClassCalled(){
			confirm.equals(1,classes,"thenOneClassCalled");
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
			thenOneClassCalled();
			thenOneTestResult();
			thenRunTimeIsThreeTimesStandard();
		}
	}GPPUNIT_INSTANCE;
}
