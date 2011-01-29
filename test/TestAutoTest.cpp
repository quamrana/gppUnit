#include "src\AutoTest.h"

#include "TestUtilities.h"

namespace TestAutoTest{
	using gppUnit::equals;

	// Warning: NEVER make an instance of MockTest on the stack or globally - always make an instance on the HEAP!!!
	class MockTest: public Utilities::MockTestCase, public gppUnit::AutoTest{
		void test(){}	
	};
	class Test: public Auto::TestCase{
		gppUnit::TestCaseList mockList;
		gppUnit::TestCase* mock;
		MockTest* actualMock;
		void setup(){
			// Give the global AutoList our list
			gppUnit::globalAutoList().autoTests(mockList);
			// Make a new test that registers itself
			mock=actualMock=new MockTest();
		}
		void test(){
			expect.that(mock,!gppUnit::is_null(),"Setup produced a test instance");
			expect.that(mockList.size(),equals(1),"A test is registered with mockList");
			confirm.that(gppUnit::autoTests().size(),equals(1),"A test is registered with mockList");
			confirm.that(mockList.front(),equals((gppUnit::PrototypeTestCase*)mock),"mock is at front");
		}
		void teardown(){
			gppUnit::globalAutoList().autoTests(Utilities::dummyTestCaseList);
			delete actualMock;
		}
	}GPPUNIT_INSTANCE;
}

