#include "src\TableFormatting.h"

#include "AutoRun.h"


namespace TestTableFormatter{

	class TestBase: public Auto::TestCase{
		gppUnit::TableFormatter tf;
	protected:
		gppUnit::TableFormatter& f(){ return tf; }
		void givenTable(){ tf.clear(); }

		void thenTableIsBlank(){
			confirm.equals("",tf.toString(),"Formatter is blank");
		}
		//void thenTableEquals(const std::string& value, const std::string message){
		//	assert.equals(value.c_str(),tf.toString(),message.c_str());
		//}
		//void thenTableEquals(const strvec& value, const std::string message){
		//	assert.equals(value,tf.toVector(),message.c_str());
		//}
	};
namespace SingleLines{
	class Blank: public TestBase{
		void test(){
			givenTable();
			thenTableIsBlank();
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
