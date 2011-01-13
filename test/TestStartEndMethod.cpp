#include "TestUtilities.h"

#include "src\Notification.h"
#include "src\MethodNames.h"
#include "src\MethodDescription.h"

#include <sstream>

namespace TestStartEndMethod{
	class MockTestCase: public Utilities::MockTestCase{
		void test(){ }
	};

	std::string setuptestteardownString(){ 
		return std::string(gppUnit::setupMethodName())+".end."+
			gppUnit::testMethodName()+".end."+
			gppUnit::teardownMethodName()+".end."; 
	}
	class Test: public Utilities::TestCaseCaller, gppUnit::Notification{
		std::stringstream collect;
		MockTestCase testcase;

		void StartMethod(const gppUnit::MethodDescription& desc){
			collect << desc.name() << '.';
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
