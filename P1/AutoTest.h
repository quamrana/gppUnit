#ifndef AUTOTEST_H_78A02A6D_558D_404F_9FA5_0C097173075F
#define AUTOTEST_H_78A02A6D_558D_404F_9FA5_0C097173075F

#include "PrototypeTestCase.h"
#include "ProjectFixture.h"

namespace Prototype1{
	namespace Auto{

		TestCaseList& autoTests();

		class AutoTest: public virtual PrototypeTestCase{
		public:
			AutoTest();
		};
	}
}

#endif // AUTOTEST_H_78A02A6D_558D_404F_9FA5_0C097173075F
