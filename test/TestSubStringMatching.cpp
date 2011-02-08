#include "TestMatchersHelpers.h"
#include "Matchers\SubStringMatchers.h"



namespace TestSubStringMatching{
	using Utilities::MatcherHelper;
	using gppUnit::starts_with;
	using gppUnit::ends_with;
	using gppUnit::contains;

	class BeginsWith: public MatcherHelper{
		void test(){
			That("foo",starts_with("f"),"a string starting with 'f'\n");
			That("bar",!starts_with("f"),"not a string starting with 'f'\n");
			That("bar",!starts_with("doof"),"not a string starting with 'doof'\n");
		}
	}GPPUNIT_INSTANCE;

	class EndsWith: public MatcherHelper{
		void test(){
			That("foo",ends_with("o"),"a string ending with 'o'\n");
			That("bar",!ends_with("o"),"not a string ending with 'o'\n");
			That("bar",!ends_with("doof"),"not a string ending with 'doof'\n");
		}
	}GPPUNIT_INSTANCE;

	class Contains: public MatcherHelper{
		void test(){
			That("bar",contains("b"),"a string that contains 'b'\n");
			That("bar",contains("a"),"a string that contains 'a'\n");
			That("bar",contains("r"),"a string that contains 'r'\n");
			That("bar",!contains("z"),"not a string that contains 'z'\n");
		}
	}GPPUNIT_INSTANCE;

}
