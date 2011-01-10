#include "AutoRun.h"

//using Auto::Testcase;

namespace gppUnit{
	class TestCase{

	};
}

class Test: public Auto::TestCase{
	void test(){ expect.fail("Failing TestCase");}
}GPPUNIT_INSTANCE;