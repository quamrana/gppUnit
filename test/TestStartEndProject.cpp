#include "src\TestCase.h"
#include "src\ProjectDescription.h"

#include "TestUtilities.h"

namespace TestStartEndProject{
	using gppUnit::equals;

	class TestOneClass: public Utilities::TestCaseCaller, gppUnit::Notification{
		Utilities::ReportingMockTestCase testcase;

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
		void thenProjectStartedAndEnded(){
			confirm.that(collect.str(),equals("TestCaseCaller.end."),"Should have recorded test");
		}
		void thenOneClassCalled(){
			confirm.that(classes,equals(1),"thenOneClassCalled");
		}
		void thenOneTestResult(){
			confirm.that(results,equals(1),"thenOneTestResult");
		}
		void thenRunTimeIsThreeTimesStandard(){
			double expected=0.3;
			bool result=
				(expected-0.001<run_time) &&
				(run_time<expected+0.001);
			// TODO: write equal_to_t<double>
			confirm.isTrue(result,"thenRunTimeIsThreeTimesStandard");
		}
		void thenProjectReturnsFalse(){
			confirm.isFalse(projectSummary(),"thenProjectReturnsFalse");
		}
		void test(){
			givenTestCase();
			whenCalled();
			thenProjectStartedAndEnded();
			thenOneClassCalled();
			thenOneTestResult();
			thenRunTimeIsThreeTimesStandard();
			thenProjectReturnsFalse();
		}
	}GPPUNIT_INSTANCE;

	class TestProjectPass: public Utilities::TestCaseCaller, gppUnit::Notification{

		const gppUnit::ProjectDescription* projectDesc;
		bool report;
	protected:
		virtual void StartProject(const gppUnit::ProjectDescription& desc){
			projectDesc=&desc;
		}
		virtual void EndProject(){
			report=projectDesc->hasPassed();
			projectDesc=0;
		}
	private:
		void givenTestCase(){
			givenNotification(this);
			projectDesc=0;
		}
		void thenProjectHasPassed(){
			confirm.isTrue(report,"thenProjectHasPassed");
		}
		void thenProjectReturnsTrue(){
			confirm.isTrue(projectSummary(),"thenProjectReturnsTrue");
		}
		void test(){
			givenTestCase();
			whenCalled();
			thenProjectHasPassed();
			thenProjectReturnsTrue();
		}
	}GPPUNIT_INSTANCE;
}

