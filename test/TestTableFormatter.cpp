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
#include "TableFormatting\TableFormatting.h"

#include "AutoRun.h"


namespace TestTableFormatter{
	using gppUnit::equals;

	typedef std::vector<std::string> strvec;

	class TestBase: public Auto::TestCase{
		gppUnit::TableFormatter tf;
	protected:
		gppUnit::TableFormatter& f(){ return tf; }
		void givenTable(){ tf.clear(); }

		void thenTableIsBlank(){
			confirm.that(tf.toString(),equals(""),"Formatter is blank");
		}
		void thenTableEquals(const std::string& value, const std::string& message){
			confirm.that(tf.toString(),equals(value),message.c_str());
		}
		void thenTableEquals(const strvec& value, const std::string& message){
			if (value!=tf.toVector()){
				confirm.fail(message.c_str());
			}
			// TODO: compare vectors
			//confirm.equals(value,tf.toVector(),message.c_str());
		}
	};
namespace SingleLines{
	using gppUnit::tab;

	class Blank: public TestBase{
		void test(){
			givenTable();
			thenTableIsBlank();
		}
	}GPPUNIT_INSTANCE;
	class NonBlank: public TestBase{
		void test(void){
			givenTable();
			f() << "add";
			thenTableEquals("add\n","Added single string");
		}
	}GPPUNIT_INSTANCE;
	class StreamingStrings: public TestBase{
		void test(void){
			givenTable();
			f() << "add";
			std::string foo="foo";
			f() << foo;
			thenTableEquals("addfoo\n","Streamed another string");
		}
	}GPPUNIT_INSTANCE;
	class StreamingOtherTypes: public TestBase{
		void test(void){
			givenTable();
			std::string foo="foo";
			double pi=3.14;
			f() << "add" << 1 << foo << pi << 'c';

			thenTableEquals("add1foo3.14c\n","Streamed strings, numbers and char");
		}
	}GPPUNIT_INSTANCE;
	class TabsDoNothing: public TestBase{
		void test(void){
			givenTable();
			f() << "add" << tab << "foo" << tab << "bar";

			thenTableEquals("add foo bar\n","Tab Does Nothing");
		}
	}GPPUNIT_INSTANCE;
	class Test2ndPage: public TestBase{
		void test(void){
			givenTable();
			f() << "add";
			givenTable();
			f() << "add";
			thenTableEquals("add\n","2nd page is single string");
		}
	}GPPUNIT_INSTANCE;
}
namespace MultipleLines{
	using gppUnit::tab;
	using gppUnit::endl;

	class ShortLines: public TestBase{
		void test(void){
			givenTable();
			f() << "add" << endl;
			f() << "add" << endl;
			thenTableEquals("add\nadd\n","Added two lines");
		}
	}GPPUNIT_INSTANCE;
	class VectorOfLines: public TestBase{
		void test(void){
			f() << "add" << endl;
			f() << "add" << endl;

			strvec expected;
			expected.push_back("add");
			expected.push_back("add");
			thenTableEquals(expected,"Vector of two lines");
		}
	}GPPUNIT_INSTANCE;
	class TabExpandsSecondLine: public TestBase{
		void test(void){
			f() << "wide" << tab << "column" << tab << "headings" << endl;
			f() << 1 << tab << 23 << tab << 456 << endl;

			strvec expected;
			expected.push_back("wide column headings");
			expected.push_back("1    23     456");

			thenTableEquals(expected,"Vector of two tabbed lines");
		}
	}GPPUNIT_INSTANCE;
	class TabsAndStdStrings: public TestBase{
		void test(void){
			std::string element="column";
			f() << "wide" << tab << element << tab << "headings" << endl;
			f() << 1 << tab << 23 << tab << 456 << endl;

			strvec expected;
			expected.push_back("wide column headings");
			expected.push_back("1    23     456");

			thenTableEquals(expected,"Vector of two lines");
		}
	}_GPPUNIT_INSTANCE;

}
namespace AppendTable{
	using gppUnit::tab;
	using gppUnit::endl;

	class SecondTableBase: public TestBase{
	protected:
		gppUnit::TableFormatter tf2;
		gppUnit::TableFormatter& f2(){ return tf2; }
		void givenSecondTable(){ tf2.clear(); }

		void whenAppendSecondToFirst(){ f() << f2(); }

	};
	class AppendToBlankTable: public SecondTableBase{
		void test(void){
			givenTable();
			givenSecondTable();
			f2() << "second";
			whenAppendSecondToFirst();
			thenTableEquals("second\n","Added single string");
		}
	}GPPUNIT_INSTANCE;
	class AppendSingleLineToLastLineOfTable: public SecondTableBase{
		void test(void){
			givenTable();
			givenSecondTable();
			f() << "Wide first column" << tab << "Second column" << endl;
			f() << "first" << tab;
			f2() << "second";
			whenAppendSecondToFirst();

			strvec expected;
			expected.push_back("Wide first column Second column");
			expected.push_back("first             second");
			thenTableEquals(expected,"Vector of two lines");
		}
	}GPPUNIT_INSTANCE;
	class AppendMultipleLinesToLastLineOfTable: public SecondTableBase{
		void test(void){
			givenTable();
			givenSecondTable();
			f() << "Wide first column" << tab << "Second column" << endl;
			f() << "first" << tab;
			f2() << "second" << endl;
			f2() << "third" << endl;
			whenAppendSecondToFirst();

			strvec expected;
			expected.push_back("Wide first column Second column");
			expected.push_back("first             second");
			expected.push_back("                  third");
			thenTableEquals(expected,"Vector of two lines");
		}
	}GPPUNIT_INSTANCE;
	class AppendWideColumnsToLastLineOfTableWithNarrowColumns: public SecondTableBase{
		void test(void){
			givenTable();
			givenSecondTable();
			f() << "Several" << tab << "narrow" << tab << "columns" << tab << "previous" << tab << "table" << endl;
			f() << 1 << tab << 2 << tab << 3 << tab << 4 << endl;
			f() << "new" << tab;
			f2() << "sub-table with extremely wide columns" << tab << "don't affect previous section" << endl;
			f2() << "just affect" << tab << "this table" << endl;
			whenAppendSecondToFirst();

			strvec expected;
			expected.push_back("Several narrow columns previous table");
			expected.push_back("1       2      3       4");
			expected.push_back("new     sub-table with extremely wide columns don't affect previous section");
			expected.push_back("        just affect                           this table");
			thenTableEquals(expected,"Vector of two lines - this already works because the stream operator renders the sub-table (SecondTable) to a vector of strings, which are considered to be ends of lines and don't contribute to column widths.");
		}
	}GPPUNIT_INSTANCE;
}

}
