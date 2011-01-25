#include "AutoRun.h"

namespace gppUnit{
	struct MatcherResult{
		bool result;

		MatcherResult(): result(false) {}
	};
	struct is_null{
		MatcherResult match(const void* actual) const {
			MatcherResult result;
			result.result= (actual==0);
			return result;
		}
	};
}

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
		}
	}GPPUNIT_INSTANCE;
}
