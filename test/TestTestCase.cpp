#include "TestUtilities.h"

#include <sstream>

namespace TestTestCase {
	class MockTestCase: public Utilities::MockTestCase{
		std::stringstream collect;
		void setup(){ collect << Utilities::setupString() << '.'; }
		void test(){ collect << Utilities::testString() << '.'; }
		void teardown(){ collect << Utilities::teardownString() << '.'; }
	public:
		std::string result(){return collect.str();}
	};

	std::string setuptestteardownString(){ 
		return Utilities::setupString()+'.'+
			Utilities::testString()+'.'+
			Utilities::teardownString()+'.'; 
	}

	class TestMethodNames: public Auto::TestCase{
		void test(){
			std::string expected;
			std::string actual;

			expected="setup";
			actual=Utilities::setupString();
			confirm.equals(expected,actual,"Should be setup");

			expected="test";
			actual=Utilities::testString();
			confirm.equals(expected,actual,"Should be test");

			expected="teardown";
			actual=Utilities::teardownString();
			confirm.equals(expected,actual,"Should be teardown");
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
			confirm.equals(expected,actual,"Should have called six methods");
		}
		void test(){
			givenTwoTestCases();
			whenCalled();
			thenSixMethodsCalled();
		}
	}GPPUNIT_INSTANCE;
}
