#include "src\TestCase.h"

#include "TestUtilities.h"

namespace TestStartEndClass{
	class MockTestCase: public Utilities::MockTestCase{
		void test(){}
	};
	class TestOneClass: public Utilities::TestCaseCaller, gppUnit::Notification{
		MockTestCase testcase;
	protected:
		std::stringstream collect;
		virtual void StartClass(const std::string name){
			collect << name << '.';
		}
		virtual void EndClass(){
			collect << "end.";
		}
	private:
		void givenTestCase(){
			add(testcase);
			givenNotification(this);
		}
		void thenEachClassStartedAndEnded(){
			confirm.equals("TestStartEndClass::MockTestCase.end.",collect.str(),"Should have recorded test");
		}
		void test(){
			givenTestCase();
			whenCalled();
			thenEachClassStartedAndEnded();
		}
	}GPPUNIT_INSTANCE;
}
