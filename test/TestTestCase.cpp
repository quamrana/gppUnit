#include "TestUtilities.h"

#include <sstream>

namespace TestTestCase {
	class MockTestCase: public Utilities::MockTestCase{
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

	class TestMethodNames: public Auto::TestCase{
		void test(){
			std::string expected;
			std::string actual;

			expected="setup";
			actual=setupString();
			confirm.isTrue(actual==expected,"Should be setup");

			expected="test";
			actual=testString();
			confirm.isTrue(actual==expected,"Should be test");

			expected="teardown";
			actual=teardownString();
			confirm.isTrue(actual==expected,"Should be teardown");
		}
	}GPPUNIT_INSTANCE;

	class AllThreeMethodsCalled: public Utilities::TestCaseCaller{
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

	class TwoTestCasesCalled: public Utilities::TestCaseCaller{
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
