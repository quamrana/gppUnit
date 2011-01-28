#include "src\Notification.h"
#include "src\MethodNames.h"
#include "src\MethodDescription.h"
#include "src\ReportResult.h"
#include "src\TestResult.h"

#include "TestUtilities.h"

#include <sstream>

namespace TestStartEndMethod{
	class MockTestCaseVariableResults: public Utilities::MockTestCase{
		int number;
		void test(){ 
			gppUnit::TestResult result;
			for(int i=0;i<number;++i){
				reporter->Report(result); 
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
	protected:
		std::stringstream collect;
	private:
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
		void thenResultRecordedInTest(){
			confirm.isTrue(collect.str().find("test.0.1.end")!=std::string::npos,"Test result is 0.1");
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
	public:
		~TestNumResults(){}
	};

	class TestNoResults: public TestNumResults<0>{
	public:
		~TestNoResults(){}
	}GPPUNIT_INSTANCE;

	class TestOneResult: public TestNumResults<1>{
	public:
		~TestOneResult(){}
	}GPPUNIT_INSTANCE;

	class TestTwoResults: public TestNumResults<2>{
	public:
		~TestTwoResults(){}
	}GPPUNIT_INSTANCE;

	class TestResultContentTrue: public TestNumResultsBase{
		virtual void Result(const gppUnit::TestResult& result){
			collect << '.' << result.result;
		}
		void test(){
			givenMockTestCase(1);
			whenCalled();
			thenResultRecordedInTest();
		}
	}GPPUNIT_INSTANCE;
}

