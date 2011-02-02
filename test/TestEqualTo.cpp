/*
Copyright (c) 2011 Andrew Wall

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "TestMatchersHelpers.h"

#include <string.h>

namespace TestEqualTo{
	using gppUnit::equal_to;
	using Utilities::MatcherHelper;

	class IntAndLong: public MatcherHelper{
		void test(){
			int actual=1;
			long expected=1;
			That(actual,equal_to(expected),"'1'\n");

			actual=2;
			MisMatch(actual,equal_to(expected),"'1'\n");

			That(actual,is_not(equal_to(expected)),"not '1'\n");
			That(actual,!equal_to(expected),"not '1'\n");
		}
	}GPPUNIT_INSTANCE;
	class DoubleNegative: public MatcherHelper{
		void test(){
			int actual=1;
			long expected=1;
			That(actual,equal_to(expected),"'1'\n");

			That(actual,is_not(is_not(equal_to(expected))),"'1'\n");
		}
	}GPPUNIT_INSTANCE;

	class TestFloatEqualsWithin: public MatcherHelper{
		void test(){
			float floatsmall=2.05f;
			float floatlarge=2.06f;

			That(floatsmall,equal_to(floatlarge).within(0.1),"'2.06' within '0.1'\n");
		}
	}GPPUNIT_INSTANCE;
	class TestDoubleEqualsWithin: public MatcherHelper{
		void test(){
			double doublesmall=2.05;
			double doublelarge=2.06;

			That(doublelarge,equal_to(doublesmall).within(0.1),"'2.05' within '0.1'\n");
		}
	}GPPUNIT_INSTANCE;

	class StringTest: public MatcherHelper{
		void test(void){
			const char* actual="1";
			char expected[100];
			strcpy(expected,actual);
			That(actual,equal_to(expected),"string '1'\n");
		}
	}GPPUNIT_INSTANCE;
	class StringTestFails: public MatcherHelper{
		void test(void){
			const char* actual="2";
			char expected[100];
			strcpy(expected,actual);
			expected[0]='1';
			MisMatch(actual,equal_to(expected),"string '1'\n");
			That(actual,!equal_to(expected),"not string '1'\n");
		}
	}GPPUNIT_INSTANCE;
}

namespace StringMismatchTests {
	using gppUnit::equal_to;
	using Utilities::MatcherHelper;

	class TestStringDescriptionTypeSHORT2: public MatcherHelper{
		void test(void){
			const char* actual="1";
			const char* sample="1234567890";
			char expected[150];
			strcpy(expected,sample);
			for(int i=0;i<10;++i) { strcat(expected,sample); }

			MisMatch(actual,equal_to(expected),"string '1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567...'\n");
		}
	}GPPUNIT_INSTANCE;
	class TestStringDescriptionTypeMEDIUM1: public MatcherHelper{
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
	class TestStringDescriptionTypeMEDIUM2: public MatcherHelper{
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
	class TestStringDescriptionTypeLONG: public MatcherHelper{
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
			That(actual,!equal_to(expected),
							//            1         2         3         4         5         6         7         8         9        10
							//   1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
				"not string         '...hijklabcdefghijklabcdefghijklabcdefghijklabcdefxhijklabcdefghijklabcdefghijklabcdefghijklabcde...'\n"
				"    first mismatch                                                    ^\n"
				"    index 150      ---------------------------------------------------|\n"
				"    actual         '...hijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcdefghijklabcde...'\n"
				);
		}
	}GPPUNIT_INSTANCE;
}

