#include "src\TestResult.h"

#include "AutoRun.h"

namespace TestTestResult{
	using gppUnit::equals;

	class Defaults: public Auto::TestCase{
		gppUnit::TestResult result;
		void givenTestResult(){
			result=gppUnit::TestResult();
		}
		void thenResultIsFalse(){
			confirm.isFalse(result.result,"Result is false by default");
		}
		void thenMessageIsEmpty(){
			confirm.that(result.message,equals(""),"Message is empty");
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
