#include "AutoRun.h"

#include "src\TestCase.h"
#include <sstream>


namespace TestTestCase {
	class MockTestCase: public gppUnit::TestCase{
		std::stringstream collect;
		void setup(){ collect << "setup" << '.'; }
		void test(){ collect << "test" << '.'; }
		void teardown(){ collect << "teardown" << '.'; }
	public:
		std::string result(){return collect.str();}
	};
	std::string setupString(){ return "setup"; }
	std::string testString(){ return "test"; }
	std::string teardownString(){ return "teardown"; }
	std::string setuptestteardownString(){ return setupString()+'.'+testString()+'.'+teardownString()+';'; }
	class AllThreeMethodsCalled: public Auto::TestCase{
		MockTestCase testcase;

		void call(gppUnit::TestCase& testcase){
			testcase.setup();
			testcase.test();
			testcase.teardown();
		}
		void givenMockTestCase(){
		}
		void whenCalled(){
			call(testcase);
		}
		void thenAllThreeMethodsCalled(){
			confirm.isTrue(testcase.result()==setuptestteardownString(),"Should have called three methods");
		}
		void test(){ 
			givenMockTestCase();
			whenCalled();
			thenAllThreeMethodsCalled();
		}
	}GPPUNIT_INSTANCE;

}
