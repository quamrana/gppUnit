#include "AutoMain.h"
#include "AutoRunner.h"
#include "MethodTimer.h"
#include "AutoTest.h"
#include "AutoOptions.h"

namespace gppUnit {

	// AutoMain defaults AutoRunner to the static MethodTimer,
	// but allows the user to override this.
	bool AutoMain() {
		AutoRunner runner;
		runner << "AutoMain" << MethodTimer::getTimer();
		AutoOptions(runner);
		return runner.run(autoTests());
	}
}

