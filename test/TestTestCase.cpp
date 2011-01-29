#include "src\MethodNames.h"

#include "TestUtilities.h"

#include <sstream>

namespace TestTestCase {
	using gppUnit::equals;

	class MockTestCase: public Utilities::MockTestCase{
		std::stringstream collect;
		void setup(){ collect << gppUnit::setupMethodName() << '.'; }
		void test(){ collect << gppUnit::testMethodName() << '.'; }
		void teardown(){ collect << gppUnit::teardownMethodName() << '.'; }
	public:
		std::string result(){return collect.str();}
	};

	std::string setuptestteardownString(){ 
			return std::string(gppUnit::setupMethodName())+'.'+
			gppUnit::testMethodName()+'.'+
			gppUnit::teardownMethodName()+'.'; 
}

	class TestMethodNames: public Auto::TestCase{
		void test(){

			confirm.that(gppUnit::setupMethodName(),equals("setup"),"Should be setup");

			confirm.that(gppUnit::testMethodName(),equals("test"),"Should be test");

			confirm.that(gppUnit::teardownMethodName(),equals("teardown"),"Should be teardown");
		}
	}GPPUNIT_INSTANCE;

	class AllThreeMethodsCalled: public Utilities::TestCaseCaller{
		MockTestCase testcase;

		void givenMockTestCase(){
			add(testcase);
		}
		void thenAllThreeMethodsCalled(){
			confirm.that(testcase.result(),equals(setuptestteardownString()),"Should have called three methods");
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
			confirm.that(actual,equals(expected),"Should have called six methods");
		}
		void test(){
			givenTwoTestCases();
			whenCalled();
			thenSixMethodsCalled();
		}
	}GPPUNIT_INSTANCE;
}
