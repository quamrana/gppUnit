#include "TestMatchersHelpers.h"
#include "Matchers\Matchers.h"

#include "AutoRun.h"

namespace TestIsNull{
	using Utilities::MatcherHelper;
	using gppUnit::is_null;

	class Test: public MatcherHelper{
		void test(){
			That(0,is_null(),"is null\n");
			MisMatch(this,is_null(),"is null\n");
			That(this,!is_null(),"not is null\n");
			MisMatch(0,!is_null(),"not is null\n");
		}
	}GPPUNIT_INSTANCE;
}
