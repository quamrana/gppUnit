#include "TestUtilities.h"

#include "src\Notification.h"
#include <sstream>

namespace TestStartEndMethod{
	class MockTestCase: public Utilities::MockTestCase{
		void test(){ }
	};
	class Test: public Utilities::TestCaseCaller, gppUnit::Notification{
		std::stringstream collect;
		MockTestCase testcase;

		void StartMethod(const std::string& name){
			collect << name << '.';
		}
		void givenMockTestCase(){
			add(testcase);
			givenNotification(this);
		}
		void thenEachMethodStartedAndEnded(){
			confirm.equals("setup.test.teardown.",collect.str(),"Should have called three methods");
		}
		void test(){
			givenMockTestCase();
			whenCalled();
			thenEachMethodStartedAndEnded();
		}
	}GPPUNIT_INSTANCE;
}
