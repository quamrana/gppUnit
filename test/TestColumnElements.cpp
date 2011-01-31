#include "TableFormatting\Column.h"

#include "AutoRun.h"

namespace ColumnElements{
	using gppUnit::equals;

	class PublicInterface: public Auto::TestCase{
		void test(void){
			gppUnit::Column c("foo");

			confirm.that(c.toString(),equals("foo"));
			confirm.that(c.size(),equals(3));
			confirm.that(c.toString(6),equals("foo   "));
		}
	}GPPUNIT_INSTANCE;
	class Copying: public Auto::TestCase{
		void TestEquals(gppUnit::Column copied, const gppUnit::Column& refd) {
			confirm.that(copied.toString(),equals(refd.toString()));
		}
		void test(void){
			gppUnit::Column c("foo");
			gppUnit::Column d("foo");
			gppUnit::Column f("bar");

			confirm.that(c.toString(),equals(d.toString()));
			confirm.that(c.toString(),!equals(f.toString()),"Columns c(foo) and f(bar) are not equal");

			TestEquals(c,d);
		}
	}GPPUNIT_INSTANCE;
}
