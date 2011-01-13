#include "TestUtilities.h"

#include "src\Notification.h"
#include "src\MethodNames.h"
#include "src\MethodDescription.h"

#include <sstream>

namespace TestStartEndMethod{
	class MockTestCaseVariableResults: public Utilities::MockTestCase{
		int number;
		void test(){ 
			for(int i=0;i<number;++i){
				reporter->Result(); 
			}
		}
	public:
		explicit MockTestCaseVariableResults(int n):number(n){}
	};

	std::string setuptestteardownString(int results){
		std::stringstream strm;
		strm << gppUnit::setupMethodName() << ".0.end." <<
			gppUnit::testMethodName() << '.' << results << ".end." <<
			gppUnit::teardownMethodName() << ".0.end."; 
		return strm.str();
	}

	class TestNumResultsBase: public Utilities::TestCaseCaller, gppUnit::Notification{
		std::stringstream collect;
		MockTestCaseVariableResults* testcase;
		const gppUnit::MethodDescription* description;

		void StartMethod(const gppUnit::MethodDescription& desc){
			description=&desc;
			collect << desc.name();
		}
		void EndMethod(){
			collect << '.' << description->results() << '.' << "end.";
		}
		void teardown(){
			delete testcase;
		}
	protected:
		void givenMockTestCase(int n){
			testcase=new MockTestCaseVariableResults(n);
			add(*testcase);
			givenNotification(this);
		}
		void thenEachMethodStartedAndEndedWithNumResults(int results){
			confirm.equals(setuptestteardownString(results),collect.str(),"Should have called three methods");
		}
	};
	template<int NUM>
	class TestNumResults: TestNumResultsBase{
	protected:
		void test(){
			givenMockTestCase(NUM);
			whenCalled();
			thenEachMethodStartedAndEndedWithNumResults(NUM);
		}
	};

	class TestNoResults: public TestNumResults<0>{
	}GPPUNIT_INSTANCE;

	class TestOneResult: public TestNumResults<1>{
	}GPPUNIT_INSTANCE;

	class TestTwoResults: public TestNumResults<2>{
	}GPPUNIT_INSTANCE;
}
