#include "AutoRun.h"

//using Auto::Testcase;

namespace gppUnit{
	class TestCase{
	public:
		virtual void setup(){}
		virtual void test()=0;
		virtual void teardown(){}
	};
}
namespace TestTestCase {
	class MockTestCase: public gppUnit::TestCase{
		void test(){}
	public:
		std::string result(){return "x";}
	};
	class Test: public Auto::TestCase{
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
			if(testcase.result()=="setup.test.teardown."){
				confirm.pass(testcase.result().c_str());
			} else {
				confirm.fail(testcase.result().c_str());
			}
		}
		void test(){ 
			//expect.fail("Failing TestCase");
			givenMockTestCase();
			whenCalled();
			thenAllThreeMethodsCalled();
		}
	}GPPUNIT_INSTANCE;

}
