#include "src\TestResult.h"

#include "AutoRun.h"

namespace TestTestResult{
	class Test: public Auto::TestCase{
		gppUnit::TestResult result;
		void givenTestResult(){
			result=gppUnit::TestResult();
		}
		void thenResultIsFalse(){
			confirm.isFalse(result.result,"Result is false by default");
		}
		void thenMessageIsEmpty(){
			confirm.equals("",result.message,"Message is empty");
			confirm.isTrue(result.message.empty(),"Message is empty");
		}
		void thenDescriptionIsEmpty(){
			confirm.isTrue(result.description.empty(),"Description is empty");
		}
		void test(){
			givenTestResult();
			thenResultIsFalse();
			thenMessageIsEmpty();
			thenDescriptionIsEmpty();
		}
	}GPPUNIT_INSTANCE;
}
