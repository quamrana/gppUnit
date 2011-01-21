#include "src\ProjectRunner.h"

#include "TestUtilities.h"

namespace Utilities{
	void TestCaseCaller::whenCalled(){
		gppUnit::ProjectRunner runner("TestCaseCaller",*notify,*timer,cases);
		projectReturn=runner.run();
	}
}
