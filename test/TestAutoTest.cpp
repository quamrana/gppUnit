#include "src\AutoTest.h"

#include "TestUtilities.h"

namespace TestAutoTest{
	// Warning: NEVER make an instance of MockTest on the stack or globally - always make an instance on the stack!!!
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
			expect.isTrue(mock!=0,"Setup produced a test instance");
			expect.equals(1,mockList.size(),"A test is registered with mockList");
			confirm.isTrue(mock==mockList.front(),"mock is at front");
		}
		void teardown(){
			gppUnit::globalAutoList().autoTests(Utilities::dummyTestCaseList);
			delete actualMock;
		}
	}GPPUNIT_INSTANCE;
}

