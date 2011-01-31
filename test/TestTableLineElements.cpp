#include "TableFormatting\TableLine.h"

#include "AutoRun.h"

namespace TestTableLineElements {
	using gppUnit::equals;

	class LineHelper: public Auto::TestCase{
		gppUnit::TableLine line;
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
			confirm.that(line.toString(),equals(str),msg.c_str());
		}
		void sizedLineEquals(const std::string& str){ 
			std::string msg="Line should equal: ";
			msg+=str;
			confirm.that(line.toString(sizes),equals(str),msg.c_str());
		}

		void thenSizesHas(size_t elements){
			expect.that(sizes.size(),equals(elements),"thenSizesHas");
		}
		void thenSizesHasAt(size_t index,size_t value){
			std::stringstream strm;
			strm << "Index: " << index << " should contain value: " << value;
			confirm.that(sizes[index],equals(value),strm.str().c_str());
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
		std::string copy(const gppUnit::TableLine& line){
			gppUnit::TableLine line2(line);
			return line2.toString();
		}
		void test(void){
			gppUnit::TableLine line;
			line.append("line");
			confirm.that(copy(line),equals("line"),"Copy retains contents");
		}
	}GPPUNIT_INSTANCE;
}
