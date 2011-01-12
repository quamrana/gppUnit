#include "TestUtilities.h"

#include "src\Notification.h"
#include <sstream>

namespace TestStartEndMethod{
	class MockTestCase: public Utilities::MockTestCase{
		void test(){ }
	};

	std::string setuptestteardownString(){ 
		return Utilities::setupString()+".end."+
			Utilities::testString()+".end."+
			Utilities::teardownString()+".end."; 
	}
	class Test: public Utilities::TestCaseCaller, gppUnit::Notification{
		std::stringstream collect;
		MockTestCase testcase;

		void StartMethod(const std::string& name){
			collect << name << '.';
		}
		void EndMethod(){
			collect << "end.";
		}
		void givenMockTestCase(){
			add(testcase);
			givenNotification(this);
		}
		void thenEachMethodStartedAndEnded(){
			confirm.equals(setuptestteardownString(),collect.str(),"Should have called three methods");
		}
		void test(){
			givenMockTestCase();
			whenCalled();
			thenEachMethodStartedAndEnded();
		}
	}GPPUNIT_INSTANCE;
}
