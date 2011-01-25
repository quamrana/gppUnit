#include "src\Matchers.h"

#include "AutoRun.h"

#include <string.h>

namespace TestEqualTo{
	using gppUnit::equal_to;
	using gppUnit::MatcherResult;

	class EqualToHelper: public Auto::TestCase{
	protected:
		template<typename MATCHER, typename ACTUAL>
		void That(const ACTUAL& actual, MATCHER m, const char* desc){
			MatcherResult result=m.match(actual);
			confirm.equals(true,result.result,"result is true");
			confirm.equals(desc,result.description(),"description is '1'");
		}
		template<typename MATCHER, typename ACTUAL>
		void MisMatch(const ACTUAL& actual, MATCHER m, const char* desc){
			MatcherResult result=m.match(actual);
			confirm.equals(false,result.result,"result is false");
			confirm.equals(desc,result.description(),"description is '1'");
		}
	};
	class IntAndLong: public EqualToHelper{
		void test(){
			int actual=1;
			long expected=1;
			That(actual,equal_to(expected),"'1'\n");

			actual=2;
			MisMatch(actual,equal_to(expected),"'1'\n");
		}
	}GPPUNIT_INSTANCE;
	class StringTest: public EqualToHelper{
		void test(void){
			const char* actual="1";
			char expected[100];
			strcpy(expected,actual);
			That(actual,equal_to(expected),"string '1'\n");
		}
	}GPPUNIT_INSTANCE;
	class StringTestFails: public EqualToHelper{
		void test(void){
			const char* actual="2";
			char expected[100];
			strcpy(expected,actual);
			expected[0]='1';
			MisMatch(actual,equal_to(expected),"string '1'\n");
		}
	}GPPUNIT_INSTANCE;
}

namespace StringMismatchTests {
	using gppUnit::equal_to;
	using TestEqualTo::EqualToHelper;

	class TestStringDescriptionTypeSHORT2: public EqualToHelper{
		void test(void){
			const char* actual="1";
			const char* sample="1234567890";
			char expected[150];
			strcpy(expected,sample);
			for(int i=0;i<10;++i) { strcat(expected,sample); }

			MisMatch(actual,equal_to(expected),"string '1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567...'\n");
		}
	}GPPUNIT_INSTANCE;
	class TestStringDescriptionTypeMEDIUM1: public EqualToHelper{
		void test(void){
			const char* actual="abcdefghijkl";
			char expected[100];
			strcpy(expected,actual);
			expected[6]='h';
			MisMatch(actual,equal_to(expected),
				"string         'abcdefhhijkl'\n"
				"first mismatch        ^\n"
				"index 6        -------|\n"
				"actual         'abcdefghijkl'\n"
				);
		}
	}GPPUNIT_INSTANCE;
	class TestStringDescriptionTypeMEDIUM2: public EqualToHelper{
		void test(void){
			const char* actual="abcdefghijkl";
			char expected[130];
			strcpy(expected,actual);
			for(int i=0;i<9;++i) { strcat(expected,actual); }

			MisMatch(actual,equal_to(expected),
							//            1         2         3         4         5         6         7         8         9        10
							//   1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
				"string         'abcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijkla...'\n"
				"first mismatch              ^\n"
				"index 12       -------------|\n"
				"actual         'abcdefghijkl'\n"
				);
		}
	}GPPUNIT_INSTANCE;
	class TestStringDescriptionTypeLONG: public EqualToHelper{
		void test(void){
			const char* sample="abcdefghijkl";
			char actual[250];
			char expected[250];
			strcpy(actual,sample);
			for(int i=0;i<19;++i) { strcat(actual,sample); }
			strcpy(expected,actual);
			expected[150]='x';

			MisMatch(actual,equal_to(expected),
							//            1         2         3         4         5         6         7         8         9        10
							//   1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
				"string         '...hijklabcdefghijklabcdefghijklabcdefghijklabcdefxhijklabcdefghijklabcdefghijklabcdefghijklabcde...'\n"
				"first mismatch                                                    ^\n"
				"index 150      ---------------------------------------------------|\n"
				"actual         '...hijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcde...'\n"
				);
		}
	}GPPUNIT_INSTANCE;
}

