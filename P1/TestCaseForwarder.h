#ifndef TESTCASEFORWARDER_H_0C73766D_442B_49A1_83B4_262BCDF83A3C
#define TESTCASEFORWARDER_H_0C73766D_442B_49A1_83B4_262BCDF83A3C

#include "TestCase.h"

namespace Prototype1{
	namespace Internal{

		class TestCaseForwarder: public TestCase{
			TestCase* testcase;
			void setup(){ testcase->setup(); }
			void test(){ testcase->test(); }
			void teardown(){ testcase->teardown(); }
		public:
			TestCaseForwarder():testcase(0){}
			void set(TestCase* nextCase){ testcase=nextCase; }
		};
	}
}

#endif // TESTCASEFORWARDER_H_0C73766D_442B_49A1_83B4_262BCDF83A3C
