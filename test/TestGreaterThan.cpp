#include "TestMatchersHelpers.h"

namespace TestGreaterThan{
	using Utilities::MatcherHelper;
	using gppUnit::greater_than;

	class Test: public MatcherHelper{
		void test(){
			int integer=1;
			long longint=2;
			signed char schar=-4;
			std::vector<MatcherHelper*> vec;

			That(longint,greater_than(integer),"a value greater than '1'\n");
			That(integer,greater_than(vec.size()),"a value greater than '0'\n");
			That(longint,greater_than(schar),"a value greater than '-4'\n");
			That(vec.size(),greater_than(schar),"a value greater than '-4'\n");
		}
	}GPPUNIT_INSTANCE;
}
