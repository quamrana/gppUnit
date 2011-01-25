#include "src\TableFormatting.h"

#include "AutoRun.h"


namespace TestTableFormatter{

	typedef std::vector<std::string> strvec;

	class TestBase: public Auto::TestCase{
		gppUnit::TableFormatter tf;
	protected:
		gppUnit::TableFormatter& f(){ return tf; }
		void givenTable(){ tf.clear(); }

		void thenTableIsBlank(){
			confirm.equals("",tf.toString(),"Formatter is blank");
		}
		void thenTableEquals(const std::string& value, const std::string& message){
			confirm.equals(value.c_str(),tf.toString(),message.c_str());
		}
		void thenTableEquals(const strvec& value, const std::string& message){
			if (value!=tf.toVector()){
				confirm.fail(message.c_str());
			}
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
namespace ColumnElements{
	class PublicInterface: public Auto::TestCase{
		void test(void){
			gppUnit::Column c("foo");

			confirm.equals("foo",c.toString());
			confirm.equals(size_t(3),c.size());
			confirm.equals("foo   ",c.toString(6));
		}
	}GPPUNIT_INSTANCE;
	class Copying: public Auto::TestCase{
		void TestEquals(gppUnit::Column copied, const gppUnit::Column& refd) {
			confirm.equals(copied.toString(),refd.toString());
		}
		void test(void){
			gppUnit::Column c("foo");
			gppUnit::Column d("foo");
			gppUnit::Column f("bar");

			confirm.equals(c.toString(),d.toString());
			confirm.isFalse(c.toString()==f.toString(),"Columns c(foo) and f(bar) are not equal");

			TestEquals(c,d);
		}
	}GPPUNIT_INSTANCE;
}
namespace LineElements {
	class LineHelper: public Auto::TestCase{
		gppUnit::Line line;
		std::vector<size_t> sizes;
	protected:
		void givenLine(){ line.clear(); }
		void givenSizes(){ sizes.clear(); }

		void whenAppend(const std::string& str){ line.append(str); }
		void whenTab(){ line.tab(); }
		void addSize(size_t size){ sizes.push_back(size); }
		void whenUpdateSizes(){ line.update(sizes); }

		void thenLineEquals(const std::string& str){ 
			std::string msg="Line should equal: ";
			msg+=str;
			confirm.equals(str,line.toString(),msg.c_str());
		}
		void sizedLineEquals(const std::string& str){ 
			std::string msg="Line should equal: ";
			msg+=str;
			confirm.equals(str,line.toString(sizes),msg.c_str());
		}

		void thenSizesHas(size_t elements){
			expect.equals(elements,sizes.size());
		}
		void thenSizesHasAt(size_t index,size_t value){
			std::stringstream strm;
			strm << "Index: " << index << " should contain value: " << value;
			confirm.equals(value,sizes[index],strm.str().c_str());
		}
	};
	class PublicInterface: public LineHelper{
		void test(void){
			givenLine();
			thenLineEquals("");

			whenAppend("foo");
			thenLineEquals("foo");

			whenAppend("foo");
			thenLineEquals("foofoo");
		}
	}GPPUNIT_INSTANCE;
	class FormattedOutput: public LineHelper{
		void test(void){
			givenLine();

			whenAppend("foo");
			whenTab();
			whenAppend("foo");
			thenLineEquals("foofoo");

			givenSizes();
			sizedLineEquals("foofoo");

			addSize(4);
			sizedLineEquals("foo foo");

			addSize(6);
			sizedLineEquals("foo foo");

			givenLine();
			thenLineEquals("");
			sizedLineEquals("");
		}
	}GPPUNIT_INSTANCE;
	class UpdateSizes: public LineHelper{
		void test(void){
			givenLine();

			whenAppend("foo");
			whenTab();
			whenAppend("doof");

			givenSizes();
			whenUpdateSizes();
			thenSizesHas(2);

			thenSizesHasAt(0,3);
			thenSizesHasAt(1,0);
		}
	}GPPUNIT_INSTANCE;
	class TestLineCopying: public Auto::TestCase{
		std::string copy(const gppUnit::Line& line){
			gppUnit::Line line2(line);
			return line2.toString();
		}
		void test(void){
			gppUnit::Line line;
			line.append("line");
			confirm.equals("line",copy(line),"Copy retains contents");
		}
	}GPPUNIT_INSTANCE;
}
}
