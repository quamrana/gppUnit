#include "AutoRun.h"

#include "src\TestCase.h"

#include <sstream>
#include <algorithm>
#include <functional>

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
	std::string setuptestteardownString(){ return setupString()+'.'+testString()+'.'+teardownString()+'.'; }

	class TestCaseCaller: public Auto::TestCase{
		gppUnit::TestCaseList cases;
		void call(gppUnit::TestCase* testcase){
			testcase->setup();
			testcase->test();
			testcase->teardown();
		}
	protected:
		void add(gppUnit::TestCase& testcase){
			cases.push_back(&testcase);
		}
		void whenCalled(){
			std::for_each(cases.begin(),cases.end(),
				std::bind1st(
					std::mem_fun(&TestCaseCaller::call),
					this
				)
			);
		}
	};

	class AllThreeMethodsCalled: public TestCaseCaller{
		MockTestCase testcase;

		void givenMockTestCase(){
			add(testcase);
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

	class TwoTestCasesCalled: public TestCaseCaller{
		MockTestCase testcase1;
		MockTestCase testcase2;
		void givenTwoTestCases(){
			add(testcase1);
			add(testcase2);
		}
		void thenSixMethodsCalled(){
			std::string expected=setuptestteardownString()+setuptestteardownString();
			std::string actual=testcase1.result()+testcase2.result();
			confirm.isTrue(actual==expected,"Should have called six methods");
		}
		void test(){
			givenTwoTestCases();
			whenCalled();
			thenSixMethodsCalled();
		}
	}GPPUNIT_INSTANCE;
}
