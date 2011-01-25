#include "src\Matchers.h"

#include "AutoRun.h"

#include <string.h>

namespace TestEqualTo{
	using gppUnit::equal_to;
	using gppUnit::MatcherResult;

	class IntAndLong: public Auto::TestCase{
		template<typename MATCHER, typename ACTUAL>
		void That(const ACTUAL& actual, MATCHER m){
			MatcherResult result=m.match(actual);
			confirm.equals(true,result.result,"result is true");
			confirm.equals("'1'\n",result.description(),"description is '1'");
		}
		template<typename MATCHER, typename ACTUAL>
		void MisMatch(const ACTUAL& actual, MATCHER m){
			MatcherResult result=m.match(actual);
			confirm.equals(false,result.result,"result is false");
			confirm.equals("'1'\n",result.description(),"description is '1'");
		}
		void test(){
			int actual=1;
			long expected=1;
			That(actual,equal_to(expected));

			actual=2;
			MisMatch(actual,equal_to(expected));
			//expect.fail("First Failing Test");
		}
	}GPPUNIT_INSTANCE;
	class StringTest: public Auto::TestCase{
		template<typename MATCHER, typename ACTUAL>
		void That(const ACTUAL& actual, MATCHER m){
			MatcherResult result=m.match(actual);
			confirm.equals(true,result.result,"result is true");
			confirm.equals("string '1'\n",result.description(),"description is '1'");
		}
		void test(void){
			const char* actual="1";
			char expected[100];
			strcpy(expected,actual);
			That(actual,equal_to(expected));
		}
	}GPPUNIT_INSTANCE;
	class StringTestFails: public Auto::TestCase{
		template<typename MATCHER, typename ACTUAL>
		void MisMatch(const ACTUAL& actual, MATCHER m){
			MatcherResult result=m.match(actual);
			confirm.equals(false,result.result,"result is false");
			confirm.equals("string '2'\n",result.description(),"description is '2'");
		}
		void test(void){
			const char* actual="1";
			char expected[100];
			strcpy(expected,actual);
			expected[0]='2';
			MisMatch(actual,equal_to(expected));
		}
	}GPPUNIT_INSTANCE;
}
