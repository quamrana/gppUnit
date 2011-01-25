#include "src\Matchers.h"

#include "AutoRun.h"

namespace TestIsNull{
	class FalseResult: public Auto::TestCase{
		gppUnit::is_null matcher;
		gppUnit::MatcherResult result;
		void givenMatcher(){
		}
		void whenMatchedWith(void* value){
			result=matcher.match(value);
		}
		void thenResultIsFalse(){
			confirm.isFalse(result.result,"thenResultIsFalse");
		}
		void thenResultIsTrue(){
			confirm.isTrue(result.result,"thenResultIsTrue");
		}
		void test(){
			givenMatcher();
			whenMatchedWith(this);
			thenResultIsFalse();

			whenMatchedWith(0);
			thenResultIsTrue();
			//TODO: add tests for description
		}
	}GPPUNIT_INSTANCE;
}
